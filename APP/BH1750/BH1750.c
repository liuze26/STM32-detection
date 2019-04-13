#include "BH1750.h"
#include "IIC.h"

u8 BH1750_BUF[2];

void Write_BH1750(u8 cmd)
{
    IIC_Start();                  //起始信号
    IIC_Send_Byte(BH1750_Addr);   //发送设备地址+写信号
	IIC_Wait_Ack();
    IIC_Send_Byte(cmd);    //内部寄存器地址
	IIC_Wait_Ack();
    IIC_Stop();                   //发送停止信号
}

void Read_BH1750(void)
{   	
    IIC_Start();                          //起始信号
    IIC_Send_Byte(BH1750_Addr+1);         //发送设备地址+读信号
	IIC_Wait_Ack();
	BH1750_BUF[0]=IIC_Read_Byte(1);  //发送ACK
	BH1750_BUF[1]=IIC_Read_Byte(0);  //发送NACK
    IIC_Stop();                          //停止信号
}

void Start_BH1750(void)
{
	Write_BH1750(BH1750_ON);	 //power on
	Write_BH1750(BH1750_RSET);	//clear
	Write_BH1750(BH1750_ONE);  //一次H分辨率模式，至少120ms，之后自动断电模式  
}

u16 Convert_BH1750(void)
{
	u16 res;
	float res_lx;
	res=(BH1750_BUF[0]<<8)+BH1750_BUF[1];
	res_lx=res/1.2;
	return res_lx;
}



