/**
 * \file
 *
 * \brief UC3-L0 Xplained board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

// Enable on-board AT45DBX interface (SPI)
#define CONF_BOARD_AT45DBX

// Enable shared pin PA11 as input
#define SHARED_PIN_PA11_IS_INPUT

// Enable TWI interface (TWI)
#define CONF_BOARD_TWI

// Enable UART Communication Port interface (UART)
#define CONF_BOARD_COM_PORT    // Connected on USB Virtual Com
#define CONF_BOARD_COM_PORT_0  // Connected on J4 header

// Enable Sensors Xplained board interface
//#define SENSORS_XPLAINED_BOARD

#endif // CONF_BOARD_H
