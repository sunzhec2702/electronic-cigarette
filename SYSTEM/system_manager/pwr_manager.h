#ifndef __PWR_MANAGER_H
#define __PWR_MANAGER_H
#include "sys.h"

#define POWER_ON_TIME       4000 //4s

#ifdef YANMING3
#define POWER_ON_KEY_TIMES  4
#else
#define POWER_ON_KEY_TIMES  5   //s
#endif

#define SLEEP       0
#define NOT_SLEEP   1
#define SLEEP_FLAG_REG_VALUE    4
#define SLEEP_FLAG_OFFSET       31
#define SLEEP_FLAG_MASK         0x1

#define NORMAL_RESET    1
#define ABNORMAL_RESET  0
#define RESET_FLAG_REG_VALUE    4
#define RESET_FLAG_OFFSET       30
#define RESET_FLAG_MASK         0x1

#define GO_TO_NOTHING               0
#define GO_TO_MX_PARAMETER          1
#define GO_TO_ABOUT_MENU            2

#define MX_FLAG_REG_VALUE           4
#define MX_FLAG_OFFSET              24
#define MX_FLAG_MASK                0x3


extern void pwr_init(void);
extern u8 check_standby_flag(void);
extern void check_standby_wakeup_button_press(void);
extern void enter_stand_by(void);
extern void enter_deep_sleep(void);
extern void reboot_system(u8 clear_sleep_flag);
extern void clear_sleep_state_flags(void);
extern void set_sleep_state_flags(void);
extern void clear_sleep_flag(void);
extern void set_sleep_flag(void);
extern u8 get_sleep_flag(void);
extern void clear_reset_flag(void);
extern void set_reset_flag(void);
extern u8 get_reset_flag(void);
void store_preset_value(void);
#endif
