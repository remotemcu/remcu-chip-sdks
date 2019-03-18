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
#include "low_power_board.h"

/** IRQ priority for PIO (The lower the value, the greater the priority) */
#define IRQ_PRIORITY_PIO    0

/** Clock list from fast RC */
uint32_t g_fastrc_clock_list[][3] = {
	/* MCK,    FastRC,                  Prescaler */
	{250000, CKGR_MOR_MOSCRCF_8_MHz, PMC_MCKR_PRES_CLK_32},
	{500000, CKGR_MOR_MOSCRCF_8_MHz, PMC_MCKR_PRES_CLK_16},
	{1000000, CKGR_MOR_MOSCRCF_8_MHz, PMC_MCKR_PRES_CLK_8},
	{2000000, CKGR_MOR_MOSCRCF_8_MHz, PMC_MCKR_PRES_CLK_4},
	{4000000, CKGR_MOR_MOSCRCF_8_MHz, PMC_MCKR_PRES_CLK_2},
	{8000000, CKGR_MOR_MOSCRCF_8_MHz, PMC_MCKR_PRES_CLK_1},
	{16000000, CKGR_MOR_MOSCRCF_16_MHz, PMC_MCKR_PRES_CLK_1},
	{24000000, CKGR_MOR_MOSCRCF_24_MHz, PMC_MCKR_PRES_CLK_1}
};

/** Clock list from PLL */
uint32_t g_pll_clock_list[][4] = {
	/* MCK, MUL, DIV, PRES */
	/* MCK = 32000 * (999+1) / 1 / 1 = 32 MHz */
	{32000000, 999, 1, PMC_MCKR_PRES_CLK_1},
	/* MCK = 32000 * (1499+1) / 1 / 1 = 48 MHz */
	{48000000, 1499, 1, PMC_MCKR_PRES_CLK_1},
};

/**
 * \brief Configures SAMG53 for low power demo.
 */
void init_specific_board(void)
{
	/* For the lowest power consumption all pins should have defined state
	 * e.g. no floating pins.
	 * Set all pins as input with pull-up enabled with the exception:
	 * - CDC UART RX (PA09) should not be pulled up because this pin is
	 *   driven by the EDBG in this application
	 * - CDC UART TX (PA10) This is actively driven by the SAMG53 in this
	 *   application
	 */
	pio_set_input(PIOA, 0xFFFFF9FF, PIO_PULLUP);
	pio_set_input(PIOA, 0x00000600, PIO_DEFAULT);
	pio_set_input(PIOB, 0xFFFFFFFF, PIO_PULLUP);

	/* Enable the PMC clocks of push button for wakeup */
	pmc_enable_periph_clk(ID_PIOA);
	pio_handler_set_priority(PIOA, PIOA_IRQn, IRQ_PRIORITY_PIO);
}
