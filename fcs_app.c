
/*
#include "fcs_app.h"
#include <math.h>

 --- Uchwyty peryferiów STM32 ---
extern TIM_HandleTypeDef htim1;

 --- Zmienne zewnętrzne z czujników i radia ---
extern Sensors_Data_t g_sensor_data;   // I2C
extern LoRa_ControlPacket_t rx_packet; // UART / LoRa

 --- Struktury wejść/wyjść Simulinka (Embedded Coder) ---
extern ExtU rtU;
extern ExtY rtY;

 --- Zmienne lokalne modułu ---
static BuzzerState_t buzzer_mode = BUZZER_HEARTBEAT;

// Bufory DMA dla kanałów DShot (16 bitów danych + 2 zera jako odstęp resetu)
static uint32_t dshot_buffer_m1[DSHOT_FRAME_SIZE];
static uint32_t dshot_buffer_m2[DSHOT_FRAME_SIZE];

*
 * @brief  Ustawienie trybu pracy buzzera

void FCS_APP_SetBuzzerMode(BuzzerState_t mode) {
    buzzer_mode = mode;
}

*
 * @brief  Obsługa buzzera w czasie rzeczywistym

void FCS_APP_BuzzerUpdate(void) {
    uint32_t now = HAL_GetTick();

    switch (buzzer_mode) {
        case BUZZER_HEARTBEAT:
            // Krótki impuls 20 ms na początku każdej sekundy
            if ((now % 1000) < 20) {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            }
            break;

        case BUZZER_FAILSAFE:
            // Szybkie piszczenie 100 ms ON / 100 ms OFF
            if ((now % 200) < 100) {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            }
            break;

        case BUZZER_ARMED:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            break;

        case BUZZER_OFF:
        default:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            break;
    }
}

*
 * @brief  Pomocnicza funkcja budująca ramkę DShot600 w pamięci RAM

static void DSHOT_Prepare_Frame(uint16_t value, uint32_t *buffer) {
    if (value > DSHOT_MAX_THROTTLE) {
        value = DSHOT_MAX_THROTTLE;
    }

    uint16_t packet = (value << 1); // bit telemetrii = 0

    // Suma kontrolna CRC (XOR co 4 bity)
    uint16_t csum = 0;
    uint16_t csum_data = packet;
    for (int i = 0; i < 3; i++) {
        csum ^= csum_data;
        csum_data >>= 4;
    }
    csum &= 0x0F;

    packet = (packet << 4) | csum;

    // Kodowanie wypełnienia bitów do rejestru CCR Timera
    for (int i = 0; i < 16; i++) {
        if (packet & (0x8000 >> i)) {
            buffer[i] = DSHOT_BIT_1; // Logiczna "1"
        } else {
            buffer[i] = DSHOT_BIT_0; // Logiczna "0"
        }
    }
    buffer[16] = 0;
    buffer[17] = 0;
}

*
 * @brief  Wysłanie wartości wysterowania silników z Simulinka do ESC przez DShot DMA

void FCS_APP_SetMotors(void) {
    // 1. Pobranie znormalizowanych sygnałów z Simulinka (0.0 - 1.0)
    float val_m1 = rtY.FCSb[1]; // M2 (PA8  - TIM1_CH1)
    float val_m2 = rtY.FCSb[0]; // M1 (PA11 - TIM1_CH4)

    // Ograniczenie zakresu bezpieczeństwa
    if (val_m1 < 0.0f) val_m1 = 0.0f; else if (val_m1 > 1.0f) val_m1 = 1.0f;
    if (val_m2 < 0.0f) val_m2 = 0.0f; else if (val_m2 > 1.0f) val_m2 = 1.0f;

    // 2. Przeskalowanie: 0.0f = DISARM (wartość 0), >0 skalujemy do zakresu 48..2047
    uint16_t dshot_m1 = (val_m1 > 0.001f) ?
        (uint16_t)(DSHOT_MIN_THROTTLE + (val_m1 * (float)(DSHOT_MAX_THROTTLE - DSHOT_MIN_THROTTLE))) : DSHOT_DISARMED;

    uint16_t dshot_m2 = (val_m2 > 0.001f) ?
        (uint16_t)(DSHOT_MIN_THROTTLE + (val_m2 * (float)(DSHOT_MAX_THROTTLE - DSHOT_MIN_THROTTLE))) : DSHOT_DISARMED;

    // 3. Budowanie ramek w buforach DMA
    DSHOT_Prepare_Frame(dshot_m1, dshot_buffer_m1);
    DSHOT_Prepare_Frame(dshot_m2, dshot_buffer_m2);

    // 4. Zatrzymanie poprzednich transferów, aby uniknąć flagi HAL_BUSY
    HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_4);

    // 5. Wystawienie nowej paczki bitów przez DMA
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, dshot_buffer_m1, DSHOT_FRAME_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, dshot_buffer_m2, DSHOT_FRAME_SIZE);
}

*
 * @brief  Inicjalizacja aplikacji pokładowej

void FCS_APP_Init(void) {
    // TIM1 to Advanced Timer – wymaga włączenia Master Output Enable
    __HAL_TIM_MOE_ENABLE(&htim1);

    // Wyczyszczenie buforów
    for (int i = 0; i < DSHOT_FRAME_SIZE; i++) {
        dshot_buffer_m1[i] = 0;
        dshot_buffer_m2[i] = 0;
    }
}

*
 * @brief  Aktualizacja wejść modelu Simulinka

void FCS_APP_Task(void) {
    // ==========================================
    // Przypisanie danych z czujników -> Simulink
    // ==========================================
    rtU.axayaz_s[0] = (real32_T)g_sensor_data.accel_x;
    rtU.axayaz_s[1] = (real32_T)g_sensor_data.accel_y;
    rtU.axayaz_s[2] = (real32_T)g_sensor_data.accel_z;

    rtU.pqr_sf[0]   = (real32_T)g_sensor_data.gyro_x;
    rtU.pqr_sf[1]   = (real32_T)g_sensor_data.gyro_y;
    rtU.pqr_sf[2]   = (real32_T)g_sensor_data.gyro_z;

    rtU.pressure_s  = (real32_T)g_sensor_data.pressure_hpa;
    rtU.temp_s      = (real32_T)g_sensor_data.temp_c;

    // Barometryczny wzór hipsometryczny (wysokość w metrach)
    if (rtU.pressure_s > 100.0f) {
        rtU.altitude_s = 44330.0f * (1.0f - powf(rtU.pressure_s / 1013.25f, 0.190295f));
    } else {
        rtU.altitude_s = 0.0f;
    }

    // Wyzerowanie nieużywanych osi magnetometru
    rtU.mxmymz_s[0] = 0.0f;
    rtU.mxmymz_s[1] = 0.0f;
    rtU.mxmymz_s[2] = 0.0f;

    // ==========================================
    // Przypisanie danych z LoRa -> Simulink
    // ==========================================
    rtU.controlModePosVSOrient = 0.0f;
    rtU.takeoff_flag           = 0.0f;
    rtU.kill_switch            = (real32_T)rx_packet.killswitch;
    rtU.status                 = 0.0f;

    rtU.pos_ref[0]             = 0.0f;
    rtU.pos_ref[1]             = 0.0f;
    rtU.pos_ref[2]             = 0.0f;

    rtU.orient_ref[0] = (real32_T)rx_packet.roll;
    rtU.orient_ref[1] = (real32_T)rx_packet.pitch;
    rtU.orient_ref[2] = (real32_T)rx_packet.yaw;
    rtU.orient_ref[3] = (real32_T)rx_packet.throttle / 1000.0f; // Przeskalowanie 0..1000 na 0.0..1.0

    // ==========================================
    // Czas systemowy i napięcie baterii
    // ==========================================
    uint32_t current_tick      = HAL_GetTick();
    rtU.timestamp_ms           = (real32_T)current_tick;
    rtU.live_time_ticks        = (real32_T)current_tick;
    rtU.vbat_s                 = 12.6f;
}

*
 * @brief  Callback wywoływany przez HAL po zakończeniu transmisji DMA

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM1) {
        HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
        HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_4);
    }
}
*/

#include "fcs_app.h"
#include <math.h>

/* --- Zmienne zewnętrzne --- */
extern TIM_HandleTypeDef htim1;
extern Sensors_Data_t g_sensor_data;
extern LoRa_ControlPacket_t rx_packet;
extern ExtU rtU;
extern ExtY rtY;

/* --- Maszyna stanów i zmienne lokalne --- */
typedef enum {
    FCS_BOOT_DELAY,
    FCS_DISARMED,
    FCS_ARMED
} FCS_State_t;

static BuzzerState_t buzzer_mode = BUZZER_HEARTBEAT;
static FCS_State_t   fcs_state   = FCS_BOOT_DELAY;

static uint32_t dshot_buffer_m1[DSHOT_DMA_BUFFER_SIZE];
static uint32_t dshot_buffer_m2[DSHOT_DMA_BUFFER_SIZE];

/* ========================================================================= */
/* 1. FUNKCJA PRZYGOTOWANIA RAMKI (Musi być PRZED Init)                      */
/* ========================================================================= */
static void DSHOT_Prepare_Frame(uint16_t value, uint32_t *buffer) {
    if (value > DSHOT_MAX_THROTTLE) {
        value = DSHOT_MAX_THROTTLE;
    }

    uint16_t packet = (value << 1);

    uint16_t csum = 0;
    uint16_t csum_data = packet;
    for (int i = 0; i < 3; i++) {
        csum ^= csum_data;
        csum_data >>= 4;
    }
    csum &= 0x0F;

    packet = (packet << 4) | csum;

    for (int i = 0; i < DSHOT_FRAME_BITS; i++) {
        if (packet & (0x8000 >> i)) {
            buffer[i] = DSHOT_BIT_1;
        } else {
            buffer[i] = DSHOT_BIT_0;
        }
    }
    buffer[16] = 0;
    buffer[17] = 0;
}

/* ========================================================================= */
/* 2. INICJALIZACJA I SEKWENCJA STARTOWA                                      */
/* ========================================================================= */
void FCS_APP_Init(void) {
    __HAL_TIM_MOE_ENABLE(&htim1);

    // Zbudowanie ramki DISARM (0)
    DSHOT_Prepare_Frame(DSHOT_DISARMED, dshot_buffer_m1);
    DSHOT_Prepare_Frame(DSHOT_DISARMED, dshot_buffer_m2);

    // Wysyłanie zer przez 2.5 sekundy na start (ESC odgrywa 5 dźwięków)
    for (int i = 0; i < 250; i++) {
        HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
        HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_4);

        HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, dshot_buffer_m1, DSHOT_DMA_BUFFER_SIZE);
        HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, dshot_buffer_m2, DSHOT_DMA_BUFFER_SIZE);

        HAL_Delay(10);
    }

    fcs_state   = FCS_DISARMED;
    buzzer_mode = BUZZER_HEARTBEAT;
}

/* ========================================================================= */
/* 3. STEROWANIE SILNIKAMI W PĘTLI GŁÓWNEJ                                    */
/* ========================================================================= */
/*void FCS_APP_SetMotors(void) {
    uint16_t dshot_m1 = DSHOT_DISARMED;
    uint16_t dshot_m2 = DSHOT_DISARMED;

    if (rx_packet.killswitch == 1) {
        fcs_state = FCS_DISARMED;
        FCS_APP_SetBuzzerMode(BUZZER_HEARTBEAT);
    } else if (fcs_state == FCS_DISARMED && rx_packet.killswitch == 0 && rx_packet.throttle < 50) {
        fcs_state = FCS_ARMED;
        FCS_APP_SetBuzzerMode(BUZZER_ARMED);
    }

    if (fcs_state == FCS_ARMED) {
        dshot_m1 = (uint16_t)rtY.FCSb[0];
        dshot_m2 = (uint16_t)rtY.FCSb[2];

        if (dshot_m1 < DSHOT_MIN_THROTTLE) dshot_m1 = DSHOT_DISARMED;
        if (dshot_m1 > DSHOT_MAX_THROTTLE) dshot_m1 = DSHOT_MAX_THROTTLE;

        if (dshot_m2 < DSHOT_MIN_THROTTLE) dshot_m2 = DSHOT_DISARMED;
        if (dshot_m2 > DSHOT_MAX_THROTTLE) dshot_m2 = DSHOT_MAX_THROTTLE;
    }

    DSHOT_Prepare_Frame(dshot_m1, dshot_buffer_m1);
    DSHOT_Prepare_Frame(dshot_m2, dshot_buffer_m2);

    HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_4);

    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, dshot_buffer_m1, DSHOT_DMA_BUFFER_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, dshot_buffer_m2, DSHOT_DMA_BUFFER_SIZE);
}*/

void FCS_APP_SetMotors(void) {
    // Wymuszenie bezpiecznych, stałych obrotów po uzbrojeniu:
    uint16_t dshot_m1 = 250;
    uint16_t dshot_m2 = 250;

    DSHOT_Prepare_Frame(dshot_m1, dshot_buffer_m1);
    DSHOT_Prepare_Frame(dshot_m2, dshot_buffer_m2);

    HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_4);

    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, dshot_buffer_m1, DSHOT_DMA_BUFFER_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, dshot_buffer_m2, DSHOT_DMA_BUFFER_SIZE);
}

/* ========================================================================= */
/* 4. POZOSTAŁE FUNKCJE (Buzzer, Task, Callback)                             */
/* ========================================================================= */
void FCS_APP_SetBuzzerMode(BuzzerState_t mode) {
    buzzer_mode = mode;
}

void FCS_APP_BuzzerUpdate(void) {
    uint32_t now = HAL_GetTick();

    switch (buzzer_mode) {
        case BUZZER_HEARTBEAT:
            if ((now % 1000) < 20) {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            }
            break;

        case BUZZER_FAILSAFE:
            if ((now % 200) < 100) {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            }
            break;

        case BUZZER_ARMED:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            break;

        case BUZZER_OFF:
        default:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            break;
    }
}

void FCS_APP_Task(void) {
    rtU.axayaz_s[0] = (real32_T)g_sensor_data.accel_x;
    rtU.axayaz_s[1] = (real32_T)g_sensor_data.accel_y;
    rtU.axayaz_s[2] = (real32_T)g_sensor_data.accel_z;

    rtU.pqr_sf[0]   = (real32_T)g_sensor_data.gyro_x;
    rtU.pqr_sf[1]   = (real32_T)g_sensor_data.gyro_y;
    rtU.pqr_sf[2]   = (real32_T)g_sensor_data.gyro_z;

    rtU.pressure_s  = (real32_T)g_sensor_data.pressure_hpa;
    rtU.temp_s      = (real32_T)g_sensor_data.temp_c;

    if (rtU.pressure_s > 100.0f) {
        rtU.altitude_s = 44330.0f * (1.0f - powf(rtU.pressure_s / 1013.25f, 0.190295f));
    } else {
        rtU.altitude_s = 0.0f;
    }

    rtU.mxmymz_s[0] = 0.0f;
    rtU.mxmymz_s[1] = 0.0f;
    rtU.mxmymz_s[2] = 0.0f;

    rtU.controlModePosVSOrient = 0.0f;
    rtU.takeoff_flag           = 0.0f;
    rtU.kill_switch            = (real32_T)rx_packet.killswitch;
    rtU.status                 = 0.0f;

    rtU.pos_ref[0]             = 0.0f;
    rtU.pos_ref[1]             = 0.0f;
    rtU.pos_ref[2]             = 0.0f;

    rtU.orient_ref[0]          = (real32_T)rx_packet.roll;
    rtU.orient_ref[1]          = (real32_T)rx_packet.pitch;
    rtU.orient_ref[2]          = (real32_T)rx_packet.yaw;
    rtU.orient_ref[3]          = (real32_T)rx_packet.throttle / 1000.0f;

    uint32_t current_tick      = HAL_GetTick();
    rtU.timestamp_ms           = (real32_T)current_tick;
    rtU.live_time_ticks        = (real32_T)current_tick;
    rtU.vbat_s                 = 12.6f;
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM1) {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
        }
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4) {
            HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_4);
        }
    }
}
