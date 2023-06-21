/**
* \file
*
* \brief SAMR21G18A_MODULE definition
*
* Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries. 
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
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, 
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

#ifndef SAMR21G18A_MODULE_H_INCLUDED
#define SAMR21G18A_MODULE_H_INCLUDED

#include <conf_board.h>
#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup group_common_boards
 * \defgroup samr21g18a_mr210ua_module_group SAMR21G18A_MR210UA_MODULE
 *
 * @{
 */

void system_board_init(void);

/**
 * \defgroup samr21g18a_mr210ua_module_features_group Features
 *
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

/** Name string macro */
#define BOARD_NAME                "SAMR21G18A_MODULE"

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
#define LED0_PIN                  PIN_PA28
#define LED0_ACTIVE               false
#define LED0_INACTIVE             !LED0_ACTIVE
#define LED0 LED0_PIN
/** @} */


/** \name SW0 definitions
 *  @{ */
#define SW0_PIN                   PIN_PA15
#define SW0_ACTIVE                false
#define SW0_INACTIVE              !SW0_ACTIVE
#define SW0_EIC_PIN               PIN_PA15A_EIC_EXTINT15
#define SW0_EIC_MUX               MUX_PA15A_EIC_EXTINT15
#define SW0_EIC_PINMUX            PINMUX_PA15A_EIC_EXTINT15
#define SW0_EIC_LINE              15
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

//! \name Communication interfaces on header J1
//@{
#define UART0_SERCOM              SERCOM2
#define UART0_SERCOM_MUX_SETTING  USART_RX_3_TX_2_XCK_3
#define UART0_SERCOM_PINMUX_PAD0  PINMUX_UNUSED
#define UART0_SERCOM_PINMUX_PAD1  PINMUX_UNUSED
#define UART0_SERCOM_PINMUX_PAD2  PINMUX_PA14C_SERCOM2_PAD2
#define UART0_SERCOM_PINMUX_PAD3  PINMUX_PA15C_SERCOM2_PAD3
 
//@}

#define UART1_SERCOM              SERCOM0
#define UART1_SERCOM_MUX_SETTING  USART_RX_3_TX_0_XCK_1
#define UART1_SERCOM_PINMUX_PAD0  PINMUX_PA08C_SERCOM0_PAD0
#define UART1_SERCOM_PINMUX_PAD1  PINMUX_UNUSED
#define UART1_SERCOM_PINMUX_PAD2  PINMUX_UNUSED
#define UART1_SERCOM_PINMUX_PAD3  PINMUX_PA07D_SERCOM0_PAD3

#define RF_SPI_MODULE              SERCOM4
#define RF_SPI_SERCOM_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_E
#define RF_SPI_SERCOM_PINMUX_PAD0  PINMUX_PC19F_SERCOM4_PAD0
#define RF_SPI_SERCOM_PINMUX_PAD1  PINMUX_PB31D_SERCOM5_PAD1
#define RF_SPI_SERCOM_PINMUX_PAD2  PINMUX_PB30F_SERCOM4_PAD2
#define RF_SPI_SERCOM_PINMUX_PAD3  PINMUX_PC18F_SERCOM4_PAD3


#define RF_IRQ_MODULE           EIC
#define RF_IRQ_INPUT            0
#define RF_IRQ_PIN              PIN_PB00A_EIC_EXTINT0
#define RF_IRQ_MUX              MUX_PB00A_EIC_EXTINT0
#define RF_IRQ_PINMUX           PINMUX_PB00A_EIC_EXTINT0

/** \name 802.15.4 TRX Interface definitions
 * @{
 */

#define AT86RFX_SPI                  SERCOM4
#define AT86RFX_RST_PIN              PIN_PB15
#define AT86RFX_IRQ_PIN              PIN_PB00
#define AT86RFX_SLP_PIN              PIN_PA20
#define AT86RFX_SPI_CS               PIN_PB31
#define AT86RFX_SPI_MOSI             PIN_PB30
#define AT86RFX_SPI_MISO             PIN_PC19
#define AT86RFX_SPI_SCK              PIN_PC18
#define PIN_RFCTRL3                  PIN_PA13
#define PIN_RFCTRL2                  PIN_PA12
#define RFCTRL_CFG_ANT_DIV           64


#define AT86RFX_SPI_SERCOM_MUX_SETTING   RF_SPI_SERCOM_MUX_SETTING
#define AT86RFX_SPI_SERCOM_PINMUX_PAD0   RF_SPI_SERCOM_PINMUX_PAD0
#define AT86RFX_SPI_SERCOM_PINMUX_PAD1   PINMUX_UNUSED
#define AT86RFX_SPI_SERCOM_PINMUX_PAD2   RF_SPI_SERCOM_PINMUX_PAD2
#define AT86RFX_SPI_SERCOM_PINMUX_PAD3   RF_SPI_SERCOM_PINMUX_PAD3

#define AT86RFX_IRQ_CHAN             RF_IRQ_INPUT
#define AT86RFX_IRQ_PINMUX           RF_IRQ_PINMUX


/** Enables the transceiver main interrupt. */
#define ENABLE_TRX_IRQ()    \
		extint_chan_enable_callback(AT86RFX_IRQ_CHAN, EXTINT_CALLBACK_TYPE_DETECT)

/** Disables the transceiver main interrupt. */
#define DISABLE_TRX_IRQ()   \
		extint_chan_disable_callback(AT86RFX_IRQ_CHAN, EXTINT_CALLBACK_TYPE_DETECT)

/** Clears the transceiver main interrupt. */
#define CLEAR_TRX_IRQ()     \
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

#endif  /* SAMR21G18A_MODULE_H_INCLUDED */
