/**
 * \file
 *
 * \brief SAM4CP16BMB board init.
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

#include "compiler.h"
#include "board.h"
#include "conf_board.h"
#include "conf_clock.h"
#include "asf.h"

/**
 * \addtogroup sam4cp16bmb_group
 * @{
 */

/**
 * \brief Set peripheral mode for IOPORT pins.
 * It will configure port mode and disable pin mode (but enable peripheral).
 * \param port IOPORT port to configure
 * \param masks IOPORT pin masks to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 */
#define ioport_set_port_peripheral_mode(port, masks, mode)\
	do {\
		ioport_set_port_mode(port, masks, mode);\
		ioport_disable_port(port, masks);\
	} while (0)

/**
 * \brief Set peripheral mode for one single IOPORT pin.
 * It will configure port mode and disable pin mode (but enable peripheral).
 * \param pin IOPORT pin to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 */
#define ioport_set_pin_peripheral_mode(pin, mode)\
	do {\
		ioport_set_pin_mode(pin, mode);\
		ioport_disable_pin(pin);\
	} while (0)

/**
 * \brief Set input mode for one single IOPORT pin.
 * It will configure port mode and disable pin mode (but enable peripheral).
 * \param pin IOPORT pin to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 * \param sense Sense for interrupt detection (\ref ioport_sense)
 */
#define ioport_set_pin_input_mode(pin, mode, sense)\
	do {\
		ioport_set_pin_dir(pin, IOPORT_DIR_INPUT);\
		ioport_set_pin_mode(pin, mode);\
		ioport_set_pin_sense_mode(pin, sense);\
	} while (0)

void board_init(void)
{
#ifndef CONF_BOARD_KEEP_WATCHDOG_AT_INIT
	/* Disable the watchdog */
	WDT->WDT_MR = WDT_MR_WDDIS;
#endif

#ifdef CONF_BOARD_32K_XTAL
	/* Select the crystal oscillator to be the source of the slow clock,
	 * as it provides a more accurate frequency
	*/
	supc_switch_sclk_to_32kxtal(SUPC, 0);
#endif

	/* GPIO has been deprecated, the old code just keeps it for compatibility.
	 * In new designs IOPORT is used instead.
	 * Here IOPORT must be initialized for others to use before setting up IO.
	 */
	ioport_init();

#ifdef CONFIG_CPCLK_ENABLE
	/* Configure the pins connected to LEDs as output and set their
	 * default initial state to high (LEDs off).
	 */
	ioport_set_pin_dir(LED0_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED0_GPIO, LED0_INACTIVE_LEVEL);
	ioport_set_pin_dir(LED1_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED1_GPIO, LED0_INACTIVE_LEVEL);
#else
#warning Please enable CONFIG_CPCLK_ENABLE in conf_clock.h to use LEDs (PIOC).
#endif

	/* Configure UART0 pins */
#ifdef CONF_BOARD_UART0
	ioport_set_port_peripheral_mode(PINS_UART0_PORT, PINS_UART0, PINS_UART0_FLAGS);
#endif

	/* Configure UART1 pins (CONSOLE) */
#if defined(CONF_BOARD_UART1) || defined(CONF_BOARD_UART_CONSOLE)
	ioport_set_port_peripheral_mode(PINS_UART1_PORT, PINS_UART1, PINS_UART1_FLAGS);
#endif

	/* Configure LCD enable */
#ifdef CONF_BOARD_LCD_EN
	ioport_set_pin_dir(LCD_EN_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LCD_EN_GPIO, LCD_EN_ACTIVE_LEVEL);
	ioport_set_pin_dir(LCD_BL_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LCD_BL_GPIO, LCD_BL_ACTIVE_LEVEL);
#else
	ioport_set_pin_dir(LCD_EN_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LCD_EN_GPIO, LCD_EN_INACTIVE_LEVEL);
	ioport_set_pin_dir(LCD_BL_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LCD_BL_GPIO, LCD_BL_INACTIVE_LEVEL);
#endif

	/* Configure SPI pins */
#ifdef CONF_BOARD_SPI0
	ioport_set_pin_peripheral_mode(SPI0_MISO_GPIO, SPI0_MISO_FLAGS);
	ioport_set_pin_peripheral_mode(SPI0_MOSI_GPIO, SPI0_MOSI_FLAGS);
	ioport_set_pin_peripheral_mode(SPI0_SPCK_GPIO, SPI0_SPCK_FLAGS);
	ioport_set_pin_peripheral_mode(SPI0_NPCS0_GPIO, SPI0_NPCS0_FLAGS);
#endif

#ifdef CONF_BOARD_SPI1
	ioport_set_pin_peripheral_mode(SPI1_MISO_GPIO, SPI1_MISO_FLAGS);
	ioport_set_pin_peripheral_mode(SPI1_MOSI_GPIO, SPI1_MOSI_FLAGS);
	ioport_set_pin_peripheral_mode(SPI1_SPCK_GPIO, SPI1_SPCK_FLAGS);
	ioport_set_pin_peripheral_mode(SPI1_NPCS0_GPIO, SPI1_NPCS0_FLAGS);
#else
	ioport_set_pin_dir(SPI1_MISO_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(SPI1_MISO_GPIO, IOPORT_PIN_LEVEL_LOW);
	ioport_set_pin_dir(SPI1_MOSI_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(SPI1_MOSI_GPIO, IOPORT_PIN_LEVEL_LOW);
	ioport_set_pin_dir(SPI1_SPCK_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(SPI1_SPCK_GPIO, IOPORT_PIN_LEVEL_LOW);
	ioport_set_pin_dir(SPI1_NPCS0_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(SPI1_NPCS0_GPIO, IOPORT_PIN_LEVEL_LOW);
#endif

	/* Configure TWI pins */
#ifdef CONF_BOARD_TWI0
	ioport_set_pin_peripheral_mode(TWIO_DATA_GPIO, TWIO_DATA_FLAG);
	ioport_set_pin_peripheral_mode(TWIO_CLK_GPIO, TWIO_CLK_FLAG);
#endif

	/* Configure USART0 pins */
#ifdef CONF_BOARD_USART0_RXD
	/* Configure USART0 RXD pin */
	ioport_set_pin_peripheral_mode(PIN_USART0_RXD_IDX,
			PIN_USART0_RXD_FLAGS);
#endif

#ifdef CONF_BOARD_USART0_TXD
	/* Configure USART0 TXD pin */
	ioport_set_pin_peripheral_mode(PIN_USART0_TXD_IDX,
			PIN_USART0_TXD_FLAGS);
#endif

#ifdef CONF_BOARD_USART0_CTS
	/* Configure USART0 CTS pin */
	ioport_set_pin_peripheral_mode(PIN_USART0_CTS_IDX,
			PIN_USART0_CTS_FLAGS);
#endif

#ifdef CONF_BOARD_USART0_RTS
	/* Configure USART0 RTS pin */
	ioport_set_pin_peripheral_mode(PIN_USART0_RTS_IDX,
			PIN_USART0_RTS_FLAGS);
#endif
	/* Configure USART1 pins */
#ifdef CONF_BOARD_USART1_RXD
	/* Configure USART1 RXD pin */
	ioport_set_pin_peripheral_mode(PIN_USART1_RXD_IDX,
			PIN_USART1_RXD_FLAGS);
#endif

#ifdef CONF_BOARD_USART1_TXD
	/* Configure USART1 TXD pin */
	ioport_set_pin_peripheral_mode(PIN_USART1_TXD_IDX,
			PIN_USART1_TXD_FLAGS);
#endif

#ifdef CONF_BOARD_USART1_CTS
	/* Configure USART1 CTS pin */
	ioport_set_pin_peripheral_mode(PIN_USART1_CTS_IDX,
			PIN_USART1_CTS_FLAGS);
#endif

#ifdef CONF_BOARD_USART1_RTS
	/* Configure USART1 RTS pin */
	ioport_set_pin_peripheral_mode(PIN_USART1_RTS_IDX,
			PIN_USART1_RTS_FLAGS);
#endif

	/* Configure Xplain PRO SLP pin */
#ifdef CONF_BOARD_XP_SLP
	ioport_set_pin_dir(XP_SLP_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(XP_SLP_GPIO, XP_SLP_INACTIVE_LEVEL);
#else
	ioport_set_pin_dir(XP_SLP_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(XP_SLP_GPIO, IOPORT_PIN_LEVEL_LOW);
#endif

}

/* @} */
