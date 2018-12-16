#include "key.h"
#include "adc.h"
#include "key_actions.h"
#include "system_state.h"
#include "value_manager.h"

static u8 value_key_lock = SYS_UNLOCK;

// declare three key struct.
static key_state keys[KEY_NUMBER] = {
    {   KEY_INCREASE, KEY_OFF, NOT_TRIGGER, 0, 0, 0, REPORT_INTERVAL, VALUE_KEY_LONG_PRESS_TIME, 0, 0, REPEAT_INTERVAL, STABLE_NUMBER, 0, NULL},

    {   KEY_REDUCE, KEY_OFF, NOT_TRIGGER, 0, 0, 0, REPORT_INTERVAL, VALUE_KEY_LONG_PRESS_TIME, 0, 0, REPEAT_INTERVAL, STABLE_NUMBER, 0, NULL},

    {   KEY_CONFIRM, KEY_OFF, NOT_TRIGGER, 0, 0, 0, SMOKE_REPORT_INTERVAL, CONFIRM_KEY_LONG_PRESS_TIME, 0, 0, REPEAT_INTERVAL, STABLE_NUMBER, 0, NULL},
};

void Key_GPIO_Config()
{
    GPIO_InitPara GPIO_InitStructure;

    RCC_AHBPeriphClock_Enable(KEY_GPIO_RCC, ENABLE);     // PA

    //Wake up Key.
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_IN;
    GPIO_InitStructure.GPIO_Pin = KEY_CONFIRM_PIN ;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;

#ifdef YANMING3
    GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLDOWN;
#else
    GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;    // Low voltage trigger in Ming's board.
#endif
    GPIO_Init(KEY_CONFIRM_GPIO, &GPIO_InitStructure);

    // Increase Key.
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_IN;
    GPIO_InitStructure.GPIO_Pin = KEY_INCREASE_PIN ;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;
    GPIO_Init(KEY_GPIO, &GPIO_InitStructure);

    // Reduce Key.
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_IN;
    GPIO_InitStructure.GPIO_Pin = KEY_REDUCE_PIN ;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;
    GPIO_Init(KEY_GPIO, &GPIO_InitStructure);
}

key_state* get_keys_state()
{
    return keys;
}

/* 检测按键释放/按下 */
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{
    u8 ret = GPIO_ReadInputBit(GPIOx, GPIO_Pin);
    if(ret == KEY_ON)
        return KEY_ON;
    else
        return KEY_OFF;
}

void keys_state_reset()
{
    u8 index;
    for (index = 0; index < KEY_NUMBER; index++) {
        key_state_reset_single(index);
    }
}

void key_state_reset_single(u8 key_type)
{
    u8 key_state;
    key_state = read_key_state(keys[key_type].type);
    keys[key_type].state = key_state;
    keys[key_type].press_tic = 0;
    keys[key_type].press_report_tic = 0;
    keys[key_type].release_tic = 0;
    keys[key_type].press_keep_tic = 0;
    keys[key_type].release_keep_tic = 0;
    keys[key_type].repeat_count = 0;
}

void keys_callback_reset()
{
    u8 index;
    for (index = 0; index < KEY_NUMBER; index++) {
        keys[index].key_callback = NULL;
    }
}

void keys_state_update()
{
    u8 index, temp_key_state = 0;
    for (index = 0; index < KEY_NUMBER; index++) {
        key_state *key = &keys[index];
        temp_key_state = read_key_state(key->type);
        if (temp_key_state == KEY_ON) {
            if (key->state == KEY_ON) {
                key->press_keep_tic++;
                key->press_report_tic++;
            } else {
                key->press_tic++;
            }
        } else {
            if (key->state == KEY_OFF) {
                key->release_keep_tic++;
                if (key->release_keep_tic == 0xFFFFFFFF) {
                    key->release_keep_tic = REPEAT_INTERVAL;
                }
            } else {
                key->release_tic++;
            }
        }
    }
}

u8 read_key_state(u8 type)
{
    u8 temp_key_state = 0;
    switch (type) {
    case KEY_INCREASE:
        if (get_screen_flip_flag() == SYS_SCREEN_NORMAL)
            temp_key_state = Key_Scan(KEY_GPIO, KEY_INCREASE_PIN);
        else
            temp_key_state = Key_Scan(KEY_GPIO, KEY_REDUCE_PIN);
        break;
    case KEY_REDUCE:
        if (get_screen_flip_flag() == SYS_SCREEN_NORMAL)
            temp_key_state = Key_Scan(KEY_GPIO, KEY_REDUCE_PIN);
        else
            temp_key_state = Key_Scan(KEY_GPIO, KEY_INCREASE_PIN);
        break;
    case KEY_CONFIRM:
        #ifdef YANMING3
        temp_key_state = !Key_Scan(KEY_CONFIRM_GPIO, KEY_CONFIRM_PIN);
        #else
        temp_key_state = Key_Scan(KEY_CONFIRM_GPIO, KEY_CONFIRM_PIN);
        #endif
        break;
    }
    return temp_key_state;
}

u8 get_value_key_lock()
{
    value_key_lock = value_restore_func(VALUE_KEY_LOCK_REG_VALUE, VALUE_KEY_LOCK_REG_OFFSET, VALUE_KEY_LOCK_LEN_MASK);
    return value_key_lock;
}

void set_value_key_lock(u8 lock)
{
    value_key_lock = lock;
    value_backup_func(VALUE_KEY_LOCK_REG_VALUE, VALUE_KEY_LOCK_REG_OFFSET, VALUE_KEY_LOCK_LEN_MASK, value_key_lock);
}

void set_value_key_lock_reverse()
{
    value_key_lock = value_key_lock == SYS_LOCK ? SYS_UNLOCK : SYS_LOCK;
    value_backup_func(VALUE_KEY_LOCK_REG_VALUE, VALUE_KEY_LOCK_REG_OFFSET, VALUE_KEY_LOCK_LEN_MASK, value_key_lock);
}
/*
static u16 key_switch_number = KEY_SWITCH_NUMBER;
// Read voltage to check if the key is pressed or not since it is not a digital key.
u8 is_key_pressed(u8 type)
{
    u16 voltage = get_key_voltage();
    switch (type) {
    case KEY_REDUCE:
        if (voltage < 900) {
            return KEY_ON;
        } else
            return KEY_OFF;
    case KEY_INCREASE:
        if (((voltage > 900) && (voltage < 2000))) {
            // HACK: Since the voltage will increase from < 900 to > 2000, the voltage will fall in INCREASE_KEY range.
            // We don't respond if KEY_REDUCE doesn't release 300ms.
            if (keys[KEY_REDUCE].release_keep_tic * TIMER_PERIOD >= key_switch_number)
                return KEY_ON;
            else
                return KEY_OFF;
        } else if (voltage < 550) {
            return KEY_ON;
        } else
            return KEY_OFF;
    default:
        return KEY_OFF;
    }
}
*/


