#include "menu_new_coil_check_value_key_action.h"
#include "menu_new_coil_check.h"
#include "key.h"

u8 menu_new_coil_check_value_key_preaction(u8 pressed_keys, void * key_t)
{
    if (pressed_keys > 1)
        return ERROR;
    return SUCCESS;
}

u8 menu_new_coil_check_value_key_trigger_action(void* key_t)
{
    key_state* key = (key_state*) key_t;
    if (key->state == KEY_ON) {
        update_current_coil_select_index(key->type);
        return ERROR;
    }
    return SUCCESS;
}

u8 menu_new_coil_check_value_key_long_event_action(void * key_t)
{
    return SUCCESS;
}

u8 menu_new_coil_check_value_key_repeat_action(void* key_t)
{
    return SUCCESS;
}


