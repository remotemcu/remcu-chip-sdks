/**
 * \file
 *
 * \brief Xplain board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

// Enable on-board AT45DBX interface (SPI)
#define CONF_BOARD_AT45DBX

// Enable on-board Analog Comparator interface (AC)
#define CONF_BOARD_ENABLE_AC_PINS

// Enable on-board Speaker (DAC)
#define CONF_BOARD_ENABLE_SPEAKER

// Enable UART Communication Port interface (UART)
#define CONF_BOARD_ENABLE_USARTC0
#define CONF_BOARD_ENABLE_USARTD0

#endif // CONF_BOARD_H
