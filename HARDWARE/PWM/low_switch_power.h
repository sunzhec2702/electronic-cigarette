#ifndef __CHARGER_H
#define __CHARGER_H
#include "sys.h"

#define LOW_SWITCH_POWER_GPIO    GPIOA
#define LOW_SWITCH_POWER_PIN     GPIO_PIN_15
#define LOW_SWITCH_POWER_RCC     RCC_AHBPERIPH_GPIOA


// It is actually low switch power
#define ENABLE_LOW_SWITCH()      GPIO_SetBits(LOW_SWITCH_POWER_GPIO, LOW_SWITCH_POWER_PIN);
#define DISABLE_LOW_SWITCH()     GPIO_ResetBits(LOW_SWITCH_POWER_GPIO, LOW_SWITCH_POWER_PIN);

extern void low_switch_power_init(void);

#endif

