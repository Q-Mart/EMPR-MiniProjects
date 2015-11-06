#include "wave.h"
#include "math.h"
#define PI 3.14159265
void dac(){
  PINSEL_CFG_Type pinCfg;

  pinCfg.Funcnum = 2;
  pinCfg.OpenDrain = 0;
  pinCfg.Pinmode = 0;
  pinCfg.Portnum = 0;
  pinCfg.Pinnum = 26;
  PINSEL_ConfigPin(&pinCfg);
  DAC_Init(LPC_DAC);
}

//Timer interrupt that will change global variable to true

void dac_UpdateData(int data){
  DAC_UpdateValue(LPC_DAC, data);
}

void dac_UpdateVoltage(int voltage){
  DAC_UpdateValue(LPC_DAC, (1023/MAX_VOLTAGE) * voltage);
}

