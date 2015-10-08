#include "lights.h"

volatile unsigned int on = 0;

void SysTick_Handler(){
  on++;
}

void main(void) {
  lightsInit();
  SysTick_Config(SystemCoreClock/1000 - 1);
  //clearAll();
  //displayNum(2);
}
