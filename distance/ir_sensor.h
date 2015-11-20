#include "serialUSB.h"
#include "lpc17xx_adc.h"
#include "delay.h"
#include "adc.h"
#include "keypad.h"
#include "lcd.c"

#define HASH 15

void ir_sensorInit();
void ir_sensorCalibrate();
int ir_sensorGetDistance();
