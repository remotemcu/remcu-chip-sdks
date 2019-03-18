/**
 * \file
 *
 * \brief SAM True Random Number Generator (TRNG) Driver
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

#include "trng.h"

/**
 * \brief Initializes a hardware TRNG module instance.
 *
 * Enables the clock and initializes the TRNG module, based on the given
 * configuration values.
 *
 * \param[in,out] module_inst  Pointer to the software module instance struct
 * \param[in]     hw           Pointer to the TRNG hardware module
 * \param[in]     config       Pointer to the TRNG configuration options struct
 *
 * \return Status of the initialization procedure.
 *
 * \retval STATUS_OK           The module was initialized successfully
 */
enum status_code trng_init(
		struct trng_module *const module_inst,
		Trng *const hw,
		struct trng_config *const config)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(hw);
	Assert(config);

	/* Initialize device instance */
	module_inst->hw = hw;

	/* Turn on the digital interface clock */
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, MCLK_APBCMASK_TRNG);

#if TRNG_CALLBACK_MODE == true
	/* Initialize parameters */
	for (uint8_t i = 0; i < TRNG_CALLBACK_N; i++) {
		module_inst->callback[i] = NULL;
	}

	/* Initialize software flags*/
	module_inst->register_callback_mask = 0x00;
	module_inst->enable_callback_mask   = 0x00;
	module_inst->job_buffer             = NULL;
	module_inst->remaining_number       = 0;
	module_inst->job_status             = STATUS_OK;

	/* Register this instance for callbacks*/
	_trng_instance = module_inst;
#endif

	/* Write configuration to module */
	hw->CTRLA.reg = ((uint32_t)config->run_in_standby << TRNG_CTRLA_RUNSTDBY_Pos);

	return STATUS_OK;
}

