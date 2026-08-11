### Brushless DC motor drive

A really cool way that got me writing so much of code with a lot of debugging! Brushless motors are cool, because unlike DC motors you can't just drive them with direct power supply and a motor driver.
The absence of brushes means the commutation is completely done with the electronics and you decide which coilss to energise in what order to move the rotor in the desired way!

Now you use ESCs for controlling your drone BLDCs but they're not really efficient in terms of power or slow speed operations with accuracy and there enters a lot of other fun algorithms!

These projects are compiled and tested on the STM32 Nucleo G491ReT6 board and SimpleFOCmini v1.0 3-phase motor driver. I'm trying to fabriate a board I had designed around the DRV8316 but sourcing all the components is time-consuming. 

Look through the pages to dive into different commutation techniques to get your BLDC moving!

