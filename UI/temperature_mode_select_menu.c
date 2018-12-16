#include "temperature_mode_select_menu.h"
#include "menu_mode_select.h"
#include "value_manager.h"
#include "oled.h"
#include "oled_content.h"
#include "UI_manager.h"

static u8 current_index_value;

static menu_info temperature_mode_menu_info = {
    temperature_mode_select_draw_current_value,
    temperature_mode_select_value_key_callback,
    temperature_mode_select_confirm_key_callback,
    TEMERATURE_MODE_SELECT_ID
};

void temperature_mode_select_page_entry(void* pt)
{
    temperature_mode_restore();
    update_menu_info(&temperature_mode_menu_info);
    switch_to_ui_page(MENU_MODE_SELECT_ID);
}

void temperature_mode_select_page_exit(void* pt)
{
    //Do nothing.
}

u8 temperature_mode_select_combine_event_callback (void * keys_t)
{
    return SUCCESS;
}

void temperature_mode_select_value_key_callback(u8 key_type)
{
    switch (key_type) {
        case KEY_INCREASE:
            current_index_value++;
            current_index_value%=TEMP_MODES_NUMBER;
            break;
        case KEY_REDUCE:
            current_index_value+=TEMP_MODES_NUMBER;
            current_index_value--;
            current_index_value%=TEMP_MODES_NUMBER;
            break;
        default:
            break;
    }
    temperature_mode_select_draw_current_value(NULL);
    temperatue_mode_backup();
}

void temperature_mode_select_confirm_key_callback(u8 long_press)
{
    
    switch(current_index_value) {
        case NI_MODE:
            switch_to_ui_page(MAIN_MENU_TEMP_NI_ID);
            break;
        case TI_MODE:
            switch_to_ui_page(MAIN_MENU_TEMP_TI_ID);
            break;
        case SS_MODE:
            switch_to_ui_page(MAIN_MENU_TEMP_SS_ID);
            break;
        case M1_MODE:
        case M2_MODE:
        case M3_MODE:
            switch_to_ui_page(MENU_MX_TCR_ID);
            break;
        default:
            current_index_value = 0;
            temperatue_mode_backup();
            switch_to_ui_page(MAIN_MENU_TEMP_NI_ID);
            break;
    }
}


void temperature_mode_select_draw_current_value(void* pt)
{
    draw_menu_select_array(0, 0, 0);
    draw_menu_select_array(93, 0, 1);
    
    switch(current_index_value) {
        case NI_MODE:
            OLED_SHOW_SPACE(3,0,16,17);
            OLED_ShowString_Mode(20, 0, "COIL NI", 16, 1);
            OLED_SHOW_SPACE(76,0,16,17);
            break;
        case TI_MODE:
            OLED_SHOW_SPACE(3,0,16,17);
            OLED_ShowString_Mode(20, 0, "COIL TI", 16, 1);
            OLED_SHOW_SPACE(76,0,16,17);
            break;
        case SS_MODE:
            OLED_SHOW_SPACE(3,0,16,17);
            OLED_ShowString_Mode(20, 0, "COIL SS", 16, 1);
            OLED_SHOW_SPACE(76,0,16,17);
            break;
        case M1_MODE:
            OLED_SHOW_SPACE(3,0,16,17);
            OLED_ShowString_Mode(20, 0, "COIL M1", 16, 1);
            OLED_SHOW_SPACE(76,0,16,17);
            break;
        case M2_MODE:
            OLED_SHOW_SPACE(3,0,16,17);
            OLED_ShowString_Mode(20, 0, "COIL M2", 16, 1);
            OLED_SHOW_SPACE(76,0,16,17);
            break;
        case M3_MODE:
            OLED_SHOW_SPACE(3,0,16,17);
            OLED_ShowString_Mode(20, 0, "COIL M3", 16, 1);
            OLED_SHOW_SPACE(76,0,16,17);
            break;
        default:
            current_index_value = 0;
            temperatue_mode_backup();
            OLED_SHOW_SPACE(3,0,16,17);
            OLED_ShowString_Mode(20, 0, "COIL NI", 16, 1);
            OLED_SHOW_SPACE(76,0,16,17);
            break;
    }
}

void temperatue_mode_backup()
{
    value_backup_func(TEMP_MODE_SELECT_REG_INDEX, TEMP_MODE_SELECT_REG_OFFSET, TEMP_MODE_SELECT_LEN_MASK, current_index_value);
}

void temperature_mode_restore()
{
    current_index_value = value_restore_func(TEMP_MODE_SELECT_REG_INDEX, TEMP_MODE_SELECT_REG_OFFSET, TEMP_MODE_SELECT_LEN_MASK);
}

u8 get_temperature_mode_index()
{
    return current_index_value;
}

u8 get_temperature_mode_ui_id()
{
    return current_index_value+MAIN_MENU_TEMP_NI_ID;
}

