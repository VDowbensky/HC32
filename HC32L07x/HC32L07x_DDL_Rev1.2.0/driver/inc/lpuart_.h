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
* @file lpuart.h 
* 
* @brief Header file for LPUART functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __LPUART_H__
#define __LPUART_H__
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
** \defgroup LPUartGroup Universal Asynchronous Receiver/Transmitter (LPUART) 
** 
******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/**********************************************************************************/

/*******************************************************************************
* Global type definitions
******************************************************************************/
/**
******************************************************************************
**\brief LPuart channel selection
**************************************************************************/

/**
**********************************************************************************
**\brief lpuart sclk clock source selection
******************************************************************************/

typedef enum en_lpuart_sclk_sel
{
    LPUartMskPclk = 0u<<11, ///<pclk
    LPUartMskXtl = 2u<<11, ///<External low-speed crystal oscillator
    LPUartMskRcl = 3u<<11, ///<Internal low-speed crystal oscillator
} en_lpuart_sclksel_t;

/**
******************************************************************************
** \brief lpuart multi-machine mode address frame/data frame or parity check
**************************************************************************/
typedef enum en_lpuart_mmdorck
{
    LPUartDataOrAddr = 0u, ///<In multi-machine mode, read and write SBUF[8] to determine whether the frame is a data frame or an address frame
    LPUartEven = 0x4u, ///<Non-multi-machine mode even parity
    LPUartOdd = 0x8u, ///<Non-multi-machine mode odd parity
} en_lpuart_mmdorck_t;

/**
******************************************************************************
** \brief LPUART multi-mode and slave address and address mask configuration
******************************************************************************/

typedef struct stc_lpuart_multimode
{
    uint8_t u8SlaveAddr; ///<slave address
    uint8_t u8SaddEn; ///<slave and address mask
}stc_lpuart_multimode_t;

/**
********************************************************************************
** \brief LPUART four operating mode selections
******************************************************************************/

typedef enum en_lpuart_mode
{
    LPUartMskMode0 = 0x00u, ///<mode 0
    LPUartMskMode1 = 0x40u, ///<Mode 1
    LPUartMskMode2 = 0x80u, ///<Mode 2
    LPUartMskMode3 = 0xc0u, ///<Mode 3
} en_lpuart_mode_t;
/**
****************************************************************************
** \brief lpuart stop length selection
******************************************************************************/

typedef enum en_lpuart_stop
{
    LPUart1bit = 0x0000u, ///<1 stop bit
    LPUart1_5bit = 0x4000u, ///<1.5 stop bits
    LPUart2bit = 0x8000u, ///<2 stop bits
} en_lpuart_stop_t;
/**
********************************************************************************
** \brief lpuart Function Enable
************************************************************************/
typedef enum en_lpuart_func
{
    LPUartRenFunc = 4u, ///<0 - TX; ///<1 - Non-mode0 mode represents RX & TX, mode0 mode represents RX;
    LPUartDmaRxFunc = 16u, ///<DMA receive function
    LPUartDmaTxFunc = 17u, ///<DMA transmit function
    LPUartRtsFunc = 18u, ///<Hardware stream RTS function
    LPUartCtsFunc = 19u, ///<Hardware stream CTS function
    LPUartHdFunc = 22u, ///<Single-line half-duplex function
}en_lpuart_func_t;
/**
****************************************************************************
** \brief lpuart interrupt enable control
******************************************************************************/
typedef enum en_lpuart_irq_sel
{
    LPUartRxIrq = 0u, ///<Receive interrupt enable
    LPUartTxIrq = 1u, ///<Transmit interrupt enable
    LPUartTxEIrq = 8u, ///<TX empty interrupt enable
    LPUartPEIrq = 13u, ///<Parity check interrupt enable
    LPUartCtsIrq = 20u, ///<CTS signal toggle interrupt enable
    LPUartFEIrq = 21u, ///<Frame error interrupt enable
}en_lpuart_irq_sel_t;

/**
****************************************************************************
** \brief lpuart status flags
********************************************************************************/
typedef enum en_lpuart_status
{
    LPUartRC = 0u, ///<Receive data complete flag
    LPUartTC = 1u, ///<Transmit data complete flag
    LPUartFE = 2u, ///<Frame error flag
    LPUartTxe = 3u, ///<TXbuff empty flag
    LPUartPE = 4u, ///<Parity error flag
    LPUartCtsIf = 5u, ///<CTS interrupt flag
    LPUartCts = 6u, ///<CTS signal flag
}en_lpuart_status_t;

/**
****************************************************************************
** \brief lpuart channel sampling frequency division configuration
****************************************************************************/
typedef enum en_lpuart_clkdiv
{
    LPUartMsk16Or32Div = 0u, ///<Mode 0 is invalid. Mode 1/3 is divided by 16, and Mode 2 is divided by 32.
    LPUartMsk8Or16Div = 0x200u, ///<Mode 0 is invalid. Mode 1/3 is divided by 8, and Mode 2 is divided by 16.
    LPUartMsk4Or8Div = 0x400u, ///<Mode 0 is invalid. Mode 1/3 is divided by 4, and Mode 2 is divided by 8.
}en_lpuart_clkdiv_t;

/**
********************************************************************************
** \brief lpuart channel Mode 1 and Mode 3 baud rate calculation parameters
************************************************************************/
typedef struct stc_lpuart_baud
{
    en_lpuart_sclksel_t enSclkSel; ///<Transmit clock source selection
    en_lpuart_clkdiv_t enSclkDiv; ///<Sampling frequency division selection
    uint32_t u32Sclk; ///<sclk
    uint32_t u32Baud; ///<Baud rate
} stc_lpuart_baud_t;
/**
******************************************************************************
** \lpuart overall configuration
**************************************************************************/
typedef struct stc_lpuart_cfg
{
    en_lpuart_mode_t enRunMode; ///<Four mode configurations
    en_lpuart_mmdorck_t enMmdorCk; ///<Parity mode
    en_lpuart_stop_t enStopBit; ///<Stop bit length
    stc_lpuart_baud_t stcBaud; ///<Mode 1/3 baud rate configuration
} stc_lpuart_cfg_t;

// Overall initialization process
en_result_t LPUart_Init(M0P_LPUART_TypeDef* LPUARTx, stc_lpuart_cfg_t* pstcCfg);

// Enable/disable LPUART single-line mode
void LPUart_HdModeEnable(M0P_LPUART_TypeDef* LPUARTx);
void LPUart_HdModeDisable(M0P_LPUART_TypeDef* LPUARTx);

// Set TB8 data
void LPUart_SetTb8(M0P_LPUART_TypeDef* LPUARTx, boolean_t bTB8Value);

// Get data register bit 8
boolean_t LPUart_GetRb8(M0P_LPUART_TypeDef* LPUARTx);

//Interrupt related setting functions enable and disable
en_result_t LPUart_EnableIrq(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_irq_sel_t enIrqSel);
en_result_t LPUart_DisableIrq(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_irq_sel_t enIrqSel);

//Special function enable and disable
en_result_t LPUart_EnableFunc(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_func_t enFunc);
en_result_t LPUart_DisableFunc(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_func_t enFunc);

//Status bit acquisition function
boolean_t LPUart_GetStatus(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_status_t enStatus);
//Clear status bit
en_result_t LPUart_ClrStatus(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_status_t enStatus);
//Get the entire status register
uint8_t LPUart_GetIsr(M0P_LPUART_TypeDef* LPUARTx);
//Clear the entire status register
en_result_t LPUart_ClrIsr(M0P_LPUART_TypeDef* LPUARTx);

//Send data query method
en_result_t LPUart_SendData(M0P_LPUART_TypeDef* LPUARTx, uint8_t u8Data);
en_result_t LPUart_SendDataTimeOut(M0P_LPUART_TypeDef* LPUARTx, uint8_t u8Data, uint32_t u32TimeOut);
//Data interrupt transmission
en_result_t LPUart_SendDataIt(M0P_LPUART_TypeDef* LPUARTx, uint8_t u8Data);
//Data reception
uint8_t LPUart_ReceiveData(M0P_LPUART_TypeDef* LPUARTx);

//LPUARTx channel number, enClk clock source option
en_result_t LPUart_SelSclk(M0P_LPUART_TypeDef* LPUARTx, en_lpuart_sclksel_t enSclk);

//LPUART channel multi-master mode configuration
en_result_t LPUart_SetMultiMode(M0P_LPUART_TypeDef* LPUARTx, stc_lpuart_multimode_t* pstcMultiCfg);

//LPUART channel multi-master mode slave address configuration function
en_result_t LPUart_SetSaddr(M0P_LPUART_TypeDef* LPUARTx, uint8_t u8Addr);

//@} // LPUartGroup

#ifdef __cplusplus
#endif

#endif /* __LPUART_H__ */
/******************************************************************************
* EOF (not truncated)
***********************************************************************/
