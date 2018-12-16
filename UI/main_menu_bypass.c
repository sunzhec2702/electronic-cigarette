#include "main_menu_bypass.h"
#include "key.h"
#include "oled.h"
#include "oled_content.h"
#include "value_manager.h"

// declare three key struct.
static key_callback keys_callback[] = {
    {KEY_CONFIRM, bypass_confirm_key_preaction, bypass_confirm_key_trigger_action, bypass_confirm_key_long_event_action, bypass_confirm_key_repeat_action},
};


void main_bypass_page_entry(void* pt)
{
    u8 index;
    key_state *keys = get_keys_state();
    keys_state_reset();
    for (index = 0; index < sizeof(keys_callback)/sizeof(key_callback); index++) {
        keys[keys_callback[index].type].key_callback = &keys_callback[index];
    }
    main_bypass_draw_whole_screen();
}

void main_bypass_page_exit(void* pt)
{
    // Do nothing for now.
    keys_callback_reset();
}

u8 main_bypass_combine_event_callback (void * keys_t)
{
    /*
    key_state *keys = (key_state*) keys_t;

    if (get_system_state() != STATE_NORMAL || get_system_lock() == SYS_LOCK || get_system_smoke() == SYS_SMOKE || get_system_smoke() == SYS_SMOKE_DONE)
        return SUCCESS;

    if (keys[KEY_INCREASE].state == KEY_ON && keys[KEY_REDUCE].state == KEY_ON) {
        if (keys[KEY_INCREASE].press_report_tic == 0 || keys[KEY_REDUCE].press_report_tic == 0) {
            switch_to_ui_page(MAIN_MENU_VOLTAGE_ID);
            return ERROR;
        }
    }
    */
    
    return SUCCESS;
}

void main_bypass_draw_whole_screen()
{
    OLED_Clear();
    draw_voltage_value(value_read(VOLTAGE_VALUE));
    draw_register_value(value_read(REGISTER_VALUE));
    draw_bypass_value();
    draw_current_battery();
}

void main_bypass_draw_current_value()
{
    draw_bypass_value();
}

