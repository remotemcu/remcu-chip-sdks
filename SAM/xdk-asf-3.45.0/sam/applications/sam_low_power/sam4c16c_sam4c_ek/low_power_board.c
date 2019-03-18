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
#include <rstc.h>
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
	/* MCK = 8000000 * (11+1) / 1 / 4 = 24 MHz */
	{24000000, 11, 1, PMC_MCKR_PRES_CLK_4},
	/* MCK = 8000000 * (11+1) / 1 / 3 = 32 MHz */
	{32000000, 11, 1, PMC_MCKR_PRES_CLK_3},
	/* MCK = 8000000 * (11+1) / 1 / 2 = 48 MHz */
	{48000000, 11, 1, PMC_MCKR_PRES_CLK_2},
	/* MCK = 8000000 * (15+1) / 1 / 2 = 64 MHz */
	{64000000, 15, 1, PMC_MCKR_PRES_CLK_2},
	/* MCK = 8000000 * (20+1) / 2 / 1 = 84 MHz */
	{84000000, 20, 2, PMC_MCKR_PRES_CLK_1},
	/* MCK = 8000000 * (24+1) / 2 / 1 = 100 MHz */
	{100000000, 24, 2, PMC_MCKR_PRES_CLK_1},
	/* MCK = 8000000 * (29+1) / 2 / 1 = 120 MHz */
	{120000000, 29, 2, PMC_MCKR_PRES_CLK_1}
};

/**
 * \brief Initialize SAM4C_EK board for low power test.
 */
void init_specific_board(void)
{
	/* Configure all PIOs as inputs to save power */
	pio_set_input(PIOA, 0xFFFFFFFF, PIO_PULLUP);
	pio_set_input(PIOB, 0xFFFFFFFF, PIO_PULLUP);

	/* Enable the PMC clocks of push button for wakeup */
	pmc_enable_periph_clk(ID_PIOA);
	pio_handler_set_priority(PIOA, PIOA_IRQn, IRQ_PRIOR_PIO);
}
