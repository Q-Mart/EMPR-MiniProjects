#include "wave.h"

void wave_Init(){
  PINSEL_CFG_Type pinCfg;

  pinCfg.Funcnum = 2;
  pinCfg.OpenDrain = 0;
  pinCfg.Pinmode = 0;
  pinCfg.Portnum = 0;
  pinCfg.Pinnum = 26;
  PINSEL_ConfigPin(&pinCfg);
  DAC_Init(LPC_DAC);
}

void wave_Sin(int val){
  DAC_UpdateValue(LPC_DAC, (uint32_t) 1000);
  DAC_UpdateValue(LPC_DAC, (uint32_t) 1000);
  DAC_UpdateValue(LPC_DAC, (uint32_t) 1000);
  DAC_UpdateValue(LPC_DAC, (uint32_t) 1000);
  DAC_UpdateValue(LPC_DAC, (uint32_t) 1000);
}
