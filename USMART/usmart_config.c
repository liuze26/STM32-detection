#include "usmart.h"
#include "usmart_str.h"
////////////////////////////用户配置区///////////////////////////////////////////////
//这下面要包含所用到的函数所申明的头文件(用户自己添加) 		
#include "SYS.h"
#include "IIC.h"
#include "ESP8266.h"
#include "R8025AC.h"

extern void led_set(u8 sta);
extern void test_fun(void(*ledset)(u8),u8 sta); 
//函数名列表初始化(用户自己添加)
//用户直接在这里输入要执行的函数名及其查找串
struct _m_usmart_nametab usmart_nametab[]=
{ 	
	(void*)I2C_ReadOneByte,"unsigned char I2C_ReadOneByte(unsigned char I2C_Addr,unsigned char addr)",
	(void*)IIC_writeOneByte,"void IIC_writeOneByte(unsigned char dev, unsigned char reg, unsigned char data)",
	
	(void*)ESP8266_AT_Setting,"ESP8266_AT_Setting(char *cmd, u16 timeout)",
	(void*)ESP8266_Scan_AP,"ESP8266_Scan_AP(u16 timeout)",
	(void*)ESP8266_Connect_AP,"ESP8266_Connect_AP(char *ssid, char *pwd, u16 timeout)",
	(void*)ESP8266_Disconnect_AP,"ESP8266_Disconnect_AP(u16 timeout)",
	(void*)ESP8266_SmartConfig,"ESP8266_SmartConfig(u8 i, u16 timeout)",
	(void*)ESP8266_Get_Status,"ESP8266_Get_Status(u16 timeout)",
	
	(void*)R8025AC_Set_Time,"void R8025AC_Set_Time(u8 Year, u8 Month, u8 Day, u8 Week, u8 Hour, u8 Minute, u8 Second)",
};						  
///////////////////////////////////END///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//函数控制管理器初始化
//得到各个受控函数的名字
//得到函数总数量
struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//函数数量
	0,	  	//参数数量
	0,	 	//函数ID
	1,		//参数显示类型,0,10进制;1,16进制
	0,		//参数类型.bitx:,0,数字;1,字符串	    
	0,	  	//每个参数的长度暂存表,需要MAX_PARM个0初始化
	0,		//函数的参数,需要PARM_LEN个0初始化
};   

