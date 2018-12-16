#include "menu_mx_tcr.h"
#include "key.h"
#include "oled.h"
#include "oled_content.h"
#include "system_state.h"
#include "temperature_mode_select_menu.h"

// declare three key struct.
static key_callback keys_callback[] = {
    {KEY_INCREASE, menu_mx_parameter_value_key_preaction, menu_mx_parameter_value_key_trigger_action, menu_mx_parameter_value_key_long_event_action, menu_mx_parameter_value_key_repeat_action},
    {KEY_REDUCE, menu_mx_parameter_value_key_preaction, menu_mx_parameter_value_key_trigger_action, menu_mx_parameter_value_key_long_event_action, menu_mx_parameter_value_key_repeat_action},
    {KEY_CONFIRM, menu_mx_parameter_confirm_key_preaction, menu_mx_parameter_confirm_key_trigger_action, menu_mx_parameter_confirm_key_long_event_action, menu_mx_parameter_confirm_key_repeat_action},
};


void menu_mx_parameter_page_entry(void* pt)
{
    u8 index;
    key_state *keys = get_keys_state();
    keys_state_reset();
    for (index = 0; index < sizeof(keys_callback)/sizeof(key_callback); index++) {
        keys[keys_callback[index].type].key_callback = &keys_callback[index];
    }
    menu_mx_parameter_draw_whole_screen();
}

void menu_mx_parameter_page_exit(void* pt)
{
    keys_callback_reset();
}

u8 menu_mx_parameter_combine_event_callback (void * keys_t)
{
    return SUCCESS;
}

void menu_mx_parameter_draw_whole_screen()
{
    OLED_Clear();
    draw_mx_mode_icon(get_temperature_mode_index()-M1_MODE+1, 1);
    switch(get_current_ui_id()) {
        case MENU_MX_TCR_ID:
            draw_mx_tcr_string(1);
            draw_mx_value(*mx_tcr_get_value_pointer(get_temperature_mode_ui_id()), 1);
            break;
        case MENU_MX_MAX_POWER_ID:
            draw_mx_max_power_string(1);
            draw_mx_max_power_value(*mx_max_power_get_value_pointer(get_temperature_mode_ui_id()), 1);
            break;
    }
}

void menu_mx_parameter_draw_current_value()
{
    draw_mx_mode_icon(get_temperature_mode_index()-M1_MODE+1, 1);
    switch(get_current_ui_id()) {
        case MENU_MX_TCR_ID:
            draw_mx_tcr_string(1);
            draw_mx_value(*mx_tcr_get_value_pointer(get_temperature_mode_ui_id()), 1);
            break;
        case MENU_MX_MAX_POWER_ID:
            draw_mx_max_power_string(1);
            draw_mx_max_power_value(*mx_max_power_get_value_pointer(get_temperature_mode_ui_id()), 1);
            break;
    }
}



