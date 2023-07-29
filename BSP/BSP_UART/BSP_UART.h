#ifndef __BSP_USART_H__
#define __BSP_USART_H__

#include "MSP430F5xx_6xx/driverlib.h"
#include <msp430.h>


//void USD_Init(void);
void uart_a0_init(void);
void uart_a1_init(void);

uint8_t A0_UART_receive(void);
uint8_t A1_UART_receive(void);
void A0_UART_sentDatas(uint8_t*Data,uint8_t Size);
void A1_UART_sentDatas(uint8_t*Data,uint8_t Size);


#endif
