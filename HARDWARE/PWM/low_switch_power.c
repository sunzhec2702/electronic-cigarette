#include "low_switch_power.h"

void low_switch_power_init()
{
    GPIO_InitPara GPIO_InitStructure;
    RCC_AHBPeriphClock_Enable(LOW_SWITCH_POWER_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT;
    GPIO_InitStructure.GPIO_Pin = LOW_SWITCH_POWER_PIN ;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_Init(LOW_SWITCH_POWER_GPIO, &GPIO_InitStructure);
}

/* USE CONFIG INSTEAD
void enable_charger()
{
    GPIO_SetBits(CHARGER_GPIO, CHARGER_PIN);
}

void disable_charger()
{
    GPIO_ResetBits(CHARGER_GPIO, CHARGER_PIN);
}
*/
