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
#include "vbat.h"
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
volatile uint32_t counter = 0;
volatile uint8_t lora_frame_ready = 0;
volatile uint8_t lora_hardware_ok = 0;
volatile uint32_t diag_i2c_error = 0;
volatile uint8_t diag_init_result = 0;
volatile uint8_t diag_scanner_found[5] = {0};
volatile uint8_t diag_scanner_count = 0;
LoRa_ControlPacket_t rx_packet;
uint16_t value = 0;			            // throttle value to be sent
uint16_t ctr = 0;						// arming sequence counter
uint8_t trottle_down=0;					// dunnot change trottle up.
uint8_t armed = 0;
uint32_t motor[DSHOT_FRAME_SIZE];		// duty cycles array
static uint8_t bme_divider = 20;
static uint16_t motor1[DSHOT_FRAME_SIZE]; // TIM1 - 16BIT
static uint16_t motor2[DSHOT_FRAME_SIZE];
static uint32_t motor3[DSHOT_FRAME_SIZE]; //TIM2 - 32BIT
static uint32_t motor4[DSHOT_FRAME_SIZE];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void dshot_encode_16(uint16_t *buf, uint16_t val);
void dshot_encode_32(uint32_t *buf, uint16_t val);
void send_dshot_motors(uint16_t m1, uint16_t m2, uint16_t m3, uint16_t m4);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/*static uint16_t dshot_prepare_packet(uint16_t value) {
    uint16_t packet = (value << 5); // telemetria = 0
    uint16_t csum = 0;
    uint16_t csum_data = packet;
    for (int i = 0; i < 3; i++) {
        csum ^= csum_data;
        csum_data >>= 4;
    }
    csum &= 0x0F;
    return (packet | csum);
}*/
static uint16_t dshot_prepare_packet(uint16_t value) {
    // 1. Zabezpieczenie zakresu DShot (0..2047)
    if (value > 2047) {
        value = 2047;
    }

    // 2. Przygotuj 12 bitów danych: 11 bitów wartości + 1 bit telemetrii (0)
    uint16_t packet = (value << 1);

    // 3. Oblicz CRC: XOR trzech 4-bitowych bloków (nibbli)
    uint16_t csum = (packet ^ (packet >> 4) ^ (packet >> 8)) & 0x0F;

    // 4. Przesuń dane na bity 15..4 i wstaw sumę kontrolną na bity 3..0
    return (packet << 4) | csum;
}
// Wypełnianie bufora 16-bitowego (dla TIM1)
static void dshot_fill_buffer_16(uint16_t *buf, uint16_t packet) {
    for (int i = 0; i < 16; i++) {
        buf[i] = (packet & (0x8000 >> i)) ? DSHOT_BIT_1 : DSHOT_BIT_0;
    }
    for (int i = 16; i < DSHOT_FRAME_SIZE; i++) {
            buf[i] = 0;
        }
}

// Wypełnianie bufora 32-bitowego (dla TIM2)
static void dshot_fill_buffer_32(uint32_t *buf, uint16_t packet) {
    for (int i = 0; i < 16; i++) {
        buf[i] = (packet & (0x8000 >> i)) ? DSHOT_BIT_1 : DSHOT_BIT_0;
    }
    for (int i = 16; i < DSHOT_FRAME_SIZE; i++) {
            buf[i] = 0;
        }
}

volatile uint16_t dbg_dshot_m1 = 0;
volatile uint16_t dbg_dshot_m2 = 0;
volatile uint16_t dbg_dshot_m3 = 0;
volatile uint16_t dbg_dshot_m4 = 0;


// Wysyłka ramek przez DMA
void dshot_write(uint16_t m1, uint16_t m2, uint16_t m3, uint16_t m4) {
		dbg_dshot_m1 = m1;
	    dbg_dshot_m2 = m2;
	    dbg_dshot_m3 = m3;
	    dbg_dshot_m4 = m4;

    dshot_fill_buffer_16(motor1, dshot_prepare_packet(m1));
    dshot_fill_buffer_16(motor2, dshot_prepare_packet(m2));
    dshot_fill_buffer_32(motor3, dshot_prepare_packet(m3));
    dshot_fill_buffer_32(motor4, dshot_prepare_packet(m4));

    // Motor 1 & 2 -> TIM1
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)motor1, DSHOT_FRAME_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_4, (uint32_t*)motor2, DSHOT_FRAME_SIZE);
    // Motor 3 & 4 -> TIM2
    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t*)motor3, DSHOT_FRAME_SIZE);
    HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, (uint32_t*)motor4, DSHOT_FRAME_SIZE);
}

// Inicjalizacja i uzbrojenie ESC (Bluejay wymaga serii zer)
void dshot_init(void) {
	__HAL_TIM_MOE_ENABLE(&htim1);

	for (int i = 0; i < 1500; i++) {
        dshot_write(0, 0, 0, 0);
        HAL_Delay(2); // Ramki zerowe wysyłane co 1 ms przez 1 sekundę
    }
}
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
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM6_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  //VBAT_Init(&hadc1);

  if (Sensors_Init(&hi2c1) != 0) {
        // Błąd komunikacji z czujnikami (opcjonalnie: dioda LED / pętla błędu)
    }
    // 2. Inicjalizacja modułu radiowego LoRa SX1278 po SPI
  if (LoRa_Init() == 1) {
        lora_hardware_ok = 1;
    } else {
        lora_hardware_ok = 0; // W razie błędu SPI dron pozostanie w bezpiecznym FAILSAFE
    }
  dshot_init();

  HAL_TIM_Base_Start_IT(&htim6);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
            if (lora_hardware_ok)
            {
                LoRa_Process(&rx_packet);
            }
            //Pętla dynamiki i sterowania (200 Hz / 5 ms)
            if (flag_process_5ms)
            {
            	flag_process_5ms = 0;
            	Sensors_TriggerMPU_DMA(&hi2c1);
            	    if (++bme_divider >= 20)
            	    {
            	        bme_divider = 0;
            	        Sensors_TriggerBME_DMA(&hi2c1);
            	        //VBAT_Update(&hadc1);
            	    }

            	    //dshot_write(100, 100, 100, 100);
            	    FCS_APP_Task();
            	     App_StateMachine();
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
        // uint8_t tick_count = 0;

        // if (++tick_count >= 3)
        //{
        //  tick_count = 0;
            flag_process_5ms = 1;
        //}
    }
}
/*void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
    UNUSED(htim);
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
