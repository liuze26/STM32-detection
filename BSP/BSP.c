#include "BSP.h"
#include "stm32f10x.h"
#include "Delay.h"
#include "SYS.h"
#include "USART_1.h" 
#include "USART_2.h" 
#include "USART_3.h" 
#include "BMP280.h" 
#include "R8025AC.h"
#include "AM2320.h"
#include "IIC.h"
#include "LED.h"
#include "ESP8266.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"	 
#include "Timer.h"
#include "KEY.h"
#include "SPI.h"
#include "usmart.h"
#include "string.h"

u16 Lux;
float Temperature,Humi;
s32 Pressure;
u8 Flag_ESP;

void BSP_Init(void)
{
	delay_init();
	IIC_Init();
	uart_init(115200);
	USART2_Init();
	USART3_Init();
	SPI1_Init();
	//R8025AC_Init();
	BMP280_Init();
	KEY_Init();
	LED_Init();
	
	if(Key_Scan())
	{
		USB_Port_Set(0); 	//USB先断开
		delay_ms(700);
		USB_Port_Set(1);	//USB再次连接
		Set_USBClock();   
		USB_Interrupts_Config();    
		USB_Init();
		
		usmart_dev.init(72);//usmart初始化
		
		Set_LED1(1);
		Set_LED2(1);
		Set_LED3(1);
		while(1);
	}
	
	delay_ms(1500);
	delay_ms(1500);
	delay_ms(1500);
	ESP8266_Init();
	
	TIM3_Int_Init(9,7199);
	Set_LED1(1);
}










