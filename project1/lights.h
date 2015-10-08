#include "lpc17xx_gpio.h"
#define L0 1<<18
#define L1 1<<20
#define L2 1<<21
#define L3 1<<23
#define ALL_LIGHTS L0 | L1 | L2 | L3
#define PORT 1

void clearAll();
void clearLight(unsigned int lightNumber);
void lightsInit();
void switchOnAll();
void switchOnLight(unsigned int lightNumber);
void displayNum(unsigned int num);//Converts num to binary to display on lights
