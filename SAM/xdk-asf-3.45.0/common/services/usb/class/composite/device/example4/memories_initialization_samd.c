/**
 * \file
 *
 * \brief Initialization of memories
 * Specific SAMDx functions to initialize the memories
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
/* To get on-board memories configurations */
#include "conf_board.h" 
#include "conf_access.h"
#include "main.h"

#ifdef CONF_BOARD_SMC_PSRAM
static void psram_init(void)
{
	// To add code here, when this feature can be realized in board
}
#endif

#ifdef CONF_BOARD_SRAM
static void ext_sram_init(void)
{
	// To add code here, when this feature can be realized in board
}
#endif

#ifdef CONF_BOARD_NAND
static void nand_init(void)
{
	/* All operations have been done in ftl_lib.
	   No additional actions to do */
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
#ifdef CONF_BOARD_NAND
	nand_init();
#endif
}
