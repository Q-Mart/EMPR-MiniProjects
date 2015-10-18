#include "lcd.h"

void lcd_Init(){
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
  I2C_MasterTransferData((LPC_I2C_TypeDef*)LPC_I2C1
				, &sendCfg
				, I2C_TRANSFER_POLLING);
}

int lcd_IsReady(){
  uint8_t recBuf = 0x80;
  I2C_M_SETUP_Type readCfg;
  readCfg.sl_addr7bit = 59;
  readCfg.tx_data = NULL;
  readCfg.tx_length = 0;
  readCfg.rx_data = &recBuf;
  readCfg.rx_length = 1;
  I2C_MasterTransferData((LPC_I2C_TypeDef*)LPC_I2C1
			 , &readCfg
			 , I2C_TRANSFER_POLLING);
  if((0x80 & recBuf) > 0){
    return 0;
  } else {
    return 1;
  }
}

void lcd_PrintChar(char c, int loc){
  int code = (int) c; //Get the ASCI code
  int lcdCode; //The character code for set R on the lcd screen.
  if ((code >= 97 && code <= 122) || (code >= 65 && code <= 218) || (code >= 48 && code <= 57) ){
    lcdCode = code + 128;
  } else {
    lcdCode = 35;
  }
}
