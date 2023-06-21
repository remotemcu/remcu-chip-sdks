/**
 * \file
 *
 * \brief SAM L21 Xplained Pro board definition
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

#ifndef SAML21_XPLAINED_PRO_H_INCLUDED
#define SAML21_XPLAINED_PRO_H_INCLUDED

#include <conf_board.h>
#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup group_common_boards
 * \defgroup saml21_xplained_pro_group SAM L21 Xplained Pro board
 *
 * @{
 */

void system_board_init(void);

/**
 * \defgroup saml21_xplained_pro_features_group Features
 *
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

/** Name string macro */
#define BOARD_NAME                "SAML21_XPLAINED_PRO"

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
#define LED0_PIN                  PIN_PB10
#define LED0_ACTIVE               false
#define LED0_INACTIVE             !LED0_ACTIVE
/** @} */

/** \name SW0 definitions
 *  @{ */
#define SW0_PIN                   PIN_PA02
#define SW0_ACTIVE                false
#define SW0_INACTIVE              !SW0_ACTIVE
#define SW0_EIC_PIN               PIN_PA02A_EIC_EXTINT2
#define SW0_EIC_MUX               MUX_PA02A_EIC_EXTINT2
#define SW0_EIC_PINMUX            PINMUX_PA02A_EIC_EXTINT2
#define SW0_EIC_LINE              2
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
#define LED_0_PWM4CTRL_CHANNEL    0
#define LED_0_PWM4CTRL_OUTPUT     0
#define LED_0_PWM4CTRL_PIN        PIN_PB10F_TCC0_WO4
#define LED_0_PWM4CTRL_MUX        MUX_PB10F_TCC0_WO4
#define LED_0_PWM4CTRL_PINMUX     PINMUX_PB10F_TCC0_WO4
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
#define EXT1_PIN_3                PIN_PB05
#define EXT1_PIN_4                PIN_PA03
#define EXT1_PIN_5                PIN_PB06
#define EXT1_PIN_6                PIN_PB07
#define EXT1_PIN_7                PIN_PA12
#define EXT1_PIN_8                PIN_PA13
#define EXT1_PIN_9                PIN_PB04
#define EXT1_PIN_10               PIN_PA02
#define EXT1_PIN_11               PIN_PA08
#define EXT1_PIN_12               PIN_PA09
#define EXT1_PIN_13               PIN_PB09
#define EXT1_PIN_14               PIN_PB08
#define EXT1_PIN_15               PIN_PA05
#define EXT1_PIN_16               PIN_PA06
#define EXT1_PIN_17               PIN_PA04
#define EXT1_PIN_18               PIN_PA07
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

/** \name Extension header #1 ADC definitions
 *  @{
 */
#define EXT1_ADC_MODULE           ADC
#define EXT1_ADC_13_CHANNEL       13
#define EXT1_ADC_13_PIN           PIN_PB05B_ADC_AIN13
#define EXT1_ADC_13_MUX           MUX_PB05B_ADC_AIN13
#define EXT1_ADC_13_PINMUX        PINMUX_PB05B_ADC_AIN13
#define EXT1_ADC_1_CHANNEL        1
#define EXT1_ADC_1_PIN            PIN_PA03B_ADC_AIN1
#define EXT1_ADC_1_MUX            MUX_PA03B_ADC_AIN1
#define EXT1_ADC_1_PINMUX         PINMUX_PA03B_ADC_AIN1
/** @} */

/** \name Extension header #1 PWM definitions
 *  @{
 */
#define EXT1_PWM_MODULE           TC2
#define EXT1_PWM_0_CHANNEL        0
#define EXT1_PWM_0_PIN            PIN_PB02E_TC2_WO0
#define EXT1_PWM_0_MUX            MUX_PB02E_TC2_WO0
#define EXT1_PWM_0_PINMUX         PINMUX_PB02E_TC2_WO0
#define EXT1_PWM_1_CHANNEL        1
#define EXT1_PWM_1_PIN            PIN_PB03E_TC2_WO1
#define EXT1_PWM_1_MUX            MUX_PB03E_TC2_WO1
#define EXT1_PWM_1_PINMUX         PINMUX_PB03E_TC2_WO1
/** @} */

/** \name Extension header #1 IRQ/External interrupt definitions
 *  @{
 */
#define EXT1_IRQ_MODULE           EIC
#define EXT1_IRQ_INPUT            4
#define EXT1_IRQ_PIN              PIN_PB04A_EIC_EXTINT4
#define EXT1_IRQ_MUX              MUX_PB04A_EIC_EXTINT4
#define EXT1_IRQ_PINMUX           PINMUX_PB04A_EIC_EXTINT4
/** @} */

/** \name Extension header #1 I2C definitions
 *  @{
 */
#define EXT1_I2C_MODULE              SERCOM2
#define EXT1_I2C_SERCOM_PINMUX_PAD0  PINMUX_PA08D_SERCOM2_PAD0
#define EXT1_I2C_SERCOM_PINMUX_PAD1  PINMUX_PA09D_SERCOM2_PAD1
#define EXT1_I2C_SERCOM_DMAC_ID_TX   SERCOM2_DMAC_ID_TX
#define EXT1_I2C_SERCOM_DMAC_ID_RX   SERCOM2_DMAC_ID_RX
/** @} */

/** \name Extension header #1 UART definitions
 *  @{
 */
#define EXT1_UART_MODULE              SERCOM4
#define EXT1_UART_SERCOM_MUX_SETTING  USART_RX_1_TX_0_XCK_1
#define EXT1_UART_SERCOM_PINMUX_PAD0  PINMUX_PB08D_SERCOM4_PAD0
#define EXT1_UART_SERCOM_PINMUX_PAD1  PINMUX_PB09D_SERCOM4_PAD1
#define EXT1_UART_SERCOM_PINMUX_PAD2  PINMUX_UNUSED
#define EXT1_UART_SERCOM_PINMUX_PAD3  PINMUX_UNUSED
#define EXT1_UART_SERCOM_DMAC_ID_TX   SERCOM4_DMAC_ID_TX
#define EXT1_UART_SERCOM_DMAC_ID_RX   SERCOM4_DMAC_ID_RX
/** @} */

/** \name Extension header #1 SPI definitions
 *  @{
 */
#define EXT1_SPI_MODULE              SERCOM0
#define EXT1_SPI_SERCOM_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_E
#define EXT1_SPI_SERCOM_PINMUX_PAD0  PINMUX_PA04D_SERCOM0_PAD0
#define EXT1_SPI_SERCOM_PINMUX_PAD1  PINMUX_PA05D_SERCOM0_PAD1
#define EXT1_SPI_SERCOM_PINMUX_PAD2  PINMUX_PA06D_SERCOM0_PAD2
#define EXT1_SPI_SERCOM_PINMUX_PAD3  PINMUX_PA07D_SERCOM0_PAD3
#define EXT1_SPI_SERCOM_DMAC_ID_TX   SERCOM0_DMAC_ID_TX
#define EXT1_SPI_SERCOM_DMAC_ID_RX   SERCOM0_DMAC_ID_RX
/** @} */

/** \name Extension header #2 pin definitions
 *  @{
 */
#define EXT2_PIN_3                PIN_PA10
#define EXT2_PIN_4                PIN_PA11
#define EXT2_PIN_5                PIN_PA20
#define EXT2_PIN_6                PIN_PA21
#define EXT2_PIN_7                PIN_PB12
#define EXT2_PIN_8                PIN_PB13
#define EXT2_PIN_9                PIN_PB14
#define EXT2_PIN_10               PIN_PB15
#define EXT2_PIN_11               PIN_PA08
#define EXT2_PIN_12               PIN_PA09
#define EXT2_PIN_13               PIN_PA19
#define EXT2_PIN_14               PIN_PA18
#define EXT2_PIN_15               PIN_PA17
#define EXT2_PIN_16               PIN_PB22
#define EXT2_PIN_17               PIN_PB16
#define EXT2_PIN_18               PIN_PB23
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

/** \name Extension header #2 ADC definitions
 *  @{
 */
#define EXT2_ADC_MODULE           ADC
#define EXT2_ADC_0_CHANNEL        18
#define EXT2_ADC_0_PIN            PIN_PA10B_ADC_AIN18
#define EXT2_ADC_0_MUX            MUX_PA10B_ADC_AIN18
#define EXT2_ADC_0_PINMUX         PINMUX_PA10B_ADC_AIN18
#define EXT2_ADC_1_CHANNEL        19
#define EXT2_ADC_1_PIN            PIN_PA11B_ADC_AIN19
#define EXT2_ADC_1_MUX            MUX_PA11B_ADC_AIN19
#define EXT2_ADC_1_PINMUX         PINMUX_PA11B_ADC_AIN19
/** @} */

/** \name Extension header #2 PWM definitions
 *  @{
 */
#define EXT2_PWM_MODULE           TC0
#define EXT2_PWM_0_CHANNEL        0
#define EXT2_PWM_0_PIN            PIN_PB12E_TC0_WO0
#define EXT2_PWM_0_MUX            MUX_PB12E_TC0_WO0
#define EXT2_PWM_0_PINMUX         PINMUX_PB12E_TC0_WO0
#define EXT2_PWM_1_CHANNEL        1
#define EXT2_PWM_1_PIN            PIN_PB13E_TC0_WO1
#define EXT2_PWM_1_MUX            MUX_PB13E_TC0_WO1
#define EXT2_PWM_1_PINMUX         PINMUX_PB13E_TC0_WO1
/** @} */

/** \name Extension header #2 IRQ/External interrupt definitions
 *  @{
 */
#define EXT2_IRQ_MODULE           EIC
#define EXT2_IRQ_INPUT            14
#define EXT2_IRQ_PIN              PIN_PB14A_EIC_EXTINT14
#define EXT2_IRQ_MUX              MUX_PB14A_EIC_EXTINT14
#define EXT2_IRQ_PINMUX           PINMUX_PB14A_EIC_EXTINT14
/** @} */

 /** \name Extension header #2 I2C definitions
 *  @{
 */
#define EXT2_I2C_MODULE              SERCOM2
#define EXT2_I2C_SERCOM_PINMUX_PAD0  PINMUX_PA08D_SERCOM2_PAD0
#define EXT2_I2C_SERCOM_PINMUX_PAD1  PINMUX_PA09D_SERCOM2_PAD1
#define EXT2_I2C_SERCOM_DMAC_ID_TX   SERCOM2_DMAC_ID_TX
#define EXT2_I2C_SERCOM_DMAC_ID_RX   SERCOM2_DMAC_ID_RX
/** @} */

/** \name Extension header #2 UART definitions
 *  @{
 */
#define EXT2_UART_MODULE              SERCOM1
#define EXT2_UART_SERCOM_MUX_SETTING  USART_RX_3_TX_2_XCK_3
#define EXT2_UART_SERCOM_PINMUX_PAD0  PINMUX_UNUSED
#define EXT2_UART_SERCOM_PINMUX_PAD1  PINMUX_UNUSED
#define EXT2_UART_SERCOM_PINMUX_PAD2  PINMUX_PA18C_SERCOM1_PAD2
#define EXT2_UART_SERCOM_PINMUX_PAD3  PINMUX_PA19C_SERCOM1_PAD3
#define EXT2_UART_SERCOM_DMAC_ID_TX   SERCOM1_DMAC_ID_TX
#define EXT2_UART_SERCOM_DMAC_ID_RX   SERCOM1_DMAC_ID_RX
/** @} */

/** \name Extension header #2 SPI definitions
 *  @{
 */
#define EXT2_SPI_MODULE              SERCOM5
#define EXT2_SPI_SERCOM_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_E
#define EXT2_SPI_SERCOM_PINMUX_PAD0  PINMUX_PB16C_SERCOM5_PAD0
#define EXT2_SPI_SERCOM_PINMUX_PAD1  PINMUX_UNUSED
#define EXT2_SPI_SERCOM_PINMUX_PAD2  PINMUX_PB22D_SERCOM5_PAD2
#define EXT2_SPI_SERCOM_PINMUX_PAD3  PINMUX_PB23D_SERCOM5_PAD3
#define EXT2_SPI_SERCOM_DMAC_ID_TX   SERCOM5_DMAC_ID_TX
#define EXT2_SPI_SERCOM_DMAC_ID_RX   SERCOM5_DMAC_ID_RX
/** @} */

/** \name Extension header #3 pin definitions
 *  @{
 */
#define EXT3_PIN_3                PIN_PB00
#define EXT3_PIN_4                PIN_PB01
#define EXT3_PIN_5                PIN_PB30
#define EXT3_PIN_6                PIN_PA15
#define EXT3_PIN_7                PIN_PB10
#define EXT3_PIN_8                PIN_PB11
#define EXT3_PIN_9                PIN_PA16
#define EXT3_PIN_10               PIN_PA27
#define EXT3_PIN_11               PIN_PA08
#define EXT3_PIN_12               PIN_PA09
#define EXT3_PIN_13               PIN_PA19
#define EXT3_PIN_14               PIN_PA18
#define EXT3_PIN_15               PIN_PB17
#define EXT3_PIN_16               PIN_PB22
#define EXT3_PIN_17               PIN_PB16
#define EXT3_PIN_18               PIN_PB23
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

/** \name Extension header #3 ADC definitions
 *  @{
 */
#define EXT3_ADC_MODULE           ADC
#define EXT3_ADC_0_CHANNEL        8
#define EXT3_ADC_0_PIN            PIN_PB00B_ADC_AIN8
#define EXT3_ADC_0_MUX            MUX_PB00B_ADC_AIN8
#define EXT3_ADC_0_PINMUX         PINMUX_PB00B_ADC_AIN8
#define EXT3_ADC_1_CHANNEL        9
#define EXT3_ADC_1_PIN            PIN_PB01B_ADC_AIN9
#define EXT3_ADC_1_MUX            MUX_PB01B_ADC_AIN9
#define EXT3_ADC_1_PINMUX         PINMUX_PB01B_ADC_AIN9
/** @} */

/** \name Extension header #3 IRQ/External interrupt definitions
 *  @{
 */
#define EXT3_IRQ_MODULE           EIC
#define EXT3_IRQ_INPUT            0
#define EXT3_IRQ_PIN              PIN_PA16A_EIC_EXTINT0
#define EXT3_IRQ_MUX              MUX_PA16A_EIC_EXTINT0
#define EXT3_IRQ_PINMUX           PINMUX_PA16A_EIC_EXTINT0
/** @} */

/** \name Extension header #3 I2C definitions
 *  @{
 */
#define EXT3_I2C_MODULE              SERCOM2
#define EXT3_I2C_SERCOM_PINMUX_PAD0  PINMUX_PA08D_SERCOM2_PAD0
#define EXT3_I2C_SERCOM_PINMUX_PAD1  PINMUX_PA09D_SERCOM2_PAD1
#define EXT3_I2C_SERCOM_DMAC_ID_TX   SERCOM2_DMAC_ID_TX
#define EXT3_I2C_SERCOM_DMAC_ID_RX   SERCOM2_DMAC_ID_RX
/** @} */

/** \name Extension header #3 UART definitions
 *  @{
 */
#define EXT3_UART_MODULE              SERCOM1
#define EXT3_UART_SERCOM_MUX_SETTING  USART_RX_3_TX_2_XCK_3
#define EXT3_UART_SERCOM_PINMUX_PAD0  PINMUX_UNUSED
#define EXT3_UART_SERCOM_PINMUX_PAD1  PINMUX_UNUSED
#define EXT3_UART_SERCOM_PINMUX_PAD2  PINMUX_PA18C_SERCOM1_PAD2
#define EXT3_UART_SERCOM_PINMUX_PAD3  PINMUX_PA19C_SERCOM1_PAD3
#define EXT3_UART_SERCOM_DMAC_ID_TX   SERCOM1_DMAC_ID_TX
#define EXT3_UART_SERCOM_DMAC_ID_RX   SERCOM1_DMAC_ID_RX

/** @} */

/** \name Extension header #3 SPI definitions
 *  @{
 */
#define EXT3_SPI_MODULE              SERCOM5
#define EXT3_SPI_SERCOM_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_E
#define EXT3_SPI_SERCOM_PINMUX_PAD0  PINMUX_PB16C_SERCOM5_PAD0
#define EXT3_SPI_SERCOM_PINMUX_PAD1  PINMUX_PB17C_SERCOM5_PAD1
#define EXT3_SPI_SERCOM_PINMUX_PAD2  PINMUX_PB22D_SERCOM5_PAD2
#define EXT3_SPI_SERCOM_PINMUX_PAD3  PINMUX_PB23D_SERCOM5_PAD3
#define EXT3_SPI_SERCOM_DMAC_ID_TX   SERCOM5_DMAC_ID_TX
#define EXT3_SPI_SERCOM_DMAC_ID_RX   SERCOM5_DMAC_ID_RX
/** @} */

/** \name Embedded debugger I2C interface definitions
 * @{
 */
#define EDBG_I2C_MODULE              SERCOM2
#define EDBG_I2C_SERCOM_PINMUX_PAD0  PINMUX_PA08D_SERCOM2_PAD0
#define EDBG_I2C_SERCOM_PINMUX_PAD1  PINMUX_PA09D_SERCOM2_PAD1
#define EDBG_I2C_SERCOM_DMAC_ID_TX   SERCOM2_DMAC_ID_TX
#define EDBG_I2C_SERCOM_DMAC_ID_RX   SERCOM2_DMAC_ID_RX
/** @} */

/** \name Embedded debugger SPI interface definitions
 * @{
 */
#define EDBG_SPI_MODULE              SERCOM5
#define EDBG_SPI_SERCOM_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_E
#define EDBG_SPI_SERCOM_PINMUX_PAD0  PINMUX_PB16C_SERCOM5_PAD0
#define EDBG_SPI_SERCOM_PINMUX_PAD1  PINMUX_PB31D_SERCOM5_PAD1
#define EDBG_SPI_SERCOM_PINMUX_PAD2  PINMUX_PB22D_SERCOM5_PAD2
#define EDBG_SPI_SERCOM_PINMUX_PAD3  PINMUX_PB23D_SERCOM5_PAD3
#define EDBG_SPI_SERCOM_DMAC_ID_TX   SERCOM5_DMAC_ID_TX
#define EDBG_SPI_SERCOM_DMAC_ID_RX   SERCOM5_DMAC_ID_RX
/** @} */

/** \name Embedded debugger CDC Gateway USART interface definitions
 * @{
 */
#define EDBG_CDC_MODULE              SERCOM3
#define EDBG_CDC_SERCOM_MUX_SETTING  USART_RX_1_TX_0_XCK_1
#define EDBG_CDC_SERCOM_PINMUX_PAD0  PINMUX_PA22C_SERCOM3_PAD0
#define EDBG_CDC_SERCOM_PINMUX_PAD1  PINMUX_PA23C_SERCOM3_PAD1
#define EDBG_CDC_SERCOM_PINMUX_PAD2  PINMUX_UNUSED
#define EDBG_CDC_SERCOM_PINMUX_PAD3  PINMUX_UNUSED
#define EDBG_CDC_SERCOM_DMAC_ID_TX   SERCOM3_DMAC_ID_TX
#define EDBG_CDC_SERCOM_DMAC_ID_RX   SERCOM3_DMAC_ID_RX


#define EDBG_CDC_SERCOM_PIN_PAD0     PIN_PA22C_SERCOM3_PAD0
#define EDBG_CDC_SERCOM_PIN_PAD1     PIN_PA23C_SERCOM3_PAD1

/** @} */

/** \name USB definitions
 * @{
 */
#define USB_ID
#define USB_TARGET_DP_PIN            PIN_PA25G_USB_DP
#define USB_TARGET_DP_MUX            MUX_PA25G_USB_DP
#define USB_TARGET_DP_PINMUX         PINMUX_PA25G_USB_DP
#define USB_TARGET_DM_PIN            PIN_PA24G_USB_DM
#define USB_TARGET_DM_MUX            MUX_PA24G_USB_DM
#define USB_TARGET_DM_PINMUX         PINMUX_PA24G_USB_DM
#define USB_VBUS_PIN                 PIN_PA14
#define USB_VBUS_EIC_LINE            14
#define USB_VBUS_EIC_MUX             MUX_PA14A_EIC_EXTINT14
#define USB_VBUS_EIC_PINMUX          PINMUX_PA14A_EIC_EXTINT14
#define USB_ID_PIN                   PIN_PB02
#define USB_ID_EIC_LINE              2
#define USB_ID_EIC_MUX               MUX_PB02A_EIC_EXTINT2
#define USB_ID_EIC_PINMUX            PINMUX_PB02A_EIC_EXTINT2
/** @} */

/** \name CCL interface definitions
 * @{
 */
#define CCL_LUT0_IN0_MUX  MUX_PA04I_CCL_IN0
#define CCL_LUT0_IN1_MUX  MUX_PA05I_CCL_IN1
#define CCL_LUT0_IN2_MUX  MUX_PA06I_CCL_IN2
#define CCL_LUT0_OUT_MUX  MUX_PA07I_CCL_OUT0

#define CCL_LUT0_IN0_PIN  PIN_PA04I_CCL_IN0
#define CCL_LUT0_IN1_PIN  PIN_PA05I_CCL_IN1
#define CCL_LUT0_IN2_PIN  PIN_PA06I_CCL_IN2
#define CCL_LUT0_OUT_PIN  PIN_PA07I_CCL_OUT0

#define CCL_LUT1_IN0_MUX  MUX_PA08I_CCL_IN3
#define CCL_LUT1_IN1_MUX  MUX_PA09I_CCL_IN4
#define CCL_LUT1_IN2_MUX  MUX_PA10I_CCL_IN5
#define CCL_LUT1_OUT_MUX  MUX_PA11I_CCL_OUT1

#define CCL_LUT1_IN0_PIN  PIN_PA08I_CCL_IN3
#define CCL_LUT1_IN1_PIN  PIN_PA09I_CCL_IN4
#define CCL_LUT1_IN2_PIN  PIN_PA10I_CCL_IN5
#define CCL_LUT1_OUT_PIN  PIN_PA11I_CCL_OUT1
/** @} */


/** \name 802.15.4 TRX Interface definitions for EXT1
 * @{
 */
#ifndef EXT2_CONFIG
#define AT86RFX_SPI                  EXT1_SPI_MODULE
#define AT86RFX_RST_PIN              EXT1_PIN_7
#define AT86RFX_MISC_PIN             EXT1_PIN_12
#define AT86RFX_IRQ_PIN              EXT1_PIN_9
#define AT86RFX_SLP_PIN              EXT1_PIN_10
#define AT86RFX_SPI_CS               EXT1_PIN_15
#define AT86RFX_SPI_MOSI             EXT1_PIN_16
#define AT86RFX_SPI_MISO             EXT1_PIN_17
#define AT86RFX_SPI_SCK              EXT1_PIN_18
#define AT86RFX_CSD                  EXT1_PIN_5
#define AT86RFX_CPS                  EXT1_PIN_8

#define AT86RFX_SPI_SERCOM_MUX_SETTING   EXT1_SPI_SERCOM_MUX_SETTING
#define AT86RFX_SPI_SERCOM_PINMUX_PAD0   EXT1_SPI_SERCOM_PINMUX_PAD0
#define AT86RFX_SPI_SERCOM_PINMUX_PAD1   PINMUX_UNUSED
#define AT86RFX_SPI_SERCOM_PINMUX_PAD2   EXT1_SPI_SERCOM_PINMUX_PAD2
#define AT86RFX_SPI_SERCOM_PINMUX_PAD3   EXT1_SPI_SERCOM_PINMUX_PAD3

#define AT86RFX_IRQ_CHAN       EXT1_IRQ_INPUT
#define AT86RFX_IRQ_PINMUX     EXT1_IRQ_PINMUX

#endif
/** Enables the transceiver main interrupt. */
#define ENABLE_TRX_IRQ()     \
		extint_chan_enable_callback(AT86RFX_IRQ_CHAN, EXTINT_CALLBACK_TYPE_DETECT)

/** Disables the transceiver main interrupt. */
#define DISABLE_TRX_IRQ()    \
		extint_chan_disable_callback(AT86RFX_IRQ_CHAN, EXTINT_CALLBACK_TYPE_DETECT)

/** Clears the transceiver main interrupt. */
#define CLEAR_TRX_IRQ()      \
		extint_chan_clear_detected(AT86RFX_IRQ_CHAN);

/*
 * This macro saves the trx interrupt status and disables the trx interrupt.
 */
#define ENTER_TRX_REGION()   \
		{ extint_chan_disable_callback(AT86RFX_IRQ_CHAN, EXTINT_CALLBACK_TYPE_DETECT)

/*
 *  This macro restores the transceiver interrupt status
 */
#define LEAVE_TRX_REGION()   \
		extint_chan_enable_callback(AT86RFX_IRQ_CHAN, EXTINT_CALLBACK_TYPE_DETECT); }

/** @} */

/** \name LoRa Radio Interface definitions for EXT1
 * @{
 */


#ifndef SX_EXT2_CONFIG

#define SX_RF_SPI                  EXT1_SPI_MODULE
#define SX_RF_RESET_PIN            EXT1_PIN_3
#define SX_RF_SPI_CS               EXT1_PIN_15
#define SX_RF_SPI_MOSI             EXT1_PIN_16
#define SX_RF_SPI_MISO             EXT1_PIN_17
#define SX_RF_SPI_SCK              EXT1_PIN_18


#define SX_RF_SPI_SERCOM_MUX_SETTING   EXT1_SPI_SERCOM_MUX_SETTING
#define SX_RF_SPI_SERCOM_PINMUX_PAD0   EXT1_SPI_SERCOM_PINMUX_PAD0
#define SX_RF_SPI_SERCOM_PINMUX_PAD1   PINMUX_UNUSED
#define SX_RF_SPI_SERCOM_PINMUX_PAD2   EXT1_SPI_SERCOM_PINMUX_PAD2
#define SX_RF_SPI_SERCOM_PINMUX_PAD3   EXT1_SPI_SERCOM_PINMUX_PAD3

#define DIO0_PIN                   EXT1_PIN_5
#define DIO0_ACTIVE                true
#define DIO0_INACTIVE              !DIO0_ACTIVE
#define DIO0_EIC_PIN               PIN_PB06A_EIC_EXTINT6
#define DIO0_EIC_MUX               MUX_PB06A_EIC_EXTINT6
#define DIO0_EIC_PINMUX            PINMUX_PB06A_EIC_EXTINT6
#define DIO0_EIC_LINE              6 //5

#define DIO1_PIN                   EXT1_PIN_6
#define DIO1_ACTIVE                true
#define DIO1_INACTIVE              !DIO1_ACTIVE
#define DIO1_EIC_PIN               PIN_PB07A_EIC_EXTINT7
#define DIO1_EIC_MUX               MUX_PB07A_EIC_EXTINT7
#define DIO1_EIC_PINMUX            PINMUX_PB07A_EIC_EXTINT7
#define DIO1_EIC_LINE              7

#define DIO2_PIN                   EXT1_PIN_7
#define DIO2_ACTIVE                true
#define DIO2_INACTIVE              !DIO2_ACTIVE
#define DIO2_EIC_PIN               PIN_PA12A_EIC_EXTINT12
#define DIO2_EIC_MUX               MUX_PA12A_EIC_EXTINT12
#define DIO2_EIC_PINMUX            PINMUX_PA12A_EIC_EXTINT12
#define DIO2_EIC_LINE              12

#define DIO3_PIN                   EXT1_PIN_8
#define DIO3_ACTIVE                true
#define DIO3_INACTIVE              !DIO2_ACTIVE
#define DIO3_EIC_PIN               PIN_PA13A_EIC_EXTINT13
#define DIO3_EIC_MUX               MUX_PA13A_EIC_EXTINT13
#define DIO3_EIC_PINMUX            PINMUX_PA13A_EIC_EXTINT13
#define DIO3_EIC_LINE              13

#define DIO4_PIN                   EXT1_PIN_9
#define DIO4_ACTIVE                true
#define DIO4_INACTIVE              !DIO2_ACTIVE
#define DIO4_EIC_PIN               PIN_PB04A_EIC_EXTINT4
#define DIO4_EIC_MUX               MUX_PB04A_EIC_EXTINT4
#define DIO4_EIC_PINMUX            PINMUX_PB04A_EIC_EXTINT4
#define DIO4_EIC_LINE              4

#define DIO5_PIN                   EXT1_PIN_10
#define DIO5_ACTIVE                true
#define DIO5_INACTIVE              !DIO2_ACTIVE
#define DIO5_EIC_PIN               PIN_PA02A_EIC_EXTINT2
#define DIO5_EIC_MUX               MUX_PA02A_EIC_EXTINT2
#define DIO5_EIC_PINMUX            PINMUX_PA02A_EIC_EXTINT2
#define DIO5_EIC_LINE              2

#define SX_RF_RESET_HIGH		   true
#define SX_RF_RESET_LOW		       !SX_RF_RESET_HIGH

#else

#define SX_RF_SPI                  EXT2_SPI_MODULE
#define SX_RF_RESET_PIN            EXT2_PIN_3
#define SX_RF_SPI_CS               EXT2_PIN_15
#define SX_RF_SPI_MOSI             EXT2_PIN_16
#define SX_RF_SPI_MISO             EXT2_PIN_17
#define SX_RF_SPI_SCK              EXT2_PIN_18


#define SX_RF_SPI_SERCOM_MUX_SETTING   EXT2_SPI_SERCOM_MUX_SETTING
#define SX_RF_SPI_SERCOM_PINMUX_PAD0   EXT2_SPI_SERCOM_PINMUX_PAD0
#define SX_RF_SPI_SERCOM_PINMUX_PAD1   EXT2_SPI_SERCOM_PINMUX_PAD1
#define SX_RF_SPI_SERCOM_PINMUX_PAD2   EXT2_SPI_SERCOM_PINMUX_PAD2
#define SX_RF_SPI_SERCOM_PINMUX_PAD3   EXT2_SPI_SERCOM_PINMUX_PAD3

#define DIO0_PIN                   EXT2_PIN_5
#define DIO0_ACTIVE                true
#define DIO0_INACTIVE              !DIO0_ACTIVE
#define DIO0_EIC_PIN               PIN_PA20A_EIC_EXTINT4
#define DIO0_EIC_MUX               MUX_PA20A_EIC_EXTINT4
#define DIO0_EIC_PINMUX            PINMUX_PA20A_EIC_EXTINT4
#define DIO0_EIC_LINE              4

#define DIO1_PIN                   EXT2_PIN_6
#define DIO1_ACTIVE                true
#define DIO1_INACTIVE              !DIO1_ACTIVE
#define DIO1_EIC_PIN               PIN_PA21A_EIC_EXTINT5
#define DIO1_EIC_MUX               MUX_PA21A_EIC_EXTINT5
#define DIO1_EIC_PINMUX            PINMUX_PA21A_EIC_EXTINT5
#define DIO1_EIC_LINE              5

#define DIO2_PIN                   EXT2_PIN_7
#define DIO2_ACTIVE                true
#define DIO2_INACTIVE              !DIO2_ACTIVE
#define DIO2_EIC_PIN               PIN_PB12A_EIC_EXTINT12
#define DIO2_EIC_MUX               MUX_PB12A_EIC_EXTINT12
#define DIO2_EIC_PINMUX            PINMUX_PB12A_EIC_EXTINT12
#define DIO2_EIC_LINE              12

#define DIO3_PIN                   EXT2_PIN_8
#define DIO3_ACTIVE                true
#define DIO3_INACTIVE              !DIO2_ACTIVE
#define DIO3_EIC_PIN               PIN_PB13A_EIC_EXTINT13
#define DIO3_EIC_MUX               MUX_PB13A_EIC_EXTINT13
#define DIO3_EIC_PINMUX            PINMUX_PB13A_EIC_EXTINT13
#define DIO3_EIC_LINE              13

#define DIO4_PIN                   EXT2_PIN_9
#define DIO4_ACTIVE                true
#define DIO4_INACTIVE              !DIO2_ACTIVE
#define DIO4_EIC_PIN               PIN_PB14A_EIC_EXTINT14
#define DIO4_EIC_MUX               MUX_PB14A_EIC_EXTINT14
#define DIO4_EIC_PINMUX            PINMUX_PB14A_EIC_EXTINT14
#define DIO4_EIC_LINE              14

#define DIO5_PIN                   EXT2_PIN_10
#define DIO5_ACTIVE                true
#define DIO5_INACTIVE              !DIO2_ACTIVE
#define DIO5_EIC_PIN               PIN_PB15A_EIC_EXTINT15
#define DIO5_EIC_MUX               MUX_PB15A_EIC_EXTINT15
#define DIO5_EIC_PINMUX            PINMUX_PB15A_EIC_EXTINT15
#define DIO5_EIC_LINE              15

#define SX_RF_RESET_HIGH		   true
#define SX_RF_RESET_LOW		       !SX_RF_RESET_HIGH
#endif

/** @} */

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

#endif  /* SAML21_XPLAINED_PRO_H_INCLUDED */
