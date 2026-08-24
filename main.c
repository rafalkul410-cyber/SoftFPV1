/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
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
#include "fcs_app.h"
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
volatile uint8_t dbg_rx_frame[16] = {0};
volatile uint8_t dbg_raw_len = 0;
volatile uint8_t dbg_pkt_crc = 0;
volatile uint8_t dbg_calc_crc = 0;

volatile uint8_t flag_process_5ms = 0;
//volatile uint8_t flaga1 = 0;
volatile uint32_t counter = 0;

volatile uint8_t lora_frame_ready = 0;
volatile uint8_t lora_hardware_ok = 0;

volatile uint32_t diag_i2c_error = 0;
volatile uint8_t diag_init_result = 0;
volatile uint8_t diag_scanner_found[5] = {0};
volatile uint8_t diag_scanner_count = 0;



// Struktury danych
LoRa_ControlPacket_t rx_packet;
Sensors_Data_t g_sensor_data;


//////////////////// DSHOT GIT////////////
uint16_t value = 0;			// throttle value to be sent
uint16_t ctr = 0;						// arming sequence counter
uint8_t trottle_down=0;					// dunnot change trottle up.
uint8_t armed = 0;
uint32_t motor[DSHOT_FRAME_SIZE];		// duty cycles array

static uint32_t motor1[DSHOT_FRAME_SIZE];
static uint32_t motor2[DSHOT_FRAME_SIZE];
static uint32_t motor3[DSHOT_FRAME_SIZE];
static uint32_t motor4[DSHOT_FRAME_SIZE];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void dshot600(uint32_t *motor, uint16_t value);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void dshot600(uint32_t *motor, uint16_t value)
{
    if (value > 2047) value = 2047;

    uint16_t packet = (value << 1);

    // DShot CRC
    uint16_t csum = 0;
    uint16_t csum_data = packet;
    for (int i = 0; i < 3; i++) {
        csum ^= csum_data;
        csum_data >>= 4;
    }
    csum &= 0x0F;
    packet = (packet << 4) | csum;

    // Kodowanie 16 bitów
    for (int i = 0; i < 16; i++) {
    	motor[i] = (packet & 0x8000) ? 200 : 100;
        packet <<= 1;
    }

    // Pozostałe słowa jako stan niski (wymagany reset linii > 20 us)
    for (int i = 16; i < DSHOT_FRAME_SIZE; i++) {
        motor[i] = 0;
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM6) {

      // 1. Faza uzbrajania (wysyłanie zera)
      if (ctr < ESC_POWER_UP) {
        ++ctr;
        value = 0;
      }
      // 2. Faza po uzbrojeniu (stały gaz roboczy)
      else if (armed) {
        value = 350;
      }
      // 3. Faza rampy testowej (jeśli jeszcze nie uzbrojony)
      else {
        ++ctr;
        if (!trottle_down) {
          ++value;
          if (value >= TROTTLE_MAX) {
            value = TROTTLE_MAX;
            trottle_down = 1;
          }
        } else {
          --value;
          if (value <= TROTTLE_MIN) {
            value = TROTTLE_MIN;
            armed = 1; // Koniec rampy, przechodzimy do armed
          }
        }
      }

      // Pojedyncze wysłanie wyliczonej wartości na koniec każdego cyklu
      dshot600(motor1, value);
      dshot600(motor2, value);
      dshot600(motor3, value);
      dshot600(motor4, value);
  }

/*void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM6) {

	  // KROK 1: Przez pierwsze 3 sekundy trzymamy MAX
	        if (ctr < 3600) {
	        	++ctr;
	          value = 2047; // ESC gra 4 tony (zapisuje MAX)
	        }
	        // KROK 2: Przez kolejne 3 sekundy trzymamy MIN (0)
	        else if (ctr < 7200) {
	        	++ctr;
	          value = 0;    // ESC zatwierdza dół i uzbraja się (2 tony)
	        }
	        // KROK 3: Po udanej kalibracji podajemy gaz roboczy
	        else {
	          value = 250;  // Silnik zaczyna się kręcić
	        }

      dshot600(motor1, value);
      dshot600(motor2, value);
      dshot600(motor3, value);
      dshot600(motor4, value);

  }
}*/

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
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  lora_hardware_ok = LoRa_Init();

    // 2. Inicjalizacja i kalibracja czujników I2C
    Sensors_Init(&hi2c1);

    // 3. Inicjalizacja wyjść DShot
    FCS_APP_Init();

    // 4. Inicjalizacja modelu Simulink / FCS
    FCS_initialize();

    // 5. Sekwencja uzbrajania ESC (wysyłanie zera przez 1,5 sekundy przed startem pętli)
    for (int i = 0; i < 300; i++) {
        rtY.FCSb[0] = 0.0f;
        rtY.FCSb[1] = 0.0f;
        rtY.FCSb[2] = 0.0f;
        rtY.FCSb[3] = 0.0f;
        FCS_APP_SetMotors();
        HAL_Delay(5);
    }

    dshot600(motor1, 0);
    dshot600(motor2, 0);
    dshot600(motor3, 0);
    dshot600(motor4, 0);

    __HAL_TIM_MOE_ENABLE(&htim1);

    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, motor1, DSHOT_FRAME_SIZE);
      HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, motor2, DSHOT_FRAME_SIZE);
      HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, motor3, DSHOT_FRAME_SIZE);
      HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, motor4, DSHOT_FRAME_SIZE);

      HAL_Delay(2000);

    // 6. START TIMERA 200 Hz DOPIERO PO ZAKOŃCZENIU UZBROJENIA
    HAL_TIM_Base_Start_IT(&htim6);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      /*  if (flag_process_5ms)
        {
            flag_process_5ms = 0; // Czyszczenie flagi cyklu 5 ms (200 Hz)
            counter++;

            // 1. Odbiór radiowy LoRa
            if (lora_hardware_ok)
            {
                LoRa_Process(&rx_packet);
            }

            // 2. Odczyt czujników (odkomentuj, gdy podłączysz I2C)
            // Sensors_Read(&hi2c1, &g_sensor_data);

            // 3. Aktualizacja wejść Simulinka z sensorów i radia
            FCS_APP_Task();

            // 4. Logika bezpieczeństwa i zadawanie mocy
            if (rx_packet.killswitch == 1)
            {
                // Silniki wyłączone (Disarmed)
                rtY.FCSb[0] = 0.0f;
                rtY.FCSb[1] = 0.0f;
                rtY.FCSb[2] = 0.0f;
                rtY.FCSb[3] = 0.0f;
                FCS_APP_SetBuzzerMode(BUZZER_FAILSAFE);
            }
            else
            {
                // FCS_step(); // Docelowy krok modelu Simulinka

                // TESTOWY GAZ: Wartość od 0.0f do 1.0f (0.05f to bezpieczne 5% obrotów biegu jałowego)
                rtY.FCSb[0] = 0.05f;
                rtY.FCSb[1] = 0.05f;
                rtY.FCSb[2] = 0.05f;
                rtY.FCSb[3] = 0.05f;
                FCS_APP_SetBuzzerMode(BUZZER_ARMED);
            }

            // 5. Wystawienie ramek DShot do ESC
            FCS_APP_SetMotors();

            // 6. Obsługa buzzera
            FCS_APP_BuzzerUpdate();
        }*/
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/*void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        flag_process_5ms = 1;
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_12)
    {
        lora_frame_ready = 1;
    }*/

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
