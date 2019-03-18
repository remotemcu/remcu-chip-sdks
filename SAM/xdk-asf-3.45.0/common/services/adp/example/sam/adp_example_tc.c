/**
 * \file
 *
 * \brief ADP service example TC functions for SAM
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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
#include <asf.h>
#include "adp_example_tc.h"
#include "conf_tc.h"

volatile bool time_out = true;

void TC0_Handler(void)
{
	/* Clear status bit to acknowledge interrupt */
	tc_get_status(CONF_TC_MODULE, 0);

	time_out = true;
}


void adp_example_tc_init(void)
{
	uint32_t ul_div;
	uint32_t ul_tcclks;
	uint32_t ul_sysclk = sysclk_get_cpu_hz();

	/* Configure PMC */
	pmc_enable_periph_clk(CONF_ID_TC);
#if SAMG55
	/* Enable PCK output */
	pmc_disable_pck(PMC_PCK_3);
	pmc_switch_pck_to_sclk(PMC_PCK_3, PMC_PCK_PRES_CLK_1);
	pmc_enable_pck(PMC_PCK_3);
#endif

	/** Configure TC for a 10Hz frequency and trigger on RC compare. */
	tc_find_mck_divisor(10, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk);
	tc_init(CONF_TC_MODULE, 0, ul_tcclks | TC_CMR_CPCTRG);
	tc_write_rc(CONF_TC_MODULE, 0, (ul_sysclk / ul_div) / 10);

	/* Configure and enable interrupt on RC compare */
	NVIC_EnableIRQ((IRQn_Type) CONF_ID_TC);
	tc_enable_interrupt(CONF_TC_MODULE, 0, TC_IER_CPCS);

	tc_start(CONF_TC_MODULE, 0);
}

