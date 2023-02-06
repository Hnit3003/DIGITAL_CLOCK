#include "DELAY.h"

//extern TIM_HandleTypeDef htim1;

TIM_HandleTypeDef *DELAY_TIMER; 

void DELAY_Init(TIM_HandleTypeDef *_DELAY_TIMER)
{
	DELAY_TIMER = _DELAY_TIMER;
}

void DELAY_us(uint16_t US_Value)
{
	DELAY_TIMER->Instance->CNT = 0;
	HAL_TIM_Base_Start(DELAY_TIMER);
	while(DELAY_TIMER->Instance->CNT < US_Value);
	HAL_TIM_Base_Stop(DELAY_TIMER);
}
