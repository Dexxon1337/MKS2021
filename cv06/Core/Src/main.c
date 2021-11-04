/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "1wire.h"
#include "sct.h"
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
ADC_HandleTypeDef hadc;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC_Init(void);
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
	int16_t temp_18b20;
	uint16_t temp_ntc_ad = 0;
	int16_t temp_ntc_converted = 0;

	int16_t temp_table [] = {1429,1420,1412,1404,1395,1387,1379,1371,1363,1355,1347,1339,1331,1323,1316,1308,1300,1293,1285,1278,1271,1263,1256,1249,1242,1235,1228,1221,1214,
	1207,1200,1193,1187,1180,1173,1167,1160,1154,1148,1141,1135,1129,1123,1116,1110,1104,1098,1092,1086,1081,1075,1069,1063,1058,1052,1046,1041,1035,
	1030,1025,1019,1014,1009,1003,998,993,988,983,978,973,968,963,958,953,949,944,939,935,930,925,921,916,912,907,903,899,894,890,886,882,877,873,869,
	865,861,857,853,849,845,841,837,834,830,826,822,819,815,811,808,804,801,797,794,790,787,783,780,777,773,770,767,764,761,757,754,751,748,745,742,739,
	736,733,730,727,724,721,719,716,713,710,708,705,702,700,697,694,692,689,687,684,681,679,677,674,672,669,667,664,662,660,657,655,653,651,648,646,644,
	642,640,638,635,633,631,629,627,625,623,621,619,617,615,613,611,609,607,606,604,602,600,598,596,595,593,591,589,588,586,584,582,581,579,577,576,574,
	573,571,569,568,566,565,563,562,560,559,557,556,554,553,551,550,548,547,545,544,543,541,540,538,537,536,534,533,532,530,529,528,527,525,524,523,521,
	520,519,518,517,515,514,513,512,510,509,508,507,506,505,503,502,501,500,499,498,497,496,494,493,492,491,490,489,488,487,486,485,484,483,482,481,479,
	478,477,476,475,474,473,472,471,470,469,468,467,466,465,464,463,462,461,460,460,459,458,457,456,455,454,453,452,451,450,449,448,447,446,445,444,443,
	443,442,441,440,439,438,437,436,435,434,433,432,432,431,430,429,428,427,426,425,424,423,423,422,421,420,419,418,417,416,415,414,414,413,412,411,410,
	409,408,407,406,406,405,404,403,402,401,400,399,398,397,397,396,395,394,393,392,391,390,389,389,388,387,386,385,384,383,382,381,380,380,379,378,377,
	376,375,374,373,372,371,370,370,369,368,367,366,365,364,363,362,361,360,359,359,358,357,356,355,354,353,352,351,350,349,348,347,346,346,345,344,343,
	342,341,340,339,338,337,336,335,334,333,332,331,330,329,328,328,327,326,325,324,323,322,321,320,319,318,317,316,315,314,313,312,311,310,309,308,307,
	306,305,304,303,302,301,300,299,298,297,296,295,294,293,292,291,290,289,288,287,286,285,284,283,282,281,280,279,278,277,276,275,274,273,272,271,270,
	269,268,267,266,265,264,263,262,261,260,259,258,257,256,255,254,253,252,251,250,249,248,247,246,245,244,243,242,241,240,239,238,237,236,235,234,233,
	232,231,230,229,228,227,226,225,224,222,221,220,219,218,217,216,215,214,213,212,211,210,209,208,207,206,205,204,203,202,201,200,199,198,197,196,195,
	194,193,192,191,190,189,188,187,186,185,184,183,182,181,180,179,178,177,176,175,174,173,172,171,170,169,168,167,166,165,164,163,162,161,160,159,158,
	157,156,156,155,154,153,152,151,150,149,148,147,146,145,144,143,142,141,140,139,138,137,136,135,134,134,133,132,131,130,129,128,127,126,125,124,123,
	122,121,120,120,119,118,117,116,115,114,113,112,111,110,110,109,108,107,106,105,104,103,102,101,101,100,99,98,97,96,95,94,93,93,92,91,90,89,88,87,86,
	86,85,84,83,82,81,80,80,79,78,77,76,75,74,74,73,72,71,70,69,68,68,67,66,65,64,63,63,62,61,60,59,58,57,57,56,55,54,53,52,52,51,50,49,48,47,47,46,45,44,
	43,42,42,41,40,39,38,38,37,36,35,34,33,33,32,31,30,29,28,27,27,26,25,24,23,22,22,21,20,19,18,17,17,16,15,14,13,12,11,11,10,9,8,7,6,5,5,4,3,2,1,0,-1,-2,
	-3,-3,-4,-5,-6,-7,-8,-9,-10,-11,-12,-13,-13,-14,-15,-16,-17,-18,-19,-20,-21,-22,-23,-24,-25,-26,-27,-28,-29,-30,-31,-32,-33,-34,-35,-36,-37,-38,-39,-40,
	-41,-42,-43,-44,-45,-47,-48,-49,-50,-51,-52,-53,-54,-55,-57,-58,-59,-60,-61,-62,-64,-65,-66,-67,-69,-70,-71,-72,-74,-75,-76,-77,-79,-80,-81,-83,-84,-85,
	-87,-88,-89,-91,-92,-94,-95,-96,-98,-99,-101,-102,-104,-105,-107,-108,-110,-111,-113,-114,-116,-118,-119,-121,-123,-124,-126,-128,-129,-131,-133,-134,
	-136,-138,-140,-141,-143,-145,-147,-149,-151,-153,-154,-156,-158,-160,-162,-164,-166,-168,-170,-172,-174,-177,-179,-181,-183,-185,-187,-190,-192,-194,
	-196,-199,-201,-203,-206,-208,-210,-213,-215,-218,-220,-223,-225,-228,-230,-233,-235,-238,-241,-243,-246,-249,-252,-254,-257,-260,-263,-266,-269,-271,
	-274,-277,-280,-283,-286,-290,-293,-296,-299,-302,-305,-309,-312,-315,-319,-322,-325,-329,-332,-336,-339,-343,-346,-350,-354,-357,-361,-365,-369,-372,
	-376,-380,-384,-388,-392,-396,-400,-404,-408,-412,-416,-421,-425,-429,-433,-438,-442,-447,-451,-456,-460,-465,-469,-474,-479,-484,-488,-493,-498,-503,-508};

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
  MX_ADC_Init();
  /* USER CODE BEGIN 2 */
  HAL_ADCEx_Calibration_Start(&hadc);
  HAL_ADC_Start(&hadc);
  sct_init();
  OWInit();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  OWConvertAll();
	  HAL_Delay(CONVERT_T_DELAY);
	  OWReadTemperature(&temp_18b20);
      // sct_value(temp_18b20/10,0);

	  temp_ntc_ad = HAL_ADC_GetValue(&hadc);
	  temp_ntc_converted = temp_table[temp_ntc_ad];
	  sct_value(temp_ntc_converted, 0);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_10B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = ENABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

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
  huart2.Init.BaudRate = 38400;
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
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED1_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED2_Pin|SCT_NOE_Pin|SCT_CLK_Pin|SCT_SDI_Pin
                          |SCT_NLA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DQ_GPIO_Port, DQ_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : S2_Pin S1_Pin */
  GPIO_InitStruct.Pin = S2_Pin|S1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LED1_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED2_Pin SCT_NOE_Pin SCT_CLK_Pin SCT_SDI_Pin
                           SCT_NLA_Pin */
  GPIO_InitStruct.Pin = LED2_Pin|SCT_NOE_Pin|SCT_CLK_Pin|SCT_SDI_Pin
                          |SCT_NLA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : DQ_Pin */
  GPIO_InitStruct.Pin = DQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DQ_GPIO_Port, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
