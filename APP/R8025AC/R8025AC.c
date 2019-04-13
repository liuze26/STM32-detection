#include "R8025AC.h"
#include "USART_3.h"
#include "IIC.h"
#include "SYS.h"

void R8025AC_Set_Time(u8 Year, u8 Month, u8 Day, u8 Week, u8 Hour, u8 Minute, u8 Second)
{
	u8 date[7];
	
	date[6]=Year;
	date[5]=Month;
	date[4]=Day;
	date[3]=Week;
	date[2]=Hour;
	date[1]=Minute;
	date[0]=Second;
	
	IICwriteBytes(R8025AC_Addr, Second_REG, 7, date);
}

u8 R8025AC_Get_Year(void)
{
	return I2C_ReadOneByte(R8025AC_Addr, Year_REG|0x01);
}

u8 R8025AC_Get_Month(void)
{
	return I2C_ReadOneByte(R8025AC_Addr, Month_REG|0x01);
}

u8 R8025AC_Get_Day(void)
{
	return I2C_ReadOneByte(R8025AC_Addr, Day_REG|0x01);
}

u8 R8025AC_Get_Hour(void)
{
	return I2C_ReadOneByte(R8025AC_Addr, Hour_REG|0x01);
}

u8 R8025AC_Get_Minute(void)
{
	return I2C_ReadOneByte(R8025AC_Addr, Minute_REG|0x01);
}

u8 R8025AC_Get_Second(void)
{
	return I2C_ReadOneByte(R8025AC_Addr, Second_REG|0x01);
}


void R8025AC_Init(void)
{
	u8 temp;
	
	temp=I2C_ReadOneByte(R8025AC_Addr, Control2_REG|0x01);
	
	if(temp!=0x2C)
	{
		IIC_writeOneByte(R8025AC_Addr, Control1_REG, 0x33);
		IIC_writeOneByte(R8025AC_Addr, Control2_REG, 0x28);
		R8025AC_Set_Time(0x17, 0x02, 0x01, 0x03, 0x12, 0x00, 0x00);
	}
}



