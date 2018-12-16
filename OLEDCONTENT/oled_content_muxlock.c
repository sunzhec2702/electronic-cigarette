#include "oled_content_muxlock.h"

static u8 oled_lock = OLED_UNLOCK;

void lock_oled(void)
{
    oled_lock = OLED_LOCKED;
}

void unlock_oled(void)
{
    oled_lock = OLED_UNLOCK;
}

u8 get_oled_lock(void)
{
    return oled_lock;
}

