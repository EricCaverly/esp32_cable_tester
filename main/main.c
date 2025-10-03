#include "esp_adc/adc_oneshot.h"
#include "freertos/idf_additions.h"
#include "hal/adc_types.h"
#include "portmacro.h"
#include "sdkconfig.h"
#include "soc/adc_channel.h"
#include "tester.h"
#include "ssd1306.h"
#include <stdbool.h>

void app_main(void) {
    int i = 0;
    SSD1306_t dev;
    int adc_v = 0;

    // Initialize the display
    i2c_master_init(&dev, SDA, SCL, CONFIG_RESET_GPIO);
    ssd1306_init(&dev, DISP_WIDTH, DISP_HEIGHT);
    ssd1306_contrast(&dev, 0xff);
    ssd1306_clear_screen(&dev, false);

    // Initialize the ADC
    adc_oneshot_unit_handle_t adc2_handle;
    adc_oneshot_unit_init_cfg_t init_cfg = {
        .unit_id = ADC_UNIT_2,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    adc_oneshot_new_unit(&init_cfg, &adc2_handle);
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc2_handle, ADC2_GPIO15_CHANNEL, &config));

    // Initialize GPIO for testing cables
    init_gpio();

    //! Test the display, remove later
    ssd1306_display_text(&dev, 0, "Hello", 5, false);

    while (1) {
        
        adc_oneshot_read(adc2_handle, ADC2_GPIO15_CHANNEL, &adc_v);
        printf("\nRaw Value: %f\n", (adc_v/4095.0)*3.3);

        printf("Disabling wire %d\n", i);
        disable_line(i);
        vTaskDelay(1 * 1000 / portTICK_PERIOD_MS);
        if (++i >= 8) i = 0;
    }
}