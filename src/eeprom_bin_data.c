#include "eeprom_bin_data.h"
#include "STC8G_H_EEPROM.h"

const uint8_t __code * __xdata ssd1106_init_sequence = (const uint8_t __code * __xdata)(MOVC_ShiftAddress + 0x0000);
const uint8_t __code * __xdata ssd1106_font6x8 = (const uint8_t __code * __xdata)(MOVC_ShiftAddress + 0x001A);
const uint8_t __code * __xdata ssd1106_font8x16 = (const uint8_t __code * __xdata)(MOVC_ShiftAddress + 0x0242);
const uint8_t __code * __xdata ssd1106_power_icon_16x16 = (const uint8_t __code * __xdata)(MOVC_ShiftAddress + 0x0832);
const uint8_t __code * __xdata kt0656m_v11_init_seq = (const uint8_t __code * __xdata)(MOVC_ShiftAddress + 0x0852);
const uint8_t __code * __xdata kt0656m_v11_sai_init_master_seq = (const uint8_t __code * __xdata)(MOVC_ShiftAddress + 0x08E0);
const uint8_t __code * __xdata kt0656m_v11_sai_init_slave_seq = (const uint8_t __code * __xdata)(MOVC_ShiftAddress + 0x08ED);
const uint8_t __code * __xdata kt0656m_v11_tune = (const uint8_t __code * __xdata)(MOVC_ShiftAddress + 0x0901);
const uint8_t __code * __xdata start_icon_bmp = (const uint8_t __code * __xdata)(MOVC_ShiftAddress + 0x091C);
const uint8_t __code * __xdata static_str_data = (const uint8_t __code * __xdata)(MOVC_ShiftAddress + 0x0ABC);
const uint8_t __code * __xdata static_val_type_data = (const uint8_t __code * __xdata)(MOVC_ShiftAddress + 0x0BF3);
const uint8_t __code * __xdata static_menu_item_data = (const uint8_t __code * __xdata)(MOVC_ShiftAddress + 0x0C69);
const uint8_t __code * __xdata default_data_channel_a = (const uint8_t __code * __xdata)(MOVC_ShiftAddress + 0x0E00);
const uint8_t __code * __xdata default_data_channel_b = (const uint8_t __code * __xdata)(MOVC_ShiftAddress + 0x0E1B);
