## AS5600
Driver for the AS5600 magnetic rotary encoder.

### Structure
- as5600.h -> sensor structure and function declarations
- as5600.c -> register declarations and function definitions

### Stuff I noticed:
- Currently I have tested my code while using the Fast filter (threshold = 9 LSB), it smoothens readings but becomes slow.
Specially around the jump from 4095->0 after a complete rotation. In the get_angles_in_degrees() function, set bypass=1
to use the raw_angle for subsequent calculations and bypass the filtered value stored in the angle register.
