#include "peripherals_manager.h"
#include "system_state.h"
#include "value_manager.h"
#include "hw_checker.h"
#include "battery_manager.h"
#include "oled_content.h"
#include "task_scheduler.h"
#include "UI_manager.h"
#include "pid_console_manager.h"
#include "PID.h"

static u8 current_coil_exist = COIL_NOT_EXIST;
static u8 charger_plug_flag = CHARGER_UNPLUGGED;
static u16 environment_temerature = 25;
static u16 coil_r_static = REG_OPEN;
static u8 coil_count = 0;


void peripherals_init()
{
    coil_r_static_restore();
    charger_init();
}

void charger_init()
{
    RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOA, ENABLE); // Enable Charger GPIO
}

/*
 * Use this function to update the status of coils, ntc temperature and charger.
 */
void peripherals_update_task()
{
    coils_state_task();
    ntc_temperature_task();
    charger_update_task();
}

void coils_state_task()
{
    if (value_read(COIL_EXIST_FLAG) == COIL_EXIST) {
        if (current_coil_exist == COIL_NOT_EXIST) {
            // Delay
            if (coil_count < 30) {
                coil_count++;
            } else {
                send_pid_command(CMD_MEAS_REG, PID_NOT_RESET);
                coil_count = 0;
            }
            // At the first boot, 
            // Command MEASURE REG has not been sent yet, the value we read is 0. We should not update the static value.
            if (value_read(REGISTER_VALUE) != REG_OPEN && value_read(REGISTER_VALUE) != 0 && get_current_pid_command() == CMD_STOP) {
                if (value_read(REGISTER_VALUE) > coil_r_static + COIL_R_STATIC_OFFSET) {
                    if (can_draw_icons() == SUCCESS) {
                        switch_to_ui_page(MENU_NEW_COIL_CHECK_ID);
                    }
                } else if (value_read(REGISTER_VALUE) < coil_r_static) {
                    coil_r_static_update();
                    set_coil_ready_flag();
                } else {
                    set_coil_ready_flag();
                }
                if (can_draw_icons() == SUCCESS && get_system_lock() != SYS_LOCK) {
                    get_current_ui_page()->draw_current_value();
                }
                current_coil_exist = COIL_EXIST;
            }
        } else {
            if (value_read(REGISTER_VALUE) != REG_OPEN && value_read(REGISTER_VALUE) < coil_r_static) {
                coil_r_static = value_read(REGISTER_VALUE);
                coil_r_static_backup();
            }
        }
    } else {
        if (current_coil_exist == COIL_EXIST) {
            send_pid_command(CMD_MEAS_REG, PID_NOT_RESET);
            if (value_read(REGISTER_VALUE) == REG_OPEN) {
                if (can_draw_icons() == SUCCESS)
                    get_current_ui_page()->draw_whole_screen();
                current_coil_exist = COIL_NOT_EXIST;
                clear_coil_ready_flag();
            }
        }
    }
}

void ntc_temperature_task()
{
    u16 current_environment_temperature = value_read(NTC_TEMPERATURE);
    if (current_environment_temperature < environment_temerature) {
        environment_temperature_update(current_environment_temperature);
    }
}

void charger_update_task()
{
    u8 state;
    state = get_system_state();
    if (check_charging() == CHARGING) {
        if (get_charger_plug_flag() == CHARGER_UNPLUGGED) {
            set_charger_plug_flag();
            task_enable(TASK_ID_CHARGING_ANIMATION, TASK_ENABLE);
        }
    } else {
        if (get_charger_plug_flag() == CHARGER_PLUGGED) {
            task_enable(TASK_ID_CHARGING_ANIMATION, TASK_DISABLE);
            clear_charger_plug_flag();
            if (can_draw_icons() == SUCCESS)
                draw_current_battery();
            if (state == STATE_CHARGING) {
                system_init();
            }
        }
    }
}

/************************************ CHARGER flag in RTC register ***************************************/
void set_charger_plug_flag()
{
    charger_plug_flag = CHARGER_PLUGGED;
    //value_backup_func(CHARGER_FLAG_REG_VALUE, CHARGER_FLAG_OFFSET_VALUE, CHARGER_FLAG_MASK_VALUE, CHARGER_PLUGGED);
}

void clear_charger_plug_flag()
{
    charger_plug_flag = CHARGER_UNPLUGGED;
    //value_backup_func(CHARGER_FLAG_REG_VALUE, CHARGER_FLAG_OFFSET_VALUE, CHARGER_FLAG_MASK_VALUE, CHARGER_UNPLUGGED);
}

u8 get_charger_plug_flag()
{
    return charger_plug_flag;
    //return value_restore_func(CHARGER_FLAG_REG_VALUE, CHARGER_FLAG_OFFSET_VALUE, CHARGER_FLAG_MASK_VALUE);
}

/************************************ COIL EXIST flag in RTC register ***************************************/
void set_coil_ready_flag()
{
    value_backup_func(COIL_READY_FLAG_REG_VALUE, COIL_READY_FLAG_OFFSET_VALUE, COIL_READY_FLAG_MASK_VALUE, COIL_READY);
}
void clear_coil_ready_flag()
{
    value_backup_func(COIL_READY_FLAG_REG_VALUE, COIL_READY_FLAG_OFFSET_VALUE, COIL_READY_FLAG_MASK_VALUE, COIL_NOT_READY);
}

u8 get_coil_ready_flag()
{
    return value_restore_func(COIL_READY_FLAG_REG_VALUE, COIL_READY_FLAG_OFFSET_VALUE, COIL_READY_FLAG_MASK_VALUE);
}

/************************************ COIL Register static in RTC register ***************************************/
u16 get_coil_r_static()
{
    return coil_r_static;
}

void coil_r_static_update()
{
    coil_r_static = value_read(REGISTER_VALUE);
    value_write(REGISTER_STATIC_VALUE, coil_r_static);
    coil_r_static_backup();
}

void coil_r_static_backup()
{
    value_backup_func(COIL_R_STATIC_REG_VALUE, COIL_R_STATIC_OFFSET_VALUE, COIL_R_STATIC_MASK_VALUE, coil_r_static);
}


void coil_r_static_restore()
{
    u16 temp_r_static = value_restore_func(COIL_R_STATIC_REG_VALUE, COIL_R_STATIC_OFFSET_VALUE, COIL_R_STATIC_MASK_VALUE);
    coil_r_static = (temp_r_static == 0) ? coil_r_static : temp_r_static;
    value_write(REGISTER_STATIC_VALUE, coil_r_static);
}

/************************************ Environment Temperature ***************************************/
void environment_temperature_update(u16 temperature)
{
    environment_temerature = temperature;
}

u16 get_environment_temperature()
{
    return environment_temerature;
}


