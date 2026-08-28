#include "display_bsp.h"
#include "src/app_bsp/lvgl_bsp.h"
#include "src/ExternLib/button/button_bsp.h"
#include "lvgl.h" 
#include "src/ui/ui.h"
#include "i2c_bsp.h"
#include "codec_bsp.h"
#include "ST7305_U8g2.h"
#include <esp_timer.h>
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
//static int switchState[] = {0,0,0,0};
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
  int64_t t_start = esp_timer_get_time();
  int pixel_count = 0;
  uint16_t *buffer = (uint16_t *)color_map;
  for (int y = area->y1; y <= area->y2; y++) {
    for (int x = area->x1; x <= area->x2; x++) {
      uint8_t color = (*buffer < 0x7fff) ? ColorBlack : ColorWhite;
      RlcdPort.RLCD_SetPixel(x, y, color);
      buffer++;
            pixel_count++;

    }
  }
    int64_t t_math_done = esp_timer_get_time();

  RlcdPort.RLCD_Display();
    int64_t t_spi_done = esp_timer_get_time();
  int32_t math_ms = (int32_t)(t_math_done - t_start) / 1000;
  int32_t spi_ms  = (int32_t)(t_spi_done - t_math_done) / 1000;
  int32_t total_ms = (int32_t)(t_spi_done - t_start) / 1000;

  // Print results to the serial terminal every 30 frames
  // static int diagnostic_counter = 0;
  // if (++diagnostic_counter >= 30) {
  //   diagnostic_counter = 0;
  //   Serial.printf("[DIAGNOSTIC] Window: (%d,%d) to (%d,%d) | Total Pixels: %d\n", 
  //          area->x1, area->y1, area->x2, area->y2, pixel_count);
  //   Serial.printf("             -> Loop Processing Math : %d ms\n", math_ms);
  //   Serial.printf("             -> SPI Bus Transmission : %d ms\n", spi_ms);
  //   Serial.printf("             -> Total Driver Staging : %d ms\n", total_ms);
  // }

  lv_disp_flush_ready(drv);
}




//s0-3
int selectPins[] =
{
0,1,2,3
};

int signalPin = 17;

int n = sizeof(selectPins)/sizeof(selectPins[0]);


bool modalOpen = false;

void BOOT_LoopTask(void *arg) {
  for (;;) {
    EventBits_t even = xEventGroupWaitBits(BootButtonGroups, (0x01 | 0x02 | 0x04), pdTRUE, pdFALSE, pdMS_TO_TICKS(2000));
    if (even & 0x01) {
    } else if (even & 0x02) {
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
       Serial.println("Press button");
      is_Music = true;
      xEventGroupSetBits(CodecGroups, 0x04);
    } else if (even & 0x02) {
      is_Music = true;
      Serial.println("Press other button");
      xEventGroupSetBits(CodecGroups, 0x04);
    }
  }
}

void TL_LoopTask(void *arg) {
  for (;;) {
    EventBits_t even = xEventGroupWaitBits(TLButtonGroups, (0x01 | 0x02 | 0x04), pdTRUE, pdFALSE, pdMS_TO_TICKS(2000));
    if (even & 0x01) {
      Serial.println("TL Click");
    } else if (even & 0x02) {
      Serial.println("TL DClick");
      if (Lvgl_lock(-1)) {
        lv_obj_t * current_screen = lv_screen_active();
        uint32_t pressed_key = LV_KEY_NEXT;
        lv_obj_send_event(current_screen, LV_EVENT_KEY, &pressed_key);
        Lvgl_unlock();

      }
    } else if (even & 0x04) {
      if (Lvgl_lock(-1)) {
        lv_obj_set_style_transform_rotation(ui_modalcontainer,1800, LV_PART_MAIN| LV_STATE_DEFAULT);
        lv_obj_update_layout(ui_modalcontainer); 

        Lvgl_unlock();
      }
    }
  }
}

void TR_LoopTask(void *arg) {
  for (;;) {
    
    EventBits_t even = xEventGroupWaitBits(TRButtonGroups, (0x01 | 0x02 | 0x04), pdTRUE, pdFALSE, pdMS_TO_TICKS(2000));

    if (even & 0x01) {
          Serial.println("TR Click");

      if (Lvgl_lock(-1)) {
        lv_obj_t * current_screen = lv_screen_active();
        lv_obj_t * next_screen = NULL;

        // 1. Identify which screen is currently on the display
        if (current_screen == ui_Screen1) {
            next_screen = ui_Screen2;
        } 
        else if (current_screen == ui_Screen2) {
            next_screen = ui_Screen1;
        } 
        // 2. Perform the safe transition if a target was found
        if (next_screen != NULL) {
          lv_screen_load_anim(next_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);
        }

        Lvgl_unlock();
      }
    } else if (even & 0x02) {
      Serial.println("TR Double Click");

    } else if (even & 0x04) {
      if (Lvgl_lock(-1)) {
        lv_obj_set_style_transform_rotation(ui_modalcontainer,2700, LV_PART_MAIN| LV_STATE_DEFAULT);
            lv_obj_update_layout(ui_modalcontainer); 

        Lvgl_unlock();
      }
    }
  }
}
void BR_LoopTask(void *arg) {
  for (;;) {
    EventBits_t even = xEventGroupWaitBits(BRButtonGroups, (0x01 | 0x02 | 0x04), pdTRUE, pdFALSE, pdMS_TO_TICKS(2000));
    if (even & 0x01) {
      Serial.println("BR Click");
    } else if (even & 0x02) {
      Serial.println("BR DClick");
    } else if (even & 0x04) {
      modalOpen = !modalOpen;
      if (Lvgl_lock(-1)) {
        lv_obj_set_style_transform_rotation(ui_modalcontainer,0, LV_PART_MAIN| LV_STATE_DEFAULT);

        if (modalOpen) {
          floatup_Animation(ui_modal,0);
        } else {
          floatdown_Animation(ui_modal, 0);
        }
        Lvgl_unlock();
      }
    }
  }
}

void BL_LoopTask(void *arg) {
  for (;;) {
    EventBits_t even = xEventGroupWaitBits(BLButtonGroups, (0x01 | 0x02 | 0x04), pdTRUE, pdFALSE, pdMS_TO_TICKS(2000));
    if (even & 0x01) {
      Serial.println("BL Click");
    } else if (even & 0x02) {
      Serial.println("BL DClick");
    } else if (even & 0x04) {
      if (Lvgl_lock(-1)) {
        lv_obj_set_style_transform_rotation(ui_modalcontainer,900, LV_PART_MAIN| LV_STATE_DEFAULT);
            lv_obj_update_layout(ui_modalcontainer); 

        Lvgl_unlock();
      }
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
    SensorState_t currState = (rawValue > 1000) ? STATE_STABLE_DARK : currentStateArr[sensor_id];
    bool stateChange = false;
    if (prevState == STATE_STABLE_COVERED && currState == STATE_STABLE_DARK) {
      currentStateArr[sensor_id] = currState;
      stateChange = true;
    }
    else if (prevState != STATE_STABLE_COVERED && rawValue < 250 && (lastTriggered[sensor_id] + 1000 * 1) < currTime) {
        is_Music = true;
            Serial.println("playing the muse");

        currState = STATE_STABLE_COVERED;
        currentStateArr[sensor_id] = currState;
        lastTriggered[sensor_id] = currTime;
        xEventGroupSetBits(CodecGroups, 1 << sensor_id);
        stateChange = true;


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
      switchState[i-12] = analogRead(signalPin)>2048;
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
    int riichi_count = 0; 
    for (int i=0; i<4;i++) {
        lv_obj_t * cui_player;
        lv_obj_t * riichi_icon;
        switch(i) {
            case 0:
                cui_player = ui_player4;
                break;
            case 1:
                cui_player = ui_player3;
                break;
            case 2:
                cui_player = ui_player1;
                break;
            case 3:
                cui_player = ui_player2;
                break;
            default:
                cui_player = ui_player1;
        }
        riichi_icon = ui_comp_get_child(cui_player, UI_COMP_PLAYER_PANEL9_RIICHI);
        if (!lv_obj_has_flag(riichi_icon, LV_OBJ_FLAG_HIDDEN) && currentStateArr[i] != STATE_STABLE_COVERED ) {
          lv_obj_add_flag(riichi_icon, LV_OBJ_FLAG_HIDDEN);

        } else if (lv_obj_has_flag(riichi_icon, LV_OBJ_FLAG_HIDDEN)&& currentStateArr[i] == STATE_STABLE_COVERED ) {
          lv_obj_remove_flag(riichi_icon, LV_OBJ_FLAG_HIDDEN);
        }
        riichi_count += (currentStateArr[i] == STATE_STABLE_COVERED) ? 1 : 0;
    }
        // "Player" (6) + Number (1) + Null terminator (1) = 8 bytes needed
    char result[3]; 

    // Concatenate safely
    snprintf(result, sizeof(result), "%s%d", "x", riichi_count);
    lv_label_set_text(ui_Label5,result);



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



void setupBarTimers() {
 lv_timer_create(bar1_update_cb, 80, ui_Bar1);
}

void setupPlayers() {
  lv_label_set_text(ui_comp_get_child(ui_player1, UI_COMP_PLAYER_PANEL9_CONTAINER_NAME), "olivia");
  lv_label_set_text(ui_comp_get_child(ui_player1, UI_COMP_PLAYER_PANEL9_PANEL8_WIND), "東");
  lv_label_set_text(ui_comp_get_child(ui_player4, UI_COMP_PLAYER_PANEL9_CONTAINER_NAME), "stephen");
  lv_label_set_text(ui_comp_get_child(ui_player4, UI_COMP_PLAYER_PANEL9_PANEL8_WIND), "南");
  lv_label_set_text(ui_comp_get_child(ui_player3, UI_COMP_PLAYER_PANEL9_CONTAINER_NAME), "jay");
  lv_label_set_text(ui_comp_get_child(ui_player3, UI_COMP_PLAYER_PANEL9_PANEL8_WIND), "西");
  lv_label_set_text(ui_comp_get_child(ui_player2, UI_COMP_PLAYER_PANEL9_CONTAINER_NAME), "porrith");
  lv_label_set_text(ui_comp_get_child(ui_player2, UI_COMP_PLAYER_PANEL9_PANEL8_WIND), "北");
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

   Lvgl_PortInit(300, 300, Lvgl_FlushCallback);
     Serial.println("attempting lvgl");

   if (Lvgl_lock(-1)) {
    ui_init();
    setupPlayers();
    setupBarTimers();
    Lvgl_unlock();

   }

  

  last_report_ms = millis();
  CodecGroups = xEventGroupCreate();
  Custom_ButtonInit();
  Multiplexer_ButtonInit();
  codecport = new CodecPort(I2cbus, "S3_RLCD_4_2");
  codecport->CodecPort_SetInfo("es8311 & es7210", 1, 16000, 2, 16);
  codecport->CodecPort_SetSpeakerVol(100);
  codecport->CodecPort_SetMicGain(35);
  //xTaskCreatePinnedToCore(BOOT_LoopTask, "BOOT_LoopTask", 4 * 1024, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(KEY_LoopTask, "KEY_LoopTask", 4 * 1024, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(TL_LoopTask, "TL_LoopTask", 4 * 1024, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(TR_LoopTask, "TR_LoopTask", 4 * 1024, NULL, 2, NULL, 1);

  xTaskCreatePinnedToCore(BR_LoopTask, "BR_LoopTask", 4 * 1024, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(BL_LoopTask, "BL_LoopTask", 4 * 1024, NULL, 2, NULL, 1);

  xTaskCreatePinnedToCore(Codec_LoopTask, "Codec_LoopTask", 4 * 1024, NULL, 4, NULL, 1);
  xTaskCreatePinnedToCore(SENSOR_LoopTask, "SENSOR_LoopTask", 4 * 1024, NULL, 4, NULL, 1);

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

}
