/**
 * \file
 *
 * \brief FreeRTOS Peripheral Control API For the USART
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
#ifndef FREERTOS_USART_SERIAL_INCLUDED
#define FREERTOS_USART_SERIAL_INCLUDED

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* ASF includes. */
#include "freertos_peripheral_control.h"
#include "usart.h"

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
 * \defgroup freertos_usart_peripheral_control_group FreeRTOS USART peripheral
 * control
 * \brief FreeRTOS peripheral control functions for the USART peripheral
 * \ingroup freertos_service_group
 */

/**
 * \ingroup freertos_usart_peripheral_control_group
 * \typedef freertos_usart_if
 * \brief Type returned from a call to freertos_usart_serial_init(), and then
 * used to reference a USART port in calls to FreeRTOS peripheral control
 * functions.
 */
typedef void *freertos_usart_if;

freertos_usart_if freertos_usart_serial_init(Usart *p_usart,
		const sam_usart_opt_t *const uart_parameters,
		const freertos_peripheral_options_t *const freertos_driver_parameters);

status_code_t freertos_usart_write_packet_async(freertos_usart_if p_usart,
		const uint8_t *data, size_t len, portTickType block_time_ticks,
		xSemaphoreHandle notification_semaphore);

uint32_t freertos_usart_serial_read_packet(freertos_usart_if p_usart,
		uint8_t *data, uint32_t len, portTickType block_time_ticks);

/**
 * \ingroup freertos_usart_peripheral_control_group
 * \brief Initiate a multi-byte write operation on an USART peripheral.
 *
 * freertos_usart_write_packet() is an ASF specific FreeRTOS driver function. It
 * configures the USART peripheral DMA controller (PDC) to transmit data on the
 * USART port, then waits until the transmission is complete. Other RTOS tasks
 * execute while the transmission is in progress.
 *
 * freertos_usart_write_packet_async() is a version that does not wait for the
 * transmission to complete before returning.
 *
 * The FreeRTOS ASF USART driver is initialized using a call to
 * freertos_usart_serial_init().  The freertos_driver_parameters.options_flags
 * parameter passed into the initialization function defines the driver
 * behavior.
 * freertos_usart_write_packet() can only be used if the
 * freertos_driver_parameters.options_flags parameter passed to the
 * initialization function had the WAIT_TX_COMPLETE bit set.
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
 * \param data    A pointer to the data to be transmitted.
 * \param len    The number of bytes to transmit.
 * \param block_time_ticks    The FreeRTOS ASF USART driver is initialized using
 *     a call to freertos_usart_serial_init().  The
 *     freertos_driver_parameters.options_flags parameter passed to the
 *     initialization function defines the driver behavior.  If
 *     freertos_driver_parameters.options_flags had the USE_TX_ACCESS_SEM bit
 *     set, then the driver will only write to the USART peripheral if it has
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
 *     to the USART peripheral could be obtained.  STATUS_OK is returned if the
 *     PDC was successfully configured to perform the USART write operation.
 */
#define freertos_usart_write_packet(p_usart, data, len, block_time_ticks) freertos_usart_write_packet_async((p_usart), (data), (len), (block_time_ticks), (NULL))
 
/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif  /* FREERTOS_USART_SERIAL_INCLUDED */

/**
 * \page freertos_usart_peripheral_control_quick_start Quick start guide for
 * FreeRTOS USART peripheral control functions
 *
 * This is the quick start guide for the
 * \ref freertos_usart_peripheral_control_group, with
 * step-by-step instructions on how to configure and use the service.
 *
 * The service can be initialized to operate in one of two different modes -
 * standard transmit mode, and fully asynchronous transmit mode.  There is only
 * one receive mode.
 *
 * freertos_usart_write_packet() is used to transmit data in standard mode.
 * freertos_usart_write_packet() does not return until all the data has been
 * fully transmitted.  Other FreeRTOS tasks will execute while the data
 * transmission is in progress.
 *
 * freertos_usart_write_packet_async() is used to transmit data in the fully
 * asynchronous mode.  freertos_usart_write_packet_async() returns as soon as
 * the data transmission has started (not when it has finished), and can opt to
 * be notified by FreeRTOS when the transmission is complete.  The buffer being
 * transmitted must not be altered until the transmission is complete.
 *
 * freertos_usart_write_packet_async() must not be used when the peripheral is
 * initialized to use standard mode.  Likewise, freertos_usart_write_packet()
 * must not be used when the peripheral is configured to use fully asynchronous
 * mode.
 *
 * On asynchronous full duplex peripherals, such as the USART, data can be
 * received at any time, not just when a receive function is called.  On these
 * peripherals, to ensure data is not lost, the FreeRTOS drivers are configured
 * to place all received data into a dma buffer, no matter when the data arrives.
 * When a receive function is called, the data already in the dma buffer is
 * copied into the user buffer specified in a parameter to the receive function.
 * Available but unread data remains in the dma buffer, ready for the next
 * receive function call.
 *
 * Refer to the FreeRTOS peripheral control projects in the Atmel ASF
 * distribution for complete working examples, and the
 * <a href="http://www.FreeRTOS.org" target="_blank">FreeRTOS web site</a> for
 * information on getting started with FreeRTOS.
 *
 * \section freertos_usart_sync_use_case_tx Transmitting In Standard Mode
 * - \subpage freertos_usart_initialization_sync
 * - \subpage freertos_usart_tx_sync
 *
 * \section freertos_usart_async_use_case_tx Transmitting in Fully Asynchronous
 * Mode
 * - \subpage freertos_usart_initialization_async
 * - \subpage freertos_usart_tx_async
 *
 * \section freertos_usart_async_use_case_rx Receiving
 * - \subpage freertos_usart_rx_async
 */

/**
 * \page freertos_usart_initialization_sync Initializing the FreeRTOS USART
 * driver for standard operation
 *
 * This example configures the FreeRTOS USART driver to:
 * - Support simultaneous access from multiple RTOS tasks.
 * - Wait in the FreeRTOS transmit function until all the data has been
 * completely sent
 *
 * Other FreeRTOS tasks will execute during any wait period.
 *
 * If the driver is initialized with this configuration then only the
 * freertos_usart_write_packet() API function can be used to transmit data.
 * freertos_usart_write_packet_async() must not be used.
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
	 // freertos_usart_serial_init() function.

	 // Declare a buffer to be used as the UART receive DMA buffer.  The FreeRTOS
	 // peripheral control drivers manage this buffer, and use it as a circular
	 // buffer.
	 uint8_t receive_buffer[BUFFER_SIZE];

	 // Handle used to access the initialized port by other FreeRTOS ASF functions.
	 freertos_usart_if freertos_usart;

	 // Configuration structure.
	 freertos_peripheral_options_t driver_options = {

	     // This peripheral has full duplex asynchronous operation, so the
	     // receive_buffer value is set to a valid buffer location (declared
	     // above).
	     receive_buffer,

	     // receive_buffer_size is set to the size, in bytes, of the buffer
	     // pointed to by the receive_buffer value.
	     BUFFER_SIZE,

	     // The interrupt priority.  The FreeRTOS driver provides the interrupt
	     // service routine, and handles all interrupt interactions.  The
	     // application writer does not need to provide any interrupt handling
	     // code, but does need to specify the priority of the DMA interrupt here.
	     // IMPORTANT!!!  see <a href="http://www.freertos.org/RTOS-Cortex-M3-M4.html">how to set interrupt priorities to work with FreeRTOS</a>
	     0x0e,

	     // The operation_mode value.
	     USART_RS232,

	     // Flags set to allow access from multiple tasks, and to wait in the
	     // transmit function until the transmit is complete.  Note that other
	     // FreeRTOS tasks will execute during the wait period.
	     (USE_TX_ACCESS_SEM | USE_RX_ACCESS_MUTEX | WAIT_TX_COMPLETE)
	  };

	  // The RS232 configuration.  This structure, and the values used in its
	  // setting, are from the standard ASF USART driver.
	  const sam_usart_opt_t usart_settings =
	  {
	      USART_BAUD_RATE,
	      US_MR_CHRL_8_BIT,
	      US_MR_PAR_NO,
	      US_MR_NBSTOP_1_BIT,
	      US_MR_CHMODE_NORMAL,
	      0 // Only used in IrDA mode, so all values are ignored.
	  };

	 /////////////////////////////////////////////////////////////////////////////
	 // Call the USART specific FreeRTOS ASF driver initialization function,
	 // storing the return value as the driver handle.
	  freertos_usart = freertos_usart_serial_init(usart_base, &usart_settings,
	                             &driver_options);
\endcode
 */

/**
 * \page freertos_usart_initialization_async Initializing the FreeRTOS USART
 * driver for asynchronous operation
 *
 * This example configures the FreeRTOS USART driver to:
 * - Support simultaneous access from multiple RTOS tasks.
 * - Exit the FreeRTOS transmit function as soon as the transmission is started.
 *
 * If the driver is initialized with this configuration then only the
 * freertos_usart_write_packet_async() API function can be used to transmit
 * data.  freertos_usart_write_packet() must not be used.
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
	 // freertos_usart_serial_init function.

	 // Declare a buffer to be used as the UART receive DMA buffer.  The FreeRTOS
	 // peripheral control drivers manage this buffer, and use it as a circular
	 // buffer.
	 uint8_t receive_buffer[BUFFER_SIZE];

	 // Handle used to access the initialized port by other FreeRTOS ASF functions.
	 freertos_usart_if freertos_usart;

	 // Configuration structure.
	 freertos_peripheral_options_t driver_options = {

	     // This peripheral has full duplex asynchronous operation, so the
	     // receive_buffer value is set to a valid buffer location (declared
	     // above).
	     receive_buffer,

	     // receive_buffer_size is set to the size, in bytes, of the buffer
	     // pointed to by the receive_buffer value.
	     BUFFER_SIZE,

	     // The interrupt priority.  The FreeRTOS driver provides the interrupt
	     // service routine, and handles all interrupt interactions.  The
	     // application writer does not need to provide any interrupt handling
	     // code, but does need to specify the priority of the DMA interrupt here.
	     // IMPORTANT!!!  see <a href="http://www.freertos.org/RTOS-Cortex-M3-M4.html">how to set interrupt priorities to work with FreeRTOS</a>
	     0x0e,

	     // The operation_mode value.
	     USART_RS232,

	     // Flags set to allow access from multiple tasks.  Note in this case the
	     // WAIT_TX_COMPLETE flag is *not* used.
	     (USE_TX_ACCESS_SEM | USE_RX_ACCESS_MUTEX)
	  };

	  // The RS232 configuration.  This structure, and the values used in its
	  // setting, are from the standard ASF USART driver.
	  const sam_usart_opt_t usart_settings =
	  {
	      USART_BAUD_RATE,
	      US_MR_CHRL_8_BIT,
	      US_MR_PAR_NO,
	      US_MR_NBSTOP_1_BIT,
	      US_MR_CHMODE_NORMAL,
	      0 // Only used in IrDA mode, so all values are ignored.
	  };

	 /////////////////////////////////////////////////////////////////////////////
	 // Call the USART specific FreeRTOS ASF driver initialization function,
	 // storing the return value as the driver handle.
	  freertos_usart = freertos_usart_serial_init(usart_base, &usart_settings,
								&driver_options);
\endcode
 */

/**
 * \page freertos_usart_tx_sync Transmitting using the FreeRTOS USART driver in
 * standard mode
 *
 * This example demonstrates using the FreeRTOS USART API to send data using the
 * standard operation mode.  * See \ref freertos_usart_initialization_sync
 *
 * The example below implements a function that transmits two strings, and then
 * returns.
 *
 * Refer to the FreeRTOS peripheral control projects in the Atmel ASF
 * distribution for complete working examples, and the
 * <a href="http://www.FreeRTOS.org" target="_blank">FreeRTOS web site</a> for
 * information on getting started with FreeRTOS.
 *
 * \code

	 // This examples assumes freertos_usart has already been set by a successful
	 // call to freertos_usart_serial_init(), and that freertos_usart_serial_init()
	 // configured the FreeRTOS USART driver to use the standard operation mode.

	 status_code_t write_two_strings(freertos_usart_if freertos_usart){
	     uint8_t write_buffer[5];
	     status_code_t result;

	     // Send a string to the USART.  The string must be in RAM, so copy it into
	     // an array.
	     strcpy(write_buffer, "one");

	     // Using a block time of 10 / portTICK_RATE_MS means "don't block any
	     // longer than 10ms" to wait for access to the USART.  Other FreeRTOS tasks
	     // will execute during the wait period.
	     result = freertos_usart_write_packet(freertos_usart, write_buffer,
							strlen("one"), 10 / portTICK_RATE_MS);

	     if(result == STATUS_OK) {
	         // freertos_usart_write_packet() does not return until transmission
	         // of the string has completed (other FreeRTOS tasks will execute
	         // while the transmission is in progress), meaning the write_buffer
	         // array can be re-used immediately without any risk of corrupting
	         // the original transmission.  Copy the second string to be
	         // transmitted into the RAM buffer.
	         strcpy(write_buffer, "two");
	         result = freertos_usart_write_packet(freertos_usart, write_buffer,
	                                     strlen("two"), 10 / portTICK_RATE_MS);
	     }

	     // freertos_usart_write_packet() does not return until transmission of
	     // the string has completed (other FreeRTOS task will execute while the
	     // transmission is in progress), meaning the function can exit even
	     // though the buffer being transmitted is declared on the function's
	     // stack because it is guaranteed that nothing is still using the data
	     // the buffer contains.
	     return result;
	 }
\endcode
 */

/**
 * \page freertos_usart_tx_async Transmitting using the FreeRTOS USART driver in
 * fully asynchronous mode
 *
 * This example demonstrates using the FreeRTOS USART API to send data using the
 * fully asynchronous operation mode.
 * See \ref freertos_usart_initialization_async
 *
 * The example below implements a function that transmits two strings, and then
 * returns.
 *
 * Refer to the FreeRTOS peripheral control projects in the Atmel ASF
 * distribution for complete working examples, and the
 * <a href="http://www.FreeRTOS.org" target="_blank">FreeRTOS web site</a> for
 * information on getting started with FreeRTOS.
 *
 * \code

	 	// This examples assumes freertos_usart has already been set by a successful
	 	// call to freertos_usart_serial_init(), and that freertos_usart_serial_init()
	 	// configured the FreeRTOS ASF driver for standard mode operation.

	 	// xSemaphoreHandle is a FreeRTOS type used to store a handle to a semaphore.
	 	// In this example, the semaphore has already been created using a call to
	 	// the FreeRTOS vSemaphoreCreateBinary() API function, and is being passed in
	 	// as a function parameter.
	  status_code_t write_two_strings(freertos_usart_if freertos_usart,
	                                   xSemaphoreHandle notification_semaphore){
	      uint8_t write_buffer[5];
	      status_code_t result;

	      // Send a string to the USART.  The string must be in RAM, so copy it
	      // into an array.  The array must exist for the entire time taken to
	      // transmit the string.  This can be ensured by making it global, static,
	      // or by allocating it on the stack and then ensuring the stack frame
	      // does not change until the transmission is complete.
	      strcpy(write_buffer, "one");

	      // notification_semaphore, passed into the function, is used by the
	      // FreeRTOS ASF driver to signal that the transmission has finished.
	      // Using a block time of 100 / portTICK_RATE_MS means "don't block any
	      // longer than 100ms" to get access to the USART.
	      result = freertos_usart_write_packet_async(freertos_usart, write_buffer,
	                  strlen("one"), 100 / portTICK_RATE_MS,
	                  notification_semaphore);

	      if(result == STATUS_OK) {
	          // Transmission of the string was started successfully.
	      }

	      // .. other processing can be performed here, while the string is being
	      // transmitted ..

	      // Another string is going to be sent, but the write_buffer array must
	      // not be altered until the original transmission is complete.  If the
	      // notification semaphore is available, then the transmission is
	      // complete and the following function call will return immediately.  If
	      // the notification semaphore is not available, then the following
	      // function call will place this task into the Blocked state for a
	      // maximum of 200ms to wait for it to become available (other tasks will
	      // execute during the wait).
	      xSemaphoreTake(notification_semaphore, 200 / portTICK_RATE_MS);
	      strcpy(write_buffer, "two");
	      result = freertos_usart_write_packet_async(freertos_usart, write_buffer,
	                  strlen("two"), 100 / portTICK_RATE_MS,
	                  notification_semaphore);
	      // .. other processing can be performed here, while the string is being
	      // transmitted ..
	      // In this example, the array being transmitted is declared on the
	      // stack.  If this function exits, the array will no longer exist, and
	      // if it was still being transmitted, the transmitted data can be
	      // corrupted.  Therefore, xSemaphoreTake() is used again to  ensure the
	      // transmission has completely finished before allowing the function to
	      // return.
	      xSemaphoreTake(notification_semaphore, 200 / portTICK_RATE_MS);

	      return result;
	  }
\endcode
 */

/**
 * \page freertos_usart_rx_async Receiving using the FreeRTOS USART driver
 *
 * This example demonstrates using the FreeRTOS USART API to receive data.
 *
 * The example below implements a function that attempts to read 20 bytes from a
 * USART.  The read operation will time out if 20 bytes could not be obtained
 * within 20ms.
 *
 * Refer to the FreeRTOS peripheral control projects in the Atmel ASF
 * distribution for complete working examples, and the
 * <a href="http://www.FreeRTOS.org" target="_blank">FreeRTOS web site</a> for
 * information on getting started with FreeRTOS.
 *
 * \code
	  void a_function(freertos_usart_if freertos_usart)
	  {
	  uint8_t receive_buffer[20];
	  uint32_t bytes_received;
	  portTickType max_wait_20ms = 20 / portTICK_RATE_MS;

	      // Attempt to read 20 bytes from freertos_usart.  If fewer than 20 bytes are
	      // available, then wait a maximum of 20ms for the rest to arrive.
	      bytes_received = freertos_usart_serial_read_packet(freertos_usart,
	                              receive_buffer, 20,  max_wait_20ms);

	      if(bytes_received == 20)
	      {
	          // All the bytes were received.  The RTOS task calling this function
	          // *may* have been placed into the Blocked state to wait for all the
	          // bytes to be available.  Other tasks will execute while this task
	          // is in the Blocked state.
	      }
	      else
	      {
	          // Fewer than the requested number of bytes have been received, so
	          // the RTOS task calling this function did enter the blocked state
	          // for the full 20 milliseconds before giving up.
	      }
	  }
\endcode
 */
