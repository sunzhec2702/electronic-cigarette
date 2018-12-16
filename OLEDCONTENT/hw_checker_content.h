#ifndef __HW_CHECKER_CONTENT_H
#define __HW_CHECKER_CONTENT_H
#include "sys.h"

#if defined SCREEN_069
#include "hw_checker_content_ssd1306.h"
#elif defined SCREEN_096
#include "hw_checker_content_sh1107.h"
#endif

extern void draw_weak_battery_revert(void);

#endif

