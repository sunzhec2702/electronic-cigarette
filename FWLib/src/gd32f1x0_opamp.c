/**
  ******************************************************************************
  * @file    gd32f1x0_opamp.c
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   OPAMP functions of the firmware library.
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0_opamp.h"
#include "gd32f1x0_rcc.h"

 #ifdef GD32F170_190
/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @defgroup OPAMP 
  * @brief OPAMP driver modules
  * @{
  */

/** @defgroup OPAMP_Private_Defines
  * @{
  */

#define OTR_OA1_TRIM_LOW_RESET          ((uint32_t)0xFFFFFFE0)       /*!< OPAMP OTR OA1 TRIM LOW Reset */
#define OTR_OA1_TRIM_HIGH_RESET         ((uint32_t)0xFFFFFC1F)       /*!< OPAMP OTR OA1 TRIM HIGH Reset */
#define OTR_OA2_TRIM_LOW_RESET          ((uint32_t)0xFFFF83FF)       /*!< OPAMP OTR OA2 TRIM LOW Reset */
#define OTR_OA2_TRIM_HIGH_RESET         ((uint32_t)0xFFF07FFF)       /*!< OPAMP OTR OA2 TRIM HIGH Reset */
#define OTR_OA3_TRIM_LOW_RESET          ((uint32_t)0xFE0FFFFF)       /*!< OPAMP OTR OA3 TRIM LOW Reset */
#define OTR_OA3_TRIM_HIGH_RESET         ((uint32_t)0xC1FFFFFF)       /*!< OPAMP OTR OA3 TRIM HIGH Reset */
#define LPOTR_OA1_TRIM_LP_LOW_RESET     ((uint32_t)0xFFFFFFE0)       /*!< OPAMP LPOTR OA1 TRIM LP LOW Reset */
#define LPOTR_OA1_TRIM_LP_HIGH_RESET    ((uint32_t)0xFFFFFC1F)       /*!< OPAMP LPOTR OA1 TRIM LP HIGH Reset */
#define LPOTR_OA2_TRIM_LP_LOW_RESET     ((uint32_t)0xFFFF83FF)       /*!< OPAMP LPOTR OA2 TRIM LP LOW Reset */
#define LPOTR_OA2_TRIM_LP_HIGH_RESET    ((uint32_t)0xFFF07FFF)       /*!< OPAMP LPOTR OA2 TRIM LP HIGH Reset */
#define LPOTR_OA3_TRIM_LP_LOW_RESET     ((uint32_t)0xFE0FFFFF)       /*!< OPAMP LPOTR OA3 TRIM LP LOW Reset */
#define LPOTR_OA3_TRIM_LP_HIGH_RESET    ((uint32_t)0xC1FFFFFF)       /*!< OPAMP LPOTR OA3 TRIM LP HIGH Reset */

/**
  * @}
  */

/** @defgroup OPAMP_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the OPAMPs register to its default reset value.
  * @param  None.
  * @retval None.
  */
void OPAMP_DeInit(void)
{
    /*!< Set OPAMP_CTLR register to reset value */
    OPAMP->CTLR = 0x00010101;

    /*!< Set OPAMP_OTR register to reset value */
    OPAMP->OTR = 0x00000000;

    /*!< Set OPAMP_LPOTR register to reset value */
    OPAMP->LPOTR = 0x00000000;
}

/**
  * @brief  Close or Open the OPAMPx switches.
  * @param  OPAMP_OPAMPxSy: selects the OPAMPx switch.
  *   This parameter can be any combinations of the following values:
  *     @arg OPAMP_T3OPA1: used to connect internally OPAMP1 output to 
  *                               OPAMP1 negative input (internal follower)
  *     @arg OPAMP_S1OPA1: used to connect PA2 to OPAMP1 negative input
  *     @arg OPAMP_S2OPA1: used to connect PA1 to OPAMP1 positive input
  *     @arg OPAMP_S3OPA1: used to connect DAC_OUT1 to OPAMP1 positive input
  *     @arg OPAMP_T3OPA2: used to connect internally OPAMP2 output to 
  *                               OPAMP2 negative input (internal follower)
  *     @arg OPAMP_S1OPA2: used to connect PA7 to OPAMP2 negative input
  *     @arg OPAMP_S2OPA2: used to connect PA6 to OPAMP2 positive input
  *     @arg OPAMP_S3OPA2: used to connect DAC_OUT1 to OPAMP2 positive input
  *     @arg OPAMP_S4OPA2: used to connect DAC_OUT2 to OPAMP2 positive input
  *     @arg OPAMP_T3OPA3: used to connect internally OPAMP3 output to 
  *                               OPAMP3 negative input (internal follower)
  *     @arg OPAMP_S1OPA3: used to connect PC2 to OPAMP3 negative input
  *     @arg OPAMP_S2OPA3: used to connect PC1 to OPAMP3 positive input
  *     @arg OPAMP_S3OPA3: used to connect DAC_OUT1 to OPAMP3 positive input
  * @param  NewValue: New state of the OPAMP switch.
  *   This parameter can be:ENABLE or DISABLE
  * @note OPAMP_S3OPA2 and OPAMP_S4OPA2 mustn't be closed together.
  * @retval None
  */
void OPAMP_SwitchEnable(uint32_t OPAMP_OPAMPxSy, TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable the OPAMP_OPAMPxSy */
        OPAMP->CTLR |= (uint32_t) OPAMP_OPAMPxSy;
    }
    else
    {
        /* Disable the OPAMP_OPAMPxSy */
        OPAMP->CTLR &= (~(uint32_t)OPAMP_OPAMPxSy);
    }
}

/**
  * @brief  Enable or disable the OPAMP peripheral.
  * @param  OPAMPx: the selected OPAMP.
  *   This parameter can be one of the following values:
  *     @arg OPAMP1: OPAMP1 is selected
  *     @arg OPAMP2: OPAMP2 is selected
  *     @arg OPAMP3: OPAMP3 is selected
  * @param  NewValue: new state of the selected OPAMP peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void OPAMP_Enable(uint32_t OPAMPx, TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable the OPAMPx */
        OPAMP->CTLR &= (~(uint32_t) OPAMPx);
    }
    else
    {
        /* Disable the OPAMPx */
        OPAMP->CTLR |= (uint32_t) OPAMPx;
    }
}

/**
  * @brief  Enable or disable the low power mode for OPAMP peripheral.
  * @param  OPAMPx: the selected OPAMP.
  *   This parameter can be one of the following values:
  *     @arg OPAMP1: OPAMP1 is selected
  *     @arg OPAMP2: OPAMP2 is selected
  *     @arg OPAMP3: OPAMP3 is selected
  * @param  NewValue: new low power state of the selected OPAMP peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void OPAMP_LowPowerEnable(uint32_t OPAMPx, TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Set the OPAMPx in low power mode */
        OPAMP->CTLR |= (uint32_t) (OPAMPx << 7);
    }
    else
    {
        /* Disable the OPAMPx in low power mode */
        OPAMP->CTLR &= (~(uint32_t) (OPAMPx << 7));
    }
}

/**
  * @brief  Select the OPAMP power range.
  * @note   The OPAMP power range selection must be performed while OPAMPs are powered down.
  * @param  OPAMP_PowerRange: the selected OPAMP power range. 
  *   This parameter can be one of the following values:
  *     @arg OPAMP_OPARANGE_LOW: Low power range is selected (VDDA is lower than 3.3V).
  *     @arg OPAMP_OPARANGE_HIGH: High power range is selected (VDDA is higher than 3.3V).
  * @retval None
  */
void OPAMP_PowerRangeConfig(uint32_t OPAMP_PowerRange)
{
    /* Reset the OPAMP power range bit */
    OPAMP->CTLR &= (~(uint32_t) (OPAMP_CTLR_OPA_RANGE));

    /* Select the OPAMP power range */
    OPAMP->CTLR |= OPAMP_PowerRange;
}

/**
  * @brief  Config the trimming mode.
  * @param  OPAMP_TrimMode: the selected offset trimming mode.
  *   This parameter  can be one of the following values:
  *     @arg OPAMP_OTR_TRIM_FACTORY: factory trimming values are used for offset
  *                                  calibration.
  *     @arg OPAMP_OTR_TRIM_USER: user trimming values are used for offset
  *                               calibration.
  * @note When OffsetTrimming_User is selected, use OPAMP_OffsetTrimValueConfig()
  *       function or OPAMP_OffsetTrimValueLowPowerConfig() function to adjust
  *       trimming value.
  * @retval None
  */
void OPAMP_OffsetTrimModeConfig(uint32_t OPAMP_TrimMode)
{
    /* Reset the OPAMP offset trimming mode bit */
    OPAMP->OTR &= (~(uint32_t) (OPAMP_OTR_OT_USER));

    /* Select the OPAMP offset trimming mode */
    OPAMP->OTR |= OPAMP_TrimMode;
}

/**
  * @brief  Configure the trimming value of OPAMPx in normal mode.
  * @param  OPAMPx: the selected OPAMP. 
  *   This parameter can be one of the following values:
  *         @arg OPAMP1: OPAMP1 is selected.
  *         @arg OPAMP2: OPAMP2 is selected.
  *         @arg OPAMP3: OPAMP3 is selected
  * @param  OPAMP_Input: the selected OPAMP input.
  *   This parameter can be one of the following values:
  *         @arg OPAMP_INPUT_N: NMOS input is selected to configure the trimming value.
  *         @arg OPAMP_INPUT_P: PMOS input is selected to configure the trimming value.
  * @param  OPAMP_TrimValue: the trimming value. This parameter can be any value lower
  *         or equal to 0x0000001F.
  * @retval None
  */
void OPAMP_OffsetTrimValueConfig(uint32_t OPAMPx, uint32_t OPAMP_Input, uint32_t OPAMP_Trimvalue)
{
    uint32_t temp = 0,temp1 = 0;
    /* Get the OPAMP_CTLR value */
    temp1 = OPAMP->CTLR;

    /* Get the OPAMP_OTR value */
    temp = OPAMP->OTR;

    if(OPAMPx == OPAMP1)
    {
        /* Reset the OPAMP1 input */
        temp1 &= (uint32_t)~(OPAMP_CTLR_OPA1CAL_L | OPAMP_CTLR_OPA1CAL_H);
        /* Set the OPAMP1 input */
        temp1 |= OPAMP_Input;

        if(OPAMP_Input == OPAMP_INPUT_P)
        {
            /* Reset the offset trim value of OPAMP1 PMOS */
            temp &= (OTR_OA1_TRIM_LOW_RESET);
            /* Set the new offset trim value of OPAMP1 PMOS */
            temp |= (OPAMP_Trimvalue);
        }
        else
        {
            /* Reset the offset trim value of OPAMP1 NMOS */
            temp &= (OTR_OA1_TRIM_HIGH_RESET);
            /* Set the new offset trim value of OPAMP1 NMOS */
            temp |= (OPAMP_Trimvalue<<5);
        }
    }
    else if (OPAMPx == OPAMP2)
    {
        /* Reset the OPAMP2 input */
        temp1 &= (uint32_t)~(OPAMP_CTLR_OPA2CAL_L | OPAMP_CTLR_OPA2CAL_H);
        /* Set the OPAMP2 input */
        temp1 |= (uint32_t)(OPAMP_Input<<8);

        if(OPAMP_Input == OPAMP_INPUT_P)
        {
            /* Reset the offset trim value of OPAMP2 PMOS */
            temp &= (OTR_OA2_TRIM_LOW_RESET);
            /* Set the new offset trim value of OPAMP2 PMOS */
            temp |= (OPAMP_Trimvalue<<10);
        }
        else
        {
            /* Reset the offset trim value of OPAMP2 NMOS */
            temp &= (OTR_OA2_TRIM_HIGH_RESET);
            /* Set the new offset trim value of OPAMP2 NMOS */
            temp |= (OPAMP_Trimvalue<<15);
        }
    }
    else
    {
        /* Reset the OPAMP3 input */
        temp1 &= (uint32_t)~(OPAMP_CTLR_OPA3CAL_L | OPAMP_CTLR_OPA3CAL_H);
        /* Set the OPAMP3 input */
        temp1 |= (uint32_t)(OPAMP_Input<<16);

        if(OPAMP_Input == OPAMP_INPUT_P)
        {
            /* Reset the offset trim value of OPAMP3 PMOS */
            temp &= (OTR_OA3_TRIM_LOW_RESET);
            /* Set the new offset trim value of OPAMP3 PMOS */
            temp |= (OPAMP_Trimvalue<<20);
        }
        else
        {
            /* Reset the offset trim value of OPAMP3 NMOS */
            temp &= (OTR_OA3_TRIM_HIGH_RESET);
            /* Set the new offset trim value of OPAMP3 NMOS */
            temp |= (OPAMP_Trimvalue<<25);
        }
    }

    /* Set the OPAMP_CTLR register */
    OPAMP->CTLR = temp1;

    /* Set the OPAMP_OTR register */
    OPAMP->OTR = temp;
}

/**
  * @brief  Configure the trimming value of OPAMPx in low power mode.
  * @param  OPAMPx: the selected OPAMP. 
  *   This parameter can be one of the following values:
  *         @arg OPAMP1: OPAMP1 is selected.
  *         @arg OPAMP2: OPAMP2 is selected.
  *         @arg OPAMP3: OPAMP3 is selected.
  * @param  OPAMP_Input: the selected OPAMP input.
  *   This parameter can be one of the following values:
  *         @arg OPAMP_INPUT_N: NMOS input is selected.
  *         @arg OPAMP_INPUT_P: PMOS input is selected.
  * @param  OPAMP_TrimValue: the trimming value. 
  *    This parameter can be any value lower or equal to 0x0000001F.
  * @retval None
  */
void OPAMP_OffsetTrimValueLowPowerConfig(uint32_t OPAMPx, uint32_t OPAMP_Input, uint32_t OPAMP_TrimValue)
{
    uint32_t temp = 0,temp1 = 0;

    /* Get the OPAMP_CTLR value */
    temp1 = OPAMP->CTLR;

    /* Get the OPAMP_LPOTR value */
    temp = OPAMP->LPOTR;

    if(OPAMPx == OPAMP1)
    {
        /* Reset the OPAMP1 input */
        temp1 &= (uint32_t)~(OPAMP_CTLR_OPA1CAL_L | OPAMP_CTLR_OPA1CAL_H);
        /* Set the OPAMP1 input */
        temp1 |= OPAMP_Input;

        if(OPAMP_Input == OPAMP_INPUT_P)
        {
            /* Reset the offset trim value of OPAMP1 PMOS */
            temp &= (LPOTR_OA1_TRIM_LP_LOW_RESET);
            /* Set the new offset trim value of OPAMP2 PMOS */
            temp |= (OPAMP_TrimValue);
        }
        else
        {
            /* Reset the offset trim value of OPAMP1 NMOS */
            temp &= (LPOTR_OA1_TRIM_LP_HIGH_RESET);
            /* Set the new offset trim value of OPAMP2 NMOS */
            temp |= (OPAMP_TrimValue<<5);
        }
    }
    else if (OPAMPx == OPAMP2)
    {
        /* Reset the OPAMP2 input */
        temp1 &= (uint32_t)~(OPAMP_CTLR_OPA2CAL_L | OPAMP_CTLR_OPA2CAL_H);
        /* Set the OPAMP2 input */
        temp1 |= (uint32_t)(OPAMP_Input<<8);

        if(OPAMP_Input == OPAMP_INPUT_P)
        {
            /* Reset the offset trim value of OPAMP2 PMOS */
            temp &= (LPOTR_OA2_TRIM_LP_LOW_RESET);
            /* Set the new offset trim value of OPAMP2 PMOS */
            temp |= (OPAMP_TrimValue<<10);
        }
        else
        {
            /* Reset the offset trim value of OPAMP2 NMOS */
            temp &= (LPOTR_OA2_TRIM_LP_HIGH_RESET);
            /* Set the new offset trim value of OPAMP2 NMOS */
            temp |= (OPAMP_TrimValue<<15);
        }
    }
    else
    {
        /* Reset the OPAMP3 input */
        temp1 &= (uint32_t)~(OPAMP_CTLR_OPA3CAL_L | OPAMP_CTLR_OPA3CAL_H);
        /* Set the OPAMP3 input */
        temp1 |= (uint32_t)(OPAMP_Input<<16);

        if(OPAMP_Input == OPAMP_INPUT_P)
        {
            /* Reset the offset trim value of OPAMP3 PMOS */
            temp &= (LPOTR_OA3_TRIM_LP_LOW_RESET);
            /* Set the new offset trim value of OPAMP3 PMOS */
            temp |= (OPAMP_TrimValue<<20);
        }
        else
        {
            /* Reset the offset trim value of OPAMP3 NMOS */
            temp &= (LPOTR_OA3_TRIM_LP_HIGH_RESET);
            /* Set the new offset trim value of OPAMP3 NMOS */
            temp |= (OPAMP_TrimValue<<25);
        }
    }

    /* Set the OPAMP_CTLR register */
    OPAMP->CTLR = temp1;

    /* Set the OPAMP_LPOTR register */
    OPAMP->LPOTR = temp;
}

/**
  * @brief  Checks OPAMPx calibration flag.
  * @note   User should wait until calibration flag change the value when changing
  *         the trimming value.
  * @param  OPAMPx: the selected OPAMP. 
  *   This parameter can be one of the following values:
  *     @arg OPAMP1: OPAMP1 is selected.
  *     @arg OPAMP2: OPAMP2 is selected.
  *     @arg OPAMP3: OPAMP3 is selected.
  * @retval The new state of the OPAMP calibration flag (SET or RESET).
  */
TypeState OPAMP_GetBitState(uint32_t OPAMPx)
{
    TypeState bitstatus = RESET;
    uint32_t temp = 0;

    /* Get the CTLR register value */
    temp = OPAMP->CTLR;

    /* OPAMP1 is selected */
    if(OPAMPx == OPAMP1)
    {
        /*  OPAMP1 CAL bit State */
        if ((temp & OPAMP_CTLR_OPA1CALOUT) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    /* OPAMP2 is selected */
    else if(OPAMPx == OPAMP2)
    {
        /* OPAMP2 CAL bit status */
        if ((temp & OPAMP_CTLR_OPA2CALOUT) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    else
    {
        /* OPAMP3 CAL bit status */
        if ((temp & OPAMP_CTLR_OPA3CALOUT) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    return bitstatus;
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
