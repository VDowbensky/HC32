/*******************************************************************************
* Copyright (C) 2018, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer: 
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/******************************************************************************/
/** \file sysctrl.h
 **
 ** Headerfile for SYSCTRL functions
 ** @link SYSCTRL Group Some description @endlink 
 **
 ** History:
 **   - 2018-04-15   Lux     First Version
 **
 ******************************************************************************/

#ifndef __SYSCTRL_H__
#define __SYSCTRL_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l136.h"

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
 ******************************************************************************/
//#define SYSTEM_XTH            32*1000*1000u     //The default is 32MHz, the specific value should be modified according to the actual system.
//#define SYSTEM_XTH            8*1000*1000u
#define SYSTEM_XTH						11059200ul
#define SYSTEM_XTL            32768u            //The default is 32768Hz, the specific value should be modified according to the actual system.
 
/**
 *******************************************************************************
 ** \brief System clock input source type definition
 ** \note
 ******************************************************************************/
typedef enum en_sysctrl_clk_source
{
    SysctrlClkRCH  = 0u,               ///< Internal high speed clock
    SysctrlClkXTH  = 1u,               ///< External high speed clock
    SysctrlClkRCL  = 2u,               ///< Internal low speed clock
    SysctrlClkXTL  = 3u,               ///< External low speed clock
    SysctrlClkPLL  = 4u,               ///< PLL clock
}en_sysctrl_clk_source_t;

/**
 *******************************************************************************
 ** \brief RCH frequency value enumeration type definition
 ******************************************************************************/
typedef enum en_sysctrl_rch_freq
{
    SysctrlRchFreq4MHz     = 0u,               ///< 4MHz
    SysctrlRchFreq8MHz     = 1u,               ///< 8MHz
    SysctrlRchFreq16MHz    = 2u,               ///< 16MHz
    SysctrlRchFreq22_12MHz = 3u,               ///< 22.12MHz
    SysctrlRchFreq24MHz    = 4u,               ///< 24MHz
}en_sysctrl_rch_freq_t;

/**
 *******************************************************************************
 ** \brief XTAL drive capability type definition
 ******************************************************************************/
typedef enum en_sysctrl_xtal_driver
{
    SysctrlXtalDriver0 = 0u,                ///< Weakest drive capability
    SysctrlXtalDriver1 = 1u,                ///< Weak drive capability
    SysctrlXtalDriver2 = 3u,                ///< General drive capability
    SysctrlXtalDriver3 = 3u,                ///< Strongest driving ability
}en_sysctrl_xtal_driver_t;

/**
 *******************************************************************************
 ** \brief XTH frequency value range selection type definition
 ******************************************************************************/
typedef enum en_sysctrl_xth_freq
{
    SysctrlXthFreq4_6MHz   = 0u,                ///< 4~6MHz
    SysctrlXthFreq6_12MHz  = 1u,                ///< 6~12MHz
    SysctrlXthFreq12_20MHz = 2u,                ///< 12~20MHz
    SysctrlXthFreq20_32MHz = 3u,                ///< 20~32MHz
}en_sysctrl_xth_freq_t;

/**
 *******************************************************************************
 ** \brief XTH clock stability period type definition
 ******************************************************************************/
typedef enum en_sysctrl_xth_cycle
{
    SysctrlXthStableCycle256   = 0u,              ///< 256 cycles
    SysctrlXthStableCycle1024  = 1u,              ///< 1024 cycles
    SysctrlXthStableCycle4096  = 2u,              ///< 4096 cycles
    SysctrlXthStableCycle16384 = 3u,              ///< 16384 cycles
}en_sysctrl_xth_cycle_t;

/**
 *******************************************************************************
 ** \brief RCL frequency value enumeration type definition
 ******************************************************************************/
typedef enum en_sysctrl_rcl_freq
{
    SysctrlRclFreq32768    = 0u,               ///< 32.768KHz
    SysctrlRclFreq38400    = 1u,               ///< 38.4KHz
}en_sysctrl_rcl_freq_t;

/**
 *******************************************************************************
 ** \brief RCL clock stabilization period number type definition
 ******************************************************************************/
typedef enum en_sysctrl_rcl_cycle
{
    SysctrlRclStableCycle4   = 0u,                  ///< 4 cycles
    SysctrlRclStableCycle16  = 1u,                  ///< 16 cycles
    SysctrlRclStableCycle64  = 2u,                  ///< 64 cycles
    SysctrlRclStableCycle256 = 3u,                  ///< 256 cycles
}en_sysctrl_rcl_cycle_t;

/**
 *******************************************************************************
 ** \brief XTL clock stability period type definition
 ******************************************************************************/
typedef enum en_sysctrl_xtl_cycle
{
    SysctrlXtlStableCycle256   = 0u,                  ///< 256 cycles
    SysctrlXtlStableCycle1024  = 1u,                  ///< 1024 cycles
    SysctrlXtlStableCycle4096  = 2u,                  ///< 4096 cycles
    SysctrlXtlStableCycle16384 = 3u,                  ///< 16384 cycles
}en_sysctrl_xtl_cycle_t;

/**
 *******************************************************************************
 ** \brief XTL crystal amplitude enumeration type definition
 ******************************************************************************/
typedef enum en_sysctrl_xtl_amp
{
    SysctrlXtlAmp0 = 0u,                ///< Minimum amplitude
    SysctrlXtlAmp1 = 1u,                ///< Small amplitude
    SysctrlXtlAmp2 = 2u,                ///< General amplitude
    SysctrlXtlAmp3 = 3u,                ///< Maximum amplitude
}en_sysctrl_xtl_amp_t;

/**
 *******************************************************************************
 ** \brief PLL clock stabilization period type definition
 ******************************************************************************/
typedef enum en_sysctrl_pll_cycle
{
    SysctrlPllStableCycle128   = 0u,                  ///< 128cycles
    SysctrlPllStableCycle256   = 1u,                  ///< 256cycles
    SysctrlPllStableCycle512   = 2u,                  ///< 512cycles
    SysctrlPllStableCycle1024  = 3u,                  ///< 1024cycles
    SysctrlPllStableCycle2048  = 4u,                  ///< 2048cycles
    SysctrlPllStableCycle4096  = 5u,                  ///< 4096cycles
    SysctrlPllStableCycle8192  = 6u,                  ///< 8192cycles
    SysctrlPllStableCycle16384 = 7u,                  ///< 16384cycles    
}en_sysctrl_pll_cycle_t;

/**
 *******************************************************************************
 ** \brief PLL input frequency range type definition
 ******************************************************************************/
typedef enum en_sysctrl_pll_infreq
{
    SysctrlPllInFreq4_6MHz   = 0u,                  ///< 4~16MHz
    SysctrlPllInFreq6_12MHz  = 1u,                  ///< 6~12MHz
    SysctrlPllInFreq12_20MHz = 2u,                  ///< 12~20MHz
    SysctrlPllInFreq20_24MHz = 3u,                  ///< 20~24MHz  
}en_sysctrl_pll_infreq_t;

/**
 *******************************************************************************
 ** \brief PLL output frequency range type definition
 ******************************************************************************/
typedef enum en_sysctrl_pll_outfreq
{
    SysctrlPllOutFreq8_12MHz  = 0u,                 ///< 8~12MHz
    SysctrlPllOutFreq12_18MHz = 1u,                 ///< 12~18MHz
    SysctrlPllOutFreq18_24MHz = 2u,                 ///< 18~24MHz
    SysctrlPllOutFreq24_36MHz = 3u,                 ///< 24~36MHz
    SysctrlPllOutFreq36_48MHz = 4u,                 ///< 36~48MHz
}en_sysctrl_pll_outfreq_t;

/**
 *******************************************************************************
 ** \brief PLL input clock source type definition
 ******************************************************************************/
typedef enum en_sysctrl_pll_clksource
{
    SysctrlPllXthXtal   = 0u,                  ///< XTH crystal input clock
    SysctrlPllXthPd00In = 2u,                  ///< XTH clock input from port PD00
    SysctrlPllRch       = 3u,                  ///< RCH clock
}en_sysctrl_pll_clksource_t;

/**
 *******************************************************************************
 ** \brief PLL input clock source type definition
 ******************************************************************************/
typedef enum en_sysctrl_pll_mul
{
    SysctrlPllMul1  = 1u,                   ///< 1 Multiplier
    SysctrlPllMul2  = 2u,                   ///< 2 Multiplier
    SysctrlPllMul3  = 3u,                   ///< 3 Multiplier
    SysctrlPllMul4  = 4u,                   ///< 4 Multiplier
    SysctrlPllMul5  = 5u,                   ///< 5 Multiplier
    SysctrlPllMul6  = 6u,                   ///< 6 Multiplier
    SysctrlPllMul7  = 7u,                   ///< 7 Multiplier
    SysctrlPllMul8  = 8u,                   ///< 8 Multiplier
    SysctrlPllMul9  = 9u,                   ///< 9 Multiplier
    SysctrlPllMul10 = 10u,                  ///< 10 Multiplier
    SysctrlPllMul11 = 11u,                  ///< 11 Multiplier
    SysctrlPllMul12 = 12u,                  ///< 12 Multiplier
}en_sysctrl_pll_mul_t;

/**
 *******************************************************************************
 ** \brief HCLK clock division factor type definition
 ******************************************************************************/
typedef enum en_sysctrl_hclk_div
{
    SysctrlHclkDiv1   = 0u,              ///< SystemClk
    SysctrlHclkDiv2   = 1u,              ///< SystemClk/2
    SysctrlHclkDiv4   = 2u,              ///< SystemClk/4
    SysctrlHclkDiv8   = 3u,              ///< SystemClk/8
    SysctrlHclkDiv16  = 4u,              ///< SystemClk/16
    SysctrlHclkDiv32  = 5u,              ///< SystemClk/32
    SysctrlHclkDiv64  = 6u,              ///< SystemClk/64
    SysctrlHclkDiv128 = 7u,              ///< SystemClk/128
}en_sysctrl_hclk_div_t;

/**
 *******************************************************************************
 ** \brief PCLK division factor
 ******************************************************************************/
typedef enum en_sysctrl_pclk_div
{
    SysctrlPclkDiv1 = 0u,                ///< HCLK
    SysctrlPclkDiv2 = 1u,                ///< HCLK/2
    SysctrlPclkDiv4 = 2u,                ///< HCLK/4
    SysctrlPclkDiv8 = 3u,                ///< HCLK/8
}en_sysctrl_pclk_div_t;

/**
 *******************************************************************************
 ** \brief RTC high speed clock compensation clock frequency data type definition
 ******************************************************************************/
typedef enum en_sysctrl_rtc_adjust
{
    SysctrlRTC4MHz  = 0u,                ///< 4MHz
    SysctrlRTC6MHz  = 1u,                ///< 6MHz
    SysctrlRTC8MHz  = 2u,                ///< 8MHz
    SysctrlRTC12MHz = 3u,                ///< 12MHz
    SysctrlRTC16MHz = 4u,                ///< 16MHz
    SysctrlRTC20MHz = 5u,                ///< 20MHz
    SysctrlRTC24MHz = 6u,                ///< 24MHz
    SysctrlRTC32MHz = 7u,                ///< 32MHz
}en_sysctrl_rtc_adjust_t;

/**
 *******************************************************************************
 ** \brief System control module other function data type definition
 ******************************************************************************/
typedef enum en_sysctrl_func
{
    SysctrlWkupByRCHEn      =0u,                    ///< Use RCH clock when waking up
    SysctrlEXTHEn           =1u,                    ///< Enable external high-speed clock input from input pin PD00
    SysctrlEXTLEn           =2u,                    ///< Enable external low speed clock input from input pin PC14
    SysctrlXTLAlwaysOnEn    =3u,                    ///< XTL_EN can only be set after enabling
    SysctrlClkFuncRTCLpmEn  =4u,                    ///< Enable RTC low power mode
    SysctrlCMLockUpEn       =5u,                    ///< After the CPU is executed, an invalid instruction will reset the MCU.
    SysctrlSWDUseIOEn       =6u,                    ///< SWD port is set to IO function
}en_sysctrl_func_t;

/**
 *******************************************************************************
 ** \brief Peripheral clock gating switch type enumeration
 ******************************************************************************/
typedef enum en_sysctrl_peripheral_gate
{
    SysctrlPeripheralUart0      = 0u,       ///< Serial port0
    SysctrlPeripheralUart1      = 1u,       ///< Serial port1
    SysctrlPeripheralLpUart0    = 2u,       ///< Low power Serial port0
    SysctrlPeripheralLpUart1    = 3u,       ///< Low power Serial port1
    SysctrlPeripheralI2c0       = 4u,       ///< I2C0
    SysctrlPeripheralI2c1       = 5u,       ///< I2C1
    SysctrlPeripheralSpi0       = 6u,       ///< SPI0
    SysctrlPeripheralSpi1       = 7u,       ///< SPI1
    SysctrlPeripheralBTim       = 8u,       ///< Basic timer
    SysctrlPeripheralLpTim      = 9u,       ///< Low power Timer
    SysctrlPeripheralAdvTim     = 10u,      ///< Advanced timer
    SysctrlPeripheralTim3       = 11u,      ///< Timer 3
    SysctrlPeripheralOpa        = 13u,      ///< OPA
    SysctrlPeripheralPca        = 14u,      ///< Programmable counting array
    SysctrlPeripheralWdt        = 15u,      ///< Watchdog
    SysctrlPeripheralAdcBgr     = 16u,      ///< ADC&BGR
    SysctrlPeripheralVcLvd      = 17u,      ///< Voltage comparison and low voltage detection
    SysctrlPeripheralRng        = 18u,      ///< RNG
    SysctrlPeripheralPcnt       = 19u,      ///< PCNT
    SysctrlPeripheralRtc        = 20u,      ///< RTC
    SysctrlPeripheralTrim       = 21u,      ///< Clock calibration
    SysctrlPeripheralLcd        = 22u,      ///< LCD
    SysctrlPeripheralTick       = 24u,      ///< System timer
    SysctrlPeripheralSwd        = 25u,      ///< SWD
    SysctrlPeripheralCrc        = 26u,      ///< CRC
    SysctrlPeripheralAes        = 27u,      ///< AES
    SysctrlPeripheralGpio       = 28u,      ///< GPIO
    SysctrlPeripheralDma        = 29u,      ///< DMA
    SysctrlPeripheralDiv        = 30u,      ///< Divider
    SysctrlPeripheralFlash      = 31u,      ///< Flash
}en_sysctrl_peripheral_gate_t;

/**
 *******************************************************************************
 ** \brief Clock initialization configuration structure definition
 ******************************************************************************/
typedef struct
{
    en_sysctrl_clk_source_t  enClkSrc;       ///< Clock source selection
    en_sysctrl_hclk_div_t    enHClkDiv;      ///< HCLK division factor
    en_sysctrl_pclk_div_t    enPClkDiv;      ///< PCLK division factor
}stc_sysctrl_clk_config_t;

/**
 *******************************************************************************
 ** \brief Clock initialization configuration structure definition
 ******************************************************************************/
typedef struct
{
    en_sysctrl_pll_infreq_t    enInFreq;        ///< PLL input clock frequency range selection
    en_sysctrl_pll_outfreq_t   enOutFreq;       ///< PLL output clock frequency range selection
    en_sysctrl_pll_clksource_t enPllClkSrc;     ///< PLL input clock source selection
    en_sysctrl_pll_mul_t       enPllMul;        ///< PLL Multiplier coefficient selection
}stc_sysctrl_pll_config_t;

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
///< System clock initialization API: used to initialize the main frequency and peripheral clock before the system works after power-on;
///< Note 1: Before using this initialization function, it is necessary to set the TRIM value of the target internal clock source or the frequency range of the external clock source according to the system.
///< Note 2: The frequency range setting of XTH and XTL needs to be determined according to the external crystal.
///< Note 3: This driver default macro definition: SYSTEM_XTH=32MHz, SYSTEM_XTL=32768Hz. If other external crystals are used, the values defined by these two macros must be modified.
en_result_t Sysctrl_ClkInit(stc_sysctrl_clk_config_t *pstcCfg);

///< System clock to initialize API: Restore to power-on default state -> PCLK = HCLK = SystemClk = RCH4MHz
en_result_t Sysctrl_ClkDeInit(void);

///< Basic function settings of the system clock module
///< Note: Before enabling the clock source to be used, the TRIM value of the target internal clock source or the frequency range of the external clock source must be set first.
en_result_t Sysctrl_ClkSourceEnable(en_sysctrl_clk_source_t enSource, boolean_t bFlag);

///<External crystal drive configuration: After the system initializes Sysctrl_ClkInit(), the drive capability of the external crystal can be configured as needed. 
//The clock initialization Sysctrl_ClkInit() defaults to the maximum value;
en_result_t Sysctrl_XTHDriverConfig(en_sysctrl_xtal_driver_t enDriver);
en_result_t Sysctrl_XTLDriverConfig(en_sysctrl_xtl_amp_t enAmp, en_sysctrl_xtal_driver_t enDriver);

///<Clock stability period setting: After the system initializes Sysctrl_ClkInit(), you can configure the stability after the clock is turned on as needed. 
//The default is the maximum value.
en_result_t Sysctrl_SetXTHStableTime(en_sysctrl_xth_cycle_t enCycle);
en_result_t Sysctrl_SetRCLStableTime(en_sysctrl_rcl_cycle_t enCycle);
en_result_t Sysctrl_SetXTLStableTime(en_sysctrl_xtl_cycle_t enCycle);
en_result_t Sysctrl_SetPLLStableTime(en_sysctrl_pll_cycle_t enCycle);

///<The system clock source switches and updates the system clock: if you need to switch the clock source after the system clock initializes Sysctrl_ClkInit(), use this function;
///< Before and after the clock switch, the flash read wait period must be set according to the target frequency value. The configurable insertion period is 0, 1, 2,
///< Note!!!: When HCLK is greater than 24MHz, the FLASH wait period insertion must be at least 1, otherwise the program may generate an unknown error.
en_result_t Sysctrl_SysClkSwitch(en_sysctrl_clk_source_t enSource);

///< Clock source frequency setting: separately set the frequency value of different clock sources according to the system conditions.;
///< Before the clock frequency is set, the flash read wait period must be set according to the target frequency value. The configurable insertion period is 0, 1, 2,
///< The XTL clock is determined by the external crystal and does not need to be set.
en_result_t Sysctrl_SetRCHTrim(en_sysctrl_rch_freq_t enRCHFreq);
en_result_t Sysctrl_SetRCLTrim(en_sysctrl_rcl_freq_t enRCLFreq);
en_result_t Sysctrl_SetXTHFreq(en_sysctrl_xth_freq_t enXTHFreq);
en_result_t Sysctrl_SetPLLFreq(stc_sysctrl_pll_config_t *pstcPLLCfg);

///< Clock division setting: According to the system situation, the assigned values of HCLK and PCLK are set separately;
en_result_t Sysctrl_SetHCLKDiv(en_sysctrl_hclk_div_t enHCLKDiv);
en_result_t Sysctrl_SetPCLKDiv(en_sysctrl_pclk_div_t enPCLKDiv);

///< Clock frequency acquisition: According to the system requirements, obtain the current HCLK and PCLK frequency values.
uint32_t Sysctrl_GetHClkFreq(void);
uint32_t Sysctrl_GetPClkFreq(void);

///< Peripheral Gating Switch/Status Acquisition: Used to control the enabling of peripheral modules. 
//Before using the function of this module, the gated clock of the module must be enabled;
en_result_t Sysctrl_SetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral, boolean_t bFlag);
boolean_t   Sysctrl_GetPeripheralGate(en_sysctrl_peripheral_gate_t enPeripheral);

///< System function configuration: used to set other system related special functions;
en_result_t Sysctrl_SetFunc(en_sysctrl_func_t enFunc, boolean_t bFlag);

///< RTC high speed clock compensation: used to set the frequency compensation under RTC high speed clock
en_result_t Sysctrl_SetRTCAdjustClkFreq(en_sysctrl_rtc_adjust_t enRtcAdj);

//@} // Sysctrl Group

#ifdef __cplusplus
#endif

#endif /* __SYSCTRL_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


