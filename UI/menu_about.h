#ifndef __MENU_ABOUT_H
#define __MENU_ABOUT_H
#include "sys.h"
#include "UI_manager.h"
#include "menu_about_confirm_key_action.h"

#define MIGIC_BACKDOOR_TIC  1000    //1000*10 ms

extern void menu_about_page_entry(void* pt);
extern void menu_about_page_exit(void* pt);
extern u8 menu_about_combine_event_callback (void * keys_t);
extern void menu_about_draw_whole_screen(void);
extern void menu_about_draw_current_value(void);

#endif

