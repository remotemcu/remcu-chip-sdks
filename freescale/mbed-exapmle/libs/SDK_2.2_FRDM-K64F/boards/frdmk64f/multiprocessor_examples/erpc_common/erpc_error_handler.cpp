/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "erpc_error_handler.h"
#include "fsl_debug_console.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

bool g_erpc_error_occurred = false;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void erpc_error_handler(erpc_status_t err)
{
    switch (err)
    {
        case kErpcStatus_Fail:
            PRINTF("\r\nGeneric failure\r\n");
            break;

        case kErpcStatus_InvalidArgument:
            PRINTF("\r\nArgument is an invalid value\r\n");
            break;

        case kErpcStatus_Timeout:
            PRINTF("\r\nOperated timed out\r\n");
            break;

        case kErpcStatus_InvalidMessageVersion:
            PRINTF("\r\nMessage header contains an unknown version\r\n");
            break;

        case kErpcStatus_ExpectedReply:
            PRINTF("\r\nExpected a reply message but got another message type\r\n");
            break;

        case kErpcStatus_CrcCheckFailed:
            PRINTF("\r\nMessage is corrupted\r\n");
            break;

        case kErpcStatus_BufferOverrun:
            PRINTF("\r\nAttempt to read or write past the end of a buffer\r\n");
            break;

        case kErpcStatus_UnknownName:
            PRINTF("\r\nCould not find host with given name\r\n");
            break;

        case kErpcStatus_ConnectionFailure:
            PRINTF("\r\nFailed to connect to host\r\n");
            break;

        case kErpcStatus_ConnectionClosed:
            PRINTF("\r\nConnected closed by peer\r\n");
            break;

        case kErpcStatus_MemoryError:
            PRINTF("\r\nMemory allocation error\r\n");
            break;

        case kErpcStatus_ServerIsDown:
            PRINTF("\r\nServer is stopped\r\n");
            break;

        case kErpcStatus_InitFailed:
            PRINTF("\r\nTransport layer initialization failed\r\n");
            break;

        case kErpcStatus_ReceiveFailed:
            PRINTF("\r\nFailed to receive data\r\n");
            break;

        case kErpcStatus_SendFailed:
            PRINTF("\r\nFailed to send data.\r\n");
            break;

        /* unhandled error */
        default:
            PRINTF("\r\nUnhandled error occurred\r\n");
            break;

        /* no error occurred */
        case kErpcStatus_Success:
            g_erpc_error_occurred = false;
    }

    /* error occurred */
    g_erpc_error_occurred = true;
}
