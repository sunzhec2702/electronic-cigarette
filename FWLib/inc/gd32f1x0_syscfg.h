/**
  ******************************************************************************
  * @file    gd32f1x0_syscfg.h
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   SYSCFG header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F1X0_SYSCFG_H
#define __GD32F1X0_SYSCFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0.h"

/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @addtogroup SYSCFG
  * @{
  */

/** @defgroup SYSCFG_Exported_Constants
  * @{
  */

/** @defgroup SYSCFG_EXTI_SOURCE_Port_Def
  * @{
  */
#define EXTI_SOURCE_GPIOA                               ((uint8_t)0x00) /*!< EXTI GPIOA configuration */
#define EXTI_SOURCE_GPIOB                               ((uint8_t)0x01) /*!< EXTI GPIOB configuration */
#define EXTI_SOURCE_GPIOC                               ((uint8_t)0x02) /*!< EXTI GPIOC configuration */
#define EXTI_SOURCE_GPIOD                               ((uint8_t)0x03) /*!< EXTI GPIOD configuration */
#define EXTI_SOURCE_GPIOF                               ((uint8_t)0x05) /*!< EXTI GPIOF configuration */

/**
  * @}
  */

/** @defgroup SYSCFG_EXTI_SOURCE_Pin_Def
  * @{
  */
#define EXTI_SOURCE_PIN0                                ((uint8_t)0x00) /*!< EXTI GPIO Pin0 configuration */
#define EXTI_SOURCE_PIN1                                ((uint8_t)0x01) /*!< EXTI GPIO Pin1 configuration */
#define EXTI_SOURCE_PIN2                                ((uint8_t)0x02) /*!< EXTI GPIO Pin2 configuration */
#define EXTI_SOURCE_PIN3                                ((uint8_t)0x03) /*!< EXTI GPIO Pin3 configuration */
#define EXTI_SOURCE_PIN4                                ((uint8_t)0x04) /*!< EXTI GPIO Pin4 configuration */
#define EXTI_SOURCE_PIN5                                ((uint8_t)0x05) /*!< EXTI GPIO Pin5 configuration */
#define EXTI_SOURCE_PIN6                                ((uint8_t)0x06) /*!< EXTI GPIO Pin6 configuration */
#define EXTI_SOURCE_PIN7                                ((uint8_t)0x07) /*!< EXTI GPIO Pin7 configuration */
#define EXTI_SOURCE_PIN8                                ((uint8_t)0x08) /*!< EXTI GPIO Pin8 configuration */
#define EXTI_SOURCE_PIN9                                ((uint8_t)0x09) /*!< EXTI GPIO Pin9 configuration */
#define EXTI_SOURCE_PIN10                               ((uint8_t)0x0A) /*!< EXTI GPIO Pin10 configuration */
#define EXTI_SOURCE_PIN11                               ((uint8_t)0x0B) /*!< EXTI GPIO Pin11 configuration */
#define EXTI_SOURCE_PIN12                               ((uint8_t)0x0C) /*!< EXTI GPIO Pin12 configuration */
#define EXTI_SOURCE_PIN13                               ((uint8_t)0x0D) /*!< EXTI GPIO Pin13 configuration */
#define EXTI_SOURCE_PIN14                               ((uint8_t)0x0E) /*!< EXTI GPIO Pin14 configuration */
#define EXTI_SOURCE_PIN15                               ((uint8_t)0x0F) /*!< EXTI GPIO Pin15 configuration */

/**
  * @}
  */

/** @defgroup SYSCFG_DMA_Remap_Def
  * @{
  */
#define SYSCFG_DMA_REMAP_ADC                            SYSCFG_R1_ADC_DMA_RMP       /*!< ADC DMA remap */
#define SYSCFG_DMA_REMAP_USART1TX                       SYSCFG_R1_USART1_TX_DMA_RMP /*!< USART1 TX DMA remap */
#define SYSCFG_DMA_REMAP_USART1RX                       SYSCFG_R1_USART1_RX_DMA_RMP /*!< USART1 RX DMA remap */
#define SYSCFG_DMA_REMAP_TIMER16                        SYSCFG_R1_TIMER16_DMA_RMP   /*!< Timer 16 DMA remap */
#define SYSCFG_DMA_REMAP_TIMER17                        SYSCFG_R1_TIMER17_DMA_RMP   /*!< Timer 17 DMA remap */

/**
  * @}
  */

/** @defgroup SYSCFG_High_Current_Def
  * @{
  */
#define SYSCFG_HIGH_CURRENT_ENABLE                      (SYSCFG_R1_PB9_HCCE)  /*!< Enable PB9 pin high current capability */
#define SYSCFG_HIGH_CURRENT_DISABLE                     (~SYSCFG_R1_PB9_HCCE) /*!< Disable PB9 pin high current capability */

/**
  * @}
  */

#ifdef GD32F170_190

/** @defgroup VLCD_BIAS
  * @{
  */
#define VLCD_BIAS1_2_RAIL1                              ((uint8_t)0) /*!< VLCD bias is 1/2, using VLCDrail1 */
#define VLCD_BIAS1_2_RAIL2                              ((uint8_t)1) /*!< VLCD bias is 1/2, using VLCDrail2 */
#define VLCD_BIAS1_2_RAIL3                              ((uint8_t)2) /*!< VLCD bias is 1/2, using VLCDrail3 */
#define VLCD_BIAS1_3_RAIL1_2                            ((uint8_t)3) /*!< VLCD bias is 1/3, using VLCDrail1 and VLCDrail2 */
#define VLCD_BIAS1_3_RAIL1_3                            ((uint8_t)4) /*!< VLCD bias is 1/3, using VLCDrail1 and VLCDrail3*/
#define VLCD_BIAS1_4_RAILALL                            ((uint8_t)5) /*!< VLCD bias is 1/4, using all VLCDrails */

/**
  * @}
  */

/** @defgroup SYSCFG_VLCDRail
  * @{
  */
#define SYSCFG_VLCD_RAIL1                               SYSCFG_R2_LCD_DECA_1 /*!< VLCDRail1 */
#define SYSCFG_VLCD_RAIL2                               SYSCFG_R2_LCD_DECA_0 /*!< VLCDRail2 */
#define SYSCFG_VLCD_RAIL3                               SYSCFG_R2_LCD_DECA_2 /*!< VLCDRail3 */

/**
  * @}
  */

#endif /* GD32F170_190 */

/** @defgroup SYSCFG_Lock_Def
  * @{
  */
#define SYSCFG_LOCK_LOCKUP                              SYSCFG_R3_LOCKUP_LOCK /*!< Enables and locks the LOCKUP (Hardfault) output of CortexM0 with Break Input of TIMER1/15/16/17 */
#define SYSCFG_LOCK_SRAM_PARITY_ERROR                   SYSCFG_R3_SRAM_PARITY_ERROR_LOCK /*!< Enables and locks the SRAM_PARITY error signal with Break Input of TIMER1/15/16/17 */
#define SYSCFG_LOCK_LVD                                 SYSCFG_R3_LVD_LOCK /*!< Enables and locks the LVD connection with Timer1 Break Input and also the LVD_EN and LVDSEL[2:0] bits of the Power Control Interface */

/**
  * @}
  */

/** @defgroup SYSCFG_SRAM_Parity_Check_Error_Flag_Def
  * @{
  */
#define SYSCFG_SRAM_PCEF                                SYSCFG_R3_SRAM_PCEF /*!< SRAM Parity check error flag */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Functions
  * @{
  */
void SYSCFG_DeInit(void);
void SYSCFG_DMARemap_Config(uint32_t SYSCFG_dma_remap, TypeState NewValue);
void SYSCFG_HighCurrent_Enable(TypeState NewValue);
void SYSCFG_EXTILine_Config(uint8_t exti_port, uint8_t exti_pin);
void SYSCFG_Lock_Config(uint32_t SYSCFG_lock);
TypeState SYSCFG_GetBitState(uint32_t SYSCFG_flag);
void SYSCFG_ClearBitState(uint32_t SYSCFG_flag);

#ifdef GD32F170_190
void SYSCFG_VLCDRail_Config(uint8_t VLCD_Bias);
#endif

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__GD32F1X0_SYSCFG_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2016 GIGADEVICE *****END OF FILE****/
