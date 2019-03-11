Overview
========
The RTC demo application demonstrates the important features of the RTC Module by using the RTC Peripheral Driver.

The RTC demo supports the following features:

- Calendar
  + Get the current date time with Year, Month, Day, Hour, Minute, and Second.
  + Set the current date time with Year, Month, Day, Hour, Minute, and Second.

- Alarm
  + Set the alarm based on the current time.
  + Application prints a notification when the alarm expires.

- Seconds interrupt
  + Use second interrupt function to display a digital time blink every second.

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
The following menu is displayed in the serial terminal:

~~~~~~~~~~~~~~~~~~~~~
RTC Demo running...

Please choose the sub demo to run:

1) Get current date time.

2) Set current date time.

3) Alarm trigger show.

4) Second interrupt show (demo for 20s).

Select:
~~~~~~~~~~~~~~~~~~~~~

### 1. Get current date time: {#GetTime}

This command gets the current date time in the format of YYYY-MM-DD HH:MM:SS.
~~~~~~~~~~~~~~~~~~~~~
Current datetime: 2015-11-11 11:11:11
~~~~~~~~~~~~~~~~~~~~~

### 2. Set current date time {#GetDate}

Sets the date time as YYYY-MM-DD HH:MM:SS.
~~~~~~~~~~~~~~~~~~~~~
Input date time like: "2010-10-10 10:10:10"
2009-10-10 10:10:10
~~~~~~~~~~~~~~~~~~~~~

### 3. Show the alarm function {#ShowAlarm}

Sets the alarm time: 1~9 seconds from the time you input and waits for the alarm event arrival.
~~~~~~~~~~~~~~~~~~~~~
Input the alarm seconds from the current moment (1s~9s):3
Triggered Alarm: 10:10:31
~~~~~~~~~~~~~~~~~~~~~

### 4. Seconds interrupt show {#Seconds}

Shows the digital time animation by seconds-interrupt function.
~~~~~~~~~~~~~~~~~~~~~
10:10:51
10:10:51
...
10:11:11
~~~~~~~~~~~~~~~~~~~~~

Customization options
=====================

