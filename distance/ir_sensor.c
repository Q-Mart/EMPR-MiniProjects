#include "ir_sensor.h"
#include "serialUSB.h"

static float m;
static float c;

void ir_sensorInit(){
  delayInit();
  ADC_InitChannel(1);
  i2c_init();
  key_pad_init();
  serialUSBInit();
  m = 0.0f;
  c = 0.0f;
}

void ir_sensorCalibrate(){
  /* Calibrates the IR sensor */
  /* TO USE: */
  /* 1. Place an object 10cm away from the sensor */
  /* 2. Press # */
  /* 3. Place an object 20cm away from the sensor */
  /* 4. Press # */

  /* You're now good to go */

  int i;
  float samples[2];
  for(i=0;i<2;i++){
    /* wait for the hash key to be pressed */
    while(key_pad_poll() != HASH);
    samples[i] = ADC_GetChannelVoltage(1);
  }
  
  m = (samples[0] - samples[1]) / ((1.0f/10.0f) - (1.0f/20.0f));
  c = samples[1] - (m/20.0f);
  char str[16];
  sprintf(str, "%.3f -- %.3f\n", m, c);
  serialUSBWrite(str);
}

float ir_sensorGetDistance(){
  /* returns the distance in cm */
  float val = ADC_GetChannelVoltage(1);
  return m/(val - c);
}
