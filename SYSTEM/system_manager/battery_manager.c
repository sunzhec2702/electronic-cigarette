#include "battery_manager.h"
#include "hw_checker.h"
#include "battery_charging_animation.h"
#include "system_state.h"
#include "oled_content.h"
#include "flag_manager.h"
#include "oled.h"
#include "PID.h"
#include "value_manager.h"
#include "PWM_TIM1.h"
#include "key.h"
#include "pid_console_manager.h"
#include "UI_manager.h"

static u16 static_battery_update_cnt = 0;
static u16 last_battery_value = 0;
static u8 last_charging_threshold = DISCHARGING;
void charging_animation_task()
{
    u8 state;
    
    state = get_system_state();
    if (state == STATE_CHARGING) {
        draw_charging_animation();
    } else if (state == STATE_NORMAL) {
        draw_charging_animation_power_on();
    }
}

void static_battery_value_update_task()
{
    if (get_system_lock() != SYS_LOCK) {
        if (static_battery_update_cnt == 0 || static_battery_update_cnt >= STATIC_BATTERY_UPDATE_PERIOD_CNT) {
            static_battery_update_cnt = 0;
            // Smoking is not allowed if the battery value is less than protest value.
            if (value_read(STATIC_BATTERY_VALUE) >= BATTERY_UNPROTECT_VALUE) {
                value_backup_func(BATTERY_SMOKE_REG_VALUE, BATTERY_SMOKE_OFFSET_VALUE, BATTERY_SMOKE_MASK_VALUE, BATTERY_SMOKE_UNPROTECT);
            } else if (value_read(STATIC_BATTERY_VALUE) < BATTERY_PROTECT_VALUE) {
                value_backup_func(BATTERY_SMOKE_REG_VALUE, BATTERY_SMOKE_OFFSET_VALUE, BATTERY_SMOKE_MASK_VALUE, BATTERY_SMOKE_PROTECT);
            }
            if (get_system_smoke() != SYS_SMOKE && get_system_smoke() != SYS_SMOKE_DONE) {
                send_pid_command(CMD_MEAS_VOLTAGE, PID_NOT_RESET);
            }
            if (check_charging() != CHARGING && can_draw_icons() == SUCCESS && get_system_smoke() != SYS_SMOKE) {
                draw_current_battery();
                #ifdef DEBUG_CHARGING_BATTERY_VALUE
                draw_register_value(value_read(STATIC_BATTERY_VALUE));
                draw_voltage_value(get_battery_level());
                #endif
                // Show Low Battery Message and power off.
                if (check_battery() == ERROR) {
                    check_system_state();
                }
            }
        }
        static_battery_update_cnt++;
    }
}

u8 get_battery_level()
{
    u16 now_value;
    // First time to read the battery value.
    if (last_battery_value == 0) {
        now_value = value_read(STATIC_BATTERY_VALUE);
        last_battery_value = now_value;
    } else {
        now_value = (3*last_battery_value + value_read(STATIC_BATTERY_VALUE))>>2;
    }
    // Just in case that the ADC is not ready.
    if (now_value == 0)
        return BATTERY_LEVEL_NOT_INIT;
    
    // ADC precision issue.
    if (check_charging() == DISCHARGING || now_value <= last_battery_value - BATTERY_LEVEL_CAL_OFFSET) {
        last_battery_value = now_value;
        last_charging_threshold = DISCHARGING;
        return get_using_battery_level(now_value);
    } else if (check_charging() == CHARGING || now_value > last_battery_value + BATTERY_LEVEL_CAL_OFFSET) {
        last_battery_value = now_value;
        last_charging_threshold = CHARGING;
        return get_charging_battery_level(now_value);
    } else {
        last_battery_value = now_value;
        switch(last_charging_threshold) {
            case DISCHARGING:
                return get_using_battery_level(now_value);
            case CHARGING:
                return get_charging_battery_level(now_value);
            default:
                return get_using_battery_level(now_value);
        }
    }
}

u8 get_charging_battery_level(u16 battery_value)
{
    if (battery_value >= BATTERY_LEVEL0_HIGH)
        return 0;
    else if (battery_value >= BATTERY_LEVEL1_HIGH)
        return 1;
    else if (battery_value >= BATTERY_LEVEL2_HIGH)
        return 2;
    else if (battery_value >= BATTERY_LEVEL3_HIGH)
        return 3;
    else if (battery_value >= BATTERY_LEVEL4_HIGH)
        return 4;
    else
        return 5;
}

u8 get_using_battery_level(u16 battery_value)
{
    if (battery_value <= BATTERY_LEVEL4_LOW)
        return 5;
    else if (battery_value <= BATTERY_LEVEL3_LOW)
        return 4;
    else if (battery_value <= BATTERY_LEVEL2_LOW)
        return 3;
    else if (battery_value <= BATTERY_LEVEL1_LOW)
        return 2;
    else if (battery_value <= BATTERY_LEVEL0_LOW)
        return 1;
    else
        return 0;
}





