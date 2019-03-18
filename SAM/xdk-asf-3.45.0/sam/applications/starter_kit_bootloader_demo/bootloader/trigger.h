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

#ifndef TRIGGER_H_INCLUDED
#define TRIGGER_H_INCLUDED

#include "regions.h"

/** All supported trigger modes */
typedef enum trigger_modes {
	TRIGGER_BOOT,        /**< Nothing, just run app */
	TRIGGER_LOAD,        /**< Load FW (from host) and update */
	TRIGGER_LOAD_FILE,   /**< Load FW (from file) and update */
	TRIGGER_UPDATE,      /**< Update loaded FW */
	TRIGGER_UPDATE_FILE, /**< Update from a file (in storage) */
	TRIGGER_NUM_MAX
} trigger_modes_t;
/** String to describe trigger modes */
static const char *trigger_modes_str[] = {
	"BOOT", "LOAD", "LOAD FILE", "UPDATE", "UPDATE FILE"
};
/**
 * Return trigger modes description string
 * \param mode Trigger mode
 * \return string of specified mode
 */
__always_inline
static const char* trigger_get_mode_str(enum trigger_modes mode)
{
	return trigger_modes_str[mode];
}

void trigger_init(void);
void trigger_cleanup(void);
enum trigger_modes trigger_poll(const struct regions_info *info);

#endif /* #ifndef TRIGGER_H_INCLUDED */

