#include "main.h"

int main(){
  char str[32];
  float dist;


  ir_sensorInit();
  lcd_Init();
  lcd_ClearScreen();
  //Start in Calibration mode
  ir_sensorCalibrate();
  //Enter main loop
  while(1){
    dist = ir_sensorGetDistance();
    if(dist < 10.0f){
      lcd_PrintString("10 ::: Distance\ntoo short");
    } else if(dist > 80.0f) {
      lcd_PrintString("80 ::: Distance\ntoo long boi");
    } else {
      sprintf(str, "Dist  %.2f", dist);
      lcd_PrintString(str);
    }
    delay(300);
  }
}
