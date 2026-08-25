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

static uint8_t bme_divider = 20;

uint16_t value = 0;			            // throttle value to be sent
uint16_t ctr = 0;						// arming sequence counter
uint8_t trottle_down=0;					// dunnot change trottle up.
uint8_t armed = 0;
uint32_t motor[DSHOT_FRAME_SIZE];		// duty cycles array

static uint16_t motor1[DSHOT_FRAME_SIZE]; // TIM1 - 16BIT
static uint16_t motor2[DSHOT_FRAME_SIZE];
static uint32_t motor3[DSHOT_FRAME_SIZE]; //TIM2 - 32BIT
static uint32_t motor4[DSHOT_FRAME_SIZE];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void dshot_encode_16(uint16_t *motor, uint16_t value);
void dshot_encode_32(uint32_t *motor, uint16_t value);
void send_dshot_motors(uint16_t m1, uint16_t m2, uint16_t m3, uint16_t m4);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// Kodowanie dla TIM2 (32-bit)
void dshot_encode_16(uint16_t *buf, uint16_t val) {
    if (val > 2047) val = 2047;
    uint16_t packet = (val << 1);
    uint16_t csum = 0, csum_data = packet;
    for (int i = 0; i < 3; i++) { csum ^= csum_data; csum_data >>= 4; }
    packet = (packet << 4) | (csum & 0x0F);

    for (int i = 0; i < 16; i++) {
        buf[i] = (packet & 0x8000) ? 200 : 100;
        packet <<= 1;
    }
    for (int i = 16; i < DSHOT_FRAME_SIZE; i++) buf[i] = 0;
}

// Kodowanie dla TIM2 (32-bit)
void dshot_encode_32(uint32_t *buf, uint16_t val) {
    if (val > 2047) val = 2047;
    uint16_t packet = (val << 1);
    uint16_t csum = 0, csum_data = packet;
    for (int i = 0; i < 3; i++) { csum ^= csum_data; csum_data >>= 4; }
    packet = (packet << 4) | (csum & 0x0F);

    for (int i = 0; i < 16; i++) {
        buf[i] = (packet & 0x8000) ? 200 : 100;
        packet <<= 1;
    }
    for (int i = 16; i < DSHOT_FRAME_SIZE; i++) buf[i] = 0;
}

/*void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM6) {

	  flag_process_5ms = 1;
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
          if (value >= TROTTLE_MAX/2) {
            value = TROTTLE_MAX/2;  // devide by 2 for less motor pick for tests
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
      	  	// TIM1
      	  	dshot_encode_16(motor1, value);
      	  	dshot_encode_16(motor2, value);
            // TIM2
            dshot_encode_32(motor3, value);
            dshot_encode_32(motor4, value);
  	}
  }*/
void send_dshot_motors(uint16_t m1, uint16_t m2, uint16_t m3, uint16_t m4) {
    dshot_encode_16(motor1, m1);
    dshot_encode_16(motor2, m2);
    dshot_encode_32(motor3, m3);
    dshot_encode_32(motor4, m4);

    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)motor1, DSHOT_FRAME_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t*)motor2, DSHOT_FRAME_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t*)motor3, DSHOT_FRAME_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, (uint32_t*)motor4, DSHOT_FRAME_SIZE);
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
  MX_TIM6_Init();
  MX_USART2_UART_Init();
  MX_SPI1_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  /*lora_hardware_ok = LoRa_Init();

    // 2. Inicjalizacja i kalibracja czujników I2C
    Sensors_Init(&hi2c1);

    // 3. Inicjalizacja wyjść DShot
    //FCS_APP_Init();

    // 4. Inicjalizacja modelu Simulink / FCS
    FCS_initialize();

    // 5. Sekwencja uzbrajania ESC

    dshot_encode_16(motor1, 0);
    dshot_encode_16(motor2, 0);
    dshot_encode_32(motor3, 0);
    dshot_encode_32(motor4, 0);

        // Start Motor 1 (PA8 - TIM1_CH1)
        HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)motor1, DSHOT_FRAME_SIZE);//1
        // Start Motor 2 (PA11 - TIM1_CH4)
        HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t*)motor2, DSHOT_FRAME_SIZE);//4
        // Start Motor 3 (PA0 - TIM2_CH1)
        HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t*)motor3, DSHOT_FRAME_SIZE);//1
        // Start Motor 4 (PA1 - TIM2_CH2)
        HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, (uint32_t*)motor4, DSHOT_FRAME_SIZE);//2

        __HAL_TIM_MOE_ENABLE(&htim1);

        // Wyłączenie przerwań w kanałach DMA (zapobiega wejściu HAL w błąd TE/ErrorCode=4)
        __HAL_DMA_DISABLE_IT(htim1.hdma[TIM_DMA_ID_CC1], DMA_IT_TC | DMA_IT_HT | DMA_IT_TE);
        __HAL_DMA_DISABLE_IT(htim1.hdma[TIM_DMA_ID_CC4], DMA_IT_TC | DMA_IT_HT | DMA_IT_TE);
        __HAL_DMA_DISABLE_IT(htim2.hdma[TIM_DMA_ID_CC1], DMA_IT_TC | DMA_IT_HT | DMA_IT_TE);
        __HAL_DMA_DISABLE_IT(htim2.hdma[TIM_DMA_ID_CC2], DMA_IT_TC | DMA_IT_HT | DMA_IT_TE);

   HAL_Delay(2000);

    // 6. START TIMERA 200 Hz DOPIERO PO ZAKOŃCZENIU UZBROJENIA
    HAL_TIM_Base_Start_IT(&htim6);
*/
  // 1. Inicjalizacja modułu LoRa
    lora_hardware_ok = LoRa_Init();

    // 2. Inicjalizacja i kalibracja czujników I2C (magistrala w 100% czysta)
    Sensors_Init(&hi2c1);

    // 3. Inicjalizacja modelu Simulink
    FCS_initialize();

/*    // 4. Konfiguracja sprzętowa TIM1 (Main Output Enable dla kanałów komplementarnych/zaawansowanych)
    __HAL_TIM_MOE_ENABLE(&htim1);

    // 5. Wstępne wyczyszczenie buforów DShot (wartość 0)
    dshot_encode_16(motor1, 0);
    dshot_encode_16(motor2, 0);
    dshot_encode_32(motor3, 0);
    dshot_encode_32(motor4, 0);

    // 6. Sekwencja uzbrojenia ESC (wysyłanie zer przez send_dshot_motors)
    for (int i = 0; i < 50; i++) {
        send_dshot_motors(0, 0, 0, 0);
        HAL_Delay(5);
    }*/

    // 7. Start timera głównej pętli 200 Hz (5 ms)
    HAL_TIM_Base_Start_IT(&htim6);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
      {
       /* if (flag_process_5ms)
        {
            flag_process_5ms = 0; // Czyszczenie flagi cyklu 200 Hz
            counter++;

            // 1. Odbiór radiowy LoRa
            if (lora_hardware_ok)
            {
                LoRa_Process(&rx_packet);
            }
*/
            // 2. Odczyt czujników I2C
            MPU6050_Read(&hi2c1, &g_sensors_data);

                    // 3. Wolny odczyt barometru (10 Hz) - co 10 cykli
                    if (++bme_divider >= 20) {
                        bme_divider = 0;
                        BME280_Read(&hi2c1, &g_sensors_data);
                    }
    /*        // 3. NADRZĘDNY KILL SWITCH (Blokada bezpieczeństwa)
                    if (rx_packet.killswitch == 1 || !lora_hardware_ok)
                    {
                        // Twarde odcięcie wyjść do silników
                        send_dshot_motors(0, 0, 0, 0);

                        // Wyzerowanie wyjść modelu FCS
                        rtY.FCSb[0] = 0.0f;
                        rtY.FCSb[1] = 0.0f;
                        rtY.FCSb[2] = 0.0f;
                        rtY.FCSb[3] = 0.0f;

                        // Reset całek i stanów regulatora w locie
                        FCS_initialize();

                        // Sygnalizacja dźwiękowa / LED
                        // FCS_APP_SetBuzzerMode(BUZZER_FAILSAFE);
                    }
                    else
                    {

            // 3. Aktualizacja wejść Simulinka i krok modelu
            FCS_APP_Task();
            FCS_step();

            // 4. FAZA TESTOWA: Rampa gazu na starcie
            if (!armed)
            {
                // Faza 1: Uzbrajanie (wysyłanie zera)
                if (ctr < ESC_POWER_UP)
                {
                    ++ctr;
                    value = 0;
                }
                // Faza 2: Rampa testowa góra / dół
                else
                {
                    ++ctr;
                    if (!trottle_down)
                    {
                        ++value;
                        if (value >= TROTTLE_MAX / 2)
                        {
                            value = TROTTLE_MAX / 2; // Bezpieczny limit 50%
                            trottle_down = 1;
                        }
                    }
                    else
                    {
                        --value;
                        if (value <= TROTTLE_MIN)
                        {
                            value = TROTTLE_MIN;
                            armed = 1; // Koniec rampy -> przejście do sterowania docelowego
                        }
                    }
                }

                // Wystawienie wartości z rampy na wszystkie 4 silniki
                send_dshot_motors(value, value, value, value);
            }
            // 5. FAZA DOCELOWA: Po zakończeniu rampy steruje Simulink / Killswitch
            else
            {
                uint16_t m1_val, m2_val, m3_val, m4_val;

                if (rx_packet.killswitch == 1)
                {
                    // Awaryjne wyłączenie (Failsafe)
                    m1_val = 0;
                    m2_val = 0;
                    m3_val = 0;
                    m4_val = 0;
                    //FCS_APP_SetBuzzerMode(BUZZER_FAILSAFE);
                }
                else
                {
                    // Gaz roboczy z Simulinka (skalowanie z 0.0f..1.0f na DShot 0..2047)
                    m1_val = (uint16_t)(rtY.FCSb[0] * 2047.0f);
                    m2_val = (uint16_t)(rtY.FCSb[1] * 2047.0f);
                    m3_val = (uint16_t)(rtY.FCSb[2] * 2047.0f);
                    m4_val = (uint16_t)(rtY.FCSb[3] * 2047.0f);
                    // FCS_APP_SetBuzzerMode(BUZZER_ARMED);
                }

                send_dshot_motors(m1_val, m2_val, m3_val, m4_val);
            }

            // 6. Obsługa buzzera
            //FCS_APP_BuzzerUpdate();
        }
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

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        flag_process_5ms = 1;
    }
}

/*void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
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
