#include "fcs_app.h"
#include "sensors.h"
#include "lora.h"
#include "FCS.h"
#include "i2c.h"
#include "tim.h"
#include <math.h>

#define TROTTLE_MIN     48
#define TROTTLE_MAX     2047

//--- Zmienne zewnętrzne z czujników i radia ---
extern Sensors_Data_t g_sensors_data;
extern LoRa_ControlPacket_t rx_packet;
extern volatile uint8_t lora_hardware_ok;
extern I2C_HandleTypeDef hi2c1;

//--- Struktury wejść/wyjść Simulinka (Embedded Coder) ---
extern ExtU rtU;
extern ExtY rtY;

//--- Typy i stany maszyny ---
/*typedef enum {
    STATE_DISARMED = 0,
    STATE_ARMING,
    STATE_RAMP_TEST,
    STATE_FLY,
    STATE_FAILSAFE
} DroneState_t;*/
/*
extern DroneState_t g_drone_state;

// Zmienne obsługi rampy i liczników
static uint16_t arm_counter = 0;
static uint8_t lora_divider = 0;
static uint16_t ramp_val = 0;
static uint8_t ramp_direction_down = 0;


// Tablice DShot dla kontrolera DMA1
static uint16_t motor1[DSHOT_FRAME_SIZE]; // TIM1_CH1 - 16BIT
static uint16_t motor2[DSHOT_FRAME_SIZE]; // TIM1_CH4 - 16BIT
static uint32_t motor3[DSHOT_FRAME_SIZE]; // TIM2_CH1 - 32BIT
static uint32_t motor4[DSHOT_FRAME_SIZE]; // TIM2_CH2 - 32BIT
*/

DroneState_t g_drone_state = STATE_DISARMED;

// --- FUNKCJE KODOWANIA DSHOT ---
/*static void dshot_encode_16(uint16_t *buf, uint16_t val) {
    if (val > 2047) val = 2047;
    uint16_t packet = (val << 1);
    uint16_t csum = 0, csum_data = packet;
    for (int i = 0; i < 3; i++) { csum ^= csum_data; csum_data >>= 4; }
    packet = (packet << 4) | (csum & 0x0F);

    for (int i = 0; i < 16; i++) {
        buf[i] = (packet & 0x8000) ? 200 : 100;
        packet <<= 1;
    }
    for (int i = 16; i < DSHOT_FRAME_SIZE; i++) buf[i] = 0;
}

static void dshot_encode_32(uint32_t *buf, uint16_t val) {
    if (val > 2047) val = 2047;
    uint16_t packet = (val << 1);
    uint16_t csum = 0, csum_data = packet;
    for (int i = 0; i < 3; i++) { csum ^= csum_data; csum_data >>= 4; }
    packet = (packet << 4) | (csum & 0x0F);

    for (int i = 0; i < 16; i++) {
        buf[i] = (packet & 0x8000) ? 200 : 100;
        packet <<= 1;
    }
    for (int i = 16; i < DSHOT_FRAME_SIZE; i++) buf[i] = 0;
}

static void dshot_update_all(uint16_t m1, uint16_t m2, uint16_t m3, uint16_t m4) {
    dshot_encode_16(motor1, m1);
    dshot_encode_16(motor2, m2);
    dshot_encode_32(motor3, m3);
    dshot_encode_32(motor4, m4);
}

// Inicjalizacja wyjść DShot i start ciągłego transferu DMA (Circular)
void FCS_APP_Init(void) {
    __HAL_TIM_MOE_ENABLE(&htim1);

    dshot_update_all(0, 0, 0, 0);

    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)motor1, DSHOT_FRAME_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t*)motor2, DSHOT_FRAME_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t*)motor3, DSHOT_FRAME_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, (uint32_t*)motor4, DSHOT_FRAME_SIZE);
}*/

void FCS_APP_Task(void) {
    // 1. Przypisanie danych z IMU -> Simulink
    rtU.axayaz_s[0] = (real32_T)g_sensors_data.accel_x;
    rtU.axayaz_s[1] = (real32_T)g_sensors_data.accel_y;
    rtU.axayaz_s[2] = (real32_T)g_sensors_data.accel_z;

    rtU.pqr_sf[0]   = (real32_T)g_sensors_data.gyro_x;
    rtU.pqr_sf[1]   = (real32_T)g_sensors_data.gyro_y;
    rtU.pqr_sf[2]   = (real32_T)g_sensors_data.gyro_z;

    rtU.pressure_s  = (real32_T)g_sensors_data.pressure_hpa;
    rtU.temp_s      = (real32_T)g_sensors_data.temp_c;

    if (rtU.pressure_s > 100.0f) {
        rtU.altitude_s = 44330.0f * (1.0f - powf(rtU.pressure_s / 1013.25f, 0.190295f));
    } else {
        rtU.altitude_s = 0.0f;
    }

    rtU.mxmymz_s[0] = 0.0f;
    rtU.mxmymz_s[1] = 0.0f;
    rtU.mxmymz_s[2] = 0.0f;

    // 2. Przypisanie danych z LoRa -> Simulink
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
    rtU.orient_ref[3] = (real32_T)rx_packet.throttle / 1000.0f;

    // 3. Czas systemowy
    uint32_t current_tick      = HAL_GetTick();
    rtU.timestamp_ms           = (real32_T)current_tick;
    rtU.live_time_ticks        = (real32_T)current_tick;
    rtU.vbat_s                 = 12.6f;
}

/*
void App_StateMachine(void) {
    // 1. Wyzwolenie asynchronicznego odczytu IMU w tle przez DMA2
    Sensors_TriggerRead_DMA(&hi2c1);

    // 2. Podpętla wolna 20 Hz (co 50 ms): Odbiór radiowy LoRa
    if (++lora_divider >= 10) {
        lora_divider = 0;
        if (lora_hardware_ok) {
            LoRa_Process(&rx_packet);
        }
    }

    // 3. Globalne sprawdzenie bezpieczeństwa (KillSwitch = 1 lub utrata łączności)
    if (rx_packet.killswitch == 1 || !lora_hardware_ok) {
        g_drone_state = STATE_FAILSAFE;
    }

    // 4. Główna maszyna stanów
    switch (g_drone_state) {
        case STATE_DISARMED:
            dshot_update_all(0, 0, 0, 0);
            FCS_initialize();

            // Bezpieczne przejście: Killswitch = 0 I gaz na dole
            if (rx_packet.killswitch == 1 && rx_packet.throttle < 50 && lora_hardware_ok) {
                arm_counter = 0;
                g_drone_state = STATE_ARMING;
            }
            break;

        case STATE_ARMING:
            // 1. Wysyłamy zera przez 250 ms, aby ESC się uzbroił
            dshot_update_all(0, 0, 0, 0);

            if (++arm_counter >= 50) {
                ramp_val = 0;
                ramp_direction_down = 0;
                g_drone_state = STATE_RAMP_TEST; // Przechodzimy do rampy
            }
            break;

        case STATE_RAMP_TEST:
            // 2. Rampa testowa: płynne rozkręcanie i zwalnianie silników
            if (!ramp_direction_down) {
                ramp_val += 2; // Zwiększaj gaz
                if (ramp_val >= (TROTTLE_MAX / 3)) { // Test do ~33% gazu
                    ramp_val = TROTTLE_MAX / 3;
                    ramp_direction_down = 1;
                }
            } else {
                if (ramp_val > 2) {
                    ramp_val -= 2; // Zmniejszaj gaz
                } else {
                    ramp_val = 0;
                    g_drone_state = STATE_FLY; // Koniec rampy -> przejście do Simulinka
                }
            }

            // Fizyczne wysłanie gazu z rampy na silniki!
            dshot_update_all(ramp_val, ramp_val, ramp_val, ramp_val);
            break;

        case STATE_FLY:
            // 3. Pełna praca algorytmu Simulink FCS
            FCS_APP_Task();
            FCS_step();

            dshot_update_all(
                (uint16_t)(rtY.FCSb[0] * 2047.0f),
                (uint16_t)(rtY.FCSb[1] * 2047.0f),
                (uint16_t)(rtY.FCSb[2] * 2047.0f),
                (uint16_t)(rtY.FCSb[3] * 2047.0f)
            );
            break;

        case STATE_FAILSAFE:
            dshot_update_all(0, 0, 0, 0);
            FCS_initialize();

            if (rx_packet.killswitch == 0 && lora_hardware_ok) {
                g_drone_state = STATE_DISARMED;
            }
            break;

        default:
            g_drone_state = STATE_DISARMED;
            break;
    }
}
*/
