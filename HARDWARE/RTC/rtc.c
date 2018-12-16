#include "rtc.h"
#include "system_state.h"
#include "value_manager.h"

RTC_InitPara   RTC_InitParameter;
RTC_AlarmPara  RTC_AlarmParameter;

__IO uint32_t asynch_Prediv = 0x63, aynch_Prediv = 0x18F;

void rtc_init()
{

    uint32_t tmp_hh = 0x01;
    /* Enable PWR clock */
    RCC_APB1PeriphClock_Enable(RCC_APB1PERIPH_PWR, ENABLE);
    PWR_BackupAccess_Enable(ENABLE);

    if (value_restore_func(BKP_VALUE_REG_VALUE, BKP_VALUE_OFFSET_VALUE, BKP_VALUE_MASK_VALUE) != BKP_VALUE) {
        RCC_LSI_Enable(ENABLE);
        while(RCC_GetBitState(RCC_FLAG_LSISTB) == RESET)
        {
        }
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
        RCC_RTCCLK_Enable(ENABLE);
        RTC_WaitRSF_ToSetAgain();
        RTC_InitParameter.RTC_Prescaler_Asyn = asynch_Prediv;
        RTC_InitParameter.RTC_Prescaler_Syn = aynch_Prediv;
        RTC_InitParameter.RTC_Year = 0x1;
        RTC_InitParameter.RTC_WeekDay = 0x1;
        RTC_InitParameter.RTC_Month = 0x1;
        RTC_InitParameter.RTC_Date = 0x1;
        RTC_InitParameter.RTC_Hour_Format = RTC_24HOUR;
        RTC_InitParameter.RTC_AM_PM = RTC_AM;
        RTC_InitParameter.RTC_Hour = tmp_hh;
        RTC_InitParameter.RTC_Minute = tmp_hh;
        RTC_InitParameter.RTC_Second = tmp_hh;
        RTC_Config(&RTC_InitParameter, RTC_STORE_NORMAL);
        value_backup_func(BKP_VALUE_REG_VALUE, BKP_VALUE_OFFSET_VALUE, BKP_VALUE_MASK_VALUE, BKP_VALUE);
    } else {
        RCC_LSI_Enable(ENABLE);
        RTC_WaitRSF_ToSetAgain();
        RTC_ClearBitState(RTC_STR_AF);
        EXTI_ClearIntBitState(RTC_EXTI_LINE);
    }
}

void rtc_deinit()
{
    RTC_Alarm_Enable(DISABLE);
    RTC_INT_Enable(RTC_INT_ALRA, DISABLE);
}

void enable_rtc(u16 seconds)
{
    RTC_Alarm_Enable(DISABLE);
    RTC_INT_Enable(RTC_INT_ALRA, DISABLE);
    RTC_GetTimeDate(&RTC_InitParameter, RTC_STORE_NORMAL);
    RTC_AlarmParameter.RTC_Alarm_Mask = RTC_ALARM_MINUTE_MASK;
    RTC_AlarmParameter.RTC_Alarm_Weekday_Sel = RTC_ALARM_DATE_SELECTED;
    RTC_AlarmParameter.RTC_Alarm_Date = RTC_InitParameter.RTC_Date;
    RTC_AlarmParameter.RTC_AM_PM = RTC_InitParameter.RTC_AM_PM;
    RTC_AlarmParameter.RTC_Hour = RTC_InitParameter.RTC_Hour;
    RTC_AlarmParameter.RTC_Minute = RTC_InitParameter.RTC_Minute;
    RTC_AlarmParameter.RTC_Second = (RTC_InitParameter.RTC_Second + seconds)%60;

    /* RTC alarm configuration */
    RTC_SetAlarm(&RTC_AlarmParameter,RTC_STORE_NORMAL);
    RTC_ClearBitState(RTC_STR_AF);
    EXTI_ClearIntBitState(RTC_EXTI_LINE);

    RTC_INT_Enable(RTC_INT_ALRA, ENABLE);
    RTC_Alarm_Enable(ENABLE);
}

void RTC_REENABLE_FEEDDOG()
{
    //if (get_system_state() == STATE_SLEEP)
    enable_rtc(FEED_DOG_TIME);
}

