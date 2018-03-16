#include "MyLCD.h"

extern GLCD_FONT GLCD_Font_16x24;

void InitDisplay(void) {
	GLCD_Initialize         ();
  GLCD_SetBackgroundColor (GLCD_COLOR_BLUE);
  GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
  GLCD_ClearScreen        ();
  GLCD_SetFont            (&GLCD_Font_16x24);
}

void Display(void) {
	GLCD_DrawString(0, 4*24, "      Hello!      ");
}
