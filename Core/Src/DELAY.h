#ifndef _DELAY_H
#define _DELAY_H

#include "main.h"

//TIM_HandleTypeDef *DELAY_TIMER;
void DELAY_Init(TIM_HandleTypeDef *_DELAY_TIMER);
void DELAY_us(uint16_t VALUE_us);

#endif