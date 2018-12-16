#ifndef __MAIN_MENU_TEMP_CONFIRM_KEY_H
#define __MAIN_MENU_TEMP_CONFIRM_KEY_H
#include "sys.h"

extern u8 main_menu_temperature_confirm_key_preaction(u8 pressed_keys, void * key_t);
extern u8 main_menu_temperature_confirm_key_trigger_action(void * key_t);
extern u8 main_menu_temperature_confirm_key_long_event_action(void* key_t);
extern u8 main_menu_temperature_confirm_key_repeat_action(void* key_t);

#endif

