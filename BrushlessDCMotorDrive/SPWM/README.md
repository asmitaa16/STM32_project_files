### Sinusoidal PWM Control
This control scheme makes use of Pulse-Width-Modulated signals with sinusoidally varying duty cycles for driving the 3-phase inverter inputs to the BLDC motor. 

spwm.h contains the motor driver parameters and spwm.c contains the driver functions. The PWM switching frequency is currently set to 25kHz and runs on 9-bit resolution (don't ask me why, my clock's set to 128Mhz and well, this is how it is). 
For closed-loop operation, the sensor configuration can be found at Serial_Comm/as5600_library. 

A few problems I encountered (and how I solved them!):
- For reading rotor position you'll have to attach an axial magnet to the exposed shaft.
- The sensor as5600, used for reading the magnet that rotates with the shaft, has a range of some 0.5-2.5mm so you'll have to print a mount for holding the sensor. 
- While reading data from i2c lines, there's a lot of electrical noise interference due to the motor's rotating magnetic field. So the i2c lines get corrupted and you won't be able to read it. To solve this issue
  - try to keep the motor driver wires and sensor wires physically far from each other while connecting to your Microcontroller.
  - tie up the SDA and SCL lines with GND wires and twist them, improves return paths and makes it robust to EM interferences.
  - solder a decoupling capacitor of 100nF near the sensor power pins and 1uF bulk capacitor (if required).

These approaches should solve the issue.

Have a look at my setup here-

![My setup](setup.png)