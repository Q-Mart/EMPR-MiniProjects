#include "main.h"
#include "lights.h"
#include "delay.h"
#include "serialUSB.h"

void init(){
  lightsInit();
  delayInit();
  serialUSBInit();
}

void stage_1(){
  int i;
  int x;

  for(i = 0; i < 5; ++i){
    for(x = 0; x < 4; ++x){
      switchOnLight(x);
      delay(1000);
      clearLight(x);
    }
  }
}

void stage_2(){
  int i;

  for(i = 0; i < 16; ++i){
    displayNum(i);
    delay(1000);
  }
  clearAll();
}

void stage_4(){
  serialUSBWrite("Hello World!\n\r");
}

void main(void) {
  init();

  serialUSBWrite("Commencing Stage 1\n\r");
  stage_1();
  serialUSBWrite("Stage 1 complete\n\r");

  delay(500);

  serialUSBWrite("Commencing Stage 2\n\r");
  stage_2();
  serialUSBWrite("Stage 2 complete\n\r");

  delay(500);

  serialUSBWrite("Commencing Stage 4\n\r");
  stage_4();
  serialUSBWrite("Stage 4 complete\n\r");
}
