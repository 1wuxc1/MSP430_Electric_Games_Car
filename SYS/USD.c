
#include "USD.h"
#include "MSP430F5xx_6xx/driverlib.h"
#define UCS_XT1_CRYSTAL_FREQUENCY   32000
#define UCS_XT2_CRYSTAL_FREQUENCY   4000000

#define UCS_XT1_TIMEOUT             5000
#define UCS_XT2_TIMEOUT             5000

#define TARGET_DOCCLK_KHZ           25000
#define TARGET_DOCCLK_RATIO         763

void USD_Init(void)
{


    PMM_setVCore(PMM_CORE_LEVEL_1);
    PMM_setVCore(PMM_CORE_LEVEL_2);
    PMM_setVCore(PMM_CORE_LEVEL_3);


  
    //set FLLREF = REFOCLK = 32768hz
    UCS_initClockSignal(
        UCS_FLLREF,
        UCS_REFOCLK_SELECT,
        UCS_CLOCK_DIVIDER_1
        );
    //Set ACLK = REFOCLK = 32768hz
    UCS_initClockSignal(
        UCS_ACLK,
        UCS_REFOCLK_SELECT,
        UCS_CLOCK_DIVIDER_1
        );

    //Set Ratio and Desired MCLK Frequency  and initialize DOCCLK
    UCS_initFLLSettle(
        TARGET_DOCCLK_KHZ,
        TARGET_DOCCLK_RATIO
        );
     //SMCLK = DCOCLK = 25MHZ
       UCS_initClockSignal(
        UCS_SMCLK,
        UCS_DCOCLK_SELECT,
        UCS_CLOCK_DIVIDER_1
        );
    //MCLK = DCOCLK = 25MHZ
        UCS_initClockSignal(
        UCS_MCLK,
        UCS_DCOCLK_SELECT,
        UCS_CLOCK_DIVIDER_1
        );
       //ACLK, MCLK, MCLK set out to pins
   
  

    //设置ACLK为32KHZ SMCLK MCLK为25MHZ
   


    //Configure UART pins (UCA0TXD/UCA0SIMO, UCA0RXD/UCA0SOMI)
    //Set P3.0 and P3.1 as Module Function Input
}
