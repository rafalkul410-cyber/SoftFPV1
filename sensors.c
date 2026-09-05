#include "sensors.h"

// Zmienne kalibracyjne BME280
typedef struct {
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;
    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;
} BME280_Calib_t;

static BME280_Calib_t bme_calib;
static float t_fine_temp;

static float accel_bias_x = 0.0f;
static float accel_bias_y = 0.0f;
static float accel_bias_z = 0.0f;

static float gyro_bias_x = 0.0f;
static float gyro_bias_y = 0.0f;
static float gyro_bias_z = 0.0f;

Sensors_Data_t g_sensors_data;

// Bufory DMA
static uint8_t mpu_dma_raw[14];
static uint8_t bme_dma_raw[6];

typedef enum {
    I2C_IDLE = 0,
    I2C_READING_MPU,
    I2C_READING_BME
} I2C_State_t;

static volatile I2C_State_t i2c_state = I2C_IDLE;

// --- KALKULACJE BME280 ---
static float BME280_CalcTemp(int32_t adc_T) {
    float v1 = (((float)adc_T) / 16384.0f - ((float)bme_calib.dig_T1) / 1024.0f) * ((float)bme_calib.dig_T2);
    float v2 = ((((float)adc_T) / 131072.0f - ((float)bme_calib.dig_T1) / 8192.0f) *
                (((float)adc_T) / 131072.0f - ((float)bme_calib.dig_T1) / 8192.0f)) * ((float)bme_calib.dig_T3);
    t_fine_temp = v1 + v2;
    return (v1 + v2) / 5120.0f;
}

static float BME280_CalcPress(int32_t adc_P) {
    float v1 = (t_fine_temp / 2.0f) - 64000.0f;
    float v2 = v1 * v1 * ((float)bme_calib.dig_P6) / 32768.0f + v1 * ((float)bme_calib.dig_P5) * 2.0f + ((float)bme_calib.dig_P4) * 65536.0f;
    v1 = (((float)bme_calib.dig_P3) * v1 * v1 / 524288.0f + ((float)bme_calib.dig_P2) * v1) / 524288.0f;
    v1 = (1.0f + v1 / 32768.0f) * ((float)bme_calib.dig_P1);

    if (v1 == 0.0f) return 0.0f;

    float p = 1048576.0f - (float)adc_P;
    p = (p - (v2 / 4096.0f)) * 6250.0f / v1;
    v1 = ((float)bme_calib.dig_P9) * p * p / 2147483648.0f;
    v2 = p * ((float)bme_calib.dig_P8) / 32768.0f;
    return (p + (v1 + v2 + ((float)bme_calib.dig_P7)) / 16.0f) / 100.0f;
}

static void BME280_ReadCalibration(I2C_HandleTypeDef *hi2c) {
    uint8_t b[24];
    HAL_I2C_Mem_Read(hi2c, BME280, 0x88, I2C_MEMADD_SIZE_8BIT, b, 24, 100);
    bme_calib.dig_T1 = (uint16_t)(b[1] << 8 | b[0]);
    bme_calib.dig_T2 = (int16_t)(b[3] << 8 | b[2]);
    bme_calib.dig_T3 = (int16_t)(b[5] << 8 | b[4]);
    bme_calib.dig_P1 = (uint16_t)(b[7] << 8 | b[6]);
    bme_calib.dig_P2 = (int16_t)(b[9] << 8 | b[8]);
    bme_calib.dig_P3 = (int16_t)(b[11] << 8 | b[10]);
    bme_calib.dig_P4 = (int16_t)(b[13] << 8 | b[12]);
    bme_calib.dig_P5 = (int16_t)(b[15] << 8 | b[14]);
    bme_calib.dig_P6 = (int16_t)(b[17] << 8 | b[16]);
    bme_calib.dig_P7 = (int16_t)(b[19] << 8 | b[18]);
    bme_calib.dig_P8 = (int16_t)(b[21] << 8 | b[20]);
    bme_calib.dig_P9 = (int16_t)(b[23] << 8 | b[22]);
}

// --- CALLBACKI DMA I BŁĘDÓW ---
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C1) {
        if (i2c_state == I2C_READING_MPU) {
            int16_t raw_ax = (int16_t)(mpu_dma_raw[0] << 8 | mpu_dma_raw[1]);
            int16_t raw_ay = (int16_t)(mpu_dma_raw[2] << 8 | mpu_dma_raw[3]);
            int16_t raw_az = (int16_t)(mpu_dma_raw[4] << 8 | mpu_dma_raw[5]);

            int16_t raw_gx = (int16_t)(mpu_dma_raw[8] << 8 | mpu_dma_raw[9]);
            int16_t raw_gy = (int16_t)(mpu_dma_raw[10] << 8 | mpu_dma_raw[11]);
            int16_t raw_gz = (int16_t)(mpu_dma_raw[12] << 8 | mpu_dma_raw[13]);

            g_sensors_data.accel_x = ((float)raw_ax / 16384.0f) - accel_bias_x;
            g_sensors_data.accel_y = ((float)raw_ay / 16384.0f) - accel_bias_y;
            g_sensors_data.accel_z = ((float)raw_az / 16384.0f) - accel_bias_z;

            g_sensors_data.gyro_x = ((float)raw_gx / 16.4f) - gyro_bias_x;
            g_sensors_data.gyro_y = ((float)raw_gy / 16.4f) - gyro_bias_y;
            g_sensors_data.gyro_z = ((float)raw_gz / 16.4f) - gyro_bias_z;
        }
        // Obsługa BME280 (Tego brakowało!)
                else if (i2c_state == I2C_READING_BME) {
                    int32_t adc_P = (int32_t)(((uint32_t)bme_dma_raw[0] << 12) | ((uint32_t)bme_dma_raw[1] << 4) | ((uint32_t)bme_dma_raw[2] >> 4));
                    int32_t adc_T = (int32_t)(((uint32_t)bme_dma_raw[3] << 12) | ((uint32_t)bme_dma_raw[4] << 4) | ((uint32_t)bme_dma_raw[5] >> 4));

                    // Zapis do struktury, z której czyta Twoje FCS_APP_Task
                    g_sensors_data.temp_c       = BME280_CalcTemp(adc_T);
                    g_sensors_data.pressure_hpa = BME280_CalcPress(adc_P);
                }

                i2c_state = I2C_IDLE; // Zwolnienie blokady pod kolejny odczyt
            }
	}

// Kluczowa funkcja odblokowująca w razie zakłóceń
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C1) {
        i2c_state = I2C_IDLE; // Zdejmij blokadę programową
    }
}

// --- WYZWALANIE ODCZYTU SENSORÓW ---
uint8_t Sensors_TriggerMPU_DMA(I2C_HandleTypeDef *hi2c) {

	if (HAL_I2C_Mem_Read(hi2c, MPU6050, 0x3B, I2C_MEMADD_SIZE_8BIT, mpu_dma_raw, 14, 11) == HAL_OK) {
		        int16_t raw_ax = (int16_t)(mpu_dma_raw[0] << 8 | mpu_dma_raw[1]);
		        int16_t raw_ay = (int16_t)(mpu_dma_raw[2] << 8 | mpu_dma_raw[3]);
		        int16_t raw_az = (int16_t)(mpu_dma_raw[4] << 8 | mpu_dma_raw[5]);

		        int16_t raw_gx = (int16_t)(mpu_dma_raw[8] << 8 | mpu_dma_raw[9]);
		        int16_t raw_gy = (int16_t)(mpu_dma_raw[10] << 8 | mpu_dma_raw[11]);
		        int16_t raw_gz = (int16_t)(mpu_dma_raw[12] << 8 | mpu_dma_raw[13]);

		        g_sensors_data.accel_x = (float)raw_ax / 16384.0f- accel_bias_x;
		        g_sensors_data.accel_y = (float)raw_ay / 16384.0f- accel_bias_y;
		        g_sensors_data.accel_z = (float)raw_az / 16384.0f- accel_bias_z;

		        g_sensors_data.gyro_x = ((float)raw_gx / 16.4f) - gyro_bias_x;
		        g_sensors_data.gyro_y = ((float)raw_gy / 16.4f) - gyro_bias_y;
		        g_sensors_data.gyro_z = ((float)raw_gz / 16.4f) - gyro_bias_z;
		        return 0;
		    }
				hi2c->Instance->CR1 &= ~I2C_CR1_PE;               // Wyłącz peryferium I2C (resetuje sprzętowe BUSY)
				for (volatile int i = 0; i < 100; i++);
				hi2c->Instance->CR1 |= I2C_CR1_PE;                // Włącz peryferium I2C ponownie
				__HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_BERR | I2C_FLAG_AF | I2C_FLAG_OVR);
				hi2c->State = HAL_I2C_STATE_READY;

		    return 1;
		}

uint8_t Sensors_TriggerBME_DMA(I2C_HandleTypeDef *hi2c) {
	// 1. Odczyt blokujący 6 bajtów od rejestru 0xF7 (Press MSB..XLSB, Temp MSB..XLSB)
	    if (HAL_I2C_Mem_Read(hi2c, BME280, 0xF7, I2C_MEMADD_SIZE_8BIT, bme_dma_raw, 6, 6) == HAL_OK) {

	        int32_t adc_P = (int32_t)(((uint32_t)bme_dma_raw[0] << 12) |
	                                 ((uint32_t)bme_dma_raw[1] << 4)  |
	                                 ((uint32_t)bme_dma_raw[2] >> 4));

	        int32_t adc_T = (int32_t)(((uint32_t)bme_dma_raw[3] << 12) |
	                                 ((uint32_t)bme_dma_raw[4] << 4)  |
	                                 ((uint32_t)bme_dma_raw[5] >> 4));

	        // Kolejność jest kluczowa: CalcTemp MUSI być pierwsze, bo wylicza t_fine dla ciśnienia!
	        g_sensors_data.temp_c       = BME280_CalcTemp(adc_T);
	        g_sensors_data.pressure_hpa = BME280_CalcPress(adc_P);

	        return 0; // Sukces
	    }

	    	hi2c->Instance->CR1 &= ~I2C_CR1_PE;               // Wyłącz peryferium I2C
	        for (volatile int i = 0; i < 100; i++);
	        hi2c->Instance->CR1 |= I2C_CR1_PE;                // Włącz peryferium I2C ponownie
	        __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_BERR | I2C_FLAG_AF | I2C_FLAG_OVR);
	        hi2c->State = HAL_I2C_STATE_READY;
	    return 1; // Błąd komunikacji
	}

// --- INICJALIZACJA ---
uint8_t Sensors_Init(I2C_HandleTypeDef *hi2c) {
    uint8_t check, val;

    // 1. MPU-6050
    HAL_I2C_Mem_Read(hi2c, MPU6050, 0x75, I2C_MEMADD_SIZE_8BIT, &check, 1, 100);
    if (check != 0x68 && check != 0x70) return 1;

    val = 0x00; HAL_I2C_Mem_Write(hi2c, MPU6050, 0x6B, I2C_MEMADD_SIZE_8BIT, &val, 1, 100); // Wybudzenie
    val = 0x00; HAL_I2C_Mem_Write(hi2c, MPU6050, 0x1C, I2C_MEMADD_SIZE_8BIT, &val, 1, 100); // Accel +-2g
    val = 0x18; HAL_I2C_Mem_Write(hi2c, MPU6050, 0x1B, I2C_MEMADD_SIZE_8BIT, &val, 1, 100); // Gyro +-2000 deg/s

    HAL_Delay(50);

    // 2. BME280
    HAL_I2C_Mem_Read(hi2c, BME280, 0xD0, I2C_MEMADD_SIZE_8BIT, &check, 1, 100);
    if (check != 0x58 && check != 0x60) return 2;

    BME280_ReadCalibration(hi2c);
    val = 0x27; HAL_I2C_Mem_Write(hi2c, BME280, 0xF4, I2C_MEMADD_SIZE_8BIT, &val, 1, 100);
    val = 0xA0; HAL_I2C_Mem_Write(hi2c, BME280, 0xF5, I2C_MEMADD_SIZE_8BIT, &val, 1, 100);

    // 3. Kalibracja żyroskopu (odczyt blokujący przed startem DMA i silników)
    float sum_gx = 0.0f, sum_gy = 0.0f, sum_gz = 0.0f;
        float sum_ax = 0.0f, sum_ay = 0.0f, sum_az = 0.0f;
        uint8_t raw[14];

        for (int i = 0; i < 200; i++) {
            HAL_I2C_Mem_Read(hi2c, MPU6050, 0x3B, I2C_MEMADD_SIZE_8BIT, raw, 14, 100);
            sum_ax += (int16_t)(raw[0] << 8 | raw[1]);
            sum_ay += (int16_t)(raw[2] << 8 | raw[3]);
            sum_az += (int16_t)(raw[4] << 8 | raw[5]);
            sum_gx += (int16_t)(raw[8] << 8 | raw[9]);
            sum_gy += (int16_t)(raw[10] << 8 | raw[11]);
            sum_gz += (int16_t)(raw[12] << 8 | raw[13]);
            HAL_Delay(3);
        }
        gyro_bias_x = (sum_gx / 200.0f) / 16.4f;
        gyro_bias_y = (sum_gy / 200.0f) / 16.4f;
        gyro_bias_z = (sum_gz / 200.0f) / 16.4f;

        accel_bias_x = (sum_ax / 200.0f) / 16384.0f;
        accel_bias_y = (sum_ay / 200.0f) / 16384.0f;
        accel_bias_z = ((sum_az / 200.0f) / 16384.0f) + 1.0f;

    Sensors_TriggerMPU_DMA(hi2c);
    Sensors_TriggerBME_DMA(hi2c);
    return 0;
}
