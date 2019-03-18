/**
 * \file
 *
 * \brief SAM4L Xplained Pro board definition
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

#ifndef SAM4L_XPLAINED_PRO_INCLUDED
#define SAM4L_XPLAINED_PRO_INCLUDED

#include <conf_board.h>

/**
 * \ingroup group_common_boards
 * \defgroup sam4l_xplained_pro_group SAM4L Xplained Pro board
 *
 * @{
 */

/**
 * \defgroup sam4l_xplained_pro_config_group Configuration
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
 * \defgroup sam4l_xplained_pro_features_group Features
 *
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

//! Name string macro
#define BOARD_NAME          "SAM4L Xplained Pro"
#define MCU_SOC_NAME        "ATSAM4LC4C"

//! \name Board oscillator definitions
//@{
//! Osc frequency (Hz.) and startup time (RCOsc periods)
#define FOSC0                     (12000000UL)
//! Osc32 frequency (Hz.) and startup time (RCOsc periods)
#define FOSC32                    (32768UL)
#define BOARD_OSC32_IS_XTAL       true
#define BOARD_OSC32_HZ            FOSC32
#define BOARD_OSC32_STARTUP_US    (750000UL)
#define BOARD_OSC32_SELCURR       BSCIF_OSCCTRL32_SELCURR(10)
#define BOARD_OSC0_IS_XTAL        true
#define BOARD_OSC0_HZ             FOSC0
#define BOARD_OSC0_STARTUP_US     (6100UL)
//@}

//! \name LED0 definitions
//@{
#define LED0                      PIN_PC07
#define LED0_PIN                  PIN_PC07 /* Wrapper definition */
#define LED0_GPIO                 PIN_PC07 /* Wrapper definition */
#define LED0_ACTIVE               false
#define LED0_INACTIVE             !LED0_ACTIVE
//@}

//! \name SW0 definitions
//@{
#define GPIO_PUSH_BUTTON_0        PIN_PC24 /* Wrapper definition */
#define SW0_PIN                   PIN_PC24
#define SW0_ACTIVE                false
#define SW0_INACTIVE              !SW0_ACTIVE
#define SW0_EIC_PIN               PIN_PC24B_EIC_EXTINT1
#define SW0_EIC_PIN_MUX           MUX_PC24B_EIC_EXTINT1
#define SW0_EIC_LINE              1
//@}

//! \name TOUCH QTouch button definitions
//@{
#define QTOUCH_DISCHARGE_PIN       PIN_PC14
#define QTOUCH_DISCHARGE_MUX       MUX_PC14G_CATB_DIS
#define QTOUCH_SENSE_PIN           PIN_PC13
#define QTOUCH_SENSE_MUX           MUX_PC13G_CATB_SENSE15
#define QTOUCH_PINSEL_BUTTON       15
//@}

/**
 * \name USB pin definitions
 *
 * These are named according to the USBC driver's requirements.
 */
//@{
#define USB_ID_PIN                PIN_PC10
#define USB_ID_FLAGS              (IOPORT_MODE_PULLUP \
		| IOPORT_MODE_GLITCH_FILTER)
#define USB_VBUS_PIN              PIN_PC11
#define USB_VBUS_FLAGS            IOPORT_MODE_GLITCH_FILTER
#define USB_VBOF_PIN              PIN_PC12
#define USB_VBOF_ACTIVE_LEVEL     1
#define USB_VBOF_INACTIVE_LEVEL   0
//@}

//! \name USART connections to GPIO for Virtual Com Port
// @{
#define COM_PORT_USART            USART1
#define COM_PORT_USART_ID         ID_USART1
#define COM_PORT_RX_PIN           PIN_PC26A_USART1_RXD
#define COM_PORT_RX_GPIO          GPIO_PC26A_USART1_RXD
#define COM_PORT_RX_MUX           MUX_PC26A_USART1_RXD
#define COM_PORT_TX_PIN           PIN_PC27A_USART1_TXD
#define COM_PORT_TX_GPIO          GPIO_PC27A_USART1_TXD
#define COM_PORT_TX_MUX           MUX_PC27A_USART1_TXD
// @}

//! \name Embedded debugger USART interface definitions
//@{
#define EDBG_UART_MODULE          USART3
#define EDBG_UART_RX_PIN          PIN_PC28A_USART3_RXD
#define EDBG_UART_RX_MUX          MUX_PC28A_USART3_RXD
#define EDBG_UART_TX_PIN          PIN_PC29A_USART3_TXD
#define EDBG_UART_TX_MUX          MUX_PC29A_USART3_TXD
#define EDBG_UART_CLK_PIN         PIN_PC31A_USART3_CLK
#define EDBG_UART_CLK_MUX         MUX_PC31A_USART3_CLK
//@}

//! \name DACC pins
// @{
#define DACC_EXT_TRIG0_PIN             PIN_PB04E_DACC_EXT_TRIG0
#define DACC_EXT_TRIG0_GPIO            GPIO_PB04E_DACC_EXT_TRIG0
#define DACC_EXT_TRIG0_MUX             MUX_PB04E_DACC_EXT_TRIG0
#define DACC_VOUT_PIN                  PIN_PA06A_DACC_VOUT
#define DACC_VOUT_GPIO                 GPIO_PA06A_DACC_VOUT
#define DACC_VOUT_MUX                  MUX_PA06A_DACC_VOUT
// @}

/**
 * \name LED #0 definitions
 *
 * Wrapper macros for LED0, to ensure common naming across all Xplained Pro
 * boards.
 */
//@{
#define LED_0_NAME                "LED0"
#define LED_0_PIN                 LED0_PIN
#define LED_0_ACTIVE              LED0_ACTIVE
#define LED_0_INACTIVE            LED0_INACTIVE
//@}

//! Number of on-board LEDs
#define LED_COUNT                 1

/**
 * \name LCD Backlight
 */
//@{
#define LCD_BL                        PC05
#define LCD_BL_GPIO                   PIN_PC05
#define LCD_BL_GPIO_MASK              GPIO_PC05

#define LCD_BL_ACTIVE_LEVEL             IOPORT_PIN_LEVEL_HIGH
#define LCD_BL_INACTIVE_LEVEL           IOPORT_PIN_LEVEL_LOW
//@}

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
#define BUTTON_0_EIC_PIN          SW0_EIC_PIN
#define BUTTON_0_EIC_PIN_MUX      SW0_EIC_PIN_MUX
#define BUTTON_0_EIC_LINE         SW0_EIC_LINE

/* Definitions for SW0 when using it as EIC pin */
#define GPIO_PUSH_BUTTON_EIC_PIN        PIN_PC24B_EIC_EXTINT1
#define GPIO_PUSH_BUTTON_EIC_PIN_MASK   GPIO_PC24B_EIC_EXTINT1
#define GPIO_PUSH_BUTTON_EIC_PIN_MUX    MUX_PC24B_EIC_EXTINT1
#define GPIO_PUSH_BUTTON_EIC_LINE       1
#define GPIO_PUSH_BUTTON_EIC_IRQ        EIC_1_IRQn
//@}

//! Number of on-board buttons
#define BUTTON_COUNT              1

//! \name Extension header #1 pin definitions
//@{
#define EXT1_PIN_3                PIN_PA04
#define EXT1_PIN_4                PIN_PA05
#define EXT1_PIN_5                PIN_PB12
#define EXT1_PIN_6                PIN_PC02
#define EXT1_PIN_7                PIN_PC00
#define EXT1_PIN_8                PIN_PC01
#define EXT1_PIN_9                PIN_PC25
#define EXT1_PIN_10               PIN_PB13
#define EXT1_PIN_11               PIN_PA23
#define EXT1_PIN_12               PIN_PA24
#define EXT1_PIN_13               PIN_PB00
#define EXT1_PIN_14               PIN_PB01
#define EXT1_PIN_15               PIN_PC03
#define EXT1_PIN_16               PIN_PA22
#define EXT1_PIN_17               PIN_PA21
#define EXT1_PIN_18               PIN_PC30
//@}

//! \name Extension header #1 pin definitions by function
//@{
#define EXT1_PIN_ADC_0            EXT1_PIN_3
#define EXT1_PIN_ADC_1            EXT1_PIN_4
#define EXT1_PIN_GPIO_0           EXT1_PIN_5
#define EXT1_PIN_GPIO_1           EXT1_PIN_6
#define EXT1_PIN_PWM_0            EXT1_PIN_7
#define EXT1_PIN_PWM_1            EXT1_PIN_8
#define EXT1_PIN_IRQ              EXT1_PIN_9
#define EXT1_PIN_TWI_SDA          EXT1_PIN_11
#define EXT1_PIN_TWI_SCL          EXT1_PIN_12
#define EXT1_PIN_UART_RX          EXT1_PIN_13
#define EXT1_PIN_UART_TX          EXT1_PIN_14
#define EXT1_PIN_SPI_SS_1         EXT1_PIN_10
#define EXT1_PIN_SPI_SS_0         EXT1_PIN_15
#define EXT1_PIN_SPI_MOSI         EXT1_PIN_16
#define EXT1_PIN_SPI_MISO         EXT1_PIN_17
#define EXT1_PIN_SPI_SCK          EXT1_PIN_18
//@}

//! \name Extension header #1 ADC definitions
//@{
#define EXT1_ADC_MODULE           ADCIFE
#define EXT1_ADC_0_CHANNEL        0
#define EXT1_ADC_0_MUX            MUX_PA04A_ADCIFE_AD0
#define EXT1_ADC_1_CHANNEL        1
#define EXT1_ADC_1_MUX            MUX_PA05A_ADCIFE_AD1
//@}

//! \name Extension header #1 PWM definitions
//@{
#define EXT1_PWM_MODULE           TC1
#define EXT1_PWM_CHANNEL          0
#define EXT1_PWM_0_MUX            MUX_PC00D_TC1_A0
#define EXT1_PWM_1_MUX            MUX_PC01D_TC1_B0
//@}

//! \name Extension header #1 IRQ/External interrupt definitions
//@{
#define EXT1_IRQ_MODULE           EIC
#define EXT1_IRQ_MUX              MUX_PC25B_EIC_EXTINT2
#define EXT1_IRQ_MASK             EIC_IMR_INT2
//@}

//! \name Extension header #1 TWI definitions
//@{
#define EXT1_TWI_MODULE           TWIM0
#define EXT1_TWI_SDA_MUX          MUX_PA23B_TWIMS0_TWD
#define EXT1_TWI_SCL_MUX          MUX_PA24B_TWIMS0_TWCK
//@}

//! \name Extension header #1 UART definitions
//@{
#define EXT1_UART_MODULE          USART0
#define EXT1_UART_RX_MUX          MUX_PB00B_USART0_RXD
#define EXT1_UART_TX_MUX          MUX_PB01B_USART0_TXD
//@}

//! \name Extension header #1 SPI definitions
//@{
#define EXT1_SPI_MODULE           SPI
#define EXT1_SPI_SS_1_MUX         MUX_PB13B_SPI_NPCS1
#define EXT1_SPI_SS_0_MUX         MUX_PC03A_SPI_NPCS0
#define EXT1_SPI_SS_MOSI          MUX_PA22A_SPI_MOSI
#define EXT1_SPI_SS_MISO          MUX_PA21A_SPI_MISO
#define EXT1_SPI_SS_SCK           MUX_PC30B_SPI_SCK
//@}

//! \name Extension header #2 pin definitions
//@{
#define EXT2_PIN_3                PIN_PA07
#define EXT2_PIN_4                PIN_PB02
#define EXT2_PIN_5                PIN_PC08
#define EXT2_PIN_6                PIN_PB10
#define EXT2_PIN_7                PIN_PC04
#define EXT2_PIN_8                PIN_PC05
#define EXT2_PIN_9                PIN_PC06
#define EXT2_PIN_10               PIN_PC09
#define EXT2_PIN_11               PIN_PB14
#define EXT2_PIN_12               PIN_PB15
#define EXT2_PIN_13               PIN_PC26
#define EXT2_PIN_14               PIN_PC27
#define EXT2_PIN_15               PIN_PB11
#define EXT2_PIN_16               PIN_PA22
#define EXT2_PIN_17               PIN_PA21
#define EXT2_PIN_18               PIN_PC30
//@}

//! \name Extension header #2 pin definitions by function
//@{
#define EXT2_PIN_ADC_0            EXT2_PIN_3
#define EXT2_PIN_ADC_1            EXT2_PIN_4
#define EXT2_PIN_GPIO_0           EXT2_PIN_5
#define EXT2_PIN_GPIO_1           EXT2_PIN_6
#define EXT2_PIN_PWM_0            EXT2_PIN_7
#define EXT2_PIN_PWM_1            EXT2_PIN_8
#define EXT2_PIN_IRQ              EXT2_PIN_9
#define EXT2_PIN_TWI_SDA          EXT2_PIN_11
#define EXT2_PIN_TWI_SCL          EXT2_PIN_12
#define EXT2_PIN_UART_RX          EXT2_PIN_13
#define EXT2_PIN_UART_TX          EXT2_PIN_14
#define EXT2_PIN_SPI_SS_1         EXT2_PIN_10
#define EXT2_PIN_SPI_SS_0         EXT2_PIN_15
#define EXT2_PIN_SPI_MOSI         EXT2_PIN_16
#define EXT2_PIN_SPI_MISO         EXT2_PIN_17
#define EXT2_PIN_SPI_SCK          EXT2_PIN_18
//@}

//! \name Extension header #2 ADC definitions
//@{
#define EXT2_ADC_MODULE           ADCIFE
#define EXT2_ADC_0_CHANNEL        2
#define EXT2_ADC_0_MUX            MUX_PA07A_ADCIFE_AD2
#define EXT2_ADC_1_CHANNEL        3
#define EXT2_ADC_1_MUX            MUX_PB02A_ADCIFE_AD3
//@}

//! \name Extension header #2 PWM definitions
//@{
#define EXT2_PWM_MODULE           TC1
#define EXT2_PWM_CHANNEL          2
#define EXT2_PWM_0_MUX            MUX_PC04D_TC1_A2
#define EXT2_PWM_1_MUX            MUX_PC05D_TC1_B2
//@}

//! \name Extension header #2 IRQ/External interrupt definitions
//@{
#define EXT2_IRQ_MODULE           EIC
#define EXT2_IRQ_MUX              MUX_PC06B_EIC_EXTINT8
#define EXT2_IRQ_MASK             EIC_IMR_INT8
//@}

//! \name Extension header #2 TWI definitions
//@{
#define EXT2_TWI_MODULE           TWIM3
#define EXT2_TWI_SDA_MUX          MUX_PB14C_TWIMS3_TWD
#define EXT2_TWI_SCL_MUX          MUX_PB15C_TWIMS3_TWCK
//@}

//! \name Extension header #2 UART definitions
//@{
#define EXT2_UART_MODULE          USART1
#define EXT2_UART_RX_MUX          MUX_PC26A_USART1_RXD
#define EXT2_UART_TX_MUX          MUX_PC27A_USART1_TXD
//@}

//! \name Extension header #2 SPI definitions
//@{
#define EXT2_SPI_MODULE           SPI
#define EXT2_SPI_SS_0_MUX         MUX_PB11B_SPI_NPCS2
#define EXT2_SPI_SS_MOSI          MUX_PA22A_SPI_MOSI
#define EXT2_SPI_SS_MISO          MUX_PA21A_SPI_MISO
#define EXT2_SPI_SS_SCK           MUX_PC30B_SPI_SCK
//@}

//! \name Extension header #3 pin definitions
//@{
#define EXT3_PIN_3                PIN_PB03
#define EXT3_PIN_4                PIN_PB04
#define EXT3_PIN_5                PIN_PC15
#define EXT3_PIN_6                PIN_PC16
#define EXT3_PIN_7                PIN_PA08
#define EXT3_PIN_8                PIN_PA09
#define EXT3_PIN_9                PIN_PA06
#define EXT3_PIN_10               PIN_PA10
#define EXT3_PIN_11               PIN_PB14
#define EXT3_PIN_12               PIN_PB15
#define EXT3_PIN_13               PIN_PC26
#define EXT3_PIN_14               PIN_PC27
#define EXT3_PIN_15               PIN_PA17
#define EXT3_PIN_16               PIN_PA20
#define EXT3_PIN_17               PIN_PA19
#define EXT3_PIN_18               PIN_PA18
//@}

//! \name Extension header #3 pin definitions by function
//@{
#define EXT3_PIN_ADC_0            EXT3_PIN_3
#define EXT3_PIN_ADC_1            EXT3_PIN_4
#define EXT3_PIN_GPIO_0           EXT3_PIN_5
#define EXT3_PIN_GPIO_1           EXT3_PIN_6
#define EXT3_PIN_PWM_0            EXT3_PIN_7
#define EXT3_PIN_PWM_1            EXT3_PIN_8
#define EXT3_PIN_IRQ              EXT3_PIN_9
#define EXT3_PIN_TWI_SDA          EXT3_PIN_11
#define EXT3_PIN_TWI_SCL          EXT3_PIN_12
#define EXT3_PIN_UART_RX          EXT3_PIN_13
#define EXT3_PIN_UART_TX          EXT3_PIN_14
#define EXT3_PIN_SPI_SS_1         EXT3_PIN_10
#define EXT3_PIN_SPI_SS_0         EXT3_PIN_15
#define EXT3_PIN_SPI_MOSI         EXT3_PIN_16
#define EXT3_PIN_SPI_MISO         EXT3_PIN_17
#define EXT3_PIN_SPI_SCK          EXT3_PIN_18
//@}

//! \name Extension header #3 ADC definitions
//@{
#define EXT3_ADC_MODULE           ADCIFE
#define EXT3_ADC_0_CHANNEL        4
#define EXT3_ADC_0_MUX            MUX_PB03A_ADCIFE_AD4
#define EXT3_ADC_1_CHANNEL        5
#define EXT3_ADC_1_MUX            MUX_PB04A_ADCIFE_AD5
//@}

//! \name Extension header #3 PWM definitions
//@{
#define EXT3_PWM_MODULE           TC0
#define EXT3_PWM_CHANNEL          0
#define EXT3_PWM_0_MUX            MUX_PA08B_TC0_A0
#define EXT3_PWM_1_MUX            MUX_PA09B_TC0_B0
//@}

//! \name Extension header #3 IRQ/External interrupt definitions
//@{
#define EXT3_IRQ_MODULE           EIC
#define EXT3_IRQ_MUX              MUX_PA06C_EIC_EXTINT1
#define EXT3_IRQ_MASK             EIC_IMR_INT1
//@}

//! \name Extension header #3 TWI definitions
//@{
#define EXT3_TWI_MODULE           TWIM3
#define EXT3_TWI_SDA_MUX          MUX_PB14C_TWIMS3_TWD
#define EXT3_TWI_SCL_MUX          MUX_PB15C_TWIMS3_TWCK
//@}

//! \name Extension header #3 UART definitions
//@{
#define EXT3_UART_MODULE          USART1
#define EXT3_UART_RX_MUX          MUX_PC26A_USART1_RXD
#define EXT3_UART_TX_MUX          MUX_PC27A_USART1_TXD
//@}

//! \name Extension header #3 SPI definitions
//@{
#define EXT3_SPI_MODULE           USART2
#define EXT3_SPI_SS_MOSI          MUX_PA20A_USART2_TXD
#define EXT3_SPI_SS_MISO          MUX_PA19A_USART2_RXD
#define EXT3_SPI_SS_SCK           MUX_PA18A_USART2_CLK
//@}

//! \name Extension header #4 pin definitions
//@{
#define EXT4_PIN_3                PIN_PB05
#define EXT4_PIN_4                PIN_PC10
#define EXT4_PIN_5                PIN_PC17
#define EXT4_PIN_6                PIN_PC18
#define EXT4_PIN_7                PIN_PA12
#define EXT4_PIN_8                PIN_PA13
#define EXT4_PIN_9                PIN_PA16
#define EXT4_PIN_10               PIN_PA15
#define EXT4_PIN_11               PIN_PB14
#define EXT4_PIN_12               PIN_PB15
#define EXT4_PIN_13               PIN_PB00
#define EXT4_PIN_14               PIN_PB01
#define EXT4_PIN_15               PIN_PA11
#define EXT4_PIN_16               PIN_PA20
#define EXT4_PIN_17               PIN_PA19
#define EXT4_PIN_18               PIN_PA18
//@}

//! \name Extension header #4 pin definitions by function
//@{
#define EXT4_PIN_ADC_0            EXT4_PIN_3
#define EXT4_PIN_ADC_1            EXT4_PIN_4
#define EXT4_PIN_GPIO_0           EXT4_PIN_5
#define EXT4_PIN_GPIO_1           EXT4_PIN_6
#define EXT4_PIN_PWM_0            EXT4_PIN_7
#define EXT4_PIN_PWM_1            EXT4_PIN_8
#define EXT4_PIN_IRQ              EXT4_PIN_9
#define EXT4_PIN_TWI_SDA          EXT4_PIN_11
#define EXT4_PIN_TWI_SCL          EXT4_PIN_12
#define EXT4_PIN_UART_RX          EXT4_PIN_13
#define EXT4_PIN_UART_TX          EXT4_PIN_14
#define EXT4_PIN_SPI_SS_1         EXT4_PIN_10
#define EXT4_PIN_SPI_SS_0         EXT4_PIN_15
#define EXT4_PIN_SPI_MOSI         EXT4_PIN_16
#define EXT4_PIN_SPI_MISO         EXT4_PIN_17
#define EXT4_PIN_SPI_SCK          EXT4_PIN_18
//@}

//! \name Extension header #4 ADC definitions
//@{
#define EXT4_ADC_MODULE           ADCIFE
#define EXT4_ADC_0_CHANNEL        6
#define EXT4_ADC_0_MUX            MUX_PB05A_ADCIFE_AD6
#define EXT4_ADC_1_CHANNEL        10
#define EXT4_ADC_1_MUX            MUX_PC10A_ADCIFE_AD10
//@}

//! \name Extension header #4 PWM definitions
//@{
#define EXT4_PWM_MODULE           TC0
#define EXT4_PWM_CHANNEL          2
#define EXT4_PWM_0_MUX            MUX_PA12B_TC0_A2
#define EXT4_PWM_1_MUX            MUX_PA13B_TC0_B2
//@}

//! \name Extension header #4 IRQ/External interrupt definitions
//@{
#define EXT4_IRQ_MODULE           EIC
#define EXT4_IRQ_MUX              MUX_PA16C_EIC_EXTINT1
#define EXT4_IRQ_MASK             EIC_IMR_INT1
//@}

//! \name Extension header #4 TWI definitions
//@{
#define EXT4_TWI_MODULE           TWIM3
#define EXT4_TWI_SDA_MUX          MUX_PB14C_TWIMS3_TWD
#define EXT4_TWI_SCL_MUX          MUX_PB15C_TWIMS3_TWCK
//@}

//! \name Extension header #4 UART definitions
//@{
#define EXT4_UART_MODULE          USART0
#define EXT4_UART_RX_MUX          MUX_PB00B_USART0_RXD
#define EXT4_UART_TX_MUX          MUX_PB01B_USART0_TXD
//@}

//! \name Extension header #4 SPI definitions
//@{
#define EXT4_SPI_MODULE           USART2
#define EXT4_SPI_SS_MOSI          MUX_PA20A_USART2_TXD
#define EXT4_SPI_SS_MISO          MUX_PA19A_USART2_RXD
#define EXT4_SPI_SS_SCK           MUX_PA18A_USART2_CLK
//@}

//! \name Embedded debugger GPIO interface definitions
//@{
#define EDBG_GPIO0_PIN            PIN_PB05
#define EDBG_GPIO1_PIN            PIN_PB10
#define EDBG_GPIO2_PIN            PIN_PB06
#define EDBG_GPIO3_PIN            PIN_PB07
//@}

//! \name Embedded debugger USART interface definitions
//@{
#define EDBG_UART_MODULE          USART3
#define EDBG_UART_RX_PIN          PIN_PC28A_USART3_RXD
#define EDBG_UART_RX_MUX          MUX_PC28A_USART3_RXD
#define EDBG_UART_TX_PIN          PIN_PC29A_USART3_TXD
#define EDBG_UART_TX_MUX          MUX_PC29A_USART3_TXD
#define EDBG_UART_CLK_PIN         PIN_PC31A_USART3_CLK
#define EDBG_UART_CLK_MUX         MUX_PC31A_USART3_CLK
//@}

//! \name Embedded debugger TWI interface definitions
//@{
#define EDBG_TWI_MODULE           TWIM0
#define EDBG_TWI_SDA_PIN          PIN_PA23B_TWIMS0_TWD
#define EDBG_TWI_SDA_MUX          MUX_PA23B_TWIMS0_TWD
#define EDBG_TWI_SCL_PIN          PIN_PA24B_TWIMS0_TWCK
#define EDBG_TWI_SCL_MUX          MUX_PA24B_TWIMS0_TWCK
//@}

//! \name OLED
//@{
/** OLED command/data select pin */
#define UG_2832HSWEG04_DATA_CMD_GPIO   (EXT2_PIN_5)
/** OLED reset pin */
#define UG_2832HSWEG04_RESET_GPIO      (EXT2_PIN_10)
/** OLED SPI configuration */
#define UG_2832HSWEG04_SS               2
#define UG_2832HSWEG04_BAUDRATE         5000000
//! \name OLED dimensions
//@{
#define LCD_WIDTH_PIXELS                (128)
#define LCD_HEIGHT_PIXELS               (32)
//@}
//@}

/*! \name Connections of the AT86RFX transceiver
 */
//! @{
#define AT86RFX_SPI                  SPI
#define AT86RFX_RST_PIN              EXT1_PIN_7
#define AT86RFX_IRQ_PIN              EXT1_PIN_9
#define AT86RFX_SLP_PIN              EXT1_PIN_10
#define AT86RFX_SPI_CS               0
#define AT86RFX_SPI_CS_PIN           EXT1_PIN_15
#define AT86RFX_SPI_CS_FLAGS         MUX_PC03A_SPI_NPCS0
#define AT86RFX_SPI_MOSI             EXT1_PIN_16
#define AT86RFX_SPI_MISO             EXT1_PIN_17
#define AT86RFX_SPI_SCK              EXT1_PIN_18
#define AT86RFX_SPI_MOSI_FLAGS       MUX_PA22A_SPI_MOSI
#define AT86RFX_SPI_MISO_FLAGS       MUX_PA21A_SPI_MISO
#define AT86RFX_SPI_SCK_FLAGS        MUX_PC30B_SPI_SCK
#define AT86RFX_CSD     		     EXT1_PIN_5
#define AT86RFX_CPS 	             EXT1_PIN_8


void at86rfx_isr(void);

#define AT86RFX_INTC_INIT()         ioport_set_pin_dir(AT86RFX_IRQ_PIN, IOPORT_DIR_INPUT);\
									ioport_set_pin_sense_mode(AT86RFX_IRQ_PIN, IOPORT_SENSE_RISING);\
									gpio_set_pin_callback(AT86RFX_IRQ_PIN, at86rfx_isr, 1);					
									

#define AT86RFX_ISR()               void at86rfx_isr(void)

/** Enables the transceiver main interrupt. */
#define ENABLE_TRX_IRQ()            gpio_enable_pin_interrupt(AT86RFX_IRQ_PIN)

/** Disables the transceiver main interrupt. */
#define DISABLE_TRX_IRQ()           gpio_disable_pin_interrupt(AT86RFX_IRQ_PIN)

/** Clears the transceiver main interrupt. */
#define CLEAR_TRX_IRQ()             gpio_clear_pin_interrupt_flag(AT86RFX_IRQ_PIN) 
/*
 * This macro saves the trx interrupt status and disables the trx interrupt.
 */
#define ENTER_TRX_REGION()          gpio_disable_pin_interrupt(AT86RFX_IRQ_PIN);

/*
 *  This macro restores the transceiver interrupt status
 */
#define LEAVE_TRX_REGION()         gpio_enable_pin_interrupt(AT86RFX_IRQ_PIN)

/** Defines required by SD MMC Stack */
#define SD_MMC_SPI_MEM_CNT          1
#define SD_MMC_0_CD_GPIO            (PIN_PB13)
#define SD_MMC_0_CD_DIR             (IOPORT_DIR_INPUT)
#define SD_MMC_0_CD_MODE            (IOPORT_MODE_PULLUP)
#define SD_MMC_0_CD_DETECT_VALUE    0
#define SD_MMC_SPI                  SPI
#define SD_MMC_SPI_0_CS             0

#define SPI_NPCS0_GPIO              (PIN_PC03A_SPI_NPCS0)
#define SPI_NPCS0_FLAGS             (MUX_PC03A_SPI_NPCS0)
#define SPI_MISO_GPIO               (PIN_PA21A_SPI_MISO)
#define SPI_MISO_FLAGS              (MUX_PA21A_SPI_MISO)
#define SPI_MOSI_GPIO               (PIN_PA22A_SPI_MOSI)
#define SPI_MOSI_FLAGS              (MUX_PA22A_SPI_MOSI)
#define SPI_SPCK_GPIO               (PIN_PC30B_SPI_SCK)
#define SPI_SPCK_FLAGS              (MUX_PC30B_SPI_SCK)

//! @}

/** @} */

/** @} */

#endif /* SAM4L_XPLAINED_PRO_INCLUDED */
