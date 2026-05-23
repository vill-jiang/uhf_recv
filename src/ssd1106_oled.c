#include "ssd1106_oled.h"
#include "STC8G_H_I2C.h"
#include "STC8G_H_EEPROM.h"
#include "eeprom_bin_data.h"

// --- Inner API ---
void _ssd1106_start(uint8_t __xdata mode)
{
    I2C_Start();              // 发送起始命令
    I2C_SendData(SSD1106_SA); // 发送设备地址+写命令
    I2C_RecvACK();
    I2C_SendData(mode); // 发送存储地址
    I2C_RecvACK();
}
void _ssd1106_send_byte(uint8_t __xdata byte)
{
    I2C_SendData(byte);
    I2C_RecvACK();
}
void _ssd1106_init_from(const uint8_t * __xdata seq, uint8_t __xdata len)
{
    _ssd1106_start(SSD1106_COMMAND);
    for (uint8_t __xdata i = 0; i < len; i++)
    {
        _ssd1106_send_byte(seq[i]);
    }
    I2C_Stop();
}

// --- Public API ---

void ssd1106_init(void)
{
    _ssd1106_init_from(ssd1106_init_sequence, SSD1106_INIT_SEQUENCE_LEN);
}

void ssd1106_setpos(uint8_t __xdata x, uint8_t __xdata y)
{
    _ssd1106_start(SSD1106_COMMAND);
    _ssd1106_send_byte(0xb0 | (y & 0x07));        // Page address
    _ssd1106_send_byte(0x10 | ((x & 0xf0) >> 4)); // Column high nibble
    _ssd1106_send_byte(x & 0x0f);                 // Column low nibble
    I2C_Stop();
}

void ssd1106_fillscreen(uint8_t __xdata fill)
{
    ssd1106_setpos(0, 0);
    _ssd1106_start(SSD1106_DATA);
    for (uint16_t __xdata i = 0; i < 128 * 8; i++)
    {
        _ssd1106_send_byte(fill);
    }
    I2C_Stop();
}

// void ssd1106_set_contrast(uint8_t value) {
//     _ssd1106_start(SSD1106_COMMAND);
//     _ssd1106_send_byte(SSD1106_COMMAND_SET_CONTRAST);
//     _ssd1106_send_byte(value);
//     I2C_Stop();
// }

#ifndef SSD1106_NO_FONT_6X8
void ssd1106_char_font6x8(char __xdata ch, uint8_t __xdata reverse)
{
    _ssd1106_start(SSD1106_DATA);
    for (uint8_t __xdata i = 0; i < 6; i++)
    {
        _ssd1106_send_byte(reverse ^ ssd1106_font6x8[(ch - 32) * 6 + i]);
    }
    I2C_Stop();
    // I2C_WriteNbyte(SSD1106_SA, SSD1106_DATA, ssd1106_font6x8 + (c * 6), 6);
}

void ssd1106_string_font6x8(const char * __xdata s, uint8_t __xdata reverse)
{
    _ssd1106_start(SSD1106_DATA);
    while (*s)
    {
        uint8_t __xdata c = *s++ - 32;
        for (uint8_t __xdata i = 0; i < 6; i++)
        {
            _ssd1106_send_byte(reverse ^ ssd1106_font6x8[c * 6 + i]);
        }
    }
    I2C_Stop();
}
#endif
#ifndef SSD1106_NO_FONT_8X16
void ssd1106_string_f8x16(uint8_t __xdata x, uint8_t __xdata y, const char* s, uint8_t __xdata reverse)
{
    uint8_t __xdata c, i = 0;
    while (*s)
    {
        c = *s++ - 32;
        if (x > 120)
        {
            x = 0;
            y += 2;
        }
        ssd1106_setpos(x, y);
        _ssd1106_start(SSD1106_DATA);
        for (i = 0; i < 8; i++)
        {
            _ssd1106_send_byte(reverse ^ ssd1106_font8x16[c * 16 + i]);
        }
        I2C_Stop();
        ssd1106_setpos(x, y + 1);
        _ssd1106_start(SSD1106_DATA);
        for (i = 0; i < 8; i++)
        {
            _ssd1106_send_byte(reverse ^ ssd1106_font8x16[c * 16 + i + 8]);
        }
        I2C_Stop();
        x += 8;
    }
}
#endif

#ifndef SSD1106_NO_DRAW_BMP
void ssd1106_draw_bmp(uint8_t __xdata x0, uint8_t __xdata y0, uint8_t __xdata x1, uint8_t __xdata y1, const uint8_t __code * bitmap, uint8_t __xdata reverse)
{
    uint16_t __xdata j = 0;
    uint8_t __xdata y, x;
    for (y = y0; y < y1; y++)
    {
        ssd1106_setpos(x0, y);
        _ssd1106_start(SSD1106_DATA);
        for (x = x0; x < x1; x++)
        {
            _ssd1106_send_byte(reverse ^ bitmap[j++]);
        }
        I2C_Stop();
    }
}
#endif