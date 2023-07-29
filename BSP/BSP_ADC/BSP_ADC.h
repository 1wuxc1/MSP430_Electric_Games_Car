#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#include "MSP430F5xx_6xx/driverlib.h"


void ADC_Init(void);
void ADC_A6_start(void);
int ADC_A6_Re_data(void);

#endif
