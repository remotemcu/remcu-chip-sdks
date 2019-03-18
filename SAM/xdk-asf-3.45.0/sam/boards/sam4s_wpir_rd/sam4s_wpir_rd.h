/**
 * \file
 *
 * \brief SAM4S-WPIR-RD Board Definition.
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

#ifndef _SAM4S_WPIR_RD_H_
#define _SAM4S_WPIR_RD_H_

#include <conf_board.h>

#define BOARD_REV_A

/*----------------------------------------------------------------------------*/

/**
 *  \page sam4s_wpir-rd_opfreq "SAM4S-WPIR-RD - Operating frequencies"
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
#define BOARD_MCK                                       CHIP_FREQ_CPU_MAX

/** board main clock xtal startup time */
#define BOARD_OSC_STARTUP_US   15625

/*----------------------------------------------------------------------------*/

/**
 * \page sam4s_wpir-rdboard_info "SAM4S-WPIR-RD - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "SAM4S-WPIR-RD"
/** Board definition */
#define sam4swpirrd
/** Family definition */
#define sam4s
/** Core definition */
#define cortexm4

/*----------------------------------------------------------------------------*/

/**
 * \page sam4s_wpir-rd_piodef "SAM4S-WPIR-RD - PIO definitions"
 * This pages lists all the pio definitions. The constants
 * are named using the following convention: PIN_* for a constant which defines
 * a single Pin instance (but may include several PIOs sharing the same
 * controller), and PINS_* for a list of Pin instances.
 *
 * ADC
 * - \ref PIN_ADC0_AD0
 * - \ref PIN_ADC0_AD4
 * - \ref PIN_ADC0_AD5
 * - \ref PINS_ADC
 *
 * UART
 * - \ref PINS_UART
 *
 * EBI
 * - \ref PIN_EBI_DATA_BUS
 * - \ref PIN_EBI_NRD
 * - \ref PIN_EBI_NWE
 * - \ref PIN_EBI_NCS0
 * - \ref PIN_EBI_SRAM_ADDR_BUS
 * - \ref PIN_EBI_SRAM_NBS
 * - \ref PIN_EBI_A1
 * - \ref PIN_EBI_NCS1
 * - \ref PIN_EBI_LCD_RS
 *
 * LEDs
 * - \ref PIN_LED_0
 * - \ref PINS_LEDS
 *
 * Push buttons
 * - \ref PIN_PUSHBUTTON_1
 * - \ref PINS_PUSHBUTTONS
 * - \ref PUSHBUTTON_BP1
 *
 * SPI
 * - \ref PIN_SPI_MISO
 * - \ref PIN_SPI_MOSI
 * - \ref PIN_SPI_SPCK
 * - \ref PINS_SPI
 * - \ref PIN_SPI_NPCS0_PA11
 *
 * PCK0
 * - \ref PIN_PCK0
 *
 * PIO PARALLEL CAPTURE
 * - \ref PIN_PIODCEN1
 * - \ref PIN_PIODCEN2
 *
 * TWI
 * - \ref PIN_TWI_TWD0
 * - \ref PIN_TWI_TWCK0
 * - \ref PINS_TWI0
 *
 * USB
 * - \ref PIN_USB_VBUS
 */

/******************************* ADC definition ******************************/

/** ADC_AD0 pin. */
#define PIN_ADC0_AD0                   {PIO_PA17, PIOA, ID_PIOA, PIO_INPUT, \
                                         PIO_DEFAULT}

/** ADC_AD4 pin. */
#define PIN_ADC0_AD4                   {PIO_PB0, PIOB, ID_PIOB, PIO_INPUT, \
                                         PIO_DEFAULT}

/** ADC_AD5 pin. */
#define PIN_ADC0_AD5                   {PIO_PB1, PIOB, ID_PIOB, PIO_INPUT, \
                                         PIO_DEFAULT}

/** ADC_AD0 pin definition. */
#define ADC0_AD0_GPIO                  (PIO_PA17_IDX)
#define ADC0_AD0_FLAGS                 (PIO_INPUT | PIO_DEFAULT)
#define ADC0_AD0_MASK                  PIO_PA17
#define ADC0_AD0_PIO                   PIOA
#define ADC0_AD0_ID                    ID_PIOA
#define ADC0_AD0_TYPE                  PIO_INPUT
#define ADC0_AD0_ATTR                  PIO_DEFAULT

/** ADC_AD4 pin definition. */
#define ADC0_AD4_GPIO                  (PIO_PB0_IDX)
#define ADC0_AD4_FLAGS                 (PIO_INPUT | PIO_DEFAULT)
#define ADC0_AD4_MASK                  PIO_PB0
#define ADC0_AD4_PIO                   PIOB
#define ADC0_AD4_ID                    ID_PIOB
#define ADC0_AD4_TYPE                  PIO_INPUT
#define ADC0_AD4_ATTR                  PIO_DEFAULT

/** ADC_AD5 pin definition. */
#define ADC0_AD5_GPIO                  (PIO_PB1_IDX)
#define ADC0_AD5_FLAGS                 (PIO_INPUT | PIO_DEFAULT)
#define ADC0_AD5_MASK                  PIO_PB1
#define ADC0_AD5_PIO                   PIOB
#define ADC0_AD5_ID                    ID_PIOB
#define ADC0_AD5_TYPE                  PIO_INPUT
#define ADC0_AD5_ATTR                  PIO_DEFAULT

/** Pins ADC */
#define PINS_ADC                       PIN_ADC0_AD0, PIN_ADC0_AD4, PIN_ADC0_AD5

/** Startup time max, return from Idle mode (in µs) */
#define ADC_STARTUP_TIME_MAX           (15)
/** Track and hold Acquisition Time min (in ns) */
#define ADC_TRACK_HOLD_TIME_MIN        (1200)
/** ADC clock frequence */
#define BOARD_ADC_FREQ                 (6000000UL)

/******************************* UART definition ******************************/

/** UART pins (UTXD0 and URXD0) definitions, PA9,10. */
#define PINS_UART                      (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0)
#define PINS_UART_FLAGS                (PIO_PERIPH_A | PIO_DEFAULT)

#define PINS_UART_MASK                 PIO_PA9A_URXD0 | PIO_PA10A_UTXD0
#define PINS_UART_PIO                  PIOA
#define PINS_UART_ID                   ID_PIOA
#define PINS_UART_TYPE                 PIO_PERIPH_A
#define PINS_UART_ATTR                 PIO_DEFAULT

#define CONSOLE_UART                   UART0
#define CONSOLE_UART_ID                ID_UART0

/******************************* EBI definition ******************************/
/** EBI Data Bus pins */
#define PIN_EBI_DATA_BUS_D0            PIO_PC0_IDX
#define PIN_EBI_DATA_BUS_D1            PIO_PC1_IDX
#define PIN_EBI_DATA_BUS_D2            PIO_PC2_IDX
#define PIN_EBI_DATA_BUS_D3            PIO_PC3_IDX
#define PIN_EBI_DATA_BUS_D4            PIO_PC4_IDX
#define PIN_EBI_DATA_BUS_D5            PIO_PC5_IDX
#define PIN_EBI_DATA_BUS_D6            PIO_PC6_IDX
#define PIN_EBI_DATA_BUS_D7            PIO_PC7_IDX
#define PIN_EBI_DATA_BUS_FLAGS         PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_DATA_BUS_MASK          (0xFF)
#define PIN_EBI_DATA_BUS_PIO           PIOC
#define PIN_EBI_DATA_BUS_ID            ID_PIOC
#define PIN_EBI_DATA_BUS_TYPE          PIO_PERIPH_A
#define PIN_EBI_DATA_BUS_ATTR          PIO_PULLUP

#define PIN_EBI_DATA_BUS               {0xFF, PIOC, ID_PIOC, PIO_PERIPH_A, \
                                         PIO_PULLUP}

/** EBI NRD pin */
#define PIN_EBI_NRD                    PIO_PC11_IDX
#define PIN_EBI_NRD_FLAGS              PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_NRD_MASK               PIO_PC11
#define PIN_EBI_NRD_PIO                PIOC
#define PIN_EBI_NRD_ID                 ID_PIOC
#define PIN_EBI_NRD_TYPE               PIO_PERIPH_A
#define PIN_EBI_NRD_ATTR               PIO_PULLUP

/** EBI NWE pin */
#define PIN_EBI_NWE                    PIO_PC8_IDX
#define PIN_EBI_NWE_FLAGS              PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_NWE_MASK               PIO_PC8
#define PIN_EBI_NWE_PIO                PIOC
#define PIN_EBI_NWE_ID                 ID_PIOC
#define PIN_EBI_NWE_TYPE               PIO_PERIPH_A
#define PIN_EBI_NWE_ATTR               PIO_PULLUP

/** EBI NCS0 pin */
#define PIN_EBI_NCS0                   PIO_PC14_IDX
#define PIN_EBI_NCS0_FLAGS             PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_NCS0_MASK              PIO_PC14
#define PIN_EBI_NCS0_PIO               PIOC
#define PIN_EBI_NCS0_ID                ID_PIOC
#define PIN_EBI_NCS0_TYPE              PIO_PERIPH_A
#define PIN_EBI_NCS0_ATTR              PIO_PULLUP

/** EBI pins for SRAM address bus */
#define PIN_EBI_ADDR_BUS_A19           PIO_PC16_IDX /* A19 */
#define PIN_EBI_ADDR_BUS_A0            PIO_PC18_IDX /* A0 */
#define PIN_EBI_ADDR_BUS_A1            PIO_PC19_IDX /* A1 */
#define PIN_EBI_ADDR_BUS_A2            PIO_PC20_IDX /* A2 */
#define PIN_EBI_ADDR_BUS_A3            PIO_PC21_IDX /* A3 */
#define PIN_EBI_ADDR_BUS_A4            PIO_PC22_IDX /* A4 */
#define PIN_EBI_ADDR_BUS_A5            PIO_PC23_IDX /* A5 */
#define PIN_EBI_ADDR_BUS_A6            PIO_PC24_IDX /* A6 */
#define PIN_EBI_ADDR_BUS_A7            PIO_PC25_IDX /* A7 */
#define PIN_EBI_ADDR_BUS_A8            PIO_PC26_IDX /* A8 */
#define PIN_EBI_ADDR_BUS_A9            PIO_PC27_IDX /* A9 */
#define PIN_EBI_ADDR_BUS_A10           PIO_PC28_IDX /* A10 */
#define PIN_EBI_ADDR_BUS_A11           PIO_PC29_IDX /* A11 */
#define PIN_EBI_ADDR_BUS_A12           PIO_PC30_IDX /* A12 */
#define PIN_EBI_ADDR_BUS_A13           PIO_PC31_IDX /* A13 */
#define PIN_EBI_ADDR_BUS_FLAG1         PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_SRAM_ADDR_PIOC         {0xFFFD0000, PIOC, ID_PIOC, \
                                         PIO_PERIPH_A, PIO_PULLUP}

#define PIN_EBI_ADDR_BUS_A14           PIO_PA18_IDX /* A14 */
#define PIN_EBI_ADDR_BUS_A15           PIO_PA19_IDX /* A15 */
#define PIN_EBI_ADDR_BUS_A16           PIO_PA20_IDX /* A16 */
#define PIN_EBI_ADDR_BUS_A17           PIO_PA0_IDX  /* A17 */
#define PIN_EBI_ADDR_BUS_A18           PIO_PA1_IDX  /* A18 */
#define PIN_EBI_ADDR_BUS_FLAG2         PIO_PERIPH_C | PIO_PULLUP
#define PIN_EBI_SRAM_ADDR_PIOA         {0x001C0003, PIOA, ID_PIOA, \
                                         PIO_PERIPH_C, PIO_PULLUP}

/** EBI NCS2 pin */
#define PIN_EBI_NCS2                   PIO_PA22_IDX /* LCD CS pin */
#define PIN_EBI_NCS2_FLAGS             PIO_PERIPH_C | PIO_PULLUP
#define PIN_EBI_NCS2_MASK              PIO_PA22
#define PIN_EBI_NCS2_PIO               PIOA
#define PIN_EBI_NCS2_ID                ID_PIOA
#define PIN_EBI_NCS2_TYPE              PIO_PERIPH_C
#define PIN_EBI_NCS2_ATTR              PIO_PULLUP

/** EBI pin for LCD RS */
#define PIN_EBI_LCD_RS                 PIO_PC19_IDX /* LCD RS pin */
#define PIN_EBI_LCD_RS_FLAGS           PIO_PERIPH_A | PIO_PULLUP
#define PIN_EBI_LCD_RS_MASK            PIO_PC19
#define PIN_EBI_LCD_RS_PIO             PIOC
#define PIN_EBI_LCD_RS_ID              ID_PIOC
#define PIN_EBI_LCD_RS_TYPE            PIO_PERIPH_A
#define PIN_EBI_LCD_RS_ATTR            PIO_PULLUP

/******************************* LED definition ******************************/
/** LED #0 pin definition (BLUE). */
#define LED_0_NAME                     "blue LED D1"
#define PIN_LED_0                      {PIO_PC12, PIOC, ID_PIOC, PIO_OUTPUT_1,	\
                                         PIO_DEFAULT}
#define PIN_LED_0_MASK                 PIO_PC12
#define PIN_LED_0_PIO                  PIOC
#define PIN_LED_0_ID                   ID_PIOC
#define PIN_LED_0_TYPE                 PIO_OUTPUT_1
#define PIN_LED_0_ATTR                 PIO_DEFAULT

#define LED0_GPIO                      (PIO_PC12_IDX)
#define LED0_FLAGS                     (PIO_OUTPUT_1 | PIO_DEFAULT)

/**Led blue index. */
#define LED_BLUE                       (0UL)

/** List of all LEDs definitions. */
#define PINS_LEDS                      PIN_LED_0

/******************************* Push-button definition
 *******************************/

/** Push button #1 definition. Attributes = pull-up + debounce + interrupt on
 * rising edge. */
#define PUSHBUTTON_1_NAME              "USRPB1"
#define PIN_PUSHBUTTON_1               {PIO_PA2, PIOA, ID_PIOA, PIO_INPUT, \
                                         PIO_PULLUP | PIO_DEBOUNCE | \
                                         PIO_IT_RISE_EDGE}
#define PIN_PUSHBUTTON_1_MASK          PIO_PA2
#define PIN_PUSHBUTTON_1_PIO           PIOA
#define PIN_PUSHBUTTON_1_ID            ID_PIOA
#define PIN_PUSHBUTTON_1_TYPE          PIO_INPUT
#define PIN_PUSHBUTTON_1_ATTR          PIO_PULLUP | PIO_DEBOUNCE | \
                                         PIO_IT_RISE_EDGE

#define GPIO_PUSH_BUTTON_1             (PIO_PA2_IDX)
#define GPIO_PUSH_BUTTON_1_FLAGS       (PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE | \
                                         PIO_IT_RISE_EDGE)

/** Push button #1 index. */
#define PUSHBUTTON_BP1                 (0UL)

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS               PIN_PUSHBUTTON_1

/******************************* SPI definition
 *********************************/
/** SPI MISO pin. */
#define PIN_SPI_MISO                   {PIO_PA12A_MISO, PIOA, ID_PIOA,	\
                                         PIO_PERIPH_A, PIO_DEFAULT}

/** SPI MOSI pin. */
#define PIN_SPI_MOSI                   {PIO_PA13A_MOSI, PIOA, ID_PIOA,	\
                                         PIO_PERIPH_A, PIO_DEFAULT}

/** SPI SPCK pin. */
#define PIN_SPI_SPCK                   {PIO_PA14A_SPCK, PIOA, ID_PIOA,	\
                                         PIO_PERIPH_A, PIO_DEFAULT}

/** SPI chip select pin. */
#define PIN_SPI_NPCS0                  {PIO_PA11A_NPCS0, PIOA, ID_PIOA, \
                                         PIO_PERIPH_A, PIO_DEFAULT}

/** SPI MISO pin definition. */
#define SPI_MISO_GPIO                  (PIO_PA12_IDX)
#define SPI_MISO_FLAGS                 (PIO_PERIPH_A | PIO_DEFAULT)
#define SPI_MISO_MASK                  PIO_PA12
#define SPI_MISO_PIO                   PIOA
#define SPI_MISO_ID                    ID_PIOA
#define SPI_MISO_TYPE                  PIO_PERIPH_A
#define SPI_MISO_ATTR                  PIO_DEFAULT

/** SPI MOSI pin definition. */
#define SPI_MOSI_GPIO                  (PIO_PA13_IDX)
#define SPI_MOSI_FLAGS                 (PIO_PERIPH_A | PIO_DEFAULT)
#define SPI_MOSI_MASK                  PIO_PA13
#define SPI_MOSI_PIO                   PIOA
#define SPI_MOSI_ID                    ID_PIOA
#define SPI_MOSI_TYPE                  PIO_PERIPH_A
#define SPI_MOSI_ATTR                  PIO_DEFAULT

/** SPI SPCK pin definition. */
#define SPI_SPCK_GPIO                  (PIO_PA14_IDX)
#define SPI_SPCK_FLAGS                 (PIO_PERIPH_A | PIO_DEFAULT)
#define SPI_SPCK_MASK                  PIO_PA14
#define SPI_SPCK_PIO                   PIOA
#define SPI_SPCK_ID                    ID_PIOA
#define SPI_SPCK_TYPE                  PIO_PERIPH_A
#define SPI_SPCK_ATTR                  PIO_DEFAULT

/** SPI chip select 0 pin definition. */
#define SPI_NPCS0_GPIO                 (PIO_PA11_IDX)
#define SPI_NPCS0_FLAGS                (PIO_PERIPH_A | PIO_DEFAULT)
#define SPI_NPCS0_MASK                 PIO_PA11
#define SPI_NPCS0_PIO                  PIOA
#define SPI_NPCS0_ID                   ID_PIOA
#define SPI_NPCS0_TYPE                 PIO_PERIPH_A
#define SPI_NPCS0_ATTR                 PIO_DEFAULT

/** List of SPI pin definitions (MISO, MOSI & SPCK). */
#define PINS_SPI                       PIN_SPI_MISO, PIN_SPI_MOSI, PIN_SPI_SPCK

/******************************* PCK0 definition
 *********************************/
/** PCK0 */
#define PIN_PCK0                       (PIO_PB13_IDX)
#define PIN_PCK0_FLAGS                 (PIO_PERIPH_B | PIO_DEFAULT)

/******************************* TWI definition
 *********************************/
/** TWI0 data pin */
#define PIN_TWI_TWD0                   {PIO_PA3A_TWD0, PIOA, ID_PIOA, \
                                         PIO_PERIPH_A, PIO_DEFAULT}

/** TWI0 clock pin */
#define PIN_TWI_TWCK0                  {PIO_PA4A_TWCK0, PIOA, ID_PIOA,	\
                                         PIO_PERIPH_A, PIO_DEFAULT}

/** TWI0 Data pins definition */
#define TWI0_DATA_GPIO                 PIO_PA3_IDX
#define TWI0_DATA_FLAGS                (PIO_PERIPH_A | PIO_DEFAULT)
#define TWI0_DATA_MASK                 PIO_PA3
#define TWI0_DATA_PIO                  PIOA
#define TWI0_DATA_ID                   ID_PIOA
#define TWI0_DATA_TYPE                 PIO_PERIPH_A
#define TWI0_DATA_ATTR                 PIO_DEFAULT

/** TWI0 clock pins definition */
#define TWI0_CLK_GPIO                  PIO_PA4_IDX
#define TWI0_CLK_FLAGS                 (PIO_PERIPH_A | PIO_DEFAULT)
#define TWI0_CLK_MASK                  PIO_PA4
#define TWI0_CLK_PIO                   PIOA
#define TWI0_CLK_ID                    ID_PIOA
#define TWI0_CLK_TYPE                  PIO_PERIPH_A
#define TWI0_CLK_ATTR                  PIO_DEFAULT

/** TWI0 pins */
#define PINS_TWI0                      PIN_TWI_TWD0, PIN_TWI_TWCK0

#define ID_BOARD_TWI		               ID_TWI0
#define BOARD_TWI			                 TWI0
#define BOARD_TWI_IRQn		             TWI0_IRQn

/******************************* VBUS definition
 *********************************/
/** USB VBUS pin */
#define PIN_USB_VBUS                   {PIO_PC17, PIOC, ID_PIOC, \
                                         PIO_INPUT, PIO_PULLUP}

/** USB VBUS pin definition */
#define USB_VBUS_GPIO                  PIO_PC17_IDX
#define USB_VBUS_FLAGS                 (PIO_INPUT | PIO_PULLUP)
#define USB_VBUS_MASK                  PIO_PC17
#define USB_VBUS_PIO                   PIOC
#define USB_VBUS_ID                    ID_PIOC
#define USB_VBUS_TYPE                  PIO_INPUT

/*----------------------------------------------------------------------------*/

/**
 * \page sam4s_wpir_rd_extcomp "SAM4S-WPIR-RD - External components"
 * This page lists the definitions related to external on-board components
 * located in the board.h file for the ATSAM4S-WPIR-RD.
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
 * SRAM
 * - \ref PIN_SRAM_VCC
 * - \ref BOARD_SRAM_PINS
 * - \ref BOARD_SRAM_BASE
 * - \ref BOARD_SRAM_LENGTH
 *
 * PIR
 * - \ref PINS_PIR
 *
 * Image sensor
 * - \ref PIN_OV_SW_OVT
 * - \ref PIN_OV_RST
 * - \ref PIN_OV_FSIN
 * - \ref PIN_OV_HSYNC
 * - \ref PIN_OV_VSYNC
 * - \ref  PINS_OV
 *
 */

/******************************* LCD definition
 *********************************/
/** board has an ILI9325 external component to manage LCD. */
#define BOARD_LCD_ILI9325

/** Backlight pin. */
#define BOARD_BACKLIGHT_PIN            {PIO_PC13, PIOC, ID_PIOC, \
                                        PIO_OUTPUT_0, PIO_DEFAULT}

/** Backlight pin definition */
#define BOARD_AAT31XX_SET_GPIO         PIO_PC13_IDX
#define BOARD_AAT31XX_SET_FLAGS        (PIO_OUTPUT_0 | PIO_DEFAULT)
#define PIN_BOARD_BACKLIGHT_MASK       PIO_PC13
#define PIN_BOARD_BACKLIGHT_PIO        PIOC
#define PIN_BOARD_BACKLIGHT_ID         ID_PIOC
#define PIN_BOARD_BACKLIGHT_TYPE       PIO_OUTPUT_0
#define PIN_BOARD_BACKLIGHT_ATTR       PIO_PULLUP

/** LCD pins list. */
#define BOARD_LCD_PINS                 PIN_EBI_DATA_BUS, PIN_EBI_NRD, \
                                        PIN_EBI_NWE, PIN_EBI_NCS2, \
                                        PIN_EBI_LCD_RS

/** Define ILI9325 base address. */
#define BOARD_ILI9325_ADDR             (0x62000000UL)

/** Define ILI9325 register select signal. */
#define BOARD_ILI9325_RS               (1UL << 1)

/** Display width in pixels. */
#define BOARD_LCD_WIDTH                (240UL)

/** Display height in pixels. */
#define BOARD_LCD_HEIGHT               (320UL)

/** Define ILI9325 chip select. */
#define BOARD_LCD_SMC_CS               (2UL)

/** Define ILI9325 chip select. */
#define BOARD_LCD_SMC_SETUP            (SMC_SETUP_NWE_SETUP(2) | \
                                        SMC_SETUP_NCS_WR_SETUP(2) | \
                                        SMC_SETUP_NRD_SETUP(2) | \
                                        SMC_SETUP_NCS_RD_SETUP(2))

/** Define ILI9325 chip select. */
#define BOARD_LCD_SMC_PULSE            (SMC_PULSE_NWE_PULSE(4) | \
                                        SMC_PULSE_NCS_WR_PULSE(4) | \
                                        SMC_PULSE_NRD_PULSE(10) | \
                                        SMC_PULSE_NCS_RD_PULSE(10))

/** Define ILI9325 chip select. */
#define BOARD_LCD_SMC_CYCLE            (SMC_CYCLE_NWE_CYCLE(10) | \
                                        SMC_CYCLE_NRD_CYCLE(22))

/** Define ILI9325 chip select. */
#define BOARD_LCD_SMC_MODE             (SMC_MODE_READ_MODE| \
                                        SMC_MODE_WRITE_MODE)

/******************************* SRAM definition
 *********************************/
/** SRAM_VCC pins */
#define PIN_SRAM_VCC                   { PIO_PC9, PIOC, ID_PIOC, \
                                         PIO_OUTPUT_0, PIO_DEFAULT }

/** SRAM_VCC pins definition */
#define SRAM_VCC_GPIO                  PIO_PC9_IDX
#define SRAM_VCC_FLAGS                 (PIO_OUTPUT_0 | PIO_DEFAULT)
#define SRAM_VCC_MASK                  PIO_PC9
#define SRAM_VCC_PIO                   PIOC
#define SRAM_VCC_ID                    ID_PIOC
#define SRAM_VCC_TYPE                  PIO_OUTPUT_0

/** SRAM pins list */
#define BOARD_SRAM_PINS                PIN_EBI_DATA_BUS, PIN_EBI_NCS0,	\
  PIN_EBI_NRD, PIN_EBI_NWE, PIN_SRAM_VCC,	\
  PIN_EBI_SRAM_ADDR_PIOA, PIN_EBI_SRAM_ADDR_PIOC

/** Define SRAM base address. */
#define BOARD_SRAM_BASE                ((void *)0x60000000UL)

/** Define SRAM chip select. */
#define BOARD_SRAM_CS                  (0UL)

/** Define SRAM length. */
#define BOARD_SRAM_LENGTH              ((uint32_t)0x00100000UL)

/******************************* PIR definition
 *********************************/
/** List of PIR sensor definitions. */
#define PINS_PIR                       PIN_ADC0_AD0

/******************************* Image sensor definition
 *********************************/
/** pin for OV_VDD */
#define PIN_OV_SW_OVT                  { PIO_PC10, PIOC, ID_PIOC, \
                                         PIO_OUTPUT_1, PIO_DEFAULT} /* OV_VDD */
#define PIN_OV_RST                     { PIO_PC15, PIOC, ID_PIOC, \
                                         PIO_OUTPUT_1, PIO_DEFAULT}
#define PIN_OV_FSIN                    { PIO_PA21, PIOA, ID_PIOA, \
                                         PIO_OUTPUT_0, PIO_DEFAULT}

/** HSYNC pin */
#define PIN_OV_HSYNC                   { PIO_PA16, PIOA, ID_PIOA, \
                                         PIO_INPUT, PIO_PULLUP | \
                                         PIO_IT_RISE_EDGE }

/** VSYNC pin */
#define PIN_OV_VSYNC                   { PIO_PA15, PIOA, ID_PIOA, \
                                         PIO_INPUT, PIO_PULLUP | \
                                         PIO_IT_RISE_EDGE }

/** OV_SW_OVT pin definition */
#define OV_SW_OVT_GPIO                 PIO_PC10_IDX
#define OV_SW_OVT_FLAGS                (PIO_OUTPUT_1 | PIO_DEFAULT)
#define OV_SW_OVT_MASK                 PIO_PC10
#define OV_SW_OVT_PIO                  PIOC
#define OV_SW_OVT_ID                   ID_PIOC
#define OV_SW_OVT_TYPE                 PIO_OUTPUT_1

/** OV_RST pin definition */
#define OV_RST_GPIO                    PIO_PC15_IDX
#define OV_RST_FLAGS                   (PIO_OUTPUT_1 | PIO_DEFAULT)
#define OV_RST_MASK                    PIO_PC15
#define OV_RST_PIO                     PIOC
#define OV_RST_ID                      ID_PIOC
#define OV_RST_TYPE                    PIO_OUTPUT_1

/** OV_RST pin definition */
#define OV_FSIN_GPIO                   PIO_PA21_IDX
#define OV_FSIN_FLAGS                  (PIO_OUTPUT_0 | PIO_DEFAULT)
#define OV_FSIN_MASK                   PIO_PA21
#define OV_FSIN_PIO                    PIOA
#define OV_FSIN_ID                     ID_PIOA
#define OV_FSIN_TYPE                   PIO_OUTPUT_0

/** OV_HSYNC pin definition */
#define OV_HSYNC_GPIO                  PIO_PA16_IDX
#define OV_HSYNC_FLAGS                 (PIO_PULLUP | PIO_IT_RISE_EDGE)
#define OV_HSYNC_MASK                  PIO_PA16
#define OV_HSYNC_PIO                   PIOA
#define OV_HSYNC_ID                    ID_PIOA
#define OV_HSYNC_TYPE                  PIO_PULLUP

/** OV_VSYNC pin definition */
#define OV_VSYNC_GPIO                  PIO_PA15_IDX
#define OV_VSYNC_FLAGS                 (PIO_PULLUP | PIO_IT_RISE_EDGE)
#define OV_VSYNC_MASK                  PIO_PA15
#define OV_VSYNC_PIO                   PIOA
#define OV_VSYNC_ID                    ID_PIOA
#define OV_VSYNC_TYPE                  PIO_PULLUP

/** OV Data Bus pins */
#define OV_DATA_BUS_D2                 PIO_PA24_IDX
#define OV_DATA_BUS_D3                 PIO_PA25_IDX
#define OV_DATA_BUS_D4                 PIO_PA26_IDX
#define OV_DATA_BUS_D5                 PIO_PA27_IDX
#define OV_DATA_BUS_D6                 PIO_PA28_IDX
#define OV_DATA_BUS_D7                 PIO_PA29_IDX
#define OV_DATA_BUS_D8                 PIO_PA30_IDX
#define OV_DATA_BUS_D9                 PIO_PA31_IDX
#define OV_DATA_BUS_FLAGS              (PIO_INPUT | PIO_PULLUP)
#define OV_DATA_BUS_MASK               (0xFF000000UL)
#define OV_DATA_BUS_PIO                PIOA
#define OV_DATA_BUS_ID                 ID_PIOA
#define OV_DATA_BUS_TYPE               PIO_INPUT
#define OV_DATA_BUS_ATTR               PIO_DEFAULT

/** List of Image sensor definitions. */
#define PINS_OV                        PIN_OV_SW_OVT, PIN_PCK0, PIN_OV_RST


/******************************* Parallel Capture definition
 *********************************/
/** Parallel Capture Mode Data Enable1 */
#define PIN_PIODCEN1                   PIO_PA15

/** Parallel Capture Mode Data Enable2 */
#define PIN_PIODCEN2                   PIO_PA16

/******************************* DEBUG definition
 *********************************/
#define PIN_PA11_DEBUG                 {PIO_PA11, PIOA, ID_PIOA, \
                                         PIO_OUTPUT_0, PIO_DEFAULT}
#define PIN_PA5_DEBUG                  {PIO_PA5, PIOA, ID_PIOA, \
                                         PIO_OUTPUT_0, PIO_DEFAULT}
#define PIN_DEBUG                      PIN_PA11_DEBUG, PIN_PA5_DEBUG

/*----------------------------------------------------------------------------*/

/**
 * \page sam4s_wpir_rd_usb "SAM4S-WPIR-RD - USB device"
 *
 * \section Definitions
 * - \ref BOARD_USB_BMATTRIBUTES
 * - \ref CHIP_USB_UDP
 * - \ref CHIP_USB_PULLUP_INTERNAL
 * - \ref CHIP_USB_NUMENDPOINTS
 * - \ref CHIP_USB_ENDPOINTS_MAXPACKETSIZE
 * - \ref CHIP_USB_ENDPOINTS_BANKS
 */

/** USB attributes configuration descriptor (bus or self powered, remote wakeup)
**/
#define BOARD_USB_BMATTRIBUTES   USBConfigurationDescriptor_SELFPOWERED_RWAKEUP

/** Indicates chip has an UDP Full Speed. */
#define CHIP_USB_UDP

/** Indicates chip has an internal pull-up. */
#define CHIP_USB_PULLUP_INTERNAL

/** Number of USB endpoints */
#define CHIP_USB_NUMENDPOINTS          (8)

/** Endpoints max paxcket size */
#define CHIP_USB_ENDPOINTS_MAXPACKETSIZE(i) \
  ((i == 0) ? 64 : \
  ((i == 1) ? 64 : \
  ((i == 2) ? 64 : \
  ((i == 3) ? 64 : \
  ((i == 4) ? 512 : \
  ((i == 5) ? 512 : \
  ((i == 6) ? 64 : \
  ((i == 7) ? 64 : 0))))))))

/** Endpoints Number of Bank */
#define CHIP_USB_ENDPOINTS_BANKS(i) \
  ((i == 0) ? 1 :	\
  ((i == 1) ? 2 :	\
  ((i == 2) ? 2 :	\
  ((i == 3) ? 1 :	\
  ((i == 4) ? 2 :	\
  ((i == 5) ? 2 :	\
  ((i == 6) ? 2 :	\
  ((i == 7) ? 2 : 0))))))))

#endif /* #ifndef _BOARD_ */
