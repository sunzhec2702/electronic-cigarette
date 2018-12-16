#ifndef __UI_MANAGER_H
#define __UI_MANAGER_H
#include "sys.h"
#include "key.h"

enum ui_ids {
    MAIN_MENU_POWER_ID = 0,
    MAIN_MENU_VOLTAGE_ID,
    MAIN_MENU_BYPASS_ID,
    MAIN_MENU_TEMP_NI_ID,
    MAIN_MENU_TEMP_TI_ID,
    MAIN_MENU_TEMP_SS_ID,
    MAIN_MENU_TEMP_M1_ID,
    MAIN_MENU_TEMP_M2_ID,
    MAIN_MENU_TEMP_M3_ID,
    MENU_MODE_SELECT_ID,
    MENU_NEW_COIL_CHECK_ID,
    MENU_MX_TCR_ID,
    MENU_ABOUT_ID,
    SMOKE_MODE_SELECT_ID,
    TEMERATURE_MODE_SELECT_ID,
    MENU_MX_MAX_POWER_ID,
    MENU_NUMBER
};


typedef struct
{
    enum ui_ids UI_ID;
    void (*page_entry)(void* pt);
    void (*page_exit)(void* pt);
    
    u8 (*combine_event_callback)(void* keys_t);
    void (*value_backup)(void);
    void (*value_restore)(void);
    void (*draw_whole_screen)(void);
    void (*draw_current_value)(void);
    u32* (*get_value_pointer)(u8 para);
} ui_page;


#define UI_ID_REG_INDEX      4
#define UI_ID_OFFSET         0
#define UI_ID_LEN_MASK       0xFF

#define INITED 0x1
#define UNINIT 0x0

#define VALUE       0x0
#define PID_VALUE   0x1

extern void UI_init(void);

extern void switch_to_ui_page(u8 index);
extern void switch_to_next_page(void);

extern u8 can_draw_icons(void);
extern ui_page* get_current_ui_page(void);
extern u8 get_current_ui_index(void);
extern u8 get_current_ui_id(void);


extern void draw_current_screen(void);
extern void value_backup_all(void);
extern void value_restore_all(void);

extern u16 get_value_init_flag(void);
extern void set_value_init_flag(void);
extern void clear_value_init_flag(void);

void value_backup(void);
void value_restore(void);


#endif

