#include "exti_rtc.h"
#include "rtc.h"
#include "iwdg.h"
#include "screen.h"
#include "oled_content.h"

u8 dummy_test = 0;
void exti_rtc_init()
{
    EXTI_InitPara  EXTI_InitStructure;
    NVIC_InitPara  NVIC_InitStructure;

    RCC_APB1PeriphClock_Enable(RCC_APB1PERIPH_PWR, ENABLE);

    /* RTC ALARM Interrupt Configuration */
    EXTI_ClearIntBitState(EXTI_LINE17);
    EXTI_InitStructure.EXTI_LINE = EXTI_LINE17;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LINEEnable = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    EXTI_ClearIntBitState(EXTI_LINE17);

    NVIC_InitStructure.NVIC_IRQ = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQPreemptPriority = 0;
    NVIC_InitStructure.NVIC_IRQSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQEnable = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void exti_rtc_deinit()
{
    EXTI_InitPara  EXTI_InitStructure;
    /* RTC ALARM Interrupt Configuration */
    EXTI_ClearIntBitState(EXTI_LINE17);
    EXTI_InitStructure.EXTI_LINE = EXTI_LINE17;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LINEEnable = DISABLE;
    EXTI_Init(&EXTI_InitStructure);
    RTC_ClearBitState(RTC_STR_AF);
    EXTI_ClearIntBitState(EXTI_LINE17);
}

void RTC_IRQHandler(void)
{
    if(RTC_GetBitState(RTC_STR_AF) != RESET)
    {
        RTC_ClearBitState(RTC_STR_AF);
        EXTI_ClearIntBitState(EXTI_LINE17);
        iwdg_feed();
        /*
        Screen_Init();
        ENABLE_OLED();
        OLED_Display_On();
        draw_battery_icon_charge((dummy_test++)%6);
        */
        RTC_REENABLE_FEEDDOG();
    }
}
