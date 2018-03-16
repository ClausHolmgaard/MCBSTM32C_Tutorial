#include <stdio.h>
#include "cmsis_os.h"

#include "MyLCD.h"

#include "Board_GLCD.h"
#include "GLCD_Config.h"

extern GLCD_FONT GLCD_Font_16x24;

void InitDisplay(void) {
	printf("Init display\r\n");
	GLCD_Initialize         ();
  GLCD_SetBackgroundColor (GLCD_COLOR_BLUE);
  GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
  GLCD_ClearScreen        ();
  GLCD_SetFont            (&GLCD_Font_16x24);
}

int main(void) {
	
	InitDisplay();
	printf("Testing\r\n");

	while(1);
}
