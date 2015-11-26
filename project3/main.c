#include "main.h"

#define PI 3.14159265

float pwm_Width;

void wave_Sin(int del, float amp){
  int i;
  float seconds = 0.0f;

  while(seconds <= 8){
    for(i=0; i<=360; i+=4){
      dac_UpdateData((amp * (1023/3.3))/2* sin(i * PI/180.0f) + 511);
      delay(del);
    }
    seconds += (float)del * 0.001 * 90;
  }
}

void rit_IRQHandler(){
  if (pwm_Width > 1.0){
    pwm_Width = 0.0;
  }
  else{
    pwm_Width = pwm_Width + 0.0002f;
  }
  pwmSetValue(6, pwm_Width, 5000);
}

int main(){
  serialUSBInit();
  delayInit();
  pwmInit(5000, 6);

  //pwmDisable();

  pwm_Width = 0.0f;

  pwmSetValue(6, 0.5, 5000);

  serialUSBWrite("Starting...\r\n");
  char str[15];
  ADC_InitChannel(1);
  dac_Init();
  int i;
  
  //Stage 1
  serialUSBWrite("Beggining Stage 1\r\n");
  float inputVal;
  for(i=0;i<5;++i){
    inputVal = ADC_GetChannelVoltage(1);
    sprintf(str, "%f\n\r", inputVal);
    serialUSBWrite(str);
    delay(1000);
  }

  serialUSBWrite("Stage 1 complete\r\n");

  //Stage 2
  serialUSBWrite("Beginning Stage 2\r\n");
  serialUSBWrite("Wave 1: Amplitude 1V, Frequency 11Hz\r\n");
  wave_Sin(1, 1.0);

  serialUSBWrite("Wave 2: Amplitude 3V, Frequency 5.5Hz\r\n");
  wave_Sin(2, 3.0);

  serialUSBWrite("Wave 3: Amplitude 1.5V Frequency 2.75Hz\r\n");
  wave_Sin(4, 1.5);

  serialUSBWrite("Stage 2 complete\r\n");

  //Stage 3
  serialUSBWrite("Beginning Stage 3\r\n");

  int val;

  while(1){
    val = ADC_GetChannelData(1)/4;
    DAC_UpdateValue(LPC_DAC, val);
  }

  
  //Stage 4
  serialUSBWrite("Beginning Stage 4\r\n");

  pwm_Width = 0.0f;
  rit_Init();
  rit_Enable();
  while(1);
}
