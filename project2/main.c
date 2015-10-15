#include "main.h"

void main(){
  serialUSBInit();
  i2c_init();

  i2c_deviceCount();
}
