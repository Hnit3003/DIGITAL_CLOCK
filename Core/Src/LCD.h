#ifndef LCD_H
#define LCD_H

#include "main.h"

void LCD_CMD_Transmit(uint8_t CMD);
void LCD_Init();
void LCD_DATA_Transmit(uint8_t DATA);
void LCD_Set_Cursor(uint8_t Row, uint8_t Column);
void LCD_Clear();
void LCD_Write_String(char *string);
void LCD_Printf(const char *String, ...);

#endif
