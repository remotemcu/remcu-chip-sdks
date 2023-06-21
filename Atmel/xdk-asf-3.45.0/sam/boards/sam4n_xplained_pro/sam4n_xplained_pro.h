/**
 * \file
 *
 * \brief SAM4N Xplained Pro board definition and driver
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
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef SAM4N_XPLAINED_PRO_H
#define SAM4N_XPLAINED_PRO_H

#include <conf_board.h>

/**
 * \ingroup group_common_boards
 * \defgroup sam4n_xplained_pro_group SAM4N Xplained Pro board
 * @{
 */


/**
 * \defgroup sam4n_xplained_pro_config_group Configuration
 *
 * Symbols to use for configuring the board and its initialization.
 *
 * @{
 */
#ifdef __DOXYGEN__

//! \name Initialization
//@{

/**
 * \def CONF_BOARD_KEEP_WATCHDOG_AT_INIT
 * \brief Let watchdog remain enabled
 *
 * If this symbol is defined, the watchdog is left running with its current
 * configuration. Otherwise, it gets disabled during board initialization.
 */
# ifndef CONF_BOARD_KEEP_WATCHDOG_AT_INIT
#  define CONF_BOARD_KEEP_WATCHDOG_AT_INIT
# endif

//@}

#endif // __DOXYGEN__
/** @} */


/**
 * \defgroup sam4n_xplained_pro_features_group Features
 *
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

//! Name string macro
#define BOARD_NAME                "SAM4N_XPLAINED_PRO"

//! \name Resonator definitions
//@{
#define BOARD_FREQ_SLCK_XTAL      (32768U)
#define BOARD_FREQ_SLCK_BYPASS    (32768U)
#define BOARD_FREQ_MAINCK_XTAL    (12000000U)
#define BOARD_FREQ_MAINCK_BYPASS  (12000000U)
#define BOARD_MCK                 CHIP_FREQ_CPU_MAX
#define BOARD_OSC_STARTUP_US      15625
//@}

//! \name LED0 definitions
//@{
#define LED0_GPIO                     PIO_PB14_IDX
#define LED0_ACTIVE_LEVEL               false
#define LED0_INACTIVE_LEVEL             !LED0_ACTIVE_LEVEL
//@}

//! \name SW0 definitions
//@{
#define SW0_PIN                   IOPORT_CREATE_PIN(PIOA, 30)
#define SW0_ACTIVE                false
#define SW0_INACTIVE              !SW0_ACTIVE
#define SW0_SUPC_INPUT            2

/**
 * Wrapper macros for SW0, to ensure common naming across all Xplained Pro
 * boards.
 */
#define PIN_SW0      {PIO_PA30, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
#define PIN_SW0_MASK PIO_PA30
#define PIN_SW0_PIO  PIOA
#define PIN_SW0_ID   ID_PIOA
#define PIN_SW0_TYPE PIO_INPUT
#define PIN_SW0_ATTR (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)
//@}

/**
 * \name LED #0 definitions
 *
 * Wrapper macros for LED0, to ensure common naming across all Xplained Pro
 * boards.
 */
//@{
#define LED_0_NAME                "LED0 (yellow)"
#define LED_0_PIN                 LED0_GPIO
#define LED_0_ACTIVE              LED0_ACTIVE_LEVEL
#define LED_0_INACTIVE            LED0_INACTIVE_LEVEL

#define PIN_LED_0      {PIO_PB14, PIOB, ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_LED_0_MASK PIO_PB14
#define PIN_LED_0_PIO  PIOB
#define PIN_LED_0_ID   ID_PIOB
#define PIN_LED_0_TYPE PIO_OUTPUT_1
#define PIN_LED_0_ATTR PIO_DEFAULT
//@}

//! Number of on-board LEDs
#define LED_COUNT 1

/**
 * \name Button #0 definitions
 *
 * Wrapper macros for SW0, to ensure common naming across all Xplained Pro
 * boards.
 */
//@{
#define BUTTON_0_NAME             "SW0"
#define BUTTON_0_PIN              SW0_PIN
#define BUTTON_0_ACTIVE           SW0_ACTIVE
#define BUTTON_0_INACTIVE         SW0_INACTIVE
#define BUTTON_0_SUPC_INPUT       SW0_SUPC_INPUT

#define PUSHBUTTON_1_NAME    "SW0"
#define PIN_PUSHBUTTON_1 {PIO_PA30, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
#define PIN_PUSHBUTTON_1_MASK PIO_PA30
#define PIN_PUSHBUTTON_1_PIO  PIOA
#define PIN_PUSHBUTTON_1_ID   ID_PIOA
#define PIN_PUSHBUTTON_1_TYPE PIO_INPUT
#define PIN_PUSHBUTTON_1_ATTR PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE
//@}

//! Number of on-board buttons
#define BUTTON_COUNT              1

//! \name Extension header #1 pin definitions
//@{
#define EXT1_PIN_3                IOPORT_CREATE_PIN(PIOA, 17)
#define EXT1_PIN_4                IOPORT_CREATE_PIN(PIOA, 18)
#define EXT1_PIN_5                IOPORT_CREATE_PIN(PIOA, 24)
#define EXT1_PIN_6                IOPORT_CREATE_PIN(PIOA, 25)
#define EXT1_PIN_7                IOPORT_CREATE_PIN(PIOC, 23)
#define EXT1_PIN_8                IOPORT_CREATE_PIN(PIOC, 24)
#define EXT1_PIN_9                IOPORT_CREATE_PIN(PIOA, 0)
#define EXT1_PIN_10               IOPORT_CREATE_PIN(PIOA, 23)
#define EXT1_PIN_11               IOPORT_CREATE_PIN(PIOA, 3)
#define EXT1_PIN_12               IOPORT_CREATE_PIN(PIOA, 4)
#define EXT1_PIN_13               IOPORT_CREATE_PIN(PIOA, 21)
#define EXT1_PIN_14               IOPORT_CREATE_PIN(PIOA, 22)
#define EXT1_PIN_15               IOPORT_CREATE_PIN(PIOA, 11)
#define EXT1_PIN_16               IOPORT_CREATE_PIN(PIOA, 13)
#define EXT1_PIN_17               IOPORT_CREATE_PIN(PIOA, 12)
#define EXT1_PIN_18               IOPORT_CREATE_PIN(PIOA, 14)
//@}

//! \name Extension header #2 pin definitions
//@{
#define EXT2_PIN_3                IOPORT_CREATE_PIN(PIOA, 19)
#define EXT2_PIN_4                IOPORT_CREATE_PIN(PIOA, 20)
#define EXT2_PIN_5                IOPORT_CREATE_PIN(PIOC, 0)
#define EXT2_PIN_6                IOPORT_CREATE_PIN(PIOC, 1)
#define EXT2_PIN_7                IOPORT_CREATE_PIN(PIOC, 26)
#define EXT2_PIN_8                IOPORT_CREATE_PIN(PIOC, 27)
#define EXT2_PIN_9                IOPORT_CREATE_PIN(PIOA, 1)
#define EXT2_PIN_10               IOPORT_CREATE_PIN(PIOC, 8)
#define EXT2_PIN_11               IOPORT_CREATE_PIN(PIOB, 0)
#define EXT2_PIN_12               IOPORT_CREATE_PIN(PIOB, 1)
#define EXT2_PIN_13               IOPORT_CREATE_PIN(PIOA, 5)
#define EXT2_PIN_14               IOPORT_CREATE_PIN(PIOA, 6)
#define EXT2_PIN_15               IOPORT_CREATE_PIN(PIOC, 4)
#define EXT2_PIN_16               IOPORT_CREATE_PIN(PIOA, 13)
#define EXT2_PIN_17               IOPORT_CREATE_PIN(PIOA, 12)
#define EXT2_PIN_18               IOPORT_CREATE_PIN(PIOA, 14)
//@}

//! \name Extension header #3 pin definitions
//@{
#define EXT3_PIN_3                IOPORT_CREATE_PIN(PIOC, 29)
#define EXT3_PIN_4                IOPORT_CREATE_PIN(PIOC, 30)
#define EXT3_PIN_5                IOPORT_CREATE_PIN(PIOC, 2)
#define EXT3_PIN_6                IOPORT_CREATE_PIN(PIOC, 3)
#define EXT3_PIN_7                IOPORT_CREATE_PIN(PIOA, 26)
#define EXT3_PIN_8                IOPORT_CREATE_PIN(PIOA, 27)
#define EXT3_PIN_9                IOPORT_CREATE_PIN(PIOB, 2)
#define EXT3_PIN_10               IOPORT_CREATE_PIN(PIOB, 3)
#define EXT3_PIN_11               IOPORT_CREATE_PIN(PIOA, 3)
#define EXT3_PIN_12               IOPORT_CREATE_PIN(PIOA, 4)
#define EXT3_PIN_13               IOPORT_CREATE_PIN(PIOA, 9)
#define EXT3_PIN_14               IOPORT_CREATE_PIN(PIOA, 10)
#define EXT3_PIN_15               IOPORT_CREATE_PIN(PIOC, 7)
#define EXT3_PIN_16               IOPORT_CREATE_PIN(PIOA, 13)
#define EXT3_PIN_17               IOPORT_CREATE_PIN(PIOA, 12)
#define EXT3_PIN_18               IOPORT_CREATE_PIN(PIOA, 14)
//@}

//! \name Embedded debugger GPIO interface definitions
//@{
#define EDBG_GPIO0_PIN            IOPORT_CREATE_PIN(PIOC, 21)
#define EDBG_GPIO1_PIN            IOPORT_CREATE_PIN(PIOC, 20)
#define EDBG_GPIO2_PIN            IOPORT_CREATE_PIN(PIOC, 19)
#define EDBG_GPIO3_PIN            IOPORT_CREATE_PIN(PIOC, 18)
//@}

//! \name Embedded debugger USART interface definitions
//@{
#define EDBG_UART_MODULE          USART2
//@}

//! \name Embedded debugger TWI interface definitions
//@{
#define EDBG_TWI_MODULE           TWI2
//@}

#define CONSOLE_UART              UART0
#define CONSOLE_UART_ID        ID_UART0

/** UART0 pins (UTXD0 and URXD0) definitions, PA9,10. */
#define PINS_UART0        (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0)
#define PINS_UART0_FLAGS  (IOPORT_MODE_MUX_A)

#define PINS_UART0_PORT   IOPORT_PIOA
#define PINS_UART0_MASK   (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0)
#define PINS_UART0_PIO    PIOA
#define PINS_UART0_ID     ID_PIOA
#define PINS_UART0_TYPE   PIO_PERIPH_A
#define PINS_UART0_ATTR   PIO_DEFAULT

/** UART3 pins (UTXD3 and URXD3) definitions, PB10,11. */
#define PINS_UART3        (PIO_PB10B_URXD3 | PIO_PB11B_UTXD3)
#define PINS_UART3_FLAGS  (IOPORT_MODE_MUX_B)

#define PINS_UART3_PORT   IOPORT_PIOB
#define PINS_UART3_MASK   (PIO_PB10B_URXD3 | PIO_PB11B_UTXD3)
#define PINS_UART3_PIO    PIOB
#define PINS_UART3_ID     ID_PIOB
#define PINS_UART3_TYPE   PIO_PERIPH_B
#define PINS_UART3_ATTR   PIO_DEFAULT

#define PIN_TC0_TIOA0         (PIO_PA0_IDX)
#define PIN_TC0_TIOA0_MUX     (IOPORT_MODE_MUX_B)
#define PIN_TC0_TIOA0_FLAGS   (PIO_PERIPH_B | PIO_DEFAULT)

#define PIN_TC0_TIOA1         (PIO_PA15_IDX)
#define PIN_TC0_TIOA1_MUX     (IOPORT_MODE_MUX_B)
#define PIN_TC0_TIOA1_FLAGS   (PIO_PERIPH_B | PIO_DEFAULT)

#define PIN_TC0_TIOA1_PIO     PIOA
#define PIN_TC0_TIOA1_MASK    PIO_PA15
#define PIN_TC0_TIOA1_ID      ID_PIOA
#define PIN_TC0_TIOA1_TYPE    PIO_PERIPH_B
#define PIN_TC0_TIOA1_ATTR    PIO_DEFAULT

#define PIN_TC0_TIOA2         (PIO_PA26_IDX)
#define PIN_TC0_TIOA2_MUX     (IOPORT_MODE_MUX_B)
#define PIN_TC0_TIOA2_FLAGS   (PIO_PERIPH_B | PIO_DEFAULT)

#define PIN_TC0_TIOA2_PIO     PIOA
#define PIN_TC0_TIOA2_MASK    PIO_PA26
#define PIN_TC0_TIOA2_ID      ID_PIOA
#define PIN_TC0_TIOA2_TYPE    PIO_INPUT
#define PIN_TC0_TIOA2_ATTR    PIO_DEFAULT

//! \name SPI
//@{
/** SPI MISO pin definition. */
#define SPI_MISO_GPIO         (PIO_PA12_IDX)
#define SPI_MISO_FLAGS       (IOPORT_MODE_MUX_A)
/** SPI MOSI pin definition. */
#define SPI_MOSI_GPIO         (PIO_PA13_IDX)
#define SPI_MOSI_FLAGS       (IOPORT_MODE_MUX_A)
/** SPI SPCK pin definition. */
#define SPI_SPCK_GPIO         (PIO_PA14_IDX)
#define SPI_SPCK_FLAGS       (IOPORT_MODE_MUX_A)

/** SPI chip select 0 pin definition. */
#define SPI_NPCS0_GPIO        (PIO_PA11_IDX)
#define SPI_NPCS0_FLAGS      (IOPORT_MODE_MUX_A)
/** SPI chip select 1 pin definition. */
#define SPI_NPCS1_GPIO        (PIO_PC4_IDX)
#define SPI_NPCS1_FLAGS      (IOPORT_MODE_MUX_B)
/** SPI chip select 2 pin definition. */
#define SPI_NPCS2_GPIO        (PIO_PC7_IDX)
#define SPI_NPCS2_FLAGS      (IOPORT_MODE_MUX_B)

//@}

//! \name OLED
//@{
/** OLED command/data select pin */
#define UG_2832HSWEG04_DATA_CMD_GPIO   (PIO_PC2_IDX)
/** OLED reset pin */
#define UG_2832HSWEG04_RESET_GPIO      (PIO_PB3_IDX)
/** OLED SPI configuration */
#define UG_2832HSWEG04_SS               2
#define UG_2832HSWEG04_BAUDRATE         5000000
//! \name OLED dimensions
//@{
#define LCD_WIDTH_PIXELS                (128)
#define LCD_HEIGHT_PIXELS               (32)
//@}
//@}

//! \name TWI
//@{
/** TWI0 pin definitions */
#define TWI0_DATA_GPIO   PIO_PA3_IDX
#define TWI0_DATA_FLAGS  IOPORT_MODE_MUX_A
#define TWI0_CLK_GPIO    PIO_PA4_IDX
#define TWI0_CLK_FLAGS   IOPORT_MODE_MUX_A
/** TWI1 pin definitions */
#define TWI1_DATA_GPIO   PIO_PB4_IDX
#define TWI1_DATA_FLAGS  IOPORT_MODE_MUX_A
#define TWI1_CLK_GPIO    PIO_PB5_IDX
#define TWI1_CLK_FLAGS   IOPORT_MODE_MUX_A
/** TWI2 pin definitions */
#define TWI2_DATA_GPIO   PIO_PB0_IDX
#define TWI2_DATA_FLAGS  IOPORT_MODE_MUX_B
#define TWI2_CLK_GPIO    PIO_PB1_IDX
#define TWI2_CLK_FLAGS   IOPORT_MODE_MUX_B
//@}

/** PCK0 pin definition (PA6) */
#define PIN_PCK0         (PIO_PA6_IDX)
#define PIN_PCK0_MUX     (IOPORT_MODE_MUX_B)
#define PIN_PCK0_FLAGS   (IOPORT_MODE_MUX_B)
#define PIN_PCK0_PORT    IOPORT_PIOA
#define PIN_PCK0_MASK    PIO_PA6B_PCK0
#define PIN_PCK0_PIO     PIOA
#define PIN_PCK0_ID      ID_PIOA
#define PIN_PCK0_TYPE    PIO_PERIPH_B
#define PIN_PCK0_ATTR    PIO_DEFAULT

/** USART0 pin RX */
#define PIN_USART0_RXD        {PIO_PA5A_RXD0, PIOA, ID_PIOA, PIO_PERIPH_A, \
		PIO_DEFAULT}
#define PIN_USART0_RXD_IDX    (PIO_PA5_IDX)
#define PIN_USART0_RXD_FLAGS  (IOPORT_MODE_MUX_A)
/** USART0 pin TX */
#define PIN_USART0_TXD        {PIO_PA6A_TXD0, PIOA, ID_PIOA, PIO_PERIPH_A, \
		PIO_DEFAULT}
#define PIN_USART0_TXD_IDX    (PIO_PA6_IDX)
#define PIN_USART0_TXD_FLAGS  (IOPORT_MODE_MUX_A)
/** USART0 pin CTS */
#define PIN_USART0_CTS        {PIO_PA8A_CTS0, PIOA, ID_PIOA, PIO_PERIPH_A, \
		PIO_DEFAULT}
#define PIN_USART0_CTS_IDX    (PIO_PA8_IDX)
#define PIN_USART0_CTS_FLAGS  (IOPORT_MODE_MUX_A)
/** USART0 pin RTS */
#define PIN_USART0_RTS        {PIO_PA7A_RTS0, PIOA, ID_PIOA, PIO_PERIPH_A, \
		PIO_DEFAULT}
#define PIN_USART0_RTS_IDX    (PIO_PA7_IDX)
#define PIN_USART0_RTS_FLAGS  (IOPORT_MODE_MUX_A)
/** USART0 pin SCK */
#define PIN_USART0_SCK        {PIO_PA2B_SCK0, PIOA, ID_PIOA, PIO_PERIPH_B, \
		PIO_DEFAULT}
#define PIN_USART0_SCK_IDX    (PIO_PA2_IDX)
#define PIN_USART0_SCK_FLAGS  (IOPORT_MODE_MUX_B)

/** USART1 pin RX */
#define PIN_USART1_RXD        {PIO_PA21A_RXD1, PIOA, ID_PIOA, PIO_PERIPH_A, \
		PIO_DEFAULT}
#define PIN_USART1_RXD_IDX    (PIO_PA21_IDX)
#define PIN_USART1_RXD_FLAGS  (IOPORT_MODE_MUX_A)
/** USART1 pin TX */
#define PIN_USART1_TXD        {PIO_PA22A_TXD1, PIOA, ID_PIOA, PIO_PERIPH_A, \
		PIO_DEFAULT}
#define PIN_USART1_TXD_IDX    (PIO_PA22_IDX)
#define PIN_USART1_TXD_FLAGS  (IOPORT_MODE_MUX_A)
/** USART1 pin CTS */
#define PIN_USART1_CTS        {PIO_PA25A_CTS1, PIOA, ID_PIOA, PIO_PERIPH_A, \
		PIO_DEFAULT}
#define PIN_USART1_CTS_IDX    (PIO_PA25_IDX)
#define PIN_USART1_CTS_FLAGS  (IOPORT_MODE_MUX_A)
/** USART1 pin RTS */
#define PIN_USART1_RTS        {PIO_PA24A_RTS1, PIOA, ID_PIOA, PIO_PERIPH_A, \
		PIO_DEFAULT}
#define PIN_USART1_RTS_IDX    (PIO_PA24_IDX)
#define PIN_USART1_RTS_FLAGS  (IOPORT_MODE_MUX_A)
/** USART1 pin SCK */
#define PIN_USART1_SCK        {PIO_PA23A_SCK1, PIOA, ID_PIOA, PIO_PERIPH_A, \
		PIO_DEFAULT}
#define PIN_USART1_SCK_IDX    (PIO_PA23_IDX)
#define PIN_USART1_SCK_FLAGS  (IOPORT_MODE_MUX_A)

/** USART2 pin RX */
#define PIN_USART2_RXD        {PIO_PC9A_RXD2, PIOC, ID_PIOC, PIO_PERIPH_A, \
		PIO_DEFAULT}
#define PIN_USART2_RXD_IDX    (PIO_PC9_IDX)
#define PIN_USART2_RXD_FLAGS  (IOPORT_MODE_MUX_A)
/** USART2 pin TX */
#define PIN_USART2_TXD        {PIO_PC10A_TXD2, PIOC, ID_PIOC, PIO_PERIPH_A, \
		PIO_DEFAULT}
#define PIN_USART2_TXD_IDX    (PIO_PC10_IDX)
#define PIN_USART2_TXD_FLAGS  (IOPORT_MODE_MUX_A)
/** USART2 pin CTS */
#define PIN_USART2_CTS        {PIO_PC17A_CTS2, PIOC, ID_PIOC, PIO_PERIPH_A, \
		PIO_DEFAULT}
#define PIN_USART2_CTS_IDX    (PIO_PC17_IDX)
#define PIN_USART2_CTS_FLAGS  (IOPORT_MODE_MUX_A)
/** USART2 pin RTS */
#define PIN_USART2_RTS        {PIO_PC16A_RTS2, PIOC, ID_PIOC, PIO_PERIPH_A, \
		PIO_DEFAULT}
#define PIN_USART2_RTS_IDX    (PIO_PC16_IDX)
#define PIN_USART2_RTS_FLAGS  (IOPORT_MODE_MUX_A)
/** USART2 pin SCK */
#define PIN_USART2_SCK        {PIO_PC14A_SCK2, PIOC, ID_PIOC, PIO_PERIPH_A, \
		PIO_DEFAULT}
#define PIN_USART2_SCK_IDX    (PIO_PC14_IDX)
#define PIN_USART2_SCK_FLAGS  (IOPORT_MODE_MUX_A)

//! \name IO1 button definitions */
//@{
/** Push button #1 definition. Attributes = pull-up + debounce + interrupt on rising edge. */
#define PUSHBUTTON_1_NAME    "SW0"
#define GPIO_PUSH_BUTTON_1   (PIO_PA30_IDX)
#define GPIO_PUSH_BUTTON_1_FLAGS    (PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)
//@}

/* ISO7816 example relate PIN definition. */
#define ISO7816_USART_ID           ID_USART0
#define ISO7816_USART              USART0
#define PIN_ISO7816_RST_IDX        PIO_PA15_IDX
#define PIN_ISO7816_RST_FLAG       (0)

//! \name Light Sensor
//@{
#define LIGHT_SENSOR_GPIO   PIO_PA17_IDX
#define LIGHT_SENSOR_FLAGS  PIO_INPUT
//@}

//! \name IO1 SD card definitions */
//@{
#define SD_MMC_SPI_MEM_CNT          1
#define SD_MMC_0_CD_GPIO            (PIO_PA23_IDX)
#define SD_MMC_0_CD_DIR             (IOPORT_DIR_INPUT)
#define SD_MMC_0_CD_MODE            (IOPORT_MODE_PULLUP)
#define SD_MMC_0_CD_DETECT_VALUE    0
#define SD_MMC_SPI                  SPI
#define SD_MMC_SPI_0_CS             0
#define SD_MMC_0_CD_PIO_ID          ID_PIOA
/**
 * Wrapper macros for IO1 SD, to ensure common naming across all Xplained Pro
 * boards.
 */
#define SD_MMC_0_CD_FLAGS           (PIO_INPUT | PIO_PULLUP)
#define SD_MMC_0_CD    {PIO_PA23, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
#define SD_MMC_0_CD_MASK PIO_PA23
#define SD_MMC_0_CD_PIO PIOA
#define SD_MMC_0_CD_ID ID_PIOA
#define SD_MMC_0_CD_TYPE PIO_INPUT
#define SD_MMC_0_CD_ATTR (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_EDGE)
//@}


//! \name IO1 temperature sensor definitions */
//@{
#define BOARD_AT30TSE_TWI          TWI0
#define BOARD_AT30TSE_TWI_ID       ID_TWI0
#define BOARD_TWI_SPEED            (400000u)
#define BOARD_USING_AT30TSE        AT30TSE758
#define BOARD_AT30TSE_DEVICE_ADDR  0x07
//@}

//! \name OLED1 led definitions */
//@{
#define OLED1_LED1_PIN                  EXT3_PIN_7
#define OLED1_LED1_ACTIVE               false
#define OLED1_LED1_INACTIVE             !OLED1_LED1_ACTIVE

#define OLED1_LED2_PIN                  EXT3_PIN_8
#define OLED1_LED2_ACTIVE               false
#define OLED1_LED2_INACTIVE             !OLED1_LED2_ACTIVE

#define OLED1_LED3_PIN                  EXT3_PIN_6
#define OLED1_LED3_ACTIVE               false
#define OLED1_LED3_INACTIVE             !OLED1_LED3_ACTIVE
//@}

//! \name OLED1 button definitions */
//@{
/** Push button #1 definition. Attributes = pull-up + debounce + interrupt on rising edge. */
#define OLED1_PUSHBUTTON_1_NAME    "BUTTON 1"
#define OLED1_GPIO_PUSH_BUTTON_1   (PIO_PB2_IDX)
#define OLED1_GPIO_PUSH_BUTTON_1_FLAGS    (PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)

#define OLED1_PIN_PUSHBUTTON_1    {PIO_PB2, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
#define OLED1_PIN_PUSHBUTTON_1_MASK PIO_PB2
#define OLED1_PIN_PUSHBUTTON_1_PIO PIOB
#define OLED1_PIN_PUSHBUTTON_1_ID ID_PIOB
#define OLED1_PIN_PUSHBUTTON_1_TYPE PIO_INPUT
#define OLED1_PIN_PUSHBUTTON_1_ATTR (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)

/** Push button #2 definition. Attributes = pull-up + debounce + interrupt on rising edge. */
#define OLED1_PUSHBUTTON_2_NAME    "BUTTON 2"
#define OLED1_GPIO_PUSH_BUTTON_2   (PIO_PC29_IDX)
#define OLED1_GPIO_PUSH_BUTTON_2_FLAGS    (PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)

#define OLED1_PIN_PUSHBUTTON_2    {PIO_PC29, PIOC, ID_PIOC, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
#define OLED1_PIN_PUSHBUTTON_2_MASK PIO_PC29
#define OLED1_PIN_PUSHBUTTON_2_PIO PIOC
#define OLED1_PIN_PUSHBUTTON_2_ID ID_PIOC
#define OLED1_PIN_PUSHBUTTON_2_TYPE PIO_INPUT
#define OLED1_PIN_PUSHBUTTON_2_ATTR (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)

/** Push button #3 definition. Attributes = pull-up + debounce + interrupt on rising edge. */
#define OLED1_PUSHBUTTON_3_NAME    "BUTTON 3"
#define OLED1_GPIO_PUSH_BUTTON_3   (PIO_PC30_IDX)
#define OLED1_GPIO_PUSH_BUTTON_3_FLAGS    (PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)

#define OLED1_PIN_PUSHBUTTON_3    {PIO_PC30, PIOC, ID_PIOC, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
#define OLED1_PIN_PUSHBUTTON_3_MASK PIO_PC30
#define OLED1_PIN_PUSHBUTTON_3_PIO PIOC
#define OLED1_PIN_PUSHBUTTON_3_ID ID_PIOC
#define OLED1_PIN_PUSHBUTTON_3_TYPE PIO_INPUT
#define OLED1_PIN_PUSHBUTTON_3_ATTR (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)
//@}

/** @} */

/** @} */

#endif /* SAM4N_XPLAINED_PRO_H */
