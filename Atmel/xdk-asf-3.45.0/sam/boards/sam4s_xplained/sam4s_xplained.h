/**
 * \file
 *
 * \brief SAM4S-XPLAINED Board Definition.
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

#ifndef SAM4S_XPLAINED_H_INCLUDED
#define SAM4S_XPLAINED_H_INCLUDED

#include "compiler.h"
#include "system_sam4s.h"


//#define BOARD_REV_A
#define BOARD_REV_B

/*----------------------------------------------------------------------------*/
/**
 *  \page sam4s_xplained_opfreq "SAM4S-XPLAINED - Operating frequencies"
 *  This page lists several definition related to the board operating frequency
 *
 *  \section Definitions
 *  - \ref BOARD_FREQ_*
 *  - \ref BOARD_MCK
 */

/** Board oscillator settings */
#define BOARD_FREQ_SLCK_XTAL        (32768U)
#define BOARD_FREQ_SLCK_BYPASS      (32768U)
#define BOARD_FREQ_MAINCK_XTAL      (12000000U)
#define BOARD_FREQ_MAINCK_BYPASS    (12000000U)

/** Master clock frequency */
#define BOARD_MCK                   CHIP_FREQ_CPU_MAX

/** board main clock xtal startup time */
#define BOARD_OSC_STARTUP_US        15625

/*----------------------------------------------------------------------------*/
/**
 * \page sam4s_xplained_board_info "SAM4S-XPLAINED - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "SAM4S-XPLAINED"
/** Board definition */
#define sam4sxplained
/** Family definition (already defined) */
#define sam4s
/** Core definition */
#define cortexm3

/*----------------------------------------------------------------------------*/
/** Pins ADC */
#define PINS_ADC_TRIG      PIO_PA8_IDX
#define PINS_ADC_TRIG_FLAG (PIO_PERIPH_B | PIO_DEFAULT)

/** UART0 pins (UTXD0 and URXD0) definitions, PA9,10. */
#define PINS_UART0         (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0)
#define PINS_UART0_FLAGS   (PIO_PERIPH_A | PIO_DEFAULT)

#define PINS_UART0_MASK    PIO_PA9A_URXD0|PIO_PA10A_UTXD0
#define PINS_UART0_PIO     PIOA
#define PINS_UART0_ID      ID_PIOA
#define PINS_UART0_TYPE    PIO_PERIPH_A
#define PINS_UART0_ATTR    PIO_DEFAULT

/** UART1 pins (UTXD1 and URXD1) definitions, PB2,PB3. */
#define PINS_UART1         (PIO_PB2A_URXD1 | PIO_PB3A_UTXD1)
#define PINS_UART1_FLAGS   (PIO_PERIPH_A | PIO_DEFAULT)

#define PINS_UART1_MASK    PIO_PB2A_URXD1 | PIO_PB3A_UTXD1
#define PINS_UART1_PIO     PIOB
#define PINS_UART1_ID      ID_PIOB
#define PINS_UART1_TYPE    PIO_PERIPH_A
#define PINS_UART1_ATTR    PIO_DEFAULT

/** EBI Data Bus pins */
#define PIN_EBI_DATA_BUS_D0        PIO_PC0_IDX
#define PIN_EBI_DATA_BUS_D1        PIO_PC1_IDX
#define PIN_EBI_DATA_BUS_D2        PIO_PC2_IDX
#define PIN_EBI_DATA_BUS_D3        PIO_PC3_IDX
#define PIN_EBI_DATA_BUS_D4        PIO_PC4_IDX
#define PIN_EBI_DATA_BUS_D5        PIO_PC5_IDX
#define PIN_EBI_DATA_BUS_D6        PIO_PC6_IDX
#define PIN_EBI_DATA_BUS_D7        PIO_PC7_IDX
#define PIN_EBI_DATA_BUS_FLAGS     PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_DATA_BUS_MASK      0xFF
#define PIN_EBI_DATA_BUS_PIO       PIOC
#define PIN_EBI_DATA_BUS_ID        ID_PIOC
#define PIN_EBI_DATA_BUS_TYPE      PIO_PERIPH_A
#define PIN_EBI_DATA_BUS_ATTR      PIO_PULLUP
/** EBI NRD pin */
#define PIN_EBI_NRD       PIO_PC11_IDX
#define PIN_EBI_NRD_FLAGS PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_NRD_MASK  1 << 11
#define PIN_EBI_NRD_PIO   PIOC
#define PIN_EBI_NRD_ID    ID_PIOC
#define PIN_EBI_NRD_TYPE  PIO_PERIPH_A
#define PIN_EBI_NRD_ATTR  PIO_PULLUP
/** EBI NWE pin */
#define PIN_EBI_NWE       PIO_PC8_IDX
#define PIN_EBI_NWE_FLAGS PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_NWE_MASK  1 << 8
#define PIN_EBI_NWE_PIO   PIOC
#define PIN_EBI_NWE_ID    ID_PIOC
#define PIN_EBI_NWE_TYPE  PIO_PERIPH_A
#define PIN_EBI_NWE_ATTR  PIO_PULLUP
/** EBI NCS0 pin */
#define PIN_EBI_NCS0       PIO_PC14_IDX
#define PIN_EBI_NCS0_FLAGS PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_NCS0_MASK  1 << 14
#define PIN_EBI_NCS0_PIO   PIOC
#define PIN_EBI_NCS0_ID    ID_PIOC
#define PIN_EBI_NCS0_TYPE  PIO_PERIPH_A
#define PIN_EBI_NCS0_ATTR  PIO_PULLUP

/** EBI NLB pin */
#ifdef BOARD_REV_A
#define PIN_EBI_NLB           PIO_PC16_IDX
#endif
#ifdef BOARD_REV_B
#define PIN_EBI_NLB           PIO_PC15_IDX
#endif
#define PIN_EBI_NLB_FLAGS     PIO_OUTPUT_0

/** EBI address bus pins  */
#define PIN_EBI_ADDR_BUS_A0    PIO_PC18_IDX
#define PIN_EBI_ADDR_BUS_A1    PIO_PC19_IDX
#define PIN_EBI_ADDR_BUS_A2    PIO_PC20_IDX
#define PIN_EBI_ADDR_BUS_A3    PIO_PC21_IDX
#define PIN_EBI_ADDR_BUS_A4    PIO_PC22_IDX
#define PIN_EBI_ADDR_BUS_A5    PIO_PC23_IDX
#define PIN_EBI_ADDR_BUS_A6    PIO_PC24_IDX
#define PIN_EBI_ADDR_BUS_A7    PIO_PC25_IDX
#define PIN_EBI_ADDR_BUS_A8    PIO_PC26_IDX
#define PIN_EBI_ADDR_BUS_A9    PIO_PC27_IDX
#define PIN_EBI_ADDR_BUS_A10   PIO_PC28_IDX
#define PIN_EBI_ADDR_BUS_A11   PIO_PC29_IDX
#define PIN_EBI_ADDR_BUS_A12   PIO_PC30_IDX
#define PIN_EBI_ADDR_BUS_A13   PIO_PC31_IDX
#define PIN_EBI_ADDR_BUS_FLAG1 PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_ADDR_BUS_A14   PIO_PA18_IDX
#define PIN_EBI_ADDR_BUS_A15   PIO_PA19_IDX
#define PIN_EBI_ADDR_BUS_A16   PIO_PA20_IDX
#define PIN_EBI_ADDR_BUS_A17   PIO_PA0_IDX
#define PIN_EBI_ADDR_BUS_A18   PIO_PA1_IDX
#define PIN_EBI_ADDR_BUS_FLAG2 PIO_PERIPH_C | PIO_PULLUP

/** LED #0 pin definition. */
#ifdef BOARD_REV_A
#define LED_0_NAME     "LED D9"
#endif
#ifdef BOARD_REV_B
#define LED_0_NAME     "LED1"
#endif
#define PIN_LED_0      {PIO_PC10, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_LED_0_MASK PIO_PC10
#define PIN_LED_0_PIO  PIOC
#define PIN_LED_0_ID   ID_PIOC
#define PIN_LED_0_TYPE PIO_OUTPUT_1
#define PIN_LED_0_ATTR PIO_DEFAULT

#define LED0_GPIO  (PIO_PC10_IDX)
#define LED0_FLAGS (PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED0_ACTIVE_LEVEL 0

/** LED #1 pin definition. */
#ifdef BOARD_REV_A
#define LED_1_NAME     "LED D10"
#endif
#ifdef BOARD_REV_B
#define LED_1_NAME     "LED2"
#endif
#define PIN_LED_1      {PIO_PC17, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_LED_1_MASK PIO_PC17
#define PIN_LED_1_PIO  PIOC
#define PIN_LED_1_ID   ID_PIOC
#define PIN_LED_1_TYPE PIO_OUTPUT_1
#define PIN_LED_1_ATTR PIO_DEFAULT

#define LED1_GPIO  (PIO_PC17_IDX)
#define LED1_FLAGS (PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED1_ACTIVE_LEVEL 0

#define BOARD_NUM_OF_LED 2

/** Push button #0 definition. Attributes = pull-up + debounce + interrupt on rising edge. */
#ifdef BOARD_REV_A
#define PUSHBUTTON_1_NAME    "SW1"
#endif

#ifdef BOARD_REV_B
#define PUSHBUTTON_1_NAME    "BP2"
#endif
#define GPIO_PUSH_BUTTON_1       (PIO_PA5_IDX)
#define GPIO_PUSH_BUTTON_1_FLAGS (PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)

#define PIN_PUSHBUTTON_1 {PIO_PA5, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
#define PIN_PUSHBUTTON_1_MASK PIO_PA5
#define PIN_PUSHBUTTON_1_PIO  PIOA
#define PIN_PUSHBUTTON_1_ID   ID_PIOA
#define PIN_PUSHBUTTON_1_TYPE PIO_INPUT
#define PIN_PUSHBUTTON_1_ATTR PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS    PIN_PUSHBUTTON_1

#define PIN_TC0_TIOA0       (PIO_PA0_IDX)
#define PIN_TC0_TIOA0_MUX   (IOPORT_MODE_MUX_B)
#define PIN_TC0_TIOA0_FLAGS (PIO_PERIPH_B | PIO_DEFAULT)

#define PIN_TC0_TIOA1       (PIO_PA15_IDX)
#define PIN_TC0_TIOA1_MUX   (IOPORT_MODE_MUX_B)
#define PIN_TC0_TIOA1_FLAGS (PIO_PERIPH_B | PIO_DEFAULT)

#define PIN_TC0_TIOA1_PIO   PIOA
#define PIN_TC0_TIOA1_MASK  PIO_PA15
#define PIN_TC0_TIOA1_ID    ID_PIOA
#define PIN_TC0_TIOA1_TYPE  PIO_PERIPH_B
#define PIN_TC0_TIOA1_ATTR  PIO_DEFAULT

#define PIN_TC0_TIOA2       (PIO_PA26_IDX)
#define PIN_TC0_TIOA2_MUX   (IOPORT_MODE_MUX_B)
#define PIN_TC0_TIOA2_FLAGS (PIO_PERIPH_B | PIO_DEFAULT)

#define PIN_TC0_TIOA2_PIO   PIOA
#define PIN_TC0_TIOA2_MASK  PIO_PA26
#define PIN_TC0_TIOA2_ID    ID_PIOA
#define PIN_TC0_TIOA2_TYPE  PIO_INPUT
#define PIN_TC0_TIOA2_ATTR  PIO_DEFAULT

/** SPI MISO pin definition. */
#define SPI_MISO_GPIO  (PIO_PA12_IDX)
#define SPI_MISO_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)
/** SPI MOSI pin definition. */
#define SPI_MOSI_GPIO  (PIO_PA13_IDX)
#define SPI_MOSI_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)
/** SPI SPCK pin definition. */
#define SPI_SPCK_GPIO  (PIO_PA14_IDX)
#define SPI_SPCK_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)

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
/** SPI chip select 3 pin definition. (multiple configurations are possible) */
#define SPI_NPCS3_PA3_GPIO        (PIO_PA3_IDX)
#define SPI_NPCS3_PA3_FLAGS       (PIO_PERIPH_B | PIO_DEFAULT)
#define SPI_NPCS3_PA5_GPIO        (PIO_PA5_IDX)
#define SPI_NPCS3_PA5_FLAGS       (PIO_PERIPH_B | PIO_DEFAULT)
#define SPI_NPCS3_PA22_GPIO       (PIO_PA22_IDX)
#define SPI_NPCS3_PA22_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)

//! \name MXT143E Xplained top module
//@{
#define MXT143E_XPLAINED_TWI            TWI0
#define MXT143E_XPLAINED_SPI            SPI
#define MXT143E_XPLAINED_CS             (PIO_PA31_IDX)
#define MXT143E_XPLAINED_SCK            (PIO_PA14_IDX)
#define MXT143E_XPLAINED_MOSI           (PIO_PA13_IDX)
#define MXT143E_XPLAINED_MISO           (PIO_PA12_IDX)
#define MXT143E_XPLAINED_CHG            (PIO_PB2_IDX)
#define MXT143E_XPLAINED_DC             (PIO_PB3_IDX)
#define MXT143E_XPLAINED_BACKLIGHT      (PIO_PA17_IDX)
#define MXT143E_XPLAINED_LCD_RESET      (PIO_PC13_IDX)
#define MXT143E_XPLAINED_SDA            (PIO_PA3_IDX)
#define MXT143E_XPLAINED_SCL            (PIO_PA4_IDX)
//@}

/** SSC pin Transmitter Data (TD) */
#define PIN_SSC_TD        (PIO_PA17_IDX)
#define PIN_SSC_TD_FLAGS  (PIO_PERIPH_A | PIO_DEFAULT)
/** SSC pin Transmitter Clock (TK) */
#define PIN_SSC_TK        (PIO_PA16_IDX)
#define PIN_SSC_TK_FLAGS  (PIO_PERIPH_A | PIO_DEFAULT)
/** SSC pin Transmitter FrameSync (TF) */
#define PIN_SSC_TF        (PIO_PA15_IDX)
#define PIN_SSC_TF_FLAGS  (PIO_PERIPH_A | PIO_DEFAULT)

/** PCK0 */
#define PIN_PCK0        (PIO_PA6_IDX)
#define PIN_PCK0_MUX    (IOPORT_MODE_MUX_B)
#define PIN_PCK0_FLAGS  (PIO_PERIPH_B | PIO_DEFAULT)

#define PIN_PCK_0_MASK PIO_PA6
#define PIN_PCK_0_PIO  PIOA
#define PIN_PCK_0_ID   ID_PIOA
#define PIN_PCK_0_TYPE PIO_PERIPH_B
#define PIN_PCK_0_ATTR PIO_DEFAULT

#define PIN_PCK1        (PIO_PA17_IDX)
#define PIN_PCK1_FLAGS  (PIO_PERIPH_B | PIO_DEFAULT)

#define PIN_PCK_1_MASK PIO_PA17
#define PIN_PCK_1_PIO  PIOA
#define PIN_PCK_1_ID   ID_PIOA
#define PIN_PCK_1_TYPE PIO_PERIPH_B
#define PIN_PCK_1_ATTR PIO_DEFAULT

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

/** USART0 pin RX */
#define PIN_USART0_RXD {PIO_PA5A_RXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RXD_IDX   (PIO_PA5_IDX)
#define PIN_USART0_RXD_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin TX */
#define PIN_USART0_TXD {PIO_PA6A_TXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_TXD_IDX   (PIO_PA6_IDX)
#define PIN_USART0_TXD_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin CTS */
#define PIN_USART0_CTS {PIO_PA8A_CTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_CTS_IDX   (PIO_PA8_IDX)
#define PIN_USART0_CTS_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin RTS */
#define PIN_USART0_RTS {PIO_PA7A_RTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RTS_IDX   (PIO_PA7_IDX)
#define PIN_USART0_RTS_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin SCK */
#define PIN_USART0_SCK {PIO_PA2B_SCK0, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART0_SCK_IDX   (PIO_PA2_IDX)
#define PIN_USART0_SCK_FLAGS (PIO_PERIPH_B | PIO_DEFAULT)

/** USART1 pin RX */
#define PIN_USART1_RXD {PIO_PA21A_RXD1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_RXD_IDX   (PIO_PA21_IDX)
#define PIN_USART1_RXD_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)
/** USART1 pin TX */
#define PIN_USART1_TXD {PIO_PA22A_TXD1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_TXD_IDX   (PIO_PA22_IDX)
#define PIN_USART1_TXD_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)
/** USART1 pin CTS */
#define PIN_USART1_CTS {PIO_PA25A_CTS1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_CTS_IDX   (PIO_PA25_IDX)
#define PIN_USART1_CTS_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)
/** USART1 pin RTS */
#define PIN_USART1_RTS {PIO_PA24A_RTS1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_RTS_IDX   (PIO_PA24_IDX)
#define PIN_USART1_RTS_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)
/** USART1 pin ENABLE */
#define PIN_USART1_EN {PIO_PA23A_SCK1, PIOA, ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
#define PIN_USART1_EN_IDX   (PIO_PA23_IDX)
#define PIN_USART1_EN_FLAGS (PIO_OUTPUT_0 | PIO_DEFAULT)
/** USART1 pin SCK */
#define PIN_USART1_SCK {PIO_PA23A_SCK1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_SCK_IDX   (PIO_PA23_IDX)
#define PIN_USART1_SCK_FLAGS (PIO_PERIPH_A | PIO_DEFAULT)

/*----------------------------------------------------------------------------*/
#define CONSOLE_UART               UART0
#define CONSOLE_UART_ID            ID_UART0

/* RE pin. */
#define PIN_RE_IDX                 PIN_USART1_CTS_IDX
#define PIN_RE_FLAGS               (PIO_OUTPUT_0 | PIO_DEFAULT)

/* IRDA SD pin. */
#define PIN_IRDA_SD_IDX            PIN_USART1_CTS_IDX
#define PIN_IRDA_SD_FLAGS          (PIO_OUTPUT_1 | PIO_DEFAULT)

/* TXD pin configuration. */
#define PIN_USART_TXD_IDX          PIN_USART1_TXD_IDX
#define PIN_USART_TXD_FLAGS        (PIO_PERIPH_A | PIO_DEFAULT)
#define PIN_USART_TXD_IO_FLAGS     (PIO_OUTPUT_0 | PIO_DEFAULT)

/* SRAM base address */
#define SRAM_BASE_ADDRESS          EBI_CS0_ADDR

/* SRAM chip select */
#define SRAM_CHIP_SELECT           0

#endif  /* SAM4S_XPLAINED_H_INCLUDED */
