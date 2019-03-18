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

/**
 * Initialize triggers
 */
void trigger_init(void)
{
	dbg_print("trigger: init ...\r\n");
	/* Initialized in board_init */
	dbg_print("trigger: init done\r\n");
}

/**
 * Cleanup triggers
 */
void trigger_cleanup(void)
{
	dbg_print("trigger: cleanup ...\r\n");
	/* Nothing to do */
	dbg_print("trigger: cleanup done\r\n");
}

/**
 * Check if triggers asserted
 * \info The information loaded from memory to check
 */
enum trigger_modes trigger_poll(const struct regions_info *info)
{
#ifdef TRIGGER_USE_BUTTONS
#  ifdef TRIGGER_LOAD_BUTTON
	if (TRIGGER_LOAD_BUTTON_ACTIVE ==
		ioport_get_pin_level(TRIGGER_LOAD_BUTTON)) {
		return TRIGGER_LOAD;
	}
#  endif
#  ifdef TRIGGER_SWITCH_BUTTON
	if (TRIGGER_SWITCH_BUTTON_ACTIVE ==
		ioport_get_pin_level(TRIGGER_SWITCH_BUTTON)) {
		return TRIGGER_UPDATE;
	}
#  endif
#endif
#ifdef TRIGGER_USE_FLAG
	return (enum trigger_modes)info->trigger;
#else
	/* No trigger */
	return TRIGGER_BOOT;
#endif
}

