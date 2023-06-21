/**
 * \file
 *
 * \brief FreeRTOS Peripheral Control API For the UART
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
#include "serial.h"
#include "freertos_uart_serial.h"
#include "freertos_peripheral_control_private.h"

/* Every bit in the interrupt mask. */
#define MASK_ALL_INTERRUPTS         (0xffffffffUL)

/* Interrupts that are enabled to catch error conditions on the bus. */
#define SR_ERROR_INTERRUPTS         (UART_SR_OVRE | UART_SR_FRAME |UART_SR_PARE)
#define IER_ERROR_INTERRUPTS        (UART_IER_OVRE | UART_IER_FRAME | UART_IER_PARE)

/* A value written to a member of an Rx buffer to show that the Rx side was not
initialised and therefore should not be used. */
#define RX_NOT_USED                 (uint8_t *) 0x1

/* Work out how many UARTS with PDC are present. */
#if defined(PDC_UART2)
	#define MAX_UARTS                              (3)
#elif defined(PDC_UART1)
	#define MAX_UARTS                              (2)
#elif defined(PDC_UART0)
	#define MAX_UARTS                              (1)
#elif defined(PDC_UART)
	#define MAX_UARTS                              (1)
#else
	#error No PDC UARTS defined
#endif

enum buffer_operations {
	data_added = 0,
	data_removed
};

/* Configures the Rx DMA to receive data into free space within the Rx buffer. */
static void configure_rx_dma(uint32_t uart_index,
		enum buffer_operations operation_performed);

/* A common interrupt handler called by all the UART peripherals. */
static void local_uart_handler(const portBASE_TYPE uart_index);

/* Structures to manage the DMA control for both Rx and Tx transactions. */
static freertos_pdc_rx_control_t rx_buffer_definitions[MAX_UARTS];
static freertos_dma_event_control_t tx_dma_control[MAX_UARTS];

/* Create an array that holds the information required about each defined
UART. */
static const freertos_pdc_peripheral_parameters_t all_uart_definitions[MAX_UARTS] = {
	#if defined(UART)
	{UART, PDC_UART, ID_UART, UART_IRQn},
	#endif

	#if defined(UART0)
	{UART0, PDC_UART0, ID_UART0, UART0_IRQn},
	#endif

	#if (MAX_UARTS > 1)
	{UART1, PDC_UART1, ID_UART1, UART1_IRQn},
	#endif

	#if (MAX_UARTS > 2)
	{UART2, PDC_UART2, ID_UART2, UART2_IRQn},
	#endif
};

/**
 * \ingroup freertos_uart_peripheral_control_group
 * \brief Initializes the FreeRTOS ASF UART driver for the specified UART
 * port.
 *
 * freertos_uart_serial_init() is an ASF specific FreeRTOS driver function.  It
 * must be called before any other ASF specific FreeRTOS driver functions
 * attempt to access the same UART port.
 *
 * If freertos_driver_parameters->operation_mode equals UART_RS232 then
 * freertos_uart_serial_init() will configure the UART port for standard RS232
 * operation.  If freertos_driver_parameters->operation_mode equals any other
 * value then freertos_uart_serial_init() will not take any action.
 *
 * Other ASF UART functions can be called after freertos_uart_serial_init()
 * has completed successfully.
 *
 * The FreeRTOS ASF driver both installs and handles the UART PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * This driver is provided with an application note, and an example project that
 * demonstrates the use of this function.
 *
 * \param p_uart    The UART peripheral being initialized.
 * \param uart_parameters    Structure that defines the UART bus and transfer
 *     parameters, such the baud rate and the number of data bits.
 *     sam_uart_opt_t is a standard ASF type (it is not FreeRTOS specific).
 * \param freertos_driver_parameters    Defines the driver behavior.  See the
 *    freertos_peripheral_options_t documentation, and the application note that
 *    accompanies the ASF specific FreeRTOS functions.
 *
 * \return If the initialization completes successfully then a handle that can
 *     be used with FreeRTOS UART read and write functions is returned.  If
 *     the initialisation fails then NULL is returned.
 */
freertos_uart_if freertos_uart_serial_init(Uart *p_uart,
		const sam_uart_opt_t *const uart_parameters,
		const freertos_peripheral_options_t *const freertos_driver_parameters)
{
	portBASE_TYPE uart_index;
	bool is_valid_operating_mode;
	freertos_uart_if return_value;
	const enum peripheral_operation_mode valid_operating_modes[] = {UART_RS232};

	/* Find the index into the all_uart_definitions array that holds details of
	the p_uart peripheral. */
	uart_index = get_pdc_peripheral_details(all_uart_definitions,
			MAX_UARTS,
			(void *) p_uart);

	/* Check the requested operating mode is valid for the peripheral. */
	is_valid_operating_mode = check_requested_operating_mode(
			freertos_driver_parameters->operation_mode,
			valid_operating_modes,
			sizeof(valid_operating_modes) /
			sizeof(enum peripheral_operation_mode));

	/* Don't do anything unless a valid p_uart pointer was used, and a valid
	operating mode was requested. */
	if ((uart_index < MAX_UARTS) && (is_valid_operating_mode == true)) {
		/* This function must be called exactly once per supported UART.  Check it
		has not been called	before. */
		configASSERT(rx_buffer_definitions[uart_index].next_byte_to_read == NULL);

		/* Disable everything before enabling the clock. */
		uart_disable_tx(p_uart);
		uart_disable_rx(p_uart);
		pdc_disable_transfer(all_uart_definitions[uart_index].pdc_base_address,
				(PERIPH_PTCR_RXTDIS | PERIPH_PTCR_TXTDIS));

		/* Enable the peripheral clock in the PMC. */
		pmc_enable_periph_clk(
				all_uart_definitions[uart_index].peripheral_id);

		switch (freertos_driver_parameters->operation_mode) {
		case UART_RS232:
			/* Call the standard ASF init function. */
			uart_init(p_uart, uart_parameters);
			break;

		default:
			/* Other modes are not currently supported. */
			break;
		}

		/* Disable all the interrupts. */
		uart_disable_interrupt(p_uart, MASK_ALL_INTERRUPTS);

		/* Create any required peripheral access mutexes and transaction complete
		semaphores.  This peripheral is full duplex so only the Tx semaphores
		are created in the following function.  The the Rx semaphores are
		created	separately. */
		create_peripheral_control_semaphores(
				freertos_driver_parameters->options_flags,
				&(tx_dma_control[uart_index]),
				NULL /* The rx structures are not created in this function. */);

		/* Is the driver also going to receive? */
		if (freertos_driver_parameters->receive_buffer != NULL) {
			/* rx_event_semaphore is used to signal the arival of new data.  It
			must be a counting semaphore for the following reason:  If the Rx
			DMA places data at the end of its circular buffer it will give the
			semaphore to indicate the presence of unread data.  If it then
			receives more data, it will write this to the start of the circular
			buffer, then give the semaphore again.  Now, if a task reads data
			out of the same circular buffer, and requests less data than is
			available, but more than is available between the next read pointer
			and the end of the buffer, the actual amount returned will be
			capped to that available up to the end of the buffer only.  If this
			semaphore was a binary semaphore, it would then be 'taken' even
			though, unknown to the reading task, unread and therefore available
			data remained at the beginning of the buffer. */
			rx_buffer_definitions[uart_index].rx_event_semaphore =
					xSemaphoreCreateCounting(portMAX_DELAY, 0);
			configASSERT(rx_buffer_definitions[uart_index].rx_event_semaphore);

			/* The receive buffer is currently empty, so the DMA has control
			over the entire buffer. */
			rx_buffer_definitions[uart_index].rx_pdc_parameters.ul_addr =
					(uint32_t)freertos_driver_parameters->receive_buffer;
			rx_buffer_definitions[uart_index].rx_pdc_parameters.ul_size =
					freertos_driver_parameters->receive_buffer_size;
			pdc_rx_init(
					all_uart_definitions[uart_index].pdc_base_address,
					&(rx_buffer_definitions[uart_index].rx_pdc_parameters),
					NULL);

			/* Set the next byte to read to the start of the buffer as no data
			has yet been read. */
			rx_buffer_definitions[uart_index].next_byte_to_read =
					freertos_driver_parameters->receive_buffer;

			/* Remember the limits of entire buffer. */
			rx_buffer_definitions[uart_index].rx_buffer_start_address =
					rx_buffer_definitions[uart_index].rx_pdc_parameters.ul_addr;
			rx_buffer_definitions[uart_index].past_rx_buffer_end_address =
					rx_buffer_definitions[uart_index].rx_buffer_start_address +
					freertos_driver_parameters->receive_buffer_size;

			/* If the rx driver is to be thread aware, create an access control
			mutex. */
			if ((freertos_driver_parameters->options_flags &
					USE_RX_ACCESS_MUTEX) != 0) {
				rx_buffer_definitions[uart_index].rx_access_mutex =
					xSemaphoreCreateMutex();
				configASSERT(rx_buffer_definitions[uart_index].rx_access_mutex);
			}

			/* Catch the DMA running out of Rx space, and gaps in the
			reception.  These events are both used to signal that there is
			data available in the Rx buffer. */
			uart_enable_interrupt(p_uart, UART_IER_ENDRX | UART_IER_RXRDY);

			/* The Rx DMA is running all the time, so enable it now. */
			pdc_enable_transfer(
					all_uart_definitions[uart_index].pdc_base_address,
					PERIPH_PTCR_RXTEN);
		} else {
			/* next_byte_to_read is used to check to see if this function
			has been called before, so it must be set to something, even if
			it is not going to be used.  The value it is set to is not
			important, provided it is not zero (NULL). */
			rx_buffer_definitions[uart_index].next_byte_to_read = RX_NOT_USED;
		}

		/* Configure and enable the UART interrupt in the interrupt controller. */
		configure_interrupt_controller(all_uart_definitions[uart_index].peripheral_irq,
				freertos_driver_parameters->interrupt_priority);

		/* Error interrupts are always enabled. */
		uart_enable_interrupt(
				all_uart_definitions[uart_index].peripheral_base_address,
				IER_ERROR_INTERRUPTS);

		/* Finally, enable the receiver and transmitter. */
		uart_enable_tx(p_uart);
		uart_enable_rx(p_uart);

		return_value = (freertos_uart_if) p_uart;
	} else {
		return_value = NULL;
	}

	return return_value;
}

/**
 * \ingroup freertos_uart_peripheral_control_group
 * \brief Initiate a completely asynchronous multi-byte write operation on a
 * UART peripheral.
 *
 * freertos_uart_write_packet_async() is an ASF specific FreeRTOS driver
 * function.  It configures the UART peripheral DMA controller (PDC) to
 * transmit data on the UART port, then returns.
 * freertos_uart_write_packet_async() does not wait for the transmission to
 * complete before returning.
 *
 * The FreeRTOS UART driver is initialized using a call to
 * freertos_uart_serial_init().  The freertos_driver_parameters.options_flags
 * parameter passed into the initialization function defines the driver behavior.
 * freertos_uart_write_packet_async() can only be used if the
 * freertos_driver_parameters.options_flags parameter passed to the initialization
 * function had the WAIT_TX_COMPLETE bit clear.
 *
 * freertos_uart_write_packet_async() is an advanced function and readers are
 * recommended to also reference the application note and examples that
 * accompany the FreeRTOS ASF drivers.  freertos_uart_write_packet() is a
 * version that does not exit until the PDC transfer is complete, but still
 * allows other RTOS tasks to execute while the transmission is in progress.
 *
 * The FreeRTOS ASF driver both installs and handles the UART PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * \param p_uart    The handle to the UART peripheral returned by the
 *     freertos_uart_serial_init() call used to initialise the peripheral.
 * \param data    A pointer to the data to be transmitted.
 * \param len    The number of bytes to transmit.
 * \param block_time_ticks    The FreeRTOS ASF UART driver is initialized using
 *     a call to freertos_uart_serial_init().  The
 *     freertos_driver_parameters.options_flags parameter passed to the
 *     initialization function defines the driver behavior.  If
 *     freertos_driver_parameters.options_flags had the USE_TX_ACCESS_SEM bit
 *     set, then the driver will only write to the UART peripheral if it has
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
 *     access to the UART peripheral could be obtained.  STATUS_OK is returned
 *     if the PDC was successfully configured to perform the UART write
 *     operation.
 */
status_code_t freertos_uart_write_packet_async(freertos_uart_if p_uart,
		const uint8_t *data, size_t len, portTickType block_time_ticks,
		xSemaphoreHandle notification_semaphore)
{
	status_code_t return_value;
	portBASE_TYPE uart_index;
	Uart *uart_base;

	uart_base = (Uart *) p_uart;
	uart_index = get_pdc_peripheral_details(all_uart_definitions,
			MAX_UARTS,
			(void *) uart_base);

	/* Don't do anything unless a valid UART pointer was used. */
	if (uart_index < MAX_UARTS) {
		return_value = freertos_obtain_peripheral_access_semphore(
				&(tx_dma_control[uart_index]),
				&block_time_ticks);

		if (return_value == STATUS_OK) {
			freertos_start_pdc_tx(&(tx_dma_control[uart_index]),
					data, len,
					all_uart_definitions[uart_index].pdc_base_address,
					notification_semaphore);

			/* Catch the end of transmission so the access mutex can be
			returned, and the task notified (if it supplied a notification
			semaphore).  The interrupt can be enabled here because the ENDTX
			signal from the PDC to the UART will have been de-asserted when
			the next transfer was configured. */
			uart_enable_interrupt(uart_base, UART_IER_ENDTX);

			return_value = freertos_optionally_wait_transfer_completion(
					&(tx_dma_control[uart_index]),
					notification_semaphore,
					block_time_ticks);
		}
	} else {
		return_value = ERR_INVALID_ARG;
	}

	return return_value;
}

/**
 * \ingroup freertos_uart_peripheral_control_group
 * \brief Initiate a completely multi-byte read operation on a UART peripheral.
 *
 * The FreeRTOS ASF UART driver uses the PDC to transfer data from a peripheral
 * to a circular buffer.  Reception happens in the background, while the
 * microcontroller is executing application code.* freertos_uart_read_packet()
 * copies bytes from the DMA buffer into the buffer passed as a
 * freertos_uart_read_packet() parameter.
 *
 * Readers are recommended to also reference the application note and examples
 * that accompany the FreeRTOS ASF drivers.
 *
 * The FreeRTOS ASF driver both installs and handles the UART PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * \param p_uart    The handle to the UART port returned by the
 *     freertos_uart_serial_init() call used to initialise the port.
 * \param data    A pointer to the buffer into which received data is to be
 *     copied.
 * \param len    The number of bytes to copy.
 * \param block_time_ticks    Defines the maximum combined time the function
 *     will wait to get exclusive access to the peripheral and receive the
 *     requested number of bytes.  Other tasks will execute during any waiting
 *     time.
 *
 *     The FreeRTOS ASF UART driver is initialized using a
 *     call to freertos_uart_serial_init().  The
 *     freertos_driver_parameters.options_flags parameter passed to the
 *     initialization function defines the driver behavior.  If
 *     freertos_driver_parameters.options_flags had the USE_RX_ACCESS_MUTEX bit
 *     set, then the driver will only read from the UART buffer if it has
 *     first gained exclusive access to it.  block_time_ticks specifies the
 *     maximum amount of time the driver will wait to get exclusive access
 *     before aborting the read operation.
 *
 *     If the number of bytes available is less than the number requested then
 *     freertos_uart_serial_read_packet() will wait for more bytes to become
 *     available.  block_time_ticks specifies the maximum amount of time the
 *     driver will wait before returning fewer bytes than were requested.
 *
 *     block_time_ticks is specified in RTOS tick periods.  To specify a block
 *     time in milliseconds, divide the milliseconds value by portTICK_RATE_MS,
 *     and pass the result in  block_time_ticks.  portTICK_RATE_MS is defined by
 *     FreeRTOS.
 *
 * \return     The number of bytes that were copied into data.  This will be
 *     less than the requested number of bytes if a time out occurred.
 */
uint32_t freertos_uart_serial_read_packet(freertos_uart_if p_uart,
		uint8_t *data, uint32_t len, portTickType block_time_ticks)
{
	portBASE_TYPE uart_index, attempt_read;
	Uart *uart_base;
	xTimeOutType time_out_definition;
	uint32_t bytes_read = 0;

	uart_base = (Uart *) p_uart;
	uart_index = get_pdc_peripheral_details(all_uart_definitions,
			MAX_UARTS,
			(void *) uart_base);

	/* It is possible to initialise the peripheral to only use Tx and not Rx.
	Check that Rx has been initialised. */
	configASSERT(rx_buffer_definitions[uart_index].next_byte_to_read);
	configASSERT(rx_buffer_definitions[uart_index].next_byte_to_read !=
			RX_NOT_USED);

	/* Only do anything if the UART is valid. */
	if (uart_index < MAX_UARTS) {
		/* Must not request more bytes than will fit in the buffer. */
		if (len <=
				(rx_buffer_definitions[uart_index].past_rx_buffer_end_address
				- rx_buffer_definitions[uart_index].rx_buffer_start_address)) {
			/* Remember the time on entry. */
			vTaskSetTimeOutState(&time_out_definition);

			/* If an Rx mutex is in use, attempt to obtain it. */
			if (rx_buffer_definitions[uart_index].rx_access_mutex != NULL) {
				/* Attempt to obtain the mutex. */
				attempt_read = xSemaphoreTake(
						rx_buffer_definitions[uart_index].rx_access_mutex,
						block_time_ticks);

				if (attempt_read == pdTRUE) {
					/* The semaphore was obtained, adjust the block_time_ticks to take
					into account the time taken to obtain the semaphore. */
					if (xTaskCheckForTimeOut(&time_out_definition,
							&block_time_ticks) == pdTRUE) {
						attempt_read = pdFALSE;

						/* The port is not going to be used, so return the
						mutex now. */
						xSemaphoreGive(rx_buffer_definitions[uart_index].rx_access_mutex);
					}
				}
			} else {
				attempt_read = pdTRUE;
			}

			if (attempt_read == pdTRUE) {
				do {
					/* Wait until data is available. */
					xSemaphoreTake(rx_buffer_definitions[uart_index].rx_event_semaphore,
							block_time_ticks);

					/* Copy as much data as is available, up to however much
					a maximum of the total number of requested bytes. */
					bytes_read += freertos_copy_bytes_from_pdc_circular_buffer(
							&(rx_buffer_definitions[uart_index]),
							all_uart_definitions[uart_index].pdc_base_address->PERIPH_RPR,
							&(data[bytes_read]),
							(len - bytes_read));

					/* The Rx DMA will have stopped if the Rx buffer had become
					full before this read operation.  If bytes were removed by
					this read then there is guaranteed to be space in the Rx
					buffer and the Rx DMA can be restarted. */
					if (bytes_read > 0) {
						taskENTER_CRITICAL();
						{
							if(rx_buffer_definitions[uart_index].rx_pdc_parameters.ul_size == 0UL) {
								configure_rx_dma(uart_index, data_removed);
							}
						}
						taskEXIT_CRITICAL();
					}

				  /* Until all the requested bytes are received, or the function
				  runs out of time. */
				} while ((bytes_read < len) && (xTaskCheckForTimeOut(
						&time_out_definition,
						&block_time_ticks) == pdFALSE));

				if (rx_buffer_definitions[uart_index].rx_access_mutex != NULL) {
					/* Return the mutex. */
					xSemaphoreGive(rx_buffer_definitions[uart_index].rx_access_mutex);
				}
			}
		}
	}

	return bytes_read;
}

/*
 * For internal use only.
 * Configures the Rx DMA to receive data into free space within the Rx buffer.
 */
static void configure_rx_dma(uint32_t uart_index,
		enum buffer_operations operation_performed)
{
	freertos_pdc_rx_control_t *rx_buffer_definition;

	rx_buffer_definition = &(rx_buffer_definitions[uart_index]);

	/* How much space is there between the start of the DMA buffer and the
	current read pointer?  */

	if (((uint32_t)rx_buffer_definition->next_byte_to_read) ==
			rx_buffer_definition->rx_pdc_parameters.ul_addr) {
		/* The read pointer and the write pointer are equal.  If this function
		was called because data was added to the buffer, then there is no free
		space in the buffer remaining.  If this function was called because data
		was removed from the buffer, then the space remaining is from the write
		pointer up to the end of the buffer. */
		if (operation_performed == data_added) {
			rx_buffer_definition->rx_pdc_parameters.ul_size = 0UL;
		} else {
			rx_buffer_definition->rx_pdc_parameters.ul_size =
				rx_buffer_definition->past_rx_buffer_end_address - rx_buffer_definition->rx_pdc_parameters.ul_addr;
		}
	} else if (((uint32_t)rx_buffer_definition->next_byte_to_read) >
			rx_buffer_definition->rx_pdc_parameters.ul_addr) {
		/* The read pointer is ahead of the write pointer.  The space available
		is up to the write pointer to ensure unread data is not overwritten. */
		rx_buffer_definition->rx_pdc_parameters.ul_size =
			((uint32_t) rx_buffer_definition->next_byte_to_read) - rx_buffer_definition->rx_pdc_parameters.ul_addr;
	} else {
		/* The write pointer is ahead of the read pointer so the space
		available is up to the end of the buffer. */
		rx_buffer_definition->rx_pdc_parameters.ul_size =
			rx_buffer_definition->past_rx_buffer_end_address - rx_buffer_definition->rx_pdc_parameters.ul_addr;
	}

	configASSERT((rx_buffer_definition->rx_pdc_parameters.ul_addr+
			rx_buffer_definition->rx_pdc_parameters.ul_size) <=
			rx_buffer_definition->past_rx_buffer_end_address);

	if (rx_buffer_definition->rx_pdc_parameters.ul_size > 0) {
		/* Restart the DMA to receive into whichever space was calculated
		as remaining.  First clear any characters that might already be in the
		registers. */
		pdc_rx_init(
				all_uart_definitions[uart_index].pdc_base_address, &rx_buffer_definition->rx_pdc_parameters,
				NULL);
		pdc_enable_transfer(
				all_uart_definitions[uart_index].pdc_base_address,
				PERIPH_PTCR_RXTEN);
		uart_enable_interrupt(
				all_uart_definitions[uart_index].peripheral_base_address,
				UART_IER_ENDRX | UART_IER_RXRDY);
	} else {
		/* The write pointer has reached the read pointer.  There is no
		more room so the DMA is not re-enabled until a read has created
		space. */
		uart_disable_interrupt(
				all_uart_definitions[uart_index].peripheral_base_address,
				UART_IDR_ENDRX | UART_IDR_RXRDY);
	}
}

/*
 * For internal use only.
 * A common UART interrupt handler that is called for all UART peripherals.
 */
static void local_uart_handler(const portBASE_TYPE uart_index)
{
	portBASE_TYPE higher_priority_task_woken = pdFALSE;
	uint32_t uart_status;
	freertos_pdc_rx_control_t *rx_buffer_definition;

	uart_status = uart_get_status(
			all_uart_definitions[uart_index].peripheral_base_address);
	uart_status &= uart_get_interrupt_mask(
			all_uart_definitions[uart_index].peripheral_base_address);

	rx_buffer_definition = &(rx_buffer_definitions[uart_index]);

	/* Has the PDC completed a transmission? */
	if ((uart_status & UART_SR_ENDTX) != 0UL) {
		uart_disable_interrupt(
				all_uart_definitions[uart_index].peripheral_base_address,
				UART_IDR_ENDTX);

		/* If the driver is supporting multi-threading, then return the access
		mutex. */
		if (tx_dma_control[uart_index].peripheral_access_sem != NULL) {
			xSemaphoreGiveFromISR(
					tx_dma_control[uart_index].peripheral_access_sem,
					&higher_priority_task_woken);
		}

		/* if the sending task supplied a notification semaphore, then
		notify the task that the transmission has completed. */
		if (tx_dma_control[uart_index].transaction_complete_notification_semaphore != NULL) {
			xSemaphoreGiveFromISR(
					tx_dma_control[uart_index].transaction_complete_notification_semaphore,
					&higher_priority_task_woken);
		}
	}

	if ((uart_status & UART_SR_ENDRX) != 0UL) {
		/* It is possible to initialise the peripheral to only use Tx and not Rx.
		Check that Rx has been initialised. */
		configASSERT(rx_buffer_definition->next_byte_to_read);
		configASSERT(rx_buffer_definition->next_byte_to_read !=
				RX_NOT_USED);

		/* Out of DMA buffer, configure the next buffer.  Start by moving
		the DMA buffer start address up to the end of the previously defined
		buffer. */
		rx_buffer_definition->rx_pdc_parameters.ul_addr +=
				rx_buffer_definition->rx_pdc_parameters.ul_size;

		/* If the end of the buffer has been reached, wrap back to the start. */
		if (rx_buffer_definition->rx_pdc_parameters.ul_addr >=
				rx_buffer_definition->past_rx_buffer_end_address)
		{
			rx_buffer_definition->rx_pdc_parameters.ul_addr =
					rx_buffer_definition->rx_buffer_start_address;
		}

		/* Reset the Rx DMA to receive data into whatever free space remains in
		the Rx buffer. */
		configure_rx_dma(uart_index, data_added);

		if (rx_buffer_definition->rx_event_semaphore != NULL) {
			/* Notify that new data is available. */
			xSemaphoreGiveFromISR(
					rx_buffer_definition->rx_event_semaphore,
					&higher_priority_task_woken);
		}
	}

	/**
	 * Normally the uart_status can't be "0" when the interrupt happened.
	 * It happened only when in PDC mode with TXRDY and RXRDY interrupts since
	 * the flags has been cleared by PDC.
	 * As the TXRDY is never enabled in this service, here we
	 * check the RXRDY interrupt case.
	 */
	if (uart_status == 0UL) {
		/* Character has been placed into the Rx buffer. */
		if (rx_buffer_definition->rx_event_semaphore != NULL) {
			/* Notify that new data is available. */
			xSemaphoreGiveFromISR(
					rx_buffer_definition->rx_event_semaphore,
					&higher_priority_task_woken);
		}
	}

	if ((uart_status & SR_ERROR_INTERRUPTS) != 0) {
		/* An error occurred in either a transmission or reception.  Abort, and
		ensure the peripheral access mutex is made available to tasks. */
		uart_reset_status(
				all_uart_definitions[uart_index].peripheral_base_address);
		if (tx_dma_control[uart_index].peripheral_access_sem != NULL) {
			xSemaphoreGiveFromISR(
					tx_dma_control[uart_index].peripheral_access_sem,
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

#ifdef UART

void UART_Handler(void)
{
	local_uart_handler(0);
}

#endif /* UART */

#ifdef UART0

void UART0_Handler(void)
{
	local_uart_handler(0);
}

#endif /* UART0 */

#ifdef UART1

void UART1_Handler(void)
{
	local_uart_handler(1);
}

#endif /* UART1 */

#ifdef UART2

void UART2_Handler(void)
{
	local_uart_handler(2);
}

#endif /* UART2 */

