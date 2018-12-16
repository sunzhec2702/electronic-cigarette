/**
  ******************************************************************************
  * @file    gd32f1x0_dac.h
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   DAC header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F1X0_DAC_H
#define __GD32F1X0_DAC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0.h"
 
/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @addtogroup DAC
  * @{
  */

/** @defgroup DAC_Exported_Types
  * @{
  */

/** 
  * @brief  DAC Initial Parameters 
  */
typedef struct
{
    uint32_t DAC_Trigger;               /*!< external trigger of the selected DAC.
                                             This parameter can be a value of @ref DAC_Trigger */
    uint32_t DAC_OutputBuffer;          /*!< Specifies whether the DAC output buffer is enabled or disabled
                                             This parameter can be a value of @ref DAC_OutputBuffer */
}DAC_InitPara;

/**
  * @}
  */

/** @defgroup DAC_Exported_Constants
  * @{
  */

/** @defgroup DAC_Trigger
  * @{
  */
#define DAC_TRIGGER_NONE                ((uint32_t)0x00000000) /*!< no trigger */
#define DAC_TRIGGER_T2_TRGO             ((uint32_t)0x00000024) /*!< TIMER2 TRGO */
#define DAC_TRIGGER_T3_TRGO             ((uint32_t)0x0000000C) /*!< TIMER3 TRGO */
#define DAC_TRIGGER_T6_TRGO             ((uint32_t)0x00000004) /*!< TIMER6 TRGO */
#define DAC_TRIGGER_T15_TRGO            ((uint32_t)0x0000001C) /*!< TIMER15 TRGO */
#define DAC_TRIGGER_EXTI_IT9            ((uint32_t)0x00000034) /*!< EXTI Line9 event */
#define DAC_TRIGGER_SOFTWARE            ((uint32_t)0x0000003C) /*!< software trigger */

/**
  * @}
  */

/** @defgroup DAC_OutputBuffer
  * @{
  */

#define DAC_OUTPUTBUFFER_ENABLE         ((uint32_t)0x00000000) /*!< DAC_OutputBuffer enable */
#define DAC_OUTPUTBUFFER_DISABLE        ((uint32_t)0x00000002) /*!< DAC_OutputBuffer disable */

/**
  * @}
  */

/** @defgroup DAC_selection
  * @{
  */

#define DAC1                            ((uint32_t)0x00000000) /*!< DAC_select DAC1 */
#ifdef GD32F170_190
#define DAC2                            ((uint32_t)0x00000010) /*!< DAC_select DAC2 */ 
#endif  /* GD32F170_190 */
/**
  * @}
  */

/** @defgroup DAC_interrupts_definition
  * @{
  */
#define DAC_INT_DMAUDR                  ((uint32_t)0x00002000) /*!< DAC interrupts_definition */

/**
  * @}
  */

/** @defgroup DAC_data_alignment
  * @{
  */
#define DAC_ALIGN_12B_R                 ((uint32_t)0x00000000) /*!< Data right 12b alignment */
#define DAC_ALIGN_12B_L                 ((uint32_t)0x00000004) /*!< Data left 12b alignment */
#define DAC_ALIGN_8B_R                  ((uint32_t)0x00000008) /*!< Data right 8b alignment */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup DAC_Exported_Functions
  * @{
  */
void DAC_DeInit(DAC_InitPara* DAC_InitParaStruct);
void DAC_Init(uint32_t DACx, DAC_InitPara* DAC_InitParaStruct);
void DAC_Enable(uint32_t DACx, TypeState NewValue);
void DAC_INTConfig(uint32_t DACx, TypeState NewValue);
void DAC_SoftwareTrigger_Enable(uint32_t DACx, TypeState NewValue);
void DAC_SetDAC1Data(uint32_t DAC_Align, uint16_t Data);
#ifdef GD32F170_190
void DAC_DualSoftwareTrigger_Enable(TypeState NewValue);
void DAC_SetDAC2Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetDualDACData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1);
#endif  /* GD32F170_190 */
uint16_t DAC_GetDataOutputValue(uint32_t DACx);
void DAC_DMA_Enable(uint32_t DACx, TypeState NewValue);
TypeState DAC_GetBitState(uint32_t DACx);
void DAC_ClearBitState(uint32_t DACx);
TypeState DAC_GetIntState(uint32_t DACx);




#ifdef __cplusplus
}
#endif

#endif /*__GD32F1X0_DAC_H */

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
