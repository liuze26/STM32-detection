#ifndef __BMP280_H__
#define __BMP280_H__


#include "stm32f10x.h"
#include "SYS.h"


#define BMP280_CHIP_ID_REG                   (0xD0)  /*Chip ID Register */
#define BMP280_RST_REG                       (0xE0) /*Softreset Register */
#define BMP280_STAT_REG                      (0xF3)  /*Status Register */
#define BMP280_CTRL_MEAS_REG                 (0xF4)  /*Ctrl Measure Register */
#define BMP280_CONFIG_REG                    (0xF5)  /*Configuration Register */
#define BMP280_PRESSURE_MSB_REG              (0xF7)  /*Pressure MSB Register */
#define BMP280_PRESSURE_LSB_REG              (0xF8)  /*Pressure LSB Register */
#define BMP280_PRESSURE_XLSB_REG             (0xF9)  /*Pressure XLSB Register */
#define BMP280_TEMPERATURE_MSB_REG           (0xFA)  /*Temperature MSB Reg */
#define BMP280_TEMPERATURE_LSB_REG           (0xFB)  /*Temperature LSB Reg */
#define BMP280_TEMPERATURE_XLSB_REG          (0xFC)  /*Temperature XLSB Reg */

#define BMP280_CHIP_ID		(0x58)

#define BMP280_DIG_T1_LSB_REG            	 (0x88)
#define BMP280_DIG_T1_MSB_REG            	 (0x89)
#define BMP280_DIG_T2_LSB_REG            	 (0x8A)
#define BMP280_DIG_T2_MSB_REG            	 (0x8B)
#define BMP280_DIG_T3_LSB_REG            	 (0x8C)
#define BMP280_DIG_T3_MSB_REG            	 (0x8D)
#define BMP280_DIG_P1_LSB_REG                (0x8E)
#define BMP280_DIG_P1_MSB_REG                (0x8F)
#define BMP280_DIG_P2_LSB_REG                (0x90)
#define BMP280_DIG_P2_MSB_REG                (0x91)
#define BMP280_DIG_P3_LSB_REG                (0x92)
#define BMP280_DIG_P3_MSB_REG                (0x93)
#define BMP280_DIG_P4_LSB_REG                (0x94)
#define BMP280_DIG_P4_MSB_REG                (0x95)
#define BMP280_DIG_P5_LSB_REG                (0x96)
#define BMP280_DIG_P5_MSB_REG                (0x97)
#define BMP280_DIG_P6_LSB_REG                (0x98)
#define BMP280_DIG_P6_MSB_REG                (0x99)
#define BMP280_DIG_P7_LSB_REG                (0x9A)
#define BMP280_DIG_P7_MSB_REG                (0x9B)
#define BMP280_DIG_P8_LSB_REG                (0x9C)
#define BMP280_DIG_P8_MSB_REG                (0x9D)
#define BMP280_DIG_P9_LSB_REG                (0x9E)
#define BMP280_DIG_P9_MSB_REG                (0x9F)

#define BMP280_SLEEP_MODE                    (0x00)
#define BMP280_FORCED_MODE                   (0x01)
#define BMP280_NORMAL_MODE                   (0x03)
#define BMP280_SOFT_RESET_CODE               (0xB6)

#define BMP280_STANDBY_TIME_1_MS              (0x00)
#define BMP280_STANDBY_TIME_63_MS             (0x01)
#define BMP280_STANDBY_TIME_125_MS            (0x02)
#define BMP280_STANDBY_TIME_250_MS            (0x03)
#define BMP280_STANDBY_TIME_500_MS            (0x04)
#define BMP280_STANDBY_TIME_1000_MS           (0x05)
#define BMP280_STANDBY_TIME_2000_MS           (0x06)
#define BMP280_STANDBY_TIME_4000_MS           (0x07)

#define BMP280_OVERSAMP_SKIPPED          (0x00)
#define BMP280_OVERSAMP_1X               (0x01)
#define BMP280_OVERSAMP_2X               (0x02)
#define BMP280_OVERSAMP_4X               (0x03)
#define BMP280_OVERSAMP_8X               (0x04)
#define BMP280_OVERSAMP_16X              (0x05)

#define BMP280_ULTRA_LOW_POWER_MODE          (0x00)
#define BMP280_LOW_POWER_MODE	             (0x01)
#define BMP280_STANDARD_RESOLUTION_MODE      (0x02)
#define BMP280_HIGH_RESOLUTION_MODE          (0x03)
#define BMP280_ULTRA_HIGH_RESOLUTION_MODE    (0x04)

#define BMP280_FILTER_COEFF_OFF               (0x00)
#define BMP280_FILTER_COEFF_2                 (0x01)
#define BMP280_FILTER_COEFF_4                 (0x02)
#define BMP280_FILTER_COEFF_8                 (0x03)
#define BMP280_FILTER_COEFF_16                (0x04)

#define CS_BMP PCout(14)

extern u16 dig_T1;/**<calibration T1 data*/
extern s16 dig_T2;/**<calibration T2 data*/
extern s16 dig_T3;/**<calibration T3 data*/
extern u16 dig_P1;/**<calibration P1 data*/
extern s16 dig_P2;/**<calibration P2 data*/
extern s16 dig_P3;/**<calibration P3 data*/
extern s16 dig_P4;/**<calibration P4 data*/
extern s16 dig_P5;/**<calibration P5 data*/
extern s16 dig_P6;/**<calibration P6 data*/
extern s16 dig_P7;/**<calibration P7 data*/
extern s16 dig_P8;/**<calibration P8 data*/
extern s16 dig_P9;/**<calibration P9 data*/

extern s32 t_fine;/**<calibration t_fine data*/


void BMP280_Init(void);
void BMP280_read_uncomp_pressure_temperature(s32 *v_uncomp_pressure_s32, s32 *v_uncomp_temperature_s32);
s32 bmp280_compensate_temperature_int32(s32 adc_T);
u32 bmp280_compensate_pressure_int32(s32 adc_P);
void BMP280_Get_Temperature_Pressure(float *temperature, s32 *pressure);

#endif


