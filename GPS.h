#ifndef GPS_H_
#define GPS_H_

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

#define GPS_DMA_BUF_SIZE 1024

typedef struct {
	double latitude;       // Szerokość geograficzna [deg] (np. 50.0614)
	double longitude;      // Długość geograficzna [deg] (np. 19.9365)
    float speed_kmh;      // Prędkość względem ziemi [km/h]
    float course_deg;     // Kąt kursu / wektor drogi [deg]
    float altitude_m;     // Wysokość n.p.m. [m]
    uint8_t satellites;   // Liczba śledzonych satelitów
    uint8_t fix_valid;    // 1 = Fix poprawny (A), 0 = brak Fixa (V)
    uint32_t last_fix_ms; // Znacznik czasu HAL_GetTick ostatniej poprawnej ramki
    //dane przeliczeniowe
	float pos_north_m;    // X w metrach (North)
    float pos_east_m;     // Y w metrach (East)
    uint8_t home_set;     // Flaga ustalenia punktu początkowego (0, 0)
} GPS_Data_t;


	#define DEG_TO_RAD (3.141592653589793f / 180.0f)
	#define METERS_PER_DEG_LAT 111139.0f


extern GPS_Data_t g_gps_data;

// Inicjalizacja nasłuchu UART w trybie DMA z detekcją IDLE
void GPS_Init(UART_HandleTypeDef *huart);

// Callback wywoływany z HAL_UARTEx_RxEventCallback
void GPS_RxEvent_Callback(UART_HandleTypeDef *huart, uint16_t size);

// Przetwarzanie odebranych danych (wywoływane w pętli głównej)
void GPS_Process(void);

#endif /* GPS_H_ */
