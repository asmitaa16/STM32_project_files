# STM32 Serial Communication

Custom STM32 HAL-based drivers.

## Libraries

### AS5600
Driver for the AS5600 12-bit absolute magnetic rotary encoder.

### MPU6050
Driver for the MPU6050 6-axis IMU (Accelerometer and Gyroscope)

## Communication

Both libraries use:

- I2C
- STM32 HAL

## Useful tip - Setting up `printf` debugging:
It is really helpful to debug your code using some print statements. But it's not really easy to get them show up on the
serial monitor. You gotta configure UART peripherals and transmit. Most nucleo boards have one of their UART peripherals directly linked with the onboard st-link and it shows up as Virtual COM Port when you connect it. You can communicate to your pc via that, using these steps:

- add this function to "main.c"
Replace `hlpuart1` with the UART peripheral your st-link uses or the one you have connected your UART-USB converter to. This function redirects `printf()` to UART. 

```c
int _write(int file, char *ptr, int len) {
  HAL_UART_Transmit(&hlpuart1, (uint8_t *)ptr, len, HAL_MAX_DELAY);
  return len;  
}
```

- add this to CMakeLists.txt, after the `add executables()`- line if you're gonna print float values

```cmake
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -u _printf_float
)
```
Now we're good to go. Oh, don't forget to include "stdio.h" !

