#include "main.h"
#include "stdio.h"
#include "delay.h"
#include "adc.h"
#include "dac.h"
#include "math.hi"

void wave_Sin(int freq, float amp){
  int i;
  int seconds = 0;
  int period = 1/freq;

  while(second <= 5){
    for(i=0; i<=360; ++i){
      dac_UpdateData((amp * (1023/3.3))/2* sin(i * PI/180.0f) + 511);
      delay(1000/(360 * freq));
    }
    second += period;
  }
}

int main(){
  serialUSBInit();
  serialUSBWrite("Starting...\r\n");
  char str[15];
  int val;
  ADC_InitChannel(1);
  dac_Init();
  int i;

  //Stage 1
  serialUSBWrite("Beggining Stage 1\r\n");
  for(i=0;i<5;++i){
    ADC_GetChannelVoltage(1);
    delay(1000);
  }
  serialUSBWrite("Stage 1 complete\r\n");

  //Stage 2
  serialUSBWrite("Beginning Stage 2\r\n");
  serialUSBWrite("Wave 1: Amplitude 1V, Frequency 2Hz\r\n");
  wave_Sin(2, 1.0);

  serialUSBWrite("Wave 2: Amplitude 3V, Frequency 10Hz\r\n");
  wave_Sin(10, 3.0);

  serialUSBWrite("Wave 3: Amplitude 1.5V Frequency 20Hz\r\n");
  wave_Sin(20, 1.5);

  serialUSBWrite("Stage 2 complete\r\n");

  serialUSBWrite("Beginning Stage 2\r\n");
  for(i=0;i<5;++i){
    val = ADC_GetChannelData(1)/4;
    DAC_UpdateValue(LPC_DAC, val);
    delay(1000);
  }
}
