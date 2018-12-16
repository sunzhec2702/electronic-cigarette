#include "exti_charging.h"
#include "system_state.h"
#include "hw_checker.h"
#include "pwr_manager.h"
#include "peripherals_manager.h"

void exti_charging_init()
{
    NVIC_InitPara   NVIC_InitStructure;
    EXTI_InitPara   EXTI_InitStructure;

    RCC_APB2PeriphClock_Enable(RCC_APB2PERIPH_CFG, ENABLE);
    /* Connect key EXTI Line to key GPIO Pin */
    SYSCFG_EXTILine_Config(CHARGING_EXTI_GPIO, CHARGING_EXTI_PIN);

    /* Configure increase key EXTI line */
    EXTI_ClearIntBitState(CHARGING_EXTILINE);
    EXTI_InitStructure.EXTI_LINE = CHARGING_EXTILINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LINEEnable = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    EXTI_ClearIntBitState(CHARGING_EXTILINE);

    NVIC_InitStructure.NVIC_IRQ = CHARGING_EXTI_IRQ;			//使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQPreemptPriority = 0x01;	//抢占优先级1
    NVIC_InitStructure.NVIC_IRQSubPriority = 0x00;					//子优先级1
    NVIC_InitStructure.NVIC_IRQEnable = ENABLE;								//使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

void exti_charging_deinit()
{
    EXTI_InitPara   EXTI_InitStructure;
    RCC_APB2PeriphClock_Enable(RCC_APB2PERIPH_CFG, ENABLE);
    /* Connect key EXTI Line to key GPIO Pin */
    SYSCFG_EXTILine_Config(CHARGING_EXTI_GPIO, CHARGING_EXTI_PIN);
    /* Configure increase key EXTI line */
    EXTI_InitStructure.EXTI_LINE = CHARGING_EXTILINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LINEEnable = DISABLE;
    EXTI_Init(&EXTI_InitStructure);
    EXTI_ClearIntBitState(CHARGING_EXTILINE);
}

void EXTI4_15_IRQHandler(void)
{
    if (EXTI_GetIntBitState(CHARGING_EXTILINE) != RESET) {
        if (check_charging() == CHARGING && get_charger_plug_flag() == CHARGER_UNPLUGGED) {
            set_charger_plug_flag();
            reboot_system(SUCCESS);
        }
        EXTI_ClearIntBitState(CHARGING_EXTILINE);
    }
}


