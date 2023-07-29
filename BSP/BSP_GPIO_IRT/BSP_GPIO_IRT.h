#ifndef __BSP_GPIO_IRT_H__
#define __BSP_GPIO_IRT_H__

#include <msp430.h>
#include "MSP430F5xx_6xx/driverlib.h"


#define PORT_1  GPIO_PORT_P2 //Init gpio port 1
#define PIN_1   GPIO_PIN4   //Init gpio pin 1

#define PORT_2  GPIO_PORT_P2 //Init gpio port 2
#define PIN_2   GPIO_PIN0   //Init gpio pin 2


void GPIO_IRT_Init(void);

#endif
