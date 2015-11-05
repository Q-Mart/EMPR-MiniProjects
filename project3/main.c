#include "main.h"
#include "stdio.h"

int main(){
  serialUSBInit();
  wave_Init();

  /* PINSEL_CFG_Type pinCfg; */

  /* pinCfg.Funcnum = 1; */
  /* pinCfg.OpenDrain = 0; */
  /* pinCfg.Pinmode = 0; */
  /* pinCfg.Portnum = 0; */
  /* pinCfg.Pinnum = 23; */
  /* PINSEL_ConfigPin(&pinCfg); */
  /* ADC_Init(LPC_ADC, 200000); */
  /* ADC_IntConfig(LPC_ADC, 0, DISABLE); */
  /* ADC_ChannelCmd(LPC_ADC, 0, ENABLE); */
  /* serialUSBWrite("Is this working?"); */
  /* char str[15]; */
  /* int val; */
  /* while(1){ */
  /*   ADC_StartCmd(LPC_ADC, ADC_START_NOW); */
  /*   while(!(ADC_ChannelGetStatus(LPC_ADC, 0, ADC_DATA_DONE))); */
  /*   val = ADC_ChannelGetData(LPC_ADC, 0); */
  /*   sprintf(str, "%d\n\r", val); */
  /*   serialUSBWrite(str); */
  /* } */

  while (1){
    wave_Sin(512);
  }
  serialUSBWrite("WAAAAAAAVE\r\n");
}
