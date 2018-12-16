#ifndef __MENU_MODE_SELECT_H
#define __MENU_MODE_SELECT_H
#include "sys.h"
#include "UI_manager.h"
#include "menu_mode_select_value_key_action.h"
#include "menu_mode_select_confirm_key_action.h"

#define MENU_MODE_NUMBER    9

typedef struct
{
    void (*draw_select_option)(void* pt);
    void (*value_key_callback)(u8 type);
    void (*confirm_key_callback)(u8 long_press);
    u8 ui_id;
} menu_info;

extern void menu_mode_select_page_entry(void* pt);
extern void menu_mode_select_page_exit(void* pt);
extern u8 menu_mode_select_combine_event_callback (void * keys_t);
extern void menu_mode_select_draw_whole_screen(void);
extern void menu_mode_select_draw_current_value(void);
extern void update_current_mode_index(u8 key_type);
extern void item_select(u8 long_press);
extern void update_menu_info(menu_info* info);
#endif

