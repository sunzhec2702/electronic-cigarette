#include "main_menu_temperature_confirm_key_action.h"
#include "main_menu_temperature.h"
#include "key.h"
#include "timer_key.h"
#include "hw_checker.h"
#include "value_manager.h"
#include "system_state.h"
#include "UI_manager.h"
#include "pwr_manager.h"
#include "PID.h"
#include "pid_console_manager.h"
#include "peripherals_manager.h"

static u16 smoke_time_record = 0;

u8 main_menu_temperature_confirm_key_preaction(u8 pressed_keys, void * key_t)
{
    return SUCCESS;
}

u8 main_menu_temperature_confirm_key_trigger_action(void * key_t)
{
    key_state* key = (key_state*) key_t;
    if (key->state == KEY_ON) {
    }
    if (key->state == KEY_OFF) {
        // clear flag
        set_pid_lock(PID_UNLOCK);
        reset_smoke_start_tic();
        reset_weak_start_tic();

        // Confirm Key release, redraw the set value from smoke time.
        if (get_system_smoke() == SYS_SMOKE || get_system_smoke() == SYS_SMOKE_DONE) {
            if (get_system_lock() != SYS_LOCK)
                draw_smoke_time(smoke_time_record*SMOKE_RT_PARA_UPDATE_INTERVAL * TIMER_PERIOD / 100);
            ENABLE_FRESH_SCREEN_TIMER(SYS_UNLOCK);
        }
        send_pid_command(CMD_STOP, PID_NOT_RESET);
    }
    return SUCCESS;
}

u8 main_menu_temperature_confirm_key_long_event_action(void* key_t)
{
    key_state* key = (key_state*) key_t;
    if (key->type != KEY_CONFIRM) {
        return ERROR;
    }

    if (key->state == KEY_ON) {
        if (get_system_state() == STATE_CHARGING)
            return ERROR;

        // pre deal the register issue.
        if ((key->press_keep_tic >= CONFIRM_KEY_PREPARE_TIME) && get_pid_lock() == PID_UNLOCK) {
            set_pid_lock(PID_LOCK);
        }

        // deal with press / long press. We all need to report time.
        if (key->press_report_tic >= key->report_tic_interval || key->press_report_tic == 0) {
            key->press_report_tic = 0;
            if ((key->press_keep_tic >= CONFIRM_KEY_PREPARE_TIME) && ((key->press_keep_tic >= key->long_press_interval) || get_system_smoke() == SYS_SMOKE) && (get_system_smoke() != SYS_SMOKE_DONE)) {
                if (get_smoke_start_tic() == SMOKE_START_DUMMY_TIC) {
                    set_smoke_start_tic(key->press_keep_tic);
                    smoke_time_record = 0;
                }
                // HW check. We need to check all the HW before firing
                if (check_hw_fire() == ERROR) {
                    // clear flag
                    set_pid_lock(PID_UNLOCK);
                    reset_smoke_start_tic();
                    send_pid_command(CMD_STOP, PID_RESET);
                    set_system_smoke(SYS_SMOKE_DONE);
                    return ERROR;
                }
                if ((key->press_keep_tic - get_smoke_start_tic()) < SMOKE_MAX_TIME_NUMBER) {
                    key->repeat_count = 0;
                    send_pid_command(CMD_SMOKE, PID_NOT_RESET);
                    if ((key->press_keep_tic - get_smoke_start_tic()) >= (smoke_time_record)*SMOKE_RT_PARA_UPDATE_INTERVAL) {
                        if ((smoke_time_record % SMOKE_RT_PARA_UPDATE_FACTOR) == 0) {
                            draw_real_time_coil_temperature(value_read(COIL_TEMPERATURE) + get_smoke_time_temperature(), get_degree_mode());
                            draw_current_value(REGISTER_VALUE);
                            draw_current_value(PID_POWER_SET_VALUE);
                        }
                        smoke_time_record++;
                    }
                    //draw_smoke_time((key->press_keep_tic - smoke_start_tic) * TIMER_PERIOD / 100);

                    // QIDONG
                    // Power ... Draw Voltage...
                } else { // exceed the max time.
                    // Redraw the MAX SMOKE TIME in case that the (key->press_report_tic - key->long_press_interval > MAX_TIME_NUMER) jump from < to > without ==
                    set_pid_lock(PID_UNLOCK);
                    draw_smoke_time(SMOKE_MAX_TIME_NUMBER * TIMER_PERIOD / 100);
                    send_pid_command(CMD_STOP, PID_RESET);
                    set_system_smoke(SYS_SMOKE_DONE);
                }
            }
        }
    } else if (key->state == KEY_OFF) {
        if (key->release_keep_tic > key->repeat_tic_interval) {
            main_menu_temperature_confirm_key_repeat_action(key_t);
        } else if (key->repeat_count >= 5){
            if (get_system_state() == STATE_CHARGING) {
                reboot_system(SUCCESS);
            } else {
                set_system_state(STATE_SLEEP);
            }
        }
    }
    return SUCCESS;
}

u8 main_menu_temperature_confirm_key_repeat_action(void* key_t)
{
    key_state * key = (key_state *) key_t;
    if (key->repeat_count == 3 && get_system_state() == STATE_NORMAL) {
        switch_to_ui_page(SMOKE_MODE_SELECT_ID);
    }

    if (key->repeat_count == 5) {
        if (get_system_state() == STATE_CHARGING) {
            reboot_system(SUCCESS);
        } else {
            set_system_state(STATE_SLEEP);
        }
    }

    // We need to clear the repeat count after we finish the action.
    key->repeat_count = 0;
    return SUCCESS;
}
