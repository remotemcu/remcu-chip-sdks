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

import sys
import random
import argparse
from serial import SerialException
import serial.tools.list_ports as list_ports

try:
    import erpc
except ImportError:
    print("Could not import erpc.\r\nPlease install it first by running \"middleware\multicore\erpc\erpc_python\setup.py\" script.")
    sys.exit()
from service import erpc_dac_adc

# make input function independent on Python version
input_fn = raw_input if sys.version_info[:2] <= (2, 7) else input

###############################################################################
# Client
###############################################################################

## Run client on specified transport layer
def runClient(transport):
    clientManager = erpc.client.ClientManager(transport, erpc.basic_codec.BasicCodec)
    client = erpc_dac_adc.client.dac_adcClient(clientManager)

    BoardName = erpc.Reference()
    client.board_get_name(BoardName)
    print(BoardName.value)

    while True:
        if BoardName.value == "FRDM-KL27Z":
            print("->Press '1' for ADC conversion")
        else:
            print("->Press '1' for DAC ADC conversion")
        print("->Press '2' for GPIO LED")
        print("->Press '3' for Accelerometer and Magnetometer")
        switchVal = input_fn()

        if switchVal == '1' and BoardName.value != "FRDM-KL27Z":
            dac_adc()
        elif switchVal == '1' and BoardName.value == "FRDM-KL27Z":
            adc()
        elif switchVal == '2':
            led_func(BoardName.value)
        elif switchVal == '3':
            accel_mag_func(BoardName.value)
        else:
            print("Invalid argument")

###############################################################################
# Accelerometer and Magnetometer function
###############################################################################
def accel_mag_func(BoardName):
    # variables
    accelResults = erpc.Reference()

    client.read_senzor_mag_accel(accelResults)

    print("Read value from Accelerometer and Magnetometer:")
    print("    Accelerometer X axis: %f" %accelResults.value.A_x)
    print("    Accelerometer Y axis: %f" %accelResults.value.A_y)
    print("    Accelerometer Z axis: %f" %accelResults.value.A_z)
    if BoardName != "FRDM-KL25Z" and BoardName != "FRDM-KL27Z" and BoardName != "FRDM-KL43Z":
        print("    Magnetometer X axis: %f" %accelResults.value.M_x)
        print("    Magnetometer Y axis: %f" %accelResults.value.M_y)
        print("    Magnetometer Z axis: %f" %accelResults.value.M_z)

###############################################################################
# LED function
###############################################################################
def led_func(BoardName):
    print("->Press '1' for red LED")
    print("->Press '2' for green LED")
    if BoardName != "FRDM-KL43Z":
        print("->Press '3' for blue LED")
    whichLed = input_fn()
    whichLed = int(whichLed)
    client.set_led(whichLed)

###############################################################################
# DAC ADC function
###############################################################################
def dac_adc():
    # variables
    AdcConfig = erpc.Reference()
    resultDAC_ADC = erpc.Reference()
    numberToConvert = 0

    # get ADC config
    client.adc_get_config(AdcConfig)
    AdcConfig_struct = AdcConfig.value

    # get Voltage to convert
    numberToConvert = input_fn("Please enter voltage <0V - 3.3V>: ")
    numberToConvert = float(numberToConvert)
    print("You entered", numberToConvert)

    # compute number of atomic steps for DAC
    numberToConvert = numberToConvert / (AdcConfig_struct.vref / AdcConfig_struct.atomicSteps)
    numberToConvert = int(numberToConvert)
    if numberToConvert >= 0 and numberToConvert <= 4096:
        if numberToConvert == 4096:
            numberToConvert = 4095
        client.convert_dac_adc(numberToConvert, resultDAC_ADC)

        # compute voltage from value in ADC
        print("Read value from ADC: %f" %(resultDAC_ADC.value * (AdcConfig_struct.vref / AdcConfig_struct.atomicSteps)))
        print("---------------------")
    else:
        print("Value for DAC/ADC out of range")

###############################################################################
# ADC function
###############################################################################
def adc():
    # variables
    AdcConfig = erpc.Reference()
    resultDAC_ADC = erpc.Reference()
    numberToConvert = 0

    # get ADC config
    client.adc_get_config(AdcConfig)
    AdcConfig_struct = AdcConfig.value
    client.convert_dac_adc(0, resultDAC_ADC)

    # compute voltage from value in ADC
    print("Read value from ADC: %f" %(resultDAC_ADC.value * (AdcConfig_struct.vref / AdcConfig_struct.atomicSteps)))
    print("---------------------")

###############################################################################
# Main
###############################################################################
if __name__ == "__main__":
    # parse cmd parameters
    argParser = argparse.ArgumentParser(description='eRPC Matrix Multiply example')
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

    try:
        # initialize UART transport layer
        transport = erpc.transport.SerialTransport(args.port, args.bd)
        print('Selected UART port: %s, %s bd' % (args.port, args.bd))

        # run client with UART transport layer
        clientManager = erpc.client.ClientManager(transport, erpc.basic_codec.BasicCodec)
        client = erpc_dac_adc.client.dac_adcClient(clientManager)

        runClient(transport)

    except SerialException:
        print('Could not open port %s' % args.port)
