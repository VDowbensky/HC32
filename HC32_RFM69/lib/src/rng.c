/******************************************************************************
*Copyright(C)2018, Huada Semiconductor Co.,Ltd All rights reserved.
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

/** \file rng.c
 **
 ** Common API of rng.
 ** @link flashGroup Some description @endlink
 **
 **   - 2018-05-08
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "rng.h"
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
  ************************************************** ***************************
  ** \brief random number initialization (first random number generated on power-on)
  **
  **
  ** \retval TRUE or FALSE
  ************************************************** ***************************/
en_result_t Rng_Init(void)
{
    //==>>Generate 64bits random number (first power-on)
    M0P_RNG->CR_f.RNGCIR_EN = 1;
    //Mode configuration 0
    M0P_RNG->MODE_f.LOAD    = 1;
    M0P_RNG->MODE_f.FDBK    = 1;
    M0P_RNG->MODE_f.CNT     = 6;
    //Generate random number 0
    M0P_RNG->CR_f.RNG_RUN  = 1;
    while(M0P_RNG->CR_f.RNG_RUN)
    {
        ;
    }
    
    //Mode configuration 1
    M0P_RNG->MODE_f.LOAD    = 0;
    M0P_RNG->MODE_f.FDBK    = 0;
    M0P_RNG->MODE_f.CNT     = 4;
    //Generate random number 1
    M0P_RNG->CR_f.RNG_RUN  = 1;
    while(M0P_RNG->CR_f.RNG_RUN)
    {
        ;
    }

    //Turn off random source circuit to save power
    M0P_RNG->CR_f.RNGCIR_EN = 0;
    
    return Ok;
}

/**
  ************************************************** ***************************
  ** \brief generates a random number (non-powered the first time to generate a random number)
  **
  **
  ** \retval TRUE or FALSE
  ************************************************** ***************************/
en_result_t Rng_Generate(void)
{
    //==>>Generate 64bits random number (not generated for the first time after power-on)
    M0P_RNG->CR_f.RNGCIR_EN = 1;
    
    //Mode configuration 0
    M0P_RNG->MODE_f.LOAD    = 0;
    M0P_RNG->MODE_f.FDBK    = 1;
    M0P_RNG->MODE_f.CNT     = 6;
    //Generate random number 0
    M0P_RNG->CR_f.RNG_RUN  = 1;
    while(M0P_RNG->CR_f.RNG_RUN)
    {
        ;
    }
    
    //Mode configuration 1
    M0P_RNG->MODE_f.FDBK    = 0;
    M0P_RNG->MODE_f.CNT     = 4;
    M0P_RNG->MODE_f.CNT     = 4;
    //Generate random number 1
    M0P_RNG->CR_f.RNG_RUN  = 1;
    while(M0P_RNG->CR_f.RNG_RUN)
    {
        ;
    }

    //Turn off random source circuit to save power
    M0P_RNG->CR_f.RNGCIR_EN = 0;    
    
    return Ok;
}

/**
  ************************************************** ***************************
  ** \brief random number acquisition
  **
  ** \retval data0
  ************************************************** ***************************/
uint32_t Rng_GetData0(void)
{
    return M0P_RNG->DATA0;
}

/**
  ************************************************** ***************************
  ** \brief random number acquisition
  **
  ** \retval data1
  ************************************************** ***************************/
uint32_t Rng_GetData1(void)
{
    return M0P_RNG->DATA1;
}

//@} // RngGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
