#include "DS1307.h"

//extern I2C_HandleTypeDef hi2c2;

I2C_HandleTypeDef *DS1307_I2C;

void DS1307_Init(I2C_HandleTypeDef *_DS1307_I2C)
{
	DS1307_I2C = _DS1307_I2C;
}

void TIME_Init(TIME *TimeInit, uint8_t SECOND, uint8_t MINUTE, uint8_t HOUR, uint8_t DAY, uint8_t DATE, uint8_t MONTH, uint8_t YEAR)
{
	TimeInit->Second = SECOND;
	TimeInit->Minute = MINUTE;
	TimeInit->Hour = HOUR;
	TimeInit->Day = DAY;
	TimeInit->Date = DATE;
	TimeInit->Month = MONTH;
	TimeInit->Year = YEAR;
}

uint8_t DEC_TO_BCD(uint8_t DEC)
{
	return ((DEC/10)<<4) | (DEC%10);
}

uint8_t BCD_TO_DEC(uint8_t BCD)
{
	return ((BCD>>4)*10) + (BCD&0x0F);
}

void DS1307_WriteTime(TIME *TIME_Set)
{
	uint8_t TIME_Transmit[8];
	TIME_Transmit[0] = SECOND_ADDR;
	TIME_Transmit[1] = DEC_TO_BCD(TIME_Set->Second);
	TIME_Transmit[2] = DEC_TO_BCD(TIME_Set->Minute);
	TIME_Transmit[3] = DEC_TO_BCD(TIME_Set->Hour);
	TIME_Transmit[4] = DEC_TO_BCD(TIME_Set->Day);
	TIME_Transmit[5] = DEC_TO_BCD(TIME_Set->Date);
	TIME_Transmit[6] = DEC_TO_BCD(TIME_Set->Month);
	TIME_Transmit[7] = DEC_TO_BCD(TIME_Set->Year);
	
	/*Transmit TIME_Transmit[8]'s data(include first address of Timkeeper Register: 00h-SECONDS and timeset's data), 
	The first byte is 7 bits of DS1307_ADDR<<1 with R/W bit: Write(R/W=0)*/
	HAL_I2C_Master_Transmit(DS1307_I2C, DS1307_ADDR<<1, TIME_Transmit, 8, 100);
}

void DS1307_ReadTime(TIME *TIME_Read)
{
	uint8_t TIME_Receive[7];
	uint8_t SecondAddress = SECOND_ADDR;
	/*Transmit first 7 bits of DS1307_ADDR<<1 with R/W bit: Write(R/W=0)
	Then transmit the first address of Timkeeper Register: 00h-SECONDS*/
	HAL_I2C_Master_Transmit(DS1307_I2C, DS1307_ADDR<<1, &SecondAddress, 1, 100);
	//Read the value of Timekeeper Rigister, 6 bytes from 00h to 06D-h(SECONMINUTE-HOUR-DATE-DAY-MONTH-YEAR)
	HAL_I2C_Master_Receive(DS1307_I2C, DS1307_ADDR<<1, TIME_Receive, 7, 100);
	
	TIME_Read->Second = BCD_TO_DEC(TIME_Receive[0]);
	TIME_Read->Minute = BCD_TO_DEC(TIME_Receive[1]);
	TIME_Read->Hour = BCD_TO_DEC(TIME_Receive[2]);
	TIME_Read->Day = BCD_TO_DEC(TIME_Receive[3]);
	TIME_Read->Date = BCD_TO_DEC(TIME_Receive[4]);
	TIME_Read->Month = BCD_TO_DEC(TIME_Receive[5]);
	TIME_Read->Year = BCD_TO_DEC(TIME_Receive[6]);
}
