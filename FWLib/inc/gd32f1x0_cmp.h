/**
  ******************************************************************************
  * @file    gd32f1x0_cmp.h
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   CMP header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F1X0_CMP_H
#define __GD32F1X0_CMP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0.h"

/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @addtogroup CMP
  * @{
  */

/** @defgroup CMP_Exported_Types
  * @{
  */

/** 
  * @brief CMP Initial Parameters
  */

typedef struct
{
    uint32_t CMP_InvertingInput;                                     /*!< The inverting input, detailed in @ref CMP_InvertingInput */
    uint32_t CMP_Output;                                             /*!< The output, detailed in @ref CMP_Output */
    uint32_t CMP_OutputPolarity;                                     /*!< The output polarity, detailed in @ref CMP_OutputPolarity */
    uint32_t CMP_Hysteresis;                                         /*!< The hysteresis level, detailed in @ref CMP_Hysteresis */
    uint32_t CMP_OperatingMode;                                      /*!< The operating mode, detailed in @ref CMP_OperatingMode */
}CMP_InitPara;

/**
  * @}
  */

/** @defgroup CMP_Exported_Constants
  * @{
  */

/** @defgroup CMP_Channel
  * @{
  */
#define CMP_CHANNEL_CMP1                    ((uint32_t)0x00000000)   /*!< comparator channel 1 */
#define CMP_CHANNEL_CMP2                    ((uint32_t)0x00000010)   /*!< comparator channel 2 */
/**
  * @}
  */

/** @defgroup CMP_InvertingInput
  * @{
  */
#define CMP_INVERTINGINPUT_1_4VREFINT       ((uint32_t)0x00000000)   /*!< comparator inverting input 1/4 Vrefint */
#define CMP_INVERTINGINPUT_1_2VREFINT       CMP_CSR_CMP1MSEL_0       /*!< comparator inverting input 1/2 Vrefint */
#define CMP_INVERTINGINPUT_3_4VREFINT       CMP_CSR_CMP1MSEL_1       /*!< comparator inverting input 3/4 Vrefint */
#define CMP_INVERTINGINPUT_VREFINT          ((uint32_t)0x00000030)   /*!< comparator inverting input Vrefint */
#define CMP_INVERTINGINPUT_DAC1             CMP_CSR_CMP1MSEL_2       /*!< comparator inverting input DAC1*/
#define CMP_INVERTINGINPUT_DAC2             ((uint32_t)0x00000050)       /*!< comparator inverting input DAC1*/
#define CMP_INVERTINGINPUT_IO               ((uint32_t)0x00000060)   /*!< comparator inverting input  */

/**
  * @}
  */
  
/** @defgroup CMP_Output
  * @{
  */
#define CMP_OUTPUT_NONE                     ((uint32_t)0x00000000)   /*!< comparator output none  */
#define CMP_OUTPUT_TIM1BKIN                 CMP_CSR_CMP1OSEL_0       /*!< comparator output timer 1 break input */
#define CMP_OUTPUT_TIM1IC1                  CMP_CSR_CMP1OSEL_1       /*!< comparator output timer 1 channel 1 input capture */
#define CMP_OUTPUT_TIM1OCREFCLR             ((uint32_t)0x00000300)   /*!< comparator output timer 1 ocrefclear input */
#define CMP_OUTPUT_TIM2IC4                  CMP_CSR_CMP1OSEL_2       /*!< comparator output timer 2 channel 4 input capture */
#define CMP_OUTPUT_TIM2OCREFCLR             ((uint32_t)0x00000500)   /*!< comparator output timer 2 ocrefclear input */
#define CMP_OUTPUT_TIM3IC1                  ((uint32_t)0x00000600)   /*!< comparator output timer 3 channle 1 input capture */
#define CMP_OUTPUT_TIM3OCREFCLR             CMP_CSR_CMP1OSEL         /*!< comparator output timer 3 ocrefclear input */

/**
  * @}
  */

/** @defgroup CMP_OutputPolarity
  * @{
  */
#define CMP_OUTPUTPOLARITY_NONINVERTED      ((uint32_t)0x00000000)   /*!< comparator output polarity noninverted */
#define CMP_OUTPUTPOLARITY_INVERTED         CMP_CSR_CMP1PL           /*!< comparator output polarity inverted */

/**
  * @}
  */

/** @defgroup CMP_Hysteresis
  * @{
  */
#define CMP_HYSTERESIS_NO                   0x00000000               /*!< comparator output no hysteresis */
#define CMP_HYSTERESIS_LOW                  CMP_CSR_CMP1HST_0        /*!< comparator output low hysteresis */
#define CMP_HYSTERESIS_MEDIUM               CMP_CSR_CMP1HST_1        /*!< comparator output medium hysteresis */
#define CMP_HYSTERESIS_HIGH                 CMP_CSR_CMP1HST          /*!< comparator output high hysteresis */

/**
  * @}
  */

/** @defgroup CMP_OperatingMode
  * @{
  */
#define CMP_OPERATINGMODE_HIGHSPEED         0x00000000               /*!< comparator mode high speed */
#define CMP_OPERATINGMODE_MEDIUMSPEED       CMP_CSR_CMP1M_0          /*!< comparator mode medium speed */
#define CMP_OPERATINGMODE_LOWSPEED          CMP_CSR_CMP1M_1          /*!< comparator mode low speed */
#define CMP_OPERATINGMODE_VERYLOWSPEED      CMP_CSR_CMP1M            /*!< comparator mode very low speed */

/**
  * @}
  */

/** @defgroup CMP_OutputLevel
  * @{
  */
#define CMP_OUTPUTLEVEL_HIGH                ((uint32_t)0x00000001)   /*!< comparator output high */
#define CMP_OUTPUTLEVEL_LOW                 ((uint32_t)0x00000000)   /*!< comparator output low */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup CMP_Exported_Functions
  * @{
  */
void CMP_DeInit(void);
void CMP_Init(uint32_t CMP_Channel, CMP_InitPara* CMP_InitParaStruct);
void CMP_ParaInit(CMP_InitPara* CMP_InitParaStruct);
void CMP_Enable(uint32_t CMP_Channel, TypeState NewState);
void CMP_Switch_Enable(TypeState NewState);
uint32_t CMP_GetOutputLevel(uint32_t CMP_Channel);
void CMP_Window_Enable(TypeState NewState);
void CMP_LockConfig(uint32_t CMP_Channel);

#ifdef __cplusplus
}
#endif

#endif /*__GD32F1X0_CMP_H */

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
