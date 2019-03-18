/**
 * \file
 *
 * \brief SAM4S Xplained Pro board initialization
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
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <board.h>
#include <gpio.h>
#include <ioport.h>
#include <wdt.h>

/**
 * \addtogroup sam4s_xplained_pro_group
 * @{
 */

void board_init(void)
{
#ifndef CONF_BOARD_KEEP_WATCHDOG_AT_INIT
	wdt_disable(WDT);
#endif

	/* GPIO has been deprecated, the old code just keeps it for compatibility.
	 * In new designs IOPORT is used instead.
	 * Here IOPORT must be initialized for others to use before setting up IO.
	 */
	ioport_init();

	/* Initialize LED0, turned off */
	ioport_set_pin_level(LED_0_PIN, !LED_0_ACTIVE);
	ioport_set_pin_dir(LED_0_PIN, IOPORT_DIR_OUTPUT);

	/* Initialize SW0 */
	ioport_set_pin_dir(BUTTON_0_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(BUTTON_0_PIN, (BUTTON_0_ACTIVE ?
				IOPORT_MODE_PULLDOWN : IOPORT_MODE_PULLUP));

	/* Initialize EXT3 LED0, LED1 & LED2, turned off */
	ioport_set_pin_level(IO1_LED1_PIN, !IO1_LED1_ACTIVE);
	ioport_set_pin_dir(IO1_LED1_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(IO1_LED2_PIN, !IO1_LED2_ACTIVE);
	ioport_set_pin_dir(IO1_LED2_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(IO1_LED3_PIN, !IO1_LED3_ACTIVE);
	ioport_set_pin_dir(IO1_LED3_PIN, IOPORT_DIR_OUTPUT);

#ifdef CONF_BOARD_UART_CONSOLE
	/* Configure UART pins */
	gpio_configure_group(PINS_UART1_PIO, PINS_UART1, PINS_UART1_FLAGS);
#endif

#ifdef CONF_BOARD_TWI0
	gpio_configure_pin(TWI0_DATA_GPIO, TWI0_DATA_FLAGS);
	gpio_configure_pin(TWI0_CLK_GPIO, TWI0_CLK_FLAGS);
#endif

	/* Configure SPI pins */
#ifdef CONF_BOARD_SPI
	gpio_configure_pin(SPI_MISO_GPIO, SPI_MISO_FLAGS);
	gpio_configure_pin(SPI_MOSI_GPIO, SPI_MOSI_FLAGS);
	gpio_configure_pin(SPI_SPCK_GPIO, SPI_SPCK_FLAGS);

	/**
	 * For NPCS 1, 2, and 3, different PINs can be used to access the same NPCS line.
	 * Depending on the application requirements, the default PIN may not be available.
	 * Hence a different PIN should be selected using the CONF_BOARD_SPI_NPCS_GPIO and
	 * CONF_BOARD_SPI_NPCS_FLAGS macros.
	 */
#ifdef CONF_BOARD_SPI_NPCS0
	gpio_configure_pin(SPI_NPCS0_GPIO, SPI_NPCS0_FLAGS);
#endif

#ifdef CONF_BOARD_SPI_NPCS1
#if defined(CONF_BOARD_SPI_NPCS1_GPIO) && defined(CONF_BOARD_SPI_NPCS1_FLAGS)
	gpio_configure_pin(CONF_BOARD_SPI_NPCS1_GPIO, CONF_BOARD_SPI_NPCS1_FLAGS);
#else
	gpio_configure_pin(SPI_NPCS1_PA9_GPIO, SPI_NPCS1_PA9_FLAGS);
#endif
#endif

#ifdef CONF_BOARD_SPI_NPCS2
#if defined(CONF_BOARD_SPI_NPCS2_GPIO) && defined(CONF_BOARD_SPI_NPCS2_FLAGS)
	gpio_configure_pin(CONF_BOARD_SPI_NPCS2_GPIO, CONF_BOARD_SPI_NPCS2_FLAGS);
#else
	gpio_configure_pin(SPI_NPCS2_PA10_GPIO, SPI_NPCS2_PA10_FLAGS);
#endif
#endif

#ifdef CONF_BOARD_SPI_NPCS3
#if defined(CONF_BOARD_SPI_NPCS3_GPIO) && defined(CONF_BOARD_SPI_NPCS3_FLAGS)
	gpio_configure_pin(CONF_BOARD_SPI_NPCS3_GPIO, CONF_BOARD_SPI_NPCS3_FLAGS);
#else
	gpio_configure_pin(SPI_NPCS3_PA22_GPIO, SPI_NPCS3_PA22_FLAGS);
#endif
#endif
#endif /* CONF_BOARD_SPI */

#ifdef CONF_BOARD_OLED_UG_2832HSWEG04
	gpio_configure_pin(UG_2832HSWEG04_DATA_CMD_GPIO, UG_2832HSWEG04_DATA_CMD_FLAGS);
	gpio_configure_pin(UG_2832HSWEG04_RESET_GPIO, UG_2832HSWEG04_RESET_FLAGS);
#endif

#ifdef CONF_BOARD_SD_MMC_SPI
	gpio_configure_pin(SD_MMC_0_CD_GPIO, SD_MMC_0_CD_FLAGS);
#endif

  if ( BUTTON_0_ACTIVE ) {
		ioport_set_pin_mode(BUTTON_0_PIN, IOPORT_MODE_PULLDOWN);
	}
  else {
		ioport_set_pin_mode(BUTTON_0_PIN, IOPORT_MODE_PULLUP);
  }
  
#ifdef CONF_BOARD_AT86RFX

	gpio_configure_pin(AT86RFX_SPI_MISO, SPI_MISO_FLAGS);
	gpio_configure_pin(AT86RFX_SPI_MOSI, SPI_MOSI_FLAGS);
	gpio_configure_pin(AT86RFX_SPI_SCK,  SPI_SPCK_FLAGS);
    gpio_configure_pin(AT86RFX_SPI_CS_PIN, AT86RFX_SPI_CS_FLAGS);

/* Initialize TRX_RST and SLP_TR as GPIO. */
	ioport_set_pin_dir(AT86RFX_RST_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(AT86RFX_RST_PIN, IOPORT_PIN_LEVEL_HIGH);
	ioport_set_pin_dir(AT86RFX_SLP_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(AT86RFX_SLP_PIN, IOPORT_PIN_LEVEL_HIGH);

#endif  

#ifdef CONF_BOARD_NAND

	gpio_configure_pin(PIN_EBI_NANDOE, PIN_EBI_NANDOE_FLAGS);
	gpio_configure_pin(PIN_EBI_NANDWE, PIN_EBI_NANDWE_FLAGS);
	gpio_configure_pin(PIN_EBI_NANDCLE, PIN_EBI_NANDCLE_FLAGS);
	gpio_configure_pin(PIN_EBI_NANDALE, PIN_EBI_NANDALE_FLAGS);
	gpio_configure_pin(PIN_EBI_NANDIO_0, PIN_EBI_NANDIO_0_FLAGS);
	gpio_configure_pin(PIN_EBI_NANDIO_1, PIN_EBI_NANDIO_1_FLAGS);
	gpio_configure_pin(PIN_EBI_NANDIO_2, PIN_EBI_NANDIO_2_FLAGS);
	gpio_configure_pin(PIN_EBI_NANDIO_3, PIN_EBI_NANDIO_3_FLAGS);
	gpio_configure_pin(PIN_EBI_NANDIO_4, PIN_EBI_NANDIO_4_FLAGS);
	gpio_configure_pin(PIN_EBI_NANDIO_5, PIN_EBI_NANDIO_5_FLAGS);
	gpio_configure_pin(PIN_EBI_NANDIO_6, PIN_EBI_NANDIO_6_FLAGS);
	gpio_configure_pin(PIN_EBI_NANDIO_7, PIN_EBI_NANDIO_7_FLAGS);
	gpio_configure_pin(PIN_NF_CE_IDX, PIN_NF_CE_FLAGS);
	gpio_configure_pin(PIN_NF_RB_IDX, PIN_NF_RB_FLAGS);
	
#endif

#ifdef CONF_BOARD_SD_MMC_HSMCI

/* Configure HSMCI pins */
gpio_configure_pin(PIN_HSMCI_MCCDA_GPIO, PIN_HSMCI_MCCDA_FLAGS);
gpio_configure_pin(PIN_HSMCI_MCCK_GPIO, PIN_HSMCI_MCCK_FLAGS);
gpio_configure_pin(PIN_HSMCI_MCDA0_GPIO, PIN_HSMCI_MCDA0_FLAGS);
gpio_configure_pin(PIN_HSMCI_MCDA1_GPIO, PIN_HSMCI_MCDA1_FLAGS);
gpio_configure_pin(PIN_HSMCI_MCDA2_GPIO, PIN_HSMCI_MCDA2_FLAGS);
gpio_configure_pin(PIN_HSMCI_MCDA3_GPIO, PIN_HSMCI_MCDA3_FLAGS);

/* Configure SD/MMC card detect pin */
gpio_configure_pin(SD_MMC_0_CD_GPIO, SD_MMC_0_CD_FLAGS);

#endif



}

/** @} */
