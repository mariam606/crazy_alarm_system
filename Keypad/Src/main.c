
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2023 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l4xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#define R1_pin GPIO_PIN_8

#define R2_pin GPIO_PIN_9

#define R3_pin GPIO_PIN_10

#define R4_pin GPIO_PIN_11

#define C1_pin GPIO_PIN_4

#define C2_pin GPIO_PIN_5

#define C3_pin GPIO_PIN_6

#define C4_pin GPIO_PIN_7

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
char read_key(){
	
	//Column 1	
	HAL_GPIO_WritePin (GPIOA, C1_pin, GPIO_PIN_RESET); //Pull the C1 low
	HAL_GPIO_WritePin (GPIOA, C2_pin, GPIO_PIN_SET);  // Pull the C2 High
	HAL_GPIO_WritePin (GPIOA, C3_pin, GPIO_PIN_SET);  // Pull the C3 High
	HAL_GPIO_WritePin (GPIOA, C4_pin, GPIO_PIN_SET);  // Pull the C4 High
	
	if (!(HAL_GPIO_ReadPin (GPIOA, R1_pin)))   // if the Col 1 is low
	{
		while (!(HAL_GPIO_ReadPin (GPIOA, R1_pin)));   // wait till the button is pressed
		return '1';
	}	
	if (!(HAL_GPIO_ReadPin (GPIOA, R2_pin)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (GPIOA, R2_pin)));   // wait till the button is pressed
		return '4';
	}
	if (!(HAL_GPIO_ReadPin (GPIOA, R3_pin)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (GPIOA, R3_pin)));   // wait till the button is pressed
		return '7';
	}	
	if (!(HAL_GPIO_ReadPin (GPIOA, R4_pin)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (GPIOA, R4_pin)));   // wait till the button is pressed
		return '0';
	}
		
	//Column 2	
	HAL_GPIO_WritePin (GPIOA, C1_pin, GPIO_PIN_SET); //Pull the C1 low
	HAL_GPIO_WritePin (GPIOA, C2_pin, GPIO_PIN_RESET);  // Pull the C2 High
	HAL_GPIO_WritePin (GPIOA, C3_pin, GPIO_PIN_SET);  // Pull the C3 High
	HAL_GPIO_WritePin (GPIOA, C4_pin, GPIO_PIN_SET);  // Pull the C4 High
	
	if (!(HAL_GPIO_ReadPin (GPIOA, R1_pin)))   // if the Col 1 is low
	{
		while (!(HAL_GPIO_ReadPin (GPIOA, R1_pin)));   // wait till the button is pressed
		return '2';
	}
		
	if (!(HAL_GPIO_ReadPin (GPIOA, R2_pin)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (GPIOA, R2_pin)));   // wait till the button is pressed
		return '5';
	}

	if (!(HAL_GPIO_ReadPin (GPIOA, R3_pin)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (GPIOA, R3_pin)));   // wait till the button is pressed
		return '8';
	}	
	
		if (!(HAL_GPIO_ReadPin (GPIOA, R4_pin)))   // if the Col 2 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R4_pin)));   // wait till the button is pressed
			return 'F';
		}

	//Column 3	
	HAL_GPIO_WritePin (GPIOA, C1_pin, GPIO_PIN_SET); //Pull the C1 low
	HAL_GPIO_WritePin (GPIOA, C2_pin, GPIO_PIN_SET);  // Pull the C2 High
	HAL_GPIO_WritePin (GPIOA, C3_pin, GPIO_PIN_RESET);  // Pull the C3 High
	HAL_GPIO_WritePin (GPIOA, C4_pin, GPIO_PIN_SET);  // Pull the C4 High
	
	if (!(HAL_GPIO_ReadPin (GPIOA, R1_pin)))   // if the Col 1 is low
	{
		while (!(HAL_GPIO_ReadPin (GPIOA, R1_pin)));   // wait till the button is pressed
		return '3';
	}
		
	if (!(HAL_GPIO_ReadPin (GPIOA, R2_pin)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (GPIOA, R2_pin)));   // wait till the button is pressed
		return '6';
	}

	if (!(HAL_GPIO_ReadPin (GPIOA, R3_pin)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (GPIOA, R3_pin)));   // wait till the button is pressed
		return '9';
	}	
	
		if (!(HAL_GPIO_ReadPin (GPIOA, R4_pin)))   // if the Col 2 is low
		{
			while (!(HAL_GPIO_ReadPin (GPIOA, R4_pin)));   // wait till the button is pressed
			return 'E';
		}
	//Column 4
	HAL_GPIO_WritePin (GPIOA, C1_pin, GPIO_PIN_SET); //Pull the C1 low
	HAL_GPIO_WritePin (GPIOA, C2_pin, GPIO_PIN_SET);  // Pull the C2 High
	HAL_GPIO_WritePin (GPIOA, C3_pin, GPIO_PIN_SET);  // Pull the C3 High
	HAL_GPIO_WritePin (GPIOA, C4_pin, GPIO_PIN_RESET);  // Pull the C4 High
	
	if (!(HAL_GPIO_ReadPin (GPIOA, R1_pin)))   // if the Col 1 is low
	{
		while (!(HAL_GPIO_ReadPin (GPIOA, R1_pin)));   // wait till the button is pressed
		return 'A';
	}
		
	if (!(HAL_GPIO_ReadPin (GPIOA, R2_pin)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (GPIOA, R2_pin)));   // wait till the button is pressed
		return 'B';
	}

	if (!(HAL_GPIO_ReadPin (GPIOA, R3_pin)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (GPIOA, R3_pin)));   // wait till the button is pressed
		return 'C';
	}	
	if (!(HAL_GPIO_ReadPin (GPIOA, R4_pin)))   // if the Col 2 is low
	{
		while (!(HAL_GPIO_ReadPin (GPIOA, R4_pin)));   // wait till the button is pressed
		return 'D';
	}
}
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	uint8_t key = 'h';
  while (1)
  {
		key = read_key();
		HAL_UART_Transmit(&huart2, &key, 1, 100);
		HAL_Delay(100);
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

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Configure LSE Drive Capability 
    */
  HAL_PWR_EnableBkUpAccess();

  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
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
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the main internal regulator output voltage 
    */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /**Enable MSI Auto calibration 
    */
  HAL_RCCEx_EnableMSIPLLMode();

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA4 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA9 PA10 PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) { 
//  RTC_AlarmTypeDef sAlarm;
//  HAL_RTC_GetAlarm(hrtc,&sAlarm,RTC_ALARM_A,FORMAT_BIN);
//  if(sAlarm.AlarmTime.Seconds>58) {
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,GPIO_PIN_RESET);
//    sAlarm.AlarmTime.Seconds=0;
//  }else{
//    sAlarm.AlarmTime.Seconds=sAlarm.AlarmTime.Seconds+1;
//  }
//    while(HAL_RTC_SetAlarm_IT(hrtc, &sAlarm, FORMAT_BIN)!=HAL_OK){}
//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,GPIO_PIN_SET);
//}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
