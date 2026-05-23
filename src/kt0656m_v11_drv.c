#include "kt0656m_v11_drv.h"
#include "type_def.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_EEPROM.h"
#include "STC8G_H_I2C.h"

uint8_t __xdata kt0656m_current_addr = KT0656M_ADDR_A;

#define OP_END (0x00)
#define OP_ADDR_OLD (0x00)
#define OP_ADDR_INC (0x40)
#define OP_ADDR_ONE_BYTE (0x80)
#define OP_ADDR_TWO_BYTES (0xC0)

#define OP_DELAY_READ (0x01)
#define OP_READ_ADDR (0x02)
#define OP_READ_ROM (0x03)
#define OP_AND (0x04)
#define OP_OR (0x08)
#define OP_AND_OR (OP_AND | OP_OR)
#define OP_WRITE (0x10)
#define OP_LOOP (0x20)
#define OP_READ_RAM_WRITE (0x30)

void kt_bus_write(uint16_t __xdata reg_addr, uint8_t __xdata data)
{
    reg_addr = ((reg_addr >> 8) & 0xFF) | (reg_addr << 8);
    I2C_WriteNbyteAddrLen(kt0656m_current_addr, (uint8_t *)(&reg_addr), 2, &data, 1);
}
uint8_t __xdata kt_bus_read(uint16_t __xdata reg_addr)
{
    uint8_t __xdata read_data = 0;
    reg_addr = ((reg_addr >> 8) & 0xFF) | (reg_addr << 8);
    I2C_ReadNbyteAddrLen(kt0656m_current_addr, (uint8_t *)(&reg_addr), 2, &read_data, 1);
    return read_data;
}

uint8_t __xdata public_data[3] = {0};
void kt0656m_run_step_seq(const uint8_t __code * __xdata steps_seq)
{
    uint16_t __xdata addr = 0;
    uint8_t __xdata reg = 0;
    uint8_t __xdata op = 0;
    uint8_t __xdata i = 0;
    uint8_t __xdata mask = 0;
    uint8_t __xdata cmd = 0;
    do
    {
        i = 0; mask = 0x03;
        op = *steps_seq++;
        if (op == OP_END) return;
        // 地址处理
        cmd = op & 0xC0;
        if (cmd == OP_ADDR_INC) {
            addr++;
        } else if (cmd == OP_ADDR_ONE_BYTE) {
            addr = *steps_seq;
            steps_seq++;
        } else if (cmd == OP_ADDR_TWO_BYTES) {
            addr = (uint16_t)steps_seq[0] << 8 | steps_seq[1];
            steps_seq += 2;
        }
        // 操作处理
        do {
            cmd = op & mask;
            if (cmd == OP_DELAY_READ) {
                delay_ms(1);
            }
            if (cmd == OP_READ_ADDR || cmd == OP_DELAY_READ) {
                reg = kt_bus_read(addr);
            } else if (cmd == OP_READ_ROM) {
                reg = steps_seq[i++];
            } else if (cmd == OP_AND) {
                reg &= steps_seq[i++];
            } else if (cmd == OP_OR) {
                reg |= steps_seq[i++];
            } else if (cmd == OP_AND_OR) {
                reg &= steps_seq[i++];
                reg |= steps_seq[i++];
            } else if (cmd == OP_WRITE) {
                kt_bus_write(addr, reg);
            } else if (cmd == OP_LOOP) {
                if (reg == steps_seq[i++]) {
                    i = 0;
                    mask = 0x03;
                    continue;
                }
            } else if (cmd == OP_READ_RAM_WRITE) {
                kt_bus_write(addr, public_data[reg]);
            }
            mask <<= 2;
        } while (mask < 0xC0);
        steps_seq += i;
    } while (1);
}

void kt0656m_tune(void)
{
    int32_t __xdata freq = 0;
    if (kt0656m_current_addr == KT0656M_ADDR_MASTER) {
        freq = *((int32_t __code *)(default_data_channel_a));
    } else {
        freq = *((int32_t __code *)(default_data_channel_b));
    }
    freq = freq & 0x000FFFFF;
    public_data[0] = (freq >> 12);
    public_data[1] = ((freq & 0x00000FFF) >> 4);
    public_data[2] = (kt_bus_read(0x0047) & 0x0F) | ((freq & 0x0000000F) << 4);
    kt0656m_run_step_seq(kt0656m_v11_tune);
    if (kt0656m_current_addr == KT0656M_ADDR_MASTER)
    {
        kt0656m_sai_init_master();
        kt0656m_volume(default_data_channel_a[4]);
    }
    else
    {
        kt0656m_sai_init_slave();
        kt0656m_volume(default_data_channel_b[4]);
    }
}

// 获取当前的频道KHz
void kt0656m_get_freq(int32_t __xdata * __xdata freq) {
    *freq = 0;
    *freq = kt_bus_read(0x0045);
    *freq <<= 8;
    *freq |= kt_bus_read(0x0046);
    *freq <<= 8;
    *freq |= kt_bus_read(0x0047);
    *freq >>= 4;
}

void kt0656m_volume(uint8_t __xdata volume)
{
    kt_bus_write(0x201, (kt_bus_read(0x201) & 0xE0) | (volume));
}

void kt0656m_inner_init(void) {
    kt0656m_run_init_seq();
    delay_ms(10);
    kt0656m_volume(0);
    kt0656m_set_echo_eq();
    kt0656m_disable_diversity();
}

void kt0656m_init(void) {
    PCM_MUTE_PIN = 0;
    KT0656M_CHIP_EN_AM = 0;
    KT0656M_CHIP_EN_BM = 0;
    delay_ms(20);
    KT0656M_CHIP_EN_AM = 1;
    kt0656m_current_addr = KT0656M_ADDR_A;
    delay_ms(25);
    kt0656m_inner_init();
    kt0656m_tune();
    // kt0656m_set_max_rf_gain(3);
    KT0656M_CHIP_EN_BM = 1;
    kt0656m_current_addr = KT0656M_ADDR_B;
    delay_ms(25);
    kt0656m_inner_init();
    kt0656m_tune();
    // kt0656m_set_max_rf_gain(3);
    PCM_MUTE_PIN = 1;
}

// void kt0656m_set_max_rf_gain(uint8_t __xdata sel)
// {
//     uint8_t __xdata regx, rf_gain;
//     sel = sel & 0x03;
//     regx = kt_bus_read(0x0102);
//     kt_bus_write(0x0102, regx & 0xFC | sel);
//     regx = kt_bus_read(0x005b);
//     rf_gain = regx & 0x7F;
//     if (rf_gain > ((sel << 2) + 42))
//     {
//         rf_gain = (sel << 2) + 42;
//         kt_bus_write(0x005b, (regx & 0x80) | rf_gain);
//     }
// }

void kt0656m_set_echo_eq(void) {
    uint16_t __xdata addr = 0x0266;
    const uint8_t __code * __xdata code_data_ptr = 
        ((kt0656m_current_addr == KT0656M_ADDR_MASTER) ? default_data_channel_a : default_data_channel_b);
    // ECHO_SW: 0 DISABLE, 1 ENABLE
    // ECHO_STRU: 0 全通, 1 梳状
    // ECHO_GAIN_DOWN: 0 -13dB, 1 -10dB, 2 -7dB
    // ECHO_GAIN_UP: 0 0dB, 1 1.9dB, 2 3.5dB, 3 5.5dB, 4 7dB, 5 9.4dB, 6 10.9dB, 7 13.1dB
    // (ECHO_SW << 7) | (ECHO_STRU << 6) | (ECHO_GAIN_DOWN << 4) | (ECHO_GAIN_UP << 0)
    kt_bus_write(addr, kt_bus_read(addr) & 0x08 | ((code_data_ptr[5] << 7) | (1 << 6) | (0 << 4) | 7));
    addr++;
    // ECHO_RATIO: 0-25 0-25/32 ECHO反馈比例
    kt_bus_write(addr, kt_bus_read(addr) & 0xE0 | code_data_ptr[6]);
    addr++;
    // ECHO_DELAY: 0-23 22ms-197ms ECHO信号延时
    kt_bus_write(addr, kt_bus_read(addr) & 0xE0 | code_data_ptr[7]);
    addr++;
    // EXCITER_SW: 0 DISABLE, 1 ENABLE
    // EXCITER_TUNE: 0 600Hz, 1 1KHz, 2 2KHz, 3 3.8KHz 激励起始频率
    // EXCITER_DRIVE: 0 0dB, 1 3.5dB, 2 6dB, 3 9dB, 4 12dB, 5 15dB 激励剩余增益
    // (EXCITER_SW << 7) | (EXCITER_TUNE << 5) | (EXCITER_DRIVE << 0)
    kt_bus_write(addr, kt_bus_read(addr) & 0x18 | (code_data_ptr[8] << 7) | (2 << 5) | 0);
    addr++;
    // EXCITER_ODD: 0-6 负无穷-0dB 奇次激励衰减量
    // EXCITER_EVEN: 0-6 负无穷-0dB 偶次激励衰减量
    // (EXCITER_ODD << 4) | EXCITER_EVEN
    kt_bus_write(addr, kt_bus_read(addr) & 0x88 | (code_data_ptr[9] << 4) | code_data_ptr[10]);
    addr = 0x0257;
    // # EQ_EN: 0 DISABLE, 1 ENABLE
    // # (EQ_EN << 5) | GAIN_25Hz
    kt_bus_write(addr, kt_bus_read(addr) & 0xC0 | (code_data_ptr[11] << 5) | (code_data_ptr[12] + 12));
    for (uint8_t i = 13; i < DEFAULT_DATA_CHANNEL_A_LEN; ++i) {
        addr++;
        kt_bus_write(addr, code_data_ptr[i] + 12);
    }
}
