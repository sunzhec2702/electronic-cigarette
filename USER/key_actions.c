#include "key_actions.h"
#include "key.h"
#include "screen.h"
#include "led.h"
#include "value_manager.h"
#include "oled_content.h"
#include "system_state.h"
#include "delay.h"
#include "timer.h"
#include "hw_checker.h"
#include "PID.h"
#include "pwr_manager.h"
#include "UI_manager.h"

ui_page* current_ui_page;

void keys_actions(void)
{
    u8 state = get_system_state();
    if (state == STATE_NORMAL || state == STATE_DISPLAYOFF || state == STATE_CHARGING) {
        u8 index, system_state, trigger_flag[KEY_NUMBER],ret, sleep_state_flag = 0, pressed_keys = 0;
        u32 system_interval;
        key_state* keys;

        system_state = get_system_state();
        system_interval = (system_state == STATE_NORMAL) ? SYS_DIS_OFF_TIME : SYS_SLEEP_TIME;
        keys = get_keys_state();
        current_ui_page = get_current_ui_page();

        // Key state udpate.
        for (index = 0; index < KEY_NUMBER; index++) {
            key_state *key = &keys[index];
            trigger_flag[index] = NOT_TRIGGER;
            key->trigger_flag = NOT_TRIGGER;
            // ON/OFF Switch trigger state.
            if (key->state == KEY_OFF && key->press_tic > 0) {
                // deal with the debounce.
                if (key->press_tic >= key->stable_tic_num) {
                    trigger_flag[index] = TRIGGERED;
                    key->trigger_flag = TRIGGERED;
                    key_state_process(key, KEY_ON);
                }
            } else if (key->state == KEY_ON && key->release_tic > 0) {
                // deal with the debounce.
                if (key->release_tic >= key->stable_tic_num) {
                    trigger_flag[index] = TRIGGERED;
                    key->trigger_flag = TRIGGERED;
                    key_state_process(key, KEY_OFF);
                }
            }
            if (key->state == KEY_ON)
                pressed_keys++;
        }

        // Common key preation.
        ret = common_key_pre_action(pressed_keys);
        if (ret == ERROR) {
            common_pre_action_error(trigger_flag, (void*)keys);
            return;
        }

        // Combine Key action.
        ret = current_ui_page->combine_event_callback(keys);
        if (ret == ERROR)
            return;


        // Each key action.
        for (index = 0; index < KEY_NUMBER; index++) {
            key_state *key = &keys[index];

            // Check if the key's callback is null or not.
            if (key->key_callback == NULL)
                continue;

            if (get_system_lock() == SYS_LOCK && key->state == KEY_ON)
                continue;
                
            // each key preation.
            ret = key->key_callback->pre_action(pressed_keys, (void*) key);
            if (ret == ERROR) {
                continue;
            }

            // If it is a ON/OFF switch, do the trigger acton.
            if (trigger_flag[index] == TRIGGERED) {
                ret = key->key_callback->trigger_action((void*) key);
                if (ret == ERROR)
                    continue;
            }

            // Normal state
            ret = key->key_callback->long_event_action((void*) key);
            //ret = key->long_event_action((void*) key);
            if (ret == ERROR) {
                continue;
            }
        }

        for (index = 0; index < KEY_NUMBER; index++) {
            key_state *key = &keys[index];
            // Check if we need to turn off display or sleep.
            if (key->release_keep_tic * TIMER_PERIOD > system_interval) {
                sleep_state_flag++;
            }
        }

        if (sleep_state_flag == KEY_NUMBER) {
            set_system_state(((get_system_state() == STATE_DISPLAYOFF) ? STATE_SLEEP : STATE_DISPLAYOFF));
        }
    }
}


// NORMAL ACTION.
void key_state_process(key_state *key, u8 state)
{
    switch (state) {
    case KEY_ON:
        key->state = KEY_ON;
        key->press_tic = 0;
        key->press_report_tic = 0;
        key->repeat_count++;
        key->release_keep_tic = 0;
        break;
    case KEY_OFF:
        key->state = KEY_OFF;
        key->release_tic = 0;
        key->press_keep_tic = 0;
        break;
    default:
        break;
    }
}

u8 common_key_pre_action(u8 pressed_keys)
{
    if (get_system_state() == STATE_SLEEP) {
        return ERROR;
    }
    if (get_system_state() == STATE_DISPLAYOFF && pressed_keys > 0) {
        system_init();
        return SUCCESS;
    }
    return SUCCESS;
}

void common_pre_action_error(u8 trigger_flag[], void * key_t)
{
    u8 index;
    key_state * key = (key_state *) key_t;
    for (index = 0; index < KEY_NUMBER; index++) {
        if (trigger_flag[index] == TRIGGERED) {
            if (key->state == KEY_ON) {
                key->repeat_count--;
            } else {
                // Do nothing.
            }
        } else {
            // Do nothing.
        }
        key++;
    }
}

u8 combine_key_action(key_state * keys)
{
    return current_ui_page->combine_event_callback(keys);
}
