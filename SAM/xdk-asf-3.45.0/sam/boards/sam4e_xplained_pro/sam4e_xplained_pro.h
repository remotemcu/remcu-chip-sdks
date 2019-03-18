/**
 * \file
 *
 * \brief SAM4E-XPRO Board Definition.
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

#ifndef _SAM4E_XPRO_H_
#define _SAM4E_XPRO_H_

#include "compiler.h"
#include "system_sam4e.h"
#include "exceptions.h"

/*----------------------------------------------------------------------------*/
/**
 *  \page sam4e_xplained_pro_opfreq "SAM4E-XPRO - Operating frequencies"
 *  This page lists several definition related to the board operating frequency
 *
 *  \section Definitions
 *  - \ref BOARD_FREQ_*
 *  - \ref BOARD_MCK
 */

/** Board oscillator settings */
#define BOARD_FREQ_SLCK_XTAL            (32768U)
#define BOARD_FREQ_SLCK_BYPASS          (32768U)
#define BOARD_FREQ_MAINCK_XTAL          (12000000U)
#define BOARD_FREQ_MAINCK_BYPASS        (12000000U)

/** Master clock frequency */
#define BOARD_MCK                       CHIP_FREQ_CPU_MAX

/** board main clock xtal statup time */
#define BOARD_OSC_STARTUP_US            15625

/*----------------------------------------------------------------------------*/
/**
 * \page sam4e_xpro_board_info "SAM4E-XPRO - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "SAM4E-XPRO"
/** Board definition */
#define sam4expro
/** Family definition (already defined) */
#define sam4e
/** Core definition */
#define cortexm4

/*----------------------------------------------------------------------------*/

/** UART0 pins (UTXD0 and URXD0) definitions, PA10,9. */
#define PINS_UART0        (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0)
#define PINS_UART0_FLAGS  (IOPORT_MODE_MUX_A)

#define PINS_UART0_PORT   IOPORT_PIOA
#define PINS_UART0_MASK   (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0)
#define PINS_UART0_PIO    PIOA
#define PINS_UART0_ID     ID_PIOA
#define PINS_UART0_TYPE   PIO_PERIPH_A
#define PINS_UART0_ATTR   PIO_DEFAULT

//! \name LED0 definitions
//@{
#define LED0_GPIO            (PIO_PD22_IDX)
#define LED0_FLAGS           (0)
#define LED0_ACTIVE_LEVEL    (IOPORT_PIN_LEVEL_LOW)
#define LED0_INACTIVE_LEVEL  (IOPORT_PIN_LEVEL_HIGH)
#define	LED_COUNT			 (1)
//@}

//! \name SW0 definitions
//@{
#define SW0_PIN                   (PIO_PA2_IDX)
#define SW0_ACTIVE                (IOPORT_PIN_LEVEL_LOW)
#define SW0_INACTIVE              (!SW0_ACTIVE)
#define SW0_SUPC_INPUT            2

/**
 * Wrapper macros for SW0, to ensure common naming across all Xplained Pro
 * boards.
 */
#define PIN_SW0      {PIO_PA2, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
#define PIN_SW0_MASK PIO_PA2
#define PIN_SW0_PIO  PIOA
#define PIN_SW0_ID   ID_PIOA
#define PIN_SW0_TYPE PIO_INPUT
#define PIN_SW0_ATTR (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)
//@}

/** HSMCI pins definition. */
/*! Number of slot connected on HSMCI interface */
#define SD_MMC_HSMCI_MEM_CNT      1
#define SD_MMC_HSMCI_SLOT_0_SIZE  4
#define PINS_HSMCI   {0x3fUL << 26, PIOA, ID_PIOA, PIO_PERIPH_C, PIO_PULLUP}
/** HSMCI MCCDA pin definition. */
#define PIN_HSMCI_MCCDA_GPIO            (PIO_PA28_IDX)
#define PIN_HSMCI_MCCDA_FLAGS           (IOPORT_MODE_MUX_C)
/** HSMCI MCCK pin definition. */
#define PIN_HSMCI_MCCK_GPIO             (PIO_PA29_IDX)
#define PIN_HSMCI_MCCK_FLAGS            (IOPORT_MODE_MUX_C)
/** HSMCI MCDA0 pin definition. */
#define PIN_HSMCI_MCDA0_GPIO            (PIO_PA30_IDX)
#define PIN_HSMCI_MCDA0_FLAGS           (IOPORT_MODE_MUX_C)
/** HSMCI MCDA1 pin definition. */
#define PIN_HSMCI_MCDA1_GPIO            (PIO_PA31_IDX)
#define PIN_HSMCI_MCDA1_FLAGS           (IOPORT_MODE_MUX_C)
/** HSMCI MCDA2 pin definition. */
#define PIN_HSMCI_MCDA2_GPIO            (PIO_PA26_IDX)
#define PIN_HSMCI_MCDA2_FLAGS           (IOPORT_MODE_MUX_C)
/** HSMCI MCDA3 pin definition. */
#define PIN_HSMCI_MCDA3_GPIO            (PIO_PA27_IDX)
#define PIN_HSMCI_MCDA3_FLAGS           (IOPORT_MODE_MUX_C)

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

#define PIN_LED_0       {PIO_PD22, PIOD, ID_PIOD, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_LED_0_MASK  PIO_PD22
#define PIN_LED_0_PIO   PIOD
#define PIN_LED_0_ID    ID_PIOD
#define PIN_LED_0_TYPE  PIO_OUTPUT_1
#define PIN_LED_0_ATTR  PIO_DEFAULT
//@}

//! Number of on-board LEDs
#define BOARD_NUM_OF_LED 1

/**
 * Push button #0 definition. Attributes = pull-up + debounce + interrupt on
 * rising edge.
 */
#define BUTTON_0_NAME             "SW0"
#define BUTTON_0_PIN              SW0_PIN
#define BUTTON_0_ACTIVE           SW0_ACTIVE
#define BUTTON_0_INACTIVE         SW0_INACTIVE
#define BUTTON_0_SUPC_INPUT       SW0_SUPC_INPUT
#define GPIO_PUSH_BUTTON_0        BUTTON_0_PIN

#define PUSHBUTTON_1_NAME        "SW0"
#define PUSHBUTTON_1_WKUP_LINE   (2)
#define PUSHBUTTON_1_WKUP_FSTT   (PMC_FSMR_FSTT2)
#define GPIO_PUSH_BUTTON_1       (PIO_PA2_IDX)
#define GPIO_PUSH_BUTTON_1_FLAGS (IOPORT_MODE_PULLUP | IOPORT_MODE_DEBOUNCE)
#define GPIO_PUSH_BUTTON_1_SENSE (IOPORT_SENSE_RISING)

#define PIN_PUSHBUTTON_1       {PIO_PA2, PIOA, ID_PIOA, PIO_INPUT, \
		PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
#define PIN_PUSHBUTTON_1_MASK  PIO_PA2
#define PIN_PUSHBUTTON_1_PIO   PIOA
#define PIN_PUSHBUTTON_1_ID    ID_PIOA
#define PIN_PUSHBUTTON_1_TYPE  PIO_INPUT
#define PIN_PUSHBUTTON_1_ATTR  (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)
#define PIN_PUSHBUTTON_1_IRQn  PIOA_IRQn

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS    {PIN_PUSHBUTTON_1}

#define PIN_TC0_TIOA0        (PIO_PA0_IDX)
#define PIN_TC0_TIOA0_MUX    (IOPORT_MODE_MUX_B)
#define PIN_TC0_TIOA0_FLAGS  (IOPORT_MODE_MUX_B)

#define PIN_TC0_TIOA1        (PIO_PA15_IDX)
#define PIN_TC0_TIOA1_MUX    (IOPORT_MODE_MUX_B)
#define PIN_TC0_TIOA1_FLAGS  (IOPORT_MODE_MUX_B)

#define PIN_TC0_TIOA1_PIO    PIOA
#define PIN_TC0_TIOA1_MASK   PIO_PA15
#define PIN_TC0_TIOA1_ID     ID_PIOA
#define PIN_TC0_TIOA1_TYPE   PIO_PERIPH_B
#define PIN_TC0_TIOA1_ATTR   PIO_DEFAULT

#define PIN_TC0_TIOA2        (PIO_PA26_IDX)
#define PIN_TC0_TIOA2_MUX    (IOPORT_MODE_MUX_B)
#define PIN_TC0_TIOA2_FLAGS  (IOPORT_MODE_MUX_B)

#define PIN_TC0_TIOA2_PIO    PIOA
#define PIN_TC0_TIOA2_MASK   PIO_PA26
#define PIN_TC0_TIOA2_ID     ID_PIOA
#define PIN_TC0_TIOA2_TYPE   PIO_PERIPH_B
#define PIN_TC0_TIOA2_ATTR   PIO_DEFAULT

/** PWM LED0 pin definitions. */
#define PIN_PWM_LED0_GPIO     PIO_PD22_IDX
#define PIN_PWM_LED0_FLAGS    (IOPORT_MODE_MUX_A)
#define PIN_PWM_LED0_CHANNEL  PWM_CHANNEL_2

/** SPI MISO pin definition. */
#define SPI_MISO_GPIO         (PIO_PA12_IDX)
#define SPI_MISO_FLAGS        (IOPORT_MODE_MUX_A)
/** SPI MOSI pin definition. */
#define SPI_MOSI_GPIO         (PIO_PA13_IDX)
#define SPI_MOSI_FLAGS        (IOPORT_MODE_MUX_A)
/** SPI SPCK pin definition. */
#define SPI_SPCK_GPIO         (PIO_PA14_IDX)
#define SPI_SPCK_FLAGS        (IOPORT_MODE_MUX_A)

/** SPI chip select 0 pin definition. (Only one configuration is possible) */
#define SPI_NPCS0_GPIO        (PIO_PA11_IDX)
#define SPI_NPCS0_FLAGS       (IOPORT_MODE_MUX_A)
/** SPI chip select 1 pin definition. (multiple configurations are possible) */
#define SPI_NPCS1_PA9_GPIO    (PIO_PA9_IDX)
#define SPI_NPCS1_PA9_FLAGS   (IOPORT_MODE_MUX_B)
#define SPI_NPCS1_PA31_GPIO   (PIO_PA31_IDX)
#define SPI_NPCS1_PA31_FLAGS  (IOPORT_MODE_MUX_A)
#define SPI_NPCS1_PB14_GPIO   (PIO_PB14_IDX)
#define SPI_NPCS1_PB14_FLAGS  (IOPORT_MODE_MUX_A)
#define SPI_NPCS1_PC4_GPIO    (PIO_PC4_IDX)
#define SPI_NPCS1_PC4_FLAGS   (IOPORT_MODE_MUX_B)
/** SPI chip select 2 pin definition. (multiple configurations are possible) */
#define SPI_NPCS2_PA10_GPIO   (PIO_PA10_IDX)
#define SPI_NPCS2_PA10_FLAGS  (IOPORT_MODE_MUX_B)
#define SPI_NPCS2_PA30_GPIO   (PIO_PA30_IDX)
#define SPI_NPCS2_PA30_FLAGS  (IOPORT_MODE_MUX_B)
#define SPI_NPCS2_PB2_GPIO    (PIO_PB2_IDX)
#define SPI_NPCS2_PB2_FLAGS   (IOPORT_MODE_MUX_B)
/** SPI chip select 3 pin definition. (multiple configurations are possible) */
#define SPI_NPCS3_PA3_GPIO    (PIO_PA3_IDX)
#define SPI_NPCS3_PA3_FLAGS   (IOPORT_MODE_MUX_B)
#define SPI_NPCS3_PA5_GPIO    (PIO_PA5_IDX)
#define SPI_NPCS3_PA5_FLAGS   (IOPORT_MODE_MUX_B)
#define SPI_NPCS3_PA22_GPIO   (PIO_PA22_IDX)
#define SPI_NPCS3_PA22_FLAGS  (IOPORT_MODE_MUX_B)

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

/** TWI0 pins definition */
#define TWI0_DATA_GPIO   PIO_PA3_IDX
#define TWI0_DATA_FLAGS  (IOPORT_MODE_MUX_A)
#define TWI0_CLK_GPIO    PIO_PA4_IDX
#define TWI0_CLK_FLAGS   (IOPORT_MODE_MUX_A)

/** USART0 pin RX */
#define PIN_USART0_RXD        {PIO_PB0C_RXD0, PIOB, ID_PIOB, PIO_PERIPH_C, \
		PIO_DEFAULT}
#define PIN_USART0_RXD_IDX    (PIO_PB0_IDX)
#define PIN_USART0_RXD_FLAGS  (IOPORT_MODE_MUX_C)
/** USART0 pin TX */
#define PIN_USART0_TXD        {PIO_PB1C_TXD0, PIOB, ID_PIOB, PIO_PERIPH_C, \
		PIO_DEFAULT}
#define PIN_USART0_TXD_IDX    (PIO_PB1_IDX)
#define PIN_USART0_TXD_FLAGS  (IOPORT_MODE_MUX_C)
/** USART0 pin CTS */
#define PIN_USART0_CTS        {PIO_PB2C_CTS0, PIOB, ID_PIOB, PIO_PERIPH_C, \
		PIO_DEFAULT}
#define PIN_USART0_CTS_IDX    (PIO_PB2_IDX)
#define PIN_USART0_CTS_FLAGS  (IOPORT_MODE_MUX_C)
/** USART0 pin RTS */
#define PIN_USART0_RTS        {PIO_PB3C_RTS0, PIOB, ID_PIOB, PIO_PERIPH_C, \
		PIO_DEFAULT}
#define PIN_USART0_RTS_IDX    (PIO_PB3_IDX)
#define PIN_USART0_RTS_FLAGS  (IOPORT_MODE_MUX_C)
/** USART0 pin SCK */
#define PIN_USART0_SCK        {PIO_PB13C_SCK0, PIOB, ID_PIOB, PIO_PERIPH_C, \
		PIO_DEFAULT}
#define PIN_USART0_SCK_IDX    (PIO_PB13_IDX)
#define PIN_USART0_SCK_FLAGS  (IOPORT_MODE_MUX_C)

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
/** USART1 pin ENABLE */
#define PIN_USART1_EN         {PIO_PA23, PIOA, ID_PIOA, PIO_OUTPUT_0, \
		PIO_DEFAULT}
#define PIN_USART1_EN_IDX     (PIO_PA23_IDX)
#define PIN_USART1_EN_FLAGS   (0)
#define PIN_USART1_EN_ACTIVE_LEVEL   IOPORT_PIN_LEVEL_LOW
#define PIN_USART1_EN_INACTIVE_LEVEL IOPORT_PIN_LEVEL_HIGH

/** USB VBus monitoring pin definition. */
#define PIN_USB_VBUS    {PIO_PE2, PIOE, ID_PIOE, PIO_INPUT, PIO_PULLUP}
#define USB_VBUS_FLAGS    (PIO_INPUT | PIO_DEBOUNCE | PIO_IT_EDGE)
#define USB_VBUS_PIN_IRQn (PIOE_IRQn)
#define USB_VBUS_PIN      (PIO_PE2_IDX)
#define USB_VBUS_PIO_ID   (ID_PIOE)
#define USB_VBUS_PIO_MASK (PIO_PE2)
/* This pin can not be used as fast wakeup source such as
 * USB_VBUS_WKUP PMC_FSMR_FSTT7 */

/** USB D- pin (System function) */
#define PIN_USB_DM      {PIO_PB10}
/** USB D+ pin (System function) */
#define PIN_USB_DP      {PIO_PB11}

/** EBI Bus pins */
#define PIN_EBI_DATA_BUS_D0        PIO_PC0_IDX
#define PIN_EBI_DATA_BUS_D1        PIO_PC1_IDX
#define PIN_EBI_DATA_BUS_D2        PIO_PC2_IDX
#define PIN_EBI_DATA_BUS_D3        PIO_PC3_IDX
#define PIN_EBI_DATA_BUS_D4        PIO_PC4_IDX
#define PIN_EBI_DATA_BUS_D5        PIO_PC5_IDX
#define PIN_EBI_DATA_BUS_D6        PIO_PC6_IDX
#define PIN_EBI_DATA_BUS_D7        PIO_PC7_IDX
#define PIN_EBI_DATA_BUS_FLAGS     IOPORT_MODE_MUX_A

#define PIN_EBI_ADDR_BUS_A0        PIO_PC18_IDX
#define PIN_EBI_ADDR_BUS_A1        PIO_PC19_IDX
#define PIN_EBI_ADDR_BUS_A2        PIO_PC20_IDX
#define PIN_EBI_ADDR_BUS_A3        PIO_PC21_IDX
#define PIN_EBI_ADDR_BUS_A4        PIO_PC22_IDX
#define PIN_EBI_ADDR_BUS_A5        PIO_PC23_IDX
#define PIN_EBI_ADDR_BUS_A6        PIO_PC24_IDX
#define PIN_EBI_ADDR_BUS_A7        PIO_PC25_IDX
#define PIN_EBI_ADDR_BUS_A8        PIO_PC26_IDX
#define PIN_EBI_ADDR_BUS_A9        PIO_PC27_IDX
#define PIN_EBI_ADDR_BUS_A10       PIO_PC28_IDX
#define PIN_EBI_ADDR_BUS_A11       PIO_PC29_IDX
#define PIN_EBI_ADDR_BUS_A12       PIO_PC30_IDX
#define PIN_EBI_ADDR_BUS_A13       PIO_PC31_IDX
#define PIN_EBI_ADDR_BUS_FLAG1     IOPORT_MODE_MUX_A
#define PIN_EBI_ADDR_BUS_A14       PIO_PA18_IDX
#define PIN_EBI_ADDR_BUS_A15       PIO_PA19_IDX
#define PIN_EBI_ADDR_BUS_A16       PIO_PA20_IDX
#define PIN_EBI_ADDR_BUS_A17       PIO_PA0_IDX
#define PIN_EBI_ADDR_BUS_A18       PIO_PA1_IDX
#define PIN_EBI_ADDR_BUS_FLAG2     IOPORT_MODE_MUX_C

#define PIN_EBI_NRD                PIO_PC11_IDX
#define PIN_EBI_NRD_FLAGS          IOPORT_MODE_MUX_A
#define PIN_EBI_NWE                PIO_PC8_IDX
#define PIN_EBI_NWE_FLAGS          IOPORT_MODE_MUX_A
#define PIN_EBI_NCS1               PIO_PD18_IDX
#define PIN_EBI_NCS1_FLAGS         IOPORT_MODE_MUX_A
#define PIN_EBI_NCS3               PIO_PD19_IDX
#define PIN_EBI_NCS3_FLAGS         IOPORT_MODE_MUX_A

/* SRAM base address */
#define SRAM_BASE_ADDRESS          EBI_CS1_ADDR
#define SRAM_BASE_ADDRESS_2ND      EBI_CS3_ADDR

/* SRAM chip select */
#define SRAM_CHIP_SELECT           1
#define SRAM_CHIP_SELECT_2ND       3

/* KSZ8051MNL relate PIN definition */
#define PIN_KSZ8051MNL_RXC_IDX                 PIO_PD14_IDX
#define PIN_KSZ8051MNL_RXC_FLAGS             (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_TXC_IDX                 PIO_PD0_IDX
#define PIN_KSZ8051MNL_TXC_FLAGS             (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_TXEN_IDX                PIO_PD1_IDX
#define PIN_KSZ8051MNL_TXEN_FLAGS            (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_TXD3_IDX                PIO_PD16_IDX
#define PIN_KSZ8051MNL_TXD3_FLAGS            (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_TXD2_IDX                PIO_PD15_IDX
#define PIN_KSZ8051MNL_TXD2_FLAGS            (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_TXD1_IDX                PIO_PD3_IDX
#define PIN_KSZ8051MNL_TXD1_FLAGS            (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_TXD0_IDX                PIO_PD2_IDX
#define PIN_KSZ8051MNL_TXD0_FLAGS            (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_RXD3_IDX                PIO_PD12_IDX
#define PIN_KSZ8051MNL_RXD3_FLAGS            (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_RXD2_IDX                PIO_PD11_IDX
#define PIN_KSZ8051MNL_RXD2_FLAGS            (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_RXD1_IDX                PIO_PD6_IDX
#define PIN_KSZ8051MNL_RXD1_FLAGS            (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_RXD0_IDX                PIO_PD5_IDX
#define PIN_KSZ8051MNL_RXD0_FLAGS            (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_RXER_IDX                PIO_PD7_IDX
#define PIN_KSZ8051MNL_RXER_FLAGS            (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_RXDV_IDX                PIO_PD4_IDX
#define PIN_KSZ8051MNL_RXDV_FLAGS            (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_CRS_IDX                 PIO_PD10_IDX
#define PIN_KSZ8051MNL_CRS_FLAGS             (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_COL_IDX                 PIO_PD13_IDX
#define PIN_KSZ8051MNL_COL_FLAGS             (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_MDC_IDX                 PIO_PD8_IDX
#define PIN_KSZ8051MNL_MDC_FLAGS             (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_MDIO_IDX                PIO_PD9_IDX
#define PIN_KSZ8051MNL_MDIO_FLAGS            (IOPORT_MODE_MUX_A)
#define PIN_KSZ8051MNL_INTRP_IDX               PIO_PD28_IDX

/** NandFlash pins definition: OE. */
#define PIN_EBI_NANDOE    (PIO_PC9_IDX)
#define PIN_EBI_NANDOE_FLAGS    (IOPORT_MODE_MUX_A)

/** NandFlash pins definition: WE. */
#define PIN_EBI_NANDWE    (PIO_PC10_IDX)
#define PIN_EBI_NANDWE_FLAGS    (IOPORT_MODE_MUX_A)

/** NandFlash pins definition: CLE. */
#define PIN_EBI_NANDCLE    (PIO_PC17_IDX)
#define PIN_EBI_NANDCLE_FLAGS    (IOPORT_MODE_MUX_A)

/** NandFlash pins definition: ALE. */
#define PIN_EBI_NANDALE    (PIO_PC16_IDX)
#define PIN_EBI_NANDALE_FLAGS    (IOPORT_MODE_MUX_A)

/** NandFlash pins definition: DATA. */
#define PIN_EBI_NANDIO_0    (PIO_PC0_IDX)
#define PIN_EBI_NANDIO_0_FLAGS    (IOPORT_MODE_MUX_A)

#define PIN_EBI_NANDIO_1    (PIO_PC1_IDX)
#define PIN_EBI_NANDIO_1_FLAGS    (IOPORT_MODE_MUX_A)

#define PIN_EBI_NANDIO_2    (PIO_PC2_IDX)
#define PIN_EBI_NANDIO_2_FLAGS    (IOPORT_MODE_MUX_A)

#define PIN_EBI_NANDIO_3    (PIO_PC3_IDX)
#define PIN_EBI_NANDIO_3_FLAGS    (IOPORT_MODE_MUX_A)

#define PIN_EBI_NANDIO_4    (PIO_PC4_IDX)
#define PIN_EBI_NANDIO_4_FLAGS    (IOPORT_MODE_MUX_A)

#define PIN_EBI_NANDIO_5    (PIO_PC5_IDX)
#define PIN_EBI_NANDIO_5_FLAGS    (IOPORT_MODE_MUX_A)

#define PIN_EBI_NANDIO_6    (PIO_PC6_IDX)
#define PIN_EBI_NANDIO_6_FLAGS    (IOPORT_MODE_MUX_A)

#define PIN_EBI_NANDIO_7    (PIO_PC7_IDX)
#define PIN_EBI_NANDIO_7_FLAGS    (IOPORT_MODE_MUX_A)

/** Nandflash chip enable pin definition. */
#define PIN_NF_CE_IDX    (PIO_PC14_IDX)

/** Nandflash ready/busy pin definition. */
/* The new board use this definition */
#define PIN_NF_RB_IDX    (PIO_PB12_IDX)
/* The old board use this definition */
//#define PIN_NF_RB_IDX    (PIO_PD10_IDX)

/* Chip select number for nand */
#define BOARD_NAND_CS    0

/*----------------------------------------------------------------------------*/
/**
 * \page sam4e_xpro_usb "SAM4E-XPRO - USB device"
 *
 * \section Definitions
 * - \ref BOARD_USB_BMATTRIBUTES
 * - \ref CHIP_USB_UDP
 * - \ref CHIP_USB_PULLUP_INTERNAL
 * - \ref CHIP_USB_NUMENDPOINTS
 * - \ref CHIP_USB_ENDPOINTS_MAXPACKETSIZE
 * - \ref CHIP_USB_ENDPOINTS_BANKS
 */

/**
 * USB attributes configuration descriptor (bus or self powered,
 * remote wakeup)
 */
#define BOARD_USB_BMATTRIBUTES  USBConfigurationDescriptor_SELFPOWERED_RWAKEUP

/** Indicates chip has an UDP Full Speed. */
#define CHIP_USB_UDP

/** Indicates chip has an internal pull-up. */
#define CHIP_USB_PULLUP_INTERNAL

/** Number of USB endpoints */
#define CHIP_USB_NUMENDPOINTS 8

/** Endpoints max packet size */
#define CHIP_USB_ENDPOINTS_MAXPACKETSIZE(i) \
   ((i == 0) ? 64 : \
   ((i == 1) ? 64 : \
   ((i == 2) ? 64 : \
   ((i == 3) ? 64 : \
   ((i == 4) ? 512 : \
   ((i == 5) ? 512 : \
   ((i == 6) ? 64 : \
   ((i == 7) ? 64 : 0 ))))))))

/** Endpoints Number of Bank */
#define CHIP_USB_ENDPOINTS_BANKS(i) \
   ((i == 0) ? 1 : \
   ((i == 1) ? 2 : \
   ((i == 2) ? 2 : \
   ((i == 3) ? 1 : \
   ((i == 4) ? 2 : \
   ((i == 5) ? 2 : \
   ((i == 6) ? 2 : \
   ((i == 7) ? 2 : 0 ))))))))

/*----------------------------------------------------------------------------*/
/**
 * \page sam4e_xpro_extcomp "SAM4E-XPRO - External components"
 * This page lists the definitions related to external on-board components
 * located in the board.h file for the SAM4E-XPRO.
 *
 * SD Card
 * - \ref BOARD_SD_PINS
 * - \ref BOARD_SD_PIN_CD
 *
 * QTouch component (QT2160)
 * - \ref BOARD_QT_TWI_INSTANCE
 * - \ref BOARD_QT_DEVICE_ADDRESS
 * - \ref BOARD_QT_CHANGE_PIN_IDX
 * - \ref BOARD_QT_CHANGE_PIN_FLAGS
 * - \ref BOARD_QT_CHANGE_PIN_SENSE
 */

/** HSMCI pins that shall be configured to access the SD card. */
#define BOARD_SD_PINS               PINS_HSMCI

/*----------------------------------------------------------------------------*/
/**
 * \page sam4e_xpro_mem "SAM4E-XPRO - Memories"
 * This page lists definitions related to internal & external on-board memories.
 *
 * \section NandFlash
 * - \ref BOARD_NF_COMMAND_ADDR
 * - \ref BOARD_NF_ADDRESS_ADDR
 * - \ref BOARD_NF_DATA_ADDR
 *
 * \section NorFlash
 * - \ref BOARD_NORFLASH_ADDR
 * - \ref BOARD_NORFLASH_DFT_BUS_SIZE
 */

/** Address for transferring command bytes to the nandflash. */
#define BOARD_NF_COMMAND_ADDR   0x60400000
/** Address for transferring address bytes to the nandflash. */
#define BOARD_NF_ADDRESS_ADDR   0x60200000
/** Address for transferring data bytes to the nandflash. */
#define BOARD_NF_DATA_ADDR      0x60000000
/* Bus width for NAND */
#define CONF_NF_BUSWIDTH    8
/* Access timing for NAND */
#define CONF_NF_SETUP_TIMING (SMC_SETUP_NWE_SETUP(0) \
		| SMC_SETUP_NCS_WR_SETUP(1) \
		| SMC_SETUP_NRD_SETUP(0) \
		| SMC_SETUP_NCS_RD_SETUP(1))
#define CONF_NF_PULSE_TIMING (SMC_PULSE_NWE_PULSE(2) \
		| SMC_PULSE_NCS_WR_PULSE(3) \
		| SMC_PULSE_NRD_PULSE(4) \
		| SMC_PULSE_NCS_RD_PULSE(4))
#define CONF_NF_CYCLE_TIMING (SMC_CYCLE_NWE_CYCLE(4) \
		| SMC_CYCLE_NRD_CYCLE(7))

/** Address for transferring command bytes to the norflash. */
#define BOARD_NORFLASH_ADDR     0x63000000
/** Default NOR bus size after power up reset */
#define BOARD_NORFLASH_DFT_BUS_SIZE 8

/*----------------------------------------------------------------------------*/

#define CONSOLE_UART               UART0
#define CONSOLE_UART_ID            ID_UART0

/*----------------------------------------------------------------------------*/
/* GMAC HW configurations */
#define BOARD_GMAC_PHY_ADDR 0

/*----------------------------------------------------------------------------*/
/**
 * \page sam4e_xpro_CAN "SAM4E-XPRO - CAN"
 * This page lists definitions related to CAN0 and CAN1.
 *
 * CAN
 * - \ref PIN_CAN0_TRANSCEIVER_RXEN
 * - \ref PIN_CAN0_TRANSCEIVER_RS
 * - \ref PIN_CAN0_TXD
 * - \ref PIN_CAN0_RXD
 * - \ref PINS_CAN0
 *
 * - \ref PIN_CAN1_TRANSCEIVER_RXEN
 * - \ref PIN_CAN1_TRANSCEIVER_RS
 * - \ref PIN_CAN1_TXD
 * - \ref PIN_CAN1_RXD
 * - \ref PINS_CAN1
 */
/** CAN0 transceiver PIN RS. */
#define PIN_CAN0_TR_RS_IDX        PIO_PE0_IDX
#define PIN_CAN0_TR_RS_FLAGS      IOPORT_DIR_OUTPUT

/** CAN0 transceiver PIN EN. */
#define PIN_CAN0_TR_EN_IDX        PIO_PE1_IDX
#define PIN_CAN0_TR_EN_FLAGS      IOPORT_DIR_OUTPUT

/** CAN0 PIN RX. */
#define PIN_CAN0_RX_IDX           PIO_PB3_IDX
#define PIN_CAN0_RX_FLAGS         IOPORT_MODE_MUX_A

/** CAN0 PIN TX. */
#define PIN_CAN0_TX_IDX           PIO_PB2_IDX
#define PIN_CAN0_TX_FLAGS         IOPORT_MODE_MUX_A

/** CAN1 transceiver PIN RS. */
#define PIN_CAN1_TR_RS_IDX        PIO_PE2_IDX
#define PIN_CAN1_TR_RS_FLAGS      IOPORT_DIR_OUTPUT

/** CAN1 transceiver PIN EN. */
#define PIN_CAN1_TR_EN_IDX        PIO_PE3_IDX
#define PIN_CAN1_TR_EN_FLAGS      IOPORT_DIR_OUTPUT

/** CAN1 PIN RX. */
#define PIN_CAN1_RX_IDX           PIO_PC12_IDX
#define PIN_CAN1_RX_FLAGS         IOPORT_MODE_MUX_C

/** CAN1 PIN TX. */
#define PIN_CAN1_TX_IDX           PIO_PC15_IDX
#define PIN_CAN1_TX_FLAGS         IOPORT_MODE_MUX_C


/*! \name Connections of the AT86RFX transceiver
 */
//! @{



#define AT86RFX_SPI                  SPI
#define AT86RFX_RST_PIN              IOPORT_CREATE_PIN(PIOA, 15)
#define AT86RFX_IRQ_PIN              IOPORT_CREATE_PIN(PIOA, 11)
#define AT86RFX_SLP_PIN              IOPORT_CREATE_PIN(PIOD, 25)
#define AT86RFX_SPI_CS               1
#define AT86RFX_SPI_CS_PIN           SPI_NPCS1_PB14_GPIO
#define AT86RFX_SPI_CS_FLAGS         SPI_NPCS1_PB14_FLAGS
#define AT86RFX_SPI_MOSI             IOPORT_CREATE_PIN(PIOA, 13)
#define AT86RFX_SPI_MISO             IOPORT_CREATE_PIN(PIOA, 12)
#define AT86RFX_SPI_SCK              IOPORT_CREATE_PIN(PIOA, 14)

void at86rfx_isr(uint32_t, uint32_t);

#define AT86RFX_INTC_INIT()         ioport_set_pin_dir(AT86RFX_IRQ_PIN, IOPORT_DIR_INPUT);\
                                    ioport_set_pin_sense_mode(AT86RFX_IRQ_PIN, IOPORT_SENSE_RISING);\
                                    pmc_enable_periph_clk(ID_PIOA);\
                                    pio_set_debounce_filter(PIOA, PIO_PA11, 10);\
                                    pio_handler_set(PIOA, ID_PIOA, PIO_PA11, PIO_IT_HIGH_LEVEL, at86rfx_isr);\
                                    NVIC_EnableIRQ((IRQn_Type) ID_PIOA);\
                                    pio_enable_interrupt(PIOA, PIO_PA11);

#define AT86RFX_ISR()               void at86rfx_isr(uint32_t arg1, uint32_t arg2)

/** Enables the transceiver main interrupt. */
#define ENABLE_TRX_IRQ()            pio_enable_pin_interrupt(AT86RFX_IRQ_PIN)

/** Disables the transceiver main interrupt. */
#define DISABLE_TRX_IRQ()           pio_disable_pin_interrupt(AT86RFX_IRQ_PIN)

/** Clears the transceiver main interrupt. */
#define CLEAR_TRX_IRQ()             NVIC_ClearPendingIRQ(PIOA_IRQn);
/*
 * This macro saves the trx interrupt status and disables the trx interrupt.
 */
#define ENTER_TRX_REGION()          pio_disable_pin_interrupt(AT86RFX_IRQ_PIN);
/*
 *  This macro restores the transceiver interrupt status
 */
#define LEAVE_TRX_REGION()         pio_enable_pin_interrupt(AT86RFX_IRQ_PIN)

//@}

/** EDBG related define */
#define EDBG_I2C_MODULE  TWI0
#define EDBG_I2C_MODULE_ID  ID_TWI0

/*----------------------------------------------------------------------------*/
#endif  /* _SAM4E_XPRO_H_ */
