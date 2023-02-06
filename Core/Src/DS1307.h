#ifndef DS1307_H
#define DS1307_H

#include "main.h"

#define DS1307_ADDR 0x68
#define SECOND_ADDR 0x00
#define MINUTE_ADDR 0x01
#define HOUR_ADDR 0x02
#define DAY_ADDR 0x03
#define DATE_ADDR 0x04
#define MONTH_ADDR 0x05
#define YEAR_ADDR 0x06

typedef struct
{
	uint8_t Second;
	uint8_t Minute;
	uint8_t Hour;
	uint8_t Day;
	uint8_t Date;
	uint8_t Month;
	uint8_t Year;
}TIME;

uint8_t DEC_TO_BCD(uint8_t DEC);
uint8_t BCD_TO_DEC(uint8_t BCD);

void DS1307_Init(I2C_HandleTypeDef *_DS1307_I2C);
void TIME_Init(TIME *TimeInit, uint8_t SECOND, uint8_t MINUTE, uint8_t HOUR, uint8_t DAY, uint8_t DATE, uint8_t MONTH, uint8_t YEAR);
void DS1307_WriteTime(TIME *TIME_Set);
void DS1307_ReadTime(TIME *TIME_Read);

#endif
