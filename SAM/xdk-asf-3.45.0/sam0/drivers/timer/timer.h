/**
 * \file
 *
 * \brief SAM TIMER Driver for SAMB11
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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
#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

/**
 * \defgroup asfdoc_samb_timer_group SAM TIMER
 *
 * This driver for Atmel&reg; | SMART SAM devices provides an interface for the
 * configuration and management of the device's basic Timer functionality.
 *
 * The following peripherals are used by this module:
 *  - TIMER
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM B11
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_samb_timer_prerequisites
 *  - \ref asfdoc_samb_timer_module_overview
 *  - \ref asfdoc_samb_timer_special_considerations
 *  - \ref asfdoc_samb_timer_extra_info
 *  - \ref asfdoc_samb_timer_examples
 *  - \ref asfdoc_samb_timer_api_overview
 *
 *
 * \section asfdoc_samb_timer_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_samb_timer_module_overview Module Overview
 * This driver proiveds a basic timer for count, is a 32-bit
 * down-counter with the following features:
 *
 * - You can generate an interrupt request signal, TIMERINT,
 * when the counter reaches 0.
 
 * - The interrupt request is held until it is cleared by writing to the INTCLEAR Register.
 *
 * - You can use the zero to one transition of the external input signal, EXTIN, as a timer enable.
 *
 * - If the APB timer count reaches 0 and, at the same time, the software clears a previous
 * interrupt status, the interrupt status is set to 1.
 *
 * - The external clock, EXTIN, must be slower than half of the peripheral clock because it is
 * sampled by a double flip-flop and then goes through edge-detection logic when the
 * external inputs act as a clock. 
 *
 * - A separate clock pin, PCLKG, for the APB register read or write logic that permits the
 * clock to peripheral register logic to stop when there is no APB activity.
 *
 * \section asfdoc_samb_timer_special_considerations Special Considerations
 *
 * There are no prerequisites for this module.
 *
 * \section asfdoc_samb_timer_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_samb_timer_extra. This includes:
 *  - \ref asfdoc_samb_timer_extra_acronyms
 *  - \ref asfdoc_samb_timer_extra_dependencies
 *  - \ref asfdoc_samb_timer_extra_errata
 *  - \ref asfdoc_samb_timer_extra_history
 *
 *
 * \section asfdoc_samb_timer_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_samb_timer_exqsg.
 *
 *
 * \section asfdoc_samb_timer_api_overview API Overview
 * @{
 */

#include <compiler.h>
#include <system_sam_b.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Type definition for a TIMER module callback function. */
typedef void (*timer_callback_t)(void);

/**
 * \brief TIMER configuration structure.
 *
 * Configuration struct for a TIMER instance. This structure should be
 * initialized by the \ref timer_get_config_defaults function before being
 * modified by the user application.
 */
struct timer_config {
	/** Reload value */
	uint32_t reload_value;
	/** Enable timer interrupt */
	bool interrupt_enable;
};

/**
 * \name Configuration and Initialization
 * @{
 */
void timer_get_config_defaults(struct timer_config *config);
void timer_init(const struct timer_config *config);
/** @} */

/**
 * \name Get and set value
 * @{
 */
uint32_t timer_get_value(void);
void timer_set_value(uint32_t value);
/** @} */

/**
 * \name Get and Clear status
 * @{
 */
uint32_t timer_get_interrupt_status(void);
void timer_clear_interrupt_status(void);
/** @} */

/**
 * \name Enable and disable module
 * @{
 */
void timer_enable(void);
void timer_disable(void);
/** @} */

/**
 * \name Callback
 * @{
 */
void timer_register_callback(timer_callback_t fun);
void timer_unregister_callback(void);
/** @} */

/** @}*/

#ifdef __cplusplus
}
#endif

/**
 * \page asfdoc_samb_timer_extra Extra Information for TIMER Driver
 *
 * \section asfdoc_samb_timer_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 * <table>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *	<tr>
 *		<td>TIMER</td>
 *		<td>Timer</td>
 *	</tr>
 * </table>
 *
 * \section asfdoc_samb_timer_extra_dependencies Dependencies
 * There are no dependencies related to this driver.
 *
 *
 * \section asfdoc_samb_timer_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_samb_timer_extra_history Module History
 * An overview of the module history is presented in the table below, with
 * details on the enhancements and fixes made to the module since its first
 * release. The current version of this corresponds to the newest version in
 * the table.
 *
 * <table>
 *  <tr>
 *      <th>Changelog</th>
 *  </tr>
 *  <tr>
 *      <td>Initial Release</td>
 *  </tr>
 * </table>
 */

/**
 * \page asfdoc_samb_timer_exqsg Examples for TIMER Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_samb_timer_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that QSGs can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_samb_timer_basic_use_case
 *
 * \page asfdoc_samb_timer_document_revision_history Document Revision History
 *
 * <table>
 *  <tr>
 *    <th>Doc. Rev.</td>
 *    <th>Date</td>
 *    <th>Comments</td>
 *  </tr>
 *  <tr>
 *    <td>A</td>
 *    <td>09/2015</td>
 *    <td>Initial release</td>
 *  </tr>
 * </table>
 */

#endif