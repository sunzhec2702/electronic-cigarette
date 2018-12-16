#ifndef __SMOKE_MODE_SELECT_MENU_H
#define __SMOKE_MODE_SELECT_MENU_H
#include "sys.h"

enum {
    MENU_SMOKE_KEY_LOCK = 0,
    MENU_SMOKE_POWER_MODE,
    /*
    MENU_SMOKE_VOLTAGE_MODE,
    MENU_SMOKE_BYPASS_MODE,
    */
    MENU_SMOKE_TEMPERATURE_MODE,
    MENU_SMOKE_SCREEN_FLIP,
    MENU_SMOKE_ABOUT,
    MENU_SMOKE_MODES_NUMBER
};

/*
#define POWER_MODE          0
#define VOLTAGE_MODE        1
#define BYPASS_MODE         2
#define TEMPERATURE_MODE    3
#define KEY_LOCK            4
#define SCREEN_FLIP         5
#define ABOUT               6
#define SMOKE_MODES_NUMBER  7
*/

extern void smoke_mode_select_page_entry(void* pt);
extern void smoke_mode_select_page_exit(void* pt);
extern u8 smoke_mode_select_combine_event_callback (void * keys_t);
extern void smoke_mode_select_value_key_callback(u8 key_type);
extern void smoke_mode_select_confirm_key_callback(u8 long_press);
extern void smoke_mode_select_draw_current_value(void* pt);

#endif

