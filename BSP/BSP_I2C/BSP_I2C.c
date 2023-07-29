#include "MSP430F5xx_6xx/driverlib.h"
#include "SYS/delay.h"
#include "BSP_I2C.h"

#include "BSP_UART/BSP_UART.h"


#define SUCCESS 0

void UserDelay(u32 count)//400KHzIIC
{
	unsigned int uiCnt = (count*8)/3;
	while (uiCnt --);
}

//初始化IIC
void IIC_Init(void)
{
    /* 设置引脚为输出模式 */
   SCL_OUT();
   SDA_OUT();

   /* 空闲状态，都为高电平 */
   IIC_SCL_High();
   IIC_SDA_High();

#ifdef IIC_SRC01
    GPIO_setAsOutputPin(SDA_PORT,SDA_PIN ); //CLK         
    GPIO_setAsOutputPin(SCL_PORT,SCL_PIN);//DIN
    //GPIO_setAsInputPinWithPullUpResistor(SDA_PORT,SDA_PIN );
    //GPIO_setAsInputPinWithPullUpResistor(SCL_PORT,SCL_PIN);
	IIC_SCL_High();
	IIC_SDA_High();
#endif /* IIC_SRC01 */
}
void LED_Init(void)
{
    LED1_OUT(); //引脚输出模式
    LED2_OUT();
    LED1_OFF(); //灯关
    LED2_OFF();
}
//产生IIC起始信号,主设备产生
void IIC_Start(void)//SDA 10 SCL 010
{
    IIC_SCL_High();
    IIC_SDA_High();
    delay_5us();
    IIC_SDA_Low();
    delay_5us();

#ifdef readme
    /* SDA引脚为输出模式 */
       SDA_OUT();

   /* 空闲状态，都为高电平 */
   IIC_SCL_High();
   IIC_SDA_High();

  // while(READ_SCL=GPIO_INPUT_PIN_HIGH && READ_SCL==GPIO_INPUT_PIN_HIGH);//确保总线空闲

   /* 起始信号：当时钟线SCL为高期间，数据线SDA由高到低的跳变 */
   delay_5us();
   IIC_SDA_Low();//START:when CLK is high,DATA change form high to low

   /* 准备发送或接收数据 */
   delay_5us();
   IIC_SCL_Low();//钳住I2C总线，准备发送或接收数据，因为SCL位低允许数据判断变化
#endif
#ifdef IIC_SRC01
	SDA_OUT();     //sda线输出
	IIC_SCL_High();
	IIC_SDA_High();
	I2C_Delay();
 	IIC_SDA_Low();//START:when CLK is high,DATA change form high to low 
 	I2C_Delay();
	IIC_SCL_Low();//钳住I2C总线，准备发送或接收数据
#endif /* IIC_SRC01 */
}	  
//产生IIC停止信号,主设备产生
void IIC_Stop(void)//SDA 01 SCL 01
{
    SDA_OUT();//sda线输出
    IIC_SCL_High();
    IIC_SDA_Low();
    delay_us(5);
    IIC_SDA_High();//发送I2C总线结束信号
    delay_us(5);    //在加延时是为留时间给从机判断，如果在快速通讯情况下，stop后就要start

#ifdef IIC_SRC01
	SDA_OUT();//sda线输出
	IIC_SCL_Low();//STOP:when CLK is high DATA change form low to high
    IIC_SDA_Low();
    I2C_Delay();
    IIC_SCL_High();
	IIC_SDA_High();//发送I2C总线结束信号
	I2C_Delay();
#endif /* IIC_SRC01 */
}

/***** 应答信号 ****************************************************************/

/* 等待从机应答信号
 * 我们只负责主机应答信号的产生，从机应答信号我们控制不了
 * 第一步.设置SDA为输入
第二步.拉高SDA：主要判断从机应答就是把SDA拉低。
第三步.拉高SCL：数据稳定就是有效数据。
第四步.等待接收器返回应答信号，
    如果数据线SDA一直为高，就一直等待ucErrTime大于250，并返回1(无效应答)，
    如果数据线SDA为低，返回0(有效应答)。
 * */
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack_R(void)//
{
    u8 ucErrTime=0;

    //注：以下是引脚模拟，没有设置开漏输出和挂上拉电阻
    //第8个时钟下降沿后，从机主动把SDA拉低。直到检测到SCL来了上升沿，

    SDA_IN();      //SDA设置为输入
    delay_us(5);
    IIC_SCL_High();delay_us(1);//这里要拉高，读取SDA是都拉低，判断从机是否有应答
    IIC_SDA_High();delay_us(1);
    while(READ_SDA) // 获取SDA电平 看自己定义那个引脚为数据脚
    {
        ucErrTime++;
        if(ucErrTime>250)
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_SCL_Low();//时钟输出0    ,wei
    return 0;
#ifdef IIC_SRC01
	u8 cy;
    SDA_IN();      //SDA设置为输入
    IIC_SCL_High();delay_us(1);
	IIC_SDA_High();delay_us(1);
    if(READ_SDA)
    {
        cy=1;
        IIC_SCL_Low();
        return cy; 
    }      
    else
    {
        cy=0;
    }             
	IIC_SCL_Low();//时钟输出0
	return cy;  
#endif /* IIC_SRC01 */
} 
//无应答
void IIC_Wait_Ack_NO_R(void)
{
    IIC_SCL_High();
	IIC_SCL_Low();
}

//从机应答信号
void IIC_slave_Ack(void)
{
    IIC_SCL_Low();
    IIC_SDA_High();
    delay_5us();
    IIC_SCL_High();
    LED1_ON();
    delay_5us();
    while(READ_SDA==GPIO_INPUT_PIN_HIGH); //低电平为从机有应答，此处定义为GPIO_INPUT_PIN_HIGH卡在while ,如SDA为低电平条件不满足，进行后面语句，GPIO_INPUT_PIN_LOW,GPIO_INPUT_PIN_HIGH
   // delay_ms(50);
    LED1_OFF();
    IIC_SCL_Low();//为下一周期做准备
    LED2_ON();
}

/* 应答信号由接收设备产生，
 * 在SCL为高电平期间，接收设备将SDA拉低，表示传输正确，产生应答。 */
//主机产生ACK应答
void IIC_Ack(void)
{

    IIC_SCL_Low();
    SDA_OUT();
    IIC_SDA_Low();//在SCL上升沿带来前，准备好SDA拉低
    delay_us(5);
    IIC_SCL_High();
    delay_us(5);
    IIC_SCL_Low();

#ifdef IIC_SRC01
    IIC_SCL_Low();
	SDA_OUT();
    IIC_SDA_Low();
    I2C_Delay();
    IIC_SCL_High();
    I2C_Delay();
	IIC_SCL_Low();
#endif /* IIC_SRC01 */
}

/* 主机不产生应答信号NACK
 * 当主机为接受设备，主机对最后一个字节不应答，以向发送设备表示数据传输结束。 */
//不产生ACK应答
void IIC_NAck(void)
{
    IIC_SCL_Low();
    SDA_OUT(); /* sda线输出*/
    IIC_SDA_High(); //在SCL上升沿带来前，准备好SDA至高，表示没应答
    delay_us(5);
    IIC_SCL_High();
    delay_us(5);
    IIC_SCL_Low();
#ifdef IIC_SRC01
	IIC_SCL_Low();
	SDA_OUT();
    IIC_SDA_High();
    I2C_Delay();
    IIC_SCL_High();
    I2C_Delay();
	IIC_SCL_Low();
#endif /* IIC_SRC01 */
}					 				     
/* 功能：IIC发送一个字节,写入一个字节
 * 说明：
 * 数据传输过程中，数据传输保持稳定(在SCL高电平期间，SDA一直保持稳定，没有跳变)，
 * 只有当SCL被拉低后，SDA才能被改变在SCL为高电平期间(有效数据时间段)，发送数据，发送8次数据，
 * 如果数据为1,显然SDA是被拉高;如果数据为0，那么SDA被拉低。
 *
 * 返回从机有无应答
 *  1，有应答
 *  0，无应答
 * */
void IIC_Send_Byte(u8 txd)
{
    u8 t;
    IIC_SCL_Low();//拉低时钟开始数据传输，允许该地变化
    for(t=0;t<8;t++)
    {
        if(txd&0x80) //与1000 0000(0x80)求取最高位, 为1条件为真发送高电平，0条件为假发送低电平
        {
            IIC_SDA_High();  //SDA高电平 ， 发送1
        }
        else
        {
            IIC_SDA_Low();  // SDA低电平 ， 发送0
        }
        txd<<=1;       //最高位出啊输完后，换下一位，所以左移1位
        delay_5us();   //数据准备好了，即TCLCH时间
        IIC_SCL_High();//拉高时钟，从机读取数据
        delay_5us();   //即TCLCH时间
        IIC_SCL_Low(); //为下一个时钟周期作准备
    }

#ifdef README
    u8 t;
       SDA_OUT();
       IIC_SCL_Low();//拉低时钟开始数据传输，允许该地变化
       for(t=0;t<8;t++)
       {
           if((txd&0x80)>>7) //与1000 0000求取最高位，再右移7位，此时最高位在最低位上，从而判断是1还是0
           {
               IIC_SDA_High();  //SDA高电平 ， 发送1
           }
           else
           {
               IIC_SDA_Low();  // SDA低电平 ， 发送0
           }
           txd<<=1;       //最高位出啊输完后，换下一位，所以左移1位

           delay_us(5);   //数据准备好了
           IIC_SCL_High();//拉高时钟，从机读取数据
           delay_us(5);
           IIC_SCL_Low();
           delay_us(5);
       }
#endif


#ifdef IIC_SRC01
    u8 t;   
	SDA_OUT(); 
    IIC_SCL_Low();//拉低时钟开始数据传输
    I2C_Delay();
    for(t=0;t<8;t++)
    {       
        if(txd&0x80)
        {
            IIC_SDA_High();I2C_Delay();
        }  
        else
        {
            IIC_SDA_Low();I2C_Delay();
        }
        txd<<=1;
		IIC_SCL_High();
		I2C_Delay();
        IIC_SCL_Low();
        I2C_Delay();
    }
        //Delay(10);
#endif /* IIC_SRC01 */
    
}


//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
u8 IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
    {
        IIC_SCL_Low();
        delay_us(5);
        IIC_SCL_High(); //根据数据有效性，时钟上升沿期间，数据保持稳定，所以这时候读取数据
        receive<<=1;
        if(READ_SDA)
                receive++;  //看底下图片
        delay_us(5);
    }
    if (!ack)  //当主机为接受设备，主机对最后一个字节不应答，以向发送设备表示数据传输结束。
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK

    return receive;
#ifdef IIC_SRC01
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
		IIC_SCL_Low();
		I2C_Delay();
        IIC_SCL_High();
        receive<<=1;
        if(READ_SDA)
            receive++;
        I2C_Delay();
    }
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK
    return receive;
#endif /* IIC_SRC01 */
}


/*
 *
 * */
int32_t I2cWrite(uint8_t ucAddr, uint8_t ucReg, uint8_t *p_ucVal, uint32_t uiLen)
{
    uint32_t i = 0;
    IIC_Start();                                // I2C 开始信号
    IIC_Send_Byte(ucAddr);                      //主机发送一个字节, (地址)
    if(IIC_Wait_Ack_R() != SUCCESS)return 0;    //等待从机应答信号
    IIC_Send_Byte(ucReg);                       //IIC发送一个字节,()
    if(IIC_Wait_Ack_R() != SUCCESS)return 0;    //等待从机应答信号
    for(i = 0; i < uiLen; i++)
    {
        IIC_Send_Byte(*p_ucVal++);              //主机发送一个字节,
        if(IIC_Wait_Ack_R() != SUCCESS)return 0;//等待从机应答信号
    }
    IIC_Stop();                                 //产生IIC停止信号,主设备产生
    return 1;
}

int32_t I2cRead(uint8_t ucAddr, uint8_t ucReg, uint8_t *p_ucVal, uint32_t uiLen)
{
    uint32_t i = 0;
    uint8_t dd;
    IIC_Start();                               // I2C 开始信号
    IIC_Send_Byte(ucAddr);                     // 主机发送一个字节, (地址 )
    if(IIC_Wait_Ack_R() != SUCCESS)return 11;    //等待从机应答信号
    IIC_Send_Byte(ucReg);                       //IIC发送一个字节,()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    if(IIC_Wait_Ack_R() != SUCCESS)return 55;    //等待从机应答信号

    //IIC_Send_Byte(0x38&0xff);
    for(i = 0; i < uiLen; i++)
    {
        if(i+1 == uiLen){*p_ucVal++ = IIC_Read_Byte(0); dd  = IIC_Read_Byte(0);}//last byte no ask
        else {*p_ucVal++ = IIC_Read_Byte(1); dd  = IIC_Read_Byte(1);}//  ask
        //USCI_A_UART_transmitData(USCI_A1_BASE,dd);
    }
    IIC_Stop();                                                                //产生IIC停止信号,主设备产生


    return 1;
}
