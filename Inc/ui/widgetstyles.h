#ifndef _WIDGET_STYLES_H
#define _WIDGET_STYLES_H

#include "gfx.h"

// WidgetStyle: White
const GWidgetStyle white = {
	HTML2COLOR(0xFFFFFF),              // background
	HTML2COLOR(0x2A8FCD),              // focus

	// Enabled color set
	{
		HTML2COLOR(0x000000),         // text
		HTML2COLOR(0x404040),         // edge
		HTML2COLOR(0xE0E0E0),         // fill
		HTML2COLOR(0x00E000),         // progress (inactive area)
	},

	// Disabled color set
	{
		HTML2COLOR(0xC0C0C0),         // text
		HTML2COLOR(0x808080),         // edge
		HTML2COLOR(0xE0E0E0),         // fill
		HTML2COLOR(0xC0E0C0),         // progress (active area)
	},

	// Pressed color set
	{
		HTML2COLOR(0x404040),         // text
		HTML2COLOR(0x404040),         // edge
		HTML2COLOR(0x808080),         // fill
		HTML2COLOR(0x00E000),         // progress (active area)
	}
};

// WidgetStyle: Black
const GWidgetStyle black = {
	HTML2COLOR(0x000000),              // background
	HTML2COLOR(0x2a8fcd),              // focus

	// Enabled color set
	{
		HTML2COLOR(0xC0C0C0),         // text
		HTML2COLOR(0xC0C0C0),         // edge
		HTML2COLOR(0x606060),         // fill
		HTML2COLOR(0x008000),         // progress (inactive area)
	},

	// Disabled color set
	{
		HTML2COLOR(0x808080),         // text
		HTML2COLOR(0x404040),         // edge
		HTML2COLOR(0x404040),         // fill
		HTML2COLOR(0x004000),         // progress (active area)
	},

	// Pressed color set
	{
		HTML2COLOR(0xFFFFFF),         // text
		HTML2COLOR(0xC0C0C0),         // edge
		HTML2COLOR(0xE0E0E0),         // fill
		HTML2COLOR(0x008000),         // progress (active area)
	}
};

// WidgetStyle: X
const GWidgetStyle x = {
	HTML2COLOR(0x00007f),              // background
	HTML2COLOR(0x2a8fcd),              // focus

	// Enabled color set
	{
		HTML2COLOR(0x00ffff),         // text
		HTML2COLOR(0x00007f),         // edge
		HTML2COLOR(0x00007f),         // fill
		HTML2COLOR(0x000000),         // progress (inactive area)
	},

	// Disabled color set
	{
		HTML2COLOR(0x000000),         // text
		HTML2COLOR(0x000000),         // edge
		HTML2COLOR(0x000000),         // fill
		HTML2COLOR(0x000000),         // progress (active area)
	},

	// Pressed color set
	{
		HTML2COLOR(0x00ffff),         // text
		HTML2COLOR(0x00007f),         // edge
		HTML2COLOR(0x000000),         // fill
		HTML2COLOR(0x000000),         // progress (active area)
	}
};

// WidgetStyle: Y
const GWidgetStyle y = {
	HTML2COLOR(0x005500),              // background
	HTML2COLOR(0x2a8fcd),              // focus

	// Enabled color set
	{
		HTML2COLOR(0xaaff00),         // text
		HTML2COLOR(0x005500),         // edge
		HTML2COLOR(0x005500),         // fill
		HTML2COLOR(0x000000),         // progress (inactive area)
	},

	// Disabled color set
	{
		HTML2COLOR(0x000000),         // text
		HTML2COLOR(0x000000),         // edge
		HTML2COLOR(0x000000),         // fill
		HTML2COLOR(0x000000),         // progress (active area)
	},

	// Pressed color set
	{
		HTML2COLOR(0x000000),         // text
		HTML2COLOR(0x000000),         // edge
		HTML2COLOR(0x000000),         // fill
		HTML2COLOR(0x000000),         // progress (active area)
	}
};

// WidgetStyle: Trg
const GWidgetStyle trg = {
	HTML2COLOR(0x005500),              // background
	HTML2COLOR(0x2a8fcd),              // focus

	// Enabled color set
	{
		HTML2COLOR(0xff0000),         // text
		HTML2COLOR(0x005500),         // edge
		HTML2COLOR(0x005500),         // fill
		HTML2COLOR(0x000000),         // progress (inactive area)
	},

	// Disabled color set
	{
		HTML2COLOR(0x000000),         // text
		HTML2COLOR(0x000000),         // edge
		HTML2COLOR(0x000000),         // fill
		HTML2COLOR(0x000000),         // progress (active area)
	},

	// Pressed color set
	{
		HTML2COLOR(0x000000),         // text
		HTML2COLOR(0x000000),         // edge
		HTML2COLOR(0x000000),         // fill
		HTML2COLOR(0x000000),         // progress (active area)
	}
};

// WidgetStyle: DivC
const GWidgetStyle divc = {
	HTML2COLOR(0x00ffff),              // background
	HTML2COLOR(0x2a8fcd),              // focus

	// Enabled color set
	{
		HTML2COLOR(0x00007f),         // text
		HTML2COLOR(0x00ffff),         // edge
		HTML2COLOR(0x00ffff),         // fill
		HTML2COLOR(0x000000),         // progress (inactive area)
	},

	// Disabled color set
	{
		HTML2COLOR(0x000000),         // text
		HTML2COLOR(0x000000),         // edge
		HTML2COLOR(0x000000),         // fill
		HTML2COLOR(0x000000),         // progress (active area)
	},

	// Pressed color set
	{
		HTML2COLOR(0x00007f),         // text
		HTML2COLOR(0xaaff7f),         // edge
		HTML2COLOR(0xaaff7f),         // fill
		HTML2COLOR(0x000000),         // progress (active area)
	}
};


#endif /* _WIDGET_STYLES_H */

