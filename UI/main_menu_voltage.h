#ifndef __MAIN_MENU_VOLTAGE_H
#define __MAIN_MENU_VOLTAGE_H
#include "sys.h"

#include "UI_manager.h"
#include "power_voltage_value_key_action.h"
#include "power_voltage_confirm_key_action.h"
#include "main_menu_voltage_value_manager.h"

extern void main_voltage_page_entry(void* pt);
extern void main_voltage_page_exit(void* pt);
extern u8 main_voltage_combine_event_callback(void* keys_t, void* trigger_event);
extern void main_voltage_draw_whole_screen(void);
extern void main_voltage_draw_current_value(void);

#endif

