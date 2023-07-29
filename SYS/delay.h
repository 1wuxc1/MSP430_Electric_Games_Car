#ifndef __DELAY_H__
#define __DELAY_H__

#include "MSP430F5xx_6xx\driverlib.h"

#if 1
#define MCLK_IN_HZ      25000000
#define delay_us(x)     __delay_cycles((MCLK_IN_HZ/1000000*(x)))
#define delay_ms(x)     __delay_cycles((MCLK_IN_HZ/1000*(x)))
#else
#define CPU_F                            ((double)25000000) 		//CPU_F代表系统选用的主时钟大小，单位Hz
#define delay_us(x)                      __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define delay_ms(x)                      __delay_cycles((long)(CPU_F*(double)x/1000.0))
#endif


#define delay_5us()     delay_us(5)
#define delay_1us()     delay_us(1)
#define delay_5ms()     delay_ms(5)


#endif
