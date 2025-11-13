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
* @file i2c.h 
* 
* @brief Header file for I2C functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __I2C_H__
#define __I2C_H__

#include "ddl.h"


/** 
******************************************************************************* 
** \defgroup I2cGroup Inter-Integrated Circuit (I2C) 
** 
** 
******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/******************************************************************************/
/****************************************************************************** 
* Global type definitions 
******************************************************************************/ 

/** ******************************************************************************
** \brief I2C function configuration
*************************************************************************/
typedef enum en_i2c_func
{
    I2cModule_En = 6u, ///<I2C module enable
    I2cStart_En = 5u, ///<Start signal
    I2cStop_En = 4u, ///<Stop signal
    I2cAck_En = 2u, ///<Acknowledge signal
    I2cHlm_En = 0u, ///<High-speed enable
}en_i2c_func_t;

/**
********************************************************************************
** \brief I2C mode configuration
*****************************************************************************/
typedef enum en_i2c_mode
{
    I2cMasterMode = 0x40u, ///<I2C master mode
    I2cSlaveMode = 0x44u, ///<I2C slave mode
}en_i2c_mode_t;

/**
******************************************************************************
** \brief I2C initialization configuration structure
*****************************************************************************/
typedef struct stc_i2c_cfg
{
    uint32_t u32Pclk; ///<Pclk setting (Hz)
    uint32_t u32Baud; ///<I2C communication baud rate (Hz)
    en_i2c_mode_t enMode; ///<I2C master and slave mode configuration
    uint8_t u8SlaveAddr; ///<Slave address configuration (if required)
    boolean_t bGc; ///<Broadcast address enabled (if needed)
}stc_i2c_cfg_t;

/******************************************************************************
* Global variable declarations ('extern', definition in C source)
*****************************************************************************/

/**************************************************************************************
* Global function prototypes (definition in C source)
*********************************************************************************/
//I2C initialization function
en_result_t I2C_Init(M0P_I2C_TypeDef* I2Cx,stc_i2c_cfg_t *pstcI2CCfg);
//Set baud rate configuration register
en_result_t I2C_SetBaud(M0P_I2C_TypeDef* I2Cx,uint8_t u8Tm);
//I2C function set function
en_result_t I2C_SetFunc(M0P_I2C_TypeDef* I2Cx, en_i2c_func_t enFunc);
//I2C function clear function
en_result_t I2C_ClearFunc(M0P_I2C_TypeDef* I2Cx, en_i2c_func_t enFunc);
//Get interrupt flag SI
boolean_t I2C_GetIrq(M0P_I2C_TypeDef* I2Cx);
//Clear interrupt flag SI
en_result_t I2C_ClearIrq(M0P_I2C_TypeDef* I2Cx);
//Get status
uint8_t I2C_GetState(M0P_I2C_TypeDef* I2Cx);

//Byte write function
en_result_t I2C_WriteByte(M0P_I2C_TypeDef* I2Cx,uint8_t u8Data);

//byte reading function
uint8_t I2C_ReadByte(M0P_I2C_TypeDef* I2Cx);

//@} // I2cGroup

#ifdef __cplusplus
#endif

#endif /* __I2C_H__ */
/****************************************************************************** 
* EOF (not truncated) 
*******************************************************************************/