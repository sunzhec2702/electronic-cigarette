#ifndef __MAIN_MENU_TEMPERATURE_H
#define __MAIN_MENU_TEMPERATURE_H
#include "sys.h"
#include "UI_manager.h"
#include "main_menu_temperature_value_manager.h"
#include "main_menu_temperature_confirm_key_action.h"
#include "main_menu_temperature_value_key_action.h"

#define RCT_NI  0
#define RCT_TI  0
#define RCT_SS  0
#define RCT_M1  0
#define RCT_M2  0
#define RCT_M3  0

extern void main_menu_temperature_page_entry(void* pt);
extern void main_menu_temperature_page_exit(void* pt);
extern u8 main_menu_temperature_combine_event_callback(void* keys_t);
extern void main_menu_temperature_draw_whole_screen(void);
extern void main_menu_temperature_draw_current_value(void);

#endif

