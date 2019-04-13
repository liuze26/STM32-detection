#include "AM2320.h"
#include "IIC.h"
#include "Delay.h"

unsigned char IIC_TX_Buffer[]={0x03,0x00,0x02}; //读温湿度命令（无CRC校验）
unsigned char IIC_RX_Buffer[10];//读回的温湿度

void Start(void)
{
	SDA_OUT();     //sda线输出 
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(20);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(20);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}
	  
void Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(20);
	IIC_SCL=1; 	
	delay_us(20);	
	IIC_SDA=1;//发送I2C总线结束信号					   	
}

u8 Wait_Ack(void)
{
	u8 i=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;delay_us(20); 
	IIC_SCL=1;delay_us(20);
	if(READ_SDA==0)
	{
		i=1;
	}else
	{
		i=0;
	}
	IIC_SCL=0;//时钟输出0 	   
	return i;  
} 

void Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(20);
	IIC_SCL=1;
	delay_us(20);
	IIC_SCL=0;
	IIC_SDA=1;
}
    
void NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(20);
	IIC_SCL=1;
	delay_us(20);
	IIC_SCL=0;
	IIC_SDA=1;
}					 				     
	  
void Send_Byte(u8 txd)
{                        
    u8 t;   
	  SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		//delay_us(10);
		IIC_SCL=1;
		delay_us(10);
		IIC_SCL=0;	
		delay_us(10);
    }	 
} 

u8 Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(10);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(10);
    }					 
    if (ack)
        IIC_Ack(); //发送ACK 
    else
        IIC_NAck();//发送nACK  
    return receive;
}

void WriteNByte(unsigned char sla,unsigned char *s,unsigned char n)
{
   unsigned char i;
   
   Start();  //启动I2C
   Send_Byte(sla);//发送器件地址
   Wait_Ack();
   
   for(i=0;i<n;i++)//写入8字节数据
   {
      Send_Byte(*(s+i));
	  Wait_Ack();
   }
   Stop();
}

void ReadNByte(unsigned char Sal, unsigned char *p,unsigned char n)
{
  unsigned char i;
  
  Start();    // 启动I2C
  Send_Byte((Sal)| 0x01); //发送器件地址
  Wait_Ack();

  delay_us(50); // 延时时间必须大于30us 只要大于 30us 以上的值都可以 但是最好不要太长 ，测试时，试过25MS都OK！ 
        
  for(i=0;i<n-1;i++)  //读取字节数据
  {
     *(p+i)=Read_Byte(1); //读取数据
  }
  *(p+n-1)=Read_Byte(0);
  Stop();  
}

void Waken(void)
{
  Start();       // 启动I2C
  Send_Byte(AM2320_Addr); // 发送器件地址
  NAck();
  //Wait_Ack();	       // 唤醒指令时 传感器不会回ACK 但是第一定要发检测ACK的时钟 否则会出错
  delay_ms(2);       // 至少延时1个Ms	说明书里，有个最大值 ，实际当中 你只要大于1MS
  Stop();	
}

//计算CRC校验码	
unsigned int CRC16(unsigned char *ptr, unsigned char len)
{
   unsigned int crc=0xffff;
   unsigned char i;
   while(len--)
   {
       crc ^=*ptr++;
       for(i=0;i<8;i++)
	   {
	       if(crc & 0x1)
		   {
		      crc>>=1;
			  crc^=0xa001;
		   }
		   else
		   {
		      crc>>=1;
		   }
	   }
   }
   return crc;
}
//检测CRC校验码是否正确
unsigned char CheckCRC(unsigned char *ptr,unsigned char len)
{
  unsigned int crc;
	crc=(unsigned int)CRC16(ptr,len-2);
	if(ptr[len-1]==(crc>>8) && ptr[len-2]==(crc & 0x00ff))
	{
	    return 0xff;
	}
	else
	{
	   return 0x0;
	}
}

void Get_Humi(float *humi)
{
  u16 temp;
  u8 i;
	
  for(i=0;i<10;i++)IIC_RX_Buffer[i]=0;

  Waken();	  // 唤醒传感器 
  WriteNByte(AM2320_Addr,IIC_TX_Buffer,3);//发送读指令 
  delay_ms(4);//发送读取或写数据命令后，至少等待2MS（给探头返回数据作时间准备） 
  ReadNByte(AM2320_Addr,IIC_RX_Buffer,6);//读返回数据	
  
  if(CheckCRC(IIC_RX_Buffer,6))
  {
	temp=(IIC_RX_Buffer[2]<<8)+IIC_RX_Buffer[3];
	*humi=(float)temp/10;
  }
}


