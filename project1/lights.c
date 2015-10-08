#include "lights.h"

void lightsInit(){
  GPIO_SetDir(PORT, ALL_LIGHTS, 1); //Set all LEDs as output
}
void clearAll(){
  GPIO_ClearValue(PORT, ALL_LIGHTS);
}
void clearLight(unsigned int lightNumber){
  switch(lightNumber % 4){
  case 0:
    GPIO_ClearValue(PORT, L0);
    break;
  case 1:
    GPIO_ClearValue(PORT, L1);
    break;
  case 2:
    GPIO_ClearValue(PORT, L2);
    break;
  case 3:
    GPIO_ClearValue(PORT, L3);
    break;
  }
}
void switchOnAll(){
  GPIO_SetValue(PORT, ALL_LIGHTS);
}
void switchOnLight(unsigned int lightNumber){
  switch(lightNumber % 4){
  case 0:
    GPIO_SetValue(PORT, L0);
    break;
  case 1:
    GPIO_SetValue(PORT, L1);
    break;
  case 2:
    GPIO_SetValue(PORT, L2);
    break;
  case 3:
    GPIO_SetValue(PORT, L3);
    break;
  }
}
void displayNum(unsigned int num){
  int val = num % 16;
  clearAll();
  if (val-8 >= 0){
    switchOnLight(0);
    val -= 8;
  }
  if (val - 4 >= 0){
    switchOnLight(1);
    val -= 4;
  }
  if (val - 2 >= 0){
    switchOnLight(2);
    val -= 2;
  }
  if (val - 1 >= 0) switchOnLight(3);
}
