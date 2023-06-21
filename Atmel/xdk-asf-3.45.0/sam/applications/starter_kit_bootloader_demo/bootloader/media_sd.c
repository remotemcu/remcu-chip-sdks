/**
 * \file
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

#include "bootloader.h"

#ifdef MEDIA_USE_SD

/**
 * Initialize for SD/MMC support
 */
void media_sd_init(void)
{
	dbg_print("media_sd: init ...\r\n");
	/* IOs are initialized in board_init() */
	sd_mmc_init();
	dbg_print("media_sd: init ... done\r\n");
}

/**
 * Cleanup for SD/MMC support
 */
void media_sd_cleanup(void)
{
	dbg_print("media_sd: cleanup ...\r\n");
	/* Nothing to do */
	dbg_print("media_sd: cleanup ... done\r\n");
}

/**
 * Try to connect to SD/MMC card
 */
bool media_sd_connect(void)
{
	Ctrl_status status;
	int i;
	for (i = 0; i < 5; i ++) {
		status = sd_mmc_test_unit_ready(0);
		if (CTRL_GOOD == status) {
			return true;
		}
		if (CTRL_NO_PRESENT == sd_mmc_check(0)) {
			return false;
		}
	}
	return false;
}

/**
 * Disconnect from SD/MMC card
 */
void media_sd_disconnect(void)
{
	/* Nothing to do */
}

#endif /* #ifdef MEDIA_USE_SD */

