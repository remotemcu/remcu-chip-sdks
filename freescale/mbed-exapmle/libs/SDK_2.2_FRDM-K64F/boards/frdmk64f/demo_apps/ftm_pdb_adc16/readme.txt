Overview
========

The FTM / PDB demo application demonstrates how to use the FTM external trigger to start the ADC conversion using the
PDB. FTM0 is configured as a complementary combined mode, and each channel output frequency is 16 KHz. The complementary
channel dead time is 1 µs. The PDB pre-trigger works in back-to-back mode. The ADC0 and ADC1 work in single-end mode.
The ADC0 uses channel 1 and channel 5, and ADC1 uses channel 1 and channel 7.

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
- FRDM-K64F
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
The ADC PDB demo application will print the following message to the terminal:

~~~~~~~~~~~~~~~~~
Run pdb trig adc with flextimer demo.
Input any character to start demo.
~~~~~~~~~~~~~~~~~~
Input a character to the serial console to start the ADC PDB demo.
The demo will then display 256 lines of information for the ADC conversion result.
Customization options
=====================

