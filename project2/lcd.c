#include "lcd.h"
#include "serialUSB.h"

void lcd_Init(){
  uint8_t buffer[] = {SEND_COMMAND, 0x34, 0x0c, 0x06,
		      0x35, 0x04, 0x10, 0x42,
		      0x9f, 0x34, 0x02, SEND_COMMAND,
		      0x01};
  I2C_M_SETUP_Type sendCfg;
  sendCfg.sl_addr7bit = ADDR;
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
  uint8_t recBuf = SELECT_DDRAM;
  I2C_M_SETUP_Type readCfg;
  readCfg.sl_addr7bit = ADDR;
  readCfg.tx_data = NULL;
  readCfg.tx_length = 0;
  readCfg.rx_data = &recBuf;
  readCfg.rx_length = 1;
  I2C_MasterTransferData((LPC_I2C_TypeDef*)LPC_I2C1
			 , &readCfg
			 , I2C_TRANSFER_POLLING);
  if((SELECT_DDRAM & recBuf) > 0){
    return 0;
  } else {
    return 1;
  }
}

void lcd_SendData(uint8_t * buffer, int buffer_length){
  //Sends I2C data to the LCD
  
  I2C_M_SETUP_Type sendCfg;
  sendCfg.sl_addr7bit = ADDR;
  sendCfg.tx_data = buffer;
  sendCfg.tx_length = buffer_length;
  sendCfg.rx_data = NULL;
  sendCfg.rx_length = 0;
  sendCfg.retransmissions_max = 3;
  I2C_MasterTransferData((LPC_I2C_TypeDef*)LPC_I2C1
      , &sendCfg
      , I2C_TRANSFER_POLLING);
}

void lcd_PrintChar(char c, int loc){
  int code = (int) c; //Get the ASCI code
  uint8_t lcdCode; //The character code for set R on the lcd screen.

  /* The buffer sent to the I2C bus 
   * What is first sent is a control byte issuing an incoming command
   * then we sent our DDRAM address ORed with the select DDRAM bit (0x80)*/
  uint8_t buffer[2] = { SEND_COMMAND, loc | SELECT_DDRAM }; //The buffer sent of I2C bus

  //Now send the data
  lcd_SendData(buffer, 2);

  /* Match the ASCII values of the character to the chip's character set 'R' 
   * A special case is given for the space character and it is specifically mapped
   * If the character is not supported by our code, we print a checkerboard patter to the screen*/
  if ((code >= 97 && code <= 122)){
    //This handles lower case character
    lcdCode = code | SELECT_CGRAM;
  }else if ((code >= 65 && code <= 218) || (code >= 32 && code <= 47) || (code >= 48 && code <=57)){
    //This handles punctuation and capital letters and numbers
    lcdCode = (code + CHARACTER_SHIFT);
  } else {
    //Otherwise, display a checkerboard
    lcdCode = 35;
  }
  

  buffer[0] = SELECT_CGRAM;
  buffer[1] = lcdCode;

  lcd_SendData(buffer, 2);

}

void lcd_PrintString(char *str){
  int i;//current character 
  int z;//current 2nd line address
  int len = strlen(str);

  /* Print a string to the lcd 
   * To print to the second line, add a \n to the beginning of your second line string*/

  //The first thing to do is to clear the screen
  lcd_ClearScreen();

  //Error handling: Cuts string to max length
  if (len > 32){
    len = 32;
  }

  /* First line of LCD is addresses 00 - 15
   * second line is 64-79 */

  /* Print the first line 
   * Breaks if:
   *          line limit (of 16) is met
   *          the actual string length is met
   *          a newline is detected*/
  for(i=0; i<16 && i<len && str[i] != '\n'; ++i){
    lcd_PrintChar(str[i], i);
  }

  /* This line is only needed for two-line mode
   * It increments the current character (i) so that the newline character is not printed*/
  ++i;

  /* Print the second line 
   * Works through every address of the second line and prints the current character*/
  for(z=64; z<80 && i<len; ++i, ++z){
    lcd_PrintChar(str[i], z);
  }
}

void lcd_ClearScreen(){
  int i; //iterator variable
  uint8_t buffer[2] = {SEND_COMMAND, SCREEN_OFF};//I2C buffer. Begin by turning the screen off
  lcd_SendData(buffer, 2);

  //Now prepare to write to DDRAM by selecting it
  buffer[0] = SEND_COMMAND;
  buffer[1] = SELECT_DDRAM;
  lcd_SendData(buffer, 2);

  //Select CGRAM
  buffer[0] = SELECT_CGRAM;
  buffer[1] = CLEAR_CHARACTER;


  //And write spaces to every address in DDRAM
  for(i=0; i<80; ++i){
    lcd_SendData(buffer, 2);
  }

  //Finally, turn the screen on
  buffer[0] = SEND_COMMAND;
  buffer[1] = SCREEN_ON;
  lcd_SendData(buffer, 2);

}
