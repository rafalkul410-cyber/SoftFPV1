/*#ifndef FCS_APP_H_
#define FCS_APP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "FCS.h"
#include "sensors.h"
#include "lora.h"
#include <stdint.h>
#include <stdbool.h>

 --- Parametry czasowe DShot600 (dla ARR = 119 przy zegarze 72 MHz) ---
#define DSHOT_BIT_0          45
#define DSHOT_BIT_1          90
#define DSHOT_FRAME_SIZE     18
#define DSHOT_MIN_THROTTLE   48
#define DSHOT_MAX_THROTTLE   2047
#define DSHOT_DISARMED       0

 --- Typy wyliczeniowe ---
typedef enum {
    BUZZER_OFF = 0,
    BUZZER_HEARTBEAT,  // Krótki impuls co 1 s (potwierdzenie działania pętli)
    BUZZER_FAILSAFE,   // Szybkie piszczenie ostrzegawcze
    BUZZER_ARMED       // Ciągły sygnał uzbrojenia
} BuzzerState_t;

 --- Zewnętrzne uchwyty timerów ---
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

 --- Deklaracje funkcji FCS ---
void FCS_APP_Init(void);
void FCS_APP_Task(void);
void FCS_APP_UpdateInputs(void);   // Krok w pętli 200 Hz
void FCS_APP_SetMotors(void);
void FCS_APP_BuzzerUpdate(void);
void FCS_APP_SetBuzzerMode(BuzzerState_t mode);

#ifdef __cplusplus
}
#endif

#endif  FCS_APP_H_ */
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
