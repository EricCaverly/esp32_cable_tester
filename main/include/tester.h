#include "esp_adc/adc_oneshot.h"
#include "ssd1306.h"
#include <stdint.h>

#define SEL_A0 GPIO_NUM_16
#define SEL_A1 GPIO_NUM_18
#define SEL_A2 GPIO_NUM_19

#define RJ45_P0 GPIO_NUM_13
#define RJ45_P1 GPIO_NUM_12
#define RJ45_P2 GPIO_NUM_14
#define RJ45_P3 GPIO_NUM_27
#define RJ45_P4 GPIO_NUM_26
#define RJ45_P5 GPIO_NUM_25
#define RJ45_P6 GPIO_NUM_33
#define RJ45_P7 GPIO_NUM_32

#define SCL GPIO_NUM_22
#define SDA GPIO_NUM_21
#define DISP_WIDTH 128
#define DISP_HEIGHT 64

#define TEST_BTN_PIN GPIO_NUM_34

#define TAG "tester"

typedef struct {
    uint8_t tx;
    uint8_t rx;
    uint8_t dir;
} test_result_t;

extern volatile bool testing;
extern const uint8_t g_lines[];

extern adc_oneshot_unit_handle_t adc2_handle;
extern SSD1306_t screen_handle;

void init_gpio();
void init_display(void);
void init_adc(void);
void init_button(void);

void reset_display();
void display_text(char* text, int line);
void display_results(test_result_t results[8]);

void select_line(uint8_t line);
void test_all_pins(test_result_t results[8]);
void tst_button_pressed(void*, void*);

test_result_t test_pin(uint8_t line);
uint8_t check_correct(test_result_t r);

