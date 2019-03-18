/**
 * \file
 *
 * \brief SAM Serial Peripheral Interface Driver (Callback Mode)
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

#ifndef SPI_INTERRUPT_H_INCLUDED
#define SPI_INTERRUPT_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup asfdoc_sam0_sercom_spi_group
 *
 * @{
 */

#include "spi.h"

/**
 * \name Callback Management
 * @{
 */

void spi_register_callback(
		struct spi_module *const module,
		spi_callback_t callback_func,
		enum spi_callback callback_type);

void spi_unregister_callback(
		struct spi_module *module,
		enum spi_callback callback_type);

/**
 * \brief Enables an SPI callback of a given type
 *
 * Enables the callback function registered by the \ref spi_register_callback.
 * The callback function will be called from the interrupt handler when the
 * conditions for the callback type are met.
 *
 * \param[in] module         Pointer to SPI software instance struct
 * \param[in] callback_type  Callback type given by an enum
 */
static inline void spi_enable_callback(
		struct spi_module *const module,
		enum spi_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Enable callback */
	module->enabled_callback |= (1 << callback_type);
}

/**
 * \brief Disables callback
 *
 * Disables the callback function registered by the \ref spi_register_callback,
 * and the callback will not be called from the interrupt routine.
 *
 * \param[in] module         Pointer to SPI software instance struct
 * \param[in] callback_type  Callback type given by an enum
 */
static inline void spi_disable_callback(
		struct spi_module *const module,
		enum spi_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Disable callback */
	module->enabled_callback &= ~(1 << callback_type);
}

/** @} */


/**
 * \name Writing and Reading
 * @{
 */
enum status_code spi_write_buffer_job(
		struct spi_module *const module,
		uint8_t *tx_data,
		uint16_t length);

enum status_code spi_read_buffer_job(
		struct spi_module *const module,
		uint8_t *rx_data,
		uint16_t length,
		uint16_t dummy);

enum status_code spi_transceive_buffer_job(
		struct spi_module *const module,
		uint8_t *tx_data,
		uint8_t *rx_data,
		uint16_t length);

void spi_abort_job(
		struct spi_module *const module);

/**
 * \brief Retrieves the current status of a job.
 *
 * Retrieves the current status of a job that was previously issued.
 *
 * \param[in]  module    Pointer to SPI software instance struct
 *
 * \return Current job status.
 */
static inline enum status_code spi_get_job_status(
		const struct spi_module *const module)
{
	return module->status;
}

/**
 * \brief Retrieves the status of job once it ends.
 *
 * Waits for current job status to become non-busy, then returns its value.
 *
 * \param[in]  module    Pointer to SPI software instance struct
 *
 * \return Current non-busy job status.
 */
static inline enum status_code spi_get_job_status_wait(
		const struct spi_module *const module)
{
	enum status_code status;

	do {
		status = spi_get_job_status(module);
	} while (status == STATUS_BUSY);

	return status;
}

/** @} */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* SPI_INTERRUPT_H_INCLUDED */
