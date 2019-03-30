/*
 * Copyright (C) 2014 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

/**
 * @file
 * @date 06 September, 2016
 * @version 1.0.4
 *
 * @brief I2C demo example
 *
 * For this demo either the COM or the HMI satellite boards for the XMC45 CPU board are required.
 * It communicates with the IO expander found in the mentioned satellite boards.
 * Attention: The address of the IO expander is different on the two satellite boards
 * The demo implements a binary counter using the LEDs attached to the IO expander.
 *
 * History <br>
 *
 * Version 1.0.0 Initial
 * Version 1.0.1 Adapted to the last llds
 * Version 1.0.2 Changed XMC_GPIO_SetMode() to XMC_GPIO_Init() for code clarity reasons
 * Version 1.0.4 Added ACT_PCA9502_ADDRESS
 */

#include <xmc_gpio.h>
#include <xmc_i2c.h>

/* IO expander address on COM board */
#define COM_PCA9502_ADDRESS (0x98)

/* IO expander address on HMI board */
#define HMI_PCA9502_ADDRESS (0x9A)

/* IO expander address on AUT_ISO board */
#define ACT_PCA9502_ADDRESS (0x90)

#define IO_EXPANDER_ADDRESS HMI_PCA9502_ADDRESS

typedef enum PCA9502_REGADDR {
    IO_DIR    = 0xA << 3,
    IO_STATE  = 0xB << 3,
    IO_INTE   = 0xC << 3,
    IO_CTRL   = 0xE << 3
} PCA9502_REGADDR_t;

#define SDA_PIN P2_14
#define SCL_PIN P5_8
XMC_GPIO_CONFIG_t i2c_sda =
{
  .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
  .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
};

XMC_GPIO_CONFIG_t i2c_scl =
{
  .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2,
  .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
};


XMC_I2C_CH_CONFIG_t i2c_cfg =
{
  .baudrate = 100000U,
};

void delay(uint32_t counter);

int main(void)
{
  uint8_t counter = 0;
  uint8_t io_state1 = 0;
  uint8_t received_data;

  XMC_I2C_CH_Init(XMC_I2C1_CH0, &i2c_cfg);
  XMC_I2C_CH_SetInputSource(XMC_I2C1_CH0, XMC_I2C_CH_INPUT_SDA, USIC1_C0_DX0_P2_14);
  XMC_I2C_CH_SetInputSource(XMC_I2C1_CH0, XMC_I2C_CH_INPUT_SCL, USIC1_C0_DX1_P5_8);
  XMC_I2C_CH_Start(XMC_I2C1_CH0);

  XMC_GPIO_Init(SCL_PIN, &i2c_scl);
  XMC_GPIO_Init(SDA_PIN, &i2c_sda);

  XMC_I2C_CH_MasterStart(XMC_I2C1_CH0, IO_EXPANDER_ADDRESS, XMC_I2C_CH_CMD_WRITE);
  while((XMC_I2C_CH_GetStatusFlag(XMC_I2C1_CH0) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
  {
    /* wait for ACK */
  }
  XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH0, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

  XMC_I2C_CH_MasterTransmit(XMC_I2C1_CH0, IO_DIR);
  while((XMC_I2C_CH_GetStatusFlag(XMC_I2C1_CH0) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
  {
    /* wait for ACK */
  }
  XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH0, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

  XMC_I2C_CH_MasterTransmit(XMC_I2C1_CH0, 0xffU);
  while((XMC_I2C_CH_GetStatusFlag(XMC_I2C1_CH0) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
  {
    /* wait for ACK */
  }
  XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH0, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

  while(counter < 255)
  {
    io_state1 = ~counter;
	  counter++;


    XMC_I2C_CH_MasterRepeatedStart(XMC_I2C1_CH0, IO_EXPANDER_ADDRESS, XMC_I2C_CH_CMD_WRITE);
    while((XMC_I2C_CH_GetStatusFlag(XMC_I2C1_CH0) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
    {
      /* wait for ACK */
    }
    XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH0, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

    XMC_I2C_CH_MasterTransmit(XMC_I2C1_CH0, IO_STATE);
    while((XMC_I2C_CH_GetStatusFlag(XMC_I2C1_CH0) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
    {
      /* wait for ACK */
    }
    XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH0, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

    XMC_I2C_CH_MasterTransmit(XMC_I2C1_CH0, io_state1);
    while((XMC_I2C_CH_GetStatusFlag(XMC_I2C1_CH0) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
    {
      /* wait for ACK */
    }
    XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH0, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

    XMC_I2C_CH_MasterRepeatedStart(XMC_I2C1_CH0, IO_EXPANDER_ADDRESS, XMC_I2C_CH_CMD_READ);
    while((XMC_I2C_CH_GetStatusFlag(XMC_I2C1_CH0) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
    {
      /* wait for ACK */
    }
    XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH0, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

    XMC_I2C_CH_MasterReceiveNack(XMC_I2C1_CH0);
    while((XMC_I2C_CH_GetStatusFlag(XMC_I2C1_CH0) & (XMC_I2C_CH_STATUS_FLAG_RECEIVE_INDICATION |
	                                                   XMC_I2C_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION)) == 0U)
    {
      /* wait for ACK */
    }
    XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH0, XMC_I2C_CH_STATUS_FLAG_RECEIVE_INDICATION |
                                             XMC_I2C_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION);

    received_data = XMC_I2C_CH_GetReceivedData(XMC_I2C1_CH0);
    if(io_state1 != received_data)
    {
      while(1);
    }

    /* Delay to make visible the change */
    delay(0xfffff);

  }

  XMC_I2C_CH_MasterStop(XMC_I2C1_CH0);

  while(1);
}

void delay(uint32_t counter)
{
	volatile uint32_t cnt = counter;
	while(--cnt);
}
