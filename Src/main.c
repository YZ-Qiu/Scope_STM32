/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
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
#include "stm32f4xx_hal.h"
#include "rng.h"
#include "spi.h"
#include "gpio.h"

#include "delay.h"
#include "LCD.h"
#include "Tpad.h"


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);

void Delayms(uint32_t millis);


/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

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
 
  MX_RNG_Init();
  MX_SPI3_Init();

  /* USER CODE BEGIN 2 */

  LCD_Initializtion();
  Tpad_Init();
    /*
	LCD_Clear(Red);
	delay(5000);
	LCD_Clear(Green);
	delay(5000);
	LCD_Clear(Blue);
	delay(5000);
	 */
  
/* USER CODE END 2 */

	LCD_TextFont(10, 10,"STM32F4-Discovery board", Green,SYSTEM_8x16);
  
  LCD_TextFont(10, 30, "Running @ 168 MHz", Green,SYSTEM_8x16);
  LCD_TextFont(10, 50, "SSD1289 320x240 GLCD", Green, SYSTEM_8x16);
  LCD_TextFont(10, 70, "XPT2046 Touchscreen", Green, SYSTEM_8x16);
  LCD_TextFont(10, 130, "Demo routine...", Green, FONT8x8);
  LCD_TextFont(10, 210, "(C) 2013 Fabio Angeletti", Green, FONT6x8);



 
  
   Clr_Backlight;
   delay(500);
   Set_Backlight;
   delay(3000);

  Tpad_Calibrate();
  LCD_Clear(Black);
  
 /* Infinite loop */
  while (1)	
  {
uint16_t x_a, x_b, y_a, y_b, color;

    // ASCII ART
    LCD_TextFont(0,0,  "                                   V8  ", Red,FONT8x8);
    LCD_TextFont(0,8,  "                                 LR 4Y ", Red,FONT8x8);
    LCD_TextFont(0,16, "                7GEMMMRI        M7   M ", Red,FONT8x8);
    LCD_TextFont(0,24, "             7MU7      7M      M     U ", Red,FONT8x8);
    LCD_TextFont(0,32, "           7M7 2C177G    M    D775   7 ", Red,FONT8x8);
    LCD_TextFont(0,40, "          XT Y7      6   M    G GY    7", Red,FONT8x8);
    LCD_TextFont(0,48, "         M77U   01       M   M  Y1    7", Red,FONT8x8);
    LCD_TextFont(0,56, "        M 37  47     L  Z  C X         ", Red,FONT8x8);
    LCD_TextFont(0,64, "       8 7  97      T   P  Z7        7 ", Red,FONT8x8);
    LCD_TextFont(0,72, "       Q 3 Z       R   M   NZ        9 ", Red,FONT8x8);
    LCD_TextFont(0,80, "      M 6 7      Y7   E   X M        9 ", Red,FONT8x8);
    LCD_TextFont(0,88, "      1 5 W  7T47   7I   B  M       G  ", Red,FONT8x8);
    LCD_TextFont(0,96, "     A  7 A        N  7 M   Q      I7  ", Red,FONT8x8);
    LCD_TextFont(0,104,"     E 7  G      G7 7  M    J     76   ", Red,FONT8x8);
    LCD_TextFont(0,112,"     K C  71  6X7  A 0U    77     P    ", Red,FONT8x8);
    LCD_TextFont(0,120,"     T 7    7    I1 M      S     M     ", Red,FONT8x8);
    LCD_TextFont(0,128,"        I      1R TM            M      ", Red,FONT8x8);
    LCD_TextFont(0,136,"         D777AF  M7            M 7     ", Red,FONT8x8);
    LCD_TextFont(0,144,"               M9             N  7C    ", Red,FONT8x8);
    LCD_TextFont(0,152,"  WT7M2    7DM9              A2   R    ", Red,FONT8x8);
    LCD_TextFont(0,160,"      DMMMZ7     7   7      7F     M   ", Red,FONT8x8);
    LCD_TextFont(0,168,"                M   7      7K       N  ", Red,FONT8x8);
    LCD_TextFont(0,176,"   7            G   G     7E     M  77 ", Red,FONT8x8);
    LCD_TextFont(0,184,"   D  7        V   B     58       M7 H ", Red,FONT8x8);
    LCD_TextFont(0,192,"   M C7        M  L    7G          Q87Y", Red,FONT8x8);
    LCD_TextFont(0,200,"   M M    XV67 E  K   7             IEM", Red,FONT8x8);
    LCD_TextFont(0,208,"   DM          9 M                   7M", Red,FONT8x8);
    LCD_TextFont(0,216,"    E          13I                     ", Red,FONT8x8);
    LCD_TextFont(0,224,"               UM                      ", Red,FONT8x8);
    LCD_TextFont(0,232,"               M                       ", Red,FONT8x8);
    LCD_TextFont(0,240,"               7                       ", Red,FONT8x8);

    delay(250);
    while(Tpad_Pressed());
    LCD_Clear(Black);
    delay(250);
	    // CIRCLEs
		// 
    for(;;)
    {
      while(__HAL_RNG_GET_FLAG(&hrng, RNG_FLAG_DRDY)== RESET);
      x_a=HAL_RNG_GetRandomNumber(&hrng)%320;

      while(__HAL_RNG_GET_FLAG(&hrng, RNG_FLAG_DRDY)== RESET);
      x_b=HAL_RNG_GetRandomNumber(&hrng)%64;

      while(__HAL_RNG_GET_FLAG(&hrng, RNG_FLAG_DRDY)== RESET);
      y_a=HAL_RNG_GetRandomNumber(&hrng)%240;

      while(__HAL_RNG_GET_FLAG(&hrng, RNG_FLAG_DRDY)== RESET);
      color=HAL_RNG_GetRandomNumber(&hrng);

      LCD_FillCircle(x_a, y_a, x_b, color);
      delay(10);
      if(!Tpad_Pressed())
        break;
    }

    LCD_Clear(Black);
    delay(250);
  }

  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

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
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

    /**Enables the Clock Security System 
    */
  HAL_RCC_EnableCSS();

    /**Configure the Systick interrupt time 
	 * HAL_RCC_GetHCLKFreq() = 168 MHz
	*/
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/10000);
//	HAL_SYSTICK_Config(SystemCoreClock/10000);


    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
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

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
