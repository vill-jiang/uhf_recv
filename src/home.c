/*---------------------------------------------------------------------*/
/* 主界面模块 - 逻辑实现                                                 */
/*---------------------------------------------------------------------*/

#include "home.h"
#include "ssd1106_oled.h"
#include "string_lib.h"
#include "eeprom_bin_data.h"
#include "encoder.h"
#include "menu.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_EEPROM.h"

home_ctx_t __xdata g_home_ctx;


/*---------------------------------------------------------------------*/
/* 数据处理：存储和加载持久化数据                                        */
/*---------------------------------------------------------------------*/

static void load_data_from_eeprom(void) {
    for (uint8_t i = 0; i < MENU_VAL_DATA_LEN; i++) {
        ch_a_val_list[i] = default_data_channel_a[i];
        ch_b_val_list[i] = default_data_channel_b[i];
    }
}

static void save_data_to_eeprom(void) {
    EEPROM_SectorErase(PERSISTENT_DATA_SECTOR_START);
    EEPROM_write_n(PERSISTENT_DATA_SECTOR_START, ch_a_val_list, MENU_VAL_DATA_LEN);
    EEPROM_write_n(PERSISTENT_DATA_SECTOR_START + MENU_VAL_DATA_LEN, ch_b_val_list, MENU_VAL_DATA_LEN);
}

/*---------------------------------------------------------------------*/
/* 输入处理: 主界面状态                                                  */
/*---------------------------------------------------------------------*/

static uint8_t input_home(home_ctx_t __xdata *ctx, uint8_t __xdata input) {
    if (input & ENCODER_EVT_CW) {
        ctx->home_focus++;
        ctx->status_bit |= HOME_STATUS_BIT_INPUT_DIRTY;
        // ctx->poweroff_cnt = 0;
    } else if (input & ENCODER_EVT_CCW) {
        ctx->home_focus--;
        ctx->status_bit |= HOME_STATUS_BIT_INPUT_DIRTY;
        // ctx->poweroff_cnt = 0;
    }
    if (ctx->home_focus > HOME_FOCUS_POWER) ctx->home_focus = HOME_FOCUS_W;
    if (ctx->home_focus < HOME_FOCUS_W) ctx->home_focus = HOME_FOCUS_POWER;

    if (input & ENCODER_EVT_BTN_UP) {
        if (ctx->home_focus == HOME_FOCUS_A ||
            ctx->home_focus == HOME_FOCUS_B) {
            // 进入菜单
            ctx->app_state = APP_STATE_MENU;
            load_data_from_eeprom();
            menu_open(&g_menu_ctx, &main_menu_def,
                (ctx->home_focus == HOME_FOCUS_A) ? ch_a_val_list : ch_b_val_list, 
                (ctx->home_focus == HOME_FOCUS_A) ? STATIC_STR_CHA_OFFSET : STATIC_STR_CHB_OFFSET);
        }
    }
    if (input & ENCODER_EVT_BTN_LONG && ctx->home_focus == HOME_FOCUS_POWER) {
        ssd1106_string_f8x16(0, 3, "PowerOff...", SSD1106_REVERSE_NONE);
        return HOME_INPUT_EVENT_POWER_OFF_PREPARE;
    }
    if (input & ENCODER_EVT_BTN_LONG_UP && ctx->home_focus == HOME_FOCUS_POWER) {
        ctx->status_bit |= HOME_STATUS_BIT_INPUT_DIRTY;
        ctx->status_bit |= HOME_STATUS_BIT_SWITCH_DIRTY;
        return HOME_INPUT_EVENT_POWER_OFF_CONFIRM;
    }
    return HOME_INPUT_EVENT_NONE;
}


uint8_t home_input(home_ctx_t __xdata * ctx) {
    encoder_process();
    uint8_t __xdata input = encoder_poll_event();
    if (input == ENCODER_EVT_NONE) return;

    if (ctx->app_state == APP_STATE_HOME) {
        return input_home(ctx, input);
    } else {
        input = menu_input(&g_menu_ctx, input);
        if (input == MENU_INPUT_EXIT_SAVE) {
            save_data_to_eeprom();
            ctx->app_state = APP_STATE_HOME;
            ctx->status_bit |= HOME_STATUS_BIT_INPUT_DIRTY;
            ctx->status_bit |= HOME_STATUS_BIT_SWITCH_DIRTY;
            return ctx->home_focus == HOME_FOCUS_A ? HOME_INPUT_EVENT_CHANGE_DATA_A : HOME_INPUT_EVENT_CHANGE_DATA_B;
        } else if (input == MENU_INPUT_EXIT_UNSAVE) {
            load_data_from_eeprom();  // 加载数据
            ctx->app_state = APP_STATE_HOME;
            ctx->status_bit |= HOME_STATUS_BIT_INPUT_DIRTY;
            ctx->status_bit |= HOME_STATUS_BIT_SWITCH_DIRTY;
        }
    }
    return HOME_INPUT_EVENT_NONE;
}

/*---------------------------------------------------------------------*/
/* API 实现                                                             */
/*---------------------------------------------------------------------*/

void home_init(home_ctx_t __xdata * ctx) {
    ctx->app_state = APP_STATE_HOME;
    ctx->home_focus = HOME_FOCUS_W;
    ctx->status_bit = 0;
    
    // 编码器初始化
    encoder_init();
    // 显示开机图片
    ssd1106_fillscreen(0);
    ssd1106_draw_bmp(START_ICON_X0, START_ICON_Y0, START_ICON_X1, START_ICON_Y1, start_icon_bmp, SSD1106_REVERSE_NONE);
    ctx->status_bit |= HOME_STATUS_BIT_SWITCH_DIRTY;  // 置脏标志, 以便主循环第一次进入home_draw时刷新显示
    ctx->status_bit |= HOME_STATUS_BIT_INPUT_DIRTY;  // 置脏标志, 以便主循环第一次进入home_draw时刷新显示
}

void home_draw(home_ctx_t __xdata *ctx) {
    if (ctx->app_state == APP_STATE_HOME) {
        if (ctx->status_bit & HOME_STATUS_BIT_SWITCH_DIRTY) {
            ssd1106_fillscreen(0);
            ctx->status_bit &= ~HOME_STATUS_BIT_SWITCH_DIRTY;
        }
        // 绘制响度条
        ssd1106_setpos(0, 2);
        ssd1106_string_font6x8(uint4_to_bar_str(ctx->af_data & 0x0F), SSD1106_REVERSE_NONE);
        ssd1106_setpos(0, 7);
        ssd1106_string_font6x8(uint4_to_bar_str(ctx->af_data >> 4), SSD1106_REVERSE_NONE);
        if (ctx->status_bit & HOME_STATUS_BIT_INPUT_DIRTY) {
            ctx->status_bit &= ~HOME_STATUS_BIT_INPUT_DIRTY;  // 清除脏位

            uint8_t __xdata focus_cur = SSD1106_REVERSE_NONE;
            // 绘制图标
            focus_cur = ctx->home_focus == HOME_FOCUS_POWER ? SSD1106_REVERSE_EN : SSD1106_REVERSE_NONE;
            ssd1106_draw_bmp(111, 3, 127, 5, ssd1106_power_icon_16x16, focus_cur);
            // 绘制频率显示
            focus_cur = ctx->home_focus == HOME_FOCUS_A ? SSD1106_REVERSE_EN : SSD1106_REVERSE_NONE;
            ssd1106_string_f8x16(0, 0, "A ", focus_cur);
            ssd1106_string_f8x16(18, 0, uint32_fixed_to_dec_str(ctx->frequency_a, 3), SSD1106_REVERSE_NONE);
            ssd1106_string_f8x16(74, 0, "MHz", SSD1106_REVERSE_NONE);

            focus_cur = ctx->home_focus == HOME_FOCUS_B ? SSD1106_REVERSE_EN : SSD1106_REVERSE_NONE;
            ssd1106_string_f8x16(0, 5, "B ", focus_cur);
            ssd1106_string_f8x16(18, 5, uint32_fixed_to_dec_str(ctx->frequency_b, 3), SSD1106_REVERSE_NONE);
            ssd1106_string_f8x16(74, 5, "MHz", SSD1106_REVERSE_NONE);
        }
    }
    else {
        menu_draw(&g_menu_ctx);
    }
}

// void home_set_channel(home_ctx_t *ctx, uint8_t ch,
//                       const uint8_t *name, menu_item_val_t *vals) {
//     if (ch > 1) return;
//     ctx->ch_name[ch] = name;
//     ctx->ch_vals[ch] = vals;
// }


