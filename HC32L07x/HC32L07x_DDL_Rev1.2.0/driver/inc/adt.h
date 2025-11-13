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
 * @file   adt.h
 *
 * @brief  Header file for ADT functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

#ifndef __ADT_H__
#define __ADT_H__

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"


/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup AdtGroup Advance Timer (ADT)
  **
 ******************************************************************************/
//@{

/******************************************************************************
 * Global type definitions
 ******************************************************************************/


 /**
 ******************************************************************************
 ** \brief ADT CHx channel definition
 *****************************************************************************/
typedef enum en_adt_CHxX_port
{
    AdtCHxA    = 0u,            ///< CHx A channel
    AdtCHxB    = 1u,            ///< CHx B channel
}en_adt_CHxX_port_t;

 /**
 ******************************************************************************
 ** \brief ADT TRIG port definition
 *****************************************************************************/
typedef enum en_adt_trig_port
{
    AdtTrigA = 0u, ///< TIMx trigger A port
    AdtTrigB = 1u, ///< TIMx trigger B port
    AdtTrigC = 2u, ///< TIMx trigger C port
    AdtTrigD = 3u, ///< TIMx trigger D port
}en_adt_trig_port_t;

/**
 ******************************************************************************
 ** \brief ADT General Control - Z-phase input mask cycle number
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_gconr_zmsk
{
    AdtZMaskDis = 0u, ///< Z-phase input mask function disabled
    AdtZMask4Cyl = 1u, ///< Z-phase input is masked for 4 count cycles after position count overflow or underflow
    AdtZMask8Cyl = 2u, ///< Z-phase input is masked for 8 count cycles after position count overflow or underflow
    AdtZMask16Cyl = 3u, ///< The Z-phase input is masked for 16 counts after a position count overflow or underflow.
}en_adt_gconr_zmsk_t;

/**
 ******************************************************************************
 ** \brief ADT General Control - Count Clock Selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_cnt_ckdiv
{
    AdtClkPClk0        = 0u,         ///< PCLK0
    AdtClkPClk0Div2    = 1u,         ///< PCLK0/2
    AdtClkPClk0Div4    = 2u,         ///< PCLK0/4
    AdtClkPClk0Div8    = 3u,         ///< PCLK0/8
    AdtClkPClk0Div16   = 4u,         ///< PCLK0/16
    AdtClkPClk0Div64   = 5u,         ///< PCLK0/64
    AdtClkPClk0Div256  = 6u,         ///< PCLK0/256
    AdtClkPClk0Div1024 = 7u,         ///< PCLK0/1024
}en_adt_cnt_ckdiv_t;

/**
 ******************************************************************************
 ** \brief ADT counting mode
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_cnt_mode
{
    AdtSawtoothMode = 0u, ///< Sawtooth mode
    AdtTriangleModeA = 4u, ///< Triangle A mode
    AdtTriangleModeB = 5u, ///< Triangle wave B mode
}en_adt_cnt_mode_t;

/**
 ******************************************************************************
 ** \brief ADT count direction
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_cnt_dir
{
    AdtCntDown = 0u, ///< Count down
    AdtCntUp = 1u, ///< Count up
}en_adt_cnt_dir_t;

/**
 ******************************************************************************
 ** \brief ADT general comparison base
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_compare
{
    AdtCompareA = 0u, ///< General comparison base A
    AdtCompareB = 1u, ///< General comparison base B
    AdtCompareC = 2u, ///< General comparison base C
    AdtCompareD = 3u, ///< General comparison base D
}en_adt_compare_t;

/**
 ******************************************************************************
 ** \brief ADT special comparison base
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_special_compare
{
    AdtSpclCompA = 0u, ///< Special comparison base A
    AdtSpclCompB = 1u, ///< Special comparison base B
}en_adt_special_compare_t;

/**
 ******************************************************************************
 ** \brief ADT Port Control - TIMx Output State Control
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_disval
{
    AdtTIMxDisValNorm = 0u, ///< When the condition selected from forced output disabling conditions 0-3 is met, the CHx port outputs normal output.
    AdtTIMxDisValHiZ = 1u, ///< When the condition selected from forced output disabling conditions 0-3 is met, the CHx port outputs high impedance.
    AdtTIMxDisValLow = 2u, ///< When the condition selected from forced output disabling conditions 0-3 is met, the CHx port outputs a low level.
    AdtTIMxDisValHigh = 3u, ///< When the selected condition among forced output disabling conditions 0-3 is met, the CHx port outputs a high level.
}en_adt_pconr_disval_t;

/**
 ******************************************************************************
 ** \brief ADT Port Control - CHx Forced Output Disabling Condition
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_dissel
{
    AdtCHxDisSel0 = 0u, ///< Select forced output disabling condition 0
    AdtCHxDisSel1 = 1u, ///< Select forced output disabling condition 1
    AdtCHxDisSel2 = 2u, ///< Select forced output disabling condition 2
    AdtCHxDisSel3 = 3u, ///< Select forced output disabling condition 3
}en_adt_pconr_dissel_t;

/**
 ******************************************************************************
 ** \brief ADT Port Control - Port Status Setting When CHx Period Values Match
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_perc
{
    AdtCHxPeriodLow = 0u, ///< When the counter value is equal to the period value, the CHx port output remains low.
    AdtCHxPeriodHigh = 1u, ///< When the counter value is equal to the period value, the CHx port output is set high.
    AdtCHxPeriodKeep = 2u, ///< When the counter value is equal to the period value, the CHx port output is set to the previous state.
    AdtCHxPeriodInv = 3u, ///< When the counter value and the period value are equal, the CHx port output is set to an inverted level.
}en_adt_pconr_perc_t;

/**
 ******************************************************************************
 ** \brief ADT Port Control - Port Status Setting When the CHx Compare Value Matches
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_cmpc
{
    AdtCHxCompareLow = 0u, ///< When the counter value and GCMxR are equal, the CHx port output remains at a low level.
    AdtCHxCompareHigh = 1u, ///< When the counter value and GCMxR are equal, the CHx port output is set to a high level.
    AdtCHxCompareKeep = 2u, ///< When the counter value and GCMxR are equal, the CHx port output is set to the previous state.
    AdtCHxCompareInv = 3u, ///< When the counter value equals GCMxR, the CHx port output is set to the inverted level.
}en_adt_pconr_cmpc_t;

/**
 ******************************************************************************
 ** \brief ADT Port Control - CHx Port Output
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_port_out
{
    AdtCHxPortOutLow = 0u, ///< Set the CHx port output to a low level.
    AdtCHxPortOutHigh = 1u, ///< Set the CHx port output to a high level.
}en_adt_pconr_port_out_t;

/**
 ******************************************************************************
 ** \brief ADT Port Control - CHx Port Function Mode Selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_capc
{
    AdtCHxCompareOutput = 0u, ///< Set the CHx port to the compare output function
    AdtCHxCompareInput = 1u, ///< Set the CHx port to the capture input function
}en_adt_pconr_capc_t;

/**
 ******************************************************************************
 ** \brief ADT Port Control - CHx Count Start/Stop Port State Selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_stastps
{
    AdtCHxStateSelSS = 0u, ///< When counting starts or stops, the CHx port output is determined by STACB and STPCB
    AdtCHxStateSelKeep = 1u, ///< When counting starts or stops, the CHx port output is set to the previous state.
}en_adt_pconr_stastps_t;

/**
 ******************************************************************************
 ** \brief ADT Dead Band Control - CHx Dead Band Separation Setting
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_dconr_sepa
{
    AdtCHxDtSeperate = 0u, ///< DTUAR and DTDAR are set separately
    AdtCHxDtEqual = 1u, ///< The DTDAR and DTUAR values are automatically equal
}en_adt_dconr_sepa_t;

/**
 ******************************************************************************
 ** \brief ADT Filter Control - TRIx/TIMxIx Port Filter Sampling Reference Clock Selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_fconr_nofick
{
    AdtFltClkPclk0 = 0u, ///< PCLK0
    AdtFltClkPclk0Div4 = 1u, ///< PCLK0/4
    AdtFltClkPclk0Div16 = 2u, ///< PCLK0/16
    AdtFltClkPclk0Div64 = 3u, ///< PCLK0/64
}en_adt_fconr_nofick_t;

/**
 ******************************************************************************
 ** \brief ADT valid period - TIMx valid period selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_vperr_pcnts
{
    AdtPeriodCnts0 = 0u, ///< Valid period selection function disabled
    AdtPeriodCnts1 = 1u, ///< Valid every 1 cycle
    AdtPeriodCnts2 = 2u, ///< Valid every 2 cycles
    AdtPeriodCnts3 = 3u, ///< Valid every 3 cycles
    AdtPeriodCnts4 = 4u, ///< Valid every 4 cycles
    AdtPeriodCnts5 = 5u, ///< Valid every 5 cycles
    AdtPeriodCnts6 = 6u, ///< Valid every 6 cycles
    AdtPeriodCnts7 = 7u, ///< Valid every 7 cycles
}en_adt_vperr_pcnts_t;

/**
 ******************************************************************************
 ** \brief ADT Effective Period - Count Condition Selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_vperr_pcnte
{
    AdtPeriodCnteDisable = 0u, ///< Disable the effective period selection function
    AdtPeriodCnteMin = 1u, ///< Sawtooth wave counts at overflow or underflow points or triangle wave troughs as counting conditions
    AdtPeriodCnteMax = 2u, ///< Sawtooth wave counts at overflow or underflow points or triangle wave peaks as counting conditions
    AdtPeriodCnteBoth = 3u, ///< Sawtooth wave counts at overflow or underflow points or triangle wave peaks or troughs as counting conditions
}en_adt_vperr_pcnte_t;

/**
 ******************************************************************************
 ** \brief ADT Port Trigger Control - Trigger Source Selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_ttrig_trigxs
{
    AdtTrigxSelPA3 = 0u, ///< PA3
    AdtTrigxSelPB3 = 1u, ///< PB3 
    AdtTrigxSelPC3 = 2u, ///< PC3 
    AdtTrigxSelPD3 = 3u, ///< PD3 
    AdtTrigxSelPA7 = 4u, ///< PA7 
    AdtTrigxSelPB7 = 5u, ///< PB7 
    AdtTrigxSelPC7 = 6u, ///< PC7 
    AdtTrigxSelPD7 = 7u, ///< PD7 
    AdtTrigxSelPA11 = 8u, ///< PA11 
    AdtTrigxSelPB11 = 9u, ///< PB11 
    AdtTrigxSelPC11 = 10u, ///< PC11 
    AdtTrigxSelPD1 = 11u, ///< PD1 
    AdtTrigxSelPA15 = 12u, ///< PA15 AdtTrigxSelPB15 = 13u, ///< PB15
    AdtTrigxSelPC15 = 14u, ///< PC15
    AdtTrigxSelPD5 = 15u, ///< PD5
}en_adt_ttrig_trigxs_t;

/**
 ******************************************************************************
 ** \brief ADT AOS Trigger Control - AOSx Trigger Source Selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_itrig_iaosxs
{
    AdtAosxTrigSelTim0Int = 0u, ///< TIM0_INT
    AdtAosxTrigSelTim1Int = 1u, ///< TIM1_INT
    AdtAosxTrigSelTim2Int = 2u, ///< TIM2_INT 
    AdtAosxTrigSelLpTimInt = 3u, ///< LPTIMER_INT 
    AdtAosxTrigSelTim4Int = 4u, ///< TIM4_INT 
    AdtAosxTrigSelTim5Int = 5u, ///< TIM5_INT 
    AdtAosxTrigSelTim6Int = 6u, ///< TIM6_INT 
    AdtAosxTrigSelUart0Int = 7u, ///< UART0_INT 
    AdtAosxTrigSelUart1Int = 8u, ///< UART1_INT 
    AdtAosxTrigSelLpUartInt = 9u, ///< LPUART_INT 
    AdtAosxTrigSelVc0Int = 10u, ///< VC0_INT 
    AdtAosxTrigSelVc1Int = 11u, ///< VC1_INT
    AdtAosxTrigSelRtcInt = 12u, ///< RTC_INT
    AdtAosxTrigSelPcaInt = 13u, ///< PCA_INT
    AdtAosxTrigSelSpiInt = 14u, ///< SPI_INT
    AdtAosxTrigSelAdcInt = 15u, ///< ADC_INT
}en_adt_itrig_iaosxs_t;

/**
 ******************************************************************************
 ** \brief ADT hardware (start/stop/clear/capture) event trigger selection
 **
 ** \note
 ******************************************************************************/

typedef enum en_adt_hw_trig
{
    AdtHwTrigAos0 = 0u, ///< Event trigger 0 from AOS is valid
    AdtHwTrigAos1 = 1u, ///< Event trigger 1 from AOS is valid
    AdtHwTrigAos2 = 2u, ///< Event trigger 2 from AOS is valid
    AdtHwTrigAos3 = 3u, ///< Event trigger 3 from AOS is valid
    AdtHwTrigCHxARise = 4u, ///< CHxA port is sampled on the rising edge
    AdtHwTrigCHxAFall = 5u, ///< CHxA port is sampled on the falling edge
    AdtHwTrigCHxBRise = 6u, ///< CHxB port is sampled on the rising edge
    AdtHwTrigCHxBFall = 7u, ///< CHxB port is sampled on the falling edge
    AdtHwTrigTimTriARise = 8u, ///< TIMTRIA port samples to the rising edge
    AdtHwTrigTimTriAFall = 9u, ///< TIMTRIA port samples to the falling edge
    AdtHwTrigTimTriBRise = 10u, ///< TIMTRIB port samples to the rising edge
    AdtHwTrigTimTriBFall = 11u, ///< TIMTRIB port samples to the falling edge
    AdtHwTrigTimTriCRise = 12u, ///< TIMTRIC port samples to the rising edge
    AdtHwTrigTimTriCFall = 13u, ///< TIMTRIC port samples to the falling edge
    AdtHwTrigTimTriDRise = 14u, ///< TIMTRID port samples to the rising edge
    AdtHwTrigTimTriDFall = 15u, ///< TIMTRID port samples to the falling edge
    AdtHwTrigEnd = 16u,
}en_adt_hw_trig_t;

/**
 ******************************************************************************
 ** \brief ADT hardware (increment/decrement) event trigger selection
 **
 ** \note
 ******************************************************************************/

typedef enum en_adt_hw_cnt
{
    AdtHwCntCHxALowCHxBRise = 0u, ///< When CHxA is low, CHxB is sampled on the rising edge.
    AdtHwCntCHxALowCHxBFall = 1u, ///< When CHxA is low, CHxB is sampled on the falling edge.
    AdtHwCntCHxAHighCHxBRise = 2u, ///< When CHxA is high, CHxB is sampled on the rising edge.
    AdtHwCntCHxAHighCHxBFall = 3u, ///< When CHxA is high, CHxB is sampled on the falling edge.
    AdtHwCntCHxBLowCHxARise = 4u, ///< When CHxB is low, CHxA is sampled on the rising edge.
    AdtHwCntCHxBLowCHxAFall = 5u, ///< When CHxB is low, CHxA is sampled on the falling edge.
    AdtHwCntCHxBHighChxARise = 6u, ///< When CHxB is high, CHxA is sampled on the rising edge.
    AdtHwCntCHxBHighCHxAFall = 7u, ///< When CHxB is high, CHxA is sampled on the falling edge.
    AdtHwCntTimTriARise = 8u, ///< When TIMTriA is sampled on the rising edge.
    AdtHwCntTimTriAFall = 9u, ///< TIMTRIA port samples to the falling edge
    AdtHwCntTimTriBRise = 10u, ///< TIMTRIB port samples to the rising edge
    AdtHwCntTimTriBFall = 11u, ///< TIMTRIB port samples to the falling edge
    AdtHwCntTimTriCRise = 12u, ///< TIMTRIC port samples to the rising edge
    AdtHwCntTimTriCFall = 13u, ///< TIMTRIC port samples to the falling edge
    AdtHwCntTimTriDRise = 14u, ///< TIMTRID port samples to the rising edge
    AdtHwCntTimTriDFall = 15u, ///< TIMTRID port samples to the falling edge
    AdtHwCntAos0 = 16u, ///< Event trigger 0 from AOS is valid
    AdtHwCntAos1 = 17u, ///< Event trigger 1 from AOS is valid
    AdtHwCntAos2 = 18u, ///< Event trigger 2 from AOS is valid
    AdtHwCntAos3 = 19u, ///< Event trigger 3 from AOS is valid
    AdtHwCntMax = 20u,
}en_adt_hw_cnt_t;

/**
 ******************************************************************************
 ** \brief ADT port brake polarity control
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_ptbrk_polarity
{
    AdtPtBrkHigh = 0u, ///< Port brake polarity high level valid
    AdtPtBrkLow = 1u, ///< Port brake polarity low level valid
}en_adt_ptbrk_polarity_t;

/**
 ******************************************************************************
 ** \brief ADT PWM spread spectrum count selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pwm_dither_type
{
    AdtPwmDitherUnderFlow = 0u, ///< PWM spread spectrum counter underflow
    AdtPwmDitherOverFlow = 1u, ///< PWM spread spectrum counter overflow
}en_adt_pwm_dither_type_t;

/**
 ******************************************************************************
 ** \brief ADT interrupt type
 **
 ** \note
 ******************************************************************************/

typedef enum en_adt_irq_type
{
    AdtCMAIrq = 0u, ///< Count match A (or capture input) interrupt
    AdtCMBIrq = 1u, ///< Count match B (or capture input) interrupt
    AdtCMCIrq = 2u, ///< Count match C interrupt
    AdtCMDIrq = 3u, ///< Count match D interrupt
    AdtOVFIrq = 6u, ///< Overflow match interrupt
    AdtUDFIrq = 7u, ///< Underflow match interrupt
    AdtDTEIrq = 8u, ///< Dead time error interrupt
    AdtSAMLIrq = 14u, ///< Same as low interrupt
    AdtSAMHIrq = 15u, ///< Same as high interrupt
}en_adt_irq_type_t;

typedef enum en_adt_state_type
{
    AdtCMAF = 0, ///< Count match A flag
    AdtCMBF = 1, ///< Count match B flag
    AdtCMCF = 2, ///< Count match C flag
    AdtCMDF = 3, ///< Count match D flag
    AdtOVFF = 6, ///< Overflow match flag
    AdtUDFF = 7, ///< Underflow match flag
    AdtDTEF = 8, ///< Dead time error flag
    AdtCMSAUF = 9, ///< Up-count dedicated comparison reference value match A flag
    AdtCMSADF = 10, ///< Down-count dedicated comparison reference value match B flag
    AdtCMSBUF = 11, ///< Up-count dedicated comparison reference value match A flag
    AdtCMSBDF = 12, ///< Down-count dedicated comparison reference value match B flag
    AdtCntDir = 31, ///< Count direction
}en_adt_state_type_t;

/**
 ******************************************************************************
 ** \brief ADT software synchronization configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_sw_sync
{
    boolean_t bAdTim4; ///< Timer 4
    boolean_t bAdTim5; ///< Timer 5
    boolean_t bAdTim6; ///< Timer 6
}stc_adt_sw_sync_t;

/**
 ******************************************************************************
 ** \brief ADT AOS trigger configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_aos_trig_cfg
{
    en_adt_itrig_iaosxs_t enAos0TrigSrc; ///< AOS0 trigger source selection
    en_adt_itrig_iaosxs_t enAos1TrigSrc; ///< AOS1 trigger source selection
    en_adt_itrig_iaosxs_t enAos2TrigSrc; ///< AOS2 trigger source selection
    en_adt_itrig_iaosxs_t enAos3TrigSrc; ///< AOS3 trigger source selection
}stc_adt_aos_trig_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT interrupt trigger configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_irq_trig_cfg
{
    boolean_t bAdtSpecilMatchBTrigDmaEn; ///< Specialized comparison reference value match B enables DMA triggering
    boolean_t bAdtSpecilMatchATrigDmaEn; ///< Specialized comparison reference value match A enables DMA triggering
    boolean_t bAdtUnderFlowTrigDmaEn; ///< Underflow match enables DMA triggering
    boolean_t bAdtOverFlowTrigDmaEn; ///< Overflow match enables DMA triggering
    boolean_t bAdtCntMatchDTrigDmaEn; ///< Count match D enables DMA triggering
    boolean_t bAdtCntMatchCTrigDmaEn; ///< Count match C enables DMA triggering
    boolean_t bAdtCntMatchBTrigDmaEn; ///< Count match B enables DMA triggering
    boolean_t bAdtCntMatchATrigDmaEn; ///< Count match A enables DMA triggering
    boolean_t bAdtSpecilMatchBTrigEn; ///< Dedicated comparison reference value match B enables ADC triggering
    boolean_t bAdtSpecilMatchATrigEn; ///< Dedicated comparison reference value match A enables ADC triggering
    boolean_t bAdtUnderFlowTrigEn; ///< Underflow match enables ADC triggering
    boolean_t bAdtOverFlowTrigEn; ///< Overflow match enables ADC triggering
    boolean_t bAdtCntMatchDTrigEn; ///< Count match D enables ADC triggering
    boolean_t bAdtCntMatchCTrigEn; ///< Count match C enables ADC triggering
    boolean_t bAdtCntMatchBTrigEn; ///< Count match B enables ADC triggering
    boolean_t bAdtCntMatchATrigEn; ///< Count match A enables ADC triggering
}stc_adt_irq_trig_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT Trig port configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_port_trig_cfg
{
    en_adt_ttrig_trigxs_t enTrigSrc; ///< Trigger source selection
    boolean_t bFltEn; ///< Trigger source capture input filter enable
    en_adt_fconr_nofick_t enFltClk; ///< Filter sampling reference clock
}stc_adt_port_trig_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT Z-phase input mask function configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_zmask_cfg
{
    en_adt_gconr_zmsk_t enZMaskCycle; ///< Z-phase input mask count cycle selection
    boolean_t bFltPosCntMaksEn; ///< During the mask cycle for Z-phase input, the position counter clear function is disabled (FALSE) or disabled (TRUE)
    boolean_t bFltRevCntMaksEn;MaksEn; ///< During the mask period of the Z-phase input, the revolution counter's counting function is unmasked (FALSE) or masked (TRUE).
}stc_adt_zmask_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT TIMxX port configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_TIMxX_port_cfg
{
    en_adt_pconr_capc_t enCap; ///< Port function mode
    boolean_t bOutEn; ///< Output enable
    en_adt_pconr_perc_t enPerc; ///< Port status when the period value matches
    en_adt_pconr_cmpc_t enCmpc; ///< Port status when the comparison value matches
    en_adt_pconr_stastps_t enStaStp; ///< Count start and stop port state selection
    en_adt_pconr_port_out_t enStaOut; ///< Count start port output state
    en_adt_pconr_port_out_t enStpOut; ///< Count stop port output state
    en_adt_pconr_disval_t enDisVal; ///< Output state control when forced output is disabled
    en_adt_pconr_dissel_t enDisSel; ///< Forced output disable condition selection
    boolean_t bFltEn; ///< Port capture input filter enable
    en_adt_fconr_nofick_t enFltClk; ///< Port filter sampling reference clock
}stc_adt_CHxX_port_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT brake port configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_break_port_cfg
{
    boolean_t bPortEn; ///< Port enable
    en_adt_ptbrk_polarity_t enPol; ///< Polarity selection
}stc_adt_break_port_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT invalid condition 3 configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_disable_3_cfg
{
    stc_adt_break_port_cfg_t stcBrkPtCfg[16]; ///< Brake port configuration
    boolean_t bFltEn; ///< Brake port filter enable
    en_adt_fconr_nofick_t enFltClk; ///< Filter sampling reference clock
}stc_adt_disable_3_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT invalid condition 1 configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_disable_1_cfg
{
    boolean_t bTim6OutSH; ///< TIM6 output high
    boolean_t bTim5OutSH; ///< TIM5 output high
    boolean_t bTim4OutSH; ///< TIM4 output high
    boolean_t bTim6OutSL; ///< TIM6 output low
    boolean_t bTim5OutSL; ///< TIM5 output low
    boolean_t bTim4OutSL; ///< TIM4 output is low
}stc_adt_disable_1_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT PWM spread spectrum counter configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_pwm_dither_cfg
{
    en_adt_pwm_dither_type_t enAdtPDType; ///< PWM spread spectrum counter selection
    boolean_t bTimxBPDEn; ///< PWM channel B spread spectrum enable
    boolean_t bTimxAPDEn; ///< PWM channel A spread spectrum enable
}stc_adt_pwm_dither_cfg_t;


/**
 ******************************************************************************
 ** \brief ADT basic counter configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_basecnt_cfg
{
    en_adt_cnt_mode_t enCntMode; ///< Counting mode
    en_adt_cnt_dir_t enCntDir; ///< Counting direction
    en_adt_cnt_ckdiv_t enCntClkDiv; ///< Counting clock selection
}stc_adt_basecnt_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT counting state
 ** \note
 ******************************************************************************/
typedef struct stc_adt_cntstate_cfg
{
    uint16_t u16Counter; ///< Current counter value
    boolean_t enCntDir; ///< Count direction
    uint8_t u8ValidPeriod; ///< Valid period count
    boolean_t bCMSBDF; ///< Comparison reference value match B flag for down counting
    boolean_t bCMSBUF; ///< Comparison reference value match A flag for up counting
    boolean_t bCMSADF; ///< Comparison reference value match B flag for down counting
    boolean_t bCMSAUF; ///< Comparison reference value match A flag for up counting
    boolean_t bDTEF; ///< Dead time error flag
    boolean_t bUDFF; ///< Underflow match flag
    boolean_t bOVFF; ///< Overflow match flag
    boolean_t bCMDF; ///< Count match D flag
    boolean_t bCMCF; ///< Count match C flag
    boolean_t bCMBF; ///< Count match B flag
    boolean_t bCMAF; ///< Count match A flag
}stc_adt_cntstate_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT valid count period
 ** \note
 ******************************************************************************/
typedef struct stc_adt_validper_cfg
{
    en_adt_vperr_pcnts_t enValidCnt; ///< Valid period selection
    en_adt_vperr_pcnte_t enValidCdt; ///< Valid period count condition
    boolean_t bPeriodD; ///< General signal valid period selection D
    boolean_t bPeriodC; ///< General signal valid period selection C
    boolean_t bPeriodB; ///< General signal valid period selection B
    boolean_t bPeriodA; ///< General signal valid period selection A
}stc_adt_validper_cfg_t;

/******************************************************************************
 * Global definitions
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//Configure hardware increment event
en_result_t Adt_CfgHwCntUp(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_cnt_t enAdtHwCntUp);
//Clear hardware increment event
en_result_t Adt_ClearHwCntUp(M0P_ADTIM_TypeDef *ADTx);
//Configure hardware decrement event
en_result_t Adt_CfgHwCntDwn(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_cnt_t enAdtHwCntDwn);
//Clear hardware decrement event
en_result_t Adt_ClearHwCntDwn(M0P_ADTIM_TypeDef *ADTx);
//Configure hardware start event
en_result_t Adt_CfgHwStart(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwStart);
//Clear hardware start event
en_result_t Adt_ClearHwStart(M0P_ADTIM_TypeDef *ADTx);
//Enable hardware start event
en_result_t Adt_EnableHwStart(M0P_ADTIM_TypeDef *ADTx);
//Disable hardware start event
en_result_t Adt_DisableHwStart(M0P_ADTIM_TypeDef *ADTx);
//Configure hardware stop event
en_result_t Adt_CfgHwStop(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwStop);
//Clear hardware stop event
en_result_t Adt_ClearHwStop(M0P_ADTIM_TypeDef *ADTx);
//Enable hardware stop event
en_result_t Adt_EnableHwStop(M0P_ADTIM_TypeDef *ADTx);
//Disable hardware stop event
en_result_t Adt_DisableHwStop(M0P_ADTIM_TypeDef *ADTx);
//Configure hardware clear event
en_result_t Adt_CfgHwClear(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwClear);
//Clear hardware clear event
en_result_t Adt_ClearHwClear(M0P_ADTIM_TypeDef *ADTx);
//Enable hardware clear event
en_result_t Adt_EnableHwClear(M0P_ADTIM_TypeDef *ADTx);
//Disable hardware clear event
en_result_t Adt_DisableHwClear(M0P_ADTIM_TypeDef *ADTx);
//Configure A channel hardware capture event
en_result_t Adt_CfgHwCaptureA(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwCaptureA);
//Clear the hardware capture event for channel A
en_result_t Adt_ClearHwCaptureA(M0P_ADTIM_TypeDef *ADTx);
//Configure the hardware capture event for channel B
en_result_t Adt_CfgHwCaptureB(M0P_ADTIM_TypeDef *ADTx, en_adt_hw_trig_t enAdtHwCaptureB);
//Clear the hardware capture event for channel B
en_result_t Adt_ClearHwCaptureB(M0P_ADTIM_TypeDef *ADTx);
//Software synchronization start
en_result_t Adt_SwSyncStart(stc_adt_sw_sync_t* pstcAdtSwSyncStart);
//Software synchronization stop
en_result_t Adt_SwSyncStop(stc_adt_sw_sync_t* pstcAdtSwSyncStop);
//Software synchronization clear
en_result_t Adt_SwSyncClear(stc_adt_sw_sync_t* pstcAdtSwSyncClear);
//Get software synchronization status
en_result_t Adt_GetSwSyncState(stc_adt_sw_sync_t* pstcAdtSwSyncState);
//AOS trigger configuration
en_result_t Adt_AosTrigCfg(stc_adt_aos_trig_cfg_t* pstcAdtAosTrigCfg);
//Interrupt trigger configuration
en_result_t Adt_IrqTrigCfg(M0P_ADTIM_TypeDef *ADTx,
                              stc_adt_irq_trig_cfg_t* pstcAdtIrqTrigCfg);
//Port trigger configuration
en_result_t Adt_PortTrigCfg(en_adt_trig_port_t enAdtTrigPort,
                               stc_adt_port_trig_cfg_t* pstcAdtPortTrigCfg);
//CHxX port configuration
en_result_t Adt_CHxXPortCfg(M0P_ADTIM_TypeDef *ADTx,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                stc_adt_CHxX_port_cfg_t* pstcAdtCHxXCfg);
//Enable port brake
en_result_t Adt_EnableBrakePort(uint8_t port, stc_adt_break_port_cfg_t* pstcAdtBrkPtCfg);
//Clear port brake
void Adt_ClearBrakePort(void);
//Invalid condition 3 configuration (port brake)
en_result_t Adt_Disable3Cfg(stc_adt_disable_3_cfg_t* pstcAdtDisable3);
//Software brake enable/disable (only applies when invalid condition 3 is enabled)
en_result_t Adt_SwBrake(boolean_t bSwBrk);
//Get port brake flag
boolean_t Adt_GetPortBrakeFlag(void);
//Clear port brake flag
void Adt_ClearPortBrakeFlag(void);
//Invalid condition 1 configuration (brake for both high and low)
en_result_t Adt_Disable1Cfg(stc_adt_disable_1_cfg_t* pstcAdtDisable1);
//Get the same high and low brake flags
boolean_t Adt_GetSameBrakeFlag(void);
//Clear the same high and low brake flags
void Adt_ClearSameBrakeFlag(void);
//PWM spread spectrum configuration
en_result_t Adt_PwmDitherCfg(M0P_ADTIM_TypeDef *ADTx, stc_adt_pwm_dither_cfg_t* pstcAdtPwmDitherCfg);
//AdvTimer initialization
en_result_t Adt_Init(M0P_ADTIM_TypeDef *ADTx, stc_adt_basecnt_cfg_t* pstcAdtBaseCntCfg);
//AdvTimer deinitialization
en_result_t Adt_DeInit(M0P_ADTIM_TypeDef *ADTx);
//AdvTimer start
en_result_t Adt_StartCount(M0P_ADTIM_TypeDef *ADTx);
//AdvTimer stop
en_result_t Adt_StopCount(M0P_ADTIM_TypeDef *ADTx);
//Set count value
en_result_t Adt_SetCount(M0P_ADTIM_TypeDef *ADTx, uint16_t u16Value);
//Get count value
uint16_t Adt_GetCount(M0P_ADTIM_TypeDef *ADTx);
//Clear count value
en_result_t Adt_ClearCount(M0P_ADTIM_TypeDef *ADTx);
//Get valid period count value
uint8_t Adt_GetVperNum(M0P_ADTIM_TypeDef *ADTx);
//Get status flag
boolean_t Adt_GetState(M0P_ADTIM_TypeDef *ADTx, en_adt_state_type_t enstate);
//Configure the counting period
en_result_t Adt_SetPeriod(M0P_ADTIM_TypeDef *ADTx, uint16_t u16Period);
//Configure the counting period buffer
en_result_t Adt_SetPeriodBuf(M0P_ADTIM_TypeDef *ADTx, uint16_t u16PeriodBuf);
//Clear the counting period buffer
en_result_t Adt_ClearPeriodBuf(M0P_ADTIM_TypeDef *ADTx);
//Configure the valid counting period
en_result_t Adt_SetValidPeriod(M0P_ADTIM_TypeDef *ADTx,
                               stc_adt_validper_cfg_t* pstcAdtValidPerCfg);
//Configure the compare output count compare value
en_result_t Adt_SetCompareValue(M0P_ADTIM_TypeDef *ADTx,
                                en_adt_compare_t enAdtCompare,
                                uint16_t u16Compare);
//Configure the general compare value/capture buffered value transfer
en_result_t Adt_EnableValueBuf(M0P_ADTIM_TypeDef *ADTx,
                                 en_adt_CHxX_port_t enAdtCHxXPort,
                                 boolean_t bCompareBufEn);
//Clear compare output count value/capture value buffer
en_result_t Adt_ClearValueBuf(M0P_ADTIM_TypeDef *ADTx,
                                     en_adt_CHxX_port_t enAdtCHxXPort);
//Get capture value
en_result_t Adt_GetCaptureValue(M0P_ADTIM_TypeDef *ADTx,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                uint16_t* pu16Capture);
//Get capture buffer value
en_result_t Adt_GetCaptureBuf(M0P_ADTIM_TypeDef *ADTx,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                uint16_t* pu16CaptureBuf);
//Set the upper reference value for the dead time
en_result_t Adt_SetDTUA(M0P_ADTIM_TypeDef *ADTx,
                        uint16_t u16Value);
//Set the lower reference value for the dead time
en_result_t Adt_SetDTDA(M0P_ADTIM_TypeDef *ADTx,
                        uint16_t u16Value);
//Configure the dead time function
en_result_t Adt_CfgDT(M0P_ADTIM_TypeDef *ADTx,
                         boolean_t bDTEn,
                         boolean_t bEqual);
//Configure interrupts
en_result_t Adt_CfgIrq(M0P_ADTIM_TypeDef *ADTx,
                          en_adt_irq_type_t enAdtIrq,
                          boolean_t bEn);
//Get interrupt flag
boolean_t Adt_GetIrqFlag(M0P_ADTIM_TypeDef *ADTx,
                         en_adt_irq_type_t enAdtIrq);
//Clear interrupt flag
en_result_t Adt_ClearIrqFlag(M0P_ADTIM_TypeDef *ADTx,
                             en_adt_irq_type_t enAdtIrq);
//Clear all interrupt flags
en_result_t Adt_ClearAllIrqFlag(M0P_ADTIM_TypeDef *ADTx);
//Set Z-phase input mask
en_result_t Adt_CfgZMask(M0P_ADTIM_TypeDef *ADTx, 
                            stc_adt_zmask_cfg_t* pstcAdtZMaskCfg);

//@} // ADT Group

#ifdef __cplusplus
}
#endif

#endif /* __ADT_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
