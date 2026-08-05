#ifndef MPU6050_H
#define MPU6050_H

#include <stdint.h>
#include <stm32g4xx_hal.h>

typedef struct{

    I2C_HandleTypeDef *hi2c;

    int16_t acc_x;
    int16_t acc_y;
    int16_t acc_z;

    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;

    int16_t temp;

    float acc_x_g;
    float acc_y_g;
    float acc_z_g;

    float gyro_x_dps;
    float gyro_y_dps;
    float gyro_z_dps;

    float gyro_x_offset;
    float gyro_y_offset;
    float gyro_z_offset;

    float acc_x_offset;
    float acc_y_offset;
    float acc_z_offset;
    
    float angle_x, angle_y, angle_z;
    float angle_acc_x, angle_acc_y, angle_acc_z, acc_vector;
    
} mpu6050;

HAL_StatusTypeDef mpu6050_init( mpu6050 *imu);
HAL_StatusTypeDef accelerometer_init( mpu6050 *imu, uint8_t data);
HAL_StatusTypeDef gyroscope_init( mpu6050 *imu, uint8_t data);
HAL_StatusTypeDef read_sensor_data( mpu6050 *imu);


void calibrate_sensor( mpu6050 *imu);
void convert_dps( mpu6050 *imu);
void convert_g( mpu6050 *imu);
void accelerometer_angles( mpu6050 *imu);
void gyro_angles( mpu6050 *imu, float dt_s);


#endif