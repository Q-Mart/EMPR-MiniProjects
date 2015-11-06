#include "wave.h"
#include "math.h"
#define PI 3.14159265
void wave_Init(){
  delayInit();
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

void wave_Sin(int freq, float amp){
  int i;

  while(1){
    for(i=0; i<=360; ++i){
      DAC_UpdateValue(LPC_DAC, (amp * (1023/3.3))/2* sin(i * PI/180.0f) + 511);
      delay(1000/(360 * freq));
    }
  }
}
