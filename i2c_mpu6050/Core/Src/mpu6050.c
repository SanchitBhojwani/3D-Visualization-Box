#include "mpu6050.h"
#include "main.h"
#include <math.h>

extern I2C_HandleTypeDef hi2c2;

uint8_t raw_data[14];

int16_t raw_ax,raw_ay,raw_az;
int16_t raw_gx,raw_gy,raw_gz;

float ax,ay,az;
float gx,gy,gz;

float acc_roll,acc_pitch;
float roll,pitch,yaw;

int mpu_init(void){

	uint8_t wake = 0x00;
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, PWR_MGMT_1, 1, &wake , 1, 100); // to wake up mpu6050

	uint8_t data = 0x00;
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR , ACCEL_CONFIG , 1 , &data , 1 , 100 ); //setting accel measurement range to ±2g

	data = 0x00;
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR , GYRO_CONFIG , 1 , &data , 1 , 100 ); // setting gyro measurement range to ±250°/s

	data = 0x03;
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR , CONFIG , 1 , &data , 1 , 100 ); // reduces high-frequency noise inside sensor DLPF (low-pass filter)

	return 0;
}

int read_raw_data(void){

	HAL_I2C_Mem_Read(&hi2c2, MPU6050_ADDR , ACCL_START , 1 ,raw_data , 14 , 100);
	return 0;
}

int combined_data(void){

	raw_ax = raw_data[0]<<8 | raw_data[1];   //combining both high and low values of ax by using or operation
	raw_ay = raw_data[2]<<8 | raw_data[3];   //combining both high and low values of ay by using or operation
	raw_az = raw_data[4]<<8 | raw_data[5];   //combining both high and low values of az by using or operation

	raw_gx = raw_data[8]<<8 | raw_data[9];   //combining both high and low values of gx by using or operation
	raw_gy = raw_data[10]<<8 | raw_data[11]; //combining both high and low values of gy by using or operation
	raw_gz = raw_data[12]<<8 | raw_data[13]; //combining both high and low values of gz by using or operation

	return 0;
}

int scaled_value(void){

	ax = (float)raw_ax/ACCEL_SCALED_VALUE; //getting values of ax in range of +-2g
	ay = (float)raw_ay/ACCEL_SCALED_VALUE; //getting values of ay in range of +-2g
	az = (float)raw_az/ACCEL_SCALED_VALUE; //getting values of az in range of +-2g

	gx = (float)raw_gx/GYRO_SCALED_VALUE;  //getting values of gx in range of +-250°/s
	gy = (float)raw_gy/GYRO_SCALED_VALUE;  //getting values of gy in range of +-250°/s
	gz = (float)raw_gz/GYRO_SCALED_VALUE;  //getting values of gz in range of +-250°/s

	return 0;
}

int calculate_rpy(void){

	acc_roll  = atan2(ay, az) * 180/M_PI;
	acc_pitch = atan2(-ax, sqrt(ay*ay + az*az)) * 180/M_PI;

	return 0;
}

int filtered_rpy(void){

	static uint32_t last_time = 0;

	uint32_t now = HAL_GetTick(); //time in ms
	float dt;

	if(last_time == 0)
	    dt = 0;
	else
	    dt = (now - last_time) / 1000.0f; //time in s
	last_time = now;
	HAL_Delay(50);

	roll  = 0.98 * (roll + gx * dt) + 0.02 * acc_roll; //formula for calculating roll
	pitch = 0.98 * (pitch + gy * dt) + 0.02 * acc_pitch; //formula for calculating pitch
	yaw = yaw + gz * dt; // formula to calculate yaw

	return 0;
}
