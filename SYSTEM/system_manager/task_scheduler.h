#ifndef __TASK_SCHEDULER_H
#define __TASK_SCHEDULER_H
#include "sys.h"

#define TASK_ENABLE         1
#define TASK_DISABLE        0

#define US_TIC_INTERVAL     6   //SystemClock/8000000
#define MS_TIC_INTERVAL     US_TIC_INTERVAL*1000

enum tasks_id {
    TASK_ID_KEY = 0,
    TASK_ID_STATIC_BATTERY,
    TASK_ID_PERIPHERALS,
    TASK_ID_CHARGING_ANIMATION,
    TASK_NUM,
};

typedef struct {
    enum tasks_id task_id;
    u32 cnt_tic;
    u32 last_tic;
    u32 interval_tic;
    u8 enable;
    void (*func) (void);
} task_t;

u8 update_tic(task_t* task);
void task_schedule(void);
extern void task_enable(u8 task_id, u8 enable);

#endif




