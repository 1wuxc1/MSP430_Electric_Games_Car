

#include "BSP_UART/BSP_UART.h"


#define UCS_XT1_CRYSTAL_FREQUENCY   32000
#define UCS_XT2_CRYSTAL_FREQUENCY   4000000

#define UCS_XT1_TIMEOUT             5000
#define UCS_XT2_TIMEOUT             5000

#define TARGET_DOCCLK_KHZ           25000
#define TARGET_DOCCLK_RATIO         763
static uint8_t received_0_Data = 0x00;
static uint8_t received_1_Data = 0x00;



//Baud rate 9600
void uart_a0_init(void)
{
   
    //P3.3,4 = USCI_A0 TXD/RXD
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P3,
        GPIO_PIN3 + GPIO_PIN4
        );

    //Baudrate = 9600, clock freq = 32768hz
    //UCBRx = 3, UCBRFx = 0, UCBRSx = 2, UCOS16 = 3
    USCI_A_UART_initParam param = {0};
    param.selectClockSource = USCI_A_UART_CLOCKSOURCE_ACLK;
    param.clockPrescalar = 3;
    param.firstModReg = 0;
    param.secondModReg = 3;
    param.parity = USCI_A_UART_NO_PARITY;
    param.msborLsbFirst = USCI_A_UART_LSB_FIRST;
    param.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;
    param.uartMode = USCI_A_UART_MODE;
    param.overSampling = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

    if (STATUS_FAIL == USCI_A_UART_init(USCI_A0_BASE, &param)){
        return;
    }

    //Enable UART module for operation
    USCI_A_UART_enable(USCI_A0_BASE);

    //Enable Receive Interrupt
	USCI_A_UART_clearInterrupt(USCI_A0_BASE,USCI_A_UART_RECEIVE_INTERRUPT);
    USCI_A_UART_enableInterrupt(USCI_A0_BASE,USCI_A_UART_RECEIVE_INTERRUPT);

    //__enable_interrupt();

}


//Baud rate 9600
void uart_a1_init(void)
{
   
    //P3.3,4 = USCI_A0 TXD/RXD
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P4,
        GPIO_PIN4 + GPIO_PIN5
        );

    //Baudrate = 9600, clock freq = 32768hz
    //UCBRx = 3, UCBRFx = 0, UCBRSx = 2, UCOS16 = 3
    USCI_A_UART_initParam param = {0};
    param.selectClockSource = USCI_A_UART_CLOCKSOURCE_ACLK;
    param.clockPrescalar = 3;
    param.firstModReg = 0;
    param.secondModReg = 3;
    param.parity = USCI_A_UART_NO_PARITY;
    param.msborLsbFirst = USCI_A_UART_LSB_FIRST;
    param.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;
    param.uartMode = USCI_A_UART_MODE;
    param.overSampling = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

    if (STATUS_FAIL == USCI_A_UART_init(USCI_A1_BASE, &param)){
        return;
    }

    //Enable UART module for operation
    USCI_A_UART_enable(USCI_A1_BASE);

    //Enable Receive Interrupt
	  USCI_A_UART_clearInterrupt(USCI_A1_BASE,USCI_A_UART_RECEIVE_INTERRUPT);
    USCI_A_UART_enableInterrupt(USCI_A1_BASE,USCI_A_UART_RECEIVE_INTERRUPT);

    //__enable_interrupt();

}

void A1_UART_sentDatas(uint8_t*Data,uint8_t Size)
{
    uint8_t temp;
    for(temp = 0;temp <(Size);temp++)
         USCI_A_UART_transmitData(USCI_A1_BASE,Data[temp]);
    
}
uint8_t A0_UART_receive(void)
{
    return received_0_Data;
}
uint8_t A1_UART_receive(void)
{
    return received_1_Data;
}

void A0_UART_sentDatas(uint8_t*Data,uint8_t Size)
{
    uint8_t temp;
    for(temp = 0;temp <(Size);temp++)
    {
         USCI_A_UART_transmitData(USCI_A0_BASE,Data[temp]);
         
    }
    
}




#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR (void)
{
    switch (__even_in_range(UCA1IV,4)){
        //Vector 2 - RXIFG
        case 2:



            received_1_Data = USCI_A_UART_receiveData(USCI_A1_BASE);
            //USCI_A_UART_transmitData(USCI_A0_BASE,receivedData);

            break;
        default: break;
    }
}


