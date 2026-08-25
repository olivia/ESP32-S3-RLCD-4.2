
#include <stdint.h>
#include <string.h>

// configuration constants - can be modified according to your needs
#define ticks_interval          5    // ms - timer interrupt interval
#define debounce_ticks          3    // max 7 (0 ~ 7) - debounce filter depth
#define short_ticks             (300 / ticks_interval)   // short press threshold
#define long_ticks              (1000 / ticks_interval)  // long press threshold
#define press_repeat_max_num    15   // maximum repeat counter value

// Forward declaration
typedef struct _LightSensor LightSensor;

// Button callback function type
typedef void (*LightSensorCallback)(LightSensor* light_sensor_handle);

// Button event types
typedef enum {
	LIGHT_SENSOR_COVERED = 0,     // light sensor covered
	LIGHT_SENSOR_EXPOSED,   // light sensor exposed
	LIGHT_SENSOR_EVENT_COUNT,        // total number of events
	LIGHT_SENSOR_NO_EVENT          // no event
} LightSensorEvent;

// Button state machine states
typedef enum {
	LIGHT_SENSOR_STATE_IDLE = 0,     // idle state
	LIGHT_SENSOR_STATE_RISING,        
	LIGHT_SENSOR_STATE_FALLING,      
	LIGHT_SENSOR_STATE_COVERED,       // light sensor covered state
	LIGHT_SENSOR_STATE_EXPOSED,        // light sensor exposed state     
} LightSensorState;

// Button structure
struct _LightSensor {
	uint16_t ticks;                     // tick counter
	uint8_t  repeat : 4;                // repeat counter (0-15)
	uint8_t  event : 4;                 // current event (0-15)
	uint8_t  state : 3;                 // state machine state (0-7)
	uint8_t  debounce_cnt : 3;          // debounce counter (0-7)
	uint8_t  active_level : 1;          // active GPIO level (0 or 1)
	uint8_t  light_level : 1;           // current light level
	uint8_t  sensor_id;                 // light sensor identifier
	uint8_t  (*hal_light_level)(uint8_t sensor_id);  // HAL function to read GPIO
	LightSensorCallback cb[LIGHT_SENSOR_EVENT_COUNT];    // callback function array
	LightSensor* next;                       // next button in linked list
};

#ifdef __cplusplus
extern "C" {
#endif

// Public API functions
void light_sensor_init(LightSensor* handle, uint8_t(*pin_level)(uint8_t), uint8_t active_level, uint8_t sensor_id);
void light_sensor_attach(LightSensor* handle, LightSensorEvent event, LightSensorCallback cb);
void light_sensor_detach(LightSensor* handle, LightSensorEvent event);
LightSensorEvent light_sensor_get_event(LightSensor* handle);
int  light_sensor_start(LightSensor* handle);
void light_sensor_stop(LightSensor* handle);
void light_sensor_ticks(void);

// Utility functions
uint8_t light_sensor_get_repeat_count(LightSensor* handle);
void light_sensor_reset(LightSensor* handle);
int light_sensor_is_covered(LightSensor* handle);

#ifdef __cplusplus
}
#endif


