#include "system_state.h"
#include "value_manager.h"
#include "exti.h"
#include "screen.h"
#include "led.h"
#include "key.h"
#include "oled_content.h"
#include "delay.h"
#include "pwr_manager.h"
#include "adc.h"
#include "timer.h"
#include "rtc.h"
#include "PWM_TIM1.h"
#include "battery_charging_animation.h"
#include "exti_charging.h"
#include "hw_checker.h"
#include "PID.h"
#include "hw_checker_content.h"
#include "low_switch_power.h"
#include "timer.h"
#include "UI_manager.h"
#include "peripherals_manager.h"
#include "pid_console_manager.h"


/*

STATE_CHARGING: charging state with power off.
STATE_NORMAL: Screen on. We can only smoke in this state.
STATE_DISPLAYOFF: screen off. But all the keys are respond to the press event.

*/

static u8 system_state = STATE_SLEEP;
static u8 system_lock = SYS_UNLOCK;
static u8 system_smoke = SYS_NOT_SMOKE;

/*
 * We expect the system canTheoretically, 
 */
void system_init()
{
    init_all_states();
    check_system_state();
    UI_init();
    clear_reset_flag();     // If reset unexpected, won't show boot up animation.
}

void init_all_states()
{
    ENABLE_LOW_SWITCH();
    send_pid_command(CMD_MEAS_VOLTAGE, PID_NOT_RESET);
    delay_ms(50);
    states_reset();
    keys_state_reset();
    values_init();
    peripherals_init();
}

void check_system_state()
{
    if (check_charging() == CHARGING && get_sleep_flag() == SLEEP) {
        // SLEEP but wake up by inserting a USB cable. Don't clear sleep flag since we need to sleep again when unplug the usb
        set_system_state(STATE_CHARGING);
    } else if (check_static_battery() == ERROR) {
        // Low Battery, Power Off.
        OLED_Clear();
        OLED_Display_On();
        show_battery_low_message();
        delay_ms(POWER_OFF_LOGO_TIME);
        set_system_state(STATE_SLEEP);
    } else if (get_sleep_flag() == SLEEP) {
        // Wake up unexpected, go to sleep directly.
        set_system_state(STATE_SLEEP);
    } else {
        set_system_state(STATE_NORMAL);
    }
}

void system_sleep()
{
    // After power off, we don't consider the coil state as ready since we cannot monitor the coil.
    clear_coil_ready_flag();
    set_sleep_state_flags();
    /* DO NOT show the power off animation.
    if (get_sleep_flag() != SLEEP) {
        draw_power_off_screen();
        delay_ms(POWER_OFF_LOGO_TIME);
        
    }
    */

    OLED_Clear();
    OLED_Display_Off();
    // If it is charging, we won't go to sleep mode, we should go to CHARGING state.
    // HACK: reset the system directly for a neccessary hardware initialization.
    if (check_charging() == CHARGING) {
        reboot_system(ERROR);
    }
    
    #ifndef YANMING3
    RTC_REENABLE_FEEDDOG(); // MUST after set type
    #endif

    #ifdef YANMING3
    enter_stand_by();
    #else
    enter_deep_sleep(); // System sleep
    #endif
}

void system_wakeup()
{
    /* DO NOT show the boot up animation.
    if (get_reset_flag() == NORMAL_RESET) { // normal reset means booting up by pressing 5 times.
        draw_power_on_screen();
        delay_ms(BOOT_UP_LOGO_TIME);
    }
    */
    clear_sleep_flag(); // We need this, or we will enter sleep mode again with a unexpected reset.
}

u8 get_system_state()
{
    return system_state;
}

void set_system_state(u8 type)
{
    switch (type) {
        case STATE_NORMAL:
            EXTIX_DeInit();
            send_pid_command(CMD_MEAS_REG, PID_NOT_RESET);
            OLED_Clear();
            OLED_Display_On();
            system_wakeup();
            system_state = type;
            break;
        case STATE_DISPLAYOFF:
            OLED_Display_Off();
            system_state = type;
            break;
        case STATE_SLEEP:
            states_reset();
            EXTIX_Init();
            TIMx_Int_DeInit();
            ADC1_Deinit();
            system_state = type;
            system_sleep();
            break;
        case STATE_CHARGING:
            OLED_Clear();
            EXTIX_DeInit();
            TIMx_Int_Init();
            system_state = type;
            break;
    }
}

/*************** Flags ************************/

/* Boot up, reset the all the states */
void states_reset()
{
    system_smoke = SYS_NOT_SMOKE;
    system_lock = SYS_UNLOCK;
}

/* Check if it is really smoking or not */
void set_system_smoke(u8 smoke)
{
    system_smoke = smoke;
}

u8 get_system_smoke()
{
    return system_smoke;
}

/* If system lock, nothing will be respond  */
void set_system_lock(u8 lock)
{
    system_lock = lock;
}

void system_lock_revert()
{
    system_lock = !system_lock;
}

u8 get_system_lock()
{
    return system_lock;
}

/* Boot up flag.
 * It is not a cold boot(with battery died), we dont need to wait extra 2s for oled.
 * We don't need this anymore.
 
void set_boot_flag()
{
    value_backup_func(BOOT_UP_FLAG_REG_VALUE, BOOT_UP_FLAG_OFFSET_VALUE, BOOT_UP_FLAG_MASK_VALUE, COLD_BOOT_UP);
}

u8 get_boot_flag()
{
    return value_restore_func(BOOT_UP_FLAG_REG_VALUE, BOOT_UP_FLAG_OFFSET_VALUE, BOOT_UP_FLAG_MASK_VALUE);
}
*/

/*  
*/

void screen_flip_flag_revert()
{
    if (get_screen_flip_flag() == SYS_SCREEN_FLIP)
        clear_screen_flip_flag();
    else
        set_screen_flip_flag();
}

void set_screen_flip_flag()
{
    value_backup_func(SCREEN_FLIP_FLAG_REG_VALUE, SCREEN_FLIP_FLAG_OFFSET_VALUE, SCREEN_FLIP_FLAG_MASK_VALUE, SYS_SCREEN_FLIP);
    
}

void clear_screen_flip_flag()
{
    value_backup_func(SCREEN_FLIP_FLAG_REG_VALUE, SCREEN_FLIP_FLAG_OFFSET_VALUE, SCREEN_FLIP_FLAG_MASK_VALUE, SYS_SCREEN_NORMAL);
}

u8 get_screen_flip_flag()
{
    return value_restore_func(SCREEN_FLIP_FLAG_REG_VALUE, SCREEN_FLIP_FLAG_OFFSET_VALUE, SCREEN_FLIP_FLAG_MASK_VALUE);
}

