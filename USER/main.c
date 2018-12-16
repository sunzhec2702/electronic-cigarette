#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "exti.h"
#include "key.h"
#include "timer.h"
#include "adc.h"
#include "iwdg.h"
#include "rtc.h"
#include "low_switch_power.h"
#include "exti_rtc.h"
#include "exti_key.h"
#include "exti_charging.h"
#include "PID.h"
#include "PWM_TIM1.h"
#include "value_manager.h"
#include "pid_console_manager.h"
#include "peripherals_manager.h"
#include "pwr_manager.h"
#include "system_state.h"
#include "hw_checker.h"
#include "task_scheduler.h"
#include "battery_charging_animation.h"
#include "oled_content.h"




int main(void)
{
    // Hardware Init
    delay_init();	    	 //延时函数初始化
    pwr_init();
    #ifdef YANMING3
    charger_init();
    if (check_standby_flag() == SUCCESS && check_charging() != CHARGING) {
        Key_GPIO_Config();
        exti_key_init();
        #ifdef DEBUG_POWER_OFF_WAKE_UP
        OLED_Init();
        OLED_Clear();
        OLED_Display_On();
        draw_about_mesage();
        #endif
        check_standby_wakeup_button_press();
        // If we boot up from standby by pressing 5 times, the system will reboot again without
        // this code block.
    }
    #endif

    // OLED Init
    OLED_Init();
    OLED_Clear();
    //
    low_switch_power_init();

    TIMx_Int_DeInit();
    EXTIX_DeInit();
    
    // Key
    Key_GPIO_Config();
    
    // PID related code
    ADC1_Configuration();
    PWM_Configuration();
    VoltagePID_Init();

    TIMx_Int_Init();
    rtc_init();

    // Our Init
    system_init();
    #ifndef YANMING3
    //iwdg_init();
    #endif

    while(1) {
        #ifndef YANMING3
        //iwdg_feed();
        #endif
        task_schedule();
    }
}
