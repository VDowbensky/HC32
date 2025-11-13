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
 * @file   trng.c
 *
 * @brief  Source file for TRNG functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "trng.h"
/**
 *******************************************************************************
 ** \addtogroup FlashGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
*****************************************************************************
** \brief Random number initialization (generating random numbers for the first time after power-up)
**
** \retval TRUE or FALSE
*****************************************************************************/
en_result_t Trng_Init(void)
{
    //==>>Generate 64-bit random number (first time after power-up)
    M0P_TRNG->CR_f.RNGCIR_EN = 1;
    //Mode configuration 0
    M0P_TRNG->MODE_f.LOAD    = 1;
    M0P_TRNG->MODE_f.FDBK    = 1;
    M0P_TRNG->MODE_f.CNT     = 6;
    //Generate random number 0
    M0P_TRNG->CR_f.RNG_RUN  = 1;
    while(M0P_TRNG->CR_f.RNG_RUN)
    {
        ;
    }
    
    //Mode configuration 1
    M0P_TRNG->MODE_f.LOAD    = 0;
    M0P_TRNG->MODE_f.FDBK    = 0;
    M0P_TRNG->MODE_f.CNT     = 4;
    //Generate random number 1
    M0P_TRNG->CR_f.RNG_RUN  = 1;
    while(M0P_TRNG->CR_f.RNG_RUN)
    {
        ;
    }

    ///Disable random source circuit to save power
    M0P_TRNG->CR_f.RNGCIR_EN = 0;
    
    return Ok;
}

/**
*********************************************************************
** \brief Generate random number (not the first time after power-on)
**
**
** \retval TRUE or FALSE
*****************************************************************************/
en_result_t Trng_Generate(void)
{
    //==>>Generate a 64-bit random number (not the first time generated after power-up)
    M0P_TRNG->CR_f.RNGCIR_EN = 1;
    
    //Mode configuration 0
    M0P_TRNG->MODE_f.LOAD    = 0;
    M0P_TRNG->MODE_f.FDBK    = 1;
    M0P_TRNG->MODE_f.CNT     = 6;
    //Generate random number 0
    M0P_TRNG->CR_f.RNG_RUN  = 1;
    while(M0P_TRNG->CR_f.RNG_RUN)
    {
        ;
    }
    
    //Mode configuration 1
    M0P_TRNG->MODE_f.FDBK    = 0;
    M0P_TRNG->MODE_f.CNT     = 4;
    M0P_TRNG->MODE_f.CNT     = 4;
    //Generate random number 1
    M0P_TRNG->CR_f.RNG_RUN  = 1;
    while(M0P_TRNG->CR_f.RNG_RUN)
    {
        ;
    }

    //Disable random source circuit to save power
    M0P_TRNG->CR_f.RNGCIR_EN = 0;    
    
    return Ok;
}

/**
*************************************************************************
** \brief Get random number
**
** \retval data0
*************************************************************************/
uint32_t Trng_GetData0(void)
{
    return M0P_TRNG->DATA0;
}

/**
*************************************************************************
** \brief Get random number
** 
** \retval data1 
*******************************************************************************/
uint32_t Trng_GetData1(void)
{
    return M0P_TRNG->DATA1;
}

//@} // TrngGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
