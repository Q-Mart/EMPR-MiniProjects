#import "i2c_helper.h"
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
  I2C_Cmd(LPC_I2C0, ENABLE)
}

int 12c_deviceCount(){
  int addr;
  uint8_t txbuff[8];
  uint8_t rxbuff[8];
  for(addr = 1; addr < 127; addr ++){
    I2C_M_SETUP_Type setupCfg;
    setupCfg.sl_addr7bit = addr;
    tx_data = txbuff;
    tx_length = 8;
    rx_data = rxbuff;
    rx_length = 8;
    rx_count = 0;
    I2C_MasterTransferData(LPC_I2C0, &setupCfg, I2C_TRANSFER_POLLING);
    serialUsbWrite("Address Found")
  }
}
