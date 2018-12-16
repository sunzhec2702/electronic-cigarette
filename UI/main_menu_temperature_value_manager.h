#ifndef __MAIN_MENU_TEMP_VALUE_MANAGER_H
#define __MAIN_MENU_TEMP_VALUE_MANAGER_H
#include "sys.h"
#define TEMP_DEGREE_SWITCH_OFFSET  185

// percent per 1,000,000
#define CONST_NI_PPM 		6087 // 6087 from book   // TBD
#define CONST_SS316_PPM     880  // TBD
#define CONST_TI_PPM 		3660   // TBD

#define DEGREE_C    0
#define DEGREE_F    1

#define MAX_TEMP_VALUE 315
#define MIN_TEMP_VALUE 100

#define TEMP_VALUE_REG_INDEX       2
#define TEMP_VALUE_OFFSET          0
#define TEMP_VALUE_LEN_MASK        0x7FFF

#define TEMP_DEGREE_MODE_REG_INDEX       2
#define TEMP_DEGREE_MODE_OFFSET          15
#define TEMP_DEGREE_MODE_LEN_MASK        0x1

extern void main_menu_temperature_value_backup(void);
extern void main_menu_temperature_value_restore(void);
extern void smoke_time_temperature_update(void);
extern u16 get_smoke_time_temperature(void);
extern u8 get_degree_mode(void);
extern void degree_mode_revert(void);
extern u32* main_menu_temperature_get_value_pointer(u8 para);
extern void main_menu_temperature_value_update_backup(void);
extern u32 get_current_TCR(void);
extern u32 get_current_max_power_value(void);
#endif

