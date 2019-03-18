/**
 * \file
 *
 * \brief FreeRTOS Peripheral Control API For the TWI
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
#include "twi_master.h"
#include "freertos_twi_master.h"
#include "freertos_peripheral_control_private.h"
#if SAMG55
#include "flexcom.h"
#endif

/* Every bit in the interrupt mask. */
#define MASK_ALL_INTERRUPTS     (0xffffffffUL)
/* TWI timeout counter */
#define TWI_TIMEOUT_COUNTER    (0xffffffffUL)

/* Interrupts that are enabled to catch error conditions on the bus. */
#define SR_ERROR_INTERRUPTS     (TWI_SR_NACK | TWI_SR_ARBLST | TWI_SR_OVRE)
#define IER_ERROR_INTERRUPTS    (TWI_IER_NACK | TWI_IER_ARBLST | TWI_IER_OVRE)

/* Work out how many TWI ports with PDC supported are present. */
#if (SAMG55)
#if defined(PDC_TWI7)
	#define MAX_TWIS                                (8)
#elif defined(PDC_TWI6)
	#define MAX_TWIS                                (7)
#elif defined(PDC_TWI5)
	#define MAX_TWIS                                (6)
#elif defined(PDC_TWI4)
	#define MAX_TWIS                                (5)
#elif defined(PDC_TWI3)
	#define MAX_TWIS                                (4)
#elif defined(PDC_TWI2)
	#define MAX_TWIS                                (3)
#elif defined(PDC_TWI1)
	#define MAX_TWIS                                (2)
#elif defined(PDC_TWI0)
	#define MAX_TWIS                                (1)
#else
	#error No TWI peripherals with PDC support defined
#endif

#else
#if (SAMG)
#if defined(PDC_TWI4)
	#define MAX_TWIS                                (4)
#elif defined(PDC_TWI3)
	#define MAX_TWIS                                (3)
#elif defined(PDC_TWI2)
	#define MAX_TWIS                                (2)
#elif defined(PDC_TWI1)
	#define MAX_TWIS                                (1)
#else
	#error No TWI peripherals with PDC support defined
#endif
#else
#if defined(PDC_TWI4)
	#define MAX_TWIS                                (5)
#elif defined(PDC_TWI3)
	#define MAX_TWIS                                (4)
#elif defined(PDC_TWI2)
	#define MAX_TWIS                                (3)
#elif defined(PDC_TWI1)
	#define MAX_TWIS                                (2)
#elif defined(PDC_TWI0)
	#define MAX_TWIS                                (1)
#elif defined(PDC_TWI)
	#define MAX_TWIS                                (1)
#else
	#error No TWI peripherals with PDC support defined
#endif
#endif
#endif

/* A common interrupt handler definition used by all the TWI peripherals. */
static void local_twi_handler(const portBASE_TYPE twi_index);

/* Structures to manage the DMA control for both Rx and Tx transactions. */
static freertos_dma_event_control_t tx_dma_control[MAX_TWIS];
static freertos_dma_event_control_t rx_dma_control[MAX_TWIS];

/* Structure to manage the end of a read transaction */
struct twi_module {
	uint8_t *buffer;
	uint32_t length;
};

/* Structures to manage the DMA control for both Rx and Tx transactions. */
static struct twi_module twis[MAX_TWIS];

/* Used to detect the init function being called after any part of the DMA
control structure has already been initialized - indicating an error
condition as init should only be called once per port. */
static const freertos_dma_event_control_t null_dma_control = {NULL, NULL};

/* Create an array that holds the information required about each defined TWI
 * peripheral. */
static const freertos_pdc_peripheral_parameters_t all_twi_definitions[MAX_TWIS] = {
	/* Chips with a single TWI port might define TWI only.  Chips with multiple
	TWI	ports defined the first TWI peripheral as TWI0. */
#if SAMG55
	{TWI0, PDC_TWI0, ID_FLEXCOM0, FLEXCOM0_IRQn},
	{TWI1, PDC_TWI1, ID_FLEXCOM1, FLEXCOM1_IRQn},
	{TWI2, PDC_TWI2, ID_FLEXCOM2, FLEXCOM2_IRQn},
	{TWI3, PDC_TWI3, ID_FLEXCOM3, FLEXCOM3_IRQn},
	{TWI4, PDC_TWI4, ID_FLEXCOM4, FLEXCOM4_IRQn},
	{TWI5, PDC_TWI5, ID_FLEXCOM5, FLEXCOM5_IRQn},
	{TWI6, PDC_TWI6, ID_FLEXCOM6, FLEXCOM6_IRQn},
#if (MAX_TWIS > 7)
	{TWI7, PDC_TWI7, ID_FLEXCOM7, FLEXCOM7_IRQn},
#endif

#else
#if (SAMG)
#if MAX_TWIS > 0
	{TWI1, PDC_TWI1, ID_TWI1, TWI1_IRQn},
#endif
#if MAX_TWIS > 1
	{TWI2, PDC_TWI2, ID_TWI2, TWI2_IRQn},
#endif
#if MAX_TWIS > 2
	{TWI3, PDC_TWI3, ID_TWI3, TWI3_IRQn},
#endif
#if MAX_TWIS > 3
	{TWI4, PDC_TWI4, ID_TWI4, TWI4_IRQn},
#endif

#else
#if defined(TWI)
	{TWI, PDC_TWI, ID_TWI, TWI_IRQn},
#else
	{TWI0, PDC_TWI0, ID_TWI0, TWI0_IRQn},
#endif

#if MAX_TWIS > 1
	{TWI1, PDC_TWI1, ID_TWI1, TWI1_IRQn},
#endif
#if MAX_TWIS > 2
	{TWI2, PDC_TWI2, ID_TWI2, TWI2_IRQn},
#endif
#if MAX_TWIS > 3
	{TWI3, PDC_TWI3, ID_TWI3, TWI3_IRQn},
#endif
#if MAX_TWIS > 4
	{TWI4, PDC_TWI4, ID_TWI4, TWI4_IRQn},
#endif
#endif
#endif
};

/**
 * \ingroup freertos_twi_peripheral_control_group
 * \brief Initializes the FreeRTOS ASF TWI (I2C) master driver for the specified
 * TWI port.
 *
 * freertos_twi_master_init() is an ASF specific FreeRTOS driver function.  It
 * must be called before any other ASF specific FreeRTOS driver functions
 * attempt to access the same TWI port.
 *
 * If freertos_driver_parameters->operation_mode equals TWI_I2C_MASTER then
 * freertos_twi_master_init() will configure the TWI port for master mode
 * operation and enable the peripheral.  If
 * freertos_driver_parameters->operation_mode equals any other value then
 * freertos_twi_master_init() will not take any action.
 *
 * Other ASF TWI functions can be called after freertos_twi_master_init() has
 * completed successfully.
 *
 * The FreeRTOS ASF driver both installs and handles the TWI PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * This driver is provided with an application note, and an example project that
 * demonstrates the use of this function.
 *
 * \param p_twi    The twi peripheral being initialized.
 * \param freertos_driver_parameters    Defines the driver behavior.  See the
 *    freertos_peripheral_options_t documentation, and the application note that
 *    accompanies the ASF specific FreeRTOS functions.
 *
 * \return If the initialization completes successfully then a handle that can
 *     be used with FreeRTOS TWI read and write functions is returned.  If
 *     the initialisation fails then NULL is returned.
 */
freertos_twi_if freertos_twi_master_init(Twi *p_twi,
		const freertos_peripheral_options_t *const freertos_driver_parameters)
{
	portBASE_TYPE twi_index;
	bool is_valid_operating_mode;
	freertos_twi_if return_value;
	const enum peripheral_operation_mode valid_operating_modes[] = {TWI_I2C_MASTER};

	/* Find the index into the all_twi_definitions array that holds details of
	the p_twi peripheral. */
	twi_index = get_pdc_peripheral_details(all_twi_definitions, MAX_TWIS,
			(void *) p_twi);

	/* Check the requested operating mode is valid for the peripheral. */
	is_valid_operating_mode = check_requested_operating_mode(
			freertos_driver_parameters->operation_mode,
			valid_operating_modes,
			sizeof(valid_operating_modes) /
			sizeof(enum peripheral_operation_mode));

	/* Don't do anything unless a valid p_twi pointer was used, and a valid
	operating mode was requested. */
	if ((twi_index < MAX_TWIS) && (is_valid_operating_mode == true)) {
		/* This function must be called exactly once per supported twi.  Check
		it has not been called	before. */
		configASSERT(memcmp((void *)&(tx_dma_control[twi_index]),
				&null_dma_control,
				sizeof(null_dma_control)) == 0);
		configASSERT(memcmp((void *)&(rx_dma_control[twi_index]),
				&null_dma_control,
				sizeof(null_dma_control)) == 0);

		/* Enable the peripheral's clock. */
#if (SAMG55)
		/* Enable the peripheral and set TWI mode. */
		uint32_t temp = (uint32_t)(all_twi_definitions[twi_index].peripheral_base_address - 0x600);
		Flexcom *p_flexcom = (Flexcom *)temp;
		flexcom_enable(p_flexcom);
		flexcom_set_opmode(p_flexcom, FLEXCOM_TWI);
#else
		pmc_enable_periph_clk(
				all_twi_definitions[twi_index].peripheral_id);
#endif
		/* Ensure everything is disabled before configuration. */
		pdc_disable_transfer(
				all_twi_definitions[twi_index].pdc_base_address,
				(PERIPH_PTCR_RXTDIS | PERIPH_PTCR_TXTDIS));
		twi_disable_interrupt(
				all_twi_definitions[twi_index].peripheral_base_address,
				MASK_ALL_INTERRUPTS);
		twi_reset(
				all_twi_definitions[twi_index].peripheral_base_address);

		switch (freertos_driver_parameters->operation_mode) {
		case TWI_I2C_MASTER:
			/* Call the standard ASF init function. */
			twi_enable_master_mode(
					all_twi_definitions[twi_index].peripheral_base_address);
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
				&(tx_dma_control[twi_index]),
				&(rx_dma_control[twi_index]));

		/* Error interrupts are always enabled. */
		twi_enable_interrupt(
				all_twi_definitions[twi_index].peripheral_base_address,
				IER_ERROR_INTERRUPTS);

		/* Configure and enable the TWI interrupt in the interrupt controller. */
		configure_interrupt_controller(
				all_twi_definitions[twi_index].peripheral_irq,
				freertos_driver_parameters->interrupt_priority);

		return_value = (freertos_twi_if) p_twi;
	} else {
		return_value = NULL;
	}

	return return_value;
}

/**
 * \ingroup freertos_twi_peripheral_control_group
 * \brief Initiate a completely asynchronous multi-byte write operation on a TWI
 * peripheral.
 *
 * freertos_twi_write_packet_async() is an ASF specific FreeRTOS driver function.
 * It configures the TWI peripheral DMA controller (PDC) to transmit data on the
 * TWI port, then returns.  freertos_twi_write_packet_async() does not wait for
 * the transmission to complete before returning.
 *
 * The FreeRTOS TWI driver is initialized using a call to
 * freertos_twi_master_init().  The freertos_driver_parameters.options_flags
 * parameter passed into the initialization function defines the driver behavior.
 * freertos_twi_write_packet_async() can only be used if the
 * freertos_driver_parameters.options_flags parameter passed to the initialization
 * function had the WAIT_TX_COMPLETE bit clear. It can also only be used if packet
 * length is more than 1.
 *
 * freertos_twi_write_packet_async() is an advanced function and readers are
 * recommended to also reference the application note and examples that
 * accompany the FreeRTOS ASF drivers.  freertos_twi_write_packet() is a version
 * that does not exit until the PDC transfer is complete, but still allows other
 * RTOS tasks to execute while the transmission is in progress.
 *
 * The FreeRTOS ASF driver both installs and handles the TWI PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * \param p_twi    The handle to the TWI peripheral returned by the
 *     freertos_twi_master_init() call used to initialise the peripheral.
 * \param p_packet    Structure that defines the TWI transfer parameters, such
 *     as the I2C chip being addressed, the source data location, and the number
 *     of bytes to transmit.  twi_packet_t is a standard ASF type (it is not
 *     FreeRTOS specific).
 * \param block_time_ticks    The FreeRTOS ASF TWI driver is initialized using a
 *     call to freertos_twi_master_init().  The
 *     freertos_driver_parameters.options_flags parameter passed to the
 *     initialization function defines the driver behavior.  If
 *     freertos_driver_parameters.options_flags had the USE_TX_ACCESS_SEM bit
 *     set, then the driver will only write to the TWI peripheral if it has
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
 *     access to the TWI peripheral could be obtained.  STATUS_OK is returned if
 *     the PDC was successfully configured to perform the TWI write operation.
 */
status_code_t freertos_twi_write_packet_async(freertos_twi_if p_twi,
		twi_packet_t *p_packet, portTickType block_time_ticks,
		xSemaphoreHandle notification_semaphore)
{
	status_code_t return_value;
	portBASE_TYPE twi_index;
	Twi *twi_base;
	uint32_t internal_address = 0;

	twi_base = (Twi *) p_twi;
	twi_index = get_pdc_peripheral_details(all_twi_definitions, MAX_TWIS,
			(void *) twi_base);

	/* Don't do anything unless a valid TWI pointer was used. */
	if ((twi_index < MAX_TWIS) && (p_packet->length > 0)) {
		return_value = freertos_obtain_peripheral_access_semphore(
				&(tx_dma_control[twi_index]), &block_time_ticks);

		if (return_value == STATUS_OK) {
			/* Set write mode and slave address. */
			twi_base->TWI_MMR = 0;
			twi_base->TWI_MMR = TWI_MMR_DADR(p_packet->chip) |
					((p_packet->addr_length <<
					TWI_MMR_IADRSZ_Pos) &
					TWI_MMR_IADRSZ_Msk);

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
			twi_base->TWI_IADR = internal_address;

			if (p_packet->length == 1) {
				uint32_t status;
				uint32_t timeout_counter = 0;
				/* Do not handle errors for short packets in interrupt handler */
				twi_disable_interrupt(
						all_twi_definitions[twi_index].peripheral_base_address,
						IER_ERROR_INTERRUPTS);
				/* Send start condition */
				twi_base->TWI_THR = *((uint8_t*)(p_packet->buffer));
				while (1) {
					status = twi_base->TWI_SR;
					if (status & TWI_SR_NACK) {
						/* Re-enable interrupts */
						twi_enable_interrupt(
								all_twi_definitions[twi_index].peripheral_base_address,
								IER_ERROR_INTERRUPTS);
						/* Release semaphore */
						xSemaphoreGive(tx_dma_control[twi_index].peripheral_access_sem);
						return ERR_BUSY;
					}
					if (status & TWI_SR_TXRDY) {
						break;
					}
					/* Check timeout condition. */
					if (++timeout_counter >= TWI_TIMEOUT_COUNTER) {
						return_value = ERR_TIMEOUT;
						break;
					}
				}
				twi_base->TWI_CR = TWI_CR_STOP;
				/* Wait for TX complete */
				while (!(twi_base->TWI_SR & TWI_SR_TXCOMP)) {
					/* Check timeout condition. */
					if (++timeout_counter >= TWI_TIMEOUT_COUNTER) {
						return_value = ERR_TIMEOUT;
						break;
					}
				}

				/* Re-enable interrupts */
				twi_enable_interrupt(
						all_twi_definitions[twi_index].peripheral_base_address,
						IER_ERROR_INTERRUPTS);
				/* Release semaphores */
				xSemaphoreGive(tx_dma_control[twi_index].peripheral_access_sem);
			} else {

				twis[twi_index].buffer = p_packet->buffer;
				twis[twi_index].length = p_packet->length;

				freertos_start_pdc_tx(&(tx_dma_control[twi_index]),
						p_packet->buffer, p_packet->length - 1,
						all_twi_definitions[twi_index].pdc_base_address,
						notification_semaphore);

				/* Catch the end of transmission so the access mutex can be
				returned, and the task notified (if it supplied a notification
				semaphore).  The interrupt can be enabled here because the ENDTX
				signal from the PDC to the peripheral will have been de-asserted when
				the next transfer was configured. */
				twi_enable_interrupt(twi_base, TWI_IER_ENDTX);

				return_value = freertos_optionally_wait_transfer_completion(
						&(tx_dma_control[twi_index]),
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
 * \ingroup freertos_twi_peripheral_control_group
 * \brief Initiate a completely asynchronous multi-byte read operation on an TWI
 * peripheral.
 *
 * freertos_twi_read_packet_async() is an ASF specific FreeRTOS driver function.
 * It configures the TWI peripheral DMA controller (PDC) to read data from the
 * TWI port, then returns.  freertos_twi_read_packet_async() does not wait for
 * the reception to complete before returning.
 *
 * The FreeRTOS ASF TWI driver is initialized using a call to
 * freertos_twi_master_init().  The freertos_driver_parameters.options_flags
 * parameter passed into the initialization function defines the driver behavior.
 * freertos_twi_read_packet_async() can only be used if the
 * freertos_driver_parameters.options_flags parameter passed to the initialization
 * function had the WAIT_RX_COMPLETE bit clear. The function can also only be used
 * if the length of the packet is more that two. If less, it will block until the
 * transfer is done.
 *
 * freertos_twi_read_packet_async() is an advanced function and readers are
 * recommended to also reference the application note and examples that
 * accompany the FreeRTOS ASF drivers.  freertos_twi_read_packet() is a version
 * that does not exit until the PDC transfer is complete, but still allows other
 * RTOS tasks to execute while the transmission is in progress.
 *
 * The FreeRTOS ASF driver both installs and handles the TWI PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * \param p_twi    The handle to the TWI port returned by the
 *     freertos_twi_master_init() call used to initialise the port.
 * \param p_packet    Structure that defines the TWI transfer parameters, such
 *     as the I2C chip being addressed, the destination for the data being read,
 *     and the number of bytes to read.  twi_packet_t is a standard ASF type (it
 *     is not FreeRTOS specific).
 * \param block_time_ticks    The FreeRTOS ASF TWI driver is initialized using a
 *     call to freertos_twi_master_init().  The
 *     freertos_driver_parameters.options_flags parameter passed to the
 *     initialization function defines the driver behavior.  If
 *     freertos_driver_parameters.options_flags had the USE_RX_ACCESS_MUTEX bit
 *     set, then the driver will only read from the TWI peripheral if it has
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
 *     access to the TWI peripheral could be obtained.  STATUS_OK is returned if
 *     the PDC was successfully configured to perform the TWI read operation.
 */
status_code_t freertos_twi_read_packet_async(freertos_twi_if p_twi,
		twi_packet_t *p_packet, portTickType block_time_ticks,
		xSemaphoreHandle notification_semaphore)
{
	status_code_t return_value;
	portBASE_TYPE twi_index;
	Twi *twi_base;
	uint32_t internal_address = 0;

	twi_base = (Twi *) p_twi;
	twi_index = get_pdc_peripheral_details(all_twi_definitions, MAX_TWIS,
			(void *) twi_base);

	/* Don't do anything unless a valid TWI pointer was used. */
	if ((twi_index < MAX_TWIS) && (p_packet->length > 0)) {
		/* Because the peripheral is half duplex, there is only one access mutex
		and the rx uses the tx mutex. */
		return_value = freertos_obtain_peripheral_access_semphore(
				&(tx_dma_control[twi_index]), &block_time_ticks);

		if (return_value == STATUS_OK) {
			/* Ensure Rx is already empty. */
			twi_read_byte(twi_base);

			/* Set read mode and slave address. */
			twi_base->TWI_MMR = 0;
			twi_base->TWI_MMR = TWI_MMR_MREAD | TWI_MMR_DADR(
					p_packet->chip) |
					((p_packet->addr_length <<
					TWI_MMR_IADRSZ_Pos) &
					TWI_MMR_IADRSZ_Msk);

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
			twi_base->TWI_IADR = internal_address;

			if (p_packet->length <= 2) {
				/* Do not handle errors for short packets in interrupt handler */
				twi_disable_interrupt(
						all_twi_definitions[twi_index].peripheral_base_address,
						IER_ERROR_INTERRUPTS);

				/* Cannot use PDC transfer, use normal transfer */
				uint8_t stop_sent = 0;
				uint32_t cnt = p_packet->length;
				uint32_t status;
				uint8_t *buffer = p_packet->buffer;
				uint32_t timeout_counter = 0;

				/* Start the transfer. */
				if (cnt == 1) {
					twi_base->TWI_CR = TWI_CR_START | TWI_CR_STOP;
					stop_sent = 1;
				} else {
					twi_base->TWI_CR = TWI_CR_START;
				}

				while (cnt > 0) {
					status = twi_base->TWI_SR;
					if (status & TWI_SR_NACK) {
						/* Re-enable interrupts */
						twi_enable_interrupt(
								all_twi_definitions[twi_index].peripheral_base_address,
								IER_ERROR_INTERRUPTS);
						/* Release semaphore */
						xSemaphoreGive(tx_dma_control[twi_index].peripheral_access_sem);
						return ERR_BUSY;
					}
					/* Last byte ? */
					if (cnt == 1 && !stop_sent) {
						twi_base->TWI_CR = TWI_CR_STOP;
						stop_sent = 1;
					}
					if (!(status & TWI_SR_RXRDY)) {
						if (++timeout_counter >= TWI_TIMEOUT_COUNTER) {
							return_value = ERR_TIMEOUT;
							break;
						}
						continue;
					}
					*buffer++ = twi_base->TWI_RHR;
					cnt--;
					timeout_counter = 0;
				}

				timeout_counter = 0;
				/* Wait for stop to be sent */
				while (!(twi_base->TWI_SR & TWI_SR_TXCOMP)) {
					/* Check timeout condition. */
					if (++timeout_counter >= TWI_TIMEOUT_COUNTER) {
						return_value = ERR_TIMEOUT;
						break;
					}
				}
				/* Re-enable interrupts */
				twi_enable_interrupt(
						all_twi_definitions[twi_index].peripheral_base_address,
						IER_ERROR_INTERRUPTS);
				/* Release semaphores */
				xSemaphoreGive(tx_dma_control[twi_index].peripheral_access_sem);
			} else {
				/* Start the PDC reception. */
				twis[twi_index].buffer = p_packet->buffer;
				twis[twi_index].length = p_packet->length;
				freertos_start_pdc_rx(&(rx_dma_control[twi_index]),
						p_packet->buffer, (p_packet->length)-2,
						all_twi_definitions[twi_index].pdc_base_address,
						notification_semaphore);

				/* Start the transfer. */
				twi_base->TWI_CR = TWI_CR_START;

				/* Catch the end of reception so the access mutex can be returned,
				and the task notified (if it supplied a notification semaphore).
				The interrupt can be enabled here because the ENDRX	signal from the
				PDC to the peripheral will have been de-asserted when the next
				transfer was configured. */
				twi_enable_interrupt(twi_base, TWI_IER_ENDRX);

				return_value = freertos_optionally_wait_transfer_completion(
						&(rx_dma_control[twi_index]),
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
 * A common TWI interrupt handler that is called for all TWI peripherals.
 */
static void local_twi_handler(const portBASE_TYPE twi_index)
{
	portBASE_TYPE higher_priority_task_woken = pdFALSE;
	uint32_t twi_status;
	Twi *twi_port;
	bool transfer_timeout = false;

	twi_port = all_twi_definitions[twi_index].peripheral_base_address;

	twi_status = twi_get_interrupt_status(twi_port);
	twi_status &= twi_get_interrupt_mask(twi_port);

	/* Has the PDC completed a transmission? */
	if ((twi_status & TWI_SR_ENDTX) != 0UL) {
		/* Disable PDC */
		pdc_disable_transfer(all_twi_definitions[twi_index].pdc_base_address, PERIPH_PTCR_TXTDIS);
		twi_disable_interrupt(twi_port, TWI_IDR_ENDTX);

		uint8_t status;
		uint32_t timeout_counter = 0;

		/* Wait for TX ready flag */
		while (1) {
			status = twi_port->TWI_SR;
			if (status & TWI_SR_TXRDY) {
				break;
			}
			/* Check timeout condition. */
			if (++timeout_counter >= TWI_TIMEOUT_COUNTER) {
				transfer_timeout = true;
				break;
			}
		}
		/* Complete the transfer - stop and last byte */
		twi_port->TWI_CR = TWI_CR_STOP;
		twi_port->TWI_THR = twis[twi_index].buffer[twis[twi_index].length-1];

		/* Wait for TX complete flag */
		while (1) {
			status = twi_port->TWI_SR;
			if (status & TWI_SR_TXCOMP) {
				break;
			}
			/* Check timeout condition. */
			if (++timeout_counter >= TWI_TIMEOUT_COUNTER) {
				transfer_timeout = true;
				break;
			}
		}
		/* If the driver is supporting multi-threading, then return the access
		mutex. */
		if (tx_dma_control[twi_index].peripheral_access_sem != NULL) {
			xSemaphoreGiveFromISR(
					tx_dma_control[twi_index].peripheral_access_sem,
					&higher_priority_task_woken);
		}

		/* if the sending task supplied a notification semaphore, then
		notify the task that the transmission has completed. */
		if (!(timeout_counter >= TWI_TIMEOUT_COUNTER)) {
			if (tx_dma_control[twi_index]. transaction_complete_notification_semaphore != NULL) {
				xSemaphoreGiveFromISR(
						tx_dma_control[twi_index].transaction_complete_notification_semaphore,
						&higher_priority_task_woken);
			}
		}
	}

	/* Has the PDC completed a reception? */
	if ((twi_status & TWI_SR_ENDRX) != 0UL) {
		uint32_t timeout_counter = 0;
		uint32_t status;
		/* Must handle the two last bytes */
		/* Disable PDC */
		pdc_disable_transfer(all_twi_definitions[twi_index].pdc_base_address, PERIPH_PTCR_RXTDIS);

		twi_disable_interrupt(twi_port, TWI_IDR_ENDRX);

		/* Wait for RX ready flag */
		while (1) {
			status = twi_port->TWI_SR;
			if (status & TWI_SR_RXRDY) {
				break;
			}
			/* Check timeout condition. */
			if (++timeout_counter >= TWI_TIMEOUT_COUNTER) {
				break;
			}
		}
		/* Complete the transfer. */
		twi_port->TWI_CR = TWI_CR_STOP;
		/* Read second last data */
		twis[twi_index].buffer[(twis[twi_index].length)-2] = twi_port->TWI_RHR;

		/* Wait for RX ready flag */
		while (1) {
			status = twi_port->TWI_SR;
			if (status & TWI_SR_RXRDY) {
				break;
			}
			/* Check timeout condition. */
			if (++timeout_counter >= TWI_TIMEOUT_COUNTER) {
				break;
			}
		}

		if (!(timeout_counter >= TWI_TIMEOUT_COUNTER)) {
			/* Read last data */
			twis[twi_index].buffer[(twis[twi_index].length)-1] = twi_port->TWI_RHR;
			timeout_counter = 0;
			/* Wait for TX complete flag before releasing semaphore */
			while (1) {
				status = twi_port->TWI_SR;
				if (status & TWI_SR_TXCOMP) {
					break;
				}
				/* Check timeout condition. */
				if (++timeout_counter >= TWI_TIMEOUT_COUNTER) {
					transfer_timeout = true;
					break;
				}
			}
		}

		/* If the driver is supporting multi-threading, then return the access
		mutex.  NOTE: As the peripheral is half duplex there is only one
		access mutex, and the reception uses the tx access muted. */
		if (tx_dma_control[twi_index].peripheral_access_sem != NULL) {
			xSemaphoreGiveFromISR(
					tx_dma_control[twi_index].peripheral_access_sem,
					&higher_priority_task_woken);
		}

		/* if the receiving task supplied a notification semaphore, then
		notify the task that the transmission has completed. */
		if  (!(timeout_counter >= TWI_TIMEOUT_COUNTER)) {
			if (rx_dma_control[twi_index].transaction_complete_notification_semaphore != NULL) {
				xSemaphoreGiveFromISR(
						rx_dma_control[twi_index].transaction_complete_notification_semaphore,
						&higher_priority_task_woken);
			}
		}
	}

	if (((twi_status & SR_ERROR_INTERRUPTS) != 0) || (transfer_timeout == true)) {
		/* An error occurred in either a transmission or reception.  Abort.
		Stop the transmission, disable interrupts used by the peripheral, and
		ensure the peripheral access mutex is made available to tasks.  As this
		peripheral is half duplex, only the Tx peripheral access mutex exits.*/

		/* Stop the PDC */
		pdc_disable_transfer(all_twi_definitions[twi_index].pdc_base_address, PERIPH_PTCR_TXTDIS | PERIPH_PTCR_RXTDIS);

		if (!(twi_status & TWI_SR_NACK)) {
			/* Do not send stop if NACK received. Handled by hardware */
			twi_port->TWI_CR = TWI_CR_STOP;
		}
		twi_disable_interrupt(twi_port, TWI_IDR_ENDTX);
		twi_disable_interrupt(twi_port, TWI_IDR_ENDRX);

		if (tx_dma_control[twi_index].peripheral_access_sem != NULL) {
			xSemaphoreGiveFromISR(
					tx_dma_control[twi_index].peripheral_access_sem,
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
#ifdef CONF_FREERTOS_USE_TWI0
void FLEXCOM0_Handler(void)
{
	local_twi_handler(0);
}
#endif
#ifdef CONF_FREERTOS_USE_TWI1
void FLEXCOM1_Handler(void)
{
	local_twi_handler(1);
}
#endif
#ifdef CONF_FREERTOS_USE_TWI2
void FLEXCOM2_Handler(void)
{
	local_twi_handler(2);
}
#endif
#ifdef CONF_FREERTOS_USE_TWI3
void FLEXCOM3_Handler(void)
{
	local_twi_handler(3);
}
#endif
#ifdef CONF_FREERTOS_USE_TWI4
void FLEXCOM4_Handler(void)
{
	local_twi_handler(4);
}
#endif
#ifdef CONF_FREERTOS_USE_TWI5
void FLEXCOM5_Handler(void)
{
	local_twi_handler(5);
}
#endif
#ifdef CONF_FREERTOS_USE_TWI6
void FLEXCOM6_Handler(void)
{
	local_twi_handler(6);
}
#endif
#ifdef CONF_FREERTOS_USE_TWI7
void FLEXCOM7_Handler(void)
{
	local_twi_handler(7);
}
#endif

#else
#if (!SAMG)
#ifdef TWI

void TWI_Handler(void)
{
	local_twi_handler(0);
}

#endif /* TWI */

#ifdef TWI0

void TWI0_Handler(void)
{
	local_twi_handler(0);
}

#endif /* TWI0 */
#endif

#ifdef TWI1

void TWI1_Handler(void)
{
	local_twi_handler(1);
}

#endif /* TWI1 */

#ifdef TWI2

void TWI2_Handler(void)
{
	local_twi_handler(2);
}

#endif /* TWI2 */

#ifdef TWI3

void TWI3_Handler(void)
{
	local_twi_handler(3);
}

#endif /* TWI3 */

#ifdef TWI4

void TWI4_Handler(void)
{
	local_twi_handler(4);
}

#endif /* TWI4 */
#endif
