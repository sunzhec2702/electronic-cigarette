#include "main_menu_temperature_value_key_action.h"
#include "key.h"
#include "Oled.h"
#include "system_state.h"
#include "value_manager.h"
#include "UI_manager.h"
#include "main_menu_temperature_value_manager.h"

static u16 temp_step[] = {5, 10, 100};

u8 main_menu_temperature_value_key_preaction(u8 pressed_keys, void * key_t)
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
    return SUCCESS;
}

u8 main_menu_temperature_value_key_trigger_action(void * key_t)
{
    key_state* key = (key_state*) key_t;
    if (key->state == KEY_ON) {
        if (key->type == KEY_INCREASE && *get_current_ui_page()->get_value_pointer(NULL) == MAX_TEMP_VALUE) {
            degree_mode_revert();
            *get_current_ui_page()->get_value_pointer(NULL) = MIN_TEMP_VALUE;
            if (can_draw_icons() == SUCCESS && get_system_lock() != SYS_LOCK)
                get_current_ui_page()->draw_current_value();
            return ERROR;
        } else if (key->type == KEY_REDUCE && *get_current_ui_page()->get_value_pointer(NULL) == MIN_TEMP_VALUE) {
            degree_mode_revert();
            *get_current_ui_page()->get_value_pointer(NULL) = MAX_TEMP_VALUE;
            if (can_draw_icons() == SUCCESS && get_system_lock() != SYS_LOCK)
                get_current_ui_page()->draw_current_value();
            return ERROR;
        }
    } else if (key->state == KEY_OFF) {
        key->report_tic_interval = REPORT_INTERVAL;   
    }
    return SUCCESS;
}

u8 main_menu_temperature_value_key_long_event_action(void* key_t)
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
        if (key->press_report_tic >= key->report_tic_interval || key->trigger_flag == TRIGGERED) {
            key->press_report_tic = 0;
            if (key->press_keep_tic > 2 * key->long_press_interval) {
                value_update_step(get_current_ui_page()->get_value_pointer(NULL), temp_step, 2, key->type, MIN_TEMP_VALUE, MAX_TEMP_VALUE);
            } else if (key->press_keep_tic > key->long_press_interval) {
                value_update_step(get_current_ui_page()->get_value_pointer(NULL), temp_step, 1, key->type, MIN_TEMP_VALUE, MAX_TEMP_VALUE);
            } else {
                value_update_step(get_current_ui_page()->get_value_pointer(NULL), temp_step, 0, key->type, MIN_TEMP_VALUE, MAX_TEMP_VALUE);
            }
            get_current_ui_page()->value_backup();
            get_current_ui_page()->draw_current_value();
        }
    } else if (key->state == KEY_OFF) {
        if (key->release_keep_tic > key->repeat_tic_interval) {
            main_menu_temperature_value_key_repeat_action(key_t);
        }
    }
    return SUCCESS;

}

u8 main_menu_temperature_value_key_repeat_action(void* key_t)
{
    key_state* key = (key_state *) key_t;
    // We need to clear the repeat count after we finish the action.*/
    key->repeat_count = 0;
    return SUCCESS;
}
