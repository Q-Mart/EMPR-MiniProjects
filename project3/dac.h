#include "lpc17xx_dac.h"
#include "lpc17xx_pinsel.h"
#include "delay.h"
void dac_Init();
void dac_UpdateData(int data);
void dac_UpdateVoltage(int voltage);

#define MAX_VOLTAGE 3.3
