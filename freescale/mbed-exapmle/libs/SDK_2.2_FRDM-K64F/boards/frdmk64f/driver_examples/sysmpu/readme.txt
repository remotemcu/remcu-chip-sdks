Overview
========

The SYSMPU example defines protected/unprotected memory region for the core access.

First, the SYSMPU will capture the hardware information and show it on the
terminal. Then, a memory region is configured as the non-writable region. The
bus fault interrupt is enabled to report the memory protection interrupt event
for this non-writable region. If an operation writes to this region, the bus
fault interrupt happens. Then the bus fault interrupt handler provides a
prevention alert by outputting a message on terminal, then the write rights
will be given to this region for core access. After the write access enabled,
the writing to the region becomes successful. When the bus fault happen, the
details of the error information will be captured and printed on the terminal.

This example provides the terminal input control to give the example show for 
several regions access test. Just press any key to the terminal when the
terminal show "Press any key to continue".

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
This SYSMPU Example project does not call for any special hardware configurations.
Although not required, the recommendation is to leave the development board's jumper settings
and configurations in default state when running this example.

Prepare the Demo
================
1. Connect a USB cable between the PC host and the OpenSDA USB port on the board.
2. Open a serial terminal with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3. Download the program to the target board.
4. Either press the reset button on your board or launch the debugger in your IDE to begin running the example.

Running the demo
================

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SYSMPU Example Start.

SYSMPU revision level 1, 5 slave ports and 12 region numbers are supported.

Set regionArray0 to un-writeable.

Write 0 to regionArray at No.0.

Core access violation and generate busfault.

RegionArray[0] = 0, not updated.

Core is granted write access permission.

Error access happen on slave port: 2, access master port 0.

Error access attributes: accessSupervisorMode.

Error access type: write.

Error access control: overlappRegion.

Error access address: xxxxxxx.

RegionArray[0] = 0, updated now.

Protected regionArray successfully.

Press any key to continue.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Customization options
=====================

