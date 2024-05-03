/******************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.
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
/*****************************************************************************/
/** \file rtc.h
 **
 ** Headerfile for RTC functions
 **  
 **
 ** History:
 **   - 2017-05-10   Cathy     First Version
 **
 *****************************************************************************/

#ifndef __RTC_H__
#define __RTC_H__

/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l136.h"

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
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
************************************************** ****************************
  ** \brief rtc clock source selection
  ************************************************** ***************************/
typedef enum en_rtc_clk
{
    RtcClk32768   = 0u, ///<external32.768k    
    RtcClk32768_1 = 1u, ///<external32.768k
    RtcClk32      = 2u, ///<internalRC32   
    RtcClk32_1    = 3u, ///<internalRC32
    RtcClkHxt128  = 4u, ///<external Crystal oscillator 4M
    RtcClkHxt256  = 5u, ///<external Crystal oscillator 8M
    RtcClkHxt512  = 6u, ///<external Crystal oscillator 16M
    RtcClkHxt1024 = 7u, ///<external Crystal oscillator 32M
}en_rtc_clk_t;
/**
************************************************** ****************************
  ** \brief rtc cycle interrupt mode selection
  ************************************************** ***************************/
typedef enum en_rtc_cyc
{
    RtcPrads = 0u, ///<Month, day, hour, minute, second
    RtcPradx = 1u, ///<step 0.5s
}en_rtc_cyc_t;
/**
************************************************** ****************************
  ** \brief rtc 12h or 24h mode selection
  ************************************************** ***************************/
typedef enum en_rtc_ampm
{
    Rtc12h = 0u, ///<12h
    Rtc24h = 1u, ///<24h
}en_rtc_ampm_t;
/**
************************************************** ****************************
  ** \brief prds interrupt cycle
  ************************************************** ***************************/
typedef enum en_rtc_cycprds
{
    Rtc_None   = 0u, ///<No cycle interruption
    Rtc_05S    = 1u, ///<0.5SInterrupt
    Rtc_1S     = 2u, ///<1s
    Rtc_1Min   = 3u, ///<1min
    Rtc_1H     = 4u, ///<1h
    Rtc_1Day   = 5u, ///<1d
    Rtc_1Mon   = 6u, ///<1month
    Rtc_1Mon_1 = 7u, ///<1month
}en_rtc_cycprds_t;
/**
************************************************** ****************************
  ** \brief rtc cycle Interrupt total configuration
  ************************************************** ***************************/
typedef struct stc_rtc_cyc_sel
{
    en_rtc_cyc_t      enCyc_sel; ///<Cycle type configuration
    en_rtc_cycprds_t  enPrds_sel;///<Cycle configuration
    uint8_t u8Prdx;
}stc_rtc_cyc_sel_t;
/**
************************************************** ****************************
  ** \brief alarm source configuration
  ************************************************** ***************************/
typedef struct stc_rtc_alarmset
{
    uint8_t  u8Minute; ///<Alarm minute
    uint8_t  u8Hour;   ///<Alarm hour
    uint8_t  u8Week;   ///<Alarm clock week
}stc_rtc_alarmset_t;
/**
************************************************** ****************************
  ** \brief Alarm Interrupt Enable Settings
  ************************************************** ***************************/
typedef enum en_rtc_alarmirq
{
    Rtc_AlarmInt_Disable = 0u,///<Alarm Interrupt disabled
    Rtc_AlarmInt_Enable  = 1u,///<Alarm Interrupt enabled
}en_rtc_alarmirq_t;

/**
************************************************** ****************************
  ** \brief rtc 1hz compensation function enable setting
  ************************************************** ***************************/
typedef enum en_rtc_compen_en
{
    Rtc_Comp_Disable = 0u,///<Clock compensation disabled
    Rtc_Comp_Enable  = 1u,///<Clock compensation enabled
}en_rtc_compen_en_t;
/**
************************************************** ****************************
  ** \brief rtc counting function enable setting
  ************************************************** ***************************/
typedef enum en_rtc_count_en
{
    Rtc_Count_Disable = 0u,///<Counting disabled
    Rtc_Count_Enable  = 1u,///<Counting enabled
}en_rtc_count_en_t;
/**
************************************************** ****************************
  ** \brief rtc count mode or read-write mode status
  ************************************************** ***************************/
typedef enum en_rtc_status
{
    RtcRunStatus = 0u, ///<Count status
    RtcRdWStatus = 1u, ///<Read and write status
}en_rtc_status_t;
/**
************************************************** ****************************
  ** \brief rtc Interrupt request flag
  ************************************************** ***************************/
typedef enum en_rtc_status_irq
{
    RtcAlmf  = 0u, ///<Alarm clock Interrupt request
    RtcPrdf  = 1u, ///<cycle Interrupt request
}en_rtc_status_irq_t;
/**
************************************************** ****************************
  ** \brief rtc clock year, month, day, hour, minute, second read and write structure
  ************************************************** ***************************/
typedef struct stc_rtc_time
{
    uint8_t  u8Second;      ///<second    
    uint8_t  u8Minute;      ///<Minute
    uint8_t  u8Hour;        ///<Time
    uint8_t  u8DayOfWeek;   ///<week
    uint8_t  u8Day;         ///<day    
    uint8_t  u8Month;       ///<month
    uint8_t  u8Year;        ///<year
} stc_rtc_time_t;
/**
************************************************** ****************************
  ** \brief rtc function description
  ************************************************** ****************************/
typedef enum en_rtc_func
{
    RtcCount     = 0u,    ///< RTC count enable
    RtcAlarmEn   = 1u,    ///< RTC alarm clock enabled
    Rtc_ComenEn  = 2u,    ///<RTC compensation enable
    Rtc1HzOutEn  = 3u,    ///<Enable 1hz output
}en_rtc_func_t;
/**
************************************************** ****************************
  ** \brief rtc alarm clock and cycle Interrupt handler
  ************************************************** ***************************/
typedef struct stc_rtc_irq_cb
{
    func_ptr_t               pfnAlarmIrqCb; ///<Alarm Interrupt Service Function     
    func_ptr_t               pfnTimerIrqCb; ///<Periodic Interrupt service function
}stc_rtc_irq_cb_t, stc_rtc_intern_cb_t;
/**
************************************************** ****************************
  ** \brief rtc overall configuration structure
  ************************************************** ***************************/
typedef struct stc_rtc_config
{
    en_rtc_clk_t          enClkSel;    ///<Clock source configuration
    en_rtc_ampm_t        enAmpmSel;    ///<Time configuration
    stc_rtc_cyc_sel_t*   pstcCycSel;   ///<Cycle configuration
    stc_rtc_time_t*      pstcTimeDate; ///<Time and date initial value configuration
    stc_rtc_irq_cb_t*     pstcIrqCb;   ///<Interrupt service function
    boolean_t            bTouchNvic;   ///<NVIC Interrupt configuration                   
} stc_rtc_config_t;

//rtc Count clock source selection
en_result_t Rtc_SelClk(en_rtc_clk_t enClk);
//rtc Count cycle setting
en_result_t Rtc_SetCyc(stc_rtc_cyc_sel_t* pstcCyc);
//rtc Ampm mode setting
en_result_t Rtc_SetAmPm(en_rtc_ampm_t enMode);
//Rtc time mode acquisition
boolean_t Rtc_GetHourMode(void);
//rtc Alarm clock related configuration
en_result_t Rtc_SetAlarmTime(stc_rtc_alarmset_t* pstcAlarmTime);
en_result_t Rtc_GetAlarmTime(stc_rtc_alarmset_t* pstcAlarmTime);
//1hz Output mode and compensation value setting
en_result_t Rtc_Set1HzMode(boolean_t bMode);
en_result_t Rtc_SetCompCr(uint16_t u16Cr);
//Week calculation
uint8_t Rtc_CalWeek(uint8_t* pu8Date);
//Determine whether it is a leap year
uint8_t Rtc_CheckLeapYear(uint8_t u8year);
//12-hour morning or afternoon reading
boolean_t Rtc_RDAmPm(void);
//rtc Read and write time counter
en_result_t Rtc_WriteDateTime(stc_rtc_time_t* pstcTimeDate,boolean_t bUpdateTime,
                            boolean_t bUpdateDate);
en_result_t Rtc_ReadDateTime(stc_rtc_time_t* pstcTimeDate);
//Format conversion function
uint8_t Change_DateTimeFormat(uint8_t u8sr);
//Time format check function
en_result_t Rtc_CheckDateTimeFormat(uint8_t* pu8TimeDate,uint8_t u8Mode);
//Data size checking function
en_result_t Check_BCD_Format(uint8_t u8data, uint8_t u8limit_min, uint8_t u8limit_max);
//Get the maximum number of days in a month
uint8_t Get_Month_Max_Day(uint8_t u8month, uint8_t u8year);
//rtc Read current status (read-write status or count status), Interruptrequest status, Interrupt clear status
en_result_t Rtc_EnAlarmIrq(en_rtc_alarmirq_t enIrqEn);
boolean_t Rtc_RDStatus(void);
boolean_t Rtc_GetIrqStatus(en_rtc_status_irq_t enIrqSel);
en_result_t Rtc_ClrIrqStatus(en_rtc_status_irq_t enIrqSel);

//Rtc function enable disable function
en_result_t Rtc_EnableFunc(en_rtc_func_t enFunc);
en_result_t Rtc_DisableFunc(en_rtc_func_t enFunc);
//Rtc initialization, disable function
en_result_t Rtc_Init(stc_rtc_config_t* pstcRtcConfig);
en_result_t Rtc_DeInit(void);

//@} // RtcGroup

#ifdef __cplusplus
#endif

#endif /* __RTC_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/    


