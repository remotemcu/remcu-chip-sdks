#!/usr/bin/python

# Copyright (c) 2016 Freescale Semiconductor, Inc.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
# o Redistributions of source code must retain the above copyright notice, this list
#   of conditions and the following disclaimer.
#
# o Redistributions in binary form must reproduce the above copyright notice, this
#   list of conditions and the following disclaimer in the documentation and/or
#   other materials provided with the distribution.
#
# o Neither the name of Freescale Semiconductor, Inc. nor the names of its
#   contributors may be used to endorse or promote products derived from this
#   software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

from __future__ import print_function

import sys, random, argparse, threading
from serial import SerialException
import serial.tools.list_ports as list_ports

try:
    import erpc
except ImportError:
    print("Could not import erpc.\r\nPlease install it first by running \"middleware\multicore\erpc\erpc_python\setup.py\" script.")
    sys.exit()

# client part
from service import erpc_remote_control_app_0
# server part
from service import erpc_remote_control_app_1

# make input function independent on Python version
input_fn = raw_input if sys.version_info[:2] <= (2, 7) else input

###############################################################################
# Variables
###############################################################################
# erpc transport arbitrator
transportArbitrator = None

# which peripherals are available on used board
boardConfig = None

###############################################################################
# Code
###############################################################################

# Remote control handler
class remote_control_app_1_handler(erpc_remote_control_app_1.interface.Iremote_control_app_1):
    # Print which button has been pressed
    def button_pressed(self, button):
        print('[Message from board] Button SW{n} was pressed'.format(n=button))

# Server worker thread
def serverThread():
    # create remote control eRPC services
    handler = remote_control_app_1_handler()
    service = erpc_remote_control_app_1.server.remote_control_app_1Service(handler)

    # create server with transport arbitrator
    server = erpc.simple_server.SimpleServer(transportArbitrator, erpc.basic_codec.BasicCodec)
    server.add_service(service)
    print('eRPC server has been run')
    server.run()


# Client worker thread
def clientThread():
    # create client manager
    clientManager = erpc.client.ClientManager(transportArbitrator.shared_transport, erpc.basic_codec.BasicCodec)
    clientManager.arbitrator = transportArbitrator

    # create client
    client = erpc_remote_control_app_0.client.remote_control_app_0Client(clientManager)
    print('eRPC client has been created')

    # get board configuration
    boardConfig = erpc.Reference()
    client.get_board_config(boardConfig)
    if boardConfig is not None:
        print('Board configuration:')
        print('\tDAC: {s}'.format(s=boardConfig.value.DAC))
        RGB = boardConfig.value.RGB
        print('\tLED: Red={r}, Green={g}, Blue={b}'.format(r=RGB[0], g=RGB[1], b=RGB[2]))
        print('\tMagnetometer: {s}'.format(s=boardConfig.value.MAG))
    else:
        print('Could not get board configuration!')

    # get ADC config
    adcConfig = erpc.Reference()
    client.get_adc_config(adcConfig)
    print("ADC configuration:")
    print("\tVref={vref} V\n\tAtomic steps={steps}".format(vref=adcConfig.value.vref, steps=adcConfig.value.atomicSteps))

    # menu loop
    while True:
        # print menu options
        print("\n---------------------------")
        print("eRPC Remote Control example")
        print("---------------------------")
        print("-> Press '1' for {dac}ADC conversion".format(dac="DAC-" if boardConfig.value.DAC else ""))
        print("-> Press '2' for GPIO LED")
        print("-> Press '3' for Accelerometer and Magnetometer values")
        print("Or press SW button on board")

        # wait for user input
        switchVal = input_fn()

        # DAC ADC conversion
        if switchVal == '1':
            result = erpc.Reference()
            voltage = 0
            atomicSteps = 0

            while True:
                # FRDM-KL27Z has only ADC, skip DAC conversion
                if boardConfig.value.DAC:
                    # get voltage to convert
                    try:
                        voltage = float(input_fn("Enter voltage <0V - 3.3V>: "))
                    except ValueError:
                        continue

                    # compute number of atomic steps for DAC
                    atomicSteps = int(voltage / (adcConfig.value.vref / adcConfig.value.atomicSteps))

                # check if number to be converted is in range
                if 0 <= atomicSteps <= 4096:
                    if atomicSteps == 4096:
                        atomicSteps = 4095

                    # convert
                    client.convert_dac_adc(atomicSteps, result)
                    if boardConfig.value.DAC:
                        print("DAC is set for {V} V which is {steps} of atomic steps".format(V=voltage, steps=atomicSteps))

                    # compute voltage from value in ADC
                    adcVoltage = result.value * (adcConfig.value.vref / adcConfig.value.atomicSteps)
                    print("ADC value: {adc} V".format(adc=adcVoltage))

                    # check if ADC read value is close to one set with DAC
                    # if not, display info message about connecting theirs pins together
                    if boardConfig.value.DAC and abs(adcVoltage - voltage) >= 0.2:
                        print("[info] Please connect DAC and ADC pins (described in board.readme) to check DAC value")

                    # conversion done, exit loop
                    break
                else:
                    print("Value for DAC out of range")
        # GPIO LED
        elif switchVal == '2':
            print('Select which LED should be turned on:')
            print("--> Press '1' for red")
            print("--> Press '2' for green")
            if boardConfig.value.RGB[2]:
                print("--> Press '3' for blue")

            # wait for user input
            whichLed = int(input_fn())
            if 1 <= whichLed <= 3:
                # turn on selected LED though one way request
                client.set_led(whichLed)

        # Accelerometer and Magnetometer
        elif switchVal == '3':
            # read values
            print("Read value from Accelerometer and Magnetometer:")
            result = erpc.Reference()
            status = erpc.Reference()
            client.read_mag_accel(result, status)
            if status.value:
                axis = result.value
                print("\tAccelerometer axis: x={x}, y={y}, z={z}".format(x=axis.A_x, y=axis.A_y, z=axis.A_z))
                if boardConfig.value.MAG:
                    print("\tMagnetometer axis: x={x}, y={y}, z={z}".format(x=axis.M_x, y=axis.M_y, z=axis.M_z))
            else:
                print("Failed to read magnetometer and accelerometer data!")

###############################################################################
# Main
###############################################################################
if __name__ == "__main__":
    # parse cmd parameters
    argParser = argparse.ArgumentParser(description='eRPC remote control example')
    argParser.add_argument('-p', '--port', help='Serial port')
    argParser.add_argument('-b', '--bd', default='115200', help='Baud rate (default value is 115200)')
    args = argParser.parse_args()

    # check if serial port has been selected
    if not args.port:
        print('Please specify serial port to be used (through -p (--port) parameter).')
        available_ports = list_ports.comports()
        if available_ports:
            print('Available ports: ')
            for port in available_ports:
                print(port)
        else:
            print('There are no available ports')
        sys.exit()

    # initialize UART transport layer
    try:
        transport = erpc.transport.SerialTransport(args.port, args.bd)
        print('Selected UART port: %s, %s bd' % (args.port, args.bd))
    except SerialException:
        print('Could not open port %s' % args.port)
        sys.exit()

    # crate transport arbitrator
    transportArbitrator = erpc.arbitrator.TransportArbitrator(transport, erpc.basic_codec.BasicCodec())

    # create server and client threads
    try:
        serverThread = threading.Thread(target=serverThread, name='SERVER')
        clientThread = threading.Thread(target=clientThread, name='CLIENT')

        serverThread.start()
        clientThread.start()
    except:
        print('Unable to start server and client thread')