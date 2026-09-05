#include "fcs_app.h"
#include "sensors.h"
#include "lora.h"
#include "FCS.h"
#include "rtwtypes.h"
#include <math.h>
#include "vbat.h"

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

    htim1.State = HAL_TIM_STATE_READY;
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)motor1, DSHOT_FRAME_SIZE);

    htim1.State = HAL_TIM_STATE_READY;
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t*)motor2, DSHOT_FRAME_SIZE);

    htim2.State = HAL_TIM_STATE_READY;
    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t*)motor3, DSHOT_FRAME_SIZE);

    htim2.State = HAL_TIM_STATE_READY;
    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, (uint32_t*)motor4, DSHOT_FRAME_SIZE);
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

/*    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)motor1, DSHOT_FRAME_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t*)motor2, DSHOT_FRAME_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t*)motor3, DSHOT_FRAME_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, (uint32_t*)motor4, DSHOT_FRAME_SIZE);*/
}

// ==============================================================================
// 2. PRZEPISANIE DANYCH DO MODELU SIMULINK WRAZ Z FILTRACJĄ
// ==============================================================================
typedef struct {
    float state;
    float alpha;
} LPF_Filter_t;

// Funkcja aktualizacji filtru
static inline float LPF_Update(LPF_Filter_t *filter, float input) {
    filter->state += filter->alpha * (input - filter->state);
    return filter->state;
}

// 1. Filtry żyroskopu: fc = ~25 Hz -> alpha = 0.44
static LPF_Filter_t lpf_gyro_p = { .state = 0.0f, .alpha = 0.44f };
static LPF_Filter_t lpf_gyro_q = { .state = 0.0f, .alpha = 0.44f };
static LPF_Filter_t lpf_gyro_r = { .state = 0.0f, .alpha = 0.44f };

// 2. Filtry akcelerometru: fc = ~10 Hz -> alpha = 0.24
static LPF_Filter_t lpf_accel_x = { .state = 0.0f, .alpha = 0.24f };
static LPF_Filter_t lpf_accel_y = { .state = 0.0f, .alpha = 0.24f };
static LPF_Filter_t lpf_accel_z = { .state = 1.0f, .alpha = 0.24f };

static void LPF_Reset_All(void) {
    lpf_gyro_p.state = 0.0f;
    lpf_gyro_q.state = 0.0f;
    lpf_gyro_r.state = 0.0f;

    lpf_accel_x.state = 0.0f;
    lpf_accel_y.state = 0.0f;
    lpf_accel_z.state = 1.0f; // Wpisanie aktualnego 1G
}

void FCS_APP_Task(void) {
    // IMU i Barometr -> Simulink
	float raw_ax = -(float)g_sensors_data.accel_y;
	float raw_ay =  (float)g_sensors_data.accel_x;
	float raw_az = -(float)g_sensors_data.accel_z;

    rtU.axayaz_s[0] = (real32_T)LPF_Update(&lpf_accel_x, raw_ax);
	rtU.axayaz_s[1] = (real32_T)LPF_Update(&lpf_accel_y, raw_ay);
	rtU.axayaz_s[2] = (real32_T)LPF_Update(&lpf_accel_z, raw_az);

	float raw_gx =  (float)g_sensors_data.gyro_y*0.0174532925f;  // deg/s --> rad/s
    float raw_gy =  (float)g_sensors_data.gyro_x*0.0174532925f;
    float raw_gz =  (float)g_sensors_data.gyro_z*0.0174532925f;

    rtU.pqr_sf[0]   = (real32_T)LPF_Update(&lpf_gyro_p, raw_gx);
    rtU.pqr_sf[1]   = (real32_T)LPF_Update(&lpf_gyro_q, raw_gy);
    rtU.pqr_sf[2]   = (real32_T)LPF_Update(&lpf_gyro_r, raw_gz);

	/*	rtU.axayaz_s[0] = 0.0f;
	    rtU.axayaz_s[1] = 0.0f;
	    rtU.axayaz_s[2] = 1.0f; // 1G w osi Z

	    rtU.pqr_sf[0]   = 0.0f; // brak rotacji roll
	    rtU.pqr_sf[1]   = 0.0f; // brak rotacji pitch
	    rtU.pqr_sf[2]   = 0.0f; // brak rotacji yaw*/


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
    //rtU.controlModePosVSOrient = (real32_T)rx_packet.Mode;
    rtU.controlModePosVSOrient = 0.0f;
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
    rtU.vbat_s                 = (real32_T)g_vbat_voltage;
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
            flight_engaged = 0; //takeoffflag
            //FCS_initialize();

            // Warunek uzbrojenia: Killswitch = 0, gaz poniżej 50
            if (rx_packet.killswitch == 0 && rx_packet.throttle < 50 && lora_hardware_ok) {
                arm_counter = 0;
                g_drone_state = STATE_ARMING;
            }
            break;

        case STATE_ARMING:
        	flight_engaged = 0;
            dshot_update_all(0, 0, 0, 0);

            if (++arm_counter >= 600) {
                ramp_val = TROTTLE_MIN;
                ramp_direction_down = 0;
                g_drone_state = STATE_RAMP_TEST;
            }
            break;

        case STATE_RAMP_TEST:
        	flight_engaged = 0;
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
                    //LPF_Reset_All();
                    g_drone_state = STATE_FLY;
                }
            }
            dshot_update_all(ramp_val, ramp_val, ramp_val, ramp_val);
            break;

        case STATE_FLY:
            // Etap 1: Czekanie na ziemi na pierwsze pchnięcie drążka
                        if (!flight_engaged) {
                            if (rx_packet.throttle >= 20) {
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

             static float m1, m2, m3, m4;
                m1 =  rtY.FCSb[0] *0.33f;
                m2 =  rtY.FCSb[1] *0.33f;
                m3 =  rtY.FCSb[2] *0.33f;
                m4 =  rtY.FCSb[3] *0.33f;

                dshot_update_all(
                    fcs_to_dshot(m1),
                    fcs_to_dshot(m2),
                    fcs_to_dshot(m3),
                    fcs_to_dshot(m4)
                );


               //dshot_update_all(80, 80, 80, 80);

           /*     dshot_update_all(
                fcs_to_dshot(rtY.FCSb[0]),
                fcs_to_dshot(rtY.FCSb[1]),
                fcs_to_dshot(rtY.FCSb[2]),
                fcs_to_dshot(rtY.FCSb[3])
                );*/

            break;

        case STATE_FAILSAFE:
            dshot_update_all(0, 0, 0, 0);
            flight_engaged = 0;

            if (rx_packet.killswitch == 0 && rx_packet.throttle < 50 && lora_hardware_ok) {
                g_drone_state = STATE_DISARMED;
                FCS_initialize();
            }
            break;

        default:
            dshot_update_all(0, 0, 0, 0);
            g_drone_state = STATE_DISARMED;
            break;
    }
}


