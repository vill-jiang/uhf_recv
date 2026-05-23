//****************************************************************************
// 来源于 KT_WirelessMicRxdrv.h 的 democode
// 实现了原始代码经过特化指令序列存储到eeprom以节省Flash空间
//****************************************************************************
#ifndef _KT0656M_V11_DRV_H_
#define _KT0656M_V11_DRV_H_

#include "config.h"
#include "eeprom_bin_data.h"

#define KT0656M_ADDR_A (0x62)
#define KT0656M_ADDR_B (0x72)
#define KT0656M_ADDR_MASTER (0x62)

extern uint8_t __xdata kt0656m_current_addr;

void kt0656m_run_step_seq(const uint8_t __code * __xdata steps_seq);
#define kt0656m_run_init_seq() kt0656m_run_step_seq(kt0656m_v11_init_seq)
#define kt0656m_sai_init_master() kt0656m_run_step_seq(kt0656m_v11_sai_init_master_seq)
#define kt0656m_sai_init_slave() kt0656m_run_step_seq(kt0656m_v11_sai_init_slave_seq)

void kt0656m_tune(void);  // in KHz
// 获取当前的频道KHz
void kt0656m_get_freq(int32_t __xdata * __xdata freq);
void kt0656m_volume(uint8_t __xdata volume);
void kt0656m_inner_init(void);
void kt0656m_init(void);

void kt_bus_write(uint16_t __xdata reg_addr, uint8_t __xdata data);
uint8_t __xdata kt_bus_read(uint16_t __xdata reg_addr);

#define kt0656m_get_af() (kt_bus_read(0x0209) & 0x0F)
// 有天线分集并且是从芯片时 0x0221
#define kt0656m_get_rssi() kt_bus_read(0x020C)
// 有天线分集并且是从芯片时 0x0222
#define kt0656m_get_fast_rssi() kt_bus_read(0x020A)
#define kt0656m_automute() (kt_bus_read(0x0088) & 0x01)
// 关闭天线分集 0x021C
#define kt0656m_disable_diversity() kt_bus_write(0x021C, kt_bus_read(0x021C) & 0xBF)
// 有天线分集并且是从芯片时 0x0223
#define kt0656m_get_snr() kt_bus_read(0x020D)
// #define kt0656m_battery_meter_read() ((int16_t)kt_bus_read(0x00c0) << 8 | kt_bus_read(0x00c1))
// 输入范围0-3 对应 36, 40, 44, 48
// void kt0656m_set_max_rf_gain(uint8_t __xdata sel);
void kt0656m_set_echo_eq(void);

#endif
