#include <stdio.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include "freertos/task.h"
#include <esp_log.h>
#include "display_bsp_2.h"

int base_width_ = 400;   // Physical panel width (e.g., 400)
int base_height_ = 430; // Physical panel height (e.g., 400)
int current_rotation_ = 0; // Current rotation state (0, 1, 2, 3)
DisplayPort::DisplayPort(int mosi, int scl, int dc, int cs, int rst, int width, int height, spi_host_device_t spihost)
  : mosi_(mosi),
    scl_(scl),
    dc_(dc),
    cs_(cs),
    rst_(rst),
    width_(300),          // Hardcoded application drawing canvas
    height_(300)         // Hardcoded application drawing canvas 
    {
  esp_err_t ret;
  spi_bus_config_t buscfg = {};
  
  // Allocate buffer exactly matching your isolated 300x300 drawing box size
  DisplayLen = (300 * 300) >> 3;  // 11250 bytes
  
  buscfg.miso_io_num = -1;
  buscfg.mosi_io_num = mosi;
  buscfg.sclk_io_num = scl;
  buscfg.quadwp_io_num = -1;
  buscfg.quadhd_io_num = -1;
  buscfg.max_transfer_sz = DisplayLen;
  ret = spi_bus_initialize(spihost, &buscfg, SPI_DMA_CH_AUTO);
  ESP_ERROR_CHECK(ret);

  esp_lcd_panel_io_spi_config_t io_config = {};
  io_config.dc_gpio_num = dc_;
  io_config.cs_gpio_num = cs_;
  io_config.pclk_hz = 20 * 1000 * 1000;
  io_config.lcd_cmd_bits = 8;
  io_config.lcd_param_bits = 8;
  io_config.spi_mode = 0;
  io_config.trans_queue_depth = 10;

  ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)spihost, &io_config, &io_handle));

  gpio_config_t gpio_conf = {};
  gpio_conf.intr_type = GPIO_INTR_DISABLE;
  gpio_conf.mode = GPIO_MODE_OUTPUT;
  gpio_conf.pin_bit_mask = (0x1ULL << rst_);
  gpio_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  gpio_conf.pull_up_en = GPIO_PULLUP_ENABLE;
  ESP_ERROR_CHECK_WITHOUT_ABORT(gpio_config(&gpio_conf));

  Set_ResetIOLevel(1);

  DispBuffer = (uint8_t *)heap_caps_malloc(DisplayLen, MALLOC_CAP_SPIRAM);
  assert(DispBuffer);
}

DisplayPort::~DisplayPort() {
}

void DisplayPort::RLCD_Init() {
  RLCD_Reset();

  RLCD_SendCommand(0xD6);  // NVM Load Control
  RLCD_SendData(0x17);
  RLCD_SendData(0x02);

  RLCD_SendCommand(0xD1);  // Booster Enable
  RLCD_SendData(0x01);

  RLCD_SendCommand(0xC0);  // Gate Voltage Control
  RLCD_SendData(0x11);
  RLCD_SendData(0x04);

  RLCD_SendCommand(0xC1);  // VSHP Setting
  RLCD_SendData(0x69);
  RLCD_SendData(0x69);
  RLCD_SendData(0x69);
  RLCD_SendData(0x69);

  RLCD_SendCommand(0xC2);
  RLCD_SendData(0x19);
  RLCD_SendData(0x19);
  RLCD_SendData(0x19);
  RLCD_SendData(0x19);

  RLCD_SendCommand(0xC4);
  RLCD_SendData(0x4B);
  RLCD_SendData(0x4B);
  RLCD_SendData(0x4B);
  RLCD_SendData(0x4B);

  RLCD_SendCommand(0xC5);
  RLCD_SendData(0x19);
  RLCD_SendData(0x19);
  RLCD_SendData(0x19);
  RLCD_SendData(0x19);

  RLCD_SendCommand(0xD8);
  RLCD_SendData(0x80);
  RLCD_SendData(0xE9);

  RLCD_SendCommand(0xB2);
  RLCD_SendData(0x02);

  RLCD_SendCommand(0xB3);
  RLCD_SendData(0xE5);
  RLCD_SendData(0xF6);
  RLCD_SendData(0x05);
  RLCD_SendData(0x46);
  RLCD_SendData(0x77);
  RLCD_SendData(0x77);
  RLCD_SendData(0x77);
  RLCD_SendData(0x77);
  RLCD_SendData(0x76);
  RLCD_SendData(0x45);

  RLCD_SendCommand(0xB4);
  RLCD_SendData(0x05);
  RLCD_SendData(0x46);
  RLCD_SendData(0x77);
  RLCD_SendData(0x77);
  RLCD_SendData(0x77);
  RLCD_SendData(0x77);
  RLCD_SendData(0x76);
  RLCD_SendData(0x45);

  RLCD_SendCommand(0x62);
  RLCD_SendData(0x32);
  RLCD_SendData(0x03);
  RLCD_SendData(0x1F);

  RLCD_SendCommand(0xB7);
  RLCD_SendData(0x13);

  RLCD_SendCommand(0xB0);
  RLCD_SendData(0x64);

  RLCD_SendCommand(0x11);
  vTaskDelay(pdMS_TO_TICKS(200));
  RLCD_SendCommand(0xC9);
  RLCD_SendData(0x00);

  RLCD_SendCommand(0x3A);
  RLCD_SendData(0x11);

  RLCD_SendCommand(0xB9);
  RLCD_SendData(0x20);

  RLCD_SendCommand(0xB8);
  RLCD_SendData(0x29);

  // Configure hardware tracking windows
  SetRotation(0);

  RLCD_SendCommand(0x21);
  RLCD_ColorClear(ColorWhite);
}

void DisplayPort::SetRotation(uint16_t degrees) {
  current_rotation_ = degrees;
  uint8_t madctl_val = 0x00;

  uint16_t active_display_w = base_width_;
  uint16_t active_display_h = base_height_;

  switch (degrees) {
    case 90:
      madctl_val = 0xE8; // Swap Page/Column & Reverse Line Layouts
      active_display_w = base_height_;
      active_display_h = base_width_;
      break;
    case 180:
      madctl_val = 0x88; // Reverse Column and Page mappings
      active_display_w = base_width_;
      active_display_h = base_height_;
      break;
    case 270:
      madctl_val = 0x28; // Swap Page/Column & Reverse Column Layouts
      active_display_w = base_height_;
      active_display_h = base_width_;
      break;
    case 0:
    default:
      madctl_val = 0x48; // Native baseline default settings
      active_display_w = base_width_;
      active_display_h = base_height_;
      current_rotation_ = 0;
      break;
  }

  RLCD_SendCommand(0x36); // MADCTL Data Access
  RLCD_SendData(madctl_val);

  // Compute precise framing bounds to lock physical center
  uint16_t offset_x = (active_display_w - 300) / 2;
  uint16_t offset_y = (active_display_h - 300) / 2;

  uint16_t x2 = offset_x + 299;
  uint16_t y2 = offset_y + 299;

  // Reprogram hardware internal boundaries to stay locked inside center 300x300
  RLCD_SendCommand(0x2A); 
  RLCD_SendData(offset_x >> 8);
  RLCD_SendData(offset_x & 0xFF);
  RLCD_SendData(x2 >> 8);
  RLCD_SendData(x2 & 0xFF);

  RLCD_SendCommand(0x2B); 
  RLCD_SendData(offset_y >> 8);
  RLCD_SendData(offset_y & 0xFF);
  RLCD_SendData(y2 >> 8);
  RLCD_SendData(y2 & 0xFF);
}

void DisplayPort::RLCD_ColorClear(uint8_t color) {
  memset(DispBuffer, color, DisplayLen);
}

void DisplayPort::RLCD_Display() {
  // Enforce boundary framing context check
  SetRotation(current_rotation_);
  
  RLCD_SendCommand(0x2C);  // Memory Write Command
  RLCD_Sendbuffera(DispBuffer, DisplayLen);
}

void DisplayPort::RLCD_Reset(void) {
  Set_ResetIOLevel(1);
  vTaskDelay(pdMS_TO_TICKS(50));
  Set_ResetIOLevel(0);
  vTaskDelay(pdMS_TO_TICKS(20));
  Set_ResetIOLevel(1);
  vTaskDelay(pdMS_TO_TICKS(50));
}

void DisplayPort::RLCD_SendCommand(uint8_t Reg) {
  ESP_ERROR_CHECK(esp_lcd_panel_io_tx_param(io_handle, Reg, NULL, 0));
}

void DisplayPort::RLCD_SendData(uint8_t Data) {
  ESP_ERROR_CHECK(esp_lcd_panel_io_tx_param(io_handle, -1, &Data, 1));
}

void DisplayPort::RLCD_Sendbuffera(uint8_t *Data, int len) {
  ESP_ERROR_CHECK(esp_lcd_panel_io_tx_color(io_handle, -1, Data, len));
}

void DisplayPort::RLCD_DisplayWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
  if (x1 >= 300 || x2 >= 300 || y1 >= 300 || y2 >= 300) return;

  uint16_t active_display_w = (current_rotation_ % 180 == 0) ? base_width_ : base_height_;
  uint16_t active_display_h = (current_rotation_ % 180 == 0) ? base_height_ : base_width_;

  uint16_t offset_x = (active_display_w - 300) / 2;
  uint16_t offset_y = (active_display_h - 300) / 2;

  // Add hardware framing offset variables to local windows coordinates
  uint16_t hw_x1 = x1 + offset_x;
  uint16_t hw_x2 = x2 + offset_x;
  uint16_t hw_y1 = y1 + offset_y;
  uint16_t hw_y2 = y2 + offset_y;

  RLCD_SendCommand(0x2A);  
  RLCD_SendData(hw_x1 >> 8);
  RLCD_SendData(hw_x1 & 0xFF);
  RLCD_SendData(hw_x2 >> 8);
  RLCD_SendData(hw_x2 & 0xFF);

  RLCD_SendCommand(0x2B);  
  RLCD_SendData(hw_y1 >> 8);
  RLCD_SendData(hw_y1 & 0xFF);
  RLCD_SendData(hw_y2 >> 8);
  RLCD_SendData(hw_y2 & 0xFF);

  RLCD_SendCommand(0x2C);  

  int window_len = ((x2 - x1 + 1) * (y2 - y1 + 1)) / 8;
  if (window_len <= 0) window_len = 1;

  RLCD_Sendbuffera(DispBuffer, window_len); 
}

void DisplayPort::Set_ResetIOLevel(uint8_t level) {
  gpio_set_level((gpio_num_t)rst_, level ? 1 : 0);
}

#if (AlgorithmOptimization != 3)
void DisplayPort::RLCD_SetPixel(uint16_t x, uint16_t y, uint8_t color) {
  if (x >= 300 || y >= 300) return;

  // Standard linear 300x300 canvas coordinate mapping
  uint32_t index = (y * 300 + x) >> 3;
  uint8_t bit = 7 - ((y * 300 + x) & 0x07);

  if (color) {
    DispBuffer[index] |= (1 << bit);
  } else {
    DispBuffer[index] &= ~(1 << bit);
  }
}
#endif
