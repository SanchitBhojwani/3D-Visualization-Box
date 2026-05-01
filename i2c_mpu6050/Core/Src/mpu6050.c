#include "mpu6050.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c2;

uint8_t raw_data[14];

int mpu_init(void){
	uint8_t wake = 0x00;
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, PWR_MGMT_1, 1, &wake , 1, 100);

	uint8_t data = 0x00;
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR , ACCEL_CONFIG , 1 , &data , 1 , 100 ); //setting accel measurement range to +-2g

	uint8_t data = 0x00;
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR , GYRO_CONFIG , 1 , &data , 1 , 100 ); // setting gyro measurement range to ±250°/s

	uint8_t data = 0x03;
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR , CONFIG , 1 , &data , 1 , 100 ); // reduces high-frequency noise inside sensor DLPF (low-pass filter)

	return 0;
}

int read_raw_data(void){
	HAL_I2C_Mem_Read(&hi2c2, MPU6050_ADDR , ACCL_START , 1 ,&raw_data , 14 , 100);
	return o;
}
