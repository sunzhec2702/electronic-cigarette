#ifndef __CONTENT_SSD1306_H
#define __CONTENT_SSD1306_H
#include "sys.h"
#ifdef SCREEN_069

extern void draw_split_lines(void);
extern void draw_current_mode(void);
extern void draw_battery_icon(u8 level);
extern void draw_battery_icon_charge(u8 level);
extern void draw_register_value(u16 reg_value);
extern void draw_voltage_value(u16 vol_value);
extern void draw_pid_power_out_value(u16 pid_power_value);
extern void draw_power_value(u16 power_value);
extern void draw_temperature_value(u16 temperature_value, u8 ui_id, u8 degree_mode);
extern void draw_preset_voltage_value(u16 preset_voltage_value);
extern void draw_bypass_value(void);
extern void draw_current_value(u8 type);
extern void draw_current_battery(void);
extern void draw_whole_screen(void);
extern void draw_smoke_time(u16 smoke_time);
extern void draw_lock_icon(u8 state);
extern void draw_current_lock_icon(void);
extern void draw_lock_message(void);
void draw_coil_string(void);
//extern void draw_coil_choose_state(u8 current_select_index);
extern void draw_coil_choose_menu(void);
extern void draw_real_time_coil_temperature(u16 temperature, u8 degree_mode);
extern void draw_mx_mode_icon(u8 mx, u8 mode);
extern void draw_mx_tcr_string(u8 mode);
extern void draw_mx_max_power_string(u8 mode);
extern void draw_mx_value(u16 mx_value, u8 select_mode);
extern void draw_mx_max_power_value(u32 mx_power_value, u8 cursor_index);
extern void draw_about_mesage(void);
extern void draw_software_verion_mesage(u8 ver1, u8 ver2, u8 ver3,u8 release);
extern void draw_menu_select_array(u8 x, u8 y, u8 direction);
#endif
#endif
