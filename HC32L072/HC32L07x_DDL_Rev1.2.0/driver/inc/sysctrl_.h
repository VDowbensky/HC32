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
* @file sysctrl.h 
* 
* @brief Header file for SYSCTRL functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __SYSCTRL_H__
#define __SYSCTRL_H__

/************************************************************************************ 
* Include files 
******************************************************************************/
#include "ddl.h"


#ifdef __cplusplus
extern "C"
{
#endif

/** 
****************************************************************************** 
** \defgroup SysCtrlGroup (SYSCTRL) 
** 
******************************************************************************/
//@{

/** 
******************************************************************************* 
** function prototypes. 
******************************************************************************/

/****************************************************************************** 
* Global type definitions
**************************************************************************/

/**
******************************************************************************
** \brief System clock input source type definition
** \note
**************************************************************************/
typedef enum en_sysctrl_clk_source
{
    SysctrlClkRCH = 0u, ///< Internal high-speed clock
    SysctrlClkXTH = 1u, ///< External high-speed clock
    SysctrlClkRCL = 2u, ///< Internal low-speed clock
    SysctrlClkXTL = 3u, ///< External low-speed clock
    SysctrlClkPLL = 4u, ///< PLL clock
    SysctrlClkRC48M = 0x48, ///< RC48M clock 
}en_sysctrl_clk_source_t;

/**
****************************************************************************
** \brief RCH frequency value enumeration type definition
************************************************************************/
typedef enum en_sysctrl_rch_freq
{
    SysctrlRchFreq4MHz = 4u, ///< 4MHz
    SysctrlRchFreq8MHz = 3u, ///< 8MHz
    SysctrlRchFreq16MHz = 2u, ///< 16MHz
    SysctrlRchFreq22_12MHz = 1u, ///< 22.12MHz
    SysctrlRchFreq24MHz = 0u, ///< 24MHz
    SysctrlRchFreq48MHz = 0x48u, ///< 48MHz
}en_sysctrl_rch_freq_t;

/**
****************************************************************************
** \brief XTAL driver capability type definition
****************************************************************************/
typedef enum en_sysctrl_xtal_driver
{
    SysctrlXtalDriver0 = 0u, ///< Weakest drive capability
    SysctrlXtalDriver1 = 1u, ///< Weak drive capability
    SysctrlXtalDriver2 = 2u, ///< Normal drive capability
    SysctrlXtalDriver3 = 3u, ///< Strongest drive capability
}en_sysctrl_xtal_driver_t;

/**
************************************************************************************
** \brief XTH frequency value range selection type definition
******************************************************************************/
typedef enum en_sysctrl_xth_freq
{
    SysctrlXthFreq4_8MHz = 0u, ///< 4~8MHz
    SysctrlXthFreq8_16MHz = 1u, ///< 8~16MHz
    SysctrlXthFreq16_24MHz = 2u, ///< 16~24MHz
    SysctrlXthFreq24_32MHz = 3u, ///< 24~32MHz
}en_sysctrl_xth_freq_t;

/**
************************************************************************************
** \brief XTH clock stable period number type definition
****************************************************************************/
typedef enum en_sysctrl_xth_cycle
{
    SysctrlXthStableCycle256 = 0u, ///< 256 cycles
    SysctrlXthStableCycle1024 = 1u, ///< 1024 cycles
    SysctrlXthStableCycle4096 = 2u, ///< 4096 cycles
    SysctrlXthStableCycle16384 = 3u, ///< 16384 cycles
}en_sysctrl_xth_cycle_t;

/**
********************************************************************************
** \brief RCL frequency value enumeration type definition
****************************************************************************/
typedef enum en_sysctrl_rcl_freq
{
    SysctrlRclFreq32768 = 0x11u, ///< 32.768KHz
    SysctrlRclFreq38400 = 0x10u, ///< 38.4KHz
}en_sysctrl_rcl_freq_t;

/**
************************************************************************************
** \brief RCL clock stable cycle number type definition
****************************************************************************/
typedef enum en_sysctrl_rcl_cycle
{
    SysctrlRclStableCycle4 = 0u, ///< 4 cycles
    SysctrlRclStableCycle16 = 1u, ///< 16 cycles
    SysctrlRclStableCycle64 = 2u, ///< 64 cycles
    SysctrlRclStableCycle256 = 3u, ///< 256 cycles
}en_sysctrl_rcl_cycle_t;

/**
********************************************************************************
** \brief XTL clock stable cycle type definition
****************************************************************************/
typedef enum en_sysctrl_xtl_cycle
{
    SysctrlXtlStableCycle256 = 0u, ///< 256 cycles
    SysctrlXtlStableCycle1024 = 1u, ///< 1024 cycles
    SysctrlXtlStableCycle4096 = 2u, ///< 4096 cycles
    SysctrlXtlStableCycle16384 = 3u, ///< 16384 cycles
}en_sysctrl_xtl_cycle_t;

/**
********************************************************************************
** \brief XTL crystal amplitude enumeration type definition
****************************************************************************/
typedef enum en_sysctrl_xtl_amp
{
    SysctrlXtlAmp0 = 0u, ///< Minimum amplitude
    SysctrlXtlAmp1 = 1u, ///< Small amplitude
    SysctrlXtlAmp2 = 2u, ///< Normal amplitude
    SysctrlXtlAmp3 = 3u, ///< Maximum amplitude
}en_sysctrl_xtl_amp_t;

/**
****************************************************************************
** \brief PLL clock stable cycle number type definition
****************************************************************************/
typedef enum en_sysctrl_pll_cycle
{
    SysctrlPllStableCycle128 = 0u, ///< 128 cycles
    SysctrlPllStableCycle256 = 1u, ///< 256 cycles
    SysctrlPllStableCycle512 = 2u, ///< 512 cycles
    SysctrlPllStableCycle1024 = 3u, ///< 1024 cycles
    SysctrlPllStableCycle2048 = 4u, ///< 2048 cycles
    SysctrlPllStableCycle4096 = 5u, ///< 4096 cycles
    SysctrlPllStableCycle8192 = 6u, ///< 8192 cycles
    SysctrlPllStableCycle16384 = 7u, ///< 16384 cycles
}en_sysctrl_pll_cycle_t;

/**
********************************************************************************
** \brief PLL input frequency range type definition
****************************************************************************/
typedef enum en_sysctrl_pll_infreq
{
    SysctrlPllInFreq4_6MHz = 0u, ///< 4~16MHz
    SysctrlPllInFreq6_12MHz = 1u, ///< 6~12MHz
    SysctrlPllInFreq12_20MHz = 2u, ///< 12~20MHz
    SysctrlPllInFreq20_24MHz = 3u, ///< 20~24MHz
}en_sysctrl_pll_infreq_t;

/**
********************************************************************************
** \brief PLL output frequency range type definition
****************************************************************************/
typedef enum en_sysctrl_pll_outfreq
{
    SysctrlPllOutFreq8_12MHz = 0u, ///< 8~12MHz
    SysctrlPllOutFreq12_18MHz = 1u, ///< 12~18MHz
    SysctrlPllOutFreq18_24MHz = 2u, ///< 18~24MHz
    SysctrlPllOutFreq24_36MHz = 3u, ///< 24~36MHz
    SysctrlPllOutFreq36_48MHz = 4u, ///< 36~48MHz
}en_sysctrl_pll_outfreq_t;

/**
************************************************************************************
** \brief PLL input clock source type definition
****************************************************************************/
typedef enum en_sysctrl_pll_clksource
{
    SysctrlPllXthXtal = 0u, ///< XTH crystal oscillator input clock
    SysctrlPllXthIn = 1u, ///< XTH slave port input clock
    SysctrlPllRch = 3u, ///< RCH clock
}en_sysctrl_pll_clksource_t;

/**
********************************************************************************
** \brief PLL input clock source type definition
************************************************************************/
typedef enum en_sysctrl_pll_mul
{
    SysctrlPllMul2 = 2u, ///< 2x frequency
    SysctrlPllMul3 = 3u, ///< 3x frequency
    SysctrlPllMul4 = 4u, ///< 4x frequency
    SysctrlPllMul5 = 5u, ///< 5x frequency
    SysctrlPllMul6 = 6u, ///< 6x frequency
    SysctrlPllMul7 = 7u, ///< 7x frequency
    SysctrlPllMul8 = 8u, ///< 8x
    SysctrlPllMul9 = 9u, ///< 9x
    SysctrlPllMul10 = 10u, ///< 10x
    SysctrlPllMul11 = 11u, ///< 11x
    SysctrlPllMul12 = 12u, ///< 12x
}en_sysctrl_pll_mul_t;

/**
********************************************************************************
** \brief HCLK clock division coefficient type definition
************************************************************************/
typedef enum en_sysctrl_hclk_div
{
    SysctrlHclkDiv1 = 0u, ///< SystemClk
    SysctrlHclkDiv2 = 1u, ///< SystemClk/2 
    SysctrlHclkDiv4 = 2u, ///< SystemClk/4 
    SysctrlHclkDiv8 = 3u, ///< SystemClk/8 
    SysctrlHclkDiv16 = 4u, ///< SystemClk/16 
    SysctrlHclkDiv32 = 5u, ///< SystemClk/32 
    SysctrlHclkDiv64 = 6u, ///< SystemClk/64 
    SysctrlHclkDiv128 = 7u, ///< SystemClk/128
}en_sysctrl_hclk_div_t;

/** 
******************************************************************************* 
** \brief PCLK frequency division coefficient 
******************************************************************************/
typedef enum en_sysctrl_pclk_div
{ 
    SysctrlPclkDiv1 = 0u, ///< HCLK 
    SysctrlPclkDiv2 = 1u, ///< HCLK/2 
    SysctrlPclkDiv4 = 2u, ///< HCLK/4 
    SysctrlPclkDiv8 = 3u, ///< HCLK/8
}en_sysctrl_pclk_div_t;

/** 
******************************************************************************* 
** Brief RTC High-Speed Clock Compensation Clock Frequency Data Type Definition
**************************************************************************/
typedef enum en_sysctrl_rtc_adjust
{
    SysctrlRTC4MHz = 0u, ///< 4MHz
    SysctrlRTC6MHz = 1u, ///< 6MHz
    SysctrlRTC8MHz = 2u, ///< 8MHz
    SysctrlRTC12MHz = 3u, ///< 12MHz
    SysctrlRTC16MHz = 4u, ///< 16MHz
    SysctrlRTC20MHz = 5u, ///< 20MHz
    SysctrlRTC24MHz = 6u, ///< 24MHz
    SysctrlRTC32MHz = 7u, ///< 32MHz
}en_sysctrl_rtc_adjust_t;

/**
*******************************************************************************
** \brief System Control Module Other Function Data Type Definitions
**************************************************************************/
typedef enum en_sysctrl_func
{
    SysctrlEXTHEn = 1u, ///< Enable external high-speed clock input from input pin
    SysctrlEXTLEn = 2u, ///< Enable external low-speed clock input from input pin
    SysctrlXTLAlwaysOnEn = 3u, ///< After enabling, XTL_EN can only be set
    SysctrlClkFuncRTCLpmEn = 5u, ///< Enable RTC low-power mode
    SysctrlCMLockUpEn = 6u, ///< After enabling, the CPU will reset the MCU if it executes an invalid instruction
    SysctrlSWDUseIOEn = 8u, ///< Set the SWD port to an IO function.
}en_sysctrl_func_t;

/**
****************************************************************************
** \brief USB clock select data type definition
********************************************************************/
typedef enum en_sysctrl_usbclk_sel
{
    SysctrlUsbClkRch48M = 0u, ///<USB clock selects RCH48M
    SysctrlUsbClkPll = 1u, ///<USB clock selects PLL
}en_sysctrl_usbclk_sel_t;

/**
************************************************************************************
** \brief Timer clock select data type definition
************************************************************************/
typedef enum en_sysctrl_timer_pllclk_sel
{
    SysctrlTimerClkPll = 0u, ///<When the timer uses the PLL, use the system clock at the same frequency.
    SysctrlTimerClkPll2 = 1u, ///<When the timer uses the PLL, use the system clock at 2x frequency.
}en_sysctrl_timer_pllclk_sel_t;

/**
********************************************************************************
** \brief Peripheral clock gate switch type enumeration
****************************************************************************/
typedef enum en_sysctrl_peripheral_gate
{
    SysctrlPeripheralUart0 = 0u, ///<Serial port 0
    SysctrlPeripheralUart1 = 1u, ///<Serial port 1
    SysctrlPeripheralLpUart0 = 2u, ///< Low-power serial port 0
    SysctrlPeripheralLpUart1 = 3u, ///< Low-power serial port 1
    SysctrlPeripheralI2c0 = 4u, ///< I2C0
    SysctrlPeripheralI2c1 = 5u, ///< I2C1
    SysctrlPeripheralSpi0 = 6u, ///< SPI0
    SysctrlPeripheralSpi1 = 7u, ///< SPI1
    SysctrlPeripheralBaseTim = 8u, ///< Basic timer TIM0/1/2
    SysctrlPeripheralLpTim0 = 9u, ///< Low-power timer 0
    SysctrlPeripheralAdvTim = 10u, ///< Advanced timer TIM4/5/6
    SysctrlPeripheralTim3 = 11u, ///< Timer 3
    SysctrlPeripheralOpa = 13u, ///< OPA
    SysctrlPeripheralPca = 14u, ///< Programmable Counter Array
    SysctrlPeripheralWdt = 15u, ///< Watchdog
    SysctrlPeripheralAdcBgr = 16u, ///< ADC & BGR
    SysctrlPeripheralVcLvd = 17u, ///< VC & LVD
    SysctrlPeripheralRng = 18u, ///< RNG
    SysctrlPeripheralPcnt = 19u, ///< PCNT
    SysctrlPeripheralRtc = 20u, ///< RTC
    SysctrlPeripheralTrim = 21u, ///< Clock Calibration
    SysctrlPeripheralLcd = 22u, ///< LCD
    SysctrlPeripheralTick = 24u, ///< System Timer
    SysctrlPeripheralSwd = 25u, ///< SWD
    SysctrlPeripheralCrc = 26u, ///< CRC
    SysctrlPeripheralAes = 27u, ///< AES
    SysctrlPeripheralGpio = 28u, ///< GPIO
    SysctrlPeripheralDma = 29u, ///< DMA
    SysctrlPeripheralHdiv = 30u, ///< Divider
    SysctrlPeripheralFlash = 31u, ///< Flash
    SysctrlPeripheralUsb = 32u, ///< USB
    SysctrlPeripheralCan = 33u, ///< CAN
    SysctrlPeripheralCts = 34u, ///< CTS
    SysctrlPeripheralDac = 35u, ///< DAC
    SysctrlPeripheralLpTim1 = 36u, ///< Low-power timer 1
    SysctrlPeripheralI2s0 = 37u, ///< I2S0
    SysctrlPeripheralI2s1 = 38u, ///< I2S1
    SysctrlPeripheralUart2 = 40u, ///< UART2
    SysctrlPeripheralUart3 = 41u, ///< UART3
}en_sysctrl_peripheral_gate_t;

/**
****************************************************************************
** \brief Clock initialization configuration structure definition
************************************************************************/
typedef struct
{
    en_sysctrl_clk_source_t enClkSrc; ///< Clock source selection
    en_sysctrl_hclk_div_t enHClkDiv; ///< HCLK division coefficient
    en_sysctrl_pclk_div_t enPClkDiv; ///< PCLK division coefficient
}stc_sysctrl_clk_cfg_t;

/**
********************************************************************************
** \brief Clock initialization configuration structure definition
************************************************************************/
typedef struct
{
    en_sysctrl_pll_infreq_t enInFreq; ///< PLL input clock frequency range selection
    en_sysctrl_pll_outfreq_t enOutFreq; ///< PLL output clock frequency range selection
    en_sysctrl_pll_clksource_t enPllClkSrc; ///< PLL input clock source selection
    en_sysctrl_pll_mul_t enPllMul; ///< PLL multiplication factor selection
}stc_sysctrl_pll_cfg_t;

/******************************************************************************
* Global variable declarations ('extern', definition in C source)
**********************************************************************************/

/******************************************************************************
* Global function prototypes (definition in C source)
******************************************************************************/
///< System clock initialization API: Used to initialize the main clock and peripheral clocks after power-up and before the system starts operating.
///< Note 1: Before using this initialization function, you must prioritize setting the TRIM value of the target internal clock source or the frequency range of the external clock source, depending on the system.
///< Note 2: The frequency range of XTH and XTL must be determined by the external crystal oscillator.
///< Note 3: This driver defaults to the macro definitions: SYSTEM_XTH = 8MHz, SYSTEM_XTL = 32768Hz. If using a different external crystal oscillator, you must modify the values of these two macro definitions.
en_result_t Sysctrl_ClkInit(stc_sysctrl_clk_cfg_t *pstcCfg);

///< System clock deinitialization API: Restores to power-on defaults -> PCLK = HCLK = SystemClk = RCH4MHz
en_result_t Sysctrl_ClkDeInit(void);

///< Basic function settings for the system clock module
///< Note: Before enabling the desired clock source, you must first set the TRIM value of the target internal clock source or the frequency range of the external clock source.
en_result_t Sysctrl_ClkSourceEnable(en_sysctrl_clk_source_t enSource, boolean_t bFlag);

///< External crystal oscillator drive configuration: After system initialization (Sysctrl_ClkInit()), you can configure the external crystal oscillator's drive capability as needed. The default clock initialization (Sysctrl_ClkInit()) is set to the maximum value.
en_result_t Sysctrl_XTHDriverCfg(en_sysctrl_xtal_driver_t enDriver);
en_result_t Sysctrl_XTLDriverCfg(en_sysctrl_xtl_amp_t enAmp, en_sysctrl_xtal_driver_t enDriver);

///<Clock stabilization period setting: After system initialization Sysctrl_ClkInit(), the clock stabilization period after startup can be configured as needed. The default is the maximum value.
en_result_t Sysctrl_SetXTHStableTime(en_sysctrl_xth_cycle_t enCycle);
en_result_t Sysctrl_SetRCLStableTime(en_sysctrl_rcl_cycle_t enCycle);
en_result_t Sysctrl_SetXTLStableTime(en_sysctrl_xtl_cycle_t enCycle);
en_result_t Sysctrl_SetPLLStableTime(en_sysctrl_pll_cycle_t enCycle);

///< System clock source switching and system clock update: Use this function if you need to switch the main clock source after the system clock is initialized with Sysctrl_ClkInit().
///< Before and after clock switching, the Flash read wait period must be set according to the target frequency value. The insertion period can be configured as 0, 1, or 2.
///< Caution!!!: When the HCLK is greater than 24MHz, the Flash wait period insertion must be at least 1, otherwise unknown errors may occur during program execution.
en_result_t Sysctrl_SysClkSwitch(en_sysctrl_clk_source_t enSource);

///< Clock source frequency setting: Set the frequency value of each clock source individually according to the system situation.
///< Before setting the clock frequency, the Flash read wait period must be set according to the target frequency value. The insertion period can be configured as 0, 1, or 2.
///< The XTL clock is determined by an external crystal oscillator and does not require configuration.
en_result_t Sysctrl_SetRCHTrim(en_sysctrl_rch_freq_t enRCHFreq);
en_result_t Sysctrl_SetRCLTrim(en_sysctrl_rcl_freq_t enRCLFreq);
en_result_t Sysctrl_SetXTHFreq(en_sysctrl_xth_freq_t enXTHFreq);
en_result_t Sysctrl_SetPLLFreq(stc_sysctrl_pll_cfg_t *pstcPLLCfg);

///< Clock frequency division setting: Set the HCLK and PCLK allocation values individually according to the system situation;
en_result_t Sysctrl_SetHCLKDiv(en_sysctrl_hclk_div_t enHCLKDiv);
en_result_t Sysctrl_SetPCLKDiv(en_sysctrl_pclk_div_t enPCLKDiv);

///< Clock Frequency Acquisition: Gets the current HCLK and PCLK frequency values based on system requirements.
uint32_t Sysctrl_GetHClkFreq(void);
uint32_t Sysctrl_GetPClkFreq(void);

///< Peripheral Gate Switch/Status Acquisition: Used to control the enabling of peripheral modules. Before using a module's functions, the module's clock gate must be enabled.
en_result_t Sysctrl_SetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral, boolean_t bFlag);
boolean_t Sysctrl_GetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral);

///< System Function Configuration: Used to set other system-related special functions;
en_result_t Sysctrl_SetFunc(en_sysctrl_func_t enFunc, boolean_t bFlag);

///< RTC High-Speed Clock Compensation: Used to set the frequency compensation for the RTC high-speed clock.
en_result_t Sysctrl_SetRTCAdjustClkFreq(en_sysctrl_rtc_adjust_t enRtcAdj);

///< USB Clock Selection
void Sysctrl_UsbClkSel(en_sysctrl_usbclk_sel_t enUsbClk);

///< Clock Selection when the timer uses the PLL
void Sysctrl_TimerPllClkSel(en_sysctrl_timer_pllclk_sel_t enTimClk);

//@} // Sysctrl Group

#ifdef __cplusplus
#endif

#endif /* __SYSCTRL_H__ */
/************************************************************************************ 
* EOF (not truncated) 
******************************************************************************/

