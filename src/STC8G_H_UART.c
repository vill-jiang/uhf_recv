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

#include "STC8G_H_UART.h"

//========================================================================
//                               本地变量声明
//========================================================================

#ifdef UART1
COMx_Define	__xdata COM1;
uint8_t	__xdata TX1_Buffer[COM_TX1_Lenth];	//发送缓冲
uint8_t __xdata RX1_Buffer[COM_RX1_Lenth];	//接收缓冲
#endif
#ifdef UART2
COMx_Define	__xdata COM2;
uint8_t	__xdata TX2_Buffer[COM_TX2_Lenth];	//发送缓冲
uint8_t 	__xdata RX2_Buffer[COM_RX2_Lenth];	//接收缓冲
#endif
#ifdef UART3
COMx_Define	__xdata COM3;
uint8_t	__xdata TX3_Buffer[COM_TX3_Lenth];	//发送缓冲
uint8_t 	__xdata RX3_Buffer[COM_RX3_Lenth];	//接收缓冲
#endif
#ifdef UART4
COMx_Define	__xdata COM4;
uint8_t	__xdata TX4_Buffer[COM_TX4_Lenth];	//发送缓冲
uint8_t 	__xdata RX4_Buffer[COM_RX4_Lenth];	//接收缓冲
#endif

//========================================================================
// 函数: UART_Configuration
// 描述: UART初始化程序.
// 参数: UARTx: UART组号, COMx结构参数,请参考UART.h里的定义.
// 返回: none.
// 版本: V1.0, 2012-10-22
//========================================================================
uint8_t UART_Configuration(uint8_t UARTx, COMx_InitDefine __xdata *COMx)
{
#if  defined( UART1 ) || defined( UART2 ) || defined( UART3 ) || defined( UART4 )
	uint16_t	__xdata i;
	uint32_t	__xdata j;
#else
	UARTx = NULL;
	COMx = NULL;
#endif

#ifdef UART1
	if(UARTx == UART1)
	{
		COM1.TX_send    = 0;
		COM1.TX_write   = 0;
		COM1.B_TX_busy  = 0;
		COM1.RX_Cnt     = 0;
		COM1.RX_TimeOut = 0;
		
		for(i=0; i<COM_TX1_Lenth; i++)	TX1_Buffer[i] = 0;
		for(i=0; i<COM_RX1_Lenth; i++)	RX1_Buffer[i] = 0;

		SCON = (SCON & 0x3f) | COMx->UART_Mode;	//模式设置
		if((COMx->UART_Mode == UART_9bit_BRTx) || (COMx->UART_Mode == UART_8bit_BRTx))	//可变波特率
		{
			// 编译期计算波特率重载值, 避免运行时32位除法
			j = COMx->UART_BaudRate;
			if(COMx->UART_BRT_Use == BRT_Timer1)
			{
				TR1 = 0;
				AUXR &= ~0x01;		//S1 BRT Use Timer1;
				TMOD &= ~(1<<6);	//Timer1 set As Timer
				TMOD &= ~0x30;		//Timer1_16bitAutoReload;
				AUXR |=  (1<<6);	//Timer1 set as 1T mode
				TH1 = (uint8_t)(j>>8);
				TL1 = (uint8_t)j;
				ET1 = 0;	//禁止中断
				TMOD &= ~0x40;	//定时
				INTCLKO &= ~0x02;	//不输出时钟
				TR1  = 1;
			}
			else if(COMx->UART_BRT_Use == BRT_Timer2)
			{
				AUXR &= ~(1<<4);	//Timer stop
				AUXR |= 0x01;		//S1 BRT Use Timer2;
				AUXR &= ~(1<<3);	//Timer2 set As Timer
				AUXR |=  (1<<2);	//Timer2 set as 1T mode
				T2H = (uint8_t)(j>>8);
				T2L = (uint8_t)j;
				IE2  &= ~(1<<2);	//禁止中断
				AUXR |=  (1<<4);	//Timer run enable
			}
			else return FAIL;	//错误
		}
		else if(COMx->UART_Mode == UART_ShiftRight)
		{
			if(COMx->BaudRateDouble == ENABLE)	AUXR |=  (1<<5);	//固定波特率SysClk/2
			else								AUXR &= ~(1<<5);	//固定波特率SysClk/12
		}
		else if(COMx->UART_Mode == UART_9bit)	//固定波特率SysClk*2^SMOD/64
		{
			if(COMx->BaudRateDouble == ENABLE)	PCON |=  (1<<7);	//固定波特率SysClk/32
			else								PCON &= ~(1<<7);	//固定波特率SysClk/64
		}
		UART1_RxEnable(COMx->UART_RxEnable);	//UART接收使能
		TI = 0;
		RI = 0;

		return SUCCESS;
	}
#endif
#ifdef UART2
	if(UARTx == UART2)
	{
		COM2.TX_send    = 0;
		COM2.TX_write   = 0;
		COM2.B_TX_busy  = 0;
		COM2.RX_Cnt     = 0;
		COM2.RX_TimeOut = 0;

		for(i=0; i<COM_TX2_Lenth; i++)	TX2_Buffer[i] = 0;
		for(i=0; i<COM_RX2_Lenth; i++)	RX2_Buffer[i] = 0;

		if((COMx->UART_Mode == UART_9bit_BRTx) ||(COMx->UART_Mode == UART_8bit_BRTx))	//可变波特率
		{
			if(COMx->UART_Mode == UART_9bit_BRTx)	S2CON |=  (1<<7);	//9bit
			else									S2CON &= ~(1<<7);	//8bit
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//按1T计算
			if(j >= 65536UL)	return FAIL;	//错误
			j = 65536UL - j;
			AUXR &= ~(1<<4);	//Timer stop
			AUXR &= ~(1<<3);	//Timer2 set As Timer
			AUXR |=  (1<<2);	//Timer2 set as 1T mode
			T2H = (uint8_t)(j>>8);
			T2L = (uint8_t)j;
			IE2  &= ~(1<<2);	//禁止中断
			AUXR |=  (1<<4);	//Timer run enable
		}
		else	return FAIL;	//模式错误
		UART2_RxEnable(COMx->UART_RxEnable);	//UART接收使能

		return SUCCESS;
	}
#endif
#ifdef UART3
	if(UARTx == UART3)
	{
		COM3.TX_send    = 0;
		COM3.TX_write   = 0;
		COM3.B_TX_busy  = 0;
		COM3.RX_Cnt     = 0;
		COM3.RX_TimeOut = 0;
		for(i=0; i<COM_TX3_Lenth; i++)	TX3_Buffer[i] = 0;
		for(i=0; i<COM_RX3_Lenth; i++)	RX3_Buffer[i] = 0;

		if((COMx->UART_Mode == UART_9bit_BRTx) || (COMx->UART_Mode == UART_8bit_BRTx))	//可变波特率
		{
			if(COMx->UART_Mode == UART_9bit_BRTx)	S3CON |=  (1<<7);	//9bit
			else									S3CON &= ~(1<<7);	//8bit
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//按1T计算
			if(j >= 65536UL)	return FAIL;	//错误
			j = 65536UL - j;
			if(COMx->UART_BRT_Use == BRT_Timer3)
			{
				S3CON |=  (1<<6);		//S3 BRT Use Timer3;
				T3H = (uint8_t)(j>>8);
				T3L = (uint8_t)j;
				T4T3M &= 0xf0;
				T4T3M |= 0x0a;			//Timer3 set As Timer, 1T mode, Start timer3
			}
			else if(COMx->UART_BRT_Use == BRT_Timer2)
			{
				AUXR &= ~(1<<4);		//Timer stop
				S3CON &= ~(1<<6);		//S3 BRT Use Timer2;
				AUXR &= ~(1<<3);		//Timer2 set As Timer
				AUXR |=  (1<<2);		//Timer2 set as 1T mode
				T2H = (uint8_t)(j>>8);
				T2L = (uint8_t)j;
				IE2  &= ~(1<<2);	//禁止中断
				AUXR |=  (1<<4);	//Timer run enable
			}
			else return FAIL;	//错误
		}
		else	return FAIL;	//模式错误
		UART3_RxEnable(COMx->UART_RxEnable);	//UART接收使能

		return SUCCESS;
	}
#endif
#ifdef UART4
	if(UARTx == UART4)
	{
		COM4.TX_send    = 0;
		COM4.TX_write   = 0;
		COM4.B_TX_busy  = 0;
		COM4.RX_Cnt     = 0;
		COM4.RX_TimeOut = 0;
		for(i=0; i<COM_TX4_Lenth; i++)	TX4_Buffer[i] = 0;
		for(i=0; i<COM_RX4_Lenth; i++)	RX4_Buffer[i] = 0;

		if((COMx->UART_Mode == UART_9bit_BRTx) || (COMx->UART_Mode == UART_8bit_BRTx))	//可变波特率
		{
			if(COMx->UART_Mode == UART_9bit_BRTx)	S4CON |=  (1<<7);	//9bit
			else									S4CON &= ~(1<<7);	//8bit
			j = (MAIN_Fosc / 4) / COMx->UART_BaudRate;	//按1T计算
			if(j >= 65536UL)	return FAIL;	//错误
			j = 65536UL - j;
			if(COMx->UART_BRT_Use == BRT_Timer4)
			{
				S4CON |=  (1<<6);		//S4 BRT Use Timer4;
				T4H = (uint8_t)(j>>8);
				T4L = (uint8_t)j;
				T4T3M &= 0x0f;
				T4T3M |= 0xa0;			//Timer4 set As Timer, 1T mode, Start timer4
			}
			else if(COMx->UART_BRT_Use == BRT_Timer2)
			{
				AUXR &= ~(1<<4);		//Timer stop
				S4CON &= ~(1<<6);		//S4 BRT Use Timer2;
				AUXR &= ~(1<<3);		//Timer2 set As Timer
				AUXR |=  (1<<2);		//Timer2 set as 1T mode
				T2H = (uint8_t)(j>>8);
				T2L = (uint8_t)j;
				IE2  &= ~(1<<2);	//禁止中断
				AUXR |=  (1<<4);	//Timer run enable
			}
			else return FAIL;	//错误
		}
		else	return FAIL;	//模式错误
		UART4_RxEnable(COMx->UART_RxEnable);	//UART接收使能
		
		return SUCCESS;
	}
#endif
	return FAIL;	//错误
}

/*********************************************************/

/********************* UART1 函数 ************************/
#ifdef UART1
void TX1_write2buff(uint8_t __xdata dat)	//串口1发送函数
{
    #if(UART_QUEUE_MODE == 1)
	TX1_Buffer[COM1.TX_write] = dat;	//装发送缓冲，使用队列式数据发送，一次性发送数据长度不要超过缓冲区大小（COM_TXn_Lenth）
	if(++COM1.TX_write >= COM_TX1_Lenth)	COM1.TX_write = 0;

	if(COM1.B_TX_busy == 0)		//空闲
	{  
		COM1.B_TX_busy = 1;		//标志忙
		TI = 1;					//触发发送中断
	}
    #else
    //以下是阻塞方式发送方法
	while(COM1.B_TX_busy);
	SBUF = dat;
	COM1.B_TX_busy = 1;		//标志忙
    #endif
}

void PrintString1(const uint8_t * __xdata puts)
{
    for (; *puts != 0;	puts++)  TX1_write2buff(*puts); 	//遇到停止符0结束
}

#endif

/********************* UART2 函数 ************************/
#ifdef UART2
void TX2_write2buff(uint8_t dat)	//串口2发送函数
{
    #if(UART_QUEUE_MODE == 1)
	TX2_Buffer[COM2.TX_write] = dat;	//装发送缓冲，使用队列式数据发送，一次性发送数据长度不要超过缓冲区大小（COM_TXn_Lenth）
	if(++COM2.TX_write >= COM_TX2_Lenth)	COM2.TX_write = 0;

	if(COM2.B_TX_busy == 0)		//空闲
	{  
		COM2.B_TX_busy = 1;		//标志忙
		SET_TI2();				//触发发送中断
	}
    #else
    //以下是阻塞方式发送方法
	S2BUF = dat;
	COM2.B_TX_busy = 1;		//标志忙
	while(COM2.B_TX_busy);
    #endif
}

void PrintString2(const uint8_t *puts)
{
    for (; *puts != 0;	puts++)  TX2_write2buff(*puts); 	//遇到停止符0结束
}

#endif

/********************* UART3 函数 ************************/
#ifdef UART3
void TX3_write2buff(uint8_t dat)	//串口3发送函数
{
    #if(UART_QUEUE_MODE == 1)
	TX3_Buffer[COM3.TX_write] = dat;	//装发送缓冲，使用队列式数据发送，一次性发送数据长度不要超过缓冲区大小（COM_TXn_Lenth）
	if(++COM3.TX_write >= COM_TX3_Lenth)	COM3.TX_write = 0;

	if(COM3.B_TX_busy == 0)		//空闲
	{  
		COM3.B_TX_busy = 1;		//标志忙
		SET_TI3();				//触发发送中断
	}
    #else
    //以下是阻塞方式发送方法
	S3BUF = dat;
	COM3.B_TX_busy = 1;		//标志忙
	while(COM3.B_TX_busy);
    #endif
}

void PrintString3(const uint8_t *puts)
{
    for (; *puts != 0;	puts++)  TX3_write2buff(*puts); 	//遇到停止符0结束
}

#endif

/********************* UART4 函数 ************************/
#ifdef UART4
void TX4_write2buff(uint8_t dat)	//串口4发送函数
{
    #if(UART_QUEUE_MODE == 1)
	TX4_Buffer[COM4.TX_write] = dat;	//装发送缓冲，使用队列式数据发送，一次性发送数据长度不要超过缓冲区大小（COM_TXn_Lenth）
	if(++COM4.TX_write >= COM_TX4_Lenth)	COM4.TX_write = 0;

	if(COM4.B_TX_busy == 0)		//空闲
	{  
		COM4.B_TX_busy = 1;		//标志忙
		SET_TI4();				//触发发送中断
	}
    #else
    //以下是阻塞方式发送方法
	S4BUF = dat;
	COM4.B_TX_busy = 1;		//标志忙
	while(COM4.B_TX_busy);
    #endif
}

void PrintString4(const uint8_t *puts)
{
    for (; *puts != 0;	puts++)  TX4_write2buff(*puts); 	//遇到停止符0结束
}

#endif

/*********************************************************/
/*
void COMx_write2buff(uint8_t UARTx, uint8_t dat)  //UART1/UART2/UART3/UART4
{
	if(UARTx == UART1)	TX1_write2buff(dat);
	if(UARTx == UART2)	TX2_write2buff(dat);
	if(UARTx == UART3)	TX3_write2buff(dat);
	if(UARTx == UART4)	TX4_write2buff(dat);
}

void PrintString(uint8_t UARTx, const uint8_t *putstr)
{
    for (; *putstr != 0;	putstr++)  COMx_write2buff(UARTx,*putstr); 	//遇到停止符0结束
}
*/

/********************* Printf 函数 ************************/
#if(PRINTF_SELECT == 1)

char uartputchar(char c)
{
	TX1_write2buff(c);
	return c;
}

#elif(PRINTF_SELECT == 2)

char uartputchar(char c)
{
	TX2_write2buff(c);
	return c;
}

#elif(PRINTF_SELECT == 3)

char uartputchar(char c)
{
	TX3_write2buff(c);
	return c;
}

#elif(PRINTF_SELECT == 4)

char uartputchar(char c)
{
	TX4_write2buff(c);
	return c;
}

#endif
