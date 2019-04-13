#include "USART_2.h"
#include "SYS.h"

u8 USART2_BUF[32];
u16 PM1_0,PM2_5,PM10;

void USART2_Init(void)  
{  
    GPIO_InitTypeDef GPIO_InitStructure;  
    USART_InitTypeDef USART_InitStructure;  
    NVIC_InitTypeDef NVIC_InitStructure;  
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    /* Configure USART Rx as input floating */  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;  
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
  
    USART_InitStructure.USART_BaudRate = 9600;  
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;  
    USART_InitStructure.USART_StopBits = USART_StopBits_1;  
    USART_InitStructure.USART_Parity = USART_Parity_No;  
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
    USART_InitStructure.USART_Mode = USART_Mode_Rx;  
    USART_Init(USART2, &USART_InitStructure);  
	
	  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
    USART_Cmd(USART2, ENABLE);  
  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
		
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);  
}  
  
void USART2_IRQHandler(void)                	//串口2中断服务程序
{
	static u8 cnt=0;
	u8 Res,i;
	u16 check;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断
	{
		Res =USART_ReceiveData(USART2);	//读取接收到的数据
		if(cnt==0)
		{
			if(Res==0x42)
			{
				USART2_BUF[0]=Res;
				cnt++;
			}		
		}else if(cnt==1)
			  {
				if(Res==0x4D)
				{
					USART2_BUF[1]=Res;
					cnt++;
				}else cnt=0;
			  }else if(cnt>1)
					{
						USART2_BUF[cnt]=Res;
						cnt++;
						if(cnt>=32)
						{
							cnt=0;
							
							for(i=0;i<30;i++)
							{
								check=check+USART2_BUF[i];//计算校验和
							}
							
							if(check==((USART2_BUF[30]<<8)+USART2_BUF[31]))//检查校验和
							{
							  PM1_0=(USART2_BUF[10]<<8)+USART2_BUF[11];
							  PM2_5=(USART2_BUF[12]<<8)+USART2_BUF[13];
							  PM10=(USART2_BUF[14]<<8)+USART2_BUF[15];
							}
						}		
					}		
	} 
} 





