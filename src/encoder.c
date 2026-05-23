/*---------------------------------------------------------------------*/
/* 旋转编码器驱动 - 平台无关逻辑层实现                                   */
/* 旋转方向在中断中判定并累积, 主循环处理按键消抖和事件生成                 */
/* 即使主循环延迟, 旋转方向也不会丢失                                     */
/*---------------------------------------------------------------------*/

#include "encoder.h"
#include "STC8G_H_Timer.h"

/*---------------------------------------------------------------------*/
/* 全局编码器实例                                                       */
/*---------------------------------------------------------------------*/

encoder_t __xdata g_encoder;

/*---------------------------------------------------------------------*/
/* GPIO 读取实现 (一次性读取全部引脚)                                    */
/*---------------------------------------------------------------------*/

uint8_t encoder_hal_read_pins(void)
{
    uint8_t pins = 0;
    if (ENC_PIN_A) pins |= ENC_MASK_A;
    if (ENC_PIN_B) pins |= ENC_MASK_B;
    if (ENC_PIN_BTN) pins |= ENC_MASK_BTN;
    return pins;
}

/*---------------------------------------------------------------------*/
/* Timer0 初始化 - 1ms 中断                                             */
/* STC8H Timer0 工作在 16位自动重载模式, 1T模式                          */
/*---------------------------------------------------------------------*/

/* Timer0 重载值计算: 65536 - (MAIN_Fosc / 1000) */
/* 1T模式下每个机器周期 = 1个时钟周期                                    */
#define TIMER0_RELOAD   (65536UL - (MAIN_Fosc / 1000UL))

void encoder_hal_init(void)
{
    /* 确保引脚为高电平(外部已有10K上拉) */
    ENC_PIN_A = 1;
    ENC_PIN_B = 1;
    ENC_PIN_BTN = 1;

    TIM_InitTypeDef __xdata time_def = {
        .TIM_Mode = TIM_16BitAutoReloadNoMask,
        .TIM_ClkSource = TIM_CLOCK_1T,
        .TIM_ClkOut = DISABLE,
        .TIM_Value = TIMER0_RELOAD,
        .TIM_PS = 0,
        .TIM_Run = ENABLE,
    };

    Timer_Inilize(Timer0, &time_def);
    TF0 = 1;  /* 清除 Timer0 溢出标志 */
    ET0 = 1;  /* 使能 Timer0 中断 */
}

/*---------------------------------------------------------------------*/
/* Timer0 中断服务函数 - 1ms 周期仅采样引脚                              */
/* 极轻量: 只读引脚并置标志位, 不做任何逻辑处理                           */
/*---------------------------------------------------------------------*/

INTERRUPT(Timer0_ISR_Handler, TMR0_VECTOR)
{
    encoder_sample();
}

/*---------------------------------------------------------------------*/
/* AB相正交编码方向判定 (纯位运算, 无需查找表)                            */
/*   顺时针: 00 -> 01 -> 11 -> 10 -> 00                                */
/*   逆时针: 00 -> 10 -> 11 -> 01 -> 00                                */
/* 方向公式: prev_A ^ curr_B                                            */
/*   结果为1 = 顺时针(+1), 结果为0 = 逆时针(-1)                         */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* 初始化                                                               */
/*---------------------------------------------------------------------*/

void encoder_init(void)
{
    uint8_t __xdata pins, ab;

    /* 先初始化硬件 */
    encoder_hal_init();

    /* 读取当前AB相状态作为初始值 */
    pins = encoder_hal_read_pins();
    ab = (pins & ENC_MASK_AB);  /* 提取AB相: (A<<1)|B */

    /* 初始化中断区: ab_prev=ab, 无按键采样标志 */
    g_encoder.isr_state = ab;
    g_encoder.rot_delta = 0;

    /* 主循环区清零 */
    g_encoder.btn_state = 0;
    g_encoder.btn_filter = 0;
    g_encoder.btn_hold = 0;
    g_encoder.events = ENCODER_EVT_NONE;
}

/*---------------------------------------------------------------------*/
/* 中断采样函数 (在定时器中断中调用, 建议周期1ms)                         */
/* 完成: 旋转方向判定+累积, 按键引脚采样                                  */
/* 8051上约15条指令, 执行时间 < 8us @24MHz                                */
/*---------------------------------------------------------------------*/

void encoder_sample(void)
{
    uint8_t __xdata pins, ab_curr, ist;

    ist = g_encoder.isr_state;
    pins = encoder_hal_read_pins();

    /* 提取AB相: (A<<1)|B */
    ab_curr = (pins & ENC_MASK_AB);

    if (ab_curr != (ist & ENC_MASK_AB)) {
        /* AB相发生变化, 判定方向并累积增量 */
        /* prev_A(bit1) ^ curr_B(bit0): 1=CW, 0=CCW */
        if (((ist >> 1) ^ ab_curr) & ENC_MASK_B) {
            g_encoder.rot_delta++;
        } else {
            g_encoder.rot_delta--;
        }
        /* 更新 ab_prev, 保留其余位 */
        ist = (ist & ~ENC_MASK_AB) | ab_curr;
    }

    /* 采样按键引脚, 存入 ENC_MASK_BTN, 置就绪标志 */
    ist = (ist & ~ENC_MASK_BTN) | (pins & ENC_MASK_BTN);
    g_encoder.isr_state = ENC_ISR_BTN_FLAG | ist;
}

/*---------------------------------------------------------------------*/
/* 主循环处理函数 (在主循环中调用, 不占用中断时间)                         */
/*---------------------------------------------------------------------*/

void encoder_process(void)
{
    int8_t __xdata delta;
    uint8_t __xdata ist, bs;

    /*--- 旋转事件: 消费中断累积的增量 ---*/
    delta = g_encoder.rot_delta;
    if (delta >= ENCODER_ROT_DELTA || delta <= - ENCODER_ROT_DELTA) {
        g_encoder.rot_delta = 0;    /* 清零 (极短窗口内可能丢失1步, 可接受) */
        if (delta > 0) {
            g_encoder.events |= ENCODER_EVT_CW;
        } else {
            g_encoder.events |= ENCODER_EVT_CCW;
        }
    }

    /*--- 按键处理: 消费中断采样的引脚值 ---*/
    ist = g_encoder.isr_state;
    if (!(ist & ENC_ISR_BTN_FLAG)) {
        return;
    }
    g_encoder.isr_state = ist & ~ENC_ISR_BTN_FLAG;   /* 清除就绪标志 */

    bs = g_encoder.btn_state;

    /* E引脚低电平有效: pin=0表示按下 */
    /* 将引脚值(bit0)取反后左移到bit1位置, 与btn_state(bit1)比较 */
    if ((((~ist & ENC_MASK_BTN) >> (ENC_MASK_BTN_SHIFT - 1)) ^ bs) & ENC_BTN_STATE) {
        /* 状态不一致, 累加滤波计数 */
        g_encoder.btn_filter++;
        if (g_encoder.btn_filter >= ENCODER_BTN_DEBOUNCE) {
            g_encoder.btn_filter = 0;
            bs ^= ENC_BTN_STATE;            /* 翻转按键状态 */
            bs &= ~ENC_BTN_LONG;            /* 清除长按标志 */
            g_encoder.events |= (bs & ENC_BTN_STATE) ? ENCODER_EVT_BTN_DOWN
                                                : ((g_encoder.btn_hold >= ENCODER_BTN_LONG_PRESS)
                                                   ? ENCODER_EVT_BTN_LONG_UP
                                                   : ENCODER_EVT_BTN_UP);
            g_encoder.btn_hold = 0;
        }
    } else {
        g_encoder.btn_filter = 0;
    }

    /* 长按检测 */
    if ((bs & ENC_BTN_STATE) && !(bs & ENC_BTN_LONG)) {
        g_encoder.btn_hold++;
        if (g_encoder.btn_hold >= ENCODER_BTN_LONG_PRESS) {
            g_encoder.events |= ENCODER_EVT_BTN_LONG;
            bs |= ENC_BTN_LONG;
        }
    }

    g_encoder.btn_state = bs;
}

/*---------------------------------------------------------------------*/
/* 提取并清除事件                                                       */
/*---------------------------------------------------------------------*/

uint8_t encoder_poll_event(void)
{
    uint8_t __xdata evt;
    evt = g_encoder.events;
    g_encoder.events = ENCODER_EVT_NONE;
    return evt;
}
