#include <stdio.h>
#include "cmsis_os.h"

#include "MyLCD.h"
#include "MyAccelerometer.h"

osThreadId TID_Accelerometer;

osThreadDef(I2CHandler, osPriorityNormal, 1, 0);

int main(void) {
	
	InitDisplay();
	I2C_Initialize();
	
	Display();
	
	TID_Accelerometer = osThreadCreate(osThread(I2CHandler), NULL);
	
	while(1);
}
