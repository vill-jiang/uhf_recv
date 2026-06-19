#include "STC8G_H_Delay.h"
#include "STC8G_H_GPIO.h"
#include "STC8G_H_Switch.h"
#include "STC8G_H_I2C.h"
#include "STC8G_H_EEPROM.h"
#include "STC8G_H_UART.h"
#include "kt0656m_v11_drv.h"
#include "ssd1106_oled.h"
#include "ws2812b_rgb.h"
#include "use_isr.h"
#include "string_lib.h"
#include "encoder.h"
#include "home.h"
#include "menu.h"

extern encoder_t __xdata g_encoder;

#define POWER_OFF_FLAG (1)
#define POWER_ON_NEED_CNT (2)
uint8_t __xdata mcu_power_off = POWER_OFF_FLAG;  // 刚开始就是关机状态
uint8_t __xdata mcu_power_on_cnt = 0;

// 重启之后只需要执行一次的初始化
void base_initialize(void) {
    // menu_def_protect_after = 0x55;
I2C_InitTypeDef __xdata i2c_init = {
    .I2C_Speed = (MAIN_Fosc / 2 / (400000UL * 2 + 4)), // 400kHz
    .I2C_Enable = ENABLE,
    .I2C_Mode = I2C_Mode_Master,
    .I2C_MS_WDTA = DISABLE
};
COMx_InitDefine __xdata uart_init = {
    .UART_Mode = UART_8bit_BRTx,
    .UART_BRT_Use = BRT_Timer1,
    .UART_BaudRate = (65536UL - (((MAIN_Fosc / 115200UL) + 2) / 4UL)),  // 115200
    .Morecommunicate = DISABLE,
    .UART_RxEnable = ENABLE,
    .BaudRateDouble = DISABLE
};
    EAXSFR();
    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
    P3_MODE_IN_HIZ(GPIO_Pin_6 | GPIO_Pin_7);
    P3_PULL_UP_ENABLE(GPIO_Pin_0 | GPIO_Pin_1);
    P3_MODE_IN_HIZ(GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
    P1_PULL_UP_ENABLE(GPIO_Pin_4 | GPIO_Pin_5);
    P3_PULL_UP_ENABLE(GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
    I2C_SW(I2C_P14_P15);
    //设定掉电唤醒时钟约为0.5秒钟
    WKTCL = 0xE7;
    WKTCH = 0x83;
    // 关闭音频输出和无线芯片
    PCM_MUTE_PIN = 0;
    KT0656M_CHIP_EN_AM = 0;
    KT0656M_CHIP_EN_BM = 0;

    I2C_Init(&i2c_init);
    ssd1106_init();
    ssd1106_fillscreen(0);
    // UART初始化X
    UART1_SW(UART1_SW_P30_P31);
    UART_Configuration(UART1, &uart_init);
    TX1_write2buff('X');
    ES = 1;
    EA = 1;
    // 关灯
    send_color(0, 0, 0);
    send_color(0, 0, 0);
    send_rst();
}
// 软关机之后仍需执行的初始化
void soft_initialize(void) {
    home_init(&g_home_ctx);
    kt0656m_init();
    // 关灯
    send_color(0, 0, 0);
    send_color(0, 0, 0);
    send_rst();
}
// 软关机
void soft_shutdown(void) {
    mcu_power_off = POWER_OFF_FLAG;
    mcu_power_on_cnt = 0;
    // 关闭音频输出和无线芯片
    PCM_MUTE_PIN = 0;
    KT0656M_CHIP_EN_AM = 0;
    KT0656M_CHIP_EN_BM = 0;
    // 清屏
    ssd1106_fillscreen(0);
    // 关灯
    send_color(0, 0, 0);
    send_color(0, 0, 0);
    send_rst();
}
// 软开机
void soft_shutdown_tick(void) {
    if (mcu_power_off == POWER_OFF_FLAG) {
        if (!ENC_PIN_BTN) {
            mcu_power_on_cnt++;
        } else {
            mcu_power_on_cnt = 0;
        }
        if (mcu_power_on_cnt >= POWER_ON_NEED_CNT) {  // 开机
            mcu_power_off = 0;
            mcu_power_on_cnt = 0;
            soft_initialize();
        } else {
            PCON = 0x02;  // MCU进入掉电模式
        }
    }
}

int main(void) {
    uint8_t __xdata color[3] = {0}, last_rx_cnt = 0;
    uint8_t __xdata draw_event = 0;

    base_initialize();

    while (1) {
        soft_shutdown_tick();
        if (mcu_power_off == POWER_OFF_FLAG) {
            continue;
        }
        draw_event = home_input(&g_home_ctx);
        if (draw_event == HOME_INPUT_EVENT_POWER_OFF_CONFIRM) {
            soft_shutdown();  // 关机
            continue;
        } else if (draw_event == HOME_INPUT_EVENT_CHANGE_DATA_A) {
            kt0656m_current_addr = KT0656M_ADDR_A;
        } else if (draw_event == HOME_INPUT_EVENT_CHANGE_DATA_B) {
            kt0656m_current_addr = KT0656M_ADDR_B;
        }
        if (draw_event != HOME_INPUT_EVENT_NONE) {
            kt0656m_set_echo_eq();
            kt0656m_tune();
        }
        kt0656m_current_addr = KT0656M_ADDR_A;
        kt0656m_get_freq(&(g_home_ctx.frequency_a));
        g_home_ctx.af_data = kt0656m_get_af();
        kt0656m_current_addr = KT0656M_ADDR_B;
        kt0656m_get_freq(&(g_home_ctx.frequency_b));
        g_home_ctx.af_data |= (kt0656m_get_af() << 4);
        home_draw(&g_home_ctx);
        send_color(g_home_ctx.af_data & 0xF0, 0, 0);
        send_color(g_home_ctx.af_data << 4, 0, 0);
        send_rst();
        delay_ms(1);
    }
}

