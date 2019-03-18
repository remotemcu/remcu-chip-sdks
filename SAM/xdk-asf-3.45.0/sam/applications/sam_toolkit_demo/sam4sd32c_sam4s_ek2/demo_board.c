/*****************************************************************************
 *
 * \file
 *
 * \brief SAM4SD32 toolkit demo board functions.
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
 ******************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include "board.h"
#include "pio.h"
#include "pio_handler.h"
#include "demo_board.h"
#include "wdt.h"
#include "gpio.h"
#include "pmc.h"

/** IRQ priority for PIO (The lower the value, the greater the priority) */
#define IRQ_PRIOR_PIO    0

/**
 * \brief Initialize SAM4S_EK board for toolkit demo.
 */
void init_specific_board(void)
{
	/* Disable the watchdog */
	wdt_disable(WDT);

	/* Configure LED pins */
	pio_configure_pin(LED0_GPIO, LED0_FLAGS);
	pio_configure_pin(LED1_GPIO, LED1_FLAGS);

	/* TC TIOA configuration */
	pio_configure_pin(PIN_TC0_TIOA1, PIN_TC0_TIOA1_FLAGS);

	/* ADC Trigger configuration */
	pio_configure_pin(PINS_ADC_TRIG, PINS_ADC_TRIG_FLAG);

	/* Configure Push Button pins */
	pio_configure_pin(GPIO_PUSH_BUTTON_1, GPIO_PUSH_BUTTON_1_FLAGS);
	pio_configure_pin(GPIO_PUSH_BUTTON_2, GPIO_PUSH_BUTTON_2_FLAGS);

	/* Configure UART pins */
	pio_configure_pin_group(PINS_UART0_PIO, PINS_UART0, PINS_UART0_FLAGS);

	/* Configure LCD EBI pins */
	pio_configure_pin(PIN_EBI_DATA_BUS_D0, PIN_EBI_DATA_BUS_FLAGS);
	pio_configure_pin(PIN_EBI_DATA_BUS_D1, PIN_EBI_DATA_BUS_FLAGS);
	pio_configure_pin(PIN_EBI_DATA_BUS_D2, PIN_EBI_DATA_BUS_FLAGS);
	pio_configure_pin(PIN_EBI_DATA_BUS_D3, PIN_EBI_DATA_BUS_FLAGS);
	pio_configure_pin(PIN_EBI_DATA_BUS_D4, PIN_EBI_DATA_BUS_FLAGS);
	pio_configure_pin(PIN_EBI_DATA_BUS_D5, PIN_EBI_DATA_BUS_FLAGS);
	pio_configure_pin(PIN_EBI_DATA_BUS_D6, PIN_EBI_DATA_BUS_FLAGS);
	pio_configure_pin(PIN_EBI_DATA_BUS_D7, PIN_EBI_DATA_BUS_FLAGS);
	pio_configure_pin(PIN_EBI_NRD, PIN_EBI_NRD_FLAGS);
	pio_configure_pin(PIN_EBI_NWE, PIN_EBI_NWE_FLAGS);
	pio_configure_pin(PIN_EBI_NCS1, PIN_EBI_NCS1_FLAGS);
	pio_configure_pin(PIN_EBI_LCD_RS, PIN_EBI_LCD_RS_FLAGS);

	/* Configure Backlight control pin */
	pio_configure_pin(BOARD_AAT31XX_SET_GPIO, BOARD_AAT31XX_SET_FLAGS);

	/* Configure Touchscreen SPI pins */
	pio_configure_pin(BOARD_ADS7843_IRQ_GPIO, BOARD_ADS7843_IRQ_FLAGS);
	pio_configure_pin(BOARD_ADS7843_BUSY_GPIO, BOARD_ADS7843_BUSY_FLAGS);
	pio_configure_pin(SPI_MISO_GPIO, SPI_MISO_FLAGS);
	pio_configure_pin(SPI_MOSI_GPIO, SPI_MOSI_FLAGS);
	pio_configure_pin(SPI_SPCK_GPIO, SPI_SPCK_FLAGS);
	pio_configure_pin(SPI_NPCS0_GPIO, SPI_NPCS0_FLAGS);

	pio_configure_pin(PIN_EBI_NANDOE, PIN_EBI_NANDOE_FLAGS);
	pio_configure_pin(PIN_EBI_NANDWE, PIN_EBI_NANDWE_FLAGS);
	pio_configure_pin(PIN_EBI_NANDCLE, PIN_EBI_NANDCLE_FLAGS);
	pio_configure_pin(PIN_EBI_NANDALE, PIN_EBI_NANDALE_FLAGS);
	pio_configure_pin(PIN_EBI_NANDIO_0, PIN_EBI_NANDIO_0_FLAGS);
	pio_configure_pin(PIN_EBI_NANDIO_1, PIN_EBI_NANDIO_1_FLAGS);
	pio_configure_pin(PIN_EBI_NANDIO_2, PIN_EBI_NANDIO_2_FLAGS);
	pio_configure_pin(PIN_EBI_NANDIO_3, PIN_EBI_NANDIO_3_FLAGS);
	pio_configure_pin(PIN_EBI_NANDIO_4, PIN_EBI_NANDIO_4_FLAGS);
	pio_configure_pin(PIN_EBI_NANDIO_5, PIN_EBI_NANDIO_5_FLAGS);
	pio_configure_pin(PIN_EBI_NANDIO_6, PIN_EBI_NANDIO_6_FLAGS);
	pio_configure_pin(PIN_EBI_NANDIO_7, PIN_EBI_NANDIO_7_FLAGS);
	pio_configure_pin(PIN_NF_CE_IDX, PIN_NF_CE_FLAGS);
	pio_configure_pin(PIN_NF_RB_IDX, PIN_NF_RB_FLAGS);

	/* Enable clocks for push buttons management */
	pmc_enable_periph_clk(ID_PIOA);
	pmc_enable_periph_clk(ID_PIOB);
	pmc_enable_periph_clk(ID_PIOC);

	/* Initializes the PIO interrupt management for touchscreen driver */
	pio_handler_set_priority(PIOA, PIOA_IRQn, IRQ_PRIOR_PIO);
	pio_handler_set_priority(PIOB, PIOB_IRQn, IRQ_PRIOR_PIO);
	pio_handler_set_priority(PIOC, PIOC_IRQn, IRQ_PRIOR_PIO);
}

