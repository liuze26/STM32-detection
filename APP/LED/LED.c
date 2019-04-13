#include "LED.h"

void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB| RCC_APB2Periph_AFIO,ENABLE);
 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); //禁止JTAG功能
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);
}

void Set_LED1(u8 n)
{
	if(n)GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	else GPIO_SetBits(GPIOB,GPIO_Pin_3);
}

void Set_LED2(u8 n)
{
	if(n)GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	else GPIO_SetBits(GPIOB,GPIO_Pin_4);
}
void Set_LED3(u8 n)
{
	if(n)GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	else GPIO_SetBits(GPIOB,GPIO_Pin_5);
}


