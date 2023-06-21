/**
 * \file
 *
 * \brief SAM4S-EK2 Board Definition.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _SAM4S_EK2_H_
#define _SAM4S_EK2_H_

#include "compiler.h"
#include "system_sam4s.h"

/*
#define BOARD_REV_A
*/
#define BOARD_REV_B

/*----------------------------------------------------------------------------*/
/**
 *  \page sam4s_ek_opfreq "SAM4S-EK - Operating frequencies"
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

/*-----------------------------------------------------------------------*/
/**
 * \page sam4s_ek_board_info "SAM4S-EK - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "SAM4S-EK2"
/** Board definition */
#define sam4sek2
/** Family definition (already defined) */
#define sam4s
/** Core definition */
#define cortexm4

/*----------------------------------------------------------------------------*/
/** Pins ADC */
#define PINS_ADC_TRIG  PIO_PA8_IDX
#define PINS_ADC_TRIG_FLAG  (PIO_PERIPH_B | PIO_DEFAULT)

/** UART0 pins (UTXD0 and URXD0) definitions, PA9,10. */
#define PINS_UART0              (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0)
#define PINS_UART0_FLAGS        (PIO_PERIPH_A | PIO_DEFAULT)

#define PINS_UART0_MASK PIO_PA9A_URXD0|PIO_PA10A_UTXD0
#define PINS_UART0_PIO PIOA
#define PINS_UART0_ID ID_PIOA
#define PINS_UART0_TYPE PIO_PERIPH_A
#define PINS_UART0_ATTR PIO_DEFAULT

/** UART1 pins (UTXD1 and URXD1) definitions, PB2,PB3. */
#define PINS_UART1        (PIO_PB2A_URXD1 | PIO_PB3A_UTXD1)
#define PINS_UART1_FLAGS    (PIO_PERIPH_A | PIO_DEFAULT)

#define PINS_UART1_MASK PIO_PB2A_URXD1 | PIO_PB3A_UTXD1
#define PINS_UART1_PIO PIOB
#define PINS_UART1_ID ID_PIOB
#define PINS_UART1_TYPE PIO_PERIPH_A
#define PINS_UART1_ATTR PIO_DEFAULT

/** EBI Data Bus pins */
#define PIN_EBI_DATA_BUS_D0        PIO_PC0_IDX
#define PIN_EBI_DATA_BUS_D1        PIO_PC1_IDX
#define PIN_EBI_DATA_BUS_D2        PIO_PC2_IDX
#define PIN_EBI_DATA_BUS_D3        PIO_PC3_IDX
#define PIN_EBI_DATA_BUS_D4        PIO_PC4_IDX
#define PIN_EBI_DATA_BUS_D5        PIO_PC5_IDX
#define PIN_EBI_DATA_BUS_D6        PIO_PC6_IDX
#define PIN_EBI_DATA_BUS_D7        PIO_PC7_IDX
#define PIN_EBI_DATA_BUS_FLAGS           PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_DATA_BUS_MASK  0xFF
#define PIN_EBI_DATA_BUS_PIO  PIOC
#define PIN_EBI_DATA_BUS_ID  ID_PIOC
#define PIN_EBI_DATA_BUS_TYPE PIO_PERIPH_A
#define PIN_EBI_DATA_BUS_ATTR PIO_PULLUP
/** EBI NRD pin */
#define PIN_EBI_NRD                 PIO_PC11_IDX
#define PIN_EBI_NRD_FLAGS       PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_NRD_MASK  1 << 11
#define PIN_EBI_NRD_PIO  PIOC
#define PIN_EBI_NRD_ID  ID_PIOC
#define PIN_EBI_NRD_TYPE PIO_PERIPH_A
#define PIN_EBI_NRD_ATTR PIO_PULLUP
/** EBI NWE pin */
#define PIN_EBI_NWE                  PIO_PC8_IDX
#define PIN_EBI_NWE_FLAGS       PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_NWE_MASK  1 << 8
#define PIN_EBI_NWE_PIO  PIOC
#define PIN_EBI_NWE_ID  ID_PIOC
#define PIN_EBI_NWE_TYPE PIO_PERIPH_A
#define PIN_EBI_NWE_ATTR PIO_PULLUP
/** EBI NCS0 pin */
#define PIN_EBI_NCS0                PIO_PC14_IDX
#define PIN_EBI_NCS0_FLAGS     PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_NCS0_MASK  1 << 14
#define PIN_EBI_NCS0_PIO  PIOC
#define PIN_EBI_NCS0_ID  ID_PIOC
#define PIN_EBI_NCS0_TYPE PIO_PERIPH_A
#define PIN_EBI_NCS0_ATTR PIO_PULLUP
/** EBI address bus pins  */
#define PIN_EBI_ADDR_BUS_A0     PIO_PC18_IDX
#define PIN_EBI_ADDR_BUS_A1     PIO_PC19_IDX
#define PIN_EBI_ADDR_BUS_A2     PIO_PC20_IDX
#define PIN_EBI_ADDR_BUS_A3     PIO_PC21_IDX
#define PIN_EBI_ADDR_BUS_A4     PIO_PC22_IDX
#define PIN_EBI_ADDR_BUS_A5     PIO_PC23_IDX
#define PIN_EBI_ADDR_BUS_A6     PIO_PC24_IDX
#define PIN_EBI_ADDR_BUS_A7     PIO_PC25_IDX
#define PIN_EBI_ADDR_BUS_A8     PIO_PC26_IDX
#define PIN_EBI_ADDR_BUS_A9     PIO_PC27_IDX
#define PIN_EBI_ADDR_BUS_A10   PIO_PC28_IDX
#define PIN_EBI_ADDR_BUS_A11   PIO_PC29_IDX
#define PIN_EBI_ADDR_BUS_A12   PIO_PC30_IDX
#define PIN_EBI_ADDR_BUS_A13   PIO_PC31_IDX
#define PIN_EBI_ADDR_BUS_FLAG1  PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_ADDR_BUS_A14   PIO_PA18_IDX
#define PIN_EBI_ADDR_BUS_A15   PIO_PA19_IDX
#define PIN_EBI_ADDR_BUS_A16   PIO_PA20_IDX
#define PIN_EBI_ADDR_BUS_A17   PIO_PA0_IDX
#define PIN_EBI_ADDR_BUS_A18   PIO_PA1_IDX
#define PIN_EBI_ADDR_BUS_A19   PIO_PA23_IDX
#define PIN_EBI_ADDR_BUS_A20   PIO_PA24_IDX
#define PIN_EBI_ADDR_BUS_FLAG2  PIO_PERIPH_C | PIO_PULLUP
/** EBI pin for LCD CS */
#define PIN_EBI_NCS1                 PIO_PC15_IDX
#define PIN_EBI_NCS1_FLAGS      PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_NCS1_MASK  1 << 15
#define PIN_EBI_NCS1_PIO  PIOC
#define PIN_EBI_NCS1_ID  ID_PIOC
#define PIN_EBI_NCS1_TYPE PIO_PERIPH_A
#define PIN_EBI_NCS1_ATTR PIO_PULLUP
/** EBI pin for LCD RS */
#define PIN_EBI_LCD_RS                PIO_PC19_IDX
#define PIN_EBI_LCD_RS_FLAGS     PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_LCD_RS_MASK  1 << 19
#define PIN_EBI_LCD_RS_PIO  PIOC
#define PIN_EBI_LCD_RS_ID  ID_PIOC
#define PIN_EBI_LCD_RS_TYPE PIO_PERIPH_A
#define PIN_EBI_LCD_RS_ATTR PIO_PULLUP

/** LED #0 pin definition (BLUE). */
#define LED_0_NAME  "blue LED D2"
#define PIN_LED_0   {PIO_PA19, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_LED_0_MASK PIO_PA19
#define PIN_LED_0_PIO PIOA
#define PIN_LED_0_ID ID_PIOA
#define PIN_LED_0_TYPE PIO_OUTPUT_1
#define PIN_LED_0_ATTR PIO_DEFAULT

#define LED0_GPIO     (PIO_PA19_IDX)
#define LED0_FLAGS    (PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED0_ACTIVE_LEVEL 0

/** LED #1 pin definition (GREEN). */
#define LED_1_NAME  "green LED D3"
#define PIN_LED_1   {PIO_PA20, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_LED_1_MASK PIO_PA20
#define PIN_LED_1_PIO PIOA
#define PIN_LED_1_ID ID_PIOA
#define PIN_LED_1_TYPE PIO_OUTPUT_1
#define PIN_LED_1_ATTR PIO_DEFAULT

#define LED1_GPIO     (PIO_PA20_IDX)
#define LED1_FLAGS    (PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED1_ACTIVE_LEVEL 0

/** LED #2 pin definition (RED). */
#define PIN_LED_2_MASK PIO_PC20
#define PIN_LED_2_PIO PIOC
#define PIN_LED_2_ID ID_PIOC
#define PIN_LED_2_TYPE PIO_OUTPUT_1
#define PIN_LED_2_ATTR PIO_DEFAULT

#define LED_2_NAME    "red LED D4"
#define LED2_GPIO     (PIO_PC20_IDX)
#define LED2_FLAGS    (PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED2_ACTIVE_LEVEL 1

#define BOARD_NUM_OF_LED 3

/** HSMCI pins definition. */
/*! Number of slot connected on HSMCI interface */
#define SD_MMC_HSMCI_MEM_CNT      1
#define SD_MMC_HSMCI_SLOT_0_SIZE  4
#define PINS_HSMCI   {0x3fUL << 26, PIOA, ID_PIOA, PIO_PERIPH_C, PIO_PULLUP}
/** HSMCI MCCDA pin definition. */
#define PIN_HSMCI_MCCDA_GPIO            (PIO_PA28_IDX)
#define PIN_HSMCI_MCCDA_FLAGS           (PIO_PERIPH_C | PIO_DEFAULT)
/** HSMCI MCCK pin definition. */
#define PIN_HSMCI_MCCK_GPIO             (PIO_PA29_IDX)
#define PIN_HSMCI_MCCK_FLAGS            (PIO_PERIPH_C | PIO_DEFAULT)
/** HSMCI MCDA0 pin definition. */
#define PIN_HSMCI_MCDA0_GPIO            (PIO_PA30_IDX)
#define PIN_HSMCI_MCDA0_FLAGS           (PIO_PERIPH_C | PIO_DEFAULT)
/** HSMCI MCDA1 pin definition. */
#define PIN_HSMCI_MCDA1_GPIO            (PIO_PA31_IDX)
#define PIN_HSMCI_MCDA1_FLAGS           (PIO_PERIPH_C | PIO_DEFAULT)
/** HSMCI MCDA2 pin definition. */
#define PIN_HSMCI_MCDA2_GPIO            (PIO_PA26_IDX)
#define PIN_HSMCI_MCDA2_FLAGS           (PIO_PERIPH_C | PIO_DEFAULT)
/** HSMCI MCDA3 pin definition. */
#define PIN_HSMCI_MCDA3_GPIO            (PIO_PA27_IDX)
#define PIN_HSMCI_MCDA3_FLAGS           (PIO_PERIPH_C | PIO_DEFAULT)
/** SD/MMC card detect pin definition. */

#ifdef BOARD_REV_A
#define PIN_HSMCI_CD {PIO_PA15, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP}
#define SD_MMC_0_CD_GPIO            (PIO_PA15_IDX)
#define SD_MMC_0_CD_PIO_ID          ID_PIOA
#define SD_MMC_0_CD_FLAGS           (PIO_INPUT | PIO_PULLUP)
#define SD_MMC_0_CD_DETECT_VALUE    0
#endif

#ifdef BOARD_REV_B
#define PIN_HSMCI_CD {PIO_PA6, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP}
#define SD_MMC_0_CD_GPIO            (PIO_PA6_IDX)
#define SD_MMC_0_CD_PIO_ID          ID_PIOA
#define SD_MMC_0_CD_FLAGS           (PIO_INPUT | PIO_PULLUP)
#define SD_MMC_0_CD_DETECT_VALUE    0
#endif

/** Push button #0 definition. Attributes = pull-up + debounce + interrupt on rising edge. */
#define PUSHBUTTON_1_NAME    "USRPB1"
#define GPIO_PUSH_BUTTON_1   (PIO_PB3_IDX)
#define GPIO_PUSH_BUTTON_1_FLAGS    (PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)

#define PIN_PUSHBUTTON_1    {PIO_PB3, PIOB, ID_PIOB, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
#define PIN_PUSHBUTTON_1_MASK PIO_PB3
#define PIN_PUSHBUTTON_1_PIO PIOB
#define PIN_PUSHBUTTON_1_ID ID_PIOB
#define PIN_PUSHBUTTON_1_TYPE PIO_INPUT
#define PIN_PUSHBUTTON_1_ATTR PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE

/** Push button #1 definition. Attributes = pull-up + debounce + interrupt on falling edge. */
#define PUSHBUTTON_2_NAME    "USRPB2"
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

#define PIN_TC0_TIOA0 (PIO_PA0_IDX)
#define PIN_TC0_TIOA0_MUX   (IOPORT_MODE_MUX_B)
#define PIN_TC0_TIOA0_FLAGS (PIO_PERIPH_B | PIO_DEFAULT)

#define PIN_TC0_TIOA1 (PIO_PA15_IDX)
#define PIN_TC0_TIOA1_MUX   (IOPORT_MODE_MUX_B)
#define PIN_TC0_TIOA1_FLAGS (PIO_PERIPH_B | PIO_DEFAULT)

#define PIN_TC0_TIOA1_PIO     PIOA
#define PIN_TC0_TIOA1_MASK  PIO_PA15
#define PIN_TC0_TIOA1_ID      ID_PIOA
#define PIN_TC0_TIOA1_TYPE   PIO_PERIPH_B
#define PIN_TC0_TIOA1_ATTR   PIO_DEFAULT

#define PIN_TC0_TIOA2 (PIO_PA26_IDX)
#define PIN_TC0_TIOA2_MUX   (IOPORT_MODE_MUX_B)
#define PIN_TC0_TIOA2_FLAGS (PIO_PERIPH_B | PIO_DEFAULT)

#define PIN_TC0_TIOA2_PIO     PIOA
#define PIN_TC0_TIOA2_MASK  PIO_PA26
#define PIN_TC0_TIOA2_ID      ID_PIOA
#define PIN_TC0_TIOA2_TYPE   PIO_INPUT
#define PIN_TC0_TIOA2_ATTR   PIO_DEFAULT

/** PWMC PWM0 pin definition: Output High. */
#define PIN_PWMC_PWMH0  {PIO_PC18B_PWMH0, PIOC, ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_PWMC_PWMH0_TRIG   PIO_PC18_IDX
#define PIN_PWMC_PWMH0_TRIG_FLAG   PIO_PERIPH_B | PIO_DEFAULT
/** PWMC PWM0 pin definition: Output Low. */
#define PIN_PWMC_PWML0  {PIO_PA19B_PWML0, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
/** PWMC PWM1 pin definition: Output High. */
#define PIN_PWMC_PWMH1  {PIO_PC19B_PWMH1, PIOC, ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
/** PWMC PWM1 pin definition: Output Low. */
#define PIN_PWMC_PWML1  {PIO_PA20B_PWML1, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
/** PWMC PWM2 pin definition: Output High. */
#define PIN_PWMC_PWMH2  {PIO_PC20B_PWMH2, PIOC, ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
/** PWMC PWM2 pin definition: Output Low. */
#define PIN_PWMC_PWML2  {PIO_PA16C_PWML2, PIOA, ID_PIOA, PIO_PERIPH_C, PIO_DEFAULT}
/** PWMC PWM3 pin definition: Output High. */
#define PIN_PWMC_PWMH3  {PIO_PC21B_PWMH3, PIOC, ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
/** PWMC PWM3 pin definition: Output Low. */
#define PIN_PWMC_PWML3  {PIO_PA15C_PWML3, PIOA, ID_PIOA, PIO_PERIPH_C, PIO_DEFAULT}
/** PWM pins definition for LED0 */
#define PIN_PWM_LED0 PIN_PWMC_PWMH0, PIN_PWMC_PWML0
/** PWM pins definition for LED1 */
#define PIN_PWM_LED1 PIN_PWMC_PWMH1, PIN_PWMC_PWML1
/** PWM pins definition for LED2 */
#define PIN_PWM_LED2 PIN_PWMC_PWMH2, PIN_PWMC_PWML2

/** PWM LED0 pin definitions. */
#define PIN_PWM_LED0_GPIO    PIO_PA19_IDX
#define PIN_PWM_LED0_FLAGS   (PIO_PERIPH_B | PIO_DEFAULT)
#define PIN_PWM_LED0_CHANNEL PWM_CHANNEL_0

/** PWM LED1 pin definitions. */
#define PIN_PWM_LED1_GPIO    PIO_PA20_IDX
#define PIN_PWM_LED1_FLAGS   (PIO_PERIPH_B | PIO_DEFAULT)
#define PIN_PWM_LED1_CHANNEL PWM_CHANNEL_1

/** PWM LED2 pin definitions. */
#define PIN_PWM_LED2_GPIO    PIO_PC20_IDX
#define PIN_PWM_LED2_FLAGS   (PIO_PERIPH_B | PIO_DEFAULT)

/** SPI MISO pin definition. */
#define SPI_MISO_GPIO         (PIO_PA12_IDX)
#define SPI_MISO_FLAGS       (PIO_PERIPH_A | PIO_DEFAULT)
/** SPI MOSI pin definition. */
#define SPI_MOSI_GPIO         (PIO_PA13_IDX)
#define SPI_MOSI_FLAGS       (PIO_PERIPH_A | PIO_DEFAULT)
/** SPI SPCK pin definition. */
#define SPI_SPCK_GPIO         (PIO_PA14_IDX)
#define SPI_SPCK_FLAGS       (PIO_PERIPH_A | PIO_DEFAULT)

/** SPI chip select 0 pin definition. (Only one configuration is possible) */
#define SPI_NPCS0_GPIO         (PIO_PA11_IDX)
#define SPI_NPCS0_FLAGS           (PIO_PERIPH_A | PIO_DEFAULT)
/** SPI chip select 1 pin definition. (multiple configurations are possible) */
#define SPI_NPCS1_PA9_GPIO     (PIO_PA9_IDX)
#define SPI_NPCS1_PA9_FLAGS       (PIO_PERIPH_B | PIO_DEFAULT)
#define SPI_NPCS1_PA31_GPIO    (PIO_PA31_IDX)
#define SPI_NPCS1_PA31_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
#define SPI_NPCS1_PB14_GPIO    (PIO_PB14_IDX)
#define SPI_NPCS1_PB14_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
#define SPI_NPCS1_PC4_GPIO     (PIO_PC4_IDX)
#define SPI_NPCS1_PC4_FLAGS       (PIO_PERIPH_B | PIO_DEFAULT)
/** SPI chip select 2 pin definition. (multiple configurations are possible) */
#define SPI_NPCS2_PA10_GPIO    (PIO_PA10_IDX)
#define SPI_NPCS2_PA10_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)
#define SPI_NPCS2_PA30_GPIO    (PIO_PA30_IDX)
#define SPI_NPCS2_PA30_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)
#define SPI_NPCS2_PB2_GPIO     (PIO_PB2_IDX)
#define SPI_NPCS2_PB2_FLAGS       (PIO_PERIPH_B | PIO_DEFAULT)
/** SPI chip select 3 pin definition. (multiple configurations are possible) */
#define SPI_NPCS3_PA3_GPIO     (PIO_PA3_IDX)
#define SPI_NPCS3_PA3_FLAGS       (PIO_PERIPH_B | PIO_DEFAULT)
#define SPI_NPCS3_PA5_GPIO     (PIO_PA5_IDX)
#define SPI_NPCS3_PA5_FLAGS       (PIO_PERIPH_B | PIO_DEFAULT)
#define SPI_NPCS3_PA22_GPIO    (PIO_PA22_IDX)
#define SPI_NPCS3_PA22_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)

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
#define PIN_PCK_0_PIO PIOA
#define PIN_PCK_0_ID ID_PIOA
#define PIN_PCK_0_TYPE PIO_PERIPH_B
#define PIN_PCK_0_ATTR PIO_DEFAULT

#define PIN_PCK1 (PIO_PA17_IDX)
#define PIN_PCK1_FLAGS (PIO_PERIPH_B | PIO_DEFAULT)

#define PIN_PCK_1_MASK PIO_PA17
#define PIN_PCK_1_PIO PIOA
#define PIN_PCK_1_ID ID_PIOA
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
#define PIN_USART0_RXD    {PIO_PA5A_RXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RXD_IDX        (PIO_PA5_IDX)
#define PIN_USART0_RXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin TX */
#define PIN_USART0_TXD    {PIO_PA6A_TXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_TXD_IDX        (PIO_PA6_IDX)
#define PIN_USART0_TXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin CTS */
#define PIN_USART0_CTS    {PIO_PA8A_CTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_CTS_IDX        (PIO_PA8_IDX)
#define PIN_USART0_CTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin RTS */
#define PIN_USART0_RTS    {PIO_PA7A_RTS0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RTS_IDX        (PIO_PA7_IDX)
#define PIN_USART0_RTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART0 pin SCK */
#define PIN_USART0_SCK    {PIO_PA2B_SCK0, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART0_SCK_IDX        (PIO_PA2_IDX)
#define PIN_USART0_SCK_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)

/** USART1 pin RX */
#define PIN_USART1_RXD    {PIO_PA21A_RXD1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_RXD_IDX        (PIO_PA21_IDX)
#define PIN_USART1_RXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART1 pin TX */
#define PIN_USART1_TXD    {PIO_PA22A_TXD1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_TXD_IDX        (PIO_PA22_IDX)
#define PIN_USART1_TXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART1 pin CTS */
#define PIN_USART1_CTS    {PIO_PA25A_CTS1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_CTS_IDX        (PIO_PA25_IDX)
#define PIN_USART1_CTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART1 pin RTS */
#define PIN_USART1_RTS    {PIO_PA24A_RTS1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_RTS_IDX        (PIO_PA24_IDX)
#define PIN_USART1_RTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/** USART1 pin ENABLE */
#define PIN_USART1_EN     {PIO_PA23A_SCK1, PIOA, ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
#define PIN_USART1_EN_IDX         (PIO_PA23_IDX)
#define PIN_USART1_EN_FLAGS       (PIO_OUTPUT_0 | PIO_DEFAULT)
/** USART1 pin SCK */
#define PIN_USART1_SCK    {PIO_PA23A_SCK1, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_SCK_IDX        (PIO_PA23_IDX)
#define PIN_USART1_SCK_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)

/** USB VBus monitoring pin definition. */
#define PIN_USB_VBUS    {PIO_PC21, PIOC, ID_PIOC, PIO_INPUT, PIO_PULLUP}
#define USB_VBUS_FLAGS    (PIO_INPUT | PIO_DEBOUNCE | PIO_IT_EDGE)
#define USB_VBUS_PIN_IRQn (PIOC_IRQn)
#define USB_VBUS_PIN      (PIO_PC21_IDX)
#define USB_VBUS_PIO_ID   (ID_PIOC)
#define USB_VBUS_PIO_MASK (PIO_PC21)
/* This pin can not be used as fast wakeup source such as
 * USB_VBUS_WKUP PMC_FSMR_FSTT7 */

/** NandFlash pins definition: OE. */
#define PIN_EBI_NANDOE    (PIO_PC9_IDX)
#define PIN_EBI_NANDOE_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

/** NandFlash pins definition: WE. */
#define PIN_EBI_NANDWE    (PIO_PC10_IDX)
#define PIN_EBI_NANDWE_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

/** NandFlash pins definition: CLE. */
#define PIN_EBI_NANDCLE    (PIO_PC17_IDX)
#define PIN_EBI_NANDCLE_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

/** NandFlash pins definition: ALE. */
#define PIN_EBI_NANDALE    (PIO_PC16_IDX)
#define PIN_EBI_NANDALE_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

/** NandFlash pins definition: DATA. */
#define PIN_EBI_NANDIO_0    (PIO_PC0_IDX)
#define PIN_EBI_NANDIO_0_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

#define PIN_EBI_NANDIO_1    (PIO_PC1_IDX)
#define PIN_EBI_NANDIO_1_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

#define PIN_EBI_NANDIO_2    (PIO_PC2_IDX)
#define PIN_EBI_NANDIO_2_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

#define PIN_EBI_NANDIO_3    (PIO_PC3_IDX)
#define PIN_EBI_NANDIO_3_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

#define PIN_EBI_NANDIO_4    (PIO_PC4_IDX)
#define PIN_EBI_NANDIO_4_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

#define PIN_EBI_NANDIO_5    (PIO_PC5_IDX)
#define PIN_EBI_NANDIO_5_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

#define PIN_EBI_NANDIO_6    (PIO_PC6_IDX)
#define PIN_EBI_NANDIO_6_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

#define PIN_EBI_NANDIO_7    (PIO_PC7_IDX)
#define PIN_EBI_NANDIO_7_FLAGS    (PIO_PERIPH_A | PIO_PULLUP)

/** Nandflash chip enable pin definition. */
#define PIN_NF_CE_IDX    (PIO_PC14_IDX)
#define PIN_NF_CE_FLAGS    (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)

/** Nandflash ready/busy pin definition. */
#define PIN_NF_RB_IDX    (PIO_PC18_IDX)
#define PIN_NF_RB_FLAGS    (PIO_INPUT | PIO_PULLUP)

/* Chip select number for nand */
#define BOARD_NAND_CS    0

/*----------------------------------------------------------------------------*/
/**
 * \page sam4s_ek_usb "SAM4S-EK - USB device"
 *
 * \section Definitions
 * - \ref BOARD_USB_BMATTRIBUTES
 * - \ref CHIP_USB_UDP
 * - \ref CHIP_USB_PULLUP_INTERNAL
 * - \ref CHIP_USB_NUMENDPOINTS
 * - \ref CHIP_USB_ENDPOINTS_MAXPACKETSIZE
 * - \ref CHIP_USB_ENDPOINTS_BANKS
 */

/** USB attributes configuration descriptor (bus or self powered, remote wakeup) */
#define BOARD_USB_BMATTRIBUTES              USBConfigurationDescriptor_SELFPOWERED_RWAKEUP

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
 * \page sam4s_ek_extcomp "SAM4S-EK - External components"
 * This page lists the definitions related to external on-board components
 * located in the board.h file for the SAM4S-EK.
 *
 * SD Card
 * - \ref BOARD_SD_PINS
 * - \ref BOARD_SD_PIN_CD
 *
 * LCD
 * - \ref BOARD_LCD_ILI9325
 * - \ref BOARD_LCD_PINS
 * - \ref BOARD_BACKLIGHT_PIN
 * - \ref BOARD_LCD_BASE
 * - \ref BOARD_LCD_RS
 * - \ref BOARD_LCD_WIDTH
 * - \ref BOARD_LCD_HEIGHT
 *
 * TouchScreen
 * - \ref BOARD_TSC_ADS7843
 * - \ref PIN_TCS_IRQ
 * - \ref PIN_TCS_BUSY
 * - \ref BOARD_TSC_SPI_BASE
 * - \ref BOARD_TSC_SPI_ID
 * - \ref BOARD_TSC_SPI_PINS
 * - \ref BOARD_TSC_NPCS
 * - \ref BOARD_TSC_NPCS_PIN
 *
 */

/** HSMCI pins that shall be configured to access the SD card. */
#define BOARD_SD_PINS               PINS_HSMCI
/** HSMCI Card Detect pin. */
#define BOARD_SD_PIN_CD             PIN_HSMCI_CD

/** Indicates board has an ILI9325 external component to manage LCD. */
#define BOARD_LCD_ILI9325

/** Backlight pin definition. */
#define BOARD_AAT31XX_SET_GPIO      PIO_PC13_IDX
#define BOARD_AAT31XX_SET_FLAGS     PIO_OUTPUT_0 | PIO_DEFAULT
/** Define ILI9325 base address. */
#define BOARD_ILI9325_ADDR          0x61000000
/** Define ILI9325 register select signal. */
#define BOARD_ILI9325_RS            (1 << 1)
/** Define ILI93xx base address. */
#define BOARD_ILI93XX_ADDR          0x61000000
/** Define ILI93xx register select signal. */
#define BOARD_ILI93XX_RS            (1 << 1)
/** Display width in pixels. */
#define BOARD_LCD_WIDTH             240
/** Display height in pixels. */
#define BOARD_LCD_HEIGHT            320

/** Touchscreen controller IRQ & Busy pin definition. */
#define BOARD_ADS7843_IRQ_GPIO      PIO_PA16_IDX
#define BOARD_ADS7843_IRQ_FLAGS     PIO_INPUT | PIO_PULLUP
#define BOARD_ADS7843_IRQ_WUP_ID    (1 << 15)
#define BOARD_ADS7843_BUSY_GPIO     PIO_PA17_IDX
#define BOARD_ADS7843_BUSY_FLAGS    PIO_INPUT | PIO_PULLUP

/** Base address of SPI peripheral connected to the touchscreen controller. */
#define BOARD_ADS7843_SPI_BASE      SPI
/** Identifier of SPI peripheral connected to the touchscreen controller. */
#define BOARD_ADS7843_SPI_ID        ID_SPI
/** Chip select connected to the touchscreen controller. */
#define BOARD_ADS7843_SPI_NPCS      0

/*----------------------------------------------------------------------------*/
/**
 * \page sam4s_ek_mem "SAM4S-EK - Memories"
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

/* ISO7816 example relate PIN definition. */
#define ISO7816_USART_ID           ID_USART1
#define ISO7816_USART              USART1
#define PIN_ISO7816_RST_IDX        PIO_PA15_IDX
#define PIN_ISO7816_RST_FLAG       (PIO_OUTPUT_0 | PIO_DEFAULT)

#endif  // _SAM4S_EK2_H_
