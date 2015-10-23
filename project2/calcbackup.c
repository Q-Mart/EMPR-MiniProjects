
void calc_loop(){
  //Start loop
  serialUSBWrite("\n\r");
  int input[16];
  int input_marker = 0;
  while(1){
    //Poll keypad:
    //Either add new symbol to input string or
    //If calculate button is pressed then calculate and reset
    int pollVal = key_pad_poll();
    IntExp last = INT;
    int lastint = input[0];
    int op = 0;
    int result;
    int first = 1;
    int i;
    switch(pollVal){
    case 15:
      for(i = 1; i < input_marker; i++){
	if(last == OP ){ //Next must be Int
	  if(input[i] > 9){
	    serialUSBWrite("Input Error 1\n\r");
	  } else {
	    lastint = input[i];
	    last = INT;
	  }
	} else {
	  if(input[i] >9){
	    if(first){
	      result = lastint;
	      lastint = 0;
	      op = input[i];
	      first = 0;
	    } else {
	      switch(op){
	      case 14: //multiply
		result = result * lastint;
		lastint = 0;
		break;
	      case 10://Add
		result = result + lastint;
		lastint = 0;
		break;
	      case 11://Subtract
		result -= lastint;
		lastint = 0;
		break;
	      case 12://divide
		result = result/lastint;
		lastint = 0;
		break;
	      }
	      last = OP;
	      op = input[i];
	    }
	  } else {
	    lastint = (lastint * 10) + input[i];
	    last = INT;
	  }
	}
      }
      switch(op){
	      case 14: //multiply
		result = result * lastint;
		lastint = 0;
		break;
	      case 10://Add
		result = result + lastint;
		lastint = 0;
		break;
	      case 11://Subtract
		result -= lastint;
		lastint = 0;
		break;
	      case 12://divide
		result = result/lastint;
		lastint = 0;
		break;
	      }
      char str[40];
      sprintf(str, "\n\r%d\n\r",result);
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
