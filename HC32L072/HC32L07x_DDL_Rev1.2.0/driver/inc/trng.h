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
* @file trng.h 
* 
* @brief Header file for TRNG functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __TRNG_H__
#define __TRNG_H__

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
** \defgroup TrngGroup (TRNG) 
** 
******************************************************************************/
//@{

/** 
******************************************************************************* 
** function prototypes. 
******************************************************************************/

/************************************************************************************ 
*Global definitions **********************************************************************************/

/******************************************************************************
* Global variable declarations ('extern', definition in C source)
******************************************************************************/

/******************************************************************************************
* Global function prototypes (definition in C source)
**********************************************************************************/
///< Random number initialization (generating random numbers for the first time after power-up)
en_result_t Trng_Init(void);
///< Generate random numbers (not the first time after power-up)
en_result_t Trng_Generate(void);
///< Get a 64-bit random number (this function can be used to obtain the random value after executing the random number initialization or random number generation function)
uint32_t Trng_GetData0(void);
uint32_t Trng_GetData1(void);

//@} // Trng Group

#ifdef __cplusplus
#endif

#endif /* __TRNG_H__ */
/************************************************************************************ 
* EOF (not truncated) 
******************************************************************************/
