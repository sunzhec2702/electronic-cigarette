#include "battery_charging_animation.h"
#include "value_manager.h"
#include "screen.h"
#include "battery_charging_content.h"
#include "system_state.h"
#include "hw_checker.h"
#include "pwr_manager.h"
#include "oled_content.h"
#include "battery_manager.h"
#include "UI_manager.h"
#include "oled_content.h"
#include "oled_content_muxlock.h"

static u8 current_level = 0;

void draw_charging_animation_power_on()
{
    if (get_system_state() == STATE_NORMAL && get_system_lock() != SYS_LOCK && can_draw_icons() == SUCCESS && get_battery_level() != BATTERY_LEVEL_NOT_INIT) {
        if (current_level == 0) {
            current_level = get_battery_level();
        } else {
            current_level--;
        }
        draw_battery_charging_power_on(current_level);
    }
}

#if defined SCREEN_096
void draw_charging_animation()
{
    if (get_system_state() == STATE_CHARGING && get_battery_level() != BATTERY_LEVEL_NOT_INIT) {
        OLED_Display_On();
        if (current_level == 0) {
            current_level = get_battery_level();
        } else {
            current_level--;
        }
        OLED_ShowString_Mode(0, PART4_PAGE - 3, "Charging", 16, 1);
        draw_battery_charging_power_on(current_level);
        #ifdef DEBUG_CHARGING_BATTERY_VALUE
        draw_register_value(value_read(STATIC_BATTERY_VALUE));
        draw_voltage_value(get_battery_level());
        #endif
    }
}
#elif defined SCREEN_069
void draw_charging_animation()
{
    if (get_system_state() == STATE_CHARGING && get_battery_level() != BATTERY_LEVEL_NOT_INIT) {
        OLED_Display_On();
        if (current_level == 0) {
            current_level = get_battery_level() * 2;
        } else {
            current_level--;
        }
        draw_battery_charging(current_level);
        #ifdef DEBUG_CHARGING_BATTERY_VALUE
        draw_register_value(value_read(STATIC_BATTERY_VALUE));
        draw_voltage_value(get_battery_level());
        #endif
    }
}
#endif

void draw_battery_charging_power_on(u8 current_level)
{
    draw_battery_icon_charge(current_level);
}

#ifdef SCREEN_069
void draw_battery_charging(u8 level)
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_SHOW_SPACE(0,0,16,30);
        OLED_DrawBMP(30, 0, 65, 2, BATTERY_CHARGING_ICON[level]);
        OLED_SHOW_SPACE(65,0,16,31);
        unlock_oled();
    }
}

void draw_power_off_screen()
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_SHOW_SPACE(0,0,16,12);
        OLED_DrawBMP(12, 0, 84, 2, PowerOffLogoF72x16);
        OLED_SHOW_SPACE(84,0,16,12);
        unlock_oled();
    }
}

void draw_power_on_screen()
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_DrawBMP(0, 0, 96, 2, PowerOnLogoF96x16);
        unlock_oled();
    }
}
#endif

