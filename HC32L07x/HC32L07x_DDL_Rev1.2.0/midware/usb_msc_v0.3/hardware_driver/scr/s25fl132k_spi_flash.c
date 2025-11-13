/******************************************************************************
* Copyright (C) 2019, Huada Semiconductor Co.,Ltd All rights reserved.
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
/** \file s25fl132k_spi_flash.c
 **
 ** A detailed description is available at
 ** @link Sample Group Some description @endlink
 **
 **   - 2019-07-15   lsq   First version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
   
#include "s25fl132k_spi_flash.h"   
#include <stdio.h>   

/**
 ******************************************************************************
 ** \brief  S25FL132K_SPI_FLASH_CS_LOW设置CS为低电平
 **
 ** \param  无
 ** \return 无
 ******************************************************************************/
void S25FL132K_SPI_FLASH_CS_LOW(void)
{
	M0P_SPI0->SSN_f.SSN=0;
}
  
/**
 ******************************************************************************
 ** \brief  使能SPI1_CS高电平
 **
 ** \param  无
 ** \return 无
 ******************************************************************************/
void S25FL132K_SPI_FLASH_CS_HIGH(void)
{
	M0P_SPI0->SSN_f.SSN=1;
}

/**
 ******************************************************************************
 ** \brief  初始化SPI1的引脚与配置
 **
 ** \param  无
 ** \return 无
 ******************************************************************************/
void S25FL132K_SPI_FLASH_Init(void)   
{   
    M0P_SYSCTRL->PERI_CLKEN0_f.SPI0=1;

    M0P_GPIO->PE12_SEL_f.SEL=2;     //端口选择作为SPI0_CS引脚
    M0P_GPIO->PEADS_f.PE12=0;       //PE12配置成数字端口
    M0P_GPIO->PEDIR_f.PE12=0;       //PE12配置成输出

    M0P_GPIO->PE13_SEL_f.SEL=2;     //端口选择作为SPI0_SCK引脚
    M0P_GPIO->PEADS_f.PE13=0;       //PE13配置成数字端口
    M0P_GPIO->PEDIR_f.PE13=0;       //PE13配置成输出

    M0P_GPIO->PE14_SEL_f.SEL=2;     //端口选择作为SPI0_MISO引脚
    M0P_GPIO->PEADS_f.PE14=0;       //PE14配置成数字端口
    M0P_GPIO->PEDIR_f.PE14=1;       //PE14配置成输入

    M0P_GPIO->PE15_SEL_f.SEL=2;     //端口选择作为SPI0_MOSI引脚
    M0P_GPIO->PEADS_f.PE15=0;       //PE15配置成数字端口
    M0P_GPIO->PEDIR_f.PE15=0;       //PE15配置成输出

    M0P_SPI0->CR_f.MSTR = 1;        //配置从主机模式
    M0P_SPI0->CR_f.CPHA = 1;        //时钟选择第二边沿
    M0P_SPI0->CR_f.CPOL = 1;        //时钟极性选择：高
    M0P_SPI0->CR_f.SPEN = 1;        //模块使能寄存器：使能
    //波特率位24MHz
    M0P_SPI0->CR_f.SPR2 = 1;        //波特率选择：001——fsys/2
    M0P_SPI0->CR_f.SPR1 = 0;
    M0P_SPI0->CR_f.SPR0 = 0;
    M0P_SPI0->SSN = 1;              //CS0=1

    M0P_SPI0->CR2_f.RXNEIE = 0;     //接收缓冲器非空中断禁止
    M0P_SPI0->CR2_f.TXEIE  = 0;     //发送缓冲器空中断禁止
    M0P_SPI0->CR2_f.INT_EN = 1;	    //中断使能	
}   
   
/**
 ******************************************************************************
 ** \brief  擦除扇区
 **
 ** \param  SectorAddr: 所要擦除的扇区的起始地址
 ** \return 无
 ******************************************************************************/   
void S25FL132K_SPI_FLASH_SectorErase(uint32_t SectorAddr)   
{   
    SectorAddr = SectorAddr<<12;
    S25FL132K_SPI_FLASH_WriteEnable();                           //写使能 
    S25FL132K_SPI_FLASH_WaitForWriteEnd();                       //等待擦除完成
    S25FL132K_SPI_FLASH_CS_LOW();                                //CS输出低电平  
    S25FL132K_SPI_FLASH_SendByte(S25FL132K_SectorErase);         //发送擦除扇区指令  
    S25FL132K_SPI_FLASH_SendByte((SectorAddr & 0xFF0000) >> 16); //发送要擦除的扇区地址的16bit-23bit   
    S25FL132K_SPI_FLASH_SendByte((SectorAddr & 0xFF00) >> 8);    //发送要擦除的扇区地址的8bit-15bit  
    S25FL132K_SPI_FLASH_SendByte(SectorAddr & 0xFF);             //发送要擦除的扇区地址的0bit-7bit    
    S25FL132K_SPI_FLASH_CS_HIGH();                               //CS输出高电平  
    S25FL132K_SPI_FLASH_WaitForWriteEnd();                       //等待擦除完成
}   
   
/**
 ******************************************************************************
 ** \brief  擦除整片
 **
 ** \param  无
 ** \return 无
 ******************************************************************************/  
void S25FL132K_SPI_FLASH_BulkErase(void)   
{   
    S25FL132K_SPI_FLASH_WriteEnable();                           //发送写使能  
    S25FL132K_SPI_FLASH_CS_LOW();                                //CS输出低电平  
    S25FL132K_SPI_FLASH_SendByte(S25FL132K_ChipErase);           //发送擦除整片的指令  
    S25FL132K_SPI_FLASH_CS_HIGH();                               //CS输出高电平 
    S25FL132K_SPI_FLASH_WaitForWriteEnd();                       //等待擦除完成   
}   
     
/**
 ******************************************************************************
 ** \brief  页编程，写入范围为一页大小以内
 **
 ** \param  pBuffer:指向要写入页中数据指针
 ** \param  WriteAddr:要写数据的FLASH目标地址
 ** \param  NumByteToWrite:要写入页的数据字节数
 ** \return 无
 ******************************************************************************/ 
void S25FL132K_SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)   
{     
    S25FL132K_SPI_FLASH_WriteEnable();                           //发送写使能      
    S25FL132K_SPI_FLASH_CS_LOW();                                //CS输出低电平     
    S25FL132K_SPI_FLASH_SendByte(S25FL132K_PageProgram);         //发送页编程指令    
    S25FL132K_SPI_FLASH_SendByte((WriteAddr & 0xFF0000) >> 16);  //发送要擦除的扇区地址的16bit-23bit  
    S25FL132K_SPI_FLASH_SendByte((WriteAddr & 0xFF00) >> 8);     //发送要擦除的扇区地址的8bit-15bit  
    S25FL132K_SPI_FLASH_SendByte(WriteAddr & 0xFF);              //发送要擦除的扇区地址的0bit-7bit
     
    while (NumByteToWrite--)                                     //一个字节一个字节往指定地址写入数据
    {     
        S25FL132K_SPI_FLASH_SendByte(*pBuffer);           
        pBuffer++;   
    }   
  
    S25FL132K_SPI_FLASH_CS_HIGH();                               //CS输出高电平   
    S25FL132K_SPI_FLASH_WaitForWriteEnd();                       //等待FLASH自己操作完成 
}   

/**
 *******************************************************************************
 ** \brief 无检验写SPI FLASH 
 **
 ** \param  pBuffer:指向要写进flash的缓存
 ** \param  WriteAddr:要写入flash的地址
 ** \param  NumByteToWrite:要写无flash的数据数量
 **
 ** \retval 无
 **
 ******************************************************************************/
void S25FL132K_SPI_FLASH_Write_NoCheck(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t pageremain;
    pageremain = 256 - WriteAddr % 256;            //单页剩余的字节数
    if (NumByteToWrite <= pageremain)              //不大于256个字节
    {
        pageremain = NumByteToWrite;
    }
    while (1)
    {
        S25FL132K_SPI_FLASH_PageWrite(pBuffer, WriteAddr, pageremain);
        if (NumByteToWrite == pageremain)
        {
            break;                                //写入结束了
        }
        else 
        {
            pBuffer        += pageremain;
            WriteAddr      += pageremain;

            NumByteToWrite -= pageremain;         //减去已经写入了的字节数
            if (NumByteToWrite > 256)             //一次可以写入256个字节
            {
                pageremain = 256;                 //不够256个字节了
            }
            else
            {
                pageremain = NumByteToWrite;
            }
        }
    }
}

/**
 ******************************************************************************
 ** \brief  从FLASH指定地址开始读取指定数量的数据
 **
 ** \param  pBuffer:指向存放读取自FLASH的数据
 ** \param  ReadAddr:要读的数据在FLASH中的起始地址
 ** \param  NumByteToWrite:要从FLASH读取的数据数据字节数
 ** \return 无
 ******************************************************************************/
void S25FL132K_SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)   
{     
    S25FL132K_SPI_FLASH_CS_LOW();                                //CS输出低电平
    S25FL132K_SPI_FLASH_SendByte(S25FL132K_ReadData);            //发送读取数据的指令    
    S25FL132K_SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);   //发送要读取数据地址的16bit-23bit    
    S25FL132K_SPI_FLASH_SendByte((ReadAddr & 0xFF00) >> 8);      //发送要读取数据地址的8bit-15bit   
    S25FL132K_SPI_FLASH_SendByte((ReadAddr & 0xFF));             //发送要读取数据地址的0bit-7bit  
    while (NumByteToRead--)                                      //读数据的循环过程  
    {     
        *pBuffer = S25FL132K_SPI_FLASH_SendByte(Dummy_Byte);    
        pBuffer++;   
    }   
    S25FL132K_SPI_FLASH_CS_HIGH();                               //CS输出高电平
}   

/**
 ******************************************************************************
 ** \brief  写整块数据到FLASH中,过程中写的周期有所减少，使用整页写的顺序
 **
 ** \param  pBuffer:指向要写入页中数据指针
 ** \param  WriteAddr:要写数据的FLASH目标地址
 ** \param  NumByteToWrite:要写入页的数据字节数
 ** \return 无
 ******************************************************************************/
uint8_t W25QXX_BUFFER[4096];
void S25FL132K_SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)   
{   
    uint32_t secpos;
    uint16_t secoff;
    uint16_t secremain;
    uint16_t i;
    uint8_t * W25QXX_BUF;
    W25QXX_BUF = W25QXX_BUFFER;
    secpos     = WriteAddr / 4096;                 //扇区地址 
    secoff     = WriteAddr % 4096;                 //在扇区内的偏移
    secremain  = 4096 - secoff;                    //扇区剩余空间大小
    if (NumByteToWrite <= secremain)               //小于4096个字节
    {
        secremain = NumByteToWrite;                                
    }
    while (1)
    {
        S25FL132K_SPI_FLASH_BufferRead(W25QXX_BUF, secpos * 4096, 4096);   //读出整个扇区的内容
        for (i = 0; i < secremain; i++)                                    //校验数据
        {
            if (W25QXX_BUF[secoff + i] != 0XFF)                            //需要擦除
            {
                break;
            }
        }
        if (i < secremain)                                                //需要擦除
        {
            S25FL132K_SPI_FLASH_SectorErase(secpos);                      //擦除这个扇区
            for (i = 0; i < secremain; i++)                               //复制数据
            {
                W25QXX_BUF[i + secoff] = pBuffer[i];
            }
            S25FL132K_SPI_FLASH_Write_NoCheck(W25QXX_BUF, secpos * 4096, 4096); //写入整个扇区 

        }
        else
        {
            S25FL132K_SPI_FLASH_Write_NoCheck(pBuffer, WriteAddr, secremain);   //写已经擦除了的,直接写入扇区剩余区间.
        }
        if (NumByteToWrite == secremain)                                        //写入结束
        {
            break;
        }
        else                                                                   //写入未结束
        {
            secpos++;                                                          //扇区地址增1
            secoff          = 0;                                               //偏移位置为0 

            pBuffer        += secremain;                                       //指针偏移
            WriteAddr      += secremain;                                       //写地址偏移
            NumByteToWrite -= secremain;                                       //字节数递减
            if (NumByteToWrite > 4096)                                         //下一个扇区还是写不完
            {
                secremain = 4096;
            }
            else                                                               //下一个扇区可以写完了
            {
                secremain = NumByteToWrite;
            }
        }
    }
    ;

}   

/**
 ******************************************************************************
 ** \brief  读取FLASH的JEDEC ID
 **
 ** \param  无
 ** \return FLASH的JEDEC ID
 ******************************************************************************/  
uint32_t S25FL132K_SPI_FLASH_ReadID(void)   
{   
    uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;   
         
    S25FL132K_SPI_FLASH_CS_LOW();                           //CS输出低电平   
    S25FL132K_SPI_FLASH_SendByte(S25FL132K_JedecDeviceID);  //发送读取ID的指令 
    Temp0 = S25FL132K_SPI_FLASH_SendByte(Dummy_Byte);       //读取高字节  :Manufacturer 
    Temp1 = S25FL132K_SPI_FLASH_SendByte(Dummy_Byte);       //读取中间字节:Memory Type  
    Temp2 = S25FL132K_SPI_FLASH_SendByte(Dummy_Byte);       //读取低字节  :Capacity
    S25FL132K_SPI_FLASH_CS_HIGH();                          //CS输出高电平       
    Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;            //将所读取的字节拼成32bit的数据
    return Temp;   
}   

/**
 ******************************************************************************
** \brief  读取FLASH的Device ID 发送过程：ABh->dummy->dummy->dummy
 **
 ** \param  无
 ** \return FLASH的ID
 ******************************************************************************/    
uint32_t S25FL132K_SPI_FLASH_ReadDeviceID(void)   
{   
    uint32_t Temp = 0;     
    S25FL132K_SPI_FLASH_CS_LOW();      
    S25FL132K_SPI_FLASH_SendByte(S25FL132K_DeviceID);   //发送ABh
    S25FL132K_SPI_FLASH_SendByte(Dummy_Byte);           //发送dummy
    S25FL132K_SPI_FLASH_SendByte(Dummy_Byte);           //发送dummy   
    S25FL132K_SPI_FLASH_SendByte(Dummy_Byte);           //发送dummy     
    Temp = S25FL132K_SPI_FLASH_SendByte(Dummy_Byte);    //读取Deveice ID
    S25FL132K_SPI_FLASH_CS_HIGH();     
    return Temp;   
}   
  
/**
 ******************************************************************************
 ** \brief  读数据时的指令序列和地址序列的发送
 **
 ** \param  ReadAddr:存放所要读数据的FLASH目标地址
 ** \return 无
 ******************************************************************************/
void S25FL132K_SPI_FLASH_StartReadSequence(uint32_t ReadAddr)   
{    
    S25FL132K_SPI_FLASH_CS_LOW();                                   //CS输出低电平
    S25FL132K_SPI_FLASH_SendByte(S25FL132K_ReadData);               //发送读指令
    S25FL132K_SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);      //发送要读的地址的bit16-bit23    
    S25FL132K_SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);          //发送要读的地址的bit8-bit15    
    S25FL132K_SPI_FLASH_SendByte(ReadAddr & 0xFF);                  //发送要读的地址的bit0-bit7
}   
    
/**
 ******************************************************************************
** \brief  从SPI读一次数据
 **
 ** \param  无
 ** \return 返回所读取的字节
 ******************************************************************************/
uint8_t S25FL132K_SPI_FLASH_ReadByte(void)   
{   
    return (S25FL132K_SPI_FLASH_SendByte(Dummy_Byte));   
}   
 
/**
 ******************************************************************************
** \brief  通过SPI发送一个字节
 **
 ** \param  无
 ** \return 返回SPI数据寄存器数据
 ******************************************************************************/
uint8_t S25FL132K_SPI_FLASH_SendByte(uint8_t byte)   
{      
    while(M0P_SPI0->STAT_f.TXE==0);                  //等待发送缓冲器空标志置位   
    M0P_SPI0->DATA_f.DAT=byte;                       //往数据寄存器写数据
    while(M0P_SPI0->STAT_f.RXNE==0);                 //等待接收缓冲器非空标志置位
    return M0P_SPI0->DATA_f.DAT;                     //返回SPI总线读取的数据
}   
   
/**
 ******************************************************************************
** \brief  发送写使能指令到FLASH
 **
 ** \param  无
 ** \return 无
 ******************************************************************************/  
void S25FL132K_SPI_FLASH_WriteEnable(void)   
{     
    S25FL132K_SPI_FLASH_CS_LOW();                           //CS输出低电平 
    S25FL132K_SPI_FLASH_SendByte(S25FL132K_WriteEnable);    //写指令
    S25FL132K_SPI_FLASH_CS_HIGH();                          //CS输出高电平 
}   
  
/**
 ******************************************************************************
 ** \brief  查询等待WIP标志位清零
 **
 ** \param  无
 ** \return 无
 ******************************************************************************/
void S25FL132K_SPI_FLASH_WaitForWriteEnd(void)   
{   
    uint8_t FLASH_Status = 0;    
    S25FL132K_SPI_FLASH_CS_LOW();                               //CS输出低电平
    S25FL132K_SPI_FLASH_SendByte(S25FL132K_ReadStatusReg);      //发送读取状态标志位的指令   
    do   
    {     
        FLASH_Status = S25FL132K_SPI_FLASH_SendByte(Dummy_Byte);   
    }   
    while ((FLASH_Status & WIP_Flag) != 0);                     //等待状态标志位复位 

    S25FL132K_SPI_FLASH_CS_HIGH();                              //输出高电平 
}   
   
/**
 ******************************************************************************
 ** \brief  使FLASH芯片进入电源关断模式
 **
 ** \param  无
 ** \return 无
 ******************************************************************************/
void S25FL132K_SPI_Flash_PowerDown(void)      
{     
    S25FL132K_SPI_FLASH_CS_LOW();                            //CS输出低电平   
    S25FL132K_SPI_FLASH_SendByte(S25FL132K_PowerDown);       //发送Deep-Power-Down指令 
    S25FL132K_SPI_FLASH_CS_HIGH();                           //CS输出高电平 
}      
   
/**
 ******************************************************************************
 ** \brief  从Deep-Power-Down模式中唤醒
 **
 ** \param  无
 ** \return 无
 ******************************************************************************/  
void S25FL132K_SPI_Flash_WAKEUP(void)      
{      
    S25FL132K_SPI_FLASH_CS_LOW();                            //CS输出低电平
    S25FL132K_SPI_FLASH_SendByte(S25FL132K_ReleasePowerDown);//发送ABh    
    S25FL132K_SPI_FLASH_CS_HIGH();                           //CS输出高电平               
}      
   
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
