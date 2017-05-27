/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics International N.V.
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include "main.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "adc.h"
#include "dma.h"
#include "rng.h"
#include "spi.h"
#include "gpio.h"
#include "LCD.h"
#include "Tpad.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
void MX_FREERTOS_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

osThreadId LED1_Handle;
osThreadId LED2_Handle;
__IO uint16_t ADC_val=0;
static uint16_t ADC_buffer[320]={0};
static uint16_t smp_cnt = 0;
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

void LED1_blink_Task(void const * argument)
{
  for(;;)
  {
  	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
    osDelay(500);
  }
}
#define PI 3.14159265
void ADC_Task(void const * argument)
{
  LCD_Initializtion();
 // Tpad_Init();
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&ADC_val,1);
  HAL_ADC_Start(&hadc1);
/*
  uint16_t result[320],i;
  double param = 30.0;
  
    for(i =40;i<240;i+=40)
  {
    LCD_DrawLine( 0, i,320, i ,Red);
  }
      for(i =40;i<320;i+=40)
  {
    LCD_DrawLine( i, 0,i, 240,Red);
  }
  for(i =0;i<640;i+=2)
  {
      result[i/2] = 120*(1.0+sin(i*(9.0/8.0)*PI/180));
  }

    for(i =0;i<160;i+=1)
  {
    LCD_DrawLine( i,result[i], i+1,result[i+1] ,Green);
  }
  int j,s,b;
  for(i =160;i<319;i+=1)
  {
    s = (result[i]<=result[i+1])?result[i]:result[i+1];
    b = (result[i]>result[i+1])?result[i]:result[i+1];

    for(j = s;j<b;j++)
      LCD_SetPoint(i,j,Green);
  }
  
 LCD_DrawLine( 1,1,200,200,Green);
 LCD_DrawLine( 1,239,319,1,Blue);
       for(i =0;i<240;i+=1)
  {
      LCD_SetPoint(i,i,Blue);
  }
*/

  uint16_t buf_i =0;
  //Assume 42MHz sample rate---> down scale to 420Hz
	char str[32],buf_str[32];
	LCD_print(10, 10, "test");
/*
		LCD_DrawLine( 0,51,1,51,Green);
		LCD_DrawLine( 1,51,2,54,Green);
		LCD_DrawLine( 2,54,3,53,Green);
		LCD_DrawLine( 3,53,4,51,Green);
*/						

	for(;;)
  {
  /*
			LCD_printColor(10, 50, str, Black);
			sprintf(str,"%d",smp_cnt);
			LCD_print(10, 50, str);
*/
  		osDelay(1);  //inevitable ,or lcd won't display,dont know why
		if(smp_cnt>=100)
		{
			if(buf_i==320)
				buf_i=0;
				
			if(buf_i != 0)
			{
				LCD_DrawLine( buf_i,ADC_buffer[buf_i],buf_i+1,ADC_buffer[buf_i+1],Black);
				ADC_buffer[buf_i] = (ADC_val)*(240.0/4096.0);
				LCD_DrawLine( buf_i-1,ADC_buffer[buf_i-1],buf_i,ADC_buffer[buf_i],Green);
				
				LCD_printColor(10, 110, str,Black);
				sprintf(str,"%d",ADC_val);
				LCD_print(10, 110, str);

			}
			else
			{
				
				LCD_DrawLine( 0,ADC_buffer[0],1,ADC_buffer[1],Black);
				ADC_buffer[buf_i] = (ADC_val)*240/4096;
			}
			buf_i++;
			smp_cnt = 0;
		}

   }



/*
   float val=0;
    char str[16];
     for(;;)
  {
    val+=0.001;
   // sprintf(str, "%.3f", val);
  //	snprintf(str, sizeof(str), "%.3f", val);

  float2str(val,str,3);

   LCD_print(10, 30, str);
    osDelay(300);
    LCD_printColor(10, 30, str, Black);
   // LCD_Clear(Black);
  }
*/

}
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_RNG_Init();
  MX_SPI3_Init();
  MX_ADC1_Init();





  /* Call init function for freertos objects (in freertos.c) */
//  osThreadDef(LED1, LED1_blink_Task,osPriorityNormal ,1, 1024);
 // LED1_Handle = osThreadCreate(osThread(LED1), NULL);

  osThreadDef(LED2, ADC_Task, osPriorityRealtime, 1, 1024);
  LED2_Handle = osThreadCreate(osThread(LED2), NULL);

  osKernelStart();

/*
	LCD_print(10, 10,"STM32F4-Discovery board");

  LCD_print(10, 30, "Running @ 168 MHz");
  LCD_print(10, 50, "SSD1289 320x240 GLCD");
  LCD_print(10, 70, "XPT2046 Touchscreen");
  LCD_print(10, 130, "Demo routine...");
  LCD_print(10, 210, "(C) 2013 Fabio Angeletti");
   Clr_Backlight;
   delay(5000);
   Set_Backlight;
   delay(5000);
*/

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
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  ADC_val = HAL_ADC_GetValue(&hadc1);
  smp_cnt++;
}


/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage
    */
  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;


    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);


}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler */
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
