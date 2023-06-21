/**
 * \file
 *
 * \brief XMEGA-B1 Xplained board configuration template
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

// Enable on-board AT45DBX interface (SPI)
#define CONF_BOARD_AT45DBX

// Enable on-board Light Sensor (ADC)
#define CONF_BOARD_ENABLE_LIGHT_SENSOR

// Enable on-board Temperature Sensor (ADC)
#define CONF_BOARD_ENABLE_TEMPERATURE_SENSOR

// Enable on-board Potentiometer Sensor (ADC)
#define CONF_BOARD_POTENTIOMETER_SENSOR

// Enable on-board LCD backlight interface (PWM and TC)
// #define CONF_BOARD_LCD_BACKLIGHT_PWM

// Enable UART Communication Port interface (UART)
#define CONF_BOARD_ENABLE_USARTC0

/* Enable USART communication on PORTE, which will disable touch buttons
 * CS2 and CS3, as they share pins. */
//#define CONF_BOARD_ENABLE_USARTE0

// Enable Sensors Xplained board interface
//#define SENSORS_XPLAINED_BOARD

#endif // CONF_BOARD_H
