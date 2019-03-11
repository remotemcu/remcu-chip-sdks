Overview
========
This example demonstrates usage of eRPC between PC and board using UART transport layer.
Board acts like a server and the PC as client. When server starts, it waits for
data being send from client over UART. Server then performs action (DAC/ADC conversion, light LEDs,
read data from magnetometer senzor) and sends result data back to client (or lights LED).

eRPC documentation
eRPC specific files are stored in: middleware\multicore_<version>\erpc
eRPC documentation is stored in: middleware\multicore_<version>\erpc\doc
eRPC is open-source project stored on github: https://github.com/EmbeddedRPC/erpc
eRPC documentation can be also found in: http://embeddedrpc.github.io

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
Connect J4-11(DAC_OUT) to J4-2(PTB2/ADC0_SE12)


Prepare the Demo
================
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board.
2.  Download the program to the target board.
3.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.
4.  Run "run.py" on your PC and select COM port.

For detailed instructions, see the appropriate board User's Guide.

Running the demo
================
Selected UART port: COM12, 115200 bd
->Press '1' for DAC ADC conversion
->Press '2' for GPIO LED
->Press '3' for Accelerometer and Magnetometer
1
Please enter voltage <0V - 3.3V>: 1.5
You entered 1.5
Read value from ADC: 1.498535
---------------------
->Press '1' for DAC ADC conversion
->Press '2' for GPIO LED
->Press '3' for Accelerometer and Magnetometer
2
->Press '1' for red LED
->Press '2' for blue LED
->Press '3' for green LED
3
->Press '1' for DAC ADC conversion
->Press '2' for GPIO LED
->Press '3' for Accelerometer and Magnetometer
3
To calibrate Magnetometer and Accelerometer, press Enter

Roll the board on all orientations to get max and min values
Read value from Magnetometer:
    Accelerometer X axis: -92.000000
    Accelerometer Y axis: -64.000000
    Accelerometer Z axis: 8144.000000
    Magnetometer X axis: 199.000000
    Magnetometer Y axis: 143.000000
    Magnetometer Z axis: 526.000000
->Press '1' for DAC ADC conversion
->Press '2' for GPIO LED
->Press '3' for Accelerometer and Magnetometer
Customization options
=====================

