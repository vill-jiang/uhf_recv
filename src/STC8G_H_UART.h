/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* --- BBS: www.STCAIMCU.com  -----------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

#ifndef __STC8G_H_UART_H
#define __STC8G_H_UART_H  

#include "config.h"

//========================================================================
//                              定义声明
//========================================================================

// 大约每个490Byte的代码体积
#define UART1 1       //使用哪些串口就开对应的定义，不用的串口可屏蔽掉定义，节省资源
// #define UART2 2
// #define UART3 3
// #define UART4 4

#define UART_QUEUE_MODE 0           //设置串口发送模式，0：阻塞模式，1：队列模式

#define PRINTF_SELECT  UART1  //选择 printf 函数所使用的串口，参数 UART1~UART4

#ifdef UART1
#define COM_TX1_Lenth 8
#define COM_RX1_Lenth 8
#endif
#ifdef UART2
#define COM_TX2_Lenth 64
#define COM_RX2_Lenth 64
#endif
#ifdef UART3
#define COM_TX3_Lenth 64
#define COM_RX3_Lenth 64
#endif
#ifdef UART4
#define COM_TX4_Lenth 32
#define COM_RX4_Lenth 32
#endif

#define UART_ShiftRight 0  //同步移位输出
#define UART_8bit_BRTx (1<<6) //8位数据,可变波特率
#define UART_9bit  (2<<6) //9位数据,固定波特率
#define UART_9bit_BRTx (3<<6) //9位数据,可变波特率

#define TimeOutSet1  5
#define TimeOutSet2  5
#define TimeOutSet3  5
#define TimeOutSet4  5

#define BRT_Timer1 1
#define BRT_Timer2 2
#define BRT_Timer3 3
#define BRT_Timer4 4

//========================================================================
//                              UART设置
//========================================================================

#define  TI2     (S2CON & 2)   /* 判断TI2是否发送完成 */
#define  RI2     (S2CON & 1)   /* 判断RI2是否接收完成 */
#define  SET_TI2()   S2CON |=  (1<<1) /* 设置TI2(引起中断) */
#define  CLR_TI2()   S2CON &= ~(1<<1) /* 清除TI2 */
#define  CLR_RI2()   S2CON &= ~1   /* 清除RI2 */

#define  TI3     (S3CON & 2) != 0 /* 判断TI3是否发送完成 */
#define  RI3     (S3CON & 1) != 0 /* 判断RI3是否接收完成 */
#define  SET_TI3()   S3CON |=  (1<<1) /* 设置TI3(引起中断) */
#define  CLR_TI3()   S3CON &= ~(1<<1) /* 清除TI3 */
#define  CLR_RI3()   S3CON &= ~1   /* 清除RI3 */

#define  TI4     (S4CON & 2) != 0 /* 判断TI3是否发送完成 */
#define  RI4     (S4CON & 1) != 0 /* 判断RI3是否接收完成 */
#define  SET_TI4()   S4CON |=  2   /* 设置TI3(引起中断) */
#define  CLR_TI4()   S4CON &= ~2   /* 清除TI3 */
#define  CLR_RI4()   S4CON &= ~1   /* 清除RI3 */

#define  UART1_RxEnable(n) (n==0?(REN = 0):(REN = 1))   /* UART1接收使能 */
#define  UART2_RxEnable(n) S2CON = (S2CON & ~0x10) | (n << 4) /* UART2接收使能 */
#define  UART3_RxEnable(n) S3CON = (S3CON & ~0x10) | (n << 4) /* UART3接收使能 */
#define  UART4_RxEnable(n) S4CON = (S4CON & ~0x10) | (n << 4) /* UART4接收使能 */

typedef struct
{ 
 uint8_t TX_send;  //已发送指针
 uint8_t TX_write;  //发送写指针
 uint8_t B_TX_busy;  //忙标志

 uint8_t  RX_Cnt;   //接收字节计数
 uint8_t RX_TimeOut;  //接收超时
} COMx_Define; 

typedef struct
{ 
 uint8_t UART_Mode;   //模式,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
 uint8_t UART_BRT_Use;  //使用波特率,   BRT_Timer1,BRT_Timer2,BRT_Timer3,BRT_Timer4
 uint32_t UART_BaudRate;  //波特率,     一般 110 ~ 115200
 uint8_t Morecommunicate; //多机通讯允许, ENABLE,DISABLE
 uint8_t UART_RxEnable;  //允许接收,   ENABLE,DISABLE
 uint8_t BaudRateDouble;  //波特率加倍, ENABLE,DISABLE
} COMx_InitDefine; 

#ifdef UART1
extern COMx_Define __xdata COM1;
extern uint8_t __xdata TX1_Buffer[COM_TX1_Lenth]; //发送缓冲
extern uint8_t __xdata RX1_Buffer[COM_RX1_Lenth]; //接收缓冲
#endif
#ifdef UART2
extern COMx_Define __xdata COM2;
extern uint8_t __xdata TX2_Buffer[COM_TX2_Lenth]; //发送缓冲
extern uint8_t __xdata RX2_Buffer[COM_RX2_Lenth]; //接收缓冲
#endif
#ifdef UART3
extern COMx_Define __xdata COM3;
extern uint8_t __xdata TX3_Buffer[COM_TX3_Lenth]; //发送缓冲
extern uint8_t __xdata RX3_Buffer[COM_RX3_Lenth]; //接收缓冲
#endif
#ifdef UART4
extern COMx_Define __xdata COM4;
extern uint8_t __xdata TX4_Buffer[COM_TX4_Lenth]; //发送缓冲
extern uint8_t __xdata RX4_Buffer[COM_RX4_Lenth]; //接收缓冲
#endif

uint8_t UART_Configuration(uint8_t UARTx, COMx_InitDefine __xdata * COMx);
#ifdef UART1
void TX1_write2buff(uint8_t __xdata dat); //串口1发送函数
void PrintString1(const uint8_t * __xdata puts);
#endif
#ifdef UART2
void TX2_write2buff(uint8_t dat); //串口2发送函数
void PrintString2(const uint8_t *puts);
#endif
#ifdef UART3
void TX3_write2buff(uint8_t dat); //串口3发送函数
void PrintString3(const uint8_t *puts);
#endif
#ifdef UART4
void TX4_write2buff(uint8_t dat); //串口4发送函数
void PrintString4(const uint8_t *puts);
#endif

//void COMx_write2buff(uint8_t UARTx, uint8_t dat); //串口发送函数
//void PrintString(uint8_t UARTx, const uint8_t *putstr);

#endif

