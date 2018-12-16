/**
  ******************************************************************************
  * @file    gd32f1x0_lcd.h
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   LCD header file of the firmware library.
  ******************************************************************************
  */
  
#ifdef GD32F170_190
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F3X0_LCD_H
#define __GD32F3X0_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0.h"
/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @addtogroup LCD
  * @{
  */

/** @defgroup LCD_Exported_Types
  * @{
  */

/** 
  * @brief  LCD Initial Parameters
  */
typedef struct
{
  uint32_t LCD_Prescaler;                               /*!< The LCD Prescaler value. 
                                                            detailed in @ref LCD_Prescaler */
  uint32_t LCD_Divider;                                 /*!< The LCD Divider value.
                                                            detailed in @ref LCD_Divider */
  uint32_t LCD_Duty;                                    /*!< The LCD Duty value.
                                                            detailed in @ref LCD_Duty */
  uint32_t LCD_VBias;                                   /*!< The LCD bias voltage.
                                                            detailed in @ref LCD_Voltage_Bias */ 
  uint32_t LCD_VSRC;                                    /*!< The LCD Voltage source.
                                                            detailed in @ref LCD_Voltage_Source */
}LCD_InitPara;

/**
  * @}
  */

/** @defgroup LCD_Exported_Constants
  * @{
  */

/** @defgroup LCD_Prescaler 
  * @{
  */
#define LCD_PRESCALER_1                                 ((uint32_t)0x00000000)      /*!< PRE = 0 */
#define LCD_PRESCALER_2                                 ((uint32_t)0x00400000)      /*!< PRE = 1 */
#define LCD_PRESCALER_4                                 ((uint32_t)0x00800000)      /*!< PRE = 2 */
#define LCD_PRESCALER_8                                 ((uint32_t)0x00C00000)      /*!< PRE = 3 */
#define LCD_PRESCALER_16                                ((uint32_t)0x01000000)      /*!< PRE = 4 */
#define LCD_PRESCALER_32                                ((uint32_t)0x01400000)      /*!< PRE = 5 */
#define LCD_PRESCALER_64                                ((uint32_t)0x01800000)      /*!< PRE = 6 */
#define LCD_PRESCALER_128                               ((uint32_t)0x01C00000)      /*!< PRE = 7 */
#define LCD_PRESCALER_256                               ((uint32_t)0x02000000)      /*!< PRE = 8 */
#define LCD_PRESCALER_512                               ((uint32_t)0x02400000)      /*!< PRE = 9 */
#define LCD_PRESCALER_1024                              ((uint32_t)0x02800000)      /*!< PRE = 10 */
#define LCD_PRESCALER_2048                              ((uint32_t)0x02C00000)      /*!< PRE = 11 */
#define LCD_PRESCALER_4096                              ((uint32_t)0x03000000)      /*!< PRE = 12 */
#define LCD_PRESCALER_8192                              ((uint32_t)0x03400000)      /*!< PRE = 13 */
#define LCD_PRESCALER_16384                             ((uint32_t)0x03800000)      /*!< PRE = 14 */
#define LCD_PRESCALER_32768                             ((uint32_t)0x03C00000)      /*!< PRE = 15 */

/**
  * @}
  */
  
/** @defgroup LCD_Divider 
  * @{
  */
#define LCD_DIVIDER_16                                  ((uint32_t)0x00000000)      /*!< DIV = 16 */
#define LCD_DIVIDER_17                                  ((uint32_t)0x00040000)      /*!< DIV = 17 */
#define LCD_DIVIDER_18                                  ((uint32_t)0x00080000)      /*!< DIV = 18 */
#define LCD_DIVIDER_19                                  ((uint32_t)0x000C0000)      /*!< DIV = 19 */
#define LCD_DIVIDER_20                                  ((uint32_t)0x00100000)      /*!< DIV = 20 */
#define LCD_DIVIDER_21                                  ((uint32_t)0x00140000)      /*!< DIV = 21 */
#define LCD_DIVIDER_22                                  ((uint32_t)0x00180000)      /*!< DIV = 22 */
#define LCD_DIVIDER_23                                  ((uint32_t)0x001C0000)      /*!< DIV = 23 */
#define LCD_DIVIDER_24                                  ((uint32_t)0x00200000)      /*!< DIV = 24 */
#define LCD_DIVIDER_25                                  ((uint32_t)0x00240000)      /*!< DIV = 25 */
#define LCD_DIVIDER_26                                  ((uint32_t)0x00280000)      /*!< DIV = 26 */
#define LCD_DIVIDER_27                                  ((uint32_t)0x002C0000)      /*!< DIV = 27 */
#define LCD_DIVIDER_28                                  ((uint32_t)0x00300000)      /*!< DIV = 28 */
#define LCD_DIVIDER_29                                  ((uint32_t)0x00340000)      /*!< DIV = 29 */
#define LCD_DIVIDER_30                                  ((uint32_t)0x00380000)      /*!< DIV = 30 */
#define LCD_DIVIDER_31                                  ((uint32_t)0x003C0000)      /*!< DIV = 31 */

/**
  * @}
  */

/** @defgroup LCD_Duty
  * @{
  */
#define LCD_DUTY_STATIC                                 ((uint32_t)0x00000000)      /*!< Static dutycycle */
#define LCD_DUTY_1_2                                    ((uint32_t)0x00000004)      /*!< 1/2 dutycycle */
#define LCD_DUTY_1_3                                    ((uint32_t)0x00000008)      /*!< 1/3 dutycycle */
#define LCD_DUTY_1_4                                    ((uint32_t)0x0000000C)      /*!< 1/4 dutycycle */
#define LCD_DUTY_1_6                                    ((uint32_t)0x00000014)      /*!< 1/6 dutycycle */
#define LCD_DUTY_1_8                                    ((uint32_t)0x00000010)      /*!< 1/8 dutycycle */

/**
  * @}
  */

/** @defgroup LCD_Voltage_Bias 
  * @{
  */
#define LCD_BIAS_1_4                                    ((uint32_t)0x00000000)      /*!< 1/4 Voltage Bias */
#define LCD_BIAS_1_2                                    ((uint32_t)0x00000020)      /*!< 1/2 Voltage Bias */
#define LCD_BIAS_1_3                                    ((uint32_t)0x00000040)      /*!< 1/3 Voltage Bias */

/**
  * @}
  */ 
    
/** @defgroup LCD_Voltage_Source 
  * @{
  */
#define LCD_VOLTAGESOURCE_INTERNAL                      ((uint32_t)0x00000000)      /*!< Internal voltage source */
#define LCD_VOLTAGESOURCE_EXTERNAL                      ((uint32_t)0x00000002)      /*!< External voltage source */

/**
  * @}
  */

/** @defgroup LCD_Interrupt_Sources
  * @{
  */
#define LCD_INT_SOF                                     LCD_CFGR_SOFIE              /*!< Start of frame interrupt */
#define LCD_INT_UPD                                     LCD_CFGR_UPDIE              /*!< LCD update done interrupt */

/**
  * @}
  */

/** @defgroup LCD_PulseOn_Duration 
  * @{
  */
#define LCD_PULSEON_DURATION_0                          ((uint32_t)0x00000000)      /*!< Pulse ON duration = 0 */
#define LCD_PULSEON_DURATION_1                          ((uint32_t)0x00000010)      /*!< Pulse ON duration = 1*1/fPRE */
#define LCD_PULSEON_DURATION_2                          ((uint32_t)0x00000020)      /*!< Pulse ON duration = 2*1/fPRE */
#define LCD_PULSEON_DURATION_3                          ((uint32_t)0x00000030)      /*!< Pulse ON duration = 3*1/fPRE */
#define LCD_PULSEON_DURATION_4                          ((uint32_t)0x00000040)      /*!< Pulse ON duration = 4*1/fPRE */
#define LCD_PULSEON_DURATION_5                          ((uint32_t)0x00000050)      /*!< Pulse ON duration = 5*1/fPRE */
#define LCD_PULSEON_DURATION_6                          ((uint32_t)0x00000060)      /*!< Pulse ON duration = 6*1/fPRE */
#define LCD_PULSEON_DURATION_7                          ((uint32_t)0x00000070)      /*!< Pulse ON duration = 7*1/fPRE */

/**
  * @}
  */

/** @defgroup LCD_DeadTime 
  * @{
  */
#define LCD_DEADTIME_PERIOD_0                           ((uint32_t)0x00000000)      /*!< No dead Time */
#define LCD_DEADTIME_PERIOD_1                           ((uint32_t)0x00000080)      /*!< 1 Phase inserted between couple of Frame */
#define LCD_DEADTIME_PERIOD_2                           ((uint32_t)0x00000100)      /*!< 2 Phase inserted between couple of Frame */
#define LCD_DEADTIME_PERIOD_3                           ((uint32_t)0x00000180)      /*!< 3 Phase inserted between couple of Frame */
#define LCD_DEADTIME_PERIOD_4                           ((uint32_t)0x00000200)      /*!< 4 Phase inserted between couple of Frame */
#define LCD_DEADTIME_PERIOD_5                           ((uint32_t)0x00000280)      /*!< 5 Phase inserted between couple of Frame */
#define LCD_DEADTIME_PERIOD_6                           ((uint32_t)0x00000300)      /*!< 6 Phase inserted between couple of Frame */
#define LCD_DEADTIME_PERIOD_7                           ((uint32_t)0x00000380)      /*!< 7 Phase inserted between couple of Frame */

/**
  * @}
  */

/** @defgroup LCD_BlinkMode 
  * @{
  */
#define LCD_BLINKMODE_OFF                               ((uint32_t)0x00000000)      /*!< Blink disabled */
#define LCD_BLINKMODE_SEG0_COM0                         ((uint32_t)0x00010000)      /*!< Blink enabled on SEG[0], COM[0] */
#define LCD_BLINKMODE_SEG0_ALLCOM                       ((uint32_t)0x00020000)      /*!< Blink enabled on SEG[0], all COM */
#define LCD_BLINKMODE_ALLSEG_ALLCOM                     ((uint32_t)0x00030000)      /*!< Blink enabled on all SEG and all COM */

/**
  * @}
  */

/** @defgroup LCD_BlinkFrequency_Divider 
  * @{
  */
#define LCD_BLINK_FREQUENCY_DIV8                        ((uint32_t)0x00000000)      /*!< The Blink frequency = fLCD/8 */
#define LCD_BLINK_FREQUENCY_DIV16                       ((uint32_t)0x00002000)      /*!< The Blink frequency = fLCD/16 */
#define LCD_BLINK_FREQUENCY_DIV32                       ((uint32_t)0x00004000)      /*!< The Blink frequency = fLCD/32 */
#define LCD_BLINK_FREQUENCY_DIV64                       ((uint32_t)0x00006000)      /*!< The Blink frequency = fLCD/64 */
#define LCD_BLINK_FREQUENCY_DIV128                      ((uint32_t)0x00008000)      /*!< The Blink frequency = fLCD/128 */
#define LCD_BLINK_FREQUENCY_DIV256                      ((uint32_t)0x0000A000)      /*!< The Blink frequency = fLCD/256 */
#define LCD_BLINK_FREQUENCY_DIV512                      ((uint32_t)0x0000C000)      /*!< The Blink frequency = fLCD/512 */
#define LCD_BLINK_FREQUENCY_DIV1024                     ((uint32_t)0x0000E000)      /*!< The Blink frequency = fLCD/1024 */

/**
  * @}
  */

/** @defgroup LCD_Contrast_Level
  * @{
  */
#define LCD_CONTRAST_LEVEL_0                            ((uint32_t)0x00000000)      /*!< Maximum LCD Voltage = 2.60V    */
#define LCD_CONTRAST_LEVEL_1                            ((uint32_t)0x00000400)      /*!< Maximum LCD Voltage = 2.73V    */
#define LCD_CONTRAST_LEVEL_2                            ((uint32_t)0x00000800)      /*!< Maximum LCD Voltage = 2.86V    */
#define LCD_CONTRAST_LEVEL_3                            ((uint32_t)0x00000C00)      /*!< Maximum LCD Voltage = 2.99V    */
#define LCD_CONTRAST_LEVEL_4                            ((uint32_t)0x00001000)      /*!< Maximum LCD Voltage = 3.12V    */
#define LCD_CONTRAST_LEVEL_5                            ((uint32_t)0x00001400)      /*!< Maximum LCD Voltage = 3.25V    */
#define LCD_CONTRAST_LEVEL_6                            ((uint32_t)0x00001800)      /*!< Maximum LCD Voltage = 3.38V    */
#define LCD_CONTRAST_LEVEL_7                            ((uint32_t)0x00001C00)      /*!< Maximum LCD Voltage = 3.51V    */

/**
  * @}
  */
      
/** @defgroup LCD_Flag 
  * @{
  */
#define LCD_FLAG_ONF                                    LCD_SFR_ONF                 /*!< LCD controller on flag */
#define LCD_FLAG_SOF                                    LCD_SFR_SOF                 /*!< Start of frame flag */
#define LCD_FLAG_UPRF                                   LCD_SFR_UPRF                /*!< LCD data update request flag */
#define LCD_FLAG_UPDF                                   LCD_SFR_UPDF                /*!< Update LCD data Done flag */
#define LCD_FLAG_VRDYF                                  LCD_SFR_VRDYF               /*!< LCD voltage ready flag */
#define LCD_FLAG_SYNF                                   LCD_SFR_SYNF                /*!< LCD CFGR Register Synchronization Flag */

/**
  * @}
  */

/** @defgroup LCD_DATA_REG
  * @{
  */
#define LCD_DATA_REG0                                   ((uint32_t)0x00000000)      /*!< LCD DATA Register 0  */
#define LCD_DATA_REG1                                   ((uint32_t)0x00000002)      /*!< LCD DATA Register 1  */
#define LCD_DATA_REG2                                   ((uint32_t)0x00000004)      /*!< LCD DATA Register 2  */
#define LCD_DATA_REG3                                   ((uint32_t)0x00000006)      /*!< LCD DATA Register 3  */
#define LCD_DATA_REG4                                   ((uint32_t)0x00000008)      /*!< LCD DATA Register 4  */
#define LCD_DATA_REG5                                   ((uint32_t)0x0000000A)      /*!< LCD DATA Register 5  */
#define LCD_DATA_REG6                                   ((uint32_t)0x0000000B)      /*!< LCD DATA Register 6  */
#define LCD_DATA_REG7                                   ((uint32_t)0x0000000C)      /*!< LCD DATA Register 7  */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup LCD_Exported_Functions
  * @{
  */
/* Initialization and Configuration functions */
void LCD_DeInit(void);
void LCD_Init(LCD_InitPara* LCD_Init);
void LCD_ParaInit(LCD_InitPara* LCD_Init);
void LCD_Enable(TypeState NewValue);
void LCD_HighDrive_Enable(TypeState NewValue);
void LCD_SegmentRemap_Enable(TypeState NewValue);
void LCD_PulseOnDurationConfig(uint32_t LCD_PulseOnDuration);
void LCD_DeadTimeConfig(uint32_t LCD_DeadTime);
void LCD_BlinkConfig(uint32_t LCD_BlinkMode, uint32_t LCD_BlinkFrequency_Divider);
void LCD_ContrastConfig(uint32_t LCD_Contrast_Level);

/* LCD data register write functions */
void LCD_WriteDataReg(uint32_t LCD_DataReg, uint32_t LCD_Data);
void LCD_DataUpdateRequest(void);

/* Interrupts and flags management functions */
void LCD_INTConfig(uint32_t LCD_INT, TypeState NewValue);
TypeState LCD_GetBitState(uint32_t LCD_FLAG);
void LCD_ClearBitState(uint32_t LCD_FLAG);
TypeState LCD_GetIntBitState(uint32_t LCD_INT);
void LCD_ClearIntBitState(uint32_t LCD_INT);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* GD32F170_190 */

#ifdef __cplusplus
}
#endif

#endif /*__GD32F1X0_LCD_H */


/******************* (C) COPYRIGHT 2016 GIGADEVICE *****END OF FILE**************/
