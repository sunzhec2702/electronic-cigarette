#include "menu_mx_parameter_value_manager.h"
#include "key.h"
#include "oled_content.h"
#include "value_manager.h"

static u8 mx_mode_index = 0;
static u8 cursor_index = CURSOR_AT_MODE;
static u32 mx_rtc[MX_MODE_NUMBER] = {0};
static u32 mx_power_value[MX_MODE_NUMBER] = {0};
static u16 step[] = {0,1000,100,10,1};
static u16 power_step[] = {1};

u32* mx_parameter_get_value_pointer(u8 para)
{
    if (para == NULL) {
        return &mx_rtc[mx_mode_index];
    } else if (para == CURSOR_AT_POWER_VALUE) {
        return &mx_power_value[mx_mode_index];
    }
    return NULL;
}

void mx_parameter_mode_index_callback(u8 key_type)
{
    switch (key_type) {
        case KEY_INCREASE:
            mx_mode_index++;
            mx_mode_index%=MX_MODE_NUMBER;
            break;
        case KEY_REDUCE:
            mx_mode_index+=MX_MODE_NUMBER;
            mx_mode_index--;
            mx_mode_index%=MX_MODE_NUMBER;
            break;
        default:
            break;
    }
    draw_mx_mode_icon(mx_mode_index, 0);
}

void mx_parameter_cursor_callback(u8 key_type)
{
    if (key_type != KEY_CONFIRM)
        return;
    cursor_index++;
    cursor_index%=CUROR_AT_NUMBER;
}

void mx_parameter_value_callback(u8 key_type)
{
    switch (key_type) {
        case KEY_INCREASE:
            if (cursor_index == CURSOR_AT_POWER_VALUE) {
                value_update_step(&mx_power_value[mx_mode_index], power_step, 0, key_type, MIN_MX_POWER_VALUE, MAX_MX_POWER_VALUE);
            } else {
                mx_rtc[mx_mode_index]+=step[cursor_index];
                if ((mx_rtc[mx_mode_index]/step[cursor_index])%10 == 0) {
                    mx_rtc[mx_mode_index]-=step[cursor_index-1];
                }
            }
            break;
        case KEY_REDUCE:
            if (cursor_index == CURSOR_AT_POWER_VALUE) {
                value_update_step(&mx_power_value[mx_mode_index], power_step, 0, key_type, MIN_MX_POWER_VALUE, MAX_MX_POWER_VALUE);
            } else {
                mx_rtc[mx_mode_index]+=10000;
                mx_rtc[mx_mode_index]-=step[cursor_index];
                mx_rtc[mx_mode_index]%=10000;
                if ((mx_rtc[mx_mode_index]/step[cursor_index])%10 == 9) {
                    mx_rtc[mx_mode_index]+=step[cursor_index-1];
                }
            }
            break;
    }
}

u8 get_mx_mode()
{
    return mx_mode_index;
}

u8 get_cursor_index()
{
    return cursor_index;
}

void menu_mx_parameter_value_backup()
{
    value_backup_func(M1_TRC_REG_INDEX, M1_TRC_OFFSET, M1_TRC_LEN_MASK, mx_rtc[0]);
    value_backup_func(M2_TRC_REG_INDEX, M2_TRC_OFFSET, M2_TRC_LEN_MASK, mx_rtc[1]);
    value_backup_func(M3_TRC_REG_INDEX, M3_TRC_OFFSET, M3_TRC_LEN_MASK, mx_rtc[2]);
    value_backup_func(M1_MAX_POWER_REG_INDEX, M1_MAX_POWER_OFFSET, M1_MAX_POWER_LEN_MASK, mx_power_value[0]);
    value_backup_func(M2_MAX_POWER_REG_INDEX, M2_MAX_POWER_OFFSET, M2_MAX_POWER_LEN_MASK, mx_power_value[1]);
    value_backup_func(M3_MAX_POWER_REG_INDEX, M3_MAX_POWER_OFFSET, M3_MAX_POWER_LEN_MASK, mx_power_value[2]);
}

void menu_mx_parameter_value_restore()
{
    u8 index;
    mx_rtc[0] = value_restore_func(M1_TRC_REG_INDEX, M1_TRC_OFFSET, M1_TRC_LEN_MASK);
    mx_rtc[1] = value_restore_func(M2_TRC_REG_INDEX, M2_TRC_OFFSET, M2_TRC_LEN_MASK);
    mx_rtc[2] = value_restore_func(M3_TRC_REG_INDEX, M3_TRC_OFFSET, M3_TRC_LEN_MASK);
    for(index=0;index<MX_MODE_NUMBER;index++) {
        if (mx_rtc[index]==0)
            mx_rtc[index] = DEFAULT_MX_VALUE;
    }
    mx_power_value[0] = value_restore_func(M1_MAX_POWER_REG_INDEX, M1_MAX_POWER_OFFSET, M1_MAX_POWER_LEN_MASK);
    mx_power_value[1] = value_restore_func(M2_MAX_POWER_REG_INDEX, M2_MAX_POWER_OFFSET, M2_MAX_POWER_LEN_MASK);
    mx_power_value[2] = value_restore_func(M3_MAX_POWER_REG_INDEX, M3_MAX_POWER_OFFSET, M3_MAX_POWER_LEN_MASK);
    for(index=0;index<MX_MODE_NUMBER;index++) {
        if (mx_power_value[index]==0)
            mx_power_value[index] = DEFAULT_MX_POWER_VALUE;
    }
}




