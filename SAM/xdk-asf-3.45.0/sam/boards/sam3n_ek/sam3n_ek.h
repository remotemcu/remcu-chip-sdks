/**
 * \file
 *
 * \brief SAM3N-EK Board Definition.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _SAM3N_EK_H_
#define _SAM3N_EK_H_

#include "compiler.h"
#include "system_sam3n.h"
#include "exceptions.h"

/*----------------------------------------------------------------------------*/
/**
 *  \page sam3n_ek_opfreq "SAM3N-EK - Operating frequencies"
 *  This page lists several definition related to the board operating frequency
 *
 *  \section Definitions
 *  - \ref BOARD_FREQ_*
 *  - \ref BOARD_MCK
 */

/** Board oscillator settings */
#define BOARD_FREQ_SLCK_XTAL		(32768U)
#define BOARD_FREQ_SLCK_BYPASS		(32768U)
#define BOARD_FREQ_MAINCK_XTAL		(12000000U)
#define BOARD_FREQ_MAINCK_BYPASS	(12000000U)

/** Master clock frequency */
#define BOARD_MCK					CHIP_FREQ_CPU_MAX

/** board main clock xtal startup time */
#define BOARD_OSC_STARTUP_US   15625

/*----------------------------------------------------------------------------*/
/**
 * \page sam3n_ek_board_info "SAM3N-EK - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "SAM3N-EK"
/** Board definition */
#define sam3nek
/** Family definition (already defined) */
#define sam3n
/** Core definition */
#define cortexm3

/* ===============  LED =============== */
#define LED_0_NAME    "blue LED D1"
#define LED0_GPIO     (PIO_PA23_IDX)
#define LED0_FLAGS    (PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED0_ACTIVE_LEVEL 0

#define PIN_LED_0_MASK PIO_PA23
#define PIN_LED_0_PIO PIOA
#define PIN_LED_0_ID ID_PIOA
#define PIN_LED_0_TYPE PIO_OUTPUT_1
#define PIN_LED_0_ATTR PIO_DEFAULT

#define LED_1_NAME    "green LED D2"
#define LED1_GPIO     (PIO_PB14_IDX)
#define LED1_FLAGS    (PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED1_ACTIVE_LEVEL 0

#define PIN_LED_1_MASK PIO_PB14
#define PIN_LED_1_PIO PIOB
#define PIN_LED_1_ID ID_PIOB
#define PIN_LED_1_TYPE PIO_OUTPUT_1
#define PIN_LED_1_ATTR PIO_DEFAULT

#define LED_2_NAME    "amber LED D3"
#define LED2_GPIO     (PIO_PA25_IDX)
#define LED2_FLAGS    (PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED2_ACTIVE_LEVEL 0

#define PIN_LED_2_MASK PIO_PA25
#define PIN_LED_2_PIO PIOA
#define PIN_LED_2_ID ID_PIOA
#define PIN_LED_2_TYPE PIO_OUTPUT_1
#define PIN_LED_2_ATTR PIO_DEFAULT

#define LED_3_NAME    "red LED D4"
#define LED3_GPIO     (PIO_PA0_IDX)
#define LED3_FLAGS    (PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED3_ACTIVE_LEVEL 1

#define PIN_LED_3_MASK PIO_PA0
#define PIN_LED_3_PIO PIOA
#define PIN_LED_3_ID ID_PIOA
#define PIN_LED_3_TYPE PIO_OUTPUT_1
#define PIN_LED_3_ATTR PIO_DEFAULT

#define BOARD_NUM_OF_LED 4

/* ===============  ADC =============== */
#define PINS_ADC_TRIG  PIO_PA8_IDX
#define PINS_ADC_TRIG_FLAG  (PIO_PERIPH_B | PIO_DEFAULT)

/* =============== UART0 =============== */
#define PINS_UART0        (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0)
#define PINS_UART0_FLAGS  (PIO_PERIPH_A | PIO_DEFAULT)

#define PINS_UART0_MASK     (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0)
#define PINS_UART0_PIO      PIOA
#define PINS_UART0_ID       ID_PIOA
#define PINS_UART0_TYPE     PIO_PERIPH_A
#define PINS_UART0_ATTR     PIO_DEFAULT

/* =============== UART1 =============== */
#define PINS_UART1          (PIO_PB2A_URXD1 | PIO_PB3A_UTXD1)
#define PINS_UART1_FLAGS    (PIO_PERIPH_A | PIO_DEFAULT)

#define PINS_UART1_MASK     (PIO_PB2A_URXD1 | PIO_PB3A_UTXD1)
#define PINS_UART1_PIO      PIOB
#define PINS_UART1_ID       ID_PIOB
#define PINS_UART1_TYPE     PIO_PERIPH_A
#define PINS_UART1_ATTR     PIO_DEFAULT

/* =============== SPI =============== */
/** SPI MISO pin definition. */
#define SPI_MISO_GPIO        (PIO_PA12_IDX)
#define SPI_MISO_FLAGS       (PIO_PERIPH_A | PIO_DEFAULT)
/** SPI MOSI pin definition. */
#define SPI_MOSI_GPIO        (PIO_PA13_IDX)
#define SPI_MOSI_FLAGS       (PIO_PERIPH_A | PIO_DEFAULT)
/** SPI SPCK pin definition. */
#define SPI_SPCK_GPIO        (PIO_PA14_IDX)
#define SPI_SPCK_FLAGS       (PIO_PERIPH_A | PIO_DEFAULT)

/** SPI chip select 0 pin definition. (Only one configuration is possible) */
#define SPI_NPCS0_GPIO            (PIO_PA11_IDX)
#define SPI_NPCS0_FLAGS           (PIO_PERIPH_A | PIO_DEFAULT)
/** SPI chip select 1 pin definition. (multiple configurations are possible) */
#define SPI_NPCS1_PA9_GPIO        (PIO_PA9_IDX)
#define SPI_NPCS1_PA9_FLAGS       (PIO_PERIPH_B | PIO_DEFAULT)
#define SPI_NPCS1_PA31_GPIO       (PIO_PA31_IDX)
#define SPI_NPCS1_PA31_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
#define SPI_NPCS1_PB14_GPIO       (PIO_PB14_IDX)
#define SPI_NPCS1_PB14_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
#define SPI_NPCS1_PC4_GPIO        (PIO_PC4_IDX)
#define SPI_NPCS1_PC4_FLAGS       (PIO_PERIPH_B | PIO_DEFAULT)
/** SPI chip select 2 pin definition. (multiple configurations are possible) */
#define SPI_NPCS2_PA10_GPIO       (PIO_PA10_IDX)
#define SPI_NPCS2_PA10_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)
#define SPI_NPCS2_PA30_GPIO       (PIO_PA30_IDX)
#define SPI_NPCS2_PA30_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)
#define SPI_NPCS2_PB2_GPIO        (PIO_PB2_IDX)
#define SPI_NPCS2_PB2_FLAGS       (PIO_PERIPH_B | PIO_DEFAULT)
#define SPI_NPCS2_PC7_GPIO        (PIO_PC7_IDX)
#define SPI_NPCS2_PC7_FLAGS       (PIO_PERIPH_B | PIO_DEFAULT)
/** SPI chip select 3 pin definition. (multiple configurations are possible) */
#define SPI_NPCS3_PA3_GPIO        (PIO_PA3_IDX)
#define SPI_NPCS3_PA3_FLAGS       (PIO_PERIPH_B | PIO_DEFAULT)
#define SPI_NPCS3_PA5_GPIO        (PIO_PA5_IDX)
#define SPI_NPCS3_PA5_FLAGS       (PIO_PERIPH_B | PIO_DEFAULT)
#define SPI_NPCS3_PA22_GPIO       (PIO_PA22_IDX)
#define SPI_NPCS3_PA22_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)

/* =============== Push Buttons =============== */
#define PUSHBUTTON_1_NAME           "USRPB1"
#define GPIO_PUSH_BUTTON_1          (PIO_PA15_IDX)
#define GPIO_PUSH_BUTTON_1_FLAGS    (PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)

#define PIN_PUSHBUTTON_1_MASK PIO_PA15
#define PIN_PUSHBUTTON_1_PIO PIOA
#define PIN_PUSHBUTTON_1_ID ID_PIOA
#define PIN_PUSHBUTTON_1_TYPE PIO_INPUT
#define PIN_PUSHBUTTON_1_ATTR PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE

#define PUSHBUTTON_2_NAME           "USRPB2"
#define GPIO_PUSH_BUTTON_2          (PIO_PA16_IDX)
#define GPIO_PUSH_BUTTON_2_FLAGS    (PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE)

#define PIN_PUSHBUTTON_2_MASK PIO_PA16
#define PIN_PUSHBUTTON_2_PIO PIOA
#define PIN_PUSHBUTTON_2_ID ID_PIOA
#define PIN_PUSHBUTTON_2_TYPE PIO_INPUT
#define PIN_PUSHBUTTON_2_ATTR PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE

/* =============== LCD =============== */
/** LCD SPI configuration */
#define BOARD_ILI9225_SPI         SPI
#define BOARD_ILI9225_SPI_IRQN    SPI_IRQn
#define BOARD_ILI9225_SPI_NPCS    2

/** LCD Register Select pin definition */
#define BOARD_ILI9225_RS_GPIO     PIO_PA28_IDX
#define BOARD_ILI9225_RS_FLAGS    PIO_OUTPUT_1 | PIO_DEFAULT

/** LCD Reset pin definition: active low */
#define BOARD_ILI9225_RSTN_GPIO   PIO_PA29_IDX
#define BOARD_ILI9225_RSTN_FLAGS  PIO_OUTPUT_1 | PIO_DEFAULT

/** LCD backlight definition */
#define BOARD_AAT31XX_SET_GPIO    PIO_PC13_IDX
#define BOARD_AAT31XX_SET_FLAGS   PIO_OUTPUT_1 | PIO_DEFAULT

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

/* =============== PWM for LEDs =============== */
/** PWM LED0 pin definitions. */
#define PIN_PWM_LED0_GPIO    PIO_PA23_IDX
#define PIN_PWM_LED0_FLAGS   (PIO_PERIPH_B | PIO_DEFAULT)
#define PIN_PWM_LED0_CHANNEL PWM_CHANNEL_0

/** PWM LED1 pin definitions. */
#define PIN_PWM_LED1_GPIO    PIO_PB14_IDX
#define PIN_PWM_LED1_FLAGS   (PIO_PERIPH_B | PIO_DEFAULT)
#define PIN_PWM_LED1_CHANNEL PWM_CHANNEL_3

/* =============== TWI =============== */
/** TWI0 pins definition */
#define TWI0_DATA_GPIO   PIO_PA3_IDX
#define TWI0_DATA_FLAGS  (PIO_PERIPH_A | PIO_DEFAULT)
#define TWI0_CLK_GPIO    PIO_PA4_IDX
#define TWI0_CLK_FLAGS   (PIO_PERIPH_A | PIO_DEFAULT)

/** TWI1 pins definition */
#define TWI1_DATA_GPIO   PIO_PB4_IDX
#define TWI1_DATA_FLAGS  (PIO_PERIPH_A | PIO_DEFAULT)
#define TWI1_CLK_GPIO    PIO_PB5_IDX
#define TWI1_CLK_FLAGS   (PIO_PERIPH_A | PIO_DEFAULT)

/* =============== PCK =============== */
/** PCK0 pin definition. */
#define PIN_PCK0        (PIO_PA6_IDX)
#define PIN_PCK0_MUX    (IOPORT_MODE_MUX_B)
#define PIN_PCK0_FLAGS  (PIO_PERIPH_B | PIO_DEFAULT)

#define PIN_PCK_0_MASK PIO_PA6
#define PIN_PCK_0_PIO PIOA
#define PIN_PCK_0_ID ID_PIOA
#define PIN_PCK_0_TYPE PIO_PERIPH_B
#define PIN_PCK_0_ATTR PIO_DEFAULT
/** PCK1 pin definition. */
#define PIN_PCK1        (PIO_PA17_IDX)
#define PIN_PCK1_FLAGS  (PIO_PERIPH_B | PIO_DEFAULT)

#define PIN_PCK_1_MASK PIO_PA17
#define PIN_PCK_1_PIO PIOA
#define PIN_PCK_1_ID ID_PIOA
#define PIN_PCK_1_TYPE PIO_PERIPH_B
#define PIN_PCK_1_ATTR PIO_DEFAULT

/* =============== USART =============== */
/** RXD0 pin definition. */
#define PIN_USART0_RXD_IDX        (PIO_PA5_IDX)
#define PIN_USART0_RXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** TXD0 pin definition. */
#define PIN_USART0_TXD_IDX        (PIO_PA6_IDX)
#define PIN_USART0_TXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** RTS0 pin definition. */
#define PIN_USART0_RTS_IDX        (PIO_PA7_IDX)
#define PIN_USART0_RTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** CTS0 pin definition. */
#define PIN_USART0_CTS_IDX        (PIO_PA8_IDX)
#define PIN_USART0_CTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin ENABLE */
#define PIN_USART0_EN_IDX         (PIO_PA2_IDX)
#define PIN_USART0_EN_FLAGS       (PIO_OUTPUT_0 | PIO_DEFAULT)
/** SCK0 pin definition. */
#define PIN_USART0_SCK_IDX        (PIO_PA2_IDX)
#define PIN_USART0_SCK_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)

/** RXD1 pin definition. */
#define PIN_USART1_RXD_IDX        (PIO_PA21_IDX)
#define PIN_USART1_RXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** TXD1 pin definition. */
#define PIN_USART1_TXD_IDX        (PIO_PA22_IDX)
#define PIN_USART1_TXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** RTS1 pin definition. */
#define PIN_USART1_RTS_IDX        (PIO_PA24_IDX)
#define PIN_USART1_RTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** CTS1 pin definition. */
#define PIN_USART1_CTS_IDX        (PIO_PA25_IDX)
#define PIN_USART1_CTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART1 pin ENABLE */
#define PIN_USART1_EN_IDX         (PIO_PA23_IDX)
#define PIN_USART1_EN_FLAGS       (PIO_OUTPUT_0 | PIO_DEFAULT)
/** SCK1 pin definition. */
#define PIN_USART1_SCK_IDX        (PIO_PA23_IDX)
#define PIN_USART1_SCK_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)

/*----------------------------------------------------------------------------*/
/**
 * \page sam3n_ek_mem "SAM3N-EK - Memories"
 * This page lists definitions related to internal & external on-board memories.
 *
 * \section SRAM
 * - \ref AT91C_IRAM
 * - \ref AT91C_IRAM_SIZE
 *
 * \section Flash
 * - \ref AT91C_IFLASH_SIZE
 * - \ref AT91C_IFLASH_PAGE_SIZE
 * - \ref AT91C_IFLASH_NB_OF_PAGES
 * - \ref AT91C_IFLASH_LOCK_REGION_SIZE
 * - \ref AT91C_IFLASH_NB_OF_LOCK_BITS
 */
/* Add new memories here. */


/*----------------------------------------------------------------------------*/
/**
 *  \page sam3n_ek_lcd "SAM3N-EK - LCD parameters"
 *  This page lists several definition related to the lcd parameters
 *
 *  \section Definitions
 *  - \ref BOARD_LCD_SPCK
 *  - \ref BOARD_LCD_NPCS
 *  - \ref BOARD_LCD_DLYBS
 *  - \ref BOARD_LCD_DLYBCT
 *  - \ref BOARD_LCD_WIDTH
 *  - \ref BOARD_LCD_HEIGHT
 */
/** LCD Spi Clock frequency */
#define BOARD_LCD_SPCK             (BOARD_MCK)
/** LCD Spi Chip Select */
#define BOARD_LCD_NPCS              2
/** LCD Spi Delay Before SPCK: >=10ns */
#define BOARD_LCD_DLYBS             1
/** LCD Spi DLYBCT: Delay Between Consecutive Transfers */
#define BOARD_LCD_DLYBCT            0
/** Display width in pixels. */
#define BOARD_LCD_WIDTH             176
/** Display height in pixels. */
#define BOARD_LCD_HEIGHT            220


/*----------------------------------------------------------------------------*/
/**
 *  \page sam3n_ek_sd "SAM3N-EK - SD(SPI) parameters"
 *  This page lists several definition related to the SD(SPI) parameters
 *
 *  \section Definitions
 *  - \ref BOARD_SD_SPCK
 *  - \ref BOARD_SD_PIN_CD
 *  - \ref BOARD_SD_SPI_BASE
 *  - \ref BOARD_SD_SPI_ID
 *  - \ref BOARD_SD_SPI_PINS
 *  - \ref BOARD_SD_SPI_IRQn
 *  - \ref BOARD_SD_NPCS
 */
/** SD/MMC Spi Clock frequency */
#define BOARD_SD_SPCK               10000000ul
/** SD/MMC Card Detect */
#define BOARD_SD_PIN_CD             {PIO_PA19, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP}
/** SD Spi Base */
#define BOARD_SD_SPI_BASE           SPI
/** SD Spi ID */
#define BOARD_SD_SPI_ID             ID_SPI
/** SD Spi Pins (and init other used NPCS to avoid conflict) */
#define BOARD_SD_SPI_PINS           PINS_SDCARD 
/** SD SPI IRQn */
#define BOARD_SD_SPI_IRQn           SPI_IRQn
/** SD Spi Chip Select */
#define BOARD_SD_NPCS               0
/** Defines required by SD MMC Stack */
#define SD_MMC_SPI_MEM_CNT          1
#define SD_MMC_0_CD_GPIO            (PIO_PA19_IDX)
#define SD_MMC_0_CD_PIO_ID          ID_PIOA
#define SD_MMC_0_CD_FLAGS           (PIO_INPUT | PIO_PULLUP)
#define SD_MMC_0_CD_DETECT_VALUE    0
#define SD_MMC_SPI                  BOARD_SD_SPI_BASE
#define SD_MMC_SPI_0_CS             BOARD_SD_NPCS

/*----------------------------------------------------------------------------*/
#define CONSOLE_UART               UART0
#define CONSOLE_UART_ID            ID_UART0

/* RE pin. */
#define PIN_RE_IDX                 PIN_USART0_CTS_IDX
#define PIN_RE_FLAGS               (PIO_OUTPUT_0 | PIO_DEFAULT)

/* IRDA SD pin. */
#define PIN_IRDA_SD_IDX            PIN_USART0_CTS_IDX
#define PIN_IRDA_SD_FLAGS          (PIO_OUTPUT_1 | PIO_DEFAULT)

/* TXD pin configuration. */
#define PIN_USART_TXD_IDX          PIN_USART0_TXD_IDX
#define PIN_USART_TXD_FLAGS        (PIO_PERIPH_A | PIO_DEFAULT)
#define PIN_USART_TXD_IO_FLAGS     (PIO_OUTPUT_0 | PIO_DEFAULT)

/* ISO7816 example relate PIN definition. */
#define ISO7816_USART_ID           ID_USART0
#define ISO7816_USART              USART0
#define PIN_ISO7816_RST_IDX        PIO_PA15_IDX
#define PIN_ISO7816_RST_FLAG       (PIO_OUTPUT_0 | PIO_DEFAULT)

/* Select the SPI module that AT25DFx is connected to */
#define AT25DFX_SPI_MODULE          SPI

/* Chip select used by AT25DFx components on the SPI module instance */
#define AT25DFX_CS      3

#endif  // _SAM3N_EK_H_
