#include "tester.h"
#include "driver/gpio.h"
#include "hal/gpio_types.h"

void reset_results() {
    for (int i=0; i<8; ++i) {
        line_result[i].conn_to_len = 0;
        line_result[i].invalid = 2;
    }
}

void wire_pins_all_input() {
    gpio_set_direction(RJ45_P0, GPIO_MODE_INPUT);
    gpio_set_direction(RJ45_P1, GPIO_MODE_INPUT);
    gpio_set_direction(RJ45_P2, GPIO_MODE_INPUT);
    gpio_set_direction(RJ45_P3, GPIO_MODE_INPUT);
    gpio_set_direction(RJ45_P4, GPIO_MODE_INPUT);
    gpio_set_direction(RJ45_P5, GPIO_MODE_INPUT);
    gpio_set_direction(RJ45_P6, GPIO_MODE_INPUT);
    gpio_set_direction(RJ45_P7, GPIO_MODE_INPUT);
}

void init_gpio() {
    // Set selector pins as output and low
    gpio_set_direction(SEL_A0, GPIO_MODE_OUTPUT);
    gpio_set_direction(SEL_A1, GPIO_MODE_OUTPUT);
    gpio_set_direction(SEL_A2, GPIO_MODE_OUTPUT);
    gpio_set_level(SEL_A0, 0);
    gpio_set_level(SEL_A1, 0);
    gpio_set_level(SEL_A2, 0);

    // Set RJ45 pins as input
    wire_pins_all_input();

    // Set Test button as input
    gpio_set_direction(TEST_BTN_PIN, GPIO_MODE_INPUT);
    
}

void disable_line(uint8_t line) {
    printf("A0:%d A1:%d A2:%d", line & 0b001, line & 0b010, line & 0b100);
    gpio_set_level(SEL_A0, line & 0b001);
    gpio_set_level(SEL_A1, line & 0b010);
    gpio_set_level(SEL_A2, line & 0b100);
}

void test_all_pins() {
    for (int i=0; i<8; ++i) {
        test_pin(i);
    }
}

void test_pin(uint8_t line) {
    uint8_t tx_wire = g_lines[line];

    wire_pins_all_input();

    gpio_set_direction(tx_wire, GPIO_MODE_OUTPUT);
    gpio_set_direction(tx_wire, 1);

    for (int j=0; j<8; ++j) {
        if (j == line) continue;

        if (gpio_get_level(g_lines[j])) {
            line_result[line].conn_to[line_result[line].conn_to_len++] = j;
            switch(line_result[line].invalid) {
                case 0:
                    line_result[line].invalid = 1;
                    break;
                case 2:
                    if(g_correct_lines[line] == g_lines[j]) line_result[line].invalid = 0;
                    else line_result[line].invalid = 1;
                    break;
            }
        }


    }
}