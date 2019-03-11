Overview
========
The Shell Demo application demonstrates to control Leds by commands.

Toolchain supported
===================
- IAR embedded Workbench 7.80.4
- Keil MDK 5.21a
- GCC ARM Embedded 2016-5.4-q3
- Kinetis Development Studio IDE 3.2.0
- MCUXpresso0.8

Hardware requirements
=====================
- Mini USB cable
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
When the example runs successfully, the following message is displayed in the terminal:

~~~~~~~~~~~~~~~~~~~~~
SHELL (build: Jan 25 2016)
Copyright (c) 2015 Freescale Semiconductor

SHELL>> help

"help": Lists all the registered commands

"led arg1 arg2":
 Usage:
    arg1: 1|2|3|4...            Led index
    arg2: on|off                Led status

"exit": Exit program

SHELL>> led 1 on
SHELL>> led 1 off
SHELL>> led 2 on
SHELL>> led 2 off
SHELL>> led 3 on
SHELL>> led 3 off
SHELL>> led 4 on
LED index is wrongs
SHELL>>
~~~~~~~~~~~~~~~~~~~~~
Customization options
=====================

