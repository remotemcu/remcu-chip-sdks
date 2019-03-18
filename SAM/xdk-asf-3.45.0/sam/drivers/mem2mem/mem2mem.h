/**
 * \file
 *
 * \brief MEM2MEM driver for SAM.
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

#ifndef MEM2MEM_H_INCLUDED
#define MEM2MEM_H_INCLUDED

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
 * \addtogroup sam_drivers_m2m_group
 *
 * See \ref sam_m2m_quickstart.
 *
 * @{
 */

/**
 * \name MEM2MEM low level access
 *
 * @{
 */

/**
 * Transfer size (byte/word/dword)
 */
enum mem2mem_transfer_size {
	MEM2MEM_TRANSFER_8_BIT = MEM2MEM_MR_TSIZE_T_8BIT,
	MEM2MEM_TRANSFER_BYTE  = MEM2MEM_MR_TSIZE_T_8BIT,
	MEM2MEM_TRANSFER_16_BIT = MEM2MEM_MR_TSIZE_T_16BIT,
	MEM2MEM_TRANSFER_WORD   = MEM2MEM_MR_TSIZE_T_16BIT,
	MEM2MEM_TRANSFER_32_BIT = MEM2MEM_MR_TSIZE_T_32BIT,
	MEM2MEM_TRANSFER_DWORD  = MEM2MEM_MR_TSIZE_T_32BIT
};

/**
 * Interrupt source (bitmap)
 */
enum mem2mem_interrupt_source {
	MEM2MEM_INTERRUPT_SRC_BUFFER_END = MEM2MEM_ISR_RXEND,
	MEM2MEM_INTERRUPT_SRC_TRANSFER_END = MEM2MEM_ISR_RXBUFF
};

/**
 * MEM2MEM transfer descriptor
 */
struct mem2mem_transfer {
	/** Source buffer address */
	uint8_t* source;
	/** Destination buffer address */
	uint8_t* destination;
	/** Transfer size */
	uint32_t size;
};

/**
 * Set transfer size.
 * \param[in] m2m MEM2MEM peripheral base.
 * \param[in] transfer_size transfer unit size (see \ref mem2mem_transfer_size).
 */
__always_inline static void mem2mem_set_transfer_size(Mem2mem *m2m,
	enum mem2mem_transfer_size transfer_size)
{
	m2m->MEM2MEM_MR = transfer_size & MEM2MEM_MR_TSIZE_Msk;
}

/**
 * Enable interrupts
 * \param[in] m2m MEM2MEM peripheral base.
 * \param[in] sources Interrupts sources bitmap.
 */
__always_inline static void mem2mem_enable_interrupts(Mem2mem *m2m,
	enum mem2mem_interrupt_source sources)
{
	m2m->MEM2MEM_IER = sources;
}

/**
 * Disable interrupts
 * \param[in] m2m MEM2MEM peripheral base.
 * \param[in] sources Interrupts sources bitmap.
 */
__always_inline static void mem2mem_disable_interrupts(Mem2mem *m2m,
	enum mem2mem_interrupt_source sources)
{
	m2m->MEM2MEM_IDR = sources;
}

/**
 * Return interrupt mask
 * \param[in] m2m MEM2MEM peripheral base.
 */
__always_inline static uint32_t mem2mem_get_interrupt_mask(Mem2mem *m2m)
{
	return m2m->MEM2MEM_IMR;
}

/**
 * Return status
 * \param[in] m2m MEM2MEM peripheral base.
 */
__always_inline static uint32_t mem2mem_get_status(Mem2mem *m2m)
{
	return m2m->MEM2MEM_ISR;
}

/**
 * Return MEM2MEM PDC base
 * \param[in] m2m MEM2MEM peripheral base.
 */
__always_inline static Pdc *mem2mem_get_pdc_base(Mem2mem *m2m)
{
	return (Pdc*)((uint32_t)m2m + 0x100);
}

/**
 * Set mem2mem transfer
 * \param[in] m2m MEM2MEM peripheral base.
 * \param[in] source Source buffer address
 * \param[in] destination Destination buffer address
 * \param[in] size Transfer size
 */
__always_inline static void mem2mem_transfer_set(Mem2mem *m2m,
	uint8_t* source, uint8_t* destination, uint32_t size)
{
	m2m->MEM2MEM_TPR = (uint32_t)source;
	m2m->MEM2MEM_RPR = (uint32_t)destination;
	m2m->MEM2MEM_RCR =
	m2m->MEM2MEM_TCR = size;
}

/**
 * Set mem2mem next transfer
 * \param[in] m2m MEM2MEM peripheral base.
 * \param[in] source Source buffer address
 * \param[in] destination Destination buffer address
 * \param[in] size Transfer size
 */
__always_inline static void mem2mem_transfer_set_next(Mem2mem *m2m,
	uint8_t* source, uint8_t* destination, uint32_t size)
{
	m2m->MEM2MEM_TNPR = (uint32_t)source;
	m2m->MEM2MEM_RNPR = (uint32_t)destination;
	m2m->MEM2MEM_RNCR =
	m2m->MEM2MEM_TNCR = size;
}

/**
 * Initialize mem2mem transfer
 * \param[in] m2m MEM2MEM peripheral base.
 * \param[in] transfer PDC transfer descriptor
 * \param[in] next_transfer PDC next transfer descriptor
 */
__always_inline static void mem2mem_transfer_init(Mem2mem *m2m,
	struct mem2mem_transfer *transfer,
	struct mem2mem_transfer *next_transfer)
{
	if (transfer) {
		m2m->MEM2MEM_TPR = (uint32_t)transfer->source;
		m2m->MEM2MEM_RPR = (uint32_t)transfer->destination;
		m2m->MEM2MEM_RCR =
		m2m->MEM2MEM_TCR = transfer->size;
	}
	if (next_transfer) {
		m2m->MEM2MEM_TNPR = (uint32_t)next_transfer->source;
		m2m->MEM2MEM_RNPR = (uint32_t)next_transfer->destination;
		m2m->MEM2MEM_RNCR =
		m2m->MEM2MEM_TNCR = next_transfer->size;
	}
}

/**
 * Enable mem2mem transfer
 * \param[in] m2m MEM2MEM peripheral base.
 */
__always_inline static void mem2mem_transfer_enable(Mem2mem *m2m)
{
	m2m->MEM2MEM_PTCR = MEM2MEM_PTCR_RXTEN | MEM2MEM_PTCR_TXTEN;
}

/**
 * Disable mem2mem transfer
 * \param[in] m2m MEM2MEM peripheral base.
 */
__always_inline static void mem2mem_transfer_disable(Mem2mem *m2m)
{
	m2m->MEM2MEM_PTCR = MEM2MEM_PTCR_RXTDIS | MEM2MEM_PTCR_TXTDIS;
}

/**
 * Check if mem2mem transfer is enabled (in progress)
 * \param[in] m2m MEM2MEM peripheral base.
 */
__always_inline static bool mem2mem_transfer_is_enabled(Mem2mem *m2m)
{
	return ((m2m->MEM2MEM_PTSR & (MEM2MEM_PTSR_RXTEN | MEM2MEM_PTSR_TXTEN))
			== (MEM2MEM_PTSR_RXTEN | MEM2MEM_PTSR_TXTEN));
}

/** @} */

/**
 * \name MEM2MEM driver access (M2M)
 *
 * @{
 */

/** Forward definition of the MEM2MEM driver (M2M) instance */
struct m2m_module;
/** Type of the callback function for MEM2MEM driver (M2M) */
typedef void (*m2m_callback_t)(const struct m2m_module *const module);
/**
 * Callback types for MEM2MEM (M2M) callback driver
 */
enum m2m_callback_type {
	/** Callback for transfer done */
	M2M_CALLBACK_TRANSFER_END,
	/** Callback for any of transfer buffer done */
	M2M_CALLBACK_BUFFER_END,
#  if !defined(__DOXYGEN__)
	/** Number of available callbacks */
	M2M_CALLBACK_N
#  endif
};

/**
 * \name MEM2MEM (M2M) Module status flags
 *
 * M2M status flags, returned by \ref m2m_get_status().
 *
 * @{
 */

/** M2M End of (one of the) Buffer */
#define M2M_STATUS_BUFFER_END    (1UL << 0)
/** M2M Buffer Full (End of transfer) */
#define M2M_STATUS_TRANSFER_END  (1UL << 1)

/** @} */

/**
 * MEM2MEM (M2M) software driver instance structure.
 */
struct m2m_module {
	/** Base address for mem2mem peripheral */
	Mem2mem *hw;
	/** Callback functions */
	m2m_callback_t callbacks[M2M_CALLBACK_N];
	/** Bit mask for enabled callbacks */
	uint8_t enabled_callbacks;
	/** Status of the last job */
	volatile enum status_code job_status;
};

/**
 * MEM2MEM (M2M) configuration structure
 */
struct m2m_config {
	/** Transfer size used to transfer data */
	enum mem2mem_transfer_size transfer_size;
	/** Initialized with interrupt enabled, must be used for _init() */
	bool enable_irq;
};

/**
 * Possible M2M jobs.
 */
enum m2m_job_type {
	/** Transfer from memory to memory */
	M2M_JOB_TRANSFER,
	/** One of buffer from memory to memory */
	M2M_JOB_BUFFER
};

/**
 * \name Driver initialization and configuration
 * @{
 */

enum status_code m2m_init(struct m2m_module *const m2m, Mem2mem *hw,
		struct m2m_config *const cfg);

/**
 * \brief Initializes M2M configuration structure to defaults
 *
 * Initializes a given M2M configuration struct to a set of known default
 * values. This function should be called on any new instance of the
 * configuration struct before being modified by the user application.
 *
 * The default configuration is as follows:
 * - Transfer size is byte (8-bit)
 * - Interrupt enabled (for background transfer)
 *
 * \param[out] cfg Pointer to configuration struct to initialize to defaults
 */
__always_inline static void m2m_get_config_default(struct m2m_config *const cfg)
{
	Assert(cfg);
	cfg->transfer_size = MEM2MEM_TRANSFER_BYTE;
	cfg->enable_irq = true;
}

/**
 * \brief Change M2M configuration
 * \param[out] m2m         Pointer to the M2M software instance struct
 * \param[in]  cfg         Pointer to the configuration struct
 * \return Status of the configuration procedure
 * \retval STATUS_OK                The initialization was successful
 * \retval ERR_INVALID_ARG          Invalid argument(s) were provided
 * \retval ERR_BUSY                 The module is busy
 */
__always_inline static enum status_code m2m_set_config(
		struct m2m_module *const m2m,
		struct m2m_config *const cfg)
{
	Assert(m2m);
	Assert(m2m->hw);
	Assert(cfg);
	/* Transfer must be stopped (done/aborted) before initialization */
	if ((m2m->hw->MEM2MEM_PTSR & (MEM2MEM_PTSR_RXTEN | MEM2MEM_PTSR_TXTEN))) {
		return ERR_BUSY;
	}
	if (cfg->transfer_size > MEM2MEM_TRANSFER_DWORD) {
		return ERR_INVALID_ARG;
	}
	/* Initialize HW */
	m2m->hw->MEM2MEM_MR = cfg->transfer_size;
	return STATUS_OK;
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
 * \param[in] m2m  Pointer to the ADC software instance struct
 *
 * \return Bitmask of \c M2M_STATUS_* flags
 *
 * \retval M2M_STATUS_TRANSFER_END  All of PDC buffers are done
 * \retval M2M_STATUS_BUFFER_END    One of PDC buffer is done
 */
__always_inline static uint32_t m2m_get_status(struct m2m_module *const m2m)
{
	Assert(m2m);
	Assert(m2m->hw);
	uint32_t isr = m2m->hw->MEM2MEM_ISR;
	return isr; /* Since the bits in register and driver definition are same */
}
/** @} */

enum status_code m2m_transfer_wait(struct m2m_module *const m2m,
	const uint8_t* source, const uint8_t* destination, uint32_t length);


/**
 * \name Enable and disable interrupts
 * @{
 */

/**
 * \brief Enable interrupt
 *
 * Enable the given interrupt request from the MEM2MEM module (M2M).
 *
 * \param[in] m2m Pointer to the M2M software instance struct
 * \param[in] interrupt Interrupts to enable
 */
static inline void m2m_enable_interrupt(struct m2m_module *const m2m,
		enum mem2mem_interrupt_source interrupt)
{
	/* Sanity check arguments */
	Assert(m2m);
	Assert(m2m->hw);
	m2m->hw->MEM2MEM_IER = interrupt;
}

/**
 * \brief Disable interrupt
 *
 * Disable the given interrupt request from the MEM2MEM module (M2M`).
 *
 * \param[in] m2m Pointer to the M2M software instance struct
 * \param[in] interrupt Interrupt to disable
 */
static inline void m2m_disable_interrupt(struct m2m_module *const m2m,
		enum mem2mem_interrupt_source interrupt)
{
	/* Sanity check arguments */
	Assert(m2m);
	Assert(m2m->hw);
	m2m->hw->MEM2MEM_IDR = interrupt;
}

/** @} */

/**
 * \name Callback Management
 * @{
 */

void m2m_register_callback(struct m2m_module *const m2m,
	m2m_callback_t callback, enum m2m_callback_type type);

void m2m_unregister_callback(struct m2m_module *const m2m,
	enum m2m_callback_type type);

/**
 * \brief Enables callback
 *
 * Enables the callback function registered by \ref
 * m2m_register_callback. The callback function will be called from the
 * interrupt handler when the conditions for the callback type are met.
 *
 * \param[in]     m2m  Pointer to M2M software instance struct
 * \param[in]     type Callback type given by an enum
 */
__always_inline static void m2m_enable_callback(struct m2m_module *const m2m,
	enum m2m_callback_type type)
{
	Assert(m2m);
	Assert(m2m->hw);
	if (type < M2M_CALLBACK_N) {
		m2m->enabled_callbacks |= (1 << type);
	}
}

/**
 * \brief Disables callback
 *
 * Disables the callback function registered by the \ref
 * m2m_register_callback.
 *
 * \param[in]     m2m  Pointer to M2M software instance struct
 * \param[in]     type Callback type given by an enum
 */
__always_inline static void m2m_disable_callback(struct m2m_module *const m2m,
	enum m2m_callback_type type)
{
	Assert(m2m);
	Assert(m2m->hw);
	if (type < M2M_CALLBACK_N) {
		m2m->enabled_callbacks &= ~(1 << type);
	}
}

/** @} */

/**
 * \name Job Management
 * @{
 */

enum status_code m2m_transfer_job(struct m2m_module *const m2m,
	const uint8_t* source, const uint8_t* destination, uint32_t length);

enum status_code m2m_get_job_status(struct m2m_module *const m2m,
	enum m2m_job_type type);

void m2m_abort_job(struct m2m_module *const m2m, enum m2m_job_type type);

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
 * \page sam_m2m_quickstart Quick start guide for the SAM MEM2MEM driver (M2M)
 *
 * This is the quick start guide for the
 * \ref sam_drivers_m2m_group "MEM2MEM module",
 * with step-by-step instructions on how to configure and use the module driver
 * in a selection of use cases.
 *
 * Note that for peripheral MEM2MEM low level access APIs, prefix "MEM2MEM_" or
 * "mem2mem_" is used, for peripheral module driver a short prefix "M2M_" or
 * "m2m_" is used. The quick start guide will focus on usage of the M2M module
 * driver.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section m2m_use_cases M2M use cases
 * - \ref m2m_basic_use_case
 * - \subpage m2m_use_case_2
 *
 * \section m2m_basic_use_case  Basic use case - Transfer data and wait
 *
 * \section m2m_basic_use_case_setup Setup
 *
 * \subsection m2m_basic_use_case_setup_pre Prerequisites
 *
 * There is no special setup requirement for this use-case, since M2M driver has
 * included the following initialize steps for general peripheral use.
 *
 * - For the use of MEM2MEM peripheral, its clock should be enabled via
 *   \ref sam_drivers_pmc_group "PMC" or \ref clk_group "sysclk"
 *   (it's done in \ref m2m_init):
 *   \snippet mem2mem.c m2m_init_clock
 * - For the use of MEM2MEM interrupts, the interrupt handler should be
 *   implemented and interrupt should be enabled via NVIC (Note that in M2M
 *   driver, the interrupt support has been implemented and enabled by default)
 *   - Following function should be implemented for MEM2MEM interrupt service
 *     \code
	void MEM2MEM_Handler(void);
\endcode
 *   - MEM2MEM interrupt should be enabled on initialization
 *     \snippet mem2mem.c m2m_init_irq
 *
 * \subsection m2m_basic_use_case_setup_code Code
 *
 * - Add module driver instance to the main application source file, outside of
 *   any functions:
 *   \snippet example.c driver_instance
 * - Add local/global values to use by M2M APIs:
 *   \snippet example.c main_values
 * - Add following code to initialize driver:
 *   \snippet example.c main_driver_init
 *
 * \section m2m_basic_use_case_usage Use case
 * Transfer data and waiting.
 *
 * \subsection m2m_basic_use_case_usage_code Example code
 * \snippet example.c main_transfer_wait
 *
 * \subsection m2m_basic_use_case_usage_flow Workflow
 * -# Create a module software instance structure for the MEM2MEM module to
 *    store the MEM2MEM driver (M2M) state while it is in use.
 *    \note This should never go out of scope as long as the module is in use.
 *          In most cases, this should be global.
 *    \snippet example.c driver_instance
 * -# Configure the M2M module
 *    -# Create a M2M module configuration struct, which can be filled out to
 *       adjust the configuration of a physical MEM2MEM peripheral.
 *       \snippet example.c main_config
 *    -# Initialize the M2M configuration struct with the module's default
 *       values.
 *       \note This should always be performed before using the configuration
 *             struct to ensure that all values are initialized to know default
 *             settings.
 *       \snippet example.c main_config_init
 *    -# Initialize M2M driver
 *       \snippet example.c main_driver_init
 * -# Now you can transfer data and polling status to wait until transfer finish
 *    via \ref m2m_transfer_wait()
 *    \snippet example.c main_transfer_wait
 */
/**
 * \page m2m_use_case_2 Advanced use case - Transfer data in background job
 * In this case, the MEM2MEM module is configured to transfer data without
 * CPU intervention. Callbacks will be invoked after transfer is done.
 *
 * \section m2m_use_case_2_setup Setup
 * The first steps of setup is the same as basic use, refer to
 * \ref m2m_basic_use_case_setup "Basic Setup" for basic setup details.
 *
 * \subsection m2m_use_case_2_setup_code Code
 * - Add basic setup
 *   - Add module driver instance to the main application source file, outside
 *     of any functions:
 *     \snippet example.c driver_instance
 *   - Add local/global values to use by M2M APIs:
 *     \snippet example.c main_values
 *   - Add following code to initialize driver:
 *     \snippet example.c main_driver_init
 * - Add callback setup
 *   - Add following global variable to use by callback function:
 *     \snippet example.c transfer_done
 *   - Add following callback function
 *     \snippet example.c _transfer_done
 *   - Add following code to register and enable callback handler
 *     \snippet example.c main_callback_register
 *
 * \section m2m_use_case_2_usage Use case
 * Start data transfer job and waiting interrupt callback.
 *
 * \subsection m2m_use_case_2_usage_code Example code
 * - Transfer job with callback
 *   \snippet example.c main_transfer_job_callback
 * - Transfer job without callback
 *   \snippet example.c main_transfer_job
 *
 * \subsection m2m_basic_use_case_usage_flow Workflow
 * Note that the first two steps are same as
 * \ref m2m_basic_use_case_usage_flow "Basic Workflow".
 * -# Create a module software instance structure for the MEM2MEM module to
 *    store the MEM2MEM driver (M2M) state while it is in use.
 *    \snippet example.c driver_instance
 * -# Configure the M2M module
 *    -# Create a M2M module configuration struct, which can be filled out to
 *       adjust the configuration of a physical MEM2MEM peripheral.
 *       \snippet example.c main_config
 *    -# Initialize the M2M configuration struct with the module's default
 *       values.
 *       \snippet example.c main_config_init
 *    -# Initialize M2M driver
 *       \snippet example.c main_driver_init
 * -# Configure the callback
 *    -# Create a callback function, which is invoked when MEM2MEM interrupt
 *       happens (transfer done interrupt), the callback set a flag to indicate
 *       transfer finish.
 *       \snippet example.c transfer_done
 *       \snippet example.c _transfer_done
 *    -# Register and enable the callback
 *       \snippet example.c main_callback_register
 * -# Now you can start transfer job via \ref m2m_transfer_job()
 *    - With callback used
 *      \snippet example.c main_transfer_job_callback
 *    - Without callback used
 *      \snippet example.c main_transfer_job
 */

#endif /* MEM2MEM_H_INCLUDED */

