/* -----------------------------------------------------------------------------

Tpad based touchscreen driver

Copyright (C) 2013  Fabio Angeletti - fabio.angeletti89@gmail.com

Part of this code is an adaptation from souce code provided by
		WaveShare - http://www.waveshare.net

I'm not the owner of the whole code

------------------------------------------------------------------------------*/

#ifndef _TPAD_H_
#define _TPAD_H_

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx.h"
//#include "stm32f4xx_hal.h"

#include "LCD.h"

/* Private typedef -----------------------------------------------------------*/
typedef	struct POINT 
{
   uint16_t x;
   uint16_t y;
}Coordinate;


typedef struct Matrix 
{						
long double An,  
            Bn,     
            Cn,   
            Dn,    
            En,    
            Fn,     
            Divider ;
} Matrix ;

/* Private variables ---------------------------------------------------------*/
extern Coordinate ScreenSample[3];
extern Coordinate DisplaySample[3];
extern Matrix matrix ;
extern Coordinate  display ;

/* Private define ------------------------------------------------------------*/

#define	CHX 	0x90
#define	CHY 	0xD0

#define Tpad_PORT		     GPIOB
#define Tpad_MISO_PIN	  GPIO_PIN_4
#define Tpad_MOSI_PIN	  GPIO_PIN_5
#define Tpad_SCK_PIN      GPIO_PIN_3
#define Tpad_CS_PIN		  GPIO_PIN_7
#define Tpad_IRQ_PIN	  GPIO_PIN_6

/* Private function prototypes -----------------------------------------------*/				
	// controller initialization
void Tpad_Init(void);
	// calibration routine	
void Tpad_Calibrate(void);
	// returns if a pressure is present
uint16_t Tpad_Press(void);
	// returns coordinates of the pressure
Coordinate *Read_Tpad(void);

	// function to calibrate touchscreen and use calibration matrix
FunctionalState setCalibrationMatrix(Coordinate * displayPtr,Coordinate * screenPtr,Matrix * matrixPtr);
FunctionalState getDisplayPoint(Coordinate * displayPtr,Coordinate * screenPtr,Matrix * matrixPtr );

	// controller specific functions - should not be used outside
static void set_CS(void);
static void reset_CS(void);
static uint16_t read_IRQ(void);
static void WR_CMD (uint16_t cmd);
static uint16_t RD_AD(void);

#endif
