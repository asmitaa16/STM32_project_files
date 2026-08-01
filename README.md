# STM32 fun codes

Hi! I'm teaching myself low-level stuff with my bluepill and it's my repo of all the stuff I do, enjoy!

## Topics
- GPIO (start from blinky here)
- Interrupts (external and timer)
- Timers (pwm and other cool stuff)
- Serial Communication stuff (this one's got some cool sensors)
- Motor control (woahhhh)

## My setup
As simple and hobbyist as it could be- and the best thing? Completely affordable :)

The primary MCU is an STM32F103C8Tx, in a cheap Bluepill (150ish INR) board that I program and debug with a ST-Link V2 clone (the blue/red ones). I write my code in VS CODE with
STM32CubeIDE extension and use it for building my projects and generating executable files (.elf files, to be precise). I tried changing the debugger to OpenOCD
vs GDB and modify config file settings to bypass
the device ID check for using my clone, but couldn't make it work (appreciate any help on that!). I installed STM32CubeProgrammer and it seemed to detect the ST-Link
(thank goodness, haha) and I can flash my bluepill from there with the generated .elf files and for debugging used UART messages and read them on Arduino Serial Monitor
and occasionally blinking leds (works good enough for pwm stuff, loll). But STM32 boards being the powerful ones they are, even this lil bluepill has a maximum 
clock frequency of 72 MHz. So, I invested a bit more and got myself an USB Logic Analyser (again a clone- 24MHz, 8 channel) and using it with a Logic analyser software - trust me,
it's a lifesaver!

So, the workflow is:

Assign pins and select clock configuration on CubeMX -> Code in VS code -> Build and generate elf files -> Burn using CubeProgrammer -> Use logic analyser for 
debugging!


