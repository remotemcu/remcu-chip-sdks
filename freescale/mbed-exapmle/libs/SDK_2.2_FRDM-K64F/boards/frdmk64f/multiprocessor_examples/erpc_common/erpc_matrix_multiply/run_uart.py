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

from service import erpc_matrix_multiply

# make input function independent on Python version
input_fn = raw_input if sys.version_info[:2] <= (2, 7) else input

# get matrix size defined in IDL
matrix_size = erpc_matrix_multiply.common.matrix_size

## Create matrix with specified size and random data
def fillMatrix(size, maxRandomValue):
    return [[random.randrange(maxRandomValue) for x in range(size)] for e in range(size)]

## Print matrix
def printMatrix(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            print('%04d' % matrix[i][j], end=" ")
        print()

###############################################################################
# Server
###############################################################################

## Matrix multiply service handler
class MatrixMultiplyServiceHandler(erpc_matrix_multiply.interface.IMatrixMultiplyService):
    ## eRPC matrix multiply method
    # @param matrix1 First matrix to be multiplied
    # @param matrix2 Second matrix to be multiplied
    # @param resultMatrix Reference object for storing result of matrix multiplication
    def erpcMatrixMultiply(self, matrix1, matrix2, resultMatrix):
        print('\r\nMatrix #1\r\n=========')
        printMatrix(matrix1)

        print('\r\nMatrix #2\r\n=========')
        printMatrix(matrix2)

        # clear the result matrix
        resultMatrix.value = [[0 for x in range(matrix_size)] for y in range(matrix_size)]

        # multiply input matrices
        for i in range(matrix_size):
            for j in range(matrix_size):
                for k in range(matrix_size):
                    resultMatrix.value[i][j] += matrix1[i][k] * matrix2[k][j]

        print('\r\nResult matrix\r\n=========')
        printMatrix(resultMatrix.value)

## Run server on specified transport layer
def runServer(transport):
    # create matrix multiply eRPC service
    handler = MatrixMultiplyServiceHandler()
    service = erpc_matrix_multiply.server.MatrixMultiplyServiceService(handler)

    # run server
    server = erpc.simple_server.SimpleServer(transport, erpc.basic_codec.BasicCodec)
    server.add_service(service)
    server.run()

###############################################################################
# Client
###############################################################################

## Run client on specified transport layer
def runClient(transport):
    # define maximum random value matrix can have
    MAX_VALUE = 50

    # create matrix multiply eRPC service
    clientManager = erpc.client.ClientManager(transport, erpc.basic_codec.BasicCodec)
    client = erpc_matrix_multiply.client.MatrixMultiplyServiceClient(clientManager)

    while True:
        # create matrices with random values
        matrix1 = fillMatrix(matrix_size, MAX_VALUE)
        matrix2 = fillMatrix(matrix_size, MAX_VALUE)

        # print matrices to the console
        print('\r\nMatrix #1\r\n=========')
        printMatrix(matrix1)

        print('\r\nMatrix #2\r\n=========')
        printMatrix(matrix2)

        # create result matrix as eRPC reference object
        resultMatrix = erpc.Reference()

        # send request to the server
        print('\r\neRPC request is sent to the server')
        client.erpcMatrixMultiply(matrix1, matrix2, resultMatrix)

        # print result matrix's value
        print('\r\nResult matrix\r\n=========')
        printMatrix(resultMatrix.value)

        # wait for key press
        input_fn('\r\nPress Enter to initiate the next matrix multiplication')

###############################################################################
# Main
###############################################################################

if __name__ == "__main__":
    # parse cmd parameters
    argParser = argparse.ArgumentParser(description='eRPC Matrix Multiply example')
    argParser.add_argument('-c', '--client', action='store_true', help='Run client')
    argParser.add_argument('-s', '--server', action='store_true', help='Run server')
    argParser.add_argument('-p', '--port', help='Serial port')
    argParser.add_argument('-b', '--bd', default='115200', help='Baud rate (default value is 115200)')
    args = argParser.parse_args()

    # check if either server or client has been selected
    if not args.client and not args.server:
        argParser.print_help()
        sys.exit('\r\nEither server or client has to be selected to run')
    # check if serial port has been selected
    elif not args.port:
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

        # run server/client with UART transport layer
        if args.client:
            runClient(transport)
        elif args.server:
            runServer(transport)
    except SerialException:
        print('Could not open port %s' % args.port)
