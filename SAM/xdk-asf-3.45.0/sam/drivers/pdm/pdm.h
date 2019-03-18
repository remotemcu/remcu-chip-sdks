/**
 * \file
 *
 * \brief PDM driver for SAM.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef PDM_H_INCLUDED
#define PDM_H_INCLUDED

#include "compiler.h"
#include "status_codes.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \addtogroup sam_drivers_pdm_group
 *
 * See \ref sam_pdm_quickstart.
 *
 * @{
 */

#define PDM_RETRY_VALUE   10000

/**
 * \name PDM low level access
 *
 * @{
 */

/**
 * Interrupt source (bitmap)
 */
enum pdmic_interrupt_source {
	PDMIC_INTERRUPT_SRC_DATA_READY = PDMIC_ISR_DRDY,
	PDMIC_INTERRUPT_SRC_OVERRUN = PDMIC_ISR_OVRE,
	PDMIC_INTERRUPT_SRC_BUFFER_END = PDMIC_ISR_ENDRX,
	PDMIC_INTERRUPT_SRC_TRANSFER_END = PDMIC_ISR_RXBUFF
};

/**
 * Resets the PDMIC, simulating a hardware reset
 * \param[in] pdmic PDMIC peripheral base.
 */
__always_inline static void pdmic_reset(Pdmic *pdmic)
{
	pdmic->PDMIC_CR = PDMIC_CR_SWRST;
}

/**
 * Enables the PDM and starts the conversions
 * \param[in] pdmic PDMIC peripheral base.
 */
__always_inline static void pdmic_conversion_enable(Pdmic *pdmic)
{
	pdmic->PDMIC_CR = PDMIC_CR_ENPDM;
}

/**
 * Disable the PDM conversions
 * \param[in] pdmic PDMIC peripheral base.
 */
__always_inline static void pdmic_conversion_disable(Pdmic *pdmic)
{
	pdmic->PDMIC_CR = (~PDMIC_CR_ENPDM & ~PDMIC_CR_SWRST);
}

/**
 * Set prescale for the PDMIC
 * \param[in] pdmic PDMIC peripheral base.
 */
__always_inline static void pdmic_set_prescal(Pdmic *pdmic, uint8_t prescal)
{
	pdmic->PDMIC_MR = PDMIC_MR_PRESCAL(prescal);
}

/**
 * The analog-to-digital conversion data is placed into this register at the end
 * of a conversion and remains until it is read
 * \param[in] pdmic PDMIC peripheral base.
 */
__always_inline static uint32_t pdmic_get_convert_data(Pdmic *pdmic)
{
	return pdmic->PDMIC_CDR;
}

/**
 * Enable interrupts
 * \param[in] pdmic PDMIC peripheral base.
 * \param[in] sources Interrupts sources bitmap.
 */
__always_inline static void pdmic_interrupts_enable(Pdmic *pdmic,
		enum pdmic_interrupt_source sources)
{
	pdmic->PDMIC_IER = sources;
}

/**
 * Disable interrupts
 * \param[in] pdmic PDMIC peripheral base.
 * \param[in] sources Interrupts sources bitmap.
 */
__always_inline static void pdmic_interrupts_disable(Pdmic *pdmic,
		enum pdmic_interrupt_source sources)
{
	pdmic->PDMIC_IDR = sources;
}

/**
 * Return interrupt mask
 * \param[in] pdmic PDMIC peripheral base.
 */
__always_inline static uint32_t pdmic_get_interrupt_mask(Pdmic *pdmic)
{
	return pdmic->PDMIC_IMR;
}

/**
 * Return status
 * \param[in] pdmic PDMIC peripheral base.
 */
__always_inline static uint32_t pdmic_get_status(Pdmic *pdmic)
{
	return pdmic->PDMIC_ISR;
}

/**
 * Return PDMIC PDC base
 * \param[in] pdmic PDMIC peripheral base.
 */
__always_inline static Pdc *pdmic_get_pdc_base(Pdmic *pdmic)
{
	return (Pdc *)((uint32_t)pdmic + 0x100);
}

/**
 * Set PDMIC buffer
 * \param[in] pdmic PDMIC peripheral base.
 * \param[in] buffer Source buffer address
 */
__always_inline static void pdmic_buffer_set(Pdmic *pdmic,
		uint8_t *buffer)
{
	pdmic->PDMIC_RPR = (uint32_t)buffer;
}

/**
 * Set PDMIC next buffer address
 * \param[in] pdmic PDMIC peripheral base.
 * \param[in] buffer Next source buffer address
 */
__always_inline static void pdmic_transfer_set_next(Pdmic *pdmic,
		uint8_t *buffer)
{
	pdmic->PDMIC_RNPR = (uint32_t)buffer;
}

/**
 * Enable PDMIC transfer
 * \param[in] pdmic PDMIC peripheral base.
 */
__always_inline static void pdmic_transfer_enable(Pdmic *pdmic)
{
	pdmic->PDMIC_PTCR = PDMIC_PTCR_RXTEN | PDMIC_PTCR_RXCBEN;
}

/**
 * Disable PDMIC transfer
 * \param[in] pdmic PDMIC peripheral base.
 */
__always_inline static void pdmic_transfer_disable(Pdmic *pdmic)
{
	pdmic->PDMIC_PTCR = PDMIC_PTCR_RXTDIS | PDMIC_PTCR_RXCBDIS;
}

/**
 * Check if PDMIC transfer is enabled (in progress)
 * \param[in] pdmic PDMIC peripheral base.
 */
__always_inline static bool pdmic_transfer_is_enabled(Pdmic *pdmic)
{
	return ((pdmic->PDMIC_PTSR & (PDMIC_PTSR_RXTEN | PDMIC_PTSR_RXCBEN))
	       == (PDMIC_PTSR_RXTEN | PDMIC_PTSR_RXCBEN));
}

/**
 * Configure DSP configuration register 0
 * \param[in] pdmic PDMIC peripheral base.
 * \param[in] cfg0 Configurations to DSP configuration regsiter 0.
 */
__always_inline static void pdmic_dsp_cfg0(Pdmic *pdmic, uint32_t cfg0)
{
	pdmic->PDMIC_DSPR0 = cfg0;
}

/**
 * Configure DSP configuration register 1
 * \param[in] pdmic PDMIC peripheral base.
 * \param[in] cfg1 Configurations to DSP configuration regsiter 1.
 */
__always_inline static void pdmic_dsp_cfg1(Pdmic *pdmic, uint32_t cfg1)
{
	pdmic->PDMIC_DSPR1 = cfg1;
}

/**
 * Enable write protect
 * \param[in] pdmic PDMIC peripheral base.
 */
__always_inline static void pdmic_write_protect_enable(Pdmic *pdmic)
{
	pdmic->PDMIC_WPMR = PDMIC_WPMR_WPEN | PDMIC_WPMR_WPKEY_PASSWD;
}

/**
 * Disable write protect
 * \param[in] pdmic PDMIC peripheral base.
 */
__always_inline static void pdmic_write_protect_disable(Pdmic *pdmic)
{
	pdmic->PDMIC_WPMR = PDMIC_WPMR_WPKEY_PASSWD;
}

/**
 * Get write protect status
 * \param[in] pdmic PDMIC peripheral base.
 */
__always_inline static uint32_t pdmic_get_write_protect_status(Pdmic *pdmic)
{
	return pdmic->PDMIC_WPSR;
}

/** @} */

/**
 * \name PDMIC driver access
 *
 * @{
 */

/** Forward definition of the PDMIC driver instance */
struct pdm_instance;
/** Type of the callback function for PDMIC driver  */
typedef void (*pdm_callback_t)(const struct pdm_instance *const module);

/**
 * Callback types for PDM callback driver
 */
enum pdm_callback_type {
	/** Callback for transfer done */
	PDM_CALLBACK_TRANSFER_END,
	/** Callback for any of transfer buffer done */
	PDM_CALLBACK_BUFFER_END,
	/** Callback for data overrun */
	PDM_CALLBACK_OVERRUN,
#  if !defined(__DOXYGEN__)
	/** Number of available callbacks */
	PDM_CALLBACK_N
#  endif
};

/**
 * Converted data size
 */
enum pdmic_converted_data_size {
	PDMIC_CONVERTED_DATA_SIZE_16 = 0,
	PDMIC_CONVERTED_DATA_SIZE_32
};

/**
 * Oversampling ratio
 */
enum pdmic_oversampling_ratio {
	PDMIC_OVERSAMPLING_RATIO_128 = 0,
	PDMIC_OVERSAMPLING_RATIO_64
};

/**
 * \name PDM Module status flags
 *
 * PDM status flags, returned by \ref pdmic_get_status().
 *
 * @{
 */

/** PDM End of (one of the) Buffer */
#define PDM_STATUS_BUFFER_END    (1UL << 0)
/** PDM Buffer Full (End of transfer) */
#define PDM_STATUS_TRANSFER_END  (1UL << 1)

/** Default prescale for PDMIC */
#define PDM_DEFAULT_PRESCAL (3)

/** @} */

/**
 * PDM software driver instance structure.
 */
struct pdm_instance {
	/** Base address for PDMIC0 peripheral */
	Pdmic *hw;
	/** Callback functions */
	pdm_callback_t callbacks[PDM_CALLBACK_N];
	/** Bit mask for enabled callbacks */
	uint32_t enabled_callbacks;
	/** Status of the last job */
	volatile enum status_code job_status;
};

/**
 * PDM configuration structure
 */
struct pdm_config {
	/** prescal determines the frequency of PDMCLK.*/
	uint8_t prescal;
	/** 0 to enable high-pass fileter, 1 to bypass filter */
	bool high_pass_filter_bypass;
	/** 0 to enable droop compensation, 1 to bypass filter */
	bool sincc_filter_bypass;
	/** Converted data size */
	uint8_t conver_data_size;
	/** Oversampling Ratio */
	uint8_t oversampling_ratio;
	/** Shifts the multiplication operation result by SCALE bits to the right */
	uint8_t data_scale;
	/** Shifts the scaled result by SHIFT bits to the right */
	uint8_t data_shift;
	/** Gain correction to apply to the final result */
	uint16_t gain;
	/** Offset correction to apply to the final result */
	uint16_t offset;
};

/**
 * \name Driver initialization and configuration
 * @{
 */

enum status_code pdm_init(struct pdm_instance *const dev_inst, Pdmic *hw,
		struct pdm_config *const cfg);

/**
 * \brief Initializes PDMIC configuration structure to defaults
 *
 * Initializes a given PDMIC configuration struct to a set of known default
 * values. This function should be called on any new instance of the
 * configuration struct before being modified by the user application.
 *
 * The default configuration is as follows:
 * - PDMCLK = MCK/8
 * - High-pass filter enabled
 * - Droop compensation filter enabled.
 * - Converted data size is 16-bit.
 * - Oversampling ratio is 128
 * - No data scale
 * - No data shift
 * - Gain is set to 1
 * - Offset is set to 0
 *
 * \param[out] cfg Pointer to configuration struct to initialize to defaults
 */
__always_inline static void pdm_get_config_default(struct pdm_config *const cfg)
{
	Assert(cfg);
	cfg->prescal = PDM_DEFAULT_PRESCAL;
	cfg->high_pass_filter_bypass = false;
	cfg->sincc_filter_bypass = false;
	cfg->conver_data_size = PDMIC_CONVERTED_DATA_SIZE_16;
	cfg->oversampling_ratio = PDMIC_OVERSAMPLING_RATIO_128;
	cfg->data_scale = 0;
	cfg->data_shift = 0;
	cfg->gain = 1;
	cfg->offset = 0;
}

/** @} */

/**
 * \name Status Management
 * @{
 */

/**
 * \brief Retrieves the current module status.
 *
 * Retrieves the status of the module, giving overall state information.
 *
 * \param[in] dev_inst  Pointer to the PDMIC software instance struct
 *
 * \return Bitmask of \c PDM_STATUS_* flags
 *
 * \retval PDM_STATUS_TRANSFER_END  All of PDC buffers are done
 * \retval PDM_STATUS_BUFFER_END    One of PDC buffer is done
 */
__always_inline static uint32_t pdm_get_interrupt_status(
		struct pdm_instance *const dev_inst)
{
	Assert(dev_inst);
	Assert(dev_inst->hw);

	return dev_inst->hw->PDMIC_ISR;
}

/** @} */

enum status_code pdm_read_convert_data(struct pdm_instance *const dev_inst,
		uint32_t *data);

/**
 * \name Enable and disable interrupts
 * @{
 */

/**
 * \brief Enable PDM conversion
 */
__always_inline static void pdm_enable(struct pdm_instance *const dev_inst)
{
	/* Sanity check arguments */
	Assert(dev_inst);
	Assert(dev_inst->hw);

	dev_inst->hw->PDMIC_CR = PDMIC_CR_ENPDM;
}

/**
 * \brief Disable PDM conversion
 */
__always_inline static void pdm_disable(struct pdm_instance *const dev_inst)
{
	/* Sanity check arguments */
	Assert(dev_inst);
	Assert(dev_inst->hw);

	dev_inst->hw->PDMIC_CR &= ~PDMIC_CR_ENPDM;
}

/**
 * \brief Enable interrupt
 *
 * Enable the given interrupt request from the PDMIC module .
 *
 * \param[in] dev_inst Pointer to the PDMIC software instance struct
 * \param[in] interrupt Interrupts to enable
 */
static inline void pdm_enable_interrupt(struct pdm_instance *const dev_inst,
		enum pdmic_interrupt_source interrupt)
{
	/* Sanity check arguments */
	Assert(dev_inst);
	Assert(dev_inst->hw);
	dev_inst->hw->PDMIC_IER = interrupt;
}

/**
 * \brief Disable interrupt
 *
 * Disable the given interrupt request from the PDM module.
 *
 * \param[in] dev_inst Pointer to the PDMIC software instance struct
 * \param[in] interrupt Interrupt to disable
 */
static inline void pdm_disable_interrupt(struct pdm_instance *const dev_inst,
		enum pdmic_interrupt_source interrupt)
{
	/* Sanity check arguments */
	Assert(dev_inst);
	Assert(dev_inst->hw);
	dev_inst->hw->PDMIC_IDR = interrupt;
}

/** @} */

/**
 * \name Callback Management
 * @{
 */

void pdm_register_callback(struct pdm_instance *const dev_inst,
		pdm_callback_t callback, enum pdm_callback_type type);

void pdm_unregister_callback(struct pdm_instance *const dev_inst,
		enum pdm_callback_type type);

/**
 * \brief Enables callback
 *
 * Enables the callback function registered by \ref
 * pdmic_register_callback. The callback function will be called from the
 * interrupt handler when the conditions for the callback type are met.
 *
 * \param[in]     dev_inst  Pointer to PDMIC software instance struct
 * \param[in]     type Callback type given by an enum
 */
__always_inline static void pdm_enable_callback(
		struct pdm_instance *const dev_inst,
		enum pdm_callback_type type)
{
	Assert(dev_inst);
	Assert(dev_inst->hw);

	if (type < PDM_CALLBACK_N) {
		dev_inst->enabled_callbacks |= (1 << type);
	}
}

/**
 * \brief Disables callback
 *
 * Disables the callback function registered by the \ref
 * pdmic_register_callback.
 *
 * \param[in]     dev_inst  Pointer to PDMIC software instance struct
 * \param[in]     type Callback type given by an enum
 */
__always_inline static void pdm_disable_callback(
		struct pdm_instance *const dev_inst,
		enum pdm_callback_type type)
{
	Assert(dev_inst);
	Assert(dev_inst->hw);

	if (type < PDM_CALLBACK_N) {
		dev_inst->enabled_callbacks &= ~(1 << type);
	}
}

/** @} */


/** @} */

/** @} */

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \page sam_pdm_quickstart Quickstart guide for SAM PDM module
 *
 * This is the quickstart guide for the "SAM PDM module", with step-by-step
 * instructions on how to configure and use the module in a selection of use
 * cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g.the main application function.
 *
 * \section pdm_use_cases PDM use cases
 * - \ref pdm_basic_use_case
 *
 * \section pdm_basic_use_case Basic use case
 * In this basic use case, the PDM module are configured for:
 * - The default configuration is as follows:
 *   PDMCLK = MCK/8
 *   High-pass filter enabled
 *   Droop compensation filter enabled.
 *   Converted data size is 16-bit.
 *   Oversampling ratio is 128
 *   No data scale
 *   No data shift
 *   Gain is set to 1
 *   Offset is set to 0
 *
 * \subsection sam_pdm_quickstart_prereq Prerequisites
 * -# \ref sysclk_group "System Clock Management (Sysclock)"
 *
 * \section pdm_basic_use_case_setup Setup steps
 * \subsection pdm_basic_use_case_setup_code Example code
 * Add to application C-file:
 * \code
	 struct pdm_instance pdm;
	 struct pdm_config pdm_cfg;
	 uint32_t data;

	 pdm_get_config_default(&pdm_cfg);
	 pdm_init(&pdm, PDMIC0, &pdm_cfg);
\endcode
 *
 * \subsection pdm_basic_use_case_setup_flow Workflow
 * -# Get default configurations:
 *   - \code
	pdm_get_config_default(&pdm_cfg);
\endcode
 * -# Initialize the PDM module with configuration:
 *   - \code
	pdm_init(&pdm, PDMIC0, &pdm_cfg);
\endcode
 * -# Enable PDM module conversion:
 *   - \code pdm_enable(&pdm); \endcode
 * -# Get converted data:
 *   - \code pdm_read_convert_data(&pdm, &data); \endcode
 */

#endif /* PDM_H_INCLUDED */
