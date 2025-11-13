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
* @file lcd.h 
* 
* @brief Header file for LCD functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __LCD_H__
#define __LCD_H__
/**********************************************************************************/
/* Include files */
/******************************************************************************/
#include "ddl.h"

/**********************************************************************************
** Global type definitions
********************************************************************************/

/**
******************************************************************************
** \brief LCD bias source selection
*****************************************************************************/
typedef enum
{
    LcdInResHighPower = 6, // Internal resistor divider, high power mode
    LcdInResLowPower = 4, // Internal resistor divider, low power mode
    LcdInResMidPower = 2, // Internal resistor divider, medium power mode
    LcdExtCap = 1, // Capacitor divider mode, requires external circuitry
    LcdExtRes = 0, // External resistor mode, requires external circuitry
}en_lcd_biassrc_t;

/**
******************************************************************************
** \brief LCD duty selection LCD_CR0 Duty
*****************************************************************************/
typedef enum
{
    LcdStatic = 0u, // Static display
    LcdDuty2 = 1u, // 1/2 duty
    LcdDuty3 = 2u, // 1/3 duty
    LcdDuty4 = 3u, // 1/4 duty
    LcdDuty6 = 5u, // 1/6 duty
    LcdDuty8 = 7u, // 1/8 duty
}en_lcd_duty_t;

/**
**************************************************************************
** \brief LCD bias configuration bit LCD_CR0 Bias
*****************************************************************************/
typedef enum
{
    LcdBias3 = 0u, // 1/3 BIAS
    LcdBias2 = 1u, // 1/2 BIAS
}en_lcd_bias_t;

/**
**********************************************************************************
** \brief LCD voltage pump clock frequency selection LCD_CR0 CpClk
*****************************************************************************/
typedef enum
{
    LcdClk2k = 0u, // 2k
    LcdClk4k = 1u, // 4k
    LcdClk8k = 2u, // 8k
    LcdClk16k = 3u // 16k
}en_lcd_cpclk_t;

/**
******************************************************************************
** \brief LCD scan frequency selection LCD_CR0 LcdClk
****************************************************************************/
typedef enum
{
    LcdClk64hz = 0u, // 64hz
    LcdClk128hz = 1u, // 128hz
    LcdClk256hz = 2u, // 256hz
    LcdClk512hz = 3u // 512hz
}en_lcd_scanclk_t;

/**
******************************************************************************
** \brief LCD enable control LCD_CR0 EN
********************************************************************************/
typedef enum
{
    LcdEnable = 1u, //LCD enable
    LcdDisable = 0u //LCD disable
}en_lcd_en_t;

/**
********************************************************************************
** \brief LCD display mode LCD_CR1 Mode
***************************************************************************/
typedef enum
{
    LcdMode0 = 0, ///<Mode 0
    LcdMode1 = 1, ///<Mode 1
}en_lcd_dispmode_t;

/**
******************************************************************************
** \brief LCD clock source selection LCD_CR1 ClkSrc
*****************************************************************************/
typedef enum
{
    LcdXTL = 1, ///<External XTL
    LcdRCL = 0, ///<Internal RCL
}en_lcd_clk_t;

/**
******************************************************************************
** \brief LCD CR1 register enable and flag bits
****************************************************************************/
typedef enum
{
    LcdBlinkEn = 6u, //LCD blink configuration bit
    LcdIe = 9u, //LCD interrupt enable bit
    LcdDmaEn = 10u, //LCD DMA hardware trigger enable bit
}en_cr1_t;

/**
************************************************************************
** \brief LCD display SEG COM port register configuration
************************************************************************/
typedef struct
{
  uint32_t u32Seg0_31; ///<SEG0-31 configuration
  union
  {
    uint32_t seg32_51_com0_8;
    struct
    {
      uint32_t Seg32_35:4;
      uint32_t Seg36Com7:1;
      uint32_t Seg37Com6:1;
      uint32_t Seg38Com5:1;
      uint32_t Seg39Com4:1; 
      uint32_t Seg40:1; 
      uint32_t Seg41:1; 
      uint32_t Seg42:1; 
      uint32_t Seg43:1; 
      uint32_t Mux :1; 
      uint32_t Seg44:1; 
      uint32_t Seg45:1; 
      uint32_t Seg46:1; 
      uint32_t Seg47:1; 
      uint32_t Seg48:1; 
      uint32_t Seg49:1; 
      uint32_t Seg50:1; 
      uint32_t Seg51:1; 
      uint32_t Com0_3 :4; 
    }segcom_bit; 
  }stc_seg32_51_com0_8_t;
}stc_lcd_segcom_t;

/**
****************************************************************************
** \brief LCD port configuration parameters
************************************************************************/
typedef struct stc_lcd_segcompara
{
    en_lcd_duty_t LcdDuty; ///<Duty cycle
    en_lcd_biassrc_t LcdBiasSrc; ///<Clock source
    uint8_t u8MaxSeg; ///<Maximum SEG port
}stc_lcd_segcompara_t;

/**
********************************************************************************
** \brief I2C initialization configuration structure
***************************************************************************/
typedef struct
{
    en_lcd_biassrc_t LcdBiasSrc; //Bias source selection
    en_lcd_duty_t LcdDuty; //Duty configuration selection
    en_lcd_bias_t LcdBias; //Bias voltage selection
    en_lcd_cpclk_t LcdCpClk; //Voltage pump clock frequency selection
    en_lcd_scanclk_t LcdScanClk; //Scan frequency selection
    en_lcd_dispmode_t LcdMode; //Display mode selection
    en_lcd_clk_t LcdClkSrc; //Clock source selection
    en_lcd_en_t LcdEn; //LCD enable
}stc_lcd_cfg_t;

/***************************************************************************
** \brief LCD-related function declarations 
******************************************************************************/

extern boolean_t Lcd_GetItStatus(void);
extern void Lcd_ClearItPendingBit(void);
extern en_result_t Lcd_GetSegCom(stc_lcd_segcompara_t *pstcSegComPara,stc_lcd_segcom_t *pstcSegCom);
extern void Lcd_SetSegCom(stc_lcd_segcom_t *pstcSegCom);
extern void Lcd_Init(stc_lcd_cfg_t *pstcLcdCfg);
extern void Lcd_FullDisp(void);
extern void Lcd_ClearDisp(void);
extern en_result_t Lcd_WriteRam(uint8_t u8Row,uint32_t u32Data);


//@} // LCDGroup

#ifdef __cplusplus
#endif

#endif /* __LCD_H__ */
/****************************************************************************** 
* EOF (not truncated) 
*******************************************************************************/
