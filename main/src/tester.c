#include "tester.h"
#include "driver/gpio.h"
#include "freertos/idf_additions.h"
#include "hal/gpio_types.h"
#include "portmacro.h"
#include "soc/adc_channel.h"

// -------------- Initialization ------------------------ //
const uint8_t g_lines[] = {
    RJ45_P0,
    RJ45_P1,
    RJ45_P2,
    RJ45_P3,
    RJ45_P4,
    RJ45_P5,
    RJ45_P6,
    RJ45_P7
};

const uint8_t g_correct_lines[] = {
    RJ45_P1,
    RJ45_P0,
    RJ45_P3,
    RJ45_P2,
    RJ45_P5,
    RJ45_P4,
    RJ45_P7,
    RJ45_P6
};

adc_oneshot_unit_handle_t adc2_handle;

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

    // Set Test button as input
    gpio_set_direction(TEST_BTN_PIN, GPIO_MODE_INPUT);
    
}

// ----------------- Helper Functions -------------------- //

uint8_t read_pins() {
    uint8_t val = 0;

    for (int i=0; i<8; ++i) {
        if (gpio_get_level(g_lines[i])) {     
            val |= 1 << (7-i);
        }
    }

    return val;
}

test_result_t test_pin(uint8_t line) {
    int adc_v;

    // Chose the line to turn high and disable ADC on it
    select_line(line+1);

    // Wait for potential interference, capacitance, inductance ex to disipate
    vTaskDelay(portTICK_PERIOD_MS * 60);

    // Read all GPIO pins
    uint8_t rx_values = read_pins();

    // Read ADC
    adc_oneshot_read(adc2_handle, ADC2_GPIO15_CHANNEL, &adc_v);

    // Determine direction based on ADC value
    uint8_t dir;
    if (adc_v < 1000)               // Open connection
        dir = 0b00;
    else if (adc_v < 1800) {        // Left?
        dir = 0b01;
    } else if (adc_v < 2900) {      // Right?
        dir = 0b10;
    } else {                        // Short
        dir = 0b11;
    }
    
    // Construct result object
    test_result_t result = {
        .tx = (1 << line),
        .rx = rx_values,
        .dir = dir
    };

    return result;
}

// ------------------ API ------------------- //

void select_line(uint8_t line) {
    // These pins do two things
    //  1) Use an optocoupler to disable the line that is currently being pulled high
    //  2) Pull the selected line high
    printf("A0:%d A1:%d A2:%d", line & 0b001, line & 0b010, line & 0b100);
    gpio_set_level(SEL_A0, line & 0b001);
    gpio_set_level(SEL_A1, line & 0b010);
    gpio_set_level(SEL_A2, line & 0b100);
}


uint8_t check_correct(test_result_t r) {
    // Check if shorted
    if (r.dir == 0b11)
        return 0;

    // Move dir for easy mask checking
    switch(r.tx) {
        case 0b10000000:
        case 0b01000000:
            r.dir = r.dir << 6;
            break;
        case 0b00100000:
        case 0b00010000:
            r.dir = r.dir << 4;
            break;
        case 0b00001000:
        case 0b00000100:
            r.dir = r.dir << 2;
            break;
        case 0b00000010:
        case 0b00000001:
            break;
    }

    // Confirm correct return path and pair not flipped
    return (r.dir | r.tx) == r.rx;
}


void test_all_pins(test_result_t results[8]) {
    // Test each pin and put the result into the results buffer passed in
    for (int i=0; i<8; ++i) {
        results[i] = test_pin(i);
    }
}


