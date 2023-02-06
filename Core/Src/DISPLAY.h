#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "main.h"
#include "LCD.h"
#include "DS1307.h"
#include "MENU.h"
#include "DHT11.h"

void DISPLAY_Handle(TIME *TIME_DS1307, TIME *TIME_Display, MODE *DISPLAY, OPTION *OPTION_Choose, OPTION *OPTION_Point);
void TIME_DisplayToLCD(TIME *TIME_DS1307, TIME *TIME_Display);
void OPTION_DisplayToLCD(OPTION *OPTION_Point);

void Date_DisplayToLCD(TIME *TIME_DS1307);

void SET_TIME_OptionDisplayToLCD(TIME *TIME_DS1307, TIME *TIME_Display);

#endif
