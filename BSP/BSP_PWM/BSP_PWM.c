#include "BSP_PWM.h"
#include "MSP430F5xx_6xx/driverlib.h"



Timer_B_initCompareModeParam initCompParam = {0};

/*PWM_f=10KHZ
Period = 2500
*/
void PWM_Init(void)
{

    
    GPIO_setAsPeripheralModuleFunctionOutputPin(
		GPIO_PORT_P3,
		GPIO_PIN6+GPIO_PIN5
		);


 //Start timer
    Timer_B_initUpModeParam initUpParam= {0};
    initUpParam.clockSource = TIMER_B_CLOCKSOURCE_SMCLK;
    initUpParam.clockSourceDivider = TIMER_B_CLOCKSOURCE_DIVIDER_1;
    initUpParam.timerPeriod = 2500;
    initUpParam.timerInterruptEnable_TBIE = TIMER_B_TBIE_INTERRUPT_DISABLE;
    initUpParam.captureCompareInterruptEnable_CCR0_CCIE =
        TIMER_B_CCIE_CCR0_INTERRUPT_DISABLE;
    initUpParam.timerClear = TIMER_B_DO_CLEAR;
    initUpParam.startTimer = false;
    Timer_B_initUpMode(TIMER_B0_BASE, &initUpParam);

	Timer_B_startCounter(TIMER_B0_BASE,
		TIMER_B_UP_MODE
		);

	//Initialize compare mode to generate PWM1

    initCompParam.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_6;
    initCompParam.compareInterruptEnable = TIMER_B_CAPTURECOMPARE_INTERRUPT_DISABLE;
    initCompParam.compareOutputMode = TIMER_B_OUTPUTMODE_RESET_SET;
    initCompParam.compareValue = 0;
    Timer_B_initCompareMode(TIMER_B0_BASE, &initCompParam);

	//Initialize compare mode to generate PWM2
 
    initCompParam.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_5;
    initCompParam.compareInterruptEnable = TIMER_B_CAPTURECOMPARE_INTERRUPT_DISABLE;
    initCompParam.compareOutputMode = TIMER_B_OUTPUTMODE_RESET_SET;
    initCompParam.compareValue = 0;
    Timer_B_initCompareMode(TIMER_B0_BASE, &initCompParam);
}

//最大为2500
void PWM_OUT(uint8_t num,uint16_t PWM_OUT_Value)
{
    if(num == PWM_OUT_1)
    {
        initCompParam.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_5;
         initCompParam.compareValue = PWM_OUT_Value;
    }
    else if(num == PWM_OUT_2)
    {
        initCompParam.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_6;
         initCompParam.compareValue = PWM_OUT_Value;
    }
     Timer_B_initCompareMode(TIMER_B0_BASE, &initCompParam);
}
