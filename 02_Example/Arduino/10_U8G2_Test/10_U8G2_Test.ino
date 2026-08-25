#include "src/ExternLib/button/button_bsp.h"
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
    EventBits_t even = xEventGroupWaitBits(CodecGroups, (0x01 | 0x02 | 0x04), pdTRUE, pdFALSE, pdMS_TO_TICKS(8 * 1000));
    if (even & 0x01) {
      //codecport->CodecPort_EchoRead(audio_ptr, 192 * 1000);
      is_eco = 1;
    } else if (even & 0x02) {
      if (1 == is_eco) {
        is_eco = 0;
        codecport->CodecPort_PlayWrite(audio_ptr, 192 * 1000);
          Serial.println("Play music");

      }
    } else if (even & 0x04) {
      codecport->CodecPort_SetSpeakerVol(90);
      uint32_t bytes_sizt;
      size_t bytes_write = 0;
      uint8_t *data_ptr = codecport->CodecPort_GetPcmData(&bytes_sizt);
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
bool isArmedArr[LIGHT_SENSORS_COUNT] = {false,false,false,false}; // Tracks if a sensor is primed to fire
void processLightSensor(int rawValue, int sensor_id) {
    int32_t emaFastScaled = emaFastScaledArr[sensor_id]; 
    int32_t emaSlowScaled = emaSlowScaledArr[sensor_id];
    
    // 1. Grab the last known settled state
    SensorState_t previousState = currentStateArr[sensor_id];
    SensorState_t currentState = previousState;

    // 2. Filter Initializer
    int32_t rawScaled = (int32_t)rawValue << 8; 
    if (emaFastScaled < 0) {
        emaFastScaledArr[sensor_id] = rawScaled;
        emaSlowScaledArr[sensor_id] = rawScaled;
        currentStateArr[sensor_id] = STATE_STABLE_BRIGHT;
        return;
    }

    // 3. Math Calculations
    emaFastScaled = emaFastScaled + ((rawScaled - emaFastScaled) >> 2); 
    emaSlowScaled = emaSlowScaled + ((rawScaled - emaSlowScaled) >> 6); 

    int emaFast = emaFastScaled >> 8;
    int emaSlow = emaSlowScaled >> 8;
    int delta = emaFast - emaSlow;

    // 4. --- STATE EVALUATION WITH INTEGRATED DEBOUNCE ---
    if (delta < -150) { 
        currentState = STATE_RAPID_COVERING;
        stableSettleCounterArr[sensor_id] = 0; // Reset counter: value is still actively falling
    } 
    else if (delta > 150) {
        currentState = STATE_RAPID_UNCOVERING;
        stableSettleCounterArr[sensor_id] = 0; // Reset counter: value is still actively spiking
    } 
    else if (abs(delta) < 50) { 
        // Delta is small, increment the confirmation check timer
        stableSettleCounterArr[sensor_id]++;

        // 🌟 DEBOUNCE REQUIREMENT: Must stay flat for 15 execution loops to count as stable
        if (stableSettleCounterArr[sensor_id] >= 15) {
            if (emaSlow > 2500) { 
                currentState = STATE_STABLE_BRIGHT;
            } else {
                currentState = STATE_STABLE_DARK;
            }
        } else {
            // Keep the previous state (e.g. RAPID_COVERING) while we wait for verification
            currentState = previousState; 
        }
    } 
    else {
        // If it lands in the middle zone (50-150), let it linger without triggering anything
        stableSettleCounterArr[sensor_id] = 0; 
    }

    // 5. --- THE FIXED EDGE DETECTOR ---
    // Will now only trigger when transitioning out of a fully debounced state change
    if (previousState == STATE_RAPID_COVERING && currentState == STATE_STABLE_DARK) {
        is_Music = true;
        xEventGroupSetBits(CodecGroups, 0x04);
    }
    
    // 6. Global Save Updates
    emaFastScaledArr[sensor_id] = emaFastScaled;
    emaSlowScaledArr[sensor_id] = emaSlowScaled;
    currentStateArr[sensor_id] = currentState;
    previousStateArr[sensor_id] = previousState;
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

void setup()
{
  audio_ptr = (uint8_t *)heap_caps_malloc(288 * 1000 * sizeof(uint8_t), MALLOC_CAP_SPIRAM);
  assert(audio_ptr);
  Serial.begin(115200);
  delay(300);

  lcd.begin(0, U8G2_R1);
  u8g2 = lcd.getU8g2();

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
  xTaskCreatePinnedToCore(DISPLAY_LoopTask, "SENSOR_LoopTask", 5 * 1024, NULL, 4, NULL,1);

  for(int i=0; i<n; i++)
  {
    pinMode(selectPins[i],OUTPUT);
  }
  u8g2->enableUTF8Print(); 

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
  //loopSwitches();
  //loopLightsensors();

}
