#include "value_manager.h"
#include "delay.h"
#include "UI_manager.h"
#include "peripherals_manager.h"
#include "key.h"
#include "PID.h"

static Sense_Value* sense_value;
static PID_Components* pid_components;

void values_init()
{
    sense_value = get_sense_value();
    pid_components = get_pid_components();
}

void value_update_step(u32* current_value_pt, u16* step_array, u8 step_index, u8 key_type, u16 min, u16 max)
{
    u32 temp_value;
    u16 step = step_array[step_index];
    if (key_type == KEY_INCREASE)
        temp_value = *current_value_pt + step;
    else if (key_type == KEY_REDUCE)
        temp_value = *current_value_pt - step;

    if (temp_value <= max && temp_value >= min) {
        *current_value_pt = temp_value;
    } else if (step_index > 0) {
        value_update_step(current_value_pt, step_array,step_index-1, key_type, min, max);
    } else {
        if (temp_value > max) {
            *current_value_pt = max;
        } else if (temp_value < min) {
            *current_value_pt = min;
        }
    }
}

u16 value_read(u8 value_type)
{
    switch (value_type) {
        case VOLTAGE_VALUE:
            return  (sense_value->Vo_q15 * 100) >> 15;
        case REGISTER_VALUE:
            if (value_read(COIL_EXIST_FLAG) == COIL_NOT_EXIST)
                return REG_OPEN;
            if (((sense_value->Rload_q15 * 100) >> 15) > 1000)
                return REG_OPEN;
            else
                return  (sense_value->Rload_q15 * 100) >> 15;
        case REGISTER_STATIC_VALUE:
            return get_coil_r_static();
        case BATTERY_VALUE:
            Updata_SenseValue();
            return (sense_value->Vi_q15 * 100) >> 15;
        case CURRENT_VALUE:
            return (sense_value->Io_q15 * 100) >> 15;
        case TEMPERATURE_FLAG:
            return (sense_value->flag_over_temp);
        case STATIC_BATTERY_VALUE:
            if (((sense_value->static_vbat_q15 * 100) >> 15) == 0)
                return value_read(BATTERY_VALUE);
            else
                return (sense_value->static_vbat_q15 * 100) >> 15;
        case MAX_PRESET_VOLTAGE_VALUE:
            return (sense_value->Max_voltage_limit_q15 * 100) >> 15;
        case COIL_EXIST_FLAG:
            return (Get_R_Exist_flag());
        case NTC_TEMPERATURE:
            return (sense_value->NTC_Temp_q15 >>15);
        case COIL_TEMPERATURE:
            return (sense_value->Temp_q15 >> 15);
        case PID_POWER_SET_VALUE:
            return (pid_components->Power_set) * 10 >> 15;
        case PID_POWER_RT_OUT_VALUE:
            return (sense_value->Pout_q15) * 10 >> 15;
        default:
            return 0xFFFF;
    }
}

void value_write(u8 value_type, u32 value)
{
    switch(value_type) {
        case REGISTER_STATIC_VALUE:
            sense_value->Rstatic_q15 = (value<<15)/100;
            break;
        case TCR_KKM_VALUE:
            sense_value->TCR_PPK_Q15 = (value<<15)/1000;
            break;
        case MAX_PRESET_POWER_VALUE:
            sense_value->Max_power_limit_q15 = (value)<<15;
            break;
    }
    
}

void value_backup_func(u8 reg_index, u8 offset, u16 len_mask, u16 value)
{
    volatile u32 *reg_pointer;
    u32 clear_value = ~(len_mask << offset);
    u32 set_value = ((value & len_mask) << offset);

    switch (reg_index) {
    case 0:
        reg_pointer = &RTC->BKP0R;
        break;
    case 1:
        reg_pointer = &RTC->BKP1R;
        break;
    case 2:
        reg_pointer = &RTC->BKP2R;
        break;
    case 3:
        reg_pointer = &RTC->BKP3R;
        break;
    case 4:
        reg_pointer = &RTC->BKP4R;
        break;
    default:
        break;
    }
    *reg_pointer &= clear_value;
    *reg_pointer |= set_value;
}

u16 value_restore_func(u8 reg_index, u8 offset, u16 len_mask)
{
    volatile u32 *reg_pointer;
    u16 read_value;
    switch (reg_index) {
    case 0:
        reg_pointer = &RTC->BKP0R;
        break;
    case 1:
        reg_pointer = &RTC->BKP1R;
        break;
    case 2:
        reg_pointer = &RTC->BKP2R;
        break;
    case 3:
        reg_pointer = &RTC->BKP3R;
        break;
    case 4:
        reg_pointer = &RTC->BKP4R;
        break;
    default:
        break;
    }
    read_value = ((*reg_pointer) & (len_mask<<offset)) >> offset;
    return read_value;
}
