/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#include "gfx.h"

#if (GFX_USE_GINPUT && GINPUT_NEED_MOUSE) 

#define GMOUSE_DRIVER_VMT		GMOUSEVMT_ADS7843
#include "src/ginput/ginput_driver_mouse.h"

// Get the hardware interface
#include "gmouse_lld_ADS7843_board.h"

//#define CMD_X				0xD1
//#define CMD_Y				0x91
#define CMD_X				0x90
#define CMD_Y				0xD0
#define CMD_ENABLE_IRQ		0x80

static bool_t MouseXYZ(GMouse* m, GMouseReading* pdr)
{
	(void)m;

	// No buttons
	pdr->buttons = 0;
	pdr->z = 0;
	
	if (getpin_pressed(m)) {

	
		pdr->z = 1;						// Set to Z_MAX as we are pressed

		
		read_value(m, CMD_X);				// Dummy read - disable PenIRQ
		pdr->x = read_value(m, CMD_X);		// Read X-Value

		read_value(m, CMD_Y);				// Dummy read - disable PenIRQ
		pdr->y = read_value(m, CMD_Y);		// Read Y-Value

		read_value(m, CMD_ENABLE_IRQ);		// Enable IRQ

	}
	return TRUE;
}

const GMouseVMT const GMOUSE_DRIVER_VMT[1] = 
{
  {
	{
		GDRIVER_TYPE_TOUCH,
		GMOUSE_VFLG_TOUCH | GMOUSE_VFLG_CALIBRATE | GMOUSE_VFLG_CAL_TEST |
			GMOUSE_VFLG_ONLY_DOWN | GMOUSE_VFLG_POORUPDOWN,
		sizeof(GMouse)+GMOUSE_ADS7843_BOARD_DATA_SIZE,
		_gmouseInitDriver,
		_gmousePostInitDriver,
		_gmouseDeInitDriver
	},
	1,				// z_max - (currently?) not supported
	0,				// z_min - (currently?) not supported
	1,				// z_touchon
	0,				// z_touchoff
	{				// pen_jitter
		GMOUSE_ADS7843_PEN_CALIBRATE_ERROR,			// calibrate
		GMOUSE_ADS7843_PEN_CLICK_ERROR,				// click
		GMOUSE_ADS7843_PEN_MOVE_ERROR				// move
	},
	{				// finger_jitter
		GMOUSE_ADS7843_FINGER_CALIBRATE_ERROR,		// calibrate
		GMOUSE_ADS7843_FINGER_CLICK_ERROR,			// click
		GMOUSE_ADS7843_FINGER_MOVE_ERROR			// move
	},
	init_board, 	// init
	0,				// deinit
	MouseXYZ,		// get
	0,				// calsave
	0				// calload
  }
};

static void WR_CMD (uint16_t cmd)
{

  /* Send SPI3 data */
	uint8_t in_data;
   HAL_SPI_TransmitReceive(&hspi3,&cmd ,  &in_data,sizeof(uint16_t), 10);

}
static bool_t init_board(GMouse* m, unsigned driverinstance) {
  GPIO_InitTypeDef GPIO_InitStruct;

  if((&hspi3)->Instance==SPI3)
  {
	/* Peripheral clock enable */
	__HAL_RCC_SPI3_CLK_ENABLE();
	/* TP_CS */
	GPIO_InitStruct.Pin = Tpad_CS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(Tpad_PORT, &GPIO_InitStruct);

	/* TP_IRQ */
	GPIO_InitStruct.Pin =  Tpad_IRQ_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(Tpad_PORT, &GPIO_InitStruct);

  }
  Tpad_set_CS

  /* Configure SPI -----------------------------------------------------------*/
	//see spi.c

}
static inline bool_t getpin_pressed(GMouse* m)
{
    return !HAL_GPIO_ReadPin(Tpad_PORT, Tpad_IRQ_PIN);
}

static inline void aquire_bus(GMouse* m) {

}

static inline void release_bus(GMouse* m) {

}

static inline uint16_t read_value(GMouse* m, uint16_t port) {
  uint16_t cur_X;
  uint16_t tmpr;
//don't remove delay or it will cause noise touch
  Tpad_reset_CS
  gfxSleepMilliseconds(1);
  WR_CMD(port);
  gfxSleepMilliseconds(1);

  HAL_SPI_TransmitReceive(&hspi3,0x0000 ,  &tmpr, sizeof(uint8_t), 10);

  cur_X=tmpr>>8;
  gfxSleepMilliseconds(1);
  Tpad_set_CS
  gfxSleepMilliseconds(1);
  return cur_X;
  
}






#endif /* GFX_USE_GINPUT && GINPUT_NEED_MOUSE */

