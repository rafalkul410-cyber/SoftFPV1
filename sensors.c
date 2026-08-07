#include "sensors.h"

typedef struct{   // pomocnicze zmienne kalibracyjne do czujników
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;
}BME280_Calib_t;

//zmienne kalibracyjne
static float gyro_bias_x=0.0f;
static float gyro_bias_y=0.0f;
static float gyro_bias_z=0.0f;

static BME280_Calib_t bme_calib;
static float t_fine_temp;

static void BME280_ReadCalibration(I2C_HandleTypeDef *hi2c){
	uint8_t b[24];

	HAL_I2C_Mem_Read(hi2c, BME280, 0x88, I2C_MEMADD_SIZE_8BIT, b, 24,100);
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

static float BME280_CalcTemp(int32_t adc_T){
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

uint8_t Sensors_Init(I2C_HandleTypeDef *hi2c){
	uint8_t check ,val;

	// 1. Inicjalizacja MPU-6050
	HAL_I2C_Mem_Read(hi2c, MPU6050, 0x75, I2C_MEMADD_SIZE_8BIT, &check, 1, 100);
	if(check!=0x68) return 1; // blad - brak mpu

		val = 0x00; HAL_I2C_Mem_Write(hi2c, MPU6050, 0x6B, I2C_MEMADD_SIZE_8BIT, &val, 1, 100); // Wybudzenie
	    val = 0x00; HAL_I2C_Mem_Write(hi2c, MPU6050, 0x1C, I2C_MEMADD_SIZE_8BIT, &val, 1, 100); // Accel +-2g
	    val = 0x18; HAL_I2C_Mem_Write(hi2c, MPU6050, 0x1B, I2C_MEMADD_SIZE_8BIT, &val, 1, 100); // Gyro +-2000 deg/s

	// 2. Inicjalizacja BME280
	    HAL_I2C_Mem_Read(hi2c, BME280, 0xD0, I2C_MEMADD_SIZE_8BIT, &check, 1, 100);
	        if (check != 0x60) return 2; // Błąd - brak BME

	        BME280_ReadCalibration(hi2c); // Pobranie stałych z EEPROM
	        val = 0x27; HAL_I2C_Mem_Write(hi2c, BME280, 0xF4, I2C_MEMADD_SIZE_8BIT, &val, 1, 100); // Normal mode
	        val = 0xA0; HAL_I2C_Mem_Write(hi2c, BME280, 0xF5, I2C_MEMADD_SIZE_8BIT, &val, 1, 100); // Filter x16

//Autokalibracja żyroskopu przy starcie
	        float sum_gx = 0.0f;
	        float sum_gy=0.0f;
	        float sum_gz=0.0f;
	        Sensors_Data_t temp_data;

	        for(int i=0;i<200;i++){
	        	 Sensors_Read(hi2c, &temp_data);
	        	 sum_gx+=temp_data.gyro_x;
	        	 sum_gy+=temp_data.gyro_y;
	        	 sum_gz+=temp_data.gyro_z;
	        	 HAL_Delay(2);
	        }
	        gyro_bias_x=sum_gx/200.0f;
	        gyro_bias_x=sum_gx/200.0f;
	        gyro_bias_x=sum_gx/200.0f;

	    return 0; // sukces
}

uint8_t Sensors_Read(I2C_HandleTypeDef *hi2c, Sensors_Data_t *data){
	uint8_t mpu_raw[14];
	uint8_t bme_raw[6];

	// --- ODCZYT MPU-6050 ---
	if (HAL_I2C_Mem_Read(hi2c, MPU6050, 0x3B, I2C_MEMADD_SIZE_8BIT, mpu_raw, 14, 100) != HAL_OK) {
	        return 1;
	    }
	int16_t raw_ax=(int16_t)(mpu_raw[0]<<8 | mpu_raw[1]);
	int16_t raw_ay=(int16_t)(mpu_raw[2]<<8 | mpu_raw[3]);
	int16_t raw_az=(int16_t)(mpu_raw[4]<<8 | mpu_raw[5]);

	int16_t raw_gx=(int16_t)(mpu_raw[8]<<8 | mpu_raw[9]);
	int16_t raw_gy=(int16_t)(mpu_raw[10]<<8 | mpu_raw[11]);
	int16_t raw_gz=(int16_t)(mpu_raw[12]<<8 | mpu_raw[13]);

	data->accel_x=(float)raw_ax / 16384.0f;
	data->accel_y=(float)raw_ay / 16384.0f;
	data->accel_z=(float)raw_az / 16384.0f;

	data->gyro_x=((float)raw_gx/16.4f) - gyro_bias_x; //skalibrowane dane czujnika gyro
	data->gyro_y=((float)raw_gy/16.4f) - gyro_bias_y;
	data->gyro_z=((float)raw_gz/16.4f) - gyro_bias_z;

	// --- ODCZYT BME280 ---
	if(HAL_I2C_Mem_Read(hi2c, BME280, 0xF7, I2C_MEMADD_SIZE_8BIT, bme_raw, 6, 100) != HAL_OK) {
        return 2;
    }

    int32_t adc_P = (int32_t)(((uint32_t)bme_raw[0] << 12) | ((uint32_t)bme_raw[1] << 4) | ((uint32_t)bme_raw[2] >> 4));
    int32_t adc_T = (int32_t)(((uint32_t)bme_raw[3] << 12) | ((uint32_t)bme_raw[4] << 4) | ((uint32_t)bme_raw[5] >> 4));

    data->temp_c       = BME280_CalcTemp(adc_T);
    data->pressure_hpa = BME280_CalcPress(adc_P);

    return 0;

}


