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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef FREERTOS_TWI_MASTER_INCLUDED
#define FREERTOS_TWI_MASTER_INCLUDED

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* ASF includes. */
#include "twi_master.h"
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
 * \defgroup freertos_twi_peripheral_control_group FreeRTOS TWI peripheral
 * control
 * \brief FreeRTOS peripheral control functions for the TWI peripheral
 * \ingroup freertos_service_group
 */

/**
 * \ingroup freertos_twi_peripheral_control_group
 * \typedef freertos_twi_if
 * \brief Type returned from a call to freertos_twi_master_init(), and then used
 * to reference a TWI port in calls to FreeRTOS peripheral control functions.
 */
typedef void *freertos_twi_if;

freertos_twi_if freertos_twi_master_init(Twi *p_twi,
		const freertos_peripheral_options_t *const freertos_driver_parameters);

status_code_t freertos_twi_write_packet_async(freertos_twi_if p_twi,
		twi_packet_t *p_packet, portTickType block_time_ticks,
		xSemaphoreHandle notification_semaphore);

status_code_t freertos_twi_read_packet_async(freertos_twi_if p_twi,
		twi_packet_t *p_packet, portTickType block_time_ticks,
		xSemaphoreHandle notification_semaphore);

/**
 * \ingroup freertos_twi_peripheral_control_group
 * \brief Initiate a multi-byte write operation on an TWI peripheral.
 *
 * freertos_twi_write_packet() is an ASF specific FreeRTOS driver function.  It
 * configures the TWI peripheral DMA controller (PDC) to transmit data on the
 * TWI port, then waits until the transmission is complete.  Other RTOS tasks
 * execute while the transmission is in progress.
 *
 * freertos_twi_write_packet_async() is a version that does not wait for the
 * transmission to complete before returning.
 *
 * The FreeRTOS ASF TWI driver is initialized using a call to
 * freertos_twi_master_init().  The freertos_driver_parameters.options_flags
 * parameter passed into the initialization function defines the driver behavior.
 * freertos_twi_write_packet() can only be used if the
 * freertos_driver_parameters.options_flags parameter passed to the initialization
 * function had the WAIT_TX_COMPLETE bit set.
 *
 * Readers are recommended to also reference the application note and examples
 * that accompany the FreeRTOS ASF drivers.
 *
 * The FreeRTOS ASF driver both installs and handles the TWI PDC interrupts.
 * Users do not need to concern themselves with interrupt handling, and must
 * not install their own interrupt handler.
 *
 * \param p_twi    The handle to the TWI port returned by the
 *     freertos_twi_master_init() call used to initialise the port.
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
 *     maximum amount of time the driver will wait to get exclusive access before
 *     aborting the write operation.  Other tasks will execute during any
 *     waiting time.  block_time_ticks is specified in RTOS tick periods.  To
 *     specify a block time in milliseconds, divide the milliseconds value by
 *     portTICK_RATE_MS, and pass the result in block_time_ticks.
 *     portTICK_RATE_MS is defined by FreeRTOS.
 *
 * \return     ERR_INVALID_ARG is returned if an input parameter is invalid.
 *     ERR_TIMEOUT is returned if block_time_ticks passed before exclusive access
 *     to the TWI peripheral could be obtained.  STATUS_OK is returned if the
 *     PDC was successfully configured to perform the TWI write operation.
 */
#define freertos_twi_write_packet(p_twi, p_packet, block_time_ticks) freertos_twi_write_packet_async((p_twi), (p_packet), (block_time_ticks), (NULL))

/**
 * \brief Initiate a multi-byte read operation on an TWI peripheral.
 *
 * freertos_twi_read_packet() is an ASF specific FreeRTOS driver function.  It
 * configures the TWI peripheral DMA controller (PDC) to read data from the
 * TWI port, then waits until the requested number of bytes have been received.
 * Other RTOS tasks execute while the DMA transfer is in progress.
 *
 * freertos_twi_read_packet_async() is a version that does not wait for the
 * reception to complete before returning.
 *
 * The FreeRTOS ASF TWI driver is initialized using a call to
 * freertos_twi_master_init().  The freertos_driver_parameters.options_flags
 * parameter passed into the initialization function defines the driver behavior.
 * freertos_twi_read_packet() can only be used if the
 * freertos_driver_parameters.options_flags parameter passed to the initialization
 * function had the WAIT_RX_COMPLETE bit set.
 *
 * Readers are recommended to also reference the application note and examples
 * that accompany the FreeRTOS ASF drivers.
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
 *     freertos_driver_parameters.options_flags had the
 *     USE_RX_ACCESS_MUTEX bit set, then the driver will only read from the TWI
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
 *     to the TWI peripheral could be obtained.  STATUS_OK is returned if the
 *     PDC was successfully configured to perform the TWI read operation.
 */
#define freertos_twi_read_packet(p_twi, p_packet, block_time_ticks) freertos_twi_read_packet_async((p_twi), (p_packet), (block_time_ticks), (NULL))

/**
 * \page freertos_twi_peripheral_control_quick_start Quick start guide for
 * FreeRTOS TWI peripheral control functions
 *
 * This is the quick start guide for the
 * \ref freertos_twi_peripheral_control_group, with
 * step-by-step instructions on how to configure and use the service.
 *
 * The service can be initialized to operate in one of two different modes -
 * standard mode, and fully asynchronous mode.
 *
 * freertos_twi_write_packet() is used to transmit data in standard mode.
 * freertos_twi_write_packet() does not return until all the data has been
 * fully transmitted.  Other FreeRTOS tasks will execute while the data
 * transmission is in progress.
 *
 * freertos_twi_read_packet() is used to receive data in standard mode.
 * freertos_twi_read_packet() does not return until all the requested data has
 * been received.  This is safe because, in master mode, the amount of data
 * being received is controlled by the receiving device, and therefore known in
 * advance.  Other FreeRTOS tasks will execute while the data is being received.
 *
 * freertos_twi_write_packet_async() is used to transmit data in the fully
 * asynchronous mode.  freertos_twi_write_packet_async() returns as soon as
 * the data transmission has started (not when it has finished), and can opt to
 * be notified by FreeRTOS when the transmission is complete.  The buffer being
 * transmitted must not be altered until the transmission is complete.
 *
 * freertos_twi_write_packet_async() and freertos_twi_read_packet_async() must
 * not be used when the peripheral is initialized to use standard mode.
 * Likewise, freertos_twi_write_packet() and freertos_twi_read_packet()
 * must not be used when the peripheral is configured to use fully asynchronous
 * mode.
 *
 * Refer to the FreeRTOS peripheral control projects in the Atmel ASF
 * distribution for complete working examples, and the
 * <a href="http://www.FreeRTOS.org" target="_blank">FreeRTOS web site</a> for
 * information on getting started with FreeRTOS.
 *
 * \section freertos_twi_sync_use_case Standard Mode Functions
 * - \subpage freertos_twi_initialization_sync
 * - \subpage freertos_twi_tx_sync
 * - \subpage freertos_twi_rx_sync
 *
 * \section freertos_twi_async_use_case Fully Asynchronous Mode Functions
 * - \subpage freertos_twi_initialization_async
 * - \subpage freertos_twi_tx_async
 * - \subpage freertos_twi_rx_async
 */

/**
 * \page freertos_twi_initialization_sync Initializing the FreeRTOS TWI driver
 * for standard operation
 *
 * This example configures the FreeRTOS TWI driver to:
 * - Support simultaneous access from multiple RTOS tasks.
 * - Wait in the FreeRTOS transmit function until all the data has been
 * completely sent
 * - Wait in the FreeRTOS receive function until all the requested data has been
 * received
 *
 * Other FreeRTOS tasks will execute during any wait periods.
 *
 * If the driver is initialized with this configuration then only the
 * freertos_twi_write_packet() and freertos_twi_read_packet() API functions can
 * be used to transmit and receive data respectively.
 * freertos_twi_write_packet_async() and freertos_twi_read_packet_async() must
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
	 // freertos_twi_master_init() function.

	 // Handle used to access the initialized port by other FreeRTOS ASF functions.
	 freertos_twi_if freertos_twi;

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
	     TWI_I2C_MASTER,

	     // Flags set to allow access from multiple tasks, wait in the transmit
	     // function until the transmit is complete, and wait in the receive
	     // function until reception is complete.  Note that other FreeRTOS tasks
	     // will execute during the wait period.
	     (USE_TX_ACCESS_SEM | USE_RX_ACCESS_MUTEX | WAIT_TX_COMPLETE | WAIT_RX_COMPLETE)
	  };

	  /////////////////////////////////////////////////////////////////////////////
	  // Call the TWI specific FreeRTOS ASF driver initialization function,
	  // storing the return value as the driver handle.
	  freertos_twi = freertos_twi_master_init(twi_base, &driver_options);

	  if (freertos_twi != NULL) {
	     // Calling freertos_twi_master_init() will enable the peripheral
	     // clock, and set the TWI into I2C master mode.  Other ASF
	     // configuration functions, such as twi_set_speed(), can then be
	     // called here.
	  }

\endcode
 */

/**
 * \page freertos_twi_initialization_async Initializing the FreeRTOS TWI driver
 * for asynchronous operation
 *
 * This example configures the FreeRTOS TWI driver to:
 * - Support simultaneous access from multiple RTOS tasks.
 * - Exit the FreeRTOS transmit function as soon as the transmission is started.
 * - Exit the receive function as soon as the receive has been requested.
 *
 * If the driver is initialized with this configuration then only the
 * freertos_twi_write_packet_async() and freertos_twi_read_packet_async() API
 * functions can be used to transmit and receive data respectively.
 * freertos_twi_write_packet() and freertos_twi_read_packet() must not be used.
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
	 // freertos_twi_master_init() function.

	 // Handle used to access the initialized port by other FreeRTOS ASF functions.
	 freertos_twi_if freertos_twi;

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
	     TWI_I2C_MASTER,

	     // Flags set to allow access from multiple tasks.  Note the
	     // WAIT_TX_COMPLETE and WAIT_RX_COMPLETE bits are *not* set.
	     (USE_TX_ACCESS_SEM | USE_RX_ACCESS_MUTEX)
	  };

	 /////////////////////////////////////////////////////////////////////////////
	 // Call the TWI specific FreeRTOS ASF driver initialization function,
	 // storing the return value as the driver handle.
	  freertos_twi = freertos_twi_master_init(twi_base, &driver_options);

	  if (freertos_twi != NULL) {
	     // Calling freertos_twi_master_init() will enable the peripheral
	     // clock, and set the TWI into I2C master mode.  Other ASF
	     // configuration functions, such as twi_set_speed(), can then be
	     // called here.
	  }

\endcode
 */

/**
 * \page freertos_twi_tx_sync Transmitting using the FreeRTOS TWI driver in
 * standard mode
 *
 * This example demonstrates using the FreeRTOS TWI driver to send data using
 * the standard operation mode.  See \ref freertos_twi_initialization_sync
 *
 * The example below implements a function that simply writes a block of data to
 * a TWI port.
 *
 * Refer to the FreeRTOS peripheral control projects in the Atmel ASF
 * distribution for complete working examples, and the
 * <a href="http://www.FreeRTOS.org" target="_blank">FreeRTOS web site</a> for
 * information on getting started with FreeRTOS.
 *
 * \code

	  // Write number_of_bytes from data_buffer to freertos_twi.
	  //
	  // This examples assumes freertos_twi has already been set by a successful
	  // call to freertos_twi_master_init(), and that freertos_twi_master_init()
	  // configured the FreeRTOS TWI driver to use the standard operation mode.

	  static void write_page_to_eeprom(freertos_twi_if freertos_twi, uint16_t page)
	  {
	  twi_packet_t write_parameters;
	  uint16_t calculated_address;
	  const portTickType max_block_time_ticks = 200UL / portTICK_RATE_MS;

	      // Calculate the address being written to
	      calculated_address = page * PAGE_SIZE;

	      // Configure the twi_packet_t structure to define the write operation
	      write_parameters.chip = BOARD_AT24C_ADDRESS;
	      write_parameters.buffer = data_buffer;
	      write_parameters.length = PAGE_SIZE;
	      write_parameters.addr[0] = (uint8_t) ((calculated_address >> 8) & 0xff);
	      write_parameters.addr[1] = (uint8_t) (calculated_address & 0xff);
	      write_parameters.addr_length = 2;

	      // Attempt to write the data to the port referenced by the freertos_twi
	      // handle.  Wait a maximum of 200ms to get exclusive access to the port
	      // (other FreeRTOS tasks will execute during any waiting time).
	      if(freertos_twi_write_packet(freertos_twi, &write_parameters, max_block_time_ticks) != STATUS_OK)
	      {
	          // The data was not written successfully, either because there was
	          // an error on the TWI bus, or because exclusive access to the TWI
	          // port was not obtained within 200ms.
	      }
	 }
\endcode
 */

/**
 * \page freertos_twi_tx_async Transmitting using the FreeRTOS TWI driver in
 * fully asynchronous mode
 *
 * This example demonstrates using the FreeRTOS TWI driver to send data using
 * the fully asynchronous operation mode.  See \ref
 * freertos_twi_initialization_async
 *
 * The example below implements a function that simply writes a block of data to
 * a TWI port.
 *
 * Refer to the FreeRTOS peripheral control projects in the Atmel ASF
 * distribution for complete working examples, and the
 * <a href="http://www.FreeRTOS.org" target="_blank">FreeRTOS web site</a> for
 * information on getting started with FreeRTOS.
 *
 * \code

	  // Write number_of_bytes from data_buffer to freertos_twi.
	  //
	  // This examples assumes freertos_twi has already been set by a successful
	  // call to freertos_twi_master_init(), and that freertos_twi_master_init()
	  // configured the FreeRTOS TWI driver to use the fully asynchronous operation
	  // mode.
	  //
	  // The example further assumes that notification_semaphore has already been
	  // initialised by a call to the vSemaphoreCreateBinary() FreeRTOS API
	  // function.

	  static void write_page_to_eeprom(freertos_twi_if freertos_twi,
	                      uint16_t page, xSemaphoreHandle notification_semaphore)
	  {
	  twi_packet_t write_parameters;
	  uint16_t calculated_address;
	  const portTickType max_block_time_ticks = 200UL / portTICK_RATE_MS;

	      // Calculate the address being written to
	      calculated_address = page * PAGE_SIZE;

	      // Configure the twi_packet_t structure to define the write operation
	      write_parameters.chip = BOARD_AT24C_ADDRESS;
	      write_parameters.buffer = data_buffer;
	      write_parameters.length = PAGE_SIZE;
	      write_parameters.addr[0] = (uint8_t) ((calculated_address >> 8) & 0xff);
	      write_parameters.addr[1] = (uint8_t) (calculated_address & 0xff);
	      write_parameters.addr_length = 2;

	      // Attempt to initiate a DMA transfer to write the data from data_buffer
	      // to the port referenced by the freertos_twi handle.  Wait a maximum of
	      // 200ms to get exclusive access to the port (other FreeRTOS tasks will
	      // execute during any waiting time).
	      if(freertos_twi_write_packet(freertos_twi, &write_parameters,
	                 max_block_time_ticks, notification_semaphore) != STATUS_OK)
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
 * \page freertos_twi_rx_sync Receiving using the FreeRTOS TWI driver in
 * standard mode
 *
 * This example demonstrates using the FreeRTOS TWI driver to receive data using
 * the standard operation mode.  See \ref freertos_twi_initialization_sync
 *
 * The example below implements a function that simply reads a block of data
 * from a TWI port.
 *
 * Refer to the FreeRTOS peripheral control projects in the Atmel ASF
 * distribution for complete working examples, and the
 * <a href="http://www.FreeRTOS.org" target="_blank">FreeRTOS web site</a> for
 * information on getting started with FreeRTOS.
 *
 * \code

	 // This examples assumes freertos_twi has already been set by a successful
	 // call to freertos_twi_master_init(), and that freertos_twi_master_init()
	 // configured the FreeRTOS TWI driver to use the standard operation mode.

	  static void read_page_from_eeprom(freertos_twi_if freertos_twi,
	                                     uint16_t page, uint8_t receive_buffer)
	  {
	  twi_packet_t read_parameters;
	  uint16_t calculated_address;
	  const portTickType max_block_time_ticks = 200UL / portTICK_RATE_MS;

	      // Calculate the address being read from.
	      calculated_address = page * PAGE_SIZE;

	      // Configure the read_parameters structure to define the read operation.
	      read_parameters.chip = BOARD_AT24C_ADDRESS;
	      read_parameters.buffer = receive_buffer;
	      read_parameters.length = PAGE_SIZE;
	      read_parameters.addr[0] = (uint8_t) ((calculated_address >> 8) & 0xff);
	      read_parameters.addr[1] = (uint8_t) (calculated_address & 0xff);
	      read_parameters.addr_length = 2;

	      // Receive the data into receive_buffer.  Don't wait any longer than 200ms
	      // to get exclusive access to the port (other FreeRTOS tasks will
	      // execute during any wait time.
	      if(freertos_twi_read_packet(freertos_twi, &read_parameters,
	                                      max_block_time_ticks) != STATUS_OK)
	      {
	          // Either an error occurred on the bus or exclusive access
	          // to the port was not obtained within 200ms.
	      }
	      else
	      {
	          // freertos_twi_read_packet() does not return until all the
	          // requested bytes have been received, so it is known that the
	          // data in receive_buffer is already complete, and can be
	          // processed immediately.

	          // ... Process received data here ...
	          do_something(receive_buffer);
	      }
	  }

\endcode
 */

/**
 * \page freertos_twi_rx_async Receiving using the FreeRTOS TWI driver in fully
 * asynchronous mode
 *
 * This example demonstrates using the FreeRTOS TWI driver to receive data using
 * the fully asynchronous operation mode.  See \ref
 * freertos_twi_initialization_sync
 *
 * The example below implements a function that receives a block of data, then
 * processes the received data while another bock is being received.
 *
 * Refer to the FreeRTOS peripheral control projects in the Atmel ASF
 * distribution for complete working examples, and the
 * <a href="http://www.FreeRTOS.org" target="_blank">FreeRTOS web site</a> for
 * information on getting started with FreeRTOS.
 *
 * \code

	 // This examples assumes freertos_twi has already been set by a successful
	 // call to freertos_twi_master_init(), and that freertos_twi_master_init()
	 // configured the FreeRTOS TWI driver to use the fully asynchronous operation
	 // mode.

	 // This example demonstrates how a single task can process data while
	 // additional data is being received on the TWI bus.  Error checking is
	 // omitted to simplify the example.
	  void a_function(freertos_twi_if freertos_twi)
	  {
	  // The buffers into which the data is placed are too large to be declared on
	  // the task stack, so are instead declared static (making this function
	  // non-reentrant meaning it can only be called by a single task at a time,
	  // otherwise multiple tasks would use the same buffers).
	  static uint8_t first_receive_buffer[BUFFER_SIZE], second_receive_buffer[BUFFER_SIZE];
	  xSemaphoreHandle notification_semaphore = NULL;
	  const max_block_time_500ms = 500 / portTICK_RATE_MS;
		twi_packet_t read_parameters;
		uint16_t calculated_address;

	      // Configure the read_parameters structure to define a read operation
	      // that fills the first receive buffer.
	      read_parameters.chip = BOARD_AT24C_ADDRESS;
	      read_parameters.buffer = first_receive_buffer;
	      read_parameters.length = BUFFER_SIZE;
	      read_parameters.addr_length = 2;

	      // The first read is from address 0.
	      calculated_address = 0;
	      read_parameters.addr[0] = 0;
	      read_parameters.addr[1] = 0;

	      // Create the notification semaphore that will be used by FreeRTOS to
	      // notify the task that the receive operation is complete.
	      vSemaphoreCreateBinary(notification_semaphore);

	      // Nothing has been read over the TWI bus yet, so make sure the
	      // semaphore starts in the expected empty state.
	      xSemaphoreTake(notification_semaphore, 0);

	      // Start an asynchronous read to fill the first buffer.  The function
	      // will be able to access the port immediately because nothing else has
	      // accessed it yet - allowing the block_time_ticks value to be set to 0.
	      freertos_twi_read_packet_async(freertos_twi, &read_parameters, 0
	                                                     notification_semaphore);

	      // Wait until the first buffer is full.  Other tasks will run during
	      // the wait.  FreeRTOS will give notification_semaphore when
	      // the receive is complete.
	      xSemaphoreTake(notification_semaphore, max_block_time_500ms);

	      // Move the calculated address by the amount of bytes read so far.
	      calculated_address += BUFFER_SIZE
	      read_parameters.addr[0] = (uint8_t) ((calculated_address >> 8) & 0xff);
	      read_parameters.addr[1] = (uint8_t) (calculated_address & 0xff);

	      // The first buffer is full.  The next read will fill the second buffer.
	      read_parameters.buffer = second_receive_buffer;

	      // Start an asynchronous read to fill the second buffer.  Assuming no
	      // other tasks are using the same TWI port, it is known that the port is
	      // already available because the first read has completed.  This means
	      // the block time can be 0.
	      freertos_twi_read_packet_async(freertos_twi, &read_parameters, 0
	                                                     notification_semaphore);

	      // Process the data in the first receive buffer while the second
	      // receive buffer is being filled.
	      process_received_data(first_receive_buffer);

	      // Wait until the second buffer is full.  Other tasks will run
	      // during the wait.  FreeRTOS will give notification_semaphore when
	      // the receive is complete.
	      xSemaphoreTake(notification_semaphore, max_block_time_500ms);

	      // Process the data in the second receive buffer.
	      process_received_data(second_receive_buffer);
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

#endif /* FREERTOS_TWI_MASTER_INCLUDED */
