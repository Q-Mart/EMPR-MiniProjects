#include "main.h"
#include "delay.h"
#include "lcd.h"
#include "key_pad.h"
#include "calc.h"


void main(){
  serialUSBInit();
  i2c_init();
  lcd_Init();
  delayInit();

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



  key_pad_init();

  calc_loop();
  while(1){
    int retVal = key_pad_poll(); 
    if( retVal < 16){
      switch(retVal){
      case 0:
	serialUSBWrite("0\n\r");
	break;
      case 1:
	serialUSBWrite("1\n\r");
	break;
      case 2:
	serialUSBWrite("2\n\r");
	break;
      case 3:
	serialUSBWrite("3\n\r");
	break;
      case 4:
	serialUSBWrite("4\n\r");
	break;
      case 5:
	serialUSBWrite("5\n\r");
	break;
      case 6:
	serialUSBWrite("6\n\r");
	break;
      case 7:
	serialUSBWrite("7\n\r");
	break;
      case 8:
	serialUSBWrite("8\n\r");
	break;
      case 9:
	serialUSBWrite("9\n\r");
	break;
      default:
	serialUSBWrite("ELSE\n\r");
	break;

	}
    }
  }
  
  serialUSBWrite("END!\n\r");

}
