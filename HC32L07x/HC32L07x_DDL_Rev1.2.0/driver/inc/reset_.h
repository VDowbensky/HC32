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
* @file reset.h 
* 
* @brief Header file for RESET functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __RESET_H__
#define __RESET_H__

/****************************************************************************** 
* Include files 
******************************************************************************/
#include "ddl.h"


#ifdef __cplusplus
extern "C"
{
#endif

/** 
****************************************************************************** 
** \defgroup ResetGroup Reset (RST) 
** 
******************************************************************************/
//@{

/** 
******************************************************************************* 
** function prototypes. 
******************************************************************************/

/************************************************************************************ 
*Global definitions ******************************************************************************/

/**
******************************************************************************
** \brief Peripheral reset control type definition
** \note
**************************************************************************/
typedef enum en_sysctrl_peripheral0
{
    ResetMskUart0 = 1u<<0u, ///< Serial port 0
    ResetMskUart1 = 1u<<1u, ///< Serial port 1
    ResetMskLpUart0 = 1u<<2u, ///< Low power serial port 0
    ResetMskLpUart1 = 1u<<3u, ///< Low power serial port 1
    ResetMskI2c0 = 1u<<4u, ///< I2C0
    ResetMskI2c1 = 1u<<5u, ///< I2C1
    ResetMskSpi0 = 1u<<6u, ///< SPI0
    ResetMskSpi1 = 1u<<7u, ///< SPI1
    ResetMskBaseTim = 1u<<8u, ///< Basic Timer TIM0/1/2
    ResetMskLpTim0 = 1u<<9u, ///< Low-Power Timer 0
    ResetMskAdvTim = 1u<<10u, ///< Advanced Timer TIM4/5/6
    ResetMskTim3 = 1u<<11u, ///< Timer 3
    ResetMskOpa = 1u<<13u, ///< OPA
    ResetMskPca = 1u<<14u, ///< Programmable Counter Array
    ResetMskAdcBgr = 1u<<16u, ///< ADC & BGR
    ResetMskVcLvd = 1u<<17u, ///< VC and LVD
    ResetMskRng = 1u<<18u, ///< RNG
    ResetMskPcnt = 1u<<19u, ///< PCNT
    ResetMskRtc = 1u<<20u, ///< RTC
    ResetMskTrim = 1u<<21u, ///< Clock calibration
    ResetMskLcd = 1u<<22u, ///< LCD
    ResetMskTick = 1u<<24u, ///< System timer
    ResetMskSwd = 1u<<25u, ///< SWD
    ResetMskCrc = 1u<<26u, ///< CRC
    ResetMskAes = 1u<<27u, ///< AES
    ResetMskGpio = 1u<<28u, ///< GPIO
    ResetMskDma = 1u<<29u, ///< DMA
    ResetMskHdiv = 1u<<30u, ///< HDIV
}en_reset_peripheral0_t;

typedef enum en_sysctrl_peripheral1
{
    ResetMskUsb = 1u<<0u, ///< USB
    ResetMskCan = 1u<<1u, ///< CAN
    ResetMskCts = 1u<<2u, ///< CTS
    ResetMskDac = 1u<<3u, ///< DAC
    ResetMskLpTim1 = 1u<<4u, ///< Low-power Timer 1
    ResetMskI2s0 = 1u<<5u, ///< I2S0
    ResetMskI2s1 = 1u<<6u, ///< I2S1
    ResetMskUart2 = 1u<<8u, ///< UART2
    ResetMskUart3 = 1u<<9u, ///< UART3
}en_reset_peripheral1_t;

/**
********************************************************************************
** \brief Reset source (flag) display
**
** \note
****************************************************************************/
typedef enum en_reset_flag
{
    ResetFlagMskPor5V = 1u<<0u, ///< 5V reset
    ResetFlagMskPor1_5V = 1u<<1u, ///< 1.5V reset
    ResetFlagMskLvd = 1u<<2u, ///< Low voltage detection reset
    ResetFlagMskWdt = 1u<<3u, ///< Watchdog timer reset
    ResetFlagMskPca = 1u<<4u, ///< PCA reset
    ResetFlagMskLockup = 1u<<5u, ///< System exception reset
    ResetFlagMskSysreq = 1u<<6u, ///< Software reset
    ResetFlagMskRstb = 1u<<7u, ///< RESET pin reset
}en_reset_flag_t;

/*******************************************************************************
* Global variable declarations ('extern', definition in C source)
************************************************************************/

/*******************************************************************************
* Global function prototypes (definition in C source)
******************************************************************************/
///< Get the reset source status
boolean_t Reset_GetFlag(en_reset_flag_t enRstFlg);
///< Clear the reset source status
void Reset_ClearFlag(en_reset_flag_t enRstFlg);
void Reset_ClearFlagAll(void);

///<Peripheral module reset
void Reset_RstPeripheralAll(void);
void Reset_RstPeripheral0(en_reset_peripheral0_t enPeri);
void Reset_RstPeripheral1(en_reset_peripheral1_t enPeri);

//@} // ResetGroup

#ifdef __cplusplus
#endif


#endif /* __RESET_H__ */
/************************************************************************************ 
* EOF (not truncated) 
******************************************************************************/
