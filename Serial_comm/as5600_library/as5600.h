#ifndef as5600_h
#define as5600_h


#include <stdint.h>
#include <stm32g4xx_hal.h>


typedef struct{
    I2C_HandleTypeDef *hi2c;

    uint16_t raw_angle;
    uint16_t angle;
    uint16_t config;
    uint16_t status;

    uint8_t magnet_detected;
    uint8_t magnet_too_strong;
    uint8_t magnet_too_weak;

    float angle_in_degrees;

} as5600;


HAL_StatusTypeDef as5600_config( as5600 *as5600);
void magnet_detected( as5600 *as5600);
HAL_StatusTypeDef get_raw_angle( as5600 *as5600);
HAL_StatusTypeDef get_angle( as5600 *as5600);
void get_angle_in_degrees( as5600 *as5600);

#endif