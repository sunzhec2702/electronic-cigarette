#ifndef __BATTERY_MANAGER_H
#define __BATTERY_MANAGER_H
#include "sys.h"

#define BATTERY_LEVEL_NOT_INIT                      0xFF

#define CHARGING_ANIMATION_PERIOD                   500
#define BATTERY_STATE_UPDATE_PERIOD                 500
#define STATIC_BATTERY_UPDATE_PERIOD                2000
#define STATIC_BATTERY_UPDATE_PERIOD_CNT            5
#define MAX_STATIC_BATTERY_VALUE_UPDATE_PERIOD      300


#define BATTERY_LEVEL0_HIGH     412 //100%
#define BATTERY_LEVEL0_LOW      395 //90%
#define BATTERY_LEVEL1_HIGH     385 //80%
#define BATTERY_LEVEL1_LOW      377 //70%
#define BATTERY_LEVEL2_HIGH     370 //60%
#define BATTERY_LEVEL2_LOW      366 //50%
#define BATTERY_LEVEL3_HIGH     363 //40%
#define BATTERY_LEVEL3_LOW      358 //30%
#define BATTERY_LEVEL4_HIGH     350 //20%
#define BATTERY_LEVEL4_LOW      340 //10%

#define BATTERY_UNPROTECT_VALUE         345
#define BATTERY_PROTECT_VALUE           330 //5%
#define BATTERY_PROTECT_DYNAMIC_VALUE   260

#define BATTERY_SMOKE_PROTECT           1
#define BATTERY_SMOKE_UNPROTECT         0
#define BATTERY_SMOKE_REG_VALUE         4
#define BATTERY_SMOKE_OFFSET_VALUE      23
#define BATTERY_SMOKE_MASK_VALUE        0x1

#define BATTERY_LEVEL_CAL_OFFSET        10

extern void charging_animation_task(void);
extern void static_battery_value_update_task(void);
extern void draw_battery_state(void);

extern u8 get_battery_level(void);
u8 get_charging_battery_level(u16 battery_value);
u8 get_using_battery_level(u16 battery_value);
#endif
