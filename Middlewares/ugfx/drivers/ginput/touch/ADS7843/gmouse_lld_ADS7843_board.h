/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */
#include "Tpad.h"

#ifndef _GINPUT_LLD_MOUSE_BOARD_H
#define _GINPUT_LLD_MOUSE_BOARD_H


// Resolution and Accuracy Settings
#define GMOUSE_ADS7843_PEN_CALIBRATE_ERROR		8
#define GMOUSE_ADS7843_PEN_CLICK_ERROR			6
#define GMOUSE_ADS7843_PEN_MOVE_ERROR			4
#define GMOUSE_ADS7843_FINGER_CALIBRATE_ERROR	14
#define GMOUSE_ADS7843_FINGER_CLICK_ERROR		18
#define GMOUSE_ADS7843_FINGER_MOVE_ERROR		14

// How much extra data to allocate at the end of the GMouse structure for the board's use
#define GMOUSE_ADS7843_BOARD_DATA_SIZE			0

#define Tpad_set_CS   HAL_GPIO_WritePin(Tpad_PORT, Tpad_CS_PIN,GPIO_PIN_SET);
#define Tpad_reset_CS   HAL_GPIO_WritePin(Tpad_PORT, Tpad_CS_PIN,GPIO_PIN_RESET);
#define Tpad_read_IRQ {  return HAL_GPIO_ReadPin(Tpad_PORT, Tpad_IRQ_PIN);}

#define Tpad_RD_AD() \
  uint16_t tmpr;\
  HAL_SPI_TransmitReceive(&hspi3,0x0000 ,  &tmpr, sizeof(uint8_t), 10);\
  return (tmpr>>8);
						


static void WR_CMD (uint16_t cmd);
static bool_t init_board(GMouse* m, unsigned driverinstance);
static inline bool_t getpin_pressed(GMouse* m);

static inline void aquire_bus(GMouse* m);

static inline void release_bus(GMouse* m);

static inline uint16_t read_value(GMouse* m, uint16_t port);
#endif /* _GINPUT_LLD_MOUSE_BOARD_H */
