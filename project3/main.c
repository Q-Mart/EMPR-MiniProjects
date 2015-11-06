#include "main.h"
#include "stdio.h"
#include "delay.h"
#include "adc.h"
#include "wave.h"
#include "lpc17xx_dac.h"

int main(){
  serialUSBInit();
  serialUSBWrite("Starting...\n\r");
  char str[15];
  int val;
  ADC_InitChannel(1);
  PINSEL_CFG_Type pinCfg;

  pinCfg.Funcnum = 2;
  pinCfg.OpenDrain = 0;
  pinCfg.Pinmode = 0;
  pinCfg.Portnum = 0;
  pinCfg.Pinnum = 26;
  PINSEL_ConfigPin(&pinCfg);
  DAC_Init(LPC_DAC);
  while(1){
    val = ADC_GetChannelData(1)/4;
    /*sprintf(str, "%d\n\r", val);
      serialUSBWrite(str);*/
    DAC_UpdateValue(LPC_DAC, val);
    /*sprintf(str, "%d\n\r", val);
      serialUSBWrite(str);*/
  }
}
