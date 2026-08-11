
#include "fcs_app.h"
#include <math.h>

extern Sensors_Data_t g_sensor_data;   // I2C
extern LoRa_ControlPacket_t rx_packet; // UART

//sturktury simulinka
extern ExtU rtU;
extern ExtY rtY;

typedef enum {
    BUZZER_OFF = 0,
    BUZZER_HEARTBEAT,  // Krótki "cyk" co 1 sekundę (potwierdzenie, że while żyje)
    BUZZER_FAILSAFE,   // Szybkie piszczenie (utrata sygnału / błąd)
    BUZZER_ARMED       // Ciągły sygnał ostrzegawczy
} BuzzerState_t;

static BuzzerState_t buzzer_mode = BUZZER_HEARTBEAT;

void FCS_APP_BuzzerUpdate(void) {
    uint32_t now = HAL_GetTick();

    switch (buzzer_mode) {
        case BUZZER_HEARTBEAT:
            // Krótki impuls 20 ms na początku każdej sekundy (co 1000 ms)
            if ((now % 1000) < 20) {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            }
            break;

        case BUZZER_FAILSAFE:
            // Szybkie miganie/piszczenie 100 ms ON / 100 ms OFF
            if ((now % 200) < 100) {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
            } else {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            }
            break;

        case BUZZER_OFF:
        default:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
            break;
    }
}

void FCS_APP_SetMotors(void){
	uint32_t ccr[4];

	    for (int i = 0; i < 4; i++) {
	        float val = rtY.FCSb[i];

	        // Ograniczenie sygnału z Simulinka do bezpiecznego zakresu 0.0 - 1.0
	        if (val < 0.0f) val = 0.0f;
	        if (val > 1.0f) val = 1.0f;

	        // Prescaler = 79 oznacza, że 1 tick = 1 us.
	        // Przeliczenie 0.0 - 1.0 na impuls ESC od 1000 us (stop) do 2000 us (max gaz):
	        ccr[i] = 1000 + (uint32_t)(val * 1000.0f);
	    }

	    // Przypisanie wypełnienia do odpowiednich pinów i timerów:
	    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, ccr[0]); // M1 (PA11)
	    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, ccr[1]); // M2 (PA8)
	    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, ccr[2]); // M3 (PA1)
	    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, ccr[3]); // M4 (PA0)

}

void FCS_APP_Task(void) {
    // ==========================================
    // Przypisanie gotowych danych z I2C -> Simulink
    // ==========================================
    rtU.axayaz_s[0] = (real32_T)g_sensor_data.accel_x;
    rtU.axayaz_s[1] = (real32_T)g_sensor_data.accel_y;
    rtU.axayaz_s[2] = (real32_T)g_sensor_data.accel_z;

    rtU.pqr_sf[0]   = (real32_T)g_sensor_data.gyro_x;
    rtU.pqr_sf[1]   = (real32_T)g_sensor_data.gyro_y;
    rtU.pqr_sf[2]   = (real32_T)g_sensor_data.gyro_z;

    rtU.pressure_s  = (real32_T)g_sensor_data.pressure_hpa;
    rtU.temp_s      = (real32_T)g_sensor_data.temp_c;

    // Przeliczenie wysokości z ciśnienia
    rtU.altitude_s  = 44330.0f * (1.0f - powf(rtU.pressure_s / 1013.25f, 0.190295f));

    // Wypełnienie zerami nieużywanych czujników
    rtU.mxmymz_s[0] = 0.0f;
    rtU.mxmymz_s[1] = 0.0f;
    rtU.mxmymz_s[2] = 0.0f;

    // ==========================================
    // Przypisanie gotowych danych z UART -> Simulink
    // ==========================================
    rtU.controlModePosVSOrient =0.0f;
    rtU.takeoff_flag           =0.0f;
    rtU.kill_switch            =0.0f;
    rtU.status                 =0.0f;

    rtU.pos_ref[0]             = 0.0f;  // x,y,z_ref
    rtU.pos_ref[1]             = 0.0f;
    rtU.pos_ref[2]             = 0.0f;

    rtU.orient_ref[0] = (real32_T)rx_packet.roll;     // Przechylenie (Roll)
        rtU.orient_ref[1] = (real32_T)rx_packet.pitch;    // Pochylenie (Pitch)
        rtU.orient_ref[2] = (real32_T)rx_packet.yaw;      // Odchylenie (Yaw)
        rtU.orient_ref[3] = (real32_T)rx_packet.throttle / 1000.0f; // Throttle z pakietu (0-1000) przeskalowany do zakresu 0.0 - 1.0 dla Simulinka:
    // ==========================================
    // Czas systemowy i zasilanie
    // ==========================================
    uint32_t current_tick      = HAL_GetTick();
    rtU.timestamp_ms           = (real32_T)current_tick;
    rtU.live_time_ticks        = (real32_T)current_tick;
    rtU.vbat_s                 = 12.6f;

}


