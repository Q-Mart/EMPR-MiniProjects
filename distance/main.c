#include "adc.h"
#include "key_pad.h"
#include "lcd.h"
#include "rit.h"
#include "serialUSB.h"
#include "delay.h"

int main(){
  //Init stuff
  delayInit();
  ADC_InitChannel(1);
  i2c_init();
  key_pad_init();
  lcd_Init();
  serialUSBInit();
  lcd_ClearScreen();
  int calibStage = 1;
  //Start in Calibration mode
  while(calibStage){
    if (key_pad_poll() == 15) calibStage =0;
    //serialUSBWrite("Started fromn the bottom now we here");
  }
  //Calibrate, by reading adc
  float point1 = ADC_GetChannelVoltage(1);
  calibStage = 1;
  //Start in Calibration mode
  while(calibStage){
    if (key_pad_poll() == 15) calibStage =0;
    //serialUSBWrite("Started fromn the bottom now we here");
  }
  //Calibrate, by reading adc
  float point2 = ADC_GetChannelVoltage(1);
  float m = (point1 - point2)/((1.0f/10.0f)- (1.0f/20.0f));//point1 should be at 10cm
  float c = point2 - (m/20.0f);
  float val;
  char str[16];
  float dist;
  //Enter main loop
  while(1){
    val = ADC_GetChannelVoltage(1);
    dist = m/(val-c);
    sprintf(str, "Dist  %f", dist);
    while(lcd_IsReady() == 0);
    lcd_PrintString(str);
    delay(500);
  }
}
