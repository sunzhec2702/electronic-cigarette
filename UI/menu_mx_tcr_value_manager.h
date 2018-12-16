#ifndef __MENU_MX_PARAMETER_VALUE_MANAGER_H
#define __MENU_MX_PARAMETER_VALUE_MANAGER_H
#include "sys.h"
#include "main_menu_power_value_manager.h"
#include "hw_checker.h"

#define MX_MODE_NUMBER      3

#define MIN_MX_TCR_VALUE                    1
#define MAX_MX_TCR_VALUE                    999
#define DEFAULT_MX_TCR_VALUE                500

// Another positin to change the max power value is at main_menu_power_value_manager.h
#define MIN_MX_POWER_VALUE          1
#define MAX_MX_POWER_VALUE          MAX_POWER_VALUE_W
#define DEFAULT_MX_POWER_VALUE      MAX_POWER_VALUE_W

#define M1_TRC_REG_INDEX       0
#define M1_TRC_OFFSET          0
#define M1_TRC_LEN_MASK        0x3FF
#define M2_TRC_REG_INDEX       3
#define M2_TRC_OFFSET          0
#define M2_TRC_LEN_MASK        0x3FF
#define M3_TRC_REG_INDEX       3
#define M3_TRC_OFFSET          10
#define M3_TRC_LEN_MASK        0x3FF

#define M1_MAX_POWER_REG_INDEX       0
#define M1_MAX_POWER_OFFSET          16
#define M1_MAX_POWER_LEN_MASK        0x7F
#define M2_MAX_POWER_REG_INDEX       4
#define M2_MAX_POWER_OFFSET          15
#define M2_MAX_POWER_LEN_MASK        0x7F
#define M3_MAX_POWER_REG_INDEX       4
#define M3_MAX_POWER_OFFSET          8
#define M3_MAX_POWER_LEN_MASK        0x7F


extern u32* mx_tcr_get_value_pointer(u8 para);
extern u32* mx_max_power_get_value_pointer(u8 para);
extern void mx_parameter_mode_index_callback(u8 key_type);
extern void mx_parameter_cursor_callback(u8 key_type);
extern void mx_parameter_value_callback(u8 key_type);
extern void menu_mx_parameter_value_backup(void);
extern void menu_mx_parameter_value_restore(void);
extern u8 get_mx_mode(void);
extern u8 get_cursor_index(void);


#endif

