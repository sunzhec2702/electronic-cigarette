#include "adc.h"
#include "pid.h"

/* Private variables ---------------------------------------------------------*/
#define MAX_CH_NUM	5
static uint16_t ADC_ConvertedValue[ MAX_CH_NUM + 1];

/**
  * @brief  Configure the system clocks,GPIO ports,DMA and ADC & NVIC.
  * @param  None
  * @retval None
  */
void ADC1_Configuration()
{
    GPIO_InitPara GPIO_InitStructure;
    DMA_InitPara DMA_InitStructure;
    ADC_InitPara ADC_InitStructure;

    NVIC_InitPara NVIC_InitStructure;

    NVIC_PRIGroup_Enable(NVIC_PRIGROUP_1);

    /* Configure DMA1 interrupt */
    NVIC_InitStructure.NVIC_IRQ = DMA1_Channel1_IRQn;
    NVIC_InitStructure.NVIC_IRQPreemptPriority = 1;
    NVIC_InitStructure.NVIC_IRQSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQEnable = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Configure the system clocks -------------------------------------------*/

    RCC_ADCCLKConfig(RCC_ADCCLK_APB2_DIV4); // RCC_ADCCLK_APB2_DIV6
    RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_DMA1 | RCC_AHBPERIPH_GPIOA, ENABLE);
    RCC_APB2PeriphClock_Enable(RCC_APB2PERIPH_ADC1, ENABLE);

    /* Configure GPIO ports --------------------------------------------------*/
#ifndef YANMING1
    /* Configure PA2 (ADC Channel11) as analog input */
    // current
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AN;
    GPIO_InitStructure.GPIO_Speed   = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PUPD_PULLDOWN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure PA3 (ADC Channel12) as analog input */
    // temp
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AN;
    GPIO_InitStructure.GPIO_Speed   = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PUPD_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure PA4 (ADC Channel13) as analog input */
    // Vo
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AN;
    GPIO_InitStructure.GPIO_Speed   = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PUPD_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure PA5 (ADC Channel14) as analog input */
    // Key
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AN;
    GPIO_InitStructure.GPIO_Speed   = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PUPD_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure PA7 (ADC Channel14) as analog input */
    //Vin
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AN;
    GPIO_InitStructure.GPIO_Speed   = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PUPD_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    /* Configure PA6 (ADC Channel14) as analog input */
//    // Protection for PA2
//    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_6;
//    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT;
//    GPIO_InitStructure.GPIO_Speed   = GPIO_SPEED_50MHZ;
//    GPIO_InitStructure.GPIO_PuPd    = GPIO_PUPD_PULLDOWN;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//    GPIO_ResetBits(GPIOA, GPIO_PIN_6);

    /* DMA channel1 configuration ----------------------------------------------*/
    DMA_DeInit(DMA1_CHANNEL1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC_RDTR_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)(&ADC_ConvertedValue[1]);
    DMA_InitStructure.DMA_DIR = DMA_DIR_PERIPHERALSRC;
    DMA_InitStructure.DMA_BufferSize = MAX_CH_NUM;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PERIPHERALINC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc = DMA_MEMORYINC_ENABLE;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PERIPHERALDATASIZE_HALFWORD;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MEMORYDATASIZE_HALFWORD;
    DMA_InitStructure.DMA_Mode = DMA_MODE_CIRCULAR;
    DMA_InitStructure.DMA_Priority = DMA_PRIORITY_HIGH;
    DMA_InitStructure.DMA_MTOM = DMA_MEMTOMEM_DISABLE;
    DMA_Init(DMA1_CHANNEL1, &DMA_InitStructure);

    /* Enable DMA1 channel1 */
    DMA_Enable(DMA1_CHANNEL1, ENABLE);



    /* Enable ADC*/
    ADC_DeInit(&ADC_InitStructure);
    ADC_InitStructure.ADC_Mode_Scan = ENABLE;
    ADC_InitStructure.ADC_Mode_Continuous = ENABLE;
    ADC_InitStructure.ADC_Trig_External = ADC_EXTERNAL_TRIGGER_MODE_NONE;
    ADC_InitStructure.ADC_Data_Align = ADC_DATAALIGN_RIGHT;
    ADC_InitStructure.ADC_Channel_Number = MAX_CH_NUM;
    ADC_Init(&ADC_InitStructure);

    /* ADC regular channels configuration */
    ADC_RegularChannel_Config(ADC_CHANNEL_2, 1, ADC_SAMPLETIME_71POINT5);
    ADC_RegularChannel_Config(ADC_CHANNEL_3, 2, ADC_SAMPLETIME_7POINT5);
    ADC_RegularChannel_Config(ADC_CHANNEL_4, 3, ADC_SAMPLETIME_7POINT5);
    ADC_RegularChannel_Config(ADC_CHANNEL_5, 4, ADC_SAMPLETIME_7POINT5);
    ADC_RegularChannel_Config(ADC_CHANNEL_7, 5, ADC_SAMPLETIME_239POINT5);

#else
    /* Configure PA1 (ADC Channel1) as analog input */
    // current
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AN;
    GPIO_InitStructure.GPIO_Speed   = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PUPD_PULLDOWN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure PA2 (ADC Channel2) as analog input */
    // Vbat Vi
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AN;
    GPIO_InitStructure.GPIO_Speed   = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PUPD_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure PA5 (ADC Channel5) as analog input */
    // temp
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AN;
    GPIO_InitStructure.GPIO_Speed   = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PUPD_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure PA6 (ADC Channel6) as analog input */
    // Vo
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AN;
    GPIO_InitStructure.GPIO_Speed   = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PUPD_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    /* DMA channel1 configuration ----------------------------------------------*/
    DMA_DeInit(DMA1_CHANNEL1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC_RDTR_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)(&ADC_ConvertedValue[1]);
    DMA_InitStructure.DMA_DIR = DMA_DIR_PERIPHERALSRC;
    DMA_InitStructure.DMA_BufferSize = MAX_CH_NUM;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PERIPHERALINC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc = DMA_MEMORYINC_ENABLE;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PERIPHERALDATASIZE_HALFWORD;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MEMORYDATASIZE_HALFWORD;
    DMA_InitStructure.DMA_Mode = DMA_MODE_CIRCULAR;
    DMA_InitStructure.DMA_Priority = DMA_PRIORITY_HIGH;
    DMA_InitStructure.DMA_MTOM = DMA_MEMTOMEM_DISABLE;
    DMA_Init(DMA1_CHANNEL1, &DMA_InitStructure);

    /* Enable DMA1 channel1 */
    DMA_Enable(DMA1_CHANNEL1, ENABLE);



    /* Enable ADC*/
    ADC_DeInit(&ADC_InitStructure);
    ADC_InitStructure.ADC_Mode_Scan = ENABLE;
    ADC_InitStructure.ADC_Mode_Continuous = ENABLE;   // DISABLE
    ADC_InitStructure.ADC_Trig_External = ADC_EXTERNAL_TRIGGER_MODE_NONE;
    ADC_InitStructure.ADC_Data_Align = ADC_DATAALIGN_RIGHT;
    ADC_InitStructure.ADC_Channel_Number = MAX_CH_NUM;
    ADC_Init(&ADC_InitStructure);

    /* ADC regular channels configuration */
    ADC_RegularChannel_Config(ADC_CHANNEL_1, 1, ADC_SAMPLETIME_13POINT5);  // current
    ADC_RegularChannel_Config(ADC_CHANNEL_5, 2, ADC_SAMPLETIME_7POINT5);  // temp
#ifdef YANMING2
    ADC_RegularChannel_Config(ADC_CHANNEL_2, 3, ADC_SAMPLETIME_7POINT5);  // Vo
    ADC_RegularChannel_Config(ADC_CHANNEL_2, 4, ADC_SAMPLETIME_7POINT5);  // dummy
    ADC_RegularChannel_Config(ADC_CHANNEL_6, 5, ADC_SAMPLETIME_239POINT5);  // Vi
#else
    ADC_RegularChannel_Config(ADC_CHANNEL_6, 3, ADC_SAMPLETIME_7POINT5);  // Vo
    ADC_RegularChannel_Config(ADC_CHANNEL_6, 4, ADC_SAMPLETIME_7POINT5);  // dummy
    ADC_RegularChannel_Config(ADC_CHANNEL_2, 5, ADC_SAMPLETIME_239POINT5);  // Vi
#endif

////    ADC_RegularChannel_Config(ADC_CHANNEL_1, 1, ADC_SAMPLETIME_13POINT5);  // current
////    ADC_RegularChannel_Config(ADC_CHANNEL_5, 2, ADC_SAMPLETIME_7POINT5);  // temp
////    ADC_RegularChannel_Config(ADC_CHANNEL_6, 3, ADC_SAMPLETIME_7POINT5);  // Vo
////    ADC_RegularChannel_Config(ADC_CHANNEL_5, 4, ADC_SAMPLETIME_7POINT5);  // dummy
////		ADC_RegularChannel_Config(ADC_CHANNEL_2, 5, ADC_SAMPLETIME_239POINT5);  // Vi
//		ADC_RegularChannel_Config(ADC_CHANNEL_1, 6, ADC_SAMPLETIME_13POINT5);
//////		ADC_RegularChannel_Config(ADC_CHANNEL_1, 7, ADC_SAMPLETIME_13POINT5);




#endif

    /* Enable ADC DMA */
    ADC_DMA_Enable(ENABLE);
    DMA_INTConfig(DMA1_CHANNEL1, DMA1_INT_TC1,ENABLE);

    /* Enable ADC */
    ADC_Enable(ENABLE);
    ADC_Calibration();

    /* Start ADC Software Conversion */
    ADC_SoftwareStartConv_Enable(ENABLE);
}

void ADC1_Deinit()
{
    DMA_INTConfig(DMA1_CHANNEL1, DMA1_INT_TC1, DISABLE);
    //ADB_DMA_Enable(DISABLE
}


u16 get_key_voltage()
{
    return ADC_ConvertedValue[4];
}

// GET ADDRESS
uint16_t * Get_ADC1_ConvertData_Addr(void)
{
    return ADC_ConvertedValue;
}

/**
  * @brief  This function handles DMA transfer complete interrupts requests.
  * @param  None
  * @retval None
*/

// ADC-> DMA 中断处理程序
void DMA1_Channel1_IRQHandler(void)
{
    /* Clear DMA1 TC1 pending interrupt bit */

//		GPIO_SetBits(GPIOA, GPIO_PIN_6); // debug
    // get measure data;
    ADC1_Data_CVT(ADC_ConvertedValue);
    DMA_ClearIntBitState(DMA1_INT_TC1);
}

