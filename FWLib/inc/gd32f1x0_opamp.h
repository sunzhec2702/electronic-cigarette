/**
  ******************************************************************************
  * @file    gd32f1x0_opamp.h
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   OPAMP header file of the firmware library.
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F1X0_OPAMP_H
#define __GD32F1X0_OPAMP_H

#ifdef GD32F170_190

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0.h"

/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @addtogroup OPAMP
  * @{
  */

/** @defgroup OPAMP_Exported_Types
  * @{
  */


/** @defgroup OPAMP_Exported_Constants
  * @{
  */


/** @defgroup OPAMP_Selection
  * @{
  */
#define OPAMP1                          OPAMP_CTLR_OPA1PD /*!< Select OPAMP1 */
#define OPAMP2                          OPAMP_CTLR_OPA2PD /*!< Select OPAMP2 */
#define OPAMP3                          OPAMP_CTLR_OPA3PD /*!< Select OPAMP3 */

/**
  * @}
  */

/** @defgroup OPAMP_Switches
  * @{
  */
#define OPAMP_T3OPA1                    OPAMP_CTLR_T3OPA1 /*!< T3 switch enable for OPAMP1 */
#define OPAMP_S1OPA1                    OPAMP_CTLR_S1OPA1 /*!< S1 switch enable for OPAMP1 */
#define OPAMP_S2OPA1                    OPAMP_CTLR_S2OPA1 /*!< S2 switch enable for OPAMP1 */
#define OPAMP_S3OPA1                    OPAMP_CTLR_S3OPA1 /*!< S3 switch enable for OPAMP1 */
#define OPAMP_T3OPA2                    OPAMP_CTLR_S3OPA2 /*!< T3 switch enable for OPAMP2 */
#define OPAMP_S1OPA2                    OPAMP_CTLR_S1OPA2 /*!< S1 switch enable for OPAMP2 */
#define OPAMP_S2OPA2                    OPAMP_CTLR_S2OPA2 /*!< S2 switch enable for OPAMP2 */
#define OPAMP_S3OPA2                    OPAMP_CTLR_S3OPA2 /*!< S3 switch enable for OPAMP2 */
#define OPAMP_S4OPA2                    OPAMP_CTLR_S4OPA2 /*!< S4 switch enable for OPAMP2 */
#define OPAMP_T3OPA3                    OPAMP_CTLR_T3OPA3 /*!< T3 switch enable for OPAMP3 */
#define OPAMP_S1OPA3                    OPAMP_CTLR_S1OPA3 /*!< S3 switch enable for OPAMP3 */
#define OPAMP_S2OPA3                    OPAMP_CTLR_S2OPA3 /*!< S3 switch enable for OPAMP3 */
#define OPAMP_S3OPA3                    OPAMP_CTLR_S3OPA3 /*!< S3 switch enable for OPAMP3 */


/**
  * @}
  */


/** @defgroup OPAMP_Trimming
  * @{
  */

#define OPAMP_OTR_TRIM_FACTORY          ((uint32_t)0x00000000) /*!< Factory trimming */
#define OPAMP_OTR_TRIM_USER             OPAMP_OTR_OT_USER      /*!< User trimming */

/**
  * @}
  */

/** @defgroup OPAMP_Input
  * @{
  */
#define OPAMP_INPUT_N                   ((uint32_t)0x00000040) /*!< NMOS input */
#define OPAMP_INPUT_P                   ((uint32_t)0x00000020) /*!< PMOS input */

/**
  * @}
  */


/** @defgroup OPAMP_TrimValue
  * @{
  */

#define OPAMP_TRIMVALUE(VALUE) ((VALUE) <= 0x0000001F) /*!< Trim value */

/**
  * @}
  */

/** @defgroup OPAMP_OPARange
  * @{
  */
#define OPAMP_OPARANGE_LOW              ((uint32_t)0x00000000) /*!< Low power range is selected (VDDA is lower than 3.3V) */
#define OPAMP_OPARANGE_HIGH              OPAMP_CTLR_OPA_RANGE   /*!< High power range is selected (VDDA is higher than 3.3V) */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup OPAMP_Exported_Functions
  * @{
  */
void OPAMP_DeInit(void);
void OPAMP_SwitchEnable(uint32_t OPAMP_OPAMPxSy, TypeState NewValue);
void OPAMP_Enable(uint32_t OPAMPx, TypeState NewValue);
void OPAMP_LowPowerEnable(uint32_t OPAMPx, TypeState NewValue);
void OPAMP_PowerRangeConfig(uint32_t OPAMP_PowerRange);
void OPAMP_OffsetTrimModeConfig(uint32_t OPAMP_TrimMode);
void OPAMP_OffsetTrimValueConfig(uint32_t OPAMPx, uint32_t OPAMP_Input, uint32_t OPAMP_TrimValue);
void OPAMP_OffsetTrimValueLowPowerConfig(uint32_t OPAMPx, uint32_t OPAMP_Input, uint32_t OPAMP_TrimValue);
TypeState OPAMP_GetBitState(uint32_t OPAMPx);


#ifdef __cplusplus
}
#endif

#endif /* __GD32F1X0_OPAMP_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif  /* GD32F170_190 */
/******************* (C) COPYRIGHT 2016 GIGADEVICE *****END OF FILE****/
