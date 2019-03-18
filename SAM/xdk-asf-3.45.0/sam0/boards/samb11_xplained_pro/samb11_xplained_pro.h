/**
 * \file
 *
 * \brief SAM B11 Xplained Pro board definition
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef SAMB11_XPLAINED_PRO_H_INCLUDED
#define SAMB11_XPLAINED_PRO_H_INCLUDED

#include <conf_board.h>
#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup group_common_boards
 * \defgroup samb11_xplained_pro_group SAM B11 Xplained Pro board
 *
 * @{
 */

void system_board_init(void);

/**
 * \defgroup samb11_xplained_pro_features_group Features
 *
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

/** Name string macro */
#define BOARD_NAME                "SAMB11_XPLAINED_PRO"

/** \name Resonator definitions
 *  @{ */
#define BOARD_FREQ_SLCK_XTAL      (32768U)
#define BOARD_FREQ_SLCK_BYPASS    (32768U)
#define BOARD_FREQ_MAINCK_XTAL    0 /* Not Mounted */
#define BOARD_FREQ_MAINCK_BYPASS  0 /* Not Mounted */
#define BOARD_MCK                 CHIP_FREQ_CPU_MAX
#define BOARD_OSC_STARTUP_US      15625
/** @} */

/** \name LED0 definitions
 *  @{ */
#define LED0_PIN                  PIN_LP_GPIO_22
#define LED0_ACTIVE               false
#define LED0_INACTIVE             !LED0_ACTIVE
/** @} */

/** \name SW0 definitions
 *  @{ */
#define SW0_PIN                   PIN_LP_GPIO_23
#define SW0_ACTIVE                false
#define SW0_INACTIVE              !SW0_ACTIVE           
/** @} */

/**
 * \name LED #0 definitions
 *
 * Wrapper macros for LED0, to ensure common naming across all Xplained Pro
 * boards.
 *
 *  @{ */
#define LED_0_NAME                "LED0 (yellow)"
#define LED_0_PIN                 LED0_PIN
#define LED_0_ACTIVE              LED0_ACTIVE
#define LED_0_INACTIVE            LED0_INACTIVE
#define LED0_GPIO                 LED0_PIN
#define LED0                      LED0_PIN
/** @} */

/** Number of on-board LEDs */
#define LED_COUNT                 1

/**
 * \name Button #0 definitions
 *
 * Wrapper macros for SW0, to ensure common naming across all Xplained Pro
 * boards.
 *
 *  @{ */
#define BUTTON_0_NAME             "SW0"
#define BUTTON_0_PIN              SW0_PIN
#define BUTTON_0_ACTIVE           SW0_ACTIVE
#define BUTTON_0_INACTIVE         SW0_INACTIVE
/** @} */

/** Number of on-board buttons */
#define BUTTON_COUNT              1

/** \name Extension header #1 pin definitions
 *  @{
 */
#define EXT1_PIN_3               PIN_GPIO_MS1
#define EXT1_PIN_4               PIN_GPIO_MS2
#define EXT1_PIN_5               PIN_LP_GPIO_4
#define EXT1_PIN_6               PIN_AO_GPIO_2
#define EXT1_PIN_9               PIN_AO_GPIO_0
#define EXT1_PIN_10              PIN_LP_GPIO_5
#define EXT1_PIN_11              PIN_LP_GPIO_8
#define EXT1_PIN_12              PIN_LP_GPIO_9
#define EXT1_PIN_13              PIN_LP_GPIO_2
#define EXT1_PIN_14              PIN_LP_GPIO_3
#define EXT1_PIN_15              PIN_LP_GPIO_12
#define EXT1_PIN_16              PIN_LP_GPIO_11
#define EXT1_PIN_17              PIN_LP_GPIO_13
#define EXT1_PIN_18              PIN_LP_GPIO_10
/** @} */

/** \name Extension header #1 pin definitions by function
 *  @{
 */
#define EXT1_PIN_ADC_0           EXT1_PIN_3
#define EXT1_PIN_ADC_1           EXT1_PIN_4
#define EXT1_PIN_GPIO_1          EXT1_PIN_5
#define EXT1_PIN_GPIO_2          EXT1_PIN_6
#define EXT1_PIN_IRQ             EXT1_PIN_9
#define EXT1_PIN_I2C_SDA         EXT1_PIN_11
#define EXT1_PIN_I2C_SCL         EXT1_PIN_12
#define EXT1_PIN_UART_RX         EXT1_PIN_13
#define EXT1_PIN_UART_TX         EXT1_PIN_14
#define EXT1_PIN_SPI_SS_1        EXT1_PIN_10
#define EXT1_PIN_SPI_SS_0        EXT1_PIN_15
#define EXT1_PIN_SPI_MOSI        EXT1_PIN_16
#define EXT1_PIN_SPI_MISO        EXT1_PIN_17
#define EXT1_PIN_SPI_SCK         EXT1_PIN_18
/** @} */

/** \name Extension header #1 ADC definitions
 *  @{
 */
#define EXT1_ADC_0_PIN           PIN_GPIO_MS1
#define EXT1_ADC_1_PIN           PIN_GPIO_MS2
/** @} */

/** \name Extension header #1 IRQ/External interrupt definitions
 *  @{
 */
#define EXT1_IRQ_PIN             PIN_AO_GPIO_0
/** @} */

/** \name Extension header #1 I2C definitions
 *  @{
 */
#define EXT1_I2C_MODULE          I2C0
#define EXT1_I2C_PIN_PAD0        PIN_LP_GPIO_8
#define EXT1_I2C_PIN_PAD1        PIN_LP_GPIO_9
#define EXT1_I2C_MUX_PAD0        MUX_LP_GPIO_8_I2C0_SDA
#define EXT1_I2C_MUX_PAD1        MUX_LP_GPIO_9_I2C0_SCL
/** @} */

/** \name Extension header #1 UART definitions
 *  @{
 */
#define EXT1_UART_MODULE         UART0
#define EXT1_UART_PIN_PAD0       PIN_LP_GPIO_2
#define EXT1_UART_PIN_PAD1       PIN_LP_GPIO_3
#define EXT1_UART_MUX_PAD0       MUX_LP_GPIO_2_UART0_RXD
#define EXT1_UART_MUX_PAD1       MUX_LP_GPIO_3_UART0_TXD
/** @} */

/** \name Extension header #1 SPI definitions
 *  @{
 */
#define EXT1_SPI_MODULE          SPI0
#define EXT1_SPI_PIN_PAD0        PIN_LP_GPIO_12
#define EXT1_SPI_PIN_PAD1        PIN_LP_GPIO_11
#define EXT1_SPI_PIN_PAD2        PIN_LP_GPIO_13
#define EXT1_SPI_PIN_PAD3        PIN_LP_GPIO_10
#define EXT1_SPI_MUX_PAD0        MUX_LP_GPIO_12_SPI0_SSN
#define EXT1_SPI_MUX_PAD1        MUX_LP_GPIO_11_SPI0_MOSI
#define EXT1_SPI_MUX_PAD2        MUX_LP_GPIO_13_SPI0_MISO
#define EXT1_SPI_MUX_PAD3        MUX_LP_GPIO_10_SPI0_SCK
/** @} */

/** \name Extension header #3 pin definitions
 *  @{
 */
#define EXT3_PIN_3               PIN_GPIO_MS3
#define EXT3_PIN_4               PIN_GPIO_MS4
#define EXT3_PIN_5               PIN_LP_GPIO_20
#define EXT3_PIN_9               PIN_AO_GPIO_1
#define EXT3_PIN_11              PIN_LP_GPIO_14
#define EXT3_PIN_12              PIN_LP_GPIO_15
#define EXT3_PIN_13              PIN_LP_GPIO_6
#define EXT3_PIN_14              PIN_LP_GPIO_7
#define EXT3_PIN_15              PIN_LP_GPIO_16
#define EXT3_PIN_16              PIN_LP_GPIO_19
#define EXT3_PIN_17              PIN_LP_GPIO_18
#define EXT3_PIN_18              PIN_LP_GPIO_17
/** @} */

/** \name Extension header #3 pin definitions by function
 *  @{
 */
#define EXT3_PIN_ADC_0           EXT3_PIN_3
#define EXT3_PIN_ADC_1           EXT3_PIN_4
#define EXT3_PIN_GPIO_1          EXT3_PIN_5
#define EXT3_PIN_IRQ             EXT3_PIN_9
#define EXT3_PIN_I2C_SDA         EXT3_PIN_11
#define EXT3_PIN_I2C_SCL         EXT3_PIN_12
#define EXT3_PIN_UART_RX         EXT3_PIN_13
#define EXT3_PIN_UART_TX         EXT3_PIN_14
#define EXT3_PIN_SPI_SS_0        EXT3_PIN_15
#define EXT3_PIN_SPI_MOSI        EXT3_PIN_16
#define EXT3_PIN_SPI_MISO        EXT3_PIN_17
#define EXT3_PIN_SPI_SCK         EXT3_PIN_18
/** @} */

/** \name Extension header #3 ADC definitions
 *  @{
 */
#define EXT3_ADC_0_PIN           PIN_GPIO_MS3
#define EXT3_ADC_1_PIN           PIN_GPIO_MS4
/** @} */

/** \name Extension header #3 IRQ/External interrupt definitions
 *  @{
 */
#define EXT3_IRQ_PIN             PIN_AO_GPIO_1
/** @} */

/** \name Extension header #3 I2C definitions
 *  @{
 */
#define EXT3_I2C_MODULE          I2C1
#define EXT3_I2C_PIN_PAD0        PIN_LP_GPIO_14
#define EXT3_I2C_PIN_PAD1        PIN_LP_GPIO_15
#define EXT3_I2C_MUX_PAD0        MUX_LP_GPIO_14_I2C1_SDA
#define EXT3_I2C_MUX_PAD1        MUX_LP_GPIO_15_I2C1_SCL
/** @} */

/** \name Extension header #3 UART definitions
 *  @{
 */
#define EXT3_UART_MODULE         UART1
#define EXT3_UART_PIN_PAD0       PIN_LP_GPIO_6
#define EXT3_UART_PIN_PAD1       PIN_LP_GPIO_7
#define EXT3_UART_MUX_PAD0       MUX_LP_GPIO_6_UART1_RXD
#define EXT3_UART_MUX_PAD1       MUX_LP_GPIO_7_UART1_TXD
/** @} */

/** \name Extension header #3 SPI definitions
 *  @{
 */
#define EXT3_SPI_MODULE          SPI1
#define EXT3_SPI_PIN_PAD0        PIN_LP_GPIO_16
#define EXT3_SPI_PIN_PAD1        PIN_LP_GPIO_19
#define EXT3_SPI_PIN_PAD2        PIN_LP_GPIO_18
#define EXT3_SPI_PIN_PAD3        PIN_LP_GPIO_17
#define EXT3_SPI_MUX_PAD0        MUX_LP_GPIO_16_SPI1_SSN
#define EXT3_SPI_MUX_PAD1        MUX_LP_GPIO_19_SPI1_MOSI
#define EXT3_SPI_MUX_PAD2        MUX_LP_GPIO_18_SPI1_MISO
#define EXT3_SPI_MUX_PAD3        MUX_LP_GPIO_17_SPI1_SCK
/** @} */

/** \name Embedded debugger GPIO interface definitions
 * @{
 */
#define EDBG_GPIO0_PIN           PIN_LP_GPIO_22
#define EDBG_GPIO1_PIN           PIN_LP_GPIO_23
#define EDBG_GPIO2_PIN           PIN_LP_GPIO_19
#define EDBG_GPIO3_PIN           PIN_LP_GPIO_20
/** @} */

/** \name Embedded debugger USART interface definitions
 * @{
 */
#define EDBG_UART_MODULE          -1 /* Not available on this board */
#define EDBG_UART_RX_PIN          -1 /* Not available on this board */
#define EDBG_UART_RX_MUX          -1 /* Not available on this board */

#define EDBG_UART_RX_PAD          -1 /* Not available on this board */
#define EDBG_UART_TX_PIN          -1 /* Not available on this board */
#define EDBG_UART_TX_MUX          -1 /* Not available on this board */
#define EDBG_UART_TX_PAD          -1 /* Not available on this board */
/** @} */

/** \name Embedded debugger I2C interface definitions
 * @{
 */
#define EDBG_I2C_MODULE        	 I2C0
#define EDBG_I2C_PIN_PAD0        PIN_LP_GPIO_8
#define EDBG_I2C_PIN_PAD1        PIN_LP_GPIO_9
#define EDBG_I2C_MUX_PAD0        MUX_LP_GPIO_8_I2C0_SDA
#define EDBG_I2C_MUX_PAD1        MUX_LP_GPIO_9_I2C0_SCL
/** @} */

/** \name Embedded debugger SPI interface definitions
 * @{
 */
#define EDBG_SPI_MODULE        	 SPI0
#define EDBG_SPI_PIN_PAD0        PIN_LP_GPIO_4
#define EDBG_SPI_PIN_PAD1        PIN_LP_GPIO_13
#define EDBG_SPI_PIN_PAD2        PIN_LP_GPIO_11
#define EDBG_SPI_PIN_PAD3        PIN_LP_GPIO_10
#define EDBG_SPI_MUX_PAD0        MUX_LP_GPIO_4_SPI0_SSN
#define EDBG_SPI_MUX_PAD1        MUX_LP_GPIO_13_SPI0_MISO
#define EDBG_SPI_MUX_PAD2        MUX_LP_GPIO_11_SPI0_MOSI
#define EDBG_SPI_MUX_PAD3        MUX_LP_GPIO_10_SPI0_SCK
/** @} */

/** \name Embedded debugger CDC Gateway USART interface definitions
 * @{
 */
#define EDBG_CDC_MODULE        	 UART0
#define EDBG_CDC_PIN_PAD0        PIN_LP_GPIO_2
#define EDBG_CDC_PIN_PAD1        PIN_LP_GPIO_3
#define EDBG_CDC_PIN_PAD2        PIN_LP_GPIO_4
#define EDBG_CDC_PIN_PAD3        PIN_LP_GPIO_5
#define EDBG_CDC_MUX_PAD0        MUX_LP_GPIO_2_UART0_RXD
#define EDBG_CDC_MUX_PAD1        MUX_LP_GPIO_3_UART0_TXD
#define EDBG_CDC_MUX_PAD2        MUX_LP_GPIO_4_UART0_CTS
#define EDBG_CDC_MUX_PAD3        MUX_LP_GPIO_5_UART0_RTS
/** @} */

/** @} */

/**
 * \brief Turns off the specified LEDs.
 *
 * \param led_gpio LED to turn off (LEDx_GPIO).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_Off(led_gpio)     gpio_pin_set_output_level(led_gpio,true)

/**
 * \brief Turns on the specified LEDs.
 *
 * \param led_gpio LED to turn on (LEDx_GPIO).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_On(led_gpio)      gpio_pin_set_output_level(led_gpio,false)

/**
 * \brief Toggles the specified LEDs.
 *
 * \param led_gpio LED to toggle (LEDx_GPIO).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_Toggle(led_gpio)  gpio_pin_toggle_output_level(led_gpio)

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* SAMB11_XPLAINED_PRO_H_INCLUDED */
