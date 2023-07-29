#ifndef __VOFA_H__
#define __VOFA_H__

#include "BSP_UART/BSP_UART.h"

//typedef uint8_t u8;

#define DataNum 10  //通道数量

#define write_data A1_UART_sentDatas//数据传输到电脑

typedef struct Fdatas {
    float fdata[DataNum];
    unsigned char tail[4];
}Fdatas;


static Fdatas Vofa_Sbuffer = {{0},{0x00,0x00,0x80,0x7f}};

/*
    Vofa_Input
    Vofa数据存入Vofa_sbuffer
    @parm data      VOFA数据
    @parm channel   vofa数据通道
*/
void Vofa_Input(float data,unsigned char channel);


/*
    Vofa_send
    数据输出到电脑
*/
void Vofa_Send(void);
#endif 






