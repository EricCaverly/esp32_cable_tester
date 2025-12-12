#include "ssd1306.h"
#include "tester.h"
#include "sdkconfig.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

SSD1306_t screen_handle;

void init_display(void) {
    i2c_master_init(&screen_handle, SDA, SCL, CONFIG_RESET_GPIO);
    ssd1306_init(&screen_handle, DISP_WIDTH, DISP_HEIGHT);
    ssd1306_contrast(&screen_handle, 0xff);
    ssd1306_clear_screen(&screen_handle, false);
}

void reset_display() {
    ssd1306_clear_screen(&screen_handle, false);
}

void display_text(char* text, int line) {
    ssd1306_display_text(&screen_handle, line, text, strlen(text), false);
    printf("Displaying: %s\n", text);
}

void binary_print(uint8_t num) {
    printf("0b");
    for (int i=7; i>=0; --i) {
        printf("%d", (num>>i)&1);
    }
}

void display_results(test_result_t results[8]) {
    ssd1306_clear_screen(&screen_handle, false);
    for (int i=0; i<8; ++i) {

        printf("Line %d | TX:", i);
        binary_print(results[i].tx);
        printf(" | RX:");
        binary_print(results[i].rx);
        printf(" | DIR: ");
        binary_print(results[i].dir);
        printf(" | Correct: %d\n", check_correct(results[i]));
        
        if (check_correct(results[i]))
            display_text("OK", i);
        else {
            display_text("Fault", i);
        }
    }    
}