#include "ssd1306.h"
#include "tester.h"
#include "sdkconfig.h"

SSD1306_t screen_handle;

void init_display(void) {
    i2c_master_init(&screen_handle, SDA, SCL, CONFIG_RESET_GPIO);
    ssd1306_init(&screen_handle, DISP_WIDTH, DISP_HEIGHT);
    ssd1306_contrast(&screen_handle, 0xff);
    ssd1306_clear_screen(&screen_handle, false);
}

void reset_display() {
    ssd1306_clear_screen(&screen_handle, false);
    ssd1306_display_text(&screen_handle, 0, "Press Test", 5, false);
}