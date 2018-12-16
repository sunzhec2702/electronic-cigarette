#ifndef __VALUE_KEY_H
#define __VALUE_KEY_H
#include "sys.h"

#define KEY_GPIO_RCC        RCC_AHBPERIPH_GPIOA
#define KEY_GPIO            GPIOA

#define KEY_INCREASE_PIN    GPIO_PIN_4
#define KEY_REDUCE_PIN      GPIO_PIN_3


#define KEY_INCREASE_EXTILINE   EXTI_LINE4
#define KEY_REDUCE_EXTILINE     EXTI_LINE3


#define KEY_INCREASE_EXTI_GPIO  EXTI_SOURCE_GPIOA
#define KEY_REDUCE_EXTI_GPIO    EXTI_SOURCE_GPIOA

#define KEY_INCREASE_EXTI_PIN   EXTI_SOURCE_PIN4
#define KEY_REDUCE_EXTI_PIN     EXTI_SOURCE_PIN3

#define VALUE_KEY_LONG_PRESS_TIME       1000/TIMER_PERIOD //800ms

extern u8 value_key_trigger_action(void* key_t);
extern u8 value_key_long_event_action(void* key_t);
extern u8 value_key_repeat_action(void* key_t);
extern u8 value_key_preaction(u8 pressed_keys, void * key_t);

#endif

