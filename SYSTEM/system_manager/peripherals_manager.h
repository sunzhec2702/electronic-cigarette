#ifndef __PERIPHERALS_MANAGER_H
#define __PERIPHERALS_MANAGER_H
#include "sys.h"

#define PERIPHERALS_STATE_UPDATE_PERIOD    100
#define COIL_R_STATIC_OFFSET                1

#define CHARGER_UNPLUGGED   0
#define CHARGER_PLUGGED     1
#define CHARGER_FLAG_REG_VALUE      4
#define CHARGER_FLAG_OFFSET_VALUE   28
#define CHARGER_FLAG_MASK_VALUE   0x1

#define COIL_READY          1
#define COIL_NOT_READY      0
#define COIL_READY_FLAG_REG_VALUE      4
#define COIL_READY_FLAG_OFFSET_VALUE   27
#define COIL_READY_FLAG_MASK_VALUE   0x1

#define COIL_R_STATIC_REG_VALUE      2
#define COIL_R_STATIC_OFFSET_VALUE   16
#define COIL_R_STATIC_MASK_VALUE   0xFFFF


extern void peripherals_init(void);
extern void charger_init(void);
extern void peripherals_update_task(void);
void charger_update_task(void);
void coils_state_task(void);
void ntc_temperature_task(void);



extern void set_charger_plug_flag(void);
extern void clear_charger_plug_flag(void);
extern u8 get_charger_plug_flag(void);
extern void set_coil_ready_flag(void);
extern void clear_coil_ready_flag(void);
extern u8 get_coil_ready_flag(void);


extern u16 get_coil_r_static(void);
extern void coil_r_static_update(void);
extern void coil_r_static_backup(void);
extern void coil_r_static_restore(void);

extern void environment_temperature_update(u16 temperature);
extern u16 get_environment_temperature(void);

#endif




