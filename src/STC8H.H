#ifndef __STC8H_H__
#define __STC8H_H__

#include <compiler.h>

//包含本头文件后,不用另外再包含"REG51.H"

SFR(P0, 0x80);
    SBIT(P00, 0x80, 0);
    SBIT(P01, 0x80, 1);
    SBIT(P02, 0x80, 2);
    SBIT(P03, 0x80, 3);
    SBIT(P04, 0x80, 4);
    SBIT(P05, 0x80, 5);
    SBIT(P06, 0x80, 6);
    SBIT(P07, 0x80, 7);

SFR(SP, 0x81);
SFR(DPL, 0x82);
SFR(DPH, 0x83);
SFR(S4CON, 0x84);
SFR(S4BUF, 0x85);
SFR(PCON, 0x87);

SFR(TCON, 0x88);
    SBIT(TF1, 0x88, 7);
    SBIT(TR1, 0x88, 6);
    SBIT(TF0, 0x88, 5);
    SBIT(TR0, 0x88, 4);
    SBIT(IE1, 0x88, 3);
    SBIT(IT1, 0x88, 2);
    SBIT(IE0, 0x88, 1);
    SBIT(IT0, 0x88, 0);

SFR(TMOD, 0x89);
SFR(TL0, 0x8a);
SFR(TL1, 0x8b);
SFR(TH0, 0x8c);
SFR(TH1, 0x8d);
SFR(AUXR, 0x8e);
SFR(INTCLKO, 0x8f);

SFR(P1, 0x90);
    SBIT(P10, 0x90, 0);
    SBIT(P11, 0x90, 1);
    SBIT(P12, 0x90, 2);
    SBIT(P13, 0x90, 3);
    SBIT(P14, 0x90, 4);
    SBIT(P15, 0x90, 5);
    SBIT(P16, 0x90, 6);
    SBIT(P17, 0x90, 7);

SFR(P1M1, 0x91);
SFR(P1M0, 0x92);
SFR(P0M1, 0x93);
SFR(P0M0, 0x94);
SFR(P2M1, 0x95);
SFR(P2M0, 0x96);

SFR(SCON, 0x98);
    SBIT(SM0, 0x98, 7);
    SBIT(SM1, 0x98, 6);
    SBIT(SM2, 0x98, 5);
    SBIT(REN, 0x98, 4);
    SBIT(TB8, 0x98, 3);
    SBIT(RB8, 0x98, 2);
    SBIT(TI, 0x98, 1);
    SBIT(RI, 0x98, 0);

SFR(SBUF, 0x99);
SFR(S2CON, 0x9a);
SFR(S2BUF, 0x9b);
SFR(IRCBAND, 0x9d);
SFR(LIRTRIM, 0x9e);
SFR(IRTRIM, 0x9f);

SFR(P2, 0xa0);
    SBIT(P20, 0xa0, 0);
    SBIT(P21, 0xa0, 1);
    SBIT(P22, 0xa0, 2);
    SBIT(P23, 0xa0, 3);
    SBIT(P24, 0xa0, 4);
    SBIT(P25, 0xa0, 5);
    SBIT(P26, 0xa0, 6);
    SBIT(P27, 0xa0, 7);

SFR(P_SW1, 0xa2);

SFR(IE, 0xa8);
    SBIT(EA, 0xa8, 7);
    SBIT(ELVD, 0xa8, 6);
    SBIT(EADC, 0xa8, 5);
    SBIT(ES, 0xa8, 4);
    SBIT(ET1, 0xa8, 3);
    SBIT(EX1, 0xa8, 2);
    SBIT(ET0, 0xa8, 1);
    SBIT(EX0, 0xa8, 0);

SFR(SADDR, 0xa9);
SFR(WKTCL, 0xaa);
SFR(WKTCH, 0xab);
SFR(S3CON, 0xac);
SFR(S3BUF, 0xad);
SFR(TA, 0xae);
SFR(IE2, 0xaf);

SFR(P3, 0xb0);
    SBIT(P30, 0xb0, 0);
    SBIT(P31, 0xb0, 1);
    SBIT(P32, 0xb0, 2);
    SBIT(P33, 0xb0, 3);
    SBIT(P34, 0xb0, 4);
    SBIT(P35, 0xb0, 5);
    SBIT(P36, 0xb0, 6);
    SBIT(P37, 0xb0, 7);

    SBIT(RD, 0xb0, 7);
    SBIT(WR, 0xb0, 6);
    SBIT(T1, 0xb0, 5);
    SBIT(T0, 0xb0, 4);
    SBIT(INT1, 0xb0, 3);
    SBIT(INT0, 0xb0, 2);
    SBIT(TXD, 0xb0, 1);
    SBIT(RXD, 0xb0, 0);

SFR(P3M1, 0xb1);
SFR(P3M0, 0xb2);
SFR(P4M1, 0xb3);
SFR(P4M0, 0xb4);
SFR(IP2, 0xb5);
SFR(IP2H, 0xb6);
SFR(IPH, 0xb7);

SFR(IP, 0xb8);
    SBIT(PPCA, 0xb8, 7);
    SBIT(PLVD, 0xb8, 6);
    SBIT(PADC, 0xb8, 5);
    SBIT(PS, 0xb8, 4);
    SBIT(PT1, 0xb8, 3);
    SBIT(PX1, 0xb8, 2);
    SBIT(PT0, 0xb8, 1);
    SBIT(PX0, 0xb8, 0);

SFR(SADEN, 0xb9);
SFR(P_SW2, 0xba);
SFR(ADC_CONTR, 0xbc);
SFR(ADC_RES, 0xbd);
SFR(ADC_RESL, 0xbe);

SFR(P4, 0xc0);
    SBIT(P40, 0xc0, 0);
    SBIT(P41, 0xc0, 1);
    SBIT(P42, 0xc0, 2);
    SBIT(P43, 0xc0, 3);
    SBIT(P44, 0xc0, 4);
    SBIT(P45, 0xc0, 5);
    SBIT(P46, 0xc0, 6);
    SBIT(P47, 0xc0, 7);

SFR(WDT_CONTR, 0xc1);
SFR(IAP_DATA, 0xc2);
SFR(IAP_ADDRH, 0xc3);
SFR(IAP_ADDRL, 0xc4);
SFR(IAP_CMD, 0xc5);
SFR(IAP_TRIG, 0xc6);
SFR(IAP_CONTR, 0xc7);

SFR(P5, 0xc8);
    SBIT(P50, 0xc8, 0);
    SBIT(P51, 0xc8, 1);
    SBIT(P52, 0xc8, 2);
    SBIT(P53, 0xc8, 3);
    SBIT(P54, 0xc8, 4);
    SBIT(P55, 0xc8, 5);
    SBIT(P56, 0xc8, 6);
    SBIT(P57, 0xc8, 7);

SFR(P5M1, 0xc9);
SFR(P5M0, 0xca);
SFR(P6M1, 0xcb);
SFR(P6M0, 0xcc);
SFR(SPSTAT, 0xcd);
SFR(SPCTL, 0xce);
SFR(SPDAT, 0xcf);

SFR(PSW, 0xd0);
    SBIT(CY, 0xd0, 7);
    SBIT(AC, 0xd0, 6);
    SBIT(F0, 0xd0, 5);
    SBIT(RS1, 0xd0, 4);
    SBIT(RS0, 0xd0, 3);
    SBIT(OV, 0xd0, 2);
    SBIT(F1, 0xd0, 1);
    SBIT(P, 0xd0, 0);

SFR(T4T3M, 0xd1);
SFR(T4H, 0xd2);
SFR(T4L, 0xd3);
SFR(T3H, 0xd4);
SFR(T3L, 0xd5);
SFR(T2H, 0xd6);
SFR(T2L, 0xd7);

SFR(T3T4M, 0xd1);
SFR(TH4, 0xd2);
SFR(TL4, 0xd3);
SFR(TH3, 0xd4);
SFR(TL3, 0xd5);
SFR(TH2, 0xd6);
SFR(TL2, 0xd7);

SFR(USBCLK, 0xdc);
SFR(PLLCR, 0xdc);
SFR(MDU32SR, 0xdd);
SFR(ADCCFG, 0xde);
SFR(IP3, 0xdf);
SFR(ACC, 0xe0);
SFR(P7M1, 0xe1);
SFR(P7M0, 0xe2);
SFR(DPS, 0xe3);
SFR(DPL1, 0xe4);
SFR(DPH1, 0xe5);
SFR(CMPCR1, 0xe6);
SFR(CMPCR2, 0xe7);

SFR(P6, 0xe8);
    SBIT(P60, 0xe8, 0);
    SBIT(P61, 0xe8, 1);
    SBIT(P62, 0xe8, 2);
    SBIT(P63, 0xe8, 3);
    SBIT(P64, 0xe8, 4);
    SBIT(P65, 0xe8, 5);
    SBIT(P66, 0xe8, 6);
    SBIT(P67, 0xe8, 7);

SFR(USBDAT, 0xec);
SFR(MDU32CR, 0xed);
SFR(IP3H, 0xee);
SFR(AUXINTIF, 0xef);
SFR(B, 0xf0);
SFR(USBCON, 0xf4);
SFR(IAP_TPS, 0xf5);

SFR(P7, 0xf8);
    SBIT(P70, 0xf8, 0);
    SBIT(P71, 0xf8, 1);
    SBIT(P72, 0xf8, 2);
    SBIT(P73, 0xf8, 3);
    SBIT(P74, 0xf8, 4);
    SBIT(P75, 0xf8, 5);
    SBIT(P76, 0xf8, 6);
    SBIT(P77, 0xf8, 7);

SFR(USBADR, 0xfc);
SFR(RSTCFG, 0xff);

//如下特殊功能寄存器位于扩展RAM区域
//访问这些寄存器,需先将P_SW2的BIT7设置为1,才可正常读写

/////////////////////////////////////////////////
//FF00H-FFFFH
/////////////////////////////////////////////////



/////////////////////////////////////////////////
//FE00H-FEFFH
/////////////////////////////////////////////////

#define     CLKSEL                  (*(unsigned char volatile __xdata *)0xfe00)
#define     CLKDIV                  (*(unsigned char volatile __xdata *)0xfe01)
#define     HIRCCR                  (*(unsigned char volatile __xdata *)0xfe02)
#define     XOSCCR                  (*(unsigned char volatile __xdata *)0xfe03)
#define     IRC32KCR                (*(unsigned char volatile __xdata *)0xfe04)
#define     MCLKOCR                 (*(unsigned char volatile __xdata *)0xfe05)
#define     IRCDB                   (*(unsigned char volatile __xdata *)0xfe06)
#define     IRC48MCR                (*(unsigned char volatile __xdata *)0xfe07)
#define     X32KCR                  (*(unsigned char volatile __xdata *)0xfe08)
#define     HSCLKDIV                (*(unsigned char volatile __xdata *)0xfe0b)

#define     P0PU                    (*(unsigned char volatile __xdata *)0xfe10)
#define     P1PU                    (*(unsigned char volatile __xdata *)0xfe11)
#define     P2PU                    (*(unsigned char volatile __xdata *)0xfe12)
#define     P3PU                    (*(unsigned char volatile __xdata *)0xfe13)
#define     P4PU                    (*(unsigned char volatile __xdata *)0xfe14)
#define     P5PU                    (*(unsigned char volatile __xdata *)0xfe15)
#define     P6PU                    (*(unsigned char volatile __xdata *)0xfe16)
#define     P7PU                    (*(unsigned char volatile __xdata *)0xfe17)
#define     P0NCS                   (*(unsigned char volatile __xdata *)0xfe18)
#define     P1NCS                   (*(unsigned char volatile __xdata *)0xfe19)
#define     P2NCS                   (*(unsigned char volatile __xdata *)0xfe1a)
#define     P3NCS                   (*(unsigned char volatile __xdata *)0xfe1b)
#define     P4NCS                   (*(unsigned char volatile __xdata *)0xfe1c)
#define     P5NCS                   (*(unsigned char volatile __xdata *)0xfe1d)
#define     P6NCS                   (*(unsigned char volatile __xdata *)0xfe1e)
#define     P7NCS                   (*(unsigned char volatile __xdata *)0xfe1f)
#define     P0SR                    (*(unsigned char volatile __xdata *)0xfe20)
#define     P1SR                    (*(unsigned char volatile __xdata *)0xfe21)
#define     P2SR                    (*(unsigned char volatile __xdata *)0xfe22)
#define     P3SR                    (*(unsigned char volatile __xdata *)0xfe23)
#define     P4SR                    (*(unsigned char volatile __xdata *)0xfe24)
#define     P5SR                    (*(unsigned char volatile __xdata *)0xfe25)
#define     P6SR                    (*(unsigned char volatile __xdata *)0xfe26)
#define     P7SR                    (*(unsigned char volatile __xdata *)0xfe27)
#define     P0DR                    (*(unsigned char volatile __xdata *)0xfe28)
#define     P1DR                    (*(unsigned char volatile __xdata *)0xfe29)
#define     P2DR                    (*(unsigned char volatile __xdata *)0xfe2a)
#define     P3DR                    (*(unsigned char volatile __xdata *)0xfe2b)
#define     P4DR                    (*(unsigned char volatile __xdata *)0xfe2c)
#define     P5DR                    (*(unsigned char volatile __xdata *)0xfe2d)
#define     P6DR                    (*(unsigned char volatile __xdata *)0xfe2e)
#define     P7DR                    (*(unsigned char volatile __xdata *)0xfe2f)
#define     P0IE                    (*(unsigned char volatile __xdata *)0xfe30)
#define     P1IE                    (*(unsigned char volatile __xdata *)0xfe31)
#define     P2IE                    (*(unsigned char volatile __xdata *)0xfe32)
#define     P3IE                    (*(unsigned char volatile __xdata *)0xfe33)
#define     P4IE                    (*(unsigned char volatile __xdata *)0xfe34)
#define     P5IE                    (*(unsigned char volatile __xdata *)0xfe35)
#define     P6IE                    (*(unsigned char volatile __xdata *)0xfe36)
#define     P7IE                    (*(unsigned char volatile __xdata *)0xfe37)

#define     LCMIFCFG                (*(unsigned char volatile __xdata *)0xfe50)
#define     LCMIFCFG2               (*(unsigned char volatile __xdata *)0xfe51)
#define     LCMIFCR                 (*(unsigned char volatile __xdata *)0xfe52)
#define     LCMIFSTA                (*(unsigned char volatile __xdata *)0xfe53)
#define     LCMIFDATL               (*(unsigned char volatile __xdata *)0xfe54)
#define     LCMIFDATH               (*(unsigned char volatile __xdata *)0xfe55)

#define     RTCCR                   (*(unsigned char volatile __xdata *)0xfe60)
#define     RTCCFG                  (*(unsigned char volatile __xdata *)0xfe61)
#define     RTCIEN                  (*(unsigned char volatile __xdata *)0xfe62)
#define     RTCIF                   (*(unsigned char volatile __xdata *)0xfe63)
#define     ALAHOUR                 (*(unsigned char volatile __xdata *)0xfe64)
#define     ALAMIN                  (*(unsigned char volatile __xdata *)0xfe65)
#define     ALASEC                  (*(unsigned char volatile __xdata *)0xfe66)
#define     ALASSEC                 (*(unsigned char volatile __xdata *)0xfe67)
#define     INIYEAR                 (*(unsigned char volatile __xdata *)0xfe68)
#define     INIMONTH                (*(unsigned char volatile __xdata *)0xfe69)
#define     INIDAY                  (*(unsigned char volatile __xdata *)0xfe6a)
#define     INIHOUR                 (*(unsigned char volatile __xdata *)0xfe6b)
#define     INIMIN                  (*(unsigned char volatile __xdata *)0xfe6c)
#define     INISEC                  (*(unsigned char volatile __xdata *)0xfe6d)
#define     INISSEC                 (*(unsigned char volatile __xdata *)0xfe6e)
#define     YEAR                    (*(unsigned char volatile __xdata *)0xfe70)
#define     MONTH                   (*(unsigned char volatile __xdata *)0xfe71)
#define     DAY                     (*(unsigned char volatile __xdata *)0xfe72)
#define     HOUR                    (*(unsigned char volatile __xdata *)0xfe73)
#define     MIN                     (*(unsigned char volatile __xdata *)0xfe74)
#define     SEC                     (*(unsigned char volatile __xdata *)0xfe75)
#define     SSEC                    (*(unsigned char volatile __xdata *)0xfe76)

#define     T11CR                   (*(unsigned char volatile __xdata *)0xfe78)
#define     T11PS                   (*(unsigned char volatile __xdata *)0xfe79)
#define     T11H                    (*(unsigned char volatile __xdata *)0xfe7a)
#define     T11L                    (*(unsigned char volatile __xdata *)0xfe7b)

#define     I2CCFG                  (*(unsigned char volatile __xdata *)0xfe80)
#define     I2CMSCR                 (*(unsigned char volatile __xdata *)0xfe81)
#define     I2CMSST                 (*(unsigned char volatile __xdata *)0xfe82)
#define     I2CSLCR                 (*(unsigned char volatile __xdata *)0xfe83)
#define     I2CSLST                 (*(unsigned char volatile __xdata *)0xfe84)
#define     I2CSLADR                (*(unsigned char volatile __xdata *)0xfe85)
#define     I2CTXD                  (*(unsigned char volatile __xdata *)0xfe86)
#define     I2CRXD                  (*(unsigned char volatile __xdata *)0xfe87)
#define     I2CMSAUX                (*(unsigned char volatile __xdata *)0xfe88)

#define     SPFUNC                  (*(unsigned char volatile __xdata *)0xfe98)
#define     RSTFLAG                 (*(unsigned char volatile __xdata *)0xfe99)

#define     TM2PS                   (*(unsigned char volatile __xdata *)0xfea2)
#define     TM3PS                   (*(unsigned char volatile __xdata *)0xfea3)
#define     TM4PS                   (*(unsigned char volatile __xdata *)0xfea4)
#define     ADCTIM                  (*(unsigned char volatile __xdata *)0xfea8)
#define     T3T4PIN                 (*(unsigned char volatile __xdata *)0xfeac)
#define     ADCEXCFG                (*(unsigned char volatile __xdata *)0xfead)
#define     CMPEXCFG                (*(unsigned char volatile __xdata *)0xfeae)

#define     PWM1_ETRPS              (*(unsigned char volatile __xdata *)0xfeb0)
#define     PWM1_ENO                (*(unsigned char volatile __xdata *)0xfeb1)
#define     PWM1_PS                 (*(unsigned char volatile __xdata *)0xfeb2)
#define     PWM1_IOAUX              (*(unsigned char volatile __xdata *)0xfeb3)
#define     PWM2_ETRPS              (*(unsigned char volatile __xdata *)0xfeb4)
#define     PWM2_ENO                (*(unsigned char volatile __xdata *)0xfeb5)
#define     PWM2_PS                 (*(unsigned char volatile __xdata *)0xfeb6)
#define     PWM2_IOAUX              (*(unsigned char volatile __xdata *)0xfeb7)
#define     PWM1_CR1                (*(unsigned char volatile __xdata *)0xfec0)
#define     PWM1_CR2                (*(unsigned char volatile __xdata *)0xfec1)
#define     PWM1_SMCR               (*(unsigned char volatile __xdata *)0xfec2)
#define     PWM1_ETR                (*(unsigned char volatile __xdata *)0xfec3)
#define     PWM1_IER                (*(unsigned char volatile __xdata *)0xfec4)
#define     PWM1_SR1                (*(unsigned char volatile __xdata *)0xfec5)
#define     PWM1_SR2                (*(unsigned char volatile __xdata *)0xfec6)
#define     PWM1_EGR                (*(unsigned char volatile __xdata *)0xfec7)
#define     PWM1_CCMR1              (*(unsigned char volatile __xdata *)0xfec8)
#define     PWM1_CCMR2              (*(unsigned char volatile __xdata *)0xfec9)
#define     PWM1_CCMR3              (*(unsigned char volatile __xdata *)0xfeca)
#define     PWM1_CCMR4              (*(unsigned char volatile __xdata *)0xfecb)
#define     PWM1_CCER1              (*(unsigned char volatile __xdata *)0xfecc)
#define     PWM1_CCER2              (*(unsigned char volatile __xdata *)0xfecd)
#define     PWM1_CNTR               (*(unsigned  int volatile __xdata *)0xfece)
#define     PWM1_CNTRH              (*(unsigned char volatile __xdata *)0xfece)
#define     PWM1_CNTRL              (*(unsigned char volatile __xdata *)0xfecf)
#define     PWM1_PSCR               (*(unsigned  int volatile __xdata *)0xfed0)
#define     PWM1_PSCRH              (*(unsigned char volatile __xdata *)0xfed0)
#define     PWM1_PSCRL              (*(unsigned char volatile __xdata *)0xfed1)
#define     PWM1_ARR                (*(unsigned  int volatile __xdata *)0xfed2)
#define     PWM1_ARRH               (*(unsigned char volatile __xdata *)0xfed2)
#define     PWM1_ARRL               (*(unsigned char volatile __xdata *)0xfed3)
#define     PWM1_RCR                (*(unsigned char volatile __xdata *)0xfed4)
#define     PWM1_CCR1               (*(unsigned  int volatile __xdata *)0xfed5)
#define     PWM1_CCR1H              (*(unsigned char volatile __xdata *)0xfed5)
#define     PWM1_CCR1L              (*(unsigned char volatile __xdata *)0xfed6)
#define     PWM1_CCR2               (*(unsigned  int volatile __xdata *)0xfed7)
#define     PWM1_CCR2H              (*(unsigned char volatile __xdata *)0xfed7)
#define     PWM1_CCR2L              (*(unsigned char volatile __xdata *)0xfed8)
#define     PWM1_CCR3               (*(unsigned  int volatile __xdata *)0xfed9)
#define     PWM1_CCR3H              (*(unsigned char volatile __xdata *)0xfed9)
#define     PWM1_CCR3L              (*(unsigned char volatile __xdata *)0xfeda)
#define     PWM1_CCR4               (*(unsigned  int volatile __xdata *)0xfedb)
#define     PWM1_CCR4H              (*(unsigned char volatile __xdata *)0xfedb)
#define     PWM1_CCR4L              (*(unsigned char volatile __xdata *)0xfedc)
#define     PWM1_BKR                (*(unsigned char volatile __xdata *)0xfedd)
#define     PWM1_DTR                (*(unsigned char volatile __xdata *)0xfede)
#define     PWM1_OISR               (*(unsigned char volatile __xdata *)0xfedf)
#define     PWM2_CR1                (*(unsigned char volatile __xdata *)0xfee0)
#define     PWM2_CR2                (*(unsigned char volatile __xdata *)0xfee1)
#define     PWM2_SMCR               (*(unsigned char volatile __xdata *)0xfee2)
#define     PWM2_ETR                (*(unsigned char volatile __xdata *)0xfee3)
#define     PWM2_IER                (*(unsigned char volatile __xdata *)0xfee4)
#define     PWM2_SR1                (*(unsigned char volatile __xdata *)0xfee5)
#define     PWM2_SR2                (*(unsigned char volatile __xdata *)0xfee6)
#define     PWM2_EGR                (*(unsigned char volatile __xdata *)0xfee7)
#define     PWM2_CCMR1              (*(unsigned char volatile __xdata *)0xfee8)
#define     PWM2_CCMR2              (*(unsigned char volatile __xdata *)0xfee9)
#define     PWM2_CCMR3              (*(unsigned char volatile __xdata *)0xfeea)
#define     PWM2_CCMR4              (*(unsigned char volatile __xdata *)0xfeeb)
#define     PWM2_CCER1              (*(unsigned char volatile __xdata *)0xfeec)
#define     PWM2_CCER2              (*(unsigned char volatile __xdata *)0xfeed)
#define     PWM2_CNTR               (*(unsigned  int volatile __xdata *)0xfeee)
#define     PWM2_CNTRH              (*(unsigned char volatile __xdata *)0xfeee)
#define     PWM2_CNTRL              (*(unsigned char volatile __xdata *)0xfeef)
#define     PWM2_PSCR               (*(unsigned  int volatile __xdata *)0xfef0)
#define     PWM2_PSCRH              (*(unsigned char volatile __xdata *)0xfef0)
#define     PWM2_PSCRL              (*(unsigned char volatile __xdata *)0xfef1)
#define     PWM2_ARR                (*(unsigned  int volatile __xdata *)0xfef2)
#define     PWM2_ARRH               (*(unsigned char volatile __xdata *)0xfef2)
#define     PWM2_ARRL               (*(unsigned char volatile __xdata *)0xfef3)
#define     PWM2_RCR                (*(unsigned char volatile __xdata *)0xfef4)
#define     PWM2_CCR1               (*(unsigned  int volatile __xdata *)0xfef5)
#define     PWM2_CCR1H              (*(unsigned char volatile __xdata *)0xfef5)
#define     PWM2_CCR1L              (*(unsigned char volatile __xdata *)0xfef6)
#define     PWM2_CCR2               (*(unsigned  int volatile __xdata *)0xfef7)
#define     PWM2_CCR2H              (*(unsigned char volatile __xdata *)0xfef7)
#define     PWM2_CCR2L              (*(unsigned char volatile __xdata *)0xfef8)
#define     PWM2_CCR3               (*(unsigned  int volatile __xdata *)0xfef9)
#define     PWM2_CCR3H              (*(unsigned char volatile __xdata *)0xfef9)
#define     PWM2_CCR3L              (*(unsigned char volatile __xdata *)0xfefa)
#define     PWM2_CCR4               (*(unsigned  int volatile __xdata *)0xfefb)
#define     PWM2_CCR4H              (*(unsigned char volatile __xdata *)0xfefb)
#define     PWM2_CCR4L              (*(unsigned char volatile __xdata *)0xfefc)
#define     PWM2_BKR                (*(unsigned char volatile __xdata *)0xfefd)
#define     PWM2_DTR                (*(unsigned char volatile __xdata *)0xfefe)
#define     PWM2_OISR               (*(unsigned char volatile __xdata *)0xfeff)

#define     PWMA_ETRPS              (*(unsigned char volatile __xdata *)0xfeb0)
#define     PWMA_ENO                (*(unsigned char volatile __xdata *)0xfeb1)
#define     PWMA_PS                 (*(unsigned char volatile __xdata *)0xfeb2)
#define     PWMA_IOAUX              (*(unsigned char volatile __xdata *)0xfeb3)
#define     PWMB_ETRPS              (*(unsigned char volatile __xdata *)0xfeb4)
#define     PWMB_ENO                (*(unsigned char volatile __xdata *)0xfeb5)
#define     PWMB_PS                 (*(unsigned char volatile __xdata *)0xfeb6)
#define     PWMB_IOAUX              (*(unsigned char volatile __xdata *)0xfeb7)
#define     PWMA_CR1                (*(unsigned char volatile __xdata *)0xfec0)
#define     PWMA_CR2                (*(unsigned char volatile __xdata *)0xfec1)
#define     PWMA_SMCR               (*(unsigned char volatile __xdata *)0xfec2)
#define     PWMA_ETR                (*(unsigned char volatile __xdata *)0xfec3)
#define     PWMA_IER                (*(unsigned char volatile __xdata *)0xfec4)
#define     PWMA_SR1                (*(unsigned char volatile __xdata *)0xfec5)
#define     PWMA_SR2                (*(unsigned char volatile __xdata *)0xfec6)
#define     PWMA_EGR                (*(unsigned char volatile __xdata *)0xfec7)
#define     PWMA_CCMR1              (*(unsigned char volatile __xdata *)0xfec8)
#define     PWMA_CCMR2              (*(unsigned char volatile __xdata *)0xfec9)
#define     PWMA_CCMR3              (*(unsigned char volatile __xdata *)0xfeca)
#define     PWMA_CCMR4              (*(unsigned char volatile __xdata *)0xfecb)
#define     PWMA_CCER1              (*(unsigned char volatile __xdata *)0xfecc)
#define     PWMA_CCER2              (*(unsigned char volatile __xdata *)0xfecd)
#define     PWMA_CNTR               (*(unsigned  int volatile __xdata *)0xfece)
#define     PWMA_CNTRH              (*(unsigned char volatile __xdata *)0xfece)
#define     PWMA_CNTRL              (*(unsigned char volatile __xdata *)0xfecf)
#define     PWMA_PSCR               (*(unsigned  int volatile __xdata *)0xfed0)
#define     PWMA_PSCRH              (*(unsigned char volatile __xdata *)0xfed0)
#define     PWMA_PSCRL              (*(unsigned char volatile __xdata *)0xfed1)
#define     PWMA_ARR                (*(unsigned  int volatile __xdata *)0xfed2)
#define     PWMA_ARRH               (*(unsigned char volatile __xdata *)0xfed2)
#define     PWMA_ARRL               (*(unsigned char volatile __xdata *)0xfed3)
#define     PWMA_RCR                (*(unsigned char volatile __xdata *)0xfed4)
#define     PWMA_CCR1               (*(unsigned  int volatile __xdata *)0xfed5)
#define     PWMA_CCR1H              (*(unsigned char volatile __xdata *)0xfed5)
#define     PWMA_CCR1L              (*(unsigned char volatile __xdata *)0xfed6)
#define     PWMA_CCR2               (*(unsigned  int volatile __xdata *)0xfed7)
#define     PWMA_CCR2H              (*(unsigned char volatile __xdata *)0xfed7)
#define     PWMA_CCR2L              (*(unsigned char volatile __xdata *)0xfed8)
#define     PWMA_CCR3               (*(unsigned  int volatile __xdata *)0xfed9)
#define     PWMA_CCR3H              (*(unsigned char volatile __xdata *)0xfed9)
#define     PWMA_CCR3L              (*(unsigned char volatile __xdata *)0xfeda)
#define     PWMA_CCR4               (*(unsigned  int volatile __xdata *)0xfedb)
#define     PWMA_CCR4H              (*(unsigned char volatile __xdata *)0xfedb)
#define     PWMA_CCR4L              (*(unsigned char volatile __xdata *)0xfedc)
#define     PWMA_BKR                (*(unsigned char volatile __xdata *)0xfedd)
#define     PWMA_DTR                (*(unsigned char volatile __xdata *)0xfede)
#define     PWMA_OISR               (*(unsigned char volatile __xdata *)0xfedf)
#define     PWMB_CR1                (*(unsigned char volatile __xdata *)0xfee0)
#define     PWMB_CR2                (*(unsigned char volatile __xdata *)0xfee1)
#define     PWMB_SMCR               (*(unsigned char volatile __xdata *)0xfee2)
#define     PWMB_ETR                (*(unsigned char volatile __xdata *)0xfee3)
#define     PWMB_IER                (*(unsigned char volatile __xdata *)0xfee4)
#define     PWMB_SR1                (*(unsigned char volatile __xdata *)0xfee5)
#define     PWMB_SR2                (*(unsigned char volatile __xdata *)0xfee6)
#define     PWMB_EGR                (*(unsigned char volatile __xdata *)0xfee7)
#define     PWMB_CCMR1              (*(unsigned char volatile __xdata *)0xfee8)
#define     PWMB_CCMR2              (*(unsigned char volatile __xdata *)0xfee9)
#define     PWMB_CCMR3              (*(unsigned char volatile __xdata *)0xfeea)
#define     PWMB_CCMR4              (*(unsigned char volatile __xdata *)0xfeeb)
#define     PWMB_CCER1              (*(unsigned char volatile __xdata *)0xfeec)
#define     PWMB_CCER2              (*(unsigned char volatile __xdata *)0xfeed)
#define     PWMB_CNTR               (*(unsigned  int volatile __xdata *)0xfeee)
#define     PWMB_CNTRH              (*(unsigned char volatile __xdata *)0xfeee)
#define     PWMB_CNTRL              (*(unsigned char volatile __xdata *)0xfeef)
#define     PWMB_PSCR               (*(unsigned  int volatile __xdata *)0xfef0)
#define     PWMB_PSCRH              (*(unsigned char volatile __xdata *)0xfef0)
#define     PWMB_PSCRL              (*(unsigned char volatile __xdata *)0xfef1)
#define     PWMB_ARR                (*(unsigned  int volatile __xdata *)0xfef2)
#define     PWMB_ARRH               (*(unsigned char volatile __xdata *)0xfef2)
#define     PWMB_ARRL               (*(unsigned char volatile __xdata *)0xfef3)
#define     PWMB_RCR                (*(unsigned char volatile __xdata *)0xfef4)
#define     PWMB_CCR5               (*(unsigned  int volatile __xdata *)0xfef5)
#define     PWMB_CCR5H              (*(unsigned char volatile __xdata *)0xfef5)
#define     PWMB_CCR5L              (*(unsigned char volatile __xdata *)0xfef6)
#define     PWMB_CCR6               (*(unsigned  int volatile __xdata *)0xfef7)
#define     PWMB_CCR6H              (*(unsigned char volatile __xdata *)0xfef7)
#define     PWMB_CCR6L              (*(unsigned char volatile __xdata *)0xfef8)
#define     PWMB_CCR7               (*(unsigned  int volatile __xdata *)0xfef9)
#define     PWMB_CCR7H              (*(unsigned char volatile __xdata *)0xfef9)
#define     PWMB_CCR7L              (*(unsigned char volatile __xdata *)0xfefa)
#define     PWMB_CCR8               (*(unsigned  int volatile __xdata *)0xfefb)
#define     PWMB_CCR8H              (*(unsigned char volatile __xdata *)0xfefb)
#define     PWMB_CCR8L              (*(unsigned char volatile __xdata *)0xfefc)
#define     PWMB_BKR                (*(unsigned char volatile __xdata *)0xfefd)
#define     PWMB_DTR                (*(unsigned char volatile __xdata *)0xfefe)
#define     PWMB_OISR               (*(unsigned char volatile __xdata *)0xfeff)

/////////////////////////////////////////////////
//FD00H-FDFFH
/////////////////////////////////////////////////

#define     P0INTE                  (*(unsigned char volatile __xdata *)0xfd00)
#define     P1INTE                  (*(unsigned char volatile __xdata *)0xfd01)
#define     P2INTE                  (*(unsigned char volatile __xdata *)0xfd02)
#define     P3INTE                  (*(unsigned char volatile __xdata *)0xfd03)
#define     P4INTE                  (*(unsigned char volatile __xdata *)0xfd04)
#define     P5INTE                  (*(unsigned char volatile __xdata *)0xfd05)
#define     P6INTE                  (*(unsigned char volatile __xdata *)0xfd06)
#define     P7INTE                  (*(unsigned char volatile __xdata *)0xfd07)
#define     P0INTF                  (*(unsigned char volatile __xdata *)0xfd10)
#define     P1INTF                  (*(unsigned char volatile __xdata *)0xfd11)
#define     P2INTF                  (*(unsigned char volatile __xdata *)0xfd12)
#define     P3INTF                  (*(unsigned char volatile __xdata *)0xfd13)
#define     P4INTF                  (*(unsigned char volatile __xdata *)0xfd14)
#define     P5INTF                  (*(unsigned char volatile __xdata *)0xfd15)
#define     P6INTF                  (*(unsigned char volatile __xdata *)0xfd16)
#define     P7INTF                  (*(unsigned char volatile __xdata *)0xfd17)
#define     P0IM0                   (*(unsigned char volatile __xdata *)0xfd20)
#define     P1IM0                   (*(unsigned char volatile __xdata *)0xfd21)
#define     P2IM0                   (*(unsigned char volatile __xdata *)0xfd22)
#define     P3IM0                   (*(unsigned char volatile __xdata *)0xfd23)
#define     P4IM0                   (*(unsigned char volatile __xdata *)0xfd24)
#define     P5IM0                   (*(unsigned char volatile __xdata *)0xfd25)
#define     P6IM0                   (*(unsigned char volatile __xdata *)0xfd26)
#define     P7IM0                   (*(unsigned char volatile __xdata *)0xfd27)
#define     P0IM1                   (*(unsigned char volatile __xdata *)0xfd30)
#define     P1IM1                   (*(unsigned char volatile __xdata *)0xfd31)
#define     P2IM1                   (*(unsigned char volatile __xdata *)0xfd32)
#define     P3IM1                   (*(unsigned char volatile __xdata *)0xfd33)
#define     P4IM1                   (*(unsigned char volatile __xdata *)0xfd34)
#define     P5IM1                   (*(unsigned char volatile __xdata *)0xfd35)
#define     P6IM1                   (*(unsigned char volatile __xdata *)0xfd36)
#define     P7IM1                   (*(unsigned char volatile __xdata *)0xfd37)
#define     P0WKUE                  (*(unsigned char volatile __xdata *)0xfd40)
#define     P1WKUE                  (*(unsigned char volatile __xdata *)0xfd41)
#define     P2WKUE                  (*(unsigned char volatile __xdata *)0xfd42)
#define     P3WKUE                  (*(unsigned char volatile __xdata *)0xfd43)
#define     P4WKUE                  (*(unsigned char volatile __xdata *)0xfd44)
#define     P5WKUE                  (*(unsigned char volatile __xdata *)0xfd45)
#define     P6WKUE                  (*(unsigned char volatile __xdata *)0xfd46)
#define     P7WKUE                  (*(unsigned char volatile __xdata *)0xfd47)

#define     PINIPL                  (*(unsigned char volatile __xdata *)0xfd60)
#define     PINIPH                  (*(unsigned char volatile __xdata *)0xfd61)
#define     P_SWX1                  (*(unsigned char volatile __xdata *)0xfd69)

#define     CRECR                   (*(unsigned char volatile __xdata *)0xfda8)
#define     CRECNTH                 (*(unsigned char volatile __xdata *)0xfda9)
#define     CRECNTL                 (*(unsigned char volatile __xdata *)0xfdaa)
#define     CRERES                  (*(unsigned char volatile __xdata *)0xfdab)

#define     CHIPID                  ( (unsigned char volatile __xdata *)0xfde0)

#define     CHIPID0                 (*(unsigned char volatile __xdata *)0xfde0)
#define     CHIPID1                 (*(unsigned char volatile __xdata *)0xfde1)
#define     CHIPID2                 (*(unsigned char volatile __xdata *)0xfde2)
#define     CHIPID3                 (*(unsigned char volatile __xdata *)0xfde3)
#define     CHIPID4                 (*(unsigned char volatile __xdata *)0xfde4)
#define     CHIPID5                 (*(unsigned char volatile __xdata *)0xfde5)
#define     CHIPID6                 (*(unsigned char volatile __xdata *)0xfde6)
#define     CHIPID7                 (*(unsigned char volatile __xdata *)0xfde7)
#define     CHIPID8                 (*(unsigned char volatile __xdata *)0xfde8)
#define     CHIPID9                 (*(unsigned char volatile __xdata *)0xfde9)
#define     CHIPID10                (*(unsigned char volatile __xdata *)0xfdea)
#define     CHIPID11                (*(unsigned char volatile __xdata *)0xfdeb)
#define     CHIPID12                (*(unsigned char volatile __xdata *)0xfdec)
#define     CHIPID13                (*(unsigned char volatile __xdata *)0xfded)
#define     CHIPID14                (*(unsigned char volatile __xdata *)0xfdee)
#define     CHIPID15                (*(unsigned char volatile __xdata *)0xfdef)
#define     CHIPID16                (*(unsigned char volatile __xdata *)0xfdf0)
#define     CHIPID17                (*(unsigned char volatile __xdata *)0xfdf1)
#define     CHIPID18                (*(unsigned char volatile __xdata *)0xfdf2)
#define     CHIPID19                (*(unsigned char volatile __xdata *)0xfdf3)
#define     CHIPID20                (*(unsigned char volatile __xdata *)0xfdf4)
#define     CHIPID21                (*(unsigned char volatile __xdata *)0xfdf5)
#define     CHIPID22                (*(unsigned char volatile __xdata *)0xfdf6)
#define     CHIPID23                (*(unsigned char volatile __xdata *)0xfdf7)
#define     CHIPID24                (*(unsigned char volatile __xdata *)0xfdf8)
#define     CHIPID25                (*(unsigned char volatile __xdata *)0xfdf9)
#define     CHIPID26                (*(unsigned char volatile __xdata *)0xfdfa)
#define     CHIPID27                (*(unsigned char volatile __xdata *)0xfdfb)
#define     CHIPID28                (*(unsigned char volatile __xdata *)0xfdfc)
#define     CHIPID29                (*(unsigned char volatile __xdata *)0xfdfd)
#define     CHIPID30                (*(unsigned char volatile __xdata *)0xfdfe)
#define     CHIPID31                (*(unsigned char volatile __xdata *)0xfdff)

/////////////////////////////////////////////////
//FC00H-FCFFH
/////////////////////////////////////////////////

#define     MD3                     (*(unsigned char volatile __xdata *)0xfcf0)
#define     MD2                     (*(unsigned char volatile __xdata *)0xfcf1)
#define     MD1                     (*(unsigned char volatile __xdata *)0xfcf2)
#define     MD0                     (*(unsigned char volatile __xdata *)0xfcf3)
#define     MD5                     (*(unsigned char volatile __xdata *)0xfcf4)
#define     MD4                     (*(unsigned char volatile __xdata *)0xfcf5)
#define     ARCON                   (*(unsigned char volatile __xdata *)0xfcf6)
#define     OPCON                   (*(unsigned char volatile __xdata *)0xfcf7)

/////////////////////////////////////////////////
//FB00H-FBFFH
/////////////////////////////////////////////////

#define     COMEN                   (*(unsigned char volatile __xdata *)0xfb00)
#define     SEGENL                  (*(unsigned char volatile __xdata *)0xfb01)
#define     SEGENH                  (*(unsigned char volatile __xdata *)0xfb02)
#define     LEDCTRL                 (*(unsigned char volatile __xdata *)0xfb03)
#define     LEDCKS                  (*(unsigned char volatile __xdata *)0xfb04)
#define     COM0_DA_L               (*(unsigned char volatile __xdata *)0xfb10)
#define     COM1_DA_L               (*(unsigned char volatile __xdata *)0xfb11)
#define     COM2_DA_L               (*(unsigned char volatile __xdata *)0xfb12)
#define     COM3_DA_L               (*(unsigned char volatile __xdata *)0xfb13)
#define     COM4_DA_L               (*(unsigned char volatile __xdata *)0xfb14)
#define     COM5_DA_L               (*(unsigned char volatile __xdata *)0xfb15)
#define     COM6_DA_L               (*(unsigned char volatile __xdata *)0xfb16)
#define     COM7_DA_L               (*(unsigned char volatile __xdata *)0xfb17)
#define     COM0_DA_H               (*(unsigned char volatile __xdata *)0xfb18)
#define     COM1_DA_H               (*(unsigned char volatile __xdata *)0xfb19)
#define     COM2_DA_H               (*(unsigned char volatile __xdata *)0xfb1a)
#define     COM3_DA_H               (*(unsigned char volatile __xdata *)0xfb1b)
#define     COM4_DA_H               (*(unsigned char volatile __xdata *)0xfb1c)
#define     COM5_DA_H               (*(unsigned char volatile __xdata *)0xfb1d)
#define     COM6_DA_H               (*(unsigned char volatile __xdata *)0xfb1e)
#define     COM7_DA_H               (*(unsigned char volatile __xdata *)0xfb1f)
#define     COM0_DC_L               (*(unsigned char volatile __xdata *)0xfb20)
#define     COM1_DC_L               (*(unsigned char volatile __xdata *)0xfb21)
#define     COM2_DC_L               (*(unsigned char volatile __xdata *)0xfb22)
#define     COM3_DC_L               (*(unsigned char volatile __xdata *)0xfb23)
#define     COM4_DC_L               (*(unsigned char volatile __xdata *)0xfb24)
#define     COM5_DC_L               (*(unsigned char volatile __xdata *)0xfb25)
#define     COM6_DC_L               (*(unsigned char volatile __xdata *)0xfb26)
#define     COM7_DC_L               (*(unsigned char volatile __xdata *)0xfb27)
#define     COM0_DC_H               (*(unsigned char volatile __xdata *)0xfb28)
#define     COM1_DC_H               (*(unsigned char volatile __xdata *)0xfb29)
#define     COM2_DC_H               (*(unsigned char volatile __xdata *)0xfb2a)
#define     COM3_DC_H               (*(unsigned char volatile __xdata *)0xfb2b)
#define     COM4_DC_H               (*(unsigned char volatile __xdata *)0xfb2c)
#define     COM5_DC_H               (*(unsigned char volatile __xdata *)0xfb2d)
#define     COM6_DC_H               (*(unsigned char volatile __xdata *)0xfb2e)
#define     COM7_DC_H               (*(unsigned char volatile __xdata *)0xfb2f)

#define     CRC16_CR                (*(unsigned char volatile __xdata *)0xfb30)
#define     CRC16_DIN               (*(unsigned char volatile __xdata *)0xfb31)
#define     CRC16_DOH               (*(unsigned char volatile __xdata *)0xfb32)
#define     CRC16_DOL               (*(unsigned char volatile __xdata *)0xfb33)

#define     TSCHEN1                 (*(unsigned char volatile __xdata *)0xfb40)
#define     TSCHEN2                 (*(unsigned char volatile __xdata *)0xfb41)
#define     TSCFG1                  (*(unsigned char volatile __xdata *)0xfb42)
#define     TSCFG2                  (*(unsigned char volatile __xdata *)0xfb43)
#define     TSWUTC                  (*(unsigned char volatile __xdata *)0xfb44)
#define     TSCTRL                  (*(unsigned char volatile __xdata *)0xfb45)
#define     TSSTA1                  (*(unsigned char volatile __xdata *)0xfb46)
#define     TSSTA2                  (*(unsigned char volatile __xdata *)0xfb47)
#define     TSRT                    (*(unsigned char volatile __xdata *)0xfb48)
#define     TSDAT                   (*(unsigned int  volatile __xdata *)0xfb49)
#define     TSDATH                  (*(unsigned char volatile __xdata *)0xfb49)
#define     TSDATL                  (*(unsigned char volatile __xdata *)0xfb4A)
#define     TSTH00                  (*(unsigned int  volatile __xdata *)0xfb50)
#define     TSTH00H                 (*(unsigned char volatile __xdata *)0xfb50)
#define     TSTH00L                 (*(unsigned char volatile __xdata *)0xfb51)
#define     TSTH01                  (*(unsigned int  volatile __xdata *)0xfb52)
#define     TSTH01H                 (*(unsigned char volatile __xdata *)0xfb52)
#define     TSTH01L                 (*(unsigned char volatile __xdata *)0xfb53)
#define     TSTH02                  (*(unsigned int  volatile __xdata *)0xfb54)
#define     TSTH02H                 (*(unsigned char volatile __xdata *)0xfb54)
#define     TSTH02L                 (*(unsigned char volatile __xdata *)0xfb55)
#define     TSTH03                  (*(unsigned int  volatile __xdata *)0xfb56)
#define     TSTH03H                 (*(unsigned char volatile __xdata *)0xfb56)
#define     TSTH03L                 (*(unsigned char volatile __xdata *)0xfb57)
#define     TSTH04                  (*(unsigned int  volatile __xdata *)0xfb58)
#define     TSTH04H                 (*(unsigned char volatile __xdata *)0xfb58)
#define     TSTH04L                 (*(unsigned char volatile __xdata *)0xfb59)
#define     TSTH05                  (*(unsigned int  volatile __xdata *)0xfb5a)
#define     TSTH05H                 (*(unsigned char volatile __xdata *)0xfb5a)
#define     TSTH05L                 (*(unsigned char volatile __xdata *)0xfb5b)
#define     TSTH06                  (*(unsigned int  volatile __xdata *)0xfb5c)
#define     TSTH06H                 (*(unsigned char volatile __xdata *)0xfb5c)
#define     TSTH06L                 (*(unsigned char volatile __xdata *)0xfb5d)
#define     TSTH07                  (*(unsigned int  volatile __xdata *)0xfb5e)
#define     TSTH07H                 (*(unsigned char volatile __xdata *)0xfb5e)
#define     TSTH07L                 (*(unsigned char volatile __xdata *)0xfb5f)
#define     TSTH08                  (*(unsigned int  volatile __xdata *)0xfb60)
#define     TSTH08H                 (*(unsigned char volatile __xdata *)0xfb60)
#define     TSTH08L                 (*(unsigned char volatile __xdata *)0xfb61)
#define     TSTH09                  (*(unsigned int  volatile __xdata *)0xfb62)
#define     TSTH09H                 (*(unsigned char volatile __xdata *)0xfb62)
#define     TSTH09L                 (*(unsigned char volatile __xdata *)0xfb63)
#define     TSTH10                  (*(unsigned int  volatile __xdata *)0xfb64)
#define     TSTH10H                 (*(unsigned char volatile __xdata *)0xfb64)
#define     TSTH10L                 (*(unsigned char volatile __xdata *)0xfb65)
#define     TSTH11                  (*(unsigned int  volatile __xdata *)0xfb66)
#define     TSTH11H                 (*(unsigned char volatile __xdata *)0xfb66)
#define     TSTH11L                 (*(unsigned char volatile __xdata *)0xfb67)
#define     TSTH12                  (*(unsigned int  volatile __xdata *)0xfb68)
#define     TSTH12H                 (*(unsigned char volatile __xdata *)0xfb68)
#define     TSTH12L                 (*(unsigned char volatile __xdata *)0xfb69)
#define     TSTH13                  (*(unsigned int  volatile __xdata *)0xfb6a)
#define     TSTH13H                 (*(unsigned char volatile __xdata *)0xfb6a)
#define     TSTH13L                 (*(unsigned char volatile __xdata *)0xfb6b)
#define     TSTH14                  (*(unsigned int  volatile __xdata *)0xfb6c)
#define     TSTH14H                 (*(unsigned char volatile __xdata *)0xfb6c)
#define     TSTH14L                 (*(unsigned char volatile __xdata *)0xfb6d)
#define     TSTH15                  (*(unsigned int  volatile __xdata *)0xfb6e)
#define     TSTH15H                 (*(unsigned char volatile __xdata *)0xfb6e)
#define     TSTH15L                 (*(unsigned char volatile __xdata *)0xfb6f)

#define     LCDCFG                  (*(unsigned char volatile __xdata *)0xfb80)
#define     LCDCFG2                 (*(unsigned char volatile __xdata *)0xfb81)
#define     DBLEN                   (*(unsigned char volatile __xdata *)0xfb82)
#define     COMLENL                 (*(unsigned char volatile __xdata *)0xfb83)
#define     COMLENM                 (*(unsigned char volatile __xdata *)0xfb84)
#define     COMLENH                 (*(unsigned char volatile __xdata *)0xfb85)
#define     BLINKRATE               (*(unsigned char volatile __xdata *)0xfb86)
#define     LCDCR                   (*(unsigned char volatile __xdata *)0xfb87)
#define     COMON                   (*(unsigned char volatile __xdata *)0xfb88)
#define     SEGON1                  (*(unsigned char volatile __xdata *)0xfb8a)
#define     SEGON2                  (*(unsigned char volatile __xdata *)0xfb8b)
#define     SEGON3                  (*(unsigned char volatile __xdata *)0xfb8c)
#define     SEGON4                  (*(unsigned char volatile __xdata *)0xfb8d)
#define     SEGON5                  (*(unsigned char volatile __xdata *)0xfb8e)
#define     C0SEGV0                 (*(unsigned char volatile __xdata *)0xfb90)
#define     C0SEGV1                 (*(unsigned char volatile __xdata *)0xfb91)
#define     C0SEGV2                 (*(unsigned char volatile __xdata *)0xfb92)
#define     C0SEGV3                 (*(unsigned char volatile __xdata *)0xfb93)
#define     C0SEGV4                 (*(unsigned char volatile __xdata *)0xfb94)
#define     C1SEGV0                 (*(unsigned char volatile __xdata *)0xfb98)
#define     C1SEGV1                 (*(unsigned char volatile __xdata *)0xfb99)
#define     C1SEGV2                 (*(unsigned char volatile __xdata *)0xfb9a)
#define     C1SEGV3                 (*(unsigned char volatile __xdata *)0xfb9b)
#define     C1SEGV4                 (*(unsigned char volatile __xdata *)0xfb9c)
#define     C2SEGV0                 (*(unsigned char volatile __xdata *)0xfba0)
#define     C2SEGV1                 (*(unsigned char volatile __xdata *)0xfba1)
#define     C2SEGV2                 (*(unsigned char volatile __xdata *)0xfba2)
#define     C2SEGV3                 (*(unsigned char volatile __xdata *)0xfba3)
#define     C2SEGV4                 (*(unsigned char volatile __xdata *)0xfba4)
#define     C3SEGV0                 (*(unsigned char volatile __xdata *)0xfba8)
#define     C3SEGV1                 (*(unsigned char volatile __xdata *)0xfba9)
#define     C3SEGV2                 (*(unsigned char volatile __xdata *)0xfbaa)
#define     C3SEGV3                 (*(unsigned char volatile __xdata *)0xfbab)
#define     C3SEGV4                 (*(unsigned char volatile __xdata *)0xfbac)

#define     HSPWMA_CFG              (*(unsigned char volatile __xdata *)0xfbf0)
#define     HSPWMA_ADR              (*(unsigned char volatile __xdata *)0xfbf1)
#define     HSPWMA_DAT              (*(unsigned char volatile __xdata *)0xfbf2)

#define     HSPWMB_CFG              (*(unsigned char volatile __xdata *)0xfbf4)
#define     HSPWMB_ADR              (*(unsigned char volatile __xdata *)0xfbf5)
#define     HSPWMB_DAT              (*(unsigned char volatile __xdata *)0xfbf6)

/////////////////////////////////////////////////
//FA00H-FAFFH
/////////////////////////////////////////////////

#define     DMA_M2M_CFG             (*(unsigned char volatile __xdata *)0xfa00)
#define     DMA_M2M_CR              (*(unsigned char volatile __xdata *)0xfa01)
#define     DMA_M2M_STA             (*(unsigned char volatile __xdata *)0xfa02)
#define     DMA_M2M_AMT             (*(unsigned char volatile __xdata *)0xfa03)
#define     DMA_M2M_DONE            (*(unsigned char volatile __xdata *)0xfa04)
#define     DMA_M2M_TXAH            (*(unsigned char volatile __xdata *)0xfa05)
#define     DMA_M2M_TXAL            (*(unsigned char volatile __xdata *)0xfa06)
#define     DMA_M2M_RXAH            (*(unsigned char volatile __xdata *)0xfa07)
#define     DMA_M2M_RXAL            (*(unsigned char volatile __xdata *)0xfa08)

#define     DMA_ADC_CFG             (*(unsigned char volatile __xdata *)0xfa10)
#define     DMA_ADC_CR              (*(unsigned char volatile __xdata *)0xfa11)
#define     DMA_ADC_STA             (*(unsigned char volatile __xdata *)0xfa12)
#define     DMA_ADC_RXA             (*(unsigned  int volatile __xdata *)0xfa17)
#define     DMA_ADC_RXAH            (*(unsigned char volatile __xdata *)0xfa17)
#define     DMA_ADC_RXAL            (*(unsigned char volatile __xdata *)0xfa18)
#define     DMA_ADC_CFG2            (*(unsigned char volatile __xdata *)0xfa19)
#define     DMA_ADC_CHSW0           (*(unsigned char volatile __xdata *)0xfa1a)
#define     DMA_ADC_CHSW1           (*(unsigned char volatile __xdata *)0xfa1b)

#define     DMA_SPI_CFG             (*(unsigned char volatile __xdata *)0xfa20)
#define     DMA_SPI_CR              (*(unsigned char volatile __xdata *)0xfa21)
#define     DMA_SPI_STA             (*(unsigned char volatile __xdata *)0xfa22)
#define     DMA_SPI_AMT             (*(unsigned char volatile __xdata *)0xfa23)
#define     DMA_SPI_DONE            (*(unsigned char volatile __xdata *)0xfa24)
#define     DMA_SPI_TXA             (*(unsigned  int volatile __xdata *)0xfa25)
#define     DMA_SPI_TXAH            (*(unsigned char volatile __xdata *)0xfa25)
#define     DMA_SPI_TXAL            (*(unsigned char volatile __xdata *)0xfa26)
#define     DMA_SPI_RXA             (*(unsigned  int volatile __xdata *)0xfa27)
#define     DMA_SPI_RXAH            (*(unsigned char volatile __xdata *)0xfa27)
#define     DMA_SPI_RXAL            (*(unsigned char volatile __xdata *)0xfa28)
#define     DMA_SPI_CFG2            (*(unsigned char volatile __xdata *)0xfa29)

#define     DMA_UR1T_CFG            (*(unsigned char volatile __xdata *)0xfa30)
#define     DMA_UR1T_CR             (*(unsigned char volatile __xdata *)0xfa31)
#define     DMA_UR1T_STA            (*(unsigned char volatile __xdata *)0xfa32)
#define     DMA_UR1T_AMT            (*(unsigned char volatile __xdata *)0xfa33)
#define     DMA_UR1T_DONE           (*(unsigned char volatile __xdata *)0xfa34)
#define     DMA_UR1T_TXA            (*(unsigned  int volatile __xdata *)0xfa35)
#define     DMA_UR1T_TXAH           (*(unsigned char volatile __xdata *)0xfa35)
#define     DMA_UR1T_TXAL           (*(unsigned char volatile __xdata *)0xfa36)
#define     DMA_UR1R_CFG            (*(unsigned char volatile __xdata *)0xfa38)
#define     DMA_UR1R_CR             (*(unsigned char volatile __xdata *)0xfa39)
#define     DMA_UR1R_STA            (*(unsigned char volatile __xdata *)0xfa3a)
#define     DMA_UR1R_AMT            (*(unsigned char volatile __xdata *)0xfa3b)
#define     DMA_UR1R_DONE           (*(unsigned char volatile __xdata *)0xfa3c)
#define     DMA_UR1R_RXA            (*(unsigned  int volatile __xdata *)0xfa3d)
#define     DMA_UR1R_RXAH           (*(unsigned char volatile __xdata *)0xfa3d)
#define     DMA_UR1R_RXAL           (*(unsigned char volatile __xdata *)0xfa3e)

#define     DMA_UR2T_CFG            (*(unsigned char volatile __xdata *)0xfa40)
#define     DMA_UR2T_CR             (*(unsigned char volatile __xdata *)0xfa41)
#define     DMA_UR2T_STA            (*(unsigned char volatile __xdata *)0xfa42)
#define     DMA_UR2T_AMT            (*(unsigned char volatile __xdata *)0xfa43)
#define     DMA_UR2T_DONE           (*(unsigned char volatile __xdata *)0xfa44)
#define     DMA_UR2T_TXA            (*(unsigned  int volatile __xdata *)0xfa45)
#define     DMA_UR2T_TXAH           (*(unsigned char volatile __xdata *)0xfa45)
#define     DMA_UR2T_TXAL           (*(unsigned char volatile __xdata *)0xfa46)
#define     DMA_UR2R_CFG            (*(unsigned char volatile __xdata *)0xfa48)
#define     DMA_UR2R_CR             (*(unsigned char volatile __xdata *)0xfa49)
#define     DMA_UR2R_STA            (*(unsigned char volatile __xdata *)0xfa4a)
#define     DMA_UR2R_AMT            (*(unsigned char volatile __xdata *)0xfa4b)
#define     DMA_UR2R_DONE           (*(unsigned char volatile __xdata *)0xfa4c)
#define     DMA_UR2R_RXA            (*(unsigned  int volatile __xdata *)0xfa4d)
#define     DMA_UR2R_RXAH           (*(unsigned char volatile __xdata *)0xfa4d)
#define     DMA_UR2R_RXAL           (*(unsigned char volatile __xdata *)0xfa4e)

#define     DMA_UR3T_CFG            (*(unsigned char volatile __xdata *)0xfa50)
#define     DMA_UR3T_CR             (*(unsigned char volatile __xdata *)0xfa51)
#define     DMA_UR3T_STA            (*(unsigned char volatile __xdata *)0xfa52)
#define     DMA_UR3T_AMT            (*(unsigned char volatile __xdata *)0xfa53)
#define     DMA_UR3T_DONE           (*(unsigned char volatile __xdata *)0xfa54)
#define     DMA_UR3T_TXA            (*(unsigned  int volatile __xdata *)0xfa55)
#define     DMA_UR3T_TXAH           (*(unsigned char volatile __xdata *)0xfa55)
#define     DMA_UR3T_TXAL           (*(unsigned char volatile __xdata *)0xfa56)
#define     DMA_UR3R_CFG            (*(unsigned char volatile __xdata *)0xfa58)
#define     DMA_UR3R_CR             (*(unsigned char volatile __xdata *)0xfa59)
#define     DMA_UR3R_STA            (*(unsigned char volatile __xdata *)0xfa5a)
#define     DMA_UR3R_AMT            (*(unsigned char volatile __xdata *)0xfa5b)
#define     DMA_UR3R_DONE           (*(unsigned char volatile __xdata *)0xfa5c)
#define     DMA_UR3R_RXA            (*(unsigned  int volatile __xdata *)0xfa5d)
#define     DMA_UR3R_RXAH           (*(unsigned char volatile __xdata *)0xfa5d)
#define     DMA_UR3R_RXAL           (*(unsigned char volatile __xdata *)0xfa5e)

#define     DMA_UR4T_CFG            (*(unsigned char volatile __xdata *)0xfa60)
#define     DMA_UR4T_CR             (*(unsigned char volatile __xdata *)0xfa61)
#define     DMA_UR4T_STA            (*(unsigned char volatile __xdata *)0xfa62)
#define     DMA_UR4T_AMT            (*(unsigned char volatile __xdata *)0xfa63)
#define     DMA_UR4T_DONE           (*(unsigned char volatile __xdata *)0xfa64)
#define     DMA_UR4T_TXA            (*(unsigned  int volatile __xdata *)0xfa65)
#define     DMA_UR4T_TXAH           (*(unsigned char volatile __xdata *)0xfa65)
#define     DMA_UR4T_TXAL           (*(unsigned char volatile __xdata *)0xfa66)
#define     DMA_UR4R_CFG            (*(unsigned char volatile __xdata *)0xfa68)
#define     DMA_UR4R_CR             (*(unsigned char volatile __xdata *)0xfa69)
#define     DMA_UR4R_STA            (*(unsigned char volatile __xdata *)0xfa6a)
#define     DMA_UR4R_AMT            (*(unsigned char volatile __xdata *)0xfa6b)
#define     DMA_UR4R_DONE           (*(unsigned char volatile __xdata *)0xfa6c)
#define     DMA_UR4R_RXA            (*(unsigned  int volatile __xdata *)0xfa6d)
#define     DMA_UR4R_RXAH           (*(unsigned char volatile __xdata *)0xfa6d)
#define     DMA_UR4R_RXAL           (*(unsigned char volatile __xdata *)0xfa6e)

#define     DMA_LCM_CFG             (*(unsigned char volatile __xdata *)0xfa70)
#define     DMA_LCM_CR              (*(unsigned char volatile __xdata *)0xfa71)
#define     DMA_LCM_STA             (*(unsigned char volatile __xdata *)0xfa72)
#define     DMA_LCM_AMT             (*(unsigned char volatile __xdata *)0xfa73)
#define     DMA_LCM_DONE            (*(unsigned char volatile __xdata *)0xfa74)
#define     DMA_LCM_TXA             (*(unsigned  int volatile __xdata *)0xfa75)
#define     DMA_LCM_TXAH            (*(unsigned char volatile __xdata *)0xfa75)
#define     DMA_LCM_TXAL            (*(unsigned char volatile __xdata *)0xfa76)
#define     DMA_LCM_RXA             (*(unsigned  int volatile __xdata *)0xfa77)
#define     DMA_LCM_RXAH            (*(unsigned char volatile __xdata *)0xfa77)
#define     DMA_LCM_RXAL            (*(unsigned char volatile __xdata *)0xfa78)

/////////////////////////////////////////////////
//F900H-F9FFH
/////////////////////////////////////////////////

#define     PWMA_ENO2               (*(unsigned char volatile __xdata *)0xf930)
#define     PWMA_IOAUX2             (*(unsigned char volatile __xdata *)0xf931)
#define     PWMA_CR3                (*(unsigned char volatile __xdata *)0xf932)
#define     PWMA_SR3                (*(unsigned char volatile __xdata *)0xf933)
#define     PWMA_CCER3              (*(unsigned char volatile __xdata *)0xf934)
#define     PWMA_CCMR1X             (*(unsigned char volatile __xdata *)0xf938)
#define     PWMA_CCMR2X             (*(unsigned char volatile __xdata *)0xf939)
#define     PWMA_CCMR3X             (*(unsigned char volatile __xdata *)0xf93a)
#define     PWMA_CCMR4X             (*(unsigned char volatile __xdata *)0xf93b)
#define     PWMA_CCMR5              (*(unsigned char volatile __xdata *)0xf93c)
#define     PWMA_CCMR5X             (*(unsigned char volatile __xdata *)0xf93d)
#define     PWMA_CCMR6              (*(unsigned char volatile __xdata *)0xf93e)
#define     PWMA_CCMR6X             (*(unsigned char volatile __xdata *)0xf93f)
#define     PWMA_CCR5H              (*(unsigned char volatile __xdata *)0xf940)
#define     PWMA_CCR5L              (*(unsigned char volatile __xdata *)0xf941)
#define     PWMA_CCR5X              (*(unsigned char volatile __xdata *)0xf942)
#define     PWMA_CCR6H              (*(unsigned char volatile __xdata *)0xf943)
#define     PWMA_CCR6L              (*(unsigned char volatile __xdata *)0xf944)

/////////////////////////////////////////////////
//USB Control Regiter
/////////////////////////////////////////////////

//sfr       USBCLK      =           0xdc;
//sfr       USBDAT      =           0xec;
//sfr       USBCON      =           0xf4;
//sfr       USBADR      =           0xfc;

//使用方法:
//      char dat;
//
//      READ_USB(CSR0, dat);        //读USB寄存器
//      WRITE_USB(FADDR, 0x00);     //写USB寄存器

#define     READ_USB(reg, dat)          \
            {                           \
                while (USBADR & 0x80);  \
                USBADR = (reg) | 0x80;  \
                while (USBADR & 0x80);  \
                (dat) = USBDAT;         \
            }

#define     WRITE_USB(reg, dat)         \
            {                           \
                while (USBADR & 0x80);  \
                USBADR = (reg) & 0x7f;  \
                USBDAT = (dat);         \
            }

#define     USBBASE                 0
#define     FADDR                   (USBBASE + 0)
#define     UPDATE                  0x80
#define     POWER                   (USBBASE + 1)
#define     ISOUD                   0x80
#define     USBRST                  0x08
#define     USBRSU                  0x04
#define     USBSUS                  0x02
#define     ENSUS                   0x01
#define     INTRIN1                 (USBBASE + 2)
#define     EP5INIF                 0x20
#define     EP4INIF                 0x10
#define     EP3INIF                 0x08
#define     EP2INIF                 0x04
#define     EP1INIF                 0x02
#define     EP0IF                   0x01
#define     INTROUT1                (USBBASE + 4)
#define     EP5OUTIF                0x20
#define     EP4OUTIF                0x10
#define     EP3OUTIF                0x08
#define     EP2OUTIF                0x04
#define     EP1OUTIF                0x02
#define     INTRUSB                 (USBBASE + 6)
#define     SOFIF                   0x08
#define     RSTIF                   0x04
#define     RSUIF                   0x02
#define     SUSIF                   0x01
#define     INTRIN1E                (USBBASE + 7)
#define     EP5INIE                 0x20
#define     EP4INIE                 0x10
#define     EP3INIE                 0x08
#define     EP2INIE                 0x04
#define     EP1INIE                 0x02
#define     EP0IE                   0x01
#define     INTROUT1E               (USBBASE + 9)
#define     EP5OUTIE                0x20
#define     EP4OUTIE                0x10
#define     EP3OUTIE                0x08
#define     EP2OUTIE                0x04
#define     EP1OUTIE                0x02
#define     INTRUSBE                (USBBASE + 11)
#define     SOFIE                   0x08
#define     RSTIE                   0x04
#define     RSUIE                   0x02
#define     SUSIE                   0x01
#define     FRAME1                  (USBBASE + 12)
#define     FRAME2                  (USBBASE + 13)
#define     INDEX                   (USBBASE + 14)
#define     INMAXP                  (USBBASE + 16)
#define     CSR0                    (USBBASE + 17)
#define     SSUEND                  0x80
#define     SOPRDY                  0x40
#define     SDSTL                   0x20
#define     SUEND                   0x10
#define     DATEND                  0x08
#define     STSTL                   0x04
#define     IPRDY                   0x02
#define     OPRDY                   0x01
#define     INCSR1                  (USBBASE + 17)
#define     INCLRDT                 0x40
#define     INSTSTL                 0x20
#define     INSDSTL                 0x10
#define     INFLUSH                 0x08
#define     INUNDRUN                0x04
#define     INFIFONE                0x02
#define     INIPRDY                 0x01
#define     INCSR2                  (USBBASE + 18)
#define     INAUTOSET               0x80
#define     INISO                   0x40
#define     INMODEIN                0x20
#define     INMODEOUT               0x00
#define     INENDMA                 0x10
#define     INFCDT                  0x08
#define     OUTMAXP                 (USBBASE + 19)
#define     OUTCSR1                 (USBBASE + 20)
#define     OUTCLRDT                0x80
#define     OUTSTSTL                0x40
#define     OUTSDSTL                0x20
#define     OUTFLUSH                0x10
#define     OUTDATERR               0x08
#define     OUTOVRRUN               0x04
#define     OUTFIFOFUL              0x02
#define     OUTOPRDY                0x01
#define     OUTCSR2                 (USBBASE + 21)
#define     OUTAUTOCLR              0x80
#define     OUTISO                  0x40
#define     OUTENDMA                0x20
#define     OUTDMAMD                0x10
#define     COUNT0                  (USBBASE + 22)
#define     OUTCOUNT1               (USBBASE + 22)
#define     OUTCOUNT2               (USBBASE + 23)
#define     FIFO0                   (USBBASE + 32)
#define     FIFO1                   (USBBASE + 33)
#define     FIFO2                   (USBBASE + 34)
#define     FIFO3                   (USBBASE + 35)
#define     FIFO4                   (USBBASE + 36)
#define     FIFO5                   (USBBASE + 37)
#define     UTRKCTL                 (USBBASE + 48)
#define     UTRKSTS                 (USBBASE + 49)

/////////////////////////////////////////////////
//Interrupt Vector
/////////////////////////////////////////////////

#define     INT0_VECTOR             0       //0003H
#define     TMR0_VECTOR             1       //000BH
#define     INT1_VECTOR             2       //0013H
#define     TMR1_VECTOR             3       //001BH
#define     UART1_VECTOR            4       //0023H
#define     ADC_VECTOR              5       //002BH
#define     LVD_VECTOR              6       //0033H
#define     UART2_VECTOR            8       //0043H
#define     SPI_VECTOR              9       //004BH
#define     INT2_VECTOR             10      //0053H
#define     INT3_VECTOR             11      //005BH
#define     TMR2_VECTOR             12      //0063H
#define     USER_VECTOR             13      //006BH
#define     INT4_VECTOR             16      //0083H
#define     UART3_VECTOR            17      //008BH
#define     UART4_VECTOR            18      //0093H
#define     TMR3_VECTOR             19      //009BH
#define     TMR4_VECTOR             20      //00A3H
#define     CMP_VECTOR              21      //00ABH
#define     I2C_VECTOR              24      //00C3H
#define     USB_VECTOR              25      //00CBH
#define     PWMA_VECTOR             26      //00D3H
#define     PWMB_VECTOR             27      //00DBH

#define     TKSU_VECTOR             35      //011BH
#define     RTC_VECTOR              36      //0123H
#define     P0INT_VECTOR            37      //012BH
#define     P1INT_VECTOR            38      //0133H
#define     P2INT_VECTOR            39      //013BH
#define     P3INT_VECTOR            40      //0143H
#define     P4INT_VECTOR            41      //014BH
#define     P5INT_VECTOR            42      //0153H
#define     P6INT_VECTOR            43      //015BH
#define     P7INT_VECTOR            44      //0163H
#define     DMA_M2M_VECTOR          47      //017BH
#define     DMA_ADC_VECTOR          48      //0183H
#define     DMA_SPI_VECTOR          49      //018BH
#define     DMA_UR1T_VECTOR         50      //0193H
#define     DMA_UR1R_VECTOR         51      //019BH
#define     DMA_UR2T_VECTOR         52      //01A3H
#define     DMA_UR2R_VECTOR         53      //01ABH
#define     DMA_UR3T_VECTOR         54      //01B3H
#define     DMA_UR3R_VECTOR         55      //01BBH
#define     DMA_UR4T_VECTOR         56      //01C3H
#define     DMA_UR4R_VECTOR         57      //01CBH
#define     DMA_LCM_VECTOR          58      //01D3H
#define     LCM_VECTOR              59      //01DBH

/////////////////////////////////////////////////

#define	EAXSFR()		P_SW2 |= 0x80		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展SFR(XSFR) */
#define	EAXRAM()		P_SW2 &= ~0x80		/* MOVX A,@DPTR/MOVX @DPTR,A指令的操作对象为扩展RAM(XRAM) */

/////////////////////////////////////////////////
#define NOP1()  NOP()
#define NOP2()  NOP1();NOP1()
#define NOP3()  NOP2();NOP1()
#define NOP4()  NOP3();NOP1()
#define NOP5()  NOP4();NOP1()
#define NOP6()  NOP5();NOP1()
#define NOP7()  NOP6();NOP1()
#define NOP8()  NOP7();NOP1()
#define NOP9()  NOP8();NOP1()
#define NOP10() NOP9();NOP1()
#define NOP11() NOP10();NOP1()
#define NOP12() NOP11();NOP1()
#define NOP13() NOP12();NOP1()
#define NOP14() NOP13();NOP1()
#define NOP15() NOP14();NOP1()
#define NOP16() NOP15();NOP1()
#define NOP17() NOP16();NOP1()
#define NOP18() NOP17();NOP1()
#define NOP19() NOP18();NOP1()
#define NOP20() NOP19();NOP1()
#define NOP21() NOP20();NOP1()
#define NOP22() NOP21();NOP1()
#define NOP23() NOP22();NOP1()
#define NOP24() NOP23();NOP1()
#define NOP25() NOP24();NOP1()
#define NOP26() NOP25();NOP1()
#define NOP27() NOP26();NOP1()
#define NOP28() NOP27();NOP1()
#define NOP29() NOP28();NOP1()
#define NOP30() NOP29();NOP1()
#define NOP31() NOP30();NOP1()
#define NOP32() NOP31();NOP1()
#define NOP33() NOP32();NOP1()
#define NOP34() NOP33();NOP1()
#define NOP35() NOP34();NOP1()
#define NOP36() NOP35();NOP1()
#define NOP37() NOP36();NOP1()
#define NOP38() NOP37();NOP1()
#define NOP39() NOP38();NOP1()
#define NOP40() NOP39();NOP1()


/////////////////////////////////////////////////

#endif
