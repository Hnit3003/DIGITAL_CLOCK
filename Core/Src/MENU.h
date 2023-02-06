#ifndef _MENU_H
#define _MENU_H

#include "main.h"
#include "LCD.h"
#include "DS1307.h"
#include "DHT11.h"

typedef enum
{
	NO_CHOOSE,
	SET_TIME,
	TEMP,
	EXIT
}MENU_OPTION;

typedef enum
{
	MAIN_MENU,
	CLOCK_DISPLAY
}DISPLAY_MODE;

typedef struct
{
	MENU_OPTION Current;
	MENU_OPTION Last;
}OPTION;

typedef struct
{
	DISPLAY_MODE Current;
	DISPLAY_MODE Last;
}MODE;

void MENU_Handle(MODE *DISPLAY, OPTION *OPTION_Choose, TIME *TIME_DS1307, TIME *TIME_Display, DHT11_Typedef *_DHT11_Menu);
void OPTION_SetTimeHandle(TIME *TIME_DS1307, TIME *TIME_Display);
void OPTION_TempHandle(DHT11_Typedef *DHT11_Menu);
void OPTION_ExitHandle(MODE *DISPLAY, OPTION *OPTION_Choose);


#endif

