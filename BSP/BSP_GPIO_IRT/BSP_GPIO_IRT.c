#include "BSP_GPIO_IRT/BSP_GPIO_IRT.h"


//gpio interrupt init
void GPIO_IRT_Init(void)
{
    //Init gpio1 interrupt
    GPIO_setAsInputPinWithPullUpResistor(
    PORT_1,PIN_1 );

    //GPIO2 interrupt enabled
    GPIO_enableInterrupt(
    PORT_1,PIN_1);

    //GPIO2 Hi/Lo edge
    GPIO_selectInterruptEdge(
    PORT_1,PIN_1,GPIO_HIGH_TO_LOW_TRANSITION);


    //GPIO2 IFG cleared
    GPIO_clearInterrupt(
    PORT_1,PIN_1);





    //Init gpio2 interrupt
    GPIO_setAsInputPinWithPullUpResistor(
    PORT_2,PIN_2 );

    //GPIO2 interrupt enabled
    GPIO_enableInterrupt(
    PORT_2,PIN_2);

    //GPIO2 Hi/Lo edge
    GPIO_selectInterruptEdge(
    PORT_2,PIN_2,GPIO_HIGH_TO_LOW_TRANSITION);


    //GPIO2 IFG cleared
    GPIO_clearInterrupt(
    PORT_2,PIN_2);
}
#pragma vector=PORT2_VECTOR
__interrupt void Port_2 (void)
{
    //中断判断
    if(GPIO_getInterruptStatus(PORT_1,PIN_1) == PIN_1){
        //P1.0 = toggle
        GPIO_toggleOutputOnPin(
        GPIO_PORT_P1,
        GPIO_PIN0
        );


        //P1.4 IFG cleared
        GPIO_clearInterrupt(
        PORT_1,
        PIN_1
        );
    }
    //中断判断
    if(GPIO_getInterruptStatus(PORT_2,PIN_2) == PIN_2){
        //P1.0 = toggle
        GPIO_toggleOutputOnPin(
        GPIO_PORT_P4,
        GPIO_PIN7
        );


        //P1.4 IFG cleared
        GPIO_clearInterrupt(
        PORT_2,
        PIN_2
        );
    }
}

