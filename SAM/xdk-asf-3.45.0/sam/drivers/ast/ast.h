/**
 * \file
 *
 * \brief SAM Asynchronous Timer (AST) driver.
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

#ifndef AST_H_INCLUDED
#define AST_H_INCLUDED

/**
 * \defgroup asfdoc_sam_drivers_ast_group SAM4L Asynchronous Timer (AST) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides 
 * an interface for the configuration and management of the device's 
 * Asynchronous Timer functionality.
 *
 * The Asynchronous Timer can generate periodic interrupts and peripheral events
 * from output from the prescaler, as well as alarm interrupts and peripheral
 * events, which can trigger at any counter value.
 *
 * Devices from the following series can use this module:
 * - Atmel | SMART SAM4L
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam_drivers_ast_prerequisites
 *  - \ref asfdoc_sam_drivers_ast_module_overview
 *  - \ref asfdoc_sam_drivers_ast_special_considerations
 *  - \ref asfdoc_sam_drivers_ast_extra_info
 *  - \ref asfdoc_sam_drivers_ast_examples
 *  - \ref asfdoc_sam_drivers_ast_api_overview
 *
 *
 * \section asfdoc_sam_drivers_ast_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam_drivers_ast_module_overview Module Overview
 * The AST module in the SAM4L devices is a 32-bit counter, with a 32-bit
 * programmable prescaler. Typically, the AST clock is run continuously,
 * including in the device's low-power sleep modes, to track the current time
 * and date information. The AST can also wake-up the system from backup mode
 * using either the alarm wakeup, periodic wakeup, or overflow wake-up mechanisms.
 *
 * The AST has been designed to meet the system tick and Real-Time Clock
 * requirements of most embedded operating systems.
 *
 * In this driver, the AST is operated in Calendar Mode. This allows for an
 * easy integration of a Real-Time Clock and calendar into a user application
 * to track the passing of time and/or perform scheduled tasks.
 *
 * Whilst operating in Calendar Mode, the AST features:
 *  - Time tracking in seconds, minutes, and hours in 24 hour format
 *  - Date tracking in day, month, and year
 *  - Automatic leap year correction
 *
 * \subsection asfdoc_sam_drivers_ast_overview_alarms Alarm Interrupt
 * The AST has a device dependent number of independent hardware alarms that can
 * be configured by the user application. These alarms will be triggered
 * on a match with the current clock value, and can be set up to trigger an
 * interrupt, event, or both. The AST can also be configured to clear the clock
 * value on alarm match which will generate an overflow interrupt.
 *
 * \note Refer to module configuration at the end of the AST section of the device
 * datasheet for the number of alarms supported.
 *
 * Whilst in Calendar Mode and using a nominal 1Hz input clock frequency, a register
 * overflow will occur after 64 years.
 *
 * \subsection asfdoc_sam_drivers_ast_overview_periodic Periodic Events
 * The AST can generate events at periodic intervals, allowing for direct
 * peripheral actions without CPU intervention. The periodic events can be
 * generated on an AST prescaler match, and will be generated on
 * the rising edge transition of the specified bit. The resulting periodic
 * frequency can be calculated by the following formula:
 *
 * \f[ f_{PERIODIC}=\frac{f_{ASY}}{2^{n+1}} \f]
 *
 * Where \f$f_{ASY}\f$ refers to the \e asynchronous clock set up in the AST
 * module configuration.
 *
 * \note The connection of events between modules requires the use of the
 *       \ref asfdoc_sam_drivers_events_group "SAM4L Peripheral Event Controller (PEVC)"
 *       to route an output event of one module to the the input event of another.
 *       For more information on event routing, refer to the event driver
 *       documentation.
 *
 * \subsection asfdoc_sam_drivers_ast_overview_correction Digital Tuner
 * The AST module contains Digital Tuner logic to compensate for inaccurate source clock
 * frequencies, which would otherwise result in skewed time measurements.
 *
 *
 * \section asfdoc_sam_drivers_ast_special_considerations Special Considerations
 *
 * \subsection asfdoc_sam_drivers_ast_special_considerations_crystal Crystal Selection
 * The external crystal selection used by the AST module in the final system design must take
 * into account:
 * - Current consumption to achieve the best power savings in low power operating modes
 * - Frequency drift (due to temperature effects on the circuit) for the best time accuracy
 *
 * \subsection asfdoc_sam_drivers_ast_special_considerations_year Year Limit
 * The AST module has a year range of 63 years from the starting year configured
 * when the module is initialized. Dates outside the start to end year range
 * described below will need software adjustment:
 *
 * \f[ [YEAR_{START}, YEAR_{START}+64] \f]
 *
 *
 * \section asfdoc_sam_drivers_ast_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_sam_drivers_ast_extra. This includes:
 *  - \ref asfdoc_sam_drivers_ast_extra_acronyms
 *  - \ref asfdoc_sam_drivers_ast_extra_dependencies
 *  - \ref asfdoc_sam_drivers_ast_extra_errata
 *  - \ref asfdoc_sam_drivers_ast_extra_history
 *
 * \section asfdoc_sam_drivers_ast_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam_drivers_ast_exqsg.
 *
 * \section asfdoc_sam_drivers_ast_api_overview API Overview
 * @{
 */
 
#include <compiler.h>

/// @cond */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond */

/** Timeout to prevent code hang in clock initialization. */
#define AST_POLL_TIMEOUT 10000

/** \name Predefined PSEL Values
 */
/* @{ */

/**
 * \brief The PSEL value to set the AST source clock (after the prescaler) to 1Hz,
 * when using an external 32-kHz crystal.
 */
#define AST_PSEL_32KHZ_1HZ    14

/**
 * \brief The PSEL value to set the AST source clock (after the prescaler)
 * to 1.76Hz when using the internal RC oscillator (~ 115kHz)
 */
#define AST_PSEL_RC_1_76HZ    15

/* @} */

#if !defined(__DOXYGEN__)
/** \internal Timeout to prevent code hang in clock initialization */
#define AST_POLL_TIMEOUT 10000
#endif /* !defined(__DOXYGEN__) */
/** Description for Calendar Field. */
struct ast_calv {
	/** Seconds in the range 0 to 59 */
	uint32_t sec   : 6;
	/** Minutes in the range range 0 to 59 */
	uint32_t min   : 6;
	/** Hours in the range 0 to 23 */
	uint32_t hour  : 5;
	/** Day in the range 1 to 31 */
	uint32_t day   : 5;
	/** Month in the range 1 to 12 */
	uint32_t month : 4;
	/** Year in the range 0 to 63 */
	uint32_t year  : 6;
};

/* Input when initializing AST in calendar mode. */
struct ast_calendar {
	union {
		uint32_t field;
		/** Calendar */
		struct ast_calv FIELD;
	};
};

/** \ref ast_mode "AST Calendar Mode". */
typedef enum ast_mode {
	/** Counter Mode */
	AST_COUNTER_MODE  = 0,
	/** Calendar Mode */
	AST_CALENDAR_MODE = 1,
} ast_mode_t;

/** \ref ast_oscillator_type "AST Oscillator type". */
typedef enum ast_oscillator_type {
	/** System RC oscillator (RCSYS) */
	AST_OSC_RC    = 0,
	/** 32kHz oscillator (OSC32 or RC32) */
	AST_OSC_32KHZ = 1,
	/** APB clock */
	AST_OSC_PB    = 2,
	/** Generic clock (GCLK) */
	AST_OSC_GCLK  = 3,
	/** 1kHz clock from the 32kHz oscillator or 32kHz RC oscillator (CLK_1K) */
	AST_OSC_1KHZ  = 4,
} ast_oscillator_type_t;

#if !defined(__DOXYGEN__)
#define AST_INTERRUPT_SOURCE_NUM    5
#endif /* !defined(__DOXYGEN__) */
/** \ref ast_interrupt_source "AST interrupt source". */
typedef enum ast_interrupt_source {
	/** Alarm interrupt */
	AST_INTERRUPT_ALARM = 0,
	/** Periodic interrupt */
	AST_INTERRUPT_PER,
	/** Overflow interrupt */
	AST_INTERRUPT_OVF,
	/** Synchronization complete interrupt */
	AST_INTERRUPT_READY,
	/** Clock synchronization complete interrupt */
	AST_INTERRUPT_CLKREADY,
} ast_interrupt_source_t;

/** \ref ast_wakeup_source "AST wake-up source". */
typedef enum ast_wakeup_source {
	/** Alarm wake-up source */
	AST_WAKEUP_ALARM = 0,
	/** Peripheral interrupt wake-up source */
	AST_WAKEUP_PER,
	/** Counter overflow wake-up source */
	AST_WAKEUP_OVF,
} ast_wakeup_source_t;

/** \ref ast_event_source "AST event source". */
typedef enum ast_event_source {
	/** Alarm event generation */
	AST_EVENT_ALARM = 0,
	/** Peripheral event generation */
	AST_EVENT_PER,
	/** Counter overflow event generation */
	AST_EVENT_OVF,
} ast_event_source_t;

/** AST configuration. */
struct ast_config {
	/**
	 * Mode: Calendar Mode:
	 * \ref AST_CALENDAR_MODE or
	 * Counter Mode: \ref AST_COUNTER_MODE
	 */
	ast_mode_t mode;
	/** Oscillator type */
	ast_oscillator_type_t osc_type;
	/** Prescaler Value */
	uint8_t psel;
	/** Initial counter Value */
	uint32_t counter;
	/** Initial calendar Value */
	struct ast_calendar calendar;
};

/** AST interrupt callback. */
typedef void (*ast_callback_t)(void);

bool ast_is_enabled(Ast *ast);

void ast_enable(Ast *ast);
void ast_disable(Ast *ast);

uint32_t ast_set_config(Ast *ast, struct ast_config *ast_conf);
void ast_set_callback(Ast *ast, ast_interrupt_source_t source,
		ast_callback_t callback, uint8_t irq_line, uint8_t irq_level);
uint32_t ast_configure_digital_tuner(Ast *ast, uint32_t input_freq,
		uint32_t tuned_freq);
void ast_init_digital_tuner(Ast *ast, bool add, uint8_t value,
		uint8_t exp);
void ast_disable_digital_tuner(Ast *ast);

void ast_write_calendar_value(Ast *ast, struct ast_calendar calendar);
struct ast_calendar ast_read_calendar_value(Ast *ast);
void ast_write_counter_value(Ast *ast, uint32_t ast_counter);
void ast_enable_counter_clear_on_alarm(Ast *ast, uint8_t alarm_channel);
void ast_clear_prescalar(Ast *ast);

/**
 * \brief Get the AST current counter value.
 *
 * \param[in] ast Module hardware register base address pointer
 *
 * \return AST current counter value.
 */
static inline uint32_t ast_read_counter_value(
		Ast *ast)
{
	return ast->AST_CV;
}

/**
 * \brief Check the busy status of the AST clock
 *
 * \param[in] ast Module hardware register base address pointer
 *
 * \return AST clock busy status.
 * \retval false AST clock is not busy
 * \retval true  AST clock is busy
 */
static inline bool ast_is_clkbusy(
		Ast *ast)
{
	return (ast->AST_SR & AST_SR_CLKBUSY) != 0;
}

/**
 * \brief Check the busy status of AST.
 *
 * \param[in] ast Module hardware register base address pointer
 *
 * \return AST busy status.
 * \retval false AST is not busy
 * \retval true AST is busy
 */
static inline bool ast_is_busy(
		Ast *ast)
{
	return (ast->AST_SR & AST_SR_BUSY) != 0;
}

/**
 * \brief Get the status of AST.
 *
 * \param[in] ast Module hardware register base address pointer
 *
 * \return AST status.
 */
static inline uint32_t ast_read_status(
		Ast *ast)
{
	return ast->AST_SR;
}

/**
 * \brief Get the AST interrupt mask value.
 *
 * \param[in] ast Module hardware register base address pointer
 *
 * \return AST Interrupt mask value.
 */
static inline uint32_t ast_read_interrupt_mask(Ast *ast)
{
	return ast->AST_IMR;
}

/**
 * \brief Start the AST counter.
 *
 * \param[in,out] ast  Module hardware register base address pointer
 */
static inline void ast_start(Ast *ast)
{
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}
	ast->AST_CR |= AST_CR_EN;
}

/**
 * \brief Stop the AST counter.
 *
 * \param[in,out] ast  Module hardware register base address pointer
 */
static inline void ast_stop(Ast *ast)
{
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}
	ast->AST_CR &= ~(AST_CR_EN);
}

void ast_write_alarm0_value(Ast *ast, uint32_t alarm_value);
void ast_write_periodic0_value(Ast *ast, uint32_t pir);

void ast_enable_interrupt(Ast *ast, ast_interrupt_source_t source);
void ast_disable_interrupt(Ast *ast, ast_interrupt_source_t source);
void ast_clear_interrupt_flag(Ast *ast, ast_interrupt_source_t source);

void ast_enable_wakeup(Ast *ast, ast_wakeup_source_t source);
void ast_disable_wakeup(Ast *ast, ast_wakeup_source_t source);

void ast_enable_event(Ast *ast, ast_event_source_t source);
void ast_disable_event(Ast *ast, ast_event_source_t source);

/// @cond */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond */

/** @} */

/**
 * \page asfdoc_sam_drivers_ast_extra Extra Information for Asynchronous Timer Driver
 *
 * \section asfdoc_sam_drivers_ast_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *  <tr>
 *      <th>Acronym</th>
 *      <th>Definition</th>
 *  </tr>
 *  <tr>
 *      <td>BPM</td>
 *      <td>Backup Power Manager</td>
 * </tr>
 *  <tr>
 *      <td>QSG</td>
 *      <td>Quick Start Guide</td>
 * </tr>
 * </table>
 *
 *
 * \section asfdoc_sam_drivers_ast_extra_dependencies Dependencies
 * This driver has the following dependencies:
 *
 *  - None
 *
 *
 * \section asfdoc_sam_drivers_ast_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam_drivers_ast_extra_history Module History
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
 * \page asfdoc_sam_drivers_ast_exqsg Examples for Asynchronous Timer Driver
 *
 * This is a list of the available Quick Start Guides (QSGs) and example
 * applications for \ref asfdoc_sam_drivers_ast_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that a QSG can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam_drivers_ast_qsg
 *  - \subpage asfdoc_sam_drivers_ast_example1
 *  - \subpage asfdoc_sam_drivers_ast_example2
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
 *		<td>42283B</td>
 *		<td>07/2015</td>
 *		<td>Updated title of application note and added list of supported devices</td>
 *	</tr>
 *	<tr>
 *		<td>42283A</td>
 *		<td>05/2014</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 *
 */

/**
 * \page asfdoc_sam_drivers_ast_qsg Quick Start Guide for the AST driver
 *
 * This is the quick start guide for the \ref asfdoc_sam_drivers_ast_group, with
 * step-by-step instructions on how to configure and use the driver for
 * a specific use case.The code examples can be copied into the main 
 * application loop or any other function that will need to control 
 * the AST module.
 *
 * \section asfdoc_sam_drivers_ast_qsg_use_cases Use Cases
 * - \ref asfdoc_sam_drivers_ast_qsg_basic
 *
 * \section asfdoc_sam_drivers_ast_qsg_basic AST Basic Usage
 *
 * This use case will demonstrate how to initialize the AST module to
 * calendar or counter mode.
 *
 *
 * \section asfdoc_sam_drivers_ast_qsg_basic_setup Setup Steps
 *
 * \subsection asfdoc_sam_ast_qsg_basic_prereq Prerequisites
 *
 * This module requires the following service:
 * - \ref clk_group "System Clock Management (sysclock)"
 *
 * \subsection asfdoc_sam_drivers_ast_qsg_basic_setup_code Setup Code
 *
 * Add this to the main loop or a setup function:
 * \code osc_priv_enable_osc32(); \endcode
 *
 * \subsection asfdoc_sam_drivers_ast_qsg_basic_setup_workflow Workflow
 *
 * -# Enable the AST module:
 * \code ast_enable(AST); \endcode
 * -# Initialize the AST to counter mode:
 * \code
 * struct ast_config ast_conf;
 * ast_conf.mode = AST_COUNTER_MODE;
 * ast_conf.osc_type = AST_OSC_32KHZ;
 * ast_conf.psel = AST_PSEL_32KHZ_1HZ;
 * ast_conf.counter = 0;
 * ast_set_config(AST, &ast_conf);
 * \endcode
 * -# Or initialize the AST to calendar mode:
 * \code
 * struct ast_calendar calendar;
 * struct ast_config ast_conf;
 * calendar.FIELD.sec = 0;
 * calendar.FIELD.min = 15;
 * calendar.FIELD.hour = 12;
 * calendar.FIELD.day = 20;
 * calendar.FIELD.month = 9;
 * calendar.FIELD.year = 12;
 * struct ast_config ast_conf;
 * ast_conf.mode = AST_CALENDAR_MODE;
 * ast_conf.osc_type = AST_OSC_32KHZ;
 * ast_conf.psel = AST_PSEL_32KHZ_1HZ;
 * ast_conf.calendar = calendar;
 * ast_set_config(AST, &ast_conf) \endcode
 * \note We need to set the clock after prescaler to 1Hz.
 *
 *
 * \section asfdoc_sam_drivers_ast_qsg_basic_usage Usage Steps
 *
 * \subsection asfdoc_sam_drivers_ast_qsg_basic_usage_code Usage Code
 *
 * We can get the calendar value by:
 * \code calendar = ast_read_calendar_value(AST); \endcode
 * Or we can get the counter value by:
 * \code ast_counter = ast_read_counter_value(AST); \endcode
 *
 * We can set the alarm interrupt by:
 * \code
 * ast_write_alarm0_value(AST, calendar.field + 1);
 * ast_set_callback(AST, ast_interrupt_alarm, ast_alarm_callback,
 *    AST_ALARM_IRQn, 1); \endcode
 * And we can set the periodic interrupt by:
 * \code
 * ast_write_periodic0_value(AST, AST_PSEL_32KHZ_1HZ - 4);
 * ast_set_callback(AST, ast_interrupt_per, ast_per_callback,
 *    AST_PER_IRQn, 1); \endcode
 */

#endif  /* AST_H_INCLUDED */
