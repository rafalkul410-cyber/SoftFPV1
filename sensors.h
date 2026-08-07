#ifndef SENSORS_H_
#define SENSORS_H

#include "main.h"

#define MPU6050 (0x68<<1)
#define BME280 (0x76<<1)

typedef struct{
	float accel_x;
	float accel_y;
	float accel_z;
	float gyro_x;
	float gyro_y;
	float gyro_z;
	float pressure_hpa;
	float temp_c;
}Sensors_Data_t;

uint8_t Sensors_Init(I2C_HandleTypeDef *hi2c);
uint8_t Sensors_Read(I2C_HandleTypeDef *hi2c, Sensors_Data_t *data);

#endif
