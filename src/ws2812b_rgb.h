#ifndef _WS2812B_RGB_H_
#define _WS2812B_RGB_H_

#include "config.h"

void send_color(uint8_t r, uint8_t g, uint8_t b);
void send_rst(void);

#endif