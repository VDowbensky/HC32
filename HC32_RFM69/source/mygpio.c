#include "mygpio.h"


void delay_ms (uint16_t ms);
void initIO(void);
void Green_On (void);
void Green_Off (void);
void Red_On (void);
void Red_Off (void);

void DIO0_enableIRQ(void);
void DIO0_disableIRQ(void);

void PORTD_IRQHandler(void) //
{
  if(Gpio_GetIrqStatus(DIO0_PORT, DIO0_PIN) == TRUE)
  {
    Gpio_ClearIrq(DIO0_PORT, DIO0_PIN);
		RF69_RXflag = 1;
	}
}


void initIO(void)
{
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	//init key and LED's lines

		stc_gpio_config_t gpio;
	  DDL_ZERO_STRUCT(gpio);
		Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);	
		gpio.enDir = GpioDirOut;
		gpio.enDrv = GpioDrvH;
		gpio.enPuPd = GpioNoPuPd;
		//gpio.enOD = GpioOdEnable;
		//gpio.enCtrlMode = GpioAHB;
		Gpio_Init(LEDPORT, RED, &gpio);
	
		gpio.enDir = GpioDirOut;
		gpio.enDrv = GpioDrvH;
		gpio.enPuPd = GpioNoPuPd;
		//gpio.enOD = GpioOdEnable;
		//gpio.enCtrlMode = GpioAHB;
		Gpio_Init(LEDPORT, GREEN, &gpio);
		
		Green_Off();
	  Red_Off();

		gpio.enDir = GpioDirIn;
		//gpio.enDrv = GpioDrvL;
		gpio.enPuPd = GpioPu;
		//gpio.enOD = GpioOdEnable;
		//gpio.enCtrlMode = GpioAHB;
		Gpio_Init(KEYPORT, K0, &gpio);

		gpio.enDir = GpioDirIn;
		//gpio.enDrv = GpioDrvL;
		gpio.enPuPd = GpioPu;
		//gpio.enOD = GpioOdEnable;
		//gpio.enCtrlMode = GpioAHB;
		Gpio_Init(KEYPORT, K1, &gpio);
		
		//DE pin
		gpio.enDir = GpioDirOut;
		gpio.enDrv = GpioDrvH;
		gpio.enPuPd = GpioNoPuPd;
		Gpio_Init(DE_PORT, DE, &gpio);		
		
//DIO0 input pin configuration

		gpio.enDir = GpioDirIn;
		gpio.enDrv = GpioDrvL;
		gpio.enPuPd = GpioPd;
		//gpio.enOD = GpioOdDisable;
		gpio.enCtrlMode = GpioAHB;
		Gpio_Init(DIO0_PORT, DIO0_PIN, &gpio);
		
		Gpio_ClearIrq(DIO0_PORT, DIO0_PIN); //maybe not needed
		EnableNvic(DIO0_IRQn, IrqLevel3, TRUE);
		//DIO0_disableIRQ();
		DIO0_enableIRQ();
	
}

void DIO0_enableIRQ(void)
{
	Gpio_EnableIrq(DIO0_PORT, DIO0_PIN, GpioIrqRising);	
}



void DIO0_disableIRQ(void)
{
	Gpio_DisableIrq(DIO0_PORT, DIO0_PIN, GpioIrqRising);
}


//DIO0 interrupt (used in RX mode only)
//void Gpio_IRQHandler(uint8_t u8Param)
//{
//	if (u8Param == DIO0_IRQPORT) DIO0_IRQhandler();
//}


//indication
void Green_Off (void)
{
	Gpio_ClrIO(LEDPORT, GREEN);
}
void Green_On (void)
{
	Gpio_SetIO(LEDPORT, GREEN);
}
void Red_Off (void)
{
	Gpio_ClrIO(LEDPORT, RED);
}
void Red_On (void)
{
	Gpio_SetIO(LEDPORT, RED);
}

