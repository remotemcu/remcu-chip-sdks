/**
 * \file
 *
 * \brief SAM4L Peripheral Event Controller (PEVC) Driver.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

/**
 * \defgroup asfdoc_sam_drivers_events_group SAM4L Peripheral Event Controller (PEVC) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers 
 * provides a unified interface for the configuration and
 * management of the Event Channels.
 *
 * The peripheral event generators and users are interconnected by a network
 * known as the Peripheral Event System.
 *
 * The Peripheral Event System allows low latency peripheral-to-peripheral
 * signaling without CPU intervention, and without consuming system resources
 * such as bus or RAM bandwidth. This offloads the CPU and system resources
 * compared to a traditional interrupt-based software driven system.
 *
 * Devices from the following series can use this module:
 * - Atmel | SMART SAM4L
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam_drivers_events_prerequisites
 *  - \ref asfdoc_sam_drivers_events_module_overview
 *  - \ref asfdoc_sam_drivers_events_special_considerations
 *  - \ref asfdoc_sam_drivers_events_extra_info
 *  - \ref asfdoc_sam_drivers_events_examples
 *  - \ref asfdoc_sam_drivers_events_api_overview
 *
 * \section asfdoc_sam_drivers_events_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam_drivers_events_module_overview Module Overview
 *
 * Peripherals within the SAM4L device are capable of generating two types of
 * actions in response to a given stimulus; they can set a register flag for later
 * intervention by the CPU (using interrupt or polling methods), or they can
 * generate event signals which can be internally routed directly to other
 * peripherals within the device. The use of events allows for direct actions
 * to be performed in one peripheral in response to a stimulus in another
 * without CPU intervention. This can lower the overall power consumption of the
 * system if the CPU is able to remain in sleep modes for longer periods, and
 * lowers the latency of the system response.
 *
 * The Peripheral Event System is comprised of a number of freely configurable Event
 * Channels, plus a number of fixed Event Users. Each Event Channel can be
 * configured to select the input peripheral that will generate the events on
 * the channel, as well as the Event Shaper (EVS) and Input Glitch Filter (IGF)
 * operating modes. The fixed-function Event Users, connected to peripherals
 * within the device, can then subscribe to an Event Channel in a one-to-many
 * relationship in order to receive events as they are generated. An overview
 * of the event system chain is shown in
 * \ref asfdoc_sam_drivers_events_overview_fig "the figure below".
 *
 * \anchor asfdoc_sam_drivers_events_overview_fig
 * \dot
 * digraph overview {
 *   rankdir=LR;
 *   node [label="Generator" shape=rectangle] event_src_gen0;
 *   node [label="Generator" shape=rectangle] event_src_gen1;
 *   node [label="Peripheral\nEvent System" shape=rectangle style=""] event_system;
 *   node [label="User" shape=rectangle style=""] event_user0;
 *   node [label="User/\nGenerator" shape=rectangle style=""] event_user1;
 *
 *   event_src_gen0 -> event_system -> event_user0;
 *   event_src_gen1 -> event_system -> event_user1 -> event_system;
 * }
 * \enddot
 *
 * There are many different events that can be routed in the device, which can
 * then trigger many different actions. For example, an Analog Comparator module
 * could be configured to generate an event when the input signal rises above
 * the compare threshold, which then triggers a Timer Counter module to capture
 * the current count value for later use.
 *
 * \subsection asfdoc_sam_drivers_events_overview_event_channels Event Channels
 * The Peripheral Event Controller module in the SAM4L device consists of several
 * channels, which can be freely linked to an Event Generator (i.e. a peripheral
 * within the device that is capable of generating events). Each channel can be
 * individually configured to select the generator peripheral, signal path,
 * Event Shaper (EVS), and Input Glitch Filter (IGF) applied to the input event
 * signal, before being passed to any event user(s).
 *
 * Event Channels can support multiple users within the device in a standardized
 * manner; when an Event User is linked to an Event Channel, the channel will
 * automatically handshake with all attached users to ensure that all modules
 * correctly receive and acknowledge the event.
 *
 * \subsection asfdoc_sam_drivers_events_overview_event_users Event Users
 * Event Users are able to subscribe to an Event Channel, once it has been
 * configured. Each Event User consists of a fixed connection to one of the
 * peripherals within the device (for example, an ADC module or Timer module)
 * and is capable of being connected to a single Event Channel.
 *
 * \subsection asfdoc_sam_drivers_events_module_overview_event_shaper Event Shaper (EVS)
 * The Peripheral Event Controller module contains Event Shapers (EVS) for
 * external inputs and general purpose waveforms (i.e. timer outputs or Generic
 * Clocks) that require synchronisation and/or edge detection prior to peripheral
 * event propagation.
 *
 * Each Event Shaper is responsible for shaping one generator input prior to
 * it going through an Event Channel.
 *
 * Refer to the module configuration section at the end
 * of the Peripheral Event Controller (PEVC) section in the device datasheet for the
 * specific configuration of Event Shapers and Input Glitch Filters.
 *
 * \subsubsection asfdoc_sam_drivers_events_module_overview_input_glitch_filer Input Glitch Filter (IGF)
 * The Peripheral Event Controller module contains Input Glitch Filters (IGF)
 * specifically to allow I/O inputs to be sampled periodically. Input Glitch
 * Filtering can be turned on or off in the Event Shaper associated with the
 * Event Channel.
 *
 * \subsection asfdoc_sam_drivers_events_overview_physical Physical Connection
 *
 * \ref asfdoc_sam_drivers_events_int_connections_fig "The diagram below"
 * shows how this module is interconnected within the device.
 *
 * \anchor asfdoc_sam_drivers_events_int_connections_fig
 * \dot
 * digraph overview {
 *   rankdir=LR;
 *   node [label="Source\nPeripherals" shape=ellipse style=filled fillcolor=lightgray] src_peripheral;
 *
 *   subgraph driver {
 *     node [label="<f0> PEVC | <f1> Event Channels" fillcolor=white shape=record] events_chan;
 *     node [label="<f0> PEVC | <f1> Event Users" fillcolor=white shape=record] events_user;
 *   }
 *
 *   node [label="Destination\nPeripherals" shape=ellipse style=filled fillcolor=lightgray] dst_peripheral;
 *
 *   src_peripheral -> events_chan:f1 [label="Source\nMUXes"];
 *   events_chan:f1 -> events_user:f1 [label="Channel\nMUXes"];
 *   events_user:f1 -> dst_peripheral;
 * }
 * \enddot
 *
 * \subsection asfdoc_sam_drivers_events_overview_config Configuring Events
 * Several steps are required to properly configure an event chain, so that
 * hardware peripherals can respond to events generated by each other,
 * listed below.
 *
 * \subsubsection asfdoc_sam_drivers_events_overview_config_src Source Peripheral
 *  -# The source peripheral (that will generate events) must be configured and
 *     enabled.
 *  -# The source peripheral (that will generate events) must have an output
 *     event enabled.
 *
 * \subsubsection asfdoc_sam_drivers_events_overview_config_evsys Event System
 *  -# The event system channel must be configured and enabled, with the
 *     correct source peripheral selected as the channel's Event Generator.
 *  -# The event system user must be configured and enabled, with the
 *     correct source Event Channel selected as the source.
 *
 * \subsubsection asfdoc_sam_drivers_events_overview_config_dst Destination Peripheral
 *  -# The destination peripheral (that will receive events) must be configured
 *     and enabled.
 *  -# The destination peripheral (that will receive events) must have an input
 *     event enabled.
 *
 *
 * \section asfdoc_sam_drivers_events_special_considerations Special Considerations
 *
 * There are no special considerations for this module.
 *
 * \section asfdoc_sam_drivers_events_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_sam_drivers_events_extra. This includes:
 *  - \ref asfdoc_sam_drivers_events_extra_acronyms
 *  - \ref asfdoc_sam_drivers_events_extra_dependencies
 *  - \ref asfdoc_sam_drivers_events_extra_errata
 *  - \ref asfdoc_sam_drivers_events_extra_history
 *
 * \section asfdoc_sam_drivers_events_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam_drivers_events_exqsg.

 *
 * \section asfdoc_sam_drivers_events_api_overview API Overview
 * @{
 */

 #include <compiler.h>
 
 /// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/** Maximum number for Event Channels (users). */
#define EVENT_CHANNEL_N      PEVC_TRIGOUT_BITS

/** Maximum number for event generator. */
#define EVENT_GENERATOR_N    PEVC_EVIN_BITS

/**
 * \brief Input Glitch Filter divider configurations.
 *
 * Enumerate for the possible division ratios of an Input Glitch Filter.
 */
enum events_igf_divider {
	/** Select a prescaler division ratio of 1 */
	EVENT_IGF_DIVIDER_1       = 0,
	/** Select a prescaler division ratio of 2 */
	EVENT_IGF_DIVIDER_2       = 1,
	/** Select a prescaler division ratio of 4 */
	EVENT_IGF_DIVIDER_4       = 2,
	/** Select a prescaler division ratio of 8 */
	EVENT_IGF_DIVIDER_8       = 3,
	/** Select a prescaler division ratio of 16 */
	EVENT_IGF_DIVIDER_16      = 4,
	/** Select a prescaler division ratio of 32 */
	EVENT_IGF_DIVIDER_32      = 5,
	/** Select a prescaler division ratio of 64 */
	EVENT_IGF_DIVIDER_64      = 6,
	/** Select a prescaler division ratio of 128 */
	EVENT_IGF_DIVIDER_128     = 7,
	/** Select a prescaler division ratio of 256 */
	EVENT_IGF_DIVIDER_256     = 8,
	/** Select a prescaler division ratio of 512 */
	EVENT_IGF_DIVIDER_512     = 9,
	/** Select a prescaler division ratio of 1024 */
	EVENT_IGF_DIVIDER_1024    = 10,
	/** Select a prescaler division ratio of 2048 */
	EVENT_IGF_DIVIDER_2048    = 11,
	/** Select a prescaler division ratio of 4096 */
	EVENT_IGF_DIVIDER_4096    = 12,
	/** Select a prescaler division ratio of 8192 */
	EVENT_IGF_DIVIDER_8192    = 13,
	/** Select a prescaler division ratio of 16384 */
	EVENT_IGF_DIVIDER_16384   = 14,
	/** Select a prescaler division ratio of 32768 */
	EVENT_IGF_DIVIDER_32768   = 15
};

/**
 * \brief Event Input Glitch Filter edge detection configurations.
 */
enum events_igf_edge {
	/** Input Glitch Filter is disabled */
	EVENT_IGF_EDGE_NONE    = 0,
	/** Event detection through Input Glitch Filter on rising edge */
	EVENT_IGF_EDGE_RISING  = 1,
	/** Event detection through Input Glitch Filter on falling edge */
	EVENT_IGF_EDGE_FALLING = 2,
	/** Event detection through Input Glitch Filter on both edges */
	EVENT_IGF_EDGE_BOTH    = 3
};

/**
 * \brief Event configuration structure.
 *
 * Configuration structure for event module.
 */
struct events_conf {
	/** Input Glitch Filter divider */
	enum events_igf_divider igf_divider;
};

/**
 * \brief Event Channel configuration structure.
 *
 * Configuration structure for an Event Channel.
 */
struct events_ch_conf {
	/** Channel to configure (user) */
	uint32_t channel_id;
	/** Event generator to connect to the channel */
	uint32_t generator_id;
	/** Enable Event Shaper (EVS) or not */
	bool shaper_enable;
	/** Edge detection for Event Channels */
	enum events_igf_edge   igf_edge;
};

void events_get_config_defaults(struct events_conf *const config);

void events_init(struct events_conf *const config);

void events_enable(void);

void events_disable(void);

/**
 * \brief Set the Input Glitch Filter Divider.
 *
 * \param[in]  divider Input Glitch Filter divider
 *
 * \note As stated in the datasheet, there is one divider value for
 * all Event Shaper (EVS) instances.
 */
static inline void events_set_igf_divider(
		enum events_igf_divider divider)
{
	PEVC->PEVC_IGFDR = PEVC_IGFDR_IGFDR(divider);
}

void events_ch_get_config_defaults(struct events_ch_conf *const config);

void events_ch_configure(struct events_ch_conf *const config);

/**
 * \brief Enable an Event Channel.
 *
 * \param[in] channel_id  Event Channel ID
 */
static inline void events_ch_enable(
		uint32_t channel_id)
{
	PEVC->PEVC_CHER = PEVC_CHER_CHE(PEVC_CHER_CHE_1 << channel_id);
}

/**
 * \brief Disable an Event Channel.
 *
 * \param[in] channel_id  Event Channel ID
 */
static inline void events_ch_disable(
		uint32_t channel_id)
{
	PEVC->PEVC_CHDR = PEVC_CHDR_CHD(PEVC_CHDR_CHD_1 << channel_id);
}

/**
 * \brief Get the status (enabled or disabled) of an Event Channel.
 *
 * \param[in] channel_id  Event Channel ID
 *
 * \return The Event Channel enabled/disabled status.
 * \retval true  Event Channel is enabled
 * \retval false Event Channel is disabled
 */
static inline bool events_ch_is_enabled(
		uint32_t channel_id)
{
	if (PEVC->PEVC_CHSR & PEVC_CHSR_CHS(PEVC_CHSR_CHS_1 << channel_id)) {
		return true;
	} else {
		return false;
	}
}

/**
 * \brief Get the busy status of an Event Channel.
 *
 * \param[in] channel_id  Event Channel ID
 *
 * \return The Event Channel busy status.
 * \retval true  If the Event Channel is ready to be used
 * \retval false If the Event Channel is currently busy
 */
static inline bool events_ch_is_ready(
		uint32_t channel_id)
{
	if (PEVC->PEVC_BUSY & PEVC_BUSY_BUSY(PEVC_BUSY_BUSY_1 << channel_id)) {
		return false;
	} else {
		return true;
	}
}

/**
 * \brief Enable the software trigger for an Event Channel.
 *
 * \param[in] channel_id  Event Channel ID
 */
static inline void events_ch_enable_software_trigger(
		uint32_t channel_id)
{
	PEVC->PEVC_CHMX[channel_id].PEVC_CHMX |= PEVC_CHMX_SMX;
}

/**
 * \brief Disable the software trigger for an Event Channel.
 *
 * \param[in] channel_id  Event Channel ID
 */
static inline void events_ch_disable_software_trigger(
		uint32_t channel_id)
{
	PEVC->PEVC_CHMX[channel_id].PEVC_CHMX &= (~PEVC_CHMX_SMX);
}

/**
 * \brief Trigger a Software Event for the corresponding Event Channel.
 *
 * \param[in] channel_id  Event Channel ID
 */
static inline void events_ch_software_trigger(
		uint32_t channel_id)
{
	PEVC->PEVC_SEV = PEVC_SEV_SEV(PEVC_SEV_SEV_1 << channel_id);
}

/**
 * \brief Get the trigger status of an Event Channel.
 *
 * \param[in] channel_id  Event Channel ID
 *
 * \return The Event Channel trigger status.
 * \retval true  A channel event has occurred
 * \retval false A channel event has not occurred
 */
static inline bool events_ch_is_triggered(
		uint32_t channel_id)
{
	if (PEVC->PEVC_TRSR & PEVC_TRSR_TRS(PEVC_TRSR_TRS_1 << channel_id)) {
		return true;
	} else {
		return false;
	}
}

/**
 * \brief Clear the trigger status of an Event Channel.
 *
 * \param[in] channel_id  Event Channel ID
 */
static inline void events_ch_clear_trigger_status(
		uint32_t channel_id)
{
	PEVC->PEVC_TRSCR = PEVC_TRSCR_TRSC(PEVC_TRSCR_TRSC_1 << channel_id);
}

/**
 * \brief Get the overrun status of an Event Channel.
 *
 * \param[in] channel_id  Event Channel ID
 *
 * \return The Event Channel overrun status.
 * \retval true  A channel overrun event has occurred
 * \retval false A channel overrun event has not occurred
 */
static inline bool events_ch_is_overrun(
		uint32_t channel_id)
{
	if (PEVC->PEVC_OVSR & PEVC_OVSR_OVS(PEVC_OVSR_OVS_1 << channel_id)) {
		return true;
	} else {
		return false;
	}
}

/**
 * \brief Clear the overrun status of an Event Channel.
 *
 * \param[in] channel_id  Event Channel ID
 */
static inline void events_ch_clear_overrun_status(
		uint32_t channel_id)
{
	PEVC->PEVC_OVSCR = PEVC_OVSCR_OVSC(PEVC_OVSCR_OVSC_1 << channel_id);
}

/** @} */

/**
 * \page asfdoc_sam_drivers_events_extra Extra Information for Peripheral Event Controller Driver
 *
 * \section asfdoc_sam_drivers_events_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *  <tr>
 *      <th>Acronym</th>
 *      <th>Definition</th>
 *  </tr>
 *  <tr>
 *      <td>ADC</td>
 *      <td>Analog to Digital Converter</td>
 * </tr>
 *  <tr>
 *      <td>AST</td>
 *      <td>Asynchronous Timer</td>
 * </tr>
 *  <tr>
 *      <td>EVS</td>
 *      <td>Event Shaper</td>
 * </tr>
 *  <tr>
 *      <td>IGF</td>
 *      <td>Input Glitch Filter</td>
 *  </tr>
 *  <tr>
 *      <td>PDCA</td>
 *      <td>Peripheral DMA Controller</td>
 * </tr>

 * </table>
 *
 *
 * \section asfdoc_sam_drivers_events_extra_dependencies Dependencies
 * This driver has the following dependencies:
 *
 *  - None
 *
 *
 * \section asfdoc_sam_drivers_events_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam_drivers_events_extra_history Module History
 * An overview of the module history is presented in the table below, with
 * details on the enhancements and fixes made to the module since its first
 * release. The current version of this corresponds to the newest version in
 * the table.
 *
 * <table>
 *	<tr>
 *		<th>Changelog</th>
 *	</tr>
 *	<tr>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 */
 
/**
 * \page asfdoc_sam_drivers_events_exqsg Examples for Peripheral Event Controller Driver
 *
 * This is a list of the available Quick Start Guides (QSGs) and example
 * applications for \ref asfdoc_sam_drivers_events_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that a QSG can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam_events_qsg
 *  - \subpage asfdoc_sam_events_ex1
 *  - \subpage asfdoc_sam_events_ex2
 *
 * \page asfdoc_sam_drivers_supc_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>42312B</td>
 *		<td>07/2015</td>
 *		<td>Updated title of application note and added list of supported devices</td>
 *	</tr>
 *	<tr>
 *		<td>42312A</td>
 *		<td>05/2014</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 *
 */
  
/** \page asfdoc_sam_events_qsg Quick Start Guide for the Peripheral Event Controller Driver
 *
 * This is the quick start guide for the \ref asfdoc_sam_drivers_events_group, with
 * step-by-step instructions on how to configure and use the driver for
 * a specific use case.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section asfdoc_sam_events_qsg_use_cases Use Cases
 * - \ref asfdoc_sam_events_qsg_basic_use_case
 *
 * \section asfdoc_sam_events_qsg_basic_use_case Basic Use Case
 *
 * This use case will demonstrate how to use the Peripheral Event Controller
 * on SAM4L_EK. In this use case, one Event Channel is configured as:
 * - Configure AST periodic event 0 as a generator
 * - Configure PDCA channel 0 as a user to transfer one word
 * - Enable the event shaper for the generator
 *
 * \section asfdoc_sam_events_qsg_setup Setup Steps
 *
 * \subsection asfdoc_sam_events_qsg_prereq Prerequisites
 *
 * This module requires the following service:
 * - \ref clk_group "Clock Management (Sysclock)"
 *
 * \subsection asfdoc_sam_events_qsg_setup_code Code Example
 *
 * Copy-paste the following setup code to your application:
 * \snippet events_example1.c quick_start_init_events_function
 *
 * Add this to the main loop or a setup function:
 * \snippet events_example1.c quick_start_init_all_basic_use
 *
 * \subsection asfdoc_sam_events_qsg_setup_workflow Workflow
 *
 * -# Initialize AST to generate periodic event 0.
 *  see sam/drivers/events/example1 for more detail:
 *  \snippet events_example1.c quick_start_init_ast_basic_use
 *
 * -# Initialize the event module and enable it:
 * \snippet events_example1.c quick_start_init_events_basic_use
 *
 * -# Initialize PDCA channel 0 to transfer data to USART.
 *  see sam/drivers/events/example1 for more detail:
 *  \snippet events_example1.c quick_start_init_pdca_basic_use
 *
 * \section asfdoc_sam_events_qsg_usage Basic Usage
 *
 * After the channel is configured correctly and enabled, each time a new
 * event from AST occurs, a character is sent to the USART via PDCA without
 * the use of the CPU.
 */

 /// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif /* EVENTS_H_INCLUDED */
