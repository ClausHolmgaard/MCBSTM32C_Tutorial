#include "MyAccelerometer.h"

void I2C_Initialize(void) {
	ptrI2C->Initialize(NULL);
	ptrI2C->PowerControl(ARM_POWER_FULL);
  ptrI2C->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);
  ptrI2C->Control(ARM_I2C_BUS_CLEAR, 0);

	I2C_WriteBuf(CTRL_REG1, 0x47);
}

int32_t I2C_WriteBuf (uint8_t reg, uint8_t val) {
  uint8_t data[2];

  data[0] = reg;
  data[1] = val;
  ptrI2C->MasterTransmit(ACCELEROMETER_ADDR, data, 2, false);
  while (ptrI2C->GetStatus().busy);
  if (ptrI2C->GetDataCount() != 2) return -1;

  return 0;
}

int32_t I2C_ReadBuf (uint32_t addr, uint8_t *buf, uint32_t len) {
	uint8_t a[1];
	
	uint32_t I2CAddr = ACCELEROMETER_ADDR;
	
	int32_t transmit_request_status;
	int32_t transmit2_receive_status;
	int32_t data_count;
	
	a[0] = (uint8_t)addr;
	
  transmit_request_status = ptrI2C->MasterTransmit(I2CAddr, a, 1, true);
	if(transmit_request_status != 0) {
		return -1;
	}

	while(ptrI2C->GetStatus().busy);
	transmit2_receive_status = ptrI2C->MasterReceive(I2CAddr, buf, len, false);
	if(transmit2_receive_status != 0) {
		return -1;
	}

  while(ptrI2C->GetStatus().busy);
	data_count = ptrI2C->GetDataCount();
  if(data_count != len) {
		return -1;
	}

  return 0;
}

int32_t Accelerometer_GetState (ACCELEROMETER_STATE *pState) {
  uint8_t val;

	int8_t x;
	int8_t y;
	int8_t z;
	
  I2C_ReadBuf(OUT_X, &val, 1);
	x = (int8_t)val;
  
  I2C_ReadBuf(OUT_Y, &val, 1);
	y = (int8_t)val;

  I2C_ReadBuf(OUT_Z, &val, 1);
	z = (int8_t)val;

	pState->x = x;
	pState->y = y;
	pState->z = z;
	
  return 0;
}

void I2CHandler(void const *arg) {
	uint8_t val;
	uint32_t rec_status;
	ACCELEROMETER_STATE acc;

	rec_status = I2C_ReadBuf(0x0F, &val, 1);
	printf("Receive status: %d\r\n", rec_status);
	printf("Val: 0x%02X\r\n", val);
	
	while(1) {
		Accelerometer_GetState(&acc);
		printf("Acc X = %d\r\n", acc.x);
		printf("Acc Y = %d\r\n", acc.y);
		printf("Acc Z = %d\r\n", acc.z);
		printf("\r\n");
		
		osDelay(100);
	}
}
