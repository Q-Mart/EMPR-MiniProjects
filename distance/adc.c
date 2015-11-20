#include "adc.h"
void ADC_InitChannel(int i){
  PINSEL_CFG_Type pinCfg;
    pinCfg.Funcnum = 1;
    pinCfg.OpenDrain = 0;
    pinCfg.Pinmode = 0;
    pinCfg.Portnum = 0;
    pinCfg.Pinnum = 23 + i;
    PINSEL_ConfigPin(&pinCfg);
  ADC_Init(LPC_ADC, 200000);
    ADC_IntConfig(LPC_ADC, i, DISABLE);
    ADC_ChannelCmd(LPC_ADC, i, ENABLE);
}

float ADC_GetChannelVoltage(int chan){
  int val = ADC_GetChannelData(chan);
  return (((float)val)/4096.0f) * 3.3;
}
int ADC_GetChannelData(int chan){
  ADC_StartCmd(LPC_ADC, ADC_START_NOW);
  while(!(ADC_ChannelGetStatus(LPC_ADC, chan, ADC_DATA_DONE)));
  return ADC_ChannelGetData(LPC_ADC, chan);
}
