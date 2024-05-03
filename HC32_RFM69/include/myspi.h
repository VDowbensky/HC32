#ifndef _RF69_INTERFACE_H_
#define _RF69_INTERFACE_H_

#include <stdint.h>
#include "mygpio.h"
#include "spi.h"


#define NSSPORT GpioPortA
#define NSS_PIN GpioPin15

#define SPIPORT GpioPortB
#define SCK_PIN GpioPin3
#define MOSI_PIN GpioPin5
#define MISO_PIN GpioPin4


extern void initSPI(void);
extern void RF69_select(void);
extern void RF69_deselect(void);
extern uint8_t spi_transfer(uint8_t b);
extern void checkDIO0(void);

#endif

