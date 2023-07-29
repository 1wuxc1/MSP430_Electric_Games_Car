#ifndef __LASER_RANGING_H__
#define __LASER_RANGING_H__

#include "BSP_UART/BSP_UART.h"

#define LASER_PACKAGE_HEAD         0x50        //激光数据包头1
#define  LASER_PACKAGE_LEN  7
//#define LASER_PACKAGE_END          0x7f        //激光数据包尾
#define LASER_PACKAGE_ERRO         0x28        //激光数据包错误


uint16_t distance_Read(void);
void LASER_RANGING_Send_instructions(void);
void LASER_RANGING_Init(void);

#endif
