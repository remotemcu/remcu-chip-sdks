/**
 * \file
 *
 * \brief MT48LC16M16A2 configuration.
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

#ifndef MT48LC16M16A2_H_INCLUDED
#define MT48LC16M16A2_H_INCLUDED

#include "compiler.h"
#include "sdramc.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \defgroup group_sam_components_memory_sdram_mt48lc16m16a2 SDRAM MT48LC16M16A2
 *
 * This is a configuration for the MT48LC16M16A2 SDRAM from Micron.
 * This configuration will be used by the SDRAM driver to set up the
 * MT48LC16M16A2 device.
 *
 * \{
 */

/* SDRAM MT48LC16M16A2 configuration */
const sdramc_memory_dev_t SDRAM_MICRON_MT48LC16M16A2 = {
	24, /* Block1 is at the bit 24, 1+9+13+1. */
	0,  /*
	     * This configures the SDRAM with the following parameters in the
	     *mode register:
	     * - bits 0 to 2: burst length: 1 (000b);
	     * - bit 3: burst type: sequential (0b);
	     * - bits 4 to 6: CAS latency;
	     * - bits 7 to 8: operating mode: standard operation (00b);
	     * - bit 9: write burst mode: programmed burst length (0b);
	     * - all other bits: reserved: 0b.
	     */
	{
		SDRAMC_CR_NC_COL9      | /* 9 column bits (512 bytes). */
		SDRAMC_CR_NR_ROW13     | /* 13 row bits    (8K). */
		SDRAMC_CR_NB_BANK4     | /* SDRAM 4 bank. */
		SDRAMC_CR_CAS_LATENCY2 | /* CAS Latency 2. */
		SDRAMC_CR_DBW          | /* Data bus width 16 bits. */
		SDRAMC_CR_TWR(2)       | /* Write Recovery Delay. */
		SDRAMC_CR_TRC_TRFC(9)  | /* Row Cycle Delay and Row Refresh
		                            Cycle. */
		SDRAMC_CR_TRP(3)       | /* Row Precharge Delay. */
		SDRAMC_CR_TRCD(3)      | /* Row to Column Delay. */
		SDRAMC_CR_TRAS(6)      | /* Active to Precharge Delay. */
		SDRAMC_CR_TXSR(10)       /* Exit from Self Refresh to Active
		                            Delay. */
	},
};

/**
 * \}
 */

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif /* MT48LC16M16A2_H_INCLUDED */
