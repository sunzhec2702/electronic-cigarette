/**
  ******************************************************************************
  * @file    gd32f1x0_iwdg.h
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   IWDG header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F1X0_IWDG_H
#define __GD32F1X0_IWDG_H

/* Exported macro ------------------------------------------------------------*/

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0.h"

/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @defgroup IWDG
  * @{
  */

/** @defgroup IWDG_Exported_Constants
  * @{
  */

/** @defgroup IWDG_WriteAccess
  * @{
  */
#define IWDG_WRITEACCESS_ENABLE     ((uint16_t)0x5555) /*!< Enable watchdog registers write access */
#define IWDG_WRITEACCESS_DISABLE    ((uint16_t)0x0000) /*!< Disable watchdog registers write access */

/**
  * @}
  */

/** @defgroup IWDG_prescaler 
  * @{
  */
#define IWDG_PRESCALER_4            ((uint8_t)0x00)  /*!< Independent watchdog timer perscaler is 1/4 frequency division */
#define IWDG_PRESCALER_8            ((uint8_t)0x01)  /*!< Independent watchdog timer perscaler is 1/8 frequency division */
#define IWDG_PRESCALER_16           ((uint8_t)0x02)  /*!< Independent watchdog timer perscaler is 1/16 frequency division */
#define IWDG_PRESCALER_32           ((uint8_t)0x03)  /*!< Independent watchdog timer perscaler is 1/32 frequency division */
#define IWDG_PRESCALER_64           ((uint8_t)0x04)  /*!< Independent watchdog timer perscaler is 1/64 frequency division */
#define IWDG_PRESCALER_128          ((uint8_t)0x05)  /*!< Independent watchdog timer perscaler is 1/128 frequency division */
#define IWDG_PRESCALER_256          ((uint8_t)0x06)  /*!< Independent watchdog timer perscaler is 1/256 frequency division */

/**
  * @}
  */

/** @defgroup IWDG_Flag
  * @{
  */
#define IWDG_BIT_PUD                IWDG_STR_PUD    /*!< Watchdog prescaler value update */
#define IWDG_BIT_RUD                IWDG_STR_RUD    /*!< Watchdog counter reload value update */
#define IWDG_BIT_WUD                IWDG_STR_WUD    /*!< Watchdog counter window value update */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup IWDG_Exported_functions
  * @{
  */
/* Prescaler and Counter configuration functions ******************************/
void IWDG_Write_Enable(uint16_t IWDG_WriteAccess);
void IWDG_SetPrescaler(uint8_t PrescalerValue);
void IWDG_SetReloadValue(uint16_t ReloadValue);
void IWDG_ReloadCounter(void);
void IWDG_SetWindowValue(uint16_t WindowValue);

/* IWDG activation function ***************************************************/
void IWDG_Enable(void);

/* Flag management function ***************************************************/
TypeState IWDG_GetBitState(uint16_t IWDG_FLAG);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __GD32F1X0_IWDG_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2016 GIGADEVICE *****END OF FILE****/
