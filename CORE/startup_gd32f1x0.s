;/**
;  ******************************************************************************
;  * @file    startup_gd32f1x0.s
;  * @author  MCU SD
;  * @version V2.0.0   
;  * @date    15-Jan-2016
;  * @brief   GD32F1x0 startup code.
;  ******************************************************************************
;  */

;/* <<< Use Configuration Wizard in Context Menu >>>                                                        */

; Amount of memory (in bytes) allocated for Stack and Heap
; Tailor those values to your application needs
;// <h> Stack Configuration
;//   <o> Stack Size (in Bytes) <0-8192:8>
;// </h>
Stack_Size          EQU     0x450

                    AREA    STACK, NOINIT, READWRITE, ALIGN = 3
Stack_Mem           SPACE   Stack_Size
__initial_sp

;// <h> Heap Configuration
;// <o>  Heap Size (in Bytes) <0-8192:8>
;// </h>
Heap_Size           EQU     0x50

                    AREA    HEAP, NOINIT, READWRITE, ALIGN = 3
__heap_base
Heap_Mem            SPACE   Heap_Size
__heap_limit


                    PRESERVE8
                    THUMB

; Vector table entries with the exceptions ISR address
                    AREA    RESET, DATA, READONLY
                    EXPORT  __Vectors
                    EXPORT  __Vectors_End
                    EXPORT  __Vectors_Size

__Vectors           DCD     __initial_sp                      ; Top of Stack
                    DCD     Reset_Handler                     ; Vector Number 1,Reset Handler
                    DCD     NMI_Handler                       ; Vector Number 2,NMI Handler
                    DCD     HardFault_Handler                 ; Vector Number 3,Hard Fault Handler
                    DCD     MemManage_Handler                 ; Vector Number 4,MPU Fault Handler
                    DCD     BusFault_Handler                  ; Vector Number 5,Bus Fault Handler
                    DCD     UsageFault_Handler                ; Vector Number 6,Usage Fault Handler
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     SVC_Handler                       ; Vector Number 11,SVCall Handler
                    DCD     DebugMon_Handler                  ; Vector Number 12,Debug Monitor Handler
                    DCD     0                                 ; Reserved
                    DCD     PendSV_Handler                    ; Vector Number 14,PendSV Handler
                    DCD     SysTick_Handler                   ; Vector Number 15,SysTick Handler

                    ; External Interrupts
                    DCD     WWDG_IRQHandler                   ; Vector Number 16,Window Watchdog
                    DCD     LVD_IRQHandler                    ; Vector Number 17,LVD through EXTI Line detect
                    DCD     RTC_IRQHandler                    ; Vector Number 18,RTC through EXTI Line
                    DCD     FMC_IRQHandler                    ; Vector Number 19,FMC
                    DCD     RCC_IRQHandler                    ; Vector Number 20,RCC
                    DCD     EXTI0_1_IRQHandler                ; Vector Number 21,EXTI Line 0 and EXTI Line 1
                    DCD     EXTI2_3_IRQHandler                ; Vector Number 22,EXTI Line 2 and EXTI Line 3
                    DCD     EXTI4_15_IRQHandler               ; Vector Number 23,EXTI Line 4 to EXTI Line 15
                    DCD     TSI_IRQHandler                    ; Vector Number 24,TSI
                    DCD     DMA1_Channel1_IRQHandler          ; Vector Number 25,DMA1 Channel 1 
                    DCD     DMA1_Channel2_3_IRQHandler        ; Vector Number 26,DMA1 Channel 2 and DMA1 Channel 3
                    DCD     DMA1_Channel4_5_IRQHandler        ; Vector Number 27,DMA1 Channel 4 and DMA1 Channel 5
                    DCD     ADC1_CMP_IRQHandler               ; Vector Number 28,ADC1 and Comparator 1-2
                    DCD     TIMER1_BRK_UP_TRG_COM_IRQHandler  ; Vector Number 29,TIMER1 Break,Update,Trigger and Commutation
                    DCD     TIMER1_CC_IRQHandler              ; Vector Number 30,TIMER1 Capture Compare
                    DCD     TIMER2_IRQHandler                 ; Vector Number 31,TIMER2
                    DCD     TIMER3_IRQHandler                 ; Vector Number 32,TIMER3
                    DCD     TIMER6_DAC_IRQHandler             ; Vector Number 33,TIMER6 and DAC
                    DCD     0                                 ; Reserved
                    DCD     TIMER14_IRQHandler                ; Vector Number 35,TIMER14
                    DCD     TIMER15_IRQHandler                ; Vector Number 36,TIMER15
                    DCD     TIMER16_IRQHandler                ; Vector Number 37,TIMER16
                    DCD     TIMER17_IRQHandler                ; Vector Number 38,TIMER17
                    DCD     I2C1_EV_IRQHandler                ; Vector Number 39,I2C1 Event
                    DCD     I2C2_EV_IRQHandler                ; Vector Number 40,I2C2 Event
                    DCD     SPI1_IRQHandler                   ; Vector Number 41,SPI1
                    DCD     SPI2_IRQHandler                   ; Vector Number 42,SPI2
                    DCD     USART1_IRQHandler                 ; Vector Number 43,USART1
                    DCD     USART2_IRQHandler                 ; Vector Number 44,USART2
                    DCD     0                                 ; Reserved
                    DCD     CEC_IRQHandler                    ; Vector Number 46,CEC
                    DCD     0                                 ; Reserved
                    DCD     I2C1_ER_IRQHandler                ; Vector Number 48,I2C1 Error
                    DCD     0                                 ; Reserved
                    DCD     I2C2_ER_IRQHandler                ; Vector Number 50,I2C2 Error
                    DCD     I2C3_EV_IRQHandler                ; Vector Number 51,I2C3 Event
                    DCD     I2C3_ER_IRQHandler                ; Vector Number 52,I2C3 Error
                    DCD     USB_FS_LP_IRQHandler              ; Vector Number 53,USB FS LP
                    DCD     USB_FS_HP_IRQHandler              ; Vector Number 54,USB FS HP
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     USBWakeUp_IRQHandler              ; Vector Number 58,USB Wakeup
                    DCD     CAN1_TX_IRQHandler                ; Vector Number 59,CAN1 TX
                    DCD     CAN1_RX0_IRQHandler               ; Vector Number 60,CAN1 RX0
                    DCD     CAN1_RX1_IRQHandler               ; Vector Number 61,CAN1 RX1
                    DCD     CAN1_SCE_IRQHandler               ; Vector Number 62,CAN1 SCE     
                    DCD     LCD_IRQHandler                    ; Vector Number 63,LCD
                    DCD     DMA1_Channel6_7_IRQHandler        ; Vector Number 64,DMA1 Channel6 and Channel7 
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     SPI3_IRQHandler                   ; Vector Number 67,SPI3
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     CAN2_TX_IRQHandler                ; Vector Number 86,CAN2 TX
                    DCD     CAN2_RX0_IRQHandler               ; Vector Number 87,CAN2 RX0
                    DCD     CAN2_RX1_IRQHandler               ; Vector Number 88,CAN2 RX1
                    DCD     CAN2_SCE_IRQHandler               ; Vector Number 89,CAN2 SCE             

                    SPACE   0x5A



__Vectors_End

__Vectors_Size      EQU  __Vectors_End - __Vectors

                    AREA    |.text|, CODE, READONLY

; Reset handler routine
Reset_Handler       PROC
                    EXPORT  Reset_Handler                     [WEAK]
                    IMPORT  __main
                    IMPORT  System_Init  
                    LDR     R0, =System_Init
                    BLX     R0
                    LDR     R0, =__main
                    BX      R0
                    ENDP

; Dummy Exception Handlers
NMI_Handler         PROC
                    EXPORT  NMI_Handler                       [WEAK]
                    B       .
                    ENDP

HardFault_Handler   PROC
                    EXPORT  HardFault_Handler                 [WEAK]
                    B       .
                    ENDP

MemManage_Handler   PROC
                    EXPORT  MemManage_Handler                 [WEAK]
                    B       .
                    ENDP

BusFault_Handler    PROC
                    EXPORT  BusFault_Handler                  [WEAK]
                    B       .
                    ENDP

UsageFault_Handler  PROC
                    EXPORT  UsageFault_Handler                [WEAK]
                    B       .
                    ENDP

SVC_Handler         PROC
                    EXPORT  SVC_Handler                       [WEAK]
                    B       .
                    ENDP

DebugMon_Handler    PROC
                    EXPORT  DebugMon_Handler                  [WEAK]
                    B       .
                    ENDP

PendSV_Handler      PROC
                    EXPORT  PendSV_Handler                    [WEAK]
                    B       .
                    ENDP

SysTick_Handler     PROC
                    EXPORT  SysTick_Handler                   [WEAK]
                    B       .
                    ENDP

Default_Handler     PROC
                    EXPORT  WWDG_IRQHandler                   [WEAK]
                    EXPORT  LVD_IRQHandler                    [WEAK]
                    EXPORT  RTC_IRQHandler                    [WEAK]
                    EXPORT  FMC_IRQHandler                    [WEAK]
                    EXPORT  RCC_IRQHandler                    [WEAK]
                    EXPORT  EXTI0_1_IRQHandler                [WEAK]
                    EXPORT  EXTI2_3_IRQHandler                [WEAK]
                    EXPORT  EXTI4_15_IRQHandler               [WEAK]
                    EXPORT  TSI_IRQHandler                    [WEAK]
                    EXPORT  DMA1_Channel1_IRQHandler          [WEAK]
                    EXPORT  DMA1_Channel2_3_IRQHandler        [WEAK]
                    EXPORT  DMA1_Channel4_5_IRQHandler        [WEAK]
                    EXPORT  ADC1_CMP_IRQHandler               [WEAK]
                    EXPORT  TIMER1_BRK_UP_TRG_COM_IRQHandler  [WEAK]
                    EXPORT  TIMER1_CC_IRQHandler              [WEAK]
                    EXPORT  TIMER2_IRQHandler                 [WEAK]
                    EXPORT  TIMER3_IRQHandler                 [WEAK]
                    EXPORT  TIMER6_DAC_IRQHandler             [WEAK]
                    EXPORT  TIMER14_IRQHandler                [WEAK]
                    EXPORT  TIMER15_IRQHandler                [WEAK]
                    EXPORT  TIMER16_IRQHandler                [WEAK]
                    EXPORT  TIMER17_IRQHandler                [WEAK]
                    EXPORT  I2C1_EV_IRQHandler                [WEAK]
                    EXPORT  I2C2_EV_IRQHandler                [WEAK]
                    EXPORT  SPI1_IRQHandler                   [WEAK]
                    EXPORT  SPI2_IRQHandler                   [WEAK]
                    EXPORT  USART1_IRQHandler                 [WEAK]
                    EXPORT  USART2_IRQHandler                 [WEAK]
                    EXPORT  CEC_IRQHandler                    [WEAK]
                    EXPORT  I2C1_ER_IRQHandler                [WEAK]
                    EXPORT  I2C2_ER_IRQHandler                [WEAK]
                    EXPORT  I2C3_EV_IRQHandler                [WEAK]
                    EXPORT  I2C3_ER_IRQHandler                [WEAK]
                    EXPORT  USB_FS_LP_IRQHandler              [WEAK]
                    EXPORT  USB_FS_HP_IRQHandler              [WEAK]
                    EXPORT  USBWakeUp_IRQHandler              [WEAK]
                    EXPORT  CAN1_TX_IRQHandler                [WEAK]
                    EXPORT  CAN1_RX0_IRQHandler               [WEAK]
                    EXPORT  CAN1_RX1_IRQHandler               [WEAK]
                    EXPORT  CAN1_SCE_IRQHandler               [WEAK]
                    EXPORT  LCD_IRQHandler                    [WEAK]
                    EXPORT  DMA1_Channel6_7_IRQHandler        [WEAK]
                    EXPORT  SPI3_IRQHandler                   [WEAK]
                    EXPORT  CAN2_TX_IRQHandler                [WEAK]
                    EXPORT  CAN2_RX0_IRQHandler               [WEAK]
                    EXPORT  CAN2_RX1_IRQHandler               [WEAK]
                    EXPORT  CAN2_SCE_IRQHandler               [WEAK]

WWDG_IRQHandler
LVD_IRQHandler
RTC_IRQHandler
FMC_IRQHandler
RCC_IRQHandler
EXTI0_1_IRQHandler
EXTI2_3_IRQHandler
EXTI4_15_IRQHandler
TSI_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_3_IRQHandler
DMA1_Channel4_5_IRQHandler
ADC1_CMP_IRQHandler
TIMER1_BRK_UP_TRG_COM_IRQHandler
TIMER1_CC_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
TIMER6_DAC_IRQHandler
TIMER14_IRQHandler
TIMER15_IRQHandler
TIMER16_IRQHandler
TIMER17_IRQHandler
I2C1_EV_IRQHandler
I2C2_EV_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
CEC_IRQHandler
I2C1_ER_IRQHandler
I2C2_ER_IRQHandler
I2C3_EV_IRQHandler
I2C3_ER_IRQHandler
USB_FS_LP_IRQHandler
USB_FS_HP_IRQHandler
USBWakeUp_IRQHandler
CAN1_TX_IRQHandler
CAN1_RX0_IRQHandler
CAN1_RX1_IRQHandler
CAN1_SCE_IRQHandler
LCD_IRQHandler
DMA1_Channel6_7_IRQHandler
SPI3_IRQHandler
CAN2_TX_IRQHandler
CAN2_RX0_IRQHandler
CAN2_RX1_IRQHandler
CAN2_SCE_IRQHandler
                B       .
                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

;/******************* (C) COPYRIGHT 2016 GIGADEVICE *****END OF FILE****/
