#include "MENU.h"

void MENU_Handle(MODE *DISPLAY, OPTION *OPTION_Choose, TIME *TIME_DS1307, TIME *TIME_Display, DHT11_Typedef *_DHT11_Menu)
{
	if(DISPLAY->Current == MAIN_MENU)
	{
		switch(OPTION_Choose->Current)
		{
			case SET_TIME:
				OPTION_SetTimeHandle(TIME_DS1307, TIME_Display);
				break;
			
			case TEMP:
				DHT11_Handle();
				OPTION_TempHandle(_DHT11_Menu);
				break;
			
			case EXIT:
				OPTION_ExitHandle(DISPLAY, OPTION_Choose);
				break;
			
			case NO_CHOOSE:
				break;
		}
	}
}

void OPTION_SetTimeHandle(TIME *TIME_DS1307, TIME *TIME_Display)
{
	if(TIME_DS1307->Minute != TIME_Display->Minute)
	{
		LCD_Set_Cursor(1,7);
		LCD_Printf("%02d", TIME_DS1307->Minute);
		TIME_Display->Minute = TIME_DS1307->Minute;
		DS1307_WriteTime(TIME_DS1307);
		if(TIME_DS1307->Hour != TIME_Display->Hour)
		{
			LCD_Set_Cursor(1,4);
			LCD_Printf("%02d", TIME_DS1307->Hour);
			TIME_Display->Hour = TIME_DS1307->Hour;
			DS1307_WriteTime(TIME_DS1307);
		}
	}
}

void OPTION_TempHandle(DHT11_Typedef *DHT11_Menu)
{
	if(DHT11_Menu->TEMP_Data.Current != DHT11_Menu->TEMP_Data.Display)
	{
		LCD_Set_Cursor(0,0);
		LCD_Printf("Temperature: %02d", DHT11_Menu->TEMP_Data.Current);

		DHT11_Menu->TEMP_Data.Display = DHT11_Menu->TEMP_Data.Current;
	}
	
	if(DHT11_Menu->HUMI_Data.Current != DHT11_Menu->HUMI_Data.Display)
	{
		LCD_Set_Cursor(1,0);
		LCD_Printf("Humidity: %02d", DHT11_Menu->HUMI_Data.Current);
		
		DHT11_Menu->HUMI_Data.Display = DHT11_Menu->HUMI_Data.Current;
	}
}

void OPTION_ExitHandle(MODE *DISPLAY, OPTION *OPTION_Choose)
{
	DISPLAY->Current = CLOCK_DISPLAY;
	OPTION_Choose->Current = NO_CHOOSE;
}