/**
  ******************************************************************************
  * @file    gd32f1x0_lcd.c
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   LCD functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0_lcd.h"
#include "gd32f1x0_rcc.h"

#ifdef GD32F170_190
/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @defgroup LCD 
  * @brief LCD driver modules
  * @{
  */

/** @defgroup LCD_Private_Defines
  * @{
  */
#define LCD_CFGR_DIV_MASK              ((uint32_t)0xFFC3FFFF)        /*!< LCD CFGR_DIV Mask */
#define LCD_CFGR_PRE_MASK              ((uint32_t)0xFC3FFFFF)        /*!< LCD CFGR_PRE Mask */
#define LCD_CFGR_PULSE_MASK            ((uint32_t)0xFFFFFF8F)        /*!< LCD CFGR_PULSE Mask */
#define LCD_CFGR_DD_MASK               ((uint32_t)0xFFFFFC7F)        /*!< LCD CFGR_DD Mask */
#define LCD_CFGR_CONR_MASK             ((uint32_t)0xFFFFE3FF)        /*!< LCD CFGR_CONR Mask */
#define LCD_CFGR_BLKM_MASK             ((uint32_t)0xFFFC1FFF)        /*!< LCD CFGR_BLKM Mask */

#define LCD_CTLR_VSRC_MASK             ((uint32_t)0xFFFFFFFD)        /*!< LCD CTLR_VSRC Mask */
#define LCD_CTLR_DUTY_MASK             ((uint32_t)0xFFFFFFE3)        /*!< LCD CTLR_DUTY Mask */
#define LCD_CTLR_BIAS_MASK             ((uint32_t)0xFFFFFF9F)        /*!< LCD CTLR_BIAS Mask */

#define SYN_TIMEOUT                    ((uint32_t)0x00008000)        /*!< LCD synchronization timeout */
/**
  * @}
  */

/* Private function prototypes */
static void LCD_WaitClkSyn(void);

/** @defgroup LCD_Private_Functions
  * @{
  */

/**
  * @brief  Deinitialize the LCD.
  * @param  None
  * @retval None
  */
void LCD_DeInit(void)
{
    /* Enable LCD reset state */
    RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_LCDRST, ENABLE);
    /* Release LCD from reset state */
    RCC_APB1PeriphReset_Enable(RCC_APB1PERIPH_LCDRST, DISABLE);
}

/**
  * @brief  Initialize the LCD controler.
  * @param  LCD_InitParaStruct : pointer to a LCD_InitPara structure .
  * @retval None
  */
void LCD_Init(LCD_InitPara* LCD_InitParaStruct)
{
    LCD->CFGR &= (uint32_t)LCD_CFGR_DIV_MASK;
    LCD->CFGR &= (uint32_t)LCD_CFGR_PRE_MASK;
    LCD->CFGR |= (uint32_t)(LCD_InitParaStruct->LCD_Prescaler | LCD_InitParaStruct->LCD_Divider);

    LCD_WaitClkSyn();

    LCD->CTLR &= (uint32_t)LCD_CTLR_VSRC_MASK;
    LCD->CTLR &= (uint32_t)LCD_CTLR_DUTY_MASK;
    LCD->CTLR &= (uint32_t)LCD_CTLR_BIAS_MASK;
    LCD->CTLR |= (uint32_t)(LCD_InitParaStruct->LCD_Duty | LCD_InitParaStruct->LCD_VBias | LCD_InitParaStruct->LCD_VSRC);
}

/**
  * @brief  Fill each LCD_InitParaStruct Struct member with a default value.
  * @param  LCD_InitParaStruct : pointer to a LCD_InitPara structure .
  * @retval None
  */
void LCD_ParaInit(LCD_InitPara* LCD_InitParaStruct)
{
    /* Fill the default value */
    LCD_InitParaStruct->LCD_Prescaler = LCD_PRESCALER_1; 

    LCD_InitParaStruct->LCD_Divider = LCD_DIVIDER_16; 

    LCD_InitParaStruct->LCD_Duty = LCD_DUTY_STATIC; 

    LCD_InitParaStruct->LCD_VBias = LCD_BIAS_1_4; 

    LCD_InitParaStruct->LCD_VSRC = LCD_VOLTAGESOURCE_INTERNAL; 
}

/**
  * @brief  ENABLE or DISABLE the LCD controler.
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void LCD_Enable(TypeState NewValue)
{
    if ( NewValue != DISABLE )
    {
        /* Enable the LCD */
        LCD->CTLR |= LCD_CTLR_LCDON;
    }
    else
    {
        /* Disable the LCD */
        LCD->CTLR &= (uint8_t)(~( ( uint8_t )LCD_CTLR_LCDON));
    }
}

/**
  * @brief  Enable or disable the specified LCD interrupts.
  * @param  LCD_INT: Specifies LCD interrupt sources.
  *   This value will be :
  *     @arg LCD_INT_SOF: Start of frame interrupt mask
  *     @arg LCD_INT_UPD: LCD update done interrupt mask
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void LCD_INTConfig(uint32_t LCD_INT, TypeState NewValue)
{
    if (NewValue != DISABLE)
    {
        /* Enable the selected LCD interrupts */
        LCD->CFGR |= LCD_INT;
    }
    else
    {
        /* Disable the selected LCD interrupts */
        LCD->CFGR &= (~(uint32_t)LCD_INT);
    }
}

/**
  * @brief  Wait for the LCD_CFGR register synchronized in the LCDCLK domain.
  *   After write operation about LCD_CFGR register please use this function.
  * @param  None
  * @retval None
  */
static void LCD_WaitClkSyn(void)
{
    uint32_t syncounter = 0;
    uint32_t synstate = 0x00;

    /* Wait for synchronization */
    while((syncounter != SYN_TIMEOUT) && (synstate == 0x00))
    {
        synstate = LCD->SFR & LCD_FLAG_SYNF;
        syncounter++;  
    }
}

/**
  * @brief  Enable or disable the LCD controler high drive function.
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void LCD_HighDrive_Enable(TypeState NewValue)
{
    if ( NewValue != DISABLE )
    {
        /* Enable the high drive function */
        LCD->CFGR |= LCD_CFGR_HDON;
    }
    else
    {
        /* Disable the high drive function */
        LCD->CFGR &= (uint32_t)(~( ( uint32_t )LCD_CFGR_HDON));
    }
}

/**
  * @brief  Enable or disable the segment remap function.
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void LCD_SegmentRemap_Enable(TypeState NewValue)
{
    if ( NewValue != DISABLE )
    {
        /* Enable the segment remap function */
        LCD->CTLR |= LCD_CTLR_COMS;
    }
    else
    {
        /* Disable the segment remap function */
        LCD->CTLR &= (uint8_t)(~( ( uint8_t )LCD_CTLR_COMS));
    }
}

/**
  * @brief  Configure the LCD pulses on duration.
  * @param  LCD_PulseOnDuration: Specifies LCD pulse on duration.
  *   This value will be :
  *     @arg LCD_PULSEON_DURATION_0: 0 pulse
  *     @arg LCD_PULSEON_DURATION_1: Pulse ON duration = 1*1/fPRE
  *     @arg LCD_PULSEON_DURATION_2: Pulse ON duration = 2*1/fPRE
  *     @arg LCD_PULSEON_DURATION_3: Pulse ON duration = 3*1/fPRE
  *     @arg LCD_PULSEON_DURATION_4: Pulse ON duration = 4*1/fPRE
  *     @arg LCD_PULSEON_DURATION_5: Pulse ON duration = 5*1/fPRE
  *     @arg LCD_PULSEON_DURATION_6: Pulse ON duration = 6*1/fPRE
  *     @arg LCD_PULSEON_DURATION_7: Pulse ON duration = 7*1/fPRE
  * @retval None
  */
void LCD_PulseOnDurationConfig(uint32_t LCD_PulseOnDuration)
{
    LCD->CFGR &= (uint32_t)LCD_CFGR_PULSE_MASK;

    LCD->CFGR |= (uint32_t)(LCD_PulseOnDuration);
}

/**
  * @brief  Configure the LCD dead time.
  * @param  LCD_DeadTime: specifies the LCD dead time period.
  *   This value will be :
  *     @arg LCD_DEADTIME_PERIOD_0: No dead Time
  *     @arg LCD_DEADTIME_PERIOD_1: 1 Phase between couple of Frame
  *     @arg LCD_DEADTIME_PERIOD_2: 2 Phase between couple of Frame
  *     @arg LCD_DEADTIME_PERIOD_3: 3 Phase between couple of Frame
  *     @arg LCD_DEADTIME_PERIOD_4: 4 Phase between couple of Frame
  *     @arg LCD_DEADTIME_PERIOD_5: 5 Phase between couple of Frame
  *     @arg LCD_DEADTIME_PERIOD_6: 6 Phase between couple of Frame 
  *     @arg LCD_DEADTIME_PERIOD_7: 7 Phase between couple of Frame
  * @retval None
  */
void LCD_DeadTimeConfig(uint32_t LCD_DeadTime)
{
    LCD->CFGR &= (uint32_t)LCD_CFGR_DD_MASK;

    LCD->CFGR |= (uint32_t)(LCD_DeadTime);
}

/**
  * @brief  Configure the LCD Blink mode and frequency.
  * @param  LCD_BlinkMode: the LCD blink mode.
  *   This value will be :
  *     @arg LCD_BLINKMODE_OFF:           Blink disabled
  *     @arg LCD_BLINKMODE_SEG0_COM0:     Blink enabled on SEG[0], COM[0]
  *     @arg LCD_BLINKMODE_SEG0_ALLCOM:   Blink enabled on SEG[0], all COM
  *     @arg LCD_BLINKMODE_ALLSEG_ALLCOM: Blink enabled on all SEG and all COM 
  * @param  LCD_BlinkFrequency: the LCD blink frequency.
  *   This value will be :
  *     @arg LCD_BLINK_FREQUENCY_DIV8:    fBLINK = fLCD/8
  *     @arg LCD_BLINK_FREQUENCY_DIV16:   fBLINK = fLCD/16
  *     @arg LCD_BLINK_FREQUENCY_DIV32:   fBLINK = fLCD/32
  *     @arg LCD_BLINK_FREQUENCY_DIV64:   fBLINK = fLCD/64
  *     @arg LCD_BLINK_FREQUENCY_DIV128:  fBLINK = fLCD/128
  *     @arg LCD_BLINK_FREQUENCY_DIV256:  fBLINK = fLCD/256
  *     @arg LCD_BLINK_FREQUENCY_DIV512:  fBLINK = fLCD/512
  *     @arg LCD_BLINK_FREQUENCY_DIV1024: fBLINK = fLCD/1024
  * @retval None
  */
void LCD_BlinkConfig(uint32_t LCD_BlinkMode, uint32_t LCD_BlinkFrequency_Divider)
{
    LCD->CFGR &= (uint32_t)LCD_CFGR_BLKM_MASK;

    LCD->CFGR |= (uint32_t)(LCD_BlinkMode | LCD_BlinkFrequency_Divider);
}

/**
  * @brief  Configure the LCD Contrast.
  * @param  LCD_Contrast: the LCD Contrast.
  *   This value will be :
  *     @arg LCD_CONTRAST_LEVEL_0: Maximum Voltage = 2.60V
  *     @arg LCD_CONTRAST_LEVEL_1: Maximum Voltage = 2.73V
  *     @arg LCD_CONTRAST_LEVEL_2: Maximum Voltage = 2.86V
  *     @arg LCD_CONTRAST_LEVEL_3: Maximum Voltage = 2.99V
  *     @arg LCD_CONTRAST_LEVEL_4: Maximum Voltage = 3.12V
  *     @arg LCD_CONTRAST_LEVEL_5: Maximum Voltage = 3.25V
  *     @arg LCD_CONTRAST_LEVEL_6: Maximum Voltage = 3.38V
  *     @arg LCD_CONTRAST_LEVEL_7: Maximum Voltage = 3.51V
  * @retval None
  */
void LCD_ContrastConfig(uint32_t LCD_Contrast_Level)
{
    LCD->CFGR &= (uint32_t)LCD_CFGR_CONR_MASK;

    LCD->CFGR |= (uint32_t)(LCD_Contrast_Level);
}

/**
  * @brief  Write a word in the specific LCD data register.
  * @param  LCD_DATA_REG: the LCD data register.
  *   This value will be :
  *     @arg LCD_DATA_REG0: LCD DATA Register 0
  *     @arg LCD_DATA_REG1: LCD DATA Register 1
  *     @arg LCD_DATA_REG2: LCD DATA Register 2
  *     @arg LCD_DATA_REG3: LCD DATA Register 3
  *     @arg LCD_DATA_REG4: LCD DATA Register 4
  *     @arg LCD_DATA_REG5: LCD DATA Register 5
  *     @arg LCD_DATA_REG6: LCD DATA Register 6
  *     @arg LCD_DATA_REG7: LCD DATA Register 7
  * @param  LCD_Data: specifies LCD Data Value to be written.
  * @retval None
  */
void LCD_WriteDataReg(uint32_t LCD_DataReg, uint32_t LCD_Data)
{
    volatile uint32_t *pdata;

    /* Point to DATA register */
    pdata = &LCD->DATA0;

    /* Wtite data word to DATA register */
    *(pdata + LCD_DataReg) = (uint32_t)LCD_Data;
}

/**
  * @brief  Enable the Update Display Request.
  * @param  None
  * @retval None
  */
void LCD_DataUpdateRequest(void)
{
    LCD->SFR |= LCD_SFR_UPRF;
}

/**
  * @brief  Check whether the flag is set or not.
  * @param  LCD_FLAG: the flag to check. 
  *   This value will be :
  *     @arg LCD_FLAG_ONF: LCD controller on flag
  *     @arg LCD_FLAG_SOF: Start of Frame flag
  *     @arg LCD_FLAG_UPRF: LCD data register update request flag
  *     @arg LCD_FLAG_UPDF: Update LCD data Done flag
  *     @arg LCD_FLAG_VRDYF: LCD voltage ready flag
  *     @arg LCD_FLAG_SYNF: LCD CFGR Register Synchronization Flag
  * @retval The new state of LCD_FLAG (SET or RESET).
  */
TypeState LCD_GetBitState(uint32_t LCD_FLAG)
{
    if ((LCD->SFR & LCD_FLAG) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
  * @brief  Clear the pending flags.
  * @param  LCD_FLAG: the flag to clear.
  *   This value will be :
  *     @arg LCD_FLAG_SOF: Start of Frame Interrupt
  *     @arg LCD_FLAG_UPDF: LCD update done interrupt
  * @retval None
  */
void LCD_ClearBitState(uint32_t LCD_FLAG)
{
    /* Clear the corresponding LCD flag */
    LCD->ICR = (uint32_t)LCD_FLAG;
}

/**
  * @brief  Check whether the interrupt is pending or not.
  * @param  LCD_INT: the LCD interrupt source to check.
  *   This value will be :
  *     @arg LCD_INT_SOF: Start of Frame Interrupt
  *     @arg LCD_INT_UPD: LCD update done interrupt
  * @retval The new state of the LCD_INT (SET or RESET).
  */
TypeState LCD_GetIntBitState(uint32_t LCD_INT)
{
    if (((LCD->CFGR & LCD_INT) != (uint16_t)RESET) && ((LCD->SFR & LCD_INT) != (uint16_t)RESET))
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
  * @brief  Clear the interrupt pending bits.
  * @param  LCD_INT: the interrupt pending bit to clear.
  *   This value will be :
  *     @arg LCD_INT_SOF: Start of Frame Interrupt
  *     @arg LCD_INT_UPD: LCD update done interrupt
  * @retval None
  */
void LCD_ClearIntBitState(uint32_t LCD_INT)
{
    /* Clear the corresponding LCD pending bit */
    LCD->ICR = (uint32_t)LCD_INT;
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

#endif /* GD32F170_190 */

/******************* (C) COPYRIGHT 2016 GIGADEVICE *****END OF FILE****/
