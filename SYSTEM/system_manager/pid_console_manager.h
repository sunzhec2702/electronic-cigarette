#ifndef __PID_CONSOLE_MANAGER_H
#define __PID_CONSOLE_MANAGER_H
#include "sys.h"

#define PID_LOCK      0x22
#define PID_UNLOCK    0x11
#define PID_RESET       1
#define PID_NOT_RESET   0

#define CMD_STOP            0
#define CMD_SMOKE           1
#define CMD_MEAS_REG        2
#define CMD_MEAS_VOLTAGE    3

extern u8 get_current_pid_command(void);
extern void send_pid_command(u8 command_id, u8 reset);
extern void set_pid_lock(u8 lock);
extern u8 get_pid_lock(void);

#endif


