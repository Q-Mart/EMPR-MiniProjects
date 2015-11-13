#include "main.h"
#include "stdio.h"
#include "delay.h"
#include "adc.h"
#include "dac.h"
#include "math.h"
#include "pwm.h"
#include "lpc17xx_rit.h"
#include "lpc17xx_nvic.h"

#define PI 3.14159265

int thing;

void wave_Sin(int freq, float amp){
  int i;
  float seconds = 0.0f;
  float period = 1.0f/(float)freq;

  while(seconds <= 5){
    for(i=0; i<=360; ++i){
      dac_UpdateData((amp * (1023/3.3))/2* sin(i * PI/180.0f) + 511);
      delay(1000/(360 * freq));
    }
    seconds += period;
  }
}

void RIT_IRQHandler(){
  thing = (thing + 1)  % 5000;
  PWM_MatchUpdate(LPC_PWM1, 6, thing, PWM_MATCH_UPDATE_NOW);
  RIT_GetIntStatus(LPC_RIT);
}

int main(){
  serialUSBInit();
  thing = 1;

  pwmInit(5000);

  PWM_ResetCounter(LPC_PWM1);
  PWM_CounterCmd(LPC_PWM1, ENABLE);
  PWM_Cmd(LPC_PWM1, ENABLE);
  NVIC_EnableIRQ(RIT_IRQn);
  RIT_Init(LPC_RIT);
  RIT_TimerConfig(LPC_RIT, 1);
  RIT_Cmd(LPC_RIT, ENABLE);
  //RIT_GetIntStatus(LPC_RIT);
  //char str[15];
  //int i = 0;
  while(1){
    //sprintf(str, "%d -- %d\n\r", i, thing);
    //serialUSBWrite(str);
    //i += 1;
    //PWM_MatchUpdate(LPC_PWM1, 6, thing, PWM_MATCH_UPDATE_NOW);
    
  }
  

  

  /*
  serialUSBInit();
  delayInit();
  serialUSBWrite("Starting...\r\n");
  char str[15];
  int val;
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
  serialUSBWrite("Wave 1: Amplitude 1V, Frequency 2Hz\r\n");
  wave_Sin(2, 1.0);

  serialUSBWrite("Wave 2: Amplitude 3V, Frequency 10Hz\r\n");
  wave_Sin(10, 3.0);

  serialUSBWrite("Wave 3: Amplitude 1.5V Frequency 20Hz\r\n");
  wave_Sin(20, 1.5);

  serialUSBWrite("Stage 2 complete\r\n");

  serialUSBWrite("Beginning Stage 3\r\n");
  while(1){
    val = ADC_GetChannelData(1)/4;
    DAC_UpdateValue(LPC_DAC, val);
  
    }*/
}
