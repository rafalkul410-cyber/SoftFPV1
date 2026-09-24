#include "fcs_app.h"
#include "sensors.h"
#include "lora.h"
#include "FCS.h"
#include "rtwtypes.h"
#include <math.h>
#include "vbat.h"
#include "main.h"

//--- Zmienne zewnętrzne z sensorów i radia ---
extern Sensors_Data_t g_sensors_data;
extern LoRa_ControlPacket_t rx_packet;
extern volatile uint8_t lora_hardware_ok;

//--- Struktury wejść i wyjść Simulinka (Embedded Coder) ---
extern ExtU_FCS_T FCS_U;
extern ExtY_FCS_T FCS_Y;

//--- Zmienne maszyny stanów ---
DroneState_t g_drone_state = STATE_DISARMED;
static uint16_t arm_counter = 0;
static uint16_t ramp_val = 0;
static uint8_t ramp_direction_down = 0;
static uint8_t flight_engaged = 0; // 0 = na ziemi, 1 = w powietrzu

//Struktura filtrów
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
	float raw_ax =  -(float)g_sensors_data.accel_y;
	float raw_ay =  (float)g_sensors_data.accel_x;
	float raw_az = -(float)g_sensors_data.accel_z;

    FCS_U.axayaz_s[0] = (real32_T)LPF_Update(&lpf_accel_x, raw_ax)*9.81f;
	FCS_U.axayaz_s[1] = (real32_T)LPF_Update(&lpf_accel_y, raw_ay)*9.81f;
	FCS_U.axayaz_s[2] = (real32_T)LPF_Update(&lpf_accel_z, raw_az)*9.81f;//w spocz

	float raw_gx =  (float)g_sensors_data.gyro_y*0.0174532925f;  // deg/s --> rad/s
    float raw_gy =  (float)g_sensors_data.gyro_x*0.0174532925f;
    float raw_gz =  (float)g_sensors_data.gyro_z*0.0174532925f;

    FCS_U.pqr_sf[0]   = (real32_T)LPF_Update(&lpf_gyro_p, raw_gx);
    FCS_U.pqr_sf[1]   = -(real32_T)LPF_Update(&lpf_gyro_q, raw_gy);
    FCS_U.pqr_sf[2]   = (real32_T)LPF_Update(&lpf_gyro_r, raw_gz);

    FCS_U.pressure_s  = (real32_T)g_sensors_data.pressure_hpa;
    FCS_U.temp_s      = (real32_T)g_sensors_data.temp_c;

    if (FCS_U.pressure_s > 100.0f) {
        FCS_U.altitude_s = 44330.0f * (1.0f - powf(FCS_U.pressure_s / 1013.25f, 0.190295f));
    } else {
        FCS_U.altitude_s = 0.0f;
    }

    FCS_U.mxmymz_s[0] = 0.0f;
    FCS_U.mxmymz_s[1] = 0.0f;
    FCS_U.mxmymz_s[2] = 0.0f;

    // Aparatura LoRa -> Simulink
    FCS_U.controlModePosVSOrient = (real32_T)rx_packet.Mode;
    FCS_U.takeoff_flag           = (real32_T)flight_engaged;
    FCS_U.kill_switch            = (real32_T)rx_packet.killswitch;
    FCS_U.status                 = 0.0f;

    FCS_U.pos_ref[0]             = 0.0f;
    FCS_U.pos_ref[1]             = 0.0f;
    FCS_U.pos_ref[2]             = 0.0f;

    FCS_U.orient_ref[0] = (real32_T)rx_packet.roll/100.0;
    FCS_U.orient_ref[1] = (real32_T)rx_packet.pitch/100.0f;
    FCS_U.orient_ref[2] = (real32_T)rx_packet.yaw/100.0f;
    //FCS_U.orient_ref[3] = (real32_T)rx_packet.throttle / 100.0f;
    FCS_U.orient_ref[3] = rx_packet.potValue/100.0f;

    uint32_t current_tick      = HAL_GetTick();
    FCS_U.timestamp_ms           = (real32_T)current_tick;
    FCS_U.live_time_ticks        = (real32_T)current_tick;
    FCS_U.vbat_s                 = (real32_T)g_vbat_voltage;
}

void App_StateMachine(void) {
    // Sprawdzenie bezpieczeństwa
    if (rx_packet.killswitch == 1 || lora_hardware_ok==0) {
        g_drone_state = STATE_FAILSAFE;
    }

    switch (g_drone_state) {
        case STATE_DISARMED:
        	dshot_write(0, 0, 0, 0);
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
        	dshot_write(0, 0, 0, 0);

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
                    dshot_write(0, 0, 0, 0);

                    FCS_initialize(); // Zerowanie całek tuż przed startem regulacji
                    //LPF_Reset_All();
                    g_drone_state = STATE_FLY;
                }
            }
        	dshot_write(ramp_val, ramp_val, ramp_val, ramp_val);
            break;

        case STATE_FLY:
            // Etap 1: Czekanie na ziemi na pierwsze pchnięcie drążka
                        if (!flight_engaged) {
                            if (rx_packet.throttle >= 20) {
                                flight_engaged = 1; // Zatrzaśnięcie lotu: od teraz dron jest w powietrzu
                            } else {
                                // Przed startem trzymaj stany zresetowane i silniki wyłączone (lub na jałowych)
                                FCS_initialize();
                                dshot_write(0, 0, 0, 0);
                                break;
                            }
                        }

            // Etap 2: Aktywny lot - Simulink
                FCS_APP_Task();
                FCS_step();
             // dshot_write(100,0, 100, 0);

       /*      static float m1, m2, m3, m4;
                m1 =  FCS_Y.FCSb[0]*0.5f;
                m2 =  FCS_Y.FCSb[1]*0.5f;
                m3 =  FCS_Y.FCSb[2]*0.5f;
                m4 =  FCS_Y.FCSb[3]*0.5f;*/
/*
            static float m1, m2, m3, m4;
            m1 = (real32_T)rx_packet.potValue;
            m2 = (real32_T)rx_packet.potValue;
            m3 = (real32_T)rx_packet.potValue;
            m4 = (real32_T)rx_packet.potValue;


                	dshot_write(m1, m2, m3, m4);
*/

             dshot_write(
                    FCS_Y.FCSb[1],
                    FCS_Y.FCSb[0],
                    FCS_Y.FCSb[3],
                    FCS_Y.FCSb[2]
                );

            break;

        case STATE_FAILSAFE:
        	dshot_write(0, 0, 0, 0);
            flight_engaged = 0;

            if (rx_packet.killswitch == 0 && rx_packet.throttle < 50 && lora_hardware_ok) {
                g_drone_state = STATE_DISARMED;
                FCS_initialize();
            }
            break;

        default:
        	dshot_write(0, 0, 0, 0);
            g_drone_state = STATE_DISARMED;
            break;
    }
}


