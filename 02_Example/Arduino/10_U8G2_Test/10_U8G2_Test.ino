#include "display_bsp.h"
#include "src/app_bsp/lvgl_bsp.h"
#include "src/ExternLib/button/button_bsp.h"
#include "lvgl.h" 
#include "src/ui/ui.h"
#include "src/ui/ui_helpers.h"

#include "i2c_bsp.h"
#include "codec_bsp.h"
#include "ST7305_U8g2.h"
#include <esp_timer.h>
#include "src/gif/Roll6.c"


#define U8G2_USE_LARGE_FONTS
#define LCD_WIDTH 400
#define LCD_HEIGHT 300
#define EAST_WIND_STR "東"
#define SOUTH_WIND_STR "南"
#define WEST_WIND_STR "西"
#define NORTH_WIND_STR "北"
#define RLCD_SCK_PIN 11
#define RLCD_MOSI_PIN 12
#define RLCD_DC_PIN 5
#define RLCD_CS_PIN 40
#define RLCD_RST_PIN 41
// static lv_ui init_ui;
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define MED_MODAL_CONTENT_HEIGHT 125

static lv_subject_t br_name_subject;
static char curr_br_name_text_buffer[128];
static char prev_br_name_text_buffer[128];

static lv_subject_t br_wind_subject;
static char curr_br_wind_text_buffer[128];
static char prev_br_wind_text_buffer[128];

static lv_subject_t br_score_subject;

static lv_subject_t tr_name_subject;
static char curr_tr_name_text_buffer[128];
static char prev_tr_name_text_buffer[128];

static lv_subject_t tr_wind_subject;
static char curr_tr_wind_text_buffer[128];
static char prev_tr_wind_text_buffer[128];

static lv_subject_t tr_score_subject;

static lv_subject_t tl_name_subject;
static char curr_tl_name_text_buffer[128];
static char prev_tl_name_text_buffer[128];


static lv_subject_t tl_wind_subject;
static char curr_tl_wind_text_buffer[128];
static char prev_tl_wind_text_buffer[128];

static lv_subject_t tl_score_subject;

static lv_subject_t bl_name_subject;
static char curr_bl_name_text_buffer[128];
static char prev_bl_name_text_buffer[128];


static lv_subject_t bl_wind_subject;
static char curr_bl_wind_text_buffer[128];
static char prev_bl_wind_text_buffer[128];
static lv_subject_t bl_score_subject;


static lv_subject_t modal_title_subject;
static char curr_modal_title_text_buffer[128];
static char prev_modal_title_text_buffer[128];

static lv_subject_t selectoption_subject;
static char curr_selectoption_text_buffer[128];
static char prev_selectoption_text_buffer[128];

static lv_subject_t optiondescription_subject;
static char curr_optiondescription_text_buffer[128];
static char prev_optiondescription_text_buffer[128];

static lv_subject_t honbacount_subject;
static lv_subject_t doracount_subject;


static lv_subject_t * subject_scores[] = {&br_score_subject, &tr_score_subject, &tl_score_subject, &bl_score_subject}; 
static lv_subject_t * subject_winds[] = {&br_wind_subject, &tr_wind_subject, &tl_wind_subject, &bl_wind_subject}; 


static int rotationIndex = 0;
static int modalContentStep = -1;
static ST7305_U8g2 lcd(RLCD_SCK_PIN, RLCD_MOSI_PIN, RLCD_DC_PIN, RLCD_CS_PIN, RLCD_RST_PIN);
static U8G2 *u8g2 = nullptr;
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
static int modal_state = 0;
I2cMasterBus I2cbus(14, 13, 0);
CodecPort *codecport = NULL;
static uint8_t *audio_ptr = NULL;
static bool is_Music = true;
EventGroupHandle_t CodecGroups;
static bool showSensors = false;
lv_obj_t * modalContentWinArr[9];

typedef enum {
  WT_RON = 0,
  WT_TSUMO = 1,
  WT_DRAW = 2,
  WT_NONE = -1
} WinType_t;


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


static void anim_rotation_cb(lv_obj_t * obj, int32_t v)
{
    lv_obj_set_style_transform_rotation(obj, v, 0);
}



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

// ESWN
char* discarders[] = {"apple", "banana", "cherry", "dewberry"};
char* winds[] = {EAST_WIND_STR, SOUTH_WIND_STR, WEST_WIND_STR, NORTH_WIND_STR}; 

char* validHan[] = {"1", "2", "3", "4", "5", "6", "7","8", "9", "10", "11", "12", "Y", "2XY", "3XY", "4XY"}; 
int hanBase[] = {8, 16, 32, 64, 2000, 3000, 3000, 4000, 4000, 4000, 6000, 6000, 8000, 16000, 24000, 32000 };
int fuMultiplier[] = {20,25,30,40,50,60,70,80,90,100,110, 1};
char* validFu[] = {"20", "25", "30", "40", "50", "60", "70","80", "90", "100", "110"}; 
#define TENPAISTATUSMODAL_INDEX 5
bool modalStepVisited[] = {
false, false, false, false, false, 
// TENPAI MODALS
false,false,false,false};
#define PLAYER_NUM 4
char* tenpaiModalOptions[] = {"NOTEN", "TENPAI"};
bool playerTenpaiFlags[] = {false, false, false, false};

static int hanIndex = 0;
static int fuIndex = 0;
static int discarderIndex = 0;
// starting from bottom right going counterclockwise
static int scoreOffsets[] = {0, 0, 0, 0};

bool modalOpen = false;
static WinType_t winType = WT_NONE;
static int seatRotationNum = 0;
static int honbaCount = 0;
static int carryoverDora = 0;
static int currentDoraCount = 0;


int playersInTenpai() {
  int tenpaiPlayers = 0;
  for (int i=0; i< PLAYER_NUM; i++) {
    tenpaiPlayers += playerTenpaiFlags[i];
  }  
  return tenpaiPlayers;
}

int calcTenpaiPayments() {
  int payments[] = {0, 3000, 1500, 1000, 0};
  return payments[playersInTenpai()];
}

int _scores[] = {
  25000, 25000, 25000, 25000
};

void setupObservers() {
  lv_subject_init_string(&br_name_subject, curr_br_name_text_buffer, prev_br_name_text_buffer, sizeof(curr_br_name_text_buffer), discarders[0]);
  lv_subject_init_string(&tr_name_subject, curr_tr_name_text_buffer, prev_tr_name_text_buffer, sizeof(curr_tr_name_text_buffer), discarders[1]);
  lv_subject_init_string(&tl_name_subject, curr_tl_name_text_buffer, prev_tl_name_text_buffer, sizeof(curr_tl_name_text_buffer), discarders[2]);
  lv_subject_init_string(&bl_name_subject, curr_bl_name_text_buffer, prev_bl_name_text_buffer, sizeof(curr_bl_name_text_buffer), discarders[3]);
  lv_subject_init_string(&modal_title_subject, curr_modal_title_text_buffer, prev_modal_title_text_buffer, sizeof(curr_modal_title_text_buffer), "DRAW");
  lv_subject_init_string(&selectoption_subject, curr_selectoption_text_buffer, prev_selectoption_text_buffer, sizeof(curr_selectoption_text_buffer), tenpaiModalOptions[0]);
  lv_subject_init_string(&optiondescription_subject, curr_optiondescription_text_buffer, prev_optiondescription_text_buffer, sizeof(curr_optiondescription_text_buffer), discarders[0]);

  //scores
  for (int i = 0; i < 4; i++) {
    lv_subject_init_int(subject_scores[i], _scores[i]);
  } 
  lv_subject_init_int(&honbacount_subject, 0);
  lv_subject_init_int(&doracount_subject, 0);

  //cui_offset_score = ui_comp_get_child(cui_player, UI_COMP_PLAYER_PANEL30_OFFSETSCORE);


  lv_label_bind_text(ui_comp_get_child(ui_player1, UI_COMP_PLAYER_CONTAINER_NAME), &br_name_subject, "%s");
  lv_label_bind_text(ui_comp_get_child(ui_player1, UI_COMP_PLAYER_PANEL8_SCORE), &br_score_subject, "%d");

  lv_label_bind_text(ui_comp_get_child(ui_player2, UI_COMP_PLAYER_CONTAINER_NAME),&tr_name_subject, "%s");
  lv_label_bind_text(ui_comp_get_child(ui_player2, UI_COMP_PLAYER_PANEL8_SCORE), &tr_score_subject, "%d");

  lv_label_bind_text(ui_comp_get_child(ui_player3, UI_COMP_PLAYER_CONTAINER_NAME), &tl_name_subject, "%s");
  lv_label_bind_text(ui_comp_get_child(ui_player3, UI_COMP_PLAYER_PANEL8_SCORE), &tl_score_subject, "%d");

  lv_label_bind_text(ui_comp_get_child(ui_player4, UI_COMP_PLAYER_CONTAINER_NAME), &bl_name_subject, "%s");
  lv_label_bind_text(ui_comp_get_child(ui_player4, UI_COMP_PLAYER_PANEL8_SCORE), &bl_score_subject, "%d");
  
  lv_label_bind_text(ui_modaltitle, &modal_title_subject, "%s");
  lv_label_bind_text(ui_selectoption, &selectoption_subject, "%s");
  lv_label_bind_text(ui_optiondescription, &optiondescription_subject, "%s");
  lv_label_bind_text(ui_doracount, &doracount_subject, "%d");
  lv_label_bind_text(ui_honbacount, &honbacount_subject, "%d");
}

typedef struct _anim_user_data_t {
    lv_obj_t *target;
    lv_image_dsc_t **imgset;
    int32_t imgset_size;
    int32_t val;
} anim_user_data_t;



// IMAGES AND IMAGE SETS
const lv_image_dsc_t *ui_imgset_roll_6_frame__[5] = {&ui_img_roll_6_frame_0_png, &ui_img_roll_6_frame_1_png, &ui_img_roll_6_frame_2_png, &ui_img_roll_6_frame_3_png, &ui_img_roll_6_frame_8_png};
const lv_image_dsc_t *ui_imgset_roll_5_frame__[5] = {&ui_img_roll_6_frame_0_png, &ui_img_roll_6_frame_1_png, &ui_img_roll_6_frame_2_png, &ui_img_roll_6_frame_3_png, &ui_img_roll_5_frame_7_png};
const lv_image_dsc_t *ui_imgset_roll_4_frame__[5] = {&ui_img_roll_6_frame_0_png, &ui_img_roll_6_frame_1_png, &ui_img_roll_6_frame_2_png, &ui_img_roll_6_frame_3_png, &ui_img_roll_4_frame_7_png};
const lv_image_dsc_t *ui_imgset_roll_3_frame__[5] = {&ui_img_roll_6_frame_0_png, &ui_img_roll_6_frame_1_png, &ui_img_roll_6_frame_2_png, &ui_img_roll_6_frame_3_png, &ui_img_roll_3_frame_7_png};
const lv_image_dsc_t *ui_imgset_roll_2_frame__[5] = {&ui_img_roll_6_frame_0_png, &ui_img_roll_6_frame_1_png, &ui_img_roll_6_frame_2_png, &ui_img_roll_6_frame_3_png, &ui_img_roll_2_frame_7_png};
const lv_image_dsc_t *ui_imgset_roll_1_frame__[5] = {&ui_img_roll_6_frame_0_png, &ui_img_roll_6_frame_1_png, &ui_img_roll_6_frame_2_png, &ui_img_roll_6_frame_3_png, &ui_img_roll_1_frame_7_png};
const lv_image_dsc_t *ui_imgset_roll_6_inv_frame__[5] = {&ui_img_roll_6_inv_frame_0_png, &ui_img_roll_6_inv_frame_1_png, &ui_img_roll_6_inv_frame_2_png, &ui_img_roll_6_inv_frame_3_png, &ui_img_roll_6_inv_frame_8_png};
const lv_image_dsc_t *ui_imgset_roll_5_inv_frame__[5] = {&ui_img_roll_6_inv_frame_0_png, &ui_img_roll_6_inv_frame_1_png, &ui_img_roll_6_inv_frame_2_png, &ui_img_roll_6_inv_frame_3_png, &ui_img_roll_5_inv_frame_7_png};
const lv_image_dsc_t *ui_imgset_roll_4_inv_frame__[5] = {&ui_img_roll_6_inv_frame_0_png, &ui_img_roll_6_inv_frame_1_png, &ui_img_roll_6_inv_frame_2_png, &ui_img_roll_6_inv_frame_3_png, &ui_img_roll_4_inv_frame_7_png};
const lv_image_dsc_t *ui_imgset_roll_3_inv_frame__[5] = {&ui_img_roll_6_inv_frame_0_png, &ui_img_roll_6_inv_frame_1_png, &ui_img_roll_6_inv_frame_2_png, &ui_img_roll_6_inv_frame_3_png, &ui_img_roll_3_inv_frame_7_png};
const lv_image_dsc_t *ui_imgset_roll_2_inv_frame__[5] = {&ui_img_roll_6_inv_frame_0_png, &ui_img_roll_6_inv_frame_1_png, &ui_img_roll_6_inv_frame_2_png, &ui_img_roll_6_inv_frame_3_png, &ui_img_roll_2_inv_frame_7_png};
const lv_image_dsc_t *ui_imgset_roll_1_inv_frame__[5] = {&ui_img_roll_6_inv_frame_0_png, &ui_img_roll_6_inv_frame_1_png, &ui_img_roll_6_inv_frame_2_png, &ui_img_roll_6_inv_frame_3_png, &ui_img_roll_1_inv_frame_7_png};


const lv_image_dsc_t **allRolls[] = {ui_imgset_roll_6_frame__,ui_imgset_roll_5_frame__,ui_imgset_roll_4_frame__,ui_imgset_roll_3_frame__,ui_imgset_roll_2_frame__,ui_imgset_roll_1_frame__};
const lv_image_dsc_t **allRollsInv[] = {ui_imgset_roll_6_inv_frame__,ui_imgset_roll_5_inv_frame__,ui_imgset_roll_4_inv_frame__,ui_imgset_roll_3_inv_frame__,ui_imgset_roll_2_inv_frame__,ui_imgset_roll_1_inv_frame__};
///////////////////// ANIMATIONS ////////////////////


 void anim_x_cb(void * var, int32_t v) {
    lv_obj_set_x((lv_obj_t *)var, v);
}

 void anim_y_cb(void * var, int32_t v) {
    lv_obj_set_y((lv_obj_t *)var, v);
}

/**
 * Create a playback animation
 */
void anim_x(void)
{
    lv_obj_t * obj = ui_diecontainer;
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_values(&a, 10, 50);
    lv_anim_set_duration(&a, 1000);
    lv_anim_set_repeat_count(&a, 0);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);
    lv_anim_set_exec_cb(&a, anim_x_cb);
    lv_anim_set_values(&a, -20, 0);
    lv_anim_start(&a);
}

/**
 * Create a playback animation
 */
void anim_y(void)
{
    lv_obj_t * obj = ui_diecontainer;
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_values(&a, 10, 50);
    lv_anim_set_duration(&a, 1000);
    lv_anim_set_repeat_count(&a, 0);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);
    lv_anim_set_exec_cb(&a, anim_y_cb);
    lv_anim_set_values(&a, 20, 0);
    lv_anim_start(&a);
}

void anim_callback_set_image_frame(lv_anim_t* a, int32_t v)
{
    int newV;
    ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
    int lastIndex = usr->imgset_size - 1;
    int map[] = {128, 256};
    newV = v;
    usr->val = v;
    if ( v<0 ) {
      v=0;
    }
    newV = v >= 20 ? lastIndex : v % lastIndex;
    lv_image_set_src(usr->target, usr->imgset[newV]);
}

lv_anim_t * rollany_Animation( lv_obj_t *TargetObject, lv_image_dsc_t **imgSet ,int delay)
{
lv_anim_t *out_anim;
anim_user_data_t *PropertyAnimation_0_user_data = (anim_user_data_t *)lv_malloc(sizeof(anim_user_data_t));
PropertyAnimation_0_user_data->target = TargetObject;
PropertyAnimation_0_user_data->imgset = imgSet;
PropertyAnimation_0_user_data->imgset_size = sizeof(ui_imgset_roll_6_frame__)/(sizeof(lv_image_dsc_t*));
PropertyAnimation_0_user_data->val = -1;
lv_anim_t PropertyAnimation_0;
lv_anim_init(&PropertyAnimation_0);
lv_anim_set_duration(&PropertyAnimation_0, 1000);
lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
lv_anim_set_custom_exec_cb(&PropertyAnimation_0, anim_callback_set_image_frame );
lv_anim_set_values(&PropertyAnimation_0, 0, 21 );
lv_anim_set_path_cb( &PropertyAnimation_0, lv_anim_path_linear);
lv_anim_set_delay( &PropertyAnimation_0, delay + 0 );
lv_anim_set_deleted_cb( &PropertyAnimation_0, _ui_anim_callback_free_user_data );
lv_anim_set_reverse_duration(&PropertyAnimation_0, 0);
lv_anim_set_reverse_delay(&PropertyAnimation_0, 0);
 lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
lv_anim_set_early_apply( &PropertyAnimation_0, false );
 lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_image_frame );
out_anim = lv_anim_start(&PropertyAnimation_0);

return out_anim;
}

lv_anim_t *activeDieAnimation;
lv_anim_t *activeDieInvAnimation;


void rollGifs(int location) {
  if (activeDieAnimation) {
    lv_anim_del_all();
  }


  int coords[] = {0,88, 88, 0, 0, -88, -88, 0};
  int width= 91;
  int height = 29;

  lv_image_set_src(ui_Image21, &ui_img_roll_6_frame_0_png);
  lv_image_set_src(ui_Image22, &ui_img_roll_6_inv_frame_0_png);

  int random_num_i = random(0, 6);
  int random_num_j = random(0, 6);;
  lv_obj_add_flag(ui_diecontainer, LV_OBJ_FLAG_HIDDEN);
  if (location % 2) {
    lv_obj_set_flex_flow(ui_diecontainer, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_width(ui_diecontainer, height);
    lv_obj_set_height(ui_diecontainer, width);

  } else {
    lv_obj_set_flex_flow(ui_diecontainer, LV_FLEX_FLOW_ROW);
    lv_obj_set_width(ui_diecontainer, width);
    lv_obj_set_height(ui_diecontainer, height);
  }

  lv_obj_set_x(ui_diecontainer,coords[location * 2]);
  lv_obj_set_y(ui_diecontainer,coords[location * 2 + 1]);


  if (location % 2) {
    anim_y();
  } else {
    anim_x();
  }
  activeDieAnimation = rollany_Animation(ui_Image21,(lv_image_dsc_t **)allRolls[random_num_i],0);
  activeDieInvAnimation = rollany_Animation(ui_Image22,(lv_image_dsc_t **)allRollsInv[random_num_j],100);
  lv_obj_remove_flag(ui_diecontainer, LV_OBJ_FLAG_HIDDEN);
}

void resetModalStepHistory() {
  size_t length = sizeof(modalStepVisited) / sizeof(modalStepVisited[0]);
  for (int i = 0; i< length; i++) {
    modalStepVisited[i] = false;
  }
  modalContentStep = -1;
}


bool isUpgradedMangan(int hanIndex, int fuIndex) {
  return (hanIndex == 3 && fuIndex >= 3 ) || (hanIndex == 2 && fuIndex >= 6);
}

bool isDealer(int index) {

  return index == (seatRotationNum & 3);
}

int getHandScore(int hanIndex, int fuIndex) {
  int multiplier = isDealer(rotationIndex) ? 6 : 4;
  if (hanIndex >= 4) {
    return multiplier * hanBase[hanIndex]; 
  } else if (isUpgradedMangan(hanIndex, fuIndex)){
    return multiplier * hanBase[4];
  } else {
    return multiplier * fuMultiplier[fuIndex] * hanBase[hanIndex]; 
  }
}

int roundScore(int score) {
  int scoreOffset = score % 100 ? 1: 0;
  int flooredScore = score/100;
  return 100 * (flooredScore + scoreOffset);
}

void applyTsumoOffsets(int playerId, int dealerScore, int nonDealerScore ) {
  int doraScore = lv_subject_get_int(&doracount_subject) * 1000;
  for (int i = 0; i < 4; i++) {
    if (playerId == i) {
      scoreOffsets[i] = doraScore + dealerScore + nonDealerScore * 2;
    } else {
      scoreOffsets[i] = ((isDealer(i)) ? -dealerScore : -nonDealerScore); 
    }
  }
}

void setupStepValues(int step) {
  if (step < 4 && step >= 0) {
    lv_subject_copy_string(&modal_title_subject, discarders[rotationIndex]);
  } else if (step >= TENPAISTATUSMODAL_INDEX && step < TENPAISTATUSMODAL_INDEX + 4) {
    lv_subject_copy_string(&modal_title_subject, "DRAW");
    lv_subject_copy_string(&optiondescription_subject, discarders[(step - TENPAISTATUSMODAL_INDEX + rotationIndex) & 3]);
    lv_subject_copy_string(&selectoption_subject, tenpaiModalOptions[playerTenpaiFlags[step- TENPAISTATUSMODAL_INDEX]]);
  }
  else if (step == 4) {
    lv_subject_copy_string(&modal_title_subject, "RESULTS");
    if (winType == WT_DRAW) {
      lv_obj_add_flag(ui_handscore, LV_OBJ_FLAG_HIDDEN);
    } else if (hanIndex >= 4) {
      lv_obj_remove_flag(ui_scoredescription, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_fucontainerdetail, LV_OBJ_FLAG_HIDDEN);
    } else {
      lv_obj_remove_flag(ui_scoredescription, LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(ui_funumdetail, LV_OBJ_FLAG_HIDDEN);
      lv_label_set_text(ui_funumdetail, validFu[fuIndex]);
    }
    lv_label_set_text(ui_handetails, validHan[hanIndex]);

    if (!isDealer(rotationIndex) && winType == WT_TSUMO) {
      lv_obj_remove_flag(ui_auxpayerdetail, LV_OBJ_FLAG_HIDDEN);
    } else {
      lv_obj_add_flag(ui_auxpayerdetail, LV_OBJ_FLAG_HIDDEN);
    }
    int score = getHandScore(hanIndex,fuIndex);
    int doraScore = lv_subject_get_int(&doracount_subject) * 1000;
    int honbaScore = lv_subject_get_int(&honbacount_subject) * 300;
    int indivHonbaScore = honbaScore / 3;
    if (winType == WT_RON) {
      // RON
      char payerScore[100];
      int payerScoreNum = roundScore(score) + honbaScore;
      sprintf(payerScore, "%d", payerScoreNum);
      scoreOffsets[rotationIndex] = payerScoreNum + doraScore;
      scoreOffsets[discarderIndex] = -payerScoreNum;
      lv_label_set_text(ui_payernamedetail, discarders[discarderIndex]);
      lv_label_set_text(ui_payerscoredetail, payerScore);
    } else if (winType == WT_TSUMO && isDealer(rotationIndex)) {
      // DEALER TSUMO
      char payerScore[100];
      int payerScoreNum = roundScore(score/3) + indivHonbaScore;
      applyTsumoOffsets(rotationIndex, payerScoreNum, payerScoreNum);
      sprintf(payerScore, "%d", payerScoreNum);
      lv_label_set_text(ui_payernamedetail, "ALL");
      lv_label_set_text(ui_payerscoredetail, payerScore);

    } else if (winType == WT_TSUMO && !isDealer(rotationIndex)) {
      char dealerScore[100];
      char nonDealerScore[100];
      int nonDealerScoreNum = roundScore(score/4) + indivHonbaScore;
      int dealerScoreNum = roundScore(score/2) + indivHonbaScore;
      applyTsumoOffsets(rotationIndex, dealerScoreNum, nonDealerScoreNum);
      sprintf(dealerScore, "%d", dealerScoreNum);
      sprintf(nonDealerScore, "%d", nonDealerScoreNum);
      // NON-DEALER TSUMO
      lv_label_set_text(ui_payernamedetail, "DEALER");
      lv_label_set_text(ui_auxpayernamedetail, "NON-DEALER");
      lv_label_set_text(ui_payerscoredetail, dealerScore);
      lv_label_set_text(ui_auxpayerscoredetail, nonDealerScore);
    } else if (winType == WT_DRAW) {
      // DRAW
      int negPayments[] = {0, -1000, -1500, -3000, 0};
      int posPayments[] = {0, 3000, 1500, 1000, 0};
      int tenpaiNum = playersInTenpai();
      char payerScore[100];
      sprintf(payerScore, "%d", -negPayments[tenpaiNum]);

      lv_label_set_text(ui_payernamedetail, "NOTEN");
      lv_label_set_text(ui_payerscoredetail, payerScore);

      for (int i = 0; i < 4; i++) {
        scoreOffsets[(rotationIndex+i)&3] = playerTenpaiFlags[i] ? posPayments[tenpaiNum] : negPayments[tenpaiNum];
      }
    }
    repaintPlayers();
  }
  
}
void initStepValues(int step) {
  switch (step) {
    case 1: 
      hanIndex = 0;
      lv_label_set_text(ui_hancount, validHan[hanIndex]);
      break;
    case 2:
      fuIndex = 2;
      lv_label_set_text(ui_fucount, validFu[fuIndex]);
      break;
    case 3:
      discarderIndex = (rotationIndex +1) & 3;
      lv_label_set_text(ui_discarder, discarders[discarderIndex]);
      break;
    case 4:
      break;
    case 5:
    case 6:
    case 7:
    case 8:
      playerTenpaiFlags[step- TENPAISTATUSMODAL_INDEX] = 0;
    break;

    default:
      break;
  }
}

void setRotation(int rotIdx) {
  rotationIndex = rotIdx;
  lv_obj_set_style_transform_rotation(ui_modalcontainer,(3600 - 900 * rotIdx) % 3600, LV_PART_MAIN| LV_STATE_DEFAULT);
  lv_obj_update_layout(ui_modalcontainer); 
}

void transitionToStep(int nextStep) {
  lv_obj_t * prevStepUI = getModalStepContent(modalContentStep);
  lv_obj_t * nextStepUI = getModalStepContent(nextStep);
  if (prevStepUI) {
    lv_obj_add_flag(prevStepUI, LV_OBJ_FLAG_HIDDEN);
  }
  if (!nextStepUI) {
    setModalVisibility(false);
    resetModalStepHistory();
  } else {
    lv_obj_remove_flag(nextStepUI, LV_OBJ_FLAG_HIDDEN);
  }
  modalContentStep = nextStep;
  if (!modalStepVisited[nextStep] && nextStep >= 0) {
    initStepValues(nextStep);
    modalStepVisited[nextStep] = true;
  }
  setupStepValues(nextStep);
}



void setupModalContentArr() {
  modalContentWinArr[0] = ui_win1;
  modalContentWinArr[1] = ui_win2;
  modalContentWinArr[2] = ui_win3;
  modalContentWinArr[3] = ui_win4;
  modalContentWinArr[4] = ui_win5;
  modalContentWinArr[TENPAISTATUSMODAL_INDEX] = ui_selectoptioncontent;
  modalContentWinArr[TENPAISTATUSMODAL_INDEX + 1] = ui_selectoptioncontent;
  modalContentWinArr[TENPAISTATUSMODAL_INDEX + 2] = ui_selectoptioncontent;
  modalContentWinArr[TENPAISTATUSMODAL_INDEX + 3] = ui_selectoptioncontent;
}
// Automatically calculate the number of elements in the array

lv_obj_t * getModalStepContent(int index) {
  // Safe bounds check: Ensure index is between 0 and the maximum array size
  if (index >= 0 && index < 9) {
    return modalContentWinArr[index];
  }
  return NULL;
}

void handleModalStep1(int button) {
  switch(button) {
    case 0:
      winType = WT_DRAW;
      transitionToStep(TENPAISTATUSMODAL_INDEX);
      break;
    case 1:
      // Ron
      winType = WT_RON;
      transitionToStep(1);
      break;
    case 2:
      // Tsumo
      winType = WT_TSUMO;
      transitionToStep(1);
      break;
    case 3:
      transitionToStep(-1);
      break;
    default: 
      break;
  }

}
void handleModalStep2(int button) {
  bool skipDiscard = !!winType;
  bool skipFu = hanIndex >= 4;
  switch(button) {
    case 0:
      transitionToStep(skipFu ? skipDiscard ? 4 : 3 : 2);
      break;
    case 1:
      hanIndex = MIN(hanIndex + 1, 15);
      lv_label_set_text(ui_hancount, validHan[hanIndex]);
      break;
    case 2:
      hanIndex = MAX(hanIndex -1, 0);
      lv_label_set_text(ui_hancount, validHan[hanIndex]);

      break;
    case 3:
      lv_obj_add_flag(getModalStepContent(1), LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(getModalStepContent(0), LV_OBJ_FLAG_HIDDEN);
      modalContentStep--;

      break;
    default: 
      break;
  }
}

void handleModalStep3(int button ) {
  bool skipDiscard = !!winType;
  switch(button) {
    case 0:
      transitionToStep(skipDiscard ? 4 : 3);
      break;
    case 1:
      // Ron
      fuIndex = MIN(fuIndex + 1, 10);
      lv_label_set_text(ui_fucount, validFu[fuIndex]);
      break;
    case 2:
      // Tsumo
      // Ron
      fuIndex = MAX(fuIndex -1, 0);
      lv_label_set_text(ui_fucount, validFu[fuIndex]);

      break;
    case 3:
      lv_obj_add_flag(getModalStepContent(2), LV_OBJ_FLAG_HIDDEN);
      lv_obj_remove_flag(getModalStepContent(1), LV_OBJ_FLAG_HIDDEN);
      modalContentStep = 1;

      break;
    default: 
      break;
  }
}

void handleModalStep4(int button) {
  int newIndex;
  bool skipFu = hanIndex >= 4;

  switch(button) {
    case 0:
      transitionToStep(4);
      break;
    case 1:
      newIndex = (discarderIndex + 1) & 3;
      newIndex += ((newIndex == rotationIndex) ? 1 : 0);
      discarderIndex = newIndex & 3;
      lv_label_set_text(ui_discarder, discarders[discarderIndex]);
      break;
    case 2:
      newIndex = (4+ discarderIndex - 1) & 3;
      newIndex += ((newIndex == rotationIndex) ? -1 : 0);
      discarderIndex = (newIndex+ 4) & 3;
      lv_label_set_text(ui_discarder, discarders[discarderIndex]);
      break;
    case 3:
      transitionToStep(skipFu ? 1 : 2);
      break;
    default: 
      break;
  }
}

void applyPlayerOffsets() {
  for (int i=0; i< 4; i++) {
    int newScore = lv_subject_get_int(subject_scores[i]) + scoreOffsets[i];
    lv_subject_set_int(subject_scores[i], newScore);
    scoreOffsets[i] = 0;
    _scores[i] = newScore;
  }
  repaintPlayers();
}

// struct ModalSelectOptionRoute {
//   char titleLabel[20];
//   char prevLabel[20];
//   char nextLabel[20];
//   char selectLabel[20];
//   char * optionLabels[];
// };

// ModalSelectOptionRoute routes[] = {
//   {""}
// }

void handleTenpaiStatusModal(int button) {
  int newIndex;
  bool skipFu = hanIndex >= 4;
  int tenpaiPlayerIndex = modalContentStep - TENPAISTATUSMODAL_INDEX;

  switch(button) {
    case 0:
      //playerTenpaiFlags
      lv_subject_copy_string(&selectoption_subject, tenpaiModalOptions[0]);
      transitionToStep(modalContentStep == (TENPAISTATUSMODAL_INDEX + 3) ? (TENPAISTATUSMODAL_INDEX - 1) : (modalContentStep + 1));
      break;
    case 1:
    case 2:
      playerTenpaiFlags[tenpaiPlayerIndex] = !playerTenpaiFlags[tenpaiPlayerIndex];
      lv_subject_copy_string(&selectoption_subject, tenpaiModalOptions[playerTenpaiFlags[tenpaiPlayerIndex]]);
      break;
    case 3:      
      lv_subject_copy_string(&selectoption_subject, tenpaiModalOptions[0]);
      transitionToStep(modalContentStep == TENPAISTATUSMODAL_INDEX ? 0 : (modalContentStep - 1));
      break;
    default: 
      break;
  }
}


void handleModalStep5(int button) {
  bool skipDiscard = !!winType;
  bool isDraw = winType == 2;
  bool skipFu = hanIndex >= 4;

    switch(button) {
    case 0:
      incrementRound();
      applyPlayerOffsets();
      transitionToStep(-1);
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      transitionToStep(isDraw ? (TENPAISTATUSMODAL_INDEX + 3) : skipDiscard ? skipFu ? 1 : 2 : 3);
      clearPlayerOffsets();
      break;
    default: 
      break;
    }
}

void (*modalHandlers[])(int) = {
  handleModalStep1,
  handleModalStep2,
  handleModalStep3,
  handleModalStep4,
  handleModalStep5,
  handleTenpaiStatusModal,
  handleTenpaiStatusModal,
  handleTenpaiStatusModal,
  handleTenpaiStatusModal
};

// 3. Automatically calculate the number of handlers
#define HANDLERS_ARR_SIZE (sizeof(modalHandlers) / sizeof(modalHandlers[0]))

void handleButton(int button) {
  int offsetButton = (button + 4 - rotationIndex) & 3;
  if (modalContentStep >=0 && modalContentStep< HANDLERS_ARR_SIZE) {
    modalHandlers[modalContentStep](offsetButton);
  } else {
    rollGifs(button);
  }
}


lv_obj_t * getPlayerComponent(int i) {
  switch (i) {
    case 0:
      return ui_player1;
    case 1:
      return ui_player2;
    case 2:
      return ui_player3;
    case 3:
      return ui_player4;
    default:
      return NULL;
  }
}

void clearPlayerOffsets() {
  for (int i = 0; i < 4; i++) {
    scoreOffsets[i] = 0;
  }
  repaintPlayers();
}

// assign offset scores, score are counter clockwise from winner
void repaintPlayers() {
  lv_obj_t * cui_player;
  lv_obj_t * cui_offset_score_container;
  lv_obj_t * cui_offset_score;

  for (int i=0; i<4;i++){
    cui_player = getPlayerComponent(i);
    cui_offset_score_container = ui_comp_get_child(cui_player, UI_COMP_PLAYER_PANEL30);
    cui_offset_score = ui_comp_get_child(cui_player, UI_COMP_PLAYER_PANEL30_OFFSETSCORE);

    if (scoreOffsets[i]) {
      char result[100]; 
      // Concatenate safely
      snprintf(result, sizeof(result), "%+d", scoreOffsets[i]);      
      lv_label_set_text(cui_offset_score, result);
      lv_obj_remove_flag(cui_offset_score_container, LV_OBJ_FLAG_HIDDEN);
    } else {
      lv_obj_add_flag(cui_offset_score_container, LV_OBJ_FLAG_HIDDEN);
    }
  }
}

void resetPlayerTenpaiFlags() {
  for (int i = 0; i<4; i++) {
    playerTenpaiFlags[i] = false;
  }
}

void resetModalLabels() {
  modalContentStep = 0;
  hanIndex = 0;
  fuIndex = 2;
  discarderIndex = 0;
  lv_label_set_text(ui_fucount, validFu[fuIndex]);
  lv_label_set_text(ui_hancount, validHan[hanIndex]);
  lv_label_set_text(ui_discarder, discarders[(rotationIndex+1)&3]);
  lv_subject_copy_string(&modal_title_subject, discarders[rotationIndex]);
}
void setModalVisibility(bool visible) {
  if (visible) {
    if (modalContentStep > 0){
      lv_obj_add_flag(getModalStepContent(modalContentStep), LV_OBJ_FLAG_HIDDEN);
      
    }
    resetModalLabels();
    lv_obj_add_flag(ui_roundpane, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_diecontainer, LV_OBJ_FLAG_HIDDEN);

    lv_obj_remove_flag(ui_modalcontainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(getModalStepContent(0), LV_OBJ_FLAG_HIDDEN);
  } else {
    lv_obj_add_flag(ui_modalcontainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(getModalStepContent(modalContentStep), LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_roundpane, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_diecontainer, LV_OBJ_FLAG_HIDDEN);
    rotationIndex = -1;
    modalContentStep = -1;
  }
}

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

void screen1TimeoutTask() {
  // sensor id -> user
  int sensorMap[] = {1,2,0,3};
  int riichi_count = 0; 
  for (int i=0; i<4;i++) {
      lv_obj_t * riichi_icon;
      riichi_icon = ui_comp_get_child(getPlayerComponent(sensorMap[i]), UI_COMP_PLAYER_CONTAINER_DOT);
      if (!lv_obj_has_flag(riichi_icon, LV_OBJ_FLAG_HIDDEN) && currentStateArr[i] != STATE_STABLE_COVERED ) {
        lv_obj_add_flag(riichi_icon, LV_OBJ_FLAG_HIDDEN);
        lv_subject_set_int(subject_scores[sensorMap[i]], _scores[sensorMap[i]]);
      } else if (lv_obj_has_flag(riichi_icon, LV_OBJ_FLAG_HIDDEN)&& currentStateArr[i] == STATE_STABLE_COVERED ) {
        lv_obj_remove_flag(riichi_icon, LV_OBJ_FLAG_HIDDEN);
        lv_subject_set_int(subject_scores[sensorMap[i]], -1000 + _scores[sensorMap[i]]);
      }
    riichi_count += (currentStateArr[i] == STATE_STABLE_COVERED) ? 1 : 0;
  }
  if (currentDoraCount != riichi_count) {
    currentDoraCount = riichi_count;
    lv_subject_set_int(&doracount_subject, riichi_count + carryoverDora);
  }
  

}
void screen2TimeoutTask() {
  lv_bar_set_value(ui_Bar1, lightState[0], LV_ANIM_ON); 
  lv_bar_set_value(ui_Bar2, lightState[1], LV_ANIM_ON); 
  lv_bar_set_value(ui_Bar3, lightState[2], LV_ANIM_ON); 
  lv_bar_set_value(ui_Bar4, lightState[3], LV_ANIM_ON);
}
void handleScreenTimeoutTask(lv_timer_t * timer) {
  lv_obj_t * current_screen = lv_screen_active();
  lv_obj_t * next_screen = NULL;

  // 1. Identify which screen is currently on the display
  if (current_screen == ui_Screen1) {
    screen1TimeoutTask();
  } 
  else if (current_screen == ui_Screen2) {
    screen2TimeoutTask();
  } 


}

void KEY_LoopTask(void *arg) {
  for (;;) {
    EventBits_t even = xEventGroupWaitBits(GP18ButtonGroups, (0x01 | 0x02 | 0x04), pdTRUE, pdFALSE, pdMS_TO_TICKS(2000));
    if (even & 0x01) {
      // is_Music = false;
      is_Music = true;
      xEventGroupSetBits(CodecGroups, 0x04);
    } else if (even & 0x02) {
      is_Music = true;
      xEventGroupSetBits(CodecGroups, 0x04);
    } else if (even & 0x04) {
      if (Lvgl_lock(-1)) {
        lv_obj_t * current_screen = lv_screen_active();
        lv_obj_t * next_screen = NULL;

        // 1. Identify which screen is currently on the display
        if (current_screen == ui_Screen1) {
            next_screen = ui_Screen2;
            showSensors = true;
        } 
        else if (current_screen == ui_Screen2) {
            next_screen = ui_Screen1;
            showSensors = false;
        } 
        // 2. Perform the safe transition if a target was found
        if (next_screen != NULL) {
          lv_screen_load_anim(next_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);
        }

        Lvgl_unlock();
      }

    }
  }
}

void TL_LoopTask(void *arg) {
  for (;;) {
    EventBits_t even = xEventGroupWaitBits(TLButtonGroups, (0x01 | 0x02 | 0x04), pdTRUE, pdFALSE, pdMS_TO_TICKS(2000));
    if (even & 0x01) {
      if (Lvgl_lock(-1)) {

        handleButton(2);
      
        Lvgl_unlock();
      }

    } else if (even & 0x02) {
      if (Lvgl_lock(-1)) {
        lv_obj_t * current_screen = lv_screen_active();
        uint32_t pressed_key = LV_KEY_NEXT;
        lv_obj_send_event(current_screen, LV_EVENT_KEY, &pressed_key);
        Lvgl_unlock();

      }
    } else if (even & 0x04) {
      if (Lvgl_lock(-1)) {
        // RlcdPort.SetRotation(180);
        setRotation(2);
        setModalVisibility(true);
        Lvgl_unlock();
      }
    }
  }
}

void TR_LoopTask(void *arg) {
  for (;;) {
    
    EventBits_t even = xEventGroupWaitBits(TRButtonGroups, (0x01 | 0x02 | 0x04), pdTRUE, pdFALSE, pdMS_TO_TICKS(2000));

    if (even & 0x01) {

      if (Lvgl_lock(-1)) {
        handleButton(1);
        Lvgl_unlock();
      }
    } else if (even & 0x02) {

    } else if (even & 0x04) {
      if (Lvgl_lock(-1)) {
//        RlcdPort.SetRotation(90);
        setRotation(1);
        setModalVisibility(true);
        Lvgl_unlock();
      }
    }
  }
}


void BR_LoopTask(void *arg) {
  for (;;) {
    EventBits_t even = xEventGroupWaitBits(BRButtonGroups, (0x01 | 0x02 | 0x04), pdTRUE, pdFALSE, pdMS_TO_TICKS(2000));
    if (even & 0x01) {
    if (Lvgl_lock(-1)) {
        handleButton(0);
        Lvgl_unlock();
      }    
    } else if (even & 0x02) {
    } else if (even & 0x04) {
      modalOpen = !modalOpen;
      if (Lvgl_lock(-1)) {
        // RlcdPort.SetRotation(0);
        setRotation(0);
        setModalVisibility(true);

        Lvgl_unlock();
      }
    }
  }
}

void BL_LoopTask(void *arg) {
  for (;;) {
    EventBits_t even = xEventGroupWaitBits(BLButtonGroups, (0x01 | 0x02 | 0x04), pdTRUE, pdFALSE, pdMS_TO_TICKS(2000));
    if (even & 0x01) {
    if (Lvgl_lock(-1)) {
        handleButton(3);
        Lvgl_unlock();
      }    } else if (even & 0x02) {
    } else if (even & 0x04) {
      if (Lvgl_lock(-1)) {
        // RlcdPort.SetRotation(270);
        setRotation(3);
        setModalVisibility(true);

        Lvgl_unlock();
      }
    }
  }
}



void processLightSensor(int rawValue, int sensor_id) {
    long currTime = millis();
    SensorState_t prevState = currentStateArr[sensor_id];
    SensorState_t currState = (rawValue > 1000) ? STATE_STABLE_DARK : currentStateArr[sensor_id];
    if (prevState == STATE_STABLE_COVERED && currState == STATE_STABLE_DARK) {
      currentStateArr[sensor_id] = currState;
    }
    else if (prevState != STATE_STABLE_COVERED && rawValue < 250 && (lastTriggered[sensor_id] + 5000 * 1) < currTime) {
        is_Music = true;

        currState = STATE_STABLE_COVERED;
        currentStateArr[sensor_id] = currState;
        lastTriggered[sensor_id] = currTime;
        xEventGroupSetBits(CodecGroups, 1 << sensor_id);
    }
    else if (prevState != STATE_STABLE_COVERED && rawValue < 250) {
        currState = STATE_STABLE_COVERED;
        currentStateArr[sensor_id] = currState;
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
    if (modalContentStep == -1) {
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
}




unsigned long previousMillis = 0; 
const unsigned long interval = 2000; // Interval in milliseconds (1 second)



void setupTimers() {
 lv_timer_create(handleScreenTimeoutTask, 100, NULL);

  // lv_anim_t a;
  // lv_anim_init(&a);
  // lv_anim_set_var(&a, ui_roundpane);
  // lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)anim_rotation_cb);

  // lv_anim_set_values(&a, 0, 3600); // 0 to 360 degrees (0.1 deg increments)
  // lv_anim_set_duration(&a, 3000);  // 3 seconds
  // lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE); // Loop forever
  // lv_anim_start(&a);
}


const lv_image_dsc_t* roundNumImgs[] ={&ui_img_1193668880, &ui_img_641408904, &ui_img_2052151144, &ui_img_1690547480};
const lv_image_dsc_t* playerWindsImgs[] ={&ui_img_toncb_png, &ui_img_nancb_png, &ui_img_shack_png, &ui_img_peicb_png};

void setPlayerWindImgs() {
    for (int i = 0; i < 4; i++) {
      lv_image_set_src(ui_comp_get_child(getPlayerComponent((seatRotationNum + i) & 3), UI_COMP_PLAYER_WINDIMG), playerWindsImgs[i]);
  }
}

void incrementRound() {
  if (winType == WT_NONE) {
    Serial.println("Somehow incremented round without ending it?");
    return;
  }
  int dealerIndex = seatRotationNum & 3;

  bool changeWinds = (rotationIndex != dealerIndex && winType != WT_DRAW) || (winType == WT_DRAW && !playerTenpaiFlags[dealerIndex]);
  bool resetHonba = changeWinds && winType != WT_DRAW;
  seatRotationNum += changeWinds ? 1 : 0;
  honbaCount = resetHonba ? 0 : (honbaCount + 1);
  setPlayerWindImgs();
  if (winType == WT_TSUMO || winType == WT_RON) {
    carryoverDora = 0;
    currentDoraCount = 0;
  }
  else {
    carryoverDora += currentDoraCount;
    currentDoraCount = 0;
  }
  if (changeWinds) {
    lv_image_set_src(ui_centerroundnum, roundNumImgs[seatRotationNum & 3]);
    lv_image_set_src(ui_centerroundwind, !((seatRotationNum>>2)&1) ? &ui_img_587546794 : &ui_img_centernan_png);
  }
  lv_subject_set_int(&honbacount_subject, honbaCount);
  lv_subject_set_int(&doracount_subject, carryoverDora);

}

void setup()
{
  audio_ptr = (uint8_t *)heap_caps_malloc(288 * 1000 * sizeof(uint8_t), MALLOC_CAP_SPIRAM);
  assert(audio_ptr);
  Serial.begin(115200);
  Serial.println("Hello world");
  delay(300);
  randomSeed(analogRead(0));

   RlcdPort.RLCD_Init();

   Lvgl_PortInit(300, 300, Lvgl_FlushCallback);

   if (Lvgl_lock(-1)) {
    ui_init();
    setupModalContentArr();
    setPlayerWindImgs();
    setupObservers();
    setupTimers();
    repaintPlayers();
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


void loop()
{

}
