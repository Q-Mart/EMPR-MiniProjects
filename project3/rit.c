#include "rit.h"

void RIT_IRQHandler(){
  rit_IRQHandler();
  RIT_GetIntStatus(LPC_RIT);
}

void rit_Init(){
  NVIC_EnableIRQ(RIT_IRQn);
  RIT_Init(LPC_RIT);
}

void rit_Enable(){
  RIT_TimerConfig(LPC_RIT, 1);
  RIT_Cmd(LPC_RIT, ENABLE);
}
