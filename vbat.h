#ifndef INC_VBAT_H_
#define INC_VBAT_H_

#include "main.h"
#include "adc.h"



/* ====================================================================
 * PARAMETRY SPRZĘTOWE DZIELNIKA
 * ==================================================================== */
// R1 = 100k, R2 = 10k -> (100k + 10k) / 10k = 11.0
#define VBAT_DIVIDER_RATIO      11.0f

// Napięcie referencyjne zasilania mikrokontrolera (VREF+ / 3.3V z płytki Nucleo)
#define VBAT_ADC_VREF           3.30f

// Współczynnik filtru dolnoprzepustowego EMA (0.0f - 1.0f)
// 0.10f oznacza: 90% historii + 10% nowej próbki (stabilny odczyt odporny na szumy ESC)
#define VBAT_FILTER_ALPHA       0.10f

/* ====================================================================
 * ZMIENNE GLOBALNE I PROTOTYPY FUNKCJI
 * ==================================================================== */
extern volatile float g_vbat_voltage; // Aktualne przefiltrowane napięcie w Voltach

/**
 * @brief Inicjalizacja i sprzętowa kalibracja przetwornika ADC pod pomiar baterii.
 * @param hadc Wskaźnik do struktury przetwornika (np. &hadc1)
 */
void VBAT_Init(ADC_HandleTypeDef *hadc);

/**
 * @brief Wykonuje pojedynczą konwersję ADC i aktualizuje przefiltrowane napięcie.
 *        Wywoływać okresowo (np. 10 Hz / co 100 ms).
 * @param hadc Wskaźnik do struktury przetwornika (np. &hadc1)
 * @return float Zwraca aktualne napięcie pakietu w Voltach
 */
float VBAT_Update(ADC_HandleTypeDef *hadc);

/**
 * @brief Zwraca ostatnio zmierzone napięcie bez ponownego wyzwalania ADC.
 */
float VBAT_GetVoltage(void);

#endif /* INC_VBAT_H_ */
