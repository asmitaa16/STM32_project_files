#ifndef as5600_h
#define as5600_h


#include <stdint.h>
#include <stm32g4xx_hal.h>


typedef struct{
    I2C_HandleTypeDef *hi2c;

    uint16_t raw_angle;
    uint16_t angle;
    uint16_t config;
    uint8_t status_reg;


    uint8_t magnet_detected;
    uint8_t magnet_too_strong;
    uint8_t magnet_too_weak;

    HAL_StatusTypeDef i2c_status;
    HAL_StatusTypeDef sensor_ready;

    float angle_in_degrees;

} as5600;

HAL_StatusTypeDef as5600_init(as5600 *as5600, I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef as5600_config( as5600 *as5600, uint16_t data);
void magnet_detected( as5600 *as5600);
HAL_StatusTypeDef get_raw_angle( as5600 *as5600);
HAL_StatusTypeDef get_angle( as5600 *as5600);
void get_angle_in_degrees( as5600 *as5600);

#endif