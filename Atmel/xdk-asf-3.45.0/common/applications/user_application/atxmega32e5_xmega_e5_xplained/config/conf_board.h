/**
 * \file
 *
 * \brief XMEGA-E5 Xplained board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

// Initialize SPI and control pins for UG_2832HSWEG04 OLED controller
#define CONF_BOARD_OLED_UG_2832HSWEG04

// Initialize Analog Comparator pin for light sensor
#define CONF_BOARD_LIGHT_SENSOR

// Initialize Quadrature encoder pins
#define CONF_BOARD_QUADRATURE_ENCODER

// Initialize IO pins for USART 0 on pins 2 and 3 of port C
#define CONF_BOARD_ENABLE_USARTC0

// Initialize IO pins for USART 0 on pins 6 and 7 of port C
//#define CONF_BOARD_ENABLE_USARTC0_REMAP // Mixed with OLED controller

// Initialize IO pins for USART 0 on pins 2 and 3 of port D
//#define CONF_BOARD_ENABLE_USARTD0 // Mixed with OLED and SW1

// Initialize IO pins for USART 0 on pins 6 and 7 of port D
#define CONF_BOARD_ENABLE_USARTD0_REMAP // UART link with board controller

/* Configure pin 2 for USARTC0 in one wire mode */
/* #define CONF_BOARD_ENABLE_USARTC0_ONEWIRE */

/* Configure pin 6 for USARTC0 in one wire mode */
/* #define CONF_BOARD_ENABLE_USARTC0_ONEWIRE_REMAP */

/* Configure pin 2 for USARTD0 in one wire mode */
/* #define CONF_BOARD_ENABLE_USARTD0_ONEWIRE */

/* Configure pin 6 for USARTD0 in one wire mode */
/* #define CONF_BOARD_ENABLE_USARTD0_ONEWIRE_REMAP */

/* Output clock on PORTC pin 7 */
/* #define CONF_BOARD_CLKOUT_PC7 */

/* XCL OUT0 configurations */
/* #define CONF_BOARD_XCL_OUT0_PD0 */
/* #define CONF_BOARD_XCL_OUT0_PD4 */
/* #define CONF_BOARD_XCL_OUT0_PC0 */
/* #define CONF_BOARD_XCL_OUT0_PC4 */
/* #define CONF_BOARD_XCL_OUT0_PD0_INV */
/* #define CONF_BOARD_XCL_OUT0_PD4_INV */
/* #define CONF_BOARD_XCL_OUT0_PC0_INV */
/* #define CONF_BOARD_XCL_OUT0_PC4_INV */


/* XCL CC0 and CC1 configurations */
/* #define CONF_BOARD_XCL_CC0_PC2 */
/* #define CONF_BOARD_XCL_CC0_PC3 */
/* #define CONF_BOARD_XCL_CC0_PD2 */
/* #define CONF_BOARD_XCL_CC0_PD3 */
/* #define CONF_BOARD_XCL_CC0_PC2_INV */
/* #define CONF_BOARD_XCL_CC0_PC3_INV */
/* #define CONF_BOARD_XCL_CC0_PD2_INV */
/* #define CONF_BOARD_XCL_CC0_PD3_INV */

/* XCL IN0 configurations */
/* #define CONF_BOARD_XCL_IN0_PD2 */
/* #define CONF_BOARD_XCL_IN0_PD2_INV */
/* #define CONF_BOARD_XCL_IN0_PD6 */
/* #define CONF_BOARD_XCL_IN0_PD6_INV */
/* #define CONF_BOARD_XCL_IN0_PC2 */
/* #define CONF_BOARD_XCL_IN0_PC2_INV */
/* #define CONF_BOARD_XCL_IN0_PC6 */
/* #define CONF_BOARD_XCL_IN0_PC6_INV */

/* XCL IN1 Configurations */
/* #define CONF_BOARD_XCL_IN1_PD0 */
/* #define CONF_BOARD_XCL_IN1_PD0_INV */
/* #define CONF_BOARD_XCL_IN1_PD4 */
/* #define CONF_BOARD_XCL_IN1_PD4_INV */
/* #define CONF_BOARD_XCL_IN1_PC0 */
/* #define CONF_BOARD_XCL_IN1_PC0_INV */
/* #define CONF_BOARD_XCL_IN1_PC4 */
/* #define CONF_BOARD_XCL_IN1_PC4_INV */

/* XCL IN2 Configurations */
/* #define CONF_BOARD_XCL_IN2_PD1 */
/* #define CONF_BOARD_XCL_IN2_PD1_INV */
/* #define CONF_BOARD_XCL_IN2_PD5 */
/* #define CONF_BOARD_XCL_IN2_PD5_INV */
/* #define CONF_BOARD_XCL_IN2_PC1 */
/* #define CONF_BOARD_XCL_IN2_PC1_INV */
/* #define CONF_BOARD_XCL_IN2_PC5 */
/* #define CONF_BOARD_XCL_IN2_PC5_INV */

/* XCL IN3 Configurations */
/* #define CONF_BOARD_XCL_IN3_PD3 */
/* #define CONF_BOARD_XCL_IN3_PD3_INV */
/* #define CONF_BOARD_XCL_IN3_PD7 */
/* #define CONF_BOARD_XCL_IN3_PD7_INV */
/* #define CONF_BOARD_XCL_IN3_PC3 */
/* #define CONF_BOARD_XCL_IN3_PC3_INV */
/* #define CONF_BOARD_XCL_IN3_PC7 */
/* #define CONF_BOARD_XCL_IN3_PC7_INV */

#endif // CONF_BOARD_H
