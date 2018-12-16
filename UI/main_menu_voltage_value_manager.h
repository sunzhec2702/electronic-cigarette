#ifndef __MAIN_MENU_VOLTAGE_VALUE_MANAGER_H
#define __MAIN_MENU_VOLTAGE_VALUE_MANAGER_H
#include "sys.h"

#define MIN_PRESET_VOLTAGE_VALUE      5


#define VOLTAGE_VALUE_REG_INDEX       1
#define VOLTAGE_VALUE_OFFSET          16
#define VOLTAGE_VALUE_LEN_MASK        0xFFFF

extern void main_voltage_value_backup(void);
extern void main_voltage_value_restore(void);
extern u32* main_voltage_get_value_pointer(u8 para);
extern void main_voltage_value_update_backup(void);

#endif

