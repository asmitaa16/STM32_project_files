#include "as5600.h"

#define ADDR            (0X36 << 1)
#define CONF_UPPER_BITS 0x07
#define CONF_LOWER_BITS 0x08
#define RAW_ANGLE_UPPER 0X0C
#define RAW_ANGLE_LOWER 0X0D
#define ANGLE_UPPER     0X0E
#define ANGLE_LOWER     0X0F
#define STATUS          0X0B

#define RAW_TO_DEGREES  0.087890625f

HAL_StatusTypeDef as5600_config( as5600 *as5600){
    uint16_t data;
    data = 0xE04;
    return HAL_I2C_Mem_Write(as5600->hi2c, ADDR, CONF_UPPER_BITS, I2C_MEMADD_SIZE_8BIT, &data,
                    2, // 1byte of data
                    100);
}


void magnet_detected( as5600 *as5600){
    HAL_I2C_Mem_Read(as5600->hi2c,ADDR, STATUS, I2C_MEMADD_SIZE_8BIT, as5600->status, 1,
                    100);

    if (as5600-> status && (1<<5) ){
        as5600 -> magnet_detected = 1;
    }

    if (as5600-> status && (1<<4)){
        as5600 -> magnet_too_strong =1;
    }

    if (as5600-> status && (1<<3)){
        as5600-> magnet_too_weak =1 ;
    }
}


HAL_StatusTypeDef get_raw_angle( as5600 *as5600){
    uint8_t buffer[2];
     HAL_StatusTypeDef status = HAL_I2C_Mem_Read(as5600->hi2c,ADDR, RAW_ANGLE_UPPER , I2C_MEMADD_SIZE_8BIT, buffer, 2,
                    100);
    if(status != HAL_OK){
        return status;
    }
    as5600-> raw_angle = (buffer[0]<<8) | buffer[1];

}


HAL_StatusTypeDef get_angle( as5600 *as5600){
    uint8_t buffer[2];
     HAL_StatusTypeDef status = HAL_I2C_Mem_Read(as5600->hi2c,ADDR, ANGLE_UPPER , I2C_MEMADD_SIZE_8BIT, buffer, 2,
                    100);
    if(status != HAL_OK){
        return status;
    }
    as5600-> angle = (buffer[0]<<8) | buffer[1];


}

void get_angle_in_degrees( as5600 *as5600){
    as5600->angle_in_degrees = (float)as5600->angle * RAW_TO_DEGREES;

}

