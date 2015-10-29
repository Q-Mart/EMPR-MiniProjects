#include "calc.h"
#include "serialUSB.h"
#include "stdio.h"
#include "lcd.h"

void print_input(int val);

typedef enum {OP, INT} IntExp;
int input[16];
int input_marker = 0;
int symbol_point = 0;
int i;
int to_clear = 0;


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
      return calculateExpression(acc / calculateExpression(0));
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
  lcd_ClearScreen();
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
      sprintf(str, "%d", res);
      serialUSBWrite(str);
      for(i=64; i<80 && str[i - 64] != '\0'; ++i){
        lcd_PrintChar(str[i - 64], i);
      }
      input_marker = 0;
      symbol_point = 0;
      to_clear = 1;
      break;
    case 16:
      break;
    default:
      if(to_clear == 1){
          lcd_ClearScreen();
          to_clear = 0;
      }
      input[input_marker] = pollVal;
      print_input(pollVal);
      input_marker++;
    }
  }
}

void print_input(int val){

  switch(val){
  case 0:
    serialUSBWrite("0");
    lcd_PrintChar('0', input_marker);
    break;
  case 1:
    serialUSBWrite("1");
    lcd_PrintChar('1', input_marker);
    break;
  case 2:
    serialUSBWrite("2");
    lcd_PrintChar('2', input_marker);
    break;
  case 3:
    serialUSBWrite("3");
    lcd_PrintChar('3', input_marker);
    break;
  case 4:
    serialUSBWrite("4");
    lcd_PrintChar('4', input_marker);
    break;
  case 5:
    serialUSBWrite("5");
    lcd_PrintChar('5', input_marker);
    break;
  case 6:
    serialUSBWrite("6");
    lcd_PrintChar('6', input_marker);
    break;
  case 7:
    serialUSBWrite("7");
    lcd_PrintChar('7', input_marker);
    break;
  case 8:
    serialUSBWrite("8");
    lcd_PrintChar('8', input_marker);
    break;
  case 9:
    serialUSBWrite("9");
    lcd_PrintChar('9', input_marker);
    break;
  case 10:
    serialUSBWrite("+");
    lcd_PrintChar('+', input_marker);
    break;
  case 11:
    serialUSBWrite("-");
    lcd_PrintChar('-', input_marker);
    break;
  case 12:
    serialUSBWrite("/");
    lcd_PrintChar('/', input_marker);
    break;
  case 14:
    serialUSBWrite("*");
    lcd_PrintChar('*', input_marker);
    break;
      default:
	serialUSBWrite("ELSE\n\r");
    lcd_PrintChar('E', input_marker);
	break;

	}

}
