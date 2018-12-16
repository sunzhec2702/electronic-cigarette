/**
  ******************************************************************************
  * @file    gd32f1x0_rcc.h
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   RCC header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F1X0_RCC_H
#define __GD32F1X0_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0.h"

/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/** @defgroup RCC_Exported_Types
  * @{
  */

/** 
  * @brief  RCC Initial Parameters
  */
typedef struct
{
  uint32_t CK_SYS_Frequency;            /*!< The frequency of the CK_SYS.     */
  uint32_t AHB_Frequency;               /*!< The frequency of the AHB.        */
  uint32_t APB1_Frequency;              /*!< The frequency of the APB1.       */
  uint32_t APB2_Frequency;              /*!< The frequency of the APB2.       */
  uint32_t ADCCLK_Frequency;            /*!< The frequency of the ADCCLK.     */
  uint32_t CECCLK_Frequency;            /*!< The frequency of the CECCLK.     */
  uint32_t USART1CLK_Frequency;         /*!< The frequency of the USART1CLK.  */
}RCC_ClocksPara;

/**
  * @}
  */

/** @defgroup RCC_Exported_Constants
  * @{
  */

/** @defgroup RCC_HSE_configuration 
  * @{
  */
#define RCC_HSE_OFF                         ((uint8_t)0x00)     /*!< External High Speed oscillator disable                */
#define RCC_HSE_ON                          ((uint8_t)0x01)     /*!< External High Speed oscillator enable                 */
#define RCC_HSE_BYPASS                      ((uint8_t)0x05)     /*!< External crystal oscillator clock bypass mode enable  */

/**
  * @}
  */ 
 
/** @defgroup RCC_PLL_Clock_Source 
  * @{
  */
#define RCC_PLLSOURCE_HSI_DIV2              RCC_GCFGR_PLLSEL_HSI_DIV2       /*!< (CK_HSI / 2) selected as PLL source clock  */
#define RCC_PLLSOURCE_HSEPREDIV             RCC_GCFGR_PLLSEL_HSEPREDIV      /*!< HSE selected as PLL source clock           */
 
/**
  * @}
  */ 

/** @defgroup RCC_PLL_Multiplication_Factor 
  * @{
  */
#define RCC_PLLMUL_2                        RCC_GCFGR_PLLMF2      /*!< PLL source clock x 2  */
#define RCC_PLLMUL_3                        RCC_GCFGR_PLLMF3      /*!< PLL source clock x 3  */
#define RCC_PLLMUL_4                        RCC_GCFGR_PLLMF4      /*!< PLL source clock x 4  */
#define RCC_PLLMUL_5                        RCC_GCFGR_PLLMF5      /*!< PLL source clock x 5  */
#define RCC_PLLMUL_6                        RCC_GCFGR_PLLMF6      /*!< PLL source clock x 6  */
#define RCC_PLLMUL_7                        RCC_GCFGR_PLLMF7      /*!< PLL source clock x 7  */
#define RCC_PLLMUL_8                        RCC_GCFGR_PLLMF8      /*!< PLL source clock x 8  */
#define RCC_PLLMUL_9                        RCC_GCFGR_PLLMF9      /*!< PLL source clock x 9  */
#define RCC_PLLMUL_10                       RCC_GCFGR_PLLMF10     /*!< PLL source clock x 10 */
#define RCC_PLLMUL_11                       RCC_GCFGR_PLLMF11     /*!< PLL source clock x 11 */
#define RCC_PLLMUL_12                       RCC_GCFGR_PLLMF12     /*!< PLL source clock x 12 */
#define RCC_PLLMUL_13                       RCC_GCFGR_PLLMF13     /*!< PLL source clock x 13 */
#define RCC_PLLMUL_14                       RCC_GCFGR_PLLMF14     /*!< PLL source clock x 14 */
#define RCC_PLLMUL_15                       RCC_GCFGR_PLLMF15     /*!< PLL source clock x 15 */
#define RCC_PLLMUL_16                       RCC_GCFGR_PLLMF16     /*!< PLL source clock x 16 */
#define RCC_PLLMUL_17                       RCC_GCFGR_PLLMF17     /*!< PLL source clock x 17 */
#define RCC_PLLMUL_18                       RCC_GCFGR_PLLMF18     /*!< PLL source clock x 18 */
#define RCC_PLLMUL_19                       RCC_GCFGR_PLLMF19     /*!< PLL source clock x 19 */
#define RCC_PLLMUL_20                       RCC_GCFGR_PLLMF20     /*!< PLL source clock x 20 */
#define RCC_PLLMUL_21                       RCC_GCFGR_PLLMF21     /*!< PLL source clock x 21 */
#define RCC_PLLMUL_22                       RCC_GCFGR_PLLMF22     /*!< PLL source clock x 22 */
#define RCC_PLLMUL_23                       RCC_GCFGR_PLLMF23     /*!< PLL source clock x 23 */
#define RCC_PLLMUL_24                       RCC_GCFGR_PLLMF24     /*!< PLL source clock x 24 */
#define RCC_PLLMUL_25                       RCC_GCFGR_PLLMF25     /*!< PLL source clock x 25 */
#define RCC_PLLMUL_26                       RCC_GCFGR_PLLMF26     /*!< PLL source clock x 26 */
#define RCC_PLLMUL_27                       RCC_GCFGR_PLLMF27     /*!< PLL source clock x 27 */
#define RCC_PLLMUL_28                       RCC_GCFGR_PLLMF28     /*!< PLL source clock x 28 */
#define RCC_PLLMUL_29                       RCC_GCFGR_PLLMF29     /*!< PLL source clock x 29 */
#define RCC_PLLMUL_30                       RCC_GCFGR_PLLMF30     /*!< PLL source clock x 30 */
#define RCC_PLLMUL_31                       RCC_GCFGR_PLLMF31     /*!< PLL source clock x 31 */
#define RCC_PLLMUL_32                       RCC_GCFGR_PLLMF32     /*!< PLL source clock x 32 */

/**
  * @}
  */

/** @defgroup RCC_HSEPREDV1_division_factor
  * @{
  */
#define  RCC_HSEPREDV1_DIV1                 RCC_GCFGR2_HSEPREDV1_DIV1        /*!< HSE input to PLL not divided   */
#define  RCC_HSEPREDV1_DIV2                 RCC_GCFGR2_HSEPREDV1_DIV2        /*!< HSE input to PLL divided by 2  */
#define  RCC_HSEPREDV1_DIV3                 RCC_GCFGR2_HSEPREDV1_DIV3        /*!< HSE input to PLL divided by 3  */
#define  RCC_HSEPREDV1_DIV4                 RCC_GCFGR2_HSEPREDV1_DIV4        /*!< HSE input to PLL divided by 4  */
#define  RCC_HSEPREDV1_DIV5                 RCC_GCFGR2_HSEPREDV1_DIV5        /*!< HSE input to PLL divided by 5  */
#define  RCC_HSEPREDV1_DIV6                 RCC_GCFGR2_HSEPREDV1_DIV6        /*!< HSE input to PLL divided by 6  */
#define  RCC_HSEPREDV1_DIV7                 RCC_GCFGR2_HSEPREDV1_DIV7        /*!< HSE input to PLL divided by 7  */
#define  RCC_HSEPREDV1_DIV8                 RCC_GCFGR2_HSEPREDV1_DIV8        /*!< HSE input to PLL divided by 8  */
#define  RCC_HSEPREDV1_DIV9                 RCC_GCFGR2_HSEPREDV1_DIV9        /*!< HSE input to PLL divided by 9  */
#define  RCC_HSEPREDV1_DIV10                RCC_GCFGR2_HSEPREDV1_DIV10       /*!< HSE input to PLL divided by 10 */
#define  RCC_HSEPREDV1_DIV11                RCC_GCFGR2_HSEPREDV1_DIV11       /*!< HSE input to PLL divided by 11 */
#define  RCC_HSEPREDV1_DIV12                RCC_GCFGR2_HSEPREDV1_DIV12       /*!< HSE input to PLL divided by 12 */
#define  RCC_HSEPREDV1_DIV13                RCC_GCFGR2_HSEPREDV1_DIV13       /*!< HSE input to PLL divided by 13 */
#define  RCC_HSEPREDV1_DIV14                RCC_GCFGR2_HSEPREDV1_DIV14       /*!< HSE input to PLL divided by 14 */
#define  RCC_HSEPREDV1_DIV15                RCC_GCFGR2_HSEPREDV1_DIV15       /*!< HSE input to PLL divided by 15 */
#define  RCC_HSEPREDV1_DIV16                RCC_GCFGR2_HSEPREDV1_DIV16       /*!< HSE input to PLL divided by 16 */

/**
  * @}
  */
 
/** @defgroup RCC_System_Clock_Source 
  * @{
  */
#define RCC_SYSCLKSOURCE_HSI                RCC_GCFGR_SCS_HSI           /*!< Select CK_HSI as the CK_SYS source */
#define RCC_SYSCLKSOURCE_HSE                RCC_GCFGR_SCS_HSE           /*!< Select CK_HSE as the CK_SYS source */
#define RCC_SYSCLKSOURCE_PLLCLK             RCC_GCFGR_SCS_PLL           /*!< Select CK_PLL as the CK_SYS source */

/**
  * @}
  */

/** @defgroup RCC_AHB_Clock_Source
  * @{
  */
#define RCC_SYSCLK_DIV1                     RCC_GCFGR_AHBPS_DIV1        /*!< Select CK_SYS as the AHB clock         */  
#define RCC_SYSCLK_DIV2                     RCC_GCFGR_AHBPS_DIV2        /*!< Select (CK_SYS / 2) as the AHB clock   */
#define RCC_SYSCLK_DIV4                     RCC_GCFGR_AHBPS_DIV4        /*!< Select (CK_SYS / 4) as the AHB clock   */
#define RCC_SYSCLK_DIV8                     RCC_GCFGR_AHBPS_DIV8        /*!< Select (CK_SYS / 8) as the AHB clock   */
#define RCC_SYSCLK_DIV16                    RCC_GCFGR_AHBPS_DIV16       /*!< Select (CK_SYS / 16) as the AHB clock  */
#define RCC_SYSCLK_DIV64                    RCC_GCFGR_AHBPS_DIV64       /*!< Select (CK_SYS / 64) as the AHB clock  */
#define RCC_SYSCLK_DIV128                   RCC_GCFGR_AHBPS_DIV128      /*!< Select (CK_SYS / 128) as the AHB clock */
#define RCC_SYSCLK_DIV256                   RCC_GCFGR_AHBPS_DIV256      /*!< Select (CK_SYS / 256) as the AHB clock */
#define RCC_SYSCLK_DIV512                   RCC_GCFGR_AHBPS_DIV512      /*!< Select (CK_SYS / 512) as the AHB clock */

/**
  * @}
  */ 

/** @defgroup RCC_APB_Clock_Source
  * @{
  */
#define RCC_APB1AHB_DIV1                    RCC_GCFGR_APB1PS_DIV1       /*!< Select CK_AHB as the APB1 clock         */
#define RCC_APB1AHB_DIV2                    RCC_GCFGR_APB1PS_DIV2       /*!< Select (CK_AHB / 2) as the APB1 clock   */
#define RCC_APB1AHB_DIV4                    RCC_GCFGR_APB1PS_DIV4       /*!< Select (CK_AHB / 4) as the APB1 clock   */
#define RCC_APB1AHB_DIV8                    RCC_GCFGR_APB1PS_DIV8       /*!< Select (CK_AHB / 8) as the APB1 clock   */
#define RCC_APB1AHB_DIV16                   RCC_GCFGR_APB1PS_DIV116     /*!< Select (CK_AHB / 16) as the APB1 clock  */

#define RCC_APB2AHB_DIV1                    RCC_GCFGR_APB2PS_DIV1       /*!< Select CK_AHB clock as the APB2 clock   */
#define RCC_APB2AHB_DIV2                    RCC_GCFGR_APB2PS_DIV2       /*!< Select (CK_AHB / 2) as the APB2 clock   */
#define RCC_APB2AHB_DIV4                    RCC_GCFGR_APB2PS_DIV4       /*!< Select (CK_AHB / 4) as the APB2 clock   */
#define RCC_APB2AHB_DIV8                    RCC_GCFGR_APB2PS_DIV8       /*!< Select (CK_AHB / 8) as the APB2 clock   */
#define RCC_APB2AHB_DIV16                   RCC_GCFGR_APB2PS_DIV116     /*!< Select (CK_AHB / 16) as the APB2 clock  */

/**
  * @}
  */
  
/** @defgroup RCC_ADC_clock_source 
  * @{
  */
#ifdef GD32F170_190
#define RCC_ADCCLK_HSI28                    ((uint32_t)0x00010000)      /*!< Select HSI28 as the ADC clock          */
#define RCC_ADCCLK_HSI28_DIV2               ((uint32_t)0x00000000)      /*!< Select (HSI28 / 2) as the ADC clock    */
#else
#define RCC_ADCCLK_HSI14                    ((uint32_t)0x00000000)      /*!< Select HSI14 as the ADC clock          */
#endif /* GD32F170_190 */

#define RCC_ADCCLK_APB2_DIV2                ((uint32_t)0x01000000)      /*!< Select (CK_APB2 / 2) as the ADC clock  */
#define RCC_ADCCLK_APB2_DIV4                ((uint32_t)0x01004000)      /*!< Select (CK_APB2 / 4) as the ADC clock  */
#define RCC_ADCCLK_APB2_DIV6                ((uint32_t)0x01008000)      /*!< Select (CK_APB2 / 6) as the ADC clock  */
#define RCC_ADCCLK_APB2_DIV8                ((uint32_t)0x0100C000)      /*!< Select (CK_APB2 / 8) as the ADC clock  */

/**
  * @}
  */
  
#ifdef GD32F130_150  
/** @defgroup RCC_USB_clock_source 
  * @{
  */
#define  RCC_USBCLK_PLL_DIV1                RCC_GCFGR_USBPS_Div1        /*!< Select CK_PLL as the USB clock          */
#define  RCC_USBCLK_PLL_DIV1_5              RCC_GCFGR_USBPS_Div1_5      /*!< Select (CK_PLL / 1.5) as the USB clock  */
#define  RCC_USBCLK_PLL_DIV2                RCC_GCFGR_USBPS_Div2        /*!< Select (CK_PLL / 2) as the USB clock    */
#define  RCC_USBCLK_PLL_DIV2_5              RCC_GCFGR_USBPS_Div2_5      /*!< Select (CK_PLL / 2.5) as the USB clock  */

/**
  * @}
  */
#endif /* GD32F130_150 */

/** @defgroup RCC_CEC_clock_source 
  * @{
  */
#define RCC_CECCLK_HSI_DIV244               RCC_GCFGR3_CECSEL_HSI_DIV244    /*!< Select (HSI / 244) as the CEC clock  */
#define RCC_CECCLK_LSE                      RCC_GCFGR3_CECSEL_LSE           /*!< Select LSE as the CEC clock          */

/**
  * @}
  */

/** @defgroup RCC_USART_clock_source 
  * @{
  */
#define RCC_USART1CLK_APB2                  RCC_GCFGR3_USART1SEL_APB2       /*!< Select CK_APB2 as the USART1 clock */
#define RCC_USART1CLK_CK_SYS                RCC_GCFGR3_USART1SEL_CK_SYS     /*!< Select CK_SYS as the USART1 clock  */
#define RCC_USART1CLK_LSE                   RCC_GCFGR3_USART1SEL_LSE        /*!< Select LSE as the USART1 clock     */
#define RCC_USART1CLK_HSI                   RCC_GCFGR3_USART1SEL_HSI        /*!< Select HSI as the USART1 clock     */

/**
  * @}
  */
       
/** @defgroup RCC_Interrupt_Source
  * @{
  */
#define RCC_INT_LSISTB                      ((uint8_t)0x01)                 /*!< RCC interrupt source is LSISTB   */ 
#define RCC_INT_LSESTB                      ((uint8_t)0x02)                 /*!< RCC interrupt source is LSESTB   */
#define RCC_INT_HSISTB                      ((uint8_t)0x04)                 /*!< RCC interrupt source is HSISTB   */
#define RCC_INT_HSESTB                      ((uint8_t)0x08)                 /*!< RCC interrupt source is HSESTB   */
#define RCC_INT_PLLSTB                      ((uint8_t)0x10)                 /*!< RCC interrupt source is PLLSTB   */
#ifdef GD32F170_190
#define RCC_INT_HSI28STB                    ((uint8_t)0x20)                 /*!< RCC interrupt source is HSI28STB */
#else
#define RCC_INT_HSI14STB                    ((uint8_t)0x20)                 /*!< RCC interrupt source is HSI14STB */
#endif /* GD32F170_190 */
#define RCC_INT_CKM                         ((uint8_t)0x80)                 /*!< RCC interrupt source is CKM      */                  

/**
  * @}
  */
  
/** @defgroup RCC_LSE_Configuration
  * @{
  */
#define RCC_LSE_OFF                         ((uint32_t)0x00000000)                          /*!< LSE disable       */
#define RCC_LSE_EN                          RCC_BDCR_LSEEN                                  /*!< LSE enable        */
#define RCC_LSE_BYPASS                      ((uint32_t)(RCC_BDCR_LSEEN | RCC_BDCR_LSEBPS))  /*!< LSE_BYPASS enable */      

/**
  * @}
  */

/** @defgroup RCC_RTC_Clock_Source
  * @{
  */
#define RCC_RTCCLKSource_LSE                RCC_BDCR_RTCSEL_LSE         /*!< Select LSE as the RTC clock        */
#define RCC_RTCCLKSource_LSI                RCC_BDCR_RTCSEL_LSI         /*!< Select LSI as the RTC clock        */
#define RCC_RTCCLKSource_HSE_DIV32          RCC_BDCR_RTCSEL_HSE         /*!< Select (HSE /32) as the RTC clock  */

/**
  * @}
  */

/** @defgroup RCC_LSE_Drive_Configuration 
  * @{
  */
  #define RCC_LSEDRIVE_LOW                    ((uint32_t)0x00000000)    /*!< LSE drive capability: lower driving capability         */ 
#define RCC_LSEDRIVE_MEDIUMLOW              RCC_BDCR_LSEDRI_0           /*!< LSE drive capability: medium low driving capability    */
#define RCC_LSEDRIVE_MEDIUMHIGH             RCC_BDCR_LSEDRI_1           /*!< LSE drive capability:  medium high driving capability  */
#define RCC_LSEDRIVE_HIGH                   RCC_BDCR_LSEDRI             /*!< LSE drive capability: higher driving capability        */

/**
  * @}
  */
  
/** @defgroup RCC_AHB_Peripherals 
  * @{
  */
#define RCC_AHBPERIPH_GPIOA                 RCC_AHBCCR_PAEN             /*!< GPIOA clock enable  */
#define RCC_AHBPERIPH_GPIOB                 RCC_AHBCCR_PBEN             /*!< GPIOB clock enable  */
#define RCC_AHBPERIPH_GPIOC                 RCC_AHBCCR_PCEN             /*!< GPIOC clock enable  */
#define RCC_AHBPERIPH_GPIOD                 RCC_AHBCCR_PDEN             /*!< GPIOD clock enable  */
#define RCC_AHBPERIPH_GPIOF                 RCC_AHBCCR_PFEN             /*!< GPIOF clock enable  */
#define RCC_AHBPERIPH_TSI                   RCC_AHBCCR_TSIEN            /*!< TSI clock enable    */
#define RCC_AHBPERIPH_CRC                   RCC_AHBCCR_CRCEN            /*!< CRC clock enable    */
#define RCC_AHBPERIPH_FMC                   RCC_AHBCCR_FMCEN            /*!< FMC clock enable    */
#define RCC_AHBPERIPH_SRAM                  RCC_AHBCCR_SRAMEN           /*!< SRAM clock enable   */
#define RCC_AHBPERIPH_DMA1                  RCC_AHBCCR_DMA1EN           /*!< DMA1 clock enable   */

/**
  * @}
  */
  
/** @defgroup RCC_AHB_Peripherals_RST 
  * @{
  */
#define  RCC_AHBPERIPH_GPIOARST             RCC_AHBRCR_PARST            /*!< GPIOA clock reset  */
#define  RCC_AHBPERIPH_GPIOBRST             RCC_AHBRCR_PBRST            /*!< GPIOB clock reset  */    
#define  RCC_AHBPERIPH_GPIOCRST             RCC_AHBRCR_PCRST            /*!< GPIOC clock reset  */ 
#define  RCC_AHBPERIPH_GPIODRST             RCC_AHBRCR_PDRST            /*!< GPIOD clock reset  */
#define  RCC_AHBPERIPH_GPIOFRST             RCC_AHBRCR_PFRST            /*!< GPIOF clock reset  */
#define  RCC_AHBPERIPH_TSIRST               RCC_AHBRCR_TSIRST           /*!< TSI clock reset    */

/**
  * @}
  */

/** @defgroup RCC_APB2_Peripherals 
  * @{
  */
#define RCC_APB2PERIPH_CFG                  RCC_APB2CCR_CFGCMPEN        /*!< CFG clock enable      */
#define RCC_APB2PERIPH_CMP                  RCC_APB2CCR_CFGCMPEN        /*!< CMP clock enable      */
#define RCC_APB2PERIPH_ADC1                 RCC_APB2CCR_ADC1EN          /*!< ADC1 clock enable     */
#define RCC_APB2PERIPH_TIMER1               RCC_APB2CCR_TIMER1EN        /*!< TIMER1 clock enable   */
#define RCC_APB2PERIPH_SPI1                 RCC_APB2CCR_SPI1EN          /*!< SPI1 clock enable     */
#define RCC_APB2PERIPH_USART1               RCC_APB2CCR_USART1EN        /*!< USART1 clock enable   */
#define RCC_APB2PERIPH_TIMER15              RCC_APB2CCR_TIMER15EN       /*!< TIMER15 clock enable  */
#define RCC_APB2PERIPH_TIMER16              RCC_APB2CCR_TIMER16EN       /*!< TIMER16 clock enable  */
#define RCC_APB2PERIPH_TIMER17              RCC_APB2CCR_TIMER17EN       /*!< TIMER17 clock enable  */

/**
  * @}
  */

/** @defgroup RCC_APB2_Peripherals_RST 
  * @{
  */
#define  RCC_APB2PERIPH_CFGRST              RCC_APB2RCR_CFGCMPRST       /*!< CFG clock reset      */
#define  RCC_APB2PERIPH_CMPRST              RCC_APB2RCR_CFGCMPRST       /*!< CPM clock reset      */
#define  RCC_APB2PERIPH_ADC1RST             RCC_APB2RCR_ADC1RST         /*!< ADC1 clock reset     */
#define  RCC_APB2PERIPH_TIMER1RST           RCC_APB2RCR_TIMER1RST       /*!< TIMER1 clock reset   */
#define  RCC_APB2PERIPH_SPI1RST             RCC_APB2RCR_SPI1RST         /*!< SPI1 clock reset     */
#define  RCC_APB2PERIPH_USART1RST           RCC_APB2RCR_USART1RST       /*!< USART1 clock reset   */
#define  RCC_APB2PERIPH_TIMER15RST          RCC_APB2RCR_TIMER15RST      /*!< TIMER15 clock reset  */
#define  RCC_APB2PERIPH_TIMER16RST          RCC_APB2RCR_TIMER16RST      /*!< TIMER16 clock reset  */
#define  RCC_APB2PERIPH_TIMER17RST          RCC_APB2RCR_TIMER17RST      /*!< TIMER17 clock reset  */

/**
  * @}
  */ 

/** @defgroup RCC_APB1_Peripherals 
  * @{
  */
#define RCC_APB1PERIPH_TIMER2               RCC_APB1CCR_TIMER2EN        /*!< TIMER2 clock enable    */
#define RCC_APB1PERIPH_TIMER3               RCC_APB1CCR_TIMER3EN        /*!< TIMER3 clock enable    */
#define RCC_APB1PERIPH_TIMER6               RCC_APB1CCR_TIMER6EN        /*!< TIMER6 clock enable    */
#define RCC_APB1PERIPH_TIMER14              RCC_APB1CCR_TIMER14EN       /*!< TIMER14 clock enable   */
#define RCC_APB1PERIPH_WWDG                 RCC_APB1CCR_WWDGEN          /*!< WWDG clock enable      */
#define RCC_APB1PERIPH_SPI2                 RCC_APB1CCR_SPI2EN          /*!< SPI2 clock enable      */
#define RCC_APB1PERIPH_SPI3                 RCC_APB1CCR_SPI3EN          /*!< SPI3 clock enable      */
#define RCC_APB1PERIPH_USART2               RCC_APB1CCR_USART2EN        /*!< USART2 clock enable    */
#define RCC_APB1PERIPH_I2C1                 RCC_APB1CCR_I2C1EN          /*!< I2C1 clock enable      */
#define RCC_APB1PERIPH_I2C2                 RCC_APB1CCR_I2C2EN          /*!< I2C2 clock enable      */
#ifdef GD32F130_150
#define RCC_APB1PERIPH_USB                  RCC_APB1CCR_USBEN           /*!< USB clock enable       */
#endif /* GD32F130_150 */
#define RCC_APB1PERIPH_PWR                  RCC_APB1CCR_PWREN           /*!< PWR clock enable       */
#define RCC_APB1PERIPH_DAC                  RCC_APB1CCR_DACEN           /*!< DAC clock enable       */
#define RCC_APB1PERIPH_CEC                  RCC_APB1CCR_CECEN           /*!< CEC clock enable       */
#ifdef GD32F170_190
#define RCC_APB1PERIPH_LCD                  RCC_APB1CCR_LCDREN          /*!< LCD clock enable       */
#define RCC_APB1PERIPH_CAN1                 RCC_APB1CCR_CAN1EN          /*!< CAN1 clock enable      */
#define RCC_APB1PERIPH_CAN2                 RCC_APB1CCR_CAN2EN          /*!< CAN2 clock enable      */
#define RCC_APB1PERIPH_OPAMP                RCC_APB1CCR_OPAMPIVREFEN    /*!< OPAMP clock enable     */
#define RCC_APB1PERIPH_IVREF                RCC_APB1CCR_OPAMPIVREFEN    /*!< IVREF clock enable     */
#endif /* GD32F170_190 */

/**
  * @}
  */ 

/** @defgroup RCC_APB1_Peripherals_RST 
  * @{
  */
#define  RCC_APB1PERIPH_TIMER2RST           RCC_APB1RCR_TIMER2RST       /*!< TIMER2 clock reset     */        
#define  RCC_APB1PERIPH_TIMER3RST           RCC_APB1RCR_TIMER3RST       /*!< TIMER3 clock reset     */      
#define  RCC_APB1PERIPH_TIMER6RST           RCC_APB1RCR_TIMER6RST       /*!< TIMER6 clock reset     */        
#define  RCC_APB1PERIPH_TIMER14RST          RCC_APB1RCR_TIMER14RST      /*!< TIMER14 clock reset    */        
#define  RCC_APB1PERIPH_WWDGRST             RCC_APB1RCR_WWDGRST         /*!< WWDG clock reset       */  
#define  RCC_APB1PERIPH_SPI2RST             RCC_APB1RCR_SPI2RST         /*!< SPI2 clock reset       */  
#define  RCC_APB1PERIPH_SPI3RST             RCC_APB1RCR_SPI3RST         /*!< SPI3 clock reset       */  
#define  RCC_APB1PERIPH_USART2RST           RCC_APB1RCR_USART2RST       /*!< USART2 clock reset     */   
#define  RCC_APB1PERIPH_I2C1RST             RCC_APB1RCR_I2C1RST         /*!< I2C1 clock reset       */     
#define  RCC_APB1PERIPH_I2C2RST             RCC_APB1RCR_I2C2RST         /*!< I2C2 clock reset       */
#ifdef GD32F130_150
#define  RCC_APB1PERIPH_USBRST              RCC_APB1RCR_USBRST          /*!< USB clock reset        */
#endif /* GD32F130_150 */
#define  RCC_APB1PERIPH_PWRRST              RCC_APB1RCR_PWRRST          /*!< PWR clock reset        */      
#define  RCC_APB1PERIPH_DACRST              RCC_APB1RCR_DACRST          /*!< DAC clock reset        */      
#define  RCC_APB1PERIPH_CECRST              RCC_APB1RCR_CECRST          /*!< CEC clock reset        */
#ifdef GD32F170_190
#define  RCC_APB1PERIPH_LCDRST              RCC_APB1RCR_LCDRST          /*!< LCD clock reset        */
#define  RCC_APB1PERIPH_CAN1RST             RCC_APB1RCR_CAN1RST         /*!< CAN1 clock reset       */
#define  RCC_APB1PERIPH_CAN2RST             RCC_APB1RCR_CAN2RST         /*!< CAN2 clock reset       */
#define  RCC_APB1PERIPH_OPAMPRST            RCC_APB1RCR_OPAMPIVREFRST   /*!< OPAMP clock reset      */
#define  RCC_APB1PERIPH_IVREFRST            RCC_APB1RCR_OPAMPIVREFRST   /*!< IVREF clock reset      */
#endif /* GD32F170_190 */

/**
  * @}
  */ 

/** @defgroup RCC_ACCRPeripherals_I2C3 
  * @{
  */
#define RCC_ACCRPERIPH_I2C3                 RCC_ACCR_I2C3EN             /*!< I2C3 clock enable      */

/**
  * @}
  */ 

/** @defgroup RCC_ARCR_Peripherals_I2C3_RST 
  * @{
  */
#define RCC_ARCRPERIPH_I2C3RST              RCC_ARCR_I2C3RST            /*!< I2C3 clock reset       */

/**
  * @}
  */

/** @defgroup RCC_CK_OUT_Clock_Source
  * @{
  */
  #define  RCC_CKOUTSRC_NOCLOCK             RCC_GCFGR_CKOUTSRC_NOCLOCK       /*!< CKOUT Clock Source Selection: No clock selected                                 */
#ifdef GD32F170_190
#define  RCC_CKOUTSRC_HSI14                 RCC_GCFGR_CKOUTSRC_HSI14         /*!< CKOUT Clock Source Selection: High Speed 28M Internal Oscillator clock selected */
#else
#define  RCC_CKOUTSRC_HSI28                 RCC_GCFGR_CKOUTSRC_HSI28         /*!< CKOUT Clock Source Selection: High Speed 14M Internal Oscillator clock selected */
#endif /* GD32F170_190 */
#define  RCC_CKOUTSRC_LSI                   RCC_GCFGR_CKOUTSRC_LSI           /*!< CKOUT Clock Source Selection: Internal Low Speed oscillator clock selected      */
#define  RCC_CKOUTSRC_LSE                   RCC_GCFGR_CKOUTSRC_LSE           /*!< CKOUT Clock Source Selection: External Low Speed oscillator clock selected      */
#define  RCC_CKOUTSRC_SYSCLK                RCC_GCFGR_CKOUTSRC_SYSCLK        /*!< CKOUT Clock Source Selection: System clock selected                             */
#define  RCC_CKOUTSRC_HSI                   RCC_GCFGR_CKOUTSRC_HSI           /*!< CKOUT Clock Source Selection: High Speed 8M Internal Oscillator clock selected  */
#define  RCC_CKOUTSRC_HSE                   RCC_GCFGR_CKOUTSRC_HSE           /*!< CKOUT Clock Source Selection: External High Speed oscillator clock selected     */
#define  RCC_CKOUTSRC_PLLCLK_DIV2           RCC_GCFGR_CKOUTSRC_PLL_DIV2      /*!< CKOUT Clock Source Selection: CK_PLL selected depend on PLLDV                   */
#define  RCC_CKOUTSRC_PLLCLK_DIV1           RCC_GCFGR_CKOUTSRC_PLL_DIV1      /*!< CKOUT Clock Source Selection: (CK_PLL / 2) selected depend on PLLDV             */

#define  RCC_CKOUTDIV_1                     RCC_GCFGR_CKOUTDIV_1             /*!< The CK_OUT is divided by 1    */
#define  RCC_CKOUTDIV_2                     RCC_GCFGR_CKOUTDIV_2             /*!< The CK_OUT is divided by 2    */
#define  RCC_CKOUTDIV_4                     RCC_GCFGR_CKOUTDIV_4             /*!< The CK_OUT is divided by 4    */
#define  RCC_CKOUTDIV_8                     RCC_GCFGR_CKOUTDIV_8             /*!< The CK_OUT is divided by 8    */
#define  RCC_CKOUTDIV_16                    RCC_GCFGR_CKOUTDIV_16            /*!< The CK_OUT is divided by 16   */
#define  RCC_CKOUTDIV_32                    RCC_GCFGR_CKOUTDIV_32            /*!< The CK_OUT is divided by 32   */
#define  RCC_CKOUTDIV_64                    RCC_GCFGR_CKOUTDIV_64            /*!< The CK_OUT is divided by 64   */
#define  RCC_CKOUTDIV_128                   RCC_GCFGR_CKOUTDIV_128           /*!< The CK_OUT is divided by 128  */

/**
  * @}
  */

#ifdef GD32F170_190
/** @defgroup RCC_CK_OUT2_Clock_Source
  * @{
  */
#define  RCC_CKOUT2SRC_NOCLOCK              RCC_GCFGR4_CKOUT2SRC_NOCLOCK     /*!< CKOUT2 Clock Source Selection: No clock selected                                 */
#define  RCC_CKOUT2SRC_HSI28                RCC_GCFGR4_CKOUT2SRC_HSI28       /*!< CKOUT2 Clock Source Selection: High Speed 28M Internal Oscillator clock selected */
#define  RCC_CKOUT2SRC_LSI                  RCC_GCFGR4_CKOUT2SRC_LSI         /*!< CKOUT2 Clock Source Selection: Internal Low Speed oscillator clock selected      */
#define  RCC_CKOUT2SRC_LSE                  RCC_GCFGR4_CKOUT2SRC_LSE         /*!< CKOUT2 Clock Source Selection: External Low Speed oscillator clock selected      */
#define  RCC_CKOUT2SRC_SYSCLK               RCC_GCFGR4_CKOUT2SRC_SYSCLK      /*!< CKOUT2 Clock Source Selection: System clock selected                             */
#define  RCC_CKOUT2SRC_HSI                  RCC_GCFGR4_CKOUT2SRC_HSI         /*!< CKOUT2 Clock Source Selection: High Speed 8M Internal Oscillator clock selected  */
#define  RCC_CKOUT2SRC_HSE                  RCC_GCFGR4_CKOUT2SRC_HSE         /*!< CKOUT2 Clock Source Selection: External High Speed oscillator clock selected     */
#define  RCC_CKOUT2SRC_PLLCLK_DIV2          ((uint32_t)0x00000002)           /*!< CKOUT2 Clock Source Selection: CK_PLL selected depend on PLLDV                   */
#define  RCC_CKOUT2SRC_PLLCLK_DIV1          ((uint32_t)0x00000001)           /*!< CKOUT2 Clock Source Selection: (CK_PLL / 2) selected depend on PLLDV             */

/**
  * @}
  */
#endif /* GD32F170_190 */

/** @defgroup RCC_Flag 
  * @{
  */
/* The flag to check is in GCCR register */
#define  RCC_FLAG_HSISTB                    ((uint8_t)0x01)        /*!< HSI high speed internal oscillator stabilization flag */
#define  RCC_FLAG_HSESTB                    ((uint8_t)0x11)        /*!< External crystal oscillator clock stabilization flag  */
#define  RCC_FLAG_PLLSTB                    ((uint8_t)0x19)        /*!< PLL clock stabilization flag                          */

/* The flag to check is in BDCR register */
#define  RCC_FLAG_LSESTB                    ((uint8_t)0x21)        /*!< External low-speed oscillator stabilization flag      */

 /* The flag to check is in GCSR register */
#define  RCC_FLAG_LSISTB                    ((uint8_t)0x41)        /*!< Internal low-speed oscillator stabilization flag      */

#define  RCC_FLAG_V12RST                    ((uint8_t)0x57)        /*!< V12 domain Power reset flag                           */
#define  RCC_FLAG_OBLRST                    ((uint8_t)0x59)        /*!< Option byte loader reset flag                         */
#define  RCC_FLAG_EPRST                     ((uint8_t)0x5A)        /*!< External PIN reset flag                               */
#define  RCC_FLAG_POPDRST                   ((uint8_t)0x5B)        /*!< Power reset flag                                      */
#define  RCC_FLAG_SWRST                     ((uint8_t)0x5C)        /*!< Software reset flag                                   */
#define  RCC_FLAG_IWDGRST                   ((uint8_t)0x5D)        /*!< Independent watchdog timer reset flag                 */
#define  RCC_FLAG_WWDGRST                   ((uint8_t)0x5E)        /*!< Window watchdog timer reset flag                      */
#define  RCC_FLAG_LPRST                     ((uint8_t)0x5F)        /*!< Low-power reset flag                                  */

#ifdef GD32F170_190
/* The flag to check is in GCCR2 register */
#define  RCC_FLAG_HSI14STB                  ((uint8_t)0x61)        /*!< HSI14 stabilization flag                              */
#else
/* The flag to check is in GCCR2 register */
#define  RCC_FLAG_HSI28STB                  ((uint8_t)0x61)        /*!< HSI28 stabilization flag                              */
#endif /* GD32F170_190 */

/**
  * @}
  */

/** @defgroup RCC_DEEPSLEEP_VC_VOL
  * @{
  */
#ifdef GD32F170_190
#define  RCC_KERNEL_VOL1_8                  RCC_DEEPSLEEP_VC1_8    /*!< The core voltage is 1.8V in Deep-sleep mode           */ 
#define  RCC_KERNEL_VOL1_6                  RCC_DEEPSLEEP_VC1_6    /*!< The core voltage is 1.6V in Deep-sleep mode           */
#define  RCC_KERNEL_VOL1_4                  RCC_DEEPSLEEP_VC1_4    /*!< The core voltage is 1.4V in Deep-sleep mode           */
#define  RCC_KERNEL_VOL1_2                  RCC_DEEPSLEEP_VC1_2    /*!< The core voltage is 1.2V in Deep-sleep mode           */
#else
#define  RCC_KERNEL_VOL1_2                  RCC_DEEPSLEEP_VC1_2    /*!< The core voltage is 1.2V in Deep-sleep mode           */
#define  RCC_KERNEL_VOL1_1                  RCC_DEEPSLEEP_VC1_1    /*!< The core voltage is 1.1V in Deep-sleep mode           */
#define  RCC_KERNEL_VOL1_0                  RCC_DEEPSLEEP_VC1_0    /*!< The core voltage is 1.0V in Deep-sleep mode           */
#define  RCC_KERNEL_VOL0_9                  RCC_DEEPSLEEP_VC0_9    /*!< The core voltage is 0.9V in Deep-sleep mode           */
#endif /* GD32F170_190 */
/**
  * @}
  */

#ifdef GD32F130_150
/** @defgroup RCC_PDR_S
  * @{
  */
#define  RCC_POWERDOWNVOL2_6                RCC_PDR_S2_6           /*!< The Power down voltage is 2.6V           */ 
#define  RCC_POWERDOWNVOL1_8                RCC_PDR_S1_8           /*!< The Power down voltage is 1.8V           */ 

/**
  * @}
  */
#endif /* GD32F130_150 */

/**
  * @}
  */
  
/** @defgroup RCC_Exported_Functions
  * @{
  */
/* Reset the RCC clock configuration to the default reset state */
void RCC_DeInit(void);

/* Internal/external clocks, PLL, CKM and CK_OUT configuration functions */
void RCC_HSEConfig(uint8_t RCC_HSE);
TypeState RCC_WaitForHSEStartUp(void);
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue);
void RCC_HSI_Enable(TypeState NewValue);
#ifdef GD32F170_190
void RCC_AdjustHSI28CalibrationValue(uint8_t HSI28CalibrationValue);
void RCC_HSI28_Enable(TypeState NewValue);
#else
void RCC_AdjustHSI14CalibrationValue(uint8_t HSI14CalibrationValue);
void RCC_HSI14_Enable(TypeState NewValue);
#endif /* GD32F170_190 */
void RCC_LSEConfig(uint32_t RCC_LSE);
void RCC_LSEDriveConfig(uint32_t RCC_LSEDrive);
void RCC_LSI_Enable(TypeState NewValue);
void RCC_PLLConfig(uint32_t RCC_PLLSelect, uint32_t RCC_PLLMF);
void RCC_PLL_Enable(TypeState NewValue);
void RCC_HSEPREDVConfig(uint32_t RCC_HSEPREDV1_Div);
void RCC_HSEClockMonitor_Enable(TypeState NewValue);
void RCC_CKOUTSRCConfig(uint32_t RCC_CKOUTSRC, uint32_t RCC_CKOUTDIV);
#ifdef GD32F170_190
void RCC_CKOUT2SRCConfig(uint32_t RCC_CKOUT2SRC, uint32_t RCC_CKOUT2DIV);
#endif /* GD32F170_190 */

/* System, AHB, APB1 and APB2 busses clocks configuration functions */
void RCC_CK_SYSConfig(uint32_t RCC_SYSCLKSource);
uint8_t RCC_GetCK_SYSSource(void);
void RCC_AHBConfig(uint32_t RCC_CK_SYSDiv);
void RCC_APB1Config(uint32_t RCC_APB1);
void RCC_APB2Config(uint32_t RCC_APB2);
void RCC_ADCCLKConfig(uint32_t RCC_ADCCLK);
#ifdef GD32F130_150
void RCC_USBCLKConfig(uint32_t RCC_USBCLK);
#endif /* GD32F130_150 */
void RCC_CECCLKConfig(uint32_t RCC_CECCLK);
void RCC_USARTCLKConfig(uint32_t RCC_USARTCLK);
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource);
void RCC_GetClocksFreq(RCC_ClocksPara* RCC_Clocks);

/* Peripheral clocks configuration functions */

void RCC_AHBPeriphClock_Enable(uint32_t RCC_AHBPeriph, TypeState NewValue);
void RCC_APB2PeriphClock_Enable(uint32_t RCC_APB2Periph, TypeState NewValue);
void RCC_APB1PeriphClock_Enable(uint32_t RCC_APB1Periph, TypeState NewValue);
void RCC_ACCRPeriphClock_Enable(uint32_t RCC_ACCRPeriph, TypeState NewValue);
void RCC_RTCCLK_Enable(TypeState NewValue);

void RCC_AHBPeriphReset_Enable(uint32_t RCC_AHBPeriphRST, TypeState NewValue);
void RCC_APB2PeriphReset_Enable(uint32_t RCC_APB2PeriphRST, TypeState NewValue);
void RCC_APB1PeriphReset_Enable(uint32_t RCC_APB1PeriphRST, TypeState NewValue);
void RCC_ARCRPeriphReset_Enable(uint32_t RCC_ARCRPeriphRST, TypeState NewValue);
void RCC_BackupReset_Enable(TypeState NewValue);

/* Interrupts and flags management functions */
void RCC_INTConfig(uint8_t RCC_INT, TypeState NewValue);
TypeState RCC_GetBitState(uint8_t RCC_FLAG);
void RCC_ClearBitState(void);
TypeState RCC_GetIntBitState(uint8_t RCC_INT);
void RCC_ClearIntBitState(uint8_t RCC_INT);

void RCC_UnlockPower(void);
void RCC_KERNELVOLConfig(uint32_t RCC_KERNEL_VOL);
#ifdef GD32F130_150
void RCC_POWERDOWNVOLConfig(uint32_t RCC_POWERDOWNVOL);
#endif /* GD32F130_150 */
#ifdef __cplusplus
}
#endif

#endif /* __GD32F1X0_RCC_H */

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
