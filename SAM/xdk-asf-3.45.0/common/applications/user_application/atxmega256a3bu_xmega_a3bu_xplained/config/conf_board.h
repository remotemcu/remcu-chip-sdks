/**
 * \file
 *
 * \brief XMEGA-A3BU Xplained board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

// Initialize IO pins for the LCD controller
#define CONF_BOARD_C12832A1Z

// Initialize IO pins for the DataFlash
#define CONF_BOARD_AT45DBX

// Initialize IO pins for use with Analog Comparator
#define CONF_BOARD_ENABLE_AC_PINS

// Initialize IO pins for use with USART 0 on port C
#define CONF_BOARD_ENABLE_USARTC0

// Initialize IO pins for use with USART 0 on port D
#define CONF_BOARD_ENABLE_USARTD0

// Initialize IO pins for use with USART 0 on port E
#define CONF_BOARD_ENABLE_USARTE0

// Enable Sensors Xplained board interface
//#define SENSORS_XPLAINED_BOARD

#endif // CONF_BOARD_H
