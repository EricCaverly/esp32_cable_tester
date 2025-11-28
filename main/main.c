#include "tester.h"
#include <stdbool.h>

volatile bool testing = false;

void app_main(void) {
    init_display();
    init_adc();
    init_gpio();
    init_button();
    reset_display();
}


