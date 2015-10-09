#include "main.h"
#include "lights.h"
#include "delay.h"

void init(){
	lightsInit();
	delayInit();
}

void stage_1(){
	int i;
	int x;

	for(i = 0; i < 5; ++i){
		for(x = 0; x < 4; ++x){
			switchOnLight(x);
			delay(1000);
			clearLight(x);
		}
	}
}

void stage_2(){
	int i;

	for(i = 0; i < 16; ++i){
		displayNum(i);
		delay(1000);
	}
	clearAll();
}

void main(void) {
	init();
	stage_2();
	
}
