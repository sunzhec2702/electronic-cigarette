#ifndef __KEY_H
#define	__KEY_H
#include "sys.h"
#include "value_key.h"
#include "confirm_key.h"

#define KEY_ON	0
#define KEY_OFF	1

#define TIMER_PERIOD            10 // 10ms
#define STABLE_NUMBER           50/TIMER_PERIOD // 80ms
#define REPORT_INTERVAL         100/TIMER_PERIOD // 100ms
#define REPEAT_INTERVAL         300/TIMER_PERIOD // 500ms, user at lease press the key twice a second.

#define SMOKE_REPORT_INTERVAL   0/TIMER_PERIOD // 10ms
#define SMOKE_MAX_TIME_NUMBER   10000/TIMER_PERIOD // 10s
#define SMOKE_START_DUMMY_TIC   0xDEADBEEF

#define KEY_SWITCH_NUMBER       400/TIMER_PERIOD
#define TIMER_FRESH_SCREEN      2500 // 2000ms Unit is ms, not tick.

#define KEY_INCREASE        0
#define KEY_REDUCE          1
#define KEY_CONFIRM         2
#define KEY_NUMBER          3

#define TRIGGERED       1
#define NOT_TRIGGER     0

#define VALUE_KEY_LOCK_REG_VALUE        4
#define VALUE_KEY_LOCK_REG_OFFSET       22
#define VALUE_KEY_LOCK_LEN_MASK         0x1



typedef struct {
    u8 type;
    u8 (*pre_action)(u8 pressed_keys, void * key);
    u8 (*trigger_action)(void * key);
    u8 (*long_event_action)(void * key);
    u8 (*repeat_event_action) (void * key);
} key_callback;

typedef struct {
    u8 type;
    u8 state;
    u8 trigger_flag;
    
    u16 press_tic;  // Check if key is really pressed.
    u16 press_report_tic;   // used for update value.
    u32 press_keep_tic; // used for recording the hold time.
    u16 report_tic_interval;
    u16 long_press_interval;

    u16 release_tic;
    u32 release_keep_tic;
    u16 repeat_tic_interval;

    u16 stable_tic_num;
    u16 repeat_count;

    key_callback* key_callback;
    
} key_state;


extern void Key_GPIO_Config(void);
extern u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);
extern void keys_state_reset(void);
extern void key_state_reset_single(u8 key_type);
extern void keys_callback_reset(void);
extern void keys_state_update(void);
extern key_state* get_keys_state(void);
extern u8 read_key_state(u8 type);
u8 is_key_pressed(u8 type);
extern u8 get_value_key_lock(void);
extern void set_value_key_lock(u8 lock);
extern void set_value_key_lock_reverse(void);


extern u32 get_smoke_start_tic(void);
extern void set_smoke_start_tic(u32 tic_value);
extern void reset_smoke_start_tic(void);

extern u32 get_weak_start_tic(void);
extern void set_weak_start_tic(u32 tic_value);
extern void reset_weak_start_tic(void);

#endif
