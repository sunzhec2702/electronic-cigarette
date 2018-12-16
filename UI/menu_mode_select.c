#include "menu_mode_select.h"
#include "UI_manager.h"
#include "screen.h"
#include "oled_content.h"
#include "mode_select_content.h"
#include "value_manager.h"

static menu_info* menu_info_ptr;

// declare three key struct.
static key_callback keys_callback[] = {
    {KEY_INCREASE, menu_mode_select_value_key_preaction, menu_mode_select_value_key_trigger_action, menu_mode_select_value_key_long_event_action, menu_mode_select_value_key_repeat_action},
    {KEY_REDUCE, menu_mode_select_value_key_preaction, menu_mode_select_value_key_trigger_action, menu_mode_select_value_key_long_event_action, menu_mode_select_value_key_repeat_action},
    {KEY_CONFIRM, menu_mode_select_confirm_key_preaction, menu_mode_select_confirm_key_trigger_action, menu_mode_select_confirm_key_long_event_action, menu_mode_select_confirm_key_repeat_action},
};

void menu_mode_select_page_entry(void* pt)
{
    u8 index;
    key_state *keys = get_keys_state();
    
    if (menu_info_ptr == NULL) {
        switch_to_ui_page(value_restore_func(UI_ID_REG_INDEX, UI_ID_OFFSET, UI_ID_LEN_MASK));
    }
    
    keys_state_reset();
    keys[KEY_INCREASE].report_tic_interval = 2*REPORT_INTERVAL;
    keys[KEY_REDUCE].report_tic_interval = 2*REPORT_INTERVAL;
    for (index = 0; index < sizeof(keys_callback)/sizeof(key_callback); index++) {
        keys[keys_callback[index].type].key_callback = &keys_callback[index];
    }
    menu_mode_select_draw_whole_screen();
}

void menu_mode_select_page_exit(void* pt)
{
    key_state *keys = get_keys_state();
    keys[KEY_INCREASE].report_tic_interval = REPORT_INTERVAL;
    keys[KEY_REDUCE].report_tic_interval = REPORT_INTERVAL;
    keys_callback_reset();
    menu_info_ptr = NULL;
}

u8 menu_mode_select_combine_event_callback (void * keys_t)
{
    return SUCCESS;
}

void menu_mode_select_draw_whole_screen()
{
    menu_info_ptr->draw_select_option(NULL);
}

void menu_mode_select_draw_current_value()
{
    menu_info_ptr->draw_select_option(NULL);
}

void update_current_mode_index(u8 key_type)
{
    menu_info_ptr->value_key_callback(key_type);
}

void item_select(u8 long_press)
{
    menu_info_ptr->confirm_key_callback(long_press);
}

void update_menu_info(menu_info* info)
{
    menu_info_ptr = info;
}


