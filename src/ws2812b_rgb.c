#include "ws2812b_rgb.h"

// 适配35MHz主频
#define SHORT_DELAY() NOP5()
#define LONG_DELAY() NOP15()

void _send_byte(uint8_t byte) {
    uint8_t i;
    // EA = 0;
    for(i = 0; i < 8; i++){
        WS2812_PIN = 1;
        if ( ( byte & 0x80UL ) == 0x80UL ) {
            LONG_DELAY();
        } else {
            SHORT_DELAY();
        }
        WS2812_PIN = 0;
        if ( ( byte & 0x80UL ) == 0x80UL ) {
            SHORT_DELAY();
        } else {
            LONG_DELAY();
        }
        byte <<= 1;
    }
}

void send_color(uint8_t r, uint8_t g, uint8_t b) {
    // EA = 0;
    _send_byte(g);
    _send_byte(r);
    _send_byte(b);
    // EA = 1;
}

void send_rst(void) {
    WS2812_PIN = 0;
    volatile uint16_t i = 2550;
    while (--i) {
        NOP();
    }
}

