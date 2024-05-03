#include "spi.h"
#include "gpio.h"
#include "main.h"



void RF69_select(void);
void RF69_deselect(void);
void RF69_HWreset (void);
void initSPI(void);
uint8_t spi_transfer(uint8_t b);
void checkDIO0(void);

//init SPI and RF GPIO
void initSPI(void)
{

		stc_gpio_config_t gpio;
		Sysctrl_SetPeripheralGate(SysctrlPeripheralSpi0, TRUE);
	  DDL_ZERO_STRUCT(gpio);
	  //NSS pin
		gpio.enDir = GpioDirOut;
		//gpio.enDrv = GpioDrvH;
		//gpio.enPuPd = GpioNoPuPd;
		//gpio.enOD = GpioOdDisable;
		//gpio.enCtrlMode = GpioAHB;
		Gpio_Init(NSSPORT, NSS_PIN, &gpio); 
		Gpio_SetAfMode(NSSPORT, NSS_PIN, GpioAf1);
	  //Gpio_SetIO(NSSPORT, NSS_PIN); //
	
	//SPI pins configurations
		//SCK pin
		//gpio.enDir = GpioDirOut;
		//gpio.enDrv = GpioDrvH;
		//gpio.enPuPd = GpioNoPuPd;
		//gpio.enOD = GpioOdDisable;
		//gpio.enCtrlMode = GpioAHB;
		Gpio_Init(SPIPORT, SCK_PIN, &gpio); 
		Gpio_SetAfMode(SPIPORT, SCK_PIN, GpioAf1); 
		//MOSI pin
		//gpio.enDir = GpioDirOut;
		//gpio.enDrv = GpioDrvH;
		//gpio.enPuPd = GpioNoPuPd;
		//gpio.enOD = GpioOdDisable;
		//gpio.enCtrlMode = GpioAHB;
		Gpio_Init(SPIPORT, MOSI_PIN, &gpio); 
		Gpio_SetAfMode(SPIPORT, MOSI_PIN, GpioAf1); 
	  //MISO pin 
		gpio.enDir = GpioDirIn;
		//gpio.enDrv = GpioDrvL;
		//gpio.enPuPd = GpioNoPuPd;
		//gpio.enOD = GpioOdDisable;
		//gpio.enCtrlMode = GpioAHB;
		Gpio_Init(SPIPORT, MISO_PIN, &gpio);
		Gpio_SetAfMode(SPIPORT, MISO_PIN, GpioAf1);		

	//init SPI module
		stc_spi_config_t  SPIConfig;
//    uint8_t   i;
    DDL_ZERO_STRUCT(SPIConfig);
		SPIConfig.bCPHA = Spicphafirst;
    SPIConfig.bCPOL = Spicpollow;
    SPIConfig.bIrqEn = FALSE;
    SPIConfig.bMasterMode = SpiMaster;
    SPIConfig.u8BaudRate = SpiClkDiv8;
    SPIConfig.pfnSpi0IrqCb = NULL;
    Spi_Init(Spi0,&SPIConfig);
		
		Spi_SetCS(Spi0,TRUE);
  
}

void RF69_select(void)
{
	//Gpio_ClrIO(NSSPORT, NSS_PIN);
	Spi_SetCS(Spi0,FALSE);
}
void RF69_deselect(void)
{
	//Gpio_SetIO(NSSPORT, NSS_PIN);
	Spi_SetCS(Spi0,TRUE);
}

uint8_t spi_transfer(uint8_t b)
{
	//uint8_t data;
	//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	//Spi_SendData(Spi0, b);
	//data = Spi_ReceiveData(Spi0, 1);
	//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
	//SPI_I2S_ReceiveData(SPI1);
	//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
	//data = (uint8_t)SPI_I2S_ReceiveData(SPI1);
	//while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
	return Spi_MasterTransfer(Spi0, b);
	//return data;
}

void RF69_HWreset (void)
{
    //set reset port as output
	  stc_gpio_config_t gpio;                    // RESET pin configuration
	
		gpio.enDir = GpioDirOut;
		gpio.enDrv = GpioDrvH;
		gpio.enPuPd = GpioNoPuPd;
		gpio.enOD = GpioOdDisable;
		gpio.enCtrlMode = GpioAHB;
		Gpio_Init(RESET_PORT, RESET_PIN, &gpio); 
	
	  Gpio_SetIO(RESET_PORT, RESET_PIN);
	  delay_ms(10);
		Gpio_ClrIO(RESET_PORT, RESET_PIN);
		delay_ms(10);
	
	//set RESET pin to HI_Z mode again
		gpio.enDir = GpioDirIn;
		gpio.enDrv = GpioDrvH;
		gpio.enPuPd = GpioNoPuPd;
		gpio.enOD = GpioOdDisable;
		gpio.enCtrlMode = GpioAHB;
		Gpio_Init(RESET_PORT, MOSI_PIN, &gpio); 
	  delay_ms(10);

}
void checkDIO0(void)
{
	while (Gpio_GetInputIO(DIO0_PORT, DIO0_PIN) == 0);
}
