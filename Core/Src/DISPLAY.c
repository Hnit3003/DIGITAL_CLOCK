#include "DISPLAY.h"

DHT11_Typedef *DHT11_Display;

void DISPLAY_Handle(TIME *TIME_DS1307, TIME *TIME_Display, MODE *DISPLAY, OPTION *OPTION_Choose, OPTION *OPTION_Point)
{
	switch(DISPLAY->Current)
	{
		case CLOCK_DISPLAY:
			DS1307_ReadTime(TIME_DS1307);
			if(DISPLAY->Current != DISPLAY->Last)
			{
				LCD_Clear();
				LCD_Set_Cursor(0,4);
				LCD_Printf("%02d:%02d:%02d", TIME_DS1307->Hour, TIME_DS1307->Minute, TIME_DS1307->Second);
				LCD_Set_Cursor(1,1);
				Date_DisplayToLCD(TIME_DS1307);
				DISPLAY->Last = DISPLAY->Current;
			}else TIME_DisplayToLCD(TIME_DS1307, TIME_Display);
			break;
		
		case MAIN_MENU:
			if(OPTION_Choose->Current == NO_CHOOSE)
			{
				if((DISPLAY->Current != DISPLAY->Last) || (OPTION_Choose->Current != OPTION_Choose->Last))
				{
					LCD_Clear();
					LCD_Set_Cursor(0,1);
					LCD_Printf("OPTION %02d:", OPTION_Point->Current);
					OPTION_DisplayToLCD(OPTION_Point);
					DISPLAY->Last = DISPLAY->Current;
					OPTION_Choose->Last = OPTION_Choose->Current;
				}
				
				if(OPTION_Point->Current != OPTION_Point->Last)
				{
					OPTION_DisplayToLCD(OPTION_Point);
					OPTION_Point->Last = OPTION_Point->Current;
				}
			}else if(OPTION_Choose->Current != NO_CHOOSE)
			{
					switch(OPTION_Choose->Current)
					{
						case SET_TIME:
							if(OPTION_Choose->Current != OPTION_Choose->Last)
							{
								LCD_Clear();
								LCD_Set_Cursor(0,1);
								LCD_Write_String("CHANGING TIME:");
								LCD_Set_Cursor(1,4);
								LCD_Printf("%02d:%02d:%02d", TIME_DS1307->Hour, TIME_DS1307->Minute, TIME_DS1307->Second);
								OPTION_Choose->Last = OPTION_Choose->Current;
							}else
							{
								SET_TIME_OptionDisplayToLCD(TIME_DS1307, TIME_Display);
							}
							break;
						
						case TEMP:
							if(OPTION_Choose->Current != OPTION_Choose->Last)
							{
								LCD_Clear();
								LCD_Set_Cursor(0,0);
								LCD_Printf("Temperature: %02d", DHT11_Display->TEMP_Data.Current);
								LCD_Set_Cursor(1,0);
								LCD_Printf("Humidity: %02d", DHT11_Display->HUMI_Data.Current);
								OPTION_Choose->Last = OPTION_Choose->Current;
							}else
							break;
						
						case EXIT:
							break;
						
						default:
							break;
				}
			}
			break;
	}
}

void TIME_DisplayToLCD(TIME *TIME_DS1307, TIME *TIME_Display)
{
	if(TIME_DS1307->Second != TIME_Display->Second)
	{
		LCD_Set_Cursor(0,10);
		LCD_Printf("%02d", TIME_DS1307->Second);
		TIME_Display->Second = TIME_DS1307->Second;
		
		if(TIME_DS1307->Minute != TIME_Display->Minute)
		{
			LCD_Set_Cursor(0,7);
			LCD_Printf("%02d", TIME_DS1307->Minute);
			TIME_Display->Minute = TIME_DS1307->Minute;
		
			if(TIME_DS1307->Hour != TIME_Display->Hour)
			{
				LCD_Set_Cursor(0,4);
				LCD_Printf("%02d", TIME_DS1307->Hour);
				TIME_Display->Hour = TIME_DS1307->Hour;
			
				if(TIME_DS1307->Date != TIME_Display->Date)
				{
					LCD_Set_Cursor(1,1);
					Date_DisplayToLCD(TIME_DS1307);
					TIME_Display->Date = TIME_DS1307->Date;
					TIME_Display->Day = TIME_DS1307->Day;
					TIME_Display->Month = TIME_DS1307->Month;
					TIME_Display->Year = TIME_DS1307->Year;
				}
			}
		}
		DS1307_WriteTime(TIME_DS1307);
	}
}

void Date_DisplayToLCD(TIME *TIME_DS1307)
{
	switch(TIME_DS1307->Date)
	{
		case 1:
			LCD_Printf("Mon-%02d/%02d/20%02d", TIME_DS1307->Day, TIME_DS1307->Month, TIME_DS1307->Year);
			break;

		case 2:
			LCD_Printf("Tue-%02d/%02d/20%02d", TIME_DS1307->Day, TIME_DS1307->Month, TIME_DS1307->Year);
			break;

		case 3:
			LCD_Printf("Wed-%02d/%02d/20%02d", TIME_DS1307->Day, TIME_DS1307->Month, TIME_DS1307->Year);
			break;
		
		case 4:
			LCD_Printf("Thu-%02d/%02d/20%02d", TIME_DS1307->Day, TIME_DS1307->Month, TIME_DS1307->Year);
			break;

		case 5:
			LCD_Printf("Fri-%02d/%02d/20%02d", TIME_DS1307->Day, TIME_DS1307->Month, TIME_DS1307->Year);
			break;

		case 6:
			LCD_Printf("Sat-%02d/%02d/20%02d", TIME_DS1307->Day, TIME_DS1307->Month, TIME_DS1307->Year);
			break;

	case 7:
			LCD_Printf("Sun-%02d/%02d/20%02d", TIME_DS1307->Day, TIME_DS1307->Month, TIME_DS1307->Year);
			break;

	default:
		break;
	}
}

void OPTION_DisplayToLCD(OPTION *OPTION_Point)
{
	switch(OPTION_Point->Current)
	{
		case SET_TIME:
			LCD_Set_Cursor(1, 0);
			LCD_Write_String("                ");
			LCD_Set_Cursor(1, 0);
			LCD_Write_String(">Set time");
			LCD_Set_Cursor(0,8);
			LCD_Printf("%02d", OPTION_Point->Current);
			break;
		
		case TEMP:
			LCD_Set_Cursor(1, 0);
			LCD_Write_String("                ");
			LCD_Set_Cursor(1, 0);
			LCD_Write_String(">Temperature");
			LCD_Set_Cursor(0,8);
			LCD_Printf("%02d", OPTION_Point->Current);
			break;
		
		case EXIT:
			LCD_Set_Cursor(1, 0);
			LCD_Write_String("                ");
			LCD_Set_Cursor(1, 0);
			LCD_Write_String(">Exit menu");
			LCD_Set_Cursor(0,8);
			LCD_Printf("%02d", OPTION_Point->Current);
			break;
		
		default:
			break;
	}
}

void SET_TIME_OptionDisplayToLCD(TIME *TIME_DS1307, TIME *TIME_Display)
{

}