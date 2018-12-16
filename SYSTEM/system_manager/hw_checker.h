#ifndef __HW_CHECKER_H
#define __HW_CHECKER_H
#include "sys.h"

#define CHARGING            1
#define DISCHARGING         0

#if defined POWER_40W
#define MAX_POWER_VALUE_W 40
#define MAX_POWER_VALUE (MAX_POWER_VALUE_W*10)
#define MIN_POWER_VALUE 70
#define MAX_VOLTAGE_VALUE   800
#define MIN_CURRENT_VALUE   0
#define MAX_CURRENT_VALUE   1800
#define MAX_BYPASS_CURRENT_VALUE_BYPASS    2300
#elif defined POWER_60W
#define MAX_POWER_VALUE_W 60
#define MAX_POWER_VALUE (MAX_POWER_VALUE_W*10)
#define MIN_POWER_VALUE 70
#define MAX_VOLTAGE_VALUE   800
#define MIN_CURRENT_VALUE   0
#define MAX_CURRENT_VALUE   1800
#define MAX_BYPASS_CURRENT_VALUE_BYPASS    2300
#elif defined POWER_90W
#define MAX_POWER_VALUE_W 90
#define MAX_POWER_VALUE (MAX_POWER_VALUE_W*10)
#define MIN_POWER_VALUE 70
#define MAX_VOLTAGE_VALUE   800
#define MIN_CURRENT_VALUE   0
#define MAX_CURRENT_VALUE   1800
#define MAX_BYPASS_CURRENT_VALUE_BYPASS    2300
#endif

#define MIN_REG_VALUE   20
#define MAX_REG_VALUE   999

extern u8 check_coil_exist(void);
extern u8 check_charging(void);
extern u8 check_battery(void);
extern u8 check_voltage_out(void);
extern u8 check_register_load(void);
extern u8 check_hw_fire(void);

#endif

