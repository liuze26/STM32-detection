#ifndef __ESP8266_H__
#define __ESP8266_H__

#include "SYS.h"

#define API_KEY "N=lzAxV7ngKPF7EV0sHNLK0xi2w="
#define Device_ID "4731090"

void ESP8266_AT_Setting(char *cmd, u16 timeout);
void ESP8266_Scan_AP(u16 timeout);
void ESP8266_Connect_AP(char *ssid, char *pwd, u16 timeout);
void ESP8266_Disconnect_AP(u16 timeout);
void ESP8266_SmartConfig(u8 i, u16 timeout);
void ESP8266_Get_Status(u16 timeout);
void ESP8266_Init(void);
void ESP8266_SendDate(u16 PM1, u16 PM25, u16 PM10, float Temp, float Humi, u32 Pressure, u16 Lux);

#endif


