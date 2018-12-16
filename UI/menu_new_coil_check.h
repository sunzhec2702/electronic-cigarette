#ifndef __MENU_NEW_COIL_CHECK_H
#define __MENU_NEW_COIL_CHECK_H
#include "sys.h"

#include "UI_manager.h"
#include "menu_new_coil_check_value_key_action.h"
#include "menu_new_coil_check_confirm_key_action.h"
#include "menu_new_coil_check_value_manager.h"

#define NEW_COIL    0
#define SAME_COIL   1

extern void menu_new_coil_check_page_entry(void* pt);
extern void menu_new_coil_check_page_exit(void* pt);
extern u8 menu_new_coil_check_combine_event_callback(void* keys_t);
extern void menu_new_coil_check_draw_whole_screen(void);
extern void menu_new_coil_check_draw_current_value(void);
extern void update_current_coil_select_index(u8 key_type);
extern void coil_select_confirm(void);
#endif

