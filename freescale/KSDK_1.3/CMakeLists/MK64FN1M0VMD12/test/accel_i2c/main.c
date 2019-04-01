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
//  Includes
///////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <unistd.h>

// SDK Included Files
#include "device_defines.h"
#include "board.h"
#include "fsl_device_registers.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"
#include "fsl_os_abstraction.h"
#include "fsl_ftm_hal.h"
#include "accel.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////
uint16_t g_xValue, g_yValue = 0;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
#include "remcu.h"

/*!
 * @brief Main demo function.
 */
int main(int argc, char** argv)
{
  printf("argc : %d\n", argc);

  if(argc < 3){
        printf("test requare 2 arguments: host and port\n");
        return -1;
    }
    const char * host = argv[1];
    printf("argv[1] : %s\n", argv[1]);
    printf("argv[2] : %s\n", argv[2]);
    const uint16_t port = (atoi(argv[2]) & 0xFFFF);
    printf("port : %d\n", port);

  if (port == 6666){
    remcu_connect2OpenOCD(host, 6666, 3);
  } else {
    remcu_connect2GDB(host, port, 3);
  }

remcu_resetRemoteUnit(__HALT);
//remcu_setVerboseLevel(LevelDebug::__INFO);
remcu_setVerboseLevel(__ERROR);

  assert(remcu_is_connected());

  SystemInit();

    ftm_pwm_param_t xAxisParams, yAxisParams;
    accel_dev_t accDev;
    accel_dev_interface_t accDevice;
    accel_sensor_data_t accelData;
    accel_i2c_interface_t i2cInterface;
    int16_t xData, yData;
    int16_t xAngle, yAngle;
    uint32_t ftmModulo;

    // Register callback func for I2C
    i2cInterface.i2c_init       =  I2C_DRV_MasterInit;
    i2cInterface.i2c_read       =  NULL; //I2C_DRV_MasterReceiveDataBlocking
    i2cInterface.i2c_write      =  NULL; //I2C_DRV_MasterSendDataBlocking;

    accDev.i2c = &i2cInterface;
    accDev.accel = &accDevice;

    accDev.slave.baudRate_kbps  = BOARD_ACCEL_BAUDRATE;
    accDev.slave.address        = BOARD_ACCEL_ADDR;
    accDev.bus                  = BOARD_ACCEL_I2C_INSTANCE;

  /* Enable clock for PORTs */
  CLOCK_SYS_EnablePortClock(PORTA_IDX);
  CLOCK_SYS_EnablePortClock(PORTB_IDX);
  CLOCK_SYS_EnablePortClock(PORTE_IDX);

  /* Enable I2C pins */
  configure_i2c_pins(0);

    // Initialize the LEDs used by this application.
    LED2_EN;
    LED3_EN;

    // Print the initial banner.
    printf("Bubble Level Demo!\r\n\r\n");

    // Initialize the Accel.
    accel_init(&accDev);

    // Turn on the clock to the FTM.
    CLOCK_SYS_EnableFtmClock(BOARD_FTM_INSTANCE);

    // Main loop.  Get sensor data and update globals for the FTM timer update.
    while(1)
    {
        // Get new accelerometer data.
          accDev.accel->accel_read_sensor_data(&accDev,&accelData);

        // Get the X and Y data from the sensor data structure.
        xData = (int16_t)((accelData.data.accelXMSB << 8) | accelData.data.accelXLSB);
        yData = (int16_t)((accelData.data.accelYMSB << 8) | accelData.data.accelYLSB);

        // Convert raw data to angle (normalize to 0-90 degrees).  No negative
        // angles.
        xAngle = abs((int16_t)(xData * 0.011));
        yAngle = abs((int16_t)(yData * 0.011));

        // Set values for next FTM ISR udpate.  Use 5 degrees as the threshold
        // for whether to turn the LED on or not.
        g_xValue = (xAngle > 5) ? (uint16_t)((xAngle / 90.0) * ftmModulo) : 0;
        g_yValue = (yAngle > 5) ? (uint16_t)((yAngle / 90.0) * ftmModulo) : 0;

        // Print out the raw accelerometer data.
        printf("x= %d y = %d\r\n", xData, yData);
    }
}
