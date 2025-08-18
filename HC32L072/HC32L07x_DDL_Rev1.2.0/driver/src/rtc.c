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
 * @file   rtc.c
 *
 * @brief  Source file for RTC functions
 *
 * @author MADS Team 
 *
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "rtc.h"
/**
 ******************************************************************************
 ** \addtogroup RtcGroup
 ******************************************************************************/
//@{

/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/

/******************************************************************************/
/* Local function prototypes ('const')                                       */
/******************************************************************************/
const uint8_t Leap_Month_Base[]     =    {3,6,0,3,5,1,3,6,2,4,0,2};
const uint8_t NonLeap_Month_Base[]  =    {4,0,0,3,5,1,3,6,2,4,0,2};
const uint8_t Cnst_Month_Tbl[12]={0x31,0x28,0x31,0x30,0x31,0x30,0x31,0x31,0x30,0x31,0x30,0x31};
/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/******************************************************************************/
/* Local variable prototypes ('static')                                       */
/******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/
 
/**
**************************************************************************
** \brief Enable or stop the RTC counter
**
** @param NewState : TRUE or FALSE
** \retval None
**
******************************************************************************/
void Rtc_Cmd(boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_RTC->CR0)), 7, NewState);
}

/**
******************************************************************************
** \brief RTC counter start wait function. If you enter low-power mode immediately after starting the RTC counter,
** This function must be executed before entering low-power mode to ensure that the RTC has started.
**
** @param NewState : TRUE or FALSE
** \retval None
**
**************************************************************************/
void Rtc_StartWait(void)
{
    M0P_RTC->CR1_f.WAIT = 1;
    while (M0P_RTC->CR1_f.WAITF != 1)  //等待直到WAITF=1
    {
        ;
    }
    M0P_RTC->CR1_f.WAIT = 0;
    while (M0P_RTC->CR1_f.WAITF != 0)  //等待直到WAITF=0 
    {
        ;
    }
}
 
/**
******************************************************************************
** \brief Enable or disable the RTC's 1Hz output
** @param price: RtcHz1selGeneralPricision or RtcHz1selHighPricision
** @param NewState: Hz1o_Disable or HZ1o_Enable
** \retval None
**
**********************************************************************************/
void Rtc_Hz1Cmd(en_rtc_hz1sel_t pricision, boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_RTC->CR0)), 6, pricision);  //设置普通精度或者高精度1Hz输出
    SetBit((uint32_t)(&(M0P_RTC->CR0)), 5, NewState);   //设置1Hz输出使能或禁止
}    

/**
******************************************************************************
** \brief Sets the periodic interrupt type (PRDSEL) and the selected interrupt time (PRDS or PRDX)
**
** @param pstCyc: Sets PRDSEL, PRDS, and PRDX according to the structure definition
** \retval Ok, Error, or ErrorInvalidParameter
**
******************************************************************************/
en_result_t Rtc_SetCyc(stc_rtc_cyccfg_t* pstCyc)
{
    en_result_t enRet = Error;
    M0P_RTC->CR0_f.PRDSEL = pstCyc->rtcPrdsel;
    if(pstCyc->rtcPrdsel == RtcPrds)
    {
        M0P_RTC->CR0_f.PRDS = pstCyc->rtcPrds; 
    }
    else if(pstCyc->rtcPrdsel == RtcPrdx)
    {
        if(pstCyc->rtcPrdx>=64)
        {
            enRet = ErrorInvalidParameter;
            return enRet;
        }
        M0P_RTC->CR0_f.PRDX = pstCyc->rtcPrdx;
    }
    else
    {
        ;
    }
    enRet = Ok;
    return enRet;
}    

/**
********************************************************************************
** \brief Enable or disable the RTC alarm interrupt
**
** @param NewState : TRUE or FALSE
** \retval None
**
**********************************************************************/
void Rtc_AlmIeCmd(boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_RTC->CR1)), 3, 0);        // Clear the periodic interrupt flag
    SetBit((uint32_t)(&(M0P_RTC->CR1)), 4, 0);        // Clear the periodic interrupt flag
    SetBit((uint32_t)(&(M0P_RTC->CR1)), 6, NewState);
}
 
/**
******************************************************************************
** \brief Enable or disable the RTC alarm.
**
** @param NewState: Almen_Disable or Almen_Enable
** \retval None
**
**************************************************************************/
void Rtc_AlmEnCmd(boolean_t NewState)
{
    SetBit((uint32_t)(&(M0P_RTC->CR1)), 7, NewState);
}

/**
******************************************************************************
** \brief Get the RTC alarm interrupt status bit.
**
** @param None
** \retval TRUE or FALSE
**
**********************************************************************************/
boolean_t Rtc_GetAlmfItStatus(void)
{
    return GetBit((uint32_t)(&(M0P_RTC->CR1)), 4);
}

/**
**************************************************************************
** \brief Clears the RTC alarm interrupt status bit
**
** @param None
** \retval None
**
**************************************************************************/
void Rtc_ClearAlmfItStatus(void)
{
    SetBit((uint32_t)(&(M0P_RTC->CR1)), 4, 0);
}

/**
******************************************************************************
** \brief Clears the RTC periodic interrupt status bit
**
** @param None
** \retval None
**
******************************************************************************/
void Rtc_ClearPrdfItStatus(void)
{
    SetBit((uint32_t)(&(M0P_RTC->CR1)), 3, 0);
}

/**
******************************************************************************
** \brief Get the RTC periodic interrupt status bit
**
** @param None
** \retval TRUE or FALSE
**
**********************************************************************************/
boolean_t Rtc_GetPridItStatus(void)
{
    return GetBit((uint32_t)(&(M0P_RTC->CR1)), 3);
}

/**
**********************************************************************************
** \brief Configure the RTC error compensation register
**
** @param CompValue: The range of values is: 32-256 
** @param NewStatus: RtcCompenDisable or RtcAmCompenEnable 
** \retval Ok ErrorInvalidParameter 
**
******************************************************************************/
en_result_t Rtc_CompCfg(uint16_t CompVlue, en_rtc_compen_t NewStatus)
{
    en_result_t enRet = Error;
    if(CompVlue<=256)
    {
        M0P_RTC->COMPEN_f.EN = NewStatus;
        M0P_RTC->COMPEN_f.CR = CompVlue;
    }
    else
    {
        enRet = ErrorInvalidParameter;
    }
    return enRet;
}

/** 
****************************************************************************** 
** \brief RTC calculates the week number based on the date.
**
** \param pu8buf time data
** \param u8limit_min minimum value
** \param u8limit_max maximum value
**
** \retval Error (Error), Ok (Check successful)
**
****************************************************************************/
en_result_t Check_BCD_Format(uint8_t u8data,uint8_t u8limit_min, uint8_t u8limit_max)
{

    if (((u8data & 0x0F) > 0x09) || ((u8data & 0xF0) > 0x90)
    ||(u8data > u8limit_max) || (u8data < u8limit_min))
    {
        return Error;
    }
    return Ok;
}

/**
****************************************************************************************
** \brief RTC Leap and Ordinary Year Detection
**
** \param u8year: Year (decimal, low digits: 0-99)
**
** \retval 1: Leap year 0: Ordinary year
**
************************************************************************/
uint8_t Rtc_CheckLeapYear(uint8_t u8year)
{
        uint16_t tmp;
        tmp=2000+u8year;
        if((((tmp % 4)==0) && ((tmp % 100) !=0))|| ((tmp % 400) ==0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
************************************************************************************
** \brief RTC Get the number of days in February based on the year
**
** \param [in] u8month month, u8year year
**
** \retval u8day day: 28 or 29
**
**************************************************************************/
uint8_t Get_Month2_Day( uint8_t u8year)
{
    uint8_t u8day = 0;
    
    u8day = 28;
    if(Rtc_CheckLeapYear(u8year) == 1)
    {
        u8day++;
    }
    return u8day;
}

/**
******************************************************************************
** \brief RTC time acquisition function
**
** \param time: Used to store the time data read from the time register, in BCD format
**
** \retval Ok Acquisition completed successfully
** \retval ErrorTimeout Time overflow error 
******************************************************************************/
en_result_t Rtc_ReadDateTime(stc_rtc_time_t* time)
{
    uint32_t u32TimeOut;
    ASSERT(NULL != pstcTimeDate);  
    u32TimeOut = 1000;
    if(1 == M0P_RTC->CR0_f.START)
    {
        M0P_RTC->CR1_f.WAIT = 1;
        while(u32TimeOut--)
        {
            if(M0P_RTC->CR1_f.WAITF)
            {
            break;
            }
        }
        if(u32TimeOut==0)
        {
            return ErrorTimeout;
        }
    }
    time->u8Second  = M0P_RTC->SEC;
    time->u8Minute  = M0P_RTC->MIN;
    if(1 == M0P_RTC->CR0_f.AMPM)
    {
        time->u8Hour   = M0P_RTC->HOUR;
    }
    else
    {
        time->u8Hour   = M0P_RTC->HOUR&0x1f;
    }
    time->u8Day       = M0P_RTC->DAY;
    time->u8DayOfWeek = M0P_RTC->WEEK;
    time->u8Month     = M0P_RTC->MON;
    time->u8Year      = M0P_RTC->YEAR;

    M0P_RTC->CR1_f.WAIT = 0;
    if(1 == M0P_RTC->CR0_f.START)
    {
            while(M0P_RTC->CR1_f.WAITF)
            {}
    }
    
    return Ok;
}

/**
**************************************************************************
** \brief Write time to the RTC time register
**
** \param time: A structure storing time. Each time is in BCD format.
**
** \retval ErrorTimeout or Ok
**
**************************************************************************/
en_result_t Rtc_SetTime(stc_rtc_time_t* time)
{
    en_result_t enRet = Ok;
    uint16_t u16TimeOut;
    u16TimeOut = 1000;
    if(M0P_RTC->CR0_f.START == 1)
    {
        M0P_RTC->CR1_f.WAIT = 1;
        while(--u16TimeOut)
        {
            if(M0P_RTC->CR1_f.WAITF)
            {
                    break;
            }
        }
        if(u16TimeOut==0)
        {
            return ErrorTimeout;
        }
    }
    M0P_RTC->SEC   = time->u8Second;
    M0P_RTC->MIN   = time->u8Minute;
    M0P_RTC->HOUR  = time->u8Hour;
    M0P_RTC->DAY   = time->u8Day;
    M0P_RTC->MON   = time->u8Month;
    M0P_RTC->YEAR  = time->u8Year;
    M0P_RTC->WEEK  = time->u8DayOfWeek;

    M0P_RTC->CR1_f.WAIT = 0;
    if(M0P_RTC->CR0_f.START == 1)
    {
        while(M0P_RTC->CR1_f.WAITF)
        {}
    }
    enRet = Ok;
    return enRet;
}

/**
**************************************************************************
** \brief Get RTC alarm interrupt time
**
** \param pstcAlarmTime: Stores alarm time register data: seconds, minutes, hours, weeks
**
** \retval None
**
**************************************************************************/
void Rtc_GetAlarmTime(stc_rtc_alarmtime_t* pstcAlarmTime)
{
    pstcAlarmTime->RtcAlarmSec    = M0P_RTC->ALMSEC;
    pstcAlarmTime->RtcAlarmMinute = M0P_RTC->ALMMIN;
    pstcAlarmTime->RtcAlarmHour     = M0P_RTC->ALMHOUR;
    pstcAlarmTime->RtcAlarmWeek     = M0P_RTC->ALMWEEK;
}

/**
********************************************************************************
** \brief RTC alarm setting
**
** \param [in] pstcAlarmTime alarm time: seconds, minutes, hours, weeks
**
** \retval Ok Setting completed
**
********************************************************************************/
en_result_t Rtc_SetAlarmTime(stc_rtc_alarmtime_t* pstcAlarmTime)
{
    en_result_t enRet = Ok;
//    ASSERT(NULL != pstcAlarmTime);
    Rtc_AlmEnCmd(FALSE);      // Set the alarm time after disabling the alarm
    enRet = Check_BCD_Format(pstcAlarmTime->RtcAlarmSec,0x00,0x59);
    if(M0P_RTC->CR0_f.AMPM == RtcAm)
    {
        enRet = Check_BCD_Format(pstcAlarmTime->RtcAlarmHour,0x00,0x12);
    }
    else
    {
        enRet = Check_BCD_Format(pstcAlarmTime->RtcAlarmHour,0x00,0x24);
    }
    if(enRet != Ok)
    {
        return enRet;
    }
    enRet = Check_BCD_Format(pstcAlarmTime->RtcAlarmMinute,0x00,0x59);
    if(enRet != Ok)
    {
        return enRet;
    }

    if(enRet != Ok)
    {
            return enRet; 
    }
    M0P_RTC->ALMSEC  = pstcAlarmTime->RtcAlarmSec & 0x7f;
    M0P_RTC->ALMMIN  = pstcAlarmTime->RtcAlarmMinute & 0x7f;
    M0P_RTC->ALMHOUR = pstcAlarmTime->RtcAlarmHour & 0x3f;
    M0P_RTC->ALMWEEK = pstcAlarmTime->RtcAlarmWeek;
    Rtc_AlmEnCmd(TRUE);      //Alarm enable
    enRet = Ok;
    return enRet;
}

/**
******************************************************************************
** \brief Initializes the RTC
**
** @param Rtc_InitStruct stores the structure of type stc_rtc_initstruct_t
** \retval None
**
******************************************************************************/
void Rtc_Init(stc_rtc_initstruct_t* Rtc_InitStruct)
{
    Rtc_Cmd(FALSE);
    M0P_RTC->CR0_f.AMPM = Rtc_InitStruct->rtcAmpm;         //Real-time clock hour
    Rtc_SetCyc(&Rtc_InitStruct->rtcPrdsel);                //Set the periodic interrupt type (PRDSEL) and the selected interrupt time (PRDS or PRDX)
    M0P_RTC->CR1_f.CKSEL = Rtc_InitStruct->rtcClksrc;      //Real-time clock RTC clock source
    Rtc_CompCfg(Rtc_InitStruct->rtcCompValue, Rtc_InitStruct->rtcCompen); //Configure the clock error compensation register
    Rtc_SetTime(&Rtc_InitStruct->rtcTime);                 //Set the initial clock
}





