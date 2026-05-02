
#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_
#include <stdio.h>

#define MPU6050_ADDR (0x68 << 1)
#define PWR_MGMT_1 0x6B
#define ACCL_START 0X3B

#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C

#define ACCEL_SCALED_VALUE 16384
#define GYRO_SCALED_VALUE 131
#define M_PI 3.14159265358979323846

int mpu_init(void);
int read_raw_data(void);
int combined_data(void);
int scaled_value(void);
int calculate_rpy(void);
int filtered_rpy(void);

#endif /* INC_MPU6050_H_ */
