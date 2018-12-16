#include "timer.h"
#include "led.h"

#include "system_state.h"
#include "oled_content.h"
#include "adc.h"

void TIMx_Int_Init()
{
    timer_key_init();
    timer_adc_init();
}

void TIMx_Int_DeInit()
{
    timer_key_deinit();
    timer_adc_deinit();
}

