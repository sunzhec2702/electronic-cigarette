#include "animation_power_off_charging_confirm_key_action.h"
#include "menu_mode_select.h"
#include "key.h"
#include "UI_manager.h"
#include "system_state.h"

u8 animation_power_off_charging_confirm_key_preaction(u8 pressed_keys, void * key_t)
{
    return SUCCESS;
}

// CONFIRM KEY TRIGGER ACTION.
u8 animation_power_off_charging_confirm_key_trigger_action(void * key_t)
{
    return SUCCESS;
}

u8 animation_power_off_charging_confirm_key_long_event_action(void* key_t)
{
    key_state* key = (key_state*) key_t;
    if (key->type != KEY_CONFIRM) {
        return ERROR;
    }

    if (key->state == KEY_ON) {
        if (get_system_state() != STATE_CHARGING)
            return ERROR;

        // deal with press / long press. We all need to report time.
        if (key->press_report_tic >= key->report_tic_interval || key->press_report_tic == 0) {
            key->press_report_tic = 0;
            if (key->press_keep_tic >= key->long_press_interval) {
                key->repeat_count = 0;
            }
        }
    } else if (key->state == KEY_OFF) {
        if (key->release_keep_tic > key->repeat_tic_interval) {
            animation_power_off_charging_confirm_key_repeat_action(key_t);
        }
    }
    return SUCCESS;
}

u8 animation_power_off_charging_confirm_key_repeat_action(void* key_t)
{
    return SUCCESS;
}

