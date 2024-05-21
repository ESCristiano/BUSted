/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "icache.h"
#include "usart.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stdlib.h"

int __io_putchar(int ch)
{
 uint8_t c[1];
 c[0] = ch & 0x00FF;
 HAL_UART_Transmit(&hlpuart1, &*c, 1, 1000);
 return ch;
}

int _write(int file,char *ptr, int len)
{
 int DataIdx;
 for(DataIdx= 0; DataIdx< len; DataIdx++)
 {
 __io_putchar(*ptr++);
 }
return len;
}
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//******************************************************************************
//DMA Covert-Channel
//******************************************************************************
#define SETUP_CONTENTION_SRAM1()do { \
    __asm("ldr r0, =0x20018000"); \
} while(0)

#define SETUP_NO_CONTENTION()do { \
    __asm("ldr r0, =0x20030000"); \
} while(0)

#define SETUP_CONTENTION()do { \
	  SETUP_CONTENTION_SRAM1(); \
} while(0)


#define TEN_LDRS() do { \
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
	__asm volatile("ldr r1, [r0]");\
} while(0)

#define HUND_LDRS()do {\
		TEN_LDRS();\
		TEN_LDRS();\
		TEN_LDRS();\
		TEN_LDRS();\
		TEN_LDRS();\
		TEN_LDRS();\
		TEN_LDRS();\
		TEN_LDRS();\
		TEN_LDRS();\
		TEN_LDRS();\
	} while(0)

#define MAX_SYMBOL 256
#define N_SAMPLES 100
#define TRASNFER_SIZE 8000

#define TROJAN_SECURE
#define CONTENTION

#include "secure_nsc.h"

__attribute__((optimize(0))) void trojan(int input_symbol){
  // Trying to balance this code in terms of time as much as possible  
  for(int i=0;i < MAX_SYMBOL; i++){
    if(i < input_symbol){
      #ifdef CONTENTION
        SETUP_CONTENTION();
      #else
        SETUP_NO_CONTENTION();
      #endif
    }
    // With else it would be unbalanced in terms of LDRs
    if(i >= input_symbol){
    	SETUP_NO_CONTENTION();
    }
    HUND_LDRS();
  }
}

void config_DMA_M2M(int size){
// Make this vars global. The stack will be destroyed.
  static int src, dst;
  //need to comment __HAL_DMA_ENABLE in function HAL_DMA_Start()
  HAL_DMA_Start_IT(&hdma_memtomem_dma1_channel1, (uint32_t)&src,
                    (uint32_t)&dst, size);
}

int input_symbol = 0, sample = 0;

__attribute__((optimize(0))) void covert_channel(){
  int *ptr_cnt = 0x40000000+0x24; // TIM2 (32 bits)
  // trigger chain of interrupts (DMA transfers)
  config_DMA_M2M(TRASNFER_SIZE);
  *ptr_cnt = 0;
  HAL_TIM_Base_Start(&htim2);
  //start DMA transaction
  //need to comment this line in function HAL_DMA_Start()
  __HAL_DMA_ENABLE(&hdma_memtomem_dma1_channel1);
  #ifdef TROJAN_SECURE
    trojan_s(input_symbol);
  #else
    trojan(input_symbol);
  #endif
  while(1);
}

/* 
* The channel is measured in the DMA ISR to avoid accessing the SRAM,which would 
* introduce a lot of noise in the covert-channel. (Remove the need of a flag
* shared between ISR and code, that would generate a lot of SRAM accesses)
*/
__attribute__((optimize(0))) void DMA1_Channel1_IRQHandler(){
  int *ptr_cnt = 0x40000000+0x24; // TIM2 (32 bits)
  HAL_TIM_Base_Stop(&htim2);
  HAL_DMA_IRQHandler(&hdma_memtomem_dma1_channel1);
  printf("(%d, %d)\r\n", input_symbol, *ptr_cnt);
  sample++;
  // N_SAMPLES per input symbol
  if(sample >= N_SAMPLES){
    if(input_symbol < MAX_SYMBOL-1){
      input_symbol++;
      sample = 0;
    }
    else {
      input_symbol = 0;
     // printf("END\r\n");
      return;
    }
  }

  config_DMA_M2M(TRASNFER_SIZE);
  *ptr_cnt = 0;
  HAL_TIM_Base_Start(&htim2);
  //start DMA transaction
  //need to comment this line in function HAL_DMA_Start()
  __HAL_DMA_ENABLE(&hdma_memtomem_dma1_channel1);
  #ifdef TROJAN_SECURE
    trojan_s(input_symbol);
  #else
    trojan(input_symbol);
  #endif
  return;
  
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
  //DISABLE SYSTICK
  SysTick->CTRL = 0;

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_ICACHE_Init();
  MX_GPIO_Init();
  MX_LPUART1_UART_Init();
  MX_DMA_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  covert_channel();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE0) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 55;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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

#ifdef  USE_FULL_ASSERT
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

