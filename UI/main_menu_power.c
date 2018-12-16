#include "main_menu_power.h"
#include "system_state.h"
#include "timer_key.h"
#include "value_manager.h"
#include "oled_content.h"
#include "screen.h"
#include "PID.h"


// declare three key struct.
static key_callback keys_callback[] = {
    {KEY_INCREASE, power_voltage_value_key_preaction, power_voltage_value_key_trigger_action, power_voltage_value_key_long_event_action, power_voltage_value_key_repeat_action},
    {KEY_REDUCE, power_voltage_value_key_preaction, power_voltage_value_key_trigger_action, power_voltage_value_key_long_event_action, power_voltage_value_key_repeat_action},
    {KEY_CONFIRM, power_voltage_confirm_key_preaction, power_voltage_confirm_key_trigger_action, power_voltage_confirm_key_long_event_action, power_voltage_confirm_key_repeat_action},
};


void main_power_page_entry(void* pt)
{
    u8 index;
    key_state *keys = get_keys_state();
    keys_state_reset();
    for (index = 0; index < sizeof(keys_callback)/sizeof(key_callback); index++) {
        keys[keys_callback[index].type].key_callback = &keys_callback[index];
    }
    value_write(MAX_PRESET_POWER_VALUE, MAX_POWER_VALUE_W);
    if(can_draw_icons() == SUCCESS)
        main_power_draw_whole_screen();
}

void main_power_page_exit(void* pt)
{
    keys_callback_reset();
}

u8 main_power_combine_event_callback(void* keys_t)
{
    /*
    key_state *keys = (key_state*) keys_t;

    if (get_system_state() != STATE_NORMAL || get_system_lock() == SYS_LOCK || get_system_smoke() == SYS_SMOKE || get_system_smoke() == SYS_SMOKE_DONE)
        return SUCCESS;

    if (keys[KEY_INCREASE].state == KEY_ON && keys[KEY_REDUCE].state == KEY_ON) {
        if (keys[KEY_INCREASE].trigger_flag == TRIGGERED || keys[KEY_REDUCE].trigger_flag == TRIGGERED) {
            switch (get_current_ui_id()) {
                case MAIN_MENU_POWER_ID:
                    switch_to_ui_page(MAIN_MENU_VOLTAGE_ID);
                    break;
                case MAIN_MENU_VOLTAGE_ID:
                    switch_to_ui_page(MAIN_MENU_BYPASS_ID);
                    break;
                case MAIN_MENU_BYPASS_ID:
                    switch_to_ui_page(MAIN_MENU_POWER_ID);
                    break;
            }
            return ERROR;
        }
    }
    */
    return SUCCESS;
}

void main_power_draw_whole_screen()
{
    OLED_Clear();
    draw_current_mode();
    if (get_current_ui_id() == MAIN_MENU_POWER_ID) {
        draw_power_value(*main_power_get_value_pointer(NULL));
        draw_voltage_value(sqrt_s32q15(Mul_s32q15(*(get_current_ui_page()->get_value_pointer(PID_VALUE)), get_sense_value()->Rstatic_q15))*100>>15);
    } else if (get_current_ui_id() == MAIN_MENU_VOLTAGE_ID) {
        draw_preset_voltage_value(*main_power_get_value_pointer(NULL));
        draw_voltage_value(*main_power_get_value_pointer(NULL));
    } else if (get_current_ui_id() == MAIN_MENU_BYPASS_ID) {
        draw_bypass_value();
        draw_pid_power_out_value(value_read(STATIC_BATTERY_VALUE)*value_read(STATIC_BATTERY_VALUE)/value_read(REGISTER_STATIC_VALUE)/10);
    }
    draw_register_value(value_read(REGISTER_STATIC_VALUE));
    draw_current_battery();
    draw_current_lock_icon();
    draw_split_lines();
    #ifdef DEBUG_CHARGING_BATTERY_VALUE
    draw_register_value(value_read(STATIC_BATTERY_VALUE));
    draw_voltage_value(get_battery_level());
    #endif
}

void main_power_draw_current_value()
{
    if (get_current_ui_id() == MAIN_MENU_POWER_ID) {
        draw_power_value(*main_power_get_value_pointer(NULL));
        draw_voltage_value(sqrt_s32q15(Mul_s32q15(*(get_current_ui_page()->get_value_pointer(PID_VALUE)), get_sense_value()->Rstatic_q15))*100>>15);
    } else if (get_current_ui_id() == MAIN_MENU_VOLTAGE_ID) {
        draw_preset_voltage_value(*main_power_get_value_pointer(NULL));
        draw_voltage_value(*main_power_get_value_pointer(NULL));
    } else if (get_current_ui_id() == MAIN_MENU_BYPASS_ID) {
        draw_bypass_value();
        draw_pid_power_out_value(value_read(STATIC_BATTERY_VALUE)*value_read(STATIC_BATTERY_VALUE)/value_read(REGISTER_STATIC_VALUE)/10);
    }
    draw_register_value(value_read(REGISTER_STATIC_VALUE));
    #ifdef DEBUG_CHARGING_BATTERY_VALUE
    draw_register_value(value_read(STATIC_BATTERY_VALUE));
    draw_voltage_value(get_battery_level());
    #endif

}

