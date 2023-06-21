/**
 * \file
 *
 * \brief Initialization of memories
 * Specific SAM functions to initialize the memories
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

#include <asf.h>
#include "conf_board.h" /* To get on-board memories configurations */
#include "conf_access.h"
#include "main.h"

#ifdef CONF_BOARD_SMC_PSRAM
static void psram_init(void)
{
	pmc_enable_periph_clk(ID_SMC);
	/* complete SMC configuration between PSRAM and SMC waveforms. */
	smc_set_setup_timing(SMC, 0, SMC_SETUP_NWE_SETUP(0)
			| SMC_SETUP_NCS_WR_SETUP(2)
			| SMC_SETUP_NRD_SETUP(2)
			| SMC_SETUP_NCS_RD_SETUP(2));
	smc_set_pulse_timing(SMC, 0, SMC_PULSE_NWE_PULSE(6)
			| SMC_PULSE_NCS_WR_PULSE(6)
			| SMC_PULSE_NRD_PULSE(6)
			| SMC_PULSE_NCS_RD_PULSE(6));
	smc_set_cycle_timing(SMC, 0, SMC_CYCLE_NWE_CYCLE(8)
			| SMC_CYCLE_NRD_CYCLE(8));
	smc_set_mode(SMC, 0, SMC_MODE_READ_MODE | SMC_MODE_WRITE_MODE
			| SMC_MODE_DBW_BIT_16);
}
#endif

#ifdef CONF_BOARD_SRAM
static void ext_sram_init(void)
{
	pmc_enable_periph_clk(ID_SMC);
	smc_set_setup_timing(SMC, 0, SMC_SETUP_NWE_SETUP(1)
			| SMC_SETUP_NCS_WR_SETUP(1)
			| SMC_SETUP_NRD_SETUP(1)
			| SMC_SETUP_NCS_RD_SETUP(1));
	smc_set_pulse_timing(SMC, 0, SMC_PULSE_NWE_PULSE(6)
			| SMC_PULSE_NCS_WR_PULSE(6)
			| SMC_PULSE_NRD_PULSE(6)
			| SMC_PULSE_NCS_RD_PULSE(6));
	smc_set_cycle_timing(SMC, 0, SMC_CYCLE_NWE_CYCLE(7)
			| SMC_CYCLE_NRD_CYCLE(7));
	smc_set_mode(SMC, 0,
			SMC_MODE_READ_MODE | SMC_MODE_WRITE_MODE 
#if !defined(SAM4S)
			| SMC_MODE_DBW_8_BIT
#endif
			);
	/* Configure LB, enable SRAM access */
	pio_configure_pin(PIN_EBI_NLB, PIN_EBI_NLB_FLAGS);
	/* Pull down LB, enable sram access */
	pio_set_pin_low(PIN_EBI_NLB);
}
#endif

void memories_initialization(void)
{
#ifdef CONF_BOARD_SMC_PSRAM
	psram_init();
#endif
#ifdef CONF_BOARD_SRAM
	ext_sram_init();
#endif
}
