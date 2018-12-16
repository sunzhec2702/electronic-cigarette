#ifndef __BATTERY_CHARGING_ANIMATION_H
#define __BATTERY_CHARGING_ANIMATION_H
#include "sys.h"

extern void draw_charging_animation_power_on(void);
extern void draw_charging_animation(void);
extern void draw_battery_charging(u8 current_level);
extern void draw_battery_charging_power_on(u8 current_level);
extern void draw_power_off_screen(void);
extern void draw_power_on_screen(void);

#endif
