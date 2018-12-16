#ifndef __HW_CHECKER_CONTENT_SSD1306_H
#define __HW_CHECKER_CONTENT_SSD1306_H
#include "sys.h"

#ifdef SCREEN_069

static const unsigned char WeakBatteryF25x8[] = 
{
    0x08,0x78,0xC0,0xF8,0xC0,0x78,0x08,0x00,0x70,0xA8,0xA8,0xA8,0xB0,0x00,0xE8,0xA8,0xA8,0xA8,0xF0,0x00,0xFE,0x20,0x30,0x48,0x88,/*"C:\Users\Darren\Documents\STM32Project\weak.BMP",0*/
};
extern void show_battery_low_message(void);
extern void show_battery_weak_message(void);
extern void clean_battery_weak_message(void);
extern void show_current_high_message(void);
extern void show_register_short_message(void);
extern void show_temp_high_message(void);
extern void show_temp_low_message(void);
extern void show_voltage_high_message(void);
extern void show_register_short_message(void);
extern void show_atomizer_message(void);
#endif

#endif
