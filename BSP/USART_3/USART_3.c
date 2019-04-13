#include "USART_3.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Delay.h"

u8 USART3_BUF[512];
u16 USART3_RX_STA=0;       //接收状态标记

void USART3_Init(void)
{  
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
      
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //使能GPIOB时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);  //使能USART3时钟
   
    //USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;              //PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //复用推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);                  
    
    //USART1_RX   GPIOA.10初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;              //PB11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);                  
 
    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3; //抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                         //根据指定的参数初始化VIC寄存器
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	
    //USART 初始化设置
    USART_InitStructure.USART_BaudRate = 115200;             //串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;  //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;     //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式
 
    USART_Init(USART3, &USART_InitStructure);               //初始化串口1
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);          //开启串口接受中断
    USART_Cmd(USART3, ENABLE);                              //使能串口1 
}  

void USART3_BUF_Clear(void)
{
	memset(USART3_BUF, 0, sizeof(USART3_BUF));
	USART3_RX_STA=0;	
}

void USART3_Write(uint8_t *Data, uint8_t len)
{
    uint8_t i;
    USART_ClearFlag(USART3, USART_FLAG_TC);
    for(i = 0; i < len; i++)
    {
        USART_SendData(USART3, *Data++);
        while( USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET );
    }
}

void USART3_IRQHandler(void)                	//串口3中断服务程序
{
   if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断
	{
		USART3_BUF[USART3_RX_STA] =USART_ReceiveData(USART3);	//读取接收到的数据
		USART3_RX_STA++;
		if(USART3_RX_STA>512-1)USART3_RX_STA=0;	
	} 
} 

