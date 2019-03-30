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
 * @date 15 January,2015
 * @version 0.1.3
 *
 * @brief SPI demo example
 *
 * Send two periodic messages via SPI with different lengths
 *
 * History <br>
 *
 * Version 0.1.0 Initial <br>
 * Version 0.1.1 Updated with latest llds<br>
 * Version 0.1.2 Updated with latest llds<br>
 * Version 0.1.3 Updated with latest llds<br>
 */

#include "xmc_spi.h"
#include "xmc_gpio.h"

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 1000

const uint8_t data[3] = {0x84,0xFF,0x84};

XMC_GPIO_CONFIG_t rx_pin_config;
XMC_GPIO_CONFIG_t tx_pin_config;
XMC_GPIO_CONFIG_t selo_pin_config;
XMC_GPIO_CONFIG_t clk_pin_config;

/**
 * @brief SPI configuration structure
*/
XMC_SPI_CH_CONFIG_t spi_config =
{
  .baudrate = 10000,
  .bus_mode = XMC_SPI_CH_BUS_MODE_MASTER,
  .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
  .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
};

void SysTick_Handler(void)
{
  uint8_t i=0;
  static uint32_t ticks = 0;
  ticks++;
  if (ticks == TICKS_WAIT)
  {
    /*Enable Slave Select line 0*/
    XMC_SPI_CH_EnableSlaveSelect(XMC_SPI0_CH0, XMC_SPI_CH_SLAVE_SELECT_0);

    /*Sending a byte*/
    XMC_SPI_CH_Transmit(XMC_SPI0_CH0, data[0], XMC_SPI_CH_MODE_STANDARD);
    /*Wait till the byte has been transmitted*/
    while((XMC_SPI_CH_GetStatusFlag(XMC_SPI0_CH0) & XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION) == 0U);
    XMC_SPI_CH_ClearStatusFlag(XMC_SPI0_CH0, XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION);

    /*Disable Slave Select line */
    XMC_SPI_CH_DisableSlaveSelect(XMC_SPI0_CH0);

    /*Enable Slave Select line 0*/
    XMC_SPI_CH_EnableSlaveSelect(XMC_SPI0_CH0, XMC_SPI_CH_SLAVE_SELECT_0);

    /*Sending 3 position of data array*/
    while(i<3)
    {
      XMC_SPI_CH_Transmit(XMC_SPI0_CH0,data[i++],XMC_SPI_CH_MODE_STANDARD);
      while((XMC_SPI_CH_GetStatusFlag(XMC_SPI0_CH0) & XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION) == 0U);
      XMC_SPI_CH_ClearStatusFlag(XMC_SPI0_CH0, XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION);

    }
    i=0;
    /*Disable Slave Select line */
    XMC_SPI_CH_DisableSlaveSelect(XMC_SPI0_CH0);
    ticks = 0;
  }
}
int main(void)
{
  /* Initialize and Start SPI */
  XMC_SPI_CH_Init(XMC_SPI0_CH0, &spi_config);
  XMC_SPI_CH_SetInputSource(XMC_SPI0_CH0, XMC_SPI_CH_INPUT_DIN0, USIC0_C0_DX0_P2_0);

  XMC_SPI_CH_Start(XMC_SPI0_CH0);

  /* GPIO Input pin configuration */
  rx_pin_config.mode = XMC_GPIO_MODE_INPUT_TRISTATE;
  XMC_GPIO_Init(XMC_GPIO_PORT2,0, &rx_pin_config);

  /* GPIO Output pin configuration */
  tx_pin_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7;
  XMC_GPIO_Init(XMC_GPIO_PORT1,0, &tx_pin_config);

  /* GPIO Slave Select line pin configuration */
  selo_pin_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6;
  XMC_GPIO_Init(XMC_GPIO_PORT0,9, &selo_pin_config);

  /* GPIO Clock pin configuration */
  clk_pin_config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT6;
  XMC_GPIO_Init(XMC_GPIO_PORT0,8, &clk_pin_config);

  /* Start sending periodic message */
  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  while(1)
  {
    /* Infinite loop */
  }
}

