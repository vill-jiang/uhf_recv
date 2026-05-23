/*---------------------------------------------------------------------*/
/* 主界面模块 - 项目相关, 非可移植                                        */
/* 管理焦点切换(A/B/关机/W)、进入退出菜单、关机进度                       */
/* 主界面绘制大部分交给用户自定义                                         */
/*---------------------------------------------------------------------*/

#ifndef __HOME_H
#define __HOME_H

#include "config.h"

/*---------------------------------------------------------------------*/
/* 整体状态机                                                           */
/*---------------------------------------------------------------------*/

#define APP_STATE_HOME      0   /* 主界面 */
#define APP_STATE_MENU      1   /* 菜单中 */

/*---------------------------------------------------------------------*/
/* 主界面焦点状态                                                       */
/*---------------------------------------------------------------------*/

#define HOME_FOCUS_W        0   /* 无选择 */
#define HOME_FOCUS_A        1   /* A通道 */
#define HOME_FOCUS_B        2   /* B通道 */
#define HOME_FOCUS_POWER    3   /* 关机图标 */

#define HOME_STATUS_BIT_INPUT_DIRTY (0x01)  /* 输入缓冲区脏 */
#define HOME_STATUS_BIT_SWITCH_DIRTY (0x02)  /* 整页切换脏 */

#define HOME_INPUT_EVENT_NONE (0x00)  /* 无事件 */
#define HOME_INPUT_EVENT_CHANGE_DATA_A (0x01)  /* A通道数据修改脏 */
#define HOME_INPUT_EVENT_CHANGE_DATA_B (0x02)  /* B通道数据修改脏 */
#define HOME_INPUT_EVENT_POWER_OFF_PREPARE (0x04)  /* 关机准备 */
#define HOME_INPUT_EVENT_POWER_OFF_CONFIRM (0x08)  /* 关机确认 */

/*---------------------------------------------------------------------*/
/* 关机参数                                                             */
/*---------------------------------------------------------------------*/

// #ifndef POWEROFF_HOLD_TICKS
// #define POWEROFF_HOLD_TICKS 5000
// #endif

/*---------------------------------------------------------------------*/
/* 主界面上下文                                                         */
/*---------------------------------------------------------------------*/

typedef struct {
    /* 整体状态 */
    uint8_t app_state; /* APP_STATE_xxx */
    int8_t home_focus; /* HOME_FOCUS_xxx */
    uint8_t status_bit;  /* 其他状态位 */
    
    /* 主界面数据 */
    uint8_t af_data;  /* I2C读到的响度数据, 低四位为A通道, 高四位为B通道 */
    int32_t frequency_a;  /* I2C读到的频率数据, A通道 */
    int32_t frequency_b;  /* I2C读到的频率数据, B通道 */
} home_ctx_t;

extern home_ctx_t __xdata g_home_ctx;

/*---------------------------------------------------------------------*/
/* 轻量级状态查询宏 (避免8051函数调用开销)                                */
/*---------------------------------------------------------------------*/

#define home_get_focus(ctx)         ((ctx)->home_focus)
// #define home_get_poweroff_cnt(ctx)  ((ctx)->poweroff_cnt)
#define home_in_menu(ctx)           ((ctx)->app_state == APP_STATE_MENU)
// #define home_is_poweroff(ctx)       ((ctx)->poweroff_cnt >= POWEROFF_HOLD_TICKS)

/*---------------------------------------------------------------------*/
/* API                                                                  */
/*---------------------------------------------------------------------*/

/**
 * @brief 初始化主界面
 */
void home_init(home_ctx_t __xdata *ctx);

/**
 * @brief 输入处理 (在主循环中调用)
 * @return 返回事件
 */
uint8_t home_input(home_ctx_t __xdata * ctx);

/**
 * @brief 绘制 (在主循环中调用)
 * @return 返回事件
 */
void home_draw(home_ctx_t __xdata *ctx);

#endif
