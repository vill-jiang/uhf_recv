/*---------------------------------------------------------------------*/
/* 旋转编码器驱动 - 平台无关逻辑层                                       */
/* 中断中仅采样引脚, 主循环中处理解码和消抖, 极低中断开销                  */
/* 移植到其它单片机时, 只需重新实现 encoder_hal.h 中的接口即可             */
/*---------------------------------------------------------------------*/

#ifndef __ENCODER_H_
#define __ENCODER_H_

#include "config.h"

/*---------------------------------------------------------------------*/
/* 配置参数 (可根据实际需求调整)                                         */
/*---------------------------------------------------------------------*/
#define ENC_MASK_B               0x01    /* bit2: B相组合掩码 */
#define ENC_MASK_A               0x02    /* bit1: A相组合掩码 */
#define ENC_MASK_BTN             0x04    /* bit0: E相组合掩码 */
#define ENC_MASK_AB              0x03    /* bit2:1: AB相组合掩码 */
#define ENC_MASK_BTN_SHIFT       2       /* bit0: E相移位 */

/* 累积多少增量判定为一步旋转 (根据编码器分辨率调整, 4适用于常见的20步/转编码器) */
#define ENCODER_ROT_DELTA (4)

/* 按键消抖时间(单位: tick次数, encoder_process 调用的次数) */
#ifndef ENCODER_BTN_DEBOUNCE
#define ENCODER_BTN_DEBOUNCE    2
#endif

/* 按键长按判定时间(单位: tick次数) */
#ifndef ENCODER_BTN_LONG_PRESS
#define ENCODER_BTN_LONG_PRESS  60
#endif

/*---------------------------------------------------------------------*/
/* 编码器事件定义                                                       */
/*---------------------------------------------------------------------*/

/* 事件标志位 */
#define ENCODER_EVT_NONE        0x00    /* 无事件 */
#define ENCODER_EVT_CW          0x01    /* 顺时针旋转一格 */
#define ENCODER_EVT_CCW         0x02    /* 逆时针旋转一格 */
/* ENCODER_EVT_BTN_DOWN -> ENCODER_EVT_BTN_UP */
/* ENCODER_EVT_BTN_DOWN -> ENCODER_EVT_BTN_LONG -> ENCODER_EVT_BTN_LONG_UP */
#define ENCODER_EVT_BTN_DOWN    0x04    /* 按键按下 */
#define ENCODER_EVT_BTN_UP      0x08    /* 按键松开 */
#define ENCODER_EVT_BTN_LONG    0x10    /* 按键长按 */
#define ENCODER_EVT_BTN_LONG_UP 0x20    /* 按键长按松开 */

/*---------------------------------------------------------------------*/
/* 编码器状态结构体 (位域压缩, 最小化RAM占用)                             */
/*---------------------------------------------------------------------*/

/*
 * 位域布局说明:
 *
 * isr_state [volatile uint8_t] - 中断读写区
 *   bit7     : 按键引脚采样就绪标志
 *   bit4~3   : AB相上次状态 (中断中维护, 用于方向判定)
 *   bit0     : 按键引脚采样值 (E引脚原始电平)
 *
 * rot_delta [volatile int8_t] - 旋转增量累加器
 *   中断中每检测到一步转移就 +1/-1, 主循环消费后清零
 *   即使主循环延迟, 旋转方向也不会丢失
 *
 * btn_state [uint8_t] - 按键状态 (主循环读写)
 *   bit1     : 按键稳定状态 (0=松开, 1=按下)
 *   bit0     : 长按已触发标志
 *
 * btn_filter [uint8_t] - 按键消抖滤波计数 (0~DEBOUNCE)
 * events     [uint8_t] - 事件标志位
 * btn_hold   [uint16_t] - 按键持续按下计数 (0~LONG_PRESS)
 */

typedef struct {
    volatile uint8_t isr_state; /* bit7=btn采样标志, ENC_MASK_AB=ab_prev, ENC_MASK_BTN=E引脚 */
    volatile int8_t  rot_delta; /* 旋转增量累加器 (中断写, 主循环读清) */
    uint8_t  btn_state;         /* bit1=btn, bit0=long_fired */
    uint8_t  btn_filter;        /* 按键消抖滤波计数 */
    uint8_t  events;            /* 事件标志位 */
    uint16_t btn_hold;          /* 按键持续按下计数 */
} encoder_t;

/* isr_state 字段的位操作宏 */
#define ENC_ISR_BTN_FLAG        0x80    /* bit7: 按键采样就绪标志 */

/* btn_state 字段的位操作宏 */
#define ENC_BTN_STATE           0x02    /* bit1: 按键稳定状态 */
#define ENC_BTN_LONG            0x01    /* bit0: 长按已触发 */

/*---------------------------------------------------------------------*/
/* 以下函数需要由具体平台实现                                            */
/*---------------------------------------------------------------------*/

/**
 * @brief 一次性读取编码器全部引脚电平
 * @return bit2=A相, bit1=B相, bit0=按键(E), 各位1=高电平, 0=低电平
 */
uint8_t encoder_hal_read_pins(void);

/**
 * @brief 初始化编码器所用的GPIO和定时器
 * @note  定时器中断中应调用 encoder_sample() 进行扫描
 *        建议定时器周期: 1ms
 */
void encoder_hal_init(void);

/*---------------------------------------------------------------------*/
/* API 函数                                                             */
/*---------------------------------------------------------------------*/

/**
 * @brief 初始化编码器状态(同时调用HAL层初始化)
 */
void encoder_init(void);

/**
 * @brief 编码器引脚采样 (极轻量, 在定时器中断中调用)
 * @note  此函数应在定时器中断中被调用, 建议周期1ms
 */
void encoder_sample(void);

/**
 * @brief 编码器事件处理 (在主循环中调用)
 */
void encoder_process(void);

/**
 * @brief 提取并清除编码器事件
 * @return 事件标志位(ENCODER_EVT_xxx 的组合)
 */
uint8_t encoder_poll_event(void);

#endif
