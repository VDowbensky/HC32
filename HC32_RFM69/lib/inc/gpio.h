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
/** \file gpio.h
 **
 ** GPIO driver
 ** @link GPIO Group Some description @endlink
 **
 **   - 2018-04-18
 **
 ******************************************************************************/

#ifndef __GPIO_H__
#define __GPIO_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l136.h"

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
#define GPIO_GPSZ       (0x40u)

/*******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief GPIO PORT type definition
 ******************************************************************************/
typedef enum en_gpio_port
{
    GpioPortA = 0x00u,                 ///< GPIO PORT A
    GpioPortB = 0x40u,                 ///< GPIO PORT B
    GpioPortC = 0x80u,                 ///< GPIO PORT C
    GpioPortD = 0xc0u,                 ///< GPIO PORT D
}en_gpio_port_t;
 
/**
 *******************************************************************************
 ** \brief GPIO PIN type definition
 ******************************************************************************/
typedef enum en_gpio_pin
{
    GpioPin0  = 0u,                 ///< GPIO PIN0 
    GpioPin1  = 1u,                 ///< GPIO PIN1 
    GpioPin2  = 2u,                 ///< GPIO PIN2 
    GpioPin3  = 3u,                 ///< GPIO PIN3 
    GpioPin4  = 4u,                 ///< GPIO PIN4 
    GpioPin5  = 5u,                 ///< GPIO PIN5 
    GpioPin6  = 6u,                 ///< GPIO PIN6 
    GpioPin7  = 7u,                 ///< GPIO PIN7 
    GpioPin8  = 8u,                 ///< GPIO PIN8 
    GpioPin9  = 9u,                 ///< GPIO PIN9 
    GpioPin10 = 10u,                ///< GPIO PIN10
    GpioPin11 = 11u,                ///< GPIO PIN11
    GpioPin12 = 12u,                ///< GPIO PIN12
    GpioPin13 = 13u,                ///< GPIO PIN13
    GpioPin14 = 14u,                ///< GPIO PIN14
    GpioPin15 = 15u,                ///< GPIO PIN15
}en_gpio_pin_t; 

/**
 *******************************************************************************
 ** \brief GPIO AF-Alternate function type definition
 ******************************************************************************/
typedef enum en_gpio_af
{
    GpioAf0  = 0u,      ///< GPIO function
    GpioAf1  = 1u,      ///< GPIO AF1: 
                        ///< PA:UART1/SPI0/UART0/IR                             
                        ///< PB:PCA/LPTIM/SPI0/I2C0/I2C1/SPI1 
                        ///< PC:LPTIM/SPI1/LPUART0/PCA/LPUART1
                        ///< PD:I2C0/PCA/I2C1 
    GpioAf2  = 2u,      ///< GPIO AF2:
                        ///< PA:LPUART1/TIM0/UART1/PCA/TIM3                             
                        ///< PB:TIM3/PCLK_OUT/PCA/TIM0/UART0/TIM1/IR/SPI1/I2C1 
                        ///< PC:PCNT/TIM5/LPTIM/TIM2/TIM6/TIM4/LPUART0/LPUART1/RTC
                        ///< PD:TIM4/LPUART0/LPUART1
    GpioAf3  = 3u,      ///< GPIO AF3:
                        ///< PA:TIM0/VC1/TIM1/PCA/TIM3/HCLK_OUT/TIM0/TIM2/I2C1/LVD/LPUART1                             
                        ///< PB:LPUART0/TIM3/LPUART1/TIM1/TIM2/SPI1/TIM0 
                        ///< PC:UART1/PCNT/LPTIM/IR/PCA/TIM2/TIM1/TIM3
                        ///< PD:UART1/TIM1/UART0    
    GpioAf4  = 4u,      ///< GPIO AF4:
                        ///< PA:VC0/TIM1/TIM2/TIM0/TIM3/I2C0/LVD                             
                        ///< PB:TIM5/TIM6/TIM4/TIM3/UART0/PCA/TIM0/LPUART1/TIM2/LPUART0 
                        ///< PC:RESERVED
                        ///< PD:RESERVED   
    GpioAf5  = 5u,      ///< GPIO AF5:
                        ///< PA:TIM1/TIM2/SPI1/TIM5/VC0/VC1/RTC/RCH_OUT/TIM0                            
                        ///< PB:RCH_OUT/LPUART0/TIM1/LPTIM/TIM2/TIM0/TIM3/TIM6/RTC 
                        ///< PC:RESERVED
                        ///< PD:RESERVED    
    GpioAf6  = 6u,      ///< GPIO AF6:
                        ///< PA:TIM3/HCLK_OUT/PCLK_OUT/LVD/XTL_OUT/VC1/TIM4/SPI0/PCNT/RCL_OUT                             
                        ///< PB:TIM0/XTL_OUT/TIM3/PCNT/LPTIM/TIM2/LPUART1/LPUART0/TIM1/RTC 
                        ///< PC:RESERVED
                        ///< PD:RESERVED    
    GpioAf7  = 7u,      ///< GPIO AF7:
                        ///< PA:TIM0/SPI1/TIM5/TIM3/XTH_OUT/LPUART0/TIM4/TIM6/PCNT/PLL_OUT                             
                        ///< PB:PLL_OUT/TIM2/XTH_OUT/LPTIM/UART0/PCNT/UART1/TIM6/TIM1/LPUART1
                        ///< PC:RESERVED
                        ///< PD:RESERVED    
}en_gpio_af_t;  
 
/**
 *******************************************************************************
 ** \brief GPIO input and output configuration data type definition
 ******************************************************************************/
typedef enum en_gpio_dir
{
    GpioDirOut = 0u,                ///< GPIO Output
    GpioDirIn  = 1u,                ///< GPIO Input            
}en_gpio_dir_t;

/**
 *******************************************************************************
 ** \brief GPIO port pull-up, pull-down configuration data type definition
 ******************************************************************************/
typedef enum en_gpio_pupd
{
    GpioNoPuPd = 0u,                ///< GPIO has no pull-down
    GpioPu     = 1u,                ///< GPIO pull up
    GpioPd     = 2u,                ///< GPIO pulldown            
}en_gpio_pupd_t;

/**
 *******************************************************************************
 ** \brief GPIO port output drive capability configuration data type definition
 ******************************************************************************/
typedef enum en_gpio_drv
{
    GpioDrvH = 0u,                  ///< GPIO high drive capability
    GpioDrvL = 1u,                  ///< GPIO low drive capability          
}en_gpio_drv_t;

/**
 *******************************************************************************
 ** \brief GPIO port open drain output control data type definition
 ******************************************************************************/
typedef enum en_gpio_od
{
    GpioOdDisable = 0u,             ///< GPIO open drain output is off          
    GpioOdEnable  = 1u,             ///< GPIO open-drain output enable
}en_gpio_od_t;

/**
 *******************************************************************************
 ** \brief GPIO port input/output value register bus control mode selection
 ******************************************************************************/
typedef enum en_gpio_ctrl_mode
{
    GpioFastIO = 0u,             ///< FAST IO Bus control mode          
    GpioAHB  = 1u,               ///< AHB Bus control mode
}en_gpio_ctrl_mode_t;

/**
 *******************************************************************************
 ** \brief GPIO interrupt trigger mode type definition
 ******************************************************************************/
typedef enum en_gpio_irqtype
{
    GpioIrqHigh     = 1u,           ///< GPIO high trigger
    GpioIrqLow      = 2u,           ///< GPIO low trigger
    GpioIrqRising   = 4u,           ///< GPIO rising edge trigger
    GpioIrqFalling  = 8u,           ///< GPIO falling edge trigger
}en_gpio_irqtype_t;

/**
 *******************************************************************************
 ** \brief GPIO SF-Secondary Function port interrupt mode type definition
 ******************************************************************************/
typedef enum en_gpio_sf_irqmode
{
    GpioSfIrqDpslpMode  = 1u,        ///< Deep Sleep mode
    GpioSfIrqActSlpMode = 0u,        ///< Active/Sleep mode
}en_gpio_sf_irqmode_t;

/**
 *******************************************************************************
 ** \brief GPIO SF-Secondary Function HCLK Output Gating Type Definition
 ******************************************************************************/
typedef enum en_gpio_sf_hclkout_g
{
    GpioSfHclkOutDisable = 0u,       ///< HCLK output gated off
    GpioSfHclkOutEnable  = 1u,       ///< HCLK output gating enable
}en_gpio_sf_hclkout_g_t;

/**
 *******************************************************************************
 ** \brief GPIO SF-Secondary Function HCLK Output Divider Selection Type Definition
 ******************************************************************************/
typedef enum en_gpio_sf_hclkout_div
{
    GpioSfHclkOutDiv1 = 0u,         ///< HCLK
    GpioSfHclkOutDiv2 = 1u,         ///< HCLK/2
    GpioSfHclkOutDiv4 = 2u,         ///< HCLK/4
    GpioSfHclkOutDiv8 = 3u,         ///< HCLK/8
}en_gpio_sf_hclkout_div_t;
/**
 *******************************************************************************
 ** \brief GPIO SF-Secondary Function PCLK Output Gating Type Definition
 ******************************************************************************/
typedef enum en_gpio_sf_pclkout_g
{
    GpioSfPclkOutDisable = 0u,       ///< PCLK output gated off
    GpioSfPclkOutEnable  = 1u,       ///< PCLK output gating enable
}en_gpio_sf_pclkout_g_t;

/**
 *******************************************************************************
 ** \brief GPIO SF-Secondary Function PCLK Output Divider Selection Type Definition
 ******************************************************************************/
typedef enum en_gpio_sf_pclkout_div
{
    GpioSfPclkOutDiv1 = 0u,         ///< PCLK
    GpioSfPclkOutDiv2 = 1u,         ///< PCLK/2
    GpioSfPclkOutDiv4 = 2u,         ///< PCLK/4
    GpioSfPclkOutDiv8 = 3u,         ///< PCLK/8
}en_gpio_sf_pclkout_div_t;

/**
 *******************************************************************************
 ** \brief GPIO SF-Secondary Function IR Output Polarity Selection Type Definition
 ******************************************************************************/
typedef enum en_gpio_sf_irpol
{
    GpioSfIrP = 0u,                  ///< IR forward output
    GpioSfIrN = 1u,                  ///< IR reverse output
}en_gpio_sf_irpol_t;

/**
 *******************************************************************************
 ** \brief GPIO SF-Secondary Function SSN channel type definition
 ******************************************************************************/
typedef enum en_gpio_sf_ssnspi
{
    GpioSpi0 = 0u,                   ///< SPI0 SSN 
    GpioSpi1 = 1u,                   ///< SPI1 SSN
}en_gpio_sf_ssnspi_t;

/**
 *******************************************************************************
 ** \brief GPIO SF-Secondary Function SSN and external clock input source selection type definition
 ******************************************************************************/
typedef enum en_gpio_sf_ssn_extclk
{
    GpioSfSsnExtClkH    = 0u,        ///< High level
    GpioSfSsnExtClkPA03 = 1u,        ///< PA03
    GpioSfSsnExtClkPA04 = 2u,        ///< PA04
    GpioSfSsnExtClkPA06 = 3u,        ///< PA06
    GpioSfSsnExtClkPA08 = 4u,        ///< PA08
    GpioSfSsnExtClkPA09 = 5u,        ///< PA09
    GpioSfSsnExtClkPA12 = 6u,        ///< PA12
    GpioSfSsnExtClkPA15 = 7u,        ///< PA15
    GpioSfSsnExtClkPB01 = 8u,        ///< PB01
    GpioSfSsnExtClkPB02 = 9u,        ///< PB02
    GpioSfSsnExtClkPB05 = 10u,       ///< PB05
    GpioSfSsnExtClkPB06 = 11u,       ///< PB06
    GpioSfSsnExtClkPB09 = 12u,       ///< PB09
    GpioSfSsnExtClkPB10 = 13u,       ///< PB10
    GpioSfSsnExtClkPB12 = 14u,       ///< PB12
    GpioSfSsnExtClkPB14 = 15u,       ///< PB14       
}en_gpio_sf_ssn_extclk_t;

/**
 *******************************************************************************
 ** \brief GPIO SF-Secondary Function timer interconnect function selection type definition
 ******************************************************************************/
typedef enum en_gpio_sf
{
    GpioSf0 = 0u,       ///< SF0:PX_SEL configuration function
    GpioSf1 = 1u,       ///< SF1：
                        ///< TIM_G:UART0_RXD/LPUART0_RXD
                        ///< TIM_E:UART0_RXD/LPUART0_RXD/PCNT_S0
                        ///< TIM_C:UART0_RXD/LPUART0_RXD/UART1_RXD/LPUART1_RXD
                        ///< PCA:PCNT_S1/PCNT_S0
    GpioSf2 = 2u,       ///< SF2：
                        ///< TIM_G:UART1_RXD/LPUART1_RXD
                        ///< TIM_E:UART1_RXD/LPUART1_RXD/LVD_OUT
                        ///< TIM_C:PA00/VC0_OUT/LPUART0_RXD/UART1_RXD
                        ///< PCA:LVD_OUT/PCNT_S1
    GpioSf3 = 3u,       ///< SF3：
                        ///< TIM_G:VC0_OUT/LPUART0
                        ///< TIM_E:VC0_OUT/VC1OUT
                        ///< TIM_C:PA02/PCNT_S0/PCNT_S1
                        ///< PCA:VC0_OUT/LVD_OUT
    GpioSf4 = 4u,       ///< SF4：
                        ///< TIM_G:VC1_OUT/LPUART1
                        ///< TIM_E:LVD_OUT/PCNT_S1/PCNT_S0/VC1_OUT
                        ///< TIM_C:PA05/PA06/PA07/VC0_OUT/VC1_OUT
                        ///< PCA:VC1_OUT
    GpioSf5 = 5u,       ///< SF5：
                        ///< TIM_G:PA03/PA08/PA10/VC0_OUT/PB03
                        ///< TIM_E:PA00/PA01/PA04
                        ///< TIM_C:PA15/PB08/PA08/PA07
                        ///< PCA:PA05/PA06
    GpioSf6 = 6u,       ///< SF6：
                        ///< TIM_G:PB08/PB03/PB04/PA06/PB05
                        ///< TIM_E:PA05/PC09/PC04/PA12/PB06
                        ///< TIM_C:PB06/PB10/PB09/PB03/PB04
                        ///< PCA:PB02/PB04
    GpioSf7 = 7u,       ///< SF7：
                        ///< TIM_G:PB15/PB13/PB11/PC00
                        ///< TIM_E:PA15/PD02/PC08/PA13/PC03
                        ///< TIM_C:PB14/PB13/PC06/PB06
                        ///< PCA:PD02/PC06
}en_gpio_sf_t;

/**
 *******************************************************************************
 ** \brief GPIO SF-Secondary Function timer gating type selection data type definition
 ******************************************************************************/
typedef enum en_gpio_sf_tim_g
{
    GpioSfTim0G  = 0u,                   ///<Tim0 Timer GATE input selection 
    GpioSfTim1G  = 3u,                   ///<Tim1 Timer GATE input selection 
    GpioSfTim2G  = 6u,                   ///<Tim2 Timer GATE input selection 
    GpioSfTim3G  = 9u,                   ///<Tim3 Timer GATE input selection 
    GpioSfLpTimG = 12u,                  ///<LPTim Timer GATE input selection 
}en_gpio_sf_tim_g_t;

/**
 *******************************************************************************
 ** \brief GPIO SF-Secondary Function timer ETR type selection data type definition
 ******************************************************************************/
typedef enum en_gpio_sf_tim_e
{
    GpioSfTim0E  = 0u,                   ///<Tim0 Timer ETR input selection 
    GpioSfTim1E  = 3u,                   ///<Tim1 Timer ETR input selection 
    GpioSfTim2E  = 6u,                   ///<Tim2 Timer ETR input selection 
    GpioSfTim3E  = 9u,                   ///<Tim3 Timer ETR input selection 
    GpioSfLpTimE = 12u,                  ///<LPTim Timer ETR input selection 
}en_gpio_sf_tim_e_t;

/**
 *******************************************************************************
 ** \brief GPIO 辅助功能（SF-Secondary Function）定时器捕获输入类型选择数据类型定义
 ******************************************************************************/
typedef enum en_gpio_sf_tim_c
{
    GpioSfTim0CA = 0u,                   ///<Tim0 Timer CHA input selection 
    GpioSfTim1CA = 3u,                   ///<Tim1 Timer CHA input selection 
    GpioSfTim2CA = 6u,                   ///<Tim2 Timer CHA input selection 
    GpioSfTim3CA = 9u,                   ///<Tim3 Timer CH0A input selection 
    GpioSfTim3CB = 12u,                  ///<Tim3 Timer CH0B input selection 
}en_gpio_sf_tim_c_t;

/**
 *******************************************************************************
 ** \brief GPIO SF-Secondary Function PCA capture selection data type definition
 ******************************************************************************/
typedef enum en_gpio_sf_pca
{
    GpioSfPcaCH0 = 0u,                   ///<PCA_CH0 capture port input selection 
    GpioSfPcaECI = 3u,                   ///<PCA ECI clock input selection 
}en_gpio_sf_pca_t;

/**
 *******************************************************************************
 ** \brief GPIO Port configuration structure definition
 ******************************************************************************/
typedef struct
{
    en_gpio_dir_t       enDir;           ///< Port direction configuration
    en_gpio_drv_t       enDrv;           ///< Port drive capability configuration
    en_gpio_pupd_t      enPuPd;          ///< Pull-down configuration on the port
    en_gpio_od_t        enOD;            ///< Port open drain output configuration
    en_gpio_ctrl_mode_t enCtrlMode;      ///< Port input/output value register Bus control mode configuration
}stc_gpio_config_t;

/*******************************************************************************
 * Global definitions
 ******************************************************************************/
 
/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
  Global function prototypes (definition in C source)
*******************************************************************************/
 ///< GPIO IO initialization / deinitialization
en_result_t Gpio_Init(en_gpio_port_t enPort, en_gpio_pin_t enPin, stc_gpio_config_t *pstcGpioCfg);
 
///< GPIO Get port input level
boolean_t   Gpio_GetInputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);
uint16_t    Gpio_GetInputData(en_gpio_port_t enPort);

///< GPIO Set port output
///< GPIO Port output level configuration and acquisition
en_result_t Gpio_WriteOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin, boolean_t bVal);
boolean_t   Gpio_ReadOutputIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);
///< GPIO Port/pin output level set
en_result_t Gpio_SetPort(en_gpio_port_t enPort, uint16_t u16ValMsk);
en_result_t Gpio_SetIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);
///< GPIO Port/pin output level clear
en_result_t Gpio_ClrPort(en_gpio_port_t enPort, uint16_t u16ValMsk);
en_result_t Gpio_ClrIO(en_gpio_port_t enPort, en_gpio_pin_t enPin);
///< GPIO Port output level set and clear settings
en_result_t Gpio_SetClrPort(en_gpio_port_t enPort, uint32_t u32ValMsk);

///< GPIO Set the port to analog
en_result_t Gpio_SetAnalogMode(en_gpio_port_t enPort, en_gpio_pin_t enPin);

///< GPIO Set the port to the port multiplexing function.
en_result_t Gpio_SetAfMode(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_af_t enAf);

///< GPIO Port interrupt control function enabled/disabled
en_result_t Gpio_EnableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType);
en_result_t Gpio_DisableIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin, en_gpio_irqtype_t enType);
///< GPIO Interrupt flag acquisition
boolean_t   Gpio_GetIrqStatus(en_gpio_port_t enPort, en_gpio_pin_t enPin);
///< GPIO Interrupt flag clear
en_result_t Gpio_ClearIrq(en_gpio_port_t enPort, en_gpio_pin_t enPin);

///< GPIO Port accessibility configuration
///< GPIO Interrupt mode configuration
en_result_t Gpio_SfIrqModeConfig(en_gpio_sf_irqmode_t enIrqMode);
///< GPIO IR output polarity configuration
en_result_t Gpio_SfIrPolConfig(en_gpio_sf_irpol_t enIrPolMode);
///< GPIO HCLK output configuration
en_result_t Gpio_SfHClkOutputConfig(en_gpio_sf_hclkout_g_t enGate, en_gpio_sf_hclkout_div_t enDiv);
///< GPIO PCLK output configuration
en_result_t Gpio_SfPClkOutputConfig(en_gpio_sf_pclkout_g_t enGate, en_gpio_sf_pclkout_div_t enDiv);
///< GPIO External clock input configuration
en_result_t Gpio_SfExtClkConfig(en_gpio_sf_ssn_extclk_t enExtClk);
///< GPIO SPI SSN input configuration
en_result_t Gpio_SfSsnConfig(en_gpio_sf_ssnspi_t enSpi, en_gpio_sf_ssn_extclk_t enSsn);
///< GPIO Timer Gated input configuration
en_result_t Gpio_SfTimGConfig(en_gpio_sf_tim_g_t enTimG, en_gpio_sf_t enSf);
///< GPIO Timer ETR selection configuration
en_result_t Gpio_SfTimEConfig(en_gpio_sf_tim_e_t enTimE, en_gpio_sf_t enSf);
///< GPIO Timer Capture input configuration
en_result_t Gpio_SfTimCConfig(en_gpio_sf_tim_c_t enTimC, en_gpio_sf_t enSf);
///< GPIO PCA capture selection configuration
en_result_t Gpio_SfPcaConfig(en_gpio_sf_pca_t enPca, en_gpio_sf_t enSf);


//@} // GpioGroup

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
