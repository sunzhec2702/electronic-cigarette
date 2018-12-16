#include "main_menu_temperature.h"
#include "UI_manager.h"
#include "key.h"
#include "screen.h"
#include "oled_content.h"
#include "system_state.h"
#include "value_manager.h"

// declare three key struct.
static key_callback keys_callback[] = {
    {KEY_INCREASE, main_menu_temperature_value_key_preaction, main_menu_temperature_value_key_trigger_action, main_menu_temperature_value_key_long_event_action, main_menu_temperature_value_key_repeat_action},
    {KEY_REDUCE, main_menu_temperature_value_key_preaction, main_menu_temperature_value_key_trigger_action, main_menu_temperature_value_key_long_event_action, main_menu_temperature_value_key_repeat_action},
    {KEY_CONFIRM, main_menu_temperature_confirm_key_preaction, main_menu_temperature_confirm_key_trigger_action, main_menu_temperature_confirm_key_long_event_action, main_menu_temperature_confirm_key_repeat_action},
};

void main_menu_temperature_page_entry(void* pt)
{
    u8 index;
    key_state *keys = get_keys_state();
    keys_state_reset();
    for (index = 0; index < sizeof(keys_callback)/sizeof(key_callback); index++) {
        keys[keys_callback[index].type].key_callback = &keys_callback[index];
    }
    value_write(TCR_KKM_VALUE, get_current_TCR());
    value_write(MAX_PRESET_POWER_VALUE, get_current_max_power_value());
    if(can_draw_icons() == SUCCESS)
        main_menu_temperature_draw_whole_screen();
}

void main_menu_temperature_page_exit(void* pt)
{
    keys_callback_reset();
}

u8 main_menu_temperature_combine_event_callback (void * keys_t)
{
    return SUCCESS;
}

void main_menu_temperature_draw_whole_screen()
{
    OLED_Clear();
    draw_current_mode();
    draw_pid_power_out_value(get_current_max_power_value()*10);
    draw_register_value(value_read(REGISTER_STATIC_VALUE));
    draw_temperature_value(*main_menu_temperature_get_value_pointer(NULL), get_current_ui_id(), get_degree_mode());
    draw_current_battery();
    draw_current_lock_icon();
    draw_split_lines();
}

void main_menu_temperature_draw_current_value()
{
    draw_pid_power_out_value(get_current_max_power_value()*10);
    draw_register_value(value_read(REGISTER_STATIC_VALUE));
    draw_temperature_value(*main_menu_temperature_get_value_pointer(NULL), get_current_ui_id(), get_degree_mode());
}

