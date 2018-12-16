#include "hw_checker_content.h"
#include "oled_content.h"
#include "value_manager.h"
#include "ui_manager.h"

void draw_weak_battery_revert()
{
    // Clean Weak battery information
    clean_battery_weak_message();
    #if defined SCREEN_069
    #elif defined SCREEN_096    
    draw_current_battery();
    #endif
}
