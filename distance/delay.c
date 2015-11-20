#include "delay.h"

volatile unsigned long on = 0;

void delayInit(){
  SysTick_Config(SystemCoreClock/1000 - 1);
}
void SysTick_Handler(){
  on++;
}
void delay(unsigned long tick){
  unsigned long systickcnt;
  systickcnt = on;
  while ((on - systickcnt) < tick);
}
