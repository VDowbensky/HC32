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
* @file gpio.h 
* 
* @brief Header file for GPIO functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __GPIO_H__
#define __GPIO_H__

/************************************************************************************ 
* Include files 
******************************************************************************/
#include "ddl.h"


/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/** 
******************************************************************************* 
** \defgroup GpioGroup General Purpose I/O (GPIO) 
** 
** 
******************************************************************************/
//@{
#define GPIO_GPSZ (0x40u)

/************************************************************************************ 
* Global type definitions 
******************************************************************************/
/** ******************************************************************************* 
** \brief GPIO PORT type definition 
******************************************************************************/
typedef enum en_gpio_port
{ 
    GpioPortA = 0x00u, ///< GPIO PORT A 
    GpioPortB = 0x40u, ///< GPIO PORT B 
    GpioPortC = 0x80u, ///< GPIO PORT C 
    GpioPortD = 0xc0u, ///< GPIO PORT D 
    GpioPortE = 0x1000u, ///< GPIO PORT E 
    GpioPortF = 0x1040u, ///< GPIO PORT F
}en_gpio_port_t;

/** ******************************************************************************* 
** \brief GPIO PIN type definition 
******************************************************************************/
typedef enum en_gpio_pin
{ 
    GpioPin0 = 0u, ///< GPIO PIN0 
    GpioPin1 = 1u, ///< GPIO PIN1 
    GpioPin2 = 2u, ///< GPIO PIN2 
    GpioPin3 = 3u, ///< GPIO PIN3 
    GpioPin4 = 4u, ///< GPIO PIN4 
    GpioPin5 = 5u, ///< GPIO PIN5 
    GpioPin6 = 6u, ///< GPIO PIN6 
    GpioPin7 = 7u, ///< GPIO PIN7 
    GpioPin8= 8u, ///< GPIO PIN 8
    GpioPin9 = 9u, ///< GPIO PIN 9
    GpioPin10 = 10u, ///< GPIO PIN 10
    GpioPin11 = 11u, ///< GPIO PIN 11
    GpioPin12 = 12u, ///< GPIO PIN 12
    GpioPin13 = 13u, ///< GPIO PIN 13
    GpioPin14 = 14u, ///< GPIO PIN 14
    GpioPin15 = 15u, ///< GPIO PIN 15
}en_gpio_pin_t;

/**
************************************************************************************
** \brief GPIO port alternate function (AF-Alternate function) type definition
** \note For specific functions and meanings, please refer to the GPIO multiplexing table in the user manual or the table below.
**************************************************************************/
typedef enum en_gpio_af
{
    GpioAf0 = 0u, ///< GPIO function
    GpioAf1 = 1u, ///< GPIO AF1: Multiplexing function 1
    GpioAf2 = 2u, ///< GPIO AF2: Multiplexing function 2
    GpioAf3 = 3u, ///< GPIO AF3: Multiplexing function 3
    GpioAf4 = 4u, ///< GPIO AF4: Multiplexing function 4
    GpioAf5 = 5u, ///< GPIO AF5: Multiplexing function 5
    GpioAf6 = 6u, ///< GPIO AF6: Multiplexing function 6
    GpioAf7 = 7u, ///< GPIO AF7: Multiplexed Function 7
}en_gpio_af_t;

/**
****************************************************************************
** \brief GPIO input/output configuration data type definition
************************************************************************/
typedef enum en_gpio_dir
{
    GpioDirOut = 0u, ///< GPIO output
    GpioDirIn = 1u, ///< GPIO input
}en_gpio_dir_t;

/**
********************************************************************************
** \brief GPIO port pull-up configuration data type definition
********************************************************************/
typedef enum en_gpio_pu
{
    GpioPuDisable = 0u, ///< GPIO pull-up disabled
    GpioPuEnable = 1u, ///< GPIO pull-up
}en_gpio_pu_t;

/**
****************************************************************************
** \brief GPIO port pull-down configuration data type definition
**************************************************************************/
typedef enum en_gpio_pd
{
    GpioPdDisable = 0u, ///< GPIO pull-down disabled
    GpioPdEnable = 1u, ///< GPIO pull-down enabled
}en_gpio_pd_t;

/**
********************************************************************************
** \brief GPIO port output drive capability configuration data type definition
**********************************************************************************/
typedef enum en_gpio_drv
{
    GpioDrvH = 0u, ///< GPIO high drive capability
    GpioDrvL = 1u, ///< GPIO low drive capability
}en_gpio_drv_t;

/**
******************************************************************************
** \brief GPIO port open-drain output control data type definition
**************************************************************************/
typedef enum en_gpio_od
{
    GpioOdDisable = 0u, ///< GPIO open-drain output disabled
    GpioOdEnable = 1u, ///< GPIO open-drain output enabled
}en_gpio_od_t;

/**
***********************************************************************************
** \brief GPIO port input/output value register bus control mode selection
**************************************************************************/
typedef enum en_gpio_ctrl_mode
{
    GpioFastIO = 0u, ///< Fast IO bus control mode
    GpioAHB = 1u, ///< AHB bus control mode
}en_gpio_ctrl_mode_t;

/**
*******************************************************************************
** \brief GPIO interrupt trigger mode type definition
**************************************************************************/
typedef enum en_gpio_irqtype
{
    GpioIrqHigh = 0u, ///< GPIO high level trigger
    GpioIrqLow = 1u, ///< GPIO low level trigger
    GpioIrqRising = 2u, ///< GPIO rising edge trigger
    GpioIrqFalling = 3u, ///< GPIO falling edge trigger
}en_gpio_irqtype_t;

/**
****************************************************************************
** \brief GPIO Secondary Function (SF) Port Interrupt Mode Type Definition
************************************************************************/
typedef enum en_gpio_sf_irqmode
{
    GpioSfIrqDpslpMode = 1u, ///< Deep Sleep mode
    GpioSfIrqActSlpMode = 0u, ///< Active/Sleep mode
}en_gpio_sf_irqmode_t;

/**
************************************************************************************
** \brief GPIO Secondary Function (SF-Secondary Function) HCLK Output Gating Type Definition
**************************************************************************/
typedef enum en_gpio_sf_hclkout_g
{
    GpioSfHclkOutDisable = 0u, ///< HCLK output gating disabled
    GpioSfHclkOutEnable = 1u, ///< HCLK output gating enabled
}en_gpio_sf_hclkout_g_t;

/**
*******************************************************************************
** \brief GPIO Secondary Function (SF-Secondary Function) HCLK Output Divider Selection Type Definition
**************************************************************************/
typedef enum en_gpio_sf_hclkout_div
{
    GpioSfHclkOutDiv1 = 0u, ///< HCLK
    GpioSfHclkOutDiv2 = 1u, ///< HCLK/2
    GpioSfHclkOutDiv4 = 2u, ///< HCLK/4
    GpioSfHclkOutDiv8 = 3u, ///< HCLK/8
}en_gpio_sf_hclkout_div_t;
/**
************************************************************************************
** \brief GPIO Secondary Function (SF-Secondary Function) PCLK Output Gating Type Definition
****************************************************************************/
typedef enum en_gpio_sf_pclkout_g
{
    GpioSfPclkOutDisable = 0u, ///< PCLK Output Gating Disable
    GpioSfPclkOutEnable = 1u, ///< PCLK output gating enable
}en_gpio_sf_pclkout_g_t;

/**
********************************************************************************
** \brief GPIO Secondary Function (SF-Secondary Function) PCLK output divider selection type definition
****************************************************************************/
typedef enum en_gpio_sf_pclkout_div
{
    GpioSfPclkOutDiv1 = 0u, ///< PCLK
    GpioSfPclkOutDiv2 = 1u, ///< PCLK/2
    GpioSfPclkOutDiv4 = 2u, ///< PCLK/4
    GpioSfPclkOutDiv8 = 3u, ///< PCLK/8
}en_gpio_sf_pclkout_div_t;

/**
****************************************************************************
** \brief GPIO Auxiliary Function (SF-Secondary Function) IR Output Polarity Selection Type Definition
************************************************************************/
typedef enum en_gpio_sf_irpol
{
    GpioSfIrP = 0u, ///< IR positive output
    GpioSfIrN = 1u, ///< IR negative output
}en_gpio_sf_irpol_t;

/**
********************************************************************************
** \brief GPIO Auxiliary Function (SF-Secondary Function) SSN Channel Type Definition
******************************************************************************/
typedef enum en_gpio_sf_ssnspi
{
    GpioSpi0 = 0u, ///< SPI0 SSN
    GpioSpi1 = 1u, ///< SPI1 SSN
}en_gpio_sf_ssnspi_t;

/**
*******************************************************************************
** \brief GPIO auxiliary function (SF-Secondary Function) SSN and external clock input signal source selection type definition
******************************************************************************/
typedef enum en_gpio_sf_ssn_extclk
{
    GpioSfSsnExtClkH = 0u, ///< High level
    GpioSfSsnExtClkPA03 = 1u, ///< PA03 
    GpioSfSsnExtClkPA04 = 2u, ///< PA04 
    GpioSfSsnExtClkPA06 = 3u, ///< PA06 
    GpioSfSsnExtClkPA08 = 4u, ///< PA08 
    GpioSfSsnExtClkPA09 = 5u, ///< PA09 
    GpioSfSsnExtClkPA12 = 6u, ///< PA12 
    GpioSfSsnExtClkPA15 = 7u, ///< PA15 
    GpioSfSsnExtClkPB01 = 8u, ///< PB01 
    GpioSfSsnExtClkPB02 = 9u, ///< PB02 
    GpioSfSsnExtClkPB05 = 10u, ///< PB05 
    GpioSfSsnExtClkPB06 = 11u, ///< PB06
    GpioSfSsnExtClkPB09 = 12u, ///< PB09
    GpioSfSsnExtClkPB10 = 13u, ///< PB10
    GpioSfSsnExtClkPB12 = 14u, ///< PB12
    GpioSfSsnExtClkPB14 = 15u, ///< PB14
}en_gpio_sf_ssn_extclk_t;

/**
*******************************************************************************
** \brief GPIO Secondary Function (SF) Timer Interconnect Function Selection Type Definition
** \note For specific functions and meanings, please refer to the GPIO Secondary Register Description in the User Manual.
******************************************************************************/
typedef enum en_gpio_sf
{
    GpioSf0 = 0u, ///< SF0: PX_SEL configuration function
    GpioSf1 = 1u, ///< SF1: Auxiliary function 1
    GpioSf2 = 2u, ///< SF2: Auxiliary function 2
    GpioSf3 = 3u, ///< SF3: Auxiliary function 3
    GpioSf4 = 4u, ///< SF4: Auxiliary function 4
    GpioSf5 = 5u, ///< SF5: Auxiliary function 5
    GpioSf6 = 6u, ///< SF6: Auxiliary function 6
    GpioSf7 = 7u, ///< SF7: Auxiliary function 7
}en_gpio_sf_t;

/**
*******************************************************************************
** \brief GPIO Secondary Function (SF-Secondary Function) Timer Gate Type Selection Data Type Definition
**************************************************************************/
typedef enum en_gpio_sf_tim_g
{
    GpioSfTim0G = 0u, ///<Tim0 timer gate input selection
    GpioSfTim1G = 3u, ///<Tim1 timer gate input selection
    GpioSfTim2G = 6u, ///<Tim2 timer gate input selection
    GpioSfTim3G = 9u, ///<Tim3 timer gate input selection
    GpioSfLpTim0G = 12u, ///<LPTim0 timer gate input selection
    GpioSfLpTim1G = 38u, ///<Tim3 timer gate input selection
    GpioSfLpTim0G = 12u, ///<LPTim0 timer gate input selection
    GpioSfLpTim1G = 38u, ///<Tim1 timer gate input selection ///<LPTim1 timer gate input selection
}en_gpio_sf_tim_g_t;

/**
********************************************************************************
** \brief GPIO Secondary Function (SF) Timer ETR Type Selection Data Type Definition
************************************************************************/
typedef enum en_gpio_sf_tim_e
{
    GpioSfTim0E = 0u, ///<Tim0 timer ETR input selection
    GpioSfTim1E = 3u, ///<Tim1 timer ETR input selection
    GpioSfTim2E = 6u, ///<Tim2 timer ETR input selection
    GpioSfTim3E = 9u, ///<Tim3 timer ETR input selection
    GpioSfLpTim0E = 12u, ///<LPTim0 timer ETR input selection
    GpioSfLpTim1E = 41u, ///<LPTim1 timer ETR input selection
}en_gpio_sf_tim_e_t;

/**
************************************************************************************
** \brief GPIO Secondary Function (SF) Timer Capture Input Type Selection Data Type Definition
************************************************************************/
typedef enum en_gpio_sf_tim_c
{
    GpioSfTim0CA = 0u, ///<Tim0 timer CHA input selection
    GpioSfTim1CA = 3u, ///<Tim1 timer CHA input selection
    GpioSfTim2CA = 6u, ///<Tim2 timer CHA input selection
    GpioSfTim3CA = 9u, ///<Tim3 timer CH0A input selection
    GpioSfTim3CB = 12u, ///<Tim3 timer CH0B input selection
}en_gpio_sf_tim_c_t;

/**
********************************************************************************
** \brief GPIO Secondary Function (SF) PCA Capture Select Data Type Definition
************************************************************************/
typedef enum en_gpio_sf_pca
{
    GpioSfPcaCH0 = 0u, ///<PCA_CH0 capture port input selection
    GpioSfPcaECI = 3u, ///<PCA ECI clock input selection
}en_gpio_sf_pca_t;

/**
****************************************************************************************
** \brief GPIO Secondary Function (SF-Secondary Function) PCNT Pulse Input Selection Data Type Definition
**************************************************************************/
typedef enum en_gpio_sf_pcnt
{
    GpioSfPcntS0 = 0u, ///<PCNT_S0 input selection
    GpioSfPcntS1 = 3u, ///<PCNT_S1 input selection
}en_gpio_sf_pcnt_t;

/**
*******************************************************************************
** \brief GPIO port configuration structure definition
******************************************************************************/
typedef struct
{
    boolean_t bOutputVal; ///< Default port output level
    en_gpio_dir_t enDir; ///< Port direction configuration
    en_gpio_drv_t enDrv; ///< Port driver capability configuration
    en_gpio_pu_t enPu; ///< Port pull-up configuration
    en_gpio_pd_t enPd; ///< Port pull-down configuration
    en_gpio_od_t enOD; ///< Port open-drain output configuration
    en_gpio_ctrl_mode_t enCtrlMode; ///< Port input/output value register bus control mode configuration
}stc_gpio_cfg_t;

/*******************************************************************************
* Global definitions
************************************************************************/

/**********************************************************************************
* Local type definitions ('typedef')
******************************************************************************/

/******************************************************************************
* Global variable definitions ('extern')
******************************************************************************/

/**************************************************************************************
Global function prototypes (definition in C source)
*******************************************************************************/
///< GPIO IO initialization/deinitialization
en_result_t Gpio_Init(en_gpio_port_t enPort, en_gpio_pin_t enPin, stc_gpio_cfg_t *pstcGpioCfg);

///< GPIO Get port input level
boolean_t Gpio_GetInputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);
uint16_t Gpio_GetInputData(en_gpio_port_t enPort);

///< GPIO Set port output
///< GPIO Configure and get port output level
en_result_t Gpio_WriteOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin, boolean_t bVal);
boolean_t Gpio_ReadOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin enPin);
///< Set the GPIO port/pin output level
en_result_t Gpio_SetPort(en_gpio_port_t enPort, uint16_t u16ValMsk);
en_result_t Gpio_SetIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);
///< Clear the GPIO port/pin output level
en_result_t Gpio_ClrPort(en_gpio_port_t enPort, uint16_t u16ValMsk);
en_result_t Gpio_ClrIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);
///< Set and clear the GPIO port output level
en_result_t Gpio_SetClrPort(en_gpio_port_t enPort, uint32_t u32ValMsk);

///< Set the GPIO port to analog function.
en_result_t Gpio_SetAnalogMode(en_gpio_port_t enPort, en_gpio_pin_t enPin);

///< Set the GPIO port to port multiplexing function.
en_result_t Gpio_SetAfMode(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_af_t enAf);

///< Enable/disable the GPIO port interrupt control function.
en_result_t Gpio_EnableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType);
en_result_t Gpio_DisableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType);
///< Get GPIO interrupt status
boolean_t Gpio_GetIrqStatus(en_gpio_port_t enPort, en_gpio_pin_t enPin);
///< Clear GPIO interrupt flag
en_result_t Gpio_ClearIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin);

///< Configure GPIO port auxiliary function
///< Configure GPIO interrupt mode
en_result_t Gpio_SfIrqModeCfg(en_gpio_sf_irqmode_t enIrqMode);
///< Configure GPIO IR output polarity
en_result_t Gpio_SfIrPolCfg(en_gpio_sf_irpol_t enIrPolMode);
///< GPIO HCLK output configuration
en_result_t Gpio_SfHClkOutputCfg(en_gpio_sf_hclkout_g_t enGate, en_gpio_sf_hclkout_div_t enDiv);
///< GPIO PCLK output configuration
en_result_t Gpio_SfPClkOutputCfg(en_gpio_sf_pclkout_g_t enGate, en_gpio_sf_pclkout_div_t enDiv);
///< GPIO external clock input configuration
en_result_t Gpio_SfExtClkCfg(en_gpio_sf_ssn_extclk_t enExtClk);
///< GPIO SPI SSN input configuration
en_result_t Gpio_SfSsnCfg(en_gpio_sf_ssnspi_t enSpi, en_gpio_sf_ssn_extclk_t enSsn);
///< GPIO Timer gate input configuration
en_result_t Gpio_SfTimGCfg(en_gpio_sf_tim_g_t enTimG, en_gpio_sf_t enSf);
///< GPIO Timer ETR selection configuration
en_result_t Gpio_SfTimECfg(en_gpio_sf_tim_e_t enTimE, en_gpio_sf_t enSf);
///< GPIO Timer capture input configuration
en_result_t Gpio_SfTimCCfg(en_gpio_sf_tim_c_t enTimC, en_gpio_sf_t enSf);
///< GPIO PCA capture selection configuration
en_result_t Gpio_SfPcaCfg(en_gpio_sf_pca_t enPca, en_gpio_sf_t enSf);
///< GPIO PCNT capture selection configuration
en_result_t Gpio_SfPcntCfg(en_gpio_sf_pcnt_t enPcnt, en_gpio_sf_t enSf);

//@} // GpioGroup

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H__ */
/******************************************************************************
* EOF (not truncated) 
******************************************************************************/
