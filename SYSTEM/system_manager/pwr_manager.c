#include "pwr_manager.h"
#include "system_state.h"
#include "delay.h"
#include "rtc.h"
#include "exti_key.h"
#include "value_manager.h"
#include "UI_manager.h"

void pwr_init()
{
    RCC_APB1PeriphClock_Enable(RCC_APB1PERIPH_PWR, ENABLE);
    PWR_BackupAccess_Enable(ENABLE);
    PWR_WKUP_Pin_Enable(PWR_WKUP_PIN_1, DISABLE);
    PWR_ClearBitState(PWR_FLAG_WKUP);
}

u8 check_standby_flag()
{
    if (get_sleep_flag() == SLEEP)
        return SUCCESS;
    else 
        return ERROR;
}

void check_standby_wakeup_button_press()
{
    u8 last_number = 0;
    while ((get_power_on_flag() != POWER_ON_NOW)) {
        delay_ms(300); //If the button is not pressed within 300ms, we do further process.
        if (last_number == get_power_on_flag_number()) {
            clear_power_on_flag();
            enter_stand_by();
        }
        last_number = get_power_on_flag_number();
    }
    reboot_system(SUCCESS);
}

void store_preset_value()
{
    PWR_BackupAccess_Enable(ENABLE);
    value_backup_all();
}

void enter_stand_by()
{
    set_sleep_flag();
    RCC_APB1PeriphClock_Enable(RCC_APB1PERIPH_PWR, ENABLE);
    PWR_WKUP_Pin_Enable(PWR_WKUP_PIN_1, ENABLE);
    PWR_ClearBitState(PWR_FLAG_WKUP);
    PWR_STDBYMode_Entry(PWR_STDBYENTRY_WFI);
}

void enter_deep_sleep()
{
    u8 last_number = 0;
    while ((get_power_on_flag() != POWER_ON_NOW) && (get_system_state() == STATE_SLEEP)) {
        u32 tick = 800000; // 300 ms for 8M
        if (last_number == get_power_on_flag_number()) {
            clear_power_on_flag();
            RCC_APB1PeriphClock_Enable(RCC_APB1PERIPH_PWR, ENABLE);
            PWR_DEEPSLEEPMode_Entry(PWR_LDO_LOWPOWER, PWR_DEEPSLEEPENTRY_WFI);
        }
        last_number = get_power_on_flag_number();
        while(tick > 0)
            tick--;
    }
    reboot_system(SUCCESS);
}

/*
 * reboot and boot up to normal status.
 */
void reboot_system(u8 clear_sleep_flag)
{
    /*
    if (Key_Scan(KEY_GPIO, KEY_INCREASE_PIN) == KEY_ON && Key_Scan(KEY_GPIO, KEY_REDUCE_PIN) == KEY_ON) {
        value_backup_func(MX_FLAG_REG_VALUE, MX_FLAG_OFFSET, MX_FLAG_MASK, GO_TO_ABOUT_MENU);
    } else if (Key_Scan(KEY_GPIO, KEY_INCREASE_PIN) == KEY_ON) {
        value_backup_func(MX_FLAG_REG_VALUE, MX_FLAG_OFFSET, MX_FLAG_MASK, GO_TO_MX_PARAMETER);
    } else if (Key_Scan(KEY_GPIO, KEY_REDUCE_PIN) == KEY_ON) {
        screen_flig_flag_revert();
    }
    */
    /***** WAR for the ADC. *****/
    if (clear_sleep_flag) {
        clear_sleep_state_flags();      //insert a usb will reset the system, won't clear the sleep flag.
    }
    delay_ms(1);                   // In case the system is not ready to reset 
    NVIC_SystemReset();
}

void set_sleep_state_flags()
{
    clear_power_on_flag();
    // If the system is reboot unpected (wdg and so on), the sleep flag is SLEEP.
    // We should not backup the values since the values have not been restored which are all zeros.
    if (get_sleep_flag() == NOT_SLEEP) {
        store_preset_value();
    }
    set_sleep_flag();
}

void clear_sleep_state_flags()
{
    clear_sleep_flag();
    set_reset_flag();
}


void set_sleep_flag()
{
    value_backup_func(SLEEP_FLAG_REG_VALUE, SLEEP_FLAG_OFFSET, SLEEP_FLAG_MASK, SLEEP);
}

void clear_sleep_flag()
{
    value_backup_func(SLEEP_FLAG_REG_VALUE, SLEEP_FLAG_OFFSET, SLEEP_FLAG_MASK, NOT_SLEEP);
}

u8 get_sleep_flag()
{
    return value_restore_func(SLEEP_FLAG_REG_VALUE, SLEEP_FLAG_OFFSET, SLEEP_FLAG_MASK);
}

// To check if the system is boot up by pressing 5 times or unpected boot up.
void set_reset_flag()
{
    value_backup_func(RESET_FLAG_REG_VALUE, RESET_FLAG_OFFSET, RESET_FLAG_MASK, NORMAL_RESET);
}

void clear_reset_flag()
{
    value_backup_func(RESET_FLAG_REG_VALUE, RESET_FLAG_OFFSET, RESET_FLAG_MASK, ABNORMAL_RESET);
}

u8 get_reset_flag()
{
    return value_restore_func(RESET_FLAG_REG_VALUE, RESET_FLAG_OFFSET, RESET_FLAG_MASK);
}


