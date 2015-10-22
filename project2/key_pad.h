#include "i2c_helper.h"
#include "math.h"
#define KEYPAD_ADDR 33
void key_pad_init();

int find_pow_of_2(int a);

const int key_pad_keys[4][4];

int key_pad_poll();
