/**
 * \file
 *
 * \brief EVK1104 board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

// Enable on-board AT45DBX interface (SPI)
#define CONF_BOARD_AT45DBX

// Enable on-board SD/MMC card interface (MCI)
#define CONF_BOARD_SD_MMC_MCI

// Enable TWI interface (TWI)
#define CONF_BOARD_TWI

// Enable UART Communication Port interface (UART)
#define CONF_BOARD_COM_PORT
#define CONF_BOARD_COM_PORT3

#endif // CONF_BOARD_H
