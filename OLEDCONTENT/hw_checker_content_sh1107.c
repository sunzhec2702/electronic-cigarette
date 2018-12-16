#include "hw_checker_content_sh1107.h"

#ifdef SCREEN_096
#include "screen.h"
#include "checker_message.h"
#include "oled_content_muxlock.h"
#include "oled_content.h"

void show_battery_low_message()
{
    OLED_Clear();
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_ShowString_Mode(20, 6, "LOW", 16, 1);
        OLED_ShowString_Mode(4, 8, "BATTERY", 16, 1);
        unlock_oled();
    }
}

void show_battery_weak_message()
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_SHOW_SPACE(0,PART4_PAGE-1,16,64);
        OLED_SHOW_SPACE(0,PART4_PAGE+1,16,64);
        OLED_ShowString_Mode(4, PART4_PAGE-1, " WEAK", 16, 1);
        OLED_ShowString_Mode(4, PART4_PAGE+1, "BATTERY", 16, 1);
        unlock_oled();
    }
}

void clean_battery_weak_message()
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_SHOW_SPACE(4,PART4_PAGE-1,16,40);
        OLED_SHOW_SPACE(4,PART4_PAGE+1,16,56);
        unlock_oled();
    }
}

void show_voltage_high_message()
{
    OLED_Clear();
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();    
        OLED_ShowString_Mode(16, 6, "OVER", 16, 1);
        OLED_ShowString_Mode(4, 8, "VOLTAGE", 16, 1);
        unlock_oled();
    }
}

void show_current_high_message()
{
    OLED_Clear();
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_ShowString_Mode(16, 6, "OVER", 16, 1);
        OLED_ShowString_Mode(4, 8, "CURRENT", 16, 1);
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
    OLED_Clear();
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_ShowString_Mode(16, 6, "TEMP", 16, 1);
        OLED_ShowString_Mode(16, 8, "HIGH", 16, 1);
        unlock_oled();
    }
}

void show_temp_low_message()
{
    OLED_Clear();
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_ShowString_Mode(16, 6, "TEMP", 16, 1);
        OLED_ShowString_Mode(20, 8, "LOW", 16, 1);
        unlock_oled();
    }
}

void show_atomizer_message()
{
    OLED_Clear();
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_ShowString_Mode(12, 6, "CHECK", 16, 1);
        OLED_ShowString_Mode(0, 8, "ATOMIZER", 16, 1);
        unlock_oled();
    }
}
#endif

