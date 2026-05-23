
#ifndef _EEPROM_CODE_DATA_H_
#define _EEPROM_CODE_DATA_H_

#include "config.h"

extern const uint8_t __code * __xdata ssd1106_init_sequence;
#define SSD1106_INIT_SEQUENCE_LEN (26)

extern const uint8_t __code * __xdata ssd1106_font6x8;
#define SSD1106_FONT6X8_LEN (552)

extern const uint8_t __code * __xdata ssd1106_font8x16;
#define SSD1106_FONT8X16_LEN (1520)

extern const uint8_t __code * __xdata ssd1106_power_icon_16x16;
#define SSD1106_POWER_ICON_16X16_LEN (32)

extern const uint8_t __code * __xdata kt0656m_v11_init_seq;
#define KT0656M_V11_INIT_SEQ_LEN (142)

extern const uint8_t __code * __xdata kt0656m_v11_sai_init_master_seq;
#define KT0656M_V11_SAI_INIT_MASTER_SEQ_LEN (13)

extern const uint8_t __code * __xdata kt0656m_v11_sai_init_slave_seq;
#define KT0656M_V11_SAI_INIT_SLAVE_SEQ_LEN (20)

extern const uint8_t __code * __xdata kt0656m_v11_tune;
#define KT0656M_V11_TUNE_LEN (27)

extern const uint8_t __code * __xdata start_icon_bmp;
#define START_ICON_BMP_LEN (416)

extern const uint8_t __code * __xdata static_str_data;
#define STATIC_STR_DATA_LEN (311)

extern const uint8_t __code * __xdata static_val_type_data;
#define STATIC_VAL_TYPE_DATA_LEN (118)

extern const uint8_t __code * __xdata static_menu_item_data;
#define STATIC_MENU_ITEM_DATA_LEN (87)

#define PERSISTENT_DATA_SECTOR_START (0x0E00)
extern const uint8_t __code * __xdata default_data_channel_a;
#define DEFAULT_DATA_CHANNEL_A_LEN (27)

extern const uint8_t __code * __xdata default_data_channel_b;
#define DEFAULT_DATA_CHANNEL_B_LEN (27)

#define START_ICON_X0 (38)
#define START_ICON_Y0 (0)
#define START_ICON_X1 (90)
#define START_ICON_Y1 (8)
// call by: ssd1106_draw_bmp(START_ICON_X0, START_ICON_Y0, START_ICON_X1, START_ICON_Y1, start_icon_bmp);

// Static Static String Offsets in static_str_data, offset-1 is the string length without the null terminator, can be used for string retrieval
#define STATIC_STR_RETURN_OFFSET (1)
#define STATIC_STR_PREFIXCHAR_OFFSET (4)
#define STATIC_STR_SUBMENU_OFFSET (11)
#define STATIC_STR_OFF_OFFSET (15)
#define STATIC_STR_ON_OFFSET (20)
#define STATIC_STR_CHA_OFFSET (24)
#define STATIC_STR_CHB_OFFSET (29)
#define STATIC_STR_FREQKHZ_OFFSET (34)
#define STATIC_STR_VOLUME_OFFSET (43)
#define STATIC_STR_ECHO_OFFSET (51)
#define STATIC_STR_ECHORATIO_OFFSET (57)
#define STATIC_STR_ECHODELAY_OFFSET (68)
#define STATIC_STR_EXCITER_OFFSET (79)
#define STATIC_STR_EXCITERODD_OFFSET (88)
#define STATIC_STR_EXCITEREVEN_OFFSET (100)
#define STATIC_STR_EQ_OFFSET (113)
#define STATIC_STR_25HZ_OFFSET (117)
#define STATIC_STR_40HZ_OFFSET (123)
#define STATIC_STR_63HZ_OFFSET (129)
#define STATIC_STR_100HZ_OFFSET (135)
#define STATIC_STR_160HZ_OFFSET (142)
#define STATIC_STR_250HZ_OFFSET (149)
#define STATIC_STR_400HZ_OFFSET (156)
#define STATIC_STR_630HZ_OFFSET (163)
#define STATIC_STR_1KHZ_OFFSET (170)
#define STATIC_STR_1_6KHZ_OFFSET (176)
#define STATIC_STR_2_5KHZ_OFFSET (184)
#define STATIC_STR_4KHZ_OFFSET (192)
#define STATIC_STR_6_3KHZ_OFFSET (198)
#define STATIC_STR_10KHZ_OFFSET (206)
#define STATIC_STR_16KHZ_OFFSET (213)
#define STATIC_STR_CLEAR_OFFSET (220)
#define STATIC_STR_LINE_OFFSET (243)
#define STATIC_STR_SAVING_OFFSET (266)
#define STATIC_STR_UNSAVED_OFFSET (289)

// Menu Item Indices, Multiple defines for easy access
#define MENU_ITEM_RETURN_IDX (0)
#define MENU_ITEM_AFREQKHZ_IDX (1)
#define MENU_ITEM_BFREQKHZ_IDX (2)
#define MENU_ITEM_VOLUME_IDX (3)
#define MENU_ITEM_ECHO_IDX (4)
#define MENU_ITEM_ECHORATIO_IDX (5)
#define MENU_ITEM_ECHODELAY_IDX (6)
#define MENU_ITEM_EXCITER_IDX (7)
#define MENU_ITEM_EXCITERODD_IDX (8)
#define MENU_ITEM_EXCITEREVEN_IDX (9)
#define MENU_ITEM_EQ_IDX (10)
#define MENU_ITEM_25HZ_IDX (11)
#define MENU_ITEM_40HZ_IDX (12)
#define MENU_ITEM_63HZ_IDX (13)
#define MENU_ITEM_100HZ_IDX (14)
#define MENU_ITEM_160HZ_IDX (15)
#define MENU_ITEM_250HZ_IDX (16)
#define MENU_ITEM_400HZ_IDX (17)
#define MENU_ITEM_630HZ_IDX (18)
#define MENU_ITEM_1KHZ_IDX (19)
#define MENU_ITEM_1_6KHZ_IDX (20)
#define MENU_ITEM_2_5KHZ_IDX (21)
#define MENU_ITEM_4KHZ_IDX (22)
#define MENU_ITEM_6_3KHZ_IDX (23)
#define MENU_ITEM_10KHZ_IDX (24)
#define MENU_ITEM_16KHZ_IDX (25)
#define MENU_ITEM_EQ_SUB_IDX (26)
#define MENU_ITEM_ECHO_SUB_IDX (27)
#define MENU_ITEM_EXCITER_SUB_IDX (28)

#define MENU_VAL_DATA_LEN (27)

#define MENU_SUBMENU_MAX_IDX (3)
#define MENU_SUBMENU_EQ_IDX (0)
#define MENU_SUBMENU_ECHO_IDX (1)
#define MENU_SUBMENU_EXCITER_IDX (2)

#endif
