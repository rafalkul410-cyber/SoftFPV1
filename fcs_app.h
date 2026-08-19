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

#include "stm32l4xx_hal.h"
#include "main.h"
#include <stdint.h>
#include <stdbool.h>

#include "FCS.h"
#include "sensors.h"
#include "lora.h"

/* --- Parametry DShot600 (STM32L4 @ 72/80 MHz) --- */


#define DSHOT_BIT_0             50
#define DSHOT_BIT_1             100
#define DSHOT_FRAME_BITS        16
#define DSHOT_DMA_BUFFER_SIZE   18

#define DSHOT_DISARMED          0
#define DSHOT_MIN_THROTTLE      48
#define DSHOT_MAX_THROTTLE      2047

typedef enum {
    BUZZER_OFF = 0,
    BUZZER_HEARTBEAT,
    BUZZER_FAILSAFE,
    BUZZER_ARMED
} BuzzerState_t;

void FCS_APP_Init(void);
void FCS_APP_Task(void);
void FCS_APP_SetMotors(void);
void FCS_APP_BuzzerUpdate(void);
void FCS_APP_SetBuzzerMode(BuzzerState_t mode);

#ifdef __cplusplus
}
#endif

#endif /* FCS_APP_H_ */
