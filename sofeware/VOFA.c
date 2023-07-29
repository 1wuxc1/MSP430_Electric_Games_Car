#include "VOFA.h"

/*
    Vofa_Input
    Vofa数据存入Vofa_sbuffer
    @prarm data      VOFA数据
    @prarm channel   vofa数据通道
*/

void Vofa_Input(float data,unsigned char channel)
{
	if(channel < DataNum)
		Vofa_Sbuffer.fdata[channel] = data;
}

/*
    Vofa_send
    数据输出到电脑
*/
void Vofa_Send(void)
{
	write_data((uint8_t*)&Vofa_Sbuffer,sizeof(Fdatas));
}

