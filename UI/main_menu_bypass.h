#ifndef __MAIN_MENU_BYPASS_H
#define __MAIN_MENU_BYPASS_H
#include "sys.h"
#include "UI_manager.h"
#include "main_menu_bypass_confirm_key_action.h"

extern void main_bypass_page_entry(void* pt);
extern void main_bypass_page_exit(void* pt);
extern u8 main_bypass_combine_event_callback(void * keys_t);
extern void main_bypass_draw_whole_screen(void);
extern void main_bypass_draw_current_value(void);


#endif

