/***************************************************************************//**
 * @file
 * @brief Provide MicroSD SPI configuration parameters.
 * @version 5.1.1
 *******************************************************************************
 * @section License
 * <b>Copyright 2015 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef __MICROSDCONFIG_H
#define __MICROSDCONFIG_H

/* Don't increase MICROSD_HI_SPI_FREQ beyond 8MHz. Next step will be 16MHz  */
/* which is out of spec.                                                    */
#define MICROSD_HI_SPI_FREQ     8000000

#define MICROSD_LO_SPI_FREQ     100000
#define MICROSD_USART           USART0
#define MICROSD_LOC             USART_ROUTE_LOCATION_LOC2
#define MICROSD_CMUCLOCK        cmuClock_USART0
#define MICROSD_GPIOPORT        gpioPortC
#define MICROSD_MOSIPIN         11
#define MICROSD_MISOPIN         10
#define MICROSD_CSPIN           8
#define MICROSD_CLKPIN          9

#endif /* __MICROSDCONFIG_H */
