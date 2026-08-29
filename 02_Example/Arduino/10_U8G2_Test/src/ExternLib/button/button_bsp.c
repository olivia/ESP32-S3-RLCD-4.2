#include <stdio.h>
#include <driver/gpio.h>
#include <esp_log.h>
#include <esp_timer.h>
#include "button_bsp.h"
#include "multi_button.h"

EventGroupHandle_t BootButtonGroups;
EventGroupHandle_t GP18ButtonGroups;
EventGroupHandle_t TLButtonGroups;
EventGroupHandle_t TRButtonGroups;
EventGroupHandle_t BLButtonGroups;
EventGroupHandle_t BRButtonGroups;
int switchState[] = {1,1,1,1};


static Button BootButton;   // Application button
#define BOOT_KEY_PIN 0      // Actual GPIO
#define BOOT_ID 1           // Button ID
#define BOOT_Active 0       // Valid level

static Button GP18Button; 
#define GP18_KEY_PIN 18    
#define GP18_ID 2         
#define GP18_Active 0       

static Button TLButton; 
static Button TRButton; 
static Button BLButton; 
static Button BRButton; 
#define BR_ID 0         
#define TR_ID 1         
#define TL_ID 2         
#define BL_ID 3         

/*******************Callback event declaration***************/
static void on_tl_single_click(Button *btn_handle) {
    xEventGroupSetBits(TLButtonGroups, set_bit_button(0));
}

static void on_tl_double_click(Button *btn_handle) {
    xEventGroupSetBits(TLButtonGroups, set_bit_button(1));
}

static void on_tl_long_press_start(Button *btn_handle) {
    xEventGroupSetBits(TLButtonGroups, set_bit_button(2));
}
static void on_tr_single_click(Button *btn_handle) {
    xEventGroupSetBits(TRButtonGroups, set_bit_button(0));
}

static void on_tr_double_click(Button *btn_handle) {
    xEventGroupSetBits(TRButtonGroups, set_bit_button(1));
}

static void on_tr_long_press_start(Button *btn_handle) {
    xEventGroupSetBits(TRButtonGroups, set_bit_button(2));
}
static void on_bl_single_click(Button *btn_handle) {
    xEventGroupSetBits(BLButtonGroups, set_bit_button(0));
}

static void on_bl_double_click(Button *btn_handle) {
    xEventGroupSetBits(BLButtonGroups, set_bit_button(1));
}

static void on_bl_long_press_start(Button *btn_handle) {
    xEventGroupSetBits(BLButtonGroups, set_bit_button(2));
}
static void on_br_single_click(Button *btn_handle) {
    xEventGroupSetBits(BRButtonGroups, set_bit_button(0));
}

static void on_br_double_click(Button *btn_handle) {
    xEventGroupSetBits(BRButtonGroups, set_bit_button(1));
}

static void on_br_long_press_start(Button *btn_handle) {
    xEventGroupSetBits(BRButtonGroups, set_bit_button(2));
}

static void on_boot_single_click(Button *btn_handle) {
    xEventGroupSetBits(BootButtonGroups, set_bit_button(0));
}

static void on_boot_double_click(Button *btn_handle) {
    xEventGroupSetBits(BootButtonGroups, set_bit_button(1));
}

static void on_boot_long_press_start(Button *btn_handle) {
    xEventGroupSetBits(BootButtonGroups, set_bit_button(2));
}

static void on_gp18_single_click(Button *btn_handle) {
    xEventGroupSetBits(GP18ButtonGroups, set_bit_button(0));
}

static void on_gp18_double_click(Button *btn_handle) {
    xEventGroupSetBits(GP18ButtonGroups, set_bit_button(1));
}

static void on_gp18_long_press_start(Button *btn_handle) {
    xEventGroupSetBits(GP18ButtonGroups, set_bit_button(2));
}



/*********************************************/

static void clock_task_callback(void *arg) {
    button_ticks();
}

static uint8_t read_button_multiplexer(uint8_t Button_ID) {
    return switchState[Button_ID];
}

static uint8_t read_button_GPIO(uint8_t Button_ID) {
    switch (Button_ID) {
    case BOOT_ID:
        return gpio_get_level(BOOT_KEY_PIN);
    case GP18_ID:
        return gpio_get_level(GP18_KEY_PIN);
    default:
        break;
    }
    return 1;
}

static void gpio_init(void) {
    gpio_config_t gpio_conf = {};
    gpio_conf.intr_type     = GPIO_INTR_DISABLE;
    gpio_conf.mode          = GPIO_MODE_INPUT;
    gpio_conf.pin_bit_mask  = (0x1ULL << BOOT_KEY_PIN) | (0x1ULL << GP18_KEY_PIN);
    gpio_conf.pull_down_en  = GPIO_PULLDOWN_DISABLE;
    gpio_conf.pull_up_en    = GPIO_PULLUP_ENABLE;

    ESP_ERROR_CHECK_WITHOUT_ABORT(gpio_config(&gpio_conf));
}

void Custom_ButtonInit(void) {
    BootButtonGroups = xEventGroupCreate();
    GP18ButtonGroups = xEventGroupCreate();
    gpio_init();

    button_init(&BootButton, read_button_GPIO, BOOT_Active, BOOT_ID);           // Initialization: Initialize object, callback function, trigger level, key ID
    button_attach(&BootButton, BTN_SINGLE_CLICK, on_boot_single_click);         // Single click event
    button_attach(&BootButton, BTN_DOUBLE_CLICK, on_boot_double_click);         // Double click event
    button_attach(&BootButton, BTN_LONG_PRESS_START, on_boot_long_press_start); // Long press event

    button_init(&GP18Button, read_button_GPIO, BOOT_Active, GP18_ID);           
    button_attach(&GP18Button, BTN_SINGLE_CLICK, on_gp18_single_click);         
    button_attach(&GP18Button, BTN_DOUBLE_CLICK, on_gp18_double_click);         
    button_attach(&GP18Button, BTN_LONG_PRESS_START, on_gp18_long_press_start);

    esp_timer_create_args_t clock_tick_timer_args = {};
    clock_tick_timer_args.callback                = &clock_task_callback;
    clock_tick_timer_args.name                    = "clock_task";
    clock_tick_timer_args.arg                     = NULL;
    esp_timer_handle_t clock_tick_timer           = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&clock_tick_timer_args, &clock_tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(clock_tick_timer, 1000 * 2)); // 5ms
    button_start(&BootButton);
    button_start(&GP18Button);
}

void Multiplexer_ButtonInit(void) {
    TLButtonGroups = xEventGroupCreate();
    TRButtonGroups = xEventGroupCreate();
    BLButtonGroups = xEventGroupCreate();
    BRButtonGroups = xEventGroupCreate();

    button_init(&TLButton, read_button_multiplexer, BOOT_Active, TL_ID);           
    button_attach(&TLButton, BTN_SINGLE_CLICK, on_tl_single_click);         
    //button_attach(&TLButton, BTN_DOUBLE_CLICK, on_tl_double_click);         
    button_attach(&TLButton, BTN_LONG_PRESS_START, on_tl_long_press_start);

    button_init(&TRButton, read_button_multiplexer, BOOT_Active, TR_ID);           
    button_attach(&TRButton, BTN_SINGLE_CLICK, on_tr_single_click);         
    //button_attach(&TRButton, BTN_DOUBLE_CLICK, on_tr_double_click);         
    button_attach(&TRButton, BTN_LONG_PRESS_START, on_tr_long_press_start);

    button_init(&BRButton, read_button_multiplexer, BOOT_Active, BR_ID);           
    button_attach(&BRButton, BTN_SINGLE_CLICK, on_br_single_click);         
    button_attach(&BRButton, BTN_DOUBLE_CLICK, on_br_double_click);         
    button_attach(&BRButton, BTN_LONG_PRESS_START, on_br_long_press_start);

    button_init(&BLButton, read_button_multiplexer, BOOT_Active, BL_ID);           
    button_attach(&BLButton, BTN_SINGLE_CLICK, on_bl_single_click);         
    //button_attach(&BLButton, BTN_DOUBLE_CLICK, on_bl_double_click);         
    button_attach(&BLButton, BTN_LONG_PRESS_START, on_bl_long_press_start);
    button_start(&TLButton);
    button_start(&TRButton);
    button_start(&BRButton);
    button_start(&BLButton);
}

uint8_t user_boot_get_repeat_count(void) {
    return (button_get_repeat_count(&BootButton));
}
