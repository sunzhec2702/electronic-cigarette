#include "menu_mx_parameter_confirm_key_action.h"
#include "menu_mx_parameter.h"
#include "key.h"
#include "pwr_manager.h"

u8 menu_mx_parameter_confirm_key_preaction(u8 pressed_keys, void * key_t)
{
    return SUCCESS;
}

// CONFIRM KEY TRIGGER ACTION.
u8 menu_mx_parameter_confirm_key_trigger_action(void * key_t)
{
    key_state* key = (key_state*) key_t;
    if (key->state == KEY_ON) {

    }
    if (key->state == KEY_OFF) {
        mx_parameter_cursor_callback(key->type);
        get_current_ui_page()->draw_current_value();
    }

    return SUCCESS;
}

u8 menu_mx_parameter_confirm_key_long_event_action(void* key_t)
{
    key_state* key = (key_state*) key_t;
    if (key->type != KEY_CONFIRM) {
        return ERROR;
    }

    if (key->state == KEY_ON) {

        // deal with press / long press. We all need to report time.
        if (key->press_report_tic >= key->report_tic_interval || key->press_report_tic == 0) {
            key->press_report_tic = 0;
            if (key->press_keep_tic >= 2 * key->long_press_interval) {
                reboot_system();
            }
        }
    } else if (key->state == KEY_OFF) {
        if (key->release_keep_tic > key->repeat_tic_interval) {
            menu_mx_parameter_confirm_key_repeat_action(key_t);
        }
    }
    return SUCCESS;
}

u8 menu_mx_parameter_confirm_key_repeat_action(void* key_t)
{
    return SUCCESS;
}
