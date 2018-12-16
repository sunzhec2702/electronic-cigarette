#ifndef __SYSTEM_STATE_H
#define __SYSTEM_STATE_H
#include "sys.h"

#define STATE_NORMAL        0
#define STATE_DISPLAYOFF    1
#define STATE_SLEEP         2
#define STATE_CHARGING      3

#define SYS_DIS_OFF_TIME        30000 // ms
#define SYS_SLEEP_TIME          600000  // ms
#define SYS_CHARGING_TIME       500     // ms

#define SYS_LOCK        0x1
#define SYS_UNLOCK      0x0

#define SYS_NOT_SMOKE   0x0
#define SYS_SMOKE       0x1
#define SYS_SMOKE_DONE  0x2

#define SYS_SCREEN_NORMAL               0x0
#define SYS_SCREEN_FLIP                 0x1
#define SCREEN_FLIP_FLAG_REG_VALUE      4
#define SCREEN_FLIP_FLAG_OFFSET_VALUE   26
#define SCREEN_FLIP_FLAG_MASK_VALUE     0x1




#define BOOT_UP_LOGO_TIME       1000
#define POWER_OFF_LOGO_TIME     1000

/*
#define COLD_NOT_BOOT_UP            0
#define COLD_BOOT_UP                1
#define BOOT_UP_FLAG_REG_VALUE      4
#define BOOT_UP_FLAG_OFFSET_VALUE   29
#define BOOT_UP_FLAG_MASK_VALUE     0x1
*/

extern void system_init(void);
void init_all_states(void);
extern void system_sleep(void);
extern void system_wakeup(void);


extern void check_system_state(void);
extern u8 get_system_state(void);
extern void set_system_state(u8 state);
extern void set_system_lock(u8 lock);

extern void set_system_smoke(u8 smoke);
extern u8 get_system_smoke(void);

extern void set_system_lock(u8 lock);
extern void system_lock_reverse(void);
extern u8 get_system_lock(void);

extern void states_reset(void);

/*
extern void set_boot_flag(void);
extern u8 get_boot_flag(void);
*/

extern void screen_flip_flag_revert(void);
extern void set_screen_flip_flag(void);
extern void clear_screen_flip_flag(void);
extern u8 get_screen_flip_flag(void);

#endif


