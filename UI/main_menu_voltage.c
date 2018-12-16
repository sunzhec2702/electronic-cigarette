#include "main_menu_voltage.h"
#include "system_state.h"
#include "timer_key.h"
#include "value_manager.h"
#include "oled.h"
#include "oled_content.h"

// declare three key struct.
static key_callback keys_callback[] = {
    {KEY_INCREASE, power_voltage_value_key_preaction, power_voltage_value_key_trigger_action, power_voltage_value_key_long_event_action, power_voltage_value_key_repeat_action},
    {KEY_REDUCE, power_voltage_value_key_preaction, power_voltage_value_key_trigger_action, power_voltage_value_key_long_event_action, power_voltage_value_key_repeat_action},
    {KEY_CONFIRM, power_voltage_confirm_key_preaction, power_voltage_confirm_key_trigger_action, power_voltage_confirm_key_long_event_action, power_voltage_confirm_key_repeat_action},
};

void main_voltage_page_entry(void* pt)
{
    u8 index;
    key_state *keys = get_keys_state();
    keys_state_reset();
    for (index = 0; index < sizeof(keys_callback)/sizeof(key_callback); index++) {
        keys[keys_callback[index].type].key_callback = &keys_callback[index];
    }
    main_voltage_draw_whole_screen();
}

void main_voltage_page_exit(void* pt)
{
    keys_callback_reset();
}

u8 main_voltage_combine_event_callback (void * keys_t)
{
    key_state *keys = (key_state*) keys_t;

    if (get_system_state() != STATE_NORMAL || get_system_lock() == SYS_LOCK || get_system_smoke() == SYS_SMOKE || get_system_smoke() == SYS_SMOKE_DONE)
        return SUCCESS;

    if (keys[KEY_INCREASE].state == KEY_ON && keys[KEY_REDUCE].state == KEY_ON) {
        if (keys[KEY_INCREASE].press_report_tic == 0 || keys[KEY_REDUCE].press_report_tic == 0) {
            switch_to_ui_page(MAIN_MENU_POWER_ID);
            return ERROR;
        }
    }
    return SUCCESS;
}

void main_voltage_draw_whole_screen()
{
    OLED_Clear();
    draw_voltage_value(value_read(VOLTAGE_VALUE));
    draw_register_value(value_read(REGISTER_VALUE));
    draw_preset_voltage_value(*main_voltage_get_value_pointer(NULL));
    draw_current_battery();
}

void main_voltage_draw_current_value()
{
    draw_preset_voltage_value(*main_voltage_get_value_pointer(NULL));
}

