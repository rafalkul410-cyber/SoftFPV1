#include "fcs_app.h"
#include "sensors.h"
#include "lora.h"
#include "FCS.h"
#include "rtwtypes.h"
#include <math.h>

//--- Uchwyty timerów i I2C ze środowiska STM32 ---
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern I2C_HandleTypeDef hi2c1;

//--- Zmienne zewnętrzne z sensorów i radia ---
extern Sensors_Data_t g_sensors_data;
extern LoRa_ControlPacket_t rx_packet;
extern volatile uint8_t lora_hardware_ok;

//--- Struktury wejść i wyjść Simulinka (Embedded Coder) ---
extern ExtU rtU;
extern ExtY rtY;

//--- Zmienne maszyny stanów ---
DroneState_t g_drone_state = STATE_DISARMED;

static uint16_t arm_counter = 0;
static uint16_t ramp_val = 0;
static uint8_t ramp_direction_down = 0;
static uint8_t flight_engaged = 0; // 0 = na ziemi, 1 = w powietrzu / aktywny lot

//--- Tablice buforów DShot pod DMA1 ---
static uint16_t motor1[DSHOT_FRAME_SIZE]; // TIM1_CH1 - 16-bit
static uint16_t motor2[DSHOT_FRAME_SIZE]; // TIM1_CH4 - 16-bit
static uint32_t motor3[DSHOT_FRAME_SIZE]; // TIM2_CH1 - 32-bit
static uint32_t motor4[DSHOT_FRAME_SIZE]; // TIM2_CH2 - 32-bit

// ==============================================================================
// 1. KODOWANIE DSHOT600 (DMA CIRCULAR)
// ==============================================================================

static void dshot_encode_16(uint16_t *buf, uint16_t val) {
    if (val > TROTTLE_MAX) val = TROTTLE_MAX;

    uint16_t packet = (val << 1);
    uint16_t csum = 0;
    uint16_t csum_data = packet;

    for (int i = 0; i < 3; i++) {
        csum ^= csum_data;
        csum_data >>= 4;
    }
    packet = (packet << 4) | (csum & 0x0F);

    for (int i = 0; i < 16; i++) {
        buf[i] = (packet & 0x8000) ? MOTOR_BIT_1 : MOTOR_BIT_0;
        packet <<= 1;
    }
    for (int i = 16; i < DSHOT_FRAME_SIZE; i++) {
        buf[i] = 0;
    }
}

static void dshot_encode_32(uint32_t *buf, uint16_t val) {
    if (val > TROTTLE_MAX) val = TROTTLE_MAX;

    uint16_t packet = (val << 1);
    uint16_t csum = 0;
    uint16_t csum_data = packet;

    for (int i = 0; i < 3; i++) {
        csum ^= csum_data;
        csum_data >>= 4;
    }
    packet = (packet << 4) | (csum & 0x0F);

    for (int i = 0; i < 16; i++) {
        buf[i] = (packet & 0x8000) ? MOTOR_BIT_1 : MOTOR_BIT_0;
        packet <<= 1;
    }
    for (int i = 16; i < DSHOT_FRAME_SIZE; i++) {
        buf[i] = 0;
    }
}

static void dshot_update_all(uint16_t m1, uint16_t m2, uint16_t m3, uint16_t m4) {
    dshot_encode_16(motor1, m1);
    dshot_encode_16(motor2, m2);
    dshot_encode_32(motor3, m3);
    dshot_encode_32(motor4, m4);
}

// Bezpieczne mapowanie zakresu 48..2047 bez mnożenia
static uint16_t fcs_to_dshot(float val) {
    if (val <= 0.0f) {
        return 0; // Silnik wyłączony
    }
    if (val < (float)TROTTLE_MIN) {
        return TROTTLE_MIN; // Obroty jałowe (48)
    }
    if (val > (float)TROTTLE_MAX) {
        return TROTTLE_MAX; // Maksimum (2047)
    }
    return (uint16_t)val;
}

// Inicjalizacja wyjść DShot i start ciągłego transferu DMA (Circular)
void FCS_APP_Init(void) {
    __HAL_TIM_MOE_ENABLE(&htim1);

    dshot_update_all(0, 0, 0, 0);

    /*HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)motor1, DSHOT_FRAME_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t*)motor2, DSHOT_FRAME_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t*)motor3, DSHOT_FRAME_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, (uint32_t*)motor4, DSHOT_FRAME_SIZE)*/;
}

// ==============================================================================
// 2. PRZEPISANIE DANYCH DO MODELU SIMULINK
// ==============================================================================

void FCS_APP_Task(void) {
    // IMU i Barometr -> Simulink
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

    // Aparatura LoRa -> Simulink
    rtU.controlModePosVSOrient = (real32_T)rx_packet.Mode;
    rtU.takeoff_flag           = (real32_T)flight_engaged;
    rtU.kill_switch            = (real32_T)rx_packet.killswitch;
    rtU.status                 = 0.0f;

    rtU.pos_ref[0]             = 0.0f;
    rtU.pos_ref[1]             = 0.0f;
    rtU.pos_ref[2]             = 0.0f;

    rtU.orient_ref[0] = (real32_T)rx_packet.roll/100.0;
    rtU.orient_ref[1] = (real32_T)rx_packet.pitch/100.0f;
    rtU.orient_ref[2] = (real32_T)rx_packet.yaw/100.0f;
    rtU.orient_ref[3] = (real32_T)rx_packet.throttle / 100.0f;

    uint32_t current_tick      = HAL_GetTick();
    rtU.timestamp_ms           = (real32_T)current_tick;
    rtU.live_time_ticks        = (real32_T)current_tick;
    rtU.vbat_s                 = 12.6f;
}

// ==============================================================================
// 3. MASZYNA STANÓW (200 Hz / 5 ms)
// ==============================================================================

void App_StateMachine(void) {
    // Sprawdzenie bezpieczeństwa
    if (rx_packet.killswitch == 1 || !lora_hardware_ok) {
        g_drone_state = STATE_FAILSAFE;
    }

    switch (g_drone_state) {
        case STATE_DISARMED:
            dshot_update_all(0, 0, 0, 0);
            FCS_initialize();
            flight_engaged = 0; //takeoffflag

            // Warunek uzbrojenia: Killswitch = 0, gaz poniżej 50
            if (rx_packet.killswitch == 0 && rx_packet.throttle < 50 && lora_hardware_ok) {
                arm_counter = 0;
                g_drone_state = STATE_ARMING;
            }
            break;

        case STATE_ARMING:
            dshot_update_all(0, 0, 0, 0);

            if (++arm_counter >= 100) {
                ramp_val = TROTTLE_MIN;
                ramp_direction_down = 0;
                g_drone_state = STATE_RAMP_TEST;
            }
            break;

        case STATE_RAMP_TEST:
            if (!ramp_direction_down) {
                ramp_val += 1;
                if (ramp_val >= (TROTTLE_MIN + 250)) {
                    ramp_direction_down = 1;
                }
            } else {
                if (ramp_val > TROTTLE_MIN) {
                    ramp_val -= 1;
                } else {
                    ramp_val = 0;
                    dshot_update_all(0, 0, 0, 0);

                    FCS_initialize(); // Zerowanie całek tuż przed startem regulacji
                    g_drone_state = STATE_FLY;
                }
            }
            dshot_update_all(ramp_val, ramp_val, ramp_val, ramp_val);
            break;

        case STATE_FLY:
            FCS_APP_Task();

            // Etap 1: Czekanie na ziemi na pierwsze pchnięcie drążka
                        if (!flight_engaged) {
                            if (rx_packet.throttle >= 100) {
                                flight_engaged = 1; // Zatrzaśnięcie lotu: od teraz dron jest w powietrzu
                            } else {
                                // Przed startem trzymaj stany zresetowane i silniki wyłączone (lub na jałowych)
                                FCS_initialize();
                                dshot_update_all(0, 0, 0, 0);
                                break;
                            }
                        }

            // Etap 2: Aktywny lot - Simulink liczy cały czas, niezależnie od puszczenia gałek
                FCS_step();

                dshot_update_all(
                    fcs_to_dshot(rtY.FCSb[0]),
                    fcs_to_dshot(rtY.FCSb[1]),
                    fcs_to_dshot(rtY.FCSb[2]),
                    fcs_to_dshot(rtY.FCSb[3])
                );

            break;

        case STATE_FAILSAFE:
            dshot_update_all(0, 0, 0, 0);
            FCS_initialize();

            if (rx_packet.killswitch == 0 && rx_packet.throttle < 50 && lora_hardware_ok) {
                g_drone_state = STATE_DISARMED;
            }
            break;

        default:
            dshot_update_all(0, 0, 0, 0);
            g_drone_state = STATE_DISARMED;
            break;
    }
}
