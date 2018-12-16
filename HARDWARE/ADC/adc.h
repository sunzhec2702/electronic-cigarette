#ifndef __ADC1_SAMPLE_H
#define __ADC1_SAMPLE_H

#include <sys.h>
#include "pid.h"

/* Private define ------------------------------------------------------------*/

#define ADC_RDTR_Address        ((uint32_t)0x4001244C)

#define TIM_KHZ			(F_CTRL/1000) // Khz

#define PEROID_MS_N  (TIM_KHZ)  // 1ms = delay PEROID_MS_N times;

#define PWR_START_DELAY_MS	( 10 )  // 10ms
#define R_MEAS_DELAY_MS			( 80 )  // 80ms
#define PWR_RESET_DELAY_MS	( 10 )  // 10ms
#define VOL_STABLE_DELAY_MS	( 1 ) // 1 ms
#define PID_STOP_DELAY_MS	( 100 ) // 100 ms


#define PWR_START_DELAY_N   ( PWR_START_DELAY_MS * PEROID_MS_N)
#define R_MEAS_DELAY_N			( R_MEAS_DELAY_MS * PEROID_MS_N )
#define PWR_RESET_DELAY_N   ( PWR_RESET_DELAY_MS * PEROID_MS_N)
#define VOL_STABLE_DELAY_N	( VOL_STABLE_DELAY_MS * PEROID_MS_N )
#define PID_STOP_DELAY_N		( PID_STOP_DELAY_MS * PEROID_MS_N)



/***  start ----- 等待电源起来10ms ------  再给个固定占空比1/4 50ms测电阻 ---------  正常PID启动   ***************/


/* Private function prototypes -----------------------------------------------*/
extern void ADC1_Configuration(void);
extern u16 get_key_voltage(void);
extern uint16_t * Get_ADC1_ConvertData_Addr(void);
extern void ADC1_Deinit(void);

// test use configuration
void DBG_GPIO_Configuration(void);



#endif
