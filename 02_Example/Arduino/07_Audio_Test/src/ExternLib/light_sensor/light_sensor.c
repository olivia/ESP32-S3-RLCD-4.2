#include "light_sensor.h"

// Macro for callback execution with null check
#define EVENT_CB(ev)   do { if(handle->cb[ev]) handle->cb[ev](handle); } while(0)
// Button handle list head
static LightSensor* head_handle = NULL;


void light_sensor_init(LightSensor* handle, uint8_t(*pin_level)(uint8_t), uint8_t active_level, uint8_t sensor_id)
{
  if (!handle || !pin_level) return;  // parameter validation
  
  memset(handle, 0, sizeof(LightSensor));
  handle->event = (uint8_t)LIGHT_SENSOR_NO_EVENT;
  handle->hal_light_level = pin_level;
  handle->light_level = !active_level;  // initialize to opposite of active level
  handle->active_level = active_level;
  handle->sensor_id = sensor_id;
  handle->state = LIGHT_SENSOR_STATE_IDLE;
}

void light_sensor_attach(LightSensor* handle, LightSensorEvent event, LightSensorCallback cb)
{
  if (!handle || event >= LIGHT_SENSOR_EVENT_COUNT) return;  // parameter validation
  handle->cb[event] = cb;
}

void light_sensor_detach(LightSensor* handle, LightSensorEvent event)
{
  if (!handle || event >= LIGHT_SENSOR_EVENT_COUNT) return;  // parameter validation
  handle->cb[event] = NULL;
}

LightSensorEvent light_sensor_get_event(LightSensor* handle)
{
  if (!handle) return LIGHT_SENSOR_NO_EVENT;  // parameter validation
  return (LightSensorEvent)handle->event;
}

int light_sensor_start(LightSensor* handle)
{
  if (!handle) return -2;  // invalid parameter
  
  LightSensor* target = head_handle;
  while (target) {
    if (target == handle) return -1;  // already exist
    target = target->next;
  }
  
  handle->next = head_handle;
  head_handle = handle;
  return 0;
}

void light_sensor_stop(LightSensor* handle)
{
  if (!handle) return -2;  // parameter validation
  
  LightSensor** curr;
  for (curr = &head_handle; *curr; ) {
    LightSensor* entry = *curr;
    if (entry == handle) {
      *curr = entry->next;
      entry->next = NULL;  // clear next pointer
      return 0;  // successfully removed
    } else {
      curr = &entry->next;
    }
  }
  
  return -1;  // not found
}

void light_sensor_ticks(void)
{
  LightSensor* handle = head_handle;
  while (handle) {
    light_sensor_handler(handle);
    handle = handle->next;
  }
}

static void light_sensor_handler(LightSensor* handle)
{
  if (!handle) return;  // parameter validation
  
  uint8_t current_level = handle->hal_light_level(handle->sensor_id);
  
  // Debounce logic
  if (current_level != handle->light_level) {
    handle->debounce_cnt++;
    if (handle->debounce_cnt >= 3) {  // debounce threshold
      handle->light_level = current_level;
      handle->debounce_cnt = 0;
      
      // State machine transitions
      switch (handle->state) {
        case LIGHT_SENSOR_STATE_IDLE:
          if (handle->light_level == handle->active_level) {
            handle->state = LIGHT_SENSOR_STATE_COVERED;
            handle->event = LIGHT_SENSOR_COVERED;
            EVENT_CB(LIGHT_SENSOR_COVERED);
          } else {
            handle->state = LIGHT_SENSOR_STATE_EXPOSED;
            handle->event = LIGHT_SENSOR_EXPOSED;
            EVENT_CB(LIGHT_SENSOR_EXPOSED);
          }
          break;
        case LIGHT_SENSOR_STATE_COVERED:
          if (handle->light_level != handle->active_level) {
            handle->state = LIGHT_SENSOR_STATE_EXPOSED;
            handle->event = LIGHT_SENSOR_EXPOSED;
            EVENT_CB(LIGHT_SENSOR_EXPOSED);
          }
          break;
        case LIGHT_SENSOR_STATE_EXPOSED:
          if (handle->light_level == handle->active_level) {
            handle->state = LIGHT_SENSOR_STATE_COVERED;
            handle->event = LIGHT_SENSOR_COVERED;
            EVENT_CB(LIGHT_SENSOR_COVERED);
          }
          break;
        default:
          break;
      }
    }
  } else {
    handle->debounce_cnt = 0;  // reset debounce counter
  }
}