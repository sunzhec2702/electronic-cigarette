#ifndef __RTC_H
#define __RTC_H
#include "sys.h"

#define RTC_CLOCK_SOURCE_LSI
#define BKP_VALUE                   0xF
#define BKP_VALUE_REG_VALUE         0
#define BKP_VALUE_OFFSET_VALUE      28
#define BKP_VALUE_MASK_VALUE        0xF


#define RTC_EXTI_LINE EXTI_LINE17
#define FEED_DOG_TIME   3   //s

extern void rtc_init(void);
extern void enable_rtc(u16 seconds);
extern void RTC_REENABLE_FEEDDOG(void);


#endif
