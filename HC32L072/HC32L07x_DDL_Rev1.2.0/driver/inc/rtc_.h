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
* @filertc.h 
* 
* @brief Header file for RTC functions 
* 
* @author MADS Team 
* 
******************************************************************************/

#ifndef __RTC_H__
#define __RTC_H__

/**************************************************************************** 
* Include files 
*******************************************************************************/
#include "ddl.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** 
****************************************************************************** 
** \defgroup RtcGroup Real Time Clock (RTC) 
** 
******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/**********************************************************************************/

/******************************************************************************
* Global type definitions
**************************************************************************/

/**
******************************************************************************
** \brief RTC periodic interrupt interval RTC_CR0 PRDS
*****************************************************************************/
typedef enum
{
    RtcNone = 0u, //No periodic interrupt
    Rtc05S = 1u, //0.5S interrupt
    Rtc1S = 2u, //1 second
    Rtc1Min = 3u, //1 minute
    Rtc1H = 4u, //1 hour
    Rtc1Day = 5u, //1 day
    Rtc1Mon = 6u //January
}en_rtc_prds_t;

/**
************************************************************************
** \brief RTC 12h or 24h format selection RTC_CR0 AMPM
************************************************************************/
typedef enum
{
    RtcAm = 0u, //12-hour format
    RtcPm = 1u //24-hour format
}en_rtc_ampm_t;

/**
********************************************************************************
** \brief Normal and high-precision 1Hz output RTC_CR0 HZ1SEL
***************************************************************************/
typedef enum
{
    RtcHz1selGeneralPricision = 0u, //Normal precision 1Hz output
    RtcHz1selHighPricision = 1u //High-precision 1Hz output
}en_rtc_hz1sel_t;

/**
****************************************************************************
** \brief Periodic interrupt selection RTC_CR0 PRDSEL
***************************************************************************/
typedef enum
{
    RtcPrds = 0u, //Periodic interrupt event interval set by PRDS
    RtcPrdx = 1u //Periodic interrupt event interval set by PRDX
}en_rtc_prdsel_t;

/**
************************************************************************************
** \brief RTC clock selection RTC_CR1 CKSEL
***************************************************************************/
typedef enum
{
    RtcClkXtl = 0u, // External low-speed clock XTL 32.768k
    RtcClkRcl = 2u, // Internal low-speed clock RCL 32k
    RtcClkXth128 = 4u, // External crystal oscillator 4M XTH/128
    RtcClkXth256 = 5u, // External crystal oscillator 8M XTH/256
    RtcClkXth512 = 6u, // External crystal oscillator 16M XTH/512
    RtcClkXth1024 = 7u // External crystal oscillator 32M XTH/1024
}en_rtc_cksel_t;

/**
********************************************************************************
** \brief Clock error compensation enabled or disabled (RTC_COMPEN EN)
*****************************************************************************/
typedef enum
{
    RtcCompenDisable = 0u,
    RtcCompenEnable = 1u
}en_rtc_compen_t;

/**
********************************************************************************
** \brief Configure PRD interrupt enable and cycle type
*****************************************************************************/
typedef struct
{
    en_rtc_prdsel_t rtcPrdsel;
    uint8_t rtcPrdx;
    en_rtc_prds_t rtcPrds;
}stc_rtc_cyccfg_t;

/**
********************************************************************************
** \brief Alarm source configuration
*****************************************************************************/
typedef struct
{
    uint8_t RtcAlarmSec; //Alarm seconds
    uint8_t RtcAlarmMinute; //Alarm minutes
    uint8_t RtcAlarmHour; //Alarm hours
    uint8_t RtcAlarmWeek; //Alarm week
}stc_rtc_alarmtime_t;

/**
********************************************************************************
** \brief Time
***************************************************************************/
/**
********************************************************************************************
** \brief RTC clock year, month, day, hour, minute, and second read/write structure
***************************************************************************/
typedef struct stc_rtc_time
{
    uint8_t u8Second; //Time: Seconds
    uint8_t u8Minute; //Time: Minutes
    uint8_t u8Hour; //Time: Hours
    uint8_t u8DayOfWeek; //Time: Week
    uint8_t u8Day; //Time: Day
    uint8_t u8Month; //Time: Month
    uint8_t u8Year; //Time: Year
} stc_rtc_time_t;

/**
********************************************************************************
** \brief Initializes the RTC structure
***********************************************************************/
typedef struct
{
    en_rtc_ampm_t rtcAmpm; //Hourly time
    stc_rtc_cyccfg_t rtcPrdsel; //Determine the periodic interrupt interval type set by PRDS or PRDX
    en_rtc_cksel_t rtcClksrc; //Real-time clock clock source
    en_rtc_compen_t rtcCompen; //Enable or disable clock error compensation
    uint16_t rtcCompValue; //When compensation is enabled, the compensation value range is: 0-255
    stc_rtc_time_t rtcTime; //Time to write to the time register
}stc_rtc_initstruct_t;

/******************************************************************************
Global function prototypes (definition in C source)
***************************************************************************/
//Enable or stop the RTC counter
extern void Rtc_Cmd(boolean_t NewState);
//RTC counter start wait function
extern void Rtc_StartWait(void);
//Enable or stop the RTC 1Hz output
extern void Rtc_Hz1Cmd(en_rtc_hz1sel_t price, boolean_t NewState);
//Set the periodic interrupt type (PRDSEL) and the selected type time (PRDS or PRDX)
extern en_result_t Rtc_SetCyc(stc_rtc_cyccfg_t* pstCyc);
//Enable or stop the RTC alarm interrupt
extern void Rtc_AlmIeCmd(boolean_t NewState);
//Enable or stop the RTC alarm
extern void Rtc_AlmEnCmd(boolean_t NewState);
//Get the RTC alarm interrupt status bit
extern boolean_t Rtc_GetAlmfItStatus(void);
//Clear the RTC alarm interrupt status bit
extern void Rtc_ClearAlmfItStatus(void);
//Clear the RTC periodic interrupt status bit
extern void Rtc_ClearPrdfItStatus(void);
//Get the RTC periodic interrupt status bit
extern boolean_t Rtc_GetPridItStatus(void);
//Configure the RTC error compensation register
extern en_result_t Rtc_CompCfg(uint16_t CompVlue, en_rtc_compen_t NewStatus);
//RTC calculates the week number based on the date
extern en_result_t Check_BCD_Format(uint8_t u8data,uint8_t u8limit_min, uint8_t u8limit_max);
//RTC time acquisition function
extern en_result_t Rtc_ReadDateTime(stc_rtc_time_t* time);
//Write time to the RTC time register
extern en_result_t Rtc_SetTime(stc_rtc_time_t* time);
//Get the RTC alarm interrupt time
extern void Rtc_GetAlarmTime(stc_rtc_alarmtime_t* pstcAlarmTime);
//Set the RTC alarm
extern en_result_t Rtc_SetAlarmTime(stc_rtc_alarmtime_t* pstcAlarmTime);
//Initialize the RTC
extern void Rtc_Init(stc_rtc_initstruct_t* Rtc_InitStruct);
#endif /* __RTC_H__ */
/******************************************************************************
* EOF (not truncated)
*****************************************************************************/

