/**
 * \file
 *
 * \brief MEM2MEM driver for SAM.
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

#include "mem2mem.h"
#include "sysclk.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \defgroup sam_drivers_m2m_group Memory-to-Memory (MEM2MEM) Driver (M2M)
 *
 * \par Purpose
 *
 * The Memory-to-Memory module allows the PDC to perform memory to memory
 * transfer without CPU intervention.
 * @{
 */

static struct m2m_module *_m2m_instances[1];

/**
 * \brief MEM2MEM Interrupt Handler
 */
void MEM2MEM_Handler(void)
{
	struct m2m_module *m2m = _m2m_instances[0];
	uint32_t isr = m2m->hw->MEM2MEM_ISR;
	/* All of the buffer done */
	if (isr & MEM2MEM_ISR_RXBUFF) {
		/* Disable PDC */
		m2m->hw->MEM2MEM_PTCR = (MEM2MEM_PTCR_RXTDIS | MEM2MEM_PTCR_TXTDIS);
		/* Disable Interrupts */
		m2m->hw->MEM2MEM_IDR = 0xFFFFFFFF;
		/* Change job status */
		m2m->job_status = STATUS_OK;
		/* Callback */
		if ((m2m->enabled_callbacks & (1 << M2M_CALLBACK_TRANSFER_END))
			&& m2m->callbacks[M2M_CALLBACK_TRANSFER_END]) {
			m2m->callbacks[M2M_CALLBACK_TRANSFER_END](m2m);
		}
	}
	/* One of the buffer done */
	else if (isr & MEM2MEM_ISR_RXEND) {
		/* Stop PDC (Pause and then start again after callback) */
		m2m->hw->MEM2MEM_PTCR = (MEM2MEM_PTCR_RXTDIS | MEM2MEM_PTCR_TXTDIS);
		/* Disable Interrupt */
		m2m->hw->MEM2MEM_IDR = MEM2MEM_IDR_RXEND;
		/* Callback */
		if ((m2m->enabled_callbacks & (1 << M2M_CALLBACK_BUFFER_END))
			&& m2m->callbacks[M2M_CALLBACK_BUFFER_END]) {
			m2m->callbacks[M2M_CALLBACK_BUFFER_END](m2m);
		}
		/* Continue PDC */
		m2m->hw->MEM2MEM_PTCR = (MEM2MEM_PTCR_RXTEN | MEM2MEM_PTCR_TXTEN);
	}
}

/**
 * \brief Initializes the MEM2MEM driver (M2M)
 *
 * Initializes the M2M struct and the hardware module based on the
 * given configuration struct values.
 *
 * \param[out] m2m         Pointer to the M2M software instance struct
 * \param[in]  hw          Pointer to the MEM2MEM hardware instance
 * \param[in]  cfg         Pointer to the configuration struct
 *
 * \return Status of the initialization procedure
 * \retval STATUS_OK                The initialization was successful
 * \retval ERR_INVALID_ARG          Invalid argument(s) were provided
 * \retval ERR_BUSY                 The module is busy
 */
enum status_code m2m_init(struct m2m_module *const m2m, Mem2mem *hw,
		struct m2m_config *const cfg)
{
	uint32_t i;
	Assert(m2m);
	Assert(hw);
	Assert(cfg);
	/* HW base init */
	m2m->hw = hw;
// [m2m_init_clock]
	/* Enable PMC clock */
	sysclk_enable_peripheral_clock(ID_MEM2MEM);
// [m2m_init_clock]
	/* Transfer must be stopped (done/aborted) before initialization */
	if ((hw->MEM2MEM_PTSR & (MEM2MEM_PTSR_RXTEN | MEM2MEM_PTSR_TXTEN))) {
		return ERR_BUSY;
	}
	if (cfg->transfer_size > MEM2MEM_TRANSFER_DWORD) {
		return ERR_INVALID_ARG;
	}
	/* Initialize HW */
	hw->MEM2MEM_MR = cfg->transfer_size;

	/* For IRQ handler to access module instance */
	_m2m_instances[0] = m2m;
	/* Initialize for Jobs */
	for (i = 0; i < M2M_CALLBACK_N; i ++) {
		m2m->callbacks[i] = NULL;
	}
	m2m->enabled_callbacks = 0;
	m2m->job_status = STATUS_OK;

	if (cfg->enable_irq) {
// [m2m_init_irq]
		/* Initialize IRQ handler */
		NVIC_EnableIRQ(MEM2MEM_IRQn);
// [m2m_init_irq]
	} else {
		NVIC_DisableIRQ(MEM2MEM_IRQn);
	}
	return STATUS_OK;
}

/**
 * \brief Blocking transfer buffer through M2M
 *
 * Read \c length units of data from the \c source into the \c destination.
 * 
 *
 * \param[in]  m2m         Pointer to M2M software instance struct
 * \param[in]  source      Source memory address
 * \param[out] destination Destiniation memory address
 * \param[in]  length      Length of data, in units of predefined
 *                         \ref mem2mem_transfer_size.
 *
 * \return Status of the transfer.
 * \retval STATUS_OK Data transfered all right
 * \retval ERR_BUSY  The job is running
 */
enum status_code m2m_transfer_wait(struct m2m_module *const m2m,
	const uint8_t* source, const uint8_t* destination, uint32_t length)
{
	Assert(m2m);
	Assert(m2m->hw);
	/* Transfer must be stopped (aborted) before initialization */
	if (m2m->hw->MEM2MEM_PTSR & (MEM2MEM_PTSR_RXTEN | MEM2MEM_PTSR_TXTEN)) {
		return ERR_BUSY;
	}
	if (length == 0) {
		return STATUS_OK;
	}
	/* Status: Busy */
	m2m->job_status = ERR_BUSY;
	/* Disable interrupts */
	m2m->hw->MEM2MEM_IDR = 0xFFFFFFFF;
	/* Prepare PDC transfer */
	m2m->hw->MEM2MEM_TPR = (uint32_t)source;
	m2m->hw->MEM2MEM_RPR = (uint32_t)destination;
	m2m->hw->MEM2MEM_RCR =
	m2m->hw->MEM2MEM_TCR = length;
	/* Start PDC transfer */
	m2m->hw->MEM2MEM_PTCR = (MEM2MEM_PTCR_RXTEN | MEM2MEM_PTCR_TXTEN);
	/* Wait until transfer done */
	while (0 == (m2m->hw->MEM2MEM_ISR & MEM2MEM_ISR_RXEND));
	/* Stop PDC transfer */
	m2m->hw->MEM2MEM_PTCR = (MEM2MEM_PTCR_RXTDIS | MEM2MEM_PTCR_TXTDIS);
	/* Status: OK */
	m2m->job_status = STATUS_OK;
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
 * \param[in] m2m       Pointer to M2M software instance struct
 * \param[in] callback  Pointer to callback function
 * \param[in] type      Callback type given by an enum
 *
 */
void m2m_register_callback(struct m2m_module *const m2m,
	m2m_callback_t callback, enum m2m_callback_type type)
{
	Assert(m2m);
	Assert(callback);
	if (type < M2M_CALLBACK_N) {
		m2m->callbacks[type] = callback;
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
 * \param[in] m2m       Pointer to M2M software instance struct
 * \param[in] type      Callback type given by an enum
 *
 */
void m2m_unregister_callback(struct m2m_module *const m2m,
	enum m2m_callback_type type)
{
	Assert(m2m);
	if (type < M2M_CALLBACK_N) {
		m2m->callbacks[type] = NULL;
	}
}

/**
 * \brief None-blocking transfer buffer through M2M
 *
 * Read \c length units of data from the \c source into the \c destination.
 *
 * \param[in]  m2m         Pointer to M2M software instance struct
 * \param[in]  source      Source memory address
 * \param[out] destination Destiniation memory address
 * \param[in]  length      Length of data, in units of predefined
 *                         \ref mem2mem_transfer_size.
 *
 * \return Status of the job start.
 * \retval STATUS_OK Job started or queued successful
 * \retval ERR_BUSY  The queue is full
 */
enum status_code m2m_transfer_job(struct m2m_module *const m2m,
	const uint8_t* source, const uint8_t* destination, uint32_t length)
{
	Mem2mem *hw;
	Assert(m2m);
	Assert(m2m->hw);

	/* Nothing to transfer, done */
	if (length == 0) {
		return STATUS_OK;
	}
	hw = m2m->hw;
	if (m2m->job_status == ERR_BUSY) {
		if (hw->MEM2MEM_RNCR > 0) {
			return ERR_BUSY;
		}
		/* Append buffer */
		hw->MEM2MEM_TNPR = (uint32_t)source;
		hw->MEM2MEM_RNPR = (uint32_t)destination;
		hw->MEM2MEM_RNCR =
		hw->MEM2MEM_TNCR = length;
		/* Enable interrupt */
		hw->MEM2MEM_IER = MEM2MEM_IER_RXEND;
		/* PDC is already running */
	} else {
	  	m2m->job_status = ERR_BUSY;
		/* Start job */
		hw->MEM2MEM_TPR = (uint32_t)source;
		hw->MEM2MEM_RPR = (uint32_t)destination;
		hw->MEM2MEM_RCR =
		hw->MEM2MEM_TCR = length;
		/* Enable interrupt */
		hw->MEM2MEM_IER = MEM2MEM_IER_RXBUFF;
		/* Callback to append buffer */
		if (m2m->enabled_callbacks & (1 << M2M_CALLBACK_BUFFER_END)) {
			m2m->callbacks[M2M_CALLBACK_BUFFER_END](m2m);
		}
		/* Start PDC */
		hw->MEM2MEM_PTCR = (MEM2MEM_PTCR_RXTEN | MEM2MEM_PTCR_TXTEN);
	}
	return STATUS_OK;
}

/**
 * \brief Gets the status of a job
 *
 * Gets the status of an ongoing or the last job.
 *
 * \param [in]  m2m    Pointer to the ADC software instance struct
 * \param [in]  type   Type of job to check
 *
 * \return Status of the job
 * \retval STATUS_OK Transfer finished/One of buffer done
 * \retval ERR_BUSY  Transfer in progress
 * \retval ERR_INVALID_ARG \c type is not valid
 */
enum status_code m2m_get_job_status(struct m2m_module *const m2m,
	enum m2m_job_type type)
{
	Assert(m2m);
	if (M2M_JOB_TRANSFER == type) {
		return m2m->job_status;
	} else if (M2M_JOB_BUFFER == type) {
		if (ERR_BUSY == m2m->job_status) {
			return (0 == m2m->hw->MEM2MEM_RCR) ? STATUS_OK : ERR_BUSY;
		} else {
			return m2m->job_status;
		}
	} else {
		return ERR_INVALID_ARG;
	}
}

/**
 * \brief Aborts all ongoing jobs
 *
 * Aborts all ongoing jobs.
 *
 * \param [in]  m2m    Pointer to the M2M software instance struct
 * \param [in]  type   Type of job to abort
 */
void m2m_abort_job(struct m2m_module *const m2m, enum m2m_job_type type)
{
	Assert(m2m);
	Assert(m2m->hw);
	UNUSED(type);
	/* Disable PDC */
	m2m->hw->MEM2MEM_PTCR = (MEM2MEM_PTCR_RXTDIS | MEM2MEM_PTCR_TXTDIS);
	/* Disable interrupts */
	m2m->hw->MEM2MEM_IDR = 0xFFFFFFFF;
	/* Mark job aborted */
	m2m->job_status = ERR_ABORTED;
}


/** @} */

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
