#ifndef __STRING_LIB_H__
#define __STRING_LIB_H__

#include "config.h"

extern char __xdata * const public_str;

// 减法除法函数, 返回商, *num更新为余数
uint8_t uint8_div(uint8_t __xdata * __xdata num, uint8_t __xdata divisor);
uint32_t uint32_div(uint32_t __xdata * __xdata num, uint32_t __xdata divisor);

uint8_t get_public_str_len(void);

const char __xdata * uint8_to_hex_str(uint8_t __xdata num);
// const char* uint8_to_dec_str(uint8_t num);
const char __xdata * uint32_to_hex_str(uint32_t __xdata num);
// 8位整数转字符串, 输出十进制字符串
const char __xdata * uint8_to_dec_str(uint8_t __xdata num);
const char __xdata * int8_to_dec_str(int8_t __xdata num);
const char __xdata * two_uint8_to_dec_str(uint8_t __xdata num1, uint8_t __xdata num2, char __xdata split);
// 32位整数转字符串, 输出十进制字符串
const char __xdata * uint32_to_dec_str(uint32_t __xdata num);
const char __xdata * int32_to_dec_str(int32_t __xdata num);
// 定点数转字符串, 输出十进制字符串, decimal_places是从右向左数的小数位数
const char __xdata * uint32_fixed_to_dec_str(uint32_t __xdata num, uint8_t __xdata decimal_places);
// 进度条样式生成,输入范围为0-15,对应0-100% 16格显示
const char __xdata * uint4_to_bar_str(uint8_t __xdata bar);
#endif