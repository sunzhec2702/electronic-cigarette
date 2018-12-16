#ifndef __TEMP_MODE_SELECT_MENU_H
#define __TEMP_MODE_SELECT_MENU_H
#include "sys.h"

#define NI_MODE                 0
#define TI_MODE                 1
#define SS_MODE                 2
#define M1_MODE                 3
#define M2_MODE                 4
#define M3_MODE                 5
#define TEMP_MODES_NUMBER       6

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

