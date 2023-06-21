/**
 * \file
 *
 * \brief SAM L22 Xplained Pro board definition
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

#ifndef SAML22_XPLAINED_PRO_H_INCLUDED
#define SAML22_XPLAINED_PRO_H_INCLUDED

#include <conf_board.h>
#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup group_common_boards
 * \defgroup saml22_xplained_pro_group SAM L22 Xplained Pro board
 *
 * @{
 */

void system_board_init(void);

/**
 * \defgroup saml22_xplained_pro_features_group Features
 *
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

/** Name string macro */
#define BOARD_NAME                "SAML22_XPLAINED_PRO"

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
#define LED0_PIN                  PIN_PC27
#define LED0_ACTIVE               false
#define LED0_INACTIVE             !LED0_ACTIVE
/** @} */

/** \name SW0 definitions
 *  @{ */
#define SW0_PIN                   PIN_PC01
#define SW0_ACTIVE                false
#define SW0_INACTIVE              !SW0_ACTIVE
#define SW0_EIC_PIN               PIN_PC01A_EIC_EXTINT9
#define SW0_EIC_MUX               MUX_PC01A_EIC_EXTINT9
#define SW0_EIC_PINMUX            PINMUX_PC01A_EIC_EXTINT9
#define SW0_EIC_LINE              9
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

#define LED_0_PWM4CTRL_MODULE     TCC0
#define LED_0_PWM4CTRL_CHANNEL    3
#define LED_0_PWM4CTRL_OUTPUT     3
#define LED_0_PWM4CTRL_PIN        PIN_PC27F_TCC0_WO3
#define LED_0_PWM4CTRL_MUX        MUX_PC27F_TCC0_WO3
#define LED_0_PWM4CTRL_PINMUX     PINMUX_PC27F_TCC0_WO3
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
#define BUTTON_0_EIC_PIN          SW0_EIC_PIN
#define BUTTON_0_EIC_MUX          SW0_EIC_MUX
#define BUTTON_0_EIC_PINMUX       SW0_EIC_PINMUX
#define BUTTON_0_EIC_LINE         SW0_EIC_LINE
/** @} */

/** Number of on-board buttons */
#define BUTTON_COUNT 1

/** \name Extension header #1 pin definitions
 *  @{
 */
#define EXT1_PIN_3                PIN_PA02
#define EXT1_PIN_4                PIN_PA03
#define EXT1_PIN_5                PIN_PA20
#define EXT1_PIN_6                PIN_PA21
#define EXT1_PIN_7                PIN_PB08
#define EXT1_PIN_8                PIN_PB09
#define EXT1_PIN_9                PIN_PC02
#define EXT1_PIN_10               PIN_PC03
#define EXT1_PIN_11               PIN_PB30
#define EXT1_PIN_12               PIN_PB31
#define EXT1_PIN_13               PIN_PA23
#define EXT1_PIN_14               PIN_PA22
#define EXT1_PIN_15               PIN_PB21
#define EXT1_PIN_16               PIN_PB00
#define EXT1_PIN_17               PIN_PB02
#define EXT1_PIN_18               PIN_PB01
/** @} */

/** \name Extension header #1 pin definitions by function
 *  @{
 */
#define EXT1_PIN_ADC_0            EXT1_PIN_3
#define EXT1_PIN_ADC_1            EXT1_PIN_4
#define EXT1_PIN_GPIO_0           EXT1_PIN_5
#define EXT1_PIN_GPIO_1           EXT1_PIN_6
#define EXT1_PIN_PWM_0            EXT1_PIN_7
#define EXT1_PIN_PWM_1            EXT1_PIN_8
#define EXT1_PIN_IRQ              EXT1_PIN_9
#define EXT1_PIN_I2C_SDA          EXT1_PIN_11
#define EXT1_PIN_I2C_SCL          EXT1_PIN_12
#define EXT1_PIN_UART_RX          EXT1_PIN_13
#define EXT1_PIN_UART_TX          EXT1_PIN_14
#define EXT1_PIN_SPI_SS_1         EXT1_PIN_10
#define EXT1_PIN_SPI_SS_0         EXT1_PIN_15
#define EXT1_PIN_SPI_MOSI         EXT1_PIN_16
#define EXT1_PIN_SPI_MISO         EXT1_PIN_17
#define EXT1_PIN_SPI_SCK          EXT1_PIN_18
/** @} */

/** \name Extension header #1 PWM definitions
 *  @{
 */
#define EXT1_PWM_MODULE           TC0
#define EXT1_PWM_0_CHANNEL        0
#define EXT1_PWM_0_PIN            PIN_PB08E_TC0_WO0
#define EXT1_PWM_0_MUX            MUX_PB08E_TC0_WO0
#define EXT1_PWM_0_PINMUX         PINMUX_PB08E_TC0_WO0
#define EXT1_PWM_1_CHANNEL        1
#define EXT1_PWM_1_PIN            PIN_PB09E_TC0_WO1
#define EXT1_PWM_1_MUX            MUX_PB09E_TC0_WO1
#define EXT1_PWM_1_PINMUX         PINMUX_PB09E_TC0_WO1
/** @} */

/** \name Extension header #1 IRQ/External interrupt definitions
 *  @{
 */
#define EXT1_IRQ_MODULE           EIC
#define EXT1_IRQ_INPUT            10
#define EXT1_IRQ_PIN              PIN_PC02A_EIC_EXTINT10
#define EXT1_IRQ_MUX              MUX_PC02A_EIC_EXTINT10
#define EXT1_IRQ_PINMUX           PINMUX_PC02A_EIC_EXTINT10
/** @} */

/** \name Extension header #1 I2C definitions
 *  @{
 */
#define EXT1_I2C_MODULE              SERCOM5
#define EXT1_I2C_SERCOM_PINMUX_PAD0  PINMUX_PB30D_SERCOM5_PAD0
#define EXT1_I2C_SERCOM_PINMUX_PAD1  PINMUX_PB31D_SERCOM5_PAD1
#define EXT1_I2C_SERCOM_DMAC_ID_TX   SERCOM5_DMAC_ID_TX
#define EXT1_I2C_SERCOM_DMAC_ID_RX   SERCOM5_DMAC_ID_RX
/** @} */

/** \name Extension header #1 UART definitions
 *  @{
 */
#define EXT1_UART_MODULE              SERCOM2
#define EXT1_UART_SERCOM_MUX_SETTING  USART_RX_1_TX_0_XCK_1
#define EXT1_UART_SERCOM_PINMUX_PAD0  PINMUX_PA22D_SERCOM2_PAD0
#define EXT1_UART_SERCOM_PINMUX_PAD1  PINMUX_PA23D_SERCOM2_PAD1
#define EXT1_UART_SERCOM_PINMUX_PAD2  PINMUX_UNUSED
#define EXT1_UART_SERCOM_PINMUX_PAD3  PINMUX_UNUSED
#define EXT1_UART_SERCOM_DMAC_ID_TX   SERCOM2_DMAC_ID_TX
#define EXT1_UART_SERCOM_DMAC_ID_RX   SERCOM2_DMAC_ID_RX
/** @} */

/** \name Extension header #1 USART RS485 definitions
 *  @{
 */
#define EXT1_RS485_MODULE              SERCOM2
#define EXT1_RS485_SERCOM_MUX_SETTING  USART_RX_1_TX_0_XCK_1_TE_2
#define EXT1_RS485_SERCOM_PINMUX_PAD0  PINMUX_PA22D_SERCOM2_PAD0
#define EXT1_RS485_SERCOM_PINMUX_PAD1  PINMUX_PA23D_SERCOM2_PAD1
#define EXT1_RS485_SERCOM_PINMUX_PAD2  PINMUX_PA20D_SERCOM2_PAD2
#define EXT1_RS485_SERCOM_PINMUX_PAD3  PINMUX_UNUSED
#define EXT1_RS485_SERCOM_DMAC_ID_TX   SERCOM2_DMAC_ID_TX
#define EXT1_RS485_SERCOM_DMAC_ID_RX   SERCOM2_DMAC_ID_RX
#define EXT1_RS485_CTS_PIN             EXT1_PIN_6

/** @} */
/** \name Extension header #1 SPI definitions
 *  @{
 */
#define EXT1_SPI_MODULE              SERCOM3
#define EXT1_SPI_SERCOM_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_E
#define EXT1_SPI_SERCOM_PINMUX_PAD0  PINMUX_PB02C_SERCOM3_PAD0
#define EXT1_SPI_SERCOM_PINMUX_PAD1  PINMUX_PB21C_SERCOM3_PAD1
#define EXT1_SPI_SERCOM_PINMUX_PAD2  PINMUX_PB00C_SERCOM3_PAD2
#define EXT1_SPI_SERCOM_PINMUX_PAD3  PINMUX_PB01C_SERCOM3_PAD3
#define EXT1_SPI_SERCOM_DMAC_ID_TX   SERCOM3_DMAC_ID_TX
#define EXT1_SPI_SERCOM_DMAC_ID_RX   SERCOM3_DMAC_ID_RX
/** @} */

/** \name Extension header #2 pin definitions
 *  @{
 */
#define EXT2_PIN_3                PIN_PA04
#define EXT2_PIN_4                PIN_PA05
#define EXT2_PIN_5                PIN_PB04
#define EXT2_PIN_6                PIN_PB05
#define EXT2_PIN_7                PIN_PC28
#define EXT2_PIN_8                PIN_PA27
#define EXT2_PIN_9                PIN_PB06
#define EXT2_PIN_10               PIN_PB07
#define EXT2_PIN_11               PIN_PB30
#define EXT2_PIN_12               PIN_PB31
#define EXT2_PIN_13               PIN_PA13
#define EXT2_PIN_14               PIN_PA12
#define EXT2_PIN_15               PIN_PA17
#define EXT2_PIN_16               PIN_PA18
#define EXT2_PIN_17               PIN_PA16
#define EXT2_PIN_18               PIN_PA19
/** @} */

/** \name Extension header #2 pin definitions by function
 *  @{
 */
#define EXT2_PIN_ADC_0            EXT2_PIN_3
#define EXT2_PIN_ADC_1            EXT2_PIN_4
#define EXT2_PIN_GPIO_0           EXT2_PIN_5
#define EXT2_PIN_GPIO_1           EXT2_PIN_6
#define EXT2_PIN_PWM_0            EXT2_PIN_7
#define EXT2_PIN_PWM_1            EXT2_PIN_8
#define EXT2_PIN_IRQ              EXT2_PIN_9
#define EXT2_PIN_I2C_SDA          EXT2_PIN_11
#define EXT2_PIN_I2C_SCL          EXT2_PIN_12
#define EXT2_PIN_UART_RX          EXT2_PIN_13
#define EXT2_PIN_UART_TX          EXT2_PIN_14
#define EXT2_PIN_SPI_SS_1         EXT2_PIN_10
#define EXT2_PIN_SPI_SS_0         EXT2_PIN_15
#define EXT2_PIN_SPI_MOSI         EXT2_PIN_16
#define EXT2_PIN_SPI_MISO         EXT2_PIN_17
#define EXT2_PIN_SPI_SCK          EXT2_PIN_18
/** @} */

/** \name Extension header #2 PWM definitions
 *  @{
 */
#define EXT2_PWM_MODULE           TCC0
#define EXT2_PWM_0_CHANNEL        4
#define EXT2_PWM_0_PIN            PIN_PC28F_TCC0_WO4
#define EXT2_PWM_0_MUX            MUX_PC28F_TCC0_WO4
#define EXT2_PWM_0_PINMUX         PINMUX_PC28F_TCC0_WO4
#define EXT2_PWM_1_CHANNEL        5
#define EXT2_PWM_1_PIN            PIN_PA27F_TCC0_WO5
#define EXT2_PWM_1_MUX            MUX_PA27F_TCC0_WO5
#define EXT2_PWM_1_PINMUX         PINMUX_PA27F_TCC0_WO5
/** @} */

/** \name Extension header #2 IRQ/External interrupt definitions
 *  @{
 */
#define EXT2_IRQ_MODULE           EIC
#define EXT2_IRQ_INPUT            6
#define EXT2_IRQ_PIN              PIN_PB06A_EIC_EXTINT6
#define EXT2_IRQ_MUX              MUX_PB06A_EIC_EXTINT6
#define EXT2_IRQ_PINMUX           PINMUX_PB06A_EIC_EXTINT6
/** @} */

 /** \name Extension header #2 I2C definitions
 *  @{
 */
#define EXT2_I2C_MODULE              SERCOM5
#define EXT2_I2C_SERCOM_PINMUX_PAD0  PINMUX_PB30D_SERCOM5_PAD0
#define EXT2_I2C_SERCOM_PINMUX_PAD1  PINMUX_PB31D_SERCOM5_PAD1
#define EXT2_I2C_SERCOM_DMAC_ID_TX   SERCOM5_DMAC_ID_TX
#define EXT2_I2C_SERCOM_DMAC_ID_RX   SERCOM5_DMAC_ID_RX
/** @} */

/** \name Extension header #2 UART definitions
 *  @{
 */
#define EXT2_UART_MODULE              SERCOM3
#define EXT2_UART_SERCOM_MUX_SETTING  USART_RX_1_TX_0_XCK_1
#define EXT2_UART_SERCOM_PINMUX_PAD0  PINMUX_PA12D_SERCOM3_PAD0
#define EXT2_UART_SERCOM_PINMUX_PAD1  PINMUX_PA13D_SERCOM3_PAD1
#define EXT2_UART_SERCOM_PINMUX_PAD2  PINMUX_UNUSED
#define EXT2_UART_SERCOM_PINMUX_PAD3  PINMUX_UNUSED
#define EXT2_UART_SERCOM_DMAC_ID_TX   SERCOM3_DMAC_ID_TX
#define EXT2_UART_SERCOM_DMAC_ID_RX   SERCOM3_DMAC_ID_RX
/** @} */

/** \name Extension header #2 SPI definitions
 *  @{
 */
#define EXT2_SPI_MODULE              SERCOM1
#define EXT2_SPI_SERCOM_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_E
#define EXT2_SPI_SERCOM_PINMUX_PAD0  PINMUX_PA16C_SERCOM1_PAD0
#define EXT2_SPI_SERCOM_PINMUX_PAD1  PINMUX_UNUSED
#define EXT2_SPI_SERCOM_PINMUX_PAD2  PINMUX_PA18C_SERCOM1_PAD2
#define EXT2_SPI_SERCOM_PINMUX_PAD3  PINMUX_PA19C_SERCOM1_PAD3
#define EXT2_SPI_SERCOM_DMAC_ID_TX   SERCOM1_DMAC_ID_TX
#define EXT2_SPI_SERCOM_DMAC_ID_RX   SERCOM1_DMAC_ID_RX
/** @} */

/** \name Extension header #3 pin definitions
 *  @{
 */
#define EXT3_PIN_3                PIN_PA06
#define EXT3_PIN_4                PIN_PA07
#define EXT3_PIN_5                PIN_PC16
#define EXT3_PIN_6                PIN_PC17
#define EXT3_PIN_7                PIN_PB16
#define EXT3_PIN_8                PIN_PB17
#define EXT3_PIN_9                PIN_PB18
#define EXT3_PIN_10               PIN_PB19
#define EXT3_PIN_11               PIN_PB30
#define EXT3_PIN_12               PIN_PB31
#define EXT3_PIN_13               PIN_PA15
#define EXT3_PIN_14               PIN_PA14
#define EXT3_PIN_15               PIN_PA09
#define EXT3_PIN_16               PIN_PA10
#define EXT3_PIN_17               PIN_PA08
#define EXT3_PIN_18               PIN_PA11
/** @} */

/** \name Extension header #3 pin definitions by function
 *  @{
 */
#define EXT3_PIN_ADC_0            EXT3_PIN_3
#define EXT3_PIN_ADC_1            EXT3_PIN_4
#define EXT3_PIN_GPIO_0           EXT3_PIN_5
#define EXT3_PIN_GPIO_1           EXT3_PIN_6
#define EXT3_PIN_PWM_0            EXT3_PIN_7
#define EXT3_PIN_PWM_1            EXT3_PIN_8
#define EXT3_PIN_IRQ              EXT3_PIN_9
#define EXT3_PIN_I2C_SDA          EXT3_PIN_11
#define EXT3_PIN_I2C_SCL          EXT3_PIN_12
#define EXT3_PIN_UART_RX          EXT3_PIN_13
#define EXT3_PIN_UART_TX          EXT3_PIN_14
#define EXT3_PIN_SPI_SS_1         EXT3_PIN_10
#define EXT3_PIN_SPI_SS_0         EXT3_PIN_15
#define EXT3_PIN_SPI_MOSI         EXT3_PIN_16
#define EXT3_PIN_SPI_MISO         EXT3_PIN_17
#define EXT3_PIN_SPI_SCK          EXT3_PIN_18
/** @} */

/** \name Extension header #1 PWM definitions
 *  @{
 */
#define EXT3_PWM_MODULE           TC2
#define EXT3_PWM_0_CHANNEL        0
#define EXT3_PWM_0_PIN            PIN_PB16E_TC2_WO0
#define EXT3_PWM_0_MUX            MUX_PB16E_TC2_WO0
#define EXT3_PWM_0_PINMUX         PINMUX_PB16E_TC2_WO0
#define EXT3_PWM_1_CHANNEL        1
#define EXT3_PWM_1_PIN            PIN_PB17E_TC2_WO1
#define EXT3_PWM_1_MUX            MUX_PB17E_TC2_WO1
#define EXT3_PWM_1_PINMUX         PINMUX_PB17E_TC2_WO1
/** @} */

/** \name Extension header #3 IRQ/External interrupt definitions
 *  @{
 */
#define EXT3_IRQ_MODULE           EIC
#define EXT3_IRQ_INPUT            2
#define EXT3_IRQ_PIN              PIN_PB18A_EIC_EXTINT2
#define EXT3_IRQ_MUX              MUX_PB18A_EIC_EXTINT2
#define EXT3_IRQ_PINMUX           PINMUX_PB18A_EIC_EXTINT2
/** @} */

/** \name Extension header #3 I2C definitions
 *  @{
 */
#define EXT3_I2C_MODULE              SERCOM5
#define EXT3_I2C_SERCOM_PINMUX_PAD0  PINMUX_PB30D_SERCOM5_PAD0
#define EXT3_I2C_SERCOM_PINMUX_PAD1  PINMUX_PB31D_SERCOM5_PAD1
#define EXT3_I2C_SERCOM_DMAC_ID_TX   SERCOM5_DMAC_ID_TX
#define EXT3_I2C_SERCOM_DMAC_ID_RX   SERCOM5_DMAC_ID_RX
/** @} */

/** \name Extension header #3 UART definitions
 *  @{
 */
#define EXT3_UART_MODULE              SERCOM4
#define EXT3_UART_SERCOM_MUX_SETTING  USART_RX_3_TX_2_XCK_3
#define EXT3_UART_SERCOM_PINMUX_PAD0  PINMUX_UNUSED
#define EXT3_UART_SERCOM_PINMUX_PAD1  PINMUX_UNUSED
#define EXT3_UART_SERCOM_PINMUX_PAD2  PINMUX_PA14C_SERCOM4_PAD2
#define EXT3_UART_SERCOM_PINMUX_PAD3  PINMUX_PA15C_SERCOM4_PAD3
#define EXT3_UART_SERCOM_DMAC_ID_TX   SERCOM4_DMAC_ID_TX
#define EXT3_UART_SERCOM_DMAC_ID_RX   SERCOM4_DMAC_ID_RX
/** @} */

/** \name Extension header #3 SPI definitions
 *  @{
 */
#define EXT3_SPI_MODULE              SERCOM0
#define EXT3_SPI_SERCOM_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_E
#define EXT3_SPI_SERCOM_PINMUX_PAD0  PINMUX_PA08C_SERCOM0_PAD0
#define EXT3_SPI_SERCOM_PINMUX_PAD1  PINMUX_PA09C_SERCOM0_PAD1
#define EXT3_SPI_SERCOM_PINMUX_PAD2  PINMUX_PA10C_SERCOM0_PAD2
#define EXT3_SPI_SERCOM_PINMUX_PAD3  PINMUX_PA11C_SERCOM0_PAD3
#define EXT3_SPI_SERCOM_DMAC_ID_TX   SERCOM0_DMAC_ID_TX
#define EXT3_SPI_SERCOM_DMAC_ID_RX   SERCOM0_DMAC_ID_RX
/** @} */

/** \name Embedded debugger I2C interface definitions
 * @{
 */
#define EDBG_I2C_MODULE              SERCOM5
#define EDBG_I2C_SERCOM_PINMUX_PAD0  PINMUX_PB30D_SERCOM5_PAD0
#define EDBG_I2C_SERCOM_PINMUX_PAD1  PINMUX_PB31D_SERCOM5_PAD1
#define EDBG_I2C_SERCOM_DMAC_ID_TX   SERCOM5_DMAC_ID_TX
#define EDBG_I2C_SERCOM_DMAC_ID_RX   SERCOM5_DMAC_ID_RX
/** @} */

/** \name Embedded debugger SPI interface definitions
 * @{
 */
#define EDBG_SPI_MODULE              SERCOM0
#define EDBG_SPI_SERCOM_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_E
#define EDBG_SPI_SERCOM_PINMUX_PAD0  PINMUX_PB24C_SERCOM0_PAD0
#define EDBG_SPI_SERCOM_PINMUX_PAD1  PINMUX_PB25C_SERCOM0_PAD1
#define EDBG_SPI_SERCOM_PINMUX_PAD2  PINMUX_PB22C_SERCOM0_PAD2
#define EDBG_SPI_SERCOM_PINMUX_PAD3  PINMUX_PB23C_SERCOM0_PAD3
#define EDBG_SPI_SERCOM_DMAC_ID_TX   SERCOM0_DMAC_ID_TX
#define EDBG_SPI_SERCOM_DMAC_ID_RX   SERCOM0_DMAC_ID_RX
/** @} */

/** \name Embedded debugger CDC Gateway USART interface definitions
 * @{
 */
#define EDBG_CDC_MODULE              SERCOM4
#define EDBG_CDC_SERCOM_MUX_SETTING  USART_RX_3_TX_2_XCK_3
#define EDBG_CDC_SERCOM_PINMUX_PAD0  PINMUX_UNUSED
#define EDBG_CDC_SERCOM_PINMUX_PAD1  PINMUX_UNUSED
#define EDBG_CDC_SERCOM_PINMUX_PAD2  PINMUX_PC24D_SERCOM4_PAD2
#define EDBG_CDC_SERCOM_PINMUX_PAD3  PINMUX_PC25D_SERCOM4_PAD3
#define EDBG_CDC_SERCOM_DMAC_ID_TX   SERCOM4_DMAC_ID_TX
#define EDBG_CDC_SERCOM_DMAC_ID_RX   SERCOM4_DMAC_ID_RX
#define EDBG_CDC_MODULE_IRQn         SERCOM4_IRQn
/** @} */
/** \name CCL interface definitions
 * @{
 */
#define CCL_LUT0_IN0_MUX  MUX_PA16I_CCL_IN0
#define CCL_LUT0_IN1_MUX  MUX_PA17I_CCL_IN1
#define CCL_LUT0_IN2_MUX  MUX_PA18I_CCL_IN2
#define CCL_LUT0_OUT_MUX  MUX_PA19I_CCL_OUT0

#define CCL_LUT0_IN0_PIN  PIN_PA16I_CCL_IN0
#define CCL_LUT0_IN1_PIN  PIN_PA17I_CCL_IN1
#define CCL_LUT0_IN2_PIN  PIN_PA18I_CCL_IN2
#define CCL_LUT0_OUT_PIN  PIN_PA19I_CCL_OUT0

#define CCL_LUT1_IN0_MUX  MUX_PA08I_CCL_IN3
#define CCL_LUT1_IN1_MUX  MUX_PA09I_CCL_IN4
#define CCL_LUT1_IN2_MUX  MUX_PA10I_CCL_IN5
#define CCL_LUT1_OUT_MUX  MUX_PA11I_CCL_OUT1

#define CCL_LUT1_IN0_PIN  PIN_PA08I_CCL_IN3
#define CCL_LUT1_IN1_PIN  PIN_PA09I_CCL_IN4
#define CCL_LUT1_IN2_PIN  PIN_PA10I_CCL_IN5
#define CCL_LUT1_OUT_PIN  PIN_PA11I_CCL_OUT1
/** @} */

#define SLCD_BACLKLIGHT    PIN_PC27

/**
 * \brief Turns off the specified LEDs.
 *
 * \param led_gpio LED to turn off (LEDx_GPIO).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_Off(led_gpio)     port_pin_set_output_level(led_gpio,true)

/**
 * \brief Turns on the specified LEDs.
 *
 * \param led_gpio LED to turn on (LEDx_GPIO).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_On(led_gpio)      port_pin_set_output_level(led_gpio,false)

/**
 * \brief Toggles the specified LEDs.
 *
 * \param led_gpio LED to toggle (LEDx_GPIO).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_Toggle(led_gpio)  port_pin_toggle_output_level(led_gpio)

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* SAML22_XPLAINED_PRO_H_INCLUDED */
