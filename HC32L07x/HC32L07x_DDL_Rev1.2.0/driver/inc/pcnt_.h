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
* @file pcnt.h 
* 
* @brief Header file for PCNT functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __PCNT_H__
#define __PCNT_H__

/***********************************************************************************
* Include files
**************************************************************************/
#include "ddl.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
******************************************************************************
** \defgroup PCNTGroup (PCNT)
**
**************************************************************************/
//@{

/**
*******************************************************************************
** function prototypes.
**************************************************************************/

/**
***********************************************************************************
** \brief PCNT S0 channel polarity selection
** \note PCNT_CTRL S0P
********************************************************************/
typedef enum
{
    PcntS0PNoinvert = 0u, // Do not invert the polarity of channel S0
    PcntS0PInvert = 1u // Invert the polarity of channel S0
}en_pcnt_s0polar_t;

/**
************************************************************************************
** \brief PCNT S1 channel polarity selection
** \note PCNT_CTRL S1P
************************************************************************/
typedef enum
{
    PcntS1PNoinvert = 0u, // Do not invert the polarity of channel S1
    PcntS1PInvert = 1u // Invert the polarity of channel S1
}en_pcnt_s1polar_t;

/**
*******************************************************************************
** \brief PCNT count direction selection
** \note PCNT_CTRL DIR
************************************************************************/
typedef enum
{
    PcntNDoubleDirAdd = 0u, // count up
    PcntNDoubleDirSub = 1u // count down
}en_pcnt_dir_t;

/**
********************************************************************************
** \brief PCNT count clock selection
** \note PCNT_CTRL ClkSel
************************************************************************/
typedef enum
{
    PcntCLKPclk = 1u, // PCLK
    PcntCLKXtl = 2u, // XTL
    PcntCLKRcl = 3u // RCL
}en_pcnt_clksel_t;

/**
****************************************************************************
** \brief PCNT pulse counting mode selection
** \note PCNT_CTRL Mode
************************************************************************/
typedef enum
{
    PcntSingleMode = 1u, // Single-channel pulse counting mode
    PcntSpecialMode = 2u, // Dual-channel non-orthogonal pulse counting mode
    PcntDoubleMode = 3u // Dual-channel orthogonal pulse counting mode
}en_pcnt_mode_t;

/**
********************************************************************************
** \brief PCNT status
** \note PCNT_IFR & PCNT_ICR & PCNT_IEN
***************************************************************************/
typedef enum
{
    PcntS1E = 7, // S1 channel pulse decoding error
    PcntS0E = 6, // S0 channel pulse decoding error
    PcntBB = 5, // Pulse decoding error
    PcntFE = 4, // Sampling period pulse decoding error
    PcntDIR = 3, // Reverse change interrupt
    PcntTO = 2, // Timeout interrupt flag
    PcntOV = 1, // Overflow interrupt flag
    PcntUF = 0, // Underflow interrupt flag
}en_pcnt_itfce_t;

/**
****************************************************************************
** \brief PCNT Status Register 1 PCNT_SR1
** \note PCNT_SR1 : DIR
***********************************************************************/
typedef enum
{
    PcntDoubleDirAdd = 0, // Dual-channel quadrature pulse count up
    PcntDoubleDirSub = 1 // Dual-channel quadrature pulse count up
}en_pcnt_sr1dir_t;

/**
****************************************************************************
** \brief PCNT Observation Output Selection Register PCNT_DBG
** \note PCNT_DBG: DBG
***********************************************************************/
typedef enum
{
    PcntDBGZero = 0, // Fixed to 0
    PcntDBGSxA = 1, // Pulse output via S0A/S1A after synchronization
    PcntDBGSxP = 2, // Pulse output via S0P/S1P after polarity selection
    PcntDBGSxPF = 3 // Pulse output via S0PF/S1PF after filtering
}en_pcnt_dbg_t;

typedef enum
{
    PcntDirUp = 0, //Increment count
    PcntDirDown = 1 //Decrement count
}en_pent_dir_t;
/**
****************************************************************************
** \brief PCNT overall configuration structure
***********************************************************************/
typedef struct stc_pcnt_cfg
{
    en_pcnt_s0polar_t Pcnt_S0Sel; //S0 channel polarity selection
    en_pcnt_s1polar_t Pcnt_S1Sel; // S1 channel polarity selection
    en_pcnt_clksel_t Pcnt_Clk; // Count clock selection
    en_pcnt_mode_t Pcnt_Mode; // Pulse counting mode selection
    boolean_t Pcnt_FltEn; // Pulse width filter enable control PCNT_FLT: EN
    uint8_t Pcnt_DebTop; // Counter threshold PCNT_FLT: DebTop
    uint16_t Pcnt_ClkDiv; // Filter clock division coefficient PCNT_FLT: ClkDiv
    boolean_t Pcnt_TocrEn; // Timeout function enable control bit PCNT_TOCR: EN
    uint16_t Pcnt_TocrTh; // Timeout threshold PCNT_TOCR: TH
    en_pcnt_dbg_t Pcnt_Dbg; // Observation output selection register PCNT_DBG 
    en_pent_dir_t Pcnt_Dir;
}stc_pcnt_initstruct_t;


/****************************************************************************** 
* Global variable declarations ('extern', definition in C source) 
******************************************************************************/

/****************************************************************************** 
* Global function prototypes (definition in C source) 
******************************************************************************/
extern boolean_t Pcnt_Cmd(boolean_t NewState);
extern en_result_t Pcnt_SetB2T(uint16_t value);
extern en_result_t Pcnt_SetB2C(uint16_t value);
extern en_result_t Pcnt_SetT2C(void);
extern void Pcnt_Init(stc_pcnt_initstruct_t* InitStruct);
extern void Pcnt_ItCfg(en_pcnt_itfce_t IT_Src, boolean_t NewState);
extern boolean_t Pcnt_GetItStatus(en_pcnt_itfce_t IT_Src);
extern void Pcnt_ClrItStatus(en_pcnt_itfce_t IT_Src);
extern uint16_t Pcnt_GetCnt(void);
extern uint16_t Pcnt_GetTop(void);
extern uint16_t Pcnt_GetBuf(void);
extern void Pcnt_SetCnt(uint16_t value);
extern void Pcnt_SetBuf(uint16_t value);
extern void Pcnt_SetTop(uint16_t value);
//@} // PCNT Group

#ifdef __cplusplus
#endif

#endif /* __PCNT_H__ */
/************************************************************************************ 
* EOF (not truncated) 
******************************************************************************/
