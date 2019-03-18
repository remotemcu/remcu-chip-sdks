/**
 * \file
 *
 * \brief SAM4E-XPRO board init.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
#include "ioport.h"

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

/**
 * \brief Set input mode for one single IOPORT pin.
 * It will configure port mode and disable pin mode (but enable peripheral).
 * \param pin IOPORT pin to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 * \param sense Sense for interrupt detection (\ref ioport_sense)
 */
#define ioport_set_pin_input_mode(pin, mode, sense) \
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

	/* Initialize IOPORTs */
	ioport_init();

	/* Configure the pins connected to LED as output and set their
	 * default initial state to high (LED off).
	 */
	ioport_set_pin_dir(LED0_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED0_GPIO, LED0_INACTIVE_LEVEL);

	/* Configure Push Button pins */
	ioport_set_pin_input_mode(GPIO_PUSH_BUTTON_1, GPIO_PUSH_BUTTON_1_FLAGS,
			GPIO_PUSH_BUTTON_1_SENSE);

#ifdef CONF_BOARD_UART_CONSOLE
	/* Configure UART pins */
	ioport_set_port_peripheral_mode(PINS_UART0_PORT, PINS_UART0,
			PINS_UART0_FLAGS);
#endif

#ifdef CONF_BOARD_PWM_LED0
	/* Configure PWM LED0 pin */
	ioport_set_pin_peripheral_mode(PIN_PWM_LED0_GPIO, PIN_PWM_LED0_FLAGS);
#endif

#ifdef CONF_BOARD_CAN
	/* Configure the CAN1 TX and RX pin. */
	ioport_set_pin_peripheral_mode(PIN_CAN1_RX_IDX, PIN_CAN1_RX_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_CAN1_TX_IDX, PIN_CAN1_TX_FLAGS);
	/* Configure the transiver1 RS & EN pins. */
	ioport_set_pin_dir(PIN_CAN1_TR_RS_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(PIN_CAN1_TR_EN_IDX, IOPORT_DIR_OUTPUT);
#endif

#if defined(CONF_BOARD_USB_PORT)
#  if defined(CONF_BOARD_USB_VBUS_DETECT)
	ioport_set_pin_peripheral_mode(USB_VBUS_PIN, USB_VBUS_FLAGS);
#  endif
#endif

#if defined (CONF_BOARD_SD_MMC_HSMCI)
	/* Configure HSMCI pins */
	ioport_set_pin_peripheral_mode(PIN_HSMCI_MCCDA_GPIO, PIN_HSMCI_MCCDA_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_HSMCI_MCCK_GPIO, PIN_HSMCI_MCCK_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_HSMCI_MCDA0_GPIO, PIN_HSMCI_MCDA0_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_HSMCI_MCDA1_GPIO, PIN_HSMCI_MCDA1_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_HSMCI_MCDA2_GPIO, PIN_HSMCI_MCDA2_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_HSMCI_MCDA3_GPIO, PIN_HSMCI_MCDA3_FLAGS);
#endif

#ifdef CONF_BOARD_KSZ8051MNL
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_RXC_IDX,
			PIN_KSZ8051MNL_RXC_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_TXC_IDX,
			PIN_KSZ8051MNL_TXC_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_TXEN_IDX,
			PIN_KSZ8051MNL_TXEN_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_TXD3_IDX,
			PIN_KSZ8051MNL_TXD3_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_TXD2_IDX,
			PIN_KSZ8051MNL_TXD2_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_TXD1_IDX,
			PIN_KSZ8051MNL_TXD1_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_TXD0_IDX,
			PIN_KSZ8051MNL_TXD0_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_RXD3_IDX,
			PIN_KSZ8051MNL_RXD3_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_RXD2_IDX,
			PIN_KSZ8051MNL_RXD2_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_RXD1_IDX,
			PIN_KSZ8051MNL_RXD1_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_RXD0_IDX,
			PIN_KSZ8051MNL_RXD0_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_RXER_IDX,
			PIN_KSZ8051MNL_RXER_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_RXDV_IDX,
			PIN_KSZ8051MNL_RXDV_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_CRS_IDX,
			PIN_KSZ8051MNL_CRS_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_COL_IDX,
			PIN_KSZ8051MNL_COL_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_MDC_IDX,
			PIN_KSZ8051MNL_MDC_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_KSZ8051MNL_MDIO_IDX,
			PIN_KSZ8051MNL_MDIO_FLAGS);
	ioport_set_pin_dir(PIN_KSZ8051MNL_INTRP_IDX, IOPORT_DIR_INPUT);
#endif

#ifdef CONF_BOARD_NAND
	ioport_set_pin_peripheral_mode(PIN_EBI_NANDOE,   PIN_EBI_NANDOE_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_NANDWE,   PIN_EBI_NANDWE_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_NANDCLE,  PIN_EBI_NANDCLE_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_NANDALE,  PIN_EBI_NANDALE_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_NANDIO_0, PIN_EBI_NANDIO_0_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_NANDIO_1, PIN_EBI_NANDIO_1_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_NANDIO_2, PIN_EBI_NANDIO_2_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_NANDIO_3, PIN_EBI_NANDIO_3_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_NANDIO_4, PIN_EBI_NANDIO_4_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_NANDIO_5, PIN_EBI_NANDIO_5_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_NANDIO_6, PIN_EBI_NANDIO_6_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_NANDIO_7, PIN_EBI_NANDIO_7_FLAGS);
	ioport_set_pin_dir(PIN_NF_CE_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(PIN_NF_RB_IDX, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(PIN_NF_RB_IDX, IOPORT_MODE_PULLUP);
#endif

#ifdef CONF_BOARD_SRAM
	ioport_set_pin_peripheral_mode(PIN_EBI_NCS1, PIN_EBI_NCS1_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_NCS3, PIN_EBI_NCS3_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_NRD, PIN_EBI_NRD_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_NWE, PIN_EBI_NWE_FLAGS);

	ioport_set_pin_peripheral_mode(PIN_EBI_DATA_BUS_D0, PIN_EBI_DATA_BUS_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_DATA_BUS_D1, PIN_EBI_DATA_BUS_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_DATA_BUS_D2, PIN_EBI_DATA_BUS_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_DATA_BUS_D3, PIN_EBI_DATA_BUS_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_DATA_BUS_D4, PIN_EBI_DATA_BUS_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_DATA_BUS_D5, PIN_EBI_DATA_BUS_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_DATA_BUS_D6, PIN_EBI_DATA_BUS_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_EBI_DATA_BUS_D7, PIN_EBI_DATA_BUS_FLAGS);

	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A0, PIN_EBI_ADDR_BUS_FLAG1);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A1, PIN_EBI_ADDR_BUS_FLAG1);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A2, PIN_EBI_ADDR_BUS_FLAG1);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A3, PIN_EBI_ADDR_BUS_FLAG1);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A4, PIN_EBI_ADDR_BUS_FLAG1);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A5, PIN_EBI_ADDR_BUS_FLAG1);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A6, PIN_EBI_ADDR_BUS_FLAG1);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A7, PIN_EBI_ADDR_BUS_FLAG1);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A8, PIN_EBI_ADDR_BUS_FLAG1);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A9, PIN_EBI_ADDR_BUS_FLAG1);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A10,
			PIN_EBI_ADDR_BUS_FLAG1);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A11,
			PIN_EBI_ADDR_BUS_FLAG1);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A12,
			PIN_EBI_ADDR_BUS_FLAG1);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A13,
			PIN_EBI_ADDR_BUS_FLAG1);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A14,
			PIN_EBI_ADDR_BUS_FLAG2);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A15,
			PIN_EBI_ADDR_BUS_FLAG2);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A16,
			PIN_EBI_ADDR_BUS_FLAG2);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A17,
			PIN_EBI_ADDR_BUS_FLAG2);
	ioport_set_pin_peripheral_mode(PIN_EBI_ADDR_BUS_A18,
			PIN_EBI_ADDR_BUS_FLAG2);
#endif

#ifdef CONF_BOARD_AT86RFX
	ioport_set_pin_peripheral_mode(AT86RFX_SPI_MISO, SPI_MISO_FLAGS);
	ioport_set_pin_peripheral_mode(AT86RFX_SPI_MOSI, SPI_MOSI_FLAGS);
	ioport_set_pin_peripheral_mode(AT86RFX_SPI_SCK,  SPI_SPCK_FLAGS);
	ioport_set_pin_peripheral_mode(AT86RFX_SPI_CS_PIN, AT86RFX_SPI_CS_FLAGS);

	/* Initialize TRX_RST and SLP_TR as GPIO. */
	ioport_set_pin_dir(AT86RFX_RST_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(AT86RFX_RST_PIN, IOPORT_PIN_LEVEL_HIGH);
	ioport_set_pin_dir(AT86RFX_SLP_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(AT86RFX_SLP_PIN, IOPORT_PIN_LEVEL_HIGH);
#endif  

#if (defined(CONF_BOARD_TWI0) || defined(CONF_BOARD_EDBG_TWI))
	ioport_set_pin_peripheral_mode(TWI0_DATA_GPIO, TWI0_DATA_FLAGS);
	ioport_set_pin_peripheral_mode(TWI0_CLK_GPIO, TWI0_CLK_FLAGS);
#endif

}
