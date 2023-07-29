#include "BSP_TimeA1/BSP_TimeA1.h"

//42ms
void Timer_A1_Init(void)
{
    Timer_A_clearTimerInterrupt(TIMER_A1_BASE);

    Timer_A_initContinuousModeParam param = {0};
    param.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    param.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_8;
    param.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE;
    param.timerClear = TIMER_A_DO_CLEAR;
    param.startTimer = true;
    Timer_A_initContinuousMode(TIMER_A1_BASE, &param);


    __enable_interrupt();

}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR (void)
{
    //Any access, read or write, of the TAIV register automatically resets the
    //highest "pending" interrupt flag
    switch ( __even_in_range(TA1IV,14) ){
        case  0: break;                          //No interrupt
        case  2: break;                          //CCR1 not used
        case  4: break;                          //CCR2 not used
        case  6: break;                          //CCR3 not used
        case  8: break;                          //CCR4 not used
        case 10: break;                          //CCR5 not used
        case 12: break;                          //CCR6 not used
        case 14:


            
            break;
        default: break;
    }
}
