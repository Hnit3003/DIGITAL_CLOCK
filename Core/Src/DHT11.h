#ifndef _DHT11_H
#define _DHT11_H

#include "main.h"
#include "LCD.h"
#include "DELAY.h"

typedef enum
{
	INVALID,
	VALID
}RESPONE_Return;

typedef struct
{
	uint16_t Current;
	uint16_t Display;
}TEMPERATURE_Typedef;

typedef struct
{
	uint16_t Current;
	uint16_t Display;
}HUMIDITY_Typedef;

typedef struct
{
	RESPONE_Return RESPON_Signal;
	uint8_t RH_IntegralByte;
	uint8_t RH_DecimalByte;
	uint8_t T_IntegralByte;
	uint8_t T_DecimalByte;
	uint8_t CHECKSUM_Byte;
	TEMPERATURE_Typedef TEMP_Data;
	HUMIDITY_Typedef HUMI_Data;
}DHT11_Typedef;

void DHT11_Handle();
void DHT11_Init(DHT11_Typedef *_DHT11, GPIO_TypeDef *_GPIOx, uint16_t _GPIO_Pin);
void PIN_ChangeMode_INPUT(GPIO_TypeDef *_GPIOx, uint16_t _GPIO_Pin);
void PIN_ChangeMode_OUTPUT(GPIO_TypeDef *_GPIOx, uint16_t _GPIO_Pin);
void START_Signal_Transmit();
void RESPONE_SIGNAL_Check();
uint8_t BYTE_ReadValueReceive();

#endif