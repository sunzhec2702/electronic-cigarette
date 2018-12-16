#include "exti.h"
#include "exti_rtc.h"
#include "exti_key.h"
#include "exti_charging.h"

void EXTIX_Init(void)
{
    exti_key_init();
    exti_rtc_init();
    exti_charging_init();
}

void EXTIX_DeInit()
{
    exti_key_deinit();
    exti_rtc_deinit();
    //exti_charging_deinit();  //we don't need to deinit exti_charging
}

