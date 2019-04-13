#include "BMP280.h"
#include "SPI.h"

u16 dig_T1;/**<calibration T1 data*/
s16 dig_T2;/**<calibration T2 data*/
s16 dig_T3;/**<calibration T3 data*/
u16 dig_P1;/**<calibration P1 data*/
s16 dig_P2;/**<calibration P2 data*/
s16 dig_P3;/**<calibration P3 data*/
s16 dig_P4;/**<calibration P4 data*/
s16 dig_P5;/**<calibration P5 data*/
s16 dig_P6;/**<calibration P6 data*/
s16 dig_P7;/**<calibration P7 data*/
s16 dig_P8;/**<calibration P8 data*/
s16 dig_P9;/**<calibration P9 data*/

s32 t_fine;/**<calibration t_fine data*/

void BMP280_Write(u8 RegAddr, u8 date)
{
	CS_BMP=0;	
	SPI1_ReadWriteByte(RegAddr&0x7F);
	SPI1_ReadWriteByte(date);
	CS_BMP=1;
}

u8 BMP280_ReadOne(u8 RegAddr)
{
	u8 date;
	
	CS_BMP=0;	
	SPI1_ReadWriteByte(RegAddr|0x80);
	date=SPI1_ReadWriteByte(0x00);
	CS_BMP=1;
	
	return date;
}

void BMP280_Get_Calib(void)
{ 
	u8 MSB, LSB;
	
	MSB=BMP280_ReadOne(BMP280_DIG_T1_MSB_REG); LSB=BMP280_ReadOne(BMP280_DIG_T1_LSB_REG);
	dig_T1=(MSB<<8)|LSB;
	MSB=BMP280_ReadOne(BMP280_DIG_T2_MSB_REG); LSB=BMP280_ReadOne(BMP280_DIG_T2_LSB_REG);
	dig_T2=(MSB<<8)|LSB;
	MSB=BMP280_ReadOne(BMP280_DIG_T3_MSB_REG); LSB=BMP280_ReadOne(BMP280_DIG_T3_LSB_REG);
	dig_T3=(MSB<<8)|LSB;
	MSB=BMP280_ReadOne(BMP280_DIG_P1_MSB_REG); LSB=BMP280_ReadOne(BMP280_DIG_P1_LSB_REG);
	dig_P1=(MSB<<8)|LSB;
	MSB=BMP280_ReadOne(BMP280_DIG_P2_MSB_REG); LSB=BMP280_ReadOne(BMP280_DIG_P2_LSB_REG);
	dig_P2=(MSB<<8)|LSB;
	MSB=BMP280_ReadOne(BMP280_DIG_P3_MSB_REG); LSB=BMP280_ReadOne(BMP280_DIG_P3_LSB_REG);
	dig_P3=(MSB<<8)|LSB;
	MSB=BMP280_ReadOne(BMP280_DIG_P4_MSB_REG); LSB=BMP280_ReadOne(BMP280_DIG_P4_LSB_REG);
	dig_P4=(MSB<<8)|LSB;
	MSB=BMP280_ReadOne(BMP280_DIG_P5_MSB_REG); LSB=BMP280_ReadOne(BMP280_DIG_P5_LSB_REG);
	dig_P5=(MSB<<8)|LSB;
	MSB=BMP280_ReadOne(BMP280_DIG_P6_MSB_REG); LSB=BMP280_ReadOne(BMP280_DIG_P6_LSB_REG);
	dig_P6=(MSB<<8)|LSB;
	MSB=BMP280_ReadOne(BMP280_DIG_P7_MSB_REG); LSB=BMP280_ReadOne(BMP280_DIG_P7_LSB_REG);
	dig_P7=(MSB<<8)|LSB;
	MSB=BMP280_ReadOne(BMP280_DIG_P8_MSB_REG); LSB=BMP280_ReadOne(BMP280_DIG_P8_LSB_REG);
	dig_P8=(MSB<<8)|LSB;
	MSB=BMP280_ReadOne(BMP280_DIG_P9_MSB_REG); LSB=BMP280_ReadOne(BMP280_DIG_P9_LSB_REG);
	dig_P9=(MSB<<8)|LSB;
}

void BMP280_Set_ctrl_meas(u8 osrs_t, u8 osrs_p, u8 mode)
{
	u8 Temp;	
	Temp=(osrs_t<<5)|(osrs_p<<2)|mode;
	
	BMP280_Write(BMP280_CTRL_MEAS_REG, Temp);	
} 

void BMP280_Set_config(u8 t_sb, u8 filter)
{
	u8 Temp;	
	Temp=(t_sb<<5)|(filter<<2);
	
	BMP280_Write(BMP280_CONFIG_REG, Temp);
}

void BMP280_read_uncomp_pressure_temperature(s32 *v_uncomp_pressure_s32, s32 *v_uncomp_temperature_s32)
{
	u8 PRESSURE_MSB, PRESSURE_LSB, PRESSURE_XLSB;
	u8 TEMPERATURE_MSB, TEMPERATURE_LSB, TEMPERATURE_XLSB;
	
	PRESSURE_MSB=BMP280_ReadOne(BMP280_PRESSURE_MSB_REG);
	PRESSURE_LSB=BMP280_ReadOne(BMP280_PRESSURE_LSB_REG);
	PRESSURE_XLSB=BMP280_ReadOne(BMP280_PRESSURE_XLSB_REG);
	
	TEMPERATURE_MSB=BMP280_ReadOne(BMP280_TEMPERATURE_MSB_REG);
	TEMPERATURE_LSB=BMP280_ReadOne(BMP280_TEMPERATURE_LSB_REG);
	TEMPERATURE_XLSB=BMP280_ReadOne(BMP280_TEMPERATURE_XLSB_REG);
	
	*v_uncomp_pressure_s32=(PRESSURE_MSB<<12)|(PRESSURE_LSB<<4)|(PRESSURE_XLSB>>4);
	*v_uncomp_temperature_s32=(TEMPERATURE_MSB<<12)|(TEMPERATURE_LSB<<4)|(TEMPERATURE_XLSB>>4);	
}

void BMP280_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );	 //PORTA时钟使能 

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_14);
	
	SPI1_SetSpeed(SPI_BaudRatePrescaler_2);
	CS_BMP=1;
	
	BMP280_Get_Calib();
	BMP280_Set_ctrl_meas(BMP280_OVERSAMP_16X, BMP280_OVERSAMP_16X, BMP280_NORMAL_MODE);
	BMP280_Set_config(BMP280_STANDBY_TIME_250_MS, BMP280_FILTER_COEFF_16);
}

s32 bmp280_compensate_temperature_int32(s32 adc_T)
{
	s32 v_x1_u32r = 0;
	s32 v_x2_u32r = 0;
	s32 temperature = 0;
	/* calculate true temperature*/
	/*calculate x1*/
	v_x1_u32r = ((((adc_T>> 3) - ((s32)dig_T1<< 1))) * ((s32)dig_T2))>> 11;
	/*calculate x2*/
	v_x2_u32r = (((((adc_T>> 4) - ((s32)dig_T1)) * ((adc_T>> 4)- ((s32)dig_T1)))>> 12) * ((s32)dig_T3))>> 14;
	/*calculate t_fine*/
	t_fine = v_x1_u32r + v_x2_u32r;
	/*calculate temperature*/
	temperature = (t_fine * 5 + 128)>> 8;

	return temperature;
}

u32 bmp280_compensate_pressure_int32(s32 adc_P)
{
	s32 v_x1_u32r = 0;
	s32 v_x2_u32r = 0;
	u32 v_pressure_u32 = 0;
	/* calculate x1*/
	v_x1_u32r = (((s32)t_fine)>> 1) - (s32)64000;
	/* calculate x2*/
	v_x2_u32r = (((v_x1_u32r >> 2) * (v_x1_u32r >> 2))>> 11) * ((s32)dig_P6);
	v_x2_u32r = v_x2_u32r + ((v_x1_u32r *((s32)dig_P5))<< 1);
	v_x2_u32r = (v_x2_u32r >> 1) + (((s32)dig_P4)<< 16);
	/* calculate x1*/
	v_x1_u32r = (((dig_P3 * (((v_x1_u32r>> 2) * (v_x1_u32r>> 2))>> 13))>> 3) + ((((s32)dig_P2)* v_x1_u32r)>> 1))>> 18;
	v_x1_u32r = ((((32768 + v_x1_u32r))* ((s32)dig_P1))>> 15);
	/* calculate pressure*/
	v_pressure_u32 = (((u32)(((s32)1048576) - adc_P) - (v_x2_u32r >> 12))) * 3125;
	/* check overflow*/
	if (v_pressure_u32 < 0x80000000)
		/* Avoid exception caused by division by zero */
		if (v_x1_u32r != 0)
			v_pressure_u32 = (v_pressure_u32<< 1)/ ((u32)v_x1_u32r);
		else
			return 0;
	else
	/* Avoid exception caused by division by zero */
	if (v_x1_u32r != 0)
		v_pressure_u32 = (v_pressure_u32 / (u32)v_x1_u32r) * 2;
	else
		return 0;
	/* calculate x1*/
	v_x1_u32r = (((s32)dig_P9) * ((s32)(((v_pressure_u32>> 3) * (v_pressure_u32>> 3))>> 13)))>> 12;
	/* calculate x2*/
	v_x2_u32r = (((s32)(v_pressure_u32 >>2)) * ((s32)dig_P8))>> 13;
	/* calculate true pressure*/
	v_pressure_u32 = (u32)((s32)v_pressure_u32 + ((v_x1_u32r + v_x2_u32r+ dig_P7)>> 4));

	return v_pressure_u32;
}

void BMP280_Get_Temperature_Pressure(float *temperature, s32 *pressure)
{
	s32 v_uncomp_pressure_s32, v_uncomp_temperature_s32;
	s32 T;
	u32 P;
		
	BMP280_read_uncomp_pressure_temperature(&v_uncomp_pressure_s32, &v_uncomp_temperature_s32);
	T=bmp280_compensate_temperature_int32(v_uncomp_temperature_s32);
	P=bmp280_compensate_pressure_int32(v_uncomp_pressure_s32);
	
	*temperature=(float)T/100;
	*pressure=P;	
}


