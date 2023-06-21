/**
 * \file
 *
 * \brief ATPL230AMB Board Definition.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef ATPL230AMB_H_INCLUDED
#define ATPL230AMB_H_INCLUDED

#include "compiler.h"
#include "conf_board.h"

/**
 * \ingroup group_common_boards
 * \defgroup atpl230amb_group "ATPL230AMB"
 * Evaluation Board for atpl230a devices.
 *
 * @{
 */

/**
 * \defgroup atpl230amb_board_info_group "ATPL230AMB - Board informations"
 * Definitions related to the board description.
 *
 * @{
 */

/** Name of the board */
#define BOARD_NAME "ATPL230AMB"
/** Board definition */
#define atpl230amb
/** Family definition (already defined) */
#define sam4s
/** Core definition */
#define cortexm4
/** Board revision definition */
#define BOARD_REV_0     0
#define BOARD_REV_1     1
#define BOARD_REV_2     2

#ifndef BOARD_REV
#define BOARD_REV BOARD_REV_2
#endif



/* @} */

/**
 *  \defgroup atpl230amb_opfreq_group "ATPL230AMB - Operating frequencies"
 *  Definitions related to the board operating frequency.
 *
 *  @{
 */

/**
 * \name Board oscillator settings
 * @{
 */
#define BOARD_FREQ_SLCK_XTAL        (32768U)
#define BOARD_FREQ_SLCK_BYPASS      (32768U)
#define BOARD_FREQ_MAINCK_XTAL      (12000000U)
#define BOARD_FREQ_MAINCK_BYPASS    (12000000U)
/* @} */

/** Master clock frequency */
#define BOARD_MCK                   CHIP_FREQ_CPU_MAX

/** board main clock xtal statup time */
#define BOARD_OSC_STARTUP_US        15625U

/* @} */

/**
 * \defgroup atpl230amb_features_group "ATPL230AMB - Features"
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

 /**
	 * \name LED #0 pin definition
	 * @{
	 */
	#define LED0_GPIO            (PIO_PA16_IDX)
	#define LED0_ACTIVE_LEVEL    IOPORT_PIN_LEVEL_LOW
	#define LED0_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_HIGH

	/* Wrapper macros to ensure common naming across all boards */
	#define LED_0_NAME      "green LED (D5)"
	#define PIN_LED_0       {PIO_PA16, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
	#define PIN_LED_0_MASK   PIO_PA16
	#define PIN_LED_0_PIO    PIOA
	#define PIN_LED_0_ID     ID_PIOA
	#define PIN_LED_0_TYPE   PIO_OUTPUT_1
	#define PIN_LED_0_ATTR   PIO_DEFAULT
	/* @} */

#if BOARD_REV == BOARD_REV_0
	/**
	 * \name LED #1 pin definition
	 * @{
	 */
	#define LED1_GPIO            (PIO_PA23_IDX)
	#define LED1_ACTIVE_LEVEL    IOPORT_PIN_LEVEL_LOW
	#define LED1_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_HIGH

	/* Wrapper macros to ensure common naming across all boards */
	#define LED_1_NAME      "red LED (D6)"
	#define PIN_LED_1       {PIO_PA23, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
	#define PIN_LED_1_MASK   PIO_PA23
	#define PIN_LED_1_PIO    PIOA
	#define PIN_LED_1_ID     ID_PIOA
	#define PIN_LED_1_TYPE   PIO_OUTPUT_1
	#define PIN_LED_1_ATTR   PIO_DEFAULT
	/* @} */ 
#elif BOARD_REV == BOARD_REV_1
	/**
	 * \name LED #1 pin definition
	 * @{
	 */
	#define LED1_GPIO            (PIO_PA25_IDX)
	#define LED1_ACTIVE_LEVEL    IOPORT_PIN_LEVEL_LOW
	#define LED1_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_HIGH

	/* Wrapper macros to ensure common naming across all boards */
	#define LED_1_NAME      "red LED (D6)"
	#define PIN_LED_1       {PIO_PA25, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
	#define PIN_LED_1_MASK   PIO_PA25
	#define PIN_LED_1_PIO    PIOA
	#define PIN_LED_1_ID     ID_PIOA
	#define PIN_LED_1_TYPE   PIO_OUTPUT_1
	#define PIN_LED_1_ATTR   PIO_DEFAULT
	/* @} */ 
#elif BOARD_REV == BOARD_REV_2
	/**
	 * \name LED #1 pin definition
	 * @{
	 */
	#define LED1_GPIO            (PIO_PA25_IDX)
	#define LED1_ACTIVE_LEVEL    IOPORT_PIN_LEVEL_LOW
	#define LED1_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_HIGH

	/* Wrapper macros to ensure common naming across all boards */
	#define LED_1_NAME      "red LED (D6)"
	#define PIN_LED_1       {PIO_PA25, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
	#define PIN_LED_1_MASK   PIO_PA25
	#define PIN_LED_1_PIO    PIOA
	#define PIN_LED_1_ID     ID_PIOA
	#define PIN_LED_1_TYPE   PIO_OUTPUT_1
	#define PIN_LED_1_ATTR   PIO_DEFAULT
	/* @} */ 
#else
	#error No known ATPL230AMB revision board defined
#endif

/**
 * \name Console UART definitions
 * @{
 */
#define CONSOLE_UART      UART1
#define CONSOLE_UART_ID   ID_UART1
/* @} */

/**
 * \name UART0 pis (UTXD0 and URXD0) definitions
 * @{
 */           
#define PINS_UART0        (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0)
#define PINS_UART0_FLAGS  (IOPORT_MODE_MUX_A)

#define PINS_UART0_PORT   IOPORT_PIOA
#define PINS_UART0_MASK   (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0)
#define PINS_UART0_PIO    PIOA
#define PINS_UART0_ID     ID_PIOA
#define PINS_UART0_TYPE   PIO_PERIPH_A
#define PINS_UART0_ATTR   PIO_DEFAULT
/* @} */

/**
 * \name UART1 pis (UTXD1 and URXD1) definitions
 * @{
 */           
#define PINS_UART1        (PIO_PB2A_URXD1 | PIO_PB3A_UTXD1)
#define PINS_UART1_FLAGS  (IOPORT_MODE_MUX_A)

#define PINS_UART1_PORT   IOPORT_PIOB
#define PINS_UART1_MASK   (PIO_PB2A_URXD1 | PIO_PB3A_UTXD1)
#define PINS_UART1_PIO    PIOB
#define PINS_UART1_ID     ID_PIOB
#define PINS_UART1_TYPE   PIO_PERIPH_A
#define PINS_UART1_ATTR   PIO_DEFAULT
/* @} */

/**
 * \name SPI pin definitions
 * @{
 */
/** SPI0 MISO pin definition. */
#define SPI0_MISO_GPIO         (PIO_PA12_IDX)
#define SPI0_MISO_FLAGS        (IOPORT_MODE_MUX_A)
/** SPI0 MOSI pin definition. */
#define SPI0_MOSI_GPIO         (PIO_PA13_IDX)
#define SPI0_MOSI_FLAGS        (IOPORT_MODE_MUX_A)
/** SPI0 SPCK pin definition. */
#define SPI0_SPCK_GPIO         (PIO_PA14_IDX)
#define SPI0_SPCK_FLAGS        (IOPORT_MODE_MUX_A)
/** SPI0 chip select 0 pin definition. */
#define SPI0_NPCS0_GPIO        (PIO_PA11_IDX)
#define SPI0_NPCS0_FLAGS       (IOPORT_MODE_MUX_A)

/* @} */


/**
 * \name TWIx pin definitions
 * @{
 */
/*! TWI0 Data pin for EEPROM */
#define TWIO_DATA_GPIO            PIO_PA3_IDX
#define TWIO_DATA_FLAG            IOPORT_MODE_MUX_A
/*! TWI0 Clock pin for EEPROM */
#define TWIO_CLK_GPIO             PIO_PA4_IDX
#define TWIO_CLK_FLAG             IOPORT_MODE_MUX_A
#define BOARD_CLK_TWI_EEPROM      TWIO_CLK_GPIO
#define BOARD_CLK_TWI_MUX_EEPROM  TWIO_CLK_FLAG
/* @} */

/**
 * \name USARTx pin definitions
 * @{
 */
/** USART0 pin RX */
#define PIN_USART0_RXD_IDX    (PIO_PA5_IDX)
#define PIN_USART0_RXD_FLAGS  (IOPORT_MODE_MUX_A)
/** USART0 pin TX */
#define PIN_USART0_TXD_IDX    (PIO_PA6_IDX)
#define PIN_USART0_TXD_FLAGS  (IOPORT_MODE_MUX_A)

/** USART1 pin RX */
#define PIN_USART1_RXD_IDX    (PIO_PA21_IDX)
#define PIN_USART1_RXD_FLAGS  (IOPORT_MODE_MUX_A)
/** USART1 pin TX */
#define PIN_USART1_TXD_IDX    (PIO_PA22_IDX)
#define PIN_USART1_TXD_FLAGS  (IOPORT_MODE_MUX_A)
/** USART1 pin SCK */
#define PIN_USART1_SCK_IDX    (PIO_PA23_IDX)
#define PIN_USART1_SCK_FLAGS  (IOPORT_MODE_MUX_A)
/** USART1 pin RTS */
#define PIN_USART1_RTS_IDX    (PIO_PA24_IDX)
#define PIN_USART1_RTS_FLAGS  (IOPORT_MODE_MUX_A)
/* @} */

/**
 * \name USB detect pin definition
 * Attributes = debounce + interrupt on rising edge.
 * @{
 */
#define GPIO_USB_DETECT       (PIO_PA26_IDX)
#define GPIO_USB_DETECT_FLAGS (IOPORT_MODE_DEBOUNCE)
#define GPIO_USB_DETECT_SENSE (IOPORT_SENSE_RISING)

#define PIN_USB_DETECT       {PIO_PA26, PIOA, ID_PIOA, PIO_INPUT, \
		PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
#define PIN_USB_DETECT_MASK  PIO_PA26
#define PIN_USB_DETECT_PIO   PIOA
#define PIN_USB_DETECT_ID    ID_PIOA
#define PIN_USB_DETECT_TYPE  PIO_INPUT
#define PIN_USB_DETECT_ATTR  (PIO_DEBOUNCE | PIO_IT_RISE_EDGE)
#define PIN_USB_DETECT_IRQn  PIOA_IRQn
/* @} */

/**
 * \name Voltage Monitor pins definition
 * @{
 */
#define VZ_CROSS_GPIO    PIO_PA0_IDX
#define V5V_SENSE_GPIO   PIO_PA19_IDX
#define VDD_SENSE_GPIO   PIO_PA20_IDX
/* @} */
  
/**
 * \name Xplain PRO pins definition
 * @{
 */
#define XP_ADC0_GPIO   PIO_PA17_IDX
#define XP_ADC1_GPIO   PIO_PA18_IDX

/* XPLAIN GPIOs */
#define XP_PB0_GPIO             (PIO_PB0_IDX)
#define XP_PB0_ACTIVE_LEVEL    IOPORT_PIN_LEVEL_HIGH
#define XP_PB0_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_LOW
/* Wrapper macros to ensure common naming across all boards */
#define XP_PB0       {PIO_PB0, PIOB, ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}
#define XP_PB0_MASK   PIO_PB0
#define XP_PB0_PIO    PIOB
#define XP_PB0_ID     ID_PIOB
#define XP_PB0_TYPE   PIO_OUTPUT_1
#define XP_PB0_ATTR   PIO_DEFAULT

#define XP_PB1_GPIO             (PIO_PB1_IDX)
#define XP_PB1_ACTIVE_LEVEL    IOPORT_PIN_LEVEL_HIGH
#define XP_PB1_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_LOW
/* Wrapper macros to ensure common naming across all boards */
#define XP_PB1       {PIO_PB1, PIOB, ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}
#define XP_PB1_MASK   PIO_PB1
#define XP_PB1_PIO    PIOB
#define XP_PB1_ID     ID_PIOB
#define XP_PB1_TYPE   PIO_OUTPUT_1
#define XP_PB1_ATTR   PIO_DEFAULT

#define XP_PB14_GPIO             (PIO_PB14_IDX)
#define XP_PB14_ACTIVE_LEVEL    IOPORT_PIN_LEVEL_HIGH
#define XP_PB14_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_LOW
/* Wrapper macros to ensure common naming across all boards */
#define XP_PB14       {PIO_PB14, PIOB, ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}
#define XP_PB14_MASK   PIO_PB14
#define XP_PB14_PIO    PIOB
#define XP_PB14_ID     ID_PIOB
#define XP_PB14_TYPE   PIO_OUTPUT_1
#define XP_PB14_ATTR   PIO_DEFAULT

/* XPLAIN INTERRUPTION */
#define XP_INT_GPIO   (PIO_PA1_IDX)
#define XP_INT_FLAGS (IOPORT_MODE_DEBOUNCE)
#define XP_INT_SENSE (IOPORT_SENSE_FALLING)

#define XP_INT       {PIO_PA1, PIOA, ID_PIOA, PIO_INPUT, \
		PIO_DEBOUNCE | PIO_IT_FALL_EDGE}
#define XP_INT_MASK  PIO_PA1
#define XP_INT_PIO   PIOA
#define XP_INT_ID    ID_PIOA
#define XP_INT_TYPE  PIO_INPUT
#define XP_INT_ATTR  (PIO_DEBOUNCE | PIO_IT_FALL_EDGE)
#define XP_INT_IRQn  PIOA_IRQn

/** XPLAIN PWM pin definitions. */
#define XP_PWMH2_GPIO     PIO_PA2_IDX
#define XP_PWMH2_FLAGS    (IOPORT_MODE_MUX_A)
#define XP_PWMH2_CHANNEL  PWM_CHANNEL_2

#define XP_PWML2_GPIO     PIO_PB13_IDX
#define XP_PWML2_FLAGS    (IOPORT_MODE_MUX_A)
#define XP_PWML2_CHANNEL  PWM_CHANNEL_2

/* @} */

/* @} */ /* End of atpl230amb_features_group */

/* @} */ /* End of atpl230amb_group */

#endif  /* ATPL230AMB_H_INCLUDED */

