#ifndef __CONTENT_H
#define __CONTENT_H
#include "sys.h"

#if defined SCREEN_069
#include "oled_content_ssd1306.h"
#elif defined SCREEN_096
#include "oled_content_sh1107.h"
#endif

#endif

