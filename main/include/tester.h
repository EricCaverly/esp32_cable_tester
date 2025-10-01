#include "driver/gpio.h"

#define SEL_A0 GPIO_NUM_18
#define SEL_A1 GPIO_NUM_19
#define SEL_A2 GPIO_NUM_21

void init_gpio();
void disable_line(uint8_t line);