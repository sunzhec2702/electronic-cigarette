#ifndef __EXTI_CHARGING_H
#define __EXTI_CHARGING_H
#include "sys.h"
#define CHARGING_EXTI_GPIO  EXTI_SOURCE_GPIOA

#ifdef YANMING1
#define CHARGING_EXTI_PIN   EXTI_SOURCE_PIN7
#else
#define CHARGING_EXTI_PIN   EXTI_SOURCE_PIN0
#endif

#ifdef YANMING1
#define CHARGING_EXTILINE   EXTI_LINE7
#else
#define CHARGING_EXTILINE   EXTI_LINE0
#endif

#define CHARGING_GPIO       GPIOA

#ifdef YANMING1
#define CHARGING_PIN        GPIO_PIN_7
#else
#define CHARGING_PIN        GPIO_PIN_0
#endif

#ifdef YANMING1
#define CHARGING_EXTI_IRQ   EXTI4_15_IRQn
#else
#define CHARGING_EXTI_IRQ   EXTI0_1_IRQn
#endif

extern void exti_charging_init(void);
extern void exti_charging_deinit(void);
#endif
