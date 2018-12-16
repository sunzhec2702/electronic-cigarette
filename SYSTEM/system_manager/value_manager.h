#ifndef __VALUE_MANAGER
#define __VALUE_MANAGER
#include "sys.h"

#define SMOKE_VOLTAGE_THRES 999
#define NORMAL_VOLTAGE_THRES 666

#define REG_OPEN        0xFFFF

#define VOLTAGE_VALUE               1
#define REGISTER_VALUE              2
#define BATTERY_VALUE               3
#define CURRENT_VALUE               4
#define TEMPERATURE_FLAG            5
#define BATTERY_LEVEL               6
#define STATIC_BATTERY_VALUE        7
#define MAX_PRESET_VOLTAGE_VALUE    8
#define COIL_EXIST_FLAG             9
#define NTC_TEMPERATURE             10
#define COIL_TEMPERATURE            11
#define REGISTER_STATIC_VALUE       12
#define TCR_KKM_VALUE               13
#define PID_POWER_SET_VALUE         14
#define MAX_PRESET_POWER_VALUE      15
#define PID_POWER_RT_OUT_VALUE      16
#define PID_WEAK_MAX_POWER_OUT_LIMIT    17

#define TEMP_HIGH       1
#define TEMP_NORMAL     0

#define COIL_EXIST      1
#define COIL_NOT_EXIST  0



#define PRESET_VALUE 98
#define ALL_VALUES 99

/*
#define POWER_MODE 0
#define VOLTAGE_MODE 1
#define TEMPERATURE_MODE 2
*/

typedef struct {
    u8 init_flag;
} value_struct;

extern void values_init(void);

extern u16 value_read(u8 value_type);
extern void value_write(u8 value_type, u32 value);
extern void value_update_step(u32* current_value_pt, u16* step_array, u8 step_index, u8 key_type, u16 min, u16 max);

extern void value_backup_func(u8 reg_index, u8 offset, u16 len_mask, u16 value);
extern u16 value_restore_func(u8 reg_index, u8 offset, u16 len_mask);
extern u32 get_max_voltage(void);

//extern void value_update(u8 value_type, u16 value);
/*
void max_voltage_update(void);

*/
#endif
