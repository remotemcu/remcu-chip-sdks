/**
 * \file
 *
 * \brief SAM4CP16BMB Board Definition.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef SAM4CP16BMB_H_INCLUDED
#define SAM4CP16BMB_H_INCLUDED

#include "compiler.h"
#include "conf_board.h"

/**
 * \ingroup group_common_boards
 * \defgroup sam4cp16bmb_group "SAM4CP16BMB"
 * Evaluation Board for SAM4CP16B devices.
 *
 * @{
 */

/**
 * \defgroup sam4cp16bmb_board_info_group "SAM4CP16BMB - Board informations"
 * Definitions related to the board description.
 *
 * @{
 */

/** Name of the board */
#define BOARD_NAME "SAM4CP16BMB"
/** Board definition */
#define sam4cp16bmb
/** Family definition (already defined) */
#define sam4cp
/** Core definition */
#define cortexm4
/** Board revision definition */
#define BOARD_REV_1     1
#define BOARD_REV_2     2

#ifndef BOARD_REV
#define BOARD_REV BOARD_REV_2
#endif



/* @} */

/**
 *  \defgroup sam4cp16bmb_opfreq_group "SAM4CP16BMB - Operating frequencies"
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
#define BOARD_FREQ_MAINCK_BYPASS    (10000000U)
/* @} */

/** Master clock frequency */
#define BOARD_MCK                   CHIP_FREQ_CPU_MAX

/** board main clock xtal statup time */
#define BOARD_OSC_STARTUP_US        15625U

/* @} */

/**
 * \defgroup sam4cp16bmb_features_group "SAM4CP16BMB - Features"
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

/**
 * \name LED #0 pin definition
 * @{
 */
#define LED0_GPIO            (PIO_PB14_IDX)
#define LED0_ACTIVE_LEVEL    IOPORT_PIN_LEVEL_LOW
#define LED0_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_HIGH

/* Wrapper macros to ensure common naming across all boards */
#define LED_0_NAME      "green LED (D5)"
#define PIN_LED_0       {PIO_PB14, PIOB, ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_LED_0_MASK   PIO_PB14
#define PIN_LED_0_PIO    PIOB
#define PIN_LED_0_ID     ID_PIOB
#define PIN_LED_0_TYPE   PIO_OUTPUT_1
#define PIN_LED_0_ATTR   PIO_DEFAULT
/* @} */

/**
 * \name LED #1 pin definition
 * @{
 */
#define LED1_GPIO            (PIO_PB15_IDX)
#define LED1_ACTIVE_LEVEL    IOPORT_PIN_LEVEL_LOW
#define LED1_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_HIGH

/* Wrapper macros to ensure common naming across all boards */
#define LED_1_NAME      "red LED (D6)"
#define PIN_LED_1       {PIO_PB15, PIOB, ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_LED_1_MASK   PIO_PB15
#define PIN_LED_1_PIO    PIOB
#define PIN_LED_1_ID     ID_PIOB
#define PIN_LED_1_TYPE   PIO_OUTPUT_1
#define PIN_LED_1_ATTR   PIO_DEFAULT
/* @} */

/** Push button #0 definition. Attributes = pull-up + debounce + interrupt on rising edge. */
#define PUSHBUTTON_1_NAME    "WAKEUP"
#define GPIO_PUSH_BUTTON_1   (PIO_PB3_IDX)
#define GPIO_PUSH_BUTTON_1_FLAGS    (PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE)

#define PIN_PUSHBUTTON_1    {PIO_PB3, PIOB, ID_PIOB, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE}	
#define PIN_PUSHBUTTON_1_MASK PIO_PB3
#define PIN_PUSHBUTTON_1_PIO PIOB
#define PIN_PUSHBUTTON_1_ID ID_PIOB
#define PIN_PUSHBUTTON_1_TYPE PIO_INPUT
#define PIN_PUSHBUTTON_1_ATTR PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE

/** Push button #1 definition. Attributes = pull-up + debounce + interrupt on falling edge. */
#define PUSHBUTTON_2_NAME    "TMP0"
#define GPIO_PUSH_BUTTON_2   (PIO_PC12_IDX)
#define GPIO_PUSH_BUTTON_2_FLAGS    (PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE)

#define PIN_PUSHBUTTON_2    {PIO_PC12, PIOC, ID_PIOC, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE}
#define PIN_PUSHBUTTON_2_MASK PIO_PC12
#define PIN_PUSHBUTTON_2_PIO PIOC
#define PIN_PUSHBUTTON_2_ID ID_PIOC
#define PIN_PUSHBUTTON_2_TYPE PIO_INPUT
#define PIN_PUSHBUTTON_2_ATTR PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS    PIN_PUSHBUTTON_1, PIN_PUSHBUTTON_2



/**
 * \name Voltage Monitor pins definition
 * @{
 */
#define V5V_SENSE_GPIO   PIO_PB23_IDX
#define VDD_SENSE_GPIO   PIO_PB31_IDX
/* @} */

/**
 * \name LCD Backlight
 */
//@{
#define LCD_BL                        PA29
#define LCD_BL_GPIO                   PIO_PA29_IDX
#define LCD_BL_GPIO_MASK              PIO_PA29

#define LCD_BL_ACTIVE_LEVEL             IOPORT_PIN_LEVEL_HIGH
#define LCD_BL_INACTIVE_LEVEL           IOPORT_PIN_LEVEL_LOW
//@}

/**
* \name LCD Enable
*/
//@{
#define LCD_EN                        PB12
#define LCD_EN_GPIO                   PIO_PB12_IDX
#define LCD_EN_GPIO_MASK              PIO_PB12

#if BOARD_REV == BOARD_REV_1
  #define LCD_EN_ACTIVE_LEVEL             IOPORT_PIN_LEVEL_LOW
  #define LCD_EN_INACTIVE_LEVEL           IOPORT_PIN_LEVEL_HIGH
#elif BOARD_REV == BOARD_REV_2
  #define LCD_EN_ACTIVE_LEVEL             IOPORT_PIN_LEVEL_HIGH
  #define LCD_EN_INACTIVE_LEVEL           IOPORT_PIN_LEVEL_LOW
#else
  #error No known SAM4CP16BMB revision board defined
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

/**
 * \name TWIx pin definitions
 * @{
 */
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

/** USART1 pin RX */
#define PIN_USART1_RXD_IDX    (PIO_PA11_IDX)
#define PIN_USART1_RXD_FLAGS  (IOPORT_MODE_MUX_A)
/** USART1 pin TX */
#define PIN_USART1_TXD_IDX    (PIO_PA12_IDX)
#define PIN_USART1_TXD_FLAGS  (IOPORT_MODE_MUX_A)
/** USART1 pin CTS */
#define PIN_USART1_CTS_IDX    (PIO_PA18_IDX)
#define PIN_USART1_CTS_FLAGS  (IOPORT_MODE_MUX_A)
/** USART1 pin RTS */
#define PIN_USART1_RTS_IDX    (PIO_PA17_IDX)
#define PIN_USART1_RTS_FLAGS  (IOPORT_MODE_MUX_A)

/* @} */

/**
 * \name ADC Xplain PRO pin definitions
 * @{
 */
#define XP_ADC_GPIO   PIO_PA4_IDX
/* @} */
   
/**
 * \name SLP Xplain PRO pin definition
 * @{
 */
#define XP_SLP_GPIO             (PIO_PC8_IDX)
#define XP_SLP_ACTIVE_LEVEL    IOPORT_PIN_LEVEL_HIGH
#define XP_SLP_INACTIVE_LEVEL  IOPORT_PIN_LEVEL_LOW

/* Wrapper macros to ensure common naming across all boards */
#define XP_SLP       {PIO_PC8, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
#define XP_SLP_MASK   PIO_PC8
#define XP_SLP_PIO    PIOC
#define XP_SLP_ID     ID_PIOC
#define XP_SLP_TYPE   PIO_OUTPUT_1
#define XP_SLP_ATTR   PIO_DEFAULT
/* @} */

/* @} */ /* End of sam4cp16bmb_features_group */

/* @} */ /* End of sam4cp16bmb_group */

#endif  /* SAM4CP16BMB_H_INCLUDED */

