

#include "PWM_TIM1.h"


/**
  * @brief  Configure the TIMER peripheral.
  * @param  None
  * @retval None
  */
void PWM_Configuration(void)
{
    TIMER_BaseInitPara TIM_TimeBaseStructure;
    TIMER_OCInitPara  TIM_OCInitStructure;
    GPIO_InitPara GPIO_InitStructure;

    /* -----------------------------------------------------------------------
    PWM_BOOST PA8   TIM1_CH1
    PWM_BUCK PA9    TIM1_CH2
    PF0	FZDY
    PB1 OUT_EN
    ----------------------------------------------------------------------- */
#ifndef YANMING1
    /* GPIOA, GPIOB and GPIOF clocks enable */
    RCC_AHBPeriphClock_Enable( RCC_AHBPERIPH_GPIOA|RCC_AHBPERIPH_GPIOB |RCC_AHBPERIPH_GPIOF  , ENABLE);


    /*Configure PA8(TIMER1 CH1) as alternate function*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PUPD_NOPULL;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOA,GPIO_PINSOURCE8,GPIO_AF_2);

    /*Configure PA9(TIMER1 CH2) as alternate function*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_PIN_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PUPD_NOPULL;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOA,GPIO_PINSOURCE9,GPIO_AF_2);

    /*Configure PF0(FZDY) as PUSH PULL*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_PIN_0;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PUPD_NOPULL;
    GPIO_Init(GPIOF,&GPIO_InitStructure);

    FZDY_DISABLE();

    /*Configure PB1(OUT_EN) as PUSH PULL*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PUPD_NOPULL;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    PWM_OUT_DISABLE();


    /* -----------------------------------------------------------------------
    TIMER1 Configuration to:
    TIMER1CLK is fixed to 48MHz, the TIMER1 Prescaler is equal to 200 so the
    PWM is 20Khz.

    ----------------------------------------------------------------------- */

    /* TIMERS clock enable */
    RCC_APB2PeriphClock_Enable(RCC_APB2PERIPH_TIMER1, ENABLE);

    /* TIMER1  configuration */
    //  48MHz / 200 = 240KHz
    TIMER_DeInit(TIMER1);
    TIM_TimeBaseStructure.TIMER_Prescaler     = 0;
    TIM_TimeBaseStructure.TIMER_CounterMode   = TIMER_COUNTER_UP;
    TIM_TimeBaseStructure.TIMER_Period        = PWM_NUM;
    TIM_TimeBaseStructure.TIMER_ClockDivision = TIMER_CDIV_DIV1;
    TIMER_BaseInit(TIMER1,&TIM_TimeBaseStructure);

    /* CH1,CH2 Configuration in PWM mode */
    TIM_OCInitStructure.TIMER_OCMode       = TIMER_OC_MODE_PWM2;  // output HIGH when CNT>CCR
    TIM_OCInitStructure.TIMER_OCPolarity   = TIMER_OC_POLARITY_HIGH;
    TIM_OCInitStructure.TIMER_OutputState  = TIMER_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.TIMER_OutputNState = TIMER_OUTPUTN_STATE_DISABLE;
    TIM_OCInitStructure.TIMER_OCIdleState  = TIMER_OC_IDLE_STATE_RESET;

    TIM_OCInitStructure.TIMER_Pulse = 0;
    TIMER_OC1_Init(TIMER1, &TIM_OCInitStructure);
    TIMER_OC1_Preload(TIMER1,TIMER_OC_PRELOAD_ENABLE);

    TIM_OCInitStructure.TIMER_OCMode       = TIMER_OC_MODE_PWM1; // output LOW when CNT>CCR

    TIM_OCInitStructure.TIMER_Pulse = 0;
    TIMER_OC2_Init(TIMER1, &TIM_OCInitStructure);
    TIMER_OC2_Preload(TIMER1,TIMER_OC_PRELOAD_ENABLE);

    /* TIMER1 output enable */
    TIMER_CtrlPWMOutputs(TIMER1,ENABLE);
    /* Auto-reload preload enable */
    TIMER_CARLPreloadConfig(TIMER1,ENABLE);
    /* TIMER enable counter*/
    TIMER_Enable( TIMER1, ENABLE );

    PWM_SET_TO_ZERO();	// reset PWM output

#else

    /* GPIOAB clocks enable */
    RCC_AHBPeriphClock_Enable( RCC_AHBPERIPH_GPIOA | RCC_AHBPERIPH_GPIOB, ENABLE);


    /*Configure PB4(TIMER3 CH1) as alternate function*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_PIN_4;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PUPD_PULLDOWN;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOB,GPIO_PINSOURCE4,GPIO_AF_1);

    /*Configure PB5(TIMER3 CH2) as alternate function*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_PIN_5;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PUPD_PULLDOWN;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOB,GPIO_PINSOURCE5,GPIO_AF_1);

    /*Configure PB3(FZDY (New board name as out_en but the same function as previous FZDY)) as PUSH PULL*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PUPD_NOPULL;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    FZDY_DISABLE();

    /*Configure PA15(LOAD SW EN) as PUSH PULL*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_PIN_15;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PUPD_NOPULL;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    PWM_OUT_EN();

    /* -----------------------------------------------------------------------
        TIMER1 Configuration to:
        TIMER1CLK is fixed to 48MHz, the TIMER1 Prescaler is equal to 200 so the
        PWM is 20Khz.

      ----------------------------------------------------------------------- */

    /* TIMERS clock enable */
    RCC_APB1PeriphClock_Enable(RCC_APB1PERIPH_TIMER3, ENABLE);

    /* TIMER1  configuration */
    //  48MHz / 200 = 240KHz
    TIMER_DeInit(TIMER1);
    TIM_TimeBaseStructure.TIMER_Prescaler     = 0;
    TIM_TimeBaseStructure.TIMER_CounterMode   = TIMER_COUNTER_UP;
    TIM_TimeBaseStructure.TIMER_Period        = PWM_NUM;
    TIM_TimeBaseStructure.TIMER_ClockDivision = TIMER_CDIV_DIV1;
    TIMER_BaseInit(TIMER3,&TIM_TimeBaseStructure);

    /* CH1,CH2 Configuration in PWM mode */
    TIM_OCInitStructure.TIMER_OCMode       = TIMER_OC_MODE_PWM2;  // output HIGH when CNT>CCR
    TIM_OCInitStructure.TIMER_OCPolarity   = TIMER_OC_POLARITY_HIGH;
    TIM_OCInitStructure.TIMER_OutputState  = TIMER_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.TIMER_OutputNState = TIMER_OUTPUTN_STATE_DISABLE;
    TIM_OCInitStructure.TIMER_OCIdleState  = TIMER_OC_IDLE_STATE_RESET;

    TIM_OCInitStructure.TIMER_Pulse = 0;
    TIMER_OC1_Init(TIMER3, &TIM_OCInitStructure);
    TIMER_OC1_Preload(TIMER3,TIMER_OC_PRELOAD_ENABLE);

    TIM_OCInitStructure.TIMER_OCMode       = TIMER_OC_MODE_PWM1; // output LOW when CNT>CCR

    TIM_OCInitStructure.TIMER_Pulse = 0;
    TIMER_OC2_Init(TIMER3, &TIM_OCInitStructure);
    TIMER_OC2_Preload(TIMER3,TIMER_OC_PRELOAD_ENABLE);

    /* TIMER1 output enable */
    TIMER_CtrlPWMOutputs(TIMER3,ENABLE);
    /* Auto-reload preload enable */
    TIMER_CARLPreloadConfig(TIMER3,ENABLE);
    /* TIMER enable counter*/
    TIMER_Enable( TIMER3, ENABLE );

    PWM_SET_TO_ZERO();	// reset PWM output

#endif


}

void Set_PWM_HL(uint32_t PWM_H, uint32_t PWM_L)
{
    SET_BUCK_REG(PWM_L);
    SET_BOOST_REG(PWM_H);
}
