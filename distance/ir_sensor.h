#include "delay.h"
#include "adc.h"
#include "key_pad.h"
 
#define HASH 15

void ir_sensorInit();
void ir_sensorCalibrate();
float ir_sensorGetDistance();
