#include "Timer.h"

uint16_t Time_200ms,Time_1000ms,Time_3000ms,Time_20000ms;

//通用定时器 3 中断初始化  
//这里时钟选择为 APB1 的 2 倍，而 APB1 为 36M  
//arr：自动重装值。  
//psc：时钟预分频数  
//这里使用的是定时器 3!  
void TIM3_Int_Init(u16 arr,u16 psc)  
{  
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
NVIC_InitTypeDef NVIC_InitStructure;  
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //①时钟 TIM3 使能  
//定时器 TIM3 初始化  
TIM_TimeBaseStructure.TIM_Period = arr; //设置自动重装载寄存器周期的值  
TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置时钟频率除数的预分频值  
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割  
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM 向上计数  
TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  //②初始化 TIM3  
TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );  //③允许更新中断  
//中断优先级 NVIC 设置  
NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3 中断  
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级 0 级  
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级 3 级  
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //IRQ 通道被使能  
NVIC_Init(&NVIC_InitStructure);   //④初始化 NVIC 寄存器  
TIM_Cmd(TIM3, ENABLE);  //⑤使能 TIM3  
	
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
}  

//控制入口
void TIM3_IRQHandler(void)		//1ms中断一次
{
    if( TIM_GetITStatus(TIM3 , TIM_IT_Update) != RESET ) 
    {     
		Time_200ms++;
		Time_1000ms++;
		Time_3000ms++;
		Time_20000ms++;

        TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);   //清除中断标志   
    }
}






