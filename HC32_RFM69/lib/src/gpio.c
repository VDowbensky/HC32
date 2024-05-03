/******************************************************************************
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
/** \file Gpio.c
 **
 ** GPIO driver API.
 ** @link Driver Group Some description @endlink
 **
 **   - 2018-04-22  1.0  Lux First version
 **
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
 *******************************************************************************
 ** \brief GPIO initialization
 **
 ** \param [in]  enPort          IO Port
 ** \param [in]  enPin           IO Pin
 ** \param [in]  pstcGpioCfg     IO configuration structure pointer
 **
 ** \retval Ok         Successful setup
 **         Values failed to set
 ******************************************************************************/
en_result_t Gpio_Init(en_gpio_port_t enPort, en_gpio_pin_t enPin, stc_gpio_config_t  *pstcGpioCfg)
{
    //Configured as default, GPIO function
    *((uint32_t*)(((uint32_t)(&(M0P_GPIO->PA00_SEL)) + enPort) + (((uint32_t)enPin)<<2))) = GpioAf0;
    
    //Direction configuration
    if(GpioDirIn == pstcGpioCfg->enDir)
    {
        setBit(((uint32_t)&M0P_GPIO->PADIR + enPort), enPin, TRUE);
    }
    else
    {
        setBit(((uint32_t)&M0P_GPIO->PADIR + enPort), enPin, FALSE);
    }
    
    //Drive capability configuration
    if(GpioDrvH == pstcGpioCfg->enDrv)
    {
        setBit(((uint32_t)&M0P_GPIO->PADR + enPort), enPin, FALSE);
    }
    else
    {
        setBit(((uint32_t)&M0P_GPIO->PADR + enPort), enPin, TRUE);
    }
    
    //Pull-up pulldown configuration
    if(GpioPu == pstcGpioCfg->enPuPd)
    {
        setBit(((uint32_t)&M0P_GPIO->PAPU + enPort), enPin, TRUE);
        setBit(((uint32_t)&M0P_GPIO->PAPD + enPort), enPin, FALSE);
    }
    else if(GpioPd == pstcGpioCfg->enPuPd)
    {
        setBit(((uint32_t)&M0P_GPIO->PAPU + enPort), enPin, FALSE);
        setBit(((uint32_t)&M0P_GPIO->PAPD + enPort), enPin, TRUE);
    }
    else
    {
        setBit(((uint32_t)&M0P_GPIO->PAPU + enPort), enPin, FALSE);
        setBit(((uint32_t)&M0P_GPIO->PAPD + enPort), enPin, FALSE);
    }
    
    //Open drain output function
    if(GpioOdDisable == pstcGpioCfg->enOD)
    {
        setBit(((uint32_t)&M0P_GPIO->PAOD + enPort), enPin, FALSE);
    }
    else
    {
        setBit(((uint32_t)&M0P_GPIO->PAOD + enPort), enPin, TRUE);
    }
    
    M0P_GPIO->CTRL2_f.AHB_SEL = pstcGpioCfg->enCtrlMode;

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO input value acquisition
 **
 ** \param [in]  enPort          IO Port
 ** \param [in]  enPin           IO Pin
 **
 ** \retval boolean_t            IO level
 ******************************************************************************/
boolean_t Gpio_GetInputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    return getBit(((uint32_t)&M0P_GPIO->PAIN + enPort), enPin);
}

/**
 *******************************************************************************
 ** \brief GPIO IO Port input data acquisition
 **
 ** \param [in]  enPort          IO Port
 **
 ** \retval boolean_t            IO Port data
 ******************************************************************************/
uint16_t    Gpio_GetInputData(en_gpio_port_t enPort)
{
    return (uint16_t)(*((uint32_t *)((uint32_t)&M0P_GPIO->PAIN + enPort))); 
}

/**
 *******************************************************************************
 ** \brief GPIO IO output value write
 **
 ** \param [in]  enPort          IO Port
 ** \param [in]  enPin           IO Pin
 ** \param [out] bVal            output value
 **
 ** \retval en_result_t          Ok      Successful setup
 **                              Values failed to set
 ******************************************************************************/
en_result_t Gpio_WriteOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin, boolean_t bVal)
{
    setBit(((uint32_t)&M0P_GPIO->PAOUT + enPort), enPin, bVal);
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO output value acquisition
 **
 ** \param [in]  enPort          IO Port
 ** \param [in]  enPin           IO Pin
 **
 ** \retval boolean_t            IO level
 ******************************************************************************/
boolean_t   Gpio_ReadOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    return getBit(((uint32_t)&M0P_GPIO->PAOUT + enPort), enPin);
}

/**
 *******************************************************************************
 ** \brief GPIO IO Port settings to simultaneously set multiple PINs in a group of ports
 **
 ** \param [in]  enPort          IO Port
 ** \param [in]  u16ValMsk       The 16 PIN mask values of the port will be valid for the bit corresponding to the PIN to be set. 
 **
 ** \retval boolean_t            IO Port data
 ******************************************************************************/
en_result_t Gpio_SetPort(en_gpio_port_t enPort, uint16_t u16ValMsk)
{
    *((uint16_t*)(((uint32_t)&(M0P_GPIO->PABSET)) + enPort)) = u16ValMsk;
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO settings
 **
 ** \param [in]  enPort          IO Port
 ** \param [in]  enPin           IO Pin
 **
 ** \retval en_result_t          Ok      Successful setup
 **                              Values failed to set
 ******************************************************************************/
en_result_t Gpio_SetIO(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    setBit(((uint32_t)&M0P_GPIO->PABSET + enPort), enPin, TRUE);
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO Clear multiple PINs in a group of ports simultaneously
 **
 ** \param [in]  enPort          IO Port
 ** \param [in]  u16ValMsk       The 16 PIN mask values of the port will be valid for the bit corresponding to the PIN that needs to be cleared.
 **
 ** \retval boolean_t            IO Port data
 ******************************************************************************/
en_result_t Gpio_ClrPort(en_gpio_port_t enPort, uint16_t u16ValMsk)
{
    *((uint16_t*)(((uint32_t)&(M0P_GPIO->PABCLR)) + enPort)) = u16ValMsk;
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO clear
 **
 ** \param [in]  enPort          IO Port
 ** \param [in]  enPin           IO Pin
 **
 ** \retval en_result_t          Ok      Successful setup
 **                              Values failed to set
 ******************************************************************************/
en_result_t Gpio_ClrIO(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    setBit(((uint32_t)&M0P_GPIO->PABCLR + enPort), enPin, TRUE);
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO Port set/clear to simultaneously set/clear multiple PINs in a group of ports
 **
 ** \param [in]  enPort       IO Port
** \param [in]  u32ValMsk     The high 16bits indicates the 16 PIN setting mask values of the port.
 **                           The lower 16 bits indicates the 16 PIN clear mask values of the port.
**                            Write the bit corresponding to the PIN to be set to 1, and the mask of the same PIN is 1 at the same time, then the PIN is cleared.                             
 **
 ** \retval en_result_t       Ok      Successful setup
 **                           Values failed to set
 ******************************************************************************/
en_result_t Gpio_SetClrPort(en_gpio_port_t enPort, uint32_t u32ValMsk)
{
    *((uint32_t*)(((uint32_t)&(M0P_GPIO->PABSETCLR)) + enPort)) = u32ValMsk;
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO configuration to analog function mode
 **
 ** \param [in]  enPort          IO Port
 ** \param [in]  enPin           IO Pin
 **
 ** \retval Ok         Successful setup
 **         Values failed to set
 ******************************************************************************/
en_result_t Gpio_SetAnalogMode(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    setBit((uint32_t)&M0P_GPIO->PAADS + enPort, enPin, TRUE);

    return Ok;
}

/**
 *******************************************************************************
** \brief GPIO IO alternate function setting
 **
 ** \param [in]  enPort    IO Port
 ** \param [in]  enPin     IO Pin
 ** \param [in]  enAf      Multiplex function enumeration type selection
 ** \retval Ok             Successful setup
 **         Values failed to set
 ******************************************************************************/
en_result_t Gpio_SetAfMode(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_af_t enAf)
{
    *((uint32_t*)(((uint32_t)(&(M0P_GPIO->PA00_SEL)) + enPort) + (((uint32_t)enPin)<<2))) = enAf;
    
    return Ok;
}


static en_result_t _GpioEnableIrq(en_gpio_port_t enPort,
                           en_gpio_pin_t enPin,
                           en_gpio_irqtype_t enType,
                           boolean_t bEnable)
{
    //high level
    if (enType & GpioIrqHigh)
    {
        setBit((uint32_t)&M0P_GPIO->PAHIE + enPort, enPin, bEnable);
    }
    //low level
    if (enType & GpioIrqLow)
    {
        setBit((uint32_t)&M0P_GPIO->PALIE + enPort, enPin, bEnable);
    }
    //rising
    if (enType & GpioIrqRising)
    {
        setBit((uint32_t)&M0P_GPIO->PARIE + enPort, enPin, bEnable);
    }
    //falling
    if (enType & GpioIrqFalling)
    {
        setBit((uint32_t)&M0P_GPIO->PAFIE + enPort, enPin, bEnable);
    }

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO interrupt enable
 **
 ** \param [in]  enPort          IO Port
 ** \param [in]  enPin           IO Pin
 ** \param [in]  enType          Interrupt enable type
 **
 ** \retval      Ok            Successful setup
 ******************************************************************************/
en_result_t Gpio_EnableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType)
{
    _GpioEnableIrq(enPort, enPin, enType, TRUE);
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO IO interrupt disable
 **
 ** \param [in]  enPort          IO Port
 ** \param [in]  enPin           IO Pin
 ** \param [in]  enType          Interrupt enable type
 **
 ** \retval      Ok            Successful setup
 ******************************************************************************/
en_result_t Gpio_DisableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType)
{
    _GpioEnableIrq(enPort, enPin, enType, FALSE);
    
    return Ok;
}


/**
 *******************************************************************************
 ** \brief GPIO Get IO interrupt status
 **
 ** \param [in]  u8Port          IO Port
 ** \param [in]  u8Pin           IO Pin
 **
 ** \retval      IO interrupt flag
 ******************************************************************************/
boolean_t Gpio_GetIrqStatus(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    return getBit((uint32_t)&M0P_GPIO->PA_STAT + enPort, enPin);
}

/**
 *******************************************************************************
 ** \brief GPIO Clear IO interrupt flag
 **
 ** \param [in]  u8Port          IO Port
 ** \param [in]  u8Pin           IO Pin
 **
 ** \retval    Ok       Successful setup
 ******************************************************************************/
en_result_t Gpio_ClearIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin)
{
    setBit((uint32_t)&M0P_GPIO->PA_ICLR + enPort, enPin, FALSE);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO Port Accessibility Configuration - Interrupt Mode Configuration
 **
 ** \param [in]  enIrqMode          Port interrupt mode (whether deep sleep responds to interrupts)
 **
 ** \retval    Ok       Successful setup
 ******************************************************************************/
en_result_t Gpio_SfIrqModeConfig(en_gpio_sf_irqmode_t enIrqMode)
{
    M0P_GPIO->CTRL0_f.IESEL = enIrqMode;
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO Port Auxiliary Function Configuration - IR Output Polarity Configuration
 **
 ** \param [in]  enIrPolMode          IR output polarity configuration enumeration
 **
 ** \retval    Ok       Successful setup
 ******************************************************************************/
en_result_t Gpio_SfIrPolConfig(en_gpio_sf_irpol_t enIrPolMode)
{
    M0P_GPIO->CTRL1_f.IR_POL = enIrPolMode;
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO Port Auxiliary Function Configuration - HCLK Output Configuration
 **
 ** \param [in]  enGate         HCLK output enable
 ** \param [in]  enDiv          Output divider
 **
 ** \retval    Ok       Successful setup
 ******************************************************************************/
en_result_t Gpio_SfHClkOutputConfig(en_gpio_sf_hclkout_g_t enGate, en_gpio_sf_hclkout_div_t enDiv)
{
    M0P_GPIO->CTRL1_f.HCLK_EN  = enGate;
    M0P_GPIO->CTRL1_f.HCLK_SEL = enDiv;
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO Port Auxiliary Function Configuration - PCLK Output Configuration
 **
 ** \param [in]  enGate         PCLK output enable
 ** \param [in]  enDiv          Output divider
 **
 ** \retval    Ok       Successful setup
 ******************************************************************************/
en_result_t Gpio_SfPClkOutputConfig(en_gpio_sf_pclkout_g_t enGate, en_gpio_sf_pclkout_div_t enDiv)
{
    M0P_GPIO->CTRL1_f.PCLK_EN  = enGate;
    M0P_GPIO->CTRL1_f.PCLK_SEL = enDiv;
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO Port Accessibility Configuration - External Clock Input Source Configuration
 **
 ** \param [in]  enExtClk         External clock signal source selection enumeration
 **
 ** \retval    Ok       Successful setup
 ******************************************************************************/
en_result_t Gpio_SfExtClkConfig(en_gpio_sf_ssn_extclk_t enExtClk)
{
    M0P_GPIO->CTRL1_f.EXT_CLK_SEL  = enExtClk;
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO Port Auxiliary Function Configuration - SSN Channel Signal Source Configuration
 **
 ** \param [in]  enSpi         SSN SPI channel selection enumeration
 ** \param [in]  enSsn         SSN Signal source selection enumeration
 **
 ** \retval    Ok       Successful setup
 ******************************************************************************/
en_result_t Gpio_SfSsnConfig(en_gpio_sf_ssnspi_t enSpi, en_gpio_sf_ssn_extclk_t enSsn)
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
 ** \brief GPIO Port Accessibility Configuration - Timer Gating Input Configuration
 **
 ** \param [in]  enTimG       Timer type selection enumeration
 ** \param [in]  enSf         Timer interconnect function selection enumeration
 **
 ** \retval    Ok       Successful setup
 ******************************************************************************/
en_result_t Gpio_SfTimGConfig(en_gpio_sf_tim_g_t enTimG, en_gpio_sf_t enSf)
{
    M0P_GPIO->TIMGS &= (uint32_t)(~(0x07U<<enTimG));
    M0P_GPIO->TIMGS |= (uint32_t)(enSf<<enTimG);
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO Port Accessibility Configuration - Timer ETR Select Configuration
 **
 ** \param [in]  enTimE       Timer type selection enumeration
 ** \param [in]  enSf         Timer interconnect function selection enumeration
 **
 ** \retval    Ok       Successful setup
 ******************************************************************************/
en_result_t Gpio_SfTimEConfig(en_gpio_sf_tim_e_t enTimE, en_gpio_sf_t enSf)
{
    M0P_GPIO->TIMES &= (uint32_t)(~(0x07U<<enTimE));
    M0P_GPIO->TIMES |= (uint32_t)(enSf<<enTimE);
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO Port Accessibility Configuration - Timer Capture Input Selection Configuration
 **
 ** \param [in]  enTimC       Timer type selection enumeration
 ** \param [in]  enSf         Timer interconnect function selection enumeration
 **
 ** \retval    Ok       Successful setup
 ******************************************************************************/
en_result_t Gpio_SfTimCConfig(en_gpio_sf_tim_c_t enTimC, en_gpio_sf_t enSf)
{
    M0P_GPIO->TIMCPS &= (uint32_t)(~(0x07u<<enTimC));
    M0P_GPIO->TIMCPS |= (uint32_t)(enSf<<enTimC);
    
    return Ok;
}

/**
 *******************************************************************************
 ** \brief GPIO Port Accessibility Configuration - PCA Capture Input Selection Configuration
 **
 ** \param [in]  enPca        PCA type selection enumeration
 ** \param [in]  enSf         PCA interconnection function selection enumeration
 **
 ** \retval    Ok       Successful setup
 ******************************************************************************/
en_result_t Gpio_SfPcaConfig(en_gpio_sf_pca_t enPca, en_gpio_sf_t enSf)
{
    if(GpioSfPcaCH0 == enPca)
    {
        M0P_GPIO->PCAS_f.PCA_CH0 = enSf;
    }
    
    if(GpioSfPcaECI == enPca)
    {
        M0P_GPIO->PCAS_f.PCA_ECI = enSf;
    }
    
    return Ok;
}


//@} // GpioGroup


/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

