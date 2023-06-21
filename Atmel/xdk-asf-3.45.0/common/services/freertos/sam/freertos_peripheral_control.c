/**
 *
 * \file
 *
 * \brief Generic FreeRTOS peripheral control functions
 *
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* ASF includes. */
#include "freertos_peripheral_control.h"
#include "freertos_peripheral_control_private.h"

/*
 * For internal use only.
 * Return the index into peripheral_array[] that contains details of the
 * peripheral that has the start address specified by peripheral_to_find.
 */
portBASE_TYPE get_pdc_peripheral_details(
		const freertos_pdc_peripheral_parameters_t peripheral_array[],
		size_t array_size, void *peripheral_to_find)
{
	size_t x;

	for (x = 0; x < array_size; x++) {
		if (peripheral_array[x].peripheral_base_address ==
				peripheral_to_find) {
			break;
		}
	}

	return x;
}

/*
 * For internal use only.
 * Return true if the value passed in requested_operating_mode is present in the
 * valid_operating_modes[] array, otherwise return false.
 */
bool check_requested_operating_mode(
		const enum peripheral_operation_mode requested_operation_mode,
		const enum peripheral_operation_mode valid_operating_modes[],
		portBASE_TYPE num_valid_operating_modes)
{
	bool return_value = false;
	portBASE_TYPE index_position;

	for (index_position = 0; index_position < num_valid_operating_modes;
			index_position++) {
		if (requested_operation_mode ==
				valid_operating_modes[index_position]) {
			return_value = true;
			break;
		}
	}

	return return_value;
}

/*
 * For internal use only.
 * Create the FreeRTOS objects necessary to control the peripheral in accordance
 * with the bits set in the options_flags value.
 */
void create_peripheral_control_semaphores(const uint8_t options_flags,
		freertos_dma_event_control_t *tx_dma_control,
		freertos_dma_event_control_t *rx_dma_control)
{
	/* If the tx driver is to be thread aware then create an access control
	semaphore.  An Rx access mutex is not created in this function as half duplex
	peripherals need only use a single access mutex, and the Tx semaphore is used
	for the purpose.  Full duplex peripherals have extra configuration steps
	that are performed separately. */
	if ((options_flags & USE_TX_ACCESS_SEM) != 0) {
		vSemaphoreCreateBinary(
				tx_dma_control->peripheral_access_sem);
		configASSERT(tx_dma_control->peripheral_access_sem);
		
		/* Ensure the binary semaphore starts with equal to 1 */
		xSemaphoreGive(tx_dma_control->peripheral_access_sem);
	}

	/* If the transmit function is only going to return once the transmit is
	complete then create an internal notification semaphore. */
	if ((options_flags & WAIT_TX_COMPLETE) != 0) {
		vSemaphoreCreateBinary(
				tx_dma_control->transaction_complete_notification_semaphore);
		configASSERT(
				tx_dma_control->transaction_complete_notification_semaphore);

		/* Ensure the semaphore starts in the expected state.  A block time
		of zero can be used here as the semaphore is guaranteed to be
		available (it has only just been created). */
		xSemaphoreTake(
				tx_dma_control->transaction_complete_notification_semaphore,
				0);
	} else {
		tx_dma_control->transaction_complete_notification_semaphore = NULL;
	}

	/* If the receive function is only going to return once the receive
	is complete then create an internal notification semaphore. */
	if (((options_flags & WAIT_RX_COMPLETE) != 0) &&
			(rx_dma_control != NULL)) {
		vSemaphoreCreateBinary(
				rx_dma_control->transaction_complete_notification_semaphore);
		configASSERT(
				rx_dma_control->transaction_complete_notification_semaphore);

		/* Ensure the semaphore starts in the expected state.  A block time
		of zero can be used here as the semaphore is guaranteed to be
		available (it has only just been created. */
		xSemaphoreTake(
				rx_dma_control->transaction_complete_notification_semaphore,
				0);
	} else {
		rx_dma_control->transaction_complete_notification_semaphore = NULL;
	}
}

/*
 * For internal use only.
 * Configure the NVIC to enable, and set the priority of, the interrupt
 * specified by peripheral_irq.
 */
void configure_interrupt_controller(const enum IRQn peripheral_irq,
		uint32_t interrupt_priority)
{
	configASSERT(interrupt_priority <=
            configLIBRARY_LOWEST_INTERRUPT_PRIORITY);
	configASSERT(interrupt_priority >=
			configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);

	NVIC_ClearPendingIRQ(peripheral_irq);
	NVIC_SetPriority(peripheral_irq, interrupt_priority);
	NVIC_EnableIRQ(peripheral_irq);
}

/*
 * For internal use only.
 * The peripheral driver is buffering received characters in a circular buffer.
 * Read bytes_to_read out of the circular buffer into buf.
 */
uint32_t freertos_copy_bytes_from_pdc_circular_buffer(
		freertos_pdc_rx_control_t *p_rx_buffer_details,
		uint32_t next_byte_to_be_written, uint8_t *buf,
		uint32_t bytes_to_read)
{
	uint32_t number_of_bytes_available, next_byte_to_read;

	/* Locate the position that data will be read from next. */
	next_byte_to_read = (uint32_t) p_rx_buffer_details->next_byte_to_read;

	if (next_byte_to_be_written == next_byte_to_read) {
		if (p_rx_buffer_details->rx_pdc_parameters.ul_size == 0) {
			/* The read and write pointers are equal, but as the Rx DMA has been
			stopped, the buffer must be full, not empty.  Data from the read
			pointer up to the end of the buffer is available. */
			number_of_bytes_available =
					p_rx_buffer_details->past_rx_buffer_end_address
					- next_byte_to_read;
		} else {
			/* The read and write pointers are equal, but the Rx DMA is still
			in operation, so the buffer must be empty. */
			number_of_bytes_available = 0;
		}
	} else if (next_byte_to_be_written > next_byte_to_read) {
		/* The write pointer has not wrapped around from the read pointer, or
		the write and read pointer are the same indicating a buffer overflow.
		Calculate the bytes available between the write and read pointers. */
		number_of_bytes_available = next_byte_to_be_written -
				next_byte_to_read;
	} else {
		/* The write pointer has wrapped around from the read pointer.
		Calculate the bytes available between the end of the buffer and the
		read pointer. */
		number_of_bytes_available =
				p_rx_buffer_details->past_rx_buffer_end_address
				- next_byte_to_read;
	}

	/* Cap the number of requested bytes to those available. */
	if (bytes_to_read > number_of_bytes_available) {
		bytes_to_read = number_of_bytes_available;
	} else if (bytes_to_read != number_of_bytes_available) {
		/* There are more bytes available than being read now, so there is no
		need to wait for the interrupt to give the semaphore to indicate that
		new data is available. */
		xSemaphoreGive(p_rx_buffer_details->rx_event_semaphore);
	}

	/* Copy the bytes into the user buffer. */
	memcpy(buf, (void *) p_rx_buffer_details->next_byte_to_read,
			bytes_to_read);

	/* Move up the read buffer accordingly, wrapping around if it reaches the
	end of the buffer. */
	next_byte_to_read += bytes_to_read;

	if (next_byte_to_read >=
			p_rx_buffer_details->past_rx_buffer_end_address) {
		/* The next_byte_to_read pointer is only read by the ISR, so the
		critical section is probably not needed on 32-bit machines. */
		taskENTER_CRITICAL();
		{
			p_rx_buffer_details->next_byte_to_read =
					(uint8_t *) p_rx_buffer_details->rx_buffer_start_address;
		}
		taskEXIT_CRITICAL();
	} else {
		/* The next_byte_to_read pointer is only read by the ISR, so the
		critical section is probably not needed on 32-bit machines. */
		taskENTER_CRITICAL();
		{
			p_rx_buffer_details->next_byte_to_read =
					(uint8_t *) next_byte_to_read;
		}
		taskEXIT_CRITICAL();
	}

	/* Return the number of bytes actually read. */
	return bytes_to_read;
}

/*
 * For internal use only.
 * If a peripheral access semphore is not defined, just return STATUS_OK and take
 * no other action.
 * If a peripheral access semphore is defined, attempt to obtain the semphore.
 * Return STATUS_OK if the semphore was obtained, and ERR_TIMEOUT if the semphore
 * did not become available within max_block_time_ticks tick periods.
 */
status_code_t freertos_obtain_peripheral_access_semphore(
		freertos_dma_event_control_t *dma_event_control,
		portTickType *max_block_time_ticks)
{
	status_code_t return_value = STATUS_OK;
	xTimeOutType time_out_definition;

	if (dma_event_control->peripheral_access_sem != NULL) {
		/* Remember the time on entry. */
		vTaskSetTimeOutState(&time_out_definition);

		/* Wait to get exclusive access to the peripheral. */
		if (xSemaphoreTake(dma_event_control->peripheral_access_sem,
				*max_block_time_ticks) == pdFAIL) {
			return_value = ERR_TIMEOUT;
		} else {
			/* Adjust the time out value in case the task had to block to
			wait for the semaphore. */
			if (xTaskCheckForTimeOut(&time_out_definition,
					max_block_time_ticks) == pdTRUE) {
				*max_block_time_ticks = 0;
			}
		}
	}

	return return_value;
}

/*
 * For internal use only.
 * If is_transmitting is false then configure the PDC to receive len bytes into
 * data.  If is_transmitting is true then configure the PDC to write len bytes
 * from data.
 * If notification_semaphore is not NULL, then the user is passing in their
 * own notification semaphore, and the semaphore is associated with the PDC
 * structure so it can be 'given' when the PDC transfer completes.  If
 * notification_semaphore is NULL then the driver will have its own internal
 * notification semaphore that it will use to only exit the send or receive
 * function when the PDC transfer has completed.
 */
void freertos_start_pdc_transfer(
		freertos_dma_event_control_t *dma_event_control,
		const uint8_t *data, size_t len, void *pdc_base_address,
		xSemaphoreHandle notification_semaphore, bool is_transmitting)
{
	pdc_packet_t pdc_packet;

	/* Remember which semaphore is to be used to indicate the end of
	transmission.  If notification_semaphore is NULL then either no
	semaphore is being used, or the driver is using an internal notification
	semaphore because it is configured to wait until the transmit has
	completed before returning. */
	if (notification_semaphore != NULL) {
		dma_event_control->transaction_complete_notification_semaphore =
				notification_semaphore;
	}

	/* Ensure the notification semaphore starts in the expected state in case
	the previous PDC transfer didn't complete for any reason. */
	if (dma_event_control->transaction_complete_notification_semaphore !=
			NULL) {
		xSemaphoreTake(
				dma_event_control->transaction_complete_notification_semaphore,
				0);
	}

	/* Configure the PDC to transmit or receive parameters. */
	pdc_packet.ul_addr = (uint32_t) data;
	pdc_packet.ul_size = (uint32_t) len;

	if (is_transmitting == true) {
		pdc_disable_transfer(pdc_base_address, PERIPH_PTCR_TXTDIS);
		pdc_tx_init(pdc_base_address, &pdc_packet, NULL);
		pdc_enable_transfer(pdc_base_address, PERIPH_PTCR_TXTEN);
	} else {
		pdc_disable_transfer(pdc_base_address, PERIPH_PTCR_RXTDIS);
		pdc_rx_init(pdc_base_address, &pdc_packet, NULL);
		pdc_enable_transfer(pdc_base_address, PERIPH_PTCR_RXTEN);
	}
}

/*
 * For internal use only.
 * If notification_semaphore is not NULL then the user has supplied their own
 * notification semaphore, indicating that they do not wish to wait for the end
 * of the PDC transfer.  In that case, this function will exit immediately and
 * always return STATUS_OK.
 * If notification_semaphore is NULL, but there is a semaphore associated with
 * the PDC, then the driver is using its own internal notification semaphore and
 * this function should not return until either the semaphore is 'taken', or
 * max_block_time_ticks RTOS ticks have passed.  STATUS_OK is returned if the
 * semaphore is taken.  ERR_TIMEOUT is returned if the wait for the semaphore
 * timed out.
 */
status_code_t freertos_optionally_wait_transfer_completion(
		freertos_dma_event_control_t *dma_event_control,
		xSemaphoreHandle notification_semaphore,
		portTickType max_block_time_ticks)
{
	status_code_t return_value = STATUS_OK;

	if (notification_semaphore == NULL) {
		if (dma_event_control->transaction_complete_notification_semaphore !=
				NULL) {
			/* Wait until notified by the ISR that transmission is
			complete. */
			if (xSemaphoreTake(dma_event_control->
					transaction_complete_notification_semaphore,
					max_block_time_ticks) != pdPASS) {
				return_value = ERR_TIMEOUT;
			}
		}
	}

	return return_value;
}
