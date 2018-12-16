#ifndef __POWER_VOLTAGE_VALUE_KEY_ACTION_H
#define __POWER_VOLTAGE_VALUE_KEY_ACTION_H
#include "sys.h"

extern u8 power_voltage_value_key_preaction(u8 pressed_keys, void * key_t);
extern u8 power_voltage_value_key_trigger_action(void* key_t);
extern u8 power_voltage_value_key_long_event_action(void * key_t);
extern u8 power_voltage_value_key_repeat_action(void* key_t);


#endif
