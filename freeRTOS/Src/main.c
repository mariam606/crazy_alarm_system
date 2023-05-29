/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>
#include <string.h>
#define R1_pin GPIO_PIN_0
#define R2_pin GPIO_PIN_1
#define R3_pin GPIO_PIN_11
#define R4_pin GPIO_PIN_12
#define C1_pin GPIO_PIN_4
#define C2_pin GPIO_PIN_5
#define C3_pin GPIO_PIN_6
#define C4_pin GPIO_PIN_5 //It's GPIOB not A
#include "liquidcrystal_i2c.h.txt"
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
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c3;

RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart2;

osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;
osThreadId myTask04Handle;
/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
int i =0,j=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_RTC_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C3_Init(void);
void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);
void StartTask04(void const * argument);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int alarm_on_flag = 0, riddle_flag = 1;
int a, b,c,d,e,f, cnt = 0;
uint8_t msg; 
uint8_t key;
RTC_AlarmTypeDef sAlarm;
uint8_t secbuffer[2], minbuffer[2], hourbuffer[2], 
alarm_sec[2], alarm_min[2], alarm_h[2], buffer0A[2],  controlbuffer[2], statusbuffer[2];
int ans;
uint8_t h1,h2,m1,m2,s1,s2;
char uartBuf [100] = {0};
char riddle_ans[100], alarm_input[100];
char empty_arr[100];
char riddle[100];
char answer[100];
char hh[2],mm[2], ss[2];
int alarm_set_flag = 0;

char read_key(){
	
	//Column 1	
	HAL_GPIO_WritePin (GPIOA, C1_pin, GPIO_PIN_RESET); //Pull the C1 low
	HAL_GPIO_WritePin (GPIOA, C2_pin, GPIO_PIN_SET);  // Pull the C2 High
	HAL_GPIO_WritePin (GPIOA, C3_pin, GPIO_PIN_SET);  // Pull the C3 High
	HAL_GPIO_WritePin (GPIOB, C4_pin, GPIO_PIN_SET);  // Pull the C4 High
	
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
	HAL_GPIO_WritePin (GPIOB, C4_pin, GPIO_PIN_SET);  // Pull the C4 High
	
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
	HAL_GPIO_WritePin (GPIOB, C4_pin, GPIO_PIN_SET);  // Pull the C4 High
	
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
	HAL_GPIO_WritePin (GPIOB, C4_pin, GPIO_PIN_RESET);  // Pull the C4 High
	
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
	return '_';
}

void forward(){
    msg = 0xC2;
    HAL_UART_Transmit( &huart2, &msg, 1, 1000);
    msg = 0x40;
    HAL_UART_Transmit( &huart2, &msg, 1, 1000);
    msg = 0xCA;
    HAL_UART_Transmit( &huart2, &msg, 1, 1000);
    msg = 0x40;
    HAL_UART_Transmit( &huart2, &msg, 1, 1000);
}

void right(){
    msg = 0xC2;
    HAL_UART_Transmit( &huart2, &msg, 1, 1000);
    msg = 0x40;
    HAL_UART_Transmit( &huart2, &msg, 1, 1000);
    msg = 0xCA;
    HAL_UART_Transmit( &huart2, &msg, 1, 1000);
    msg = 0x00;
    HAL_UART_Transmit( &huart2, &msg, 1, 1000);
}

void backward(){
    msg = 0x0;
    HAL_UART_Transmit( &huart2, &msg, 1, 1000);
    msg = 0x0;
    HAL_UART_Transmit( &huart2, &msg, 1, 1000);
    msg = 0x0;
    HAL_UART_Transmit( &huart2, &msg, 1, 1000);
    msg = 0x0;
    HAL_UART_Transmit( &huart2, &msg, 1, 1000);
}

void stop(){
	  msg = 0xC2;
    HAL_UART_Transmit( &huart2, &msg, 1, 1000);
    msg = 0x0;
    HAL_UART_Transmit( &huart2, &msg, 1, 1000);
    msg = 0xCA;
    HAL_UART_Transmit( &huart2, &msg, 1, 1000);
    msg = 0x0;
    HAL_UART_Transmit( &huart2, &msg, 1, 1000);
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
  MX_USART2_UART_Init();
  MX_RTC_Init();
  MX_I2C1_Init();
  MX_I2C3_Init();
  /* USER CODE BEGIN 2 */
	HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);  //not necessary now 
	HD44780_Init(2);
	HD44780_Clear();
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityLow, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, StartTask03, osPriorityIdle, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* definition and creation of myTask04 */
  osThreadDef(myTask04, StartTask04, osPriorityIdle, 0, 128);
  myTask04Handle = osThreadCreate(osThread(myTask04), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_LSE
                              |RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_I2C3;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x10909CEC;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.Timing = 0x10909CEC;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  RTC_AlarmTypeDef sAlarm = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable the Alarm A
  */
  sAlarm.AlarmTime.Hours = 0x0;
  sAlarm.AlarmTime.Minutes = 0x0;
  sAlarm.AlarmTime.Seconds = 0x10;
  sAlarm.AlarmTime.SubSeconds = 0x0;
  sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
  sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY|RTC_ALARMMASK_HOURS
                              |RTC_ALARMMASK_MINUTES;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarm.AlarmDateWeekDay = 0x1;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 19200;
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
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 PA6 PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
	//Displaying the first screen that allows the user to input the alarm
	HD44780_Clear();
	a = rand() % 10, b = rand() % 10, c = rand() % 100, d = rand() % 10, e = rand() % 10, f = rand() % 10;
	ans = a * b + c * d + e * f;
	sprintf(answer, "%dA",ans);
	sprintf(riddle, "%d*%d+%d*%d+%d*%d =",a,b,c,d,e,f );
	HD44780_Init(2);
	HD44780_Clear();
	sprintf(alarm_input, "Set Alarm hh:mm");
	HD44780_Clear();
	HD44780_SetCursor(0,0);
	HD44780_PrintStr(alarm_input);
	HD44780_SetCursor(0,1);
	HD44780_PrintStr("Then Press B");
	controlbuffer[0] = 0x0E; 
	controlbuffer[1] = 0x1C;  //00011101
	HAL_I2C_Master_Transmit(&hi2c3, 0xD0, controlbuffer, 2, 10);
	j = 10;
  for(;;)
  {
		if (!alarm_set_flag && !alarm_on_flag){ //Getting the alarm input from the user
		key = read_key();
		if (key != '_') {
			alarm_input[j] = key;
			if (j == 11) j+= 2;
			else j++;
		  HD44780_Clear();
			HD44780_SetCursor(0,0);
			HD44780_PrintStr(alarm_input);
			HD44780_SetCursor(0,1);
			HD44780_PrintStr("Then Press B");
				
			if(key == 'B')
			{
				alarm_set_flag = 1;
				HD44780_Clear();
		    HD44780_SetCursor(0,0);
				HD44780_PrintStr("Alarm Set!");
						
				mm[0]=alarm_input[10];
				mm[1]=alarm_input[11]; 
				ss[0]=alarm_input[13];
				ss[1]=alarm_input[14];
				//RTC work
				//set the alarm here
				// seconds
				secbuffer[0] = 0x00; //register address
				secbuffer[1] = 0x00; //data to put in register --> 35 sec
				HAL_I2C_Master_Transmit(&hi2c3, 0xD0, secbuffer, 2, 10);
				// minutes
				minbuffer[0] = 0x01; //register address
				minbuffer[1] = 0x10; //data to put in register --> 10 AM
				HAL_I2C_Master_Transmit(&hi2c3, 0xD0, minbuffer, 2, 10);

				// hours
				hourbuffer[0] = 0x02; //register address
				hourbuffer[1] = 0x50; //data to put in register 01001100 --> 10 am
				HAL_I2C_Master_Transmit(&hi2c3, 0xD0, hourbuffer, 2, 10);

				//alarm:
				alarm_sec[0] = 0x07;
				alarm_sec[1] = (ss[0] - '0') * 16 + ss[1] - '0';
				HAL_I2C_Master_Transmit(&hi2c3, 0xD0, alarm_sec, 2, 10);
				
				alarm_min[0] = 0x08;
				alarm_min[1] = (mm[0] - '0') * 16 + mm[1] - '0';


				HAL_I2C_Master_Transmit(&hi2c3, 0xD0, alarm_min, 2, 10);
				alarm_h[0] = 0x09;
				alarm_h[1] = 0x50;	//0101 //0 AM/PM 
				HAL_I2C_Master_Transmit(&hi2c3, 0xD0, alarm_h, 2, 10);
				
				buffer0A[0] = 0x0A;
				buffer0A[1] = 0x80;	//1000 0000
				HAL_I2C_Master_Transmit(&hi2c3, 0xD0, buffer0A, 2, 10);
				
				//control:
				controlbuffer[0] = 0x0E; 
				controlbuffer[1] = 0x1D;  //00011101
				HAL_I2C_Master_Transmit(&hi2c3, 0xD0, controlbuffer, 2, 10);
				statusbuffer[0] = 0x0F;
				statusbuffer[1] = 0x88;
				HAL_I2C_Master_Transmit(&hi2c3, 0xD0, statusbuffer, 2, 10);
			}
		}
	}
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
		if(alarm_set_flag == 1){ //calculating the time for the alarm to start working
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_SET);
		//send seconds register address 00h to read from
		 HAL_I2C_Master_Transmit(&hi2c3, 0xD0, secbuffer, 1, 10);
		 HAL_I2C_Master_Receive(&hi2c3, 0xD1, secbuffer+1, 1, 10);
		 //prepare UART output
		 s1 = secbuffer[1] >> 4;
		 s2 = secbuffer[1] & 0x0F;
		 HAL_I2C_Master_Transmit(&hi2c3, 0xD0, minbuffer, 1, 10);
		 HAL_I2C_Master_Receive(&hi2c3, 0xD1, minbuffer+1, 1, 10);
		 m1 = minbuffer[1] >> 4;
		 m2 = minbuffer[1] & 0x0F;
		 HAL_I2C_Master_Transmit(&hi2c3, 0xD0, hourbuffer, 1, 10);
		 HAL_I2C_Master_Receive(&hi2c3, 0xD1, hourbuffer+1, 1, 10);
		 h1 = (hourbuffer[1] >> 4) & 1;
		 h2 = hourbuffer[1] & 0x0F;
		
		sprintf(uartBuf, "%d%d:%d%d:%d%d\r\n",h1,h2,m1,m2,s1,s2);
		HAL_UART_Transmit(&huart2, (uint8_t *)uartBuf, sizeof(uartBuf), 10);
		HAL_Delay(1000);
		}
		if (s1 == (ss[0] - '0') && s2 == (ss[1] - '0') && riddle_flag && m1 == (mm[0] - '0') && m2 == (mm[1] - '0')){
			//display riddle
			HD44780_Clear();
			HD44780_SetCursor(0,0);
			HD44780_PrintStr(riddle);
			HAL_UART_Transmit(&huart2, (uint8_t*)"I got here\r\n", 100, 1000);
			riddle_flag = 0;
			alarm_set_flag = 0; //to stop incrementing
			alarm_on_flag = 1;
		}
    osDelay(1);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {
		if (alarm_on_flag){ //getting the riddle answer and moving the car 
			key = read_key();
			riddle_ans[i] = key;
			if (key != '_') {
				i++;
				HD44780_SetCursor(0,1);
				HD44780_PrintStr(riddle_ans);
					
				if(key == 'A')
				{
	//			HAL_UART_Transmit(&huart2, (uint8_t*)answer, sizeof(answer), 100);
					if(strcmp(riddle_ans,answer)==0)
					{
						HD44780_SetCursor(0,1);
						HD44780_PrintStr("Correct");
						alarm_on_flag = 0;
						alarm_set_flag = 0;
						controlbuffer[1] = 0x1C;  //00011101
						HAL_I2C_Master_Transmit(&hi2c3, 0xD0, controlbuffer, 2, 10);
						j = 10; //problem here
						sprintf(alarm_input, "Set Alarm hh:mm");			
					}
					else
					{
						HD44780_SetCursor(0,1);
						HD44780_PrintStr("Wrong");
						HAL_Delay(2000);
						HD44780_Clear();
						memset(riddle_ans, 0, sizeof(riddle_ans));
						i = 0;
						riddle_flag = 1;
					}
				}
			}
		}
    osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void const * argument)
{
  /* USER CODE BEGIN StartTask04 */
  /* Infinite loop */
  for(;;)
  {
		if (alarm_on_flag){ 
			//car movement	
			forward();
			HAL_Delay(1000);
			right();
			HAL_Delay(1000);
			backward();
			HAL_Delay(1000);
			stop();
			HAL_Delay(2000);
		}
    osDelay(1);
  }
  /* USER CODE END StartTask04 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
