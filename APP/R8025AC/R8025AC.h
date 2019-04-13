#ifndef __R8025AC_H__
#define __R8025AC_H__

#include "SYS.h"

#define R8025AC_Addr 0x64

#define Second_REG 0x00
#define Minute_REG 0x10
#define Hour_REG 0x20
#define Week_REG 0x30
#define Day_REG 0x40
#define Month_REG 0x50
#define Year_REG 0x60
#define Control1_REG 0xE0 //0x34
#define Control2_REG 0xF0
    
void R8025AC_Set_Time(u8 Year, u8 Month, u8 Day, u8 Week, u8 Hour, u8 Minute, u8 Second);
u8 R8025AC_Get_Year(void);
u8 R8025AC_Get_Month(void);
u8 R8025AC_Get_Day(void);
u8 R8025AC_Get_Hour(void);
u8 R8025AC_Get_Minute(void);
u8 R8025AC_Get_Second(void);
void R8025AC_Init(void);

#endif

