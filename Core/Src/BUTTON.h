#ifndef _BUTTON_H
#define _BUTTON_H

#include "main.h"
#include "MENU.h"

typedef struct
{
	uint8_t Current;
	uint8_t Last;
	uint8_t Pressed;
	uint8_t Is_Press_Short;
	uint8_t Is_Pressed_Long;
	uint32_t Debounce_Counter;
	uint32_t Pressed_Counter;
}BUTTON_Typedef;

void BUTTON_Handle(BUTTON_Typedef *BTN, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, MODE *DISPLAY_MODE, OPTION *OPTION_Choose, OPTION *OPTION_Point);
void BUTTON_Detect(BUTTON_Typedef *BTN, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void PRESSED_SignalHandle(BUTTON_Typedef *BTN, MODE *DISPLAY_MODE, OPTION *OPTION_Choose, OPTION *OPTION_Point);

#endif
