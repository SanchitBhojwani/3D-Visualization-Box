
#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_
#include <stdio.h>

#define MPU6050_ADDR (0x68 << 1)
#define PWR_MGMT_1 0x6B
#define ACCL_START 0X3B

#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C

int mpu_init(void);
int read_raw_data(void);

#endif /* INC_MPU6050_H_ */
