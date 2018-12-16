#include "hw_checker_content.h"
#include "oled.h"
#include "checker_message.h"
#include "oled_content_muxlock.h"

void show_battery_low_message()
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_SHOW_SPACE(0,0,16,4);
        OLED_ShowString_Mode(0, 0, "LOW BATTERY", 16, 1);
        OLED_SHOW_SPACE(92,0,16,4);
        unlock_oled();
    }
    //OLED_DrawBMP(4, 0, 92, 2, BatteryLOWF88x16);
}

void show_battery_weak_message()
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_ShowString_Mode(0, 0, "WEAK BATTERY", 16, 1);
        //OLED_DrawBMP(0, 0, 96, 2, BatteryWEAKF96X16);
        unlock_oled();
    }
}

void show_voltage_high_message()
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();    
        OLED_ShowString_Mode(0, 0, "OVER VOLTAGE", 16, 1);
        unlock_oled();
    }
}

void show_current_high_message()
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_ShowString_Mode(0, 0, "OVER CURRENT", 16, 1);
        //OLED_DrawBMP(0, 0, 96, 2, OverCurrentF96x16);
        unlock_oled();
    }
}

/*
void show_register_short_message()
{
    OLED_SHOW_SPACE(0,0,16,16);
    OLED_ShowString_Mode(16, 0, "TEMP HIGH", 16, 1);
    OLED_DrawBMP(16, 0, 80, 2, RegisterShortF64x16);
    OLED_SHOW_SPACE(80,0,16,16);
}
*/

void show_temp_high_message()
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_SHOW_SPACE(0,0,16,12);
        OLED_ShowString_Mode(12, 0, "TEMP HIGH", 16, 1);
        OLED_SHOW_SPACE(84,0,16,12);
        unlock_oled();
    }
}

void show_temp_low_message()
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_SHOW_SPACE(0,0,16,16);
        OLED_ShowString_Mode(16, 0, "TEMP LOW", 16, 1);
        OLED_SHOW_SPACE(80,0,16,16);
        unlock_oled();
    }
}

void show_atomizer_message()
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_SHOW_SPACE(0,0,16,4);
        OLED_ShowString_Mode(4, 0, "NO ATOMIZER", 16, 1);
        OLED_SHOW_SPACE(92,0,16,4);
        unlock_oled();
    }
}
