#include "menu_mx_tcr_value_manager.h"
#include "key.h"
#include "UI_manager.h"
#include "oled_content.h"
#include "value_manager.h"

static u32 mx_tcr[MX_MODE_NUMBER] = {0};
static u32 mx_max_power[MX_MODE_NUMBER] = {0};

u32* mx_tcr_get_value_pointer(u8 para)
{
    if (para != NULL) {
        return (u32*)&mx_tcr[para - MAIN_MENU_TEMP_M1_ID];
    }
    return NULL;
}

u32* mx_max_power_get_value_pointer(u8 para)
{
    if (para != NULL) {
        return (u32*)&mx_max_power[para - MAIN_MENU_TEMP_M1_ID];
    }
    return NULL;
}

void menu_mx_parameter_value_backup()
{
    value_backup_func(M1_TRC_REG_INDEX, M1_TRC_OFFSET, M1_TRC_LEN_MASK, mx_tcr[0]);
    value_backup_func(M2_TRC_REG_INDEX, M2_TRC_OFFSET, M2_TRC_LEN_MASK, mx_tcr[1]);
    value_backup_func(M3_TRC_REG_INDEX, M3_TRC_OFFSET, M3_TRC_LEN_MASK, mx_tcr[2]);
    
    value_backup_func(M1_MAX_POWER_REG_INDEX, M1_MAX_POWER_OFFSET, M1_MAX_POWER_LEN_MASK, mx_max_power[0]);
    value_backup_func(M2_MAX_POWER_REG_INDEX, M2_MAX_POWER_OFFSET, M2_MAX_POWER_LEN_MASK, mx_max_power[1]);
    value_backup_func(M3_MAX_POWER_REG_INDEX, M3_MAX_POWER_OFFSET, M3_MAX_POWER_LEN_MASK, mx_max_power[2]);
    
}

void menu_mx_parameter_value_restore()
{
    u8 index;
    mx_tcr[0] = value_restore_func(M1_TRC_REG_INDEX, M1_TRC_OFFSET, M1_TRC_LEN_MASK);
    mx_tcr[1] = value_restore_func(M2_TRC_REG_INDEX, M2_TRC_OFFSET, M2_TRC_LEN_MASK);
    mx_tcr[2] = value_restore_func(M3_TRC_REG_INDEX, M3_TRC_OFFSET, M3_TRC_LEN_MASK);
    for(index = 0; index < MX_MODE_NUMBER; index++) {
        if (mx_tcr[index] == 0)
            mx_tcr[index] = DEFAULT_MX_TCR_VALUE;
    }
    
    mx_max_power[0] = value_restore_func(M1_MAX_POWER_REG_INDEX, M1_MAX_POWER_OFFSET, M1_MAX_POWER_LEN_MASK);
    mx_max_power[1] = value_restore_func(M2_MAX_POWER_REG_INDEX, M2_MAX_POWER_OFFSET, M2_MAX_POWER_LEN_MASK);
    mx_max_power[2] = value_restore_func(M3_MAX_POWER_REG_INDEX, M3_MAX_POWER_OFFSET, M3_MAX_POWER_LEN_MASK);
    for(index = 0; index < MX_MODE_NUMBER; index++) {
        if (mx_max_power[index] == 0)
            mx_max_power[index] = DEFAULT_MX_POWER_VALUE;
    }
}




