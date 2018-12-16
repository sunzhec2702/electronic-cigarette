#include "oled_content_sh1107.h"

#ifdef SCREEN_096

#include "value_manager.h"
#include "system_state.h"
#include "screen.h"
#include "bmp.h"
#include "oled_content_muxlock.h"
#include "peripherals_manager.h"
#include "battery_manager.h"
#include "UI_manager.h"
#include "main_menu_temperature_value_manager.h"

void draw_split_line(u8 page)
{
    u8 i;
    for (i = 0; i < 63; i++) {
        OLED_DrawBMP(i, page, i+1, page+1, SplitPointF1x8);
    }
}

void draw_split_lines()
{
    draw_split_line(6);
    draw_split_line(11);
}

void draw_current_mode()
{
    switch(get_current_ui_id()) {
    case MAIN_MENU_POWER_ID:
        OLED_ShowString_Mode(0, PART1_PAGE, "POWER", 16, 1);
        break;
    case MAIN_MENU_VOLTAGE_ID:
        OLED_ShowString_Mode(0, PART1_PAGE, "VOLTAGE", 16, 1);
        break;
    case MAIN_MENU_TEMP_NI_ID:
        OLED_ShowString_Mode(0, PART1_PAGE, "TEMP NI", 16, 1);
        break;
    case MAIN_MENU_TEMP_TI_ID:
        OLED_ShowString_Mode(0, PART1_PAGE, "TEMP TI", 16, 1);
        break;
    case MAIN_MENU_TEMP_SS_ID:
        OLED_ShowString_Mode(0, PART1_PAGE, "TEMP SS", 16, 1);
        break;
    case MAIN_MENU_BYPASS_ID:
        OLED_ShowString_Mode(0, PART1_PAGE, "BYPASS", 16, 1);
        break;
    case MAIN_MENU_TEMP_M1_ID:
        OLED_ShowString_Mode(0, PART1_PAGE, "TEMP M1", 16, 1);
        break;
    case MAIN_MENU_TEMP_M2_ID:
        OLED_ShowString_Mode(0, PART1_PAGE, "TEMP M2", 16, 1);
        break;
    case MAIN_MENU_TEMP_M3_ID:
        OLED_ShowString_Mode(0, PART1_PAGE, "TEMP M3", 16, 1);
        break;
    }
}

void draw_battery_icon(u8 level)
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        if (get_oled_weak_lock() != SYS_LOCK) {
            OLED_SHOW_SPACE(0, PART4_PAGE, 16, 9);
            OLED_DrawBMP(9, PART4_PAGE, 64, PART4_PAGE+2, BatteryF55x16[level]);
        }
        unlock_oled();
    }
}

void draw_battery_icon_charge(u8 level)
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        if (get_oled_weak_lock() != SYS_LOCK) {
            OLED_DrawBMP(0, PART4_PAGE, 8, PART4_PAGE+2, BatteryChargeF8x16);
            OLED_DrawBMP(9, PART4_PAGE, 64, PART4_PAGE+2, BatteryF55x16[level]);
        }
        unlock_oled();
    }
}

void draw_current_lock_icon()
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        if (get_value_key_lock() == SYS_LOCK) {
            OLED_SHOW_SPACE(51,PART2_PAGE,16,4);
            OLED_DrawBMP(55, PART2_PAGE, 64, PART2_PAGE+2, LockKeyIconF9x16);
        } else {
            OLED_SHOW_SPACE(51,PART2_PAGE,16,13);
        }
        unlock_oled();
    }
}

void draw_register_value(u16 reg_value)
{
    u16 int_value, dec_value1, dec_value2;
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_ShowString_Mode(0, PART3_PAGE+1, "COIL", 8, 1);
        if (reg_value != REG_OPEN && value_read(COIL_EXIST_FLAG) != COIL_NOT_EXIST) {
            int_value = (u16) (reg_value / 100) % 10;
            dec_value1 = (u16) (reg_value / 10) % 10;
            dec_value2 = (u16) (reg_value) % 10;
            OLED_ShowNum(28, PART3_PAGE, int_value, 1, 16, 1);
            OLED_DrawBMP(36, PART3_PAGE, 38, PART3_PAGE+2, SMALLPOINTF2x16);
            OLED_ShowNum(38, PART3_PAGE, dec_value1, 1, 16, 1);
            OLED_ShowNum(46, PART3_PAGE, dec_value2, 1, 16, 1);
            OLED_DrawBMP(54, PART3_PAGE, 64, PART3_PAGE+2, OMEGAF10x16);
        } else {
            OLED_DrawBMP(28, PART3_PAGE, 36, PART3_PAGE+2, UNDERSTOKEF8x16);
            OLED_DrawBMP(36, PART3_PAGE, 38, PART3_PAGE+2, SMALLPOINTF2x16);
            OLED_DrawBMP(38, PART3_PAGE, 46, PART3_PAGE+2, UNDERSTOKEF8x16);
            OLED_DrawBMP(46, PART3_PAGE, 54, PART3_PAGE+2, UNDERSTOKEF8x16);
            OLED_DrawBMP(54, PART3_PAGE, 64, PART3_PAGE+2, OMEGAF10x16);
        }
        unlock_oled();
    }
}

void draw_voltage_value(u16 vol_value)
{
    u16 int_value, dec_value1, dec_value2;
    OLED_ShowString_Mode(0, PART3_PAGE+3, "VOLT", 8, 1);

    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        if (value_read(REGISTER_VALUE) != REG_OPEN && value_read(COIL_EXIST_FLAG) != COIL_NOT_EXIST) {
            int_value = (u16) (vol_value / 100) % 10;
            dec_value1 = (u16) (vol_value / 10) % 10;
            dec_value2 = (u16) (vol_value) % 10;
            OLED_ShowNum(28, PART3_PAGE+2, int_value, 1, 16, 1);
            OLED_DrawBMP(36, PART3_PAGE+2, 38, PART3_PAGE+4, SMALLPOINTF2x16);
            OLED_ShowNum(38, PART3_PAGE+2, dec_value1, 1, 16, 1);
            OLED_ShowNum(46, PART3_PAGE+2, dec_value2, 1, 16, 1);
            OLED_DrawBMP(54, PART3_PAGE+2, 64, PART3_PAGE+4, BoldVolUnitDOWN);
        } else {
            OLED_DrawBMP(28, PART3_PAGE+2, 36, PART3_PAGE+4, UNDERSTOKEF8x16);
            OLED_DrawBMP(36, PART3_PAGE+2, 38, PART3_PAGE+4, SMALLPOINTF2x16);
            OLED_DrawBMP(38, PART3_PAGE+2, 46, PART3_PAGE+4, UNDERSTOKEF8x16);
            OLED_DrawBMP(46, PART3_PAGE+2, 54, PART3_PAGE+4, UNDERSTOKEF8x16);
            OLED_DrawBMP(54, PART3_PAGE+2, 64, PART3_PAGE+4, BoldVolUnitDOWN);
        }
        unlock_oled();
    }
}

void draw_pid_power_out_value(u16 pid_power_value)
{
    u16 int_value, dec_value;
    OLED_ShowString_Mode(0, PART3_PAGE+3, "PWR ", 8, 1);

    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        if (value_read(REGISTER_VALUE) != REG_OPEN && value_read(COIL_EXIST_FLAG) != COIL_NOT_EXIST) {
            int_value = (u16) (pid_power_value/10);
            dec_value = (u16) (pid_power_value) % 10;
            OLED_ShowNum(28, PART3_PAGE+2, int_value, 2, 16, 1);
            OLED_DrawBMP(44, PART3_PAGE+2, 46, PART3_PAGE+4, SMALLPOINTF2x16);
            OLED_ShowNum(46, PART3_PAGE+2, dec_value, 1, 16, 1);
            OLED_DrawBMP(54, PART3_PAGE+2, 64, PART3_PAGE+4, BoldPowerUnit_DOWN);
        } else {
            OLED_DrawBMP(28, PART3_PAGE+2, 36, PART3_PAGE+4, UNDERSTOKEF8x16);
            OLED_DrawBMP(36, PART3_PAGE+2, 44, PART3_PAGE+4, UNDERSTOKEF8x16);
            OLED_DrawBMP(44, PART3_PAGE+2, 46, PART3_PAGE+4, SMALLPOINTF2x16);
            OLED_DrawBMP(46, PART3_PAGE+2, 54, PART3_PAGE+4, UNDERSTOKEF8x16);
            OLED_DrawBMP(54, PART3_PAGE+2, 64, PART3_PAGE+4, BoldPowerUnit_DOWN);
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
        OLED_ShowChar_Bold(0, PART2_PAGE, int_value1 + '0', 32);
        OLED_ShowChar_Bold(16, PART2_PAGE, int_value2 + '0', 32);
        OLED_DrawBMP(32, PART2_PAGE, 36, PART2_PAGE+4, BoldPointF4x32);
        OLED_ShowChar_Bold(36, PART2_PAGE, dec_value + '0', 32);
        OLED_SHOW_SPACE(52,PART2_PAGE,32,2);
        OLED_DrawBMP(54, PART2_PAGE+2, 64, PART2_PAGE+4, BoldPowerUnit_DOWN);
        unlock_oled();
    }
}

void draw_temperature_value(u16 temperature_value, u8 ui_id, u8 degree_mode)
{
    u16 int_value1, int_value2, dec_value;
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        switch (degree_mode) {
        case DEGREE_C:
            OLED_DrawBMP(54, PART2_PAGE+2, 64, PART2_PAGE+4, TempUnitCF10x16);
            break;
        case DEGREE_F:
            temperature_value+=TEMP_DEGREE_SWITCH_OFFSET;
            OLED_DrawBMP(54, PART2_PAGE+2, 64, PART2_PAGE+4, TempUnitFF10x16);
            break;
        default:
            OLED_DrawBMP(54, PART2_PAGE+2, 64, PART2_PAGE+4, TempUnitCF10x16);
            break;
        }
        int_value1 = (u16) (temperature_value / 100) % 10;
        int_value2 = (u16) (temperature_value / 10) % 10;
        dec_value = (u16) (temperature_value) % 10;
        OLED_ShowChar_Bold(0, PART2_PAGE, int_value1 + '0', 32);
        OLED_ShowChar_Bold(16, PART2_PAGE, int_value2 + '0', 32);
        OLED_ShowChar_Bold(32, PART2_PAGE, dec_value + '0', 32);
        OLED_SHOW_SPACE(52,PART2_PAGE,32,2);
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
        OLED_ShowChar_Bold(0, PART2_PAGE, int_value + '0', 32);
        OLED_DrawBMP(16, PART2_PAGE, 20, PART2_PAGE+4, BoldPointF4x32);
        OLED_ShowChar_Bold(20, PART2_PAGE, dec_value1 + '0', 32);
        OLED_ShowChar_Bold(36, PART2_PAGE, dec_value2 + '0', 32);
        OLED_SHOW_SPACE(52,PART2_PAGE,32,2);
        OLED_DrawBMP(54, PART2_PAGE+2, 64, PART2_PAGE+4, BoldVolUnit);
        unlock_oled();
    }
}

void draw_bypass_value(void)
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_ShowString_Mode(0, PART2_PAGE+2, "BYPASS", 16, 1);
        OLED_SHOW_SPACE(48,PART2_PAGE,32,6);
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
        OLED_ShowChar_Bold(0, PART2_PAGE, int_value1 + '0', 32);
        OLED_ShowChar_Bold(16, PART2_PAGE, int_value2 + '0', 32);
        OLED_DrawBMP(32, PART2_PAGE, 36, PART2_PAGE+4, BoldPointF4x32);
        OLED_ShowChar_Bold(36, PART2_PAGE, dec_value + '0', 32);
        OLED_SHOW_SPACE(52,PART2_PAGE,32,2);
        OLED_DrawBMP(54, PART2_PAGE+2, 64, PART2_PAGE+4, SecondUnitF10x16);
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
        draw_pid_power_out_value((value_read(PID_POWER_SET_VALUE) <= value_read(PID_WEAK_MAX_POWER_OUT_LIMIT)) ?  value_read(PID_POWER_SET_VALUE) : value_read(PID_WEAK_MAX_POWER_OUT_LIMIT));
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
        OLED_ShowString_Mode(16, 3, "COIL", 16, 1);
        unlock_oled();
    }
}

void draw_coil_choose_menu()
{
    u8 mode = 1;
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        // OLED_SHOW_SPACE(24, 0, 16, 6);
        OLED_ShowString_Mode(0, 7, "SAME", 16, mode);
        OLED_SHOW_SPACE(32, 7, 16, 8);
        OLED_SHOW_SPACE(40, 7, 16, 4);
        OLED_DrawBMP(44, 7, 60, 9, UpArrayF16x16);
        OLED_ShowString_Mode(8, 10, "or", 16, mode);
        OLED_SHOW_SPACE(63, 0, 16, 3);
        OLED_ShowString_Mode(4, 13, "NEW", 16, mode);
        OLED_SHOW_SPACE(32, 13, 16, 8);
        OLED_SHOW_SPACE(40, 13, 16, 4);
        OLED_DrawBMP(44, 13, 60, 15, DownArrayF16x16);
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
            OLED_DrawBMP(54, PART2_PAGE+2, 64, PART2_PAGE+4, TempUnitCF10x16);
            break;
        case DEGREE_F:
            temperature+=TEMP_DEGREE_SWITCH_OFFSET;
            OLED_DrawBMP(54, PART2_PAGE+2, 64, PART2_PAGE+4, TempUnitFF10x16);
            break;
        default:
            OLED_DrawBMP(54, PART2_PAGE+2, PART2_PAGE+4, 16, TempUnitCF10x16);
            break;
        }
        int_value1 = (u16) (temperature / 100) % 10;
        int_value2 = (u16) (temperature / 10) % 10;
        dec_value = (u16) (temperature) % 10;
        OLED_ShowChar_Bold(0, PART2_PAGE, int_value1 + '0', 32);
        OLED_ShowChar_Bold(16, PART2_PAGE, int_value2 + '0', 32);
        OLED_ShowChar_Bold(32, PART2_PAGE, dec_value + '0', 32);
        OLED_SHOW_SPACE(52,PART2_PAGE,32,2);
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
        OLED_ShowString_Mode(20, 5, "TCR", 16, mode);
        unlock_oled();
    }
}

void draw_mx_max_power_string(u8 mode)
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_SHOW_SPACE(21,0,16,5);
        OLED_ShowString_Mode(4, 5, "MAX PWR", 16, mode);
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
        OLED_ShowChar_Mode(16, 8, int_value2 + '0', 16, mode);
        OLED_ShowChar_Mode(24, 8, int_value3 + '0', 16, mode);
        OLED_ShowChar_Mode(32, 8, int_value4 + '0', 16, mode);
        OLED_ShowChar_Mode(40, 8, '0', 16, mode);
        unlock_oled();
    }
}

void draw_mx_max_power_value(u32 mx_power_value, u8 cursor_index)
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_ShowNum(20, 8, mx_power_value, 2, 16, (cursor_index == 5)?0:1);
        OLED_ShowChar_Mode(36, 8, 'W', 16, 1);
        unlock_oled();
    }
}

void draw_about_mesage()
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_ShowString_Mode(4, 3, "POWERED", 16, 1);
        OLED_ShowString_Mode(24, 5, "BY", 16, 1);
        OLED_ShowString_Mode(4, 7, "BOZZTEK", 16, 1);
        unlock_oled();
    }
}

void draw_software_verion_mesage(u8 ver1, u8 ver2, u8 ver3, u8 release)
{
    if (get_oled_lock() != OLED_LOCKED) {
        lock_oled();
        OLED_ShowString_Mode(32, 12, "ver", 16, 1);
        if (release) {
            OLED_ShowNum(56, 14, ver1, 1, 16, 1);
        } else {
            OLED_ShowNum(40, 14, ver1, 1, 16, 1);
            OLED_ShowNum(48, 14, ver2, 1, 16, 1);
            OLED_ShowNum(56, 14, ver3, 1, 16, 1);
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
            OLED_DrawBMP(x, y, x+16, y+2, UpArrayF16x16);
            break;
        case 1:
            OLED_DrawBMP(x, y, x+16, y+2, DownArrayF16x16);
            break;
        }
        unlock_oled();
    }
}

#endif


