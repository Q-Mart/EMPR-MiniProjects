#include "adc.h"
#include "serialUSB.h"
void ADC_InitAll(){
  PINSEL_CFG_Type pinCfg;
  
  int i;
  for(i = 23; i < 26; i++ ){
    pinCfg.Funcnum = 1;
    pinCfg.OpenDrain = 0;
    pinCfg.Pinmode = 0;
    pinCfg.Portnum = 0;
    pinCfg.Pinnum = i;
    PINSEL_ConfigPin(&pinCfg);
  }
  /*serialUSBWrite("Done 23 to 25");
  for(i = 30; i < 31; i++ ){
    pinCfg.Funcnum = 1;
    pinCfg.OpenDrain = 0;
    pinCfg.Pinmode = 0;
    pinCfg.Portnum = 1;
    pinCfg.Pinnum = i;
    PINSEL_ConfigPin(&pinCfg);
    }*/
  serialUSBWrite("Done 30, 31");
  ADC_Init(LPC_ADC, 200000);
  for(i = 0; i < 3; i++){
    ADC_IntConfig(LPC_ADC, i, DISABLE);
    ADC_ChannelCmd(LPC_ADC, i, ENABLE);
  }
  serialUSBWrite("INIT DONE");
}

float ADC_GetChannelVoltage(int chan){
  ADC_StartCmd(LPC_ADC, ADC_START_NOW);
  serialUSBWrite("Checking Value");
  //while(!(ADC_ChannelGetStatus(LPC_ADC, chan, ADC_DATA_DONE)));
  serialUSBWrite("Do I get here?");
  int val = ADC_ChannelGetData(LPC_ADC, chan);
  return ((float)val/4096.0f) * 3.3f;
}
