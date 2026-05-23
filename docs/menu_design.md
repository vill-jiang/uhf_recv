
# UHF 接收机菜单系统设计文档

## 一、面临的问题

本项目运行在 **STC8H1K17** (8051 内核) 单片机上，主频 24MHz，资源极度受限：

| 约束 | 具体限制 |
|------|---------|
| RAM (xdata) | 仅 1KB，所有全局变量共享 |
| ROM (code) | 17KB Flash，需存放程序 + 常量数据 |
| 栈深度 | 8051 idata 栈仅 128 字节 |
| 显示 | SSD1106 OLED 128×64，6×8 字体下仅 21 列 × 8 行 |
| 输入 | 单个旋转编码器（旋转 + 按键） |
| 菜单项数量 | 29 个菜单项，含 3 个子菜单，15 段 EQ 参数 |

### 核心矛盾

1. **ROM 空间紧张**：菜单的字符串、值范围描述等静态数据如果以 C 结构体硬编码，编译器会将其放入 code 段，但手动维护困难且容易出错。
2. **RAM 极度稀缺**：不能为每个菜单项分配独立的值存储结构体，否则 RAM 会迅速耗尽。
3. **多通道复用**：A/B 两个通道共享相同的菜单结构（频率范围不同除外），需要用最小代价实现通道切换。
4. **可维护性**：菜单项的增删改需要同步修改字符串表、值类型表、菜单项索引等多处数据，手动维护极易出错。

### 解决思路

采用 **"离线生成 + 运行时解释"** 的架构：

- **离线**：Python 脚本 (`gen_eeprom_bin.py`) 从声明式配置生成紧凑的二进制数据（字符串表、值类型表、菜单项表），烧录到 EEPROM/code 区。
- **运行时**：C 代码通过偏移量索引访问只读数据，用一个扁平的 `int8_t val_list[]` 数组存储所有可变值，实现数据与逻辑的彻底解耦。

---

## 二、整体架构

```
┌─────────────────────────────────────────────────────────────┐
│                    gen_eeprom_bin.py                        │
│  (声明式配置 → 二进制数据 → eeprom_bin_data.h/.c)             │
└──────────────────────────┬──────────────────────────────────┘
                           │ 生成
                           ▼
┌──────────────────────────────────────────────────────────────┐
│              EEPROM / Code 区 (只读)                         │
│  ┌───────────────┬────────────────────┬─────────────────────┐│
│  │static_str_data│static_val_type_data│static_menu_item_data││
│  │  (265 Bytes)  │   (118 Bytes)      │    (87 Bytes)       ││
│  └───────────────┴────────────────────┴─────────────────────┘│
└──────────────────────────┬───────────────────────────────────┘
                           │ 偏移量索引
                           ▼
┌─────────────────────────────────────────────────────────────┐
│                   menu.c 运行时引擎                          │
│  ┌────────────┐  ┌────────────┐  ┌──────────────────┐       │
│  │ menu_input │→ │ menu_draw  │→ │ menu_value_change│       │
│  └────────────┘  └────────────┘  └──────────────────┘       │
│         ↕                                    ↕              │
│  ┌────────────────────────────────────────────┐             │
│  │  val_list[MENU_VAL_DATA_LEN] (xdata RAM)   │             │
│  │  ch_a_val_list / ch_b_val_list (27 Bytes)  │             │
│  └────────────────────────────────────────────┘             │
└─────────────────────────────────────────────────────────────┘
```

---

## 三、各模块设计详解

### 3.1 静态字符串表 (`static_str_data`)

#### 存储格式

```
[len][char0][char1]...[charN][0x00]  ← 每个字符串
```

- `offset - 1` 处存放字符串长度（不含 `\0`）
- `offset` 处开始是实际字符数据，以 `\0` 结尾

#### 访问宏

```c
#define get_static_string(offset)     (static_str_data + (offset))
#define get_static_string_len(offset) (static_str_data[(offset) - 1])
```

#### 设计优点

- 字符串共享：多个菜单项可引用同一个字符串偏移（如 `FreqKhz` 被 A/B 频率共用）
- 零拷贝：直接返回 code 区指针给 OLED 驱动，无需 RAM 缓冲
- 编译期确定：所有 `STATIC_STR_xxx_OFFSET` 宏由 Python 自动生成

#### Python 生成逻辑

```python
menu_static_str_map = {
    'RETURN': '-',
    'PrefixChar': '<""">',   # 按 MENU_ITEM_TYPE_xxx 索引取前导字符
    'FreqKhz': 'FreqKhz',
    'Volume': 'Volume',
    ...
}
```

遍历字典，依次写入 `[len][data][0x00]`，记录每个字符串的起始偏移。

---

### 3.2 值类型描述表 (`static_val_type_data`)

每个菜单项的值约束信息紧凑排列在此表中，根据类型不同有不同的结构：

| 类型 | 结构体 | 字节数 | 字段说明 |
|------|--------|--------|---------|
| INT8 | `val_type_int8_t` | 4 | `cur_val_idx`(1) + `min`(1) + `max`(1) + `step`(1) |
| INT32 | `val_type_int32_t` | 13 | `cur_val_idx`(1) + `min`(4) + `max`(4) + `step`(4) |
| STRENUM | `val_type_str_t` | 3 | `cur_val_idx`(1) + `first_str`(1) + `str_count`(1) |
| SUBMENU | 子菜单索引 | 1 | 指向 `sub_menu_def_register[]` 的索引 |

#### 关键字段 `cur_val_idx`

这是整个解耦设计的核心——它不存储值本身，而是存储 **值在 `val_list[]` 数组中的下标**。

```c
// 运行时读取值：
int8_t current_volume = val_list[val_ptr->cur_val_idx];  // cur_val_idx = 4
```

#### 访问宏

```c
#define get_static_val_type(type, offset) \
    ((const type __code *)(static_val_type_data + (offset)))
```

通过 `menu_item_t.val_offset` 定位到对应的值类型描述。

---

### 3.3 菜单项表 (`static_menu_item_data`)

每个菜单项固定 3 字节：

```
[type][name_offset][val_offset]
```

| 字段 | 大小 | 说明 |
|------|------|------|
| `type` | 1 Byte | `MENU_ITEM_TYPE_BACK/INT8/INT32/STRENUM/SUBMENU` |
| `name` | 1 Byte | 指向 `static_str_data` 的偏移 |
| `val_offset` | 1 Byte | 指向 `static_val_type_data` 的偏移 |

#### 访问宏

```c
#define get_static_menu_item(idx) \
    (((const menu_item_t __code *)static_menu_item_data) + (idx))
```

29 个菜单项仅占 87 字节 ROM。

---

### 3.4 菜单定义结构 (`menu_def_t`)

```c
typedef struct menu_def {
    menu_string_offset_t name;           // 菜单标题在字符串表中的偏移
    uint8_t state_bits;                  // 状态位（脏标志 + 选择模式）
    int8_t cur_idx;                      // 当前光标位置
    int8_t first_show_idx;              // 滚动窗口起始位置
    menu_item_idx_t __xdata *first_item_idx;  // 菜单项索引数组指针
    struct menu_def __xdata *parent_menu;     // 父菜单指针
    int8_t count;                        // 菜单项总数
} menu_def_t;
```

#### 状态位设计

```
bit7: MENU_STATE_BITS_MODIFY_DATA  - 数据被修改（用于判断是否需要保存）
bit6: MENU_STATE_BITS_MODIFY_MENU  - 菜单显示需要刷新
bit5: MENU_STATE_BITS_SWITCH_MENU  - 切换了菜单层级（需重绘标题）
bit0: MENU_STATE_BITS_CHOOSE_VALUE - 当前处于值编辑模式
```

这种位域设计将多个布尔状态压缩到 1 字节，极大节省 RAM。

---

### 3.5 菜单上下文 (`menu_ctx_t`)

```c
typedef struct {
    menu_def_t __xdata *root_menu;   // 根菜单（A通道或B通道）
    menu_def_t __xdata *cur_menu;    // 当前展示的菜单层级
    int8_t __xdata *val_list;        // 当前通道的值数组指针
} menu_ctx_t;
```

仅 6 字节 RAM（3 个指针），通过指针切换即可实现 A/B 通道复用：

```c
// 打开A通道菜单
menu_open(&g_menu_ctx, &main_menu_def, ch_a_val_list, STATIC_STR_CHA_OFFSET);
// 打开B通道菜单（复用同一个 main_menu_def）
menu_open(&g_menu_ctx, &main_menu_def, ch_b_val_list, STATIC_STR_CHB_OFFSET);
```

---

### 3.6 EEPROM 数据与用户变量的解耦机制

这是本设计最核心的创新点：

```
┌────────────────────────────────┐     ┌──────────────────────────┐
│   EEPROM / Code 区 (只读)      │     │   xdata RAM (可读写)      │
│                                │     │                          │
│  val_type_int8_t {             │     │  ch_a_val_list[27] = {   │
│    cur_val_idx = 4,  ──────────┼──┐  │    [0..3]: freq_a (int32)│
│    min = 0,                    │  │  │    [4]: volume           │
│    max = 31,                   │  └──┼──► [5]: echo_sw          │
│    step = 1                    │     │    [6]: echo_ratio       │
│  }                             │     │    ...                   │
│                                │     │    [26]: eq_16khz        │
└────────────────────────────────┘     │  }                       │
                                       └──────────────────────────┘
```

#### 解耦原则

1. **只读描述** 存放在 code 区：值的范围、步进、显示名称等元数据
2. **可变数据** 存放在 xdata RAM：一个扁平的 `int8_t` 数组
3. **桥梁**：`cur_val_idx` 字段将两者关联——它告诉运行时引擎"去 `val_list` 的第几个字节读/写当前值"

#### 优势

- **零耦合**：增删菜单项只需修改 Python 配置，不影响 C 运行时代码
- **极省 RAM**：27 字节存储所有通道参数，A/B 通道各一份共 54 字节
- **类型安全**：INT32 类型的值占 4 字节（从 `val_list[0]` 开始），INT8 类型占 1 字节，通过 `cur_val_idx` 精确定位
- **通道隔离**：切换通道只需更换 `val_list` 指针，菜单结构完全复用

#### 值修改流程

```c
// menu_value_change() 中：
// 1. 从 code 区读取值描述
const val_type_int8_t __code *val_ptr = get_static_val_type(val_type_int8_t, item_ptr->val_offset);
// 2. 通过 cur_val_idx 定位到 RAM 中的实际值
int8_t *p_val = &val_list[val_ptr->cur_val_idx];
// 3. 在 min/max/step 约束下循环增减
int8_cicle(p_val, val_ptr->min_val, val_ptr->max_val, val_ptr->step_val, direction);
```

---

### 3.7 输入系统设计

#### 编码器事件定义

```c
#define ENCODER_EVT_CW          0x01    // 顺时针
#define ENCODER_EVT_CCW         0x02    // 逆时针
#define ENCODER_EVT_BTN_DOWN    0x04    // 按下
#define ENCODER_EVT_BTN_UP      0x08    // 松开
#define ENCODER_EVT_BTN_LONG    0x10    // 长按
#define ENCODER_EVT_BTN_LONG_UP 0x20    // 长按松开
```

#### 关键设计：编码器事件与菜单输入统一

菜单系统的 `MENU_INPUT_xxx` 宏与编码器事件值完全一致，避免了转换开销：

```c
#define MENU_INPUT_CW    0x01   // == ENCODER_EVT_CW
#define MENU_INPUT_CCW   0x02   // == ENCODER_EVT_CCW
#define MENU_INPUT_BTN_UP 0x08  // == ENCODER_EVT_BTN_UP
```

#### 状态机流转

```
         ┌──────────────────────────────────────┐
         │           APP_STATE_HOME             │
         │  旋转: 切换焦点 (W→A→B→Power→W)       │
         │  按键: 进入菜单                       │
         └───────────────┬──────────────────────┘
                         │ BTN_UP (焦点在A或B)
                         ▼
         ┌──────────────────────────────────────┐
         │           APP_STATE_MENU             │
         │  旋转: 移动光标 / 修改值               │
         │  按键: 进入子菜单 / 选择值 / 返回      │
         └───────────────┬──────────────────────┘
                         │ 返回到根菜单的 BACK 项
                         ▼
                   回到 APP_STATE_HOME
```

---

### 3.8 显示绘制设计

#### 脏标志驱动的局部刷新

为了减少 I2C 通信量，采用脏标志位控制刷新粒度：

| 标志 | 触发条件 | 刷新范围 |
|------|---------|---------|
| `SWITCH_MENU` | 切换菜单层级 | 重绘标题栏 |
| `MODIFY_MENU` | 任何菜单操作 | 重绘项目列表 + 分数指示 |
| `HOME_STATUS_BIT_INPUT_DIRTY` | 主界面输入 | 重绘频率和焦点 |
| `HOME_STATUS_BIT_SWITCH_DIRTY` | 页面切换 | 全屏清除 |

#### 菜单绘制布局

```
行0: [标题>子标题]          [cur_idx/count]
行1: [#####################]  ← 分割线
行2: ["Volume              31]  ← 菜单项（前缀+名称+值）
行3: [>EQ                  ->]
行4: [>Echo                ->]
行5: [>Exciter             ->]
行6:
行7:
```

- 前缀字符由 `PrefixChar` 字符串按类型索引：`<` = BACK, `"` = INT8/INT32, `"` = STRENUM, `>` = SUBMENU
- 反显（黑底白字）表示当前选中项或值编辑模式

---

### 3.9 Python 代码生成工具 (`gen_eeprom_bin.py`)

#### 输入：声明式配置

```python
menu_static_val_type_list = {
    'Volume': (MENU_ITEM_TYPE_INT8, 'Volume', [4, 0, 31, 1]),
    #          类型                  显示名称    [val_idx, min, max, step]
    'EQ_SUB': (MENU_ITEM_TYPE_SUBMENU, 'EQ', None),
}
```

#### 输出

1. `eeprom_data.bin` — 烧录到 EEPROM 的二进制文件
2. `src/eeprom_bin_data.h` — 所有偏移量宏定义 + extern 声明
3. `src/eeprom_bin_data.c` — 指针常量定义（基于 `MOVC_ShiftAddress`）

#### 自动化保证一致性

修改菜单配置后只需重新运行 Python 脚本，所有索引、偏移量、长度宏自动更新，C 代码无需任何改动。

---

## 四、子菜单机制

### 子菜单注册表

```c
menu_def_t __xdata sub_menu_def_register[MENU_SUBMENU_MAX_IDX];
```

每个子菜单通过 `parent_menu` 指针形成准双向链表结构(实际只存储了子到父指针,父到子采用注册表偏移实现)，支持多级嵌套。当前实现了 3 个子菜单：

| 索引 | 名称 | 包含项目 |
|------|------|---------|
| 0 | EQ | 开关 + 15 段频率增益 |
| 1 | Echo | 开关 + 混响比 + 延迟 |
| 2 | Exciter | 开关 + 奇次谐波 + 偶次谐波 |

### 进入/退出逻辑

```c
// 进入子菜单
ctx->cur_menu = get_sub_menu_def_ptr(item_ptr->val_offset);
init_menu_start_data(ctx->cur_menu);

// 退出子菜单
ctx->cur_menu = ctx->cur_menu->parent_menu;
```

---

## 五、未来提升建议

### 5.1 菜单项动态可见性

某些菜单项应根据开关状态隐藏（如 EQ 关闭时隐藏 15 段频率调节）。可在 `menu_item_t` 中增加 1 字节的 `visible_condition` 字段，指向 `val_list` 中的开关值。

### 5.2 值变更回调

当前值修改后没有立即通知硬件驱动。建议增加回调机制：

```c
typedef void (*val_change_cb_t)(cur_val_idx_t idx, int8_t new_val);
```

在 `menu_value_change()` 末尾调用回调，实时下发参数到 KT0656M 芯片。

### 5.3 长按快速调节

对于 INT32 类型（如频率 740150~769850，步进 10），旋转一圈仅改变 40，调满需要旋转 ~75 圈。建议：

- 长按 + 旋转时自动加大步进（如 ×10 或 ×100）
- 或增加"粗调/细调"模式切换

### 5.4 撤销/恢复功能

在进入菜单时备份 `val_list`（仅 27 字节），若用户选择"取消"则恢复备份，避免误操作。

### 5.5 菜单项排序与分组优化

当前菜单项的 `val_list` 索引是手动分配的。可在 Python 脚本中自动按类型紧凑排列（INT32 对齐到 4 字节边界），进一步减少 `MENU_VAL_DATA_LEN`。
