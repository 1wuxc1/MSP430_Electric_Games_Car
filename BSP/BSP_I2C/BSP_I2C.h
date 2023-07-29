#ifndef __BSP_I2C_H__
#define __BSP_I2C_H__
#include "MSP430F5xx_6xx/driverlib.h"
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;


/* SCL-P1.2，SDA-P1.5 */
#define SCL_PORT    GPIO_PORT_P3
#define SCL_PIN     GPIO_PIN2
#define SDA_PORT    GPIO_PORT_P2
#define SDA_PIN     GPIO_PIN7

/* SCL、SDA 高电电平 */
#define IIC_SCL_High()  GPIO_setOutputHighOnPin(SCL_PORT,SCL_PIN)
#define IIC_SCL_Low()   GPIO_setOutputLowOnPin(SCL_PORT,SCL_PIN)
#define IIC_SDA_High()  GPIO_setOutputHighOnPin(SDA_PORT,SDA_PIN)
#define IIC_SDA_Low()   GPIO_setOutputLowOnPin(SDA_PORT,SDA_PIN)

/* SDA 输出、输入模式 */
#define SCL_OUT()   GPIO_setAsOutputPin(SCL_PORT,SCL_PIN)
#define SDA_OUT()   GPIO_setAsOutputPin(SDA_PORT,SDA_PIN)
#define SDA_IN()    GPIO_setAsInputPin(SDA_PORT,SDA_PIN)

/* 获取引脚输入值，读取引脚电平
 * 没有修改寄存器，而是读取PxIN寄存器。
 * 高电平返回GPIO_INPUT_PIN_HIGH（值为1），
 * 低电平返回GPIO_INPUT_PIN_LOW（值为0）。*/
#define READ_SCL    GPIO_getInputPinValue(SCL_PORT,SCL_PIN)
#define READ_SDA    GPIO_getInputPinValue(SDA_PORT,SDA_PIN)

/* LED1、2 */
#define LED1_PORT    GPIO_PORT_P1
#define LED1_PIN     GPIO_PIN0
#define LED2_PORT    GPIO_PORT_P4
#define LED2_PIN     GPIO_PIN7

#define LED1_OUT()      GPIO_setAsOutputPin(LED1_PORT,LED1_PIN)
#define LED1_ON()       GPIO_setOutputHighOnPin(LED1_PORT,LED1_PIN)
#define LED1_OFF()      GPIO_setOutputLowOnPin(LED1_PORT,LED1_PIN)
#define LED1_toggle()   GPIO_toggleOutputOnPin(LED1_PORT,LED1_PIN);// XOR P1.0
#define LED2_OUT()      GPIO_setAsOutputPin(LED2_PORT,LED2_PIN)
#define LED2_ON()       GPIO_setOutputHighOnPin(LED2_PORT,LED2_PIN)
#define LED2_OFF()      GPIO_setOutputLowOnPin(LED2_PORT,LED2_PIN)
#define LED2_toggle()   GPIO_toggleOutputOnPin(LED2_PORT,LED2_PIN);// XOR P1.0

#define TEST_SCL_toggle()   GPIO_toggleOutputOnPin(SCL_PORT,SCL_PIN);



//IIC有操作函�?
void IIC_Init(void);                //初始化IIC的IO�?
void LED_Init(void);
void IIC_Start(void);				//发�?�IIC�?始信�?
void IIC_Stop(void);	  			//发�?�IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发�?�一个字�?
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取�?个字�?
uint8_t IIC_Wait_Ack_R(void); 				//IIC等待ACK信号
void IIC_Wait_Ack_NO_R(void);
void IIC_Ack(void);					//IIC发�?�ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号
void IIC_slave_Ack(void);

int32_t I2cRead(uint8_t ucAddr, uint8_t ucReg, uint8_t *p_ucVal, uint32_t uiLen);
int32_t I2cWrite(uint8_t ucAddr, uint8_t ucReg, uint8_t *p_ucVal, uint32_t uiLen);  


#endif
