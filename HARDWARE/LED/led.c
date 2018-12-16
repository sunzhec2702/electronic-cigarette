#include "led.h"

GPIO_TypeDef* LED_PORTS[] = {
    LED0_PORT,
};

u16 LED_PINS[] = {
    LED0_PIN,
};

//LED IO初始化
void LED_init(void)
{
    // LED1 PF_6
    GPIO_InitPara  GPIO_InitStructure;
    RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOF, ENABLE);	 //使能PF端口时钟    
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_6 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;            
    GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP ;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOF, GPIO_PIN_6);
    
}

void LED_set(u8 index, u8 state)
{
    switch (state) {
        case LED_ON:
            GPIO_SetBits(LED_PORTS[index], LED_PINS[index]);          
            break;
        case LED_OFF:
            GPIO_ResetBits(LED_PORTS[index], LED_PINS[index]);
            break;
        case LED_REVERT:
            LED_set(index, !GPIO_ReadOutputBit(LED_PORTS[index], LED_PINS[index]));
            break;
    }
}
