#include "main_menu_temperature_value_manager.h"
#include "value_manager.h"
#include "main_menu_temperature.h"
#include "peripherals_manager.h"
#include "menu_mx_tcr_value_manager.h"

static u32 preset_temperature;
static u32 preset_temperature_delta;
static u16 smoke_enviroument_temperature;
static u8 temperature_degree_mode;

u32* main_menu_temperature_get_value_pointer(u8 para)
{
    smoke_time_temperature_update();
    if (para == NULL)
        return &preset_temperature;
    if (para == PID_VALUE) {
        return &preset_temperature_delta;
    }
    return NULL;
}

u8 get_degree_mode()
{
    return temperature_degree_mode;
}

void degree_mode_revert()
{
    temperature_degree_mode = !temperature_degree_mode;
}

void main_menu_temperature_value_backup()
{
    value_backup_func(TEMP_VALUE_REG_INDEX, TEMP_VALUE_OFFSET, TEMP_VALUE_LEN_MASK, preset_temperature);
    value_backup_func(TEMP_DEGREE_MODE_REG_INDEX, TEMP_DEGREE_MODE_OFFSET, TEMP_DEGREE_MODE_LEN_MASK, temperature_degree_mode);
    smoke_time_temperature_update();
}

void main_menu_temperature_value_restore()
{
    u16 bkr_value;
    bkr_value = value_restore_func(TEMP_VALUE_REG_INDEX, TEMP_VALUE_OFFSET, TEMP_VALUE_LEN_MASK);
    temperature_degree_mode = value_restore_func(TEMP_DEGREE_MODE_REG_INDEX, TEMP_DEGREE_MODE_OFFSET, TEMP_DEGREE_MODE_LEN_MASK);
    if (bkr_value == 0)
        preset_temperature = MIN_TEMP_VALUE;
    else
        preset_temperature = bkr_value;

}

u32 get_current_TCR()
{
    switch(get_current_ui_id()) {
        case MAIN_MENU_TEMP_NI_ID:
            return CONST_NI_PPM;
        case MAIN_MENU_TEMP_TI_ID:
            return CONST_TI_PPM;
        case MAIN_MENU_TEMP_SS_ID:
            return CONST_SS316_PPM;
        case MAIN_MENU_TEMP_M1_ID:
        case MAIN_MENU_TEMP_M2_ID:
        case MAIN_MENU_TEMP_M3_ID:
            return (*mx_tcr_get_value_pointer(get_current_ui_id()))*10;
        default:
            return CONST_NI_PPM;
        
    }
}

u32 get_current_max_power_value()
{
    switch(get_current_ui_id()) {
        case MAIN_MENU_TEMP_NI_ID:
        case MAIN_MENU_TEMP_TI_ID:
        case MAIN_MENU_TEMP_SS_ID:
            return MAX_MX_POWER_VALUE;
        case MAIN_MENU_TEMP_M1_ID:
        case MAIN_MENU_TEMP_M2_ID:
        case MAIN_MENU_TEMP_M3_ID:
            return (*mx_max_power_get_value_pointer(get_current_ui_id()));
        default:
            return MAX_MX_POWER_VALUE;
    }
}

void smoke_time_temperature_update()
{
    smoke_enviroument_temperature = get_environment_temperature();
    preset_temperature_delta = (preset_temperature - smoke_enviroument_temperature)<<15;
}

u16 get_smoke_time_temperature()
{
    return smoke_enviroument_temperature;
}


