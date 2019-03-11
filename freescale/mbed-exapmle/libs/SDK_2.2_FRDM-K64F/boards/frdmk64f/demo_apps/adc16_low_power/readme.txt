Overview
========
The ADC Low Power demo application demonstrates the usage of the ADC peripheral while in a low power mode. The
microcontroller is first set to very low power stop (VLPS) mode. Every 500 ms, an interrupt wakes up the ADC module and
reads the current temperature of the microcontroller. While the temperature remains within boundaries, both LEDs are on.
If the core temperature is higher or lower than average, the LEDs change state respectively.

Toolchain supported
===================
- IAR embedded Workbench 7.80.4
- Keil MDK 5.21a
- GCC ARM Embedded 2016-5.4-q3
- Kinetis Development Studio IDE 3.2.0
- MCUXpresso0.8

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K64F board
- Personal Computer

Board settings
==============
No special settings are required.

Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board.
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ADC LOW POWER DEMO
 The Low Power ADC project is designed to work with the Tower System or in a stand alone setting
 1. Set your target board in a place where the temperature is constant.
 2. Wait until two Led light turns on.
 3. Increment or decrement the temperature to see the changes.
 Wait two led on...

 Enter any character to begin...

 ---> OK! Main process is running...!

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Note:
 - when the temperature is above the average: LED RED on, LED GREEN off.
 - when the temperature is below the average: LED GREEN on, LED RED off.
Customization options
=====================

