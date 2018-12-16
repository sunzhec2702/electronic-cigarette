/**
  ******************************************************************************
  * @file    gd32f1x0_ivref.c
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   IVREF functions of the firmware library.
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0_ivref.h"
#include "gd32f1x0_rcc.h"

#ifdef GD32F170_190

/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @defgroup IVREF 
  * @brief IVREF driver modules
  * @{
  */

/** @defgroup IVREF_Private_Defines
  * @{
  */

#define CTLR_DECAP_RESET                ((uint32_t)0xBFFFFFFF)       /*!< IVREF CTLR DECAP Reset */
#define CTLR_VPT_RESET                  ((uint32_t)0xE0FFFFFF)       /*!< IVREF CTLR VPTP Reset */
#define CTLR_MODSEL_RESET               ((uint32_t)0xFFFF4FFF)       /*!< IVREF CTLR MODSEL Reset */
#define CTLR_CPT_RESET                  ((uint32_t)0xFFFFE0FF)       /*!< IVREF CTLR CPT Reset */
#define CTLR_SCMO_RESET                 ((uint32_t)0xFFFFFF7F)       /*!< IVREF CTLR SCMO Reset */
#define CTLR_CSDA_RESET                 ((uint32_t)0xFFFFFFC0)       /*!< IVREF CTLR CSDA Reset */

/**
  * @}
  */

/** @defgroup IVREF_Private_Functions
  * @{
  */

/**
  * @brief  Reset the IVREF peripheral.
  * @retval None
  */
void IVREF_DeInit(void)
{
    /*!< Set CTLR register to reset value */
    IVREF->CTLR = 0x10000F00;
}

/**
  * @brief  Enable or disable the VREF.
  * @param  NewValue: New value of the VREF.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void IVREF_VREF_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable the Voltage Reference */
        IVREF->CTLR |= IVREF_CTLR_VREN;
    }
    else
    {
        /* Disable the Voltage Reference */
        IVREF->CTLR &= ~(IVREF_CTLR_VREN);
    }
}

/**
  * @brief  Set the VREF Mode.
  * @param  VREFMode: the VREF connect or Disconnect external capacitor.
  *   This parameter can be any combination of the following values:
  *     @arg VREF_CONNECT_EXTERNAL_CAP : VREF connect external capacitor.
  *     @arg VREF_DISCONNECT_EXTERNAL_CAP: VREF Disconnect external capacitor.
  * @retval None
  */
void IVREF_SetVREFMode(uint32_t VREFMode)
{
    uint32_t temp = 0;
    /* Get CTLR value */
    temp = IVREF->CTLR;
    /* Clear Voltage Reference Enable bits */
    temp = temp&CTLR_DECAP_RESET;
    /* Set Voltage Reference Enable bits */
    temp |= VREFMode;
    /* Write to CTLR */
    IVREF->CTLR = temp;
}

/**
  * @brief  Set the VREF Voltage Precision Trim.
  * @param  VREFPrecisionTrim: the Voltage precision trim 
  *   This parameter can be any combination of the following values:
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_0  : -6.4%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_1  : -6.0%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_2  : -5.6%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_3  : -5.2%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_4  : -4.8%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_5  : -4.4%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_6  : -4.0%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_7  : -3.6%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_8  : -3.2%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_9  : -2.8%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_10 : -2.4%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_11 : -2.0%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_12 : -1.6%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_13 : -1.2%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_14 : -0.8%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_15 : -0.4%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_16 :  0%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_17 : +0.4%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_18 : +0.8%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_19 : +1.2%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_20 : +1.6%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_21 : +2.0%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_22 : +2.4%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_23 : +2.8%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_24 : +3.2%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_25 : +3.6%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_26 : +4.0%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_27 : +4.4%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_28 : +4.8%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_29 : +5.2%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_30 : +5.6%
  *     @arg VREF_VOLTAGE_PRECISION_TRIM_31 : +6.0%
  * @retval None
  */
void IVREF_VREFPrecisionTrimConfig(uint32_t VREFPrecisionTrim)
{
    uint32_t temp = 0;
    /* Get CTLR value */
    temp = IVREF->CTLR;
    /* Clear Voltage precision trim bits */
    temp = temp&CTLR_VPT_RESET;
    /* Set Voltage precision trim bits */
    temp |= VREFPrecisionTrim;
    /* Write to CTLR */
    IVREF->CTLR = temp;
}

/**
  * @brief  Enable or disable the IREF.
  * @param  NewValue: New value of the IREF.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void IVREF_IREF_Enable(TypeState NewValue) 
{
    if (NewValue != DISABLE)
    {
        /* Enable the Current Reference */
        IVREF->CTLR |= IVREF_CTLR_CREN;
    }
    else
    {
        /* Disable the Current Reference */
        IVREF->CTLR &= ~(IVREF_CTLR_CREN);
    }
}

/**
  * @brief  Set the IREF Mode.
  * @param  IREFMode: Mode selection
  *   This parameter can be any combination of the following values:
  *     @arg IREF_MODE_LOW_POWER : 1uA step.
  *     @arg IREF_MODE_HIGH_CURRENT: 8uA step.
  * @retval None
  */
void IVREF_SetIREFMode(uint32_t IREFMode)
{
    uint32_t temp = 0;
    /* Get CTLR value */
    temp = IVREF->CTLR;
    /* Clear Mode selection bits */
    temp &= CTLR_MODSEL_RESET;
    /* Set Mode selection bits */
    temp |= IREFMode;
    /* Write to CTLR */
    IVREF->CTLR = temp;
}

/**
  * @brief  Set the IREF Current precision Trim.
  * @param  IREFPrecisionTrim: the Current precision trim 
  *   This parameter can be any combination of the following values:
  *     @arg IREF_CURRENT_PRECISION_TRIM_0  : -15%
  *     @arg IREF_CURRENT_PRECISION_TRIM_1  : -14%
  *     @arg IREF_CURRENT_PRECISION_TRIM_2  : -13%
  *     @arg IREF_CURRENT_PRECISION_TRIM_3  : -12%
  *     @arg IREF_CURRENT_PRECISION_TRIM_4  : -11%
  *     @arg IREF_CURRENT_PRECISION_TRIM_5  : -10%
  *     @arg IREF_CURRENT_PRECISION_TRIM_6  : -9%
  *     @arg IREF_CURRENT_PRECISION_TRIM_7  : -8%
  *     @arg IREF_CURRENT_PRECISION_TRIM_8  : -7%
  *     @arg IREF_CURRENT_PRECISION_TRIM_9  : -6%
  *     @arg IREF_CURRENT_PRECISION_TRIM_10 : -5%
  *     @arg IREF_CURRENT_PRECISION_TRIM_11 : -4%
  *     @arg IREF_CURRENT_PRECISION_TRIM_12 : -3%
  *     @arg IREF_CURRENT_PRECISION_TRIM_13 : -2%
  *     @arg IREF_CURRENT_PRECISION_TRIM_14 : -1%
  *     @arg IREF_CURRENT_PRECISION_TRIM_15 :  0%
  *     @arg IREF_CURRENT_PRECISION_TRIM_16 : +1%
  *     @arg IREF_CURRENT_PRECISION_TRIM_17 : +2%
  *     @arg IREF_CURRENT_PRECISION_TRIM_18 : +3%
  *     @arg IREF_CURRENT_PRECISION_TRIM_19 : +4%
  *     @arg IREF_CURRENT_PRECISION_TRIM_20 : +5%
  *     @arg IREF_CURRENT_PRECISION_TRIM_21 : +6%
  *     @arg IREF_CURRENT_PRECISION_TRIM_22 : +7%
  *     @arg IREF_CURRENT_PRECISION_TRIM_23 : +8%
  *     @arg IREF_CURRENT_PRECISION_TRIM_24 : +9%
  *     @arg IREF_CURRENT_PRECISION_TRIM_25 : +10%
  *     @arg IREF_CURRENT_PRECISION_TRIM_26 : +11%
  *     @arg IREF_CURRENT_PRECISION_TRIM_27 : +12%
  *     @arg IREF_CURRENT_PRECISION_TRIM_28 : +13%
  *     @arg IREF_CURRENT_PRECISION_TRIM_29 : +14%
  *     @arg IREF_CURRENT_PRECISION_TRIM_30 : +15%
  *     @arg IREF_CURRENT_PRECISION_TRIM_31 : +16%
  * @retval None
  */
void IVREF_IREFPrecisionTrimConfig(uint32_t IREFPrecisionTrim)
{
    uint32_t temp = 0;
    /* Get CTLR value */
    temp = IVREF->CTLR;
    /* Clear Current precision trim bits */
    temp &= CTLR_CPT_RESET;
    /* Set Current precision trim bits */
    temp |= IREFPrecisionTrim;
    /* Write to CTLR */
    IVREF->CTLR = temp;
}

/**
  * @brief  Set the IREF Sink.
  * @param  IREFSinkMode: Mode selection
  *   This parameter can be any combination of the following values:
  *     @arg IREF_SOURCE_CURRENT : Source current.
  *     @arg IREF_SINK_CURRENT: Sink current
  * @retval None
  */
void IVREF_SetIREFSink(uint32_t IREFSinkMode)
{
    uint32_t temp = 0;
    /* Get CTLR value */
    temp = IVREF->CTLR;
    /* Clear Sink current mode bits */
    temp &= CTLR_SCMO_RESET;
    /* Set Sink current mode bits */
    temp |= IREFSinkMode;
    /* Write to CTLR */
    IVREF->CTLR = temp;
}

/**
  * @brief  Set the VREF Current step Data.
  * @param  IREFStepData: Current step data
  *   This parameter can be any combination of the following values:
  *     @arg IREF_CURRENT_STEP_DATA_0 : Default value
  *     @arg IREF_CURRENT_STEP_DATA_2 : Step*2
  *     @arg IREF_CURRENT_STEP_DATA_3 : Step*3
  *     @arg IREF_CURRENT_STEP_DATA_4 : Step*4
  *     @arg IREF_CURRENT_STEP_DATA_5 : Step*5
  *     @arg IREF_CURRENT_STEP_DATA_6 : Step*6
  *     @arg IREF_CURRENT_STEP_DATA_7 : Step*7
  *     @arg IREF_CURRENT_STEP_DATA_8 : Step*8
  *     @arg IREF_CURRENT_STEP_DATA_9 : Step*9
  *     @arg IREF_CURRENT_STEP_DATA_10 : Step*10
  *     @arg IREF_CURRENT_STEP_DATA_11 : Step*11
  *     @arg IREF_CURRENT_STEP_DATA_12 : Step*12
  *     @arg IREF_CURRENT_STEP_DATA_13 : Step*13
  *     @arg IREF_CURRENT_STEP_DATA_14 : Step*14
  *     @arg IREF_CURRENT_STEP_DATA_15 : Step*15
  *     @arg IREF_CURRENT_STEP_DATA_16 : Step*16
  *     @arg IREF_CURRENT_STEP_DATA_17 : Step*17
  *     @arg IREF_CURRENT_STEP_DATA_18 : Step*18
  *     @arg IREF_CURRENT_STEP_DATA_19 : Step*19
  *     @arg IREF_CURRENT_STEP_DATA_20 : Step*20
  *     @arg IREF_CURRENT_STEP_DATA_21 : Step*21
  *     @arg IREF_CURRENT_STEP_DATA_22 : Step*22
  *     @arg IREF_CURRENT_STEP_DATA_23 : Step*23
  *     @arg IREF_CURRENT_STEP_DATA_24 : Step*24
  *     @arg IREF_CURRENT_STEP_DATA_25 : Step*25
  *     @arg IREF_CURRENT_STEP_DATA_26 : Step*26
  *     @arg IREF_CURRENT_STEP_DATA_27 : Step*27
  *     @arg IREF_CURRENT_STEP_DATA_28 : Step*28
  *     @arg IREF_CURRENT_STEP_DATA_29 : Step*29
  *     @arg IREF_CURRENT_STEP_DATA_30 : Step*30
  *     @arg IREF_CURRENT_STEP_DATA_31 : Step*31
  *     @arg IREF_CURRENT_STEP_DATA_32 : Step*32
  *     @arg IREF_CURRENT_STEP_DATA_33 : Step*33
  *     @arg IREF_CURRENT_STEP_DATA_34 : Step*34
  *     @arg IREF_CURRENT_STEP_DATA_35 : Step*35
  *     @arg IREF_CURRENT_STEP_DATA_36 : Step*36
  *     @arg IREF_CURRENT_STEP_DATA_37 : Step*37
  *     @arg IREF_CURRENT_STEP_DATA_38 : Step*38
  *     @arg IREF_CURRENT_STEP_DATA_39 : Step*39
  *     @arg IREF_CURRENT_STEP_DATA_40 : Step*40
  *     @arg IREF_CURRENT_STEP_DATA_41 : Step*41
  *     @arg IREF_CURRENT_STEP_DATA_42 : Step*42
  *     @arg IREF_CURRENT_STEP_DATA_43 : Step*43
  *     @arg IREF_CURRENT_STEP_DATA_44 : Step*44
  *     @arg IREF_CURRENT_STEP_DATA_45 : Step*45
  *     @arg IREF_CURRENT_STEP_DATA_46 : Step*46
  *     @arg IREF_CURRENT_STEP_DATA_47 : Step*47
  *     @arg IREF_CURRENT_STEP_DATA_48 : Step*48
  *     @arg IREF_CURRENT_STEP_DATA_49 : Step*49
  *     @arg IREF_CURRENT_STEP_DATA_50 : Step*50
  *     @arg IREF_CURRENT_STEP_DATA_51 : Step*51
  *     @arg IREF_CURRENT_STEP_DATA_52 : Step*52
  *     @arg IREF_CURRENT_STEP_DATA_53 : Step*53
  *     @arg IREF_CURRENT_STEP_DATA_54 : Step*54
  *     @arg IREF_CURRENT_STEP_DATA_55 : Step*55
  *     @arg IREF_CURRENT_STEP_DATA_56 : Step*56
  *     @arg IREF_CURRENT_STEP_DATA_57 : Step*57
  *     @arg IREF_CURRENT_STEP_DATA_58 : Step*58
  *     @arg IREF_CURRENT_STEP_DATA_59 : Step*59
  *     @arg IREF_CURRENT_STEP_DATA_60 : Step*60
  *     @arg IREF_CURRENT_STEP_DATA_61 : Step*61
  *     @arg IREF_CURRENT_STEP_DATA_62 : Step*62
  *     @arg IREF_CURRENT_STEP_DATA_63 : Step*63
  * @retval None
  */
void IVREF_IREFStepDataConfig(uint32_t IREFStepData)
{
    uint32_t temp = 0;
    /* Get CTLR value */
    temp = IVREF->CTLR;
    /* Clear Current step data bits */
    temp &= CTLR_CSDA_RESET;
    /* Set Current step data bits */
    temp |= IREFStepData;
    /* Write to CTLR */
    IVREF->CTLR = temp;
}

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
