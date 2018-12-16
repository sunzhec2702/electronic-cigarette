/**
  ******************************************************************************
  * @file    gd32f1x0_adc.c
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   ADC functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0_adc.h"
#include "gd32f1x0_rcc.h"

/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @defgroup ADC 
  * @brief ADC driver modules
  * @{
  */

/** @defgroup ADC_Private_Defines
  * @{
  */

#define CTLR1_DISNUM_RESET             ((uint32_t)0xFFFF1FFF)        /*!< ADC CTLR1_DISNUM mask */
#define CTLR1_DISRC_SET                ((uint32_t)0x00000800)        /*!< ADC CTLR1_DISRC mask */
#define CTLR1_ICA_SET                  ((uint32_t)0x00000400)        /*!< ADC CTLR1_ICA mask */
#define CTLR1_DISIC_SET                ((uint32_t)0x00001000)        /*!< ADC CTLR1_DISIC mask */
#define CTLR1_AWCS_RESET               ((uint32_t)0xFFFFFFE0)        /*!< ADC CTLR1_AWCS mask */
#define CTLR1_AWDMODE_RESET            ((uint32_t)0xFF3FFDFF)        /*!< ADC CTLR1_AWDMode mask */
#ifdef GD32F170_190
#define CTLR1_DRES_RESET               ((uint32_t)0xFCFFFFFF)        /*!< ADC CTLR1_DRES mask */
#endif /* GD32F170_190 */
#define CTLR1_BITS_CLEAR               ((uint32_t)0xFFFFFEFF)        /*!< ADC CTLR1 register mask */

#define CTLR2_ADCON_SET                ((uint32_t)0x00000001)        /*!< ADC CTLR2_ADCON mask */
#define CTLR2_DMA_SET                  ((uint32_t)0x00000100)        /*!< ADC CTLR2_DMA mask */
#define CTLR2_RSTCLB_SET               ((uint32_t)0x00000008)        /*!< ADC CTLR2_RSTCLB mask */
#define CTLR2_CLB_SET                  ((uint32_t)0x00000004)        /*!< ADC CTLR2_CLB mask */
#define CTLR2_SWRCST_SET               ((uint32_t)0x00400000)        /*!< ADC CTLR2_SWRCST mask */
#define CTLR2_ETERC_SET                ((uint32_t)0x00100000)        /*!< ADC CTLR2_ETERC mask */
#define CTLR2_ETERC_SWRCST_SET         ((uint32_t)0x00500000)        /*!< ADC CTLR2_ETERC_SWRCST mask */
#define CTLR2_ETSIC_RESET              ((uint32_t)0xFFFF8FFF)        /*!< ADC CTLR2_ETSIC mask */
#define CTLR2_ETEIC_SET                ((uint32_t)0x00008000)        /*!< ADC CTLR2_ETEIC mask */
#define CTLR2_SWICST_SET               ((uint32_t)0x00200000)        /*!< ADC CTLR2_SWICST mask */
#define CTLR2_ETEIC_SWICST_SET         ((uint32_t)0x00208000)        /*!< ADC CTLR2_ETEIC_SWICST mask */
#define CTLR2_TSVREN_SET               ((uint32_t)0x00800000)        /*!< ADC CTLR2_TSVREN mask */
#define CTLR2_VBATEN_SET               ((uint32_t)0x01000000)        /*!< ADC CTLR2_VBATEN mask */
#define CTLR2_BITS_CLEAR               ((uint32_t)0xFFF1F7FD)        /*!< CTLR2 register mask */

#define RSQ3_RSQ_SET                   ((uint32_t)0x0000001F)        /*!< ADC RSQ3 mask */
#define RSQ2_RSQ_SET                   ((uint32_t)0x0000001F)        /*!< ADC RSQ2 mask */
#define RSQ1_RSQ_SET                   ((uint32_t)0x0000001F)        /*!< ADC RSQ1 mask */
#define RSQ1_BITS_CLEAR                ((uint32_t)0xFF0FFFFF)        /*!< RSQ1 register mask */

#define ISQ_ISQ_SET                    ((uint32_t)0x0000001F)        /*!< ADC ISQx mask */
#define ISQ_IL_SET                     ((uint32_t)0x00300000)        /*!< ADC IL mask */

#define SPT1_SPT_SET                   ((uint32_t)0x00000007)        /*!< ADC SPT1 mask */
#define SPT2_SPT_SET                   ((uint32_t)0x00000007)        /*!< ADC SPT2 mask */

#define IDTR_OFFSET                    ((uint8_t)0x28)               /*!< ADC IDTRx registers offset */

#define RDTR_ADDRESS                   ((uint32_t)0x4001244C)        /*!< ADC1 RDTR register base address */

#ifdef GD32F170_190
#define OVSCR_OVSS_RESET               ((uint32_t)0xFFFFFE1F)        /*!< ADC OVSCR_OVSS mask */
#define OVSCR_OVSR_RESET               ((uint32_t)0xFFFFFFE3)        /*!< ADC OVSCR_OVSR mask */
#define OVSCR_TOVS_SET                 ((uint32_t)0x00000200)        /*!< ADC OVSCR_TOVS mask */
#define OVSCR_OVSE_SET                 ((uint32_t)0x00000001)        /*!< ADC OVSCR_OVSE mask */
#endif /* GD32F170_190 */
/**
  * @}
  */

/** @defgroup ADC_Private_Functions
  * @{
  */

/**
  * @brief  Reset the ADC interface and init the sturct ADC_InitPara .
  * @param  ADC_InitParaStruct : the sturct ADC_InitPara pointer.
  * @retval None
  */
void ADC_DeInit(ADC_InitPara* ADC_InitParaStruct)
{
    /* Enable ADC1 reset state */
    RCC_APB2PeriphReset_Enable(RCC_APB2PERIPH_ADC1RST, ENABLE);
    /* Release ADC1 from reset state */
    RCC_APB2PeriphReset_Enable(RCC_APB2PERIPH_ADC1RST, DISABLE);
    /* Reset ADC1 init structure parameters values */
    /* Initialize the ADC_Mode_Scan member,disable scan mode */
    ADC_InitParaStruct->ADC_Mode_Scan = DISABLE;
    /* Initialize the ADC_Mode_Continuous member,disable continuous mode */
    ADC_InitParaStruct->ADC_Mode_Continuous = DISABLE;
    /* Initialize the ADC_Trig_External member,choose T1 CC1 as external trigger */
    ADC_InitParaStruct->ADC_Trig_External = ADC_EXTERNAL_TRIGGER_MODE_T1_CC1;
    /* Initialize the ADC_Data_Align member,specifies the ADC data alignment right */
    ADC_InitParaStruct->ADC_Data_Align = ADC_DATAALIGN_RIGHT;
    /* Initialize the ADC_Channel_Number member,only 1 channel */
    ADC_InitParaStruct->ADC_Channel_Number = 1;
}

/**
  * @brief  Initialize the ADC1 interface parameters.
  * @param  ADC_InitParaStruct: the sturct ADC_InitPara pointer.
  * @retval None
  */
void ADC_Init(ADC_InitPara* ADC_InitParaStruct)
{
    uint32_t temp1 = 0;
    uint8_t temp2 = 0;
    /*---------------------------- ADC1 CTLR1 Configuration -----------------*/
    /* Get the ADC1 CTLR1 previous value */
    temp1 = ADC1->CTLR1;
    /* Clear SM bits */
    temp1 &= CTLR1_BITS_CLEAR;
    /* Configure ADC1: scan conversion mode */
    /* Configure SCAN bit according to ADC_Mode_Scan value */
    temp1 |= ((uint32_t)ADC_InitParaStruct->ADC_Mode_Scan << 8);
    /* Write new value to ADC1 CTLR1 */
    ADC1->CTLR1 = temp1;

    /*---------------------------- ADC1 CTLR2 Configuration -----------------*/
    /* Get the ADC1 CTLR2 previous value */
    temp1 = ADC1->CTLR2;
    /* Clear CTN, DAL and ETSRC bits */
    temp1 &= CTLR2_BITS_CLEAR;
    /* Configure ADC1: external trigger mode select and continuous conversion mode */
    /* Configure DAL bit according to ADC_Data_Align value */
    /* Configure ETSRC bits according to ADC_Trig_External value */
    /* Configure CTN bit according to ADC_Mode_Continuous value */
    temp1 |= (uint32_t)(ADC_InitParaStruct->ADC_Data_Align | ADC_InitParaStruct->ADC_Trig_External |
            ((uint32_t)ADC_InitParaStruct->ADC_Mode_Continuous << 1));
    /* Write new value to ADC1 CTLR2 */
    ADC1->CTLR2 = temp1;

    /*---------------------------- ADC1 RSQ1 Configuration -----------------*/
    /* Get the ADC1 RSQ1 previous value */
    temp1 = ADC1->RSQ1;
    /* Clear RL bits */
    temp1 &= RSQ1_BITS_CLEAR;
    /* Configure ADC1: regular channel sequence length */
    /* Configure RL bits according to ADC_Channel_Number value */
    temp2 |= (uint8_t) (ADC_InitParaStruct->ADC_Channel_Number - (uint8_t)1);
    temp1 |= (uint32_t)temp2 << 20;
    /* Write new value to ADC1 RSQ1 */
    ADC1->RSQ1 = temp1;
}

/**
  * @brief  Enable or disable the ADC1 interface.
  * @param  NewValue: New state of the ADC1 interface.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable the ADC1 interface */
        ADC1->CTLR2 |= CTLR2_ADCON_SET;
    }
    else
    {
        /* Disable the ADC1 interface */
        ADC1->CTLR2 &= ~CTLR2_ADCON_SET;
    }
}

/**
  * @brief  Enable or disable the ADC1 DMA request.
  * @param  NewValue: New state of ADC1 DMA transfer.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_DMA_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable ADC1 DMA request */
        ADC1->CTLR2 |= CTLR2_DMA_SET;
    }
    else
    {
        /* Disable ADC1 DMA request */
        ADC1->CTLR2 &= ~CTLR2_DMA_SET;
    }
}

/**
  * @brief  Enable or disable the specified ADC1 interrupts.
  * @param  ADC_INT: Specifies ADC1 interrupt sources.
  *   This parameter can be any combination of the following values:
  *     @arg ADC_INT_EOC: Regular conversion over interrupt mask
  *     @arg ADC_INT_AWE: Analog watchdog interrupt mask
  *     @arg ADC_INT_EOIC: Inserted conversion over interrupt mask
  * @param  NewValue: ADC1 interrupts state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_INTConfig(uint16_t ADC_INT, TypeState NewValue)
{
    uint8_t temp_it = 0;

    /* ADC1 INT old state */
    temp_it = (uint8_t)ADC_INT;

    if (NewValue != DISABLE)
    {
        /* Enable the selected ADC1 interrupts */
        ADC1->CTLR1 |= temp_it;
    }
    else
    {
        /* Disable the selected ADC1 interrupts */
        ADC1->CTLR1 &= (~(uint32_t)temp_it);
    }
}

/**
  * @brief  ADC1 calibration.
  * @retval None
  */
void ADC_Calibration(void)
{
    /* Reset the selected ADC1 calibration registers */
    ADC1->CTLR2 |= CTLR2_RSTCLB_SET;
    /* Check the RSTCLB bit state */
    while((ADC1->CTLR2 & CTLR2_RSTCLB_SET));
    /* Enable ADC1 calibration process */
    ADC1->CTLR2 |= CTLR2_CLB_SET;
    /* Check the CLB bit state */
    while((ADC1->CTLR2 & CTLR2_CLB_SET) != (uint32_t)RESET);
}

/**
  * @brief  Enable or disable ADC1 software start conversion .
  * @param  NewValue: ADC1 software start conversion state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_SoftwareStartConv_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* ADC1 software conversion start */
        ADC1->CTLR2 |= CTLR2_ETERC_SWRCST_SET;
    }
    else
    {
        /* ADC1 software conversion stop */
        ADC1->CTLR2 &= ~CTLR2_ETERC_SWRCST_SET;
    }
}

/**
  * @brief  Get the status of ADC1 Software start conversion.
  * @retval ADC1 software start conversion state(SET or RESET).
  */
TypeState ADC_GetSoftwareStartConvBitState(void)
{
    /* Check SWRCST bit state*/
    if ((ADC1->CTLR2 & CTLR2_SWRCST_SET) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
  * @brief  Configure the ADC1 channel discontinuous mode.
  * @param  Number: the count value of discontinuous mode regular channel
  *   This number must be 1~8.
  * @retval None
  */
void ADC_DiscModeChannelCount_Config(uint8_t Number)
{
    uint32_t temp1 = 0;
    uint32_t temp2 = 0;
    /* Get the old value of CTLR1 */
    temp1 = ADC1->CTLR1;
    /* Clear discontinuous mode channel count */
    temp1 &= CTLR1_DISNUM_RESET;
    /* Set the discontinuous mode channel count */
    temp2 = Number - 1;
    temp1 |= temp2 << 13;
    /* Write to CTLR1 */
    ADC1->CTLR1 = temp1;
}

/**
  * @brief  Enable or disable the discontinuous mode.
  * @param  NewValue: ADC1 discontinuous mode state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_DiscMode_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable ADC1 regular discontinuous mode */
        ADC1->CTLR1 |= CTLR1_DISRC_SET;
    }
    else
    {
        /* Disable ADC1 regular discontinuous mode */
        ADC1->CTLR1 &= ~CTLR1_DISRC_SET;
    }
}

/**
  * @brief  Configure array and sample time.
  * @param  ADC_Channel: the selected ADC channel.
  *   This parameter can be as follows:
  *     @arg ADC_CHANNEL_0: ADC Channel0
  *     @arg ADC_CHANNEL_1: ADC Channel1
  *     @arg ADC_CHANNEL_2: ADC Channel2
  *     @arg ADC_CHANNEL_3: ADC Channel3
  *     @arg ADC_CHANNEL_4: ADC Channel4
  *     @arg ADC_CHANNEL_5: ADC Channel5
  *     @arg ADC_CHANNEL_6: ADC Channel6
  *     @arg ADC_CHANNEL_7: ADC Channel7
  *     @arg ADC_CHANNEL_8: ADC Channel8
  *     @arg ADC_CHANNEL_9: ADC Channel9
  *     @arg ADC_CHANNEL_10: ADC Channel10
  *     @arg ADC_CHANNEL_11: ADC Channel11
  *     @arg ADC_CHANNEL_12: ADC Channel12
  *     @arg ADC_CHANNEL_13: ADC Channel13
  *     @arg ADC_CHANNEL_14: ADC Channel14
  *     @arg ADC_CHANNEL_15: ADC Channel15
  *     @arg ADC_CHANNEL_16: ADC Channel16
  *     @arg ADC_CHANNEL_17: ADC Channel17
  *     @arg ADC_CHANNEL_18: ADC Channel18
  * @param  Array: The regular group sequencer rank. This parameter must be between 1 to 16.
  * @param  ADC_SampleTime: The sample time value.
  *   This parameter can be one of the following values:
  *     @arg ADC_SAMPLETIME_1POINT5: 1.5 cycles
  *     @arg ADC_SAMPLETIME_7POINT5: 7.5 cycles
  *     @arg ADC_SAMPLETIME_13POINT5: 13.5 cycles
  *     @arg ADC_SAMPLETIME_28POINT5: 28.5 cycles
  *     @arg ADC_SAMPLETIME_41POINT5: 41.5 cycles
  *     @arg ADC_SAMPLETIME_55POINT5: 55.5 cycles
  *     @arg ADC_SAMPLETIME_71POINT5: 71.5 cycles
  *     @arg ADC_SAMPLETIME_239POINT5: 239.5 cycles
  * @retval None
  */
void ADC_RegularChannel_Config(uint8_t ADC_Channel, uint8_t Array, uint8_t ADC_SampleTime)
{
    uint32_t temp1 = 0, temp2 = 0;

    /* if ADC_Channel is between 10 to 18 */
    if (ADC_Channel > ADC_CHANNEL_9)
    {
        /* Get SPT1 value */
        temp1 = ADC1->SPT1;
        /* Calculate the mask to clear */
        temp2 = SPT1_SPT_SET << (3 * (ADC_Channel - 10));
        /* Clear sample time */
        temp1 &= ~temp2;
        /* Calculate the mask to set */
        temp2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
        /* Configure sample time */
        temp1 |= temp2;
        /* Write to SPT1 */
        ADC1->SPT1 = temp1;
    }
    else /* ADC_Channel is between 0 to 9 */
    {
        /* Get SPT2 value */
        temp1 = ADC1->SPT2;
        /* Calculate the mask to clear */
        temp2 = SPT2_SPT_SET << (3 * ADC_Channel);
        /* Clear sample time */
        temp1 &= ~temp2;
        /* Calculate the mask to set */
        temp2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
        /* Set sample time */
        temp1 |= temp2;
        /* Write to SPT2 */
        ADC1->SPT2 = temp1;
    }
    /* For Array 1 to 6 */
    if (Array < 7)
    {
        /* Get RSQ3 value */
        temp1 = ADC1->RSQ3;
        /* Calculate the mask to clear */
        temp2 = RSQ3_RSQ_SET << (5 * (Array - 1));
        /* Clear RSQ3 bits */
        temp1 &= ~temp2;
        /* Calculate the mask to set */
        temp2 = (uint32_t)ADC_Channel << (5 * (Array - 1));
        /* Configure the RSQ3 bits */
        temp1 |= temp2;
        /* Write to RSQ3 */
        ADC1->RSQ3 = temp1;
    }
    /* For Array 7 to 12 */
    else if (Array < 13)
    {
        /* Get RSQ2 value */
        temp1 = ADC1->RSQ2;
        /* Calculate the mask to clear */
        temp2 = RSQ2_RSQ_SET << (5 * (Array - 7));
        /* Clear the old RSQ2 bits */
        temp1 &= ~temp2;
        /* Calculate the mask to set */
        temp2 = (uint32_t)ADC_Channel << (5 * (Array - 7));
        /* Set the RSQ2 bits  */
        temp1 |= temp2;
        /* Write to RSQ2 */
        ADC1->RSQ2 = temp1;
    }
    /* For Array 13 to 16 */
    else
    {
        /* Get RSQ1 value */
        temp1 = ADC1->RSQ1;
        /* Calculate the mask to clear */
        temp2 = RSQ1_RSQ_SET << (5 * (Array - 13));
        /* Clear the old RSQ1 bits */
        temp1 &= ~temp2;
        /* Calculate the mask to set */
        temp2 = (uint32_t)ADC_Channel << (5 * (Array - 13));
        /* Set the RSQ1 bits */
        temp1 |= temp2;
        /* Write to RSQ1 */
        ADC1->RSQ1 = temp1;
    }
}

/**
  * @brief  Enable or disable the ADC1 external conversion .
  * @param  NewValue: ADC1 external trigger state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ExternalTrigConv_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable external trigger conversion */
        ADC1->CTLR2 |= CTLR2_ETERC_SET;
    }
    else
    {
        /* Disable external trigger conversion */
        ADC1->CTLR2 &= ~CTLR2_ETERC_SET;
    }
}

/**
  * @brief  Return the ADC1 regular channel conversion data.
  * @retval conversion data.
  */
uint16_t ADC_GetConversionValue(void)
{
    /* Return ADC1 conversion data */
    return (uint16_t) ADC1->RDTR;
}

/**
  * @brief  Enable or disable ADC1 automatic inserted conversion.
  * @param  NewValue: ADC1 auto inserted conversion state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AutoInsertedConv_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable ADC1 automatic inserted conversion */
        ADC1->CTLR1 |= CTLR1_ICA_SET;
    }
    else
    {
        /* Disable ADC1 automatic inserted conversion */
        ADC1->CTLR1 &= ~CTLR1_ICA_SET;
    }
}

/**
  * @brief  Enable or disable the discontinuous mode for ADC1 inserted group channel. 
  * @param  NewValue: ADC1 discontinuous mode state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_InsertedDiscMode_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable the inserted discontinuous mode of the selected ADC channel */
        ADC1->CTLR1 |= CTLR1_DISIC_SET;
    }
    else
    {
        /* Disable the inserted discontinuous mode of the selected ADC channel */
        ADC1->CTLR1 &= ~CTLR1_DISIC_SET;
    }
}

/**
  * @brief  Configure the ADC1 inserted channels external trigger conversion.
  * @param  ADC_ExternalTrigInsertConv: ADC inserted conversion trigger.
  *   This parameter can be as follows:
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T1_TRGO: Timer1 TRGO event
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T1_CC4: Timer1 capture compare4
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T2_TRGO: Timer2 TRGO event
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T2_CC1: Timer2 capture compare1
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T3_CC4: Timer3 capture compare4
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T15_TRGO: Timer15 TRGO event
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_EXT_IT15: External interrupt line 15
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_NONE: Inserted conversion started by software 
  * @retval None
  */
void ADC_ExternalTrigInsertedConv_Config(uint32_t ADC_ExternalTrigInsertConv)
{
    uint32_t temp = 0;
    /* Get CRLR2 value */
    temp = ADC1->CTLR2;
    /* Clear inserted external event */
    temp &= CTLR2_ETSIC_RESET;
    /* Configure inserted external event */
    temp |= ADC_ExternalTrigInsertConv;
    /* Write to CTLR2 */
    ADC1->CTLR2 = temp;
}

/**
  * @brief  Enable or disable the ADC1 inserted channels conversion through
  *         external trigger
  * @param  NewValue: ADC1 external trigger start of inserted conversion state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ExternalTrigInsertedConv_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable external event */
        ADC1->CTLR2 |= CTLR2_ETEIC_SET;
    }
    else
    {
        /* Disable external event */
        ADC1->CTLR2 &= ~CTLR2_ETEIC_SET;
    }
}

/**
  * @brief  Enable or disable ADC1 inserted channels conversion start.
  * @param  NewValue: ADC software start inserted conversion state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_SoftwareStartInsertedConv_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Start ADC1 inserted conversion */
        ADC1->CTLR2 |= CTLR2_ETEIC_SWICST_SET;
    }
    else
    {
        /* Stop ADC1 inserted conversion */
        ADC1->CTLR2 &= ~CTLR2_ETEIC_SWICST_SET;
    }
}

/**
  * @brief  Get ADC Software start inserted conversion State.
  * @retval ADC software start inserted conversion state(SET or RESET).
  */
TypeState ADC_GetSoftwareStartInsertedConvCmdBitState(void)
{
    /* Check SWICST bit */
    if ((ADC1->CTLR2 & CTLR2_SWICST_SET) != (uint32_t)RESET)
    {
        /* Set SWICST bit */
        return SET;
    }
    else
    {
        /* Reset SWICST bit */
        return RESET;
    }
}

/**
  * @brief  Configure Array and sample time for the selected ADC inserted channel.
  * @param  ADC_Channel: the selected ADC channel. 
  *   This parameter can be as follows:
  *     @arg ADC_CHANNEL_0: ADC Channel0
  *     @arg ADC_CHANNEL_1: ADC Channel1
  *     @arg ADC_CHANNEL_2: ADC Channel2
  *     @arg ADC_CHANNEL_3: ADC Channel3
  *     @arg ADC_CHANNEL_4: ADC Channel4
  *     @arg ADC_CHANNEL_5: ADC Channel5
  *     @arg ADC_CHANNEL_6: ADC Channel6
  *     @arg ADC_CHANNEL_7: ADC Channel7
  *     @arg ADC_CHANNEL_8: ADC Channel8
  *     @arg ADC_CHANNEL_9: ADC Channel9
  *     @arg ADC_CHANNEL_10: ADC Channel10
  *     @arg ADC_CHANNEL_11: ADC Channel11
  *     @arg ADC_CHANNEL_12: ADC Channel12
  *     @arg ADC_CHANNEL_13: ADC Channel13
  *     @arg ADC_CHANNEL_14: ADC Channel14
  *     @arg ADC_CHANNEL_15: ADC Channel15
  *     @arg ADC_CHANNEL_16: ADC Channel16
  *     @arg ADC_CHANNEL_17: ADC Channel17
  *     @arg ADC_CHANNEL_18: ADC Channel18
  * @param  Array: The inserted group sequencer Array. This parameter must be between 1 and 4.
  * @param  ADC_SampleTime: The sample time of the selected channel. 
  *   This parameter can be as follows:
  *     @arg ADC_SAMPLETIME_1POINT5: 1.5 cycles
  *     @arg ADC_SAMPLETIME_7POINT5: 7.5 cycles
  *     @arg ADC_SAMPLETIME_13POINT5: 13.5 cycles
  *     @arg ADC_SAMPLETIME_28POINT5: 28.5 cycles
  *     @arg ADC_SAMPLETIME_41POINT5: 41.5 cycles
  *     @arg ADC_SAMPLETIME_55POINT5: 55.5 cycles
  *     @arg ADC_SAMPLETIME_71POINT5: 71.5 cycles
  *     @arg ADC_SAMPLETIME_239POINT5: 239.5 cycles
  * @retval None
  */
void ADC_InsertedChannel_Config(uint8_t ADC_Channel, uint8_t Array, uint8_t ADC_SampleTime)
{
    uint32_t temp1 = 0, temp2 = 0, temp3 = 0;
    
    /* if ADC_Channel is between 10 to 17 */
    if (ADC_Channel > ADC_CHANNEL_9)
    {
        /* Get SPT1 value */
        temp1 = ADC1->SPT1;
        /* Calculate the sample time mask */
        temp2 = SPT1_SPT_SET << (3*(ADC_Channel - 10));
        /* Clear sample time */
        temp1 &= ~temp2;
        /* Calculate the sample time mask */
        temp2 = (uint32_t)ADC_SampleTime << (3*(ADC_Channel - 10));
        /* Set sample time */
        temp1 |= temp2;
        /* Write to SPT1 */
        ADC1->SPT1 = temp1;
    }
    else /* ADC_Channel is between 0 to 9 */
    {
        /* Get SPT2 value */
        temp1 = ADC1->SPT2;
        /* Calculate the sample time mask */
        temp2 = SPT2_SPT_SET << (3 * ADC_Channel);
        /* Clear sample time */
        temp1 &= ~temp2;
        /* Calculate the sample time mask */
        temp2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
        /* Set sample time */
        temp1 |= temp2;
        /* Write to SPT2 */
        ADC1->SPT2 = temp1;
    }
    /* Array configuration */
    /* Get ISQ value */
    temp1 = ADC1->ISQ;
    /* Get IL value: Number = IL+1 */
    temp3 =  (temp1 & ISQ_IL_SET)>> 20;
    /* Calculate the ISQ mask : ((Array-1)+(4-IL-1)) */
    temp2 = ISQ_ISQ_SET << (5 * (uint8_t)((Array + 3) - (temp3 + 1)));
    /* Clear ISQx bits */
    temp1 &= ~temp2;
    /* Calculate the ISQ mask: ((Array-1)+(4-IL-1)) */
    temp2 = (uint32_t)ADC_Channel << (5 * (uint8_t)((Array + 3) - (temp3 + 1)));
    /* Set ISQx bits  */
    temp1 |= temp2;
    /* Write to ISQ */
    ADC1->ISQ = temp1;
}

/**
  * @brief  Configure the sequencer length of inserted channels
  * @param  Length: The sequencer length. 
  *   This parameter must be a number between 1 to 4.
  * @retval None
  */
void ADC_InsertedSequencerLength_Config(uint8_t Length)
{
    uint32_t temp1 = 0;
    uint32_t temp2 = 0;  
    /* Get ISQ value */
    temp1 = ADC1->ISQ;
    /* Clear IL bits */
    temp1 &= ~ISQ_IL_SET;
    /* Set IL bits */
    temp2 = Length - 1; 
    temp1 |= temp2 << 20;
    /* Write to ISQ */
    ADC1->ISQ = temp1;
}

/**
  * @brief  Set the offset of the inserted channels conversion value.
  * @param  ADC_InsertedChannel: one of the four inserted channels to set its offset.
  *   This parameter can be one of the following values:
  *     @arg ADC_INSERTEDCHANNEL_1: Inserted Channel1
  *     @arg ADC_INSERTEDCHANNEL_2: Inserted Channel2
  *     @arg ADC_INSERTEDCHANNEL_3: Inserted Channel3
  *     @arg ADC_INSERTEDCHANNEL_4: Inserted Channel4
  * @param  Offset: the offset value of the selected ADC inserted channel
  *   This parameter must be a 12bit value.
  * @retval None
  */
void ADC_SetInsertedOffset(uint8_t ADC_InsertedChannel, uint16_t Offset)
{
    __IO uint32_t temp = 0;
    temp = (uint32_t)ADC1;
    temp += ADC_InsertedChannel;

    /* Set the offset of the selected inserted channel */
    *(__IO uint32_t *) temp = (uint32_t)Offset;
}

/**
  * @brief  Get the ADC inserted channel conversion result
  * @param  ADC_InsertedChannel: ADC inserted channel.
  *   This parameter can be one of the following values:
  *     @arg ADC_INSERTEDCHANNEL_1: Inserted Channel1
  *     @arg ADC_INSERTEDCHANNEL_2: Inserted Channel2
  *     @arg ADC_INSERTEDCHANNEL_3: Inserted Channel3
  *     @arg ADC_INSERTEDCHANNEL_4: Inserted Channel4
  * @retval The conversion value.
  */
uint16_t ADC_GetInsertedConversionValue(uint8_t ADC_InsertedChannel)
{
    __IO uint32_t temp = 0;
    temp = (uint32_t)ADC1;
    temp += ADC_InsertedChannel + IDTR_OFFSET;
    
    /* Return the result of the selected inserted channel conversion */
    return (uint16_t) (*(__IO uint32_t*)  temp);
}

/**
  * @brief  Enable or disable the analog watchdog.
  * @param  ADC_AnalogWatchdog: the ADC analog watchdog configuration.
  *   This parameter can be one of the following values:
  *     @arg ADC_ANALOGWATCHDOG_SINGLEREGENABLE: single regular channel
  *     @arg ADC_ANALOGWATCHDOG_SINGLEINSERTENABLE: single inserted channel
  *     @arg ADC_ANALOGWATCHDOG_SINGLEREGORINSERTENABLE: single regular or inserted channel
  *     @arg ADC_ANALOGWATCHDOG_ALLREGENABLE: all regular channel
  *     @arg ADC_ANALOGWATCHDOG_ALLINSERTENABLE: all inserted channel
  *     @arg ADC_ANALOGWATCHDOG_ALLREGALLINSERTENABLE: all regular and inserted channels
  *     @arg ADC_ANALOGWATCHDOG_NONE: No channel 
  * @retval None      
  */
void ADC_AnalogWatchdog_Enable(uint32_t ADC_AnalogWatchdog)
{
    uint32_t temp = 0;
    /* Get CTLR1 value */
    temp = ADC1->CTLR1;
    /* Clear AWDEN, AWDENJ and AWDSGL bits */
    temp &= CTLR1_AWDMODE_RESET;
    /* Set the analog watchdog mode */
    temp |= ADC_AnalogWatchdog;
    /* Write to CTLR1 */
    ADC1->CTLR1 = temp;
}

/**
  * @brief  Configure the high and low thresholds of the analog watchdog.
  * @param  HighThreshold: the ADC analog watchdog High threshold value.
  *   This parameter must be a 12bit value.
  * @param  LowThreshold: the ADC analog watchdog Low threshold value.
  *   This parameter must be a 12bit value.
  * @retval None
  */
void ADC_AnalogWatchdogThresholds_Config(uint16_t HighThreshold,uint16_t LowThreshold)
{
    /* Set the ADC1 high threshold */
    ADC1->AWHT = HighThreshold;
    /* Set the ADC1 low threshold */
    ADC1->AWLT = LowThreshold;
}

/**
  * @brief  Configure the analog watchdog on single channel mode.
  * @param  ADC_Channel: ADC channel. 
  *   This parameter can be as follows:
  *     @arg ADC_CHANNEL_0: ADC Channel0
  *     @arg ADC_CHANNEL_1: ADC Channel1
  *     @arg ADC_CHANNEL_2: ADC Channel2
  *     @arg ADC_CHANNEL_3: ADC Channel3
  *     @arg ADC_CHANNEL_4: ADC Channel4
  *     @arg ADC_CHANNEL_5: ADC Channel5
  *     @arg ADC_CHANNEL_6: ADC Channel6
  *     @arg ADC_CHANNEL_7: ADC Channel7
  *     @arg ADC_CHANNEL_8: ADC Channel8
  *     @arg ADC_CHANNEL_9: ADC Channel9
  *     @arg ADC_CHANNEL_10: ADC Channel10
  *     @arg ADC_CHANNEL_11: ADC Channel11
  *     @arg ADC_CHANNEL_12: ADC Channel12
  *     @arg ADC_CHANNEL_13: ADC Channel13
  *     @arg ADC_CHANNEL_14: ADC Channel14
  *     @arg ADC_CHANNEL_15: ADC Channel15
  *     @arg ADC_CHANNEL_16: ADC Channel16
  *     @arg ADC_CHANNEL_17: ADC Channel17
  *     @arg ADC_CHANNEL_18: ADC Channel18
  * @retval None
  */
void ADC_AnalogWatchdogSingleChannel_Config(uint8_t ADC_Channel)
{
    uint32_t temp = 0;
    /* Get CTLR1 value */
    temp = ADC1->CTLR1;
    /* Clear AWCS */
    temp &= CTLR1_AWCS_RESET;
    /* Set the Analog watchdog channel */
    temp |= ADC_Channel;
    /* Write to CTLR1 */
    ADC1->CTLR1 = temp;
}

/**
  * @brief  Enable or disable the temperature sensor and Vrefint channel.
  * @param  NewValue: temperature sensor state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_TempSensorVrefint_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable the temperature sensor and Vrefint channel*/
        ADC1->CTLR2 |= CTLR2_TSVREN_SET;
    }
    else
    {
        /* Disable the temperature sensor and Vrefint channel*/
        ADC1->CTLR2 &= ~CTLR2_TSVREN_SET;
    }
}

/**
  * @brief  Enable or disable the VBat channel.
  * @param  NewValue: temperature sensor state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_VBat_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable the VBat channel*/
        ADC1->CTLR2 |= CTLR2_VBATEN_SET;
    }
    else
    {
        /* Disable the VBat channel*/
        ADC1->CTLR2 &= ~CTLR2_VBATEN_SET;
    }
}

/**
  * @brief  Check the ADC flag.
  * @param  ADC_FLAG: the flag to check.
  *   This parameter can be as follows:
  *     @arg ADC_FLAG_AWE: The flag of the analog watchdog
  *     @arg ADC_FLAG_EOC: The flag of the end of conversion
  *     @arg ADC_FLAG_EOIC: The flag of the end of inserted group conversion
  *     @arg ADC_FLAG_STIC: The flag of the start of inserted group conversion
  *     @arg ADC_FLAG_STRC: The flag of the start of regular group conversion
  * @retval ADC_FLAG state(SET or RESET).
  */
TypeState ADC_GetBitState(uint8_t ADC_FLAG)
{
    /* Check the specified ADC flag state */
    if ((ADC1->STR & ADC_FLAG) != (uint8_t)RESET)
    {
        /* ADC_FLAG is set */
        return SET;
    }
    else
    {
        /* ADC_FLAG is reset */
        return RESET;
    }
}

/**
  * @brief  Clear the ADC1's pending flags.
  * @param  ADC_FLAG: the flag to clear. 
  *   This parameter can be any combination of the following values:
  *     @arg ADC_FLAG_AWE: The flag of the analog watchdog
  *     @arg ADC_FLAG_EOC: The flag of the end of conversion
  *     @arg ADC_FLAG_EOIC: The flag of the end of inserted group conversion
  *     @arg ADC_FLAG_STIC: The flag of the start of inserted group conversion
  *     @arg ADC_FLAG_STRC: The flag of the start of regular group conversion
  * @retval None
  */
void ADC_ClearBitState(uint8_t ADC_FLAG)
{
    /* Clear the selected ADC flags */
    ADC1->STR = ~(uint32_t)ADC_FLAG;
}

/**
  * @brief  Check whether the specified ADC interrupt has occurred or not.
  * @param  ADC_IT: ADC interrupt source. 
  *   This parameter can be one of the following values:
  *     @arg ADC_INT_EOC: The interrupt mask of the end of conversion
  *     @arg ADC_INT_AWE: The interrupt mask of the analog watchdog
  *     @arg ADC_INT_EOIC: The interrupt mask of the end of inserted conversion
  * @retval The new state of ADC_IT (SET or RESET).
  */
TypeState ADC_GetIntState(uint16_t ADC_INT)
{
    uint32_t temp_it = 0, enablestatus = 0;
    /* Get the ADC INT index */
    temp_it = ADC_INT >> 8;
    /* Get the ADC_INT enable bit status */
    enablestatus = (ADC1->CTLR1 & (uint8_t)ADC_INT) ;
    /* Check the status of the specified ADC interrupt */
    if (((ADC1->STR & temp_it) != (uint32_t)RESET) && enablestatus)
    {
        /* ADC_INT is set */
        return SET;
    }
    else
    {
        /* ADC_INT is reset */
        return RESET;
    }
}

/**
  * @brief  Clear the ADC1's interrupt pending bits.
  * @param  ADC_INT: specifies the ADC interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg ADC_INT_EOC: The interrupt mask of the end of conversion
  *     @arg ADC_INT_AWE: The interrupt mask of the analog watchdog
  *     @arg ADC_INT_EOIC: The interrupt mask of the end of inserted conversion
  * @retval None
  */
void ADC_ClearIntBitState(uint16_t ADC_INT)
{
    uint8_t temp_it = 0;
    /* Get the ADC INT index */
    temp_it = (uint8_t)(ADC_INT >> 8);
    /* Clear ADC1 interrupt pending bits */
    ADC1->STR = ~(uint32_t)temp_it;
}

#ifdef GD32F170_190
/**
  * @brief  Configure the ADCx's resolution.
  * @param  ADC_Resolution: the ADC resolution bit.
  *   This parameter can be any combination of the following values:
  *     @arg ADC_RESOLUTION_6B: The ADC resolution 6 bits.
  *     @arg ADC_RESOLUTION_8B: The ADC resolution 8 bits.
  *     @arg ADC_RESOLUTION_10B: The ADC resolution 10 bits.
  *     @arg ADC_RESOLUTION_12B: The ADC resolution 12 bits.
  * @retval None
  */
void ADC_Resolution_Config(uint32_t ADC_Resolution)
{
    uint32_t temp = 0;
    /* Get CTLR1 value */
    temp = ADC1->CTLR1;
    /* Clear ADC resolution bits */
    temp &= CTLR1_DRES_RESET;
    /* Set ADC resolution bits */
    temp |= ADC_Resolution;
    /* Write to CTLR1 */
    ADC1->CTLR1 = temp;
}

/**
  * @brief  Configure the ADCx's Oversampling shift.
  * @param  ADC_Oversampling_Shift: the ADCx's Oversampling shift.
  *   This parameter can be any combination of the following values:
  *     @arg ADC_OVERSAMPLING_SHIFT_NONE: the ADCx's Oversampling shift None
  *     @arg ADC_OVERSAMPLING_SHIFT_1B: the ADCx's Oversampling shift 1 bit
  *     @arg ADC_OVERSAMPLING_SHIFT_2B: the ADCx's Oversampling shift 2 bit
  *     @arg ADC_OVERSAMPLING_SHIFT_3B: the ADCx's Oversampling shift 3 bit
  *     @arg ADC_OVERSAMPLING_SHIFT_4B: the ADCx's Oversampling shift 4 bit
  *     @arg ADC_OVERSAMPLING_SHIFT_5B: the ADCx's Oversampling shift 5 bit
  *     @arg ADC_OVERSAMPLING_SHIFT_6B: the ADCx's Oversampling shift 6 bit
  *     @arg ADC_OVERSAMPLING_SHIFT_7B: the ADCx's Oversampling shift 7 bit
  *     @arg ADC_OVERSAMPLING_SHIFT_8B: the ADCx's Oversampling shift 8 bit
  * @retval None
  */
void ADC_OversamplingShift_Config(uint32_t ADC_Oversampling_Shift)
{
    uint32_t temp = 0;
    /* Get OVSCR value */
    temp = ADC1->OVSCR;
    /* Clear Oversampling shift bits */
    temp &= OVSCR_OVSS_RESET;
    /* Set Oversampling shift bits */
    temp |= ADC_Oversampling_Shift;
    /* Write to OVSCR */
    ADC1->OVSCR = temp;
}

/**
  * @brief  Configure the ADCx's Oversampling Ratio
  * @param  ADC_Oversampling_Ratio: the ADCx's Oversampling Ratio.
  *   This parameter can be any combination of the following values:
  *     @arg ADC_OVERSAMPLING_RATIO_2X the ADCx's Oversampling ratio 2x
  *     @arg ADC_OVERSAMPLING_RATIO_4X the ADCx's Oversampling ratio 4x
  *     @arg ADC_OVERSAMPLING_RATIO_8X the ADCx's Oversampling ratio 8x
  *     @arg ADC_OVERSAMPLING_RATIO_16X the ADCx's Oversampling ratio 16x
  *     @arg ADC_OVERSAMPLING_RATIO_32X the ADCx's Oversampling ratio 32x
  *     @arg ADC_OVERSAMPLING_RATIO_64X the ADCx's Oversampling ratio 64x
  *     @arg ADC_OVERSAMPLING_RATIO_128X the ADCx's Oversampling ratio 128x
  *     @arg ADC_OVERSAMPLING_RATIO_256X the ADCx's Oversampling ratio 256x
  * @retval None
  */
void ADC_OversamplingRatio_Config(uint32_t ADC_Oversampling_Ratio)
{
    uint32_t temp = 0;
    /* Get OVSCR value */
    temp = ADC1->OVSCR;
    /* Clear Oversampling ratio bits */
    temp &= OVSCR_OVSR_RESET;
    /* Set Oversampling ratio bits */
    temp |= ADC_Oversampling_Ratio;
    /* Write to OVSCR */
    ADC1->OVSCR = temp;
}

/**
  * @brief  Enable or disable ADC1's Oversampler.Trigger.
  * @param  NewValue: the state of the Oversampler.Trigger.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_TriggeredOversampling_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable the ADC1's Oversampler.Trigger.*/
        ADC1->OVSCR |= OVSCR_TOVS_SET;
    }
    else
    {
        /* Disable the ADC1's Oversampler.Trigger.*/
        ADC1->OVSCR &= ~OVSCR_TOVS_SET;
    }
}

/**
  * @brief  Enable or disable the ADC1's Oversampler.
  * @param  NewValue: the state of the Oversampler.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Oversampler_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable the ADC1's Oversampler.*/
        ADC1->OVSCR |= OVSCR_OVSE_SET;
    }
    else
    {
        /* Disable the ADC1's Oversampler.*/
        ADC1->OVSCR &= ~OVSCR_OVSE_SET;
    }
}
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

/******************* (C) COPYRIGHT 2016 GIGADEVICE *****END OF FILE****/
