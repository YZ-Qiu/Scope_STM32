/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#include "gfx.h"

#if GFX_USE_GDISP /*|| defined(__DOXYGEN__)*/

/* This controller is only ever used with a 240 x 320 display */
#if defined(GDISP_SCREEN_HEIGHT)
	#warning "GDISP: This low level driver does not support setting a screen size. It is being ignored."
	#undef GDISP_SCREEN_HEIGHT
#endif
#if defined(GDISP_SCREEN_WIDTH)
	#warning "GDISP: This low level driver does not support setting a screen size. It is being ignored."
	#undef GDISP_SCREEN_WIDTH
#endif

#define GDISP_DRIVER_VMT			GDISPVMT_ILI9325
#include "drivers/gdisp/ILI9325/gdisp_lld_config.h"
#include "src/gdisp/gdisp_driver.h"

#include "board_ILI9325.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_SCREEN_WIDTH
	#define GDISP_SCREEN_WIDTH		MAX_X
#endif
#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT		MAX_Y
#endif
#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST	50
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT	100
#endif

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

// Some common routines and macros
#define dummy_read(g)				{ volatile uint16_t dummy; dummy = read_data(g); (void) dummy; }
#define write_reg(g, reg, data)		{ 	write_index(g, reg); write_data(g, data);}

static void set_cursor(GDisplay *g) 
{
	int16_t Xpos,Ypos;

	switch(g->g.Orientation)
	{
		default:
		case GDISP_ROTATE_0:
			write_reg(g, 0x20,g->p.x);
			write_reg(g, 0x21,g->p.y);
			write_index(g, 0x22);
		return;
		break;

		case GDISP_ROTATE_180:
			Xpos = 240 - 1 - g->p.x;
			Ypos = 320 - 1 - g->p.y;
		break;
		//X240 Y320
		case GDISP_ROTATE_90:
			Xpos = g->p.y;
			Ypos = 320 - 1 - g->p.x;
		break;
		//correct
		case GDISP_ROTATE_270:
			Xpos = g->p.y;
			Ypos = g->p.x;
		break;
	}
	write_reg(g, 0x20,Xpos);
	write_reg(g, 0x21,Ypos);
	write_index(g, 0x22);
}

static void set_viewport(GDisplay* g) {
	switch(g->g.Orientation) {
		default:
		case GDISP_ROTATE_0:
		case GDISP_ROTATE_180:
			write_reg(g, 0x50, g->p.x);
			write_reg(g, 0x51, g->p.x + g->p.cx - 1);
			write_reg(g, 0x52, g->p.y);
			write_reg(g, 0x53, g->p.y + g->p.cy - 1);
			break;
		case GDISP_ROTATE_90:
		//no problem
			write_reg(g, 0x50, g->p.y);
			write_reg(g, 0x51, g->p.y + g->p.cy - 1);

			write_reg(g, 0x53, 320-1-g->p.x);
			write_reg(g, 0x52, 320-1-(g->p.x + g->p.cx - 1));
			break;
		case GDISP_ROTATE_270:
			write_reg(g, 0x50, g->p.y);
			write_reg(g, 0x51, g->p.y + g->p.cy - 1);
		//	write_reg(g, 0x51, 320-1-(g->p.y));
		//write_reg(g, 0x50, 320-1-(g->p.y + g->p.cy - 1));
			
			write_reg(g, 0x52, g->p.x);
			write_reg(g, 0x53, g->p.x + g->p.cx - 1);
		break;
	}
}

LLDSPEC bool_t gdisp_lld_init(GDisplay *g) {


	// No private area for this controller
	g->priv = 0;

	// Initialise the board interface
	init_board(g);

	/* Hardware reset */
	Clr_Reset;
	delay_ms(100);
  	Set_Reset;
  	Set_Backlight;

	// chinese code starts here

		write_reg(g, 0x0000,0x0001);  	/* start internal osc */

		write_reg(g, 0x0001,(0<<10)|(1<<8));

		write_reg(g, 0x0002,0x0700); 	/* power on sequence */
	#if (DISP_ORIENTATION == 0)
		write_reg(g, 0x0003,(1<<12)|(1<<5)|(1<<4)|(0<<3));
	#elif (DISP_ORIENTATION == 90)
		write_reg(g, 0x0003,(1<<12)|(0<<5)|(1<<4)|(1<<3));
	#elif (DISP_ORIENTATION == 180)
		write_reg(g, 0x0003,(1<<12)|(0<<5)|(0<<4)|(0<<3));
	#elif (DISP_ORIENTATION == 270)
    write_reg(g, 0x0003,(1<<12)|(1<<5)|(0<<4)|(1<<3));
	#endif
		write_reg(g, 0x0004,0x0000);
		write_reg(g, 0x0008,0x0207);
		write_reg(g, 0x0009,0x0000);
		write_reg(g, 0x000a,0x0000); 	/* display setting */
		write_reg(g, 0x000c,0x0001);	/* display setting */
		write_reg(g, 0x000d,0x0000);
		write_reg(g, 0x000f,0x0000);
		/* Power On sequence */
		write_reg(g, 0x0010,0x0000);
		write_reg(g, 0x0011,0x0007);
		write_reg(g, 0x0012,0x0000);
		write_reg(g, 0x0013,0x0000);
		gfxSleepMilliseconds(50);  /* delay 50 ms */
		write_reg(g, 0x0010,0x1590);
		write_reg(g, 0x0011,0x0227);
		gfxSleepMilliseconds(50);  /* delay 50 ms */
		write_reg(g, 0x0012,0x009c);
		gfxSleepMilliseconds(50);  /* delay 50 ms */
		write_reg(g, 0x0013,0x1900);
		write_reg(g, 0x0029,0x0023);
		write_reg(g, 0x002b,0x000e);
		gfxSleepMilliseconds(50);  /* delay 50 ms */
		gfxSleepMilliseconds(50);  /* delay 50 ms */
		write_reg(g, 0x0030,0x0007);
		write_reg(g, 0x0031,0x0707);
		write_reg(g, 0x0032,0x0006);
		write_reg(g, 0x0035,0x0704);
		write_reg(g, 0x0036,0x1f04);
		write_reg(g, 0x0037,0x0004);
		write_reg(g, 0x0038,0x0000);
		write_reg(g, 0x0039,0x0706);
		write_reg(g, 0x003c,0x0701);
		write_reg(g, 0x003d,0x000f);
		gfxSleepMilliseconds(50);  /* delay 50 ms */
		write_reg(g, 0x0050,0x0000);
		write_reg(g, 0x0051,0x00ef);
		write_reg(g, 0x0052,0x0000);
		write_reg(g, 0x0053,0x013f);
		write_reg(g, 0x0060,0xa700);
 		write_reg(g, 0x0061,0x0001);
		write_reg(g, 0x006a,0x0000);
		write_reg(g, 0x0080,0x0000);
		write_reg(g, 0x0081,0x0000);
		write_reg(g, 0x0082,0x0000);
		write_reg(g, 0x0083,0x0000);
		write_reg(g, 0x0084,0x0000);
		write_reg(g, 0x0085,0x0000);
		write_reg(g, 0x0090,0x0010);
		write_reg(g, 0x0092,0x0600);
		write_reg(g, 0x0093,0x0003);
		write_reg(g, 0x0095,0x0110);
		write_reg(g, 0x0097,0x0000);
		write_reg(g, 0x0098,0x0000);
		/* display on sequence */
		write_reg(g, 0x0007,0x0133);


        gfxSleepMilliseconds(50);

    // Finish Init
    post_init_board(g);


    /* Initialise the GDISP structure */
    g->g.Width = GDISP_SCREEN_WIDTH;
    g->g.Height = GDISP_SCREEN_HEIGHT;
    g->g.Orientation = DISP_ORIENTATION;
    g->g.Powermode = powerOn;
    g->g.Backlight = GDISP_INITIAL_BACKLIGHT;
    g->g.Contrast = GDISP_INITIAL_CONTRAST;

	return TRUE;
}

#if GDISP_HARDWARE_STREAM_WRITE
	LLDSPEC	void gdisp_lld_write_start(GDisplay *g) {
		acquire_bus(g);
		set_viewport(g);
	}
	LLDSPEC	void gdisp_lld_write_color(GDisplay *g) {
		write_data(g, gdispColor2Native(g->p.color));
	}
	LLDSPEC	void gdisp_lld_write_stop(GDisplay *g) {
		release_bus(g);
	}
	LLDSPEC void gdisp_lld_write_pos(GDisplay *g) {
		set_cursor(g);
	}
#endif

#if GDISP_HARDWARE_STREAM_READ
	LLDSPEC	void gdisp_lld_read_start(GDisplay *g) {
		acquire_bus(g);
		set_viewport(g);
		set_cursor(g);
		setreadmode(g);
		dummy_read(g);
	}
	LLDSPEC	color_t gdisp_lld_read_color(GDisplay *g) {
		uint16_t	data;

		data = read_data(g);
		return gdispNative2Color(data);
	}
	LLDSPEC	void gdisp_lld_read_stop(GDisplay *g) {
		setwritemode(g);
		release_bus(g);
	}
#endif

#if GDISP_NEED_CONTROL && GDISP_HARDWARE_CONTROL
	LLDSPEC void gdisp_lld_control(GDisplay *g) {
		switch(g->p.x) {
		case GDISP_CONTROL_POWER:
			if (g->g.Powermode == (powermode_t)g->p.ptr)
				return;
			switch((powermode_t)g->p.ptr) {
			case powerOff:
				acquire_bus(g);
				write_reg(g, 0x07, 0x0000);
				write_reg(g, 0x10, 0x0000);
				write_reg(g, 0x11, 0x0000);
				write_reg(g, 0x12, 0x0000);
				write_reg(g, 0x13, 0x0000);
				release_bus(g);
				set_backlight(g, 0);
				break;

			case powerOn:
				//*************Power On sequence ******************//
				acquire_bus(g);
				write_reg(g, 0x10, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
				write_reg(g, 0x11, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
				write_reg(g, 0x12, 0x0000); /* VREG1OUT voltage */
				write_reg(g, 0x13, 0x0000); /* VDV[4:0] for VCOM amplitude */
				gfxSleepMilliseconds(200);            /* Dis-charge capacitor power voltage */
				write_reg(g, 0x10, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
				write_reg(g, 0x11, 0x0147); /* DC1[2:0], DC0[2:0], VC[2:0] */
				gfxSleepMilliseconds(50);
				write_reg(g, 0x12, 0x013C); /* VREG1OUT voltage */
				gfxSleepMilliseconds(50);
				write_reg(g, 0x13, 0x0E00); /* VDV[4:0] for VCOM amplitude */
				write_reg(g, 0x29, 0x0009); /* VCM[4:0] for VCOMH */
				gfxSleepMilliseconds(50);
				write_reg(g, 0x07, 0x0173); /* 262K color and display ON */
				release_bus(g);
				set_backlight(g, g->g.Backlight);
				break;

			case powerSleep:
				acquire_bus(g);
				write_reg(g, 0x07, 0x0000); /* display OFF */
				write_reg(g, 0x10, 0x0000); /* SAP, BT[3:0], APE, AP, DSTB, SLP */
				write_reg(g, 0x11, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
				write_reg(g, 0x12, 0x0000); /* VREG1OUT voltage */
				write_reg(g, 0x13, 0x0000); /* VDV[4:0] for VCOM amplitude */
				gfxSleepMilliseconds(200); /* Dis-charge capacitor power voltage */
				write_reg(g, 0x10, 0x0002); /* SAP, BT[3:0], APE, AP, DSTB, SLP */
				release_bus(g);
				gdisp_lld_backlight(g, 0);
				break;

			case powerDeepSleep:
				acquire_bus(g);
				write_reg(g, 0x07, 0x0000); /* display OFF */
				write_reg(g, 0x10, 0x0000); /* SAP, BT[3:0], APE, AP, DSTB, SLP */
				write_reg(g, 0x11, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
				write_reg(g, 0x12, 0x0000); /* VREG1OUT voltage */
				write_reg(g, 0x13, 0x0000); /* VDV[4:0] for VCOM amplitude */
				gfxSleepMilliseconds(200); /* Dis-charge capacitor power voltage */
				write_reg(g, 0x10, 0x0004); /* SAP, BT[3:0], APE, AP, DSTB, SLP */
				release_bus(g);
				gdisp_lld_backlight(g, 0);
				break;

			default:
				return;
			}
			g->g.Powermode = (powermode_t)g->p.ptr;
			return;
			
		case GDISP_CONTROL_ORIENTATION:
			if (g->g.Orientation == (orientation_t)g->p.ptr)
				return;
			switch((orientation_t)g->p.ptr) {
				case GDISP_ROTATE_0:
					acquire_bus(g);
					write_reg(g, 0x01, 0x0100);
					write_reg(g, 0x03, 0x1038);
					write_reg(g, 0x60, 0x2700);
					release_bus(g);
					g->g.Height = GDISP_SCREEN_HEIGHT;
					g->g.Width = GDISP_SCREEN_WIDTH;
					break;

				case GDISP_ROTATE_90:
					acquire_bus(g);
					write_reg(g, 0x01, 0x0000);
					write_reg(g, 0x03, 0x1030);
					write_reg(g, 0x60, 0x2700);
					release_bus(g);
					g->g.Height = GDISP_SCREEN_WIDTH;
					g->g.Width = GDISP_SCREEN_HEIGHT;
					break;

				case GDISP_ROTATE_180:
					acquire_bus(g);
					write_reg(g, 0x01, 0x0000);
					write_reg(g, 0x03, 0x1038);
					write_reg(g, 0x60, 0xa700);
					release_bus(g);
					g->g.Height = GDISP_SCREEN_HEIGHT;
					g->g.Width = GDISP_SCREEN_WIDTH;
					break;
	
				case GDISP_ROTATE_270:
					acquire_bus(g);
					write_reg(g, 0x01, 0x0100);
					write_reg(g, 0x03, 0x1030);
					write_reg(g, 0x60, 0xA700);
					release_bus(g);
					g->g.Height = GDISP_SCREEN_WIDTH;
					g->g.Width = GDISP_SCREEN_HEIGHT;
					break;

				default:
					return;
			}

			g->g.Orientation = (orientation_t)g->p.ptr;
			return;
			
        case GDISP_CONTROL_BACKLIGHT:
            if ((unsigned)g->p.ptr > 100)
            	g->p.ptr = (void *)100;
            set_backlight(g, (unsigned)g->p.ptr);
            g->g.Backlight = (unsigned)g->p.ptr;
            return;
		
		default:
			return;
		}
	}
#endif

#endif /* GFX_USE_GDISP */
