#include "string_lib.h"

// 8位无符号减法除法, 返回商, *num更新为余数
uint8_t uint8_div(uint8_t __xdata * __xdata num, uint8_t __xdata divisor) {
    uint8_t __xdata q = 0;
    while (*num >= divisor) { *num -= divisor; q++; }
    return q;
}

// 32位无符号减法除法, 返回商, *num更新为余数
uint32_t uint32_div(uint32_t __xdata * __xdata num, uint32_t __xdata divisor) {
    uint32_t __xdata q = 0;
    while (*num >= divisor) { *num -= divisor; q++; }
    return q;
}

// 公共字符串缓冲区,第0个元素是字符串长度
char __xdata public_str_buf[12] = {0};
char __xdata * const public_str = public_str_buf + 1;

#define public_str_len (public_str_buf[0])

uint8_t get_public_str_len(void) {
    return public_str_len;
}

// 后续带buf输入的只需要增加public_str_len即可

static void uint8_to_hex_buf(uint8_t __xdata num, char __xdata *buf)
{
    uint8_t __xdata tmp = num >> 4;
    buf[0] = ((tmp) < 10) ? ('0' + (tmp)) : ('A' + (tmp) - 10);
    tmp = num & 0x0F;
    buf[1] = ((tmp) < 10) ? ('0' + (tmp)) : ('A' + (tmp) - 10);
    buf[2] = '\0';
    public_str_len += 2;
}
// 8位无符号整数转十进制字符串缓冲区(无前导零)
static void uint8_to_dec_buf(uint8_t __xdata num, char __xdata *buf)
{
    uint8_t __xdata start = 0, d;
    // 百位
    d = uint8_div(&num, 100);
    if (d) buf[start++] = '0' + d;
    // 十位
    d = uint8_div(&num, 10);
    if (d || start) buf[start++] = '0' + d;
    // 个位
    buf[start++] = '0' + num;
    buf[start] = '\0';
    public_str_len += start;
}

// 后续buf输出的只需要重设public_str_len即可
const char __xdata * uint8_to_dec_str(uint8_t __xdata num) {
    public_str_len = 0;
    uint8_to_dec_buf(num, public_str);
    return public_str;
}
const char __xdata * two_uint8_to_dec_str(uint8_t __xdata num1, uint8_t __xdata num2, char __xdata split) {
    uint8_t __xdata i = 0;
    public_str_len = 0;
    uint8_to_dec_buf(num1, public_str);
    while (public_str[i] != '\0') {
        ++i;
    }
    public_str[i] = split;
    public_str_len += 1;
    uint8_to_dec_buf(num2, public_str + i + 1);
    return public_str;
}
const char __xdata * uint8_to_hex_str(uint8_t __xdata num)
{
    public_str_len = 0;
    uint8_to_hex_buf(num, public_str);
    return public_str;
}

const char __xdata * uint32_to_hex_str(uint32_t __xdata num)
{
    public_str_len = 0;
    uint8_t __xdata i = 4, tmp;
    while (i--)
    {
        tmp = (num >> (i * 8)) & 0xFF;
        uint8_to_hex_buf(tmp, public_str + ((3 - i) * 2));
    }
    return public_str;
}

// 8位整数转字符串, 输出十进制字符串
const char __xdata * int8_to_dec_str(int8_t __xdata num) {
    if (num < 0) {
        public_str[0] = '-';
        public_str_len = 1;
        uint8_to_dec_buf(-num, public_str + 1);
    } else {
        public_str_len = 0;
        uint8_to_dec_buf(num, public_str);
    }
    return public_str;
}

// 10的幂次表
static const uint32_t __code _pow10[] = {
    1000000000UL, 100000000UL, 10000000UL, 1000000UL,
    100000UL, 10000UL, 1000UL, 100UL, 10UL, 1UL
};

const char __xdata * uint32_to_dec_str(uint32_t __xdata num)
{
    uint8_t __xdata i = 0, d, started = 0;
    const uint32_t __code *p = _pow10;
    const uint32_t __code *end = _pow10 + 10;
    for (; p < end; p++) {
        d = (uint8_t)uint32_div(&num, *p);
        if (d || started) {
            public_str[i++] = '0' + d;
            started = 1;
        }
    }
    if (i == 0) public_str[i++] = '0';
    public_str[i] = '\0';
    public_str_len = i;
    return public_str;
}

const char __xdata * int32_to_dec_str(int32_t __xdata num) {
    if (num < 0) {
        uint32_to_dec_str(-(uint32_t)num);
        // 右移所有字符，插入负号
        uint8_t __xdata i = public_str_len;
        while (i > 0) {
            public_str[i] = public_str[i - 1];
            --i;
        }
        public_str[0] = '-';
        public_str_len += 1;
        public_str[public_str_len] = '\0';
    } else {
        uint32_to_dec_str((uint32_t)num);
    }
    return public_str;
}

// 定点数转字符串, decimal_places是从右向左数的小数位数
// 例如: uint32_fixed_to_dec_str(12345, 2) => "123.45"
const char __xdata * uint32_fixed_to_dec_str(uint32_t __xdata num, uint8_t __xdata decimal_places) {
    uint8_t __xdata len = 0;
    uint8_t __xdata i;
    uint32_to_dec_str(num);
    if (decimal_places == 0) {
        return public_str;
    }
    len = public_str_len;

    /* 整数部分足够, 插入小数点: 将小数位移1位, 放入 '.' */
    i = len;
    /* 整数部分不够, 插入小数点在所有整数前面 */
    len = ((len > decimal_places) ? (len - decimal_places) : 0);
    for (; i >= len; i--) {
        public_str[i + 1] = public_str[i];
    }
    public_str[len] = '.';
    public_str_len += 1;

    return public_str;
}

// 进度条样式生成,输入范围为0-15,对应0-100% 15格显示
const char __xdata * uint4_to_bar_str(uint8_t __xdata bar)
{
    uint8_t __xdata i = 0;
    bar = bar & 0x0F;
    for (; i < bar; i++) public_str[i] = '!';
    for (; i < 16; i++) public_str[i] = '{';
    public_str[16] = '\0';
    public_str_len = 16;
    return public_str;
}
