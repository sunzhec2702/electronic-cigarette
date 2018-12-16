#include "menu_new_coil_check.h"
#include "key.h"
#include "screen.h"
#include "oled_content.h"
#include "peripherals_manager.h"

//static u8 current_coil_select_index = NEW_COIL;
static u8 last_ui_id;

// declare three key struct.
static key_callback keys_callback[] = {
    {KEY_INCREASE, menu_new_coil_check_value_key_preaction, menu_new_coil_check_value_key_trigger_action, menu_new_coil_check_value_key_long_event_action, menu_new_coil_check_value_key_repeat_action},
    {KEY_REDUCE, menu_new_coil_check_value_key_preaction, menu_new_coil_check_value_key_trigger_action, menu_new_coil_check_value_key_long_event_action, menu_new_coil_check_value_key_repeat_action},
    //{KEY_CONFIRM, menu_new_coil_check_confirm_key_preaction, menu_new_coil_check_confirm_key_trigger_action, menu_new_coil_check_confirm_key_long_event_action, menu_new_coil_check_confirm_key_repeat_action},
};


void menu_new_coil_check_page_entry(void* pt)
{
    u8 index;
    key_state *keys = get_keys_state();
    last_ui_id = *(u8 *)pt;
    keys_state_reset();
    for (index = 0; index < sizeof(keys_callback)/sizeof(key_callback); index++) {
        keys[keys_callback[index].type].key_callback = &keys_callback[index];
    }
    menu_new_coil_check_draw_whole_screen();
}

void menu_new_coil_check_page_exit(void* pt)
{
    // Do nothing for now.
    last_ui_id = 0;
    keys_callback_reset();
}

u8 menu_new_coil_check_combine_event_callback (void * keys_t)
{
    return SUCCESS;
}

void menu_new_coil_check_draw_whole_screen()
{
    OLED_Clear();
    draw_coil_string();
    draw_coil_choose_menu();
}

void menu_new_coil_check_draw_current_value()
{
    draw_coil_string();
    draw_coil_choose_menu();
}

void update_current_coil_select_index(u8 key_type)
{
    set_coil_ready_flag();
    switch (key_type) {
        case KEY_INCREASE: // RIGHT
            break;
        case KEY_REDUCE: // LEFT
            coil_r_static_update();
            break;
        default:
            break;
    }
    switch_to_ui_page(last_ui_id);
}

void coil_select_confirm()
{
    
}


