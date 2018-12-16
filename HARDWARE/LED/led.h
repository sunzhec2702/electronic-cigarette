#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LED_OFF 0
#define LED_ON 1
#define LED_REVERT 2

#define LED0 0
#define LED1 1
#define LED_NUM 2


#define LED0_PORT GPIOF
#define LED0_PIN GPIO_PIN_6

extern void LED_init(void);//≥ı ºªØ
extern void LED_set(u8 index, u8 state);

#endif
