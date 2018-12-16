#ifndef __SCREEN_H
#define __SCREEN_H
#include "sys.h"

#if defined SCREEN_SSD1306
#include "oled_ssd1306.h"
#elif defined SCREEN_SH1107
#include "oled_sh1107.h"
#elif defined SCREEN_SSD1327
#include "oled_ssd1327.h"
#endif

extern void Screen_Init(void);

#endif

