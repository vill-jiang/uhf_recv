#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
将 Keil 语法的 STC8H.h 转换为 SDCC 兼容的头文件
使用 compiler.h 中定义的 SFR/SBIT/SFRX 宏
"""

import re
import sys

input_file = r'./src/STC8H.h'
output_file = input_file  # 直接覆盖

with open(input_file, 'r', encoding='utf-8') as f:
    content = f.read()

# 第一步：收集所有 sfr 名称到地址的映射
sfr_map = {}
for m in re.finditer(r'^\s*sfr\s+(\w+)\s*=\s*(0x[0-9a-fA-F]+)\s*;', content, re.MULTILINE):
    sfr_map[m.group(1)] = m.group(2)

print(f'找到 {len(sfr_map)} 个 SFR 寄存器')

sfr_count = 0
sbit_count = 0
xdata_count = 0
nop_count = 0

lines = content.split('\n')
new_lines = []
is_included = False

for i, line in enumerate(lines):
    stripped = line.strip()

    # 转换 sfr 声明: sfr NAME = 0xADDR;  ->  SFR(NAME, 0xADDR);
    sfr_match = re.match(r'^sfr\s+(\w+)\s*=\s*(0x[0-9a-fA-F]+)\s*;', stripped)
    if sfr_match:
        name = sfr_match.group(1)
        addr = sfr_match.group(2)
        new_lines.append(f'SFR({name}, {addr});')
        sfr_count += 1
        continue

    # 转换 sbit 声明: sbit NAME = SFR_NAME^BIT;  ->  SBIT(NAME, 0xADDR, BIT);
    sbit_match = re.match(r'^\s*sbit\s+(\w+)\s*=\s*(\w+)\^(\d+)\s*;', stripped)
    if sbit_match:
        name = sbit_match.group(1)
        sfr_name = sbit_match.group(2)
        bit = sbit_match.group(3)
        if sfr_name in sfr_map:
            addr = sfr_map[sfr_name]
            new_lines.append(f'    SBIT({name}, {addr}, {bit});')
            sbit_count += 1
        else:
            print(f'WARNING: 第{i+1}行, sfr "{sfr_name}" 未找到地址映射', file=sys.stderr)
            new_lines.append(f'    /* WARNING: sfr {sfr_name} not found */ // {line.strip()}')
        continue

    # 转换 xdata 关键字在 #define 宏中: " xdata " -> " __xdata "
    if '#define' in stripped and ' xdata ' in line:
        line = line.replace(' xdata ', ' __xdata ')
        new_lines.append(line)
        xdata_count += 1
        continue

    # 转换 _nop_() 为 NOP()
    if '_nop_()' in stripped:
        line = line.replace('_nop_()', 'NOP()')
        new_lines.append(line)
        nop_count += 1
        continue

    # 转换 NOP 声明: NOP39(),NOP1()  ->  NOP39();NOP1()
    nop_match = re.match(r'#define\s+NOP\d+\(\)\s+(NOP\d+\(\)),NOP1\(\)', stripped)
    if nop_match:
        nop_n = nop_match.group(1)
        new_lines.append(stripped.replace(nop_n + ',NOP1()', nop_n + ';NOP1()'))
        nop_count += 1
        continue

    # 删除 NOP(N)
    if 'NOP##N' in stripped:
        nop_count += 1
        continue

    # 添加 #include <compiler.h>
    if stripped.startswith('///////////////////////////////////') and not is_included:
        new_lines.append('#include <compiler.h>')
        is_included = True
        continue

    # 其他行保持不变
    new_lines.append(line)

result = '\n'.join(new_lines)

with open(output_file, 'w', encoding='utf-8') as f:
    f.write(result)

print(f'转换完成！')
print(f'  SFR 转换: {sfr_count} 个')
print(f'  SBIT 转换: {sbit_count} 个')
print(f'  XDATA 转换: {xdata_count} 个')
print(f'  NOP 转换: {nop_count} 个')
print(f'输出文件: {output_file}')
