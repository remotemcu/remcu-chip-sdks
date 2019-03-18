/**
 * \file
 *
 * \brief FreeRTOS Peripheral Control API For the SPI
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
#include "spi_master.h"
#include "freertos_spi_master.h"
#include "freertos_peripheral_control_private.h"
#if SAMG55
#include "flexcom.h"
#endif

/* Every bit in the interrupt mask. */
#define MASK_ALL_INTERRUPTS                         (0xffffffffUL)

/* Interrupts that get enabled to catch error conditions on the bus.  The
 * overrun error is not enabled as overruns on Rx are expected while sending. */
#define SR_ERROR_INTERRUPTS                         (SPI_SR_MODF)
#define IER_ERROR_INTERRUPTS                        (SPI_IER_MODF)

/* Work out how many SPI ports are present. */
#if defined(SPI7)
	#define MAX_SPIS                                (8)
#elif defined(SPI6)
	#define MAX_SPIS                                (7)
#elif defined(SPI5)
	#define MAX_SPIS                                (6)
#elif defined(SPI4)
	#define MAX_SPIS                                (5)
#elif defined(SPI3)
	#define MAX_SPIS                                (4)
#elif defined(SPI2)
	#define MAX_SPIS                                (3)
#elif defined(SPI1)
	#define MAX_SPIS                                (2)
#elif defined(SPI0)
	#define MAX_SPIS                                (1)
#elif defined(SPI)
	#define MAX_SPIS                                (1)
#else
	#error No SPI peripherals defined
#endif

/*
 * A common interrupt handler used by all the SPI peripherals.
 */
static void local_spi_handler(const portBASE_TYPE spi_index);

/* Structures to manage the DMA control for both Rx and Tx transactions. */
static freertos_dma_event_control_t tx_dma_control[MAX_SPIS];
static freertos_dma_event_control_t rx_dma_control[MAX_SPIS];

/* Used to detect the init function being called after any part of the DMA
control structure has already been initialilsed - indicating an error condition
as init should only be called once per port. */
static const freertos_dma_event_control_t null_dma_control = {NULL, NULL};

/* Create an array that holds the information required about each defined
SPI peripheral. */
static const freertos_pdc_peripheral_parameters_t all_spi_definitions[MAX_SPIS] = {
	/* Chips with a single SPI port define SPI only.  Chips with multiple SPI
	ports defined the first SPI peripheral as SPI0. */
#if SAMG55
	{SPI0, PDC_SPI0, ID_FLEXCOM0, FLEXCOM0_IRQn},
	{SPI1, PDC_SPI1, ID_FLEXCOM1, FLEXCOM1_IRQn},
	{SPI2, PDC_SPI2, ID_FLEXCOM2, FLEXCOM2_IRQn},
	{SPI3, PDC_SPI3, ID_FLEXCOM3, FLEXCOM3_IRQn},
	{SPI4, PDC_SPI4, ID_FLEXCOM4, FLEXCOM4_IRQn},
	{SPI5, PDC_SPI5, ID_FLEXCOM5, FLEXCOM5_IRQn},
	{SPI6, PDC_SPI6, ID_FLEXCOM6, FLEXCOM6_IRQn},
#if MAX_SPIS > 7
	{SPI7, PDC_SPI7, ID_FLEXCOM7, FLEXCOM7_IRQn},
#endif

#else
#if defined(SPI)
	{SPI, PDC_SPI, ID_SPI, SPI_IRQn},
#else
	{SPI0, PDC_SPI0, ID_SPI0, SPI0_IRQn},
#endif

#if MAX_SPIS > 1
	{SPI1, PDC_SPI1, ID_SPI1, SPI1_IRQn},
#endif
#if MAX_SPIS > 2
	{SPI2, PDC_SPI2, ID_SPI2, SPI2_IRQn},
#endif
#if MAX_SPIS > 3
	{SPI3, PDC_SPI3, ID_SPI3, SPI3_IRQn},
#endif
#if MAX_SPIS > 4
	{SPI4, PDC_SPI4, ID_SPI4, SPI4_IRQn},
#endif
#if MAX_SPIS > 5
	{SPI5, PDC_SPI5, ID_SPI5, SPI5_IRQn},
#endif
#if MAX_SPIS > 6
	{SPI6, PDC_SPI6, ID_SPI6, SPI6_IRQn},
#endif
#if MAX_SPIS > 7
	{SPI7, PDC_SPI7, ID_SPI7, SPI7_IRQn},
#endif

#endif
};

/**
 * \ingroup freertos_spi_peripheral_control_group
 * \brief Initializes the FreeRTOS ASF SPI master driver for the specified SPI port.
 *
 * freertos_spi_master_init() is an ASF specific FreeRTOS driver function.  It
 * must be called before any other ASF specific FreeRTOS driver functions
 * attempt to access the same SPI port.
 *
 * If freertos_driver_parameters->operation_mode equals SPI_MASTER then
 * freertos_spi_master_init() will configure the SPI port for master mode
 * operation and enable the peripheral.  If
 * freertos_driver_parameters->operation_mode equals any other value then
 * freertos_spi_master_init() will not take any action.
 *
 * Other ASF SPI functions, such as those to set the SPI clock rate and other
 * bus parameters, can be called after freertos_spi_master_init() has completed
 * successfully.
 *
 * The FreeRTOS ASF driver both installs and handles the SPI PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * This driver is provided with an application note, and an example project that
 * demonstrates the use of this function.
 *
 * \param p_spi    The SPI peripheral being initialized.
 * \param freertos_driver_parameters    Defines the driver behavior.  See the
 *    freertos_peripheral_options_t documentation, and the application note that
 *    accompanies the ASF specific FreeRTOS functions.
 *
 * \return If the initialization completes successfully then a handle that can
 *     be used with FreeRTOS SPI read and write functions is returned.  If
 *     the initialisation fails then NULL is returned.
 */
freertos_spi_if freertos_spi_master_init(Spi *p_spi,
		const freertos_peripheral_options_t *const freertos_driver_parameters)
{
	portBASE_TYPE spi_index;
	bool is_valid_operating_mode;
	freertos_spi_if return_value;
	const enum peripheral_operation_mode valid_operating_modes[] = {SPI_MASTER};
#if (SAMG55)
	uint32_t temp;
#endif

	/* Find the index into the all_spi_definitions array that holds details of
	the p_spi peripheral. */
	spi_index = get_pdc_peripheral_details(all_spi_definitions, MAX_SPIS,
			(void *) p_spi);

	/* Check the requested operating mode is valid for the peripheral. */
	is_valid_operating_mode = check_requested_operating_mode(
			freertos_driver_parameters->operation_mode,
			valid_operating_modes,
			sizeof(valid_operating_modes) /
			sizeof(enum peripheral_operation_mode));

	/* Don't do anything unless a valid p_spi pointer was used, and a valid
	operating mode was requested. */
	if ((spi_index < MAX_SPIS) && (is_valid_operating_mode == true)) {
		/* This function must be called exactly once per supported spi.  Check it
		has not been called	before. */
		configASSERT(memcmp((void *) &(tx_dma_control[spi_index]),
				&null_dma_control,
				sizeof(null_dma_control)) == 0);
		configASSERT(memcmp((void *) &(rx_dma_control[spi_index]),
				&null_dma_control,
				sizeof(null_dma_control)) == 0);

		/* Ensure everything is disabled before configuration. */
		spi_disable(all_spi_definitions[spi_index].peripheral_base_address);
		pdc_disable_transfer(
				all_spi_definitions[spi_index].pdc_base_address,
				(PERIPH_PTCR_RXTDIS | PERIPH_PTCR_TXTDIS));
		spi_disable_interrupt(
				all_spi_definitions[spi_index].peripheral_base_address,
				MASK_ALL_INTERRUPTS);

		switch (freertos_driver_parameters->operation_mode) {
		case SPI_MASTER:
			/* Call the standard ASF init function. */
#if (SAMG55)
			/* Enable the peripheral and set SPI mode. */
			temp = (uint32_t)(all_spi_definitions[spi_index].peripheral_base_address - 0x400);
			Flexcom *p_flexcom = (Flexcom *)temp;
			flexcom_enable(p_flexcom);
			flexcom_set_opmode(p_flexcom, FLEXCOM_SPI);
#endif
			spi_master_init(
					all_spi_definitions[spi_index].peripheral_base_address);
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
				&(tx_dma_control[spi_index]),
				&(rx_dma_control[spi_index]));

		/* Configure and enable the SPI interrupt in the interrupt controller. */
		configure_interrupt_controller(
				all_spi_definitions[spi_index].peripheral_irq,
				freertos_driver_parameters->interrupt_priority);

		/* Error interrupts are always enabled. */
		spi_enable_interrupt(
				all_spi_definitions[spi_index].peripheral_base_address,
				IER_ERROR_INTERRUPTS);

		/* Finally, enable the peripheral. */
		spi_enable(all_spi_definitions[spi_index].peripheral_base_address);

		return_value = (freertos_spi_if)p_spi;
	} else {
		return_value = NULL;
	}

	return return_value;
}

/**
 * \ingroup freertos_spi_peripheral_control_group
 * \brief Initiate a completely asynchronous multi-byte write operation on an
 * SPI peripheral.
 *
 * freertos_spi_write_packet_async() is an ASF specific FreeRTOS driver function.
 * It configures the SPI peripheral DMA controller (PDC) to transmit data on the
 * SPI port, then returns.  freertos_spi_write_packet_async() does not wait for
 * the transmission to complete before returning.
 *
 * The FreeRTOS SPI driver is initialized using a call to
 * freertos_spi_master_init().  The freertos_driver_parameters.options_flags
 * parameter passed into the initialization function defines the driver behavior.
 * freertos_spi_write_packet_async() can only be used if the
 * freertos_driver_parameters.options_flags parameter passed to the initialization
 * function had the WAIT_TX_COMPLETE bit clear.
 *
 * freertos_spi_write_packet_async() is an advanced function and readers are
 * recommended to also reference the application note and examples that
 * accompany the FreeRTOS ASF drivers.  freertos_spi_write_packet() is a version
 * that does not exit until the PDC transfer is complete, but still allows other
 * RTOS tasks to execute while the transmission is in progress.
 *
 * The FreeRTOS ASF driver both installs and handles the SPI PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * \param p_spi    The handle to the SPI peripheral returned by the
 *     freertos_spi_master_init() call used to initialise the peripheral.
 * \param data    A pointer to the data to be transmitted.
 * \param len    The number of bytes to transmit.
 * \param block_time_ticks    The FreeRTOS ASF SPI driver is initialized using a
 *     call to freertos_spi_master_init().  The
 *     freertos_driver_parameters.options_flags parameter passed to the
 *     initialization function defines the driver behavior.  If
 *     freertos_driver_parameters.options_flags had the USE_TX_ACCESS_SEM bit
 *     set, then the driver will only write to the SPI peripheral if it has
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
 *     access to the SPI peripheral could be obtained.  STATUS_OK is returned if
 *     the PDC was successfully configured to perform the SPI write operation.
 */
status_code_t freertos_spi_write_packet_async(freertos_spi_if p_spi,
		const uint8_t *data, size_t len, portTickType block_time_ticks,
		xSemaphoreHandle notification_semaphore)
{
	status_code_t return_value;
	portBASE_TYPE spi_index;
	Spi *spi_base;

	spi_base = (Spi *) p_spi;
	spi_index = get_pdc_peripheral_details(all_spi_definitions, MAX_SPIS,
			(void *) spi_base);

	/* Don't do anything unless a valid SPI pointer was used. */
	if (spi_index < MAX_SPIS) {
		return_value = freertos_obtain_peripheral_access_semphore(
				&(tx_dma_control[spi_index]), &block_time_ticks);

		if (return_value == STATUS_OK) {
			freertos_start_pdc_tx(&(tx_dma_control[spi_index]),
					data, len,
					all_spi_definitions[spi_index].pdc_base_address,
					notification_semaphore);

			/* Catch the end of transmission so the access mutex can be
			returned, and the task notified (if it supplied a notification
			semaphore).  The interrupt can be enabled here because the ENDTX
			signal from the PDC to the peripheral will have been de-asserted when
			the next transfer was configured. */
			spi_enable_interrupt(spi_base, SPI_IER_ENDTX);

			return_value = freertos_optionally_wait_transfer_completion(
					&(tx_dma_control[spi_index]),
					notification_semaphore,
					block_time_ticks);
		}
	} else {
		return_value = ERR_INVALID_ARG;
	}

	return return_value;
}

/**
 * \ingroup freertos_spi_peripheral_control_group
 * \brief Initiate a completely asynchronous multi-byte read operation on an SPI
 * peripheral.
 *
 * freertos_spi_read_packet_async() is an ASF specific FreeRTOS driver function.
 * It configures the SPI peripheral DMA controller (PDC) to read data from the
 * SPI port, then returns.  freertos_spi_read_packet_async() does not wait for
 * the reception to complete before returning.
 *
 * The FreeRTOS ASF SPI driver is initialized using a call to
 * freertos_spi_master_init().  The freertos_driver_parameters.options_flags
 * parameter passed into the initialization function defines the driver behavior.
 * freertos_spi_read_packet_async() can only be used if the
 * freertos_driver_parameters.options_flags parameter passed to the initialization
 * function had the WAIT_RX_COMPLETE bit clear.
 *
 * freertos_spi_read_packet_async() is an advanced function and readers are
 * recommended to also reference the application note and examples that
 * accompany the FreeRTOS ASF drivers.  freertos_spi_read_packet() is a version
 * that does not exit until the PDC transfer is complete, but still allows other
 * RTOS tasks to execute while the transmission is in progress.
 *
 * The FreeRTOS ASF driver both installs and handles the SPI PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * \param p_spi    The handle to the SPI port returned by the
 *     freertos_spi_master_init() call used to initialise the port.
 * \param data    A pointer to the buffer into which received data is to be
 *     written.
 * \param len    The number of bytes to receive.
 * \param block_time_ticks    The FreeRTOS ASF SPI driver is initialized using a
 *     call to freertos_spi_master_init().  The
 *     freertos_driver_parameters.options_flags parameter passed to the
 *     initialization function defines the driver behavior.  If
 *     freertos_driver_parameters.options_flags had the USE_RX_ACCESS_MUTEX bit
 *     set, then the driver will only read from the SPI peripheral if it has
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
 *     access to the SPI peripheral could be obtained.  STATUS_OK is returned if
 *     the PDC was successfully configured to perform the SPI read operation.
 */
status_code_t freertos_spi_read_packet_async(freertos_spi_if p_spi,
		uint8_t *data, uint32_t len, portTickType block_time_ticks,
		xSemaphoreHandle notification_semaphore)
{
	status_code_t return_value;
	pdc_packet_t pdc_tx_packet;
	portBASE_TYPE spi_index;
	Spi *spi_base;
	volatile uint16_t junk_value;

	spi_base = (Spi *) p_spi;
	spi_index = get_pdc_peripheral_details(all_spi_definitions, MAX_SPIS,
			(void *) spi_base);

	/* Don't do anything unless a valid SPI pointer was used. */
	if (spi_index < MAX_SPIS) {
		/* Because the peripheral is half duplex, there is only one access mutex
		and the rx uses the tx mutex. */
		return_value = freertos_obtain_peripheral_access_semphore(
				&(tx_dma_control[spi_index]), &block_time_ticks);

		if (return_value == STATUS_OK) {
			/* Data must be sent for data to be received.  Set the receive
			buffer to all 0xffs so it can also be used as the send buffer. */
			memset((void *)data, 0xff, (size_t)len);

			/* Ensure Rx is already empty. */
			while(spi_is_rx_full(all_spi_definitions[spi_index].peripheral_base_address) != 0) {
				junk_value = ((Spi*) all_spi_definitions[spi_index].peripheral_base_address)->SPI_RDR;
				(void) junk_value;
			}

			/* Start the PDC reception, although nothing is received until the
			SPI is also transmitting. */
			freertos_start_pdc_rx(&(rx_dma_control[spi_index]),
					data, len,
					all_spi_definitions[spi_index].pdc_base_address,
					notification_semaphore);

			/* Start the transmit so data is also received. */
			pdc_tx_packet.ul_addr = (uint32_t)data;
			pdc_tx_packet.ul_size = (uint32_t)len;
			pdc_disable_transfer(
					all_spi_definitions[spi_index].pdc_base_address,
					PERIPH_PTCR_TXTDIS);
			pdc_tx_init(
					all_spi_definitions[spi_index].pdc_base_address, &pdc_tx_packet,
					NULL);
			pdc_enable_transfer(
					all_spi_definitions[spi_index].pdc_base_address,
					PERIPH_PTCR_TXTEN);

			/* Catch the end of reception so the access mutex can be returned,
			and the task notified (if it supplied a notification semaphore).
			The interrupt can be enabled here because the ENDRX	signal from the
			PDC to the peripheral will have been de-asserted when the next
			transfer was configured. */
			spi_enable_interrupt(spi_base, SPI_IER_ENDRX);

			return_value = freertos_optionally_wait_transfer_completion(
					&(rx_dma_control[spi_index]),
					notification_semaphore,
					block_time_ticks);
		}
	} else {
		return_value = ERR_INVALID_ARG;
	}

	return return_value;
}

/**
 * \ingroup freertos_spi_peripheral_control_group
 * \brief Initiate a completely asynchronous multi-byte full duplex operation on an SPI
 * peripheral.
 *
 * freertos_spi_full_duplex_packet_async() is an ASF specific FreeRTOS driver function.
 * It configures the SPI peripheral DMA controller (PDC) to read/write data from the
 * SPI port, then returns.  freertos_spi_full_duplex_packet_async() does not wait for
 * the reception and transmission to complete before returning.
 *
 * The FreeRTOS ASF SPI driver is initialized using a call to
 * freertos_spi_master_init().  The freertos_driver_parameters.options_flags
 * parameter passed into the initialization function defines the driver behavior.
 * freertos_spi_full_duplex_packet_async() can only be used if the
 * freertos_driver_parameters.options_flags parameter passed to the initialization
 * function had the WAIT_RX_COMPLETE and WAIT_TX_COMPLETE bit clear.
 *
 * freertos_spi_full_duplex_packet_async() is an advanced function and readers are
 * recommended to also reference the application note and examples that
 * accompany the FreeRTOS ASF drivers.
 *
 * The FreeRTOS ASF driver both installs and handles the SPI PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * \param p_spi    The handle to the SPI port returned by the
 *     freertos_spi_master_init() call used to initialise the port.
 * \param rx_data    A pointer to the buffer into which received data is to be
 *     written.
 * \param tx_data    A pointer to the data to be transmitted.
 * \param len    The number of bytes to receive/transmit.
 * \param block_time_ticks    The FreeRTOS ASF SPI driver is initialized using a
 *     call to freertos_spi_master_init().  The
 *     freertos_driver_parameters.options_flags parameter passed to the
 *     initialization function defines the driver behavior.  If
 *     freertos_driver_parameters.options_flags had the USE_RX_ACCESS_MUTEX bit
 *     set, then the driver will only read from the SPI peripheral if it has
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
 *     access to the SPI peripheral could be obtained.  STATUS_OK is returned if
 *     the PDC was successfully configured to perform the SPI read operation.
 */
status_code_t freertos_spi_full_duplex_packet_async(freertos_spi_if p_spi,
		uint8_t *rx_data, uint8_t *tx_data, uint32_t len,
		portTickType block_time_ticks, xSemaphoreHandle notification_semaphore)
{
	status_code_t return_value;
	pdc_packet_t pdc_tx_packet;
	portBASE_TYPE spi_index;
	Spi *spi_base;
	volatile uint16_t junk_value;

	spi_base = (Spi *) p_spi;
	spi_index = get_pdc_peripheral_details(all_spi_definitions, MAX_SPIS,
			(void *) spi_base);

	/* Don't do anything unless a valid SPI pointer was used. */
	if (spi_index < MAX_SPIS) {
		/* Because the peripheral is half duplex, there is only one access mutex
		and the rx uses the tx mutex. */
		return_value = freertos_obtain_peripheral_access_semphore(
				&(tx_dma_control[spi_index]), &block_time_ticks);

		if (return_value == STATUS_OK) {
			/* Data must be sent for data to be received.  Set the receive
			buffer with write buffer content since it also be used as the send buffer. */
			memcpy(rx_data, tx_data, len);

			/* Ensure Rx is already empty. */
			while(spi_is_rx_full(all_spi_definitions[spi_index].peripheral_base_address) != 0) {
				junk_value = ((Spi*) all_spi_definitions[spi_index].peripheral_base_address)->SPI_RDR;
				(void) junk_value;
			}

			/* Start the PDC reception, although nothing is received until the
			SPI is also transmitting. */
			freertos_start_pdc_rx(&(rx_dma_control[spi_index]),
					rx_data, len,
					all_spi_definitions[spi_index].pdc_base_address,
					notification_semaphore);

			/* Start the transmit so data is also received. */
			pdc_tx_packet.ul_addr = (uint32_t)rx_data;
			pdc_tx_packet.ul_size = (uint32_t)len;
			pdc_disable_transfer(
					all_spi_definitions[spi_index].pdc_base_address,
					PERIPH_PTCR_TXTDIS);
			pdc_tx_init(
					all_spi_definitions[spi_index].pdc_base_address, &pdc_tx_packet,
					NULL);
			pdc_enable_transfer(
					all_spi_definitions[spi_index].pdc_base_address,
					PERIPH_PTCR_TXTEN);

			/* Catch the end of reception so the access mutex can be returned,
			and the task notified (if it supplied a notification semaphore).
			The interrupt can be enabled here because the ENDRX	signal from the
			PDC to the peripheral will have been de-asserted when the next
			transfer was configured. */
			spi_enable_interrupt(spi_base, SPI_IER_ENDRX);

			return_value = freertos_optionally_wait_transfer_completion(
					&(rx_dma_control[spi_index]),
					notification_semaphore,
					block_time_ticks);
		}
	} else {
		return_value = ERR_INVALID_ARG;
	}

	return return_value;
}

/*
 * For internal use only.
 * A common SPI interrupt handler that is called for all SPI peripherals.
 */
static void local_spi_handler(const portBASE_TYPE spi_index)
{
	portBASE_TYPE higher_priority_task_woken = pdFALSE;
	uint32_t spi_status;
	Spi *spi_port;

	spi_port = all_spi_definitions[spi_index].peripheral_base_address;

	spi_status = spi_read_status(spi_port);
	spi_status &= spi_read_interrupt_mask(spi_port);

	/* Has the PDC completed a transmission? */
	if ((spi_status & SPI_SR_ENDTX) != 0UL) {
		spi_disable_interrupt(spi_port, SPI_IDR_ENDTX);

		/* If the driver is supporting multi-threading, then return the access
		mutex. */
		if (tx_dma_control[spi_index].peripheral_access_sem != NULL) {
			xSemaphoreGiveFromISR(
					tx_dma_control[spi_index].peripheral_access_sem,
					&higher_priority_task_woken);
		}

		/* if the sending task supplied a notification semaphore, then
		 * notify the task that the transmission has completed. */
		if (tx_dma_control[spi_index].transaction_complete_notification_semaphore != NULL) {
			xSemaphoreGiveFromISR(
					tx_dma_control[spi_index].transaction_complete_notification_semaphore,
					&higher_priority_task_woken);
		}
	}

	/* Has the PDC completed a reception? */
	if ((spi_status & SPI_SR_ENDRX) != 0UL) {
		spi_disable_interrupt(spi_port, SPI_IDR_ENDRX);

		/* If the driver is supporting multi-threading, then return the access
		mutex.  NOTE: As a reception is performed by first performing a
		transmission, the SPI receive function uses the tx access semaphore. */
		if (tx_dma_control[spi_index].peripheral_access_sem != NULL) {
			xSemaphoreGiveFromISR(
					tx_dma_control[spi_index].peripheral_access_sem,
					&higher_priority_task_woken);
		}

		/* If the receiving task supplied a notification semaphore, then
		notify the task that the transmission has completed. */
		if (rx_dma_control[spi_index].transaction_complete_notification_semaphore != NULL) {
			xSemaphoreGiveFromISR(
					rx_dma_control[spi_index].transaction_complete_notification_semaphore,
					&higher_priority_task_woken);
		}
	}

	if ((spi_status & SR_ERROR_INTERRUPTS) != 0) {
		/* An mode error occurred in either a transmission or reception.  Abort.
		Stop the transmission, disable interrupts used by the peripheral, and
		ensure the peripheral access mutex is made available to tasks.  As this
		peripheral is half duplex, only the Tx peripheral access mutex exits. */
		spi_disable_interrupt(spi_port, SPI_IDR_ENDTX);
		spi_disable_interrupt(spi_port, SPI_IDR_ENDRX);

		if (tx_dma_control[spi_index].peripheral_access_sem != NULL) {
			xSemaphoreGiveFromISR(
					tx_dma_control[spi_index].peripheral_access_sem,
					&higher_priority_task_woken);
		}

		/* The SPI port will have been disabled, re-enable it. */
		spi_enable(spi_port);
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
#ifdef CONF_FREERTOS_USE_SPI0
void FLEXCOM0_Handler(void)
{
	local_spi_handler(0);
}
#endif
#ifdef CONF_FREERTOS_USE_SPI1
void FLEXCOM1_Handler(void)
{
	local_spi_handler(1);
}
#endif
#ifdef CONF_FREERTOS_USE_SPI2
void FLEXCOM2_Handler(void)
{
	local_spi_handler(2);
}
#endif
#ifdef CONF_FREERTOS_USE_SPI3
void FLEXCOM3_Handler(void)
{
	local_spi_handler(3);
}
#endif
#ifdef CONF_FREERTOS_USE_SPI4
void FLEXCOM4_Handler(void)
{
	local_spi_handler(4);
}
#endif
#ifdef CONF_FREERTOS_USE_SPI5
void FLEXCOM5_Handler(void)
{
	local_spi_handler(5);
}
#endif
#ifdef CONF_FREERTOS_USE_SPI6
void FLEXCOM6_Handler(void)
{
	local_spi_handler(6);
}
#endif
#ifdef CONF_FREERTOS_USE_SPI7
void FLEXCOM7_Handler(void)
{
	local_spi_handler(7);
}
#endif

#else
#ifdef SPI

void SPI_Handler(void)
{
	local_spi_handler(0);
}

#endif /* SPI */

#ifdef SPI0

void SPI0_Handler(void)
{
	local_spi_handler(0);
}

#endif /* SPI0 */

#ifdef SPI1

void SPI1_Handler(void)
{
	local_spi_handler(1);
}

#endif /* SPI1 */

#ifdef SPI2

void SPI2_Handler(void)
{
	local_spi_handler(2);
}

#endif /* SPI2 */

#ifdef SPI3

void SPI3_Handler(void)
{
	local_spi_handler(3);
}

#endif /* SPI3 */

#ifdef SPI4

void SPI4_Handler(void)
{
	local_spi_handler(4);
}

#endif /* SPI4 */

#endif
