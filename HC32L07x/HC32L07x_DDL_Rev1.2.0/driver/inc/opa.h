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
* @file opa.h 
* 
* @brief Header file for OPA functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __OPA_H__
#define __OPA_H__

/************************************************************************************ 
* Include files 
******************************************************************************/
#include "ddl.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** 
****************************************************************************** 
** \defgroup OPAGroup (OPA) 
** 
******************************************************************************/
//@{

/** 
******************************************************************************* 
** function prototypes. 
******************************************************************************/

typedef enum
{ 
    Opa0 = 5, 
    Opa1 = 6, 
    Opa2 = 7, 
    Opa3 = 8, Opa4 = 9
}en_opa_t;
#define OPA_AZEN_Pos(Opax) ((uint32_t)((Opax)-(Opa0))) /* Calculate the corresponding teach-to-zero enable bit based on the OPA value */

typedef enum
{
    Opa_Dac0Buff = 10, /* DAC0 uses OP3 units to increase the buffer enable */
    Opa_Dac1Buff = 11 /* DAC0 uses OP3 units to increase the buffer enable */
}en_opa_dac_buff_t;

typedef enum
{
    Opa_Ch_Oen1 = 0u, /* OPA OUT1 */
    Opa_Ch_Oen2 = 1u, /* OPA OUT2 */
    Opa_Ch_Oen3 = 2u, /* OPA OUT3 */
    Opa_Ch_Oen4 = 3u, /* OPA OUT4 */
}en_opa_oenx_t;
#define OPA_CHANNEL_OUT_Pos(Opax, Opa_OutChx) ((uint32_t)((Opax)-(Opa0))*4 + (Opa_OutChx)) /* Calculate the specified output channel bit position using the OPA value. */

typedef enum
{
    Opa_M1Pclk = 0u,
    Opa_M2Pclk = 1u,
    Opa_M4Pclk = 2u,
    Opa_M8Pclk = 3u,
    Opa_M16Pclk = 4u,
    Opa_M32Pclk = 5u,
    Opa_M64Pclk = 6u,
    Opa_M128Pclk = 7u,
    Opa_M256Pclk = 8u,
    Opa_M512Pclk = 9u,
    Opa_M1024Pclk = 10u,
    Opa_M2048Pclk = 11u,
    Opa_M4096Pclk = 12u
}en_opa_clksrc_t;

typedef struct
{
    boolean_t bClk_sw_set; /* Automatic teach-to-zero selection 1: Enable software calibration. 0: Software calibration disabled, software-triggered calibration enabled */
    boolean_t bAz_pulse; /* Set to 1 for software calibration, set to 0 for software-triggered calibration */
    boolean_t bAdctr_en; /* When set to 1, ADC startup triggers OPA auto-calibration */
    en_opa_clksrc_t enClksrc; /* Auto-calibration pulse width setting */
}stc_opa_zconfig_t;

typedef struct
{
    boolean_t opa_ch1; /* OPA output 1 enable configuration */
    boolean_t opa_ch2; /* OPA output 2 enable configuration */
    boolean_t opa_ch3; /* OPA output 3 enable configuration */
    boolean_t opa_ch4; /* OPA output 4 enable configuration */
}stc_opa_oenx_config_t;

/****************************************************************************** 
* Global variable declarations ('extern', definition in C source) 
******************************************************************************/

/****************************************************************************** 
* Global function prototypes (definition in C source) 
******************************************************************************/
void Opa_OutChannelConfig(en_opa_t Opax, stc_opa_oenx_config_t OutChs);
void Opa_Cmd(en_opa_t Opax, boolean_t NewStatus);
void Opa_DacBufCmd(en_opa_dac_buff_t Buffx, boolean_t NewStatus);
void Opa_CalCmd(en_opa_t Opax, boolean_t NewStatus);
void Opa_CalConfig(stc_opa_zconfig_t* InitZero);
void Opa_CalSwTrig(void);

//@} // OPA Group

#ifdef __cplusplus
#endif

#endif /* __OPA_H__ */
/************************************************************************************ 
* EOF (not truncated) 
******************************************************************************/
