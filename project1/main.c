#include "lights.h"

volatile unsigned long on = 0;

void SysTick_Handler(){
  on++;
}
void Delay(unsigned long tick){
  unsigned long systickcnt;
  systickcnt = on;
  while ((on - systickcnt) < tick);
}

void main(void) {
  lightsInit();
  SysTick_Config(SystemCoreClock/1000 - 1);
  clearAll();
  Delay(500);
  displayNum(2);
  Delay(500);
  displayNum(9);
  int buzz = 0;
  for(;;)    {
    if(buzz == 0){
      clearAll();
      switchOnAll();
      buzz=1;
    } else {
      buzz = 0;
      clearAll();
      displayNum(9);
    }
    Delay(500);
  }
}
