/**
 * \file
 *
 * \brief SAM4L-EK Board init.
 *
 * This file contains board initialization function.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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
#include "sam4l_ek.h"
#include "conf_board.h"
#include "ioport.h"
#include "board.h"
#include "wdt_sam4l.h"

/**
 * \addtogroup  sam4l_ek_group
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

	// Initialize IOPORTs
	ioport_init();

	// Put all pins to default state (input & pull-up)
	uint32_t pin;

	for (pin = PIN_PA00; pin <= PIN_PC31; pin ++) {
		// Skip output pins to configure later
		if (pin == LED0_GPIO || pin == LCD_BL_GPIO
#ifdef CONF_BOARD_RS485
		|| pin == RS485_USART_CTS_PIN
#endif
		/* PA02 is not configured as it is driven by hardware
		configuration */
		|| pin == PIN_PA02) {
			continue;
		}
		ioport_set_pin_dir(pin, IOPORT_DIR_INPUT);
		ioport_set_pin_mode(pin, IOPORT_MODE_PULLUP);
	}

	/* Configure the pins connected to LEDs as output and set their
	 * default initial state to high (LEDs off).
	 */
	ioport_set_pin_dir(LED0_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED0_GPIO, LED0_INACTIVE_LEVEL);

#ifdef  CONF_BOARD_EIC
	// Set push button as external interrupt pin
	ioport_set_pin_peripheral_mode(GPIO_PUSH_BUTTON_EIC_PIN,
			GPIO_PUSH_BUTTON_EIC_PIN_MUX);
	ioport_set_pin_peripheral_mode(GPIO_UNIT_TEST_EIC_PIN,
			GPIO_UNIT_TEST_EIC_PIN_MUX);
#else
	// Push button as input: already done, it's the default pin state
#endif

#if (defined CONF_BOARD_BL)
	// Configure LCD backlight
	ioport_set_pin_dir(LCD_BL_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LCD_BL_GPIO, LCD_BL_INACTIVE_LEVEL);
#endif

#if (defined CONF_BOARD_USB_PORT)
	ioport_set_pin_peripheral_mode(PIN_PA25A_USBC_DM, MUX_PA25A_USBC_DM);
	ioport_set_pin_peripheral_mode(PIN_PA26A_USBC_DP, MUX_PA26A_USBC_DP);
# if defined(CONF_BOARD_USB_VBUS_DETECT)
#   if defined(USB_VBUS_EIC)
	ioport_set_pin_peripheral_mode(USB_VBUS_EIC,
			USB_VBUS_EIC_MUX|USB_VBUS_FLAGS);
#   elif defined(USB_VBUS_PIN)
	ioport_set_pin_dir(USB_VBUS_PIN, IOPORT_DIR_INPUT);
#   else
#       warning USB_VBUS pin not defined
#   endif
# endif
# if defined(CONF_BOARD_USB_ID_DETECT)
#   if defined(USB_ID_EIC)
	ioport_set_pin_peripheral_mode(USB_ID_EIC,
			USB_ID_EIC_MUX|USB_ID_FLAGS);
#   elif defined(USB_ID_PIN)
	ioport_set_pin_dir(USB_ID_PIN, IOPORT_DIR_INPUT);
#   else
#       warning USB_ID pin not defined
#   endif
# endif
# if defined(CONF_BOARD_USB_VBUS_CONTROL)
#   if defined(USB_VBOF_PIN)
	ioport_set_pin_dir(USB_VBOF_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(USB_VBOF_PIN, USB_VBOF_INACTIVE_LEVEL);
#   else
#       warning USB_VBOF pin not defined
#   endif
#  if defined(CONF_BOARD_USB_VBUS_ERR_DETECT)
#    if defined(USB_VBERR_EIC)
	ioport_set_pin_peripheral_mode(USB_VBERR_EIC,
			USB_VBERR_EIC_MUX|USB_VBERR_FLAGS);
#    elif defined(USB_VBERR_PIN)
	ioport_set_pin_dir(USB_VBERR_PIN, IOPORT_DIR_INPUT);
#    else
#        warning USB_VBERR pin not defined
#    endif
#  endif
# endif /* !(defined CONF_BOARD_USB_NO_VBUS_CONTROL) */
#endif /* (defined CONF_BOARD_USB_PORT) */

#if defined (CONF_BOARD_COM_PORT)
	ioport_set_pin_peripheral_mode(COM_PORT_RX_PIN, COM_PORT_RX_MUX);
	ioport_set_pin_peripheral_mode(COM_PORT_TX_PIN, COM_PORT_TX_MUX);
#endif

#if defined (CONF_BOARD_BM_USART)
	ioport_set_pin_peripheral_mode(BM_USART_RX_PIN, BM_USART_RX_MUX);
	ioport_set_pin_peripheral_mode(BM_USART_TX_PIN, BM_USART_TX_MUX);
#endif

#ifdef CONF_BOARD_SPI
	ioport_set_pin_peripheral_mode(PIN_PC04A_SPI_MISO, MUX_PC04A_SPI_MISO);
	ioport_set_pin_peripheral_mode(PIN_PC05A_SPI_MOSI, MUX_PC05A_SPI_MOSI);
	ioport_set_pin_peripheral_mode(PIN_PC06A_SPI_SCK, MUX_PC06A_SPI_SCK);

	#ifdef CONF_BOARD_SPI_NPCS0
		ioport_set_pin_peripheral_mode(PIN_PA02B_SPI_NPCS0,
				MUX_PA02B_SPI_NPCS0);
	#endif
	#ifdef CONF_BOARD_SPI_NPCS2
		ioport_set_pin_peripheral_mode(PIN_PC00A_SPI_NPCS2,
				MUX_PC00A_SPI_NPCS2);
	#endif
	#ifdef CONF_BOARD_SPI_NPCS3
		ioport_set_pin_peripheral_mode(PIN_PC01A_SPI_NPCS3,
				MUX_PC01A_SPI_NPCS3);
	#endif

#endif

#ifdef CONF_BOARD_RS485
	ioport_set_pin_peripheral_mode(RS485_USART_RX_PIN, RS485_USART_RX_MUX);
	ioport_set_pin_peripheral_mode(RS485_USART_TX_PIN, RS485_USART_TX_MUX);
	ioport_set_pin_peripheral_mode(RS485_USART_RTS_PIN,
			RS485_USART_RTS_MUX);
	ioport_set_pin_dir(RS485_USART_CTS_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(RS485_USART_CTS_PIN, IOPORT_PIN_LEVEL_LOW);
#endif

#ifdef CONF_BOARD_TWIMS1
	ioport_set_pin_peripheral_mode(TWIMS1_TWI_SCL_PIN, TWIMS1_TWI_SCL_MUX);
	ioport_set_pin_peripheral_mode(TWIMS1_TWI_SDA_PIN, TWIMS1_TWI_SDA_MUX);
#endif

#ifdef CONF_BOARD_USART0
	ioport_set_pin_peripheral_mode(USART0_RX_PIN, USART0_RX_MUX);
	ioport_set_pin_peripheral_mode(USART0_TX_PIN, USART0_TX_MUX);
#endif

#ifdef CONF_BOARD_DACC_VOUT
	ioport_set_pin_peripheral_mode(DACC_VOUT_PIN, DACC_VOUT_MUX);
#endif

#ifdef CONF_BOARD_ACIFC
	ioport_set_pin_peripheral_mode(PIN_PA06E_ACIFC_ACAN0, MUX_PA06E_ACIFC_ACAN0);
	ioport_set_pin_peripheral_mode(PIN_PA07E_ACIFC_ACAP0, MUX_PA07E_ACIFC_ACAP0);
#endif

#ifdef CONF_BOARD_ABDACB_PORT
	ioport_set_pin_peripheral_mode(ABDACB_AUDIO0_PIN, ABDACB_AUDIO0_MUX);
	ioport_set_pin_peripheral_mode(ABDACB_AUDIO1_PIN, ABDACB_AUDIO1_MUX);
#endif
}
/**
 * @}
 */
