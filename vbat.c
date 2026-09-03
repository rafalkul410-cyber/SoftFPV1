#include "vbat.h"

volatile float g_vbat_voltage = 0.0f;
volatile uint32_t test_raw_adc = 0;

void VBAT_Init(ADC_HandleTypeDef *hadc)
{
    // 1. Wymagana w STM32L4 sprzętowa kalibracja przed startem pomiarów
    HAL_ADCEx_Calibration_Start(hadc, ADC_SINGLE_ENDED);

    // 2. Pierwszy odczyt rozruchowy, aby filtr nie startował od 0.0V
    uint32_t raw_adc = 0;
    HAL_ADC_Start(hadc);
    if (HAL_ADC_PollForConversion(hadc, 2) == HAL_OK)
    {
        raw_adc = HAL_ADC_GetValue(hadc);
    }
    HAL_ADC_Stop(hadc);

    float pin_voltage = ((float)raw_adc * VBAT_ADC_VREF) / 4095.0f;
    g_vbat_voltage = pin_voltage * VBAT_DIVIDER_RATIO;
}

float VBAT_Update(ADC_HandleTypeDef *hadc)
{
    uint32_t raw_adc = 0;

    // 1. Start konwersji ADC
    HAL_ADC_Start(hadc);

    // 2. Odczyt wyniku
    if (HAL_ADC_PollForConversion(hadc, 1) == HAL_OK)
    {
        raw_adc = HAL_ADC_GetValue(hadc);
        test_raw_adc = raw_adc; // <--- Zapisujemy surowe bity PRZED obliczeniami!
    }
    HAL_ADC_Stop(hadc);

    // 3. Przeliczenie bitów na napięcie na pinie PA6
    float pin_voltage = ((float)raw_adc * VBAT_ADC_VREF) / 4095.0f;

    // 4. Rzeczywiste napięcie baterii
    float raw_vbat = pin_voltage * VBAT_DIVIDER_RATIO;

    // 5. Filtr EMA
    g_vbat_voltage = ((1.0f - VBAT_FILTER_ALPHA) * g_vbat_voltage) + (VBAT_FILTER_ALPHA * raw_vbat);

    // 6. Return MUSI być na samym końcu funkcji!
    return g_vbat_voltage;
}

float VBAT_GetVoltage(void)
{
    return g_vbat_voltage;
}
