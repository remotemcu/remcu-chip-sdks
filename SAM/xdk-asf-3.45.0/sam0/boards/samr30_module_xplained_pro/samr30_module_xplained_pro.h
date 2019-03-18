/**
 * \file
 *
 * \brief SAM R30 Module Xplained Pro board definition
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

#ifndef SAMR30_MODULE_XPLAINED_PRO_H_INCLUDED
#define SAMR30_MODULE_XPLAINED_PRO_H_INCLUDED

#include <conf_board.h>
#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup group_common_boards
 * \defgroup samr30_xplained_pro_group SAM R30 Xplained Pro board
 *
 * @{
 */

void system_board_init(void);

/**
 * \defgroup samr30_xplained_pro_features_group Features
 *
 * Symbols that describe features and capabilities of the board.
 *
 * @{
 */

/** Name string macro */
#define BOARD_NAME                "SAMR30_MODULE_XPLAINED_PRO"

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
#define LED0_PIN                  PIN_PA14
#define LED0_ACTIVE               false
#define LED0_INACTIVE             !LED0_ACTIVE
/** @} */

/** \name LED1 definitions
 *  @{ */
#define LED1_PIN                  PIN_PA18
#define LED1_ACTIVE               false
#define LED1_INACTIVE             !LED1_ACTIVE
/** @} */

/** \name SW0 definitions
 *  @{ */
#define SW0_PIN                   PIN_PA07
#define SW0_ACTIVE                false
#define SW0_INACTIVE              !SW0_ACTIVE
#define SW0_EIC_PIN               PIN_PA07A_EIC_EXTINT7
#define SW0_EIC_MUX               MUX_PA07A_EIC_EXTINT7
#define SW0_EIC_PINMUX            PINMUX_PA07A_EIC_EXTINT7
#define SW0_EIC_LINE              7
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
#define LED_0_PWM4CTRL_CHANNEL    4
#define LED_0_PWM4CTRL_OUTPUT     4
#define LED_0_PWM4CTRL_PIN        PIN_PA14F_TCC0_WO4
#define LED_0_PWM4CTRL_MUX        MUX_PA14F_TCC0_WO4
#define LED_0_PWM4CTRL_PINMUX     PINMUX_PA14F_TCC0_WO4

/** @} */

/**
 * \name LED #1 definitions
 *
 * Wrapper macros for LED0, to ensure common naming across all Xplained Pro
 * boards.
 *
 *  @{ */
#define LED_1_NAME                "LED1 (Green)"
#define LED_1_PIN                 LED1_PIN
#define LED_1_ACTIVE              LED1_ACTIVE
#define LED_1_INACTIVE            LED1_INACTIVE
#define LED1_GPIO                 LED1_PIN
#define LED1                      LED1_PIN

#define LED_1_PWM2CTRL_MODULE     TCC0
#define LED_1_PWM2CTRL_CHANNEL    2
#define LED_1_PWM2CTRL_OUTPUT     2
#define LED_1_PWM2CTRL_PIN        PIN_PA18F_TCC0_WO2
#define LED_1_PWM2CTRL_MUX        MUX_PA18F_TCC0_WO2
#define LED_1_PWM2CTRL_PINMUX     PINMUX_PA18F_TCC0_WO2

/** @} */

/** Number of on-board LEDs */
#define LED_COUNT                 2


/**
 * \name Serial flash definitions
 *
 * On board Serial flash definitions.
 *
 *  @{ */
#define SERIALFLASH_SPI_MODULE       SERCOM1
#define SERIALFLASH_SPI_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_E
#define SERIALFLASH_SPI_PINMUX_PAD0  PINMUX_PA16C_SERCOM1_PAD0
#define SERIALFLASH_SPI_PINMUX_PAD1  PINMUX_UNUSED
#define SERIALFLASH_SPI_PINMUX_PAD2  PINMUX_PA18C_SERCOM1_PAD2
#define SERIALFLASH_SPI_PINMUX_PAD3  PINMUX_PA19C_SERCOM1_PAD3
#define SERIALFLASH_SPI_CS PIN_PA27
/** @} */

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

/** \name Extension header pin definitions
 *  @{
 */
#define EXT_PIN_3                PIN_PA06
#define EXT_PIN_4                UNUSED
#define EXT_PIN_5                PIN_PA14
#define EXT_PIN_6                UNUSED
#define EXT_PIN_7                UNUSED
#define EXT_PIN_8                UNUSED
#define EXT_PIN_9                PIN_PA06
#define EXT_PIN_10               PIN_PA28
#define EXT_PIN_11               PIN_PA08
#define EXT_PIN_12               PIN_PA09
#define EXT_PIN_13               PIN_PA14
#define EXT_PIN_14               PIN_PA15
#define EXT_PIN_15               PIN_PA17
#define EXT_PIN_16               PIN_PA18
#define EXT_PIN_17               PIN_PA16
#define EXT_PIN_18               PIN_PA19
/** @} */

/** \name Extension header pin definitions by function
 *  @{
 */
#define EXT_PIN_ADC_0            EXT_PIN_3
#define EXT_PIN_ADC_1            EXT_PIN_4
#define EXT_PIN_GPIO_0           EXT_PIN_5
#define EXT_PIN_GPIO_1           EXT_PIN_6
#define EXT_PIN_PWM_0            EXT_PIN_7
#define EXT_PIN_PWM_1            EXT_PIN_8
#define EXT_PIN_IRQ              EXT_PIN_9
#define EXT_PIN_I2C_SDA          EXT_PIN_11
#define EXT_PIN_I2C_SCL          EXT_PIN_12
#define EXT_PIN_UART_RX          EXT_PIN_13
#define EXT_PIN_UART_TX          EXT_PIN_14
#define EXT_PIN_SPI_SS_1         EXT_PIN_10  
#define EXT_PIN_SPI_SS_0         EXT_PIN_15  
#define EXT_PIN_SPI_MOSI         EXT_PIN_16
#define EXT_PIN_SPI_MISO         EXT_PIN_17
#define EXT_PIN_SPI_SCK          EXT_PIN_18
/** @} */

/** \name Extension header ADC definitions
 *  @{
 */
#define EXT_ADC_MODULE           ADC
#define EXT_ADC_6_CHANNEL        6
#define EXT_ADC_6_PIN            PIN_PA06B_ADC_AIN6
#define EXT_ADC_6_MUX            MUX_PA06B_ADC_AIN6
#define EXT_ADC_6_PINMUX         PINMUX_PA06B_ADC_AIN6
/** @} */

/** \name Extension header TC definitions
 *  @{
 */
#define EXT_PWM_MODULE           TC4
#define EXT_PWM_0_CHANNEL        0
#define EXT_PWM_0_PIN            PIN_PA14E_TC4_WO0
#define EXT_PWM_0_MUX            MUX_PA14E_TC4_WO0
#define EXT_PWM_0_PINMUX         PINMUX_PA14E_TC4_WO0
/** @} */



/** \name Extension header IRQ/External interrupt definitions
 *  @{
 */
#define EXT_IRQ_MODULE           EIC
#define EXT_IRQ_INPUT            6
#define EXT_IRQ_PIN              PIN_PA06A_EIC_EXTINT6
#define EXT_IRQ_MUX              MUX_PA06A_EIC_EXTINT6
#define EXT_IRQ_PINMUX           PINMUX_PA06A_EIC_EXTINT6
/** @} */

/** \name Extension header I2C definitions
 *  @{
 */
#define EXT_I2C_MODULE              SERCOM0
#define EXT_I2C_SERCOM_PINMUX_PAD0  PINMUX_PA08C_SERCOM0_PAD0
#define EXT_I2C_SERCOM_PINMUX_PAD1  PINMUX_PA09C_SERCOM0_PAD1
#define EXT_I2C_SERCOM_DMAC_ID_TX   SERCOM0_DMAC_ID_TX
#define EXT_I2C_SERCOM_DMAC_ID_RX   SERCOM0_DMAC_ID_RX
/** @} */

/** \name Extension header UART definitions
 *  @{
 */
#define EXT_UART_MODULE              SERCOM2
#define EXT_UART_SERCOM_MUX_SETTING  USART_RX_3_TX_2_XCK_3
#define EXT_UART_SERCOM_PINMUX_PAD0  PINMUX_UNUSED
#define EXT_UART_SERCOM_PINMUX_PAD1  PINMUX_UNUSED
#define EXT_UART_SERCOM_PINMUX_PAD2  PINMUX_PA14C_SERCOM2_PAD2
#define EXT_UART_SERCOM_PINMUX_PAD3  PINMUX_PA15C_SERCOM2_PAD3
#define EXT_UART_SERCOM_DMAC_ID_TX   SERCOM2_DMAC_ID_TX
#define EXT_UART_SERCOM_DMAC_ID_RX   SERCOM2_DMAC_ID_RX
/** @} */

/** \ Temperature sensor definitions
 *  @{
 */
#define TEMPERATURE_SENSOR_I2C_MODULE              SERCOM0
#define TEMPERATURE_ALERT_IRQ_MODULE               EIC
#define TEMPERATURE_ALERT_IRQ_INPUT                8
#define TEMPERATURE_ALERT_IRQ_PIN                  PIN_PA28A_EIC_EXTINT8
#define TEMPERATURE_ALERT_IRQ_MUX                  MUX_PA28A_EIC_EXTINT8
#define TEMPERATURE_ALERT_IRQ_PINMUX               PINMUX_PA28A_EIC_EXTINT8
#define TEMPERATURE_SENSOR_SDA                     EXT_I2C_SERCOM_PINMUX_PAD0
#define TEMPERATURE_SENSOR_SCL                     EXT_I2C_SERCOM_PINMUX_PAD1
#define TEMPERATURE_SENSOR_I2C_SERCOM_DMAC_ID_TX   SERCOM0_DMAC_ID_TX
#define TEMPERATURE_SENSOR_I2C_SERCOM_DMAC_ID_RX   SERCOM0_DMAC_ID_RX
#define TEMPERATURE_SENSOR_ALERT_PIN               TEMPERATURE_ALERT_IRQ_PINMUX  
/** @} */

/** \name Extension header SPI definitions
 *  @{
 */
#define EXT_SPI_MODULE              SERCOM1
#define EXT_SPI_SERCOM_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_E
#define EXT_SPI_SERCOM_PINMUX_PAD0  PINMUX_PA16C_SERCOM1_PAD0
#define EXT_SPI_SERCOM_PINMUX_PAD1  PINMUX_PA17C_SERCOM1_PAD1
#define EXT_SPI_SERCOM_PINMUX_PAD2  PINMUX_PA18C_SERCOM1_PAD2
#define EXT_SPI_SERCOM_PINMUX_PAD3  PINMUX_PA19C_SERCOM1_PAD3
#define EXT_SPI_SERCOM_DMAC_ID_TX   SERCOM1_DMAC_ID_TX
#define EXT_SPI_SERCOM_DMAC_ID_RX   SERCOM1_DMAC_ID_RX
/** @} */

/** \name Embedded debugger CDC Gateway USART interface definitions
 * @{
 */
#define CDC_MODULE              SERCOM3
#define CDC_SERCOM_MUX_SETTING  USART_RX_3_TX_2_XCK_3
#define CDC_SERCOM_PINMUX_PAD0  PINMUX_UNUSED
#define CDC_SERCOM_PINMUX_PAD1  PINMUX_UNUSED
#define CDC_SERCOM_PINMUX_PAD2  PINMUX_PA24C_SERCOM3_PAD2
#define CDC_SERCOM_PINMUX_PAD3  PINMUX_PA25C_SERCOM3_PAD3
#define CDC_SERCOM_DMAC_ID_TX   SERCOM3_DMAC_ID_TX
#define CDC_SERCOM_DMAC_ID_RX   SERCOM3_DMAC_ID_RX
/** @} */

#define RF_SPI_MODULE              SERCOM4
#define RF_SPI_SERCOM_MUX_SETTING  SPI_SIGNAL_MUX_SETTING_E
#define RF_SPI_SERCOM_PINMUX_PAD0  PINMUX_PC19F_SERCOM4_PAD0
#define RF_SPI_SERCOM_PINMUX_PAD1  PINMUX_PB31F_SERCOM4_PAD1
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

#define AT86RFX_IRQ_CHAN       RF_IRQ_INPUT
#define AT86RFX_IRQ_PINMUX     RF_IRQ_PINMUX


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

#endif  /* SAMR30_MODULE_XPLAINED_PRO_H_INCLUDED */
