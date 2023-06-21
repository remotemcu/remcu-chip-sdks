/**
 * \file
 *
 * \brief SDRAM controller (SDRAMC) driver for SAM.
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
#include "sdramc.h"
#include "board.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \defgroup sam_drivers_sdramc_group SDRAMC - SDRAM Controller
 *
 * See \ref sam_sdramc_quickstart.
 *
 * Driver for the SDRAMC (SDRAM Controller). This driver provides access to the
 * main features of the SDRAM controller.
 *
 * \section dependencies Dependencies
 * This driver does not depend on other modules. 
 * \{
 */

/**
 * \brief Initialize the SDRAM controller.
 *
 * \param p_sdram  Pointer to the sdram memory structure.
 * \param ul_clk  SDRAM clock frequency.
 */
void sdramc_init(sdramc_memory_dev_t *p_sdram, uint32_t ul_clk)
{
	volatile uint32_t i;
	volatile uint16_t *pSdram = (uint16_t *)(BOARD_SDRAM_ADDR);

	/* Prevent setting the SDRAMC entering to sleep mode */
	sleepmgr_lock_mode(SLEEPMGR_ACTIVE);

	/* SDRAM device configuration */
	/* Step 1. */
	/* Set the features of SDRAM device into the Configuration Register */
	SDRAMC->SDRAMC_CR = p_sdram->cr.ul_cfg;

	/* Step 2. */

	/* For low-power SDRAM, Temperature-Compensated Self Refresh (TCSR),
	   Drive Strength (DS) and Partial Array Self Refresh (PASR) must be set
	   in the Low-power Register. */
	SDRAMC->SDRAMC_LPR = 0;

	/* Step 3. */
	/* Program the memory device type into the Memory Device Register */
	SDRAMC->SDRAMC_MDR = SDRAMC_MDR_MD_SDRAM;

	/* Step 4. */

	/* A minimum pause of 200 µs is provided to precede any signal toggle.
	   (6 core cycles per iteration) */
	for (i = 0; i < ((ul_clk / 1000000) * 1000 / 6); i++) {
		;
	}

	/* Step 5. */

	/* A NOP command is issued to the SDR-SDRAM. Program NOP command into
	   Mode Register, and the application must set Mode to 1 in the Mode
	   Register. Perform a write access to any SDR-SDRAM address to
	   acknowledge this command. Now the clock which drives SDR-SDRAM
	   device is enabled. */
	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_NOP;
	*pSdram = 0x0;

	/* Step 6. */

	/* An all banks precharge command is issued to the SDR-SDRAM. Program
	   all banks precharge command into Mode Register, and the application
	   must set Mode to 2 in the Mode Register. Perform a write access to
	   any SDRSDRAM address to acknowledge this command. */
	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_ALLBANKS_PRECHARGE;
	*pSdram = 0x0;

	/* Add some delays after precharge */
	for (i = 0; i < ((ul_clk / 1000000) * 1000 / 6); i++) {
		;
	}

	/* Step 7. */
	/* Eight auto-refresh (CBR) cycles are provided. Program the auto
	   refresh command (CBR) into Mode Register, and the application
	   must set Mode to 4 in the Mode Register. Once in the idle state,
	   eight AUTO REFRESH cycles must be performed. */
	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_AUTO_REFRESH;
	*pSdram = 0x1;

	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_AUTO_REFRESH;
	*pSdram = 0x2;

	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_AUTO_REFRESH;
	*pSdram = 0x3;

	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_AUTO_REFRESH;
	*pSdram = 0x4;

	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_AUTO_REFRESH;
	*pSdram = 0x5;

	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_AUTO_REFRESH;
	*pSdram = 0x6;

	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_AUTO_REFRESH;
	*pSdram = 0x7;

	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_AUTO_REFRESH;
	*pSdram = 0x8;

	/* Step 8. */
	/* A Mode Register Set (MRS) cycle is issued to program the parameters
	   of the SDRAM devices, in particular CAS latency and burst length. */
	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_LOAD_MODEREG;
	*((uint16_t *)(pSdram + p_sdram->ul_mode)) = 0xcafe;
    
	/* Add some delays */
	for (i = 0; i < ((ul_clk / 1000000) * 1000 / 6); i++) {
		;
	}

	/* Step 9. */

	/* For low-power SDR-SDRAM initialization, an Extended Mode Register Set
	   (EMRS) cycle is issued to program the SDR-SDRAM parameters (TCSR,
	   PASR, DS). The write address must be chosen so that BA[1] is set to
	   1 and BA[0] is set to 0. */
	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_EXT_LOAD_MODEREG;
	*((uint16_t *)(pSdram + (1 << p_sdram->ul_bk1))) = 0x0;

	/* Step 10. */
	/* The application must go into Normal Mode, setting Mode to 0 in the
	   Mode Register and perform a write access at any location in the\
	   SDRAM to acknowledge this command. */
	SDRAMC->SDRAMC_MR = SDRAMC_MR_MODE_NORMAL;
	*pSdram = 0x0;

	/* Step 11. */

	/* Write the refresh rate into the count field in the SDRAMC Refresh
	   Timer register. Set Refresh timer to 15.625 us. */
	i = ul_clk / 1000u;
	i *= 15625u;
	i /= 1000000u;
	SDRAMC->SDRAMC_TR = SDRAMC_TR_COUNT(i);
}

/**
 * \brief De-initialize the SDRAM controller.
 */
void sdramc_deinit( void )
{
	/* Allow the SDRAMC entering to the sleep mode */
	sleepmgr_unlock_mode(SLEEPMGR_ACTIVE);
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \}
 */
