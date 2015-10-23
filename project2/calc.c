#include "calc.h"
#include "serialUSB.h"
#include "stdio.h"

void print_input(int val);

typedef enum {OP, INT} IntExp;
int input[16];
int input_marker = 0;
int symbol_point = 0;

int getNextSymbol(){
  if(symbol_point < input_marker){
    return input[symbol_point++];
  } else {
    return 16;
  }
}
int calculateExpression(int acc){
  int symb = getNextSymbol();
  if (symb == 16) return acc;
  if(symb > 9){
    switch(symb){
    case 10://Plus
      return acc + calculateExpression(0);
    case 11://Minus
      return acc - calculateExpression(0);
    case 12://Divide
      return calculateExpression(acc * calculateExpression(0));
    case 14://Multiply
      return calculateExpression(acc * calculateExpression(0));
    default:
      return 0;
    }
  } else {
    return calculateExpression((acc*10) + symb);
  }
}


void calc_loop(){
  //Start loop
  serialUSBWrite("\n\r");
  while(1){
    //Poll keypad:
    //Either add new symbol to input string or
    //If calculate button is pressed then calculate and reset
    int pollVal = key_pad_poll();
    int res;
    char str[16];
    switch(pollVal){
    case 15:
      res = calculateExpression(0);
      sprintf(str, "\n\r%d\n\r", res);
      serialUSBWrite(str);
      input_marker = 0;
      break;
    case 16:
      break;
    default:
      input[input_marker] = pollVal;
      input_marker++;
      print_input(pollVal);
    }
  }
}

void print_input(int val){

  switch(val){
  case 0:
    serialUSBWrite("0");
    break;
  case 1:
    serialUSBWrite("1");
    break;
  case 2:
    serialUSBWrite("2");
    break;
  case 3:
    serialUSBWrite("3");
    break;
  case 4:
    serialUSBWrite("4");
    break;
  case 5:
    serialUSBWrite("5");
    break;
  case 6:
    serialUSBWrite("6");
    break;
  case 7:
    serialUSBWrite("7");
    break;
  case 8:
    serialUSBWrite("8");
    break;
  case 9:
    serialUSBWrite("9");
    break;
  case 10:
    serialUSBWrite("+");
    break;
  case 11:
    serialUSBWrite("-");
    break;
  case 12:
    serialUSBWrite("/");
    break;
  case 14:
    serialUSBWrite("*");
    break;
      default:
	serialUSBWrite("ELSE\n\r");
	break;

	}

}
