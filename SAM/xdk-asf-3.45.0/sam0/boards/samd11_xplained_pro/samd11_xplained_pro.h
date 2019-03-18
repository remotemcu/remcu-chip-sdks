/**
 * \file
 *
 * \brief SAM D11 Xplained Pro board definition
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

#ifndef SAMD11_XPLAINED_PRO_H_INCLUDED
#define SAMD11_XPLAINED_PRO_H_INCLUDED

#include <conf_board.h>
#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup group_common_boards
 * \defgroup samd11_xplained_pro_group SAM D11 Xplained Pro board
 *
 * @{
 */

void system_board_init(void);

/**
 * \defgroup samd11_xplained_pro_features_group Features
 *
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

/** Name string macro */
#define BOARD_NAME                "SAMD11_XPLAINED_PRO"

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
#define LED0_PIN                  PIN_PA16
#define LED0_ACTIVE               false
#define LED0_INACTIVE             !LED0_ACTIVE
#define LED0_GPIO                 LED0_PIN
/** @} */

/** \name SW0 definitions
 *  @{ */
#define SW0_PIN                   PIN_PA14
#define SW0_ACTIVE                false
#define SW0_INACTIVE              !SW0_ACTIVE
#define SW0_EIC_PIN               PIN_PA14A_EIC_NMI
#define SW0_EIC_MUX               MUX_PA14A_EIC_NMI
#define SW0_EIC_PINMUX            PINMUX_PA14A_EIC_NMI
#define SW0_EIC_LINE              0
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
#define EXT1_PIN_5                PIN_PA04
#define EXT1_PIN_6                PIN_PA05
#define EXT1_PIN_7                PIN_PA16
#define EXT1_PIN_8                PIN_PA17
#define EXT1_PIN_9                PIN_PA14
#define EXT1_PIN_10               PIN_PA15
#define EXT1_PIN_11               PIN_PA22
#define EXT1_PIN_12               PIN_PA23
#define EXT1_PIN_13               PIN_PA11
#define EXT1_PIN_14               PIN_PA10
#define EXT1_PIN_15               PIN_PA08
#define EXT1_PIN_16               PIN_PA06
#define EXT1_PIN_17               PIN_PA09
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
#define EXT1_PIN_GPIO_3           EXT1_PIN_9
#define EXT1_PIN_GPIO_4           EXT1_PIN_10
#define EXT1_PIN_I2C_SDA          EXT1_PIN_11
#define EXT1_PIN_I2C_SCL          EXT1_PIN_12
#define EXT1_PIN_UART_RX          EXT1_PIN_13
#define EXT1_PIN_UART_TX          EXT1_PIN_14
#define EXT1_PIN_SPI_SS_0         EXT1_PIN_15
#define EXT1_PIN_SPI_MOSI         EXT1_PIN_16
#define EXT1_PIN_SPI_MISO         EXT1_PIN_17
#define EXT1_PIN_SPI_SCK          EXT1_PIN_18
/** @} */

/** \name Extension header #1 PWM definitions
 *  @{
 */
#define EXT1_PWM_MODULE           TC1
#define EXT1_PWM_0_CHANNEL        0
#define EXT1_PWM_0_PIN            PIN_PA16E_TC1_WO0
#define EXT1_PWM_0_MUX            MUX_PA16E_TC1_WO0
#define EXT1_PWM_0_PINMUX         PINMUX_PA16E_TC1_WO0
#define EXT1_PWM_1_CHANNEL        1
#define EXT1_PWM_1_PIN            PIN_PA17E_TC1_WO1
#define EXT1_PWM_1_MUX            MUX_PA17E_TC1_WO1
#define EXT1_PWM_1_PINMUX         PINMUX_PA17E_TC1_WO1
/** @} */

/** \name Extension header #1 IRQ/External interrupt definitions
 *  @{
 */
#define EXT1_IRQ_MODULE           EIC
#define EXT1_IRQ_INPUT            0
#define EXT1_IRQ_PIN              PIN_PA14A_EIC_NMI
#define EXT1_IRQ_MUX              MUX_PA14A_EIC_NMI
#define EXT1_IRQ_PINMUX           PINMUX_PA14A_EIC_NMI
/** @} */

/** \name Extension header #1 I2C definitions
 *  @{
 */
#define EXT1_I2C_MODULE              SERCOM1
#define EXT1_I2C_SERCOM_PINMUX_PAD0  PINMUX_PA22C_SERCOM1_PAD0
#define EXT1_I2C_SERCOM_PINMUX_PAD1  PINMUX_PA23C_SERCOM1_PAD1
#define EXT1_I2C_SERCOM_DMAC_ID_TX   SERCOM1_DMAC_ID_TX
#define EXT1_I2C_SERCOM_DMAC_ID_RX   SERCOM1_DMAC_ID_RX
/** @} */

/** \name Extension header #1 SPI definitions
 *  @{
 */
#define EXT1_SPI_MODULE              SERCOM0
#define EXT1_SPI_SERCOM_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_D
#define EXT1_SPI_SERCOM_PINMUX_PAD0  PINMUX_PA06C_SERCOM0_PAD0
#define EXT1_SPI_SERCOM_PINMUX_PAD1  PINMUX_PA07C_SERCOM0_PAD1
#define EXT1_SPI_SERCOM_PINMUX_PAD2  PINMUX_PA08D_SERCOM0_PAD2
#define EXT1_SPI_SERCOM_PINMUX_PAD3  PINMUX_PA09D_SERCOM0_PAD3
#define EXT1_SPI_SERCOM_DMAC_ID_TX   SERCOM0_DMAC_ID_TX
#define EXT1_SPI_SERCOM_DMAC_ID_RX   SERCOM0_DMAC_ID_RX

/** \name Extension header #2 pin definitions (not used, defined to avoid compiling errors)
 *  @{
 */
#define EXT2_PIN_3                   -1 /* Not available on this board */
#define EXT2_PIN_4                   -1 /* Not available on this board */
#define EXT2_PIN_5                   -1 /* Not available on this board */
#define EXT2_PIN_6                   -1 /* Not available on this board */
#define EXT2_PIN_7                   -1 /* Not available on this board */
#define EXT2_PIN_8                   -1 /* Not available on this board */
#define EXT2_PIN_9                   -1 /* Not available on this board */
#define EXT2_PIN_10                  -1 /* Not available on this board */
#define EXT2_PIN_11                  -1 /* Not available on this board */
#define EXT2_PIN_12                  -1 /* Not available on this board */
#define EXT2_PIN_13                  -1 /* Not available on this board */
#define EXT2_PIN_14                  -1 /* Not available on this board */
#define EXT2_PIN_15                  -1 /* Not available on this board */
#define EXT2_PIN_16                  -1 /* Not available on this board */
#define EXT2_PIN_17                  -1 /* Not available on this board */
#define EXT2_PIN_18                  -1 /* Not available on this board */
/** @} */


/** \name Extension header #3 pin definitions
 *  @{
 */
#define EXT3_PIN_3                   -1 /* Not available on this board */
#define EXT3_PIN_4                   -1 /* Not available on this board */
#define EXT3_PIN_5                   -1 /* Not available on this board */
#define EXT3_PIN_6                   -1 /* Not available on this board */
#define EXT3_PIN_7                   -1 /* Not available on this board */
#define EXT3_PIN_8                   -1 /* Not available on this board */
#define EXT3_PIN_9                   -1 /* Not available on this board */
#define EXT3_PIN_10                  -1 /* Not available on this board */
#define EXT3_PIN_11                  -1 /* Not available on this board */
#define EXT3_PIN_12                  -1 /* Not available on this board */
#define EXT3_PIN_13                  -1 /* Not available on this board */
#define EXT3_PIN_14                  -1 /* Not available on this board */
#define EXT3_PIN_15                  -1 /* Not available on this board */
#define EXT3_PIN_16                  -1 /* Not available on this board */
#define EXT3_PIN_17                  -1 /* Not available on this board */
#define EXT3_PIN_18                  -1 /* Not available on this board */
/** @} */

/** \name Extension header #3 SPI definitions
 *  @{
 */
#define EXT3_SPI_SLAVE_SELECT_PIN    -1 /* Not available on this board */
#define EXT3_SPI_MODULE              -1 /* Not available on this board */
#define EXT3_SPI_SERCOM_MUX_SETTING  -1 /* Not available on this board */
#define EXT3_SPI_SERCOM_PINMUX_PAD0  -1 /* Not available on this board */
#define EXT3_SPI_SERCOM_PINMUX_PAD1  -1 /* Not available on this board */
#define EXT3_SPI_SERCOM_PINMUX_PAD2  -1 /* Not available on this board */
#define EXT3_SPI_SERCOM_PINMUX_PAD3  -1 /* Not available on this board */
#define EXT3_SPI_SERCOM_DMAC_ID_TX   -1 /* Not available on this board */
#define EXT3_SPI_SERCOM_DMAC_ID_RX   -1 /* Not available on this board */
/** @} */

/** \name Embedded debugger CDC Gateway USART interface definitions
 * @{
 */
#define EDBG_CDC_MODULE              SERCOM2
#define EDBG_CDC_SERCOM_MUX_SETTING  USART_RX_3_TX_2_XCK_3
#define EDBG_CDC_SERCOM_PINMUX_PAD0  PINMUX_UNUSED
#define EDBG_CDC_SERCOM_PINMUX_PAD1  PINMUX_UNUSED
#define EDBG_CDC_SERCOM_PINMUX_PAD2  PINMUX_PA10D_SERCOM2_PAD2
#define EDBG_CDC_SERCOM_PINMUX_PAD3  PINMUX_PA11D_SERCOM2_PAD3
#define EDBG_CDC_SERCOM_DMAC_ID_TX   SERCOM2_DMAC_ID_TX
#define EDBG_CDC_SERCOM_DMAC_ID_RX   SERCOM2_DMAC_ID_RX
#define EDBG_CDC_MODULE_IRQn         SERCOM2_IRQn
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


#ifdef __cplusplus
}
#endif

#endif  /* SAMD11_XPLAINED_PRO_H_INCLUDED */
