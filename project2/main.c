#include "main.h"
#include "delay.h"


void main(){
  serialUSBInit();
  i2c_init();

  //i2c_deviceCount();
  
  int addr = 59;
  uint8_t buffer[] = {0x00, 0x34, 0x0c, 0x06,
		      0x35, 0x04, 0x10, 0x42,
		      0x9f, 0x34, 0x02, 0x00,
		      0x01};
  I2C_M_SETUP_Type sendCfg;
  sendCfg.sl_addr7bit = addr;
  sendCfg.tx_data = buffer;
  sendCfg.tx_length = 13;
  sendCfg.rx_data = NULL;
  sendCfg.rx_length = 0;
  sendCfg.retransmissions_max = 3;
  if (I2C_MasterTransferData((LPC_I2C_TypeDef*)LPC_I2C1
			     , &sendCfg
			     , I2C_TRANSFER_POLLING) == SUCCESS){

    serialUSBWrite("Write to I2C bus succeeded!\n\r");
  }


  uint8_t recBuf = 0x80;
  I2C_M_SETUP_Type readCfg;
  readCfg.sl_addr7bit = addr;
  readCfg.tx_data = NULL;
  readCfg.tx_length = 0;
  readCfg.rx_data = &recBuf;
  readCfg.rx_length = 1;
  while ((0x80 & recBuf) > 0){
    I2C_MasterTransferData((LPC_I2C_TypeDef*)LPC_I2C1
			   ,&readCfg
			   ,I2C_TRANSFER_POLLING);
    serialUSBWrite("Waiting\n\r");
  }
  serialUSBWrite("Ready!\n\r");
  delayInit();
  delay(1000);
  

  uint8_t bufferLd[] = {0x00, 0x81};

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

  uint8_t bufferYay[] = {0x40, 0x64, 0x64};

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
    
  

}
