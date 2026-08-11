### Open loop sinusoidal PWM control for Burshless DC motor

The libraries written is this code use code from the AS5600 sensor library from this repo. 
The code generates a rotating magnetic field around the stator coils which the rotor keeps trying to align itself into and in doing so, rotates in a circle.

The hardware consists of:
- STM32 Nucleo G491RET6 board
- SimpleFOCmini v1.0 motor driver based on DRV8313
- AS5600 absolute magnetic encoder (not used in this case)
- General tools

The 3 PWM inputs are generated from timer 1 while timer 2 is used to run a hardware interrupt to
update the electrical angle theta at a frequency of 2kHz. You can change this frequency by playing around with the timer 2 parameters in the  MX_TIM2_Init() function. Keep it low enough for rotor to actually be able to follow otherwise it'll just vibrate.

