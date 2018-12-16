#include "main_menu_voltage_value_manager.h"
#include "UI_manager.h"
#include "oled.h"
#include "oled_content.h"
#include "value_manager.h"

static u32 voltage_value;
static u32 voltage_value_pid;

u32* main_voltage_get_value_pointer(u8 para)
{
    if (para == NULL)
        return &voltage_value;
    else if (para == PID_VALUE) {
        return &voltage_value_pid;
    }
    return NULL;
}

void main_voltage_value_backup()
{
    voltage_value_pid = (voltage_value << 15) / 100;
    value_backup_func(VOLTAGE_VALUE_REG_INDEX, VOLTAGE_VALUE_OFFSET, VOLTAGE_VALUE_LEN_MASK, voltage_value);
}

void main_voltage_value_restore()
{
    u16 bkr_value = value_restore_func(VOLTAGE_VALUE_REG_INDEX, VOLTAGE_VALUE_OFFSET, VOLTAGE_VALUE_LEN_MASK);
    if (bkr_value == 0)
        voltage_value = MIN_PRESET_VOLTAGE_VALUE;
    else
        voltage_value = bkr_value;
    voltage_value_pid = (voltage_value << 15) / 100;
}

