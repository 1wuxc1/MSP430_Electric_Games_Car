#include <msp430.h> 
#include "BSP_SPI/BSP_SPI.h"
#include "BSP_I2C/BSP_I2C.h"
#include "BSP_PWM/BSP_PWM.h"
#include "BSP_UART/BSP_UART.h"

#include "sofeware/VOFA.h"

#include "sys/USD.h"
#include "sys/delay.h"

#include "NRF24L01/24l01.h"
#include "OLED/oled.h"
#include "LASER_RANGING/LASER_RANGING.h"


void main (void)
{
    //Stop WDT
    WDT_A_hold(WDT_A_BASE);
    USD_Init();
    IIC_Init();
    uart_a1_init();
    OLED_Init();

    while(1)
    {
        
        //OLED_Clear();
        Vofa_Send();



    }
}
