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
#include "ff.h"



#include "gfx.h"
#include "ui.h"

void SystemClock_Config(void);
void Error_Handler(void);
void MX_FREERTOS_Init(void);


osThreadId UI_TaskHandle;

osThreadId TouchTaskHandle;
void Touch_Task(void const * argument)
{
    LCD_Initializtion();

  Tpad_Init();
  Tpad_Calibrate();
  for(;;){}
}

#define PI 3.14159265
int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_DMA_Init();
  MX_RNG_Init();
  MX_SPI3_Init();
//  LCD_Initializtion();


  osThreadDef(UI_Task, UserInterface, osPriorityHigh, 1, 2048);
  UI_TaskHandle = osThreadCreate(osThread(UI_Task), NULL);

  /*
    osThreadDef(t_Task,Touch_Task, osPriorityHigh, 1, 1024);
  TouchTaskHandle = osThreadCreate(osThread(t_Task), NULL);
*/
//HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
  osKernelStart();



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
  RCC_OscInitStruct.PLL.PLLM = 24;
  RCC_OscInitStruct.PLL.PLLN = 335;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

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

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler */
}

