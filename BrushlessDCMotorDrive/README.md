### Brushless DC motor drive

A really cool project that got me writing so much of code with a lot of debugging! These files are on the tougher side and include the use of a lot of programming concepts that are written up in the other files. I suggest you to go through them first and then dive into BLDCs.

Brushless motors are tough to control, because unlike DC motors you can't just drive them with direct power supply and a motor driver. The absence of brushes means the commutation is completely done with the electronics and you decide which coils to energise in what order to move the rotor in the desired way!

Now you use ESCs for controlling your drone BLDCs but they're not really efficient in terms of power or slow speed operations with accuracy and there enters a lot of other fun algorithms!

The hardware in all of the projects in this folder consists of:
- STM32 Nucleo G491RET6 board
- 2208 80 KV Gimbal Motor (14poles)
- SimpleFOCmini v1.0 motor driver based on DRV8313
- AS5600 absolute magnetic encoder
- DSO, Bench Power supply
- General tools

Look through the pages to dive into different commutation techniques to get your BLDC moving!

