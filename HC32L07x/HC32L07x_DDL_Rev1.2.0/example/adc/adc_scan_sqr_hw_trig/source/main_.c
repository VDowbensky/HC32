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
* Function implementation - global ('extern') and local ('static') ******************************************************************************/
void App_PortInit(void);
void App_AdcInit(void);
void App_AdcSqrCfg(void);

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

  ///< Port initialization
  App_PortInit();

  ///< ADC module initialization
  App_AdcInit();

  ///< ADC sequential scan mode configuration
  App_AdcSqrCfg();

  while(1)
  {
    ///< Wait for external IO trigger
    while(FALSE == Adc_GetIrqStatus(AdcMskIrqSqr));
    ///< Get sampled values
    u32AdcRestult0 = Adc_GetSqrResult(AdcSQRCH0MUX);
    u32AdcRestult2 = Adc_GetSqrResult(AdcSQRCH1MUX);
    u32AdcRestult5 = Adc_GetSqrResult(AdcSQRCH2MUX);
  }
}

///< Port initialization
void App_PortInit(void)
{
  stc_gpio_cfg_t stcGpioCfg;

  ///< Enable the GPIO peripheral clock
  Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

  Gpio_SetAnalogMode(GpioPortA, GpioPin0); //PA00 (AIN0)
  Gpio_SetAnalogMode(GpioPortA, GpioPin2); //PA02 (AIN2)
  Gpio_SetAnalogMode(GpioPortA, GpioPin5); //PA05 (AIN5)

  ///< GPIO IO USER KEY initialization
  stcGpioCfg.enDir = GpioDirIn; ///< GPIO input
  stcGpioCfg.enDrv = GpioDrvL; ///< GPIO low drive capability
  stcGpioCfg.enPu = GpioPuDisable; ///< GPIO pull-up disabled
  stcGpioCfg.enPd = GpioPdDisable; ///< GPIO pull-down disabled
  stcGpioCfg.enOD = GpioOdDisable; ///< GPIO open-drain output disabled
  stcGpioCfg.enCtrlMode = GpioAHB; ///< AHB bus control mode
  Gpio_Init(EVB_KEY1_PORT, EVB_KEY1_PIN, &stcGpioCfg); ///< GPIO initialization
  Gpio_EnableIrq(EVB_KEY1_PORT, EVB_KEY1_PIN, GpioIrqFalling); ///< GPIO interrupt enable
}

///< ADC module initialization
void App_AdcInit(void)
{
  stc_adc_cfg_t stcAdcCfg;

  ///< Enable ADC/BGR peripheral clock
  Sysctrl_SetPeripheralGate(SysctrlPeripheralAdcBgr, TRUE);

  Bgr_BgrEnable(); ///< Enable BGR

  ///< ADC initialization configuration
  stcAdcCfg.enAdcMode = AdcScanMode; ///<Sampling mode - Scan
  stcAdcCfg.enAdcClkDiv = AdcMskClkDiv1; ///<Sampling divider - 1
  stcAdcCfg.enAdcSampCycleSel = AdcMskSampCycle8Clk; ///<Sampling cycle count - 8
  stcAdcCfg.enAdcRefVolSel = AdcMskRefVolSelAVDD; ///<Reference voltage selection - VCC
  stcAdcCfg.enAdcOpBuf = AdcMskBufDisable; ///<OP BUF configuration - Off
  stcAdcCfg.enInRef = AdcMskInRefDisable; ///<Internal reference voltage enable - Off
  stcAdcCfg.enAdcAlign = AdcAlignRight; ///<Conversion result alignment - right
  Adc_Init(&stcAdcCfg); ///<
}

///< ADC sequential scan mode configuration
void App_AdcSqrCfg(void)
{
  stc_adc_sqr_cfg_t stcAdcSqrCfg;

  ///< Sequential scan mode function and channel configuration
  ///< Note: In scan mode, when the number of conversions is configured as n, the configuration range of the conversion channel must be [SQRCH(0)MUX, SQRCH(n-1)MUX]
  stcAdcSqrCfg.bSqrDmaTrig = FALSE;
  stcAdcSqrCfg.enResultAcc = AdcResultAccDisable;
  stcAdcSqrCfg.u8SqrCnt = 3;
  Adc_SqrModeCfg(&stcAdcSqrCfg);

  ///< Configure the sequential scan conversion channel
  Adc_CfgSqrChannel(AdcSQRCH0MUX, AdcExInputCH0);
  Adc_CfgSqrChannel(AdcSQRCH1MUX, AdcExInputCH2);
  Adc_CfgSqrChannel(AdcSQRCH2MUX, AdcExInputCH5);

  ///< Select the sequential scan trigger port
  Adc_SqrExtTrigCfg(AdcMskTrigPA07, TRUE);

}

/******************************************************************************
* EOF (not truncated)
******************************************************************************/
