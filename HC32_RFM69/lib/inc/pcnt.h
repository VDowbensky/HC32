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
/** \file pcnt.h
 **
 ** Headerfile for PCNT functions
 ** @link PCNT Group Some description @endlink 
 **
 ** History:
 **   - 2018-04-15   Devi     First Version
 **
 ******************************************************************************/

#ifndef __PCNT_H__
#define __PCNT_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l136.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup PCNTGroup  (PCNT)
  **
 ******************************************************************************/
//@{

/**
 *******************************************************************************
 ** function prototypes.
 ******************************************************************************/
/**
************************************************** *****************************
  ** \brief PCNT S1 channel polarity selection
  ** \note
  ************************************************** ****************************/
typedef enum en_pcnt_s1sel
{
    S1P_Noinvert = 0u, ///<<S1 channel normal polarity 
    S1P_Invert   = 1u, ///<<S1 channel reverse polarity 
}en_pcnt_s1sel_t;

/**
************************************************** *****************************
  ** \brief PCNT S0 channel polarity selection
  ** \note
  ************************************************** ****************************/
typedef enum en_pcnt_s0sel
{
    S0P_Noinvert = 0u, ///<<S0 channel normal polarity 
    S0P_Invert   = 1u, ///<<S0 channel reverse polarity 
}en_pcnt_s0sel_t;

/**
************************************************** *****************************
  ** \brief PCNT count direction selection
  ** \note
  ************************************************** ****************************/
typedef enum en_pcnt_direcsel
{
    Direct_Add   = 0u, ///<<Count up
    Direct_Sub   = 1u, ///<<Countdown
}en_pcnt_direcsel_t;

/**
************************************************** *****************************
  ** \brief PCNT count clock selection
  ** \note
  ************************************************** ****************************/
typedef enum en_pcnt_clksel
{
    CLK_Pclk   = 1u, ///<<PCLK
    CLK_Xtl    = 2u, ///<<XTL
    CLK_Rcl    = 3u, ///<<RCL     
}en_pcnt_clksel_t;

/**
************************************************** *****************************
  ** \brief PCNT pulse count mode selection
  ** \note
  ************************************************** ****************************/
typedef enum en_pcnt_modesel
{
    Single_Mode   = 1u, ///<<Single channel pulse counting mode
    Special_Mode  = 2u, ///<<Dual channel non-orthogonal pulse counting mode
    Double_Mode   = 3u, ///<<Dual channel quadrature pulse counting mode  
}en_pcnt_modesel_t;

/**
 ******************************************************************************
 ** \brief PCNT status
 *****************************************************************************/
typedef enum en_pcnt_status
{
    PCNT_S1E            = 0x80,   ///<S1 channel pulse decoding error
    PCNT_S0E            = 0x40,   ///<S0 channel pulse decoding error   
    PCNT_BB             = 0x20,   ///<Pulse decoding error    
    PCNT_FE             = 0x10,   ///<Sampling period pulse decoding error
    PCNT_DIR            = 0x08,   ///<Reverse change interrupt    
    PCNT_TO             = 0x04,   ///<Timeout interrupt   
    PCNT_OV             = 0x02,   ///<Overflow interrupt flag
    PCNT_UF             = 0x01,   ///<Underflow interrupt flag     
}en_pcnt_status_t;

/**
************************************************** ****************************
  ** \brief PCNT global configuration structure
  ************************************************** ***************************/
typedef struct stc_pcnt_config
{
    en_pcnt_s1sel_t     bS1Sel;          ///< S1 channel polarity selection
	  en_pcnt_s0sel_t     bS0Sel;          ///< S0 channel polarity selection
    en_pcnt_direcsel_t  u8Direc;         ///< Counting direction selection    	
	  en_pcnt_clksel_t    u8Clk;           ///< Counting clock selection
    en_pcnt_modesel_t   u8Mode;          ///< Pulse counting mode selection
    boolean_t           bFLTEn;          ///< Filter control enable
    uint8_t             u8FLTDep;        ///< Filter threshold
    uint8_t             u8FLTClk;        ///< Filter clock
    boolean_t           bTOEn;           ///< Timeout enable
    uint16_t            u16TODep;         ///< Timeout threshold
	  uint8_t             u8IrqStatus;     ///< Interrupt mode
    boolean_t           bIrqEn;           ///< Interrupt enable
    func_ptr_t          pfnIrqCb;         ///< Interrupt callback function
}stc_pcnt_config_t;

//PCNT Interrupt
void Pcnt_IRQHandler(void);

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
///< PCNT initialization
en_result_t PCNT_Init(stc_pcnt_config_t*  pstcPcntConfig);
///< PCNT deinitialization
void PCNT_DeInit(void);
///< PCNT parameter settings
en_result_t PCNT_Parameter(uint8_t start,uint8_t end);
///< PCNT Read PCNT direction
en_pcnt_direcsel_t PCNT_Direction(void);
///< PCNT Read PCNT count value
uint16_t PCNT_Count(void);
///< PCNT Read PCNT overflow value
uint16_t PCNT_TopCount(void);
///< PCNT Set PCNT
void PCNT_Run(boolean_t work);
///< PCNT acquisition status
boolean_t PCNT_GetStatus(en_pcnt_status_t enStatus);
///< PCNT clear status
void PCNT_ClrStatus(en_pcnt_status_t enStatus);
///< PCNT setting interrupt
void PCNT_SetIrqStatus(en_pcnt_status_t enStatus);


//@} // PCNT Group

#ifdef __cplusplus
#endif

#endif /* __PCNT_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


