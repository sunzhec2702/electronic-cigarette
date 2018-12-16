#include "menu_mx_parameter_value_key_action.h"
#include "menu_mx_parameter.h"
#include "key.h"
#include "system_state.h"
#include "value_manager.h"

//static u16 step[] = {1,10,100};
u8 menu_mx_parameter_value_key_preaction(u8 pressed_keys, void * key_t)
{
    key_state* key = (key_state*) key_t;
    if (pressed_keys > 1) {
        key_state_reset_single(key->type);
        return ERROR;
    }
    return SUCCESS;
}

u8 menu_mx_parameter_value_key_trigger_action(void * key_t)
{
    key_state* key = (key_state*) key_t;
    if (key->state == KEY_ON) {
        if (get_cursor_index() == CURSOR_AT_MODE) {
            mx_parameter_mode_index_callback(key->type);
            get_current_ui_page()->value_backup();
            get_current_ui_page()->draw_current_value();
            return ERROR;

        }
    } else if (key->state == KEY_OFF) {
        key->report_tic_interval = REPORT_INTERVAL;
    }
    return SUCCESS;
}

u8 menu_mx_parameter_value_key_long_event_action(void* key_t)
{
    key_state* key = (key_state *) key_t;
    if (key->type != KEY_INCREASE && key->type != KEY_REDUCE) {
        return ERROR;
    }

    if (get_system_state() == STATE_CHARGING || get_cursor_index() == CURSOR_AT_MODE)
        return ERROR;

    if (key->state == KEY_ON) {
        // deal with press / long press.
        if (key->press_report_tic >= key->report_tic_interval || key->trigger_flag == TRIGGERED) {
            key->press_report_tic = 0;
            mx_parameter_value_callback(key->type);
            get_current_ui_page()->value_backup();
            get_current_ui_page()->draw_current_value();
        }
    } else if (key->state == KEY_OFF) {
        if (key->release_keep_tic > key->repeat_tic_interval) {
            menu_mx_parameter_value_key_repeat_action(key_t);
        }
    }
    return SUCCESS;
}

u8 menu_mx_parameter_value_key_repeat_action(void* key_t)
{
    return SUCCESS;
}



