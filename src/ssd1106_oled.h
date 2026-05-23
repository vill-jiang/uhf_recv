#ifndef SSD1106_OLED_H
#define SSD1106_OLED_H
#include "config.h"

#ifndef SSD1106_SA
#define SSD1106_SA 0x78
#endif

/** @def SSD1106_NO_FONT_6X8
 * Exclude the 6x8 font data, ssd1106_char_font6x8(), and
 * ssd1106_string_font6x8(). The 6x8 font costs 678 bytes when used. */
// #define SSD1106_NO_FONT_6X8

/** @def SSD1106_NO_FONT_8X16
 * Exclude the 8x16 font data and ssd1106_string_f8x16().
 * The 8x16 font costs 1722 bytes when used. */
// #define SSD1106_NO_FONT_8X16

/** @def SSD1106_NO_DRAW_BMP
 * Exclude ssd1106_draw_bmp() (the page-aligned bitmap draw).
 * Use ssd1106_draw_bmp_px() instead. Costs 66 bytes when used. */
// #define SSD1106_NO_DRAW_BMP

/** I2C control byte: next bytes are commands. */
#define SSD1106_COMMAND 0x00
/** I2C control byte: next bytes are display data. */
#define SSD1106_DATA 0x40
#define SSD1106_COMMAND_DISPLAY_OFF 0xAE
#define SSD1106_COMMAND_DISPLAY_ON 0xAF
#define SSD1106_COMMAND_SET_CONTRAST 0x81

#define SSD1106_REVERSE_NONE 0x00
#define SSD1106_REVERSE_EN 0xFF

/**
 * @brief Initialize the display and clear the screen.
 *
 * Sends the full init sequence (clock, multiplex, charge pump, addressing
 * mode, etc.) then fills every pixel with zero. Takes about 20 I2C
 * command bytes (26 total) plus 1024 data bytes.
 */
void ssd1106_init(void);

/**
 * @brief Move the write cursor to a given position.
 *
 * @param x Column (0-127).
 * @param y Page (0-7). Each page is 8 pixels tall.
 */
void ssd1106_setpos(uint8_t __xdata x, uint8_t __xdata y);

/**
 * @brief Fill the entire screen with a byte pattern.
 *
 * Writes 1024 bytes (128 columns x 8 pages). Pass 0x00 to clear the
 * screen, 0xFF to turn every pixel on, or any other pattern.
 *
 * @param fill The byte pattern to repeat across the display.
 */
void ssd1106_fillscreen(uint8_t __xdata fill);

#ifndef SSD1106_NO_FONT_6X8
/**
 * @brief Print one character using the 6x8 font.
 *
 * Draws at the current cursor position and advances the cursor 6
 * columns to the right. The character occupies one page (8 pixels tall).
 *
 * @param ch ASCII character (32-127).
 * @param reverse SSD1106_REVERSE_EN to invert the character, SSD1106_REVERSE_NONE for normal display.
 */
void ssd1106_char_font6x8(char __xdata ch, uint8_t __xdata reverse);

/**
 * @brief Print a null-terminated string using the 6x8 font.
 *
 * Draws at the current cursor position. Uses a single I2C data
 * transaction for the whole string (faster than calling
 * ssd1106_char_font6x8() per character). Does not wrap lines
 * automatically.
 *
 * @param s Pointer to a null-terminated string.
 * @param reverse SSD1106_REVERSE_EN to invert the character, SSD1106_REVERSE_NONE for normal display.
 */
void ssd1106_string_font6x8(const char * __xdata s, uint8_t __xdata reverse);
#endif
#ifndef SSD1106_NO_FONT_8X16
/**
 * @brief Print a string using the 8x16 font at a given position.
 *
 * Each character is 8 columns wide and spans two pages (16 pixels tall).
 * If x > 120, wraps to the next line. The function draws the top half
 * and bottom half of each character in two separate passes.
 *
 * @param x Starting column (0-127).
 * @param y Starting page (0-7). The character occupies pages y and y+1.
 * @param s Null-terminated string to print.
 * @param reverse SSD1106_REVERSE_EN to invert the character, SSD1106_REVERSE_NONE for normal display.
 */
void ssd1106_string_f8x16(uint8_t __xdata x, uint8_t __xdata y, const char* s, uint8_t __xdata reverse);
#endif

#ifndef SSD1106_NO_DRAW_BMP
/**
 * @brief Draw a page-aligned bitmap.
 *
 * The bitmap must be page-aligned (y coordinates are page numbers, not
 * pixels). For pixel-level positioning, use ssd1106_draw_bmp_px() instead.
 *
 * @param x0 Starting column.
 * @param y0 Starting page.
 * @param x1 Ending column (exclusive).
 * @param y1 Ending page (exclusive).
 * @param bitmap Byte array stored in PROGMEM.
 * @param reverse SSD1106_REVERSE_EN to invert the bitmap, SSD1106_REVERSE_NONE for normal display.
 */
void ssd1106_draw_bmp(uint8_t __xdata x0, uint8_t __xdata y0, uint8_t __xdata x1, uint8_t __xdata y1, const uint8_t __code * bitmap, uint8_t __xdata reverse);
#endif


#endif