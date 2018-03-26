#include <stdio.h>
#include "Driver_I2C.h"
#include "cmsis_os.h"

#ifndef __ACCELEROMETER_H
#define __ACCELEROMETER_H

typedef struct _ACCELEROMETER_STATE {
  int8_t x;
  int8_t y;
  int8_t z;
} ACCELEROMETER_STATE;

#define ACCELEROMETER_ADDR 			0x1C

#define CTRL_REG1             	0x20
#define OUT_X                 	0x29
#define OUT_Y                 	0x2B
#define OUT_Z                 	0x2D

#ifndef ACCELEROMETER_I2C_PORT
#define ACCELEROMETER_I2C_PORT 	1
#endif

#define _I2C_Driver_(n)  Driver_I2C##n
#define  I2C_Driver_(n)  _I2C_Driver_(n)
extern ARM_DRIVER_I2C    I2C_Driver_(ACCELEROMETER_I2C_PORT);
#define ptrI2C           (&I2C_Driver_(ACCELEROMETER_I2C_PORT))

void I2C_Initialize (void);
int32_t I2C_ReadBuf (uint32_t addr, uint8_t *buf, uint32_t len);
int32_t I2C_WriteBuf (uint8_t reg, uint8_t val);
int32_t Accelerometer_GetState (ACCELEROMETER_STATE *pState);
void I2CHandler(void const *arg);

#endif
