/**
 * \file
 *
 * \brief SAMG53 Xplained Pro board initialization
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

#include <compiler.h>
#include <board.h>
#include <conf_board.h>
#include <ioport.h>

/**
 * \addtogroup samg53_xplained_pro_group
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

#if defined(__GNUC__)
void board_init(void) WEAK __attribute__((alias("system_board_init")));
#elif defined(__ICCARM__)
void board_init(void);
#  pragma weak board_init=system_board_init
#endif

void system_board_init(void)
{

#ifndef CONF_BOARD_KEEP_WATCHDOG_AT_INIT
	WDT->WDT_MR = WDT_MR_WDDIS;
#endif
	ioport_init();

	/* Initialize LED0, turned off */
	ioport_set_pin_dir(LED_0_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED_0_PIN, IOPORT_PIN_LEVEL_HIGH);

	/* Initialize SW0 */
	ioport_set_pin_dir(BUTTON_0_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(BUTTON_0_PIN, IOPORT_MODE_PULLUP);

#if defined (CONF_BOARD_UART_CONSOLE)
	/* Configure UART pins */
	ioport_set_port_peripheral_mode(PINS_UART0_PORT, PINS_UART0,
			PINS_UART0_FLAGS);
#endif

#ifdef CONF_BOARD_USART_RXD
	/* Configure USART RXD pin */
	ioport_set_pin_peripheral_mode(EXT1_PIN_UART_RX,
			IOPORT_MODE_MUX_A);
#endif

#ifdef CONF_BOARD_USART_TXD
	/* Configure USART TXD pin */
	ioport_set_pin_peripheral_mode(EXT1_PIN_UART_TX,
			IOPORT_MODE_MUX_A);
#endif

#ifdef CONF_BOARD_USART_SCK
	/* Configure USART synchronous communication SCK pin */
	ioport_set_pin_peripheral_mode(EXT3_PIN_10,
			IOPORT_MODE_MUX_B);
#endif

#if defined(CONF_BOARD_SPI) || defined(CONF_BOARD_SD_MMC_SPI)
	ioport_set_pin_peripheral_mode(SPI_MISO_GPIO, SPI_MISO_FLAGS);
	ioport_set_pin_peripheral_mode(SPI_MOSI_GPIO, SPI_MOSI_FLAGS);
	ioport_set_pin_peripheral_mode(SPI_SPCK_GPIO, SPI_SPCK_FLAGS);

#ifdef CONF_BOARD_SPI_NPCS0
	ioport_set_pin_peripheral_mode(SPI_NPCS0_GPIO, SPI_NPCS0_FLAGS);
#endif

#ifdef CONF_BOARD_SPI_NPCS1
	ioport_set_pin_peripheral_mode(SPI_NPCS1_GPIO, SPI_NPCS1_FLAGS);
#endif
#endif

#ifdef CONF_BOARD_TWI0
	ioport_set_pin_peripheral_mode(TWI0_DATA_GPIO, TWI0_DATA_FLAGS);
	ioport_set_pin_peripheral_mode(TWI0_CLK_GPIO, TWI0_CLK_FLAGS);
#endif

#ifdef CONF_BOARD_TWI1
	ioport_set_pin_peripheral_mode(TWI1_DATA_GPIO, TWI1_DATA_FLAGS);
	ioport_set_pin_peripheral_mode(TWI1_CLK_GPIO, TWI1_CLK_FLAGS);
#endif

#if defined(CONF_BOARD_TWI2) || defined(CONF_BOARD_AT30TSE)
	ioport_set_pin_peripheral_mode(TWI2_DATA_GPIO, TWI2_DATA_FLAGS);
	ioport_set_pin_peripheral_mode(TWI2_CLK_GPIO, TWI2_CLK_FLAGS);
#endif

#ifdef CONF_BOARD_I2S0
	ioport_set_pin_peripheral_mode(I2S0_SCK_GPIO, I2S0_SCK_FLAGS);
	ioport_set_pin_peripheral_mode(I2S0_MCK_GPIO, I2S0_MCK_FLAGS);
	ioport_set_pin_peripheral_mode(I2S0_SDI_GPIO, I2S0_SDI_FLAGS);
	ioport_set_pin_peripheral_mode(I2S0_SDO_GPIO, I2S0_SDO_FLAGS);
	ioport_set_pin_peripheral_mode(I2S0_WS_GPIO, I2S0_WS_FLAGS);
#endif

#ifdef CONF_BOARD_I2S1
	ioport_set_pin_peripheral_mode(I2S1_SCK_GPIO, I2S1_SCK_FLAGS);
	ioport_set_pin_peripheral_mode(I2S1_MCK_GPIO, I2S1_MCK_FLAGS);
	ioport_set_pin_peripheral_mode(I2S1_SDI_GPIO, I2S1_SDI_FLAGS);
	ioport_set_pin_peripheral_mode(I2S1_SDO_GPIO, I2S1_SDO_FLAGS);
	ioport_set_pin_peripheral_mode(I2S1_WS_GPIO, I2S1_WS_FLAGS);
#endif

#ifdef CONF_BOARD_PDM
ioport_set_pin_peripheral_mode(PDM_CLK_GPIO, PDM_CLK_FLAGS);
ioport_set_pin_peripheral_mode(PDM_DAT_GPIO, PDM_DAT_FLAGS);
#endif
}

/** @} */
