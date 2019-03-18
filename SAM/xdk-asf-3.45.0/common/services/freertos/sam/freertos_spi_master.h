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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef FREERTOS_SPI_MASTER_INCLUDED
#define FREERTOS_SPI_MASTER_INCLUDED

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* ASF includes. */
#include "spi_master.h"
#include "freertos_peripheral_control.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

#if XMEGA
# error Unsupported chip type
#elif UC3
# error Unsupported chip type
#elif SAM
	/* SAM is supported. */
#else
# error Unsupported chip type
#endif

/**
 * \defgroup freertos_spi_peripheral_control_group FreeRTOS SPI peripheral
 * control
 * \brief FreeRTOS peripheral control functions for the SPI peripheral
 * \ingroup freertos_service_group
 */

/**
 * \ingroup freertos_spi_peripheral_control_group
 * \typedef freertos_spi_if
 * \brief Type returned from a call to freertos_spi_master_init(), and then used
 * to reference an SPI port in calls to FreeRTOS peripheral control functions.
 */
typedef void *freertos_spi_if;

freertos_spi_if freertos_spi_master_init(Spi *p_spi,
		const freertos_peripheral_options_t *const freertos_driver_parameters);

status_code_t freertos_spi_write_packet_async(freertos_spi_if p_spi,
		const uint8_t *data, size_t len, portTickType block_time_ticks,
		xSemaphoreHandle notification_semaphore);

status_code_t freertos_spi_read_packet_async(freertos_spi_if p_spi,
		uint8_t *data, uint32_t len, portTickType block_time_ticks,
		xSemaphoreHandle notification_semaphore);

status_code_t freertos_spi_full_duplex_packet_async(freertos_spi_if p_spi,
		uint8_t *rx_data, uint8_t *tx_data, uint32_t len,
		portTickType block_time_ticks, xSemaphoreHandle notification_semaphore);

/**
 * \ingroup freertos_spi_peripheral_control_group
 * \brief Initiate a multi-byte write operation on an SPI peripheral.
 *
 * freertos_spi_write_packet() is an ASF specific FreeRTOS driver function.  It
 * configures the SPI peripheral DMA controller (PDC) to transmit data on the
 * SPI port, then waits until the transmission is complete.  Other RTOS tasks
 * execute while the transmission is in progress.
 *
 * freertos_spi_write_packet_async() is a version that does not wait for the
 * transmission to complete before returning.
 *
 * The FreeRTOS ASF SPI driver is initialized using a call to
 * freertos_spi_master_init().  The freertos_driver_parameters.options_flags
 * parameter passed into the initialization function defines the driver
 * behavior.
 * freertos_spi_write_packet() can only be used if the
 * freertos_driver_parameters.options_flags parameter passed to the
 * initialization function had the WAIT_TX_COMPLETE bit set.
 *
 * Readers are recommended to also reference the application note and examples
 * that accompany the FreeRTOS ASF drivers.
 *
 * The FreeRTOS ASF driver both installs and handles the SPI PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * \param p_spi    The handle to the SPI port returned by the
 *     freertos_spi_master_init() call used to initialise the port.
 * \param data    A pointer to the data to be transmitted.
 * \param len    The number of bytes to transmit.
 * \param block_time_ticks    The FreeRTOS ASF SPI driver is initialized using a
 *     call to freertos_spi_master_init().  The
 *     freertos_driver_parameters.options_flags parameter passed to the
 *     initialization function defines the driver behavior.  If
 *     freertos_driver_parameters.options_flags had the USE_TX_ACCESS_SEM bit
 *     set, then the driver will only write to the SPI peripheral if it has
 *     first gained exclusive access to it.  block_time_ticks specifies the
 *     maximum amount of time the driver will wait to get exclusive access before
 *     aborting the write operation.  Other tasks will execute during any
 *     waiting time.  block_time_ticks is specified in RTOS tick periods.  To
 *     specify a block time in milliseconds, divide the milliseconds value by
 *     portTICK_RATE_MS, and pass the result in block_time_ticks.
 *     portTICK_RATE_MS is defined by FreeRTOS.
 *
 * \return     ERR_INVALID_ARG is returned if an input parameter is invalid.
 *     ERR_TIMEOUT is returned if block_time_ticks passed before exclusive access
 *     to the SPI peripheral could be obtained.  STATUS_OK is returned if the
 *     PDC was successfully configured to perform the SPI write operation.
 */
#define freertos_spi_write_packet(p_spi, data, len, block_time_ticks) freertos_spi_write_packet_async((p_spi), (data), (len), (block_time_ticks), (NULL))

/**
 * \brief Initiate a multi-byte read operation on an SPI peripheral.
 *
 * freertos_spi_read_packet() is an ASF specific FreeRTOS driver function.  It
 * configures the SPI peripheral DMA controller (PDC) to read data from the
 * SPI port, then waits until the requested number of bytes have been received.
 * Other RTOS tasks execute while the DMA transfer is in progress.
 *
 * freertos_spi_read_packet_async() is a version that does not wait for the
 * reception to complete before returning.
 *
 * The FreeRTOS ASF SPI driver is initialized using a call to
 * freertos_spi_master_init().  The freertos_driver_parameters.options_flags
 * parameter passed into the initialization function defines the driver behavior.
 * freertos_spi_read_packet() can only be used if the
 * freertos_driver_parameters.options_flags parameter passed to the initialization
 * function had the WAIT_RX_COMPLETE bit set.
 *
 * Readers are recommended to also reference the application note and examples
 * that accompany the FreeRTOS ASF drivers.
 *
 * The FreeRTOS ASF driver both installs and handles the SPI PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * \param p_spi    The handle to the SPI port returned by the
 *     freertos_spi_master_init() call used to initialise the port.
 * \param data    A pointer to the buffer into which received data is to be written.
 * \param len    The number of bytes to receive.
 * \param block_time_ticks    The FreeRTOS ASF SPI driver is initialized using a
 *     call to freertos_spi_master_init().  The
 *     freertos_driver_parameters.options_flags parameter passed to the
 *     initialization function defines the driver behavior.  If
 *     freertos_driver_parameters.options_flags had the
 *     USE_RX_ACCESS_MUTEX bit set, then the driver will only read from the SPI
 *     peripheral if it has first gained exclusive access to it.  block_time_ticks
 *     specifies the maximum amount of time the driver will wait to get
 *     exclusive access before aborting the read operation.  Other tasks will
 *     execute during any waiting time.  block_time_ticks is specified in RTOS
 *     tick periods.  To specify a block time in milliseconds, divide the
 *     milliseconds value by portTICK_RATE_MS, and pass the result in
 *     block_time_ticks.  portTICK_RATE_MS is defined by FreeRTOS.
 *
 * \return     ERR_INVALID_ARG is returned if an input parameter is invalid.
 *     ERR_TIMEOUT is returned if block_time_ticks passed before exclusive access
 *     to the SPI peripheral could be obtained.  STATUS_OK is returned if the
 *     PDC was successfully configured to perform the SPI read operation.
 */
#define freertos_spi_read_packet(p_spi, data, len, block_time_ticks) freertos_spi_read_packet_async((p_spi), (data), (len), (block_time_ticks), (NULL))


/**
 * \page freertos_spi_peripheral_control_quick_start Quick start guide for
 * FreeRTOS SPI peripheral control functions
 *
 * This is the quick start guide for the
 * \ref freertos_spi_peripheral_control_group, with
 * step-by-step instructions on how to configure and use the service.
 *
 * The service can be initialized to operate in one of two different modes -
 * standard mode, and fully asynchronous mode.
 *
 * freertos_spi_write_packet() is used to transmit data in standard mode.
 * freertos_spi_write_packet() does not return until all the data has been
 * fully transmitted.  Other FreeRTOS tasks will execute while the data
 * transmission is in progress.
 *
 * freertos_spi_read_packet() is used to receive data in standard mode.
 * freertos_spi_read_packet() does not return until all the requested data has
 * been received.  This is safe because, in master mode, the amount of data
 * being received is controlled by the receiving device, and therefore known in
 * advance.  Other FreeRTOS tasks will execute while the data is being received.
 *
 * freertos_spi_write_packet_async() is used to transmit data in the fully
 * asynchronous mode.  freertos_spi_write_packet_async() returns as soon as
 * the data transmission has started (not when it has finished), and can opt to
 * be notified by FreeRTOS when the transmission is complete.  The buffer being
 * transmitted must not be altered until the transmission is complete.
 *
 * freertos_spi_write_packet_async() and freertos_spi_read_packet_async() must
 * not be used when the peripheral is initialized to use standard mode.
 * Likewise, freertos_spi_write_packet() and freertos_spi_read_packet()
 * must not be used when the peripheral is configured to use fully asynchronous
 * mode.
 *
 * Refer to the FreeRTOS peripheral control projects in the Atmel ASF
 * distribution for complete working examples, and the
 * <a href="http://www.FreeRTOS.org" target="_blank">FreeRTOS web site</a> for
 * information on getting started with FreeRTOS.
 *
 * \section freertos_spi_sync_use_case Standard Mode Functions
 * - \subpage freertos_spi_initialization_sync
 * - \subpage freertos_spi_tx_sync
 * - \subpage freertos_spi_rx_sync
 *
 * \section freertos_spi_async_use_case Fully Asynchronous Mode Functions
 * - \subpage freertos_spi_initialization_async
 * - \subpage freertos_spi_tx_async
 * - \subpage freertos_spi_rx_async
 */

/**
 * \page freertos_spi_initialization_sync Initializing the FreeRTOS SPI driver
 * for standard operation
 *
 * This example configures the FreeRTOS SPI driver to:
 * - Support simultaneous access from multiple RTOS tasks.
 * - Wait in the FreeRTOS transmit function until all the data has been
 * completely sent
 * - Wait in the FreeRTOS receive function until all the requested data has been
 * received
 *
 * Other FreeRTOS tasks will execute during any wait periods.
 *
 * If the driver is initialized with this configuration then only the
 * freertos_spi_write_packet() and freertos_spi_read_packet() API functions can
 * be used to transmit and receive data respectively.
 * freertos_spi_write_packet_async() and freertos_spi_read_packet_async() must
 * not be used.
 *
 * Refer to the FreeRTOS peripheral control projects in the Atmel ASF
 * distribution for complete working examples, and the
 * <a href="http://www.FreeRTOS.org" target="_blank">FreeRTOS web site</a> for
 * information on getting started with FreeRTOS.
 *
 *
 * \code

	 /////////////////////////////////////////////////////////////////////////////
	 // Declare the variables used as parameters to the
	 // freertos_spi_master_init() function.

	 // Handle used to access the initialized port by other FreeRTOS ASF functions.
	 freertos_spi_if freertos_spi;

	 // Configuration structure.
	 freertos_peripheral_options_t driver_options = {

	     // This peripheral is synchronous and so does not need a receive buffer.
	     // The receive_buffer value is just set to NULL.
	     NULL,

	     // There isn't a receive buffer, so the receive_buffer_size value can
	     // take any value.
	     0,

	     // The interrupt priority.  The FreeRTOS driver provides the interrupt
	     // service routine, and handles all interrupt interactions.  The
	     // application writer does not need to provide any interrupt handling
	     // code, but does need to specify the priority of the DMA interrupt here.
	     // IMPORTANT!!!  see <a href="http://www.freertos.org/RTOS-Cortex-M3-M4.html">how to set interrupt priorities to work with FreeRTOS</a>
	     0x0e,

	     // The operation_mode value.
	     SPI_MASTER,

	     // Flags set to allow access from multiple tasks, wait in the transmit
	     // function until the transmit is complete, and wait in the receive
	     // function until reception is complete.  Note that other FreeRTOS tasks
	     // will execute during the wait period.
	     (USE_TX_ACCESS_SEM | USE_RX_ACCESS_MUTEX | WAIT_TX_COMPLETE | WAIT_RX_COMPLETE)
	  };

	  /////////////////////////////////////////////////////////////////////////////
	  // Call the SPI specific FreeRTOS ASF driver initialization function,
	  // storing the return value as the driver handle.
	  freertos_spi = freertos_spi_master_init(spi_base, &driver_options);

	  if (freertos_spi != NULL) {
	      // Calling freertos_spi_master_init() will enable the peripheral clock,
	      // and set the SPI into master mode.  Other ASF configuration functions,
	      // such as spi_set_clock_polarity(), and spi_set_baudrate_div() can then
	      // be called here.
	  }
\endcode
 */

/**
 * \page freertos_spi_initialization_async Initializing the FreeRTOS SPI driver
 * for asynchronous operation
 *
 * This example configures the FreeRTOS SPI driver to:
 * - Support simultaneous access from multiple RTOS tasks.
 * - Exit the FreeRTOS transmit function as soon as the transmission is started.
 * - Exit the receive function as soon as the receive has been requested.
 *
 * If the driver is initialized with this configuration then only the
 * freertos_spi_write_packet_async() and freertos_spi_read_packet_async() API
 * functions can be used to transmit and receive data respectively.
 * freertos_spi_write_packet() and freertos_spi_read_packet() must not be used.
 *
 * Refer to the FreeRTOS peripheral control projects in the Atmel ASF
 * distribution for complete working examples, and the
 * <a href="http://www.FreeRTOS.org" target="_blank">FreeRTOS web site</a> for
 * information on getting started with FreeRTOS.
 *
 *
 * \code

	 /////////////////////////////////////////////////////////////////////////////
	 // Declare the variables used as parameters to the
	 // freertos_spi_master_init() function.

	 // Handle used to access the initialized port by other FreeRTOS ASF functions.
	 freertos_spi_if freertos_spi;

	 // Configuration structure.
	 freertos_peripheral_options_t driver_options = {

	     // This peripheral is synchronous and so does not need a receive buffer.
	     // The receive_buffer value is just set to NULL.
	     NULL,

	     // There isn't a receive buffer, so the receive_buffer_size value can
	     // take any value.
	     0,

	     // The interrupt priority.  The FreeRTOS driver provides the interrupt
	     // service routine, and handles all interrupt interactions.  The
	     // application writer does not need to provide any interrupt handling
	     // code, but does need to specify the priority of the DMA interrupt here.
	     // IMPORTANT!!!  see <a href="http://www.freertos.org/RTOS-Cortex-M3-M4.html">how to set interrupt priorities to work with FreeRTOS</a>
	     0x0e,

	     // The operation_mode value.
	     SPI_MASTER,

	     // Flags set to allow access from multiple tasks.  Note the
	     // WAIT_TX_COMPLETE and WAIT_RX_COMPLETE bits are *not* set.
	     (USE_TX_ACCESS_SEM | USE_RX_ACCESS_MUTEX)
	  };

	 /////////////////////////////////////////////////////////////////////////////
	 // Call the SPI specific FreeRTOS ASF driver initialization function,
	 // storing the return value as the driver handle.
	  freertos_spi = freertos_spi_master_init(spi_base, &driver_options);

	  if (freertos_spi != NULL) {
	      // Calling freertos_spi_master_init() will enable the peripheral clock,
	      // and set the SPI into master mode.  Other ASF configuration functions,
	      // such as spi_set_clock_polarity(), and spi_set_baudrate_div() can then
	      // be called here.
	  }
\endcode
 */

/**
 * \page freertos_spi_tx_sync Transmitting using the FreeRTOS SPI driver in
 * standard mode
 *
 * This example demonstrates using the FreeRTOS SPI driver to send data using
 * the standard operation mode.  See \ref freertos_spi_initialization_sync
 *
 * The example below implements a function that simply writes a block of data to
 * an SPI port.
 *
 * Refer to the FreeRTOS peripheral control projects in the Atmel ASF
 * distribution for complete working examples, and the
 * <a href="http://www.FreeRTOS.org" target="_blank">FreeRTOS web site</a> for
 * information on getting started with FreeRTOS.
 *
 * \code

	 // Write number_of_bytes from data_buffer to freertos_spi.
	 //
	 // This examples assumes freertos_spi has already been set by a successful
	 // call to freertos_spi_master_init(), and that freertos_spi_master_init()
	 // configured the FreeRTOS SPI driver to use the standard operation mode.

	  static void write_to_eeprom(freertos_spi_if freertos_spi,
	                      uint8_t data_buffer size_t number_of_bytes)
	  {
	  const portTickType max_block_time_ticks = 200UL / portTICK_RATE_MS;

	      // Attempt to write number_of_bytes from data_buffer to the port
	      // referenced by the freertos_spi handle.  Wait a maximum of 200ms to
	      // get exclusive access to the port (other FreeRTOS tasks will execute
	      // during any waiting time).
	      if(freertos_spi_write_packet(freertos_spi, data_buffer,
	                      number_of_bytes, max_block_time_ticks) != STATUS_OK)
	      {
	          // The data was not written successfully, either because there was
	          // an error on the SPI bus, or because exclusive access to the SPI
	          // port was not obtained within 200ms.
	      }
	  }
\endcode
 */

/**
 * \page freertos_spi_tx_async Transmitting using the FreeRTOS SPI driver in
 * fully asynchronous mode
 *
 * This example demonstrates using the FreeRTOS SPI driver to send data using
 * the fully asynchronous operation mode.  See \ref
 * freertos_spi_initialization_async
 *
 * The example below implements a function that simply writes a block of data to
 * an SPI port.
 *
 * Refer to the FreeRTOS peripheral control projects in the Atmel ASF
 * distribution for complete working examples, and the
 * <a href="http://www.FreeRTOS.org" target="_blank">FreeRTOS web site</a> for
 * information on getting started with FreeRTOS.
 *
 * \code

	 // Write number_of_bytes from data_buffer to freertos_spi.
	 //
	 // This examples assumes freertos_spi has already been set by a successful
	 // call to freertos_spi_master_init(), and that freertos_spi_master_init()
	 // configured the FreeRTOS SPI driver to use the fully asynchronous operation
	 // mode.
	 //
	 // The example further assumes that notification_semaphore has already been
	 // initialised by a call to the vSemaphoreCreateBinary() FreeRTOS API
	 // function.

	  static void write_to_eeprom(freertos_spi_if freertos_spi,
	                      uint8_t data_buffer size_t number_of_bytes,
	                      xSemaphoreHandle notification_semaphore)
	  {
	  const portTickType max_block_time_ticks = 200UL / portTICK_RATE_MS;

	      // Attempt to initiate a DMA transfer of number_of_bytes bytes from
	      // data_buffer to the port referenced by the freertos_spi handle.  Wait
	      // a maximum of 200ms to get exclusive access to the port (other
	      //  FreeRTOS tasks will execute during any waiting time).
	      if(freertos_spi_write_packet_async(freertos_spi, data_buffer,
	                                  number_of_bytes, max_block_time_ticks,
	                                  notification_semaphore) != STATUS_OK)
	      {
	          // The DMA transfer was not started because exclusive access to the
	          // port was not obtained within 200ms.
	      }
	      else
	      {
	          // The DMA transfer was started successfully, but has not
	          // necessarily completed yet.  Other processing can be performed
	          // here, but THE DATA IN data_buffer MUST NOT BE ALTERED UNTIL THE
	          // TRANSMISSION HAS COMPLETED.

	          // ...

	          // Ensure the transaction is complete before proceeding further by
	          // waiting for the notification_semaphore.  Don't wait longer than
	          // 200ms.  Other FreeRTOS tasks will execute during any waiting
	          // time.
	          if(xSemaphoreTake(notification_semaphore,
	                                            max_block_time_ticks) != pdPASS)
	          {
	              // The semaphore could not be obtained within 200ms.  Either the
	              // data is still being transmitted, or an error occurred.
	          }
	      }
	  }
\endcode
 */

/**
 * \page freertos_spi_rx_sync Receiving using the FreeRTOS SPI driver in
 * standard mode
 *
 * This example demonstrates using the FreeRTOS SPI driver to receive data using
 * the standard operation mode.  See \ref freertos_spi_initialization_sync
 *
 * The example below implements a function that simply reads a block of data
 * from an SPI port on each iteration of a loop.
 *
 * Refer to the FreeRTOS peripheral control projects in the Atmel ASF
 * distribution for complete working examples, and the
 * <a href="http://www.FreeRTOS.org" target="_blank">FreeRTOS web site</a> for
 * information on getting started with FreeRTOS.
 *
 * \code

	 // This examples assumes freertos_spi has already been set by a successful
	 // call to freertos_spi_master_init(), and that freertos_spi_master_init()
	 // configured the FreeRTOS SPI driver to use the standard operation mode.

	  void a_function(freertos_spi_if freertos_spi)
	  {
	  // The receive buffer is declared static to ensure it does not overflow the
	  // task stack.
	  static uint8_t receive_buffer[50];
	  const max_block_time_50ms = 50 / portTICK_RATE_MS;

	      // Loop around, reading and then processing 20 bytes from freertos_spi
	      // on each iteration.
	      for(;;)
	      {
	          // Receive 20 bytes from freertos_spi into receive_buffer.  Don't
	          // wait any longer than 50ms to get exclusive access to the port
	          // (other FreeRTOS tasks will execute during any wait time).
	          if(freertos_spi_read_packet(freertos_spi, receive_buffer, 20,
	                                          max_block_time_50ms) == STATUS_OK)
	{
	              // freertos_spi_read_packet() does not return until all the
	              // requested bytes have been received, so it is known that the
	              // data in receive_buffer is already complete, and can be
	              // processed immediately.

	              // ... Process received data here ...
	              do_something(receive_buffer);
	          }
	          else
	          {
	              // Either an error occurred on the bus or exclusive access
	              // to the port was not obtained within 50ms.
	          }
	      }
	  }
\endcode
 */

/**
 * \page freertos_spi_rx_async Receiving using the FreeRTOS SPI driver in fully
 * asynchronous mode
 *
 * This example demonstrates using the FreeRTOS SPI driver to receive data using
 * the fully asynchronous operation mode.  See \ref
 * freertos_spi_initialization_sync
 *
 * The example below implements a function that continuously processes
 * previously received data while more data is being received.
 *
 * This is a comprehensive quick start example and is intended for advanced
 * users.  It demonstrates the power and efficiency of the fully asynchronous
 * API.
 *
 * Refer to the FreeRTOS peripheral control projects in the Atmel ASF
 * distribution for complete working examples, and the
 * <a href="http://www.FreeRTOS.org" target="_blank">FreeRTOS web site</a> for
 * information on getting started with FreeRTOS.
 *
 * \code

	 // This examples assumes freertos_spi has already been set by a successful
	 // call to freertos_spi_master_init(), and that freertos_spi_master_init()
	 // configured the FreeRTOS SPI driver to use the fully asynchronous operation
	 // mode.

	 // This example demonstrates how a single task can process data while
	 // additional data is being received on the SPI bus.  Error checking is
	 // omitted to simplify the example.
	  void a_function(freertos_spi_if freertos_spi)
	  {
	  // The buffers into which the data is placed are too large to be declared on
	  // the task stack, so are instead declared static (making this function
	  // non-reentrant meaning it can only be called by a single task at a time,
	  // otherwise multiple tasks would use the same buffers).
	  static uint8_t first_receive_buffer[BUFFER_SIZE], second_receive_buffer[BUFFER_SIZE];
	  xSemaphoreHandle first_notification_semaphore = NULL, second_notification_semaphore = NULL;
	  const max_block_time_500ms = 500 / portTICK_RATE_MS;

	      // Create the notification semaphores, one per buffer.
	      // vSemaphoreCreateBinary() is a FreeRTOS API function.
	      vSemaphoreCreateBinary(first_notification_semaphore);
	      vSemaphoreCreateBinary(second_notification_semaphore);

	      // Nothing has been read over the SPI bus yet, so make sure both
	      // semaphores are empty.
	      xSemaphoreTake(first_notification_semaphore, 0);
	      xSemaphoreTake(second_notification_semaphore, 0);

	      // Start an asynchronous read to fill the first buffer.  The function
	      // will be able to access the port immediately because nothing else has
	      // accessed it yet - allowing the block_time_ticks value to be set to 0.
	      freertos_spi_read_packet_async(freertos_spi, first_receive_buffer,
	                      BUFFER_SIZE, 0, first_notification_semaphore);

	      for(;;)
	      {
	          // Wait until the first buffer is full.  Other tasks will run during
	          // the wait.  FreeRTOS will give first_notification_semaphore when
	          // the receive is complete.
	          xSemaphoreTake(first_notification_semaphore, max_block_time_500ms);

	          // Start an asynchronous read to fill the second buffer.  Again
	          // block_time_ticks is set to zero as it is known that the read
	          // operation that was filling the first buffer has completed -
	          // leaving the SPI port available.
	          freertos_spi_read_packet_async(freertos_spi, second_receive_buffer,
	                          BUFFER_SIZE, 0,    second_notification_semaphore);

	          // Process the data in the first receive buffer while the second
	          // receive buffer is being refreshed.
	          process_received_data(first_receive_buffer);

	          // Wait until the second buffer is full.  Other tasks will run
	          // during the wait.  FreeRTOS will give second_notification_semaphore
	          // when the receive is complete.
	          xSemaphoreTake(second_notification_semaphore, max_block_time_500ms);

	          // Start an asynchronous read to fill the first buffer again.
	          freertos_spi_read_packet_async(freertos_spi, second_receive_buffer,
	                          BUFFER_SIZE, 0,    second_notification_semaphore);

	          // Process the data in the second receive buffer while the first
	          // receive buffer is being refreshed.
	          process_received_data(second_receive_buffer);
	      }
	  }
\endcode
 */

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

 #endif /* FREERTOS_SPI_MASTER_INCLUDED */
