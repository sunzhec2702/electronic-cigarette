#ifndef __CONFIRM_KEY_H
#define __CONFIRM_KEY_H
#include "sys.h"

#define KEY_CONFIRM_RCC     RCC_AHBPERIPH_GPIOA
#define KEY_CONFIRM_GPIO    GPIOA
// The confirm key is PA0 in Ming's board
#ifdef YANMING1
#define KEY_CONFIRM_PIN     GPIO_PIN_0
#else
#define KEY_CONFIRM_PIN     GPIO_PIN_1
#endif

#ifdef YANMING1
#define KEY_CONFIRM_EXTILINE    EXTI_LINE0
#else
#define KEY_CONFIRM_EXTILINE    EXTI_LINE1
#endif

#define KEY_CONFIRM_EXTI_GPIO   EXTI_SOURCE_GPIOA
#ifdef YANMING1
#define KEY_CONFIRM_EXTI_PIN    EXTI_SOURCE_PIN0
#else
#define KEY_CONFIRM_EXTI_PIN    EXTI_SOURCE_PIN1
#endif


#define CONFIRM_KEY_LONG_PRESS_TIME             200/TIMER_PERIOD // 1000ms change to smoke mode
#define CONFIRM_KEY_PREPARE_TIME				100/TIMER_PERIOD		//100ms

#define SMOKE_RT_PARA_UPDATE_INTERVAL    50  //500ms

extern u8 confirm_key_trigger_action(void* key_t);
extern u8 confirm_key_long_event_action(void* key_t);
extern u8 confirm_key_repeat_action(void* key_t);
extern u8 comfirm_key_preaction(u8 pressed_keys, void * key_t);

#endif

