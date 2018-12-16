#ifndef __SYS_H
#define __SYS_H
#ifndef GD32F130_150
#define GD32F130_150
#endif
#include "gd32f1x0.h"
#include "debug_config.h"
#define YANMING1    1   // For Yanming's board v1.1
#define YANMING2    1   // For Yanming's board v1.2
#define YANMING3    1   // For Yanming's board v1.3
#include "stdlib.h"


#define SW_VER1    2
#define SW_VER2    2
#define SW_VER3    9


//#define POWER_40W 1
//#define POWER_60W
#define POWER_90W


//#define SCREEN_SSD1306 1
#define SCREEN_SH1107 1
//#define SCREEN_SSD1327  1

//#define SCREEN_069    1
#define SCREEN_096  1

/*
RTC register list
BKR0    RTC
bit31~28: RTC Init Value
bit22~16:  MAX_POWER_VALUE_1
bit9~0: M1 TRC

BKR1    
bit31~16: preset_voltage_value
bit15~0:    preset_power_value

BKR2
bit31~16: coil_r_static
bit15:   C or F degree mode
bit14~0: preset_temperature

BKR3
bit23~20:   temperature_select_index
bit19~10:   M2 TRC
bit9~0:    M3 TRC

BKR4
bit31: sleep flag
bit30: reset flag
bit29: boot_up flag
bit28: charger_flag 
bit27: coil_ready_flag
bit26: screen flip flag
bit25~24: mx parameter set flag
bit23: smoke_error_flag
bit22: value key lock flag

bit21~15: MAX_POWER_VALUE_2
bit14~8: MAX_POWER_VALUE_3
bit7~0: UI_ID
*/



#endif
