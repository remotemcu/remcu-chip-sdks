/**
 * \file
 *
 * \brief SAM4L8 Xplained Pro board initialization
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
#include <wdt_sam4l.h>

/**
 * \addtogroup sam4l8_xplained_pro_group
 * @{
 */

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
	struct wdt_dev_inst wdt_inst;
	struct wdt_config   wdt_cfg;

	wdt_get_config_defaults(&wdt_cfg);
	wdt_init(&wdt_inst, WDT, &wdt_cfg);
	wdt_disable(&wdt_inst);
#endif

	/* Initialize IOPORT */
	ioport_init();

	/* Initialize LED0, turned off */
	ioport_set_pin_dir(LED_0_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED_0_PIN, IOPORT_PIN_LEVEL_HIGH);

	/* Initialize SW0 */
	ioport_set_pin_dir(BUTTON_0_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(BUTTON_0_PIN, IOPORT_MODE_PULLUP);

#ifdef CONF_BOARD_EIC
	/* Set push button as external interrupt pin */
	ioport_set_pin_peripheral_mode(BUTTON_0_EIC_PIN,
			BUTTON_0_EIC_PIN_MUX | IOPORT_MODE_PULLUP);
#else
	/* Push button as input: already done, it's the default pin state */
#endif

#if defined (CONF_BOARD_COM_PORT)
	ioport_set_pin_peripheral_mode(COM_PORT_RX_PIN, COM_PORT_RX_MUX);
	ioport_set_pin_peripheral_mode(COM_PORT_TX_PIN, COM_PORT_TX_MUX);
#endif

#ifdef CONF_BOARD_TWIMS0
	ioport_set_pin_peripheral_mode(PIN_PA23B_TWIMS0_TWD,
			MUX_PA23B_TWIMS0_TWD);
	ioport_set_pin_peripheral_mode(PIN_PA24B_TWIMS0_TWCK,
			MUX_PA24B_TWIMS0_TWCK);
#endif

#ifdef CONF_BOARD_TWIMS3
	ioport_set_pin_peripheral_mode(PIN_PB14C_TWIMS3_TWD,
			MUX_PB14C_TWIMS3_TWD);
	ioport_set_pin_peripheral_mode(PIN_PB15C_TWIMS3_TWCK,
			MUX_PB15C_TWIMS3_TWCK);
#endif

#ifdef CONF_BOARD_USART0
	ioport_set_pin_peripheral_mode(EXT1_PIN_UART_RX, EXT1_UART_RX_MUX);
	ioport_set_pin_peripheral_mode(EXT1_PIN_UART_TX, EXT1_UART_TX_MUX);
#endif

#if (defined CONF_BOARD_USB_PORT)
	ioport_set_pin_peripheral_mode(PIN_PA25A_USBC_DM, MUX_PA25A_USBC_DM);
	ioport_set_pin_peripheral_mode(PIN_PA26A_USBC_DP, MUX_PA26A_USBC_DP);
# if defined(CONF_BOARD_USB_VBUS_DETECT)
	ioport_set_pin_dir(USB_VBUS_PIN, IOPORT_DIR_INPUT);
# endif
# if defined(CONF_BOARD_USB_ID_DETECT)
	ioport_set_pin_dir(USB_ID_PIN, IOPORT_DIR_INPUT);
# endif
# if defined(CONF_BOARD_USB_VBUS_CONTROL)
	ioport_set_pin_dir(USB_VBOF_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(USB_VBOF_PIN, USB_VBOF_INACTIVE_LEVEL);
# endif
#endif

#ifdef CONF_BOARD_AT86RFX
	ioport_set_pin_peripheral_mode(AT86RFX_SPI_MISO, MUX_PA21A_SPI_MISO);
	ioport_set_pin_peripheral_mode(AT86RFX_SPI_MOSI, MUX_PA22A_SPI_MOSI);
	ioport_set_pin_peripheral_mode(AT86RFX_SPI_SCK, MUX_PC30B_SPI_SCK);

	ioport_set_pin_peripheral_mode(EXT1_PIN_15, MUX_PC03A_SPI_NPCS0);

	/* Initialize TRX_RST and SLP_TR as GPIO. */
	ioport_set_pin_dir(AT86RFX_RST_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(AT86RFX_RST_PIN, IOPORT_PIN_LEVEL_HIGH);
	ioport_set_pin_dir(AT86RFX_SLP_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(AT86RFX_SLP_PIN, IOPORT_PIN_LEVEL_HIGH);
#endif

#if defined(CONF_BOARD_SPI) || defined(CONF_BOARD_SD_MMC_SPI)
	ioport_set_pin_peripheral_mode(PIN_PA21A_SPI_MISO, MUX_PA21A_SPI_MISO);
	ioport_set_pin_peripheral_mode(PIN_PA22A_SPI_MOSI, MUX_PA22A_SPI_MOSI);
	ioport_set_pin_peripheral_mode(PIN_PC30B_SPI_SCK, MUX_PC30B_SPI_SCK);

	#ifdef CONF_BOARD_SD_MMC_SPI
		/* Setting SD detection pin */
		ioport_set_pin_dir(SD_MMC_0_CD_GPIO, IOPORT_DIR_INPUT);
		ioport_set_pin_mode(SD_MMC_0_CD_GPIO, IOPORT_MODE_PULLUP);

		/* Setting SD CS pin */
		ioport_set_pin_peripheral_mode(SPI_NPCS0_GPIO, SPI_NPCS0_FLAGS);
	#endif
	#ifdef CONF_BOARD_SPI_NPCS0
		ioport_set_pin_peripheral_mode(PIN_PC03A_SPI_NPCS0,
				MUX_PC03A_SPI_NPCS0);
	#endif
	#ifdef CONF_BOARD_SPI_NPCS1
		ioport_set_pin_peripheral_mode(PIN_PB13B_SPI_NPCS1,
				MUX_PB13B_SPI_NPCS1);
	#endif
	#ifdef CONF_BOARD_SPI_NPCS2
		ioport_set_pin_peripheral_mode(PIN_PB11B_SPI_NPCS2,
				MUX_PB11B_SPI_NPCS2);
	#endif
#endif

#ifdef CONF_BOARD_DACC_VOUT
	ioport_set_pin_peripheral_mode(DACC_VOUT_PIN, DACC_VOUT_MUX);
#endif

#ifdef CONF_BOARD_ACIFC
	ioport_set_pin_peripheral_mode(PIN_PA06E_ACIFC_ACAN0, MUX_PA06E_ACIFC_ACAN0);
	ioport_set_pin_peripheral_mode(PIN_PA07E_ACIFC_ACAP0, MUX_PA07E_ACIFC_ACAP0);
#endif

#ifdef CONF_BOARD_PARC
	ioport_set_pin_peripheral_mode(PIN_PA17D_PARC_PCCK, MUX_PA17D_PARC_PCCK);
	ioport_set_pin_peripheral_mode(PIN_PA09D_PARC_PCDATA0, MUX_PA09D_PARC_PCDATA0);
	ioport_set_pin_peripheral_mode(PIN_PA10D_PARC_PCDATA1, MUX_PA10D_PARC_PCDATA1);
	ioport_set_pin_peripheral_mode(PIN_PA11D_PARC_PCDATA2, MUX_PA11D_PARC_PCDATA2);
	ioport_set_pin_peripheral_mode(PIN_PA12D_PARC_PCDATA3, MUX_PA12D_PARC_PCDATA3);
	ioport_set_pin_peripheral_mode(PIN_PA13D_PARC_PCDATA4, MUX_PA13D_PARC_PCDATA4);
	ioport_set_pin_peripheral_mode(PIN_PA14D_PARC_PCDATA5, MUX_PA14D_PARC_PCDATA5);
	ioport_set_pin_peripheral_mode(PIN_PA15D_PARC_PCDATA6, MUX_PA15D_PARC_PCDATA6);
	ioport_set_pin_peripheral_mode(PIN_PA16D_PARC_PCDATA7, MUX_PA16D_PARC_PCDATA7);
	ioport_set_pin_peripheral_mode(PIN_PA18D_PARC_PCEN1, MUX_PA18D_PARC_PCEN1);
	ioport_set_pin_peripheral_mode(PIN_PA19D_PARC_PCEN2, MUX_PA19D_PARC_PCEN2);
#endif

#ifdef CONF_BOARD_OLED_UG_2832HSWEG04
	ioport_set_pin_dir(UG_2832HSWEG04_DATA_CMD_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_mode(UG_2832HSWEG04_DATA_CMD_GPIO, IOPORT_MODE_PULLUP);
	ioport_set_pin_dir(UG_2832HSWEG04_RESET_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_mode(UG_2832HSWEG04_RESET_GPIO, IOPORT_MODE_PULLUP);
#endif
}

/** @} */
