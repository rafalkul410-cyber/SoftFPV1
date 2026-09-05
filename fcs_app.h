#ifndef FCS_APP_H_
#define FCS_APP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

/* --- Konfiguracja DShot600 --- */
#define MOTOR_BIT_0           100
#define MOTOR_BIT_1           200
#define DSHOT_FRAME_SIZE      32

#define TROTTLE_MIN           48
#define TROTTLE_MAX           2047

#define DSHOT_CMD_SPIN_DIR_NORMAL   20   // Kierunek 1 (domyślny / CW)
#define DSHOT_CMD_SPIN_DIR_REVERSED 21   // Kierunek 2 (odwrócony / CCW)
#define DSHOT_CMD_SAVE_SETTINGS     12   // Zapis do EEPROM regulatora

/* --- Typy stanów maszyny drona --- */
typedef enum {
    STATE_DISARMED = 0,
    STATE_ARMING,
    STATE_RAMP_TEST,
    STATE_FLY,
    STATE_FAILSAFE
} DroneState_t;

extern DroneState_t g_drone_state;

/* --- Prototypy funkcji modułu FCS --- */
void FCS_APP_Init(void);
void FCS_APP_Task(void);
void App_StateMachine(void);

#ifdef __cplusplus
}
#endif

#endif /* FCS_APP_H_ */
