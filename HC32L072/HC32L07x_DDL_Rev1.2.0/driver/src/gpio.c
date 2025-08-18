/******************************************************************************
 * Copyright (C) 2021, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************/

/******************************************************************************
 * @file   gpio.c
 *
 * @brief  Source file for GPIO functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "gpio.h"

/**
 *******************************************************************************
 ** \addtogroup GpioGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define IS_VALID_PIN(port,pin)      (  )
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')         *
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
**********************************************************************************
** \brief GPIO initialization
**
** \param [in] enPort IO port
** \param [in] enPin IO pin
** \param [in] pstcGpioCfg IO configuration structure pointer
**
** \retval Ok Setting successful
** Other values Setting failed
**************************************************************************/
en_result_t Gpio_Init(en_gpio_port_t enPort, en_gpio_pin_t enPin, stc_gpio_cfg_t  *pstcGpioCfg)
{
    //Configure to default values, GPIO function
    SetBit((uint32_t)&M0P_GPIO->PAADS + enPort, enPin, FALSE);
    *((uint32_t*)(((uint32_t)(&(M0P_GPIO->PA00_SEL)) + enPort) + (((uint32_t)enPin)<<2))) = GpioAf0;

    //Default output value configuration
    SetBit(((uint32_t)&M0P_GPIO->PAOUT + enPort), enPin, pstcGpioCfg->bOutputVal);
    //Direction configuration
    SetBit(((uint32_t)&M0P_GPIO->PADIR + enPort), enPin, (boolean_t)(pstcGpioCfg->enDir));
    //Drive capability configuration
    SetBit(((uint32_t)&M0P_GPIO->PADR + enPort), enPin, (boolean_t)(pstcGpioCfg->enDrv));
    //Pull-up/pull-down configuration
    SetBit(((uint32_t)&M0P_GPIO->PAPU + enPort), enPin, (boolean_t)(pstcGpioCfg->enPu));
    SetBit(((uint32_t)&M0P_GPIO->PAPD + enPort), enPin, (boolean_t)(pstcGpioCfg->enPd));
    //Open-drain output function
    SetBit(((uint32_t)&M0P_GPIO->PAOD + enPort), enPin, (boolean_t)(pstcGpioCfg->enOD));

    M0P_GPIO->CTRL2_f.AHB_SEL = pstcGpioCfg->enCtrlMode;

    return Ok;
}

/**
*******************************************************************************
** \brief GPIO IO input value acquisition
**
** \param [in] enPort IO port
** \param [in] enPin IO pin
**
** \retval boolean_t IO level high/low
********************************************************************************/
boolean_t Gpio_GetInputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    return GetBit(((uint32_t)&M0P_GPIO->PAIN + enPort), enPin);
}

/**
************************************************************************************
** \brief GPIO IO port input data acquisition
**
** \param [in] enPort IO port
**
** \retval boolean_t IO Port data
**************************************************************************/
uint16_t    Gpio_GetInputData(en_gpio_port_t enPort)
{
    return (uint16_t)(*((uint32_t *)((uint32_t)&M0P_GPIO->PAIN + enPort)));
}

/**
*******************************************************************************
** \brief GPIO output value write
**
** \param [in] enPort IO port
** \param [in] enPin IO pin
** \param [out] bVal Output value
**
** \retval en_result_t Ok Set successfully
****************************************************************************/
en_result_t Gpio_WriteOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin, boolean_t bVal)
{
    SetBit(((uint32_t)&M0P_GPIO->PAOUT + enPort), enPin, bVal);

    return Ok;
}

/**
*******************************************************************************
** \brief GPIO IO output value acquisition
**
** \param [in] enPort IO port
** \param [in] enPin IO pin
**
** \retval boolean_t IO level
**************************************************************************/
boolean_t   Gpio_ReadOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    return GetBit(((uint32_t)&M0P_GPIO->PAOUT + enPort), enPin);
}

/**
************************************************************************************
** \brief GPIO IO Port settings. Multiple PINs in a port group can be set simultaneously.
**
** \param [in] enPort IO Port
** \param [in] u16ValMsk 16 PIN mask values for this port. Writing 1 to the corresponding bit of the PIN to be set is valid.
**
** \retval boolean_t IO Port data
************************************************************************/
en_result_t Gpio_SetPort(en_gpio_port_t enPort, uint16_t u16ValMsk)
{
    *((uint16_t*)(((uint32_t)&(M0P_GPIO->PABSET)) + enPort)) = u16ValMsk;
    return Ok;
}

/**
*******************************************************************************
** \brief GPIO IO settings
**
** \param [in] enPort IO port
** \param [in] enPin IO pin
**
** \retval en_result_t Ok Setting successful
** Other values Setting failed
**************************************************************************/
en_result_t Gpio_SetIO(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    SetBit(((uint32_t)&M0P_GPIO->PABSET + enPort), enPin, TRUE);

    return Ok;
}

/**
****************************************************************************
** \brief GPIO IO Port clear, can clear multiple PINs in a port group simultaneously
**
** \param [in] enPort IO Port
** \param [in] u16ValMsk 16 PIN mask value for this port. Writing 1 to the corresponding bit of the PIN to be cleared is valid.
**
** \retval boolean_t IO Port data
************************************************************************/
en_result_t Gpio_ClrPort(en_gpio_port_t enPort, uint16_t u16ValMsk)
{
    *((uint16_t*)(((uint32_t)&(M0P_GPIO->PABCLR)) + enPort)) = u16ValMsk;

    return Ok;
}

/**
*************************************************************************
** \brief GPIO IO clear
**
** \param [in] enPort IO port
** \param [in] enPin IO pin
**
** \retval en_result_t Ok Set successful
** Other values Set failed
********************************************************************/
en_result_t Gpio_ClrIO(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    SetBit(((uint32_t)&M0P_GPIO->PABCLR + enPort), enPin, TRUE);

    return Ok;
}

/**
************************************************************************************
** \brief GPIO IO Port setting/clearing. Multiple PINs in a port group can be set/cleared simultaneously.
**
** \param [in] enPort IO Port
** \param [in] u32ValMsk. The upper 16 bits represent the set mask value for the 16 PINs in this port.
** The lower 16 bits represent the clear mask value for the 16 PINs in this port.
** Write 1 to the bit corresponding to the PIN to be set. If the mask for the same PIN is 1 at the same time, the PIN is cleared.
**
** \retval en_result_t Ok Setting successful
** Other values Setting failed
********************************************************************/
en_result_t Gpio_SetClrPort(en_gpio_port_t enPort, uint32_t u32ValMsk)
{
    *((uint32_t*)(((uint32_t)&(M0P_GPIO->PABSETCLR)) + enPort)) = u32ValMsk;

    return Ok;
}

/**
************************************************************************************
** \brief GPIO IO configuration to analog function mode
**
** \param [in] enPort IO port
** \param [in] enPin IO pin
**
** \retval Ok Setting successful
** Other values Setting failed
******************************************************************************/
en_result_t Gpio_SetAnalogMode(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    SetBit((uint32_t)&M0P_GPIO->PAADS + enPort, enPin, TRUE);

    return Ok;
}

/**
*******************************************************************************
** \brief GPIO IO multiplexing function settings
**
** \param [in] enPort IO port
** \param [in] enPin IO pin
** \param [in] enAf Multiplexing function enumeration type selection
** \retval Ok Setting successful
** Other values Setting failed
***************************************************************************/
en_result_t Gpio_SetAfMode(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_af_t enAf)
{
    *((uint32_t*)(((uint32_t)(&(M0P_GPIO->PA00_SEL)) + enPort) + (((uint32_t)enPin)<<2))) = enAf;

    return Ok;
}

/**
****************************************************************************************
** \brief GPIO interrupt enable
**
** \param [in] enPort IO port
** \param [in] enPin IO pin
** \param [in] enType interrupt enable type
**
** \retval Ok Setting successful 
******************************************************************************/
en_result_t Gpio_EnableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType)
{
    uint32_t u32PieAddr;

    u32PieAddr = ((uint32_t)((&M0P_GPIO->PAHIE) + enType)) + enPort;

    SetBit(u32PieAddr, enPin, TRUE);

    return Ok;
}

/**
************************************************************************************
** \brief GPIO IO interrupt disable
**
** \param [in] enPort IO port
** \param [in] enPin IO pin
** \param [in] enType interrupt enable type
**
** \retval Ok Setting successful 
******************************************************************************/
en_result_t Gpio_DisableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType)
{
    uint32_t u32PieAddr;

    u32PieAddr = ((uint32_t)((&M0P_GPIO->PAHIE) + enType)) + enPort;

    SetBit(u32PieAddr, enPin, FALSE);

    return Ok;
}


/** 
******************************************************************************* 
** \brief GPIO Get IO interrupt status 
** 
** \param [in] u8Port IO Port 
** \param [in] u8Pin IO Pin 
** 
** \retval IO interrupt status switch
**************************************************************************/
boolean_t Gpio_GetIrqStatus(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    return GetBit((uint32_t)&M0P_GPIO->PA_STAT + enPort, enPin);
}

/**
*******************************************************************************
** \brief GPIO Clear IO interrupt status
**
** \param [in] u8Port IO port
** \param [in] u8Pin IO pin
**
** \retval Ok Set successfully
**************************************************************************/
en_result_t Gpio_ClearIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    SetBit((uint32_t)&M0P_GPIO->PA_ICLR + enPort, enPin, FALSE);

    return Ok;
}

/**
********************************************************************************
** \brief GPIO port auxiliary function configuration - interrupt mode configuration
**
** \param [in] enIrqMode port interrupt mode (whether deep sleep responds to interrupts)
**
** \retval Ok Setting successful
****************************************************************************/
en_result_t Gpio_SfIrqModeCfg(en_gpio_sf_irqmode_t enIrqMode)
{
    M0P_GPIO->CTRL0_f.IESEL = enIrqMode;

    return Ok;
}

/**
*******************************************************************************
** \brief GPIO port auxiliary function configuration - IR output polarity configuration
**
** \param [in] enIrPolMode IR output polarity configuration enumeration
**
** \retval Ok Setting successful
************************************************************************/
en_result_t Gpio_SfIrPolCfg(en_gpio_sf_irpol_t enIrPolMode)
{
    M0P_GPIO->CTRL1_f.IR_POL = enIrPolMode;

    return Ok;
}

/**
************************************************************************************
** \brief GPIO port auxiliary function configuration - HCLK output configuration
**
** \param [in] enGate HCLK output enable
** \param [in] enDiv Output frequency divider enumeration value
**
** \retval Ok Setting successful
********************************************************************/
en_result_t Gpio_SfHClkOutputCfg(en_gpio_sf_hclkout_g_t enGate, en_gpio_sf_hclkout_div_t enDiv)
{
    M0P_GPIO->CTRL1_f.HCLK_EN  = enGate;
    M0P_GPIO->CTRL1_f.HCLK_SEL = enDiv;

    return Ok;
}

/**
************************************************************************************
** \brief GPIO port auxiliary function configuration - PCLK output configuration
**
** \param [in] enGate PCLK output enable
** \param [in] enDiv Output frequency divider enumeration value
**
** \retval Ok Setting successful
**************************************************************************/
en_result_t Gpio_SfPClkOutputCfg(en_gpio_sf_pclkout_g_t enGate, en_gpio_sf_pclkout_div_t enDiv)
{
    M0P_GPIO->CTRL1_f.PCLK_EN  = enGate;
    M0P_GPIO->CTRL1_f.PCLK_SEL = enDiv;

    return Ok;
}

/**
*******************************************************************************
** \brief GPIO port auxiliary function configuration - external clock input source configuration
**
** \param [in] enExtClk External clock signal source selection enumeration
**
** \retval Ok Setting successful
******************************************************************************/
en_result_t Gpio_SfExtClkCfg(en_gpio_sf_ssn_extclk_t enExtClk)
{
    M0P_GPIO->CTRL1_f.EXT_CLK_SEL  = enExtClk;

    return Ok;
}

/**
*******************************************************************************
** \brief GPIO port auxiliary function configuration - SSN channel signal source configuration
**
** \param [in] enSpi SSN SPI channel selection enumeration
** \param [in] enSsn SSN signal source selection enumeration
**
** \retval Ok Setting successful
***************************************************************************/
en_result_t Gpio_SfSsnCfg(en_gpio_sf_ssnspi_t enSpi, en_gpio_sf_ssn_extclk_t enSsn)
{
    //SPI0
    if(enSpi == GpioSpi0)
    {
        M0P_GPIO->CTRL1_f.SSN0_SEL = enSsn;
    }
    //SPI1
    if(enSpi == GpioSpi1)
    {
        M0P_GPIO->CTRL2_f.SSN1_SEL = enSsn;
    }

    return Ok;
}

/**
*******************************************************************************
** \brief GPIO port auxiliary function configuration - Timer gate input configuration
**
** \param [in] enTimG Timer type selection enumeration
** \param [in] enSf Timer interconnect function selection enumeration
**
** \retval Ok Setting successful
********************************************************************/
en_result_t Gpio_SfTimGCfg(en_gpio_sf_tim_g_t enTimG, en_gpio_sf_t enSf)
{
    if(enTimG&0x20u)
    {
        enTimG &= ~0x20u;
        M0P_GPIO->PCAS &= (uint32_t)(~(0x07U<<enTimG));
        M0P_GPIO->PCAS |= (uint32_t)(enSf<<enTimG);
    }
    else
    {
        M0P_GPIO->TIMGS &= (uint32_t)(~(0x07U<<enTimG));
        M0P_GPIO->TIMGS |= (uint32_t)(enSf<<enTimG);
    }

    return Ok;
}

/** *******************************************************************************
** \brief GPIO port auxiliary function configuration - Timer ETR selection configuration
**
** \param [in] enTimE Timer type selection enumeration
** \param [in] enSf Timer interconnection function selection enumeration
**
** \retval Ok Setting successful
************************************************************************/
en_result_t Gpio_SfTimECfg(en_gpio_sf_tim_e_t enTimE, en_gpio_sf_t enSf)
{
    if(enTimE&0x20u)
    {
        enTimE &= ~0x20u;
        M0P_GPIO->PCAS &= (uint32_t)(~(0x07U<<enTimE));
        M0P_GPIO->PCAS |= (uint32_t)(enSf<<enTimE);
    }
    else
    {
        M0P_GPIO->TIMES &= (uint32_t)(~(0x07U<<enTimE));
        M0P_GPIO->TIMES |= (uint32_t)(enSf<<enTimE);
    }

    return Ok;
}

/**
*******************************************************************************
** \brief GPIO port auxiliary function configuration - Timer capture input selection configuration
**
** \param [in] enTimC Timer type selection enumeration
** \param [in] enSf Timer interconnection function selection enumeration
**
** \retval Ok Setting successful
***************************************************************************/
en_result_t Gpio_SfTimCCfg(en_gpio_sf_tim_c_t enTimC, en_gpio_sf_t enSf)
{
    M0P_GPIO->TIMCPS &= (uint32_t)(~(0x07u<<enTimC));
    M0P_GPIO->TIMCPS |= (uint32_t)(enSf<<enTimC);

    return Ok;
}

/**
********************************************************************************
** \brief GPIO port auxiliary function configuration - PCA capture input selection configuration
**
** \param [in] enPca PCA type selection enumeration
** \param [in] enSf PCA interconnect function selection enumeration
**
** \retval Ok Setting successful
****************************************************************************/
en_result_t Gpio_SfPcaCfg(en_gpio_sf_pca_t enPca, en_gpio_sf_t enSf)
{
    M0P_GPIO->PCAS &= (uint32_t)(~(0x07u<<enPca));
    M0P_GPIO->PCAS |= (uint32_t)(enSf<<enPca);

    return Ok;
}

//@} // GpioGroup


/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

