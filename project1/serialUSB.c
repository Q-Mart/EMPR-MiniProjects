#include "serialUSB.h"

void serialUSBInit(){
  UART_CFG_Type uartConfigStruct;
  UART_FIFO_CFG_Type uartFIFOConfigStruct;
  PINSEL_CFG_Type pinCfg;

  //Transmission setup
  pinCfg.Funcnum = 1;
  pinCfg.OpenDrain = 0;
  pinCfg.Pinmode = 0;
  pinCfg.Portnum = 0;
  pinCfg.Pinnum = 2;
  PINSEL_ConfigPin(&pinCfg);

  //Reciever setup
  pinCfg.Pinnum = 3;
  PINSEL_ConfigPin(&pinCfg);

  UART_ConfigStructInit(&uartConfigStruct);
  UART_FIFOConfigStructInit(&uartFIFOConfigStruct);

  UART_Init((LPC_UART_TypeDef *)LPC_UART0, &uartConfigStruct);
  UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART0, &uartFIFOConfigStruct);
  UART_TxCmd((LPC_UART_TypeDef *)LPC_UART0, ENABLE);
}

int serialUSBRead(char *buffer, int buffer_length){
  return(UART_Receive((LPC_UART_TypeDef *)LPC_UART0,
		      (uint8_t *)buffer, buffer_length, NONE_BLOCKING));
}

int serialUSBWrite(char *buffer){
  return(UART_Send((LPC_UART_TypeDef *)LPC_UART0,
		   (uint8_t *)buffer, strlen(*buffer), BLOCKING)); 
}
