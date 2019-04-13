#ifndef __Timer_H__
#define __Timer_H__

#include "SYS.h" 

extern uint16_t Time_200ms,Time_1000ms,Time_3000ms,Time_20000ms;

void TIM3_Int_Init(u16 arr,u16 psc);

#endif

