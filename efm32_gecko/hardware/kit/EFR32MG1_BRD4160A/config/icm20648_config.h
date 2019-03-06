/***************************************************************************//**
 * @file icm20648_config.h
 * @brief Configuration file for the Invensense ICM20648 6-axis motion sensor
 * @version 5.1.1
 *******************************************************************************
 * @section License
 * <b>Copyright 2017 Silicon Laboratories, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef ICM20648_CONFIG_H
#define ICM20648_CONFIG_H


#define ICM20648_USART_INITSYNC                                                           \
{                                                                                         \
  usartEnable,    /* Enable RX/TX when init completed                                  */ \
  0,              /* Use current configured reference clock for configuring baudrate   */ \
  1000000,        /* 1 Mbits/s                                                         */ \
  usartDatabits8, /* 8 databits                                                        */ \
  true,           /* Master mode                                                       */ \
  true,           /* Send least significant bit first                                  */ \
  usartClockMode0,/* Clock idle low, sample on rising edge                             */ \
  false,          /* Not USART PRS input mode                                          */ \
  usartPrsRxCh0,  /* PRS channel 0                                                     */ \
  false,          /* No AUTOTX mode                                                    */ \
  false,          /* No AUTOCS mode                                                    */ \
  0,              /* Auto CS Hold cycles                                               */ \
  0               /* Auto CS Setup cycles                                              */ \
}

/* SPI bus related definitions */
#define ICM20648_SPI_USART           USART1           /**< UART instance               */
#define ICM20648_SPI_CLK             cmuClock_USART1  /**< HFPER Clock                 */


#define ICM20648_LOCATION_SPI_MOSI   11               /**< Location of the MOSI pin    */
#define ICM20648_LOCATION_SPI_MISO   11               /**< Location of the MISO pin    */
#define ICM20648_LOCATION_SPI_SCLK   11               /**< Location of the SCLK pin    */


#define ICM20648_PORT_SPI_MOSI       gpioPortC        /**< MOSI port definition        */
#define ICM20648_PIN_SPI_MOSI        6                /**< MOSI pin definition         */
#define ICM20648_PORT_SPI_MISO       gpioPortC        /**< MISO port definition        */
#define ICM20648_PIN_SPI_MISO        7                /**< MISO pin definition         */
#define ICM20648_PORT_SPI_SCLK       gpioPortC        /**< SCLK port definition        */
#define ICM20648_PIN_SPI_SCLK        8                /**< SCLK pin definition         */
#define ICM20648_PORT_SPI_CS         gpioPortA        /**< ICM20648 CS port definition */
#define ICM20648_PIN_SPI_CS          5                /**< ICM20648 CS pin definition  */

#endif /* ICM20648_CONFIG_H */
