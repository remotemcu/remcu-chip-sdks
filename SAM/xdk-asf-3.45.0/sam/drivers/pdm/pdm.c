/**
 * \file
 *
 * \brief PDM driver for SAM.
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

#include "pdm.h"
#include "sysclk.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \defgroup sam_drivers_pdm_group Pulse-Density-Modulation Interface Controller
 * (PDMIC) Driver.
 *
 * \par Purpose
 *
 * The Pulse Density Modulation Interface Controller (PDMIC) is a PDM interface
 * controller and decoder that is compatible with mono/stereo PDM format. It
 * integrates a clock generator driving the PDM microphones and embeds filters
 * which decimate the incoming bitstream to obtain most common audio rates.
 * @{
 */
/** PDMIC interface numbers */
#define PDMIC_NUM 2

static struct pdm_instance *_pdm_instances[PDMIC_NUM];

/**
 * \brief PDM Interrupt Handler
 *
 * \param[in]  pdm_num  PDMIC controller number
 */
static void PDMIC_Handler(uint8_t pdm_num)
{
	struct pdm_instance *dev_inst = _pdm_instances[pdm_num];
	uint32_t isr = dev_inst->hw->PDMIC_ISR;
	/* All of the buffer done */
	if (isr & PDMIC_ISR_RXBUFF) {
		/* Disable PDC */
		dev_inst->hw->PDMIC_PTCR = (PDMIC_PTCR_RXTDIS);
		/* Disable Interrupts */
		dev_inst->hw->PDMIC_IDR = 0xFFFFFFFF;
		/* Change job status */
		dev_inst->job_status = STATUS_OK;
		/* Callback */
		if ((dev_inst->enabled_callbacks &
				(1 << PDM_CALLBACK_TRANSFER_END)) &&
				dev_inst->callbacks[PDM_CALLBACK_TRANSFER_END]) {
			dev_inst->callbacks[PDM_CALLBACK_TRANSFER_END](dev_inst);
		}
	}
	/* One of the buffer done */
	else if (isr & PDMIC_ISR_ENDRX) {
		/* Stop PDC (Pause and then start again after callback) */
		dev_inst->hw->PDMIC_PTCR = (PDMIC_PTCR_RXTDIS);
		/* Disable Interrupt */
		dev_inst->hw->PDMIC_IDR = PDMIC_IDR_ENDRX;
		/* Callback */
		if ((dev_inst->enabled_callbacks &
				(1 << PDM_CALLBACK_BUFFER_END)) &&
				dev_inst->callbacks[PDM_CALLBACK_BUFFER_END]) {
			dev_inst->callbacks[PDM_CALLBACK_BUFFER_END](dev_inst);
		}

		/* Continue PDC */
		dev_inst->hw->PDMIC_PTCR = (PDMIC_PTCR_RXTEN);
	}
	/* Over Run */
	else if (isr & PDMIC_ISR_OVRE) {
		/* Callback */
		if ((dev_inst->enabled_callbacks &
				(1 << PDM_CALLBACK_OVERRUN)) &&
				dev_inst->callbacks[PDM_CALLBACK_OVERRUN]) {
			dev_inst->callbacks[PDM_CALLBACK_OVERRUN](dev_inst);
		}
	}
}

/**
 * \brief PDMIC 0 Interrupt Handler
 */
void PDMIC0_Handler(void)
{
	PDMIC_Handler(0);
}

/**
 * \brief PDMIC 1 Interrupt Handler
 */
void PDMIC1_Handler(void)
{
	PDMIC_Handler(1);
}

/**
 * \brief Initializes the PDM module
 *
 * Initializes the PDM struct and the hardware module based on the
 * given configuration struct values and converted data buffers.
 *
 * \param dev_inst         Pointer to the PDM software instance struct
 * \param  hw          Pointer to the PDMIC hardware instance
 * \param  cfg         Pointer to the configuration struct
 *
 * \return Status of the initialization procedure
 * \retval STATUS_OK                The initialization was successful
 * \retval ERR_INVALID_ARG          Invalid argument(s) were provided
 * \retval ERR_BUSY                 The module is busy
 */
enum status_code pdm_init(struct pdm_instance *const dev_inst, Pdmic *hw,
		struct pdm_config *const cfg)
{
	uint32_t dsp_cfg = 0;

	Assert(dev_inst);
	Assert(hw);
	Assert(cfg);

	/* HW base init */
	dev_inst->hw = hw;

	hw->PDMIC_CR = PDMIC_CR_SWRST;

	/* Enable PMC clock */
	if (hw == PDMIC1) {
		sysclk_enable_peripheral_clock(ID_PDMIC1);
		_pdm_instances[1] = dev_inst;
	} else {
		sysclk_enable_peripheral_clock(ID_PDMIC0);
		_pdm_instances[0] = dev_inst;
	}

	/* Set prescal */
	hw->PDMIC_MR = PDMIC_MR_PRESCAL(cfg->prescal);

	/* Initialize DSP0 */
	if (cfg->high_pass_filter_bypass) {
		dsp_cfg |= PDMIC_DSPR0_HPFBYP;
	}

	if (cfg->sincc_filter_bypass) {
		dsp_cfg |= PDMIC_DSPR0_SINBYP;
	}

	if (cfg->conver_data_size) {
		dsp_cfg |= PDMIC_DSPR0_SIZE;
	}

	if (cfg->oversampling_ratio) {
		dsp_cfg |= PDMIC_DSPR0_OSR_64;
	} else {
		dsp_cfg |= PDMIC_DSPR0_OSR_128;
	}

	dsp_cfg |= PDMIC_DSPR0_SCALE(cfg->data_scale) |
			PDMIC_DSPR0_SHIFT(cfg->data_shift);
	hw->PDMIC_DSPR0 = dsp_cfg;

	/* Set gain and offset */
	hw->PDMIC_DSPR1 = PDMIC_DSPR1_DGAIN(cfg->gain) |
			PDMIC_DSPR1_OFFSET(cfg->offset);

	/* Initialize for Jobs */
	for (uint32_t i = 0; i < PDM_CALLBACK_N; i++) {
		dev_inst->callbacks[i] = NULL;
	}

	dev_inst->enabled_callbacks = 0;

	dev_inst->job_status = STATUS_OK;

	return STATUS_OK;
}

/**
 * \brief Gets converted data
 *
 * Gets the converted data
 *
 * \param [in]  dev_inst    Pointer to the PDM software instance struct
 * \param [in]  data    Pointer to store the converted data
 */
enum status_code pdm_read_convert_data(struct pdm_instance *const dev_inst,
		uint32_t *data)
{
	/* Sanity check arguments */
	Assert(dev_inst);
	Assert(dev_inst->hw);

	uint32_t timeout = PDM_RETRY_VALUE;

	while (!(dev_inst->hw->PDMIC_ISR & PDMIC_ISR_DRDY) && timeout) {
		--timeout;
	}

	if (timeout == 0) {
		return STATUS_ERR_TIMEOUT;
	}

	*data = pdmic_get_convert_data(dev_inst->hw);

	return STATUS_OK;
}

/**
 * \brief Registers a callback
 *
 * Registers a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by for the interrupt handler to call it
 * when the condition for the callback is met.
 *
 * \param[in] dev_inst       Pointer to PDM software instance struct
 * \param[in] callback  Pointer to callback function
 * \param[in] type      Callback type given by an enum
 *
 */
void pdm_register_callback(struct pdm_instance *const dev_inst,
		pdm_callback_t callback, enum pdm_callback_type type)
{
	Assert(dev_inst);
	Assert(callback);

	if (type < PDM_CALLBACK_N) {
		dev_inst->callbacks[type] = callback;
	}
}

/**
 * \brief Unregisters a callback
 *
 * Unregisters a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by for the interrupt handler to call it
 * when the condition for the callback is met.
 *
 * \param[in] dev_inst       Pointer to PDM software instance struct
 * \param[in] type      Callback type given by an enum
 *
 */
void pdm_unregister_callback(struct pdm_instance *const dev_inst,
		enum pdm_callback_type type)
{
	Assert(dev_inst);
	if (type < PDM_CALLBACK_N) {
		dev_inst->callbacks[type] = NULL;
	}
}

/** @} */

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
