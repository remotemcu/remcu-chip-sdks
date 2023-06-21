/**
 * \file
 *
 * \brief Initialization of memories
 * Specific AVR UC3 functions to initialize memories.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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
#include "conf_access.h"
#include "unit_tests.h"

#if (defined AT45DBX_MEM) && (AT45DBX_MEM == ENABLE)
# include "conf_at45dbx.h"
# include "at45dbx.h"
#endif

void memories_initialization(void)
{
	//-- Hmatrix bus configuration
	// This improve speed performance
#ifdef AVR32_HMATRIXB
	union {
		unsigned long scfg;
		avr32_hmatrixb_scfg_t SCFG;
	} u_avr32_hmatrixb_scfg;

	sysclk_enable_pbb_module(SYSCLK_HMATRIX);

	// For the internal-flash HMATRIX slave, use last master as default.
	u_avr32_hmatrixb_scfg.scfg =
			AVR32_HMATRIXB.scfg[AVR32_HMATRIXB_SLAVE_FLASH];
	u_avr32_hmatrixb_scfg.SCFG.defmstr_type =
			AVR32_HMATRIXB_DEFMSTR_TYPE_LAST_DEFAULT;
	AVR32_HMATRIXB.scfg[AVR32_HMATRIXB_SLAVE_FLASH] =
			u_avr32_hmatrixb_scfg.scfg;
	// For the internal-SRAM HMATRIX slave, use last master as default.
	u_avr32_hmatrixb_scfg.scfg =
			AVR32_HMATRIXB.scfg[AVR32_HMATRIXB_SLAVE_SRAM];
	u_avr32_hmatrixb_scfg.SCFG.defmstr_type =
			AVR32_HMATRIXB_DEFMSTR_TYPE_LAST_DEFAULT;
	AVR32_HMATRIXB.scfg[AVR32_HMATRIXB_SLAVE_SRAM] =
			u_avr32_hmatrixb_scfg.scfg;
# ifdef AVR32_HMATRIXB_SLAVE_EBI
	// For the EBI HMATRIX slave, use last master as default.
	u_avr32_hmatrixb_scfg.scfg =
			AVR32_HMATRIXB.scfg[AVR32_HMATRIXB_SLAVE_EBI];
	u_avr32_hmatrixb_scfg.SCFG.defmstr_type =
			AVR32_HMATRIXB_DEFMSTR_TYPE_LAST_DEFAULT;
	AVR32_HMATRIXB.scfg[AVR32_HMATRIXB_SLAVE_EBI] =
			u_avr32_hmatrixb_scfg.scfg;
# endif
#endif

#ifdef AVR32_HMATRIX
	union {
		unsigned long scfg;
		avr32_hmatrix_scfg_t SCFG;
	} u_avr32_hmatrix_scfg;

	sysclk_enable_pbb_module(SYSCLK_HMATRIX);

	// For the internal-flash HMATRIX slave, use last master as default.
	u_avr32_hmatrix_scfg.scfg =
			AVR32_HMATRIX.scfg[AVR32_HMATRIX_SLAVE_FLASH];
	u_avr32_hmatrix_scfg.SCFG.defmstr_type =
			AVR32_HMATRIX_DEFMSTR_TYPE_LAST_DEFAULT;
	AVR32_HMATRIX.scfg[AVR32_HMATRIX_SLAVE_FLASH] =
			u_avr32_hmatrix_scfg.scfg;
	// For the internal-SRAM HMATRIX slave, use last master as default.
	u_avr32_hmatrix_scfg.scfg =
			AVR32_HMATRIX.scfg[AVR32_HMATRIX_SLAVE_SRAM];
	u_avr32_hmatrix_scfg.SCFG.defmstr_type =
			AVR32_HMATRIX_DEFMSTR_TYPE_LAST_DEFAULT;
	AVR32_HMATRIX.scfg[AVR32_HMATRIX_SLAVE_SRAM] =
			u_avr32_hmatrix_scfg.scfg;
# ifdef AVR32_HMATRIX_SLAVE_EBI
	// For the EBI HMATRIX slave, use last master as default.
	u_avr32_hmatrix_scfg.scfg =
			AVR32_HMATRIX.scfg[AVR32_HMATRIX_SLAVE_EBI];
	u_avr32_hmatrix_scfg.SCFG.defmstr_type =
			AVR32_HMATRIX_DEFMSTR_TYPE_LAST_DEFAULT;
	AVR32_HMATRIX.scfg[AVR32_HMATRIX_SLAVE_EBI] =
			u_avr32_hmatrix_scfg.scfg;
# endif
#endif

#ifdef AVR32_HMATRIX_MASTER_USBB_DMA
	union {
		unsigned long                 mcfg;
		avr32_hmatrix_mcfg_t          MCFG;
	} u_avr32_hmatrix_mcfg;
 
	// For the USBB DMA HMATRIX master, use infinite length burst.
	u_avr32_hmatrix_mcfg.mcfg =
			AVR32_HMATRIX.mcfg[AVR32_HMATRIX_MASTER_USBB_DMA];
	u_avr32_hmatrix_mcfg.MCFG.ulbt =
			AVR32_HMATRIX_ULBT_INFINITE;
	AVR32_HMATRIX.mcfg[AVR32_HMATRIX_MASTER_USBB_DMA] =
			u_avr32_hmatrix_mcfg.mcfg;
	
	// For the USBB DPRAM HMATRIX slave, use the USBB DMA as fixed default master.
	u_avr32_hmatrix_scfg.scfg =
			AVR32_HMATRIX.scfg[AVR32_HMATRIX_SLAVE_USBB_DPRAM];
	u_avr32_hmatrix_scfg.SCFG.fixed_defmstr =
			AVR32_HMATRIX_MASTER_USBB_DMA;
	u_avr32_hmatrix_scfg.SCFG.defmstr_type =
			AVR32_HMATRIX_DEFMSTR_TYPE_FIXED_DEFAULT;
	AVR32_HMATRIX.scfg[AVR32_HMATRIX_SLAVE_USBB_DPRAM] =
			u_avr32_hmatrix_scfg.scfg;
#endif

#if (defined AT45DBX_MEM) && (AT45DBX_MEM == ENABLE)
	at45dbx_init();
#endif

#if ((defined SD_MMC_0_MEM) && (SD_MMC_0_MEM == ENABLE)) \
	|| ((defined SD_MMC_1_MEM) && (SD_MMC_1_MEM == ENABLE))
	sd_mmc_init();
#endif
}

