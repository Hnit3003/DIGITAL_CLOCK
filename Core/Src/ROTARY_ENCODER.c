#include "ROTARY_ENCODER.h"

void ROTARY_ENCODER_Handle(ROTARY_State *RE_State, MODE *DISPLAY, OPTION *OPTION_Choose, OPTION *OPTION_Point, TIME *TIME_DS1307)
{
	ROTARY_ENCODER_Detect(RE_State);
	ROTARY_SignalHandle(RE_State, DISPLAY, OPTION_Choose, OPTION_Point, TIME_DS1307);
}

void ROTARY_ENCODER_Detect(ROTARY_State *RE_State)
{
	if(HAL_GPIO_ReadPin(GPIOA, CLK_Pin) == 0)
	{
		if(HAL_GPIO_ReadPin(GPIOB, DT_Pin) == 1)
		{
			while(HAL_GPIO_ReadPin(GPIOB, DT_Pin) == 1);
			*RE_State = FOLLOW_CW;
			while(HAL_GPIO_ReadPin(GPIOA, CLK_Pin) == 0);
			while(HAL_GPIO_ReadPin(GPIOB, DT_Pin) == 0);
		}
	}
	else if(HAL_GPIO_ReadPin(GPIOB, DT_Pin) == 0)
	{
		if(HAL_GPIO_ReadPin(GPIOA, CLK_Pin) == 1)
		{
			while(HAL_GPIO_ReadPin(GPIOA, CLK_Pin) == 1);
			*RE_State = ANTI_CW;
			while(HAL_GPIO_ReadPin(GPIOB,DT_Pin) == 0);
			while(HAL_GPIO_ReadPin(GPIOA, CLK_Pin) == 0);
		}
	}
}

void ROTARY_SignalHandle(ROTARY_State *RE_State, MODE *DISPLAY, OPTION *OPTION_Choose, OPTION *OPTION_Point, TIME *TIME_DS1307)
{
	if(*RE_State != STAND)
	{
		switch(*RE_State)
		{
			case FOLLOW_CW:
				ROTARY_FollowCW_Handle(DISPLAY, OPTION_Choose, OPTION_Point, TIME_DS1307);
				break;
			
			case ANTI_CW:
				ROTARY_AntiCW_Handle(DISPLAY, OPTION_Choose, OPTION_Point, TIME_DS1307);
				break;
			
			default:
				break;
		}
		*RE_State = STAND;
	}
}

void ROTARY_FollowCW_Handle(MODE *DISPLAY, OPTION *OPTION_Choose, OPTION *OPTION_Point, TIME *TIME_DS1307)
{
	if((DISPLAY->Current == MAIN_MENU) && (OPTION_Choose->Current == NO_CHOOSE))
	{
		if(OPTION_Point->Current == EXIT) OPTION_Point->Current = SET_TIME;
		else OPTION_Point->Current++;
	}else if((DISPLAY->Current == MAIN_MENU) && (OPTION_Choose->Current != NO_CHOOSE))
	{
		switch(OPTION_Choose->Current)
		{
			case SET_TIME:
				if(TIME_DS1307->Minute == 59)
				{
					TIME_DS1307->Minute = 0;
					TIME_DS1307->Hour++;
				}else
					TIME_DS1307->Minute++;
				break;
				
			default:
				break;
		}
	}
}

void ROTARY_AntiCW_Handle(MODE *DISPLAY, OPTION *OPTION_Choose, OPTION *OPTION_Point, TIME *TIME_DS1307)
{
	if((DISPLAY->Current == MAIN_MENU) && (OPTION_Choose->Current == NO_CHOOSE))
	{
		if(OPTION_Point->Current == SET_TIME) OPTION_Point->Current = EXIT;
		else OPTION_Point->Current--;
	}else if((DISPLAY->Current == MAIN_MENU) && (OPTION_Choose->Current != NO_CHOOSE))
	{
		switch(OPTION_Choose->Current)
		{
			case SET_TIME:
				if(TIME_DS1307->Minute == 0)
				{
					TIME_DS1307->Minute = 59;
					TIME_DS1307->Hour--;
				}else
					TIME_DS1307->Minute--;
				break;
				
			default:
				break;
		}
	}
}