#ifndef __BSP_H__
#define __BSP_H__

#include "SYS.h"

extern u16 Lux;
extern float Temperature,Humi;
extern s32 Pressure;
extern u8 Flag_ESP;

void BSP_Init(void);

#endif



