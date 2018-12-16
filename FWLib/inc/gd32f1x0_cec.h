/**
  ******************************************************************************
  * @file    gd32f1x0_cec.h
  * @author  MCU SD
  * @version V2.0.0
  * @date    15-Jan-2016
  * @brief   CEC header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F1X0_CEC_H
#define __GD32F1X0_CEC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0.h"

/** @addtogroup GD32F1x0_Firmware
  * @{
  */

/** @addtogroup CEC
  * @{
  */

/** @defgroup CEC_Exported_Types
  * @{
  */

/** 
  * @brief  CEC Initial Parameters
  */

typedef struct
{
    uint32_t CEC_SFTM;                  /*!< The CEC Signal Free Time, choose one from @ref CEC_Signal_Free_Time */
    uint32_t CEC_RTOL;                  /*!< The CEC Reception Tolerance, choose one from @ref CEC_RxTolerance */
    uint32_t CEC_RBRESTOP;              /*!< Stop reception when detected BRE, choose one from @ref CEC_BRE_Stop_Reception */
    uint32_t CEC_RBREGEN;               /*!< Generate Error-Bit when detected BRE, choose one from @ref CEC_Bit_Rising_Error_Generation */
    uint32_t CEC_RLBPEGEN;              /*!< Generate Error-Bit when detected LBPE, choose one from @ref CEC_Long_Bit_Error_Generation */
    uint32_t CEC_BCNG;                  /*!< Do not generate Error-Bit in broadcast, choose one from @ref CEC_Broadcast_No_Generation */
    uint32_t CEC_SFTMOPT;               /*!< The CEC Signal Free Time option, choose one from @ref CEC_SFT_Option */
}CEC_InitPara;

/**
  * @}
  */
  
/** @defgroup CEC_Exported_Constants
  * @{
  */

/** @defgroup CEC_Signal_Free_Time
  * @{
  */
#define CEC_SFTM_STD                    ((uint32_t)0x00000000)  /*!< Signal Free Time Standard */
#define CEC_SFTM_1T                     ((uint32_t)0x00000001)  /*!< SFTM 1.5 data bit periods */
#define CEC_SFTM_2T                     ((uint32_t)0x00000002)  /*!< SFTM 2.5 data bit periods */
#define CEC_SFTM_3T                     ((uint32_t)0x00000003)  /*!< SFTM 3.5 data bit periods */
#define CEC_SFTM_4T                     ((uint32_t)0x00000004)  /*!< SFTM 4.5 data bit periods */
#define CEC_SFTM_5T                     ((uint32_t)0x00000005)  /*!< SFTM 5.5 data bit periods */
#define CEC_SFTM_6T                     ((uint32_t)0x00000006)  /*!< SFTM 6.5 data bit periods */
#define CEC_SFTM_7T                     ((uint32_t)0x00000007)  /*!< SFTM 7.5 data bit periods */

/**
  * @}
  */

/** @defgroup CEC_RxTolerance
  * @{
  */
#define CEC_RTOL_STD                    ((uint32_t)0x00000000)  /*!< Standard bit timing tolerance */
#define CEC_RTOL_EXD                    CEC_SR_RTOL             /*!< Extended bit timing tolerance */

/**
  * @}
  */

/** @defgroup CEC_RBRE_Stop_Reception
  * @{
  */
#define CEC_RBRESTOP_OFF                ((uint32_t)0x00000000)  /*!< Do not stop reception on bit Rising Error */
#define CEC_RBRESTOP_ON                 CEC_SR_RBRESTP          /*!< Stop reception on bit Rising Error */

/**
  * @}
  */

/** @defgroup CEC_Bit_Rising_Error_Generation
  * @{
  */
#define CEC_RBREGEN_OFF                 ((uint32_t)0x00000000)  /*!< Do not generate Error-Bit on bit Rising Error */
#define CEC_RBREGEN_ON                  CEC_SR_RBREGEN          /*!< Generate Error-Bit on bit Rising Error */

/**
  * @}
  */

/** @defgroup CEC_Long_Bit_Error_Generation
  * @{
  */
#define CEC_RLBPEGEN_OFF                ((uint32_t)0x00000000)  /*!< Do not generate Error-Bit on Long Bit Period Error */
#define CEC_RLBPEGEN_ON                 CEC_SR_RLBPEGEN         /*!< Generate Error-Bit on Long Bit Period Error */

/**
  * @}
  */

/** @defgroup CEC_Broadcast_No_Generation
  * @{
  */

#define CEC_BCNG_OFF                    ((uint32_t)0x00000000)  /*!< Generate Error-Bit in Broadcast */
#define CEC_BCNG_ON                     CEC_SR_BCNG             /*!< Do not generate Error-Bit in Broadcast */

/**
  * @}
  */

/** @defgroup CEC_SFTM_Option
  * @{
  */
#define CEC_SFTMOPT_SOM                 ((uint32_t)0x00000000)  /*!< SFTM counter starts when SOM is set */
#define CEC_SFTMOPT_LAST                CEC_SR_SFTMOPT          /*!< SFTM counter starts after the end of the last message */

/**
  * @}
  */

/** @defgroup CEC_Interrupt_Configuration_definition
  * @{
  */
#define CEC_INT_TAE                     CEC_IER_TAEIE           /*!< Tx Missing Acknowledge Error Interrupt Enable */
#define CEC_INT_TE                      CEC_IER_TEIE            /*!< Tx-Error Interrupt Enable */
#define CEC_INT_TU                      CEC_IER_TUIE            /*!< Tx Data Buffer Underrun Interrupt Enable */
#define CEC_INT_TEND                    CEC_IER_TENDIE          /*!< End of Transmission Successfully Interrupt Enable */
#define CEC_INT_TBR                     CEC_IER_TBRIE           /*!< Tx-Byte Data Request Interrupt Enable */
#define CEC_INT_LSTARB                  CEC_IER_LSTARBIE        /*!< Arbitration Lost Interrupt Enable */
#define CEC_INT_RAE                     CEC_IER_RAEIE           /*!< Rx Missing Acknowledge Interrupt Enable */
#define CEC_INT_RLBPE                   CEC_IER_RLBPEIE         /*!< Rx Long Bit Period Error Interrupt Enable */
#define CEC_INT_RSBPE                   CEC_IER_RSBPEIE         /*!< Rx Short Bit Period Error Interrupt Enable */
#define CEC_INT_RBRE                    CEC_IER_RBREIE          /*!< Rx Bit Rising Error Interrupt Enable */
#define CEC_INT_RO                      CEC_IER_ROIE            /*!< Rx Overrun Interrupt Enable */
#define CEC_INT_REND                    CEC_IER_RENDIE          /*!< End Of Reception Interrupt Enable */
#define CEC_INT_RBR                     CEC_IER_RBRIE           /*!< Rx-Byte Received Interrupt Enable */

/**
  * @}
  */

/** @defgroup CEC_ISTR_register_flags_definition
  * @{
  */
#define CEC_FLAG_TAE                    CEC_ISTR_TAE            /*!< Tx Missing Acknowledge Error Flag*/
#define CEC_FLAG_TE                     CEC_ISTR_TE             /*!< Tx-Error Flag */
#define CEC_FLAG_TU                     CEC_ISTR_TU             /*!< Tx Data Buffer Underrun Flag */
#define CEC_FLAG_TEND                   CEC_ISTR_TEND           /*!< End of Transmission Successfully Flag */
#define CEC_FLAG_TBR                    CEC_ISTR_TBR            /*!< Tx-Byte Data Request Flag */
#define CEC_FLAG_LSTARB                 CEC_ISTR_LSTARB         /*!< Arbitration Lost Flag */
#define CEC_FLAG_RAE                    CEC_ISTR_RAE            /*!< Rx Missing Acknowledge Flag */
#define CEC_FLAG_RLBPE                  CEC_ISTR_RLBPE          /*!< Rx Long Bit period Error Flag */
#define CEC_FLAG_RSBPE                  CEC_ISTR_RSBPE          /*!< Rx Short Bit period Error Flag */
#define CEC_FLAG_RBRE                   CEC_ISTR_RBRE           /*!< Rx Bit Rising Error Flag */
#define CEC_FLAG_RO                     CEC_ISTR_RO             /*!< Rx-Overrun Flag */
#define CEC_FLAG_REND                   CEC_ISTR_REND           /*!< End Of Reception Flag */
#define CEC_FLAG_RBR                    CEC_ISTR_RBR            /*!< Rx-Byte Received Flag */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup CEC_Exported_Functions
  * @{
  */

void CEC_DeInit(void);
void CEC_Init(CEC_InitPara* CEC_InitParaStruct);
void CEC_ParaInit(CEC_InitPara* CEC_InitParaStruct);
void CEC_Enable(TypeState NewValue);
void CEC_ListenModeEnable(TypeState NewValue);
void CEC_SetOwnAddress(uint8_t CEC_OwnAddress);
void CEC_ClearAllOwnAddress(void);
void CEC_SendData(uint8_t Data);
uint8_t CEC_ReceiveData(void);
void CEC_StartOfMessage(void);
void CEC_EndOfMessage(void);
void CEC_INTConfig(uint32_t CEC_INT, TypeState NewValue);
TypeState CEC_GetBitState(uint32_t CEC_FLAG);
void CEC_ClearBitState(uint32_t CEC_FLAG);
TypeState CEC_GetIntBitState(uint32_t CEC_INT);
void CEC_ClearIntBitState(uint32_t CEC_INT);

#ifdef __cplusplus
}
#endif

#endif /* __GD32F1X0_CEC_H */

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
