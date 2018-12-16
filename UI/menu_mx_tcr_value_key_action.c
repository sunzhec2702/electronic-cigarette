#include "menu_mx_tcr_value_key_action.h"
#include "menu_mx_tcr.h"
#include "key.h"
#include "system_state.h"
#include "value_manager.h"
#include "temperature_mode_select_menu.h"

static u16 step[] = {1,10};
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
    return SUCCESS;
}

u8 menu_mx_parameter_value_key_long_event_action(void* key_t)
{
    u16 min,max;
    key_state* key = (key_state *) key_t;
    u8 temperature_mode_index = get_temperature_mode_index();
    if (key->type != KEY_INCREASE && key->type != KEY_REDUCE) {
        return ERROR;
    }

    if (get_system_state() == STATE_CHARGING)
        return ERROR;

    if (key->state == KEY_ON) {
        // deal with press / long press.
        if (key->press_report_tic >= key->report_tic_interval || key->trigger_flag == TRIGGERED) {
            key->press_report_tic = 0;
            switch(get_current_ui_id()) {
                case MENU_MX_TCR_ID:
                    min = MIN_MX_TCR_VALUE;
                    max = MAX_MX_TCR_VALUE;
                    if (key->press_keep_tic > 2 * key->long_press_interval) {
                        value_update_step(get_current_ui_page()->get_value_pointer(get_temperature_mode_ui_id()), step, 1, key->type, min, max);
                    } else if (key->press_keep_tic > key->long_press_interval) {
                        value_update_step(get_current_ui_page()->get_value_pointer(get_temperature_mode_ui_id()), step, 1, key->type, min, max);
                    } else {
                        value_update_step(get_current_ui_page()->get_value_pointer(get_temperature_mode_ui_id()), step, 0, key->type, min, max);
                    }
                    break;
                case MENU_MX_MAX_POWER_ID:
                    min = MIN_MX_POWER_VALUE;
                    max = MAX_MX_POWER_VALUE;
                    if (key->press_keep_tic > key->long_press_interval) {
                        value_update_step(get_current_ui_page()->get_value_pointer(get_temperature_mode_ui_id()), step, 0, key->type, min, max);
                    } else {
                        value_update_step(get_current_ui_page()->get_value_pointer(get_temperature_mode_ui_id()), step, 0, key->type, min, max);
                    }
                    break;
            }

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



