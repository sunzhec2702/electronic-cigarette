#include "main_menu_power_value_manager.h"
#include "UI_manager.h"
#include "main_menu_power.h"
#include "main_menu_voltage.h"
#include "oled.h"
#include "oled_content.h"
#include "value_manager.h"
#include "hw_checker.h"

static u32 power_value;
static u32 power_value_pid;
static u32 voltage_value;
static u32 voltage_value_pid;

u32* main_power_get_value_pointer(u8 para)
{
    switch(get_current_ui_id()) {
        case MAIN_MENU_POWER_ID:
            if (para == NULL)
                return &power_value;
            else if (para == PID_VALUE) {
                return &power_value_pid;
            }
            break;
        case MAIN_MENU_VOLTAGE_ID:
            if (para == NULL)
                return &voltage_value;
            else if (para == PID_VALUE) {
                return &voltage_value_pid;
            }
            break;
    }
    return NULL;
}

void main_power_value_backup()
{
    power_value_pid = (power_value << 15) / 10;
    value_backup_func(POWER_VALUE_REG_INDEX, POWER_VALUE_OFFSET, POWER_VALUE_LEN_MASK, power_value);
    voltage_value_pid = (voltage_value << 15) / 100;
    value_backup_func(VOLTAGE_VALUE_REG_INDEX, VOLTAGE_VALUE_OFFSET, VOLTAGE_VALUE_LEN_MASK, voltage_value);
}

void main_power_value_restore()
{
    u16 bkr_value = value_restore_func(POWER_VALUE_REG_INDEX, POWER_VALUE_OFFSET, POWER_VALUE_LEN_MASK);
    if (bkr_value == 0)
        power_value = MIN_POWER_VALUE;
    else
        power_value = bkr_value;
    power_value_pid = (power_value << 15) / 10;
    
    bkr_value = value_restore_func(VOLTAGE_VALUE_REG_INDEX, VOLTAGE_VALUE_OFFSET, VOLTAGE_VALUE_LEN_MASK);
    if (bkr_value == 0)
        voltage_value = MIN_PRESET_VOLTAGE_VALUE;
    else
        voltage_value = bkr_value;
    voltage_value_pid = (voltage_value << 15) / 100;
}

