#ifndef __TEMP_MODE_SELECT_MENU_H
#define __TEMP_MODE_SELECT_MENU_H
#include "sys.h"

enum {
    NI_MODE = 0,
    #if defined SCREEN_069
    TI_MODE,
    SS_MODE,
    M1_MODE,
    M2_MODE,
    M3_MODE,
    #elif defined SCREEN_096
    M3_MODE,
    M2_MODE,
    M1_MODE,
    SS_MODE,
    TI_MODE,
    #endif
    TEMP_MODES_NUMBER
};

#define TEMP_MODE_SELECT_REG_INDEX  3
#define TEMP_MODE_SELECT_REG_OFFSET 20
#define TEMP_MODE_SELECT_LEN_MASK   0xF

extern void temperature_mode_select_page_entry(void* pt);
extern void temperature_mode_select_page_exit(void* pt);
extern u8 temperature_mode_select_combine_event_callback (void * keys_t);
extern void temperature_mode_select_value_key_callback(u8 key_type);
extern void temperature_mode_select_confirm_key_callback(u8 long_press);
extern void temperature_mode_select_draw_current_value(void* pt);
extern void temperatue_mode_backup(void);
extern void temperature_mode_restore(void);
extern u8 get_temperature_mode_index(void);
extern u8 get_temperature_mode_ui_id(void);

#endif

