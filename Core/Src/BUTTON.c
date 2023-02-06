#include "BUTTON.h"
void BUTTON_Handle(BUTTON_Typedef *BTN, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, MODE *DISPLAY_MODE, OPTION *OPTION_Choose, OPTION *OPTION_Point)
{
	BUTTON_Detect(BTN, GPIOx, GPIO_Pin);
	PRESSED_SignalHandle(BTN, DISPLAY_MODE, OPTION_Choose, OPTION_Point);
}

void BUTTON_Detect(BUTTON_Typedef *BTN, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	BTN->Current = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
	if(BTN->Current != BTN->Last)
	{
		HAL_Delay(10);
		if(BTN->Current == 0)
		{
			BTN->Pressed_Counter = HAL_GetTick();
			BTN->Pressed = 1;
		}else if(BTN->Current == 1)
		{
			if(HAL_GetTick() - BTN->Pressed_Counter < 3000)
			{
				BTN->Is_Press_Short = 1;
				BTN->Is_Pressed_Long = 0;
			}
			BTN->Pressed= 0;
			BTN->Pressed_Counter = HAL_GetTick();
		}
		BTN->Last = BTN->Current;
	}
	
	if((HAL_GetTick() - BTN->Pressed_Counter >= 3000) && (BTN->Pressed == 1))
	{
		BTN->Is_Pressed_Long = 1;
		BTN->Is_Press_Short = 0;
		BTN->Pressed = 0;
	}
}

void PRESSED_SignalHandle(BUTTON_Typedef *BTN, MODE *DISPLAY_MODE, OPTION *OPTION_Choose, OPTION *OPTION_Point)
{
		if(BTN->Is_Pressed_Long == 1)
		{
			if(DISPLAY_MODE->Current == CLOCK_DISPLAY) DISPLAY_MODE->Current = MAIN_MENU;
			else DISPLAY_MODE->Current++;
			OPTION_Choose->Current = NO_CHOOSE;
			BTN->Is_Pressed_Long = 0;
		}else if(BTN->Is_Press_Short == 1 && DISPLAY_MODE->Current == MAIN_MENU)
		{
			if(OPTION_Choose->Current != NO_CHOOSE) OPTION_Choose->Current = NO_CHOOSE;
			else OPTION_Choose->Current = OPTION_Point->Current;
			BTN->Is_Press_Short = 0;
		}
}
