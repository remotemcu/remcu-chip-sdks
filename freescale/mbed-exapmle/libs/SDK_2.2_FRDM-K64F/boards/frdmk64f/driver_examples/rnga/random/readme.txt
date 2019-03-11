Overview
========
The RNGA is a digital integrated circuit capable of generating the 32-bit random numbers. The RNGA
Example project is a demonstration program that uses the KSDK software to generate random numbers
and prints them to the terminal.


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
This Example project does not call for any special hardware configurations.
Although not required, the recommendation is to leave the development board's jumper settings
and configurations in default state when running this example.
Prepare the Demo
================
Connect a serial cable from the debug UART port of the board to the PC. Start Tera Term
(http://ttssh2.osdn.jp) and make a connection to the virtual serial port.

1. Start Tera Term
2. New connection -> Serial
3. Set apropriate COMx port (x is port number) in Port context menu. Number is provided by operation
   system and could be different from computer to computer. Select COM number related to virtual
   serial port. Confirm selected port by OK button.
4. Set following connection parameters in menu Setup->Serial port...
        Baud rate:    115200
        Data:         8
        Parity:       none
        Stop:         1
        Flow control: one
5.  Confirm selected parameters by OK button.

Running the demo
================
When the demo runs successfully, from the terminal you can see:

RNGA Peripheral Driver Example
Generate 10 random numbers:
Random[0] = 0xE1554295
Random[1] = 0x827AD456
Random[2] = 0x9A1CBE1E
Random[3] = 0x4354CB53
Random[4] = 0xFE3B2494
Random[5] = 0xEDAB3F7D
Random[6] = 0x9AB91722
Random[7] = 0x4F54D999
Random[8] = 0x492414D1
Random[9] = 0x84611992

 Press any key to continue...
Customization options
=====================

