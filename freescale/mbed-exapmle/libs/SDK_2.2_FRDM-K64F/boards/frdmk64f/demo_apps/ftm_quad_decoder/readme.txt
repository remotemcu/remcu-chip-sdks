Overview
========
This demo describes the usage of Quad Decoder feature in FTM module, which can be used to count the position of decoder.

An external decoder is used to generate the PHA and PHB's signal. These two signals are feed to the FTM pins with Quad Decoder feature (FTMx_QD_PHA and FTMx_QD_PHB). Then, the counter value and direction would be displayed in terminal window predically.


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
- Encoder with PHA and PHB singal.

Board settings
==============
1. Connect the "J1-1" (PTB18, FTM2_QD_PHA) to encoder's PHA singal.
2. Connect the "J1-3" (PTB19, FTM2_QD_PHB) to encoder's PHB singal.

Prepare the Demo
================
1. Connect a USB cable between the PC host and the OpenSDA USB port on the board.
2. Connect the board with encoder.
3. Open a serial terminal with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
4. Download the program to the target board.
5. Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================
Scroll forward and backword the encoder and watch the log on the terminal window:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

FTM quad decoder example
Encoder direction: -
Get current counter: 0
Encoder direction: -
Get current counter: 0
Encoder direction: -
Get current counter: 0
Encoder direction: -
Get current counter: 0
Encoder direction: -
Get current counter: 0
Encoder direction: -
Get current counter: 1995
Encoder direction: +
Get current counter: 1998
Encoder direction: +
Get current counter: 11
Encoder direction: +
Get current counter: 7
Encoder direction: +
Get current counter: 13
Encoder direction: +
Get current counter: 0
Encoder direction: +
Get current counter: 0
Encoder direction: +
Get current counter: 0
Encoder direction: -
Get current counter: 1995

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Customization options
=====================

