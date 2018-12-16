#include "power_voltage_value_key_action.h"
#include "UI_manager.h"
#include "main_menu_power.h"
#include "main_menu_voltage.h"
#include "key.h"
#include "system_state.h"
#include "value_manager.h"
#include "oled_content.h"
#include "hw_checker.h"

static u16 step[] = {1, 10};

u8 power_voltage_value_key_preaction(u8 pressed_keys, void * key_t)
{
    key_state* key = (key_state*) key_t;
    if (pressed_keys > 1) {
        key_state_reset_single(key->type);
        return ERROR;
    }
    if (get_system_state() == STATE_CHARGING) {
        return ERROR;
    }
    
    if (get_value_key_lock() == SYS_LOCK && key->type != KEY_CONFIRM) {
        return ERROR;
    }
    
    if (get_current_ui_id() == MAIN_MENU_BYPASS_ID)
        return ERROR;
    return SUCCESS;
}

// For power key state trigger function.
u8 power_voltage_value_key_trigger_action(void* key_t)
{
    return SUCCESS;
}

// LONG EVENT ACTION.
u8 power_voltage_value_key_long_event_action(void * key_t)
{
    u8 smoke_state;
    u16 min,max;
    key_state* key = (key_state *) key_t;
    if (key->type != KEY_INCREASE && key->type != KEY_REDUCE) {
        return ERROR;
    }
    
    if (get_system_state() == STATE_CHARGING)
        return ERROR;

    if (key->state == KEY_ON) {
        // Do not respond when we are smoking.
        smoke_state = get_system_smoke();
        if (smoke_state == SYS_SMOKE || smoke_state == SYS_SMOKE_DONE)
            return ERROR;

        // deal with press / long press.
        if (key->press_report_tic >= key->report_tic_interval || key->trigger_flag == TRIGGERED) {
            key->press_report_tic = 0;
            if (get_current_ui_id() == MAIN_MENU_POWER_ID) {
                min = MIN_POWER_VALUE;
                max = MAX_POWER_VALUE;
            } else if (get_current_ui_id() == MAIN_MENU_VOLTAGE_ID) {
                min = MIN_PRESET_VOLTAGE_VALUE;
                max = value_read(MAX_PRESET_VOLTAGE_VALUE);
            }
            if (key->press_keep_tic > key->long_press_interval) {
                value_update_step(get_current_ui_page()->get_value_pointer(NULL), step, 1, key->type, min, max);
            } else {
                value_update_step(get_current_ui_page()->get_value_pointer(NULL), step, 0, key->type, min, max);
            }
            get_current_ui_page()->value_backup();
            get_current_ui_page()->draw_current_value();
        }
    } else if (key->state == KEY_OFF) {
        if (key->release_keep_tic > key->repeat_tic_interval) {
            power_voltage_value_key_repeat_action(key_t);
        }
    }
    return SUCCESS;

}

// REPEAT KEY ACTION.
u8 power_voltage_value_key_repeat_action(void* key_t)
{
    key_state* key = (key_state *) key_t;
    // We need to clear the repeat count after we finish the action.*/
    key->repeat_count = 0;
    return SUCCESS;

}
