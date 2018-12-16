#ifndef __TIMER_ADC_H
#define __TIMER_ADC_H
#include "sys.h"
#include "PID.h"

#define ADC_PSC 0
#define ADC_ARR (48000000 / F_CTRL)

extern void timer_adc_init(void);
extern void timer_adc_deinit(void);
#endif

