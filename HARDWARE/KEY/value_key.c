#include "value_key.h"
#include "key.h"
#include "system_state.h"
#include "oled_content.h"
#include "value_manager.h"

u8 value_key_preaction(u8 pressed_keys, void * key_t)
{
    if (pressed_keys > 1)
        return ERROR;
    return SUCCESS;
}

// For power key state trigger function.
u8 value_key_trigger_action(void* key_t)
{
    return SUCCESS;
}

// LONG EVENT ACTION.
u8 value_key_long_event_action(void * key_t)
{
    u8 smoke_state;
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
        if (key->press_report_tic >= key->report_tic_interval || key->press_report_tic == 0) {
            u8 value_type;
            key->press_report_tic = 0;
            value_type = (value_read(CURRENT_MODE) == POWER_MODE) ? POWER_VALUE : PRESET_VOLTAGE_VALUE;
            if (key->press_keep_tic > key->long_press_interval) {
                value_update_step(value_type, VALUE_10_STEP, key->type);
            } else {
                value_update_step(value_type, VALUE_1_STEP, key->type);
            }
            draw_current_value(value_type);
        }
    } else if (key->state == KEY_OFF) {
        if (key->release_keep_tic > key->repeat_tic_interval) {
            key->repeat_event_action(key_t);
        }
    }
    return SUCCESS;

}

// REPEAT KEY ACTION.
u8 value_key_repeat_action(void* key_t)
{
    key_state* key = (key_state *) key_t;
    // We need to clear the repeat count after we finish the action.*/
    key->repeat_count = 0;
    return SUCCESS;

}

