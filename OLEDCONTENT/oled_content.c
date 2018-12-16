#include "oled_content.h"
#include "value_manager.h"
#include "system_state.h"
#include "oled.h"
#include "bmp.h"
#include "oled_content_muxlock.h"
#include "peripherals_manager.h"
#include "battery_manager.h"
#include "UI_manager.h"
#include "main_menu_temperature_value_manager.h"

void draw_battery_icon(u8 level)
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_DrawBMP(0, 0, 9, 2, BatteryF9x16[level]);
        unlock_oled();
    }
}

void draw_battery_icon_charge(u8 level)
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_DrawBMP(0, 0, 9, 2, BatteryChargeF9x16[level]);
        unlock_oled();
    }
}

void draw_current_lock_icon()
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        if (get_value_key_lock() == SYS_LOCK) {
            OLED_DrawBMP(11, 0, 16, 2, LockIconF4x16);
        } else {
            OLED_SHOW_SPACE(9,0,16,7);
        }
        unlock_oled();
    }
}

void draw_register_value(u16 reg_value)
{
    u16 int_value, dec_value1, dec_value2;
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
#ifdef DEBUG_CHARGING_BATTERY_VALUE
        int_value = (u16) (reg_value / 100) % 10;
        dec_value1 = (u16) (reg_value / 10) % 10;
        dec_value2 = (u16) (reg_value) % 10;
        OLED_ShowNum(16, 0, int_value, 1, 8, 1);
        OLED_DrawBMP(22, 0, 23, 1, PointF1x8);
        OLED_ShowNum(23, 0, dec_value1, 1, 8, 1);
        OLED_ShowNum(29, 0, dec_value2, 1, 8, 1);
        OLED_DrawBMP(36, 0, 42, 1, OMEGAF6x8);
        unlock_oled();
        return;
#endif
        if (reg_value != REG_OPEN && value_read(COIL_EXIST_FLAG) != COIL_NOT_EXIST) {
            int_value = (u16) (reg_value / 100) % 10;
            dec_value1 = (u16) (reg_value / 10) % 10;
            dec_value2 = (u16) (reg_value) % 10;
            OLED_ShowNum(16, 0, int_value, 1, 8, 1);
            OLED_DrawBMP(22, 0, 23, 1, PointF1x8);
            OLED_ShowNum(23, 0, dec_value1, 1, 8, 1);
            OLED_ShowNum(29, 0, dec_value2, 1, 8, 1);
            OLED_DrawBMP(36, 0, 42, 1, OMEGAF6x8);
        } else {
            OLED_DrawBMP(16, 0, 22, 1, UNDERSTOKEF6x8);
            OLED_DrawBMP(22, 0, 23, 1, PointF1x8);
            OLED_DrawBMP(23, 0, 29, 1, UNDERSTOKEF6x8);
            OLED_DrawBMP(29, 0, 35, 1, UNDERSTOKEF6x8);
            OLED_DrawBMP(36, 0, 42, 1, OMEGAF6x8);
        }
        unlock_oled();
    }
}

void draw_voltage_value(u16 vol_value)
{
    u16 int_value, dec_value1, dec_value2;
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
#ifdef DEBUG_CHARGING_BATTERY_VALUE
        int_value = (u16) (vol_value / 100) % 10;
        dec_value1 = (u16) (vol_value / 10) % 10;
        dec_value2 = (u16) (vol_value) % 10;
        OLED_ShowNum(16, 1, int_value, 1, 8, 1);
        OLED_DrawBMP(22, 1, 23, 2, PointF1x8);
        OLED_ShowNum(23, 1, dec_value1, 1, 8, 1);
        OLED_ShowNum(29, 1, dec_value2, 1, 8, 1);
        OLED_ShowChar(36, 1, 'V', 8);
        unlock_oled();
        return;
#endif
        if (value_read(REGISTER_VALUE) != REG_OPEN && value_read(COIL_EXIST_FLAG) != COIL_NOT_EXIST) {
            int_value = (u16) (vol_value / 100) % 10;
            dec_value1 = (u16) (vol_value / 10) % 10;
            dec_value2 = (u16) (vol_value) % 10;
            OLED_ShowNum(16, 1, int_value, 1, 8, 1);
            OLED_DrawBMP(22, 1, 23, 2, PointF1x8);
            OLED_ShowNum(23, 1, dec_value1, 1, 8, 1);
            OLED_ShowNum(29, 1, dec_value2, 1, 8, 1);
            OLED_ShowChar(36, 1, 'V', 8);
        } else {
            OLED_DrawBMP(16, 1, 22, 2, UNDERSTOKEF6x8);
            OLED_DrawBMP(22, 1, 23, 2, PointF1x8);
            OLED_DrawBMP(23, 1, 29, 2, UNDERSTOKEF6x8);
            OLED_DrawBMP(29, 1, 35, 2, UNDERSTOKEF6x8);
            OLED_ShowChar(36, 1, 'V', 8);
        }
        unlock_oled();
    }
}

void draw_pid_power_out_value(u16 pid_power_value)
{
    u16 int_value, dec_value;
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        if (value_read(REGISTER_VALUE) != REG_OPEN && value_read(COIL_EXIST_FLAG) != COIL_NOT_EXIST) {
            /*
            if (get_system_smoke() != SYS_SMOKE && get_system_smoke() != SYS_SMOKE_DONE) {
                int_value = 0;
                dec_value = 0;
            } else {*/
            int_value = (u16) (pid_power_value/10);
            dec_value = (u16) (pid_power_value) % 10;
            //}
            OLED_ShowNum(16, 1, int_value, 2, 8, 1);
            OLED_DrawBMP(28, 1, 29, 2, PointF1x8);
            OLED_ShowNum(29, 1, dec_value, 1, 8, 1);
            OLED_ShowChar(36, 1, 'W', 8);
        } else {
            OLED_DrawBMP(16, 1, 22, 2, UNDERSTOKEF6x8);
            OLED_DrawBMP(22, 1, 23, 2, PointF1x8);
            OLED_DrawBMP(23, 1, 29, 2, UNDERSTOKEF6x8);
            OLED_DrawBMP(29, 1, 35, 2, UNDERSTOKEF6x8);
            OLED_ShowChar(36, 1, 'W', 8);
        }
        unlock_oled();
    }
}

void draw_power_value(u16 power_value)
{
    u16 int_value1, int_value2, dec_value;
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();

        int_value1 = (u16) (power_value / 100) % 10;
        int_value2 = (u16) (power_value / 10) % 10;
        dec_value = (u16) (power_value) % 10;
        OLED_ShowChar_Bold(47, 0, int_value1 + '0', 16);
        OLED_ShowChar_Bold(55, 0, int_value2 + '0', 16);
        OLED_DrawBMP(63, 0, 67, 2, BoldPointF4x16);
        OLED_ShowChar_Bold(67, 0, dec_value + '0', 16);
        OLED_SHOW_SPACE(75,0,16,2);
        OLED_DrawBMP(77, 0, 87, 2, BoldPowerUnit);
        OLED_SHOW_SPACE(87,0,16,9);
        unlock_oled();
    }
}

void draw_temperature_value(u16 temperature_value, u8 ui_id, u8 degree_mode)
{
    u16 int_value1, int_value2, dec_value;
    const unsigned char* temp_mode_content;
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();

        switch (degree_mode) {
        case DEGREE_C:
            OLED_DrawBMP(73, 1, 85, 2, TempUnitCF10x8);
            break;
        case DEGREE_F:
            temperature_value+=TEMP_DEGREE_SWITCH_OFFSET;
            OLED_DrawBMP(73, 1, 85, 2, TempUnitFF10x8);
            break;
        default:
            OLED_DrawBMP(73, 1, 85, 2, TempUnitCF10x8);
            break;
        }
        int_value1 = (u16) (temperature_value / 100) % 10;
        int_value2 = (u16) (temperature_value / 10) % 10;
        dec_value = (u16) (temperature_value) % 10;
        OLED_ShowChar_Bold(47, 0, int_value1 + '0', 16);
        OLED_ShowChar_Bold(55, 0, int_value2 + '0', 16);
        OLED_ShowChar_Bold(63, 0, dec_value + '0', 16);
        OLED_SHOW_SPACE(71,0,16,2);
        switch (ui_id) {
        case MAIN_MENU_TEMP_NI_ID:
            temp_mode_content = TempModeNiF10x8;
            break;
        case MAIN_MENU_TEMP_TI_ID:
            temp_mode_content = TempModeTiF10x8;
            break;
        case MAIN_MENU_TEMP_SS_ID:
            temp_mode_content = TempModeSSF10x8;
            break;
        case MAIN_MENU_TEMP_M1_ID:
            temp_mode_content = TempModeM1F10x8;
            break;
        case MAIN_MENU_TEMP_M2_ID:
            temp_mode_content = TempModeM2F10x8;
            break;
        case MAIN_MENU_TEMP_M3_ID:
            temp_mode_content = TempModeM3F10x8;
            break;
        default:
            temp_mode_content = TempModeNiF10x8;
            break;
        }
        OLED_DrawBMP(73, 0, 85, 1, temp_mode_content);
        OLED_SHOW_SPACE(85,0,16,11);
        unlock_oled();
    }
}

void draw_preset_voltage_value(u16 preset_voltage_value)
{
    u16 int_value, dec_value1, dec_value2;
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        int_value = (u16) (preset_voltage_value / 100) % 10;
        dec_value1 = (u16) (preset_voltage_value / 10) % 10;
        dec_value2 = (u16) (preset_voltage_value) % 10;
        OLED_ShowChar_Bold(47, 0, int_value + '0', 16);
        OLED_DrawBMP(55, 0, 59, 2, BoldPointF4x16);
        OLED_ShowChar_Bold(59, 0, dec_value1 + '0', 16);
        OLED_ShowChar_Bold(67, 0, dec_value2 + '0', 16);
        OLED_SHOW_SPACE(75,0,16,2);
        OLED_DrawBMP(77, 0, 87, 2, BoldVolUnit);
        OLED_SHOW_SPACE(87,0,16,9);
        unlock_oled();
    }
}

void draw_bypass_value(void)
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_ShowString_Mode(47, 0, "BYPASS", 16, 1);
        OLED_SHOW_SPACE(95,0,16,1);
        unlock_oled();
    }
}

void draw_smoke_time(u16 smoke_time)
{
    u16 int_value1, int_value2, dec_value;
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        int_value1 = (u16) (smoke_time / 100) % 10;
        int_value2 = (u16) (smoke_time / 10) % 10;
        dec_value = (u16) (smoke_time) % 10;
        OLED_SHOW_SPACE(45,0,16,11);
        OLED_ShowChar_SMALL(56, 0, int_value1 + '0', 16);
        OLED_ShowChar_SMALL(63, 0, int_value2 + '0', 16);
        OLED_DrawBMP(70, 0, 72, 2, SMALLPOINTF2x16);
        OLED_ShowChar_SMALL(72, 0, dec_value + '0', 16);
        OLED_DrawBMP(79, 0, 85, 2, SMALLSecondUnit);
        OLED_SHOW_SPACE(85,0,16,11);
        unlock_oled();
    }
}

void draw_current_value(u8 type)
{
    switch (type) {
    case VOLTAGE_VALUE:
        draw_voltage_value(value_read(VOLTAGE_VALUE));
        break;
    case REGISTER_VALUE:
        draw_register_value(value_read(REGISTER_VALUE));
        break;
    case PID_POWER_SET_VALUE:
        draw_pid_power_out_value(value_read(PID_POWER_SET_VALUE));
        break;
    case PID_POWER_RT_OUT_VALUE:
        draw_pid_power_out_value(value_read(PID_POWER_RT_OUT_VALUE));
        break;
    default:
        break;
    }
}

void draw_current_battery()
{
    u8 level = get_battery_level();
    if (level == BATTERY_LEVEL_NOT_INIT)
        return;
    if (get_charger_plug_flag() == CHARGER_PLUGGED)
        draw_battery_icon_charge(level);
    else
        draw_battery_icon(level);
}

void draw_coil_string()
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_ShowString_Mode(0, 0, "COIL", 8, 1);
        unlock_oled();
    }
}

void draw_coil_choose_menu()
{
    u8 mode = 1;
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_SHOW_SPACE(24, 0, 16, 6);
        OLED_ShowString_Mode(30, 0, "NEW", 8, mode);
        OLED_SHOW_SPACE(48, 0, 16, 3);
        OLED_ShowString_Mode(51, 0, "or", 8, mode);
        OLED_SHOW_SPACE(63, 0, 16, 3);
        OLED_ShowString_Mode(66, 0, "SAME", 8, mode);
        OLED_SHOW_SPACE(90, 0, 16, 6);
        OLED_DrawBMP(37, 1, 40, 2, LEFTARRAYF3x8);
        OLED_DrawBMP(77, 1, 80, 2, RIGHTARRAYF3x8);
        /*
        OLED_ShowString_Mode(27, 1, "LEFT", 8, mode);
        OLED_ShowString_Mode(63, 1, "RIGHT", 8, mode);
        */
        unlock_oled();
    }
}

void draw_real_time_coil_temperature(u16 temperature, u8 degree_mode)
{
    u16 int_value1, int_value2, dec_value;
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        switch (degree_mode) {
            case DEGREE_C:
                OLED_DrawBMP(79, 1, 89, 2, TempUnitCF10x8);
                break;
            case DEGREE_F:
                temperature+=TEMP_DEGREE_SWITCH_OFFSET;
                OLED_DrawBMP(79, 1, 89, 2, TempUnitFF10x8);
                break;
            default:
                OLED_DrawBMP(79, 1, 89, 2, TempUnitCF10x8);
                break;
        }
        int_value1 = (u16) (temperature / 100) % 10;
        int_value2 = (u16) (temperature / 10) % 10;
        dec_value = (u16) (temperature) % 10;
        OLED_SHOW_SPACE(45,0,16,11);
        OLED_ShowChar_SMALL(56, 0, int_value1 + '0', 16);
        OLED_ShowChar_SMALL(63, 0, int_value2 + '0', 16);
        OLED_ShowChar_SMALL(70, 0, dec_value + '0', 16);
        OLED_SHOW_SPACE(77,0,16,2);
        OLED_SHOW_SPACE(79,0,8,10);
        OLED_SHOW_SPACE(89,0,16,7);
        unlock_oled();
    }
}

void draw_mx_mode_icon(u8 mx, u8 mode)
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_SHOW_SPACE(0,0,16,5);
        OLED_ShowChar_Mode(5, 0, 'M', 16, mode);
        OLED_ShowChar_Mode(13, 0, '0'+mx, 16, mode);
        //OLED_SHOW_SPACE(21,0,16,5);
        unlock_oled();
    }
}

void draw_mx_tcr_string(u8 mode)
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_SHOW_SPACE(21,0,16,5);
        OLED_ShowString_Mode(26, 0, "TCR", 16, mode);
        //OLED_SHOW_SPACE(21,0,16,5);
        unlock_oled();
    }
}

void draw_mx_max_power_string(u8 mode)
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_SHOW_SPACE(21,0,16,5);
        OLED_ShowString_Mode(26, 0, "Max", 16, mode);
        //OLED_SHOW_SPACE(21,0,16,5);
        unlock_oled();
    }
}


/*
void draw_mx_value(u16 mx_value, u8 cursor_index)
{

    u16 int_value1, int_value2, int_value3, int_value4;
    int_value1 = (u16) (mx_value / 1000) % 10;
    int_value2 = (u16) (mx_value / 100) % 10;
    int_value3 = (u16) (mx_value / 10) % 10;
    int_value4 = (u16) mx_value % 10;
    OLED_ShowChar_Mode(26, 0, int_value1 + '0', 16, (cursor_index == 1)?0:1);
    OLED_ShowChar_Mode(34, 0, int_value2 + '0', 16, (cursor_index == 2)?0:1);
    OLED_ShowChar_Mode(42, 0, int_value3 + '0', 16, (cursor_index == 3)?0:1);
    OLED_ShowChar_Mode(50, 0, int_value4 + '0', 16, (cursor_index == 4)?0:1);

}
*/

void draw_mx_value(u16 mx_value, u8 mode)
{
    u16 int_value2, int_value3, int_value4;
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        int_value2 = (u16) (mx_value / 100) % 10;
        int_value3 = (u16) (mx_value / 10) % 10;
        int_value4 = (u16) mx_value % 10;
        OLED_ShowChar_Mode(64, 0, int_value2 + '0', 16, mode);
        OLED_ShowChar_Mode(72, 0, int_value3 + '0', 16, mode);
        OLED_ShowChar_Mode(80, 0, int_value4 + '0', 16, mode);
        OLED_ShowChar_Mode(88, 0, '0', 16, mode);
        unlock_oled();
    }
}

void draw_mx_max_power_value(u32 mx_power_value, u8 cursor_index)
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_ShowNum(63, 0, mx_power_value, 2, 16, (cursor_index == 5)?0:1);
        OLED_ShowChar_Mode(81, 0, 'W', 16, 1);
        OLED_SHOW_SPACE(89,0,16,7);
        unlock_oled();
    }
}

void draw_about_mesage()
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_SHOW_SPACE(0, 0, 16, 5);
        OLED_ShowString_Mode(5, 0, "bozztek.com", 8, 1);
        unlock_oled();
    }
}

void draw_software_verion_mesage(u8 ver1, u8 ver2, u8 ver3, u8 release)
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_ShowString_Mode(56, 1, "ver", 8, 1);
        if (release) {
            OLED_ShowNum(72, 1, ver1, 1, 8, 1);
        } else {
            OLED_ShowNum(72, 1, ver1, 1, 8, 1);
            OLED_ShowNum(78, 1, ver2, 1, 8, 1);
            OLED_ShowNum(84, 1, ver3, 1, 8, 1);
        }
        unlock_oled();
    }
}

void draw_menu_select_array(u8 x, u8 y, u8 direction)
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        switch (direction) {
            case 0:
                OLED_DrawBMP(x, y, x+3, y+2, LEFTARRAYF3x16);
                break;
            case 1:
                OLED_DrawBMP(x, y, x+3, y+2, RIGHTARRAYF3x16);
                break;
            }
        unlock_oled();
    }
}


