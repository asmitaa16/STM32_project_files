#include "mpu6050.h"
#include <math.h>


#define MPU6050_ADDR           (0x68 << 1)
#define MPU6050_PWR_MGMT_1     0x6B
#define MPU6050_ACCEL_XOUT_H   0x3B
#define MPU6050_GYRO_XOUT_H    0x43
#define MPU6050_WHO_AM_I       0x75
#define ACCEL_CONFIG           0x1C
#define GYRO_CONFIG            0x1B


#define gyro_500dps 0.0152671756f
#define acc_4g 0.0001220703125f


HAL_StatusTypeDef mpu6050_init( mpu6050 *imu){
    uint8_t data;
    data = 0x00;
    return HAL_I2C_Mem_Write(imu->hi2c, MPU6050_ADDR, MPU6050_PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, &data,
                    1, // 1byte of data
                    100);
}

HAL_StatusTypeDef accelerometer_init( mpu6050 *imu, uint8_t data){
    //data is the range of operation values for accelerometer
    //00- 0x00 for +-2g
    //01- 0x08 for +-4g
    //10- 0x10 for +-8g
    //11- 0x18 for +-16g
    return HAL_I2C_Mem_Write(imu->hi2c, MPU6050_ADDR, ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT, &data, 1,
                        100);
}

HAL_StatusTypeDef gyroscope_init( mpu6050 *imu, uint8_t data){
    //data is the range of operation values for accelerometer
    //00- 0x00 for +-250dps
    //01- 0x08 for +-500dps
    //10- 0x10 for +-1000dps
    //11- 0x18 for +-2000dps
    return HAL_I2C_Mem_Write(imu->hi2c, MPU6050_ADDR, GYRO_CONFIG, I2C_MEMADD_SIZE_8BIT, &data, 1,
                        100);

}

HAL_StatusTypeDef read_sensor_data( mpu6050 *imu){
    uint8_t buffer[14];

    // reading 14bytes of data sequentially starting from memory address 0x3B:
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(imu->hi2c, MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, buffer, 14,
                    100);

    if (status != HAL_OK)
        return status;

    // store the data in their respective variables:
    imu-> acc_x = (buffer[0] << 8) | buffer[1];
    imu-> acc_y = (buffer[2] << 8) | buffer[3];
    imu-> acc_z = (buffer[4] << 8) | buffer[5];
    imu-> temp = (buffer[6] << 8) | buffer[7];
    imu-> gyro_x = (buffer[8] << 8) | buffer[9];
    imu-> gyro_y = (buffer[10] << 8) | buffer[11];
    imu-> gyro_z = (buffer[12] << 8) | buffer[13];

    return HAL_OK;
}


// for initial caibration, choosing 32 bits since we're summing 1000 16bit values
void calibrate_sensor( mpu6050 *imu){
    uint16_t i;
    int32_t gyro_x_cal, gyro_y_cal, gyro_z_cal;
    int32_t acc_x_cal, acc_y_cal, acc_z_cal;

    gyro_x_cal = 0;
    gyro_y_cal = 0;
    gyro_z_cal = 0;

    acc_x_cal = 0;
    acc_y_cal = 0;
    acc_z_cal = 0;

    // take 1000 readings while keeping sensor still to calculate
    // intial offset and adjust readings accordingly
    for (i = 0; i < 1000; i++) {
        read_sensor_data(imu);
        gyro_x_cal += imu-> gyro_x;
        gyro_y_cal += imu-> gyro_y;
        gyro_z_cal += imu-> gyro_z;

        acc_x_cal += imu-> acc_x;
        acc_y_cal += imu-> acc_y;
        acc_z_cal += imu-> acc_z;

        // 250 hz loop
        HAL_Delay(4);
    }

    imu-> gyro_x_offset = (float)gyro_x_cal / 1000.0f;
    imu-> gyro_y_offset = (float)gyro_y_cal / 1000.0f;
    imu-> gyro_z_offset = (float)gyro_z_cal / 1000.0f;

    imu-> acc_x_offset = (float)acc_x_cal / 1000.0f;
    imu-> acc_y_offset = (float)acc_y_cal / 1000.0f;
    imu-> acc_z_offset = (float)acc_z_cal / 1000.0f;
}


void convert_dps( mpu6050 *imu){
    // configured at 500 dps
    // lsb sensitivity = 65.5
    imu-> gyro_x_dps = ((float)imu-> gyro_x - imu-> gyro_x_offset) * gyro_500dps;
    imu-> gyro_y_dps = ((float)imu-> gyro_y - imu-> gyro_y_offset) * gyro_500dps;
    imu-> gyro_z_dps = ((float)imu-> gyro_z - imu-> gyro_z_offset) * gyro_500dps;

}

void convert_g( mpu6050 *imu){
    // configured to 4g
    // lsb sensitivity = 8192
    // 0.0001220703125
    imu-> acc_x_g = ((float)imu-> acc_x - imu-> acc_x_offset) * acc_4g;
    imu-> acc_y_g = ((float)imu-> acc_y - imu-> acc_y_offset) * acc_4g;
    // acc_z_g = ((float)acc_z - acc_z_offset) * acc_4g;
    imu-> acc_z_g = (float)imu-> acc_z * acc_4g;
}

void accelerometer_angles( mpu6050 *imu){
    // let's now do stuff with the accn:
  imu-> acc_vector =
      sqrt((imu-> acc_x_g * imu-> acc_x_g) + (imu-> acc_y_g * imu-> acc_y_g) + (imu-> acc_z_g * imu-> acc_z_g));

  imu-> angle_acc_y = asin(imu-> acc_y_g / imu-> acc_vector) * 57.296f;

  // Calculate the roll angle
  imu-> angle_acc_x = asin((float)imu-> acc_x_g / imu-> acc_vector) * -57.296f;

}

void gyro_angles( mpu6050 *imu, float dt_s){
    (imu-> angle_x) += imu-> gyro_x_dps * dt_s;
    (imu-> angle_y) += imu-> gyro_y_dps * dt_s;
    (imu-> angle_z) += imu-> gyro_z_dps * dt_s;
}

