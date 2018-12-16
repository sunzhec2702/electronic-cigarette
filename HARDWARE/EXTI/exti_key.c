#include "exti_key.h"
#include "exti_charging.h"
#include "key.h"
#include "system_state.h"
#include "pwr_manager.h"
#include "delay.h"
#include "screen.h"
#include "oled_content.h"
#include "hw_checker.h"
#include "battery_manager.h"

static u8 power_on_flag = NOT_POWER_ON;
static u8 power_on_number = 0;

void exti_key_init()
{
    NVIC_InitPara   NVIC_InitStructure;
    EXTI_InitPara   EXTI_InitStructure;

    RCC_APB2PeriphClock_Enable(RCC_APB2PERIPH_CFG, ENABLE);
    SYSCFG_EXTILine_Config(KEY_CONFIRM_EXTI_GPIO, KEY_CONFIRM_EXTI_PIN);

    /* Configure confirm key EXTI line */
    EXTI_InitStructure.EXTI_LINE = KEY_CONFIRM_EXTILINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    #ifdef YANMING3
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    #else
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    #endif
    EXTI_InitStructure.EXTI_LINEEnable = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    EXTI_ClearIntBitState(KEY_CONFIRM_EXTILINE);

    NVIC_InitStructure.NVIC_IRQ = EXTI0_1_IRQn;			//使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQPreemptPriority = 0x00;	//抢占优先级2
    NVIC_InitStructure.NVIC_IRQSubPriority = 0x00;					//子优先级1
    NVIC_InitStructure.NVIC_IRQEnable = ENABLE;								//使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

void exti_key_deinit()
{

    EXTI_InitPara   EXTI_InitStructure;
    /* Configure key EXTI line */
    EXTI_InitStructure.EXTI_LINE = KEY_CONFIRM_EXTILINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    #ifdef YANMING3
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    #else
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    #endif
    EXTI_InitStructure.EXTI_LINEEnable = DISABLE;
    EXTI_Init(&EXTI_InitStructure);
}

void EXTI0_1_IRQHandler(void)
{
    #ifndef YANMING3
    if (EXTI_GetIntBitState(KEY_CONFIRM_EXTILINE) != RESET) {
        delay_ms(10);
        power_on_number++;   
        if (power_on_number >= POWER_ON_KEY_TIMES) {
            power_on_flag = POWER_ON_NOW;
        } else
            power_on_flag = NOT_POWER_ON;
        EXTI_ClearIntBitState(KEY_CONFIRM_EXTILINE);
    }
    #else
    if (EXTI_GetIntBitState(KEY_CONFIRM_EXTILINE) != RESET) {
        power_on_number++;   
        if (power_on_number >= POWER_ON_KEY_TIMES) {
            power_on_flag = POWER_ON_NOW;
        } else
            power_on_flag = NOT_POWER_ON;
        EXTI_ClearIntBitState(KEY_CONFIRM_EXTILINE);
    }
    #endif
}

u8 get_power_on_flag_number()
{
    return power_on_number;
}

u8 get_power_on_flag()
{
    return power_on_flag;
}

void clear_power_on_flag()
{
    power_on_flag = NOT_POWER_ON;
    power_on_number = 0;
}
