#ifndef __IIC_H__
#define __IIC_H__
#include "stm32f10x.h"
#include "SYS.h"


////驱动接口，GPIO模拟IIC
//SCL-->PB6
//SDA-->PB7
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0x80000000;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0x30000000;}


//IO操作函数	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //输入SDA 

//IIC所有操作函数
void IIC_Init(void);          //初始化IIC的IO口				 
void IIC_Start(void);			   	//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

unsigned char I2C_ReadOneByte(unsigned char I2C_Addr,unsigned char addr);
u8 IICreadBytes(u8 dev, u8 reg, u8 length, u8 *data);
u8 IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data);
void IIC_writeOneByte(unsigned char dev, unsigned char reg, unsigned char data);

#endif

//------------------End of File----------------------------//

