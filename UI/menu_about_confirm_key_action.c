#include "menu_about_confirm_key_action.h"
#include "menu_about.h"
#include "key.h"
#include "system_state.h"

u8 menu_about_confirm_key_preaction(u8 pressed_keys, void * key_t)
{
    return SUCCESS;
}

// CONFIRM KEY TRIGGER ACTION.
u8 menu_about_confirm_key_trigger_action(void * key_t)
{
    key_state* key = (key_state*) key_t;
    if (key->state == KEY_ON) {
        
    }
    if (key->state == KEY_OFF) {
        system_init();
        //NVIC_SystemReset();
    }
    return SUCCESS;
}

u8 menu_about_confirm_key_long_event_action(void* key_t)
{
    return SUCCESS;
}

u8 menu_about_confirm_key_repeat_action(void* key_t)
{
    return SUCCESS;
}

