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
* @file main.c 
* 
* @brief Source file for ADC example 
* 
* @author MADS Team 
* ******************************************************************************/

/****************************************************************************** 
* Include files 
******************************************************************************/
#include "adc.h"
#include "gpio.h"
#include "bgr.h"
/****************************************************************************** 
* Local pre-processor symbols/macros ('#define') 
******************************************************************************/


/****************************************************************************** 
* Global variable definitions (declared in header file with 'extern') 
******************************************************************************/
volatile uint32_t u32AdcRestult0;
volatile uint32_t u32AdcRestult0_1;
volatile uint32_t u32AdcRestult2;
volatile uint32_t u32AdcRestult5;
/****************************************************************************** 
* Local type definitions ('typedef') 
******************************************************************************/

/****************************************************************************** 
* Local function prototypes ('static') 
******************************************************************************/

/****************************************************************************** 
* Local variable definitions ('static') * 
******************************************************************************/

/**************************************************************************** 
* Function implementation - global ('extern') and local ('static')
**************************************************************************/
void App_AdcPortInit(void);
void App_AdcInit(void);
void App_AdcJqrCfg(void);

/**
******************************************************************************
** \brief Main function of project
**
** \return uint32_t return value, if needed
**
** This sample
**
**************************************************************************/
int32_t main(void)
{
  ///< ADC sampling port initialization
  App_AdcPortInit();

  ///< ADC module initialization
  App_AdcInit();

  ///< ADC queue scan function configuration
  App_AdcJqrCfg();

  while(1)
  {
    ;
  }
}

///< ADC interrupt service function
void Adc_IRQHandler(void)
{
  if(TRUE == Adc_GetIrqStatus(AdcMskIrqJqr))
  {
    Adc_ClrIrqStatus(AdcMskIrqJqr);

    u32AdcRestult0 = Adc_GetJqrResult(AdcJQRCH0MUX);
    u32AdcRestult2 = Adc_GetJqrResult(AdcJQRCH1MUX);
    u32AdcRestult5 = Adc_GetJqrResult(AdcJQRCH2MUX);
    u32AdcRestult0_1 = Adc_GetJqrResult(AdcJQRCH3MUX);

    Adc_JQR_Stop();
  }
}

///< ADC sampling port initialization
void App_AdcPortInit(void)
{
    ///< Enable the ADC/BGR GPIO peripheral clock
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

    Gpio_SetAnalogMode(GpioPortA, GpioPin0); //PA00 (AIN0)
    Gpio_SetAnalogMode(GpioPortA, GpioPin2); //PA02 (AIN2)
    Gpio_SetAnalogMode(GpioPortA, GpioPin5); //PA05 (AIN5)
}

///< Initialize the ADC module
void App_AdcInit(void)
{
    stc_adc_cfg_t stcAdcCfg;

    DDL_ZERO_STRUCT(stcAdcCfg);
    Sysctrl_SetPeripheralGate(SysctrlPeripheralAdcBgr, TRUE);
    Bgr_BgrEnable(); ///< Enable BGR
    ///< ADC initialization configuration
    stcAdcCfg.enAdcMode = AdcScanMode; ///< Sampling mode - Scan
    stcAdcCfg.enAdcClkDiv = AdcMskClkDiv1; ///< Sampling divider - 1
    stcAdcCfg.enAdcSampCycleSel = AdcMskSampCycle8Clk; ///< Sampling cycle count - 8
    stcAdcCfg.enAdcRefVolSel = AdcMskRefVolSelAVDD; ///< Reference voltage selection - VCC
    stcAdcCfg.enAdcOpBuf = AdcMskBufDisable; ///< OP BUF configuration - Off
    stcAdcCfg.enInRef = AdcMskInRefDisable; ///< Internal reference voltage enable - off
    stcAdcCfg.enAdcAlign = AdcAlignRight; ///< Conversion result alignment - right
    Adc_Init(&stcAdcCfg);
}
///< ADC queue-jump scan function configuration
void App_AdcJqrCfg(void)
{
    stc_adc_jqr_cfg_t stcAdcJqrCfg;

    DDL_ZERO_STRUCT(stcAdcJqrCfg);

    ///< Queue-jump scan mode function and channel configuration
    ///< Note: In scan mode, when the number of conversions is configured as n, the configuration range of the conversion channel must be [JQRCH(0)MUX,JQRCH(n-1)MUX]
    stcAdcJqrCfg.bJqrDmaTrig = FALSE; 
    stcAdcJqrCfg.u8JqrCnt = 4; 
    Adc_JqrModeCfg(&stcAdcJqrCfg); 

    Adc_CfgJqrChannel(AdcJQRCH0MUX, AdcExInputCH0);
    Adc_CfgJqrChannel(AdcJQRCH1MUX, AdcExInputCH2);
    Adc_CfgJqrChannel(AdcJQRCH2MUX, AdcExInputCH5);
    Adc_CfgJqrChannel(AdcJQRCH3MUX, AdcExInputCH0);

    ///< Enable ADC interrupt
    Adc_EnableIrq();
    EnableNvic(ADC_DAC_IRQn, IrqLevel3, TRUE);

    ///< Start queue-jump scan sampling
    Adc_JQR_Start();
}
/******************************************************************************
* EOF (not truncated)
****************************************************************************/
