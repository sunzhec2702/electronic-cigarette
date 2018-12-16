#include "menu_mode_select_value_key_action.h"
#include "menu_mode_select.h"
#include "key.h"
#include "system_state.h"

u8 menu_mode_select_value_key_preaction(u8 pressed_keys, void * key_t)
{
    if (pressed_keys > 1)
        return ERROR;
    return SUCCESS;
}

u8 menu_mode_select_value_key_trigger_action(void * key_t)
{
    return SUCCESS;
}

u8 menu_mode_select_value_key_long_event_action(void* key_t)
{
    key_state* key = (key_state *) key_t;
    if (key->type != KEY_INCREASE && key->type != KEY_REDUCE) {
        return ERROR;
    }
    
    if (get_system_state() == STATE_CHARGING)
        return ERROR;

    if (key->state == KEY_ON) {
        
        // deal with press / long press.
        if (key->press_report_tic >= key->report_tic_interval || key->press_report_tic == 0) {
            key->press_report_tic = 0;
            update_current_mode_index(key->type);
        }
    } else if (key->state == KEY_OFF) {
        if (key->release_keep_tic > key->repeat_tic_interval) {
            menu_mode_select_value_key_repeat_action(key_t);
        }
    }
    
    return SUCCESS;
}

u8 menu_mode_select_value_key_repeat_action(void* key_t)
{
    return SUCCESS;
}
