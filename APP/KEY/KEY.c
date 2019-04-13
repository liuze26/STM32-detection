#include "KEY.h"
#include "Delay.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}

u8 Key_Scan(void)
{
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==0)
	{
		delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)==0)
		{
			return 1;
		}else return 0;
	} 
	return 0;
}






