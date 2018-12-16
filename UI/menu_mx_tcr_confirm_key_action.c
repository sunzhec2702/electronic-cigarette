#include "menu_mx_tcr_confirm_key_action.h"
#include "menu_mx_tcr.h"
#include "key.h"
#include "pwr_manager.h"
#include "temperature_mode_select_menu.h"

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
        switch(get_current_ui_id()) {
            case MENU_MX_TCR_ID:
                switch_to_ui_page(MENU_MX_MAX_POWER_ID);
                break;
            case MENU_MX_MAX_POWER_ID:
                switch_to_ui_page(get_temperature_mode_ui_id());
                break;
        }
        /*
        mx_parameter_cursor_callback(key->type);
        get_current_ui_page()->draw_current_value();
        */
    }

    return SUCCESS;
}

u8 menu_mx_parameter_confirm_key_long_event_action(void* key_t)
{
    key_state* key = (key_state*) key_t;
    if (key->type != KEY_CONFIRM) {
        return ERROR;
    }
    return SUCCESS;
}

u8 menu_mx_parameter_confirm_key_repeat_action(void* key_t)
{
    return SUCCESS;
}
