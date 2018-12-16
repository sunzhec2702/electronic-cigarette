#include "smoke_mode_select_menu.h"
#include "menu_mode_select.h"
#include "system_state.h"
#include "value_manager.h"
#include "oled_content.h"
#include "oled.h"
#include "UI_manager.h"
#include "pwr_manager.h"
#include "temperature_mode_select_menu.h"

static u8 current_index_value;

static menu_info smoke_mode_menu_info = {
    smoke_mode_select_draw_current_value,
    smoke_mode_select_value_key_callback,
    smoke_mode_select_confirm_key_callback,
    SMOKE_MODE_SELECT_ID
};
    
void smoke_mode_select_page_entry(void* pt)
{
    current_index_value = 0;
    /*
    if (get_value_key_lock() == SYS_LOCK)
        current_index_value = MENU_SMOKE_KEY_LOCK;
    else {
        switch(value_restore_func(UI_ID_REG_INDEX, UI_ID_OFFSET, UI_ID_LEN_MASK)) {
            case MAIN_MENU_POWER_ID:
                current_index_value = MENU_SMOKE_POWER_MODE;
                break;
            case MAIN_MENU_VOLTAGE_ID:
                current_index_value = MENU_SMOKE_VOLTAGE_MODE;
                break;
            case MAIN_MENU_BYPASS_ID:
                current_index_value = MENU_SMOKE_BYPASS_MODE;
                break;
            case MAIN_MENU_TEMP_NI_ID:
            case MAIN_MENU_TEMP_TI_ID:
            case MAIN_MENU_TEMP_SS_ID:
            case MAIN_MENU_TEMP_M1_ID:
            case MAIN_MENU_TEMP_M2_ID:
            case MAIN_MENU_TEMP_M3_ID:
                current_index_value = MENU_SMOKE_TEMPERATURE_MODE;
                break;
        }
    }
    */
    update_menu_info(&smoke_mode_menu_info);
    switch_to_ui_page(MENU_MODE_SELECT_ID);
}

void smoke_mode_select_page_exit(void* pt)
{
    //Do nothing.
}

u8 smoke_mode_select_combine_event_callback (void * keys_t)
{
    return SUCCESS;
}

void smoke_mode_select_value_key_callback(u8 key_type)
{
    if (get_value_key_lock() == SYS_LOCK) {
        current_index_value = MENU_SMOKE_KEY_LOCK;
        //smoke_mode_select_draw_current_value(NULL);
        system_init();
        return;
    }
    switch (key_type) {
        case KEY_INCREASE:
            current_index_value++;
            current_index_value%=MENU_SMOKE_MODES_NUMBER;
            if (current_index_value == 0 && get_value_key_lock() == SYS_LOCK)
                current_index_value = MENU_SMOKE_KEY_LOCK;
            break;
        case KEY_REDUCE:
            current_index_value+=MENU_SMOKE_MODES_NUMBER;
            current_index_value--;
            current_index_value%=MENU_SMOKE_MODES_NUMBER;
        default:
            break;
    }
    smoke_mode_select_draw_current_value(NULL);
}

void smoke_mode_select_confirm_key_callback(u8 long_press)
{
    switch(current_index_value) {
        case MENU_SMOKE_POWER_MODE:
            switch_to_ui_page(MAIN_MENU_POWER_ID);
            break;
        /*
        case MENU_SMOKE_VOLTAGE_MODE:
            switch_to_ui_page(MAIN_MENU_VOLTAGE_ID);
            break;
        case MENU_SMOKE_BYPASS_MODE:
            switch_to_ui_page(MAIN_MENU_BYPASS_ID);
            break;
        */
        case MENU_SMOKE_TEMPERATURE_MODE:
            if (long_press == ERROR)
                switch_to_ui_page(TEMERATURE_MODE_SELECT_ID);
            else if (long_press == SUCCESS)
                switch_to_ui_page(get_temperature_mode_ui_id());
            break;
        case MENU_SMOKE_KEY_LOCK:
            set_value_key_lock_reverse();
            system_init();
            break;
        case MENU_SMOKE_SCREEN_FLIP:
            screen_flip_flag_revert();
            reboot_system(SUCCESS);
            break;
        case MENU_SMOKE_ABOUT:
            switch_to_ui_page(MENU_ABOUT_ID);
            break;
    }
    
}


void smoke_mode_select_draw_current_value(void* pt)
{
    u8 offset = 0;
    if (get_value_key_lock() != SYS_LOCK) {
        offset = 3;
        draw_menu_select_array(0, 0, 0);
        draw_menu_select_array(93, 0, 1);
    }
    
    switch(current_index_value) {
        case MENU_SMOKE_POWER_MODE:
            OLED_SHOW_SPACE(0+offset,0,16,8-offset);
            OLED_ShowString_Mode(8, 0, "POWER MODE", 16, 1);
            OLED_SHOW_SPACE(88,0,16,8-offset);
            break;
        /*
        case MENU_SMOKE_VOLTAGE_MODE:
            OLED_SHOW_SPACE(0+offset,0,16,12-offset);
            OLED_ShowString_Mode(12, 0, "VOLT MODE", 16, 1);
            OLED_SHOW_SPACE(84,0,16,12-offset);
            break;
        case MENU_SMOKE_BYPASS_MODE:
            OLED_SHOW_SPACE(0+offset,0,16,4-offset);
            OLED_ShowString_Mode(4, 0, "BYPASS MODE", 16, 1);
            OLED_SHOW_SPACE(92,0,16,4-offset);
            break;
        */
        case MENU_SMOKE_TEMPERATURE_MODE:
            OLED_SHOW_SPACE(0+offset, 0, 16, 12-offset);
            OLED_ShowString_Mode(12, 0, "TEMP MODE", 16, 1);
            OLED_SHOW_SPACE(84, 0, 16, 12-offset);
            break;
        case MENU_SMOKE_KEY_LOCK:
            if (get_value_key_lock() == SYS_UNLOCK) {
                OLED_SHOW_SPACE(0+offset, 0, 16, 12-offset);
                OLED_ShowString_Mode(12, 0, "LOCK ATTR", 16, 1);
                OLED_SHOW_SPACE(84, 0, 16, 12-offset);
            } else {
                OLED_SHOW_SPACE(0+offset, 0, 16, 4-offset);
                OLED_ShowString_Mode(4, 0, "UNLOCK ATTR", 16, 1);
                OLED_SHOW_SPACE(92, 0, 16, 4-offset);
            }
            break;
        case MENU_SMOKE_SCREEN_FLIP:
            OLED_SHOW_SPACE(0+offset, 0, 16, 4-offset);
            OLED_ShowString_Mode(4, 0, "SCREEN FLIP", 16, 1);
            OLED_SHOW_SPACE(92, 0, 16, 4-offset);
            break;
        case MENU_SMOKE_ABOUT:
            OLED_SHOW_SPACE(0+offset, 0, 16, 28-offset);
            OLED_ShowString_Mode(28, 0, "ABOUT", 16, 1);
            OLED_SHOW_SPACE(68, 0, 16, 28-offset);
            break;
    }
}



