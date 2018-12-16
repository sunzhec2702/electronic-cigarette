#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#include "timer_key.h"
#include "timer_adc.h"

extern void TIMx_Int_Init(void);
extern void TIMx_Int_DeInit(void);

void TIM17_Int_Init(u16 arr,u16 psc);



#endif
