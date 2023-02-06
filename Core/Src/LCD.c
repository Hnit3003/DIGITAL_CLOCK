#include "LCD.h"
#include "string.h"
#include "stdarg.h"
#include "stdio.h"

#define LCD_COLUMN 16
#define LCD_ROW 2

void LCD_CMD_Transmit(uint8_t CMD)
{
	//RS=0: Receive command
	HAL_GPIO_WritePin(GPIOB, RS_Pin, 0);

	//Transmit the first 4 bit(CMD>>4 -> [D7][D6][D5][D4])
	HAL_GPIO_WritePin(GPIOA, D4_Pin, (CMD>>4) & 0x01);
	HAL_GPIO_WritePin(GPIOA, D5_Pin, (CMD>>4) & 0x02);
	HAL_GPIO_WritePin(GPIOA, D6_Pin, (CMD>>4) & 0x04);
	HAL_GPIO_WritePin(GPIOA, D7_Pin, (CMD>>4) & 0x08);
	//Generate EN_Pin pulse
	HAL_GPIO_WritePin(GPIOB, EN_Pin, 1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, EN_Pin, 0);

	//Transmit the last 4 bit(CMD -> -> [D7][D6][D5][D4])
	HAL_GPIO_WritePin(GPIOA, D4_Pin, CMD & 0x01);
	HAL_GPIO_WritePin(GPIOA, D5_Pin, CMD & 0x02);
	HAL_GPIO_WritePin(GPIOA, D6_Pin, CMD & 0x04);
	HAL_GPIO_WritePin(GPIOA, D7_Pin, CMD & 0x08);
	//Generate EN_Pin pulse
	HAL_GPIO_WritePin(GPIOB, EN_Pin, 1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, EN_Pin, 0);
}

void LCD_Init()
{
	//Power On and wait for more than 15ms after Vcc rise to 4.5V, wait for more than 40ms after Vcc rise to 2.7V
	HAL_Delay(50);
	//Special case of "Function set" (lower four bits are irrelevant) (0011 ****)
	LCD_CMD_Transmit(0x03);
	//Wait for more than 4.1ms
	HAL_Delay(5);
	//Special case of "Function set" (lower four bits are irrelevant) (0011 ****)
	LCD_CMD_Transmit(0x03);
	//Wait for more than 100us
	HAL_Delay(1);	
	//Special case of "Function set" (lower four bits are irrelevant) (0011 ****)
	LCD_CMD_Transmit(0x03);
	//Wait for more than 100us
	HAL_Delay(1);
	//Initial "Function Set" to change interface (lower four bit are irrelevant) (0010 ****)
	LCD_CMD_Transmit(0x02);
	//Wait for 100us
	HAL_Delay(1);

	//Function Set (001[DL] [N][F][*][*]): 4 bit(DL=0), 2 lines(N=1), font=5x8 dots(F=0(N=1))
	LCD_CMD_Transmit(0x20 | 0x00 | 0x08 | 0x00);
	//Wait for more than 53us or until busy flag is clear
	HAL_Delay(1);
	
	//Display ON/OFF (0000 1[D][C][B]): display off(D=0), display cursor off(C=0), character blink off(B=0)
	LCD_CMD_Transmit(0x08 | 0x00 | 0x00 | 0x00);
	//Wait for more than 53us or until busy flag is clear
	HAL_Delay(1);
	
	//Clear Display (0000 0001): clears all display and returns cursor to the home position(Address 0)
	LCD_CMD_Transmit(0x01);
	//Wait for more than 3ms or until busy flag is clear
	HAL_Delay(3);
	
	//Entry Mode Set (0000 01[I/D][S]: increment(I/D=1), display stand(S=0)
	LCD_CMD_Transmit(0x04 | 0x02 | 0x00);
	//Wait for more than 53us or until busy flag is clear
	HAL_Delay(1);

	//Display ON/OFF (0000 1[D][C][B]): display on(D=1), display cursor off(C=0), character blink off(B=0)
	LCD_CMD_Transmit(0x08 | 0x04 | 0x00 | 0x00);
	//Wait for more than 53us or until busy flag is clear
	HAL_Delay(1);
	
//	//Cursor and Display Shift (0001 [S/R][R/L][*][*]: Shift cursor to the right (S/R=0, R/L=1)(Address Counter is incremented by 1)
//	LCD_CMD_Transmit(0x01 | 0x00 | 0x04);

	//Return Home (0000 001[*]): returns the cursor to the home position (Address 0), returns display to its original state if it was shifted
	LCD_CMD_Transmit(0x02);
}

void LCD_DATA_Transmit(uint8_t DATA)
{
	//RS=1: Receive data
	HAL_GPIO_WritePin(GPIOB, RS_Pin, 1);

	//Transmit the first 4 bit(CMD>>4)
	HAL_GPIO_WritePin(GPIOA, D4_Pin, (DATA>>4) & 0x01);
	HAL_GPIO_WritePin(GPIOA, D5_Pin, (DATA>>4) & 0x02);
	HAL_GPIO_WritePin(GPIOA, D6_Pin, (DATA>>4) & 0x04);
	HAL_GPIO_WritePin(GPIOA, D7_Pin, (DATA>>4) & 0x08);
	//Generate EN_Pin pulse
	HAL_GPIO_WritePin(GPIOB, EN_Pin, 1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, EN_Pin, 0);

	//Transmit the last 4 bit(CMD)
	HAL_GPIO_WritePin(GPIOA, D4_Pin, DATA & 0x01);
	HAL_GPIO_WritePin(GPIOA, D5_Pin, DATA & 0x02);
	HAL_GPIO_WritePin(GPIOA, D6_Pin, DATA & 0x04);
	HAL_GPIO_WritePin(GPIOA, D7_Pin, DATA & 0x08);
	//Generate EN_Pin pulse
	HAL_GPIO_WritePin(GPIOB, EN_Pin, 1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, EN_Pin, 0);
}

void LCD_Set_Cursor(uint8_t Row, uint8_t Column)
{
	if(Column<LCD_COLUMN && Row<LCD_ROW)
	{
		uint8_t ADDR=0;
		switch (Row){
			case 0:
				ADDR = 0x80 + Column;
				break;
			case 1:
				ADDR = 0xC0 + Column;
				break;
			default:
				break;
		}
		LCD_CMD_Transmit(ADDR);
	}
}

void LCD_Clear()
{
	//Clear Display (0000 0001): clears all display and returns cursor to the home position(Address 0)
	LCD_CMD_Transmit(0x01);
}

void LCD_Write_String(char *string)
{
	for(uint8_t i=0; i<strlen(string); i++)
	{
		LCD_DATA_Transmit(string[i]);
	}
}

void LCD_Printf(const char *String, ...)
{
	char StringArray[16];
	va_list args;
	va_start(args, String);
	vsprintf(StringArray, String, args);
	va_end(args);
	
	for(uint8_t i=0; i<strlen(StringArray) && i<LCD_COLUMN; i++)
	{
		LCD_DATA_Transmit((uint8_t)StringArray[i]);
	}
}