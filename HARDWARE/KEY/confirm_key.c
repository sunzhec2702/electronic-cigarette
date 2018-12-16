#include "confirm_key.h"
#include "key.h"
#include "system_state.h"
#include "oled_content.h"
#include "value_manager.h"
#include "timer.h"
#include "hw_checker.h"
#include "pwr_manager.h"

static u32 smoke_start_tic = SMOKE_START_DUMMY_TIC;

u8 comfirm_key_preaction(u8 pressed_keys, void * key_t)
{
    return SUCCESS;
}


// CONFIRM KEY TRIGGER ACTION.
u8 confirm_key_trigger_action(void * key_t)
{
    key_state* key = (key_state*) key_t;
    if (key->state == KEY_ON) {
        /*
        // UPDATE THE BATTERY ICON ONLY WHEN THE CONFIRM KEY IS PRESSED/RELEASED
        if (get_system_state() == STATE_NORMAL && get_system_lock() != SYS_LOCK)
            draw_current_battery();
        */
    }
    if (key->state == KEY_OFF) {
        // clear flag
        set_smoke_pid_flow_lock(SMOKE_PID_UNLOCK);
        smoke_start_tic = SMOKE_START_DUMMY_TIC;

        // Confirm Key release, redraw the set value from smoke time.
        if (get_system_smoke() == SYS_SMOKE || get_system_smoke() == SYS_SMOKE_DONE) {
            ENABLE_FRESH_SCREEN_TIMER(SYS_UNLOCK);
        }
        set_system_smoke(SYS_NOT_SMOKE);
    }
    return SUCCESS;

}

u8 confirm_key_long_event_action(void* key_t)
{
    key_state* key = (key_state*) key_t;
    if (key->type != KEY_CONFIRM) {
        return ERROR;
    }

    if (key->state == KEY_ON) {
        if (get_system_state() == STATE_CHARGING)
            return ERROR;

        // pre deal the register issue.
        if ((key->press_keep_tic >= CONFIRM_KEY_PREPARE_TIME) && get_smoke_pid_flow_lock() == SMOKE_PID_UNLOCK) {
            set_smoke_pid_flow_lock(SMOKE_PID_LOCK);
            set_system_smoke(SYS_MEASURE_REG);
        }

        // deal with press / long press. We all need to report time.
        if (key->press_report_tic >= key->report_tic_interval || key->press_report_tic == 0) {
            key->press_report_tic = 0;
            if ((key->press_keep_tic >= CONFIRM_KEY_PREPARE_TIME) && ((key->press_keep_tic >= key->long_press_interval) || (Get_PID_Flow_Cnt() == R_MEAS_DONE) || get_system_smoke() == SYS_SMOKE)) {
                if (smoke_start_tic == SMOKE_START_DUMMY_TIC) {
                    smoke_start_tic = key->press_keep_tic;
                }
                // HW check. We need to check all the HW before firing
                if (check_hw_fire() == ERROR) {
                    // clear flag
                    set_smoke_pid_flow_lock(SMOKE_PID_UNLOCK);
                    smoke_start_tic = SMOKE_START_DUMMY_TIC;
                    set_system_smoke(SYS_NOT_SMOKE);
                    return ERROR;
                }
                if ((key->press_keep_tic - smoke_start_tic) <= SMOKE_MAX_TIME_NUMBER) {
                    key->repeat_count = 0;
                    set_system_smoke(SYS_SMOKE);
                    draw_smoke_time((key->press_keep_tic - smoke_start_tic) * TIMER_PERIOD / 100);
                    draw_current_value(REGISTER_VALUE);
                    draw_current_value(VOLTAGE_VALUE);
                    // QIDONG
                    // Power ... Draw Voltage...
                } else { // exceed the max time.
                    // Redraw the MAX SMOKE TIME in case that the (key->press_report_tic - key->long_press_interval > MAX_TIME_NUMER) jump from < to > without ==
                    draw_smoke_time(SMOKE_MAX_TIME_NUMBER * TIMER_PERIOD / 100);
                    set_system_smoke(SYS_SMOKE_DONE);
                }
            }
        }
    } else if (key->state == KEY_OFF) {
        if (key->release_keep_tic > key->repeat_tic_interval) {
            confirm_key_repeat_action(key_t);
        }
    }
    return SUCCESS;
}

u8 confirm_key_repeat_action(void* key_t)
{
    key_state * key = (key_state *) key_t;
    if (key->repeat_count == 3 && get_system_state() == STATE_NORMAL) {
        current_mode_reverse();
        draw_current_value(PRESET_VALUE);
        //draw_current_battery();
    }

    if (key->repeat_count == 5) {
        if (get_system_state() == STATE_CHARGING) {
            clear_sleep_state_flags();
            NVIC_SystemReset();
        } else {
            set_system_state(STATE_SLEEP);
        }
    }

    // We need to clear the repeat count after we finish the action.
    key->repeat_count = 0;
    return SUCCESS;
}
