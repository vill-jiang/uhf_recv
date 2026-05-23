/*---------------------------------------------------------------------*/
/* 设置菜单系统                                                         */
/*---------------------------------------------------------------------*/

#ifndef __MENU_H
#define __MENU_H

#include "type_def.h"

/*---------------------------------------------------------------------*/
/* 屏幕参数 (用户可在编译时覆盖)                                         */
/*---------------------------------------------------------------------*/

#ifndef SCREEN_W
#define SCREEN_W        128
#endif
#ifndef SCREEN_H
#define SCREEN_H        64
#endif
#define CHAR_W          6
#define CHAR_H          8
#define SCREEN_COLS     (SCREEN_W / CHAR_W)   /* 21 */
#define SCREEN_ROWS     (SCREEN_H / CHAR_H)   /* 8  */

/*---------------------------------------------------------------------*/
/* 菜单操作输入,这里的input与编码器定义一致,避免了编码器和菜单系统的转换    */
/*---------------------------------------------------------------------*/

#define MENU_INPUT_NONE        (0x00)    /* 无事件 */
#define MENU_INPUT_CW          (0x01)    /* 顺时针旋转一格 */
#define MENU_INPUT_CCW         (0x02)    /* 逆时针旋转一格 */
#define MENU_INPUT_BTN_DOWN    (0x04)    /* 按键按下 */
#define MENU_INPUT_BTN_UP      (0x08)    /* 按键松开 */
#define MENU_INPUT_BTN_LONG    (0x10)    /* 按键长按 */
#define MENU_INPUT_BTN_LONG_UP (0x20)    /* 按键长按松开 */

#define MENU_INPUT_RET_NONE    (0x00)    /* 菜单继续 */
#define MENU_INPUT_EXIT_SAVE   (0x01)    /* 菜单退出 */
#define MENU_INPUT_EXIT_UNSAVE (0x02)    /* 菜单退出不保存 */

/*---------------------------------------------------------------------*/
/* 菜单条目类型 (4种)                                                    */
/*---------------------------------------------------------------------*/

#define MENU_ITEM_TYPE_BACK      0   /* 返回上一级 */
#define MENU_ITEM_TYPE_INT8      1   /* int8_t 值 (覆盖int8范围) val_type_int8_t */
#define MENU_ITEM_TYPE_INT32     2   /* int32_t 值 (覆盖int8范围) val_type_int32_t */
#define MENU_ITEM_TYPE_STRENUM   3   /* 字符串枚举 (含ON/OFF开关) val_type_str_t */
#define MENU_ITEM_TYPE_SUBMENU   4   /* 嵌套子菜单 menu_def_t */

#define MENU_STATE_BITS_MODIFY_DATA   (0x80)  /* 修改数据置脏,仅指示当前菜单下的非子菜单数据是否修改过 */
#define MENU_STATE_BITS_MODIFY_MENU   (0x40)  /* 操作了菜单项目置脏 */
#define MENU_STATE_BITS_SWITCH_MENU   (0x20)  /* 切换了菜单置脏 */
#define MENU_STATE_BITS_CHOOSE_VALUE  (0x01)  /* 选择了值 */

// 是一个索引到全局字符串表的uint8_t, 0表示空字符串, 1-255表示对应索引的字符串
// 每个字符串都是0结束,以1个字节的长度开始,后跟实际字符数据
typedef uint8_t menu_string_offset_t;

// 是一个索引到菜单数据区的uint8_t
typedef uint8_t cur_val_idx_t;

typedef struct {
    cur_val_idx_t cur_val_idx;  // cur_val_list 的下标, 实际数字占2个字节
    int32_t min_val;
    int32_t max_val;
    int32_t step_val;
} val_type_int32_t;

typedef struct {
    cur_val_idx_t cur_val_idx;  // cur_val_list 的下标, 实际数字占1个字节
    int8_t min_val;
    int8_t max_val;
    int8_t step_val;
} val_type_int8_t;

typedef struct {
    cur_val_idx_t cur_val_idx;  // cur_val_list 的下标, 实际数字占1个字节
    menu_string_offset_t first_str;
    int8_t str_count;
} val_type_str_t;

// 是一个索引到全局静态val_type_xxx_t的uint8_t
typedef uint8_t val_type_offset_t;

typedef struct {
    uint8_t type;  /* MENU_ITEM_TYPE_xx 指示val是什么指针 */
    menu_string_offset_t name;
    val_type_offset_t val_offset;
} menu_item_t;

// 是一个索引到全局静态menu_item_t的uint8_t
typedef uint8_t menu_item_idx_t;

typedef struct menu_def {
    menu_string_offset_t name;  /* 菜单名称 */
    uint8_t state_bits;  /* bit7=修改置脏, bit0=选择了值 */
    int8_t cur_idx;  /* 当前选择的条目索引 (0~count-1) */
    int8_t first_show_idx;  /* 当前显示的第一条索引 (0~count-1) */
    menu_item_idx_t __xdata * first_item_idx;  /* 条目idx列表 */
    struct menu_def __xdata * parent_menu;  /* 父菜单,NULL表示根菜单 */
    int8_t count;
} menu_def_t;

typedef struct {
    menu_def_t __xdata * root_menu;  /* 当前根菜单 */
    menu_def_t __xdata * cur_menu;  /* 当前展示的菜单 */
    int8_t __xdata * val_list;  /* 存储当前设置的值 */
} menu_ctx_t;

extern menu_def_t __xdata sub_menu_def_register[];
extern menu_def_t __xdata main_menu_def;
extern int8_t __xdata ch_a_val_list[];
extern int8_t __xdata ch_b_val_list[];
extern menu_ctx_t __xdata g_menu_ctx;
extern uint8_t __xdata menu_def_protect_after;

/*---------------------------------------------------------------------*/
/* API                                                                  */
/*---------------------------------------------------------------------*/

// 构造一个菜单上下文, root是根菜单定义, val_list是存储当前设置的值的数组
void menu_open(menu_ctx_t __xdata * ctx,
               menu_def_t __xdata * root_menu,
               int8_t __xdata * val_list,
               menu_string_offset_t __xdata root_name);  // 重设菜单名称

void menu_draw(menu_ctx_t __xdata *ctx);

// 菜单操作输入,这里的input与编码器定义一致,避免了编码器和菜单系统的转换
// 返回值表示菜单是否完全退出
uint8_t menu_input(menu_ctx_t __xdata *ctx, uint8_t __xdata input);

#endif
