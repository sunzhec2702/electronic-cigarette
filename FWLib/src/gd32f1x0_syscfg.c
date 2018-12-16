/**
  ******************************************************************************
  * @file    gd32f1x0_syscfg.c
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   SYSCFG functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0_syscfg.h"

/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @defgroup SYSCFG
  * @brief SYSCFG driver modules
  * @{
  */

/** @defgroup SYSCFG_Private_Defines
  * @{
  */
#define        EXTI_SS_MASK            0x0F  /*!< Exti source select bit mask */
#define        EXTI_SS_STEP            0x04  /*!< Exti source select jumping step */
#define        EXTI_PIN_MASK           0x03  /*!< Exti pin bit mask */
#define        EXTI_SS_OFFSET          0x02  /*!< Exti source select offset */

/**
  * @}
  */

/** @defgroup SYSCFG_Private_Functions
  * @{
  */

/**
  * @brief  Reset the SYSCFG registers.
  * @param  None
  * @retval None
  * @note   BOOT_MODE bits are read only.
  */
void SYSCFG_DeInit(void)
{
    SYSCFG->R1 = 0;
    SYSCFG->EXTISS[0] = 0;
    SYSCFG->EXTISS[1] = 0;
    SYSCFG->EXTISS[2] = 0;
    SYSCFG->EXTISS[3] = 0;
#ifdef GD32F170_190
    SYSCFG->R2 = 0;
#endif
    SYSCFG->R3 = 0;
}

/**
  * @brief  Enable or disable the DMA channels remapping
  * @param  SYSCFG_dma_remap: Specify the DMA channels to remap.
  *   This parameter can be any of the following values:
  *     @arg SYSCFG_DMA_REMAP_TIMER17: Remap TIM17 CH1 and UP DMA requests to channel2(defaut channel1)
  *     @arg SYSCFG_DMA_REMAP_TIMER16: Remap TIM16 CH1 and UP DMA requests to channel4(defaut channel3)
  *     @arg SYSCFG_DMA_REMAP_USART1RX: Remap USART1 Rx DMA request to channel5(default channel3)
  *     @arg SYSCFG_DMA_REMAP_USART1TX: Remap USART1 Tx DMA request to channel4(default channel2)
  *     @arg SYSCFG_DMA_REMAP_ADC: Remap ADC1 DMA requests from channel1 to channel2
  * @param  NewValue: DMA remapping state to configure.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG_DMARemap_Config(uint32_t SYSCFG_dma_remap, TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        SYSCFG->R1 |= (uint32_t)SYSCFG_dma_remap;
    }
    else
    {
        SYSCFG->R1 &= (uint32_t)(~SYSCFG_dma_remap);
    }
}

/**
  * @brief  Enable or disable PB9 high current capability
  * @param  NewValue: PB9 high current state to configure.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG_HighCurrent_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE)
    {    
        SYSCFG->R1 |= (uint32_t)SYSCFG_HIGH_CURRENT_ENABLE;
    }
    else
    {   
        SYSCFG->R1 &= (uint32_t)SYSCFG_HIGH_CURRENT_DISABLE;
    }
}

#ifdef GD32F170_190

/**
  * @brief  Configure the VLCD intermediate voltage rail
  * @param  VLCD_Bias: Specify VLCD bias.
  *   This parameter can be any of the following values:
  *     @arg VLCD_BIAS1_2_RAIL1: VLCD bias is 1/2, using rail1
  *     @arg VLCD_BIAS1_2_RAIL2: VLCD bias is 1/2, using rail2
  *     @arg VLCD_BIAS1_2_RAIL3: VLCD bias is 1/2, using rail3
  *     @arg VLCD_BIAS1_3_RAIL1_2: VLCD bias is 1/3, using rail1 and rail2
  *     @arg VLCD_BIAS1_3_RAIL1_3: VLCD bias is 1/3, using rail1 and rail3
  *     @arg VLCD_BIAS1_4_RAILALL: VLCD bias is 1/4, using all rails
  * @retval None
  */
void SYSCFG_VLCDRail_Config(uint8_t VLCD_Bias)
{
    uint32_t Temp = SYSCFG->R2;

    /* Clear system configuration register 2 */
    SYSCFG->R2 = 0;

    switch(VLCD_Bias)
    {
        case VLCD_BIAS1_2_RAIL1:
            SYSCFG->R2 |= SYSCFG_VLCD_RAIL1;
            break;

        case VLCD_BIAS1_2_RAIL2:
            SYSCFG->R2 |= SYSCFG_VLCD_RAIL2;
            break;

        case VLCD_BIAS1_2_RAIL3:
            SYSCFG->R2 |= SYSCFG_VLCD_RAIL3;
            break;

        case VLCD_BIAS1_3_RAIL1_2:
            SYSCFG->R2 |= SYSCFG_VLCD_RAIL2 | SYSCFG_VLCD_RAIL1;
            break;

        case VLCD_BIAS1_3_RAIL1_3:
            SYSCFG->R2 |= SYSCFG_VLCD_RAIL3 | SYSCFG_VLCD_RAIL1;
            break;

        case VLCD_BIAS1_4_RAILALL:
            SYSCFG->R2 |= SYSCFG_VLCD_RAIL3 | SYSCFG_VLCD_RAIL2 | SYSCFG_VLCD_RAIL1;
            break;

        default:
            SYSCFG->R2 = Temp;
            break;
    }
}

#endif /* GD32F170_190 */

/**
  * @brief  Configure the GPIO pin as EXTI Line
  * @param  exti_port: Specify the GPIO port used in EXTI
  *   This parameter can be  any of the following values:
  *     @arg EXTI_SOURCE_GPIOA
  *     @arg EXTI_SOURCE_GPIOB
  *     @arg EXTI_SOURCE_GPIOC
  *     @arg EXTI_SOURCE_GPIOD
  *     @arg EXTI_SOURCE_GPIOF 
  * @param  exti_pin: Specify the EXTI line
  *   This parameter can be  any of the following values:
  *     @arg EXTI_SOURCE_PIN0
  *     @arg EXTI_SOURCE_PIN1
  *     @arg EXTI_SOURCE_PIN2
  *     @arg EXTI_SOURCE_PIN3
  *     @arg EXTI_SOURCE_PIN4
  *     @arg EXTI_SOURCE_PIN5
  *     @arg EXTI_SOURCE_PIN6
  *     @arg EXTI_SOURCE_PIN7
  *     @arg EXTI_SOURCE_PIN8
  *     @arg EXTI_SOURCE_PIN9
  *     @arg EXTI_SOURCE_PIN10
  *     @arg EXTI_SOURCE_PIN11
  *     @arg EXTI_SOURCE_PIN12
  *     @arg EXTI_SOURCE_PIN13
  *     @arg EXTI_SOURCE_PIN14
  *     @arg EXTI_SOURCE_PIN15
  * @retval None
  */
void SYSCFG_EXTILine_Config(uint8_t exti_port, uint8_t exti_pin)
{
    uint32_t temp = 0x00;

    temp = ((uint32_t)EXTI_SS_MASK) << (EXTI_SS_STEP * (exti_pin & (uint8_t)EXTI_PIN_MASK));
    SYSCFG->EXTISS[exti_pin >> EXTI_SS_OFFSET] &= ~temp;
    SYSCFG->EXTISS[exti_pin >> EXTI_SS_OFFSET] |= (((uint32_t)exti_port) << (EXTI_SS_STEP * (exti_pin & (uint8_t)EXTI_PIN_MASK)));
}

/**
  * @brief  Connect TIM1/15/16/17 break input to the selected parameter
  * @param  SYSCFG_lock: Specify the parameter to be connected
  *   This parameter can be any of the following values
  *     @arg SYSCFG_LOCK_LVD: LVD interrupt connected to the break input
  *     @arg SYSCFG_LOCK_SRAM_PARITY_ERROR: SRAM_PARITY check error connected to the break input
  *     @arg SYSCFG_LOCK_LOCKUP: Cortex-M3 Lockup output connected to the break input
  * @retval None
  */
void SYSCFG_Lock_Config(uint32_t SYSCFG_lock)
{
    SYSCFG->R3 |= (uint32_t) SYSCFG_lock;
}

/**
  * @brief  Check if the specified flag in SYSCFG_R3 is set or not.
  * @param  SYSCFG_flag: Specify the flag in SYSCFG_R3 to check.
  *   This parameter can be any of the following values:
  *     @arg SYSCFG_SRAM_PCEF: SRAM parity check error flag.
  * @retval The SYSCFG_flag state returned (SET or RESET).
  */
TypeState SYSCFG_GetBitState(uint32_t SYSCFG_flag)
{
    if ((SYSCFG->R3 & SYSCFG_SRAM_PCEF) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
  * @brief  Clear the flag in SYSCFG_R3.
  * @param  SYSCFG_flag: Specify the flag in SYSCFG_R2 to clear.
  *   This parameter can be any of the following values:
  *     @arg SYSCFG_SRAM_PCEF: SRAM parity check error flag.
  * @retval None
  */
void SYSCFG_ClearBitState(uint32_t SYSCFG_flag)
{
    SYSCFG->R3 |= (uint32_t) SYSCFG_flag;
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

/************************ (C) COPYRIGHT 2016 GIGADEVICE*****END OF FILE****/
