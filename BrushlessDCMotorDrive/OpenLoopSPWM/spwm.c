#include "spwm.h"
#include "as5600.h"
#include "stm32g491xx.h"
#include "math.h"
#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_gpio.h"

#include "stdio.h"
#include <stdint.h>


#define PI              3.14159265358979323846f
#define pole_pairs      14
#define pwm_resolution  512
#define mod_index       0.05f

as5600 sensor;

//all the calculations done over with raw_angle measurement
//i.e. 12bit reading from sensor.

//using timer2 for generating hardware timer interrupt;
void driver_init(bldcMotorDriver *driver, TIM_TypeDef *pwm_timer, TIM_HandleTypeDef *htim, 
    I2C_HandleTypeDef *hi2c, uint32_t ch_a, uint32_t ch_b, uint32_t ch_c,
    GPIO_TypeDef *GPIOx, uint16_t GPIO_En_Pin
    ){

    driver->timer = pwm_timer;
    driver-> htim = htim;
    driver-> in1 = 0;
    driver-> in2 = 0;
    driver-> in3 = 0;
    driver-> poles = pole_pairs;
    driver-> theta_electrical = 0;
    driver-> theta_mechanical = 0;
    driver-> theta_offset = 0;

    //set duty cyles (value of CCRx registers) to 0
    driver-> timer-> CCR1 = 0;
    driver-> timer-> CCR2 = 0;
    driver-> timer-> CCR3 = 0;

    //set timer channels
    driver->ch_a = ch_a;
    driver->ch_b = ch_b;
    driver->ch_c = ch_c;
    
    //set motor driver enable pin
    driver->GPIOx = GPIOx;
    driver->GPIO_En_Pin = GPIO_En_Pin;
    HAL_GPIO_WritePin(driver->GPIOx, driver-> GPIO_En_Pin, 1);

    //start timers
    HAL_TIM_PWM_Start(driver->htim, driver-> ch_a);
    HAL_TIM_PWM_Start(driver->htim, driver-> ch_b);
    HAL_TIM_PWM_Start(driver->htim, driver-> ch_c);

    
    initialise sensor
    driver->sensor_ok = as5600_init(&sensor, hi2c);
    as5600_config(&sensor, 0xEE4);

}


void set_pwm(bldcMotorDriver *driver, uint32_t duty_a, uint32_t duty_b, uint32_t duty_c){
    driver->timer->CCR1 = duty_a;
    driver->timer->CCR2 = duty_b;
    driver->timer->CCR3 = duty_c;
}

//put input theta in radians:
void spin_motor(bldcMotorDriver *driver, float theta){

    float theta_a, theta_b, theta_c;

    theta_a = theta;
    theta_b = theta_a + 2.0f * PI / 3.0f;
    theta_c = theta_a - 2.0f * PI / 3.0f;

    theta_a = fmodf(theta_a, 2.0f * PI);
    theta_b = fmodf(theta_b, 2.0f * PI);
    theta_c = fmodf(theta_c, 2.0f * PI);

    float sin_a, sin_b, sin_c;

    //calculate sinusoid values
    sin_a = ((mod_index * sinf(theta_a) + 1)* 0.5f) * pwm_resolution;
    sin_b = ((mod_index * sinf(theta_b) + 1)* 0.5f) * pwm_resolution;
    sin_c = ((mod_index * sinf(theta_c) + 1)* 0.5f) * pwm_resolution;

    set_pwm(driver, sin_a, sin_b, sin_c);
}


void get_offset(bldcMotorDriver *driver){
    //needs to measure the initial angle of the rotor from absolute encoder

    get_raw_angle(&sensor);
    driver-> theta_offset = sensor.raw_angle;
}


//only getting raw angle here (that's the fastest!), do the processing later on in code
//remove any printf statements if it's gonna be used in the main loop
uint16_t get_sensor_angle(bldcMotorDriver *driver){
    get_raw_angle(&sensor);
    //printf("Angle: %d\r\n", sensor.raw_angle);
    return sensor.raw_angle;
}
