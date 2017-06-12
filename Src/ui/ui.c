
#include "gfx.h"
#include "ui.h"

#include "gdisp.h"
#include "gui.h"
#include "gdriver.h"
#include "ginput_mouse.h"
#include "ginput_driver_mouse.h"
#include <string.h>

/*  screeen disp coordinate
         __________
    (0,0)          (320,0)
    |                   |
    |                   |
    (0,240)________(320,240)
*/


void UserInterface()
{

  gfxInit();
//ginputCalibrateMouse(0);


  gdispSetBacklight(100);
  gdispSetContrast(100);

  geventListenerInit(&glistener);
  gwinAttachListener(&glistener);

  guiCreate();




  while (1) {
    guiEventLoop();
  }
}