#include "hw_checker.h"
#include "hw_checker_content.h"
#include "UI_manager.h"
#include "peripherals_manager.h"
#include "value_manager.h"
#include "battery_manager.h"
#include "exti_charging.h"
#include "timer_key.h"
#include "PID.h"

u8 check_battery()
{
    
    u16 dynamic_battery_value = value_read(BATTERY_VALUE);
    u16 static_battery_value = value_read(STATIC_BATTERY_VALUE);
    if ((Get_PID_Flow_Cnt() == PID_STOP_VBAT_LOW) ||
        (dynamic_battery_value <= BATTERY_PROTECT_DYNAMIC_VALUE) ||
        (value_restore_func(BATTERY_SMOKE_REG_VALUE, BATTERY_SMOKE_OFFSET_VALUE, BATTERY_SMOKE_MASK_VALUE) == BATTERY_SMOKE_PROTECT) ||
        (static_battery_value <= BATTERY_PROTECT_VALUE)) {
        // Users are not allowed to smoke again in any low battery issues until the static battery value is more than unprotected value.
        value_backup_func(BATTERY_SMOKE_REG_VALUE, BATTERY_SMOKE_OFFSET_VALUE, BATTERY_SMOKE_MASK_VALUE, BATTERY_SMOKE_PROTECT);
        return ERROR;
    }
    return SUCCESS;
}

u8 check_coil_exist()
{
    if (Get_PID_Flow_Cnt() == PID_STOP_OPEN_CIRCUIT)
        return ERROR;
    if(value_read(COIL_EXIST_FLAG) == COIL_EXIST && value_read(REGISTER_VALUE) != REG_OPEN)
        return SUCCESS;
    return ERROR;
}

u8 check_voltage_out()
{
    u16 voltage = value_read(VOLTAGE_VALUE);
    if (voltage >= MAX_VOLTAGE_VALUE) {
        return ERROR;
    }
    return SUCCESS;
}

u8 check_high_temp()
{
    if (Get_PID_Flow_Cnt() == PID_STOP_OVER_TEMP)
        return ERROR;
    if (value_read(TEMPERATURE_FLAG) == TEMP_HIGH)
        return ERROR;
    return SUCCESS;
}

u8 check_low_temp()
{
    if (value_read(NTC_TEMPERATURE) == 0)
        return ERROR;
    return SUCCESS;
}

u8 check_register_load()
{
    u16 register_value = value_read(REGISTER_VALUE);
    if (register_value < MIN_REG_VALUE || register_value > MAX_REG_VALUE) {
        return ERROR;
    }
    return SUCCESS;
}

u8 check_charging()
{

    if (GPIO_ReadInputBit(CHARGING_GPIO, CHARGING_PIN) == CHARGING) {
        return CHARGING;
    } else {
        return DISCHARGING;
    }
}

u8 check_current_value()
{
    u16 current_value = value_read(CURRENT_VALUE);
    if (current_value > MAX_CURRENT_VALUE) {
        return ERROR;
    }
    return SUCCESS;
}

u8 check_hw_fire()
{
    if (check_coil_exist() == ERROR) {
        show_atomizer_message();
        ENABLE_FRESH_SCREEN_TIMER(SYS_LOCK);
        return ERROR;
    }
    if (get_coil_ready_flag() == COIL_NOT_READY) {
        switch_to_ui_page(MENU_NEW_COIL_CHECK_ID);
        return ERROR;
    }
    if (check_high_temp() == ERROR) {
        show_temp_high_message();
        ENABLE_FRESH_SCREEN_TIMER(SYS_LOCK);
        return ERROR;
    }
    if(check_voltage_out() == ERROR) {
        show_voltage_high_message();
        ENABLE_FRESH_SCREEN_TIMER(SYS_LOCK);
        return ERROR;
    }
    if (check_current_value() == ERROR) {
        show_current_high_message();
        ENABLE_FRESH_SCREEN_TIMER(SYS_LOCK);
        return ERROR;
    }
    if (check_battery() == ERROR) {
        show_battery_weak_message();
        ENABLE_FRESH_SCREEN_TIMER(SYS_LOCK);
        return ERROR;
    }
    if (check_low_temp() == ERROR) {
        show_temp_low_message();
        ENABLE_FRESH_SCREEN_TIMER(SYS_LOCK);
        return ERROR;
    }
    return SUCCESS;
}

