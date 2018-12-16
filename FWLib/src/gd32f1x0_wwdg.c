/**
  ******************************************************************************
  * @file    gd32f1x0_wwdg.c
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   WWDG functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0_wwdg.h"
#include "gd32f1x0_rcc.h"

/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @defgroup WWDG 
  * @brief WWDG driver modules
  * @{
  */

/** @defgroup WWDG_Private_Variables
  * @{
  */

/* WWDG Bit mask */
#define WWDG_BIT_MASK_PS            (~(uint32_t)WWDG_CFR_PS)   /*!< Window watchdog prescaler mask */
#define WWDG_BIT_MASK_WIN           (~(uint32_t)WWDG_CFR_WIN)  /*!< Window watchdog window value mask */
#define WWDG_BIT_MASK_CNT           (WWDG_CTLR_CNT)            /*!< Window watchdog CTLR register count mask */

/**
  * @}
  */

/** @defgroup WWDG_Private_Functions
  * @{
  */

/**
  * @brief  Reset the WWDG configuration.
  * @param  None
  * @retval None
  */
void WWDG_DeInit(void)
{
    RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_WWDGRST, ENABLE);
    RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_WWDGRST, DISABLE);
}

/**
  * @brief  Set WWDG prescaler value.
  * @param  PrescalerValue: WWDG Prescaler value.
  *   This parameter can be one of the following values:
  *     @arg WWDG_PRESCALER_1: the time base of watchdog counter = (PCLK1/4096)/1
  *     @arg WWDG_PRESCALER_2: the time base of watchdog counter = (PCLK1/4096)/2
  *     @arg WWDG_PRESCALER_4: the time base of watchdog counter = (PCLK1/4096)/4
  *     @arg WWDG_PRESCALER_8: the time base of watchdog counter = (PCLK1/4096)/8
  * @retval None
  */
void WWDG_SetPrescalerValue(uint32_t PrescalerValue)
{
    uint32_t temp = 0;

    /* Clear PS[1:0] bits */
    temp = WWDG->CFR & WWDG_BIT_MASK_PS;

    /* Set PS[1:0] bits */
    temp |= PrescalerValue;
    WWDG->CFR = temp;
}

/**
  * @brief  Set watchdog window value.
  * @param  WindowValue: the window value to be compared to the downcounter.
  * @retval None
  */
void WWDG_SetWindowValue(uint8_t WindowValue)
{
    __IO uint32_t temp = 0;

    /* Clear WIN[6:0] bits */
    temp = WWDG->CFR & WWDG_BIT_MASK_WIN;

    /* Set WIN[6:0] bits */
    temp |= WindowValue & WWDG_BIT_MASK_CNT;
    WWDG->CFR = temp;
}

/**
  * @brief  Enable the WWDG Early wakeup interrupt(EWI).
  * @note   An interrupt occurs when the counter reaches 0x40 if the bit is set. 
  *         It's cleared by a hardware reset. A write of 0 has no effect.
  * @param  None
  * @retval None
  */
void WWDG_EnableInt(void)
{
    WWDG->CFR |= WWDG_CFR_EWI;
}

/**
  * @brief  Set the value of the watchdog counter.
  * @param  CounterValue: the watchdog counter value.
  * @retval None
  */
void WWDG_SetCounterValue(uint8_t CounterValue)
{
    /* Write to CNT[6:0] bits */
    WWDG->CTLR = CounterValue & WWDG_BIT_MASK_CNT;
}

/**
  * @brief  Start the window watchdog counter.
  * @param  CounterValue: The value of the watchdog counter.
  * @retval None
  */
void WWDG_Enable(uint8_t CounterValue)
{
    WWDG->CTLR = WWDG_CTLR_WDGEN | CounterValue;
}

/**
  * @brief  Check the Early Wakeup interrupt bit state.
  * @param  None
  * @retval The new state of the Early Wakeup interrupt (SET or RESET).
  */
TypeState WWDG_GetBitState(void)
{    
    if ((WWDG->STR) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
  * @brief  Clear Early Wakeup interrupt flag.
  * @param  None
  * @retval None
  */
void WWDG_ClearBitState(void)
{
    WWDG->STR = (uint32_t)RESET;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2016 GIGADEVICE *****END OF FILE****/
