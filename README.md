# STM32 codes

Hi! I'm teaching myself low-level stuff with my bluepill and it's my repo of all the stuff I've done !

## Topics
- GPIO 
- Interrupts (external hardware and timer)
- Timers (pwm and servo control)
- Serial Communication  (Libraries for MPU6050 and AS5600 sensors)
- BrushlessDC motor drive project

## My setup

The primary MCU is an STM32F103C8Tx, in a Bluepill board that I program and debug with a ST-Link V2. I write my code in VS CODE with
STM32CubeIDE extension and use it for building my projects and generating executable files (.elf files, to be precise). The projects are built on the CubeMX boilerplate provided after configuring the pins , clock speeds and any other functionalities I wish to include in my project,  such as interrupts, Serial communication etc. 
