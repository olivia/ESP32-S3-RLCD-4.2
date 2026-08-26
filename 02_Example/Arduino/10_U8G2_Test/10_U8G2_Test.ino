#include "display_bsp.h"
#include "src/app_bsp/lvgl_bsp.h"
#include "src/ExternLib/button/button_bsp.h"
#include "lvgl.h" 
#include "src/ui/ui.h"
#include "i2c_bsp.h"
#include "codec_bsp.h"
#include "ST7305_U8g2.h"
#include "maru.c"
#define U8G2_USE_LARGE_FONTS
#define LCD_WIDTH 400
#define LCD_HEIGHT 300

#define RLCD_SCK_PIN 11
#define RLCD_MOSI_PIN 12
#define RLCD_DC_PIN 5
#define RLCD_CS_PIN 40
#define RLCD_RST_PIN 41
// static lv_ui init_ui;


static ST7305_U8g2 lcd(RLCD_SCK_PIN, RLCD_MOSI_PIN, RLCD_DC_PIN, RLCD_CS_PIN, RLCD_RST_PIN);
static U8G2 *u8g2 = nullptr;
static int switchState[] = {0,0,0,0};
static int lightState[] = {0,0,0,0};

static uint32_t counter = 0;
static uint32_t frames = 0;
static uint32_t last_report_frames = 0;
static uint32_t last_report_ms = 0;
static uint32_t fps_x100 = 0;
static uint32_t frame_us = 0;
static uint32_t flush_us = 0;
static int tCX = 80;
static int tCY = 30;
static int bCX = 320;
static int bCY = 267;
static int CIRCLE_RAD = 20;
I2cMasterBus I2cbus(14, 13, 0);
CodecPort *codecport = NULL;
static uint8_t *audio_ptr = NULL;
static bool is_Music = true;
EventGroupHandle_t CodecGroups;

DisplayPort RlcdPort(12, 11, 5, 40, 41, 400, 300);

static void Lvgl_FlushCallback(lv_display_t *drv, const lv_area_t *area, uint8_t *color_map) {
  uint16_t *buffer = (uint16_t *)color_map;
  for (int y = area->y1; y <= area->y2; y++) {
    for (int x = area->x1; x <= area->x2; x++) {
      uint8_t color = (*buffer < 0x7fff) ? ColorBlack : ColorWhite;
      RlcdPort.RLCD_SetPixel(x, y, color);
      buffer++;
    }
  }
  RlcdPort.RLCD_Display();
  lv_disp_flush_ready(drv);
}



static void drawCenteredUTF8X2(int y, const char *text)
{
  int text_width = u8g2->getUTF8Width(text);
  int x = (240 - text_width*2) / 2;
  if (x < 0) {
    x = 0;
  }
  u8g2->drawUTF8X2(x+tCX, y, text);
}

static void drawCenteredStr(int y, const char *text)
{
  int text_width = u8g2->getStrWidth(text);
  int x = (LCD_WIDTH - text_width) / 2;
  if (x < 0) {
    x = 0;
  }
  u8g2->drawStr(x, y, text);
}

//s0-3
int selectPins[] =
{
0,1,2,3
};

int signalPin = 17;

int n = sizeof(selectPins)/sizeof(selectPins[0]);

// Global variable for your input device
lv_indev_t * indev_keypad;

void gpio_keypad_read_cb(lv_indev_t * indev, lv_indev_data_t * data) {
  data->state = LV_INDEV_STATE_RELEASED; // Default state

  const uint32_t target_keys[] = {
    LV_KEY_NEXT,
    LV_KEY_PREV,
    LV_KEY_UP,
    LV_KEY_DOWN
  };

  for(int i=0; i<4; i++)
  {
    if (switchState[i]) {
        data->state = LV_INDEV_STATE_PRESSED;
        data->key = target_keys[i];
        uint32_t pressed_key = LV_KEY_NEXT;
        
        // CHANGED: lv_scr_act() is replaced by lv_screen_active() in v9
lv_obj_t * current_screen = lv_screen_active();
lv_obj_send_event(current_screen, LV_EVENT_KEY, &pressed_key);
        break; // Added break to stop checking once a pressed key is handled
    } else {
      data->state = LV_INDEV_STATE_RELEASED;
    }
  }
}

void init_gpio_input(void) {
    // 1. CHANGED: Directly create the input device object
    indev_keypad = lv_indev_create();
    
    // 2. CHANGED: Configure the input device using specific setter functions
    lv_indev_set_type(indev_keypad, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev_keypad, gpio_keypad_read_cb);

    // 3. Create an object group and assign it to the input device
    lv_group_t * g = lv_group_create();
    lv_indev_set_group(indev_keypad, g);

    // Add the PANEL widget inside the screen
    lv_group_add_obj(g, ui_Panel1); 
    lv_group_focus_obj(ui_Panel1);
    lv_group_focus_freeze(g, true); 
}




void BOOT_LoopTask(void *arg) {
  for (;;) {
    EventBits_t even = xEventGroupWaitBits(BootButtonGroups, (0x01 | 0x02 | 0x04), pdTRUE, pdFALSE, pdMS_TO_TICKS(2000));
    if (even & 0x01) {
      xEventGroupSetBits(CodecGroups, 0x02);
    } else if (even & 0x02) {
      xEventGroupSetBits(CodecGroups, 0x01);
    }
  }
}

void Codec_LoopTask(void *arg) {
  bool is_eco = 0;
  for (;;) {
    EventBits_t even = xEventGroupWaitBits(CodecGroups, (0x01 | 0x02 | 0x04| 0x08), pdTRUE, pdFALSE, pdMS_TO_TICKS(8 * 1000));
    if (even) 
      {
      int indexArgs = even;
      int index = 0;
      while (indexArgs > 0 && (indexArgs & 0x01) != 1) {
        index++;
        indexArgs >>= 1;
      }
      
      codecport->CodecPort_SetSpeakerVol(90);
      uint32_t bytes_sizt;
      size_t bytes_write = 0;
      Serial.printf("attempting to get %d", index);
      uint8_t *data_ptr = codecport->CodecPort_GetPcmData(&bytes_sizt, index);
      while (bytes_write < bytes_sizt) {
        codecport->CodecPort_PlayWrite(data_ptr, 256);
        data_ptr += 256;
        bytes_write += 256;
        if (!is_Music)
          break;
      }
      codecport->CodecPort_SetSpeakerVol(100);
    } else {
    }
  }
}

void KEY_LoopTask(void *arg) {
  for (;;) {
    EventBits_t even = xEventGroupWaitBits(GP18ButtonGroups, (0x01 | 0x02 | 0x04), pdTRUE, pdFALSE, pdMS_TO_TICKS(2000));
    if (even & 0x01) {
      // is_Music = false;
      // Serial.println("Press button");
      is_Music = true;
      xEventGroupSetBits(CodecGroups, 0x04);
    } else if (even & 0x02) {
      is_Music = true;
      Serial.println("Press other button");
      xEventGroupSetBits(CodecGroups, 0x04);
    }
  }
}
#define LIGHT_SENSORS_COUNT 4
typedef enum {
    STATE_STABLE_COVERED       = 5, // Light is low and steady (covered)

    STATE_STABLE_DARK       = 0, // Light is low and steady (covered)
    STATE_STABLE_BRIGHT     = 1, // Light is high and steady (uncovered)
    STATE_RAPID_COVERING    = 2, // Signal is plunging sharply (hand dropping over it)
    STATE_RAPID_UNCOVERING  = 3, // Signal is spiking sharply (hand lifting away)
    STATE_GRADUAL_CHANGING  = 4  // Signal is moving slowly (room lights dimming/brightening)
} SensorState_t;




// Filter histories (shifted left by 8 bits for fixed-point math)
static int32_t emaFastScaledArr[LIGHT_SENSORS_COUNT] = { -1, -1, -1, -1 }; 
static int32_t emaSlowScaledArr[LIGHT_SENSORS_COUNT] = { -1, -1, -1, -1 };

// State tracking histories for edge detection
static SensorState_t currentStateArr[LIGHT_SENSORS_COUNT] = { STATE_STABLE_DARK, STATE_STABLE_DARK, STATE_STABLE_DARK, STATE_STABLE_DARK };
static SensorState_t previousStateArr[LIGHT_SENSORS_COUNT] = { STATE_STABLE_DARK, STATE_STABLE_DARK, STATE_STABLE_DARK, STATE_STABLE_DARK };


uint16_t stableSettleCounterArr[LIGHT_SENSORS_COUNT] = {0,0,0,0};
unsigned long lastTriggered[LIGHT_SENSORS_COUNT] = {0,0,0,0};

bool isArmedArr[LIGHT_SENSORS_COUNT] = {false,false,false,false}; // Tracks if a sensor is primed to fire
void processLightSensor(int rawValue, int sensor_id) {
    long currTime = millis();
    SensorState_t prevState = currentStateArr[sensor_id];
    SensorState_t currState = (rawValue > 400) ? STATE_STABLE_DARK : currentStateArr[sensor_id];
    if (prevState == STATE_STABLE_COVERED && currState == STATE_STABLE_DARK) {
      currentStateArr[sensor_id] = currState;
    }
    else if (prevState != STATE_STABLE_COVERED && rawValue < 175 && (lastTriggered[sensor_id] + 1000 * 1) < currTime) {
        is_Music = true;
            Serial.println("playing the muse");

        currState = STATE_STABLE_COVERED;
        currentStateArr[sensor_id] = currState;
        lastTriggered[sensor_id] = currTime;
        xEventGroupSetBits(CodecGroups, 1 << sensor_id);
    }
    previousStateArr[sensor_id] = currState;
    
}

void SENSOR_LoopTask(void *arg) {
  const TickType_t xSettleDelay = pdMS_TO_TICKS(1); // 1ms for hardware stabilization
  const TickType_t xLoopDelay = pdMS_TO_TICKS(50);  // 50ms cycle rate for the whole task

  for (;;) {
    for(int i=12; i<16; i++)
    {
    
      int s0 = (i>>0)&1;
      int s1 = (i>>1)&1;
      int s2 = (i>>2)&1;
      int s3 = (i>>3)&1;
      digitalWrite(selectPins[0], s0);
      digitalWrite(selectPins[1], s1);
      digitalWrite(selectPins[2], s2);
      digitalWrite(selectPins[3], s3);
      vTaskDelay(xSettleDelay);
      switchState[i-12] = analogRead(signalPin)<2048;
    }
    for(int i=8; i<12; i++)
    {
      int s0 = (i>>0)&1;
      int s1 = (i>>1)&1;
      int s2 = (i>>2)&1;
      int s3 = (i>>3)&1;
      digitalWrite(selectPins[0], s0);
      digitalWrite(selectPins[1], s1);
      digitalWrite(selectPins[2], s2);
      digitalWrite(selectPins[3], s3);
      vTaskDelay(xSettleDelay);
      int rawVal = analogRead(signalPin);
      lightState[i-8] = floor(180.0*rawVal/4095.0);
      
      processLightSensor(rawVal, i-8);
    }
  }
}

static void bar1_update_cb(lv_timer_t * timer) {
    lv_bar_set_value(ui_Bar1, lightState[0], LV_ANIM_ON); 
    lv_bar_set_value(ui_Bar2, lightState[1], LV_ANIM_ON); 
    lv_bar_set_value(ui_Bar3, lightState[2], LV_ANIM_ON); 
    lv_bar_set_value(ui_Bar4, lightState[3], LV_ANIM_ON); 

}

static void bar2_update_cb(lv_timer_t * timer) {
lv_obj_t * bar = (lv_obj_t *)lv_timer_get_user_data(timer);
    // Replace 'new_value' with your actual data source (e.g., sensor reading)
    lv_bar_set_value(ui_Bar2, lightState[1], LV_ANIM_OFF); 
}

static void bar3_update_cb(lv_timer_t * timer) {
lv_obj_t * bar = (lv_obj_t *)lv_timer_get_user_data(timer);
    // Replace 'new_value' with your actual data source (e.g., sensor reading)
    lv_bar_set_value(ui_Bar3, lightState[2], LV_ANIM_OFF); 
}

static void bar4_update_cb(lv_timer_t * timer) {
lv_obj_t * bar = (lv_obj_t *)lv_timer_get_user_data(timer);
    // Replace 'new_value' with your actual data source (e.g., sensor reading)
    lv_bar_set_value(ui_Bar4, lightState[3], LV_ANIM_OFF); 
}


const char* const utf8Labels[] = {
  "東 1", 
  "東 2",   
  "東 3",   
  "東 4", 
  "南 1", 
  "南 2",   
  "南 3",   
  "南 4"
};

const int labelCount = sizeof(utf8Labels) / sizeof(utf8Labels[0]);
unsigned long previousMillis = 0; 
const unsigned long interval = 2000; // Interval in milliseconds (1 second)



void DISPLAY_LoopTask(void *arg) {
    
  for (;;) {
    char text[80];
    uint32_t frame_start_us = micros();
    int round = (millis() % (interval* labelCount))/2000;
    int rotateOffset = round&3;


    u8g2->clearBuffer();


    int number_height = u8g2->getAscent() - u8g2->getDescent();
    int number_y = ((LCD_HEIGHT - number_height) / 2) + u8g2->getAscent();
    // drawCenteredStr(number_y, text);

    u8g2->setFont(u8g2_font_ncenB08_tr);	// choose a suitable font

    //u8g2->drawFrame(80, 10, 290, 290);

    u8g2->setFont(u8g2_font_6x13_tf);
    // drawCenteredStr(number_y + 26, "ST7305 refresh counter");
    // snprintf(text, sizeof(text), "FPS:%lu.%02lu  frame:%lums  flush:%lums",
    //          (unsigned long)(fps_x100 / 100),
    //          (unsigned long)(fps_x100 % 100),
    //          (unsigned long)(frame_us / 1000),
    //          (unsigned long)(flush_us / 1000));
    
    // u8g2->drawStr(20, 282, text);
    //vertical
    u8g2->drawFrame(60, 60, 10, 180);
    u8g2->drawFrame(330, 60, 10, 180);
    //horizontal
    u8g2->drawFrame(110, 10, 180, 10);
    u8g2->drawFrame(110, 277, 180, 10);


    //vertical
    u8g2->drawBox(60, 60, 10, lightState[3]);
    u8g2->setCursor(80,100);
    u8g2->print( currentStateArr[3]);

    u8g2->drawBox(330, 60, 10, lightState[0]);
        u8g2->setCursor(310,100);

    u8g2->print( currentStateArr[0]);
    //horizontal
    u8g2->drawBox(110, 10, lightState[1],10);
        u8g2->setCursor(200,20);

    u8g2->print( currentStateArr[1]);

    u8g2->drawBox(110, 277, lightState[2],10);
    u8g2->setCursor(200,250);
    u8g2->print( currentStateArr[2]);


    if (switchState[0]) {
      u8g2->drawDisc(bCX, bCY, CIRCLE_RAD);
    } else {
      u8g2->drawCircle(bCX, bCY, CIRCLE_RAD);
    }
    if (switchState[1]) {
      u8g2->drawDisc(bCX, tCY, CIRCLE_RAD);
    } else {
      u8g2->drawCircle(bCX, tCY, CIRCLE_RAD);
    }

    if (switchState[2]) {
      u8g2->drawDisc(tCX, tCY, CIRCLE_RAD);
    } else {
      u8g2->drawCircle(tCX, tCY, CIRCLE_RAD);
    }
    if (switchState[3]) {
      u8g2->drawDisc(tCX, bCY, CIRCLE_RAD);
    } else {
      u8g2->drawCircle(tCX, bCY, CIRCLE_RAD);
    }

    u8g2->setDrawColor(2);
    u8g2->setFontMode(1);  /* activate transparent font mode */

    int offset = 7;
    int directions[] = {0x6771,0x5357,0x897F,0x5317};
    snprintf(text, sizeof(text), "%lu", (unsigned long)counter);
    u8g2->setFont(maru8g2); 
    // u8g2->setFont(u8g2_font_unifont_t_chinese2); 
    u8g2->setFontDirection(0);
    // East
    u8g2->drawGlyph(bCX-offset, bCY+offset, directions[(8-rotateOffset)&3]);
    u8g2->setFontDirection(3);

    // South
    u8g2->drawGlyph(bCX+offset, tCY+offset, directions[((8-rotateOffset+1)&3)]);
      u8g2->setFontDirection(2);

    // West
    u8g2->drawGlyph(tCX+offset, tCY-offset, directions[(8-rotateOffset+2)&3]);
      u8g2->setFontDirection(1);

    // North
    u8g2->drawGlyph(tCX-offset, bCY-offset, directions[(8-rotateOffset+3)&3]);
      u8g2->setFontDirection(0);

    u8g2->setDrawColor(1);

    drawCenteredUTF8X2((tCY+bCY)/2, utf8Labels[round]);

    u8g2->setFontMode(0);  /* activate transparent font mode */




    uint32_t flush_start_us = micros();
    u8g2->sendBuffer();
    uint32_t now_us = micros();

    flush_us = now_us - flush_start_us;
    frame_us = now_us - frame_start_us;
    counter++;
    frames++;

    uint32_t now_ms = millis();
    uint32_t elapsed_ms = now_ms - last_report_ms;
    if (elapsed_ms >= 1000) {
      uint32_t delta_frames = frames - last_report_frames;
      fps_x100 = (uint32_t)((uint64_t)delta_frames * 100000ULL / elapsed_ms);
      /*
      Serial.printf("counter=%lu fps=%lu.%02lu frame=%lu us flush=%lu us\r\n",
                    (unsigned long)counter,
                    (unsigned long)(fps_x100 / 100),
                    (unsigned long)(fps_x100 % 100),
                    (unsigned long)frame_us,
                    (unsigned long)flush_us);
      */
      last_report_ms = now_ms;
      last_report_frames = frames;
    }

    if ((frames % 16) == 0) {
      delay(1);
    } else {
      yield();
    }
  }
}
void setupBarTimers() {
  lv_timer_create(bar1_update_cb, 80, ui_Bar1);
}

void setup()
{
  audio_ptr = (uint8_t *)heap_caps_malloc(288 * 1000 * sizeof(uint8_t), MALLOC_CAP_SPIRAM);
  assert(audio_ptr);
  Serial.begin(115200);
  Serial.println("Hello world");
  delay(300);


   RlcdPort.RLCD_Init();
     Serial.println("attempting port");

   Lvgl_PortInit(400, 300, Lvgl_FlushCallback);
     Serial.println("attempting lvgl");

   if (Lvgl_lock(-1)) {
    ui_init();
    //init_gpio_input();  
    //setupBarTimers();
    Lvgl_unlock();

   }

  
  // lcd.begin(0, U8G2_R1);
  //  u8g2 = lcd.getU8g2();
  // u8g2->enableUTF8Print(); 

  last_report_ms = millis();
  CodecGroups = xEventGroupCreate();
  Custom_ButtonInit();
  codecport = new CodecPort(I2cbus, "S3_RLCD_4_2");
  codecport->CodecPort_SetInfo("es8311 & es7210", 1, 16000, 2, 16);
  codecport->CodecPort_SetSpeakerVol(100);
  codecport->CodecPort_SetMicGain(35);
  xTaskCreatePinnedToCore(BOOT_LoopTask, "BOOT_LoopTask", 4 * 1024, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(KEY_LoopTask, "KEY_LoopTask", 4 * 1024, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(Codec_LoopTask, "Codec_LoopTask", 4 * 1024, NULL, 4, NULL, 1);
  xTaskCreatePinnedToCore(SENSOR_LoopTask, "SENSOR_LoopTask", 4 * 1024, NULL, 4, NULL, 1);
  //xTaskCreatePinnedToCore(DISPLAY_LoopTask, "DISPLAY_LoopTask", 5 * 1024, NULL, 4, NULL,1);

  for(int i=0; i<n; i++)
  {
    pinMode(selectPins[i],OUTPUT);
  }

  Serial.println("ST7305 U8g2 counter demo started");
}
void loopSwitches() {
  
  for(int i=12; i<16; i++)
  {
  
    int s0 = (i>>0)&1;
    int s1 = (i>>1)&1;
    int s2 = (i>>2)&1;
    int s3 = (i>>3)&1;
    digitalWrite(selectPins[0], s0);
    digitalWrite(selectPins[1], s1);
    digitalWrite(selectPins[2], s2);
    digitalWrite(selectPins[3], s3);
    delay(10);
    switchState[i-12] = analogRead(signalPin)<2048;
  }
}

void loopLightsensors() {
    for(int i=8; i<12; i++)
  {
  
    int s0 = (i>>0)&1;
    int s1 = (i>>1)&1;
    int s2 = (i>>2)&1;
    int s3 = (i>>3)&1;
    digitalWrite(selectPins[0], s0);
    digitalWrite(selectPins[1], s1);
    digitalWrite(selectPins[2], s2);
    digitalWrite(selectPins[3], s3);
    delay(10);

    lightState[i-8] = floor(180.0*analogRead(signalPin)/4095.0);
  }
}

void loop()
{
  lv_timer_handler();
  vTaskDelay(pdMS_TO_TICKS(100));
  //loopSwitches();
  //loopLightsensors();

}
