#include "lpc17xx_pwm.h"
#include "lpc17xx_pinsel.h"

void pwmInit(int base, int channel);
void pwmSetValue(int channel, float val, int base);
void pwmDisable();
