#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"
void ADC_InitChannel(int i);
float ADC_GetChannelVoltage(int chan);
int ADC_GetChannelData(int chan);
