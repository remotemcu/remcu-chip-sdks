/**
 * \file
 *
 * \brief Debug print include
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

#ifndef DBG_PRINT_H
#define DBG_PRINT_H

#include <compiler.h>
#include <status_codes.h>
#include <conf_dbg_print.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup asfdoc_common_freertos_dbg_print_group Debug Print Service for FreeRTOS
 *
 * This service provides a thread-safe, buffered debug print facility via UART
 * for FreeRTOS-based applications.
 *
 * It can also be used without FreeRTOS, but will then not be thread-safe nor
 * have efficient waiting when the buffer is full.
 *
 * The following peripherals are used by this module:
 * - SERCOM (Serial Communication Interface)
 *
 * The outline of this documentation is as follows:
 * - \ref asfdoc_common_freertos_dbg_print_prerequisites
 * - \ref asfdoc_common_freertos_dbg_print_module_overview
 * - \ref asfdoc_common_freertos_dbg_print_extra_info
 * - \ref asfdoc_common_freertos_dbg_print_examples
 * - \ref asfdoc_common_freertos_dbg_print_api_overview
 *
 *
 * \section asfdoc_common_freertos_dbg_print_prerequisites Prerequisites
 *
 * The reader is assumed to be familiar with configuration of the SERCOM USART
 * driver since this service uses similar configuration settings.
 *
 * To enable FreeRTOS-support, the symbol \c __FREERTOS__ must be defined. This
 * will typically be done automatically if FreeRTOS is included from ASF. As
 * this service is meant to be used in tasks, the FreeRTOS scheduler should be
 * started before any of the print functions are called.
 *
 * To get thread-safety and efficient waiting with other OS or schedulers, the
 * following functions in \ref dbg_print.c must be modified:
 * - \ref _dbg_wait_for_lock()
 * - \ref _dbg_unlock()
 * - \ref _dbg_interrupt_handler()
 * - \ref _dbg_wait_for_requested_space()
 * - \ref dbg_init()
 *
 *
 * \section asfdoc_common_freertos_dbg_print_module_overview Module Overview
 *
 * This service essentially consists of a print buffer and functions for doing
 * protected writes to it, and an interrupt handler which performs transmission
 * of the buffer contents using a SERCOM module in UART mode. It has been
 * written for use in FreeRTOS-based applications where concurrent tasks need to
 * output debug messages, for example via the Communication Device Class (CDC)
 * of the Embedded Debugger (EDBG) on Xplained Pro boards.
 *
 * This service can be used without FreeRTOS, but will then not be thread safe
 * nor have efficient waiting when the buffer is full. To support other OSes and
 * schedulers, see \ref asfdoc_common_freertos_dbg_print_prerequisites for a
 * list of the functions that must be modified.
 *
 * This service should not be used within interrupts.
 *
 *
 * \subsection asfdoc_common_freertos_dbg_print_buffer Print Buffer
 *
 * The reason for using a print buffer is to minimize the time it takes for a
 * task to output its debug message, so the impact on application response time
 * and functionality is reduced. Instead of waiting for the debug message to be
 * sent, the calling task only needs to wait for the message to get into the
 * print buffer. Of course, if the print buffer becomes full, the tasks must
 * wait for buffer space to free up.
 *
 * Both buffer size and UART baud rate are configurable, so one may find a
 * reasonable balance between memory usage and interrupt rate. As a minimum
 * requirement, the print buffer should not be smaller than the longest debug
 * message in the application.
 *
 *
 * \subsection asfdoc_common_freertos_dbg_print_access Access Control
 *
 * Access control for the print buffer is built into this service to prevent
 * concurrent calls from corrupting each other's print output. The FreeRTOS
 * mechanism for this access control, a mutex, will keep other calling tasks
 * waiting while the print buffer is being modified by one task. Once the print
 * buffer becomes available again, the waiting task with the highest priority
 * is given access to the buffer.
 *
 * Note that this mechanism may cause tasks of lower priority to be kept waiting
 * indefinitely if the print buffer is small and there is a lot of waiting for
 * buffer space to free up. In such cases, the higher priority tasks may end up
 * taking turns waiting for enough buffer space to get their respective debug
 * messages into it.
 *
 *
 * \subsection asfdoc_common_freertos_dbg_print_config Configuration
 *
 * This service implements a single debug print interface, which is compile-time
 * configured via the header file \ref conf_dbg_print.h to ensure the smallest
 * size code and highest execution speed.
 *
 * The available configuration symbols are:
 * <table>
 *   <tr>
 *     <th>Name</th>
 *     <th>Description</th>
 *   </tr>
 *   <tr>
 *     <td>\ref CONF_DBG_PRINT_BUFFER_SIZE</td>
 *     <td>Print buffer size. Must be a power of 2 (.., 32, 64, 128, ..).</td>
 *   </tr>
 *   <tr>
 *     <td>\ref CONF_DBG_PRINT_SERCOM</td>
 *     <td>The SERCOM module to use as UART.</td>
 *   </tr>
 *   <tr>
 *     <td>\ref CONF_DBG_PRINT_GCLK_SOURCE</td>
 *     <td>The GCLK that the SERCOM shall use as clock source</td>
 *   </tr>
 *   <tr>
 *     <td>\ref CONF_DBG_PRINT_BAUD_RATE</td>
 *     <td>Target baud rate for computation of the SERCOM's BAUD register value.
 *        </td>
 *   </tr>
 *   <tr>
 *     <td>\ref CONF_DBG_PRINT_BAUD_VALUE</td>
 *     <td>Optional override of \ref CONF_DBG_PRINT_BAUD_RATE, lets user
 *        explicitly set the register value to reduce code size.</td>
 *   </tr>
 *   <tr>
 *     <td>\ref CONF_DBG_PRINT_SERCOM_MUX</td>
 *     <td>The SERCOM signal MUX setting to use.</td>
 *   </tr>
 *   <tr>
 *     <td>\ref CONF_DBG_PRINT_PINMUX_PAD0</td>
 *     <td>Pin MUX setting for connecting pin with SERCOM pad 0.</td>
 *   </tr>
 *   <tr>
 *     <td>\ref CONF_DBG_PRINT_PINMUX_PAD1</td>
 *     <td>Pin MUX setting for connecting pin with SERCOM pad 1.</td>
 *   </tr>
 *   <tr>
 *     <td>\ref CONF_DBG_PRINT_PINMUX_PAD2</td>
 *     <td>Pin MUX setting for connecting pin with SERCOM pad 2.</td>
 *   </tr>
 *   <tr>
 *     <td>\ref CONF_DBG_PRINT_PINMUX_PAD3</td>
 *     <td>Pin MUX setting for connecting pin with SERCOM pad 3.</td>
 *   </tr>
 * </table>
 *
 * \note If \c CONF_DBG_PRINT_BAUD_VALUE is defined, the symbol
 * \c CONF_DBG_PRINT_BAUD_RATE will not have any effect, and does not need to be
 * defined at all.
 *
 *
 * \section asfdoc_common_freertos_dbg_print_extra_info Extra Info
 *
 * For extra information see \ref asfdoc_common_freertos_dbg_print_extra.
 * This includes:
 * - \ref asfdoc_common_freertos_dbg_print_extra_freertos
 * - \ref asfdoc_common_freertos_dbg_print_extra_acronyms
 * - \ref asfdoc_common_freertos_dbg_print_extra_dependencies
 *
 *
 * \section asfdoc_common_freertos_dbg_print_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_common_freertos_dbg_print_exqsg.
 *
 *
 * \section asfdoc_common_freertos_dbg_print_api_overview API Overview
 *
 * @{
 */

//! \name Configuration macros
//@{

/**
 * \def CONF_DBG_PRINT_SERCOM
 * \brief SERCOM module to use as UART
 */

/**
 * \def CONF_DBG_PRINT_BUFFER_SIZE
 * \brief Size of print buffer (must be a power of 2)
 */

/**
 * \def CONF_DBG_PRINT_GCLK_SOURCE
 * \brief GCLK generator to use for SERCOM
 */

#ifdef __DOXYGEN__

/**
 * \def CONF_DBG_PRINT_BAUD_RATE
 * \brief Desired baud rate
 *
 * \note This macro can be overridden with a hardcoded BAUD register value in
 * CONF_DBG_PRINT_BAUD_VALUE.
 */
# if !defined(CONF_DBG_PRINT_BAUD_RATE)
#  define CONF_DBG_PRINT_BAUD_RATE
# endif

/**
 * \def CONF_DBG_PRINT_BAUD_VALUE
 * \brief Hardcoded BAUD register value (optional)
 *
 * To reduce code size, a hardcoded BAUD register value can be supplied via this
 * configuration macro.
 *
 * The formula to use is: \f$ 65536 \times (1 - \frac{16 \times f_{baud}}{f_{gclk}}) \f$
 * where \c f_gclk is the rate of the GCLK source.
 *
 * \note If this macro is defined, the macro CONF_DBG_PRINT_BAUD_RATE will have
 * no effect.
 */
# if !defined(CONF_DBG_PRINT_BAUD_VALUE)
#  define CONF_DBG_PRINT_BAUD_VALUE
# endif

#endif

/**
 * \def CONF_DBG_PRINT_SERCOM_MUX
 * \brief SERCOM signal MUX setting
 */

/**
 * \def CONF_DBG_PRINT_PINMUX_PAD0
 * \brief Pin MUX setting for SERCOM pad 0
 */

/**
 * \def CONF_DBG_PRINT_PINMUX_PAD1
 * \brief Pin MUX setting for SERCOM pad 1
 */

/**
 * \def CONF_DBG_PRINT_PINMUX_PAD2
 * \brief Pin MUX setting for SERCOM pad 2
 */

/**
 * \def CONF_DBG_PRINT_PINMUX_PAD3
 * \brief Pin MUX setting for SERCOM pad 3
 */

//@}

//! \name Initialization
//@{
enum status_code dbg_init(void);
//@}

//! \name Print to string
//@{
void dbg_sprint_hexint(char *outstr, uint32_t outint);
//@}

//! \name Print to buffer
//@{
void dbg_print_hexint(uint32_t outint);
void dbg_print_str(const char *outstr);
void dbg_print_char(const char outchar);
//@}

/** @} */

#ifdef __cplusplus
}
#endif

/**
 * \page asfdoc_common_freertos_dbg_print_extra Extra Information for Debug Print Service for FreeRTOS
 *
 * \section asfdoc_common_freertos_dbg_print_extra_freertos FreeRTOS Version
 *
 * \section asfdoc_common_freertos_dbg_print_extra_acronyms Acronyms
 *
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *   <tr>
 *     <th>Acronym</th>
 *     <th>Description</th>
 *   </tr>
 *   <tr>
 *     <td>CDC</td>
 *     <td>Communications Device Class</td>
 *   </tr>
 *   <tr>
 *     <td>EDBG</td>
 *     <td>Embedded Debugger</td>
 *   </tr>
 *   <tr>
 *     <td>GCLK</td>
 *     <td>Generic Clock</td>
 *   </tr>
 *   <tr>
 *     <td>UART</td>
 *     <td>Universal Asynchronous Receiver/Transmitter</td>
 *   </tr>
 * </table>
 *
 *
 * \section asfdoc_common_freertos_dbg_print_extra_dependencies Dependencies
 * This driver has the following dependencies:
 * - FreeRTOS
 * - \ref asfdoc_sam0_sercom_usart_group "SERCOM USART Driver"
 * - \ref asfdoc_sam0_system_clock_group "System Clock Driver"
 * - \ref asfdoc_sam0_system_pinmux_group "System Pin MUX Driver"
 *
 *
 * \section asfdoc_common_freertos_dbg_print_extra_errata Errata
 *
 * There are no errata related to this driver.
 */

/**
 * \page asfdoc_common_freertos_dbg_print_exqsg Examples for Debug Print Service for FreeRTOS
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_common_freertos_dbg_print_group. QSGs are simple
 * examples with step-by-step instructions to configure and use this driver in
 * a selection of use cases. Note that QSGs can be compiled as a standalone
 * application or be added to the user application.
 *
 *  - \subpage asfdoc_common_freertos_dbg_print_basic_use_case
 */

/**
 * \page asfdoc_common_freertos_dbg_print_document_revision_history Document Revision History
 *
 * <table>
 *   <tr>
 *     <th>Doc. Rev.</td>
 *     <th>Date</td>
 *     <th>Comments</td>
 *   </tr>
 *   <tr>
 *     <td>A</td>
 *     <td>02/2014</td>
 *     <td>Initial release</td>
 *   </tr>
 * </table>
 */

#endif // DBG_PRINT_H
