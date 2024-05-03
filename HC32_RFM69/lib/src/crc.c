/******************************************************************************
*Copyright(C)2017, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd("HDSC").
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

/** \file crc.c
 **
 ** Common API of crc.
 ** @link crcGroup Some description @endlink
 **
 **   - 2017-05-16
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "crc.h"
/**
 *******************************************************************************
 ** \addtogroup CrcGroup
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
 ** \brief CRC16 Encoding (byte fill mode)
 **
 ** This function is mainly used to generate CRC16 encoding.
 **
 ** \param [in]  pu8Data          Data pointer to be encoded (byte mode input)
 ** \param [in]  u32Len           Data length to be encoded (bytes)
 ** 
 ** \retval CRC16                 CRC16 value.                                
 *****************************************************************************/
uint16_t CRC16_Get8(uint8_t* pu8Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    
    M0P_CRC->CR_f.CR = 0;
    M0P_CRC->RESULT = 0xFFFF;
    for(u32Index = 0;u32Index<u32Len;u32Index++)
    {
            *((volatile uint8_t*)(&(M0P_CRC->DATA)))  = pu8Data[u32Index];
    }

    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 Coding (half word filling method)
 **
 ** This function is mainly used to generate CRC16 encoding.
 **
 ** \param [in]  pu16Data          Data pointer to be encoded (half word input)
 ** \param [in]  u32Len           Data length to be encoded (half word count)
 ** 
 ** \retval CRC16                 CRC16 value.                                
 *****************************************************************************/
uint16_t CRC16_Get16(uint16_t* pu16Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
	
    M0P_CRC->CR_f.CR = 0;
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }
  
    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 Coding (word filling method)
 **
 ** This function is mainly used to generate CRC16 encoding.
 **
 ** \param [in]  pu32Data          Data pointer to be encoded (word input)
 ** \param [in]  u32Len            Data length to be encoded (number of words)
 ** 
 ** \retval CRC16                  CRC16 value.                                
 *****************************************************************************/
uint16_t CRC16_Get32(uint32_t* pu32Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    
	M0P_CRC->CR_f.CR = 0;
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        M0P_CRC->DATA_f.DATA = pu32Data[u32Index];
    }
  
    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 Check (byte fill mode)
 **
 ** This function is mainly used to verify the data and CRC16 values.
 **
 ** \param [in]  pu8Data          Data pointer to be verified (byte mode input)
 ** \param [in]  u32Len           Data length to be verified (bytes)
 ** \param [in]  u16CRC            CRC16 value to be verified
 ** 
 ** \retval Ok                    CRC check is correct
 ** \retval Error                 CRC check error                                
 *****************************************************************************/
en_result_t CRC16_Check8(uint8_t* pu8Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;
    
    M0P_CRC->CR_f.CR = 0;	
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint8_t*)(&(M0P_CRC->DATA))) = pu8Data[u32Index];
    }
    
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)((((uint32_t)u16CRC)>>0)&0xFF);
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)(((uint32_t)u16CRC>>8)&0xFF);
    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult); 
}

/**
 *****************************************************************************
 ** \brief CRC16 Verification (half word filling method)
 **
 ** This function is mainly used to verify the data and CRC16 values.
 **
 ** \param [in]  pu16Data         Data pointer to be verified (half word input)
 ** \param [in]  u32Len           Data length to be verified (half word count)
 ** \param [in]  u16CRC            CRC16 value to be verified
 ** 
 ** \retval Ok                    CRC check is correct
 ** \retval Error                 CRC check error                                
 *****************************************************************************/
en_result_t CRC16_Check16(uint16_t* pu16Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;

    M0P_CRC->CR_f.CR = 0;	
    M0P_CRC->RESULT_f.RESULT = 0xFFFF;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }
    
     *((volatile uint16_t*)(&(M0P_CRC->DATA))) = u16CRC;
    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult); 
}

/**
 *****************************************************************************
 ** \brief CRC16 Check (word filling method)
 **
 ** This function is mainly used to verify the data and CRC16 values.
 **
 ** \param [in]  pu32Data         Data pointer to be verified (word input)
 ** \param [in]  u32Len           Data length to be verified (number of words)
 ** \param [in]  u16CRC            CRC16 value to be verified
 ** 
 ** \retval Ok                    CRC check is correct
 ** \retval Error                 CRC check error                                
 *****************************************************************************/
en_result_t CRC16_Check32(uint32_t* pu32Data, uint32_t u32Len, uint16_t u16CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;

    M0P_CRC->CR_f.CR = 0;	
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint32_t*)(&(M0P_CRC->DATA))) = pu32Data[u32Index];
    }
    
     *((volatile uint16_t*)(&(M0P_CRC->DATA))) = ((uint16_t)u16CRC);
    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult);
}

/**
 *****************************************************************************
 ** \brief CRC16 Encoding (byte fill mode)
 **
 ** This function is mainly used to generate CRC16 encoding.
 **
 ** \param [in]  pu8Data          Data pointer to be encoded (byte mode input)
 ** \param [in]  u32Len           Data length to be encoded (bytes)
 ** 
 ** \retval CRC16                 CRC16 value.                                
 *****************************************************************************/
uint32_t CRC32_Get8(uint8_t* pu8Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    
    M0P_CRC->CR_f.CR = 1;
    M0P_CRC->RESULT = 0xFFFFFFFFu;
    for(u32Index = 0;u32Index<u32Len;u32Index++)
    {
            *((volatile uint8_t*)(&(M0P_CRC->DATA)))  = pu8Data[u32Index];
    }

    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 Coding (half word filling method)
 **
 ** This function is mainly used to generate CRC16 encoding.
 **
 ** \param [in]  pu16Data          Data pointer to be encoded (half word input)
 ** \param [in]  u32Len           Data length to be encoded (half word count)
 ** 
 ** \retval CRC16                 CRC16 value.                                
 *****************************************************************************/
uint32_t CRC32_Get16(uint16_t* pu16Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
    
    M0P_CRC->CR_f.CR = 1;
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }
  
    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 Coding (word filling method)
 **
 ** This function is mainly used to generate CRC16 encoding.
 **
 ** \param [in]  pu32Data          Data pointer to be encoded (word input)
 ** \param [in]  u32Len            Data length to be encoded (number of words)
 ** 
 ** \retval CRC16                  CRC16 value.                                
 *****************************************************************************/
uint32_t CRC32_Get32(uint32_t* pu32Data, uint32_t u32Len)
{
    uint32_t u32Index = 0;
	
    M0P_CRC->CR_f.CR = 1;    
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        M0P_CRC->DATA_f.DATA = pu32Data[u32Index];
    }
  
    return (M0P_CRC->RESULT_f.RESULT);
}

/**
 *****************************************************************************
 ** \brief CRC16 Check (byte fill mode)
 **
 ** This function is mainly used to verify the data and CRC16 values.
 **
 ** \param [in]  pu8Data          Data pointer to be verified (byte mode input)
 ** \param [in]  u32Len           Data length to be verified (bytes)
 ** \param [in]  u16CRC            CRC16 value to be verified
 ** 
 ** \retval Ok                    CRC check is correct
 ** \retval Error                 CRC check error                                
 *****************************************************************************/
en_result_t CRC32_Check8(uint8_t* pu8Data, uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;
	
    M0P_CRC->CR_f.CR = 1;     
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint8_t*)(&(M0P_CRC->DATA))) = pu8Data[u32Index];
    }
    
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)((u32CRC>>0)&0xFF);
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)((u32CRC>>8)&0xFF);
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)((u32CRC>>16)&0xFF);
     *((volatile uint8_t*)(&(M0P_CRC->DATA))) = (uint8_t)((u32CRC>>24)&0xFF);
		
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult); 
}

/**
 *****************************************************************************
 ** \brief CRC16 Verification (half word filling method)
 **
 ** This function is mainly used to verify the data and CRC16 values.
 **
 ** \param [in]  pu16Data         Data pointer to be verified (half word input)
 ** \param [in]  u32Len           Data length to be verified (half word count)
 ** \param [in]  u16CRC            CRC16 value to be verified
 ** 
 ** \retval Ok                    CRC check is correct
 ** \retval Error                 CRC check error                                
 *****************************************************************************/
en_result_t CRC32_Check16(uint16_t* pu16Data, uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;
	
    M0P_CRC->CR_f.CR = 1;     
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint16_t*)(&(M0P_CRC->DATA))) = pu16Data[u32Index];
    }
    
     *((volatile uint16_t*)(&(M0P_CRC->DATA))) = (uint16_t)((u32CRC>>0)&0xFFFF);
     *((volatile uint16_t*)(&(M0P_CRC->DATA))) = (uint16_t)((u32CRC>>16)&0xFFFF);

    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult); 
}

/**
 *****************************************************************************
 ** \brief CRC16 Check (word filling method)
 **
 ** This function is mainly used to verify the data and CRC16 values.
 **
 ** \param [in]  pu32Data         Data pointer to be verified (word input)
 ** \param [in]  u32Len           Data length to be verified (number of words)
 ** \param [in]  u16CRC            CRC16 value to be verified
 ** 
 ** \retval Ok                    CRC check is correct
 ** \retval Error                 CRC check error                                
 *****************************************************************************/
en_result_t CRC32_Check32(uint32_t* pu32Data, uint32_t u32Len, uint32_t u32CRC)
{
    en_result_t enResult = Ok;
    uint32_t    u32Index = 0;
	
    M0P_CRC->CR_f.CR = 1;     
    M0P_CRC->RESULT_f.RESULT = 0xFFFFFFFFu;
    for (u32Index=0; u32Index<u32Len; u32Index++)
    {
        *((volatile uint32_t*)(&(M0P_CRC->DATA))) = pu32Data[u32Index];
    }
    
     *((volatile uint32_t*)(&(M0P_CRC->DATA))) = u32CRC;
    
    enResult = M0P_CRC->CR_f.FLAG ? Ok : Error;
    
    return (enResult);
}
//@} // CrcGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
