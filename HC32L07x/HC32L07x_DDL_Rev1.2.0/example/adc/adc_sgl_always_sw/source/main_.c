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
volatile uint32_t u32AdcRestult;

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
******************************************************************************/
void App_AdcPortInit(void);
void App_AdcInit(void);
void App_AdcSglCfg(void);

/**
**************************************************************************
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

  ///< ADC single sampling mode configuration
  App_AdcSglCfg();

  while(1)
  {
    if(TRUE == Adc_GetIrqStatus(AdcMskIrqSgl))
    {
      ///< Get sampling value
      u32AdcRestult = Adc_GetSglResult();
      Adc_ClrIrqStatus(AdcMskIrqSgl);
    }
  }
}

///< ADC sampling port initialization
void App_AdcPortInit(void)
{
  ///< Enable the ADC/BGR GPIO peripheral clock
  Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

  Gpio_SetAnalogMode(GpioPortA, GpioPin0); //PA00 (AIN0)
}

///< ADC module initialization
void App_AdcInit(void)
{
  stc_adc_cfg_t stcAdcCfg;

  DDL_ZERO_STRUCT(stcAdcCfg);

  ///< Enable the ADC/BGR peripheral clock
  Sysctrl_SetPeripheralGate(SysctrlPeripheralAdcBgr, TRUE);

  Bgr_BgrEnable(); ///< Enable BGR

  ///< ADC initialization configuration
  stcAdcCfg.enAdcMode = AdcSglMode; ///< Sampling mode - single
  stcAdcCfg.enAdcClkDiv = AdcMskClkDiv1; ///< Sampling divider - 1
  stcAdcCfg.enAdcSampCycleSel = AdcMskSampCycle12Clk; ///< Sampling cycle count - 12
  stcAdcCfg.enAdcRefVolSel = AdcMskRefVolSelInBgr2p5; ///< Reference voltage selection - internal 2.5V
  stcAdcCfg.enAdcOpBuf = AdcMskBufDisable; ///< OP BUF configuration - Off
  stcAdcCfg.enInRef = AdcMskInRefEnable; ///< Internal reference voltage enable - On
  stcAdcCfg.enAdcAlign = AdcAlignRight; ///< Conversion result alignment - Right
  Adc_Init(&stcAdcCfg);
  }

  ///< ADC single-shot sampling mode configuration
  void App_AdcSglCfg(void)
  {
  ///< Configure the single-shot sampling channel
  Adc_CfgSglChannel(AdcExInputCH0);

  ///< Start single-shot constant sampling
  Adc_SGL_Always_Start();

}

/******************************************************************************
* EOF (not truncated)
****************************************************************************/