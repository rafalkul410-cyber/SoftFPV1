/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "FCS.h"
#include <string.h>
#include "lora.h"
#include "sensors.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

volatile uint8_t flag_process_5ms = 0;
volatile uint8_t flaga = 0;
volatile uint32_t counter = 0;


//volatile uint8_t lora_frame_ready = 0;
//LoRa_ControlPacket_t lora_packet;
//uint8_t lora_hardware_ok = 0;  // Będzie 1, jeśli SPI widzi moduł
//uint32_t packet_count = 0;     // Licznik odebranych ramek
//uint8_t raw_data[64] = {0};    // Tutaj wpadną surowe bajty z ESP
//uint8_t raw_len = 0;           // Długość odebranych bajtów

volatile uint8_t lora_frame_ready = 0;
volatile uint8_t lora_hardware_ok = 0;


// Zmienna przechowywująca zdekodowane dane z joysticka
LoRa_ControlPacket_t rx_packet;
Sensors_Data_t sensor_data;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_TIM6_Init();
  MX_USART2_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start_IT(&htim6);  // 2. Start Timera 6 w trybie przerwań (co 5 ms)
  FCS_initialize();

 // LORA_CS_HIGH();
    lora_hardware_ok = LoRa_Init();
    // Inicjalizacja I2C, wybudzenie MPU-6050, BME280 oraz autokalibracja żyroskopu (200 próbek)
      if (Sensors_Init(&hi2c1) != 0) {
          // Jeśli któryś czujnik nie odpowie na magistrali I2C -> zatrzymaj mikroprocesor
          Error_Handler();
      }


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

    while (1)
	{
	        // Pętla wykonuje się deterministycznie co 5 ms (200 Hz)
	        if (flag_process_5ms)
	        {
	            flag_process_5ms = 0; // Czyszczenie flagi timera
	            counter++;
	            flaga = 1;            // Sygnalizacja rozpoczęcia obliczeń w cyklu 5 ms

	            // 1. ODBIÓR LORA (tylko gdy moduł działa I pin DIO0 zgłosił nową ramkę)
	            if(lora_hardware_ok)
	            {
	                lora_frame_ready = 0; // Czyszczenie flagi przerwania EXTI

	                if (LoRa_Process(&rx_packet))
	                {
	                //obsługa odebranej ramki
	                }
	            }
	            //Odczyt I2C + uaktualnienie struktur w pamięci
	            Sensors_Read(&hi2c1, &sensor_data);


	            // 2. KROK MODELU STEROWANIA MATLAB / SIMULINK
	            // FCS_step();

	            flaga = 0; // Koniec obliczeń w cyklu 5 ms
	        }
	    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        flag_process_5ms = 1; // Wystawienie flagi dla pętli głównej
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)  //DID0 od LoRa
{
    if (GPIO_Pin == GPIO_PIN_12)
    {
        lora_frame_ready = 1;
    }

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }

  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
