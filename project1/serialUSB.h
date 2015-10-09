#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"
#include "lpc_types.h"

void serialInit();

//Read serial. non-blocking
int serialUSBRead(char *buffer, int buffer_length);

//Write serial. Blocking
int serialUSBWrite(char *buffer, int buffer_length);
