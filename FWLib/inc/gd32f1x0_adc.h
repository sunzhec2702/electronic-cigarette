/**
  ******************************************************************************
  * @file    gd32f1x0_adc.h
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   ADC header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F1X0_ADC_H
#define __GD32F1X0_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0.h"
/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/** @defgroup ADC_Exported_Types
  * @{
  */

/** 
  * @brief  ADC Initial Parameters 
  */
typedef struct
{
    uint32_t ADC_Trig_External;         /*!< Defines the external trigger used to start the AD conversion of regular channels.  */
    uint8_t ADC_Channel_Number;         /*!< Specifies the number of ADC channels that will be converted.
                                             This parameter must range from 1 to 16. */ 
    uint32_t ADC_Data_Align;            /*!< Specifies whether the ADC data alignment is left or right. */
    TypeState ADC_Mode_Scan;            /*!< Specifies whether the conversion is performed in
                                             multichannels or Single channel mode.
                                             This parameter can be set to ENABLE or DISABLE */
    TypeState ADC_Mode_Continuous;      /*!< Specifies whether the conversion is performed in
                                             Continuous or Single mode.
                                             This parameter can be set to ENABLE or DISABLE. */
}ADC_InitPara;

/**
  * @}
  */

/** @defgroup ADC_Exported_Constants
  * @{
  */
  
/** @defgroup ADC_External_Trigger_For_Regular_Channels 
  * @{
  */

#define ADC_EXTERNAL_TRIGGER_MODE_T1_CC1                ((uint32_t)0x00000000)      /*!< External trigger Timer 1 CC1 event select for regular channel */
#define ADC_EXTERNAL_TRIGGER_MODE_T1_CC2                ((uint32_t)0x00020000)      /*!< External trigger Timer 1 CC2 event select for regular channel */
#define ADC_EXTERNAL_TRIGGER_MODE_T1_CC3                ((uint32_t)0x00040000)      /*!< External trigger Timer 1 CC3 event select for regular channel */
#define ADC_EXTERNAL_TRIGGER_MODE_T2_CC2                ((uint32_t)0x00060000)      /*!< External trigger Timer 2 CC2 event select for regular channel */
#define ADC_EXTERNAL_TRIGGER_MODE_T3_TRGO               ((uint32_t)0x00080000)      /*!< External trigger Timer 3 TRGO event select for regular channel */
#define ADC_EXTERNAL_TRIGGER_MODE_T15_CC1               ((uint32_t)0x000A0000)      /*!< External trigger Timer 15 CC1 event select for regular channel */
#define ADC_EXTERNAL_TRIGGER_MODE_EXT_IT11              ((uint32_t)0x000C0000)      /*!< External trigger Extiline 11 select for regular channel */
#define ADC_EXTERNAL_TRIGGER_MODE_NONE                  ((uint32_t)0x000E0000)      /*!< Software trigger select for regular channel */

/**
  * @}
  */

/** @defgroup ADC_Data_Align 
  * @{
  */
#define ADC_DATAALIGN_RIGHT                             ((uint32_t)0x00000000)      /*!< Data LSB alignment */
#define ADC_DATAALIGN_LEFT                              ((uint32_t)0x00000800)      /*!< Data HSB alignment */

/**
  * @}
  */

/** @defgroup ADC_Channels 
  * @{
  */
#define ADC_CHANNEL_0                                   ((uint8_t)0x00)             /*!< Channel 0 selected */
#define ADC_CHANNEL_1                                   ((uint8_t)0x01)             /*!< Channel 1 selected */
#define ADC_CHANNEL_2                                   ((uint8_t)0x02)             /*!< Channel 2 selected */
#define ADC_CHANNEL_3                                   ((uint8_t)0x03)             /*!< Channel 3 selected */
#define ADC_CHANNEL_4                                   ((uint8_t)0x04)             /*!< Channel 4 selected */
#define ADC_CHANNEL_5                                   ((uint8_t)0x05)             /*!< Channel 5 selected */
#define ADC_CHANNEL_6                                   ((uint8_t)0x06)             /*!< Channel 6 selected */
#define ADC_CHANNEL_7                                   ((uint8_t)0x07)             /*!< Channel 7 selected */
#define ADC_CHANNEL_8                                   ((uint8_t)0x08)             /*!< Channel 8 selected */
#define ADC_CHANNEL_9                                   ((uint8_t)0x09)             /*!< Channel 9 selected */
#define ADC_CHANNEL_10                                  ((uint8_t)0x0A)             /*!< Channel 10 selected */
#define ADC_CHANNEL_11                                  ((uint8_t)0x0B)             /*!< Channel 11 selected */
#define ADC_CHANNEL_12                                  ((uint8_t)0x0C)             /*!< Channel 12 selected */
#define ADC_CHANNEL_13                                  ((uint8_t)0x0D)             /*!< Channel 13 selected */
#define ADC_CHANNEL_14                                  ((uint8_t)0x0E)             /*!< Channel 14 selected */
#define ADC_CHANNEL_15                                  ((uint8_t)0x0F)             /*!< Channel 15 selected */
#define ADC_CHANNEL_16                                  ((uint8_t)0x10)             /*!< Channel 16 selected */
#define ADC_CHANNEL_17                                  ((uint8_t)0x11)             /*!< Channel 17 selected */
#define ADC_CHANNEL_18                                  ((uint8_t)0x12)             /*!< Channel 18 selected */
#define ADC_CHANNEL_TEMPSENSOR                          ((uint8_t)ADC_CHANNEL_16)   /*!< Tempreture channel(16) selected */
#define ADC_CHANNEL_VREFINT                             ((uint8_t)ADC_CHANNEL_17)   /*!< Reference voltage channel(17) selected */
#define ADC_CHANNEL_VBAT                                ((uint8_t)ADC_CHANNEL_18)   /*!< Battary voltage channel(18) selected */

/**
  * @}
  */

/** @defgroup ADC_Sampling_Time 
  * @{
  */
#define ADC_SAMPLETIME_1POINT5                          ((uint8_t)0x00)             /*!< Channel sample time 1.5 cycles */
#define ADC_SAMPLETIME_7POINT5                          ((uint8_t)0x01)             /*!< Channel sample time 7.5 cycles */
#define ADC_SAMPLETIME_13POINT5                         ((uint8_t)0x02)             /*!< Channel sample time 13.5 cycles */
#define ADC_SAMPLETIME_28POINT5                         ((uint8_t)0x03)             /*!< Channel sample time 28.5 cycles */
#define ADC_SAMPLETIME_41POINT5                         ((uint8_t)0x04)             /*!< Channel sample time 41.5 cycles */
#define ADC_SAMPLETIME_55POINT5                         ((uint8_t)0x05)             /*!< Channel sample time 55.5 cycles */
#define ADC_SAMPLETIME_71POINT5                         ((uint8_t)0x06)             /*!< Channel sample time 71.5 cycles */
#define ADC_SAMPLETIME_239POINT5                        ((uint8_t)0x07)             /*!< Channel sample time 239.5 cycles */

/**
  * @}
  */

/** @defgroup ADC_External_Trigger_For_Inserted_Channels
  * @{
  */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T1_TRGO            ((uint32_t)0x00000000)      /*!< External trigger Timer 1 TRGO event select for inserted channel */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T1_CC4             ((uint32_t)0x00001000)      /*!< External trigger Timer 1 CC4 event select for inserted channel */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T2_TRGO            ((uint32_t)0x00002000)      /*!< External trigger Timer 2 TRGO event select for inserted channel */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T2_CC1             ((uint32_t)0x00003000)      /*!< External trigger Timer 2 CC1 event select for inserted channel */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T3_CC4             ((uint32_t)0x00004000)      /*!< External trigger Timer 3 CC4 event select for inserted channel */
#define ADC_EXTERNAL_TRIG_INSERTCONV_T15_TRGO           ((uint32_t)0x00005000)      /*!< External trigger Timer 15 TRGO event select for inserted channel */
#define ADC_EXTERNAL_TRIG_INSERTCONV_EXT_IT15           ((uint32_t)0x00006000)      /*!< External trigger Extiline 15 event select for inserted channel */
#define ADC_EXTERNAL_TRIG_INSERTCONV_NONE               ((uint32_t)0x00007000)      /*!< Software trigger select for inserted channel */

/**
  * @}
  */

/** @defgroup ADC_Inserted_Channel_Selection
  * @{
  */
#define ADC_INSERTEDCHANNEL_1                           ((uint8_t)0x14)             /*!< Inserted channel 1 */
#define ADC_INSERTEDCHANNEL_2                           ((uint8_t)0x18)             /*!< Inserted channel 2 */
#define ADC_INSERTEDCHANNEL_3                           ((uint8_t)0x1C)             /*!< Inserted channel 3 */
#define ADC_INSERTEDCHANNEL_4                           ((uint8_t)0x20)             /*!< Inserted channel 4 */

/**
  * @}
  */

/** @defgroup ADC_Analog_Watchdog_Selection 
  * @{
  */
#define ADC_ANALOGWATCHDOG_SINGLEREGENABLE              ((uint32_t)0x00800200)      /*!< Analog watchdog on one regular channel */
#define ADC_ANALOGWATCHDOG_SINGLEINSERTENABLE           ((uint32_t)0x00400200)      /*!< Analog watchdog on one inserted channel */
#define ADC_ANALOGWATCHDOG_SINGLEREGORINSERTENABLE      ((uint32_t)0x00C00200)      /*!< Analog watchdog on one regular or inserted channel */
#define ADC_ANALOGWATCHDOG_ALLREGENABLE                 ((uint32_t)0x00800000)      /*!< Analog watchdog on all regular channel */
#define ADC_ANALOGWATCHDOG_ALLINSERTENABLE              ((uint32_t)0x00400000)      /*!< Analog watchdog on all inserted channel */
#define ADC_ANALOGWATCHDOG_ALLREGALLINSERTENABLE        ((uint32_t)0x00C00000)      /*!< Analog watchdog on all regular or inserted channel */
#define ADC_ANALOGWATCHDOG_NONE                         ((uint32_t)0x00000000)      /*!< Analog watchdog is disable */

/**
  * @}
  */

/** @defgroup ADC_Interrupts_Definition
  * @{
  */
#define ADC_INT_EOC                                     ((uint16_t)0x0220)          /*!< Interrupt for end of conversion on regular channnel */
#define ADC_INT_AWE                                     ((uint16_t)0x0140)          /*!< Interrupt for Analog watchdog */
#define ADC_INT_EOIC                                    ((uint16_t)0x0480)          /*!< Interrupt for end of conversion on inserted channnel */

/**
  * @}
  */

/** @defgroup ADC_Flags_Definition 
  * @{
  */
#define ADC_FLAG_AWE                                    ((uint8_t)0x01)             /*!< Analog watchdog event flag */
#define ADC_FLAG_EOC                                    ((uint8_t)0x02)             /*!< End of group conversion flag */
#define ADC_FLAG_EOIC                                   ((uint8_t)0x04)             /*!< End of inserted group conversion flag */
#define ADC_FLAG_STIC                                   ((uint8_t)0x08)             /*!< Start flag of inserted channel group */
#define ADC_FLAG_STRC                                   ((uint8_t)0x10)             /*!< Start flag of regular channel group */

/**
  * @}
  */

#ifdef GD32F170_190
/** @defgroup ADC_Resolution_Definition 
  * @{
  */
#define ADC_RESOLUTION_12B                              ((uint32_t)0x00000000)      /*!< 12-bit ADC resolution */
#define ADC_RESOLUTION_10B                              ((uint32_t)0x01000000)      /*!< 10-bit ADC resolution */
#define ADC_RESOLUTION_8B                               ((uint32_t)0x02000000)      /*!< 8-bit ADC resolution */
#define ADC_RESOLUTION_6B                               ((uint32_t)0x03000000)      /*!< 6-bit ADC resolution */

/**
  * @}
  */
  
/** @defgroup ADC_Oversampling_Shift_Definition
  * @{
  */
#define ADC_OVERSAMPLING_SHIFT_NONE                     ((uint32_t)0x00000000)      /*!< No oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_1B                       ((uint32_t)0x00000020)      /*!< 1-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_2B                       ((uint32_t)0x00000040)      /*!< 2-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_3B                       ((uint32_t)0x00000060)      /*!< 3-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_4B                       ((uint32_t)0x00000080)      /*!< 4-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_5B                       ((uint32_t)0x000000A0)      /*!< 5-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_6B                       ((uint32_t)0x000000C0)      /*!< 6-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_7B                       ((uint32_t)0x000000E0)      /*!< 7-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_8B                       ((uint32_t)0x00000100)      /*!< 8-bit oversampling shift */

/**
  * @}
  */
  
/** @defgroup ADC_Oversampling_Ratio_Definition
  * @{
  */
#define ADC_OVERSAMPLING_RATIO_2X                       ((uint32_t)0x00000000)      /*!< Oversampling ratio X2 */
#define ADC_OVERSAMPLING_RATIO_4X                       ((uint32_t)0x00000004)      /*!< Oversampling ratio X4 */
#define ADC_OVERSAMPLING_RATIO_8X                       ((uint32_t)0x00000008)      /*!< Oversampling ratio X8 */
#define ADC_OVERSAMPLING_RATIO_16X                      ((uint32_t)0x0000000C)      /*!< Oversampling ratio X16 */
#define ADC_OVERSAMPLING_RATIO_32X                      ((uint32_t)0x00000010)      /*!< Oversampling ratio X32 */
#define ADC_OVERSAMPLING_RATIO_64X                      ((uint32_t)0x00000014)      /*!< Oversampling ratio X64 */
#define ADC_OVERSAMPLING_RATIO_128X                     ((uint32_t)0x00000018)      /*!< Oversampling ratio X128 */
#define ADC_OVERSAMPLING_RATIO_256X                     ((uint32_t)0x0000001C)      /*!< Oversampling ratio X256 */

/**
  * @}
  */
#endif /* GD32F170_190 */

/**
  * @}
  */

/** @defgroup ADC_Exported_Functions
  * @{
  */
void ADC_DeInit(ADC_InitPara* ADC_InitParaStruct);
void ADC_Init(ADC_InitPara* ADC_InitParaStruct);
void ADC_Enable(TypeState NewValue);
void ADC_DMA_Enable(TypeState NewValue);
void ADC_INTConfig(uint16_t ADC_INT, TypeState NewValue);
void ADC_Calibration(void);
void ADC_SoftwareStartConv_Enable(TypeState NewValue);
TypeState ADC_GetSoftwareStartConvBitState(void);
void ADC_DiscModeChannelCount_Config(uint8_t Number);
void ADC_DiscMode_Enable(TypeState NewValue);
void ADC_RegularChannel_Config(uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_ExternalTrigConv_Enable(TypeState NewValue);
uint16_t ADC_GetConversionValue(void);
void ADC_AutoInsertedConv_Enable(TypeState NewValue);
void ADC_InsertedDiscMode_Enable(TypeState NewValue);
void ADC_ExternalTrigInsertedConv_Config(uint32_t ADC_ExternalTrigInsertConv);
void ADC_ExternalTrigInsertedConv_Enable(TypeState NewValue);
void ADC_SoftwareStartInsertedConv_Enable(TypeState NewValue);
TypeState ADC_GetSoftwareStartInsertedConvCmdBitState(void);
void ADC_InsertedChannel_Config(uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_InsertedSequencerLength_Config(uint8_t Length);
void ADC_SetInsertedOffset(uint8_t ADC_InsertedChannel, uint16_t Offset);
uint16_t ADC_GetInsertedConversionValue(uint8_t ADC_InsertedChannel);
void ADC_AnalogWatchdog_Enable(uint32_t ADC_AnalogWatchdog);
void ADC_AnalogWatchdogThresholds_Config(uint16_t HighThreshold, uint16_t LowThreshold);
void ADC_AnalogWatchdogSingleChannel_Config(uint8_t ADC_Channel);
void ADC_TempSensorVrefint_Enable(TypeState NewValue);
void ADC_VBat_Enable(TypeState NewValue);
TypeState ADC_GetBitState(uint8_t ADC_FLAG);
void ADC_ClearBitState(uint8_t ADC_FLAG);
TypeState ADC_GetIntState(uint16_t ADC_INT);
void ADC_ClearIntBitState(uint16_t ADC_INT);

#ifdef GD32F170_190
void ADC_Resolution_Config(uint32_t ADC_Resolution);
void ADC_OversamplingShift_Config(uint32_t ADC_Oversampling_Shift);
void ADC_OversamplingRatio_Config(uint32_t ADC_Oversampling_Ratio);
void ADC_TriggeredOversampling_Enable(TypeState NewValue);
void ADC_Oversampler_Enable(TypeState NewValue);
#endif /* GD32F170_190 */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /*__GD32F1X0_ADC_H */


/******************* (C) COPYRIGHT 2016 GIGADEVICE *****END OF FILE**************/
