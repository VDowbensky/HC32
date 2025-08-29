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
volatile uint32_t u32AdcRestult2;
volatile uint32_t u32AdcRestult5;
volatile uint32_t u32AdcRestultAcc;
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
void App_AdcSQRCfg(void);
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

  ///< ADC sequential scan function configuration
  App_AdcSQRCfg();

  while(1)
  {
    ;
  }
}

///< ADC Interrupt Service Routine
void Adc_IRQHandler(void)
{
  if(TRUE == Adc_GetIrqStatus(AdcMskIrqSqr))
  {
    Adc_ClrIrqStatus(AdcMskIrqSqr);

    u32AdcRestult0 = Adc_GetSqrResult(AdcSQRCH0MUX); //Get Sequential Scan Channel 0
    u32AdcRestult2 = Adc_GetSqrResult(AdcSQRCH1MUX); //Get Sequential Scan Channel 1
    u32AdcRestult5 = Adc_GetSqrResult(AdcSQRCH2MUX); //Get Sequential Scan Channel 2

    u32AdcRestultAcc = Adc_GetAccResult();

    Adc_SQR_Stop();
  }
}

///< ADC Sampling port initialization
void App_AdcPortInit(void)
{
  ///< Enable GPIO peripheral clock
  Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

  Gpio_SetAnalogMode(GpioPortA, GpioPin0); //PA00 (AIN0)
  Gpio_SetAnalogMode(GpioPortA, GpioPin2); //PA02 (AIN2)
  Gpio_SetAnalogMode(GpioPortA, GpioPin5); //PA05 (AIN5)
}

///< ADC module initialization
void App_AdcInit(void)
{
  stc_adc_cfg_t stcAdcCfg;

  DDL_ZERO_STRUCT(stcAdcCfg);

  ///< Enable ADC/BGR peripheral clock
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

///< ADC sequential scan function configuration
void App_AdcSQRCfg(void)
{
  stc_adc_sqr_cfg_t stcAdcSqrCfg;

  DDL_ZERO_STRUCT(stcAdcSqrCfg);

  ///< Sequential scan mode function and channel configuration
  ///< Note: In scan mode, when the number of conversions is configured as n, the configuration range of the conversion channel must be [SQRCH(0)MUX, SQRCH(n-1)MUX]
  stcAdcSqrCfg.bSqrDmaTrig = FALSE; 
  stcAdcSqrCfg.enResultAcc = AdcResultAccEnable;
  stcAdcSqrCfg.u8SqrCnt = 3;
  Adc_SqrModeCfg(&stcAdcSqrCfg);

  Adc_CfgSqrChannel(AdcSQRCH0MUX, AdcExInputCH0);
  Adc_CfgSqrChannel(AdcSQRCH1MUX, AdcExInputCH2);
  Adc_CfgSqrChannel(AdcSQRCH2MUX, AdcExInputCH5);

  ///< ADC interrupt enable
  Adc_EnableIrq();
  EnableNvic(ADC_DAC_IRQn, IrqLevel3, TRUE);

  ///< Start sequential scan sampling
  Adc_SQR_Start();

}

/********************************************************************************** 
* EOF (not truncated) 
******************************************************************************/
