#include "i2c_helper.h"
#define ADDR 59
#define SEND_COMMAND 0x00
#define SELECT_DDRAM 0X80
#define SELECT_CGRAM 0X40
#define CLEAR_CHARACTER 0XA0
#define SCREEN_OFF 0X8
#define SCREEN_ON 0XC
#define CHARACTER_SHIFT 128
void lcd_Init();
void lcd_PrintChar(char c, int loc);
void lcd_PrintString(char *str);
void lcd_ClearScreen();
void lcd_SendData(uint8_t * buffer, int buffer_length);
int lcd_IsReady();
