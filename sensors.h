
#ifndef SENSORS_H_
#define SENSORS_H_

#include "main.h"


#define MPU6050 (0x68 << 1)
#define BME280  (0x76 << 1)

typedef struct Sensors_Data_s {
    float accel_x;
    float accel_y;
    float accel_z;
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float pressure_hpa;
    float temp_c;
} Sensors_Data_t;

extern Sensors_Data_t g_sensors_data;

uint8_t Sensors_Init(I2C_HandleTypeDef *hi2c);
uint8_t Sensors_TriggerMPU_DMA(I2C_HandleTypeDef *hi2c);
uint8_t Sensors_TriggerBME_DMA(I2C_HandleTypeDef *hi2c);

#endif
