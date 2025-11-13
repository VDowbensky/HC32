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
* @brief Source file for ADT example 
* 
* @author MADS Team 
* ******************************************************************************/

/****************************************************************************** 
* Include files 
******************************************************************************/
#include "adt.h"
#include "gpio.h"

/****************************************************************************** 
* Local pre-processor symbols/macros ('#define') 
******************************************************************************/


/****************************************************************************** 
* Global variable definitions (declared in header file with 'extern') 
******************************************************************************/

/****************************************************************************** 
* Local type definitions ('typedef') 
******************************************************************************/

/****************************************************************************** 
* Local function prototypes ('static') 
******************************************************************************/

/****************************************************************************** 
* Local variable definitions ('static') * 
******************************************************************************/
static uint16_t u16CaptureA;
static uint16_t u16CaptureB;

/**************************************************************************** 
* Function implementation - global ('extern') and local ('static') 
******************************************************************************/

void Tim4_IRQHandler(void)
{
  //Capture interrupt A
  if(TRUE == Adt_GetIrqFlag(M0P_ADTIM4, AdtCMAIrq))
  {
    Adt_GetCaptureValue(M0P_ADTIM4, AdtCHxA, &u16CaptureA); //Pulse low level count value

    Adt_ClearIrqFlag(M0P_ADTIM4, AdtCMAIrq);
  }
  //Capture interrupt B
  if(TRUE == Adt_GetIrqFlag(M0P_ADTIM4, AdtCMBIrq))
  {
    Adt_GetCaptureValue(M0P_ADTIM4, AdtCHxB, &u16CaptureB); //Pulse high level count value

    Adt_ClearIrqFlag(M0P_ADTIM4, AdtCMBIrq);
  }
}

///< AdvTimer port initialization
void App_AdtPortInit(void)
{
  stc_gpio_cfg_t stcTIM4Port;

  DDL_ZERO_STRUCT(stcTIM4Port);

  Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); //Port peripheral clock enable

  stcTIM4Port.enDir = GpioDirIn;
  //PA08 is set to TIM4_CHA
  Gpio_Init(GpioPortA, GpioPin8, &stcTIM4Port);
  Gpio_SetAfMode(GpioPortA, GpioPin8, GpioAf6);

  //PA07 is set to TIM4_CHB
  //Gpio_Init(GpioPortA, GpioPin7, &stcTIM4Port); 
  //Gpio_SetAfMode(GpioPortA,GpioPin7,GpioAf7);

}


///< AdvTimer initialization
void App_AdvTimerInit(void)
{ 
  uint16_t u16Period; 
  stc_adt_basecnt_cfg_t stcAdtBaseCntCfg; 
  stc_adt_CHxX_port_cfg_t stcAdtTIM4ACfg; 
  stc_adt_CHxX_port_cfg_t stcAdtTIM4BCfg; 

  DDL_ZERO_STRUCT(stcAdtBaseCntCfg); 
  DDL_ZERO_STRUCT(stcAdtTIM4ACfg); 
  DDL_ZERO_STRUCT(stcAdtTIM4BCfg); Sysctrl_SetPeripheralGate(SysctrlPeripheralAdvTim, TRUE); //ADT peripheral clock enable

  stcAdtBaseCntCfg.enCntMode = AdtSawtoothMode; //Sawtooth Mode
  stcAdtBaseCntCfg.enCntDir = AdtCntUp; //Cnt up
  stcAdtBaseCntCfg.enCntClkDiv = AdtClkPClk0Div4; //PCLK0/4
  Adt_Init(M0P_ADTIM4, &stcAdtBaseCntCfg); //ADT carrier, counting mode, and clock configuration

  u16Period = 0xFFFF;
  Adt_SetPeriod(M0P_ADTIM4, u16Period); //Period setting

  stcAdtTIM4ACfg.enCap = AdtCHxCompareInput; //Channel A Used as capture input
  stcAdtTIM4ACfg.bFltEn = TRUE;
  stcAdtTIM4ACfg.enFltClk = AdtFltClkPclk0Div16;
  Adt_CHxXPortCfg(M0P_ADTIM4, AdtCHxA, &stcAdtTIM4ACfg); //Channel A configuration & GPIO CHA input filter enable

  stcAdtTIM4BCfg.enCap = AdtCHxCompareInput; //Channel B used as capture input
  Adt_CHxXPortCfg(M0P_ADTIM4, AdtCHxB, &stcAdtTIM4BCfg);

  Adt_CfgHwCaptureA(M0P_ADTIM4, AdtHwTrigCHxARise); //Hardware capture A condition configuration: CHA port upsampled to rising edge
  Adt_CfgHwCaptureB(M0P_ADTIM4, AdtHwTrigCHxAFall); // Hardware capture B condition configuration: CHA port sampling on the falling edge

  Adt_CfgHwClear(M0P_ADTIM4, AdtHwTrigCHxARise); // Hardware clear condition: CHA port sampling on the rising edge
  Adt_CfgHwClear(M0P_ADTIM4, AdtHwTrigCHxAFall); // Hardware clear condition: Sample the CHA port to the falling edge
  Adt_EnableHwClear(M0P_ADTIM4);

  Adt_ClearAllIrqFlag(M0P_ADTIM4);
  Adt_CfgIrq(M0P_ADTIM4, AdtCMAIrq, TRUE); //Capture interrupt A configuration
  Adt_CfgIrq(M0P_ADTIM4, AdtCMBIrq, TRUE); //Capture interrupt B configuration
  EnableNvic(ADTIM4_IRQn, IrqLevel3, TRUE); //Enable AdvTimer4 interrupt
}

/**
****************************************************************************
** \brief Main function of project
**
** \return uint32_t return value, if needed
**
** This sample
**
****************************************************************************/
int32_t main(void)
{
  App_AdtPortInit(); //AdvTimer4 port initialization

  App_AdvTimerInit(); //AdvTimer4 initialization

  Adt_StartCount(M0P_ADTIM4); //AdvTimer4 running

  while(1);
}

/******************************************************************************
* EOF (not truncated)
************************************************************************/