/**
 * \file
 *
 * \brief FreeRTOS Peripheral Control API For the TWIHS
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

/* Standard includes. */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <string.h>

/* ASF includes. */
#include "twihs_master.h"
#include "freertos_twihs_master.h"
#include "freertos_peripheral_control_private.h"

/* Every bit in the interrupt mask. */
#define MASK_ALL_INTERRUPTS     (0xffffffffUL)
/* TWIHS timeout counter */
#define TWIHS_TIMEOUT_COUNTER    (0xffffffffUL)

/* Interrupts that are enabled to catch error conditions on the bus. */
#define SR_ERROR_INTERRUPTS  (TWIHS_SR_NACK | TWIHS_SR_ARBLST | TWIHS_SR_OVRE)
#define IER_ERROR_INTERRUPTS (TWIHS_IER_NACK | TWIHS_IER_ARBLST | TWIHS_IER_OVRE)

/* Work out how many TWIHS ports with PDC supported are present. */
#define MAX_TWIHS                                (1)

/* A common interrupt handler definition used by all the TWIHS peripherals. */
static void local_twihs_handler(const portBASE_TYPE twihs_index);

/* Structures to manage the DMA control for both Rx and Tx transactions. */
static freertos_dma_event_control_t tx_dma_control[MAX_TWIHS];
static freertos_dma_event_control_t rx_dma_control[MAX_TWIHS];

/* Structure to manage the end of a read transaction */
struct twihs_module {
	uint8_t *buffer;
	uint32_t length;
};

/* Structures to manage the DMA control for both Rx and Tx transactions. */
static struct twihs_module twihss[MAX_TWIHS];

/* Used to detect the init function being called after any part of the DMA
control structure has already been initialilsed - indicating an error
condition as init should only be called once per port. */
static const freertos_dma_event_control_t null_dma_control = {NULL, NULL};

/* Create an array that holds the information required about each defined TWIHS
 * peripheral. */
static const freertos_pdc_peripheral_parameters_t all_twihs_definitions[MAX_TWIHS] = {
	{TWI0, PDC_TWI0, ID_TWI0, TWI0_IRQn},
};

/**
 * \ingroup freertos_twihs_peripheral_control_group
 * \brief Initializes the FreeRTOS ASF TWIHS (I2C) master driver for the specified
 * TWIHS port.
 *
 * freertos_twihs_master_init() is an ASF specific FreeRTOS driver function.  It
 * must be called before any other ASF specific FreeRTOS driver functions
 * attempt to access the same TWIHS port.
 *
 * If freertos_driver_parameters->operation_mode equals TWIHS_I2C_MASTER then
 * freertos_twihs_master_init() will configure the TWIHS port for master mode
 * operation and enable the peripheral.  If
 * freertos_driver_parameters->operation_mode equals any other value then
 * freertos_twihs_master_init() will not take any action.
 *
 * Other ASF TWIHS functions can be called after freertos_twihs_master_init() has
 * completed successfully.
 *
 * The FreeRTOS ASF driver both installs and handles the TWIHS PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * This driver is provided with an application note, and an example project that
 * demonstrates the use of this function.
 *
 * \param p_twihs    The twihs peripheral being initialized.
 * \param freertos_driver_parameters    Defines the driver behavior.  See the
 *    freertos_peripheral_options_t documentation, and the application note that
 *    accompanies the ASF specific FreeRTOS functions.
 *
 * \return If the initialization completes successfully then a handle that can
 *     be used with FreeRTOS TWIHS read and write functions is returned.  If
 *     the initialisation fails then NULL is returned.
 */
freertos_twihs_if freertos_twihs_master_init(Twihs *p_twihs,
		const freertos_peripheral_options_t *const freertos_driver_parameters)
{
	portBASE_TYPE twihs_index;
	bool is_valid_operating_mode;
	freertos_twihs_if return_value;
	const enum peripheral_operation_mode valid_operating_modes[] = {TWIHS_I2C_MASTER};

	/* Find the index into the all_twihs_definitions array that holds details of
	the p_twihs peripheral. */
	twihs_index = get_pdc_peripheral_details(all_twihs_definitions, MAX_TWIHS,
			(void *) p_twihs);

	/* Check the requested operating mode is valid for the peripheral. */
	is_valid_operating_mode = check_requested_operating_mode(
			freertos_driver_parameters->operation_mode,
			valid_operating_modes,
			sizeof(valid_operating_modes) /
			sizeof(enum peripheral_operation_mode));

	/* Don't do anything unless a valid p_twihs pointer was used, and a valid
	operating mode was requested. */
	if ((twihs_index < MAX_TWIHS) && (is_valid_operating_mode == true)) {
		/* This function must be called exactly once per supported twihs.  Check
		it has not been called	before. */
		configASSERT(memcmp((void *)&(tx_dma_control[twihs_index]),
				&null_dma_control,
				sizeof(null_dma_control)) == 0);
		configASSERT(memcmp((void *)&(rx_dma_control[twihs_index]),
				&null_dma_control,
				sizeof(null_dma_control)) == 0);

		/* Enable the peripheral's clock. */
		pmc_enable_periph_clk(
				all_twihs_definitions[twihs_index].peripheral_id);

		/* Ensure everything is disabled before configuration. */
		pdc_disable_transfer(
				all_twihs_definitions[twihs_index].pdc_base_address,
				(PERIPH_PTCR_RXTDIS | PERIPH_PTCR_TXTDIS));
		twihs_disable_interrupt(
				all_twihs_definitions[twihs_index].peripheral_base_address,
				MASK_ALL_INTERRUPTS);
		twihs_reset(
				all_twihs_definitions[twihs_index].peripheral_base_address);

		switch (freertos_driver_parameters->operation_mode) {
		case TWIHS_I2C_MASTER:
			/* Call the standard ASF init function. */
			twihs_enable_master_mode(
					all_twihs_definitions[twihs_index].peripheral_base_address);
			break;

		default:
			/* No other modes are currently supported. */
			break;
		}

		/* Create any required peripheral access mutexes and transaction complete
		semaphores.  This peripheral is half duplex so only a single access
		mutex is required. */
		create_peripheral_control_semaphores(
				freertos_driver_parameters->options_flags,
				&(tx_dma_control[twihs_index]),
				&(rx_dma_control[twihs_index]));

		/* Error interrupts are always enabled. */
		twihs_enable_interrupt(
				all_twihs_definitions[twihs_index].peripheral_base_address,
				IER_ERROR_INTERRUPTS);

		/* Configure and enable the TWIHS interrupt in the interrupt controller. */
		configure_interrupt_controller(
				all_twihs_definitions[twihs_index].peripheral_irq,
				freertos_driver_parameters->interrupt_priority);

		return_value = (freertos_twihs_if) p_twihs;
	} else {
		return_value = NULL;
	}

	return return_value;
}

/**
 * \ingroup freertos_twihs_peripheral_control_group
 * \brief Initiate a completely asynchronous multi-byte write operation on a TWIHS
 * peripheral.
 *
 * freertos_twihs_write_packet_async() is an ASF specific FreeRTOS driver function.
 * It configures the TWIHS peripheral DMA controller (PDC) to transmit data on the
 * TWIHS port, then returns.  freertos_twihs_write_packet_async() does not wait for
 * the transmission to complete before returning.
 *
 * The FreeRTOS TWIHS driver is initialized using a call to
 * freertos_twihs_master_init().  The freertos_driver_parameters.options_flags
 * parameter passed into the initialization function defines the driver behavior.
 * freertos_twihs_write_packet_async() can only be used if the
 * freertos_driver_parameters.options_flags parameter passed to the initialization
 * function had the WAIT_TX_COMPLETE bit clear.
 *
 * freertos_twihs_write_packet_async() is an advanced function and readers are
 * recommended to also reference the application note and examples that
 * accompany the FreeRTOS ASF drivers.  freertos_twihs_write_packet() is a version
 * that does not exit until the PDC transfer is complete, but still allows other
 * RTOS tasks to execute while the transmission is in progress.
 *
 * The FreeRTOS ASF driver both installs and handles the TWIHS PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * \param p_twihs    The handle to the TWIHS peripheral returned by the
 *     freertos_twihs_master_init() call used to initialise the peripheral.
 * \param p_packet    Structure that defines the TWIHS transfer parameters, such
 *     as the I2C chip being addressed, the source data location, and the number
 *     of bytes to transmit.  twihs_packet_t is a standard ASF type (it is not
 *     FreeRTOS specific).
 * \param block_time_ticks    The FreeRTOS ASF TWIHS driver is initialized using a
 *     call to freertos_twihs_master_init().  The
 *     freertos_driver_parameters.options_flags parameter passed to the
 *     initialization function defines the driver behavior.  If
 *     freertos_driver_parameters.options_flags had the USE_TX_ACCESS_SEM bit
 *     set, then the driver will only write to the TWIHS peripheral if it has
 *     first gained exclusive access to it.  block_time_ticks specifies the
 *     maximum amount of time the driver will wait to get exclusive access
 *     before aborting the write operation.  Other tasks will execute during any
 *     waiting time.  block_time_ticks is specified in RTOS tick periods.  To
 *     specify a block time in milliseconds, divide the milliseconds value by
 *     portTICK_RATE_MS, and pass the result in block_time_ticks.
 *     portTICK_RATE_MS is defined by FreeRTOS.
 * \param notification_semaphore    The RTOS task that calls the transmit
 *     function exits the transmit function as soon as the transmission starts.
 *     The data being transmitted by the PDC must not be modified until after
 *     the transmission has completed.  The PDC interrupt (handled internally by
 *     the FreeRTOS ASF driver) 'gives' the semaphore when the PDC transfer
 *     completes.  The notification_semaphore therefore provides a mechanism for
 *     the calling task to know when the PDC has finished accessing the data.
 *     The calling task can call standard FreeRTOS functions to block on the
 *     semaphore until the PDC interrupt occurs.  Other RTOS tasks will execute
 *     while the the calling task is in the Blocked state.  The semaphore must
 *     be created using the FreeRTOS vSemaphoreCreateBinary() API function
 *     before it is used as a parameter.
 *
 * \return     ERR_INVALID_ARG is returned if an input parameter is invalid.
 *     ERR_TIMEOUT is returned if block_time_ticks passed before exclusive
 *     access to the TWIHS peripheral could be obtained.  STATUS_OK is returned if
 *     the PDC was successfully configured to perform the TWIHS write operation.
 */
status_code_t freertos_twihs_write_packet_async(freertos_twihs_if p_twihs,
		twihs_packet_t *p_packet, portTickType block_time_ticks,
		xSemaphoreHandle notification_semaphore)
{
	status_code_t return_value;
	portBASE_TYPE twihs_index;
	Twihs *twihs_base;
	uint32_t internal_address = 0;

	twihs_base = (Twihs *) p_twihs;
	twihs_index = get_pdc_peripheral_details(all_twihs_definitions, MAX_TWIHS,
			(void *) twihs_base);

	/* Don't do anything unless a valid TWIHS pointer was used. */
	if ((twihs_index < MAX_TWIHS) && (p_packet->length > 0)) {
		return_value = freertos_obtain_peripheral_access_semphore(
				&(tx_dma_control[twihs_index]), &block_time_ticks);

		if (return_value == STATUS_OK) {
			/* Set write mode and slave address. */
			twihs_base->TWIHS_MMR = 0;
			twihs_base->TWIHS_MMR = TWIHS_MMR_DADR(p_packet->chip) |
					((p_packet->addr_length <<
					TWIHS_MMR_IADRSZ_Pos) &
					TWIHS_MMR_IADRSZ_Msk);

			/* Set internal address if any. */
			if (p_packet->addr_length > 0) {
				internal_address = p_packet->addr[0];
				if (p_packet->addr_length > 1) {
					internal_address <<= 8;
					internal_address |= p_packet->addr[1];
				}

				if (p_packet->addr_length > 2) {
					internal_address <<= 8;
					internal_address |= p_packet->addr[2];
				}
			}
			twihs_base->TWIHS_IADR = internal_address;

			if (p_packet->length == 1) {
				uint32_t status;
				uint32_t timeout_counter = 0;
				/* Do not handle errors for short packets in interrupt handler */
				twihs_disable_interrupt(
						all_twihs_definitions[twihs_index].peripheral_base_address,
						IER_ERROR_INTERRUPTS);
				/* Send start condition */
				twihs_base->TWIHS_THR = *((uint8_t*)(p_packet->buffer));
				while (1) {
					status = twihs_base->TWIHS_SR;
					if (status & TWIHS_SR_NACK) {
						/* Re-enable interrupts */
						twihs_enable_interrupt(
								all_twihs_definitions[twihs_index].peripheral_base_address,
								IER_ERROR_INTERRUPTS);
						/* Release semaphore */
						xSemaphoreGive(tx_dma_control[twihs_index].peripheral_access_sem);
						return TWIHS_RECEIVE_NACK;
					}
					if (status & TWIHS_SR_TXRDY) {
						break;
					}
					/* Check timeout condition. */
					if (++timeout_counter >= TWIHS_TIMEOUT_COUNTER) {
						return_value = ERR_TIMEOUT;
						break;
					}
				}
				twihs_base->TWIHS_CR = TWIHS_CR_STOP;
				/* Wait for TX complete */
				while (!(twihs_base->TWIHS_SR & TWIHS_SR_TXCOMP)) {
					/* Check timeout condition. */
					if (++timeout_counter >= TWIHS_TIMEOUT_COUNTER) {
						return_value = ERR_TIMEOUT;
						break;
					}
				}

				/* Re-enable interrupts */
				twihs_enable_interrupt(
						all_twihs_definitions[twihs_index].peripheral_base_address,
						IER_ERROR_INTERRUPTS);
				/* Release semaphores */
				xSemaphoreGive(tx_dma_control[twihs_index].peripheral_access_sem);
			} else {

				twihss[twihs_index].buffer = p_packet->buffer;
				twihss[twihs_index].length = p_packet->length;

				freertos_start_pdc_tx(&(tx_dma_control[twihs_index]),
						p_packet->buffer, p_packet->length,
						all_twihs_definitions[twihs_index].pdc_base_address,
						notification_semaphore);

				/* Catch the end of transmission so the access mutex can be
				returned, and the task notified (if it supplied a notification
				semaphore).  The interrupt can be enabled here because the ENDTX
				signal from the PDC to the peripheral will have been de-asserted when
				the next transfer was configured. */
				twihs_enable_interrupt(twihs_base, TWIHS_IER_ENDTX);

				return_value = freertos_optionally_wait_transfer_completion(
						&(tx_dma_control[twihs_index]),
						notification_semaphore,
						block_time_ticks);
			}
		}
	} else {
		return_value = ERR_INVALID_ARG;
	}

	return return_value;
}

/**
 * \ingroup freertos_twihs_peripheral_control_group
 * \brief Initiate a completely asynchronous multi-byte read operation on an TWIHS
 * peripheral.
 *
 * freertos_twihs_read_packet_async() is an ASF specific FreeRTOS driver function.
 * It configures the TWIHS peripheral DMA controller (PDC) to read data from the
 * TWIHS port, then returns.  freertos_twihs_read_packet_async() does not wait for
 * the reception to complete before returning.
 *
 * The FreeRTOS ASF TWIHS driver is initialized using a call to
 * freertos_twihs_master_init().  The freertos_driver_parameters.options_flags
 * parameter passed into the initialization function defines the driver behavior.
 * freertos_twihs_read_packet_async() can only be used if the
 * freertos_driver_parameters.options_flags parameter passed to the initialization
 * function had the WAIT_RX_COMPLETE bit clear.
 *
 * freertos_twihs_read_packet_async() is an advanced function and readers are
 * recommended to also reference the application note and examples that
 * accompany the FreeRTOS ASF drivers.  freertos_twihs_read_packet() is a version
 * that does not exit until the PDC transfer is complete, but still allows other
 * RTOS tasks to execute while the transmission is in progress.
 *
 * The FreeRTOS ASF driver both installs and handles the TWIHS PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * \param p_twihs    The handle to the TWIHS port returned by the
 *     freertos_twihs_master_init() call used to initialise the port.
 * \param p_packet    Structure that defines the TWIHS transfer parameters, such
 *     as the I2C chip being addressed, the destination for the data being read,
 *     and the number of bytes to read.  twihs_packet_t is a standard ASF type (it
 *     is not FreeRTOS specific).
 * \param block_time_ticks    The FreeRTOS ASF TWIHS driver is initialized using a
 *     call to freertos_twihs_master_init().  The
 *     freertos_driver_parameters.options_flags parameter passed to the
 *     initialization function defines the driver behavior.  If
 *     freertos_driver_parameters.options_flags had the USE_RX_ACCESS_MUTEX bit
 *     set, then the driver will only read from the TWIHS peripheral if it has
 *     first gained exclusive access to it.  block_time_ticks specifies the
 *     maximum amount of time the driver will wait to get exclusive access
 *     before aborting the read operation.  Other tasks will execute during any
 *     waiting time.  block_time_ticks is specified in RTOS tick periods.  To
 *     specify a block time in milliseconds, divide the milliseconds value by
 *     portTICK_RATE_MS, and pass the result in block_time_ticks.
 *     portTICK_RATE_MS is defined by FreeRTOS.
 * \param notification_semaphore    The RTOS task that calls the receive
 *     function exits the receive function as soon as the reception starts.
 *     The data being received by the PDC cannot normally be processed until
 *     after the reception has completed.  The PDC interrupt (handled internally
 *     by the FreeRTOS ASF driver) 'gives' the semaphore when the PDC transfer
 *     completes.  The notification_semaphore therefore provides a mechanism for
 *     the calling task to know when the PDC has read the requested number of
 *     bytes.  The calling task can call standard FreeRTOS functions to block on
 *     the semaphore until the PDC interrupt occurs.  Other RTOS tasks will
 *     execute while the the calling task is in the Blocked state.  The
 *     semaphore must be created using the FreeRTOS vSemaphoreCreateBinary() API
 *     function before it is used as a parameter.
 *
 * \return     ERR_INVALID_ARG is returned if an input parameter is invalid.
 *     ERR_TIMEOUT is returned if block_time_ticks passed before exclusive
 *     access to the TWIHS peripheral could be obtained.  STATUS_OK is returned if
 *     the PDC was successfully configured to perform the TWIHS read operation.
 */
status_code_t freertos_twihs_read_packet_async(freertos_twihs_if p_twihs,
		twihs_packet_t *p_packet, portTickType block_time_ticks,
		xSemaphoreHandle notification_semaphore)
{
	status_code_t return_value;
	portBASE_TYPE twihs_index;
	Twihs *twihs_base;
	uint32_t internal_address = 0;

	twihs_base = (Twihs *) p_twihs;
	twihs_index = get_pdc_peripheral_details(all_twihs_definitions, MAX_TWIHS,
			(void *) twihs_base);

	/* Don't do anything unless a valid TWIHS pointer was used. */
	if ((twihs_index < MAX_TWIHS) && (p_packet->length > 0)) {
		/* Because the peripheral is half duplex, there is only one access mutex
		and the rx uses the tx mutex. */
		return_value = freertos_obtain_peripheral_access_semphore(
				&(tx_dma_control[twihs_index]), &block_time_ticks);

		if (return_value == STATUS_OK) {
			/* Ensure Rx is already empty. */
			twihs_read_byte(twihs_base);

			/* Set read mode and slave address. */
			twihs_base->TWIHS_MMR = 0;
			twihs_base->TWIHS_MMR = TWIHS_MMR_MREAD | TWIHS_MMR_DADR(
					p_packet->chip) |
					((p_packet->addr_length <<
					TWIHS_MMR_IADRSZ_Pos) &
					TWIHS_MMR_IADRSZ_Msk);

			/* Set internal address if any. */
			if (p_packet->addr_length) {
				internal_address = p_packet->addr [0];
				if (p_packet->addr_length > 1) {
					internal_address <<= 8;
					internal_address |= p_packet->addr[1];
				}

				if (p_packet->addr_length > 2) {
					internal_address <<= 8;
					internal_address |= p_packet->addr[2];
				}
			}
			twihs_base->TWIHS_IADR = internal_address;

			if (p_packet->length <= 2) {
				/* Do not handle errors for short packets in interrupt handler */
				twihs_disable_interrupt(
						all_twihs_definitions[twihs_index].peripheral_base_address,
						IER_ERROR_INTERRUPTS);

				/* Cannot use PDC transfer, use normal transfer */
				uint8_t stop_sent = 0;
				uint32_t cnt = p_packet->length;
				uint32_t status;
				uint8_t *buffer = p_packet->buffer;
				uint32_t timeout_counter = 0;

				/* Start the transfer. */
				if (cnt == 1) {
					twihs_base->TWIHS_CR = TWIHS_CR_START | TWIHS_CR_STOP;
					stop_sent = 1;
				} else {
					twihs_base->TWIHS_CR = TWIHS_CR_START;
				}

				while (cnt > 0) {
					status = twihs_base->TWIHS_SR;
					if (status & TWIHS_SR_NACK) {
						/* Re-enable interrupts */
						twihs_enable_interrupt(
								all_twihs_definitions[twihs_index].peripheral_base_address,
								IER_ERROR_INTERRUPTS);
						/* Release semaphore */
						xSemaphoreGive(tx_dma_control[twihs_index].peripheral_access_sem);
						return TWIHS_RECEIVE_NACK;
					}
					/* Last byte ? */
					if (cnt == 1 && !stop_sent) {
						twihs_base->TWIHS_CR = TWIHS_CR_STOP;
						stop_sent = 1;
					}
					if (!(status & TWIHS_SR_RXRDY)) {
						if (++timeout_counter >= TWIHS_TIMEOUT_COUNTER) {
							return_value = ERR_TIMEOUT;
							break;
						}
						continue;
					}
					*buffer++ = twihs_base->TWIHS_RHR;
					cnt--;
					timeout_counter = 0;
				}

				timeout_counter = 0;
				/* Wait for stop to be sent */
				while (!(twihs_base->TWIHS_SR & TWIHS_SR_TXCOMP)) {
					/* Check timeout condition. */
					if (++timeout_counter >= TWIHS_TIMEOUT_COUNTER) {
						return_value = ERR_TIMEOUT;
						break;
					}
				}
				/* Re-enable interrupts */
				twihs_enable_interrupt(
						all_twihs_definitions[twihs_index].peripheral_base_address,
						IER_ERROR_INTERRUPTS);
				/* Release semaphores */
				xSemaphoreGive(tx_dma_control[twihs_index].peripheral_access_sem);
			} else {
				/* Start the PDC reception. */
				twihss[twihs_index].buffer = p_packet->buffer;
				twihss[twihs_index].length = p_packet->length;
				freertos_start_pdc_rx(&(rx_dma_control[twihs_index]),
						p_packet->buffer, p_packet->length,
						all_twihs_definitions[twihs_index].pdc_base_address,
						notification_semaphore);

				/* Start the transfer. */
				twihs_base->TWIHS_CR = TWIHS_CR_START;

				/* Catch the end of reception so the access mutex can be returned,
				and the task notified (if it supplied a notification semaphore).
				The interrupt can be enabled here because the ENDRX	signal from the
				PDC to the peripheral will have been de-asserted when the next
				transfer was configured. */
				twihs_enable_interrupt(twihs_base, TWIHS_IER_ENDRX);

				return_value = freertos_optionally_wait_transfer_completion(
						&(rx_dma_control[twihs_index]),
						notification_semaphore,
						block_time_ticks);
			}
		}
	} else {
		return_value = ERR_INVALID_ARG;
	}

	return return_value;
}

/*
 * For internal use only.
 * A common TWIHS interrupt handler that is called for all TWIHS peripherals.
 */
static void local_twihs_handler(const portBASE_TYPE twihs_index)
{
	portBASE_TYPE higher_priority_task_woken = pdFALSE;
	uint32_t twihs_status;
	Twihs *twihs_port;

	twihs_port = all_twihs_definitions[twihs_index].peripheral_base_address;

	twihs_status = twihs_get_interrupt_status(twihs_port);
	twihs_status &= twihs_get_interrupt_mask(twihs_port);

	/* Has the PDC completed a transmission? */
	if ((twihs_status & TWIHS_SR_ENDTX) != 0UL) {
		/* Disable PDC */
		pdc_disable_transfer(all_twihs_definitions[twihs_index].pdc_base_address, PERIPH_PTCR_TXTDIS);
		twihs_disable_interrupt(twihs_port, TWIHS_IDR_ENDTX);

		uint8_t status;
		uint32_t timeout_counter = 0;

		/* Wait for TX ready flag */
		while (1) {
			status = twihs_port->TWIHS_SR;
			if (status & TWIHS_SR_TXRDY) {
				break;
			}
			/* Check timeout condition. */
			if (++timeout_counter >= TWIHS_TIMEOUT_COUNTER) {
				status = ERR_TIMEOUT;
				break;
			}
		}
		/* Complete the transfer - stop and last byte */
		twihs_port->TWIHS_CR = TWIHS_CR_STOP;
		twihs_port->TWIHS_THR = twihss[twihs_index].buffer[twihss[twihs_index].length-1];

		/* Wait for TX complete flag */
		while (1) {
			status = twihs_port->TWIHS_SR;
			if (status & TWIHS_SR_TXCOMP) {
				break;
			}
			/* Check timeout condition. */
			if (++timeout_counter >= TWIHS_TIMEOUT_COUNTER) {
				status = ERR_TIMEOUT;
				break;
			}
		}


		/* If the driver is supporting multi-threading, then return the access
		mutex. */
		if (tx_dma_control[twihs_index].peripheral_access_sem != NULL) {
			xSemaphoreGiveFromISR(
					tx_dma_control[twihs_index].peripheral_access_sem,
					&higher_priority_task_woken);
		}

		/* if the sending task supplied a notification semaphore, then
		notify the task that the transmission has completed. */
		if (!(timeout_counter >= TWIHS_TIMEOUT_COUNTER)) {
			if (tx_dma_control[twihs_index].transaction_complete_notification_semaphore != NULL) {
				xSemaphoreGiveFromISR(
						tx_dma_control[twihs_index].transaction_complete_notification_semaphore,
						&higher_priority_task_woken);
			}
		}
	}

	/* Has the PDC completed a reception? */
	if ((twihs_status & TWIHS_SR_ENDRX) != 0UL) {
		uint32_t timeout_counter = 0;
		uint32_t status;
		/* Must handle the two last bytes */
		/* Disable PDC */
		pdc_disable_transfer(all_twihs_definitions[twihs_index].pdc_base_address, PERIPH_PTCR_RXTDIS);

		twihs_disable_interrupt(twihs_port, TWIHS_IDR_ENDRX);

		/* Wait for RX ready flag */
		while (1) {
			status = twihs_port->TWIHS_SR;
			if (status & TWIHS_SR_RXRDY) {
				break;
			}
			/* Check timeout condition. */
			if (++timeout_counter >= TWIHS_TIMEOUT_COUNTER) {
				break;
			}
		}
		/* Complete the transfer. */
		twihs_port->TWIHS_CR = TWIHS_CR_STOP;
		/* Read second last data */
		twihss[twihs_index].buffer[(twihss[twihs_index].length)-2] = twihs_port->TWIHS_RHR;

		/* Wait for RX ready flag */
		while (1) {
			status = twihs_port->TWIHS_SR;
			if (status & TWIHS_SR_RXRDY) {
				break;
			}
			/* Check timeout condition. */
			if (++timeout_counter >= TWIHS_TIMEOUT_COUNTER) {
				break;
			}
		}

		if (!(timeout_counter >= TWIHS_TIMEOUT_COUNTER)) {
			/* Read last data */
			twihss[twihs_index].buffer[(twihss[twihs_index].length)-1] = twihs_port->TWIHS_RHR;
			timeout_counter = 0;
			/* Wait for TX complete flag before releasing semaphore */
			while (1) {
				status = twihs_port->TWIHS_SR;
				if (status & TWIHS_SR_TXCOMP) {
					break;
				}
				/* Check timeout condition. */
				if (++timeout_counter >= TWIHS_TIMEOUT_COUNTER) {
					status = ERR_TIMEOUT;
					break;
				}
			}
		}

		/* If the driver is supporting multi-threading, then return the access
		mutex.  NOTE: As the peripheral is half duplex there is only one
		access mutex, and the reception uses the tx access muted. */
		if (tx_dma_control[twihs_index].peripheral_access_sem != NULL) {
			xSemaphoreGiveFromISR(
					tx_dma_control[twihs_index].peripheral_access_sem,
					&higher_priority_task_woken);
		}

		/* if the receiving task supplied a notification semaphore, then
		notify the task that the transmission has completed. */
		if  (!(timeout_counter >= TWIHS_TIMEOUT_COUNTER)) {
			if (rx_dma_control[twihs_index].transaction_complete_notification_semaphore != NULL) {
				xSemaphoreGiveFromISR(
						rx_dma_control[twihs_index].transaction_complete_notification_semaphore,
						&higher_priority_task_woken);
			}
		}
	}

	if ((twihs_status & SR_ERROR_INTERRUPTS) != 0) {
		/* An error occurred in either a transmission or reception.  Abort.
		Stop the transmission, disable interrupts used by the peripheral, and
		ensure the peripheral access mutex is made available to tasks.  As this
		peripheral is half duplex, only the Tx peripheral access mutex exits.*/

		/* Stop the PDC */
		pdc_disable_transfer(all_twihs_definitions[twihs_index].pdc_base_address, PERIPH_PTCR_TXTDIS | PERIPH_PTCR_RXTDIS);

		if (!(twihs_status & TWIHS_SR_NACK)) {
			/* Do not send stop if NACK received. Handled by hardware */
			twihs_port->TWIHS_CR = TWIHS_CR_STOP;
		}
		twihs_disable_interrupt(twihs_port, TWIHS_IDR_ENDTX);
		twihs_disable_interrupt(twihs_port, TWIHS_IDR_ENDRX);

		if (tx_dma_control[twihs_index].peripheral_access_sem != NULL) {
			xSemaphoreGiveFromISR(
					tx_dma_control[twihs_index].peripheral_access_sem,
					&higher_priority_task_woken);
		}
	}

	/* If giving a semaphore caused a task to unblock, and the unblocked task
	has a priority equal to or higher than the currently running task (the task
	this ISR interrupted), then higher_priority_task_woken will have
	automatically been set to pdTRUE within the semaphore function.
	portEND_SWITCHING_ISR() will then ensure that this ISR returns directly to
	the higher priority unblocked task. */
	portEND_SWITCHING_ISR(higher_priority_task_woken);
}

/*
 * Individual interrupt handlers follow from here.  Each individual interrupt
 * handler calls the common interrupt handler.
 */
#ifdef TWI0
void TWI0_Handler(void)
{
	local_twihs_handler(0);
}
#endif /* TWI0 */

