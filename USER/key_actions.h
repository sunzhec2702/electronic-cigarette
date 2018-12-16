#ifndef __KEY_ACTIONS_H
#define __KEY_ACTIONS_H
#include "sys.h"
#include "key.h"

extern void reset_pressed_number(void);
extern void keys_actions(void);
void key_state_process(key_state *key, u8 state);
u8 common_key_preaction(void* key_t);
u8 common_key_pre_action(u8 pressed_keys);
void preaction_error_action(u8 triggered, void * key_t);
void common_pre_action_error(u8 triggered[], void * key_t);
extern u8 combine_key_action(key_state * keys);

#endif
