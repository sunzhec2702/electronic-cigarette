/**
  ******************************************************************************
  * @file    gd32f1x0_mcudbg.c
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   MCUDBG functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0_mcudbg.h"

/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @defgroup MCUDBG 
  * @brief MCUDBG driver modules
  * @{
  */ 

/** @defgroup MCUDBG_Private_Defines
  * @{
  */


/**
  * @}
  */

/** @defgroup MCUDBG_Private_Functions
  * @{
  */


/**
  * @brief  Read MCUDBG ID code register.
  * @param  None
  * @retval MCUDBG ID code
  */
uint32_t MCUDBG_GetID(void)
{
   return(MCUDBG->IDR);
}

/**
  * @brief  Configure CTLR1 peripheral behavior in Debug mode.
  * @param  MCUDBG_CTLR1Periph: CTLR1 peripheral.
  *
  *   For @b GD32F130 or GD32F150 devices, this parameter can be any combination of 
  *   the following values:
  *     @arg MCUDBG_SLEEP_HOLD: Keep debugger connection during SLEEP mode              
  *     @arg MCUDBG_DEEPSLEEP_HOLD: Keep debugger connection during DEEPSLEEP mode
  *     @arg MCUDBG_STANDBY_HOLD: Keep debugger connection during STANDBY mode
  *     @arg MCUDBG_IWDG_HOLD: Debug IWDG kept when Core is halted          
  *     @arg MCUDBG_WWDG_HOLD: Debug WWDG kept when Core is halted          
  *     @arg MCUDBG_TIMER1_HOLD: TIMER1 counter kept when Core is halted
  *     @arg MCUDBG_TIMER2_HOLD: TIMER2 counter kept when Core is halted
  *     @arg MCUDBG_TIMER3_HOLD: TIMER3 counter kept when Core is halted
  *     @arg MCUDBG_I2C1_HOLD: Hold I2C1 SMBUS when Core is halted
  *     @arg MCUDBG_I2C2_HOLD: Hold I2C2 SMBUS when Core is halted
  *     @arg MCUDBG_I2C3_HOLD: Hold I2C3 SMBUS when Core is halted
  *     @arg MCUDBG_TIMER6_HOLD: Hold TIMER6 counter when Core is halted
  *     @arg MCUDBG_TIMER14_HOLD: Hold TIMER14 counter when Core is halted
  *
  *   For @b GD32F170 or GD32F190 devices, this parameter can be any combination of 
  *   the following values:
  *     @arg MCUDBG_SLEEP_HOLD: Keep debugger connection during SLEEP mode 
  *     @arg MCUDBG_DEEPSLEEP_HOLD: Keep debugger connection during DEEPSLEEP mode
  *     @arg MCUDBG_STANDBY_HOLD: Keep debugger connection during STANDBY mode
  *     @arg MCUDBG_IWDG_HOLD: Debug IWDG kept when Core is halted          
  *     @arg MCUDBG_WWDG_HOLD: Debug WWDG kept when Core is halted          
  *     @arg MCUDBG_TIMER1_HOLD: TIMER1 counter kept when Core is halted
  *     @arg MCUDBG_TIMER2_HOLD: TIMER2 counter kept when Core is halted
  *     @arg MCUDBG_TIMER3_HOLD: TIMER3 counter kept when Core is halted
  *     @arg MCUDBG_CAN1_HOLD: CAN1 counter kept when Core is halted
  *     @arg MCUDBG_I2C1_HOLD: Hold I2C1 SMBUS when Core is halted
  *     @arg MCUDBG_I2C2_HOLD: Hold I2C2 SMBUS when Core is halted
  *     @arg MCUDBG_I2C3_HOLD: Hold I2C3 SMBUS when Core is halted
  *     @arg MCUDBG_TIMER6_HOLD: Hold TIMER6 counter when Core is halted
  *     @arg MCUDBG_CAN2_HOLD: Hold CAN2 counter when Core is halted
  *     @arg MCUDBG_TIMER14_HOLD: Hold TIMER14 counter when Core is halted
  *
  * @param  NewValue: new value of the specified CTLR1 peripheral in Debug mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void MCUDBG_CTLR1PeriphConfig(uint32_t MCUDBG_CTLR1Periph, TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        MCUDBG->CTLR1 |= MCUDBG_CTLR1Periph;
    }
    else
    {
        MCUDBG->CTLR1 &= ~MCUDBG_CTLR1Periph;
    }
}

/**
  * @brief  Configure CTLR2 peripheral behavior when the MCU is in Debug mode.
  * @param  MCUDBG_CTLR2Periph:  CTLR2 peripheral.
  *   This parameter can be any combination of the following values:
  *     @arg MCUDBG_RTC_HOLD: Hold RTC Calendar and Wakeup counter when Core is halted.
  *     @arg MCUDBG_TIMER15_HOLD: Hold TIMER15 counter when Core is halted
  *     @arg MCUDBG_TIMER16_HOLD: Hold TIMER16 counter when Core is halted
  *     @arg MCUDBG_TIMER17_HOLD: Hold TIMER17 counter when Core is halted
  * @param  NewValue: new value of the specified APB2 peripheral in Debug mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void MCUDBG_CTLR2PeriphConfig(uint32_t MCUDBG_CTLR2Periph, TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        MCUDBG->CTLR2 |= MCUDBG_CTLR2Periph;
    }
    else
    {
        MCUDBG->CTLR2 &= ~MCUDBG_CTLR2Periph;
    }
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
