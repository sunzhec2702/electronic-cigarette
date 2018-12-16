/**
  ******************************************************************************
  * @file    gd32f1x0_usart.h
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   USART header file of the firmware library.
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F1X0_USART_H
#define __GD32F1X0_USART_H

#ifdef __cplusplus
 extern "C" {
#endif 
  
/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0.h"

/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @addtogroup USART
  * @{
  */

/** @defgroup USART_Exported_Types
  * @{
  */

/** 
  * @brief USART Initial Parameters
  */
typedef struct
{
    uint32_t USART_BRR;                      /*!< the USART communication baud rate configuration.
                                                 The baud-rate divider (USARTDIV) has the following relationship to the system clock: 
                                                 In case of oversampling by 16, the equation is:
                                                 USARTDIV=  UCLK/(16*Baud Rate)
                                                 In case of oversampling by 8, the equation is:
                                                 USARTDIV=  UCLK/(8*Baud Rate) */
    uint32_t USART_WL;                       /*!< Set by USART_CTLR1_WL   Word length 0: 8 Data bits,
                                                 1: 9 Data bits */
    uint32_t USART_STBits;                   /*!< Stop bits configuration */

    uint32_t USART_Parity;                   /*!< Set by USART_CTLR1_PCEN */

    uint32_t USART_RxorTx;                   /*!< Specifies wether the Receive or Transmit mode is enabled or disabled. */

    uint32_t USART_HardwareFlowControl;      /*!< Specifies wether the hardware flow control mode is enabled
                                                 or disabled.This parameter can be a value of @ref USART_Hardware_Flow_Control */
} USART_InitPara;

/** 
  * @brief  USART Clock Initial Parameters
  */ 

typedef struct
{
    uint32_t USART_CKEN;                     /*!< USART clock enabled this parameter can be a value of @ref USART_CKEN */     
                                         
    uint32_t USART_CPL;                      /*!< Clock polarity of Steady state this parameter can be a value of @ref USART_USART_CKEN */
                                        
    uint32_t USART_CPH;                      /*!< Clock phase this parameter can be a value of @ref USART_Clock_Phase */
                                   
    uint32_t USART_LBCP;                     /*!< Last bit clock pulse this parameter can be a value of @ref USART_Last_Bit */                                                                     
} USART_ClockInitPara;

/**
  * @}
  */
  
/** @defgroup USART_Exported_Constants
  * @{
  */ 

/** @defgroup USART_WL 
  * @{
  */ 
#define USART_WL_8B                          ((uint32_t)0x00000000)                         /*!< Word length:8 Data bits */
#define USART_WL_9B                          USART_CTLR1_WL                                 /*!< Word length:9 Data bits */

/**
  * @}
  */ 

/** @defgroup USART_STBits 
  * @{
  */ 
#define USART_STBITS_1                       ((uint32_t)0x00000000)                         /*!< STOP bits length:1 Stop bit */
#define USART_STBITS_2                       USART_CTLR2_STB_1                              /*!< STOP bits length:2 Stop bit*/
#define USART_STBITS_1_5                     (USART_CTLR2_STB_0 | USART_CTLR2_STB_1)        /*!< STOP bits length:1.5 Stop bit */

/**
  * @}
  */ 

/** @defgroup USART_Parity 
  * @{
  */
#define USART_PARITY_RESET                   ((uint32_t)0x00000000)                         /*!< Parity control disabled */
#define USART_PARITY_SETEVEN                 USART_CTLR1_PCEN                               /*!< Parity mode: Even parity */
#define USART_PARITY_SETODD                  (USART_CTLR1_PCEN | USART_CTLR1_PM)            /*!< Parity mode: Odd parity */ 

/**
  * @}
  */ 

/** @defgroup USART_RxorTx 
  * @{
  */ 
#define USART_RXORTX_RX                      USART_CTLR1_REN                                /*!< Receiver enable */
#define USART_RXORTX_TX                      USART_CTLR1_TEN                                /*!< Transmitter enable */

/**
  * @}
  */ 

/** @defgroup USART_Hardware_Flow_Control 
  * @{
  */ 
#define USART_HARDWAREFLOWCONTROL_NONE       ((uint32_t)0x00000000)                         /*!< hardware flow control disabled */
#define USART_HARDWAREFLOWCONTROL_RTS        USART_CTLR3_RTSEN                              /*!< RTS hardware flow control enabled */
#define USART_HARDWAREFLOWCONTROL_CTS        USART_CTLR3_CTSEN                              /*!< CTS hardware flow control enabled */
#define USART_HARDWAREFLOWCONTROL_RTS_CTS    (USART_CTLR3_RTSEN | USART_CTLR3_CTSEN)        /*!< Both RTS hardware flow control and CTS hardware flow control enabled */

/**
  * @}
  */ 

/** @defgroup USART_USART_CKEN 
  * @{
  */ 
#define USART_CKEN_RESET                     ((uint32_t)0x00000000)                         /*!< CK pin disabled */
#define USART_CKEN_SET                       USART_CTLR2_CKEN                               /*!< CK pin enabled */

/**
  * @}
  */ 

/** @defgroup USART_Clock_Polarity 
  * @{
  */
#define USART_CPL_LOW                        ((uint32_t)0x00000000)                         /*!< Clock polarity: Steady low value on CK pin outside transmission window in synchronous mode*/
#define USART_CPL_HIGH                       USART_CTLR2_CPL                                /*!< Clock polarity: Steady high value on CK pin outside transmission window in synchronous mode */

/**
  * @}
  */ 

/** @defgroup USART_Clock_Phase
  * @{
  */
#define USART_CPH_1EDGE                      ((uint32_t)0x00000000)                         /*!< Clock phase: the first clock transition is the first data capture edge */
#define USART_CPH_2EDGE                      USART_CTLR2_CPH                                /*!< Clock phase: the second clock transition is the first data capture edge */

/**
  * @}
  */

/** @defgroup USART_Last_Bit
  * @{
  */
#define USART_LBCP_DISABLE                   ((uint32_t)0x00000000)                         /*!< Last bit clock pulse: the clock pulse of the last data bit (MSB) is not output to the CK pin */
#define USART_LBCP_ENABLE                    USART_CTLR2_LBCP                               /*!< Last bit clock pulse: the clock pulse of the last data bit (MSB) is output to the CK pin */

/**
  * @}
  */
  
/** @defgroup USART_DMA_Requests 
  * @{
  */
#define USART_DMAREQ_TX                      USART_CTLR3_DENT                               /*!< DMA enable for transmission */
#define USART_DMAREQ_RX                      USART_CTLR3_DENR                               /*!< DMA enable for reception */

/**
  * @}
  */ 

/** @defgroup USART_DMA_Recception_Error
  * @{
  */
#define USART_DMAONERROR_ENABLE              ((uint32_t)0x00000000)                         /*!< DMA is not disabled in case of reception error */
#define USART_DMAONERROR_DISABLE             USART_CTLR3_DDRE                               /*!< DMA is disabled following a reception error */

/**
  * @}
  */ 

/** @defgroup USART_MuteMode_WakeUp_methods
  * @{
  */
#define USART_WAKEUP_IDLELINE                ((uint32_t)0x00000000)                         /*!< Wakeup method in mute mode:Idle Line */
#define USART_WAKEUP_ADDRESSMARK             USART_CTLR1_WM                                 /*!< Wakeup method in mute mode:Address Mark */

/**
  * @}
  */

/** @defgroup USART_Address_Detection
  * @{
  */ 
#define USART_ADDRESSLENGTH_4B               ((uint32_t)0x00000000)                         /*!< Address detection mode: 4-bit address detection*/
#define USART_ADDRESSLENGTH_7B               USART_CTLR2_ADDM                               /*!< Address detection mode: full-bit address detection */

/**
  * @}
  */ 

/** @defgroup USART_StopMode_WakeUp_methods 
  * @{
  */ 
#define USART_WAKEUPSOURCE_ADDRESSMATCH      ((uint32_t)0x00000000)                         /*!< Wakeup mode from Deep-sleep mode: WU active on address match */
#define USART_WAKEUPSOURCE_STARTBIT          USART_CTLR3_WUM_1                              /*!< Wakeup mode from Deep-sleep mode: WU active on Start bit */
#define USART_WAKEUPSOURCE_RBNE              (USART_CTLR3_WUM_0 | USART_CTLR3_WUM_1)        /*!< Wakeup mode from Deep-sleep mode: WU active on RBNE */

/**
  * @}
  */ 

/** @defgroup USART_LIN_Break_Detection_Length 
  * @{
  */
#define USART_LINBREAKDETECTLENGTH_10B       ((uint32_t)0x00000000)                         /*!< LIN break detection length:10 bit break detection */
#define USART_LINBREAKDETECTLENGTH_11B       USART_CTLR2_LBDL                               /*!< LIN break detection length:11 bit break detection */

/**
  * @}
  */

/** @defgroup USART_IrDA_Low_Power 
  * @{
  */
#define USART_IRDAMODE_LOWPOWER              USART_CTLR3_IRLP                               /*!< IrDA low-power: normal mode*/
#define USART_IRDAMODE_NORMAL                ((uint32_t)0x00000000)                         /*!< IrDA low-power: low-power mode */

/**
  * @}
  */ 

/** @defgroup USART_DE_Polarity 
  * @{
  */
#define USART_DEPOLARITY_HIGH                ((uint32_t)0x00000000)                         /*!< Driver enable polarity mode:DE signal is active high */
#define USART_DEPOLARITY_LOW                 USART_CTLR3_DEP                                /*!< Driver enable polarity mode:DE signal is active low */

/**
  * @}
  */ 

/** @defgroup USART_Inversion_Pins 
  * @{
  */
#define USART_INVPIN_TX                      USART_CTLR2_TINV                               /*!< TX pin level inversion */
#define USART_INVPIN_RX                      USART_CTLR2_RINV                               /*!< RX pin level inversion */

/**
  * @}
  */ 

/** @defgroup USART_AutoBaudRate_Mode 
  * @{
  */
#define USART_AUTOBAUDRATE_STARTBIT          ((uint32_t)0x00000000)                         /*!< Auto baud rate mode:falling edge to rising edge measurement */
#define USART_AUTOBAUDRATE_FALLINGEDGE       USART_CTLR2_ABDM_0                             /*!< Auto baud rate mode:falling edge to falling edge measurement */

/**
  * @}
  */ 

/** @defgroup USART_OVR_DETECTION
  * @{
  */
#define USART_OVRDETECTION_ENABLE            ((uint32_t)0x00000000)                         /*!< Overrun functionality is enabled */
#define USART_OVRDETECTION_DISABLE           USART_CTLR3_OVRD                               /*!< Overrun functionality is disabled */

/**
  * @}
  */ 
  
/** @defgroup USART_Cmd 
  * @{
  */
#define USART_REQUEST_ABDCMD                 USART_CMD_ABDCMD                               /*!< Auto baudrate detection command */
#define USART_REQUEST_SBKCMD                 USART_CMD_SBKCMD                               /*!< Send break command */
#define USART_REQUEST_MMRQ                   USART_CMD_MMCMD                                /*!< Mute mode command */
#define USART_REQUEST_RXFCMD                 USART_CMD_RXFCMD                               /*!< Receive data flush command */
#define USART_REQUEST_TXFCMD                 USART_CMD_TXFCMD                               /*!< Transmit data flush request */

/**
  * @}
  */ 

/** @defgroup USART_Flags 
  * @{
  */
#define USART_FLAG_REA                       USART_STR_REA                                  /*!< Receive enable acknowledge flag */
#define USART_FLAG_TEA                       USART_STR_TEA                                  /*!< Transmit enable acknowledge flag */
#define USART_FLAG_WUF                       USART_STR_WUF                                  /*!< Wakeup from Deep-sleep mode flag */
#define USART_FLAG_RWU                       USART_STR_RWU                                  /*!< Receiver wakeup from mute mode */
#define USART_FLAG_SBF                       USART_STR_SBF                                  /*!< Send break flag */
#define USART_FLAG_AMF                       USART_STR_AMF                                  /*!< ADDR match flag */
#define USART_FLAG_BSY                       USART_STR_BSY                                  /*!< Busy flag */
#define USART_FLAG_ABDF                      USART_STR_ABDF                                 /*!< Auto baudrate detection flag */
#define USART_FLAG_ABDE                      USART_STR_ABDE                                 /*!< Auto baudrate detection error */
#define USART_FLAG_EBF                       USART_STR_EBF                                  /*!< End of block flag */
#define USART_FLAG_RTF                       USART_STR_RTF                                  /*!< Receiver timeout flag */
#define USART_FLAG_CTS                       USART_STR_CTS                                  /*!< CTS level */
#define USART_FLAG_CTSF                      USART_STR_CTSF                                 /*!< CTS change flag */
#define USART_FLAG_LBDF                      USART_STR_LBDF                                 /*!< LIN break detected flag */
#define USART_FLAG_TBE                       USART_STR_TBE                                  /*!< Transmit data register empty */
#define USART_FLAG_TC                        USART_STR_TC                                   /*!< Transmission complete */
#define USART_FLAG_RBNE                      USART_STR_RBNE                                 /*!< Read data buffer not empty */
#define USART_FLAG_IDLEF                     USART_STR_IDLEF                                /*!< IDLE line detected flag */
#define USART_FLAG_ORE                       USART_STR_ORE                                  /*!< Overrun error */
#define USART_FLAG_NE                        USART_STR_NE                                   /*!< Noise error flag */
#define USART_FLAG_FE                        USART_STR_FE                                   /*!< Framing error */
#define USART_FLAG_PE                        USART_STR_PE                                   /*!< Parity error  */

/**
  * @}
  */ 

/** @defgroup USART_Interrupt_definition 
  * @{
  */
#define USART_INT_WU                         ((uint32_t)0x00140316)                         /*!< Wakeup from Deep-sleep mode interrupt enable */
#define USART_INT_AM                         ((uint32_t)0x0011010E)                         /*!< ADDR match interrupt enable */
#define USART_INT_EB                         ((uint32_t)0x000C011B)                         /*!< End of Block interrupt enable */
#define USART_INT_RT                         ((uint32_t)0x000B011A)                         /*!< Receiver timeout interrupt enable */
#define USART_INT_PE                         ((uint32_t)0x00000108)                         /*!< Parity error interrupt enable */
#define USART_INT_TBE                        ((uint32_t)0x00070107)                         /*!< Transmitter register empty interrupt enable */
#define USART_INT_TC                         ((uint32_t)0x00060106)                         /*!< Transmission complete interrupt enable */
#define USART_INT_RBNE                       ((uint32_t)0x00050105)                         /*!< Read data buffer not empty interrupt and overrun error interrupt enable */
#define USART_INT_IDLEF                      ((uint32_t)0x00040104)                         /*!< IDLE line detected interrupt enable */
#define USART_INT_LBDF                       ((uint32_t)0x00080206)                         /*!< LIN break detection interrupt enable */
#define USART_INT_CTSF                       ((uint32_t)0x0009030A)                         /*!< CTS interrupt enable */
#define USART_INT_ERIE                       ((uint32_t)0x00000300)                         /*!< Error interrupt enable in multibuffer Communication */
#define USART_INT_ORE                        ((uint32_t)0x00030300)                         /*!< Error interrupt enable in multibuffer Communication */
#define USART_INT_NE                         ((uint32_t)0x00020300)                         /*!< Error interrupt enable in multibuffer Communication */
#define USART_INT_FE                         ((uint32_t)0x00010300)                         /*!< Error interrupt enable in multibuffer Communication */

/**
  * @}
  */
  
/**
  * @}
  */
  
/** @defgroup USART_Exported_Functions
  * @{
  */
void USART_DeInit(USART_TypeDef* USARTx);
void USART_Init(USART_TypeDef* USARTx, USART_InitPara* USART_InitParaStruct);
void USART_ParaInit(USART_TypeDef* USARTx,USART_InitPara* USART_InitParaStruct);
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitPara* USART_ClockInitStruct);
void USART_ClockStructInit(USART_ClockInitPara* USART_ClockInitParaStruct);
void USART_Enable(USART_TypeDef* USARTx, TypeState NewValue);
void USART_TransferDirection_Enable(USART_TypeDef* USARTx, uint32_t USART_Direction, TypeState NewValue);
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler);
void USART_OverSampling8_Enable(USART_TypeDef* USARTx, TypeState NewValue);
void USART_OneSamplingBit_Enable(USART_TypeDef* USARTx, TypeState NewValue);
void USART_MSBFirst_Enable(USART_TypeDef* USARTx, TypeState NewValue);
void USART_DataInvert_Enable(USART_TypeDef* USARTx, TypeState NewValue);
void USART_InvPin_Enable(USART_TypeDef* USARTx, uint32_t USART_InvertPin, TypeState NewValue);
void USART_SWPFunction_Enable(USART_TypeDef* USARTx, TypeState NewValue);
void USART_ReceiverTimeOut_Enable(USART_TypeDef* USARTx, TypeState NewValue);
void USART_SetReceiveTimeOut_Threshold(USART_TypeDef* USARTx, uint32_t USART_ReceiverTimeOutThreshold);
void USART_DataSend(USART_TypeDef* USARTx,uint16_t Data);
uint16_t USART_DataReceive(USART_TypeDef* USARTx);
void USART_AutoBaudRateDect_Enable(USART_TypeDef* USARTx,TypeState NewValue);
void USART_AutoBaudRateDectMode_Set(USART_TypeDef* USARTx, uint32_t USART_AutoBaudRate);
void USART_Address(USART_TypeDef* USARTx, uint8_t USART_Address);
void USART_MuteMode_Enable(USART_TypeDef* USARTx, TypeState NewState);
void USART_MuteModeWakeUp_Set(USART_TypeDef* USARTx, uint32_t USART_WakeUp);
void USART_AddressDetection_Set(USART_TypeDef* USARTx, uint32_t USART_AddressLength);
void USART_SetLINBDLength(USART_TypeDef* USARTx,uint32_t USART_LINBreakDetectLength);
void USART_LIN_Enable(USART_TypeDef* USARTx,TypeState NewValue);
void USART_HalfDuplex_Enable(USART_TypeDef* USARTx, TypeState NewValue);
void USART_GuardTime_Set(USART_TypeDef* USARTx, uint8_t USART_GuardTime);
void USART_SmartCard_Enable(USART_TypeDef* USARTx,TypeState NewValue);
void USART_SmartCardNACK_Enable(USART_TypeDef* USARTx,TypeState NewValue);
void USART_AutoRetryNumber_Set(USART_TypeDef* USARTx,uint8_t USART_AutoNumber);
void USART_BlockLength_Set(USART_TypeDef* USARTx,uint8_t USART_BlockLength);
void USART_IrDA_Set(USART_TypeDef* USARTx,uint32_t USART_IrDAMode);
void USART_IrDA_Enable(USART_TypeDef* USARTx,TypeState NewValue);
void USART_DE_Enable(USART_TypeDef* USARTx,TypeState NewValue);
void USART_DriverEnablePolarity_Set(USART_TypeDef* USARTx, uint32_t USART_DEPly);
void USART_DEATime_Set(USART_TypeDef* USARTx, uint32_t USART_DEATime);
void USART_DEDTime_Set(USART_TypeDef* USARTx, uint32_t USART_DEDTime);
void USART_DMA_Enable(USART_TypeDef* USARTx, uint32_t USART_DMAEnable, TypeState NewValue);
void USART_DMARE_Set(USART_TypeDef* USARTx, uint32_t USART_DMARE);

void USART_DEEPSLEEPModeEnable(USART_TypeDef* USARTx, TypeState NewState);
void USART_DEEPSLEEPModeWakeUpSourceConfig(USART_TypeDef* USARTx, uint32_t USART_WakeUpSource);

void USART_INT_Set(USART_TypeDef* USARTx, uint32_t USART_INT, TypeState NewValue);
void USART_Request_Enable(USART_TypeDef* USARTx, uint32_t USART_Cmd, TypeState NewValue);
void USART_OverRunFunc_Set(USART_TypeDef* USARTx, uint32_t USART_OVRD);
TypeState USART_GetBitState(USART_TypeDef* USARTx, uint32_t USART_FLAG);
void USART_ClearBitState(USART_TypeDef* USARTx, uint32_t USART_FLAG);
TypeState USART_GetIntBitState(USART_TypeDef* USARTx, uint32_t USART_INT);
void USART_ClearIntBitState(USART_TypeDef* USARTx, uint32_t USART_INT);

#ifdef __cplusplus
}
#endif

#endif /*__GD32F1X0_USART_H */
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
