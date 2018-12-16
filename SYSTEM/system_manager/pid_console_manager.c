#include "pid_console_manager.h"
#include "system_state.h"
#include "PID.h"

static u8 current_pid_command = CMD_STOP;
static u8 pid_lock = PID_UNLOCK;

u8 get_current_pid_command()
{
    return current_pid_command;
}

void send_pid_command(u8 command_id, u8 reset)
{
    if (command_id == CMD_SMOKE || pid_lock != PID_LOCK) {
        if (reset == PID_RESET) {
            Force_PID_Start();
        }
        switch (command_id) {
            case CMD_SMOKE:
                set_system_smoke(SYS_SMOKE);
                break;
            case CMD_STOP:
                set_system_smoke(SYS_NOT_SMOKE);
                break;
        }
        current_pid_command = command_id;
    }
}

void set_pid_lock(u8 lock)
{
    pid_lock = lock;
}

u8 get_pid_lock()
{
    return pid_lock;
}


