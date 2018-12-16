#include "task_scheduler.h"
#include "key.h"
#include "key_actions.h"
#include "system_state.h"
#include "battery_charging_animation.h"
#include "flag_manager.h"
#include "battery_manager.h"
#include "peripherals_manager.h"

static task_t tasks[TASK_NUM] = {
    {TASK_ID_KEY, 0, 0xFFFFFF, 3*TIMER_PERIOD * MS_TIC_INTERVAL, TASK_ENABLE, keys_actions},
    {TASK_ID_PERIPHERALS, 0, 0xFFFFFF, PERIPHERALS_STATE_UPDATE_PERIOD * MS_TIC_INTERVAL, TASK_ENABLE, peripherals_update_task},
    {TASK_ID_CHARGING_ANIMATION, 0, 0xFFFFFF, CHARGING_ANIMATION_PERIOD * MS_TIC_INTERVAL, TASK_DISABLE, charging_animation_task},
    {TASK_ID_STATIC_BATTERY, 0, 0xFFFFFF, STATIC_BATTERY_UPDATE_PERIOD * MS_TIC_INTERVAL, TASK_ENABLE, static_battery_value_update_task},
};

void task_schedule()
{
    u16 index;
    for (index = 0; index < TASK_NUM; index++) {
        task_t* task = &tasks[index];
        if (task->enable == TASK_ENABLE)
            update_tic(task);
    }
}

u8 update_tic(task_t* task)
{
    if (task->cnt_tic > task->interval_tic) {
        task->cnt_tic = 0;
        task->func();
        task->last_tic = SysTick->VAL;
        return SUCCESS;
    } else {
        u32 now_tic = SysTick->VAL;
        if(now_tic < task->last_tic)
            task->cnt_tic += (task->last_tic - now_tic);
        else
            task->cnt_tic += (SysTick->LOAD - now_tic + task->last_tic);
        task->last_tic = now_tic;
        return ERROR;
    }
}

/*
NOTE: We don't consider the multiply thread situation. Or we need a muxlock or record the current running task.
*/
void task_enable(u8 task_id, u8 enable)
{
    u8 index;
    for (index = 0; index < TASK_NUM; index++) {
        if (tasks[index].task_id == task_id) {
            tasks[index].enable = enable;
            if (enable == TASK_DISABLE) {
                tasks[index].cnt_tic = 0;
                tasks[index].last_tic = 0xFFFFFF;
            }
            break;
        }
    }
}

