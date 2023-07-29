#ifndef __BSP_SPI_H__
#define __BSP_SPI_H__
#include "MSP430F5xx_6xx/driverlib.h"

void USCI_B0_SPI_Init(void);
void B0_SPI_Send(uint8_t data);
uint8_t SPIx_ReadWriteByte(uint8_t data);

#endif
