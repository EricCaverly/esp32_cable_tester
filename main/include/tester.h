#include "driver/gpio.h"

#define SEL_A0 GPIO_NUM_19
#define SEL_A1 GPIO_NUM_18
#define SEL_A2 GPIO_NUM_17

#define RJ45_P0 GPIO_NUM_13
#define RJ45_P1 GPIO_NUM_12
#define RJ45_P2 GPIO_NUM_14
#define RJ45_P3 GPIO_NUM_27
#define RJ45_P4 GPIO_NUM_26
#define RJ45_P5 GPIO_NUM_25
#define RJ45_P6 GPIO_NUM_33
#define RJ45_P7 GPIO_NUM_32

#define SCL 22
#define SDA 21
#define DISP_WIDTH 128
#define DISP_HEIGHT 64

void init_gpio();
void disable_line(uint8_t line);