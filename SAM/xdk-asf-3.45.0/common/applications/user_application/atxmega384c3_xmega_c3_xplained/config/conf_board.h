/**
 * \file
 *
 * \brief XMEGA-C3 Xplained board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

// Initialize SPI and control pins for UG_2832HSWEG04 OLED controller
#define CONF_BOARD_OLED_UG_2832HSWEG04

// Initialize SPI pins and presence pin for MicroSD card slot
#define CONF_BOARD_SD_MMC_SPI

// Initialize Analog Comparator pin for light sensor
#define CONF_BOARD_LIGHT_SENSOR

// Initialize Analog Comparator pin for NTC sensor
#define CONF_BOARD_TEMPERATURE_SENSOR

// Initialize Analog Comparator pin and input signal pin
// for Analog Filter (lowpass RC @ 159 Hz)
#define CONF_BOARD_ANALOG_FILTER

// Initialize IO pins for use with USART 0 on port C
#define CONF_BOARD_ENABLE_USARTC0

// Initialize IO pins for use with USART 0 on port D
#define CONF_BOARD_ENABLE_USARTD0

// Initialize IO pins for use with USART 0 on port E
#define CONF_BOARD_ENABLE_USARTE0

#endif // CONF_BOARD_H
