#include "menu_about.h"
#include "Oled.h"
#include "oled_content.h"

#define SW_VER1    2
#define SW_VER2    2
#define SW_VER3    6

// declare three key struct.
static key_callback keys_callback[] = {
    {KEY_CONFIRM, menu_about_confirm_key_preaction, menu_about_confirm_key_trigger_action, menu_about_confirm_key_long_event_action, menu_about_confirm_key_repeat_action},
};

void menu_about_page_entry(void* pt)
{
    u8 index;
    key_state *keys = get_keys_state();
    keys_state_reset();
    for (index = 0; index < sizeof(keys_callback)/sizeof(key_callback); index++) {
        keys[keys_callback[index].type].key_callback = &keys_callback[index];
    }
    menu_about_draw_whole_screen();
}

void menu_about_page_exit(void* pt)
{
    keys_callback_reset();
}

u8 menu_about_combine_event_callback (void * keys_t)
{
    key_state *keys = (key_state*) keys_t;
    if (keys[KEY_INCREASE].state == KEY_ON && keys[KEY_REDUCE].state == KEY_ON) {
        if ((keys[KEY_INCREASE].press_keep_tic >= MIGIC_BACKDOOR_TIC) && (keys[KEY_REDUCE].press_keep_tic >= MIGIC_BACKDOOR_TIC)) {
                draw_software_verion_mesage(SW_VER1, SW_VER2, SW_VER3, 0);
        }
    }
    return SUCCESS;
}

void menu_about_draw_whole_screen()
{
    OLED_Clear();
    draw_about_mesage();
    draw_software_verion_mesage(SW_VER1, SW_VER2, SW_VER3, 1);
}

void menu_about_draw_current_value()
{
    OLED_Clear();
    draw_about_mesage();
    draw_software_verion_mesage(SW_VER1, SW_VER2, SW_VER3, 1);
}

