#include "UI_manager.h"
#include "main_menu_power.h"
#include "main_menu_temperature.h"
#include "menu_mode_select.h"
#include "menu_new_coil_check.h"
#include "menu_mx_tcr.h"
#include "smoke_mode_select_menu.h"
#include "temperature_mode_select_menu.h"
#include "menu_mx_tcr.h"
#include "value_manager.h"
#include "system_state.h"
#include "pwr_manager.h"
#include "menu_about.h"

// Add the UI pages in this struction.
ui_page UI_MENUS[MENU_NUMBER]= {

    {   MAIN_MENU_POWER_ID, main_power_page_entry, main_power_page_exit,
        main_power_combine_event_callback, main_power_value_backup, main_power_value_restore, main_power_draw_whole_screen, main_power_draw_current_value, main_power_get_value_pointer,
    },
    {   MAIN_MENU_VOLTAGE_ID, main_power_page_entry, main_power_page_exit,
        main_power_combine_event_callback, main_power_value_backup, main_power_value_restore, main_power_draw_whole_screen, main_power_draw_current_value, main_power_get_value_pointer,
    },
    {   MAIN_MENU_BYPASS_ID, main_power_page_entry, main_power_page_exit,
        main_power_combine_event_callback, main_power_value_backup, main_power_value_restore, main_power_draw_whole_screen, main_power_draw_current_value, main_power_get_value_pointer,
    },
    {   MAIN_MENU_TEMP_NI_ID, main_menu_temperature_page_entry, main_menu_temperature_page_exit,
        main_menu_temperature_combine_event_callback, main_menu_temperature_value_backup, main_menu_temperature_value_restore, main_menu_temperature_draw_whole_screen, main_menu_temperature_draw_current_value, main_menu_temperature_get_value_pointer,
    },
    {   MAIN_MENU_TEMP_TI_ID, main_menu_temperature_page_entry, main_menu_temperature_page_exit,
        main_menu_temperature_combine_event_callback, main_menu_temperature_value_backup, main_menu_temperature_value_restore, main_menu_temperature_draw_whole_screen, main_menu_temperature_draw_current_value, main_menu_temperature_get_value_pointer,
    },
    {   MAIN_MENU_TEMP_SS_ID, main_menu_temperature_page_entry, main_menu_temperature_page_exit,
        main_menu_temperature_combine_event_callback, main_menu_temperature_value_backup, main_menu_temperature_value_restore, main_menu_temperature_draw_whole_screen, main_menu_temperature_draw_current_value, main_menu_temperature_get_value_pointer,
    },
    {   MAIN_MENU_TEMP_M1_ID, main_menu_temperature_page_entry, main_menu_temperature_page_exit,
        main_menu_temperature_combine_event_callback, main_menu_temperature_value_backup, main_menu_temperature_value_restore, main_menu_temperature_draw_whole_screen, main_menu_temperature_draw_current_value, main_menu_temperature_get_value_pointer,
    },
    {   MAIN_MENU_TEMP_M2_ID, main_menu_temperature_page_entry, main_menu_temperature_page_exit,
        main_menu_temperature_combine_event_callback, main_menu_temperature_value_backup, main_menu_temperature_value_restore, main_menu_temperature_draw_whole_screen, main_menu_temperature_draw_current_value, main_menu_temperature_get_value_pointer,
    },
    {   MAIN_MENU_TEMP_M3_ID, main_menu_temperature_page_entry, main_menu_temperature_page_exit,
        main_menu_temperature_combine_event_callback, main_menu_temperature_value_backup, main_menu_temperature_value_restore, main_menu_temperature_draw_whole_screen, main_menu_temperature_draw_current_value, main_menu_temperature_get_value_pointer,
    },
    {   MENU_MODE_SELECT_ID, menu_mode_select_page_entry, menu_mode_select_page_exit,
        menu_mode_select_combine_event_callback, NULL, NULL, menu_mode_select_draw_whole_screen, menu_mode_select_draw_current_value, NULL,
    },
    {   MENU_NEW_COIL_CHECK_ID, menu_new_coil_check_page_entry, menu_new_coil_check_page_exit,
        menu_new_coil_check_combine_event_callback, NULL, NULL, menu_new_coil_check_draw_whole_screen, menu_new_coil_check_draw_current_value, NULL,
    },
    {   MENU_MX_TCR_ID, menu_mx_parameter_page_entry, menu_mx_parameter_page_exit,
        menu_mx_parameter_combine_event_callback, menu_mx_parameter_value_backup, menu_mx_parameter_value_restore, menu_mx_parameter_draw_whole_screen, menu_mx_parameter_draw_current_value, mx_tcr_get_value_pointer,
    },
    {   MENU_ABOUT_ID, menu_about_page_entry, menu_about_page_exit,
        menu_about_combine_event_callback, NULL, NULL, menu_about_draw_whole_screen, menu_about_draw_current_value, NULL,
    },
    {   SMOKE_MODE_SELECT_ID, smoke_mode_select_page_entry, smoke_mode_select_page_exit,
        NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {   TEMERATURE_MODE_SELECT_ID, temperature_mode_select_page_entry, temperature_mode_select_page_exit,
        NULL, temperatue_mode_backup, temperature_mode_restore, NULL, NULL, NULL,
    },
    {   MENU_MX_MAX_POWER_ID, menu_mx_parameter_page_entry, menu_mx_parameter_page_exit,
        menu_mx_parameter_combine_event_callback, menu_mx_parameter_value_backup, menu_mx_parameter_value_restore, menu_mx_parameter_draw_whole_screen, menu_mx_parameter_draw_current_value, mx_max_power_get_value_pointer,
    },
};

static u8 current_ui_index;
static ui_page * current_ui_page;

void UI_init()
{
    // Restore all values.
    value_restore_all();
}

void switch_to_next_page()
{
    u8 next_index = (current_ui_index + 1)%MENU_NUMBER;
    switch_to_ui_page(next_index);
}
void switch_to_ui_page(u8 id_number)
{
    u8 index,last_index = current_ui_index;
    for (index = 0; index < MENU_NUMBER; index++) {
        if (UI_MENUS[index].UI_ID == id_number)
            break;
    }
    if (index == MENU_NUMBER) {
        index = 0;
        id_number = UI_MENUS[index].UI_ID;
    }
    UI_MENUS[current_ui_index].page_exit(NULL);

    current_ui_index = index;
    current_ui_page = &UI_MENUS[current_ui_index];

    switch(id_number) {
        case MENU_MODE_SELECT_ID:
        case SMOKE_MODE_SELECT_ID:
        case TEMERATURE_MODE_SELECT_ID:
        case MENU_NEW_COIL_CHECK_ID:
            UI_MENUS[current_ui_index].page_entry((void*)&UI_MENUS[last_index].UI_ID);
            break;
        default:
            UI_MENUS[current_ui_index].page_entry(NULL);
            break;
    }
    value_backup();
}

u8 get_current_ui_index()
{
    return current_ui_index;
}

u8 get_current_ui_id()
{
    return current_ui_page->UI_ID;
}

ui_page* get_current_ui_page()
{
    return current_ui_page;
}

void draw_current_screen(void)
{
    UI_MENUS[current_ui_index].draw_whole_screen();
}

void value_backup_all()
{
    u8 index;
    value_backup();
    for (index = 0; index < MENU_NUMBER; index++) {
        if (UI_MENUS[index].value_backup != NULL)
            UI_MENUS[index].value_backup();
    }
}

void value_restore_all()
{
    u8 index;
    for (index = 0; index < MENU_NUMBER; index++) {
        if (UI_MENUS[index].value_restore != NULL)
            UI_MENUS[index].value_restore();
    }
    value_restore();
}

// For UI manager.
void value_backup()
{
    switch(UI_MENUS[current_ui_index].UI_ID) {
        case MENU_MODE_SELECT_ID:
        case SMOKE_MODE_SELECT_ID:
        case MENU_NEW_COIL_CHECK_ID:
        case MENU_MX_TCR_ID:
        case MENU_MX_MAX_POWER_ID:
        case MENU_ABOUT_ID:
        case TEMERATURE_MODE_SELECT_ID:
            break;
        default:
            value_backup_func(UI_ID_REG_INDEX, UI_ID_OFFSET, UI_ID_LEN_MASK, current_ui_page->UI_ID);
    }
}

void value_restore()
{
    if (value_restore_func(MX_FLAG_REG_VALUE, MX_FLAG_OFFSET, MX_FLAG_MASK) == GO_TO_MX_PARAMETER) {
        switch_to_ui_page(MENU_MX_TCR_ID);
        value_backup_func(MX_FLAG_REG_VALUE, MX_FLAG_OFFSET, MX_FLAG_MASK, GO_TO_NOTHING);
    } else if (value_restore_func(MX_FLAG_REG_VALUE, MX_FLAG_OFFSET, MX_FLAG_MASK) == GO_TO_ABOUT_MENU) {
        switch_to_ui_page(MENU_ABOUT_ID);
        value_backup_func(MX_FLAG_REG_VALUE, MX_FLAG_OFFSET, MX_FLAG_MASK, GO_TO_NOTHING);
    } else {
        switch_to_ui_page(value_restore_func(UI_ID_REG_INDEX, UI_ID_OFFSET, UI_ID_LEN_MASK));
        //switch_to_ui_page(SMOKE_MODE_SELECT_ID);
    }
}

u8 can_draw_icons()
{
    if (get_system_state() == STATE_DISPLAYOFF || get_system_state() == STATE_CHARGING)
        return ERROR;

    switch(get_current_ui_id()) {
        case MAIN_MENU_POWER_ID:
        case MAIN_MENU_VOLTAGE_ID:
        case MAIN_MENU_TEMP_NI_ID:
        case MAIN_MENU_TEMP_TI_ID:
        case MAIN_MENU_TEMP_SS_ID:
        case MAIN_MENU_BYPASS_ID:
        case MAIN_MENU_TEMP_M1_ID:
        case MAIN_MENU_TEMP_M2_ID:
        case MAIN_MENU_TEMP_M3_ID:
            return SUCCESS;
        case MENU_MODE_SELECT_ID:
        case MENU_NEW_COIL_CHECK_ID:
        case MENU_MX_TCR_ID:
        case MENU_MX_MAX_POWER_ID:
        case MENU_ABOUT_ID:
            return ERROR;
        default:
            return ERROR;
        }
}


