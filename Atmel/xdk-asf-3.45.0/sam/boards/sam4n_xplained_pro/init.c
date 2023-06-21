/**
 * \file
 *
 * \brief SAM4N Xplained Pro board initialization
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
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <board.h>
#include <ioport.h>

/**
 * \addtogroup sam4n_xplained_pro_group
 * @{
 */

/**
 * \brief Set peripheral mode for IOPORT pins.
 * It will configure port mode and disable pin mode (but enable peripheral).
 * \param port IOPORT port to configure
 * \param masks IOPORT pin masks to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 */
#define ioport_set_port_peripheral_mode(port, masks, mode) \
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
#define ioport_set_pin_peripheral_mode(pin, mode) \
	do {\
		ioport_set_pin_mode(pin, mode);\
		ioport_disable_pin(pin);\
	} while (0)
	
void board_init(void)
{
#ifndef CONF_BOARD_KEEP_WATCHDOG_AT_INIT
	/* Disable the watchdog */
	WDT->WDT_MR = WDT_MR_WDDIS;
#endif

	/* Initialize IOPORT */
	ioport_init();

	/* Initialize LED0, turned off */
	ioport_set_pin_dir(LED_0_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED_0_PIN, IOPORT_PIN_LEVEL_HIGH);

	/* Initialize SW0 */
	ioport_set_pin_dir(BUTTON_0_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(BUTTON_0_PIN, IOPORT_MODE_PULLUP);

	/* Initialize EXT3 LED0, LED1 & LED2, turned off */
	ioport_set_pin_level(OLED1_LED1_PIN, !OLED1_LED1_ACTIVE);
	ioport_set_pin_dir(OLED1_LED1_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(OLED1_LED2_PIN, !OLED1_LED2_ACTIVE);
	ioport_set_pin_dir(OLED1_LED2_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(OLED1_LED3_PIN, !OLED1_LED3_ACTIVE);
	ioport_set_pin_dir(OLED1_LED3_PIN, IOPORT_DIR_OUTPUT);

#if defined (CONF_BOARD_UART_CONSOLE)
	/* Configure UART pins */
	ioport_set_port_peripheral_mode(PINS_UART0_PORT, PINS_UART0,
			PINS_UART0_FLAGS);
#endif

#ifdef CONF_BOARD_USART_RXD
	/* Configure USART RXD pin */
	ioport_set_pin_peripheral_mode(PIN_USART1_RXD_IDX,
			PIN_USART1_RXD_FLAGS);
#endif

#ifdef CONF_BOARD_USART_TXD
	/* Configure USART TXD pin */
	ioport_set_pin_peripheral_mode(PIN_USART1_TXD_IDX,
			PIN_USART1_TXD_FLAGS);
#endif

#ifdef CONF_BOARD_USART_SCK
	/* Configure USART synchronous communication SCK pin */
	ioport_set_pin_peripheral_mode(PIN_USART1_SCK_IDX,
			PIN_USART1_SCK_FLAGS);
#endif

#ifdef CONF_BOARD_USART_RTS
	/* Configure USART synchronous communication RST pin */
	ioport_set_pin_peripheral_mode(PIN_USART1_RTS_IDX,
			PIN_USART1_RTS_FLAGS);
#endif

#ifdef CONF_BOARD_ISO7816_RST
	/* Configure ISO7816 card reset pin */
	ioport_set_pin_dir(PIN_ISO7816_RST_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_ISO7816_RST_IDX, IOPORT_PIN_LEVEL_LOW);
#endif

#ifdef CONF_BOARD_ISO7816
	/* Configure ISO7816 interface TXD & SCK pin */
	ioport_set_pin_peripheral_mode(PIN_USART0_TXD_IDX, PIN_USART0_TXD_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_USART0_SCK_IDX, PIN_USART0_SCK_FLAGS);
#endif

#if defined(CONF_BOARD_TWI0) || defined(CONF_BOARD_AT30TSE)
	ioport_set_pin_peripheral_mode(TWI0_DATA_GPIO, TWI0_DATA_FLAGS);
	ioport_set_pin_peripheral_mode(TWI0_CLK_GPIO, TWI0_CLK_FLAGS);
#endif

#ifdef CONF_BOARD_TWI1
	ioport_set_pin_peripheral_mode(TWI1_DATA_GPIO, TWI1_DATA_FLAGS);
	ioport_set_pin_peripheral_mode(TWI1_CLK_GPIO, TWI1_CLK_FLAGS);
#endif

#ifdef CONF_BOARD_TWI2
	ioport_set_pin_peripheral_mode(TWI2_DATA_GPIO, TWI2_DATA_FLAGS);
	ioport_set_pin_peripheral_mode(TWI2_CLK_GPIO, TWI2_CLK_FLAGS);
#endif

#if defined(CONF_BOARD_SPI) || defined(CONF_BOARD_SD_MMC_SPI) || defined(CONF_BOARD_AT45DBX)
	ioport_set_pin_peripheral_mode(SPI_MISO_GPIO, SPI_MISO_FLAGS);
	ioport_set_pin_peripheral_mode(SPI_MOSI_GPIO, SPI_MOSI_FLAGS);
	ioport_set_pin_peripheral_mode(SPI_SPCK_GPIO, SPI_SPCK_FLAGS);

#ifdef CONF_BOARD_SD_MMC_SPI
	/* Setting SD detection pin */
	ioport_set_pin_dir(SD_MMC_0_CD_GPIO, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(SD_MMC_0_CD_GPIO, IOPORT_MODE_PULLUP);
#endif

#ifdef CONF_BOARD_SPI_NPCS0
	ioport_set_pin_peripheral_mode(SPI_NPCS0_GPIO, SPI_NPCS0_FLAGS);
#endif

#ifdef CONF_BOARD_SPI_NPCS1
	ioport_set_pin_peripheral_mode(SPI_NPCS1_GPIO, SPI_NPCS1_FLAGS);
#endif

#ifdef CONF_BOARD_SPI_NPCS2
	ioport_set_pin_peripheral_mode(SPI_NPCS2_GPIO, SPI_NPCS2_FLAGS);
#endif

#endif

#ifdef CONF_BOARD_OLED_UG_2832HSWEG04
	ioport_set_pin_dir(UG_2832HSWEG04_DATA_CMD_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_mode(UG_2832HSWEG04_DATA_CMD_GPIO, IOPORT_MODE_PULLUP);
	ioport_set_pin_dir(UG_2832HSWEG04_RESET_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_mode(UG_2832HSWEG04_RESET_GPIO, IOPORT_MODE_PULLUP);
#endif
}

/** @} */
