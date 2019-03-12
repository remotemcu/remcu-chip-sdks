/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
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
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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
///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

 // Standard C Included Files
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// SDK Included Files
#include "board.h"
#include "fsl_os_abstraction.h"
#include "fsl_i2c_hal.h"
#include "fsl_i2c_master_driver.h"
#include "fsl_clock_manager.h"

#include "remcu.h"

#define DATA_LENGTH             64

// Buffer store data to send to slave
uint8_t txBuff[DATA_LENGTH] = {0};
// Buffer store data to receive from slave
uint8_t rxBuff[DATA_LENGTH] = {0};

///////////////////////////////////////////////////////////////////////////////
// Code
///////////////////////////////////////////////////////////////////////////////

/*!
 * @brief compare the data received with data sent.
 * @param source The pointer to send buffer
 * @param sink The pointer to received buffer
 * @param count The number of bytes to be compared
 * @return true or false
 */
bool i2c_compare(uint8_t *txBuff, uint8_t *rxBuff, uint32_t count)
{
    uint32_t i;
    /* Comapre source and sink data*/
    for (i = 0; i < count ; i++)
    {
        if (txBuff[i] != rxBuff[i])
        {
            return false;
        }
    }
    return true;
}

/*!
* @brief The i2c master
* The function send array to slave, then receive a array from slave
* Then compare whether the two buffers are same
*/
int main(void)
{
    // Number byte data will be transfer
    uint32_t count = 0;
    uint32_t i = 0;
    // i2c master base address
    I2C_Type * baseAddr = g_i2cBase[BOARD_I2C_INSTANCE];

    uint16_t address = BOARD_FXOS8700_ADDR;
    uint32_t baudRate_kbps = BOARD_ACCEL_BAUDRATE;   // 400 Kbps

    uint32_t i2cClockFreq;

        remcu_connect2OpenOCD("localhost", 6666);
remcu_resetRemoteUnit(ResetType::__HALT);
remcu_setVerboseLevel(LevelDebug::__INFO);
//remcu_setVerboseLevel(LevelDebug::__ERROR);

    /* enable clock for PORTs */
  CLOCK_SYS_EnablePortClock(PORTA_IDX);
  CLOCK_SYS_EnablePortClock(PORTB_IDX);
  CLOCK_SYS_EnablePortClock(PORTE_IDX);

  configure_i2c_pins(0);
  /* Init board clock */
  BOARD_ClockInit();

    // Initialize OSA
    OSA_Init();

    printf("\r\n=================== I2C MASTER POLLING ==================\r\n");
    printf("\r\n1. Master sends length of string (1 byte).\
    \r\n2. Master sends a string to slave.\
    \r\n3. Master receives a string from slave.\
    \r\n4. Compare rxBuff and txBuff to see result.\r\n");
    printf("\r\n=========================================================\r\n");

    /* Enable clock for I2C.*/
    CLOCK_SYS_EnableI2cClock(BOARD_I2C_INSTANCE);

    /* Initialize peripheral to known state.*/
    I2C_HAL_Init(baseAddr);

    /* Enable module.*/
    //I2C_HAL_Enable(baseAddr);
    I2C_HAL_Enable_NS(baseAddr);

    /* Get the current bus clock.*/
    i2cClockFreq = CLOCK_SYS_GetI2cFreq(BOARD_I2C_INSTANCE);

    I2C_HAL_SetBaudRate(baseAddr, i2cClockFreq, baudRate_kbps, NULL);

    // Initialize data to send
    for(i = 0; i < DATA_LENGTH; i++)
    {
        txBuff[i] = i + 1;
    }

    count = 1;
    printf("\r\nPress any key to start transfer:\r\n\r\n");
     // Loop for transfer
    while(1)
    {
        // Wait user press any key
        //GETCHAR();
        uint8_t command = 0x0d;

        i2c_status_t ret = I2C_HAL_MasterReceiveDataPolling(baseAddr, address, &command, 1, rxBuff, count);

        printf("i2c_status_t :%d | rxBuff : %x\n", ret, rxBuff[0]);

        command = 0x13;

        ret = I2C_HAL_MasterReceiveDataPolling(baseAddr, address, &command, 1, rxBuff, count);

        printf("i2c_status_t :%d | rxBuff : %x\n", ret, rxBuff[0]);

        command = 0x14;

        ret = I2C_HAL_MasterReceiveDataPolling(baseAddr, address, &command, 1, rxBuff, count);

        printf("i2c_status_t :%d | rxBuff : %x\n", ret, rxBuff[0]);



        uint8_t reg_addr = 0x2A;
        command = 0x00;
        //accel_write_reg : 2b  > 40

        ret = I2C_HAL_MasterSendDataPolling(baseAddr, address, &reg_addr, 1, &command, 1);
        printf("i2c_status_t :%d | rxBuff : %x\n", ret, rxBuff[0]);

        return 0;

        // Print out transmit buffer.
        printf("Master sends %d bytes:\r\n", count);
        for (i = 0; i < count; i++)
        {
            // Print 16 numbers in a line.
            if ((i & 0x0F) == 0)
            {
                printf("\r\n    ");
            }
            printf(" %02X", txBuff[i]);
        }

        // Send length of string (1 byte)
        I2C_HAL_MasterSendDataPolling(baseAddr, address, NULL, 0, (const uint8_t*)&count, 1);

        // Delay to wait slave received data
        OSA_TimeDelay(10);

        // Master send count bytes data to slave
        I2C_HAL_MasterSendDataPolling(baseAddr, address, NULL, 0, (const uint8_t*)txBuff, count);

        // Delay to wait slave received data
        OSA_TimeDelay(10);

        // Clear rxBuff
        for(i = 0; i < count; i++)
        {
            rxBuff[i] = 0;
        }

        // Master receive count byte data from slave
        I2C_HAL_MasterReceiveDataPolling(baseAddr, address, NULL, 0, rxBuff, count);

        /* Compare to check result */
        if(i2c_compare((uint8_t*)txBuff, rxBuff, count) != true)
        {
            printf("\r\nFailure when transfer with size of buffer is %d.\r\n", count);
            break;
        }
        printf("\r\nMaster Sends/ Receives %2d bytes Successfully\r\n\r\n", count);

        if(++count > DATA_LENGTH)
        {
#if defined(KM34Z7_SERIES)
            break;
#else
            count = 1;
#endif
        }

        OSA_TimeDelay(2);
    }

    printf("\r\n=================== I2C MASTER FINISH =================== \r\n");

    /* Disable module.*/
    I2C_HAL_Disable(baseAddr);

    /* Disable clock for I2C.*/
    CLOCK_SYS_DisableI2cClock(BOARD_I2C_INSTANCE);

    return 0;
}
/*******************************************************************************
 * EOF
 ******************************************************************************/
