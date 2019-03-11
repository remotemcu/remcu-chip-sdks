Overview
========

The pdb_dac_trigger example shows how to use the PDB to generate a DAC trigger.

Based on the basic counter, to use the DAC trigger, just to enable the DAC trigger's "milestone" and set the user-
defined value for it.
The DAC's "milestone" is called as "interval". Multiple DAC trigger intervals can be included into one PDB counter's cycle.
DAC trigger's counter would reset after the trigger is created and start counting again to the interval value.

In this example, the DAC is configured with hardware buffer enabled in normal work mode. Once it gets the trigger from 
the PDB, the buffer read pointer increases.

Toolchain supported
===================
- IAR embedded Workbench 7.80.4
- Keil MDK 5.21a
- GCC ARM Embedded 2016-5.4-q3
- Kinetis Development Studio IDE 3.2.0
- MCUXpresso0.8

Hardware requirements
=====================
- Mini/Micro USB cable
- FRDM-K64F board
- Personal Computer

Board settings
==============
No special is needed.

Prepare the Demo
================
1.  Connect a USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

PDB DAC trigger Example.

DAC Buffer Information
          Buffer index max  : 15
          Buffer watermark  : 14
Type any key into terminal to trigger the DAC buffer through PDB ...

DAC Buffer Index  0: ReadPointerTopPositionEvent
DAC Buffer Index  1:
DAC Buffer Index  2:
DAC Buffer Index  3:
DAC Buffer Index  4:
DAC Buffer Index  5:
DAC Buffer Index  6:
DAC Buffer Index  7:
DAC Buffer Index  8:
DAC Buffer Index  9:
DAC Buffer Index 10:
DAC Buffer Index 11:
DAC Buffer Index 12:
DAC Buffer Index 13:
DAC Buffer Index 14: WatermarkEvent
DAC Buffer Index 15: ReadPointerBottomPositionEvent
Customization options
=====================

