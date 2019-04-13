#include "ESP8266.h"
#include "USART_3.h"
#include "hw_config.h"
#include "Delay.h"
#include "stdio.h"	
#include <string.h>
#include <stdint.h>

void ESP8266_AT_Setting(char *cmd, u16 timeout)
{
	USART3_BUF_Clear();

    USART3_Write((unsigned char *)cmd, strlen((const char *)cmd));
	
	USART_SendData(USART3, 0X0D);
    while( USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET );//发送回车符
	USART_SendData(USART3, 0X0A);
    while( USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET );//发送回车符
		
	while(timeout>0)
	{
		delay_ms(1);
		timeout--;
	}
	
	usb_printf("\r\n%s",USART3_BUF);//打印出结果
}

void ESP8266_Scan_AP(u16 timeout)
{
	ESP8266_AT_Setting("AT+CWLAP", timeout);//扫描AP
}

void ESP8266_Connect_AP(char *ssid, char *pwd, u16 timeout)
{
	char temp[50];
	
	sprintf(temp, "AT+CWJAP=\"%s\",\"%s\"",ssid,pwd);//连接AP
	
	ESP8266_AT_Setting(temp, timeout);
}

void ESP8266_Disconnect_AP(u16 timeout)
{
	ESP8266_AT_Setting("AT+CWQAP", timeout);//断开AP连接
}

void ESP8266_SmartConfig(u8 i, u16 timeout)
{
    if(i==0)
	{
		ESP8266_AT_Setting("AT+CWSTOPSMART", timeout);//开启
	}
	if(i==1)
	{
		ESP8266_AT_Setting("AT+CWSTARTSMART", timeout);//关闭
	}
}

void ESP8266_Get_Status(u16 timeout)
{
	ESP8266_AT_Setting("AT+CIPSTATUS", timeout);
}

void ESP8266_Init(void)
{
	USART3_Write("AT+CIPMODE=1\r\n", 14);//station模式
	delay_ms(1000);
	USART3_Write("AT+CIPMUX=0\r\n", 13);//单连接
}

void ESP8266_SendDate(u16 PM1, u16 PM25, u16 PM10, float Temp, float Humi, u32 Pressure, u16 Lux)
{
	u8 i;
	
	char HTTP_Buf[200]={0};     //HTTP报文缓存区
	
	char dataBuf[200]={0};
	char lenBuf[3]={0};
	
	USART3_BUF_Clear();//清除缓存
	//USART3_Write("AT+CIPSTART=\"TCP\",\"jjfarfapi.heclouds.com\",80\r\n", 47);//连接服务器
	USART3_Write("AT+CIPSTART=\"TCP\",\"183.230.40.33\",80\r\n", 38);//连接服务器
	/************************************生成HTTP报文*****************************************/
	sprintf(dataBuf, "{\"PM1.0\":%d,\"PM2.5\":%d,\"PM10\":%d,\"Temperature\":%.2f,\"Humidity\":%.1f,\"Pressure\":%d,\"Illumination\":%d}", PM1, PM25, PM10, Temp, Humi, Pressure, Lux);     //采用分割字符串格式
	sprintf(lenBuf, "%d", strlen(dataBuf));
	
	//strcat(HTTP_Buf, "POST /devices/4731090/datapoints?type=3 HTTP/1.1\r\n");
	//strcat(HTTP_Buf, "api-key: N=lzAxV7ngKPF7EV0sHNLK0xi2w=\r\n");
	strcat(HTTP_Buf, "POST /devices/");
	strcat(HTTP_Buf, Device_ID);
	strcat(HTTP_Buf, "/datapoints?type=3 HTTP/1.1\r\n");
	strcat(HTTP_Buf, "api-key: ");
	strcat(HTTP_Buf, API_KEY);
	strcat(HTTP_Buf, "\r\n");
	
	strcat(HTTP_Buf, "Host: api.heclouds.com\r\n");
	strcat(HTTP_Buf, "Connection: close\r\n");
	
	strcat(HTTP_Buf, "Content-Length:");
  strcat(HTTP_Buf, lenBuf);
  strcat(HTTP_Buf, "\r\n\r\n");
	
	for(i=0;i<100;i++)
	{
		delay_ms(100);
		
		if(strstr((const char *)USART3_BUF, "CONNECT")!= NULL)break;
	}
	
	USART3_BUF_Clear();//清除缓存
	USART3_Write("AT+CIPSEND\r\n", 12);//开启透传
	for(i=0;i<150;i++)
	{
		delay_ms(10);
		
		if(strstr((const char *)USART3_BUF, ">")!= NULL)break;
	}
	USART3_BUF_Clear();//清除缓存
	
	USART3_Write((uint8_t *)HTTP_Buf, strlen(HTTP_Buf));//上传数据
	USART3_Write((uint8_t *)dataBuf, strlen(dataBuf));//上传数据
	
	for(i=0;i<50;i++)
	{
		delay_ms(100);
		
		if(strstr((const char *)USART3_BUF, "HTTP/1.1 200 OK")!= NULL)break;
	}
	
	USART3_Write("+++", 3);//退出透传
	delay_ms(1000);
	USART3_Write("AT+CIPCLOSE\r\n", 13);//关闭连接
}





