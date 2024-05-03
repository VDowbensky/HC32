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
/** \file adt.h
 **
 ** Headerfile for Advance Timer functions
 ** @link ADT Group Some description @endlink
 **
 **   - 2018-04-18 Husj    First Version
 **
 ******************************************************************************/

#ifndef __ADT_H__
#define __ADT_H__

/******************************************************************************
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
 ** \brief High performance timer selection
 *****************************************************************************/
typedef enum en_adt_unit
{
    AdtTIM4    = 0u,            ///< TIM4
    AdtTIM5    = 1u,            ///< TIM5
    AdtTIM6    = 2u,            ///< TIM6
}en_adt_unit_t;

 /**
 ******************************************************************************
 ** \brief ADT CHx port definition
 *****************************************************************************/
typedef enum en_adt_CHxX_port
{
    AdtCHxA    = 0u,            ///< CHx A port
    AdtCHxB    = 1u,            ///< CHx B port
}en_adt_CHxX_port_t;

 /**
 ******************************************************************************
 ** \brief ADT TRIG port definition
 *****************************************************************************/
typedef enum en_adt_trig_port
{
    AdtTrigA    = 0u,            ///< TIMx Trigger A port
    AdtTrigB    = 1u,            ///< TIMx Trigger B port
    AdtTrigC    = 2u,            ///< TIMx Trigger C port
    AdtTrigD    = 3u,            ///< TIMx Trigger D port
}en_adt_trig_port_t;

/**
 ******************************************************************************
 ** \brief ADT Universal Control - Z Phase Input Masking Cycles
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_gconr_zmsk
{
    AdtZMaskDis   = 0u,      ///< Z phase input masking function is invalid
    AdtZMask4Cyl  = 1u,      ///< The Z phase input is blocked after 4 count cycles after the position count overflows or underflows
    AdtZMask8Cyl  = 2u,      ///< The Z phase input is blocked within 8 count cycles after the position count overflows or underflows
    AdtZMask16Cyl = 3u,      ///< The Z phase input is blocked after 16 count cycles after the position count overflows or underflows
}en_adt_gconr_zmsk_t;

/**
 ******************************************************************************
 ** \brief ADT Universal Control - Counter Clock Selection
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
    AdtSawtoothMode  = 0u,          ///< Sawtooth mode
    AdtTriangleModeA = 4u,          ///< Triangle wave A mode
    AdtTriangleModeB = 5u,          ///< Triangle wave B mode
}en_adt_cnt_mode_t;

/**
 ******************************************************************************
 ** \brief ADT counting direction
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_cnt_dir
{
    AdtCntDown = 0u,      ///< Countdown
    AdtCntUp   = 1u,      ///< Count up
}en_adt_cnt_dir_t;

/**
 ******************************************************************************
 ** \brief ADT General Comparison Benchmark
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_compare
{
    AdtCompareA = 0u,            ///< General Comparison Benchmark A
    AdtCompareB = 1u,            ///< General Comparison Benchmark B
    AdtCompareC = 2u,            ///< General Comparison Benchmark C
    AdtCompareD = 3u,            ///< General Comparison Benchmark D
}en_adt_compare_t;

/**
 ******************************************************************************
 ** \brief ADT-specific benchmark
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_special_compare
{
    AdtSpclCompA = 0u,            ///< Dedicated benchmark A
    AdtSpclCompB = 1u,            ///< Dedicated benchmark B
}en_adt_special_compare_t;

/**
 ******************************************************************************
 ** \brief ADT Port Control - TIMx Output Status Control
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_disval
{
    AdtTIMxDisValNorm = 0u,     ///< When the selected condition of the forced output invalid condition 0~3 is established, the CHx port is normally output.
    AdtTIMxDisValHiZ  = 1u,     ///< When the selected condition of the forced output invalid condition 0~3 is established, the CHx port outputs a high-impedance state.
    AdtTIMxDisValLow  = 2u,     ///< When the selected condition of the forced output invalid condition 0~3 is established, the CHx port outputs a low level.
    AdtTIMxDisValHigh = 3u,     ///< When the selected condition of the forced output invalid condition 0~3 is established, the CHx port outputs a high level.
}en_adt_pconr_disval_t;

/**
 ******************************************************************************
 ** \brief ADT port control - CHx forced output invalid condition selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_dissel
{
    AdtCHxDisSel0 = 0u,        ///< Select forced output invalid condition 0
    AdtCHxDisSel1 = 1u,        ///< Select forced output invalid condition 1
    AdtCHxDisSel2 = 2u,        ///< Select forced output invalid condition 2
    AdtCHxDisSel3 = 3u,        ///< Select forced output invalid condition 3
}en_adt_pconr_dissel_t;

/**
 ******************************************************************************
 ** \brief ADT port control - Port status setting when CHx period value matches
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_perc
{
    AdtCHxPeriodLow  = 0u,      ///< When the counter count value is equal to the period value, the CHx port output remains low.
    AdtCHxPeriodHigh = 1u,      ///< When the counter count value is equal to the period value, the CHx port output is set to high level.
    AdtCHxPeriodKeep = 2u,      ///< When the counter count value is equal to the period value, the CHx port output is set to the previous state.
    AdtCHxPeriodInv  = 3u,      ///< When the counter count value is equal to the period value, the CHx port output is set to the reverse level.
}en_adt_pconr_perc_t;

/**
 ******************************************************************************
 ** \brief ADT port control - Port status setting when CHx comparison value matches
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_cmpc
{
    AdtCHxCompareLow  = 0u,     ///< When the counter count value is equal to GCMxR, the CHx port output remains low.
    AdtCHxCompareHigh = 1u,     ///< When the counter count value is equal to GCMxR, the CHx port output is set to high level.
    AdtCHxCompareKeep = 2u,     ///< When the counter count value is equal to GCMxR, the CHx port output is set to the previous state.
    AdtCHxCompareInv  = 3u,     ///< When the counter count value is equal to GCMxR, the CHx port output is set to the reverse level.
}en_adt_pconr_cmpc_t;

/**
 ******************************************************************************
 ** \brief ADT port control - CHx port output
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_port_out
{
    AdtCHxPortOutLow  = 0u,  ///< CHx port output is set to low
    AdtCHxPortOutHigh = 1u,  ///< CHx port output is set to high level
}en_adt_pconr_port_out_t;

/**
 ******************************************************************************
 ** \brief ADT port control - CHx port function mode selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_capc
{
    AdtCHxCompareOutput = 0u,   ///< CHx port is set to compare output function
    AdtCHxCompareInput  = 1u,   ///< CHx port is set to capture input function
}en_adt_pconr_capc_t;

/**
 ******************************************************************************
 ** \brief ADT port control - CHx count starts to stop port status selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pconr_stastps
{
    AdtCHxStateSelSS   = 0u,    ///< When the count starts or stops, the CHx port output is determined by STACB and STPCB.
    AdtCHxStateSelKeep = 1u,    ///< When the count starts or stops, the CHx port output is set to the previous state.
}en_adt_pconr_stastps_t;

/**
 ******************************************************************************
 ** \brief ADT dead zone control - CHx dead zone separation setting
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_dconr_sepa
{
    AdtCHxDtSeperate = 0u,      ///< DTUAR and DTDAR are set separately
    AdtCHxDtEqual    = 1u,      ///< The value of DTDAR and the value of DTUAR are automatically equal
}en_adt_dconr_sepa_t;

/**
 ******************************************************************************
 ** \brief ADT Filter Control - TRIx/TIMxIx Port Filter Sampling Reference Clock Selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_fconr_nofick
{
    AdtFltClkPclk0      = 0u,    ///< PCLK0
    AdtFltClkPclk0Div4  = 1u,    ///< PCLK0/4
    AdtFltClkPclk0Div16 = 2u,    ///< PCLK0/16
    AdtFltClkPclk0Div64 = 3u,    ///< PCLK0/64
}en_adt_fconr_nofick_t;

/**
 ******************************************************************************
 ** \brief ADT effective period - TIMx effective period selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_vperr_pcnts
{
    AdtPeriodCnts0 = 0u,         ///< Valid period selection function is invalid
    AdtPeriodCnts1 = 1u,         ///< Valid every 1 cycle
    AdtPeriodCnts2 = 2u,         ///< Valid every 2 cycles
    AdtPeriodCnts3 = 3u,         ///< Valid every 3 cycles
    AdtPeriodCnts4 = 4u,         ///< Valid every 4 cycles
    AdtPeriodCnts5 = 5u,         ///< Valid every 5 cycles
    AdtPeriodCnts6 = 6u,         ///< Valid every 6 cycles
    AdtPeriodCnts7 = 7u,         ///< Valid every 7 cycles
}en_adt_vperr_pcnts_t;

/**
 ******************************************************************************
 ** \brief ADT effective period - counting condition selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_vperr_pcnte
{
    AdtPeriodCnteDisable = 0u,     ///< Valid period selection function is invalid
    AdtPeriodCnteMin     = 1u,     ///< Sawtooth count up, underflow point or triangle wave trough as count condition
    AdtPeriodCnteMax     = 2u,     ///< Sawtooth count up, underflow point or triangle wave peak as count condition
    AdtPeriodCnteBoth    = 3u,     ///< Sawtooth count up, underflow point or triangle wave peak, trough as counting condition
}en_adt_vperr_pcnte_t;

/**
 ******************************************************************************
 ** \brief ADT port trigger control - trigger source selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_ttrig_trigxs
{
    AdtTrigxSelPA3  = 0u,    ///< PA3
    AdtTrigxSelPB3  = 1u,    ///< PB3
    AdtTrigxSelPC3  = 2u,    ///< PC3
    AdtTrigxSelPD3  = 3u,    ///< PD3
    AdtTrigxSelPA7  = 4u,    ///< PA7
    AdtTrigxSelPB7  = 5u,    ///< PB7
    AdtTrigxSelPC7  = 6u,    ///< PC7
    AdtTrigxSelPD7  = 7u,    ///< PD7
    AdtTrigxSelPA11 = 8u,    ///< PA11
    AdtTrigxSelPB11 = 9u,    ///< PB11
    AdtTrigxSelPC11 = 10u,   ///< PC11
    AdtTrigxSelPD1  = 11u,   ///< PD1
    AdtTrigxSelPA15 = 12u,   ///< PA15
    AdtTrigxSelPB15 = 13u,   ///< PB15
    AdtTrigxSelPC5  = 14u,   ///< PC5
    AdtTrigxSelPD5  = 15u,   ///< PD5
}en_adt_ttrig_trigxs_t;

/**
 ******************************************************************************
 ** \brief ADT AOS trigger control - AOSx trigger source selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_itrig_iaosxs
{
    AdtAosxTrigSelTim0Int   = 0u,    ///< TIM0_INT
    AdtAosxTrigSelTim1Int   = 1u,    ///< TIM1_INT
    AdtAosxTrigSelTim2Int   = 2u,    ///< TIM2_INT
    AdtAosxTrigSelLpTimInt  = 3u,    ///< LPTIMER_INT
    AdtAosxTrigSelTim4Int   = 4u,    ///< TIM4_INT
    AdtAosxTrigSelTim5Int   = 5u,    ///< TIM5_INT
    AdtAosxTrigSelTim6Int   = 6u,    ///< TIM6_INT
    AdtAosxTrigSelUart0Int  = 7u,    ///< UART0_INT
    AdtAosxTrigSelUart1Int  = 8u,    ///< UART1_INT
    AdtAosxTrigSelLpUartInt = 9u,    ///< LPUART_INT
    AdtAosxTrigSelVc0Int    = 10u,   ///< VC0_INT
    AdtAosxTrigSelVc1Int    = 11u,   ///< VC1_INT
    AdtAosxTrigSelRtcInt    = 12u,   ///< RTC_INT
    AdtAosxTrigSelPcaInt    = 13u,   ///< PCA_INT
    AdtAosxTrigSelSpiInt    = 14u,   ///< SPI_INT
    AdtAosxTrigSelAdcInt    = 15u,   ///< ADC_INT
}en_adt_itrig_iaosxs_t;

/**
 ******************************************************************************
 ** \brief ADT hardware (start/stop/clear/capture) event trigger selection
 **
 ** \note
 ******************************************************************************/

typedef enum en_adt_hw_trig
{
    AdtHwTrigAos0        = 0u,       ///< Event triggered from AOS is valid 0
    AdtHwTrigAos1        = 1u,       ///< Event trigger 1 from AOS is valid
    AdtHwTrigAos2        = 2u,       ///< Event trigger 2 from AOS is valid
    AdtHwTrigAos3        = 3u,       ///< Event trigger from AOS 3 is valid
    AdtHwTrigCHxARise    = 4u,       ///< CHxA port upsampled to rising edge
    AdtHwTrigCHxAFall    = 5u,       ///< CHxA port upsampled to falling edge
    AdtHwTrigCHxBRise    = 6u,       ///< CHxB port upsampled to rising edge
    AdtHwTrigCHxBFall    = 7u,       ///< CHxB port upsampled to falling edge
    AdtHwTrigTimTriARise = 8u,       ///< TIMTRIA port upsampled to rising edge
    AdtHwTrigTimTriAFall = 9u,       ///< TIMTRIA port upsampled to falling edge
    AdtHwTrigTimTriBRise = 10u,      ///< TIMTRIB port upsampled to rising edge
    AdtHwTrigTimTriBFall = 11u,      ///< TIMTRIB port upsampled to falling edge
    AdtHwTrigTimTriCRise = 12u,      ///< TIMTRIC port upsampled to rising edge
    AdtHwTrigTimTriCFall = 13u,      ///< TIMTRIC port upsampled to falling edge
    AdtHwTrigTimTriDRise = 14u,      ///< TIMTRID port upsampled to rising edge
    AdtHwTrigTimTriDFall = 15u,      ///< TIMTRID port upsampled to falling edge
    AdtHwTrigEnd         = 16u,
}en_adt_hw_trig_t;

/**
 ******************************************************************************
 ** \brief ADT hardware (advance/decrement) event trigger selection
 **
 ** \note
 ******************************************************************************/

typedef enum en_adt_hw_cnt
{
    AdtHwCntCHxALowCHxBRise   = 0u,      ///< When the CHxA port is low, the CHxB port is sampled to the rising edge.
    AdtHwCntCHxALowCHxBFall   = 1u,      ///< When the CHxA port is low, the CHxB port is sampled to the falling edge.
    AdtHwCntCHxAHighCHxBRise  = 2u,      ///< When the CHxA port is high, the CHxB port is sampled to the rising edge.
    AdtHwCntCHxAHighCHxBFall  = 3u,      ///< When the CHxA port is high, the CHxB port is sampled to the falling edge.
    AdtHwCntCHxBLowCHxARise   = 4u,      ///< When the CHxB port is low, the CHxA port is sampled to the rising edge.
    AdtHwCntCHxBLowCHxAFall   = 5u,      ///< When the CHxB port is low, the CHxA port is sampled to the falling edge.
    AdtHwCntCHxBHighChxARise  = 6u,      ///< When the CHxB port is high, the CHxA port is sampled to the rising edge.
    AdtHwCntCHxBHighCHxAFall  = 7u,      ///< When the CHxB port is high, the CHxA port is sampled to the falling edge.
    AdtHwCntTimTriARise       = 8u,      ///< TIMTRIA port upsampled to rising edge
    AdtHwCntTimTriAFall       = 9u,      ///< TIMTRIA port upsampled to falling edge
    AdtHwCntTimTriBRise       = 10u,     ///< TIMTRIB port upsampled to rising edge
    AdtHwCntTimTriBFall       = 11u,     ///< TIMTRIB port upsampled to falling edge
    AdtHwCntTimTriCRise       = 12u,     ///< TIMTRIC port upsampled to rising edge
    AdtHwCntTimTriCFall       = 13u,     ///< TIMTRIC port upsampled to falling edge
    AdtHwCntTimTriDRise       = 14u,     ///< TIMTRID port upsampled to rising edge
    AdtHwCntTimTriDFall       = 15u,     ///< TIMTRID port upsampled to falling edge
    AdtHwCntAos0              = 16u,     ///< Event triggered from AOS is valid 0
    AdtHwCntAos1              = 17u,     ///< Event trigger 2 from AOS is valid
    AdtHwCntAos2              = 18u,     ///< Event trigger 3 from AOS is valid
    AdtHwCntAos3              = 19u,     ///< Event trigger 4 from AOS is valid
    AdtHwCntMax               = 20u,
}en_adt_hw_cnt_t;

/**
 ******************************************************************************
 ** \brief ADT port brake polarity control
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_ptbrk_polarity
{
    AdtPtBrkHigh = 0u,     ///< Port brake polarity is active high
    AdtPtBrkLow  = 1u,     ///< Port brake polarity is active low
}en_adt_ptbrk_polarity_t;

/**
 ******************************************************************************
 ** \brief ADT PWM spread frequency count selection
 **
 ** \note
 ******************************************************************************/
typedef enum en_adt_pwm_dither_type
{
    AdtPwmDitherUnderFlow = 0u,    ///< PWM spread count under overflow
    AdtPwmDitherOverFlow  = 1u,    ///< PWM spread frequency count overflow
}en_adt_pwm_dither_type_t;

/**
 ******************************************************************************
 ** \brief ADT interrupt type
 **
 ** \note
 ******************************************************************************/

typedef enum en_adt_irq_type
{
    AdtCMAIrq  = 0u,     ///< Count match A (or capture input) interrupt
    AdtCMBIrq  = 1u,     ///< Count match B (or capture input) interrupt
    AdtCMCIrq  = 2u,     ///< Count matching C interrupt
    AdtCMDIrq  = 3u,     ///< Count match D interrupt
    AdtOVFIrq  = 6u,     ///< Overflow match interrupt
    AdtUDFIrq  = 7u,     ///< Underflow match interrupt
    AdtDTEIrq  = 8u,     ///< Dead time error interrupt
    AdtSAMLIrq = 14u,    ///< Same low interrupt
    AdtSAMHIrq = 15u,    ///< Same high interrupt
}en_adt_irq_type_t;

/**
 ******************************************************************************
 ** \brief ADT software synchronization configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_sw_sync
{
    boolean_t               bAdTim4;      ///< Timer 4
    boolean_t               bAdTim5;      ///< Timer 5
    boolean_t               bAdTim6;      ///< Timer 6

}stc_adt_sw_sync_t;

/**
 ******************************************************************************
 ** \brief ADT AOS trigger configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_aos_trig_cfg
{
    en_adt_itrig_iaosxs_t   enAos0TrigSrc;      ///< AOS0 Trigger source selection
    en_adt_itrig_iaosxs_t   enAos1TrigSrc;      ///< AOS1 Trigger source selection
    en_adt_itrig_iaosxs_t   enAos2TrigSrc;      ///< AOS2 Trigger source selection
    en_adt_itrig_iaosxs_t   enAos3TrigSrc;      ///< AOS3 Trigger source selection
}stc_adt_aos_trig_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT Interrupt trigger configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_irq_trig_cfg
{
    boolean_t   bAdtSpecilMatchBTrigDmaEn;  ///< Dedicated compare reference match B enable trigger DMA
    boolean_t   bAdtSpecilMatchATrigDmaEn;  ///< Dedicated compare reference match A enable trigger DMA
    boolean_t   bAdtUnderFlowTrigDmaEn;     ///< Underflow match enable trigger DMA
    boolean_t   bAdtOverFlowTrigDmaEn;      ///< Overflow match enable trigger DMA
    boolean_t   bAdtCntMatchDTrigDmaEn;     ///< Count match D enable trigger DMA
    boolean_t   bAdtCntMatchCTrigDmaEn;     ///< Count match C enable trigger DMA
    boolean_t   bAdtCntMatchBTrigDmaEn;     ///< Count match B enable trigger DMA
    boolean_t   bAdtCntMatchATrigDmaEn;     ///< Count match A enable trigger DMA
    boolean_t   bAdtSpecilMatchBTrigEn;     ///< Dedicated compare reference match B enable trigger ADC
    boolean_t   bAdtSpecilMatchATrigEn;     ///< Dedicated compare reference match A enable trigger ADC
    boolean_t   bAdtUnderFlowTrigEn;        ///< Underflow match enable trigger ADC
    boolean_t   bAdtOverFlowTrigEn;         ///< Overflow match enable trigger ADC
    boolean_t   bAdtCntMatchDTrigEn;        ///< Count match D enable trigger ADC
    boolean_t   bAdtCntMatchCTrigEn;        ///< Count match C enable trigger ADC
    boolean_t   bAdtCntMatchBTrigEn;        ///< Count match B enable trigger ADC
    boolean_t   bAdtCntMatchATrigEn;        ///< Count match A enable trigger ADC
	

}stc_adt_irq_trig_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT Trig port configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_port_trig_cfg
{
    en_adt_ttrig_trigxs_t   enTrigSrc;      ///< Trigger source selection
    boolean_t               bFltEn;         ///< Trigger source capture input filter enable
    en_adt_fconr_nofick_t   enFltClk;       ///< Filtered sampling reference clock
}stc_adt_port_trig_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT Z phase input shielding function configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_zmask_cfg
{
    en_adt_gconr_zmsk_t     enZMaskCycle;              ///< Z phase input mask count cycle selection
    boolean_t               bFltPosCntMaksEn;          ///< The zeroing function of the position counter is not masked (FALSE) or masked (TRUE) during the mask period of the Z phase input.
    boolean_t               bFltRevCntMaksEn;          ///< The counting function of the revolution counter is not masked (FALSE) or masked (TRUE) during the mask period of the Z phase input.
}stc_adt_zmask_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT TIMxX port configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_TIMxX_port_cfg
{
    en_adt_pconr_capc_t     enCap;      ///< Port function mode
    boolean_t               bOutEn;     ///< Output enable
    en_adt_pconr_perc_t     enPerc;     ///< Port status when the period value matches
    en_adt_pconr_cmpc_t     enCmpc;     ///< Port status when the comparison value matches
    en_adt_pconr_stastps_t  enStaStp;   ///< Count start stop port status selection
    en_adt_pconr_port_out_t enStaOut;   ///< Count start port output status
    en_adt_pconr_port_out_t enStpOut;   ///< Count stop port output status
    en_adt_pconr_disval_t   enDisVal;   ///< Output state control when forced output is invalid
    en_adt_pconr_dissel_t   enDisSel;   ///< Forced output invalid condition selection
    boolean_t               bFltEn;     ///< Port capture input filtering enable
    en_adt_fconr_nofick_t   enFltClk;   ///< Port filter sampling reference clock
}stc_adt_CHxX_port_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT brake port configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_break_port_cfg
{
    boolean_t               bPortEn;    ///< Port enable
    en_adt_ptbrk_polarity_t enPol;      ///< Polarity selection
}stc_adt_break_port_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT invalid condition 3 configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_disable_3_cfg
{
    stc_adt_break_port_cfg_t    stcBrkPtCfg[16];    ///< Brake port configuration
    boolean_t                   bFltEn;             ///< Brake port filter enable
    en_adt_fconr_nofick_t       enFltClk;           ///< Filtered sampling reference clock
    boolean_t                   bSwBrk;             ///< Software brake
}stc_adt_disable_3_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT invalid condition 1 configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_disable_1_cfg
{
    boolean_t   bTim6OutSH;     ///< TIM6 output is the same height
    boolean_t   bTim5OutSH;     ///< TIM5 output is the same height
    boolean_t   bTim4OutSH;     ///< TIM4 output is the same height
    boolean_t   bTim6OutSL;     ///< TIM6 output is low
    boolean_t   bTim5OutSL;     ///< TIM5 output is low
    boolean_t   bTim4OutSL;     ///< TIM4 output is low
}stc_adt_disable_1_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT PWM spread spectrum count configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_pwm_dither_cfg
{
    en_adt_pwm_dither_type_t    enAdtPDType;    ///< PWM spread frequency count selection
    boolean_t   bTimxBPDEn;                     ///< PWM channel B spread spectrum enable
    boolean_t   bTimxAPDEn;                     ///< PWM channel A spread spectrum enable
}stc_adt_pwm_dither_cfg_t;


/**
 ******************************************************************************
 ** \brief ADT basic count configuration
 ** \note
 ******************************************************************************/
typedef struct stc_adt_basecnt_cfg
{
    en_adt_cnt_mode_t       enCntMode;      ///< Counting mode
    en_adt_cnt_dir_t        enCntDir;       ///< Counting direction
    en_adt_cnt_ckdiv_t      enCntClkDiv;    ///< Counting clock selection
}stc_adt_basecnt_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT count status
 ** \note
 ******************************************************************************/
typedef struct stc_adt_cntstate_cfg
{
    uint16_t         u16Counter;      ///< Current counter count value
    boolean_t        enCntDir;        ///< Counting direction
    uint8_t          u8ValidPeriod;   ///< Effective cycle count
    boolean_t        bCMSBDF;         ///< Count down the dedicated comparison reference value to match the B flag
    boolean_t        bCMSBUF;         ///< Up-counting dedicated comparison reference value matches A flag
    boolean_t        bCMSADF;         ///< Count down the dedicated comparison reference value to match the B flag
    boolean_t        bCMSAUF;         ///< Up-counting dedicated comparison reference value matches A flag
    boolean_t        bDTEF;           ///< Dead time error flag
    boolean_t        bUDFF;           ///< Underflow match flag
    boolean_t        bOVFF;           ///< Overflow matching flag
    boolean_t        bCMDF;           ///< Count matching D flag
    boolean_t        bCMCF;           ///< Count matching C flag
    boolean_t        bCMBF;           ///< Count matching B flag
    boolean_t        bCMAF;           ///< Count matching A flag
}stc_adt_cntstate_cfg_t;

/**
 ******************************************************************************
 ** \brief ADT effective counting period
 ** \note
 ******************************************************************************/
typedef struct stc_adt_validper_cfg
{
    en_adt_vperr_pcnts_t    enValidCnt;     ///< Effective period selection
    en_adt_vperr_pcnte_t    enValidCdt;     ///< Valid period count condition
    boolean_t               bPeriodD;       ///< General signal effective period selection D
    boolean_t               bPeriodC;       ///< General signal valid period selection C
    boolean_t               bPeriodB;       ///< General signal valid period selection B
    boolean_t               bPeriodA;       ///< General signal effective period selection A
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
en_result_t Adt_ConfigHwCntUp(en_adt_unit_t enAdtUnit, en_adt_hw_cnt_t enAdtHwCntUp);
en_result_t Adt_ClearHwCntUp(en_adt_unit_t enAdtUnit);
en_result_t Adt_ConfigHwCntDwn(en_adt_unit_t enAdtUnit, en_adt_hw_cnt_t enAdtHwCntDwn);
en_result_t Adt_ClearHwCntDwn(en_adt_unit_t enAdtUnit);
en_result_t Adt_ConfigHwStart(en_adt_unit_t enAdtUnit, en_adt_hw_trig_t enAdtHwStart);
en_result_t Adt_ClearHwStart(en_adt_unit_t enAdtUnit);
en_result_t Adt_EnableHwStart(en_adt_unit_t enAdtUnit);
en_result_t Adt_DisableHwStart(en_adt_unit_t enAdtUnit);
en_result_t Adt_ConfigHwStop(en_adt_unit_t enAdtUnit, en_adt_hw_trig_t enAdtHwStop);
en_result_t Adt_ClearHwStop(en_adt_unit_t enAdtUnit);
en_result_t Adt_EnableHwStop(en_adt_unit_t enAdtUnit);
en_result_t Adt_DisableHwStop(en_adt_unit_t enAdtUnit);
en_result_t Adt_ConfigHwClear(en_adt_unit_t enAdtUnit, en_adt_hw_trig_t enAdtHwClear);
en_result_t Adt_ClearHwClear(en_adt_unit_t enAdtUnit);
en_result_t Adt_EnableHwClear(en_adt_unit_t enAdtUnit);
en_result_t Adt_DisableHwClear(en_adt_unit_t enAdtUnit);
en_result_t Adt_ConfigHwCaptureA(en_adt_unit_t enAdtUnit, en_adt_hw_trig_t enAdtHwCaptureA);
en_result_t Adt_ClearHwCaptureA(en_adt_unit_t enAdtUnit);
en_result_t Adt_ConfigHwCaptureB(en_adt_unit_t enAdtUnit, en_adt_hw_trig_t enAdtHwCaptureB);
en_result_t Adt_ClearHwCaptureB(en_adt_unit_t enAdtUnit);

en_result_t Adt_SwSyncStart(stc_adt_sw_sync_t* pstcAdtSwSyncStart);
en_result_t Adt_SwSyncStop(stc_adt_sw_sync_t* pstcAdtSwSyncStop);
en_result_t Adt_SwSyncClear(stc_adt_sw_sync_t* pstcAdtSwSyncClear);
en_result_t Adt_GetSwSyncState(stc_adt_sw_sync_t* pstcAdtSwSyncState);

en_result_t Adt_AosTrigConfig(stc_adt_aos_trig_cfg_t* pstcAdtAosTrigCfg);

en_result_t Adt_IrqTrigConfig(en_adt_unit_t enAdtUnit,
                              stc_adt_irq_trig_cfg_t* pstcAdtIrqTrigCfg);

en_result_t Adt_PortTrigConfig(en_adt_trig_port_t enAdtTrigPort,
                               stc_adt_port_trig_cfg_t* pstcAdtPortTrigCfg);

en_result_t Adt_CHxXPortConfig(en_adt_unit_t enAdtUnit,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                stc_adt_CHxX_port_cfg_t* pstcAdtCHxXCfg);

en_result_t Adt_EnableBreakPort(uint8_t port, stc_adt_break_port_cfg_t* pstcAdtBrkPtCfg);
void Adt_ClearBrakePort(void);
en_result_t Adt_Disable3Cfg(stc_adt_disable_3_cfg_t* pstcAdtDisable3);
boolean_t Adt_GetPortBrakeFlag(void);
void Adt_ClearPortBrakeFlag(void);
en_result_t Adt_Disable1Cfg(stc_adt_disable_1_cfg_t* pstcAdtDisable1);
boolean_t Adt_GetSameBrakeFlag(void);
void Adt_ClearSameBrakeFlag(void);

en_result_t Adt_PwmDitherConfig(en_adt_unit_t enAdtUnit, stc_adt_pwm_dither_cfg_t* pstcAdtPwmDitherCfg);

en_result_t Adt_Init(en_adt_unit_t enAdtUnit, stc_adt_basecnt_cfg_t* pstcAdtBaseCntCfg);
en_result_t Adt_DeInit(en_adt_unit_t enAdtUnit);

en_result_t Adt_StartCount(en_adt_unit_t enAdtUnit);
en_result_t Adt_StopCount(en_adt_unit_t enAdtUnit);
en_result_t Adt_SetCount(en_adt_unit_t enAdtUnit, uint16_t u16Value);
uint16_t Adt_GetCount(en_adt_unit_t enAdtUnit);
en_result_t Adt_ClearCount(en_adt_unit_t enAdtUnit);
en_result_t Adt_GetCntState(en_adt_unit_t enAdtUnit, stc_adt_cntstate_cfg_t* pstcAdtCntState);
en_result_t Adt_SetPeriod(en_adt_unit_t enAdtUnit, uint16_t u16Period);
en_result_t Adt_SetPeriodBuf(en_adt_unit_t enAdtUnit, uint16_t u16PeriodBuf);
en_result_t Adt_ClearPeriodBuf(en_adt_unit_t enAdtUnit);
en_result_t Adt_SetValidPeriod(en_adt_unit_t enAdtUnit,
                               stc_adt_validper_cfg_t* pstcAdtValidPerCfg);
en_result_t Adt_SetCompareValue(en_adt_unit_t enAdtUnit,
                                en_adt_compare_t enAdtCompare,
                                uint16_t u16Compare);
en_result_t Adt_EnableValueBuf(en_adt_unit_t enAdtUnit,
                                 en_adt_CHxX_port_t enAdtCHxXPort,
                                 boolean_t bCompareBufEn);
en_result_t Adt_ClearValueBuf(en_adt_unit_t enAdtUnit,
                                     en_adt_CHxX_port_t enAdtCHxXPort);
en_result_t Adt_GetCaptureValue(en_adt_unit_t enAdtUnit,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                uint16_t* pu16Capture);
en_result_t Adt_GetCaptureBuf(en_adt_unit_t enAdtUnit,
                                en_adt_CHxX_port_t enAdtCHxXPort,
                                uint16_t* pu16CaptureBuf);

en_result_t Adt_SetDTUA(en_adt_unit_t enAdtUnit,
                        uint16_t u16Value);
en_result_t Adt_SetDTDA(en_adt_unit_t enAdtUnit,
                        uint16_t u16Value);
en_result_t Adt_ConfigDT(en_adt_unit_t enAdtUnit,
                         boolean_t bDTEn,
                         boolean_t bEqual);

en_result_t Adt_ConfigIrq(en_adt_unit_t enAdtUnit,
                          en_adt_irq_type_t enAdtIrq,
                          boolean_t bEn,
                          func_ptr_t pfnIrqCalbak);
en_result_t Adt_GetIrqFlag(en_adt_unit_t enAdtUnit,
                           en_adt_irq_type_t enAdtIrq,
                           boolean_t* pbFlag);
en_result_t Adt_ClearIrqFlag(en_adt_unit_t enAdtUnit,
                             en_adt_irq_type_t enAdtIrq);
en_result_t Adt_ConfigZMask(en_adt_unit_t enAdtUnit, 
                            stc_adt_zmask_cfg_t* pstcAdtZMaskCfg);

//@} // ADT Group

#ifdef __cplusplus
}
#endif

#endif /* __ADT_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
