/**
 * \file
 *
 * \brief SAMR21ZLL-EK board definition
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

#ifndef SAMR21ZLL_EK_H_INCLUDED
#define SAMR21ZLL_EK_H_INCLUDED

#include <conf_board.h>
#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup group_common_boards
 * \defgroup samr21zll_ek_group SAMR21ZLL-EK board
 *
 * @{
 */

void system_board_init(void);

/**
 * \defgroup samr21zll_ek_features_group Features
 *
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

/** Name string macro */
#define BOARD_NAME                "SAMR21ZLL_EK"

/** \name Resonator definitions
 *  @{ */
#define BOARD_FREQ_SLCK_XTAL      (32768U)
#define BOARD_FREQ_SLCK_BYPASS    (32768U)
#define BOARD_FREQ_MAINCK_XTAL    (16000000)
#define BOARD_FREQ_MAINCK_BYPASS  (16000000)
#define BOARD_MCK                 CHIP_FREQ_CPU_MAX
#define BOARD_OSC_STARTUP_US      15625
/** @} */

/** \name LED0 definitions
 *  @{ */
#define LED0_PIN                  PIN_PA19
#define LED0_ACTIVE               true
#define LED0_INACTIVE             !LED0_ACTIVE
#define LED0 LED0_PIN
/** @} */

/** Number of on-board LEDs */
#define LED_COUNT                 1

/** \name SW0 definitions
 *  @{ */
#define SW0_PIN                   PIN_PB23
#define SW0_ACTIVE                false
#define SW0_INACTIVE              !SW0_ACTIVE
#define SW0_EIC_PIN               PIN_PB23A_EIC_EXTINT7
#define SW0_EIC_MUX               MUX_PB23A_EIC_EXTINT7
#define SW0_EIC_PINMUX            PINMUX_PB23A_EIC_EXTINT7
#define SW0_EIC_LINE              7
/** @} */

/**
 * \name LED #0 definitions
 *
 * Wrapper macros for LED0, to ensure common naming across all Xplained Pro
 * boards.
 *
 *  @{ */
#define LED_0_NAME                "LED0 (red)"
#define LED_0_PIN                 LED0_PIN
#define LED_0_ACTIVE              LED0_ACTIVE
#define LED_0_INACTIVE            LED0_INACTIVE
#define LED0_GPIO                 LED0_PIN

/** @} */


/**
 * \name Button #0 definitions
 *
 * Wrapper macros for SW0, to ensure common naming across all boards.
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


/** \name Extension header #1 pin definitions
 *  @{
 */
#define EXT1_PIN_3                PIN_PA06
#define EXT1_PIN_4                PIN_PA07
#define EXT1_PIN_5                PIN_PA13
#define EXT1_PIN_6                PIN_PA12
#define EXT1_PIN_7                PIN_PA18
#define EXT1_PIN_8                PIN_PA19
#define EXT1_PIN_9                PIN_PA22
#define EXT1_PIN_10               PIN_PA23
#define EXT1_PIN_11               PIN_PA16
#define EXT1_PIN_12               PIN_PA17
#define EXT1_PIN_13               PIN_PA04
#define EXT1_PIN_14               PIN_PA05
#define EXT1_PIN_15               PIN_PB03
#define EXT1_PIN_16               PIN_PB22
#define EXT1_PIN_17               PIN_PB02
#define EXT1_PIN_18               PIN_PB23
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

/** \name Embedded debugger CDC Gateway USART interface definitions
 *  On SAMR21ZLL-EK board, EDBG USART can be selected with jumper, make
 *  sure the jumper select correctly.
 * @{
 */
#define EDBG_CDC_MODULE              SERCOM3
#define EDBG_CDC_SERCOM_MUX_SETTING  USART_RX_1_TX_0_XCK_1
#define EDBG_CDC_SERCOM_PINMUX_PAD0  PINMUX_PA27F_SERCOM3_PAD0
#define EDBG_CDC_SERCOM_PINMUX_PAD1  PINMUX_PA28F_SERCOM3_PAD1
#define EDBG_CDC_SERCOM_PINMUX_PAD2  PINMUX_UNUSED
#define EDBG_CDC_SERCOM_PINMUX_PAD3  PINMUX_UNUSED
#define EDBG_CDC_SERCOM_DMAC_ID_TX   SERCOM3_DMAC_ID_TX
#define EDBG_CDC_SERCOM_DMAC_ID_RX   SERCOM3_DMAC_ID_RX

/** \name LCD Interface definitions
 * @{
 */
#define LCD_SPI_MODULE              SERCOM5
#define LCD_SPI_SERCOM_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_C
#define LCD_SPI_SERCOM_PINMUX_PAD0  PINMUX_PB02D_SERCOM5_PAD0
#define LCD_SPI_SERCOM_PINMUX_PAD1  PINMUX_PB03D_SERCOM5_PAD1
#define LCD_SPI_SERCOM_PINMUX_PAD2  PINMUX_PB22D_SERCOM5_PAD2
#define LCD_SPI_SERCOM_PINMUX_PAD3  PINMUX_UNUSED
#define LCD_DC_PIN                  PIN_PA22
#define LCD_RESET_PIN               PIN_PA23
#define LCD_CS_PIN                  PIN_PB22

/** \name Joystick Interface definitions
 * @{
 */
#define JOYSTICK_ADC_INPUT_PIN     EXT1_PIN_ADC_0

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
#define PIN_RFCTRL1                  PIN_PA09
#define PIN_RFCTRL2                  PIN_PA12
#define RFCTRL_CFG_ANT_DIV           4


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

#endif  /* SAMR21ZLL_EK_H_INCLUDED */
