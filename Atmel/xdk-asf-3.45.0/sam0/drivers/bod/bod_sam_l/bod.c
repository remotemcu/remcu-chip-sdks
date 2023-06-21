/**
 * \file
 *
 * \brief SAM Brown Out Detector Driver
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
#include "bod.h"

/**
 * \brief Configure a Brown Out Detector module.
 *
 * Configures a given BOD module with the settings stored in the given
 * configuration structure.
 *
 * \param[in] conf     Configuration settings to use for the specified BOD33
 *
 * \retval STATUS_OK                  Operation completed successfully
 * \retval STATUS_ERR_INVALID_ARG     An invalid BOD was supplied
 * \retval STATUS_ERR_INVALID_OPTION  The requested BOD level was outside the acceptable range
 */
enum status_code bod33_set_config(
		struct bod33_config *const conf)
{
	/* Sanity check arguments */
	Assert(conf);

	uint32_t temp = 0;

	/* Check if module is enabled. */
	if (SUPC->BOD33.reg & SUPC_BOD33_ENABLE) {
		SUPC->BOD33.reg &= ~SUPC_BOD33_ENABLE;
	}

	/* Convert BOD prescaler, trigger action and mode to a bitmask */
	temp |= (uint32_t)conf->prescaler | (uint32_t)conf->action | (uint32_t)conf->monitor |
			(uint32_t)conf->mode_in_active | (uint32_t)conf->mode_in_standby;

	if (conf->hysteresis == true) {
		temp |= SUPC_BOD33_HYST;
	}

	if (conf->run_in_standby == true) {
		temp |= SUPC_BOD33_RUNSTDBY;
	}

	if (conf->run_in_backup == true) {
		temp |= SUPC_BOD33_RUNBKUP;
	}

	if (conf->level > 0x3F || conf->backuplevel > 0x3F) {
		return STATUS_ERR_INVALID_ARG;
	}

	SUPC->BOD33.reg = SUPC_BOD33_LEVEL(conf->level) |
			SUPC_BOD33_BKUPLEVEL(conf->backuplevel) | temp;

	return STATUS_OK;
}

/**
 * \brief Configure a Brown Out Detector module.
 *
 * Configures a given BOD module with the settings stored in the given
 * configuration structure.
 *
 * \param[in] conf     Configuration settings to use for the specified BOD12
 *
 * \retval STATUS_OK                  Operation completed successfully
 * \retval STATUS_ERR_INVALID_ARG     An invalid BOD was supplied
 * \retval STATUS_ERR_INVALID_OPTION  The requested BOD level was outside the acceptable range
 */
enum status_code bod12_set_config(
		struct bod12_config *const conf)
{
	/* Sanity check arguments */
	Assert(conf);

	uint32_t temp = 0;

	/* Check if module is enabled. */
	if (SUPC->BOD12.reg & SUPC_BOD12_ENABLE) {
		SUPC->BOD12.reg &= ~SUPC_BOD12_ENABLE;
	}

/* Convert BOD prescaler, trigger action and mode to a bitmask */
	temp |= (uint32_t)conf->prescaler | (uint32_t)conf->action |
			(uint32_t)conf->mode_in_active | (uint32_t)conf->mode_in_standby;

	if (conf->hysteresis == true) {
		temp |= SUPC_BOD12_HYST;
	}

	if (conf->run_in_standby == true) {
		temp |= SUPC_BOD12_RUNSTDBY;
	}

	if (conf->level > 0x3F) {
		return STATUS_ERR_INVALID_ARG;
	}

	SUPC->BOD12.reg = SUPC_BOD12_LEVEL(conf->level) | temp;

	return STATUS_OK;
}