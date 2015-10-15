#include "i2c_helper.h"
void i2c_init(){
  PINSEL_CFG_Type pinCfg;

  pinCfg.Funcnum = 1;
  pinCfg.OpenDrain = 0;
  pinCfg.Pinmode = 0;
  pinCfg.Portnum = 0;
  pinCfg.Pinnum = 27;
  PINSEL_ConfigPin(&pinCfg);
  pinCfg.Pinnum = 28;
  PINSEL_ConfigPin(&pinCfg);
  I2C_Init(LPC_I2C0, 100000);
  I2C_Cmd(LPC_I2C0, ENABLE);
}

int i2c_deviceCount(){
  int addr;
  int count = 0;
  uint8_t txbuff[8];
  uint8_t rxbuff[8];
  for(addr = 1; addr < 127; addr ++){
    I2C_M_SETUP_Type setupCfg;
    setupCfg.sl_addr7bit = addr;
    setupCfg.tx_data = txbuff;
    setupCfg.tx_length = 8;
    setupCfg.rx_data = rxbuff;
    setupCfg.rx_length = 8;
    setupCfg.rx_count = 0;
    if(I2C_MasterTransferData(LPC_I2C0, &setupCfg, I2C_TRANSFER_POLLING) == SUCCESS){
      serialUSBWrite("Address Found");
      count++;
    }
  }
  return count;
}
