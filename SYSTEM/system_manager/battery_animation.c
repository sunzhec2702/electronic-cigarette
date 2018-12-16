#include "battery_charging_animation.h"
#include "value_manager.h"
#include "oled.h"


static u8 current_level = 0;

void draw_charging_animation()
{
    if (current_level == 0) {
        draw_charging_icon(get_battery_level());
    } else if () {

    }


}


void draw_charging_icon(u8 level)
{
    OLED_SHOW_SPACE(0,0,16,3);
    OLED_DrawBMP(3, 0, 93, 2, LOCKMESSAGEF80x16);
    OLED_SHOW_SPACE(93,0,16,3);
}