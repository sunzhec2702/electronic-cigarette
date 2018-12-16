/**
  ******************************************************************************
  * @file    gd32f1x0_mcudbg.h
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   MCUDBG header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F1X0_MCUDBG_H
#define __GD32F1X0_MCUDBG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0.h"

/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @addtogroup MCUDBG
  * @{
  */

/** @defgroup MCUDBG_Exported_Constants
  * @{
  */
/* MCUDBG_CTLR1 */
#define MCUDBG_SLEEP_HOLD               MCUDBG_CTLR1_SLEEP_HOLD         /*!< Sleep mode hold       */
#define MCUDBG_DEEPSLEEP_HOLD           MCUDBG_CTLR1_DEEPSLEEP_HOLD     /*!< Deep-sleep mode hold  */
#define MCUDBG_STANDBY_HOLD             MCUDBG_CTLR1_STANDBY_HOLD       /*!< Standby mode hold     */
#define MCUDBG_IWDG_HOLD                MCUDBG_CTLR1_IWDG_HOLD          /*!< IWDG hold             */
#define MCUDBG_WWDG_HOLD                MCUDBG_CTLR1_WWDG_HOLD          /*!< WWDG hold             */
#define MCUDBG_TIMER1_HOLD              MCUDBG_CTLR1_TIMER1_HOLD        /*!< TIMER1 hold           */
#define MCUDBG_TIMER2_HOLD              MCUDBG_CTLR1_TIMER2_HOLD        /*!< TIMER12 hold          */
#define MCUDBG_TIMER3_HOLD              MCUDBG_CTLR1_TIMER3_HOLD        /*!< TIMER13 hold          */
#define MCUDBG_I2C1_HOLD                MCUDBG_CTLR1_I2C1_HOLD          /*!< I2C1 hold             */
#define MCUDBG_I2C2_HOLD                MCUDBG_CTLR1_I2C2_HOLD          /*!< I2C2 hold             */
#define MCUDBG_I2C3_HOLD                MCUDBG_CTLR1_I2C3_HOLD          /*!< I2C3 hold             */
#define MCUDBG_TIMER6_HOLD              MCUDBG_CTLR1_TIMER6_HOLD        /*!< TIMER6 hold           */
#define MCUDBG_TIMER14_HOLD             MCUDBG_CTLR1_TIMER14_HOLD       /*!< TIMER14 hold          */
#ifdef GD32F170_190
#define MCUDBG_CAN1_HOLD                MCUDBG_CTLR1_CAN1_HOLD          /*!< CAN1 hold             */
#define MCUDBG_CAN2_HOLD                MCUDBG_CTLR1_CAN2_HOLD          /*!< CAN2 hold             */
#endif /* GD32F170_190 */

/* MCUDBG_CTLR2 */
#define MCUDBG_RTC_HOLD                 MCUDBG_CTLR2_RTC_HOLD           /*!< RTC hold              */
#define MCUDBG_TIMER15_HOLD             MCUDBG_CTLR2_TIMER15_HOLD       /*!< TIMER15 hold          */
#define MCUDBG_TIMER16_HOLD             MCUDBG_CTLR2_TIMER16_HOLD       /*!< TIMER15 hold          */
#define MCUDBG_TIMER17_HOLD             MCUDBG_CTLR2_TIMER17_HOLD       /*!< TIMER15 hold          */

/**
  * @}
  */ 

/** @defgroup MCUDBG_Exported_Functions
  * @{
  */

uint32_t MCUDBG_GetID(void);
void MCUDBG_CTLR1PeriphConfig(uint32_t MCUDBG_CTLR1Periph, TypeState NewValue);
void MCUDBG_CTLR2PeriphConfig(uint32_t MCUDBG_CTLR2Periph, TypeState NewValue);

#ifdef __cplusplus
}
#endif

#endif /* __GD32F1X0_MCUDBG_H */

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
