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
#include "FCS.h"
#include "sensors.h"
#include "lora.h"
#include <stdint.h>
#include <stdbool.h>

/* --- Konfiguracja DShot600 (zgodna z Twoim kodem bazowym) --- */
#define MOTOR_BIT_0           100
#define MOTOR_BIT_1           200
#define DSHOT_FRAME_SIZE      32 // 64 bylo i dzialalo
#define MOTOR_BITLENGTH       20

#define TROTTLE_MIN   48
#define TROTTLE_MAX    2047

#define ESC_POWER_UP    600 // Czas oczekiwania/uzbrajania w przerwaniach TIM6 (np. 2 sekundy przy 1 kHz)

/* --- Typy stanów buzzera --- */
typedef enum {
    BUZZER_OFF = 0,
    BUZZER_HEARTBEAT,
    BUZZER_FAILSAFE,
    BUZZER_ARMED
} BuzzerState_t;

/*
 --- Deklaracje timerów peryferiów ---
extern TIM_HandleTypeDef htim1; // Silniki  1,2 (np. CH1)
extern TIM_HandleTypeDef htim2; // Silnik 3,4  (np. CH1)
extern TIM_HandleTypeDef htim6; // Główny timer pętli przerwań
*/

/* --- Główne funkcje modułu --- */
void FCS_APP_Init(void);
void FCS_APP_Task(void);
void App_StateMachine(void);


typedef enum {
    STATE_DISARMED = 0,
    STATE_ARMING,
    STATE_RAMP_TEST,
    STATE_FLY,
    STATE_FAILSAFE
} DroneState_t;

extern DroneState_t g_drone_state;


#ifdef __cplusplus
}
#endif

#endif /* FCS_APP_H_ */
