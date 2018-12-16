#ifndef __TIMER_KEY_H
#define __TIMER_KEY_H
#include "sys.h"
#include "key.h"
#include "oled_content.h"
#include "system_state.h"

#define KEY_PSC     4799
#define KEY_ARR     TIMER_PERIOD*10-1

#define KEY_FRESH_PSC       4799
#define KEY_FRESH_ARR       TIMER_FRESH_SCREEN*10-1

#define KEY_UPDATE_TIMER    TIMER14
#define KEY_UPDATE_INT      TIMER14_IRQn
#define KEY_UPDATE_TIMER_RCC      RCC_APB1PERIPH_TIMER14

#define KEY_FRESH_TIMER    TIMER16
#define KEY_FRESH_INT      TIMER16_IRQn
#define KEY_FRESH_TIMER_RCC      RCC_APB2PERIPH_TIMER16

extern void ENABLE_FRESH_SCREEN_TIMER(u8 lock);
extern void timer_key_init(void);
extern void timer_key_deinit(void);
#endif
