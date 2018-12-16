#ifndef __EXTI_KEY_H
#define __EXTI_KEY_H
#include "sys.h"
#define POWER_ON_NOW    0
#define NOT_POWER_ON    1

extern void exti_key_init(void);
extern void exti_key_deinit(void);
extern u8 get_power_on_flag_number(void);
extern void clear_power_on_flag(void);
extern u8 get_power_on_flag(void);

#endif
