/**
  ******************************************************************************
  * @file    gd32f1x0_ivref.h
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   IVREF header file of the firmware library.
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F1X0_IVREF_H
#define __GD32F1X0_IVREF_H

#ifdef GD32F170_190

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0.h"

/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @addtogroup IVREF
  * @{
  */

/** @defgroup IVREF_Exported_Constants
  * @{
  */

/** @defgroup VREF_Mode_Connect_define
  * @{
  */
#define VREF_CONNECT_EXTERNAL_CAP       ((uint32_t)0x00000000) /*!< connect external capacitor */
#define VREF_DISCONNECT_EXTERNAL_CAP    ((uint32_t)0x40000000) /*!< Disconnect external capacitor */

/**
  * @}
  */

/** @defgroup VREF_Voltage_precision_Trim
  * @{
  */
#define VREF_VOLTAGE_PRECISION_TRIM_0   ((uint32_t)0x00000000) /*!< -6.4% */
#define VREF_VOLTAGE_PRECISION_TRIM_1   ((uint32_t)0x01000000) /*!< -6.0% */
#define VREF_VOLTAGE_PRECISION_TRIM_2   ((uint32_t)0x02000000) /*!< -5.6% */
#define VREF_VOLTAGE_PRECISION_TRIM_3   ((uint32_t)0x03000000) /*!< -5.2% */
#define VREF_VOLTAGE_PRECISION_TRIM_4   ((uint32_t)0x04000000) /*!< -4.8% */
#define VREF_VOLTAGE_PRECISION_TRIM_5   ((uint32_t)0x05000000) /*!< -4.4% */
#define VREF_VOLTAGE_PRECISION_TRIM_6   ((uint32_t)0x06000000) /*!< -4.0% */
#define VREF_VOLTAGE_PRECISION_TRIM_7   ((uint32_t)0x07000000) /*!< -3.6% */
#define VREF_VOLTAGE_PRECISION_TRIM_8   ((uint32_t)0x08000000) /*!< -3.2% */
#define VREF_VOLTAGE_PRECISION_TRIM_9   ((uint32_t)0x09000000) /*!< -2.8% */
#define VREF_VOLTAGE_PRECISION_TRIM_10  ((uint32_t)0x0A000000) /*!< -2.4% */
#define VREF_VOLTAGE_PRECISION_TRIM_11  ((uint32_t)0x0B000000) /*!< -2.0% */
#define VREF_VOLTAGE_PRECISION_TRIM_12  ((uint32_t)0x0C000000) /*!< -1.6% */
#define VREF_VOLTAGE_PRECISION_TRIM_13  ((uint32_t)0x0D000000) /*!< -1.2% */
#define VREF_VOLTAGE_PRECISION_TRIM_14  ((uint32_t)0x0E000000) /*!< -0.8% */
#define VREF_VOLTAGE_PRECISION_TRIM_15  ((uint32_t)0x0F000000) /*!< -0.4% */
#define VREF_VOLTAGE_PRECISION_TRIM_16  ((uint32_t)0x10000000) /*!<  0% */
#define VREF_VOLTAGE_PRECISION_TRIM_17  ((uint32_t)0x11000000) /*!< +0.4% */
#define VREF_VOLTAGE_PRECISION_TRIM_18  ((uint32_t)0x12000000) /*!< +0.8% */
#define VREF_VOLTAGE_PRECISION_TRIM_19  ((uint32_t)0x13000000) /*!< +1.2% */
#define VREF_VOLTAGE_PRECISION_TRIM_20  ((uint32_t)0x14000000) /*!< +1.6% */
#define VREF_VOLTAGE_PRECISION_TRIM_21  ((uint32_t)0x15000000) /*!< +2.0% */
#define VREF_VOLTAGE_PRECISION_TRIM_22  ((uint32_t)0x16000000) /*!< +2.4% */
#define VREF_VOLTAGE_PRECISION_TRIM_23  ((uint32_t)0x17000000) /*!< +2.8% */
#define VREF_VOLTAGE_PRECISION_TRIM_24  ((uint32_t)0x18000000) /*!< +3.2% */
#define VREF_VOLTAGE_PRECISION_TRIM_25  ((uint32_t)0x19000000) /*!< +3.6% */
#define VREF_VOLTAGE_PRECISION_TRIM_26  ((uint32_t)0x1A000000) /*!< +4.0% */
#define VREF_VOLTAGE_PRECISION_TRIM_27  ((uint32_t)0x1B000000) /*!< +4.4% */
#define VREF_VOLTAGE_PRECISION_TRIM_28  ((uint32_t)0x1C000000) /*!< +4.8% */
#define VREF_VOLTAGE_PRECISION_TRIM_29  ((uint32_t)0x1D000000) /*!< +5.2% */
#define VREF_VOLTAGE_PRECISION_TRIM_30  ((uint32_t)0x1E000000) /*!< +5.6% */
#define VREF_VOLTAGE_PRECISION_TRIM_31  ((uint32_t)0x1F000000) /*!< +6.0% */


/**
  * @}
  */

/** @defgroup IREF_Mode_Selection
  * @{
  */
#define IREF_MODE_LOW_POWER             ((uint32_t)0x00000000) /*!< Low power */
#define IREF_MODE_HIGH_CURRENT          ((uint32_t)0x00004000) /*!< High current */

/**
  * @}
  */

/** @defgroup IREF_Sink_Current_Mode
  * @{
  */
#define IREF_SOURCE_CURRENT             ((uint32_t)0x00000000) /*!< Source current */
#define IREF_SINK_CURRENT               ((uint32_t)0x00000080) /*!< Sink current */

/**
  * @}
  */

/** @defgroup IREF_Current_Precision_Trim
  * @{
  */
#define IREF_CURRENT_PRECISION_TRIM_0   ((uint32_t)0x00000000) /*!< -15% */
#define IREF_CURRENT_PRECISION_TRIM_1   ((uint32_t)0x00000100) /*!< -14% */
#define IREF_CURRENT_PRECISION_TRIM_2   ((uint32_t)0x00000200) /*!< -13% */
#define IREF_CURRENT_PRECISION_TRIM_3   ((uint32_t)0x00000300) /*!< -12% */
#define IREF_CURRENT_PRECISION_TRIM_4   ((uint32_t)0x00000400) /*!< -11% */
#define IREF_CURRENT_PRECISION_TRIM_5   ((uint32_t)0x00000500) /*!< -10% */
#define IREF_CURRENT_PRECISION_TRIM_6   ((uint32_t)0x00000600) /*!< -9% */
#define IREF_CURRENT_PRECISION_TRIM_7   ((uint32_t)0x00000700) /*!< -8% */
#define IREF_CURRENT_PRECISION_TRIM_8   ((uint32_t)0x00000800) /*!< -7% */
#define IREF_CURRENT_PRECISION_TRIM_9   ((uint32_t)0x00000900) /*!< -6% */
#define IREF_CURRENT_PRECISION_TRIM_10  ((uint32_t)0x00000A00) /*!< -5% */
#define IREF_CURRENT_PRECISION_TRIM_11  ((uint32_t)0x00000B00) /*!< -4% */
#define IREF_CURRENT_PRECISION_TRIM_12  ((uint32_t)0x00000C00) /*!< -3% */
#define IREF_CURRENT_PRECISION_TRIM_13  ((uint32_t)0x00000D00) /*!< -2% */
#define IREF_CURRENT_PRECISION_TRIM_14  ((uint32_t)0x00000E00) /*!< -1% */
#define IREF_CURRENT_PRECISION_TRIM_15  ((uint32_t)0x00000F00) /*!<  0% */
#define IREF_CURRENT_PRECISION_TRIM_16  ((uint32_t)0x00001000) /*!< +1% */
#define IREF_CURRENT_PRECISION_TRIM_17  ((uint32_t)0x00001100) /*!< +2% */
#define IREF_CURRENT_PRECISION_TRIM_18  ((uint32_t)0x00001200) /*!< +3% */
#define IREF_CURRENT_PRECISION_TRIM_19  ((uint32_t)0x00001300) /*!< +4% */
#define IREF_CURRENT_PRECISION_TRIM_20  ((uint32_t)0x00001400) /*!< +5% */
#define IREF_CURRENT_PRECISION_TRIM_21  ((uint32_t)0x00001500) /*!< +6% */
#define IREF_CURRENT_PRECISION_TRIM_22  ((uint32_t)0x00001600) /*!< +7% */
#define IREF_CURRENT_PRECISION_TRIM_23  ((uint32_t)0x00001700) /*!< +8% */
#define IREF_CURRENT_PRECISION_TRIM_24  ((uint32_t)0x00001800) /*!< +9% */
#define IREF_CURRENT_PRECISION_TRIM_25  ((uint32_t)0x00001900) /*!< +10% */
#define IREF_CURRENT_PRECISION_TRIM_26  ((uint32_t)0x00001A00) /*!< +11% */
#define IREF_CURRENT_PRECISION_TRIM_27  ((uint32_t)0x00001B00) /*!< +12% */
#define IREF_CURRENT_PRECISION_TRIM_28  ((uint32_t)0x00001C00) /*!< +13% */
#define IREF_CURRENT_PRECISION_TRIM_29  ((uint32_t)0x00001D00) /*!< +14% */
#define IREF_CURRENT_PRECISION_TRIM_30  ((uint32_t)0x00001E00) /*!< +15% */
#define IREF_CURRENT_PRECISION_TRIM_31  ((uint32_t)0x00001F00) /*!< +16% */

/**
  * @}
  */

/** @defgroup IREF_Current_Step
  * @{
  */
#define IREF_CURRENT_STEP_DATA_0        ((uint32_t)0x00000000) /*!< Default value */
#define IREF_CURRENT_STEP_DATA_1        ((uint32_t)0x00000001) /*!< Step*1 */
#define IREF_CURRENT_STEP_DATA_2        ((uint32_t)0x00000002) /*!< Step*2 */
#define IREF_CURRENT_STEP_DATA_3        ((uint32_t)0x00000003) /*!< Step*3 */
#define IREF_CURRENT_STEP_DATA_4        ((uint32_t)0x00000004) /*!< Step*4 */
#define IREF_CURRENT_STEP_DATA_5        ((uint32_t)0x00000005) /*!< Step*5 */
#define IREF_CURRENT_STEP_DATA_6        ((uint32_t)0x00000006) /*!< Step*6 */
#define IREF_CURRENT_STEP_DATA_7        ((uint32_t)0x00000007) /*!< Step*7 */
#define IREF_CURRENT_STEP_DATA_8        ((uint32_t)0x00000008) /*!< Step*8 */
#define IREF_CURRENT_STEP_DATA_9        ((uint32_t)0x00000009) /*!< Step*9 */
#define IREF_CURRENT_STEP_DATA_10       ((uint32_t)0x0000000A) /*!< Step*10 */
#define IREF_CURRENT_STEP_DATA_11       ((uint32_t)0x0000000B) /*!< Step*11 */
#define IREF_CURRENT_STEP_DATA_12       ((uint32_t)0x0000000C) /*!< Step*12 */
#define IREF_CURRENT_STEP_DATA_13       ((uint32_t)0x0000000D) /*!< Step*13 */
#define IREF_CURRENT_STEP_DATA_14       ((uint32_t)0x0000000E) /*!< Step*14 */
#define IREF_CURRENT_STEP_DATA_15       ((uint32_t)0x0000000F) /*!< Step*15 */
#define IREF_CURRENT_STEP_DATA_16       ((uint32_t)0x00000010) /*!< Step*16 */
#define IREF_CURRENT_STEP_DATA_17       ((uint32_t)0x00000011) /*!< Step*17 */
#define IREF_CURRENT_STEP_DATA_18       ((uint32_t)0x00000012) /*!< Step*18 */
#define IREF_CURRENT_STEP_DATA_19       ((uint32_t)0x00000013) /*!< Step*19 */
#define IREF_CURRENT_STEP_DATA_20       ((uint32_t)0x00000014) /*!< Step*20 */
#define IREF_CURRENT_STEP_DATA_21       ((uint32_t)0x00000015) /*!< Step*21 */
#define IREF_CURRENT_STEP_DATA_22       ((uint32_t)0x00000016) /*!< Step*22 */
#define IREF_CURRENT_STEP_DATA_23       ((uint32_t)0x00000017) /*!< Step*23 */
#define IREF_CURRENT_STEP_DATA_24       ((uint32_t)0x00000018) /*!< Step*24 */
#define IREF_CURRENT_STEP_DATA_25       ((uint32_t)0x00000019) /*!< Step*25 */
#define IREF_CURRENT_STEP_DATA_26       ((uint32_t)0x0000001A) /*!< Step*26 */
#define IREF_CURRENT_STEP_DATA_27       ((uint32_t)0x0000001B) /*!< Step*27 */
#define IREF_CURRENT_STEP_DATA_28       ((uint32_t)0x0000001C) /*!< Step*28 */
#define IREF_CURRENT_STEP_DATA_29       ((uint32_t)0x0000001D) /*!< Step*29 */
#define IREF_CURRENT_STEP_DATA_30       ((uint32_t)0x0000001E) /*!< Step*30 */
#define IREF_CURRENT_STEP_DATA_31       ((uint32_t)0x0000001F) /*!< Step*31 */
#define IREF_CURRENT_STEP_DATA_32       ((uint32_t)0x00000020) /*!< Step*32 */
#define IREF_CURRENT_STEP_DATA_33       ((uint32_t)0x00000021) /*!< Step*33 */
#define IREF_CURRENT_STEP_DATA_34       ((uint32_t)0x00000022) /*!< Step*34 */
#define IREF_CURRENT_STEP_DATA_35       ((uint32_t)0x00000023) /*!< Step*35 */
#define IREF_CURRENT_STEP_DATA_36       ((uint32_t)0x00000024) /*!< Step*36 */
#define IREF_CURRENT_STEP_DATA_37       ((uint32_t)0x00000025) /*!< Step*37 */
#define IREF_CURRENT_STEP_DATA_38       ((uint32_t)0x00000026) /*!< Step*38 */
#define IREF_CURRENT_STEP_DATA_39       ((uint32_t)0x00000027) /*!< Step*39 */
#define IREF_CURRENT_STEP_DATA_40       ((uint32_t)0x00000028) /*!< Step*40 */
#define IREF_CURRENT_STEP_DATA_41       ((uint32_t)0x00000029) /*!< Step*41 */
#define IREF_CURRENT_STEP_DATA_42       ((uint32_t)0x0000002A) /*!< Step*42 */
#define IREF_CURRENT_STEP_DATA_43       ((uint32_t)0x0000002B) /*!< Step*43 */
#define IREF_CURRENT_STEP_DATA_44       ((uint32_t)0x0000002C) /*!< Step*44 */
#define IREF_CURRENT_STEP_DATA_45       ((uint32_t)0x0000002D) /*!< Step*45 */
#define IREF_CURRENT_STEP_DATA_46       ((uint32_t)0x0000002E) /*!< Step*46 */
#define IREF_CURRENT_STEP_DATA_47       ((uint32_t)0x0000002F) /*!< Step*47 */
#define IREF_CURRENT_STEP_DATA_48       ((uint32_t)0x00000030) /*!< Step*48 */
#define IREF_CURRENT_STEP_DATA_49       ((uint32_t)0x00000031) /*!< Step*49 */
#define IREF_CURRENT_STEP_DATA_50       ((uint32_t)0x00000032) /*!< Step*50 */
#define IREF_CURRENT_STEP_DATA_51       ((uint32_t)0x00000033) /*!< Step*51 */
#define IREF_CURRENT_STEP_DATA_52       ((uint32_t)0x00000034) /*!< Step*52 */
#define IREF_CURRENT_STEP_DATA_53       ((uint32_t)0x00000035) /*!< Step*53 */
#define IREF_CURRENT_STEP_DATA_54       ((uint32_t)0x00000036) /*!< Step*54 */
#define IREF_CURRENT_STEP_DATA_55       ((uint32_t)0x00000037) /*!< Step*55 */
#define IREF_CURRENT_STEP_DATA_56       ((uint32_t)0x00000038) /*!< Step*56 */
#define IREF_CURRENT_STEP_DATA_57       ((uint32_t)0x00000039) /*!< Step*57 */
#define IREF_CURRENT_STEP_DATA_58       ((uint32_t)0x0000003A) /*!< Step*58 */
#define IREF_CURRENT_STEP_DATA_59       ((uint32_t)0x0000003B) /*!< Step*59 */
#define IREF_CURRENT_STEP_DATA_60       ((uint32_t)0x0000003C) /*!< Step*60 */
#define IREF_CURRENT_STEP_DATA_61       ((uint32_t)0x0000003D) /*!< Step*61 */
#define IREF_CURRENT_STEP_DATA_62       ((uint32_t)0x0000003E) /*!< Step*62 */
#define IREF_CURRENT_STEP_DATA_63       ((uint32_t)0x0000003F) /*!< Step*63 */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup IVREF_Exported_Functions
  * @{
  */
void IVREF_DeInit(void);
void IVREF_VREF_Enable(TypeState NewValue);
void IVREF_SetVREFMode(uint32_t VREFMode);
void IVREF_VREFPrecisionTrimConfig(uint32_t VREFPrecisionTrim);
void IVREF_IREF_Enable(TypeState NewValue);
void IVREF_SetIREFMode(uint32_t IREFMode);
void IVREF_IREFPrecisionTrimConfig(uint32_t IREFPrecisionTrim);
void IVREF_SetIREFSink(uint32_t IREFSinkMode);
void IVREF_IREFStepDataConfig(uint32_t IREFStepData);

#ifdef __cplusplus
}
#endif

#endif /* __GD32F1X0_IVREF_H */

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
