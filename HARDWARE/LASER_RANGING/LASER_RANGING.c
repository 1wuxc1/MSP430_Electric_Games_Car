#include "LASER_RANGING/LASER_RANGING.h"

static uint8_t Rec;
static uint8_t UART_A0_RX_sta;
static uint8_t UART_A0_Package[LASER_PACKAGE_LEN];


/*********************************
 * 激光初始化
 * @date 2023 7.23
 * @name 吴昕灿
 * @param void 
 * @return void
**********************************/
void LASER_RANGING_Init(void)
{
    uart_a0_init();

}


/*********************************
 * 激光数据读取命令发送
 * @date 2023 7.23
 * @name 吴昕灿
 * @param void 
 * @return void
**********************************/
void LASER_RANGING_Send_instructions(void)
{   

    uint8_t data[8] = {0x50,0x03,0x00,0x34,0x00,0x01,0xc8,0x45};
    //50 03 00 34 00 01 c8 45
    A0_UART_sentDatas(data,8);
    
}





/*********************************
 * 激光数据读取
 * @date 2023 3.13
 * @name 吴昕灿
 * @param void 
 * @return distance:Y轴距离
**********************************/
uint16_t distance_Read(void)
{
    uint16_t distance;
    distance = UART_A0_Package[4];
    distance |= UART_A0_Package[3]<<8;
    return distance;
}





#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR (void)
{
    static uint8_t Temp;
    switch (__even_in_range(UCA0IV,4)){
        //Vector 2 - RXIFG
        case 2:
            Rec =  USCI_A_UART_receiveData(USCI_A0_BASE);// 读取接收到的数据


        if(UART_A0_RX_sta == 0)  //接收未开始
        {
            if(Rec == LASER_PACKAGE_HEAD)
            {
                UART_A0_RX_sta = 1;

            }
            else 
            {
                UART_A0_RX_sta = 0;
            } 
        }
        if(UART_A0_RX_sta == 1)//开始接收
        { 
            
            if(Temp == (LASER_PACKAGE_LEN-1))
            {
                //USART2_Package[Temp] = LASER_PACKAGE_END;
                UART_A0_RX_sta = 0;//接收完成
                Temp = 0;

            }
            else
            {
                UART_A0_Package[Temp] = Rec;
                Temp++;

            } 
        }

            break;
        default: break;
    }
}


