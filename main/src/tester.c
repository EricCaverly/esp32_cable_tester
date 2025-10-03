#include "tester.h"
#include "driver/gpio.h"
#include "hal/gpio_types.h"

void init_gpio() {
    // Set selector pins as output and low
    gpio_set_direction(SEL_A0, GPIO_MODE_OUTPUT);
    gpio_set_direction(SEL_A1, GPIO_MODE_OUTPUT);
    gpio_set_direction(SEL_A2, GPIO_MODE_OUTPUT);
    gpio_set_level(SEL_A0, 0);
    gpio_set_level(SEL_A1, 0);
    gpio_set_level(SEL_A2, 0);

    // Set RJ45 pins as input
    gpio_set_direction(RJ45_P0, GPIO_MODE_INPUT);
    gpio_set_direction(RJ45_P1, GPIO_MODE_INPUT);
    gpio_set_direction(RJ45_P2, GPIO_MODE_INPUT);
    gpio_set_direction(RJ45_P3, GPIO_MODE_INPUT);
    gpio_set_direction(RJ45_P4, GPIO_MODE_INPUT);
    gpio_set_direction(RJ45_P5, GPIO_MODE_INPUT);
    gpio_set_direction(RJ45_P6, GPIO_MODE_INPUT);
    gpio_set_direction(RJ45_P7, GPIO_MODE_INPUT);
    
}

void disable_line(uint8_t line) {
    printf("A0:%d A1:%d A2:%d", line & 0b001, line & 0b010, line & 0b100);
    gpio_set_level(SEL_A0, line & 0b001);
    gpio_set_level(SEL_A1, line & 0b010);
    gpio_set_level(SEL_A2, line & 0b100);
}