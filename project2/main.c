#include "main.h"
#include "delay.h"
#include "lcd.h"


void main(){
  serialUSBInit();
  i2c_init();
  lcd_Init();

  //i2c_deviceCount();
  
  serialUSBWrite("Write to I2C bus succeeded!\n\r");

  while (lcd_IsReady() == 0){
    serialUSBWrite("Waiting\n\r");
  }

  serialUSBWrite("Done waiting\n\r");
  

  uint8_t bufferLd[] = {0x00, 0x80};

  I2C_M_SETUP_Type sendCfg;
  int addr = 59;
  sendCfg.sl_addr7bit = addr;
  sendCfg.tx_data = bufferLd;
  sendCfg.tx_length = 2;
  sendCfg.rx_data = NULL;
  sendCfg.rx_length = 0;
  sendCfg.retransmissions_max = 3;
  if (I2C_MasterTransferData((LPC_I2C_TypeDef*)LPC_I2C1
			     , &sendCfg
			     , I2C_TRANSFER_POLLING) == SUCCESS){

    serialUSBWrite("Write to I2C bus succeeded! Zoot up\n\r");
  }

  uint8_t bufferYay[] = {0x40, 0xA0, 0x64};

  sendCfg.sl_addr7bit = addr;
  sendCfg.tx_data = bufferYay;
  sendCfg.tx_length = 3;
  sendCfg.rx_data = NULL;
  sendCfg.rx_length = 0;
  sendCfg.retransmissions_max = 3;
  if (I2C_MasterTransferData((LPC_I2C_TypeDef*)LPC_I2C1
			     , &sendCfg
			     , I2C_TRANSFER_POLLING) == SUCCESS){

    serialUSBWrite("Write to I2C bus succeeded! Zoot up\n\r");
  }


  lcd_PrintChar('a', 0);
  lcd_PrintChar(' ', 1);
  lcd_PrintString("Hello World!");
    
 lcd_ClearScreen();
 lcd_PrintString("I'm back");

}
