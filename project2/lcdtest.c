#include "main.h"
#include "delay.h"
#include "lcd.h"
#include <stdio.h>


void main(){
  serialUSBInit();
  i2c_init();
  lcd_Init();
  delayInit();

  int i;
  char phrase[] = "Clearing in\n3";

  lcd_PrintString("Hello, world!");
  delay(3000);

  for(i=3; i>0; --i){
    sprintf(phrase, "Clearing in\n%d", i);
    lcd_PrintString(phrase);
    delay(1000);
  }
  lcd_ClearScreen();
}
