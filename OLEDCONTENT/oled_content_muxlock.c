#include "oled_content_muxlock.h"

static u8 oled_lock = OLED_UNLOCK;
static u8 weak_battery_lock = OLED_UNLOCK;

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

void lock_weak_oled(void)
{
    weak_battery_lock = OLED_LOCKED;
}

void unlock_weak_oled(void)
{
    weak_battery_lock = OLED_UNLOCK;
}

u8 get_oled_weak_lock(void)
{
    return weak_battery_lock;
}

