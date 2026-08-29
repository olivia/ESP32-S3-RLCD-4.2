#include <stdio.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include "freertos/semphr.h"
#include <esp_log.h>
#include <esp_timer.h>
#include "lvgl_bsp.h"
#include <Arduino.h>

static SemaphoreHandle_t lvgl_mux = NULL;
#define BYTES_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565))


static const char *TAG = "LvglPort";

static void Increase_lvgl_tick(void *arg)
{
  	lv_tick_inc(LVGL_TICK_PERIOD_MS);
}

bool Lvgl_lock(int timeout_ms)
{
  	const TickType_t timeout_ticks = (timeout_ms == -1) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
  	return xSemaphoreTake(lvgl_mux, timeout_ticks) == pdTRUE;       
}

void Lvgl_unlock(void)
{
  	assert(lvgl_mux && "bsp_display_start must be called first");
  	xSemaphoreGive(lvgl_mux);
}

static void Lvgl_port_task(void *arg)
{
  	uint32_t task_delay_ms = LVGL_TASK_MAX_DELAY_MS;
  	for(;;)
  	{
  	  	if (Lvgl_lock(-1)) 
  	  	{
  	  	  	task_delay_ms = lv_timer_handler();
  	  	  	//Release the mutex
  	  	  	Lvgl_unlock();
  	  	}
  	  	if (task_delay_ms > LVGL_TASK_MAX_DELAY_MS)
  	  	{
  	  	  	task_delay_ms = LVGL_TASK_MAX_DELAY_MS;
  	  	} else if (task_delay_ms < LVGL_TASK_MIN_DELAY_MS)
  	  	{
  	  	  	task_delay_ms = LVGL_TASK_MIN_DELAY_MS;
  	  	}
  	  	vTaskDelay(pdMS_TO_TICKS(task_delay_ms));
  	}
}


// This callback takes the internal LVGL logs and forces them out of Arduino's Serial
void my_log_cb(lv_log_level_t level, const char * buf) {
    Serial.println(buf);
    Serial.flush(); // Crucial: forces the text out instantly before a freeze can block it
}

void Lvgl_PortInit(int width, int height, DispFlushCb flush_cb) {
    lvgl_mux = xSemaphoreCreateMutex();
    lv_init();
    lv_display_t * disp = lv_display_create(width, height); /* 以水平和垂直分辨率（像素）进行基本初始化 */
		  lv_display_set_offset(disp, 50, 0);
    lv_display_set_flush_cb(disp, flush_cb);
	
	
    // Turn off software edge smoothing globally for this screen
    // This reduces the per-pixel rendering math during transformations!
    lv_display_set_antialiasing(disp, false); 	
		#if LV_USE_LOG
			lv_log_register_print_cb(my_log_cb);
    #endif

		size_t buffer_size = width * height * BYTES_PER_PIXEL;
		uint8_t *buffer_1 = NULL;
    uint8_t *buffer_2 = NULL;
   // Allocate inside fast Internal RAM for quick bit-masking if possible, 
    // or keep SPIRAM if internal memory is restricted.
    buffer_1 = (uint8_t *)heap_caps_malloc(buffer_size, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    buffer_2 = (uint8_t *)heap_caps_malloc(buffer_size, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
//		uint8_t *my_canvas_buffer = (uint8_t *)ps_malloc(CANVAS_WIDTH * CANVAS_HEIGHT * 2);
		// if(my_canvas_buffer == NULL) {
    // // Handle allocation failure
		// ESP_LOGE(TAG, "Failed to allocate canvas buffer");
		// }

    
    if(!buffer_1 || !buffer_2) { // Fallback to SPIRAM if internal memory is full
			if(buffer_1) heap_caps_free(buffer_1);
			if(buffer_2) heap_caps_free(buffer_2);

        buffer_1 = (uint8_t *)heap_caps_malloc(buffer_size, MALLOC_CAP_SPIRAM);
        buffer_2 = (uint8_t *)heap_caps_malloc(buffer_size, MALLOC_CAP_SPIRAM);
    }
    assert(buffer_1);
    assert(buffer_2);


    lv_display_set_buffers(disp, buffer_1, buffer_2, buffer_size, LV_DISPLAY_RENDER_MODE_PARTIAL);

    ESP_LOGI(TAG, "Install LVGL tick timer");
  	esp_timer_create_args_t lvgl_tick_timer_args = {};
  	lvgl_tick_timer_args.callback = &Increase_lvgl_tick;
  	lvgl_tick_timer_args.name = "lvgl_tick";
    esp_timer_handle_t lvgl_tick_timer = NULL;
  	ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
  	ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer,LVGL_TICK_PERIOD_MS * 1000));

    xTaskCreatePinnedToCore(Lvgl_port_task, "LVGL", 16 * 1024, NULL, 5, NULL, 0);
}
