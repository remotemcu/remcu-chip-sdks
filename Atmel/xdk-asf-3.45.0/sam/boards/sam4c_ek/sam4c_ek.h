/**
 * \file
 *
 * \brief SAM4C-EK Board Definition.
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

#ifndef SAM4C_EK_H_INCLUDED
#define SAM4C_EK_H_INCLUDED

#include "compiler.h"

/**
 * \ingroup group_common_boards
 * \defgroup sam4c_ek_group "SAM4C-EK"
 * Evaluation Kit for SAM4C devices.
 *
 * @{
 */

/**
 * \defgroup sam4c_ek_board_info_group "SAM4C-EK - Board informations"
 * Definitions related to the board description.
 *
 * @{
 */

/** Name of the board */
#define BOARD_NAME "SAM4C-EK"
/** Board definition */
#define sam4cek
/** Family definition (already defined) */
#define sam4c
/** Core definition */
#define cortexm4
/** Board revision definition */
#define BOARD_REV_C

/* @} */

/**
 *  \defgroup sam4c_ek_opfreq_group "SAM4C-EK - Operating frequencies"
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
#define BOARD_FREQ_MAINCK_XTAL      (8000000U)
#define BOARD_FREQ_MAINCK_BYPASS    (8000000U)
/* @} */

/** Master clock frequency */
#define BOARD_MCK                   CHIP_FREQ_CPU_MAX

/** board main clock xtal startup time */
#define BOARD_OSC_STARTUP_US        15625U

/* @} */

/**
 * \defgroup sam4c_ek_features_group "SAM4C-EK - Features"
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

/**
 * \name LED #0 pin definition
 * @{
 */
#define LED0_GPIO            (PIO_PC6_IDX)
#define LED0_ACTIVE_LEVEL    IOPORT_PIN_LEVEL_LOW
#define LED0_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_HIGH

/* Wrapper macros to ensure common naming across all boards */
#define LED_0_NAME      "green LED (D10)"
#define PIN_LED_0       {PIO_PC6, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_LED_0_MASK   PIO_PC6
#define PIN_LED_0_PIO    PIOC
#define PIN_LED_0_ID     ID_PIOC
#define PIN_LED_0_TYPE   PIO_OUTPUT_1
#define PIN_LED_0_ATTR   PIO_DEFAULT
/* @} */

/**
 * \name LED #1 pin definition
 * @{
 */
#define LED1_GPIO            (PIO_PC7_IDX)
#define LED1_ACTIVE_LEVEL    IOPORT_PIN_LEVEL_LOW
#define LED1_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_HIGH

/* Wrapper macros to ensure common naming across all boards */
#define LED_1_NAME      "amber LED (D9)"
#define PIN_LED_1       {PIO_PC7, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_LED_1_MASK   PIO_PC7
#define PIN_LED_1_PIO    PIOC
#define PIN_LED_1_ID     ID_PIOC
#define PIN_LED_1_TYPE   PIO_OUTPUT_1
#define PIN_LED_1_ATTR   PIO_DEFAULT
/* @} */

/**
 * \name LED #2 pin definition
 * @{
 */
#define LED2_GPIO            (PIO_PC8_IDX)
#define LED2_ACTIVE_LEVEL    IOPORT_PIN_LEVEL_LOW
#define LED2_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_HIGH

/* Wrapper macros to ensure common naming across all boards */
#define LED_2_NAME      "blue LED (D8)"
#define PIN_LED_2       {PIO_PC8, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_LED_2_MASK   PIO_PC8
#define PIN_LED_2_PIO    PIOC
#define PIN_LED_2_ID     ID_PIOC
#define PIN_LED_2_TYPE   PIO_OUTPUT_1
#define PIN_LED_2_ATTR   PIO_DEFAULT
/* @} */

/**
 * \name LCD Backlight
 */
//@{
#define LCD_BL                        PA13
#define LCD_BL_GPIO                   PIO_PA13_IDX
#define LCD_BL_GPIO_MASK              PIO_PA13

#define LCD_BL_ACTIVE_LEVEL             IOPORT_PIN_LEVEL_LOW
#define LCD_BL_INACTIVE_LEVEL           IOPORT_PIN_LEVEL_HIGH
//@}

/**
 * \name Push button #1 definition
 * Attributes = pull-up + debounce + interrupt on rising edge.
 * @{
 */
#define PUSHBUTTON_1_NAME        "SCROLL_DOWN (BP5)"
#define GPIO_PUSH_BUTTON_1       (PIO_PA20_IDX)
#define GPIO_PUSH_BUTTON_1_FLAGS (IOPORT_MODE_PULLUP | IOPORT_MODE_DEBOUNCE)
#define GPIO_PUSH_BUTTON_1_SENSE (IOPORT_SENSE_RISING)

#define PIN_PUSHBUTTON_1       {PIO_PA20, PIOA, ID_PIOA, PIO_INPUT, \
		PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
#define PIN_PUSHBUTTON_1_MASK  PIO_PA20
#define PIN_PUSHBUTTON_1_PIO   PIOA
#define PIN_PUSHBUTTON_1_ID    ID_PIOA
#define PIN_PUSHBUTTON_1_TYPE  PIO_INPUT
#define PIN_PUSHBUTTON_1_ATTR  (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)
#define PIN_PUSHBUTTON_1_IRQn  PIOA_IRQn
/* @} */

/**
 * \name Push button #2 definition
 * Attributes = pull-up + debounce + interrupt on rising edge.
 * @{
 */
#define PUSHBUTTON_2_NAME        "SCROLL_UP (BP4)"
#define PUSHBUTTON_2_WKUP_LINE   (4)
#define PUSHBUTTON_2_WKUP_FSTT   (PMC_FSMR_FSTT4)
#define GPIO_PUSH_BUTTON_2       (PIO_PA19_IDX)
#define GPIO_PUSH_BUTTON_2_FLAGS (IOPORT_MODE_PULLUP | IOPORT_MODE_DEBOUNCE)
#define GPIO_PUSH_BUTTON_2_SENSE (IOPORT_SENSE_RISING)

#define PIN_PUSHBUTTON_2       {PIO_PA19, PIOA, ID_PIOA, PIO_INPUT, \
		PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
#define PIN_PUSHBUTTON_2_MASK  PIO_PA19
#define PIN_PUSHBUTTON_2_PIO   PIOA
#define PIN_PUSHBUTTON_2_ID    ID_PIOA
#define PIN_PUSHBUTTON_2_TYPE  PIO_INPUT
#define PIN_PUSHBUTTON_2_ATTR  (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)
#define PIN_PUSHBUTTON_2_IRQn  PIOA_IRQn
/* @} */

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS    {PIN_PUSHBUTTON_1, PIN_PUSHBUTTON_2}

/**
 * \name TC pins definition
 * @{
 */
#define PIN_TC0_TIOA0        (PIO_PA13_IDX)
#define PIN_TC0_TIOA0_MUX    (IOPORT_MODE_MUX_B)
#define PIN_TC0_TIOA0_FLAGS  (IOPORT_MODE_MUX_B)

#define PIN_TC0_TIOA1        (PIO_PB7_IDX)
#define PIN_TC0_TIOA1_MUX    (IOPORT_MODE_MUX_A)
#define PIN_TC0_TIOA1_FLAGS  (IOPORT_MODE_MUX_A)

#define PIN_TC0_TIOA1_PIO    PIOB
#define PIN_TC0_TIOA1_MASK   PIO_PB7
#define PIN_TC0_TIOA1_ID     ID_PIOB
#define PIN_TC0_TIOA1_TYPE   PIO_PERIPH_A
#define PIN_TC0_TIOA1_ATTR   PIO_DEFAULT

#define PIN_TC0_TIOA2        (PIO_PB10_IDX)
#define PIN_TC0_TIOA2_MUX    (IOPORT_MODE_MUX_A)
#define PIN_TC0_TIOA2_FLAGS  (IOPORT_MODE_MUX_A)

#define PIN_TC0_TIOA2_PIO    PIOB
#define PIN_TC0_TIOA2_MASK   PIO_PB10
#define PIN_TC0_TIOA2_ID     ID_PIOB
#define PIN_TC0_TIOA2_TYPE   PIO_PERIPH_A
#define PIN_TC0_TIOA2_ATTR   PIO_DEFAULT
/* @} */

/**
 * \name Console UART definitions
 * @{
 */
#define CONSOLE_UART      UART0
#define CONSOLE_UART_ID   ID_UART0
/* @} */

/**
 * \name UART0 pis (UTXD0 and URXD0) definitions
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
 * \name UART1 pis (UTXD1 and URXD1) definitions
 * @{
 */
#define PINS_UART1        (PIO_PC0A_URXD0 | PIO_PC1A_UTXD0)
#define PINS_UART1_FLAGS  (IOPORT_MODE_MUX_A)

#define PINS_UART1_PORT   IOPORT_PIOC
#define PINS_UART1_MASK   (PIO_PC0A_URXD0 | PIO_PC1A_UTXD0)
#define PINS_UART1_PIO    PIOC
#define PINS_UART1_ID     ID_PIOC
#define PINS_UART1_TYPE   PIO_PERIPH_A
#define PINS_UART1_ATTR   PIO_DEFAULT
/* @} */

/**
 * \name PWM LEDx pin definitions
 * @{
 */
/** PWM LED Green pin definitions. */
#define PIN_PWM_LED0_GPIO     PIO_PC6_IDX
#define PIN_PWM_LED0_FLAGS    (IOPORT_MODE_MUX_A)
#define PIN_PWM_LED0_CHANNEL  PWM_CHANNEL_0

/** PWM LED Amber pin definitions. */
#define PIN_PWM_LED1_GPIO     PIO_PC7_IDX
#define PIN_PWM_LED1_FLAGS    (IOPORT_MODE_MUX_A)
#define PIN_PWM_LED1_CHANNEL  PWM_CHANNEL_1

/** PWM LED Blue pin definitions. */
#define PIN_PWM_LED2_GPIO     PIO_PC8_IDX
#define PIN_PWM_LED2_FLAGS    (IOPORT_MODE_MUX_A)
#define PIN_PWM_LED2_CHANNEL  PWM_CHANNEL_2
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
/** SPI0 chip select 0 pin definition. */
#define SPI0_NPCS0_GPIO        (PIO_PA5_IDX)
#define SPI0_NPCS0_FLAGS       (IOPORT_MODE_MUX_A)

/** SPI1 MISO pin definition. */
#define SPI1_MISO_GPIO         (PIO_PC3_IDX)
#define SPI1_MISO_FLAGS        (IOPORT_MODE_MUX_A)
/** SPI1 MOSI pin definition. */
#define SPI1_MOSI_GPIO         (PIO_PC4_IDX)
#define SPI1_MOSI_FLAGS        (IOPORT_MODE_MUX_A)
/** SPI1 SPCK pin definition. */
#define SPI1_SPCK_GPIO         (PIO_PC5_IDX)
#define SPI1_SPCK_FLAGS        (IOPORT_MODE_MUX_A)
/** SPI1 chip select 0 pin definition. */
#define SPI1_NPCS0_GPIO        (PIO_PC2_IDX)
#define SPI1_NPCS0_FLAGS       (IOPORT_MODE_MUX_A)
/* @} */

/* Select the SPI module that AT25DFx is connected to */
#define AT25DFX_SPI_MODULE     SPI0

/* Chip select used by AT25DFx components on the SPI module instance */
#define AT25DFX_CS             0

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
#define BOARD_AT30TSE_TWI         TWI0
#define BOARD_AT30TSE_DEVICE_ADDR 0
#define BOARD_AT30TSE_TWI_ID      ID_TWI0
#define BOARD_USING_AT30TSE       AT30TS75

/*! TWI0 Data pin for EEPROM */
#define TWIO_DATA_GPIO            PIO_PA24_IDX
#define TWIO_DATA_FLAG            IOPORT_MODE_MUX_A
/*! TWI0 Clock pin for EEPROM */
#define TWIO_CLK_GPIO             PIO_PA25_IDX
#define TWIO_CLK_FLAG             IOPORT_MODE_MUX_A
#define BOARD_CLK_TWI_EEPROM      TWIO_CLK_GPIO
#define BOARD_CLK_TWI_MUX_EEPROM  TWIO_CLK_FLAG

/*! TWI1 Data pin for EEPROM */
#define TWI1_DATA_GPIO            PIO_PB0_IDX
#define TWI1_DATA_FLAG            IOPORT_MODE_MUX_A
/*! TWI1 Clock pin for EEPROM */
#define TWI1_CLK_GPIO             PIO_PB1_IDX
#define TWI1_CLK_FLAG             IOPORT_MODE_MUX_A
/* @} */

/**
 * \name PCK pin definitions
 * @{
 */
#define PIN_PCK2        (PIO_PA0_IDX)
#define PIN_PCK2_MUX    (IOPORT_MODE_MUX_B)
/* @} */

/**
 * \name USARTx pin definitions
 * @{
 */
/** USART0 pin RX */
#define PIN_USART0_RXD_IDX    (PIO_PB16_IDX)
#define PIN_USART0_RXD_FLAGS  (IOPORT_MODE_MUX_A)
/** USART0 pin TX */
#define PIN_USART0_TXD_IDX    (PIO_PB17_IDX)
#define PIN_USART0_TXD_FLAGS  (IOPORT_MODE_MUX_A)
/** USART0 pin CTS */
#define PIN_USART0_CTS_IDX    (PIO_PA20_IDX)
#define PIN_USART0_CTS_FLAGS  (IOPORT_MODE_MUX_A)
/** USART0 pin RTS */
#define PIN_USART0_RTS_IDX    (PIO_PA19_IDX)
#define PIN_USART0_RTS_FLAGS  (IOPORT_MODE_MUX_A)
/** USART0 pin SCK */
#define PIN_USART0_SCK_IDX    (PIO_PB18_IDX)
#define PIN_USART0_SCK_FLAGS  (IOPORT_MODE_MUX_A)

/** USART1 pin CTS */
#define PIN_USART1_CTS_IDX    (PIO_PA18_IDX)
#define PIN_USART1_CTS_FLAGS  (IOPORT_MODE_MUX_A)
/** USART1 pin RTS */
#define PIN_USART1_RTS_IDX    (PIO_PA17_IDX)
#define PIN_USART1_RTS_FLAGS  (IOPORT_MODE_MUX_A)
/** USART1 pin RX */
#define PIN_USART1_RXD_IDX    (PIO_PA11_IDX)
#define PIN_USART1_RXD_FLAGS  (IOPORT_MODE_MUX_A)
/** USART1 pin SCK */
#define PIN_USART1_SCK_IDX    (PIO_PA16_IDX)
#define PIN_USART1_SCK_FLAGS  (IOPORT_MODE_MUX_A)
/** USART1 pin TX */
#define PIN_USART1_TXD_IDX    (PIO_PA12_IDX)
#define PIN_USART1_TXD_FLAGS  (IOPORT_MODE_MUX_A)

/** USART2 pin CTS */
#define PIN_USART2_CTS_IDX    (PIO_PA15_IDX)
#define PIN_USART2_CTS_FLAGS  (IOPORT_MODE_MUX_A)
/** USART2 pin RTS */
#define PIN_USART2_RTS_IDX    (PIO_PA14_IDX)
#define PIN_USART2_RTS_FLAGS  (IOPORT_MODE_MUX_A)
/** USART2 pin RX */
#define PIN_USART2_RXD_IDX    (PIO_PA9_IDX)
#define PIN_USART2_RXD_FLAGS  (IOPORT_MODE_MUX_A)
/** USART2 pin SCK */
#define PIN_USART2_SCK_IDX    (PIO_PA13_IDX)
#define PIN_USART2_SCK_FLAGS  (IOPORT_MODE_MUX_A)
/** USART2 pin TX */
#define PIN_USART2_TXD_IDX    (PIO_PA10_IDX)
#define PIN_USART2_TXD_FLAGS  (IOPORT_MODE_MUX_A)

/* IRDA SD pin. */
#define PIN_IRDA_SD_IDX       PIN_USART2_CTS_IDX
#define PIN_IRDA_SD_FLAGS     (0)
/* TXD pin configuration. */
#define PIN_USART_TXD_IDX          PIN_USART2_TXD_IDX
#define PIN_USART_TXD_FLAGS        (IOPORT_MODE_MUX_A)
#define PIN_USART_TXD_IO_FLAGS     (0)

/* RS485 RE pin. */
#define PIN_RE_IDX                 PIN_USART2_CTS_IDX
#define PIN_RE_FLAGS               (0)

/* ISO7816 pin. */
#define ISO7816_USART_ID           ID_USART2
#define ISO7816_USART              USART2
#define PIN_ISO7816_RST_IDX        PIO_PA15_IDX
#define PIN_ISO7816_RST_FLAG       (0)
/* @} */

/**
 * \name ADC pin definitions
 * @{
 */
#define PINS_ADC_TRIG       PIO_PB23_IDX
#define PINS_ADC_TRIG_FLAG  IOPORT_MODE_MUX_A
/* @} */

/**
 * \name EBI pin definitions
 * @{
 */
// TBD
/* @} */


/* @} */ /* End of sam4c_ek_features_group */

/* @} */ /* End of sam4c_ek_group */

#endif  /* SAM4C_EK_H_INCLUDED */

