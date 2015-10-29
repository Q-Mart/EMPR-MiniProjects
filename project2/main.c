#include "main.h"
#include "delay.h"
#include "lcd.h"
#include "key_pad.h"
#include "calc.h"
#include "serialUSB.h"


void main(){
  serialUSBInit();
  i2c_init();
  lcd_Init();
  delayInit();
  key_pad_init();
  
  lcd_ClearScreen();

  serialUSBWrite("Sniffing bus:\r\n");
  char str[25];
  sprintf(str,"%d devices connected\r\n",i2c_deviceCount());
  serialUSBWrite(str);
  
  delay(3000);

  serialUSBWrite("Printing Hello World\r\n");
  lcd_PrintString("Hello, World!");

  delay(3000);
  serialUSBWrite("Calculator ready\r\n");
  calc_loop();

}
