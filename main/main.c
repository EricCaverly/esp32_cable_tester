#include "driver/gpio.h"
#include "freertos/idf_additions.h"
#include "portmacro.h"
#include "tester.h"

void app_main(void) {
    int i = 0;
    init_gpio();

    while (1) {
        printf("Disabling wire %d\n", i);
        disable_line(i);
        vTaskDelay(1 * 1000 / portTICK_PERIOD_MS);
        if (++i >= 8) i = 0;
    }
}