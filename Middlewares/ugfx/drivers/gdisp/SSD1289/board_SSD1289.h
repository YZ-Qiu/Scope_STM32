/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H
#include "LCD.h"
static inline void init_board(GDisplay *g) {
	(void) g;
	GPIO_InitTypeDef GPIO_InitStructure;

	    /* configure DATA PORT  pins*/
	GPIO_InitStructure.Pin = GPIO_PIN_All;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(ILI9325_DATA_PORT, &GPIO_InitStructure);

    /* configure CONTROL PORT pins */
	GPIO_InitStructure.Pin = ILI9325_RESET_PIN | ILI9325_nWR_PIN | ILI9325_nRD_PIN | ILI9325_CS_PIN | ILI9325_RS_PIN;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP ;
	HAL_GPIO_Init(ILI9325_CTRL_PORT, &GPIO_InitStructure);

    /* configure BACKLIGHT pin */
	GPIO_InitStructure.Pin = ILI9325_BACKLIGHT_PIN;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP ;
	HAL_GPIO_Init(ILI9325_BACKLIGHT_PORT, &GPIO_InitStructure);

}

static inline void post_init_board(GDisplay *g) {
	(void) g;
	LCD_Clear(Red);
}

static inline void setpin_reset(GDisplay *g, bool_t state) {
	(void) g;
	(void) state;
	if(state == true)
		Clr_Reset;
	else
		Set_Reset;
}

static inline void set_backlight(GDisplay *g, uint8_t percent) {
	(void) g;
	(void) percent;
	Set_Backlight;
}

static inline void acquire_bus(GDisplay *g) {
	(void) g;
}

static inline void release_bus(GDisplay *g) {
	(void) g;
}

static inline void write_index(GDisplay *g, uint16_t index) {
	Clr_Rs;
	Set_nRd;
	LCD_Delay(0);
	GPIOE->ODR = index;	 /* GPIO_Write(GPIOE,index); */
	LCD_Delay(0);
	Clr_nWr;
	Set_nWr;
}

static inline void write_data(GDisplay *g, uint16_t data) {

	Set_Rs;
	LCD_Delay(0);
	GPIOE->ODR = data;	 /* GPIO_Write(GPIOE,data); */
	LCD_Delay(0);
	Clr_nWr;
	Set_nWr;
}

static inline void setreadmode(GDisplay *g) {
	(void) g;
}

static inline void setwritemode(GDisplay *g) {
	(void) g;
}

static inline uint16_t read_data(GDisplay *g) {
	(void) g;
	return 0;
}

//Optional define if your board interface supports it
//#define GDISP_USE_DMA			TRUE

// Optional define - valid only when GDISP_USE_DMA is TRUE
//#define GDISP_NO_DMA_FROM_STACK	FALSE

#if defined(GDISP_USE_DMA) && GDISP_USE_DMA

	static inline void dma_with_noinc(GDisplay *g, color_t *buffer, int area) {
		(void) g;
		(void) buffer;
		(void) area;
	}

	static inline void dma_with_inc(GDisplay *g, color_t *buffer, int area) {
		(void) g;
		(void) buffer;
		(void) area;
	}
#endif

#endif /* _GDISP_LLD_BOARD_H */
