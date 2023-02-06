#include "DHT11.h"

DHT11_Typedef *DHT11;
GPIO_TypeDef *GPIOx;
uint16_t GPIO_Pin;


void DHT11_Init(DHT11_Typedef *_DHT11, GPIO_TypeDef *_GPIOx, uint16_t _GPIO_Pin)
{
	DHT11 = _DHT11;
	GPIOx = _GPIOx;
	GPIO_Pin = _GPIO_Pin;
}

void PIN_ChangeMode_INPUT(GPIO_TypeDef *_GPIOx, uint16_t _GPIO_Pin)
{
GPIO_InitTypeDef GPIO_InitStruct_ForIP = {0};
GPIO_InitStruct_ForIP.Mode = GPIO_MODE_INPUT;
GPIO_InitStruct_ForIP.Pin = _GPIO_Pin;
GPIO_InitStruct_ForIP.Pull = GPIO_NOPULL;

HAL_GPIO_Init(_GPIOx, &GPIO_InitStruct_ForIP);
}

void PIN_ChangeMode_OUTPUT(GPIO_TypeDef *_GPIOx, uint16_t _GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct_ForOP = {0};
	GPIO_InitStruct_ForOP.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct_ForOP.Pin = _GPIO_Pin;
	GPIO_InitStruct_ForOP.Speed = GPIO_SPEED_FREQ_LOW;
	
	HAL_GPIO_Init(_GPIOx, &GPIO_InitStruct_ForOP);
}

/*INITIALIZATION
1. Set the pin (data) as output
2. Pull the pin low and wait for 18ms
3. Set the pin as input for receiving the data*/

void START_Signal_Transmit()
{
	PIN_ChangeMode_OUTPUT(GPIOx, GPIO_Pin);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, 0);
	HAL_Delay(18);
	PIN_ChangeMode_INPUT(GPIOx, GPIO_Pin);
}

/*RESPONSE
1. Wait for 40 us
2. Check if the pin is low, than wait for 80 us. This will totally be a delay of 120 us and the pin should be high now
2. Check if the pin is high. If it is, than the response is VALID */

void RESPONE_SIGNAL_Check()
{
	DHT11->RESPON_Signal = INVALID;
	DELAY_us(40);
	if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 0)
	{
		DELAY_us(80);
		if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 1)
		{
			DHT11->RESPON_Signal = VALID;
		}
	}
	while(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 1);
}

uint8_t BYTE_ReadValueReceive()
{
	uint8_t BIT_Receive;
	uint8_t BIT_Numbering;
	
	for(BIT_Numbering = 0; BIT_Numbering < 8; BIT_Numbering++)
	{
		while(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 0);
		DELAY_us(40);
		if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 0)
		{
			BIT_Receive = BIT_Receive & (1<<(7-BIT_Numbering));
		}else
		{
			BIT_Receive = BIT_Receive | (1<<(7-BIT_Numbering));
		}
		while(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == 1);
	}
	return BIT_Receive;
}

void DHT11_Handle()
{
	START_Signal_Transmit();
	RESPONE_SIGNAL_Check();
	DHT11->RH_IntegralByte = BYTE_ReadValueReceive();
	DHT11->RH_DecimalByte = BYTE_ReadValueReceive();
	DHT11->T_IntegralByte = BYTE_ReadValueReceive();
	DHT11->T_DecimalByte = BYTE_ReadValueReceive();
	DHT11->CHECKSUM_Byte = BYTE_ReadValueReceive();
	
	DHT11->TEMP_Data.Current = DHT11->T_IntegralByte;
	DHT11->HUMI_Data.Current = DHT11->RH_IntegralByte;
}
