#ifndef __BSP_PWM_H__
#define __BSP_PWM_H__

#include "MSP430F5xx_6xx/driverlib.h"
#define PWM_OUT_1 0X01
#define PWM_OUT_2 0X02

void PWM_Init(void);
void PWM_OUT(uint8_t num,uint16_t PWM_OUT_Value);

#endif
