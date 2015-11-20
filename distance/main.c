#include "main.h"

int main(){
  char str[16];
  float dist;

  ir_sensorInit();
  //Start in Calibration mode
  ir_sensorCalibrate();
  //Enter main loop
  while(1){
    dist = ir_sensorGetDistance();
    sprintf(str, "Dist  %f", dist);
    lcd_PrintString(str);
  }
}
