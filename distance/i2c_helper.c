#include "i2c_helper.h"
void i2c_init(){
  PINSEL_CFG_Type pinCfg;

  pinCfg.Funcnum = 3;
  pinCfg.OpenDrain = 0;
  pinCfg.Pinmode = 0;
  pinCfg.Portnum = 0;
  pinCfg.Pinnum = 0;
  PINSEL_ConfigPin(&pinCfg);
  pinCfg.Pinnum = 1;
  PINSEL_ConfigPin(&pinCfg);
  I2C_Init((LPC_I2C_TypeDef*)LPC_I2C1, 100000);
  I2C_Cmd((LPC_I2C_TypeDef*)LPC_I2C1, ENABLE);
}

int i2c_deviceCount(){
  int addr;
  int count = 0;
  uint8_t txbuff = 0;
  uint8_t rxbuff[4];
  char message[80];
  for(addr = 1; addr < 127; addr++){
    I2C_M_SETUP_Type setupCfg;
    setupCfg.sl_addr7bit = addr;
    setupCfg.tx_data = &txbuff;
    setupCfg.tx_length = 1;
    setupCfg.rx_data = NULL;
    setupCfg.rx_length = 0;
    setupCfg.retransmissions_max = 3;
    if(I2C_MasterTransferData((LPC_I2C_TypeDef*)LPC_I2C1, &setupCfg, I2C_TRANSFER_POLLING) == SUCCESS){
      sprintf(message, "Address Found: %d\n\r", addr);
      serialUSBWrite(message);
      count++;
    }
  }
  return count;
}
