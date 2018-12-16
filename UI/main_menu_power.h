#ifndef __MAIN_MENU_POWER_H
#define __MAIN_MENU_POWER_H
#include "sys.h"

#include "UI_manager.h"
#include "power_voltage_value_key_action.h"
#include "power_voltage_confirm_key_action.h"
#include "main_menu_power_value_manager.h"

extern void main_power_page_entry(void* pt);
extern void main_power_page_exit(void* pt);
extern u8 main_power_combine_event_callback(void* keys_t);
extern void main_power_draw_whole_screen(void);
extern void main_power_draw_current_value(void);

#endif

