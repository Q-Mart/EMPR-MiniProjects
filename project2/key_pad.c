#include "key_pad.h"
#include "serialUSB.h"

void key_pad_init(){
  i2c_init();

  uint8_t txbuff = {0xFF};
  I2C_M_SETUP_Type setupCfg;
  setupCfg.sl_addr7bit = KEYPAD_ADDR;
  setupCfg.tx_data = &txbuff;
  setupCfg.tx_length = 1;
  setupCfg.rx_data = NULL;
  setupCfg.rx_length = 0;
  if(I2C_MasterTransferData((LPC_I2C_TypeDef*) LPC_I2C1, &setupCfg, I2C_TRANSFER_POLLING) == SUCCESS){
    serialUSBWrite("key pad init successful");
  }
}

int find_pow_of_2(int a){
  int p = 0;
  while(a >1){
    p+=1;
    a = a/2;
  }

  return p;
}

const int key_pad_keys[4][4] = {{1, 2, 3, 10},
				{4, 5, 6, 11},
				{7, 8, 9, 12},
				{14, 0, 15, 13}};

int key_pad_poll(){
  int i;
  for(i = 0; i <= 3; i++){
    //Loop through columns
    uint8_t byte = ((~(1<<(3-i)))<<4) | 0x0F;
    uint8_t rxbuff;
    I2C_M_SETUP_Type setupCfg;
    setupCfg.sl_addr7bit = KEYPAD_ADDR;
    setupCfg.tx_data = &byte;
    setupCfg.tx_length = 1;
    setupCfg.rx_data = &rxbuff;
    setupCfg.rx_length = 1;
    I2C_MasterTransferData((LPC_I2C_TypeDef*) LPC_I2C1, &setupCfg, I2C_TRANSFER_POLLING);
    rxbuff = (~(rxbuff & 0x0F)) & 0x0F;
    if(rxbuff != 0){
      rxbuff = 3 - find_pow_of_2(rxbuff);
      return key_pad_keys[rxbuff][i];
    }
  }
  return 16;
}
