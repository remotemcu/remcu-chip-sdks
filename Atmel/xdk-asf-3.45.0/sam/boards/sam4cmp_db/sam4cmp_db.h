/**
 * \file
 *
 * \brief SAM4CMP-DB Board Definition.
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

#ifndef SAM4CMP_DB_H_INCLUDED
#define SAM4CMP_DB_H_INCLUDED

#include "compiler.h"

/**
 * \ingroup group_common_boards
 * \defgroup sam4cmp_db_group "SAM4CMP-DB"
 * Demo Board for SAM4CMP devices.
 *
 * @{
 */

/**
 * \defgroup sam4cmp_db_board_info_group "SAM4CMP-DB - Board informations"
 * Definitions related to the board description.
 *
 * @{
 */

/** Name of the board */
#define BOARD_NAME "SAM4CMP-DB"
/** Board definition */
#define sam4cmpdb
/** Family definition (already defined) */
#define sam4cmp
/** Core definition */
#define cortexm4
/** Board revision definition */
#define BOARD_REV_B

/* @} */

/**
 *  \defgroup sam4cmp_db_opfreq_group "SAM4CMP-DB - Operating frequencies"
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
#define BOARD_FREQ_MAINCK_XTAL      (8192000U)
#define BOARD_FREQ_MAINCK_BYPASS    (8192000U)
/* @} */

/** Master clock frequency */
#define BOARD_MCK                   CHIP_FREQ_CPU_MAX

/** board main clock xtal startup time */
#define BOARD_OSC_STARTUP_US        15625U

/* @} */

/**
 * \defgroup sam4cmp_db_features_group "SAM4CMP-DB - Features"
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

/**
 * \name LED #4 pin definition
 * Note: Must short pin 5 and 6 on J11, and solder 0 ohm resistor on R304
 * to make this LED available.
 * @{
 */
#define LED4_GPIO            (PIO_PC6_IDX)
#define LED4_ACTIVE_LEVEL    IOPORT_PIN_LEVEL_LOW
#define LED4_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_HIGH

/* Wrapper macros to ensure common naming across all boards */
#define LED_4_NAME      "blue LED4"
#define PIN_LED_4       {PIO_PC6, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_LED_4_MASK   PIO_PC6
#define PIN_LED_4_PIO    PIOC
#define PIN_LED_4_ID     ID_PIOC
#define PIN_LED_4_TYPE   PIO_OUTPUT_1
#define PIN_LED_4_ATTR   PIO_DEFAULT
/* @} */

/**
 * \name Console UART definitions
 * @{
 */
#define CONSOLE_UART      UART0
#define CONSOLE_UART_ID   ID_UART0
/* @} */

/**
 * \name UART0 pin (UTXD0 and URXD0) definitions
 * @{
 */
#define PINS_UART0        (PIO_PB4A_URXD0 | PIO_PB5A_UTXD0)
#define PINS_UART0_FLAGS  (IOPORT_MODE_MUX_A)

#define PINS_UART0_PORT   IOPORT_PIOB
#define PINS_UART0_MASK   (PIO_PB4A_URXD0 | PIO_PB5A_UTXD0)
#define PINS_UART0_PIO    PIOB
#define PINS_UART0_ID     ID_PIOB
#define PINS_UART0_TYPE   PIO_PERIPH_A
#define PINS_UART0_ATTR   PIO_DEFAULT
/* @} */

/**
 * \name UART1 pin (UTXD1 and URXD1) definitions
 * @{
 */
#define PINS_UART1        (PIO_PC1A_URXD1 | PIO_PC0A_UTXD1)
#define PINS_UART1_FLAGS  (IOPORT_MODE_MUX_A)

#define PINS_UART1_PORT   IOPORT_PIOC
#define PINS_UART1_MASK   (PIO_PC1A_URXD1 | PIO_PC0A_UTXD1)
#define PINS_UART1_PIO    PIOC
#define PINS_UART1_ID     ID_PIOC
#define PINS_UART1_TYPE   PIO_PERIPH_A
#define PINS_UART1_ATTR   PIO_DEFAULT
/* @} */

/**
 * \name SPI pin definitions
 * @{
 */
/** SPI0 MISO pin definition. */
#define SPI0_MISO_GPIO         (PIO_PA6_IDX)
#define SPI0_MISO_FLAGS        (IOPORT_MODE_MUX_A)
/** SPI0 MOSI pin definition. */
#define SPI0_MOSI_GPIO         (PIO_PA7_IDX)
#define SPI0_MOSI_FLAGS        (IOPORT_MODE_MUX_A)
/** SPI0 SPCK pin definition. */
#define SPI0_SPCK_GPIO         (PIO_PA8_IDX)
#define SPI0_SPCK_FLAGS        (IOPORT_MODE_MUX_A)
/** SPI0 chip select 1 pin definition. */
#define SPI0_NPCS1_GPIO        (PIO_PA21_IDX)
#define SPI0_NPCS1_FLAGS       (IOPORT_MODE_MUX_A)
/** SPI0 chip select 3 pin definition. */
#define SPI0_NPCS3_GPIO        (PIO_PA23_IDX)
#define SPI0_NPCS3_FLAGS       (IOPORT_MODE_MUX_A)
/* @} */

/* Select the SPI module that AT25DFx is connected to */
#define AT25DFX_SPI_MODULE     SPI0

/* Chip select used by AT25DFx components on the SPI module instance */
#define AT25DFX_CS             1

/**
 * \name TWIx pin definitions
 * @{
 */
/*! TWI ID for EEPROM application to use */
#define BOARD_ID_TWI_EEPROM       ID_TWI0

/*! TWI Base for TWI EEPROM application to use */
#define BOARD_BASE_TWI_EEPROM     TWI0
#define BOARD_AT24C_TWI_INSTANCE  TWI0
#define BOARD_AT24C_ADDRESS       0x50u

/*! TWI Base for TWI Temperature Sensor application to use */
#define BOARD_AT30TSE_TWI         TWI0
#define BOARD_AT30TSE_DEVICE_ADDR 0x48u
#define BOARD_AT30TSE_TWI_ID      ID_TWI0
#define BOARD_USING_AT30TSE       AT30TS75

/*! TWI Base for TWI Crypto Authentication application to use */
#define BOARD_ATSHA204_TWI         TWI0
#define BOARD_ATSHA204_DEVICE_ADDR 0xc9u
#define BOARD_ATSHA204_TWI_ID      ID_TWI0

/*! TWI0 Data pin for EEPROM */
#define TWIO_DATA_GPIO            PIO_PA24_IDX
#define TWIO_DATA_FLAG            IOPORT_MODE_MUX_A
/*! TWI0 Clock pin for EEPROM */
#define TWIO_CLK_GPIO             PIO_PA25_IDX
#define TWIO_CLK_FLAG             IOPORT_MODE_MUX_A
#define BOARD_CLK_TWI_EEPROM      TWIO_CLK_GPIO
#define BOARD_CLK_TWI_MUX_EEPROM  TWIO_CLK_FLAG
/* @} */

/**
 * \name PCK pin definitions
 * @{
 */
#define PIN_PCK0        (PIO_PB13_IDX)
#define PIN_PCK0_MUX    (IOPORT_MODE_MUX_A)
/* @} */

/* @} */ /* End of sam4cmp_db_features_group */

/* @} */ /* End of sam4cmp_db_group */

#endif  /* SAM4CMP_DB_H_INCLUDED */

