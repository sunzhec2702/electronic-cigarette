#ifndef __OLED_CONTENT_MUXLOCK_H
#define __OLED_CONTENT_MUXLOCK_H
#include "sys.h"
#include "system_state.h"

#define OLED_UNLOCK      SYS_UNLOCK
#define OLED_LOCKED      SYS_LOCK

extern void lock_oled(void);
extern void unlock_oled(void);
extern u8 get_oled_lock(void);

#endif
