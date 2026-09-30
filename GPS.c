#include "GPS.h"
#include <string.h>
#include <stdlib.h>

GPS_Data_t g_gps_data = {0};

static UART_HandleTypeDef *gps_uart;
static uint8_t gps_dma_rx[GPS_DMA_BUF_SIZE];
static uint8_t gps_proc_buf[GPS_DMA_BUF_SIZE];
static volatile uint16_t gps_rx_len = 0;
static volatile uint8_t gps_frame_ready = 0;

// Konwersja formatu NMEA (ddmm.mmmm) na stopnie dziesiętne
static float NMEA_To_Degrees(const char *nmea_coord, char direction) {
    if (!nmea_coord || strlen(nmea_coord) < 4) return 0.0f;

    float raw = strtof(nmea_coord, NULL);
    int degrees = (int)(raw / 100.0f);
    float minutes = raw - (float)(degrees * 100);
    float dec_degrees = (float)degrees + (minutes / 60.0f);

    if (direction == 'S' || direction == 'W') {
        dec_degrees = -dec_degrees;
    }
    return dec_degrees;
}

// Rozbicie i parsowanie ramki NMEA
static void GPS_Parse_NMEA(char *sentence) {
    // Sprawdzamy czy to ramka RMC ($GNRMC lub $GPRMC)
    if (strstr(sentence, "RMC") != NULL) {
        char *token;
        char *rest = sentence;
        uint8_t field_idx = 0;

        char status = 'V';
        char lat_str[16] = {0};
        char lat_dir = 'N';
        char lon_str[16] = {0};
        char lon_dir = 'E';
        char speed_str[16] = {0};
        char course_str[16] = {0};

        while ((token = strtok_r(rest, ",", &rest)) != NULL) {
            switch (field_idx) {
                case 2: status = token[0]; break;                      // Status: A = OK, V = Warning
                case 3: strncpy(lat_str, token, sizeof(lat_str)-1); break;
                case 4: lat_dir = token[0]; break;
                case 5: strncpy(lon_str, token, sizeof(lon_str)-1); break;
                case 6: lon_dir = token[0]; break;
                case 7: strncpy(speed_str, token, sizeof(speed_str)-1); break; // Prędkość w węzłach
                case 8: strncpy(course_str, token, sizeof(course_str)-1); break;
                default: break;
            }
            field_idx++;
        }

        if (status == 'A') {
            g_gps_data.fix_valid = 1;
            g_gps_data.latitude = NMEA_To_Degrees(lat_str, lat_dir);
            g_gps_data.longitude = NMEA_To_Degrees(lon_str, lon_dir);
            g_gps_data.speed_kmh = strtof(speed_str, NULL) * 1.852f; // węzły na km/h
            g_gps_data.course_deg = strtof(course_str, NULL);
            g_gps_data.last_fix_ms = HAL_GetTick();
        } else {
            g_gps_data.fix_valid = 0;
        }
    }
    // Opcjonalnie ramka GGA dla wysokości i liczby satelitów ($GNGGA)
    else if (strstr(sentence, "GGA") != NULL) {
        char *token;
        char *rest = sentence;
        uint8_t field_idx = 0;

        while ((token = strtok_r(rest, ",", &rest)) != NULL) {
            if (field_idx == 7) {
                g_gps_data.satellites = (uint8_t)atoi(token);
            } else if (field_idx == 9) {
                g_gps_data.altitude_m = strtof(token, NULL);
            }
            field_idx++;
        }
    }
}

void GPS_Init(UART_HandleTypeDef *huart) {
/*    gps_uart = huart;

    HAL_UARTEx_ReceiveToIdle_DMA(gps_uart, gps_dma_rx, GPS_DMA_BUF_SIZE);
    __HAL_DMA_DISABLE_IT(gps_uart->hdmarx, DMA_IT_HT);*/
	    gps_uart = huart;

	    // 1. Wyczyszczenie wszystkich flag błędów sprzętowych UART
	    __HAL_UART_CLEAR_OREFLAG(gps_uart);
	    __HAL_UART_CLEAR_NEFLAG(gps_uart);
	    __HAL_UART_CLEAR_FEFLAG(gps_uart);
	    __HAL_UART_CLEAR_PEFLAG(gps_uart);

	    // 2. Twardy reset stanu błędu i odblokowanie RxState
	    gps_uart->ErrorCode = HAL_UART_ERROR_NONE;
	    gps_uart->RxState = HAL_UART_STATE_READY;
	    gps_uart->gState = HAL_UART_STATE_READY;

	    // 3. Zatrzymanie ewentualnego wiszącego transferu DMA
	    if (gps_uart->hdmarx != NULL) {
	        HAL_DMA_Abort(gps_uart->hdmarx);
	    }

	    // 4. Uruchomienie odbioru DMA
	    HAL_UARTEx_ReceiveToIdle_DMA(gps_uart, gps_dma_rx, GPS_DMA_BUF_SIZE);

	    // 5. Wyłączenie przerwania Half-Transfer tylko wtedy, gdy DMA wystartowało
	    if (gps_uart->hdmarx != NULL) {
	        __HAL_DMA_DISABLE_IT(gps_uart->hdmarx, DMA_IT_HT);
	    }

	}

void GPS_RxEvent_Callback(UART_HandleTypeDef *huart, uint16_t size) {
    if (huart->Instance == gps_uart->Instance) {
        memcpy(gps_proc_buf, gps_dma_rx, size);
        gps_proc_buf[size] = '\0';
        gps_rx_len = size;
        gps_frame_ready = 1;



        // Reset wskaźnika DMA i ponowny start odbioru od indeksu 0
        HAL_UARTEx_ReceiveToIdle_DMA(gps_uart, gps_dma_rx, GPS_DMA_BUF_SIZE);
        __HAL_DMA_DISABLE_IT(gps_uart->hdmarx, DMA_IT_HT);
    }
}

void GPS_Process(void) {
    if (!gps_frame_ready) return;

    gps_frame_ready = 0;

    // Linia po linii wyodrębniamy poszczególne zdania NMEA
    char *saveptr;
    char *line = strtok_r((char*)gps_proc_buf, "\r\n", &saveptr);
    while (line != NULL) {
        if (line[0] == '$') {
            GPS_Parse_NMEA(line);
        }
        line = strtok_r(NULL, "\r\n", &saveptr);
    }
}
