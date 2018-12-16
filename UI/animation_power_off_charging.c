#include "animation_power_off_charging.h"
#include "peripherals_manager.h"
#include "task_scheduler.h"
#include "key.h"
#include "Oled.h"
#include "oled_content.h"
#include "system_state.h"
#include "value_manager.h"

// declare three key struct.
static key_callback keys_callback[] = {
    {KEY_CONFIRM, animation_power_off_charging_confirm_key_preaction, animation_power_off_charging_confirm_key_trigger_action, animation_power_off_charging_confirm_key_long_event_action, animation_power_off_charging_confirm_key_repeat_action},
};

void animation_power_off_charging_page_entry(void* pt)
{
    u8 index;
    key_state *keys = get_keys_state();
    keys_state_reset();
    for (index = 0; index < sizeof(keys_callback)/sizeof(key_callback); index++) {
        keys[keys_callback[index].type].key_callback = &keys_callback[index];
    }
    task_enable(TASK_ID_CHARGING_ANIMATION, TASK_ENABLE);
}

void animation_power_off_charging_page_exit(void* pt)
{
    // Do nothing for now.
}

u8 animation_power_off_charging_combine_event_callback (void * keys_t)
{
    return ERROR;
}

void animation_power_off_charging_draw_whole_screen()
{
    OLED_Clear();
}

void animation_power_off_charging_draw_current_value()
{
    // Do nothing
}

