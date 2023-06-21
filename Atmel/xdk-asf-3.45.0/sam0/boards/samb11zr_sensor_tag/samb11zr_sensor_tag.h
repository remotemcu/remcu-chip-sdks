/**
 * \file
 *
 * \brief SAMB11ZR_SENSOR_TAG board definition
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
#ifndef SAMB11ZR_SENSOR_TAG_H_INCLUDED
#define SAMB11ZR_SENSOR_TAG_H_INCLUDED

#include <conf_board.h>
#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup group_common_boards
 * \defgroup samb11_sensor_tag_group SAM B11 ZR sensor tag board
 *
 * @{
 */

void system_board_init(void);

/** Name string macro */
#define BOARD_NAME                "SAMB11ZR_SENSOR_TAG"

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
#define LED0_PIN                  PIN_LP_GPIO_7
#define LED0_ACTIVE               false
#define LED0_INACTIVE             !LED0_ACTIVE
/** @} */

/** \name SW0 definitions
 *  @{ */
#define SW0_PIN                   0xFF//Not used
#define SW0_ACTIVE                false
#define SW0_INACTIVE              !SW0_ACTIVE    
#define BUTTON_0_PIN              SW0_PIN      
/** @} */

/**
 * \name LED #0 definitions
 *
 * Wrapper macros for LED0, to ensure common naming across all Xplained Pro
 * boards.
 *
 *  @{ */
#define LED_0_NAME                "LED0 (blue)"
#define LED_0_PIN                 LED0_PIN
#define LED_0_ACTIVE              LED0_ACTIVE
#define LED_0_INACTIVE            LED0_INACTIVE
#define LED0_GPIO                 LED0_PIN
#define LED0                      LED0_PIN
/** @} */

/** Number of on-board LEDs */
#define LED_COUNT                 1

/** \name I2C definitions
 *  @{
 */
#define SENSOR_I2C_MODULE          I2C0
#define SENSOR_I2C_PIN_PAD0        PIN_LP_GPIO_8
#define SENSOR_I2C_PIN_PAD1        PIN_LP_GPIO_9
#define SENSOR_I2C_MUX_PAD0        MUX_LP_GPIO_8_I2C0_SDA
#define SENSOR_I2C_MUX_PAD1        MUX_LP_GPIO_9_I2C0_SCL
/** @} */


/** \name I2C definitions
 *  @{
 */
#define CRYPTO_I2C_MODULE          I2C1
#define CRYPTO_I2C_PIN_PAD0        PIN_LP_GPIO_14
#define CRYPTO_I2C_PIN_PAD1        PIN_LP_GPIO_15
#define CRYPTO_I2C_MUX_PAD0        MUX_LP_GPIO_14_I2C1_SDA
#define CRYPTO_I2C_MUX_PAD1        MUX_LP_GPIO_15_I2C1_SCL
/** @} */

/** \name Embedded debugger CDC Gateway USART interface definitions
 * @{
 */
#define EDBG_CDC_MODULE			 UART0
#define EDBG_CDC_PIN_PAD0		 PIN_LP_GPIO_2
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

#endif  /* SAMB11ZR_SENSOR_TAG_H_INCLUDED */
