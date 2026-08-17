#ifndef spwm_h
#define spwm_h

#include <stdint.h>
#include <stm32g4xx_hal.h>


typedef struct{

    TIM_TypeDef *timer;
    TIM_HandleTypeDef *htim;

    uint8_t poles;

    float theta_electrical;
    float theta_mechanical;
    float theta_offset;

    //pwm channgels- motor driver output
    uint32_t ch_a;
    uint32_t ch_b;
    uint32_t ch_c;

    HAL_StatusTypeDef sensor_ok;

    //motor driver enable pins
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_En_Pin;


} bldcMotorDriver;


void driver_init(bldcMotorDriver *driver, TIM_TypeDef *pwm_timer, TIM_HandleTypeDef *htim, 
    I2C_HandleTypeDef *hi2c, uint32_t ch_a, uint32_t ch_b, uint32_t ch_c,
    GPIO_TypeDef *GPIOx, uint16_t GPIO_En_Pin
    );
void get_offset(bldcMotorDriver *driver);
void spin_motor(bldcMotorDriver *driver, float theta);

void set_pwm(bldcMotorDriver *driver, uint32_t duty_a, uint32_t duty_b, uint32_t duty_c);

uint16_t get_sensor_angle(bldcMotorDriver *driver);


#endif