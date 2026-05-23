#include "menu.h"
#include "eeprom_bin_data.h"
#include "ssd1106_oled.h"
#include "string_lib.h"
#include "STC8G_H_UART.h"

#define get_static_string(offset) (static_str_data + (offset))
#define get_static_string_len(offset) (static_str_data[(offset) - 1])
#define get_static_string_ptr_len(static_str_ptr) (*(static_str_ptr - 1))
#define get_static_menu_item(idx) (((const menu_item_t __code * __xdata)static_menu_item_data) + (idx))
#define get_static_val_type(type, offset) ((const type __code * __xdata)(static_val_type_data + (offset)))
#define get_str_int8_val(val_list, offset) (int8_to_dec_str(val_list[offset]))
#define get_str_int32_val(val_list, offset) (int32_to_dec_str(*(int32_t __xdata *)(val_list + offset)))

#define cicle_inc(val, min_val, max_val, step) ((((val) += (step)) <= (max_val)) ? (0) : ((val) = (min_val)))
#define cicle_dec(val, min_val, max_val, step) ((((val) -= (step)) >= (min_val)) ? (0) : ((val) = (max_val)))

// int8循环增减函数, 替代宏展开以节省代码空间
static void int8_cicle(int8_t __xdata *val, int8_t min_v, int8_t max_v, int8_t step_v, uint8_t __xdata dir) {
    if (dir) { cicle_inc(*val, min_v, max_v, step_v); }
    else     { cicle_dec(*val, min_v, max_v, step_v); }
}

// int32循环增减函数
static void int32_cicle(int32_t __xdata *val, int32_t min_v, int32_t max_v, int32_t step_v, uint8_t __xdata dir) {
    if (dir) { cicle_inc(*val, min_v, max_v, step_v); }
    else     { cicle_dec(*val, min_v, max_v, step_v); }
}

#define START_ITEM_IDX 1
#define MENU_TITLE_ROWS 2
#define MENU_MAX_FRAC_COLS 8
#define MENU_ITEM_ROWS (SCREEN_ROWS - MENU_TITLE_ROWS)

#define get_sub_menu_def_ptr(offset) (&(sub_menu_def_register[*(static_val_type_data + (offset))]))

menu_item_idx_t __xdata echo_menu_item_list[] = {
    MENU_ITEM_RETURN_IDX,
    MENU_ITEM_ECHO_IDX,
    MENU_ITEM_ECHORATIO_IDX,
    MENU_ITEM_ECHODELAY_IDX,
};
menu_item_idx_t __xdata exciter_menu_item_list[] = {
    MENU_ITEM_RETURN_IDX,
    MENU_ITEM_EXCITER_IDX,
    MENU_ITEM_EXCITERODD_IDX,
    MENU_ITEM_EXCITEREVEN_IDX,
};
menu_item_idx_t __xdata eq_menu_item_list[] = {
    MENU_ITEM_RETURN_IDX,
    MENU_ITEM_EQ_IDX,
    MENU_ITEM_25HZ_IDX,
    MENU_ITEM_40HZ_IDX,
    MENU_ITEM_63HZ_IDX,
    MENU_ITEM_100HZ_IDX,
    MENU_ITEM_160HZ_IDX,
    MENU_ITEM_250HZ_IDX,
    MENU_ITEM_400HZ_IDX,
    MENU_ITEM_630HZ_IDX,
    MENU_ITEM_1KHZ_IDX,
    MENU_ITEM_1_6KHZ_IDX,
    MENU_ITEM_2_5KHZ_IDX,
    MENU_ITEM_4KHZ_IDX,
    MENU_ITEM_6_3KHZ_IDX,
    MENU_ITEM_10KHZ_IDX,
    MENU_ITEM_16KHZ_IDX,
};

menu_def_t __xdata sub_menu_def_register[MENU_SUBMENU_MAX_IDX] = {
// #define MENU_SUBMENU_EQ_IDX (0)
{
    .name = STATIC_STR_EQ_OFFSET,  /* 菜单名称 */
    .state_bits = 0,  /* bit7=修改置脏, bit0=选择了值 */
    .cur_idx = 0,  /* 当前选择的条目索引 (0~count-1) */
    .first_show_idx = 0,  /* 当前显示的第一条索引 (0~count-1) */
    .first_item_idx = eq_menu_item_list,  /* 条目idx列表 */
    .parent_menu = &main_menu_def,  /* 父菜单,NULL表示根菜单 */
    .count = sizeof(eq_menu_item_list) / sizeof(menu_item_idx_t)
},
// #define MENU_SUBMENU_ECHO_IDX (1)
{
    .name = STATIC_STR_ECHO_OFFSET,  /* 菜单名称 */
    .state_bits = 0,  /* bit7=修改置脏, bit0=选择了值 */
    .cur_idx = 0,  /* 当前选择的条目索引 (0~count-1) */
    .first_show_idx = 0,  /* 当前显示的第一条索引 (0~count-1) */
    .first_item_idx = echo_menu_item_list,  /* 条目idx列表 */
    .parent_menu = &main_menu_def,  /* 父菜单,NULL表示根菜单 */
    .count = sizeof(echo_menu_item_list) / sizeof(menu_item_idx_t)
},
// #define MENU_SUBMENU_EXCITER_IDX (2)
{
    .name = STATIC_STR_EXCITER_OFFSET,  /* 菜单名称 */
    .state_bits = 0,  /* bit7=修改置脏, bit0=选择了值 */
    .cur_idx = 0,  /* 当前选择的条目索引 (0~count-1) */
    .first_show_idx = 0,  /* 当前显示的第一条索引 (0~count-1) */
    .first_item_idx = exciter_menu_item_list,  /* 条目idx列表 */
    .parent_menu = &main_menu_def,  /* 父菜单,NULL表示根菜单 */
    .count = sizeof(exciter_menu_item_list) / sizeof(menu_item_idx_t)
}
};
menu_item_idx_t __xdata main_menu_item_list[] = {
    MENU_ITEM_RETURN_IDX,
    MENU_ITEM_AFREQKHZ_IDX,
    MENU_ITEM_VOLUME_IDX,
    MENU_ITEM_EQ_SUB_IDX,
    MENU_ITEM_ECHO_SUB_IDX,
    MENU_ITEM_EXCITER_SUB_IDX,
};
menu_def_t __xdata main_menu_def = {
    .name = STATIC_STR_RETURN_OFFSET,  /* 菜单名称 */
    .state_bits = 0,  /* bit7=修改置脏, bit0=选择了值 */
    .cur_idx = 0,  /* 当前选择的条目索引 (0~count-1) */
    .first_show_idx = 0,  /* 当前显示的第一条索引 (0~count-1) */
    .first_item_idx = main_menu_item_list,  /* 条目idx列表 */
    .parent_menu = NULL,  /* 父菜单,NULL表示根菜单 */
    .count = sizeof(main_menu_item_list) / sizeof(menu_item_idx_t)
};
menu_ctx_t __xdata g_menu_ctx;

int8_t __xdata ch_a_val_list[MENU_VAL_DATA_LEN] = {0};
int8_t __xdata ch_b_val_list[MENU_VAL_DATA_LEN] = {0};
uint8_t __xdata menu_def_protect_after = 0xA0;

static void init_menu_start_data(menu_def_t __xdata * menu_ptr) {
    menu_ptr->state_bits |= MENU_STATE_BITS_SWITCH_MENU;
    menu_ptr->state_bits |= MENU_STATE_BITS_MODIFY_MENU;
    menu_ptr->cur_idx = START_ITEM_IDX;
    menu_ptr->first_show_idx = 0;
}

void menu_open(menu_ctx_t __xdata * ctx,
               menu_def_t __xdata * root_menu,
               int8_t __xdata * val_list,
               menu_string_offset_t __xdata root_name) {
    ctx->root_menu = root_menu;
    ctx->cur_menu = root_menu;
    ctx->val_list = val_list;
    ctx->root_menu->name = root_name;
    ctx->root_menu->state_bits = 0;
    init_menu_start_data(ctx->root_menu);
    // 特殊处理一下,为了共用同一个菜单结构
    if (root_name == STATIC_STR_CHA_OFFSET) {
        ctx->root_menu->first_item_idx[1] = MENU_ITEM_AFREQKHZ_IDX;
    } else if (root_name == STATIC_STR_CHB_OFFSET) {
        ctx->root_menu->first_item_idx[1] = MENU_ITEM_BFREQKHZ_IDX;
    }
    // *((int32_t __xdata *)val_list) = -1234354;
    ssd1106_fillscreen(0);
}

static void menu_title_draw(menu_ctx_t __xdata *ctx) {
    menu_def_t __xdata * menu_ptr = ctx->root_menu;
    uint8_t __xdata cur_line_chars = MENU_MAX_FRAC_COLS;
    // 绘制标题>子标题
    ssd1106_setpos(0, 0);
    do {
        if (menu_ptr != ctx->root_menu) {
            ssd1106_char_font6x8('>', SSD1106_REVERSE_NONE);
            cur_line_chars += 1;
        }
        ssd1106_string_font6x8(get_static_string(menu_ptr->name), SSD1106_REVERSE_NONE);
        cur_line_chars += get_static_string_len(menu_ptr->name);
        if (menu_ptr == ctx->cur_menu) {
            break;  // 结束循环
        }
        const menu_item_t __code * __xdata item_ptr = get_static_menu_item(menu_ptr->first_item_idx[menu_ptr->cur_idx]);
        if (item_ptr->type == MENU_ITEM_TYPE_SUBMENU) {
            menu_ptr = get_sub_menu_def_ptr(item_ptr->val_offset);
        } else {
            break;  // 结束循环
        }
    } while (1);
    // 填充空格清除后面已有字符
    while (cur_line_chars < SCREEN_COLS) {
        ssd1106_char_font6x8(' ', SSD1106_REVERSE_NONE);
        ++cur_line_chars;
    }
    // 绘制分割横线
    ssd1106_setpos(0, 1);
    ssd1106_string_font6x8(get_static_string(STATIC_STR_LINE_OFFSET), SSD1106_REVERSE_NONE);
}

static void menu_frac_draw(menu_def_t __xdata * menu_ptr) {
    uint8_t __xdata cur_line_chars = (SCREEN_COLS - MENU_MAX_FRAC_COLS) * CHAR_W;
    // 绘制空格和分数
    ssd1106_setpos(cur_line_chars, 0);
    cur_line_chars = (SCREEN_COLS - MENU_MAX_FRAC_COLS);
    two_uint8_to_dec_str(menu_ptr->cur_idx, menu_ptr->count - 1, '/');
    cur_line_chars += get_public_str_len();
    // 填充空格
    while (cur_line_chars < SCREEN_COLS) {
        ssd1106_char_font6x8(' ', SSD1106_REVERSE_NONE);
        ++cur_line_chars;
    }
    // 绘制分数
    ssd1106_string_font6x8(public_str, SSD1106_REVERSE_NONE);
}

// 获取菜单项的值字符串, 返回字符串长度, 结果存入public_str或返回code指针
// 返回值: 字符串长度; *out_code_str 非NULL时表示结果在code区
static uint8_t get_item_val_str(const menu_item_t __code * __xdata item_ptr, int8_t __xdata * val_list, const char __code * __xdata * out_code_str) {
    *out_code_str = NULL;
    if (item_ptr->type == MENU_ITEM_TYPE_INT8) {
        const val_type_int8_t __code * __xdata val_ptr = get_static_val_type(val_type_int8_t, item_ptr->val_offset);
        get_str_int8_val(val_list, val_ptr->cur_val_idx);
        return get_public_str_len();
    } else if (item_ptr->type == MENU_ITEM_TYPE_INT32) {
        const val_type_int32_t __code * __xdata val_ptr = get_static_val_type(val_type_int32_t, item_ptr->val_offset);
        get_str_int32_val(val_list, val_ptr->cur_val_idx);
        return get_public_str_len();
    } else if (item_ptr->type == MENU_ITEM_TYPE_STRENUM) {
        const val_type_str_t __code * __xdata val_ptr = get_static_val_type(val_type_str_t, item_ptr->val_offset);
        uint8_t __xdata idx = 0;
        uint8_t __xdata str_offset = val_ptr->first_str;
        if (val_list[val_ptr->cur_val_idx] >= 0 && val_list[val_ptr->cur_val_idx] < val_ptr->str_count) {
            idx = val_list[val_ptr->cur_val_idx];
        }
        while (idx--) {
            str_offset += get_static_string_len(str_offset);
            str_offset += 2;
        }
        *out_code_str = get_static_string(str_offset);
        return get_static_string_ptr_len(*out_code_str);
    } else if (item_ptr->type == MENU_ITEM_TYPE_SUBMENU) {
        *out_code_str = get_static_string(STATIC_STR_SUBMENU_OFFSET);
        return get_static_string_ptr_len(*out_code_str);
    }
    return 0;
}

// 绘制一行, y_idx 当前绘制的行表示第几行, 0-5
static void item_draw(menu_def_t __xdata * menu_ptr, int8_t __xdata * val_list, int8_t __xdata y_idx) {
    uint8_t __xdata reverse_flag = SSD1106_REVERSE_NONE, cur_line_chars = 0;
    const menu_item_t __code * __xdata item_ptr = 0;
    const char __code * __xdata code_str_ptr = NULL;
    ssd1106_setpos(0, y_idx + MENU_TITLE_ROWS);
    
    y_idx += menu_ptr->first_show_idx;
    if (y_idx < menu_ptr->count) {
        item_ptr = get_static_menu_item(menu_ptr->first_item_idx[y_idx]);
        // 1. 绘制字段前缀和名称
        reverse_flag = ((y_idx == menu_ptr->cur_idx) && (~(menu_ptr->state_bits) & MENU_STATE_BITS_CHOOSE_VALUE)) 
                         ? SSD1106_REVERSE_EN : SSD1106_REVERSE_NONE;
        ssd1106_char_font6x8(*(const char __code *)(get_static_string(STATIC_STR_PREFIXCHAR_OFFSET + item_ptr->type)), reverse_flag);
        ++cur_line_chars;
        ssd1106_string_font6x8(get_static_string(item_ptr->name), reverse_flag);
        cur_line_chars += get_static_string_len(item_ptr->name);
        // 2. 获取值字符串并计算总长度
        cur_line_chars += get_item_val_str(item_ptr, val_list, &code_str_ptr);
        // 3. 填充空格
        while (cur_line_chars < SCREEN_COLS) {
            ssd1106_char_font6x8(' ', SSD1106_REVERSE_NONE);
            ++cur_line_chars;
        }
        // 4. 绘制值字符串
        reverse_flag = ((y_idx == menu_ptr->cur_idx) && (menu_ptr->state_bits & MENU_STATE_BITS_CHOOSE_VALUE)) 
                         ? SSD1106_REVERSE_EN : SSD1106_REVERSE_NONE;
        if (code_str_ptr != NULL) {
            ssd1106_string_font6x8(code_str_ptr, reverse_flag);
        } else if (item_ptr->type != MENU_ITEM_TYPE_BACK) {
            ssd1106_string_font6x8(public_str, reverse_flag);
        }
        return;
    } else {
        ssd1106_string_font6x8(get_static_string(STATIC_STR_CLEAR_OFFSET), SSD1106_REVERSE_NONE);
    }
}

void menu_draw(menu_ctx_t __xdata *ctx) {
    if (ctx->cur_menu->state_bits & MENU_STATE_BITS_SWITCH_MENU) {
        menu_title_draw(ctx);
        ctx->cur_menu->state_bits &= ~MENU_STATE_BITS_SWITCH_MENU;  // 只绘制一次
    }
    // 绘制项目列表
    if (ctx->cur_menu->state_bits & MENU_STATE_BITS_MODIFY_MENU) {
        menu_frac_draw(ctx->cur_menu);
        for (int8_t __xdata i = 0; i < MENU_ITEM_ROWS; i++) {
            item_draw(ctx->cur_menu, ctx->val_list, i);
        }
        ctx->cur_menu->state_bits &= ~MENU_STATE_BITS_MODIFY_MENU;
    }
    return;
}

static void menu_value_change(int8_t __xdata * __xdata val_list, const menu_item_t __code * __xdata item_ptr, uint8_t __xdata input) {
    if (item_ptr->type == MENU_ITEM_TYPE_INT32) {
        const val_type_int32_t __code * __xdata val_ptr = get_static_val_type(val_type_int32_t, item_ptr->val_offset);
        int32_t __xdata *p_val = (int32_t __xdata *)(val_list + val_ptr->cur_val_idx);
        int32_cicle(p_val, val_ptr->min_val, val_ptr->max_val, val_ptr->step_val, input & MENU_INPUT_CW);
    } else {
        // INT8 和 STRENUM 统一处理: 都是对 val_list[idx] 做 int8_t 循环增减
        int8_t __xdata min_v, max_v, step_v;
        cur_val_idx_t __xdata idx;
        if (item_ptr->type == MENU_ITEM_TYPE_INT8) {
            const val_type_int8_t __code * __xdata val_ptr = get_static_val_type(val_type_int8_t, item_ptr->val_offset);
            idx = val_ptr->cur_val_idx;
            min_v = val_ptr->min_val;
            max_v = val_ptr->max_val;
            step_v = val_ptr->step_val;
        } else {
            const val_type_str_t __code * __xdata val_ptr = get_static_val_type(val_type_str_t, item_ptr->val_offset);
            idx = val_ptr->cur_val_idx;
            min_v = 0;
            max_v = val_ptr->str_count - 1;
            step_v = 1;
        }
        int8_cicle(&val_list[idx], min_v, max_v, step_v, input & MENU_INPUT_CW);
    }
}

// 菜单操作输入,这里的input与编码器定义一致,避免了编码器和菜单系统的转换
uint8_t menu_input(menu_ctx_t __xdata *ctx, uint8_t __xdata input) {
    if (input & MENU_INPUT_BTN_LONG) {
        ssd1106_setpos(0, 0);
        ssd1106_string_font6x8(get_static_string(STATIC_STR_UNSAVED_OFFSET), SSD1106_REVERSE_NONE);
        return MENU_INPUT_RET_NONE;
    }
    if (input & MENU_INPUT_BTN_LONG_UP) {
        return MENU_INPUT_EXIT_UNSAVE;
    }
    const menu_item_t __code * item_ptr = get_static_menu_item(ctx->cur_menu->first_item_idx[ctx->cur_menu->cur_idx]);
    if (input & (MENU_INPUT_CW | MENU_INPUT_CCW)) {
        if (ctx->cur_menu->state_bits & MENU_STATE_BITS_CHOOSE_VALUE) {
            ctx->cur_menu->state_bits |= MENU_STATE_BITS_MODIFY_DATA;
            menu_value_change(ctx->val_list, item_ptr, input);
        } else {
            int8_cicle(&ctx->cur_menu->cur_idx, 0, ctx->cur_menu->count - 1, 1, input & MENU_INPUT_CW);
        }
    } else if (input & MENU_INPUT_BTN_UP) {
        // 进入子菜单或选择值
        if (ctx->cur_menu->state_bits & MENU_STATE_BITS_CHOOSE_VALUE) {
            // 进入菜单项选择模式
            ctx->cur_menu->state_bits &= ~MENU_STATE_BITS_CHOOSE_VALUE;
        } else {
            // 根据类型操作
            if (item_ptr->type == MENU_ITEM_TYPE_BACK) {
                // 回到上一级或者退出
                if (ctx->cur_menu == ctx->root_menu) {
                    ssd1106_setpos(0, 0);
                    ssd1106_string_font6x8(get_static_string(STATIC_STR_SAVING_OFFSET), SSD1106_REVERSE_NONE);
                    return MENU_INPUT_EXIT_SAVE;
                }
                ctx->cur_menu = ctx->cur_menu->parent_menu;
                ctx->cur_menu->state_bits |= MENU_STATE_BITS_SWITCH_MENU;
            } else if (item_ptr->type == MENU_ITEM_TYPE_SUBMENU) {
                // 进入子菜单
                ctx->cur_menu = get_sub_menu_def_ptr(item_ptr->val_offset);
                // 初始化子菜单数据
                init_menu_start_data(ctx->cur_menu);
            } else {
                // 进入值选择模式
                ctx->cur_menu->state_bits |= MENU_STATE_BITS_CHOOSE_VALUE;
            }
        }
    }
    // 滚动到屏幕外部的情况, 跟随调整
    if (ctx->cur_menu->cur_idx < ctx->cur_menu->first_show_idx) {
        ctx->cur_menu->first_show_idx = ctx->cur_menu->cur_idx;
    }
    // 滚动到屏幕循环的情况, 跟随调整
    if (ctx->cur_menu->first_show_idx + MENU_ITEM_ROWS <= ctx->cur_menu->cur_idx) {
        ctx->cur_menu->first_show_idx = ctx->cur_menu->cur_idx - MENU_ITEM_ROWS + 1;
    }
    ctx->cur_menu->state_bits |= MENU_STATE_BITS_MODIFY_MENU;
    return 0;
}
