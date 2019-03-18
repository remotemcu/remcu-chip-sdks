/**
 * \file
 *
 * \brief FreeRTOS Peripheral Control API For the USART
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

/* ASF includes. */
#include "serial.h"
#include "freertos_usart_serial.h"
#include "freertos_peripheral_control_private.h"
#if (SAMG55)
#include "flexcom.h"
#endif

/* Every bit in the interrupt mask. */
#define MASK_ALL_INTERRUPTS         (0xffffffffUL)

/* Interrupts that are enabled to catch error conditions on the bus. */
#define SR_ERROR_INTERRUPTS         (US_CSR_OVRE | US_CSR_FRAME | US_CSR_PARE)
#define IER_ERROR_INTERRUPTS        (US_IER_OVRE | US_IER_FRAME | US_IER_PARE)

/* A value written to a member of an Rx buffer to show that the Rx side was not
initialised and therefore should not be used. */
#define RX_NOT_USED                 (uint8_t *) 0x1

/* Divide by this number to convert bits per second to bits per 5 milliseconds.
Equivalent to times 5 then divide by 1000. */
#define BITS_PER_5_MS               (200UL)

/* Work out how many USARTS are present. */
#if defined(PDC_USART7)
	#define MAX_USARTS                              (8)
#elif defined(PDC_USART6)
	#define MAX_USARTS                              (7)
#elif defined(PDC_USART5)
	#define MAX_USARTS                              (6)
#elif defined(PDC_USART4)
	#define MAX_USARTS                              (5)
#elif defined(PDC_USART3)
	#define MAX_USARTS                              (4)
#elif defined(PDC_USART2)
	#define MAX_USARTS                              (3)
#elif defined(PDC_USART1)
	#define MAX_USARTS                              (2)
#elif defined(PDC_USART0)
	#define MAX_USARTS                              (1)
#elif defined(PDC_USART)
	#define MAX_USARTS                              (1)
#else
	#error No PDC USARTS defined
#endif


enum buffer_operations {
	data_added = 0,
	data_removed
};

/* Configures the Rx DMA to receive data into free space within the Rx buffer. */
static void configure_rx_dma(uint32_t usart_index,
		enum buffer_operations operation_performed);

/* A common interrupt handler called by all the USART peripherals. */
static void local_usart_handler(const portBASE_TYPE usart_index);

/* Structures to manage the DMA control for both Rx and Tx transactions. */
static freertos_pdc_rx_control_t rx_buffer_definitions[MAX_USARTS];
static freertos_dma_event_control_t tx_dma_control[MAX_USARTS];

/* Create an array that holds the information required about each defined
USART. */
static const freertos_pdc_peripheral_parameters_t all_usart_definitions[MAX_USARTS] = {
#if SAMG55
	{USART0, PDC_USART0, ID_FLEXCOM0, FLEXCOM0_IRQn},
	{USART1, PDC_USART1, ID_FLEXCOM1, FLEXCOM1_IRQn},
	{USART2, PDC_USART2, ID_FLEXCOM2, FLEXCOM2_IRQn},
	{USART3, PDC_USART3, ID_FLEXCOM3, FLEXCOM3_IRQn},
	{USART4, PDC_USART4, ID_FLEXCOM4, FLEXCOM4_IRQn},
	{USART5, PDC_USART5, ID_FLEXCOM5, FLEXCOM5_IRQn},
	{USART6, PDC_USART6, ID_FLEXCOM6, FLEXCOM6_IRQn},
#if (MAX_USARTS > 7)
	{USART7, PDC_USART7, ID_FLEXCOM7, FLEXCOM7_IRQn},
#endif

#else
#if	defined(PDC_USART0)
	{USART0, PDC_USART0, ID_USART0, USART0_IRQn},
#endif

#if	defined(PDC_USART)
	{USART, PDC_USART, ID_USART, USART_IRQn},
#endif

#if (MAX_USARTS > 1)
	{USART1, PDC_USART1, ID_USART1, USART1_IRQn},
#endif

#if (MAX_USARTS > 2)
	{USART2, PDC_USART2, ID_USART2, USART2_IRQn},
#endif

#if (MAX_USARTS > 3)
	{USART3, PDC_USART3, ID_USART3, USART3_IRQn},
#endif

#if (MAX_USARTS > 4)
	{USART4, PDC_USART4, ID_USART4, USART4_IRQn},
#endif

#if (MAX_USARTS > 5)
	{USART5, PDC_USART5, ID_USART5, USART5_IRQn},
#endif

#if (MAX_USARTS > 6)
	{USART6, PDC_USART6, ID_USART6, USART6_IRQn},
#endif

#if (MAX_USARTS > 7)
	{USART7, PDC_USART7, ID_USART7, USART7_IRQn},
#endif

#endif
};

/**
 * \ingroup freertos_usart_peripheral_control_group
 * \brief Initializes the FreeRTOS ASF USART driver for the specified USART
 * port.
 *
 * freertos_usart_serial_init() is an ASF specific FreeRTOS driver function.  It
 * must be called before any other ASF specific FreeRTOS driver functions
 * attempt to access the same USART port.
 *
 * If freertos_driver_parameters->operation_mode equals USART_RS232 then
 * freertos_usart_serial_init() will configure the USART port for standard RS232
 * operation.  If freertos_driver_parameters->operation_mode equals any other
 * value then freertos_usart_serial_init() will not take any action.
 *
 * Other ASF USART functions can be called after freertos_usart_serial_init()
 * has completed successfully.
 *
 * The FreeRTOS ASF driver both installs and handles the USART PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * This driver is provided with an application note, and an example project that
 * demonstrates the use of this function.
 *
 * \param p_usart    The USART peripheral being initialized.
 * \param uart_parameters    Structure that defines the USART bus and transfer
 *     parameters, such the baud rate and the number of data bits.
 *     sam_usart_opt_t is a standard ASF type (it is not FreeRTOS specific).
 * \param freertos_driver_parameters    Defines the driver behavior.  See the
 *    freertos_peripheral_options_t documentation, and the application note that
 *    accompanies the ASF specific FreeRTOS functions.
 *
 * \return If the initialization completes successfully then a handle that can
 *     be used with FreeRTOS USART read and write functions is returned.  If
 *     the initialisation fails then NULL is returned.
 */
freertos_usart_if freertos_usart_serial_init(Usart *p_usart,
		const sam_usart_opt_t *const uart_parameters,
		const freertos_peripheral_options_t *const freertos_driver_parameters)
{
	portBASE_TYPE usart_index;
	bool is_valid_operating_mode;
	freertos_usart_if return_value;
	const enum peripheral_operation_mode valid_operating_modes[] = {USART_RS232};

	/* Find the index into the all_usart_definitions array that holds details of
	the p_usart peripheral. */
	usart_index = get_pdc_peripheral_details(all_usart_definitions,
			MAX_USARTS,
			(void *) p_usart);

	/* Check the requested operating mode is valid for the peripheral. */
	is_valid_operating_mode = check_requested_operating_mode(
			freertos_driver_parameters->operation_mode,
			valid_operating_modes,
			sizeof(valid_operating_modes) /
			sizeof(enum peripheral_operation_mode));

	/* Don't do anything unless a valid p_usart pointer was used, and a valid
	operating mode was requested. */
	if ((usart_index < MAX_USARTS) && (is_valid_operating_mode == true)) {
		/* This function must be called exactly once per supported USART.  Check it
		has not been called	before. */
		configASSERT(rx_buffer_definitions[usart_index].next_byte_to_read == NULL);

		/* Disable everything before enabling the clock. */
		usart_disable_tx(p_usart);
		usart_disable_rx(p_usart);
		pdc_disable_transfer(all_usart_definitions[usart_index].pdc_base_address,
				(PERIPH_PTCR_RXTDIS | PERIPH_PTCR_TXTDIS));

#if (SAMG55)
		/* Enable the peripheral and set USART mode. */
		uint32_t temp = (uint32_t)all_usart_definitions[usart_index].peripheral_base_address - 0x200;
		Flexcom *p_flexcom = (Flexcom *)temp;
		flexcom_enable(p_flexcom);
		flexcom_set_opmode(p_flexcom, FLEXCOM_USART);
#else
		/* Enable the peripheral clock in the PMC. */
		pmc_enable_periph_clk(
				all_usart_definitions[usart_index].peripheral_id);
#endif

		switch (freertos_driver_parameters->operation_mode) {
		case USART_RS232:
			/* Call the standard ASF init function. */
			usart_init_rs232(p_usart, uart_parameters,
					sysclk_get_cpu_hz());
			break;

		default:
			/* Other modes are not currently supported. */
			break;
		}

		/* Disable all the interrupts. */
		usart_disable_interrupt(p_usart, MASK_ALL_INTERRUPTS);

		/* Create any required peripheral access mutexes and transaction complete
		semaphores.  This peripheral is full duplex so only the Tx semaphores
		are created in the following function.  The the Rx semaphores are
		created	separately. */
		create_peripheral_control_semaphores(
				freertos_driver_parameters->options_flags,
				&(tx_dma_control[usart_index]),
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
			rx_buffer_definitions[usart_index].rx_event_semaphore =
					xSemaphoreCreateCounting(portMAX_DELAY, 0);
			configASSERT(rx_buffer_definitions[usart_index].rx_event_semaphore);

			/* Set the timeout to 5ms, then start waiting for a character (the
			timeout is not started until characters have started to	be
			received). */
			usart_set_rx_timeout(p_usart,
					(uart_parameters->baudrate / BITS_PER_5_MS));
			usart_start_rx_timeout(p_usart);

			/* The receive buffer is currently empty, so the DMA has control
			over the entire buffer. */
			rx_buffer_definitions[usart_index].rx_pdc_parameters.ul_addr =
					(uint32_t)freertos_driver_parameters->receive_buffer;
			rx_buffer_definitions[usart_index].rx_pdc_parameters.ul_size =
					freertos_driver_parameters->receive_buffer_size;
			pdc_rx_init(
					all_usart_definitions[usart_index].pdc_base_address,
					&(rx_buffer_definitions[usart_index].rx_pdc_parameters),
					NULL);

			/* Set the next byte to read to the start of the buffer as no data
			has yet been read. */
			rx_buffer_definitions[usart_index].next_byte_to_read =
					freertos_driver_parameters->receive_buffer;

			/* Remember the limits of entire buffer. */
			rx_buffer_definitions[usart_index].rx_buffer_start_address =
					rx_buffer_definitions[usart_index].rx_pdc_parameters.ul_addr;
			rx_buffer_definitions[usart_index].past_rx_buffer_end_address =
					rx_buffer_definitions[usart_index].rx_buffer_start_address +
					freertos_driver_parameters->receive_buffer_size;

			/* If the rx driver is to be thread aware, create an access control
			mutex. */
			if ((freertos_driver_parameters->options_flags &
					USE_RX_ACCESS_MUTEX) != 0) {
				rx_buffer_definitions[usart_index].rx_access_mutex =
					xSemaphoreCreateMutex();
				configASSERT(rx_buffer_definitions[usart_index].rx_access_mutex);
			}

			/* Catch the DMA running out of Rx space, and gaps in the
			reception.  These events are both used to signal that there is
			data available in the Rx buffer. */
			usart_enable_interrupt(p_usart, US_IER_ENDRX | US_IER_TIMEOUT);

			/* The Rx DMA is running all the time, so enable it now. */
			pdc_enable_transfer(
					all_usart_definitions[usart_index].pdc_base_address,
					PERIPH_PTCR_RXTEN);
		} else {
			/* next_byte_to_read is used to check to see if this function
			has been called before, so it must be set to something, even if
			it is not going to be used.  The value it is set to is not
			important, provided it is not zero (NULL). */
			rx_buffer_definitions[usart_index].next_byte_to_read = RX_NOT_USED;
		}

		/* Configure and enable the USART interrupt in the interrupt controller. */
		configure_interrupt_controller(all_usart_definitions[usart_index].peripheral_irq,
				freertos_driver_parameters->interrupt_priority);

		/* Error interrupts are always enabled. */
		usart_enable_interrupt(
				all_usart_definitions[usart_index].peripheral_base_address,
				IER_ERROR_INTERRUPTS);

		/* Finally, enable the receiver and transmitter. */
		usart_enable_tx(p_usart);
		usart_enable_rx(p_usart);

		return_value = (freertos_usart_if) p_usart;
	} else {
		return_value = NULL;
	}

	return return_value;
}

/**
 * \ingroup freertos_usart_peripheral_control_group
 * \brief Initiate a completely asynchronous multi-byte write operation on a
 * USART peripheral.
 *
 * freertos_usart_write_packet_async() is an ASF specific FreeRTOS driver
 * function.  It configures the USART peripheral DMA controller (PDC) to
 * transmit data on the USART port, then returns.
 * freertos_usart_write_packet_async() does not wait for the transmission to
 * complete before returning.
 *
 * The FreeRTOS USART driver is initialized using a call to
 * freertos_usart_serial_init().  The freertos_driver_parameters.options_flags
 * parameter passed into the initialization function defines the driver behavior.
 * freertos_usart_write_packet_async() can only be used if the
 * freertos_driver_parameters.options_flags parameter passed to the initialization
 * function had the WAIT_TX_COMPLETE bit clear.
 *
 * freertos_usart_write_packet_async() is an advanced function and readers are
 * recommended to also reference the application note and examples that
 * accompany the FreeRTOS ASF drivers.  freertos_usart_write_packet() is a
 * version that does not exit until the PDC transfer is complete, but still
 * allows other RTOS tasks to execute while the transmission is in progress.
 *
 * The FreeRTOS ASF driver both installs and handles the USART PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * \param p_usart    The handle to the USART peripheral returned by the
 *     freertos_usart_serial_init() call used to initialise the peripheral.
 * \param data    A pointer to the data to be transmitted.
 * \param len    The number of bytes to transmit.
 * \param block_time_ticks    The FreeRTOS ASF USART driver is initialized using
 *     a call to freertos_usart_serial_init().  The
 *     freertos_driver_parameters.options_flags parameter passed to the
 *     initialization function defines the driver behavior.  If
 *     freertos_driver_parameters.options_flags had the USE_TX_ACCESS_SEM bit
 *     set, then the driver will only write to the USART peripheral if it has
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
 *     access to the USART peripheral could be obtained.  STATUS_OK is returned
 *     if the PDC was successfully configured to perform the USART write
 *     operation.
 */
status_code_t freertos_usart_write_packet_async(freertos_usart_if p_usart,
		const uint8_t *data, size_t len, portTickType block_time_ticks,
		xSemaphoreHandle notification_semaphore)
{
	status_code_t return_value;
	portBASE_TYPE usart_index;
	Usart *usart_base;

	usart_base = (Usart *) p_usart;
	usart_index = get_pdc_peripheral_details(all_usart_definitions,
			MAX_USARTS,
			(void *) usart_base);

	/* Don't do anything unless a valid USART pointer was used. */
	if (usart_index < MAX_USARTS) {
		return_value = freertos_obtain_peripheral_access_semphore(
				&(tx_dma_control[usart_index]),
				&block_time_ticks);

		if (return_value == STATUS_OK) {
			freertos_start_pdc_tx(&(tx_dma_control[usart_index]),
					data, len,
					all_usart_definitions[usart_index].pdc_base_address,
					notification_semaphore);

			/* Catch the end of transmission so the access mutex can be
			returned, and the task notified (if it supplied a notification
			semaphore).  The interrupt can be enabled here because the ENDTX
			signal from the PDC to the USART will have been de-asserted when
			the next transfer was configured. */
			usart_enable_interrupt(usart_base, US_IER_ENDTX);

			return_value = freertos_optionally_wait_transfer_completion(
					&(tx_dma_control[usart_index]),
					notification_semaphore,
					block_time_ticks);
		}
	} else {
		return_value = ERR_INVALID_ARG;
	}

	return return_value;
}

/**
 * \ingroup freertos_usart_peripheral_control_group
 * \brief Initiate a completely multi-byte read operation on a USART peripheral.
 *
 * The FreeRTOS ASF USART driver uses the PDC to transfer data from a peripheral
 * to a circular buffer.  Reception happens in the background, while the
 * microcontroller is executing application code.* freertos_usart_read_packet()
 * copies bytes from the DMA buffer into the buffer passed as a
 * freertos_usart_read_packet() parameter.
 *
 * Readers are recommended to also reference the application note and examples
 * that accompany the FreeRTOS ASF drivers.
 *
 * The FreeRTOS ASF driver both installs and handles the USART PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * \param p_usart    The handle to the USART port returned by the
 *     freertos_usart_serial_init() call used to initialise the port.
 * \param data    A pointer to the buffer into which received data is to be
 *     copied.
 * \param len    The number of bytes to copy.
 * \param block_time_ticks    Defines the maximum combined time the function
 *     will wait to get exclusive access to the peripheral and receive the
 *     requested number of bytes.  Other tasks will execute during any waiting
 *     time.
 *
 *     The FreeRTOS ASF USART driver is initialized using a
 *     call to freertos_usart_serial_init().  The
 *     freertos_driver_parameters.options_flags parameter passed to the
 *     initialization function defines the driver behavior.  If
 *     freertos_driver_parameters.options_flags had the USE_RX_ACCESS_MUTEX bit
 *     set, then the driver will only read from the USART buffer if it has
 *     first gained exclusive access to it.  block_time_ticks specifies the
 *     maximum amount of time the driver will wait to get exclusive access
 *     before aborting the read operation.
 *
 *     If the number of bytes available is less than the number requested then
 *     freertos_usart_serial_read_packet() will wait for more bytes to become
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
uint32_t freertos_usart_serial_read_packet(freertos_usart_if p_usart,
		uint8_t *data, uint32_t len, portTickType block_time_ticks)
{
	portBASE_TYPE usart_index, attempt_read;
	Usart *usart_base;
	xTimeOutType time_out_definition;
	uint32_t bytes_read = 0;

	usart_base = (Usart *) p_usart;
	usart_index = get_pdc_peripheral_details(all_usart_definitions,
			MAX_USARTS,
			(void *) usart_base);

	/* It is possible to initialise the peripheral to only use Tx and not Rx.
	Check that Rx has been initialised. */
	configASSERT(rx_buffer_definitions[usart_index].next_byte_to_read);
	configASSERT(rx_buffer_definitions[usart_index].next_byte_to_read !=
			RX_NOT_USED);

	/* Only do anything if the USART is valid. */
	if (usart_index < MAX_USARTS) {
		/* Must not request more bytes than will fit in the buffer. */
		if (len <=
				(rx_buffer_definitions[usart_index].past_rx_buffer_end_address
				- rx_buffer_definitions[usart_index].rx_buffer_start_address)) {
			/* Remember the time on entry. */
			vTaskSetTimeOutState(&time_out_definition);

			/* If an Rx mutex is in use, attempt to obtain it. */
			if (rx_buffer_definitions[usart_index].rx_access_mutex != NULL) {
				/* Attempt to obtain the mutex. */
				attempt_read = xSemaphoreTake(
						rx_buffer_definitions[usart_index].rx_access_mutex,
						block_time_ticks);

				if (attempt_read == pdTRUE) {
					/* The semaphore was obtained, adjust the block_time_ticks to take
					into account the time taken to obtain the semaphore. */
					if (xTaskCheckForTimeOut(&time_out_definition,
							&block_time_ticks) == pdTRUE) {
						attempt_read = pdFALSE;

						/* The port is not going to be used, so return the
						mutex now. */
						xSemaphoreGive(rx_buffer_definitions[usart_index].rx_access_mutex);
					}
				}
			} else {
				attempt_read = pdTRUE;
			}

			if (attempt_read == pdTRUE) {
				do {
					/* Wait until data is available. */
					xSemaphoreTake(rx_buffer_definitions[usart_index].rx_event_semaphore,
							block_time_ticks);

					/* Copy as much data as is available, up to however much
					a maximum of the total number of requested bytes. */
					bytes_read += freertos_copy_bytes_from_pdc_circular_buffer(
							&(rx_buffer_definitions[usart_index]),
							all_usart_definitions[usart_index].pdc_base_address->PERIPH_RPR,
							&(data[bytes_read]),
							(len - bytes_read));

					/* The Rx DMA will have stopped if the Rx buffer had become
					full before this read operation.  If bytes were removed by
					this read then there is guaranteed to be space in the Rx
					buffer and the Rx DMA can be restarted. */
					if (bytes_read > 0) {
						taskENTER_CRITICAL();
						{
							if(rx_buffer_definitions[usart_index].rx_pdc_parameters.ul_size == 0UL) {
								configure_rx_dma(usart_index, data_removed);
							}
						}
						taskEXIT_CRITICAL();
					}

				  /* Until all the requested bytes are received, or the function
				  runs out of time. */
				} while ((bytes_read < len) && (xTaskCheckForTimeOut(
						&time_out_definition,
						&block_time_ticks) == pdFALSE));

				if (rx_buffer_definitions[usart_index].rx_access_mutex != NULL) {
					/* Return the mutex. */
					xSemaphoreGive(rx_buffer_definitions[usart_index].rx_access_mutex);
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
static void configure_rx_dma(uint32_t usart_index,
		enum buffer_operations operation_performed)
{
	freertos_pdc_rx_control_t *rx_buffer_definition;

	rx_buffer_definition = &(rx_buffer_definitions[usart_index]);

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

	configASSERT((rx_buffer_definition->rx_pdc_parameters.ul_addr +
			rx_buffer_definition->rx_pdc_parameters.ul_size) <=
			rx_buffer_definition->past_rx_buffer_end_address);

	if (rx_buffer_definition->rx_pdc_parameters.ul_size > 0) {
		/* Restart the DMA to receive into whichever space was calculated
		as remaining.  First clear any characters that might already be in the
		registers. */
		pdc_rx_init(
				all_usart_definitions[usart_index].pdc_base_address, &rx_buffer_definition->rx_pdc_parameters,
				NULL);
		pdc_enable_transfer(
				all_usart_definitions[usart_index].pdc_base_address,
				PERIPH_PTCR_RXTEN);
		usart_enable_interrupt(
				all_usart_definitions[usart_index].peripheral_base_address, US_IER_ENDRX |
				US_IER_TIMEOUT);
	} else {
		/* The write pointer has reached the read pointer.  There is no
		more room so the DMA is not re-enabled until a read has created
		space. */
		usart_disable_interrupt(
				all_usart_definitions[usart_index].peripheral_base_address, US_IER_ENDRX |
				US_IER_TIMEOUT);
	}
}

/*
 * For internal use only.
 * A common USART interrupt handler that is called for all USART peripherals.
 */
static void local_usart_handler(const portBASE_TYPE usart_index)
{
	portBASE_TYPE higher_priority_task_woken = pdFALSE;
	uint32_t usart_status;
	freertos_pdc_rx_control_t *rx_buffer_definition;

	usart_status = usart_get_status(
			all_usart_definitions[usart_index].peripheral_base_address);
	usart_status &= usart_get_interrupt_mask(
			all_usart_definitions[usart_index].peripheral_base_address);

	rx_buffer_definition = &(rx_buffer_definitions[usart_index]);

	/* Has the PDC completed a transmission? */
	if ((usart_status & US_CSR_ENDTX) != 0UL) {
		usart_disable_interrupt(
				all_usart_definitions[usart_index].peripheral_base_address,
				US_IER_ENDTX);

		/* If the driver is supporting multi-threading, then return the access
		mutex. */
		if (tx_dma_control[usart_index].peripheral_access_sem != NULL) {
			xSemaphoreGiveFromISR(
					tx_dma_control[usart_index].peripheral_access_sem,
					&higher_priority_task_woken);
		}

		/* if the sending task supplied a notification semaphore, then
		notify the task that the transmission has completed. */
		if (tx_dma_control[usart_index].transaction_complete_notification_semaphore != NULL) {
			xSemaphoreGiveFromISR(
					tx_dma_control[usart_index].transaction_complete_notification_semaphore,
					&higher_priority_task_woken);
		}
	}

	if ((usart_status & US_CSR_ENDRX) != 0UL) {
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
		configure_rx_dma(usart_index, data_added);

		if (rx_buffer_definition->rx_event_semaphore != NULL) {
			/* Notify that new data is available. */
			xSemaphoreGiveFromISR(
					rx_buffer_definition->rx_event_semaphore,
					&higher_priority_task_woken);
		}
	}

	if ((usart_status & US_IER_TIMEOUT) != 0UL) {
		/* More characters have been placed into the Rx buffer.

		Restart the timeout after more data has been received. */
		usart_start_rx_timeout(all_usart_definitions[usart_index].peripheral_base_address);

		if (rx_buffer_definition->rx_event_semaphore != NULL) {
			/* Notify that new data is available. */
			xSemaphoreGiveFromISR(
					rx_buffer_definition->rx_event_semaphore,
					&higher_priority_task_woken);
		}
	}

	if ((usart_status & SR_ERROR_INTERRUPTS) != 0) {
		/* An error occurred in either a transmission or reception.  Abort, and
		ensure the peripheral access mutex is made available to tasks. */
		usart_reset_status(
				all_usart_definitions[usart_index].peripheral_base_address);
		if (tx_dma_control[usart_index].peripheral_access_sem != NULL) {
			xSemaphoreGiveFromISR(
					tx_dma_control[usart_index].peripheral_access_sem,
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
#if SAMG55
#ifdef CONF_FREERTOS_USE_USART0
void FLEXCOM0_Handler(void)
{
	local_usart_handler(0);
}
#endif
#ifdef CONF_FREERTOS_USE_USART1
void FLEXCOM1_Handler(void)
{
	local_usart_handler(1);
}
#endif
#ifdef CONF_FREERTOS_USE_USART2
void FLEXCOM2_Handler(void)
{
	local_usart_handler(2);
}
#endif
#ifdef CONF_FREERTOS_USE_USART3
void FLEXCOM3_Handler(void)
{
	local_usart_handler(3);
}
#endif
#ifdef CONF_FREERTOS_USE_USART4
void FLEXCOM4_Handler(void)
{
	local_usart_handler(4);
}
#endif
#ifdef CONF_FREERTOS_USE_USART5
void FLEXCOM5_Handler(void)
{
	local_usart_handler(5);
}
#endif
#ifdef CONF_FREERTOS_USE_USART6
void FLEXCOM6_Handler(void)
{
	local_usart_handler(6);
}
#endif
#ifdef CONF_FREERTOS_USE_USART7
void FLEXCOM7_Handler(void)
{
	local_usart_handler(7);
}
#endif
	
#else
#ifdef USART

void USART_Handler(void)
{
	local_usart_handler(0);
}

#endif /* USART */

#ifdef USART0

void USART0_Handler(void)
{
	local_usart_handler(0);
}

#endif /* USART0 */

#ifdef USART1

void USART1_Handler(void)
{
	local_usart_handler(1);
}

#endif /* USART1 */

#ifdef USART2

void USART2_Handler(void)
{
	local_usart_handler(2);
}

#endif /* USART2 */

#ifdef USART3

void USART3_Handler(void)
{
	local_usart_handler(3);
}

#endif /* USART3 */

#ifdef USART4

void USART4_Handler(void)
{
	local_usart_handler(4);
}

#endif /* USART4 */

#ifdef USART5

void USART5_Handler(void)
{
	local_usart_handler(5);
}

#endif /* USART5 */

#ifdef USART6

void USART6_Handler(void)
{
	local_usart_handler(6);
}

#endif /* USART6 */
#endif
