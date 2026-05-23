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

#include    "STC8G_H_I2C.h"

#if defined(USE_I2C) && defined(USE_I2C_INT)
uint8_t __xdata I2C_Buffer[I2C_BUF_LENTH];
#endif

//========================================================================
// 函数: void I2C_Init(I2C_InitTypeDef *I2Cx)
// 描述: I2C初始化程序.
// 参数: I2Cx: 结构参数,请参考I2C.h里的定义.
// 返回: none.
// 版本: V1.0, 2012-11-22
//========================================================================
#ifdef USE_I2C
void I2C_Init(I2C_InitTypeDef __xdata * I2Cx)
{
    if(I2Cx->I2C_Mode == I2C_Mode_Master)
    {
        I2C_Master();            //设为主机    
        I2CMSST = 0x00;        //清除I2C主机状态寄存器
        I2C_SetSpeed(I2Cx->I2C_Speed);
        if(I2Cx->I2C_MS_WDTA == ENABLE)        I2C_WDTA_EN();    //使能自动发送
        else                                    I2C_WDTA_DIS();    //禁止自动发送
    }
    else
    {
        I2C_Slave();    //设为从机
        I2CSLST = 0x00;        //清除I2C从机状态寄存器
        I2C_Address(I2Cx->I2C_SL_ADR);
        if(I2Cx->I2C_SL_MA == ENABLE)        I2C_MATCH_EN();    //从机地址比较功能，只接受相匹配地址
        else                                    I2C_MATCH_DIS();    //禁止从机地址比较功能，接受所有设备地址
    }
    
    I2C_Function(I2Cx->I2C_Enable);
}
#endif

//========================================================================
// 函数: uint8_t    Get_MSBusy_Status (void)
// 描述: 获取主机忙碌状态.
// 参数: none.
// 返回: 主机忙碌状态.
// 版本: V1.0, 2012-11-22
//========================================================================
#ifdef USE_I2C
uint8_t Get_MSBusy_Status(void)
{
    return (I2CMSST & 0x80);
}
#endif

//========================================================================
// 函数: void    I2C_Wait (void)
// 描述: 等待主机模式I2C控制器执行完成I2CMSCR.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2012-11-22
//========================================================================
#ifdef USE_I2C
void I2C_Wait(void)
{
    while (!(I2CMSST & 0x40));
    I2CMSST &= ~0x40;
}
#endif

//========================================================================
// 函数: void I2C_Start (void)
// 描述: I2C总线起始函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-15
//========================================================================
#ifdef USE_I2C
void I2C_Start(void)
{
    I2CMSCR = 0x01;                         //发送START命令
    I2C_Wait();
}
#endif

//========================================================================
// 函数: void I2C_SendData (char dat)
// 描述: I2C发送一个字节数据函数.
// 参数: 发送的数据.
// 返回: none.
// 版本: V1.0, 2020-09-15
//========================================================================
#ifdef USE_I2C
void I2C_SendData(char __xdata dat)
{
    I2CTXD = dat;                           //写数据到数据缓冲区
    I2CMSCR = 0x02;                         //发送SEND命令
    I2C_Wait();
}
#endif

//========================================================================
// 函数: void I2C_RecvACK (void)
// 描述: I2C获取ACK函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-15
//========================================================================
#ifdef USE_I2C
void I2C_RecvACK(void)
{
    I2CMSCR = 0x03;                         //发送读ACK命令
    I2C_Wait();
}
#endif

//========================================================================
// 函数: char I2C_RecvData (void)
// 描述: I2C读取一个字节数据函数.
// 参数: none.
// 返回: 读取数据.
// 版本: V1.0, 2020-09-15
//========================================================================
#ifdef USE_I2C
char I2C_RecvData(void)
{
    I2CMSCR = 0x04;                         //发送RECV命令
    I2C_Wait();
    return I2CRXD;
}
#endif

//========================================================================
// 函数: void I2C_SendACK (void)
// 描述: I2C发送ACK函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-15
//========================================================================
#ifdef USE_I2C
void I2C_SendACK(void)
{
    I2CMSST = 0x00;                         //设置ACK信号
    I2CMSCR = 0x05;                         //发送ACK命令
    I2C_Wait();
}
#endif

//========================================================================
// 函数: void I2C_SendNAK (void)
// 描述: I2C发送NAK函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-15
//========================================================================
#ifdef USE_I2C
void I2C_SendNAK(void)
{
    I2CMSST = 0x01;                         //设置NAK信号
    I2CMSCR = 0x05;                         //发送ACK命令
    I2C_Wait();
}
#endif

//========================================================================
// 函数: void I2C_Stop (void)
// 描述: I2C总线停止函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2020-09-15
//========================================================================
#ifdef USE_I2C
void I2C_Stop(void)
{
    I2CMSCR = 0x06;                         //发送STOP命令
    I2C_Wait();
}
#endif

//========================================================================
// 函数: void I2C_SendCmdData (uint8_t cmd, uint8_t dat)
// 描述: I2C发送一个字节数据函数.
// 参数: 命令/数据.
// 返回: none.
// 版本: V1.0, 2020-09-15
//========================================================================
#ifdef USE_I2C
void I2C_SendCmdData(uint8_t __xdata cmd, uint8_t __xdata dat)
{
    I2CTXD = dat;                           //写数据到数据缓冲区
    I2CMSCR = cmd;                          //设置命令
    I2C_Wait();
}
#endif

//========================================================================
// 函数: void I2C_WriteNbyte(uint8_t dev_addr, uint8_t mem_addr, uint8_t *p, uint8_t number)
// 描述: I2C写入数据函数.
// 参数: dev_addr: 设备地址, mem_addr: 存储地址, *p写入数据存储位置, number写入数据个数.
// 返回: none.
// 版本: V1.0, 2020-09-15
//========================================================================
#ifdef USE_I2C
void I2C_WriteNbyteAddrLen(uint8_t __xdata dev_addr, uint8_t __xdata * mem_addr, uint8_t __xdata mem_len, uint8_t __xdata * p, uint8_t __xdata number)
{
    I2C_Start();                                //发送起始命令
    I2C_SendData(dev_addr);                     //发送设备地址+写命令
    I2C_RecvACK();
    do
    {
        I2C_SendData(*mem_addr++);
        I2C_RecvACK();
    } while(--mem_len);                         //发送存储地址
    do
    {
        I2C_SendData(*p++);
        I2C_RecvACK();
    } while(--number);
    I2C_Stop();                                 //发送停止命令
}
void I2C_WriteNbyte(uint8_t __xdata dev_addr, uint8_t __xdata mem_addr, uint8_t __xdata * p, uint8_t __xdata number) {
    I2C_WriteNbyteAddrLen(dev_addr, &mem_addr, 1, p, number);
}
#endif

//========================================================================
// 函数: void I2C_ReadNbyte(uint8_t dev_addr, uint8_t mem_addr, uint8_t *p, uint8_t number)
// 描述: I2C读取数据函数.
// 参数: dev_addr: 设备地址, mem_addr: 存储地址, *p读取数据存储位置, number读取数据个数.
// 返回: none.
// 版本: V1.0, 2020-09-15
//========================================================================
#ifdef USE_I2C
void I2C_ReadNbyteAddrLen(uint8_t __xdata dev_addr, uint8_t __xdata * mem_addr, uint8_t __xdata mem_len, uint8_t __xdata * p, uint8_t __xdata number)
{
    I2C_Start();                                //发送起始命令
    I2C_SendData(dev_addr);                     //发送设备地址+写命令
    I2C_RecvACK();
    do
    {
        I2C_SendData(*mem_addr++);
        I2C_RecvACK();
    } while(--mem_len);                         //发送存储地址
    I2C_Start();                                //发送起始命令
    I2C_SendData(dev_addr|1);                   //发送设备地址+读命令
    I2C_RecvACK();
    do
    {
        *p = I2C_RecvData();
        p++;
        if(number != 1) I2C_SendACK();          //send ACK
    } while(--number);
    I2C_SendNAK();                              //send no ACK    
    I2C_Stop();                                 //发送停止命令
}
void I2C_ReadNbyte(uint8_t __xdata dev_addr, uint8_t __xdata mem_addr, uint8_t __xdata * p, uint8_t __xdata number) {
    I2C_ReadNbyteAddrLen(dev_addr, &mem_addr, 1, p, number);
}
#endif
