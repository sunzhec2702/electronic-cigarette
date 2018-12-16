#ifndef __MENU_MX_PARAMETER_H
#define __MENU_MX_PARAMETER_H
#include "sys.h"
#include "UI_manager.h"
#include "menu_mx_parameter_value_key_action.h"
#include "menu_mx_parameter_confirm_key_action.h"
#include "menu_mx_parameter_value_manager.h"

extern void menu_mx_parameter_page_entry(void* pt);
extern void menu_mx_parameter_page_exit(void* pt);
extern u8 menu_mx_parameter_combine_event_callback(void* keys_t);
extern void menu_mx_parameter_draw_whole_screen(void);
extern void menu_mx_parameter_draw_current_value(void);



#endif


