#ifndef __USART_3_H__
#define __USART_3_H__
#include "stdio.h"	
#include "sys.h" 

extern u8 USART3_BUF[512];
extern u16 USART3_RX_STA;       //接收状态标记

void USART3_Init(void);
void USART3_BUF_Clear(void);
void USART3_Write(uint8_t *Data, uint8_t len);
u8 SendCmd(char* cmd, char* result, int timeOut);


#endif



