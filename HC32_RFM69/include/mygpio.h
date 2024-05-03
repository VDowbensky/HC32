#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_
#include <stdint.h>
#include "gpio.h"
#include "main.h"


#define KEYDELAY 50
#define KEY_LEFT 1
#define KEY_RIGHT 2
#define KEY_BOTH 3

//hardware

#define UARTPORT GpioPortB
#define TXD_PIN GpioPin6
#define RXD_PIN GpioPin7

#define DE_PORT GpioPortB
#define DE GpioPin11	 

#define LEDPORT GpioPortC
#define RED GpioPin15  //pin3
#define GREEN GpioPin14  //pin2
//#define BLUE GpioPin12


//#define KEYPORT GpioPortB
//#define K0 GpioPin11
//#define K1 GpioPin0 //unused


#define KEYPORT GpioPortA
#define K0 GpioPin2 //pin 8 in sch
#define K1 GpioPin4 //pin 9 in sch


#define RESET_PORT GpioPortA
#define RESET_PIN GpioPin10

#define DIO0_PORT GpioPortD
#define DIO0_PIN GpioPin3
#define DIO0_IRQPORT 3 //Port D
#define DIO0_IRQn PORTD_IRQn
//#define DIO0_IRQHandler PORTD_IRQHandler


extern void initIO(void);
extern void Green_On (void);
extern void Green_Off (void);
extern void Red_On (void);
extern void Red_Off (void);

extern void DIO0_enableIRQ(void);
extern void DIO0_disableIRQ(void);



#endif


