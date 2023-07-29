#include "BSP_SPI/BSP_SPI.h"
#include "SYS/delay.h"
#include <msp430.h>

#define SPICLK 5000000

static uint8_t receiveData = 0;

void USCI_B0_SPI_Init(void)
{
    bool returnValue;
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P3,
        GPIO_PIN0 + GPIO_PIN2 + GPIO_PIN1
    );
    GPIO_setAsOutputPin(
        GPIO_PORT_P2,
        GPIO_PIN7
        );
     //Initialize Master
    USCI_B_SPI_initMasterParam param = {0};
    param.selectClockSource = USCI_B_SPI_CLOCKSOURCE_SMCLK;
    param.clockSourceFrequency = 25000000;//SMCLK = 25MHZ
    param.desiredSpiClock = SPICLK;
    param.msbFirst = USCI_B_SPI_MSB_FIRST;
    param.clockPhase = USCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT;
    param.clockPolarity = USCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW;
    returnValue =  USCI_B_SPI_initMaster(USCI_B0_BASE, &param);

    if (STATUS_FAIL == returnValue){
        return;
    }

    //Enable SPI module
    USCI_B_SPI_enable(USCI_B0_BASE);

    //Enable Receive interrupt
	USCI_B_SPI_clearInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);
    //USCI_B_SPI_enableInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);

     while (!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE,
               USCI_B_SPI_TRANSMIT_INTERRUPT)) ;

     GPIO_setOutputLowOnPin(
        GPIO_PORT_P2,
        GPIO_PIN7
        );
}
void B0_SPI_Send(uint8_t data)
{
    //USCI_B0 TX buffer ready?
while (!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE,
       USCI_B_SPI_TRANSMIT_INTERRUPT)) ;

//Transmit Data to slave
USCI_B_SPI_transmitData(USCI_B0_BASE, data);
}



uint8_t SPIx_ReadWriteByte(uint8_t data)
{
      //USCI_B0 TX buffer ready?


//Transmit Data to slave
    while(USCI_B_SPI_isBusy(USCI_B0_BASE) == USCI_B_SPI_BUSY);
USCI_B_SPI_transmitData(USCI_B0_BASE, data);
while(USCI_B_SPI_isBusy(USCI_B0_BASE) == USCI_B_SPI_BUSY);
    receiveData = USCI_B_SPI_receiveData(USCI_B0_BASE);

    //__bis_SR_register(GIE);

    return receiveData;
}
/*
//SPI interrupt
#pragma vector=USCI_B0_VECTOR
__interrupt void USCI_B0_ISR (void)
{
    switch (__even_in_range(UCB0IV,4)){
        //Vector 2 - RXIFG
        case 2:


            receiveData = USCI_B_SPI_receiveData(USCI_B0_BASE);


          

            break;
        default: break;
    }
}
*/

