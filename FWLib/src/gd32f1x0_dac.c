/**
  ******************************************************************************
  * @file    gd32f1x0_dac.c
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   DAC functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0_dac.h"
#include "gd32f1x0_rcc.h"

/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @defgroup DAC 
  * @brief DAC driver modules
  * @{
  */

/** @defgroup DAC_Private_Defines
  * @{
  */

#define CTLR_BITS_CLEAR                 ((uint32_t)0x0000003E)       /*!< CTLR register bits RESET */
#define ODR_OFFSET                      ((uint32_t)0x0000002C)       /*!< ODR register offset */
#ifdef GD32F170_190
#define SWTR_SET                        ((uint32_t)0x00000003)       /*!< SWTR SET */
#endif  /* GD32F170_190 */
#define DAC1_R12DHR_OFFSET              ((uint32_t)0x00000008)       /*!< DHR registers offsets */
#ifdef GD32F170_190
#define DAC2_R12DHR_OFFSET              ((uint32_t)0x00000014)       /*!< DAC2_R12DHR registers offsets */
#define DACD_R12DHR_OFFSET              ((uint32_t)0x00000020)       /*!< DACD_R12DHR registers offsets */
#endif  /* GD32F170_190 */

/**
  * @}
  */

/** @defgroup DAC_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the DAC peripheral registers.
  * @param  DAC_InitParaStruct: DAC_InitPara structure that contains the
  *   configuration information for the selected DAC.
  * @retval None
  */
void DAC_DeInit(DAC_InitPara* DAC_InitParaStruct)
{
    /* Enable DAC reset state */
    RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_DACRST, ENABLE);
    /* Release DAC from reset state */
    RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_DACRST, DISABLE);
    /* Initialize the DAC_Trigger member */
    DAC_InitParaStruct->DAC_Trigger = DAC_TRIGGER_NONE;
    /* Initialize the DAC_OutputBuffer member */
    DAC_InitParaStruct->DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
}

/**
  * @brief  Initialize the DAC peripheral.
  * @param  DACx: the selected DAC.
  *   This parameter can be one of the following values:
  *     @arg DAC1: DAC1 is selected
  *     @arg DAC2: DAC2 is selected
  * @param  DAC_InitStruct: DAC_InitTypeDef structure
  * @retval None
  */
void DAC_Init(uint32_t DACx, DAC_InitPara* DAC_InitParaStruct)
{
    uint32_t temp1 = 0, temp2 = 0;

    /* DAC CTLR Configuration */
    /* Get the DAC CTLR value */
    temp1 = DAC->CTLR;

    /* Clear DBOFF, DTEN and DTSEL bits */
    temp1 &= ~(CTLR_BITS_CLEAR<< DACx);
    /* Configure for the DAC: buffer output, trigger*/
    /* Set DTSEL and DTEN bits according to DAC_Trigger */
    /* Set DBOFF bit according to DAC_OutputBuffer */
    temp2 = (DAC_InitParaStruct->DAC_Trigger | DAC_InitParaStruct->DAC_OutputBuffer);
    /* Calculate CTLR register value */
    temp1 |= temp2<< DACx;

    /* Write to DAC CTLR */
    DAC->CTLR = temp1;
}

/**
  * @brief  Enable or disable the DAC.
  * @param  DACx: the selected DAC.
  *   This parameter can be one of the following values:
  *     @arg DAC1: DAC1 is selected
  *     @arg DAC2: DAC2 is selected
  * @param  NewValue: New value of the DAC Number.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_Enable(uint32_t DACx, TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable the selected DAC */
        DAC->CTLR |= (DAC_CTLR_DEN1<< DACx);
    }
    else
    {
        /* Disable the selected DAC */
        DAC->CTLR &= ~(DAC_CTLR_DEN1 << DACx);
    }
}

/**
  * @brief  Enable or disable the selected DAC software trigger.
  * @param  DACx: the selected DAC.
  *   This parameter can be one of the following values:
  *     @arg DAC1: DAC1 is selected
  *     @arg DAC2: DAC2 is selected
  * @param  NewValue: New value of the selected DACx software trigger.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_SoftwareTrigger_Enable(uint32_t DACx, TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable software trigger for DACx */
        DAC->SWTR |= (uint32_t)DAC_SWTR_SWTR1<< (DACx >> 4);
    }
    else
    {
        /* Disable software trigger for DACx */
        DAC->SWTR &= ~((uint32_t)DAC_SWTR_SWTR1<< (DACx >> 4));
    }
}

#ifdef GD32F170_190
/**
  * @brief  Enable or disable simultaneously the two DACs software
  *   triggers.
  * @param  NewValue: new value of the DACs software triggers.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_DualSoftwareTrigger_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable software trigger */
        DAC->SWTR |= SWTR_SET ;
    }
    else
    {
        /* Disable software trigger */
        DAC->SWTR &= ~SWTR_SET;
    }
}
#endif  /* GD32F170_190 */

/**
  * @brief  Set the specified data holding register value for DAC1.
  * @param  DAC_Align: the data alignment for DAC1.
  *   This parameter can be one of the following values:
  *     @arg DAC_ALIGN_8B_R: select 8bit right data alignment
  *     @arg DAC_ALIGN_12B_L: select 12bit left data alignment
  *     @arg DAC_ALIGN_12B_R: select 12bit right data alignment
  * @param  Data: Data to be loaded.
  * @retval None
  */
void DAC_SetDAC1Data(uint32_t DAC_Align, uint16_t Data)
{
    __IO uint32_t temp = 0;
    temp = (uint32_t)DAC_BASE;
    temp += DAC1_R12DHR_OFFSET + DAC_Align;
    /* Set the DAC1 */
    *(__IO uint32_t *) temp = Data;
}

#ifdef GD32F170_190
/**
  * @brief  Set the specified data holding register value for DAC2.
  * @param  DAC_Align: the data alignment for DAC2.
  *   This parameter can be one of the following values:
  *     @arg DAC_ALIGN_8B_R: select 8bit right data alignment
  *     @arg DAC_ALIGN_12B_L: select 12bit left data alignment
  *     @arg DAC_ALIGN_12B_R: select 12bit right data alignment
  * @param  Data: Data to be loaded.
  * @retval None
  */
void DAC_SetDAC2Data(uint32_t DAC_Align, uint16_t Data)
{
    __IO uint32_t temp = 0;

    temp = (uint32_t)DAC_BASE;
    temp += DAC2_R12DHR_OFFSET + DAC_Align;
    /* Set the DAC2 */
    *(__IO uint32_t *) temp = Data;
}
#endif  /* GD32F170_190 */

#ifdef GD32F170_190
/**
  * @brief  Set the specified data for dual DAC
  * @param  DAC_Align: the data alignment for dual DAC.
  *   This parameter can be one of the following values:
  *     @arg DAC_Align_8b_R: select 8bit right data alignment
  *     @arg DAC_Align_12b_L: select 12bit left data alignment
  *     @arg DAC_Align_12b_R: select 12bit right data alignment
  * @param  Data2: Data for DAC2.
  * @param  Data1: Data for DAC1.
  * @retval None
  */
void DAC_SetDualDACData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1)
{
    uint32_t data = 0, temp = 0;

    /* set dual DAC data holding register value */
    if (DAC_Align == DAC_ALIGN_8B_R)
    {
        data = ((uint32_t)Data2 << 8) | Data1;
    }
    else
    {
        data = ((uint32_t)Data2 << 16) | Data1;
    }

    temp = (uint32_t)DAC_BASE;
    temp += DACD_R12DHR_OFFSET + DAC_Align;

    /* Set the dual DAC selected data holding register */
    *(__IO uint32_t *)temp = data;
}
#endif  /* GD32F170_190 */

/**
  * @brief  Return the last data output value.
  * @param  DACx: the selected DAC.
  *   This parameter can be one of the following values:
  *     @arg DAC1: DAC1 is selected
  *     @arg DAC2: DAC2 is selected
  * @retval The DAC data output value.
  */
uint16_t DAC_GetDataOutputValue(uint32_t DACx)
{
    __IO uint32_t temp = 0;

    temp = (uint32_t) DAC_BASE;
    temp += ODR_OFFSET+ ((uint32_t)DACx >> 2);

    /* Returns the DACx data */
    return (uint16_t) (*(__IO uint32_t*) temp);
}

/**
  * @brief  Enable or disable DMA request.
  * @param  DACx: the selected DAC.
  *   This parameter can be one of the following values:
  *     @arg DAC1: DAC1 is selected
  *     @arg DAC2: DAC2 is selected
  * @param  NewValue: New value of the selected DAC DMA request.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_DMA_Enable(uint32_t DACx, TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable DMA request */
        DAC->CTLR |= (DAC_CTLR_DDMAEN1<< DACx);
    }
    else
    {
        /* Disable DMA request */
        DAC->CTLR &= ~(DAC_CTLR_DDMAEN1<< DACx);
    }
}

/**
  * @brief  Enable or disable the specified DAC interrupts.
  * @param  DACx: the selected DAC.
  *   This parameter can be one of the following values:
  *     @arg DAC1: DAC1 is selected
  *     @arg DAC2: DAC2 is selected
  * @param  NewValue: Alternative state of the specified DAC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_INTConfig(uint32_t DACx, TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable the DACx DMAUDR interrupts */
        DAC->CTLR |=  (DAC_INT_DMAUDR << DACx);
    }
    else
    {
        /* Disable the DACx DMAUDR interrupts */
        DAC->CTLR &= (~(uint32_t)(DAC_INT_DMAUDR << DACx));
    }
}

/**
  * @brief  Check the specified DAC flag.
  * @param  DACx: the selected DAC.
  *   This parameter can be one of the following values:
  *     @arg DAC1: DAC1 is selected
  *     @arg DAC2: DAC2 is selected
  * @retval The new state of DAC_FLAG (SET or RESET).
  */
TypeState DAC_GetBitState(uint32_t DACx)
{
    /* Check the status of DAC DMAUDR flag */
    if ((DAC->STR & (DAC_STR_DDMA1UDR<< DACx)) != (uint8_t)RESET)
    {
        /* DAC_FLAG is set */
        return SET;
    }
    else
    {
        /* DAC_FLAG is reset */
        return RESET;
    }
}

/**
  * @brief  Clear the DAC DMAUDR flags.
  * @param  DACx: the selected DAC.
  *   This parameter can be one of the following values:
  *     @arg DAC1: DAC1 is selected
  *     @arg DAC2: DAC2 is selected
  * @retval None
  */
void DAC_ClearBitState(uint32_t DACx)
{
    /* Clear the DAC DMAUDR flags */
    DAC->STR = (DAC_STR_DDMA1UDR<< DACx);
}

/**
  * @brief  Check the DAC DMAUDR interrupt.
  * @param  DACx: the selected DAC.
  *   This parameter can be one of the following values:
  *     @arg DAC1: DAC1 is selected
  *     @arg DAC2: DAC2 is selected
  * @retval The new state of DAC_INT (SET or RESET).
  */
TypeState DAC_GetIntState(uint32_t DACx)
{
    /* Check the status of the specified DAC interrupt */
    if (((DAC->STR & (DAC_STR_DDMA1UDR<< DACx)) != (uint32_t)RESET) && (DAC->CTLR & (DAC_STR_DDMA1UDR<< DACx)))
    {
        /* DAC_INT is set */
        return SET;
    }
    else
    {
        /* DAC_INT is reset */
        return RESET;
    }
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

/******************* (C) COPYRIGHT 2016 GIGADEVICE *****END OF FILE****/
