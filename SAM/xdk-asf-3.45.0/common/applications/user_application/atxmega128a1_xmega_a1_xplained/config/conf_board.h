/**
 * \file
 *
 * \brief XMEGA-A1 Xplained board configuration template
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

// Enable on-board Light Sensor (ADC)
#define CONF_BOARD_ENABLE_LIGHT_SENSOR

// Enable on-board Temperature Sensor (ADC)
#define CONF_BOARD_ENABLE_TEMPERATURE_SENSOR

// Enable on-board Speaker (DAC)
#define CONF_BOARD_ENABLE_SPEAKER

// Enable UART Communication Port interface (UART)
#define CONF_BOARD_ENABLE_USARTC0
#define CONF_BOARD_ENABLE_USARTD0

// Enable Sensors Xplained board interface
//#define SENSORS_XPLAINED_BOARD

#endif // CONF_BOARD_H
