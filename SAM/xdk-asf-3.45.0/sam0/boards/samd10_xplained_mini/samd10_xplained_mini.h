/**
 * \file
 *
 * \brief SAM D10 Xplained Mini board definition
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

#ifndef SAMD10_XPLAINED_MINI_H_INCLUDED
#define SAMD10_XPLAINED_MINI_H_INCLUDED

#include <conf_board.h>
#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup group_common_boards
 * \defgroup samd10_xplained_mini_group SAM D10 Xplained Mini board
 *
 * @{
 */

void system_board_init(void);

/**
 * \defgroup samd10_xplained_mini_features_group Features
 *
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

/** Name string macro */
#define BOARD_NAME                "SAMD10_XPLAINED_MINI"

/** \name Resonator definitions
 *  @{ */
#define BOARD_FREQ_SLCK_XTAL      0 /* Not Mounted */
#define BOARD_FREQ_SLCK_BYPASS    0 /* Not Mounted */
#define BOARD_FREQ_MAINCK_XTAL    0 /* Not Mounted */
#define BOARD_FREQ_MAINCK_BYPASS  0 /* Not Mounted */
#define BOARD_MCK                 CHIP_FREQ_CPU_MAX
#define BOARD_OSC_STARTUP_US      15625
/** @} */

/** \name LED0 definitions
 *  @{ */
#define LED0_PIN                  PIN_PA09
#define LED0_ACTIVE               true
#define LED0_INACTIVE             !LED0_ACTIVE
#define LED0_GPIO                 LED0_PIN
/** @} */

/** \name SW0 definitions
 *  @{ */
#define SW0_PIN                   PIN_PA25
#define SW0_ACTIVE                false
#define SW0_INACTIVE              !SW0_ACTIVE
#define SW0_EIC_PIN               PIN_PA25A_EIC_EXTINT5
#define SW0_EIC_MUX               MUX_PA25A_EIC_EXTINT5
#define SW0_EIC_PINMUX            PINMUX_PA25A_EIC_EXTINT5
#define SW0_EIC_LINE              5
/** @} */

/**
 * \name LED #0 definitions
 *
 * Wrapper macros for LED0, to ensure common naming across all Xplained
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
 * Wrapper macros for SW0, to ensure common naming across all Xplained
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
/** @} */

/**
 * \brief Turns off the specified LEDs.
 *
 * \param led_gpio LED to turn off (LEDx_GPIO).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_Off(led_gpio)     port_pin_set_output_level(led_gpio, false)

/**
 * \brief Turns on the specified LEDs.
 *
 * \param led_gpio LED to turn on (LEDx_GPIO).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_On(led_gpio)      port_pin_set_output_level(led_gpio, true)

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

#endif  /* SAMD10_XPLAINED_MINI_H_INCLUDED */
