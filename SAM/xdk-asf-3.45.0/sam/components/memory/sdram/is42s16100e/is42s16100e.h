/**
 * \file
 *
 * \brief IS42S16100E configuration.
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

#ifndef IS42S16100E_H_INCLUDED
#define IS42S16100E_H_INCLUDED

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
 * \defgroup group_sam_components_memory_sdram_is42s16100e SDRAM IS42S16100E
 *
 * This is a configuration for the IS42S16100E SDRAM from Micron.
 * This configuration will be used by the SDRAM driver to set up the
 * IS42S16100E device.
 *
 * \{
 */

/* SDRAM IS42S16100E configuration */
const sdramc_memory_dev_t SDRAM_ISSI_IS42S16100E = {
	22, /* Block1 is at the bit 22, 2+8+11+1. */
	0x30,  /*
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
		SDRAMC_CR_NC_COL8      | /* 8 column bits. */
		SDRAMC_CR_NR_ROW11     | /* 11 row bits    (2K). */
		SDRAMC_CR_NB_BANK2     | /* SDRAM 2 bank. */
		SDRAMC_CR_CAS_LATENCY3 | /* CAS Latency 3. */
		SDRAMC_CR_DBW          | /* Data bus width 16 bits. */
		SDRAMC_CR_TWR(5)       | /* Write Recovery Delay. */
		SDRAMC_CR_TRC_TRFC(13) | /* Row Cycle Delay and Row Refresh Cycle. */
		SDRAMC_CR_TRP(5)       | /* Row Precharge Delay. */
		SDRAMC_CR_TRCD(5)      | /* Row to Column Delay. */
		SDRAMC_CR_TRAS(9)      | /* Active to Precharge Delay. */
		SDRAMC_CR_TXSR(15)       /* Exit from Self Refresh to Active Delay. */
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

#endif /* IS42S16100E_H_INCLUDED */
