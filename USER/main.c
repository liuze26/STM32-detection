#include "stm32f10x.h"
#include "Delay.h"
#include "SYS.h"
#include "USART_1.h" 
#include "USART_2.h" 
#include "USART_3.h" 
#include "BMP280.h" 
#include "BH1750.h"
#include "AM2320.h"
#include "LED.h"
#include "Timer.h"
#include "KEY.h"
#include "BSP.h"
#include "string.h"
#include "ESP8266.h"
//#include "W25Q16.h" 

int main(void)
{
	u8 Flag_BH1750;
	
	BSP_Init();
	
	while(1)
	{
		if(Time_200ms>200)
		{
			Time_200ms=0;
			
			if(Flag_BH1750==0)
			{
				Flag_BH1750=1;
				
				Start_BH1750();//启动BH1750
			}else
			{
				Flag_BH1750=0;
				
				Read_BH1750();//读取BH1750
        Lux=Convert_BH1750();//转换
			}
			
			BMP280_Get_Temperature_Pressure(&Temperature, &Pressure);//读取BMP280
		}
		
		if(Time_1000ms>3000)
		{
			Time_1000ms=0;
			/*******通过串口上传数据*******/
			printf("The PM1.0 is %d ug/m3,The PM2.5 is %d ug/m3,The PM10 is %d ug/m3\r\n",PM1_0,PM2_5,PM10);
			printf("The Temperature is %.2f 'C,The Humidity is %.1f RH\r\n",Temperature,Humi);
			printf("The Pressure is %d Pa\r\n",Pressure);
			printf("The Illumination is %d lx\r\n\r\n",Lux);	
		}
		
		if(Time_3000ms>3000)
		{
			Time_3000ms=0;
			
			Get_Humi(&Humi);//读取AM2320
		}
		
		if(Time_20000ms>20000)
		{
			Time_20000ms=0;
					
				Set_LED2(1);
				ESP8266_SendDate(PM1_0, PM2_5, PM10, Temperature, Humi, Pressure, Lux);//上传数据
				Set_LED2(0);
		}
	}
}






