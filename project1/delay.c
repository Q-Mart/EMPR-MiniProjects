#include "delay.h"

volatile unsigned long on = 0; //Global variable to track tick count

void delayInit(){
  SysTick_Config(SystemCoreClock/1000); //Initialize the SysTick timer to interrupt every millisecond
}
void SysTick_Handler(){
  on++;
}
void delay(unsigned long tick){
  unsigned long systickcnt;
  systickcnt = on;//Essentially 0 out systickcnt
  while ((on - systickcnt) < tick);
}
