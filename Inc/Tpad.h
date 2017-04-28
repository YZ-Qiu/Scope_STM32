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
extern SPI_HandleTypeDef hspi3;

/* Private define ------------------------------------------------------------*/

#define	CHX 	0x90
#define	CHY 	0xD0


/* Private function prototypes -----------------------------------------------*/
	// controller initialization
void Tpad_Init(void);
	// calibration routine
void Tpad_Calibrate(void);
	// returns if a pressure is present
GPIO_PinState Tpad_Pressed(void);
	// returns coordinates of the pressure
Coordinate *Read_Tpad(void);

	// function to calibrate touchscreen and use calibration matrix
FunctionalState setCalibrationMatrix(Coordinate * displayPtr,Coordinate * screenPtr,Matrix * matrixPtr);
FunctionalState getDisplayPoint(Coordinate * displayPtr,Coordinate * screenPtr,Matrix * matrixPtr );

	// controller specific functions - should not be used outside
static void set_CS(void);
static void reset_CS(void);
GPIO_PinState read_IRQ(void);
static void WR_CMD (uint16_t cmd);
static uint16_t RD_AD(void);

#endif
