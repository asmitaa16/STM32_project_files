### Open loop sinusoidal PWM control for Burshless DC motor

The libraries written is this code use code from the AS5600 sensor library from folder Serial_comm/as5600_library. The motor driver controlling code is written in spwm.h and spwm.c 

The code generates a rotating magnetic field around the stator coils which the rotor keeps trying to align itself into and in doing so, rotates in a circle.

The 3 PWM inputs are generated from timer 1 while timer 2 is used to run a hardware interrupt to
update the electrical angle theta at a frequency of 2kHz. You can change this frequency by playing around with the timer 2 parameters in the  MX_TIM2_Init() function. Keep it low enough for rotor to actually be able to follow otherwise it'll just vibrate about its mean position. Open-loop speed control can be achieved by controlling loop speeds and rate of change of electrical angle theta. 

