/****************************************************************************** 
* Copyright (C) 2021, Xiaohua Semiconductor Co., Ltd. All rights reserved. 
* 
* This software component is licensed by XHSC under BSD 3-Clause license 
* (the "License"); You may not use this file except in compliance with the 
* License. You may obtain a copy of the License at: 
* opensource.org/licenses/BSD-3-Clause 
* 
******************************************************************************/

/****************************************************************************** 
* @file uart.h 
* 
* @brief Header file for UART functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __UART_H__
#define __UART_H__
/**************************************************************************** 
* Include files 
*******************************************************************************/
#include "ddl.h"


#ifdef __cplusplus
extern "C"
{
#endif

/** 
****************************************************************************** 
** \defgroup UartGroup Universal Asynchronous Receiver/Transmitter (UART) 
** 
******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/**********************************************************************************/

/******************************************************************************
* Global type definitions
******************************************************************************/
/**
******************************************************************************
**\brief uart channel selection
******************************************************************************/

/**
******************************************************************************
** \brief uart multi-machine mode address frame/data frame or parity check
******************************************************************************/
typedef enum en_uart_mmdorck
{
    UartMskDataOrAddr = 0u, ///< In multi-machine mode, determine whether the frame is a data frame or an address frame by reading and writing SBUF[8]
    UartMskEven = 0x4u, ///<Even parity in non-multi-process mode
    UartMskOdd = 0x8u, ///<Odd parity in non-multi-process mode
}en_uart_mmdorck_t;

/**
****************************************************************************
** \brief UART multi-process mode and slave address and address mask configuration
******************************************************************************/
typedef struct stc_uart_multimode
{
    uint8_t u8SlaveAddr; ///<Slave address
    uint8_t u8SaddEn; ///<Slave address and address mask
}stc_uart_multimode_t;

/**
************************************************************************************
** \brief UART four operating mode selections
******************************************************************************/

typedef enum en_uart_mode
{
    UartMskMode0 = 0x00u, ///<Mode 0
    UartMskMode1 = 0x40u, ///<Mode 1
    UartMskMode2 = 0x80u, ///<Mode 2
    UartMskMode3 = 0xc0u, ///<Mode 3
} en_uart_mode_t;
/**
********************************************************************************
** \brief UART stop length selection
****************************************************************************/

typedef enum en_uart_stop
{
    UartMsk1bit = 0x0000u, ///<1 stop bit
    UartMsk1_5bit = 0x4000u, ///<1.5 stop bits
    UartMsk2bit = 0x8000u, ///<2 stop bits
} en_uart_stop_t;
/**
****************************************************************************
** \brief UART function enable
************************************************************************/
typedef enum en_uart_func
{
    UartRenFunc = 4u, ///<0 - TX; ///<1 - Non-mode0 mode represents RX & TX, mode0 mode represents RX;
    UartDmaRxFunc = 16u, ///<DMA receive function
    UartDmaTxFunc = 17u, ///<DMA transmit function
    UartRtsFunc = 18u, ///<Hardware stream RTS function
    UartCtsFunc = 19u, ///<Hardware stream CTS function
    UartHdFunc = 22u, ///<Single-line half-duplex function
}en_uart_func_t;
/**
****************************************************************************
** \brief UART interrupt enable control
************************************************************************/
typedef enum en_uart_irq_sel
{
    UartRxIrq = 0u, ///<Receive interrupt enable
    UartTxIrq = 1u, ///<Transmit interrupt enable
    UartTxEIrq = 8u, ///<TX empty interrupt enable
    UartPEIrq = 13u, ///<Parity check interrupt enable
    UartCtsIrq = 20u, ///<CTS signal toggle interrupt enable
    UartFEIrq = 21u, ///<Frame error interrupt enable 
}en_uart_irq_sel_t;

/**
************************************************************************
** \brief UART status flags
************************************************************************/
typedef enum en_uart_status
{
    UartRC = 0u, ///<Receive data complete flag
    UartTC = 1u, ///<Transmit data complete flag
    UartFE = 2u, ///<Frame error flag
    UartTxe = 3u, ///<TXbuff empty flag
    UartPE = 4u, ///<Parity error flag
    UartCtsIf = 5u, ///<CTS interrupt flag
    UartCts = 6u, ///<CTS signal flag
}en_uart_status_t;

/**
************************************************************************************
** Brief UART channel sampling and frequency division configuration
**********************************************************************************/
typedef enum en_uart_clkdiv
{
    UartMsk16Or32Div = 0u, ///<Mode 0 is invalid. Mode 1/3 is divided by 16, and Mode 2 is divided by 32.
    UartMsk8Or16Div = 0x200u, ///<Mode 0 is invalid. Mode 1/3 is divided by 8, and Mode 2 is divided by 16.
}en_uart_clkdiv_t;
/**
********************************************************************************
** \brief UART channel Mode 1 and Mode 3 baud rate calculation parameters
************************************************************************/
typedef struct stc_uart_baud
{
    en_uart_clkdiv_t enClkDiv; ///<Sampling divider
    uint32_t u32Pclk; ///<pclk
    uint32_t u32Baud; ///<baud rate
}stc_uart_baud_t;
/**
****************************************************************************
**\uart overall configuration
************************************************************************/

typedef struct stc_uart_cfg
{
    en_uart_mode_t enRunMode; ///<four mode configurations
    en_uart_mmdorck_t enMmdorCk; ///<check mode
    en_uart_stop_t enStopBit; ///<stop bit length
    stc_uart_baud_t stcBaud; ///<Mode 1/3 baud rate configuration
}stc_uart_cfg_t;

//UART initialization
en_result_t Uart_Init(M0P_UART_TypeDef* UARTx, stc_uart_cfg_t* pstcCfg);

///< Enable/disable UART single-wire mode
void Uart_HdModeEnable(M0P_UART_TypeDef* UARTx);
void Uart_HdModeDisable(M0P_UART_TypeDef* UARTx);

//UART module multi-device mode setting function
en_result_t Uart_SetMultiMode(M0P_UART_TypeDef* UARTx,stc_uart_multimode_t* pstcMultiCfg);

//TB8 data setting
void Uart_SetTb8(M0P_UART_TypeDef* UARTx, boolean_t bTB8Value);
//RB8 data acquisition
boolean_t Uart_GetRb8(M0P_UART_TypeDef* UARTx);

//Interrupt related setting function
en_result_t Uart_EnableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel);
en_result_t Uart_DisableIrq(M0P_UART_TypeDef* UARTx, en_uart_irq_sel_t enIrqSel);

//Function enable and disable
en_result_t Uart_EnableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc);
en_result_t Uart_DisableFunc(M0P_UART_TypeDef* UARTx, en_uart_func_t enFunc);

//Get and clear status bits
uint8_t Uart_GetIsr(M0P_UART_TypeDef* UARTx);
boolean_t Uart_GetStatus(M0P_UART_TypeDef* UARTx, en_uart_status_t enStatus);
en_result_t Uart_ClrIsr(M0P_UART_TypeDef* UARTx);
en_result_t Uart_ClrStatus(M0P_UART_TypeDef* UARTx, en_uart_status_t enStatus);

//Data transmission and reception operations
///< Data query mode transmission
en_result_t Uart_SendDataPoll(M0P_UART_TypeDef* UARTx, uint8_t u8Data);
en_result_t Uart_SendDataPollTimeOut(M0P_UART_TypeDef* UARTx, uint8_t u8Data, uint32_t u32TimeOut);
///< Data interrupt mode transmission
en_result_t Uart_SendDataIt(M0P_UART_TypeDef* UARTx, uint8_t u8Data);
uint8_t Uart_ReceiveData(M0P_UART_TypeDef* UARTx);

//@} // UartGroup

#ifdef __cplusplus
#endif

#endif /* __UART_H__ */
/****************************************************************************** 
* EOF (not truncated) 
*******************************************************************************/
