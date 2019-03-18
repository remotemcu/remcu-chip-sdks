/**
 * \file
 *
 * \brief Board specific code for low power example.
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

#include "board.h"
#include "pio.h"
#include "pio_handler.h"
#include "pmc.h"
#include "adc.h"
#include "low_power_board.h"

/** IRQ priority for PIO (The lower the value, the greater the priority) */
#define IRQ_PRIOR_PIO    0

/** Clock list from fast RC */
uint32_t g_fastrc_clock_list[][3] = {
	/* MCK,    FastRC,                  Prescaler */
	{125000,   CKGR_MOR_MOSCRCF_4_MHz,  PMC_MCKR_PRES_CLK_32},
	{250000,   CKGR_MOR_MOSCRCF_4_MHz,  PMC_MCKR_PRES_CLK_16},
	{500000,   CKGR_MOR_MOSCRCF_4_MHz,  PMC_MCKR_PRES_CLK_8},
	{1000000,  CKGR_MOR_MOSCRCF_4_MHz,  PMC_MCKR_PRES_CLK_4},
	{2000000,  CKGR_MOR_MOSCRCF_4_MHz,  PMC_MCKR_PRES_CLK_2},
	{4000000,  CKGR_MOR_MOSCRCF_4_MHz,  PMC_MCKR_PRES_CLK_1},
	{8000000,  CKGR_MOR_MOSCRCF_8_MHz,  PMC_MCKR_PRES_CLK_1},
	{12000000, CKGR_MOR_MOSCRCF_12_MHz, PMC_MCKR_PRES_CLK_1}
};

/** Clock list from PLL */
uint32_t g_pll_clock_list[][4] = {
	/* MCK, MUL, DIV, PRES */
	/* MCK = 12000000 * (7+1) / 1 / 4 = 24 MHz */
	{24000000, 7, 1, PMC_MCKR_PRES_CLK_4},
	/* MCK = 12000000 * (7+1) / 1 / 3 = 32 MHz */
	{32000000, 7, 1, PMC_MCKR_PRES_CLK_3},
	/* MCK = 12000000 * (7+1) / 1 / 2 = 48 MHz */
	{48000000, 7, 1, PMC_MCKR_PRES_CLK_2},
	/* MCK = 12000000 * (31+1) / 3 / 2 = 64 MHz */
	{64000000, 31, 3, PMC_MCKR_PRES_CLK_2},
	/* MCK = 12000000 * (13+1) / 1 / 2 = 84 MHz */
	{84000000, 13, 1, PMC_MCKR_PRES_CLK_2},
	/* MCK = 12000000 * (24+1) / 1 / 3 = 100 MHz */
	{100000000, 24, 1, PMC_MCKR_PRES_CLK_3},
	/* MCK = 12000000 * (19+1) / 1 / 2 = 120 MHz */
	{120000000, 19, 1, PMC_MCKR_PRES_CLK_2}
};

/**
 * \brief Initialize SAM4 Xplained Pro board for low power test.
 */
void init_specific_board(void)
{
	/* Configure all PIOs as inputs to save power */
	pio_set_input(PIOA, 0xFFFFFFFF, PIO_PULLUP);
	pio_set_input(PIOB, 0xFFFFFFFF, PIO_PULLUP);
	pio_set_input(PIOC, 0xFFFFFFFF, PIO_PULLUP);

	/* Disable USB Clock */
	//pmc_disable_udpck();

	/* Disable PIO pull-up for PB10(USB_DDM), PB11(USB_DDP) */
	pio_pull_up(PIOB, (0x3 << 10), 0);
	/* Disable PIO pull-up for PC21(USB_CNX) */
	pio_pull_up(PIOC, (0x1 << 21), 0);

	/* Initialize ADC pin as ADC input mode to save power */
	adc_enable_channel(ADC, ADC_CHANNEL_4);

	/* Enable the PMC clocks of push button for wakeup */
	pmc_enable_periph_clk(ID_PIOB);
	pio_handler_set_priority(PIOB, PIOB_IRQn, IRQ_PRIOR_PIO);
}
