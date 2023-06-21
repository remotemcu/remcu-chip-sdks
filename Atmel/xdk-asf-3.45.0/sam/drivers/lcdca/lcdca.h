/**
 * \file
 *
 * \brief SAM4L Liquid Crystal Display driver (LCDCA).
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
#ifndef LCDCA_H_INCLUDED
#define LCDCA_H_INCLUDED

/**
 * \defgroup asfdoc_sam_drivers_lcdca_group SAM4L Liquid Crystal Display (LCDCA) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides an interface for 
 * the configuration and management of the device's Liquid Crystal Display Controller 
 * functionality.
 *
 * The LCD controller is intended for monochrome passive Liquid Crystal Displays
 * (LCDs) with up to four common terminals and up to 40 segment terminals.
 *
 * Devices from the following series can use this module:
 * - Atmel | SMART SAM4L
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam_drivers_lcdca_prerequisites
 *  - \ref asfdoc_sam_drivers_lcdca_module_overview
 *  - \ref asfdoc_sam_drivers_lcdca_special_considerations
 *  - \ref asfdoc_sam_drivers_lcdca_extra_info
 *  - \ref asfdoc_sam_drivers_lcdca_examples
 *  - \ref asfdoc_sam_drivers_lcdca_api_overview
 *
 *
 * \section asfdoc_sam_drivers_lcdca_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam_drivers_lcdca_module_overview Module Overview
 *
 * \subsection asfdoc_sam_drivers_lcdca_module_overview_internal Display Physiology
 *
 * An LCD is made up of several segments (or complete symbols), which can be
 * visible or invisible. Any single segment has two electrodes, with liquid
 * crystal between them. These electrodes are connected to the common
 * terminal (COM) and the segment terminal (SEG) on the display. When a
 * voltage above a threshold voltage is applied across the liquid crystal,
 * the segment becomes visible. The voltage must alternate, to avoid an
 * electrophoresis effect in the liquid crystal, which degrades the display.
 *
 * \subsection asfdoc_sam_drivers_lcdca_module_overview_supported Supported Display Types
 * The LCD Controller is intended for use with monochrome passive Liquid
 * Crystal Displays (LCDs) with up to four common terminals and up to 40 segment
 * terminals.
 *
 * \subsection asfdoc_sam_drivers_lcdca_module_overview_functional Functional Description
 * The LCDCA display memory stores the values of all segments to display and
 * should be filled before the next frame starts.
 *
 * The start of a new frame triggers the update of the shadow display memory.
 * The content of the display memory is copied into the shadow display memory.
 * A display memory refresh is possible without affecting data that is sent to
 * the panel.
 *
 * \note The LCDCA display memory is not initialized at power-up.
 *
 * When any bit in the display memory is written to a one, the corresponding LCD
 * segment will be energized and opaque. If the same bit has zero written to it,
 * then the corresponding LCD segment is de-energized and thus transparent.
 *
 * \section asfdoc_sam_drivers_lcdca_special_considerations Special Considerations
 *
 * \subsection asfdoc_sam_drivers_lcdca_special_considerations_io I/O Lines
 *
 * The LCDCA pins (SEGx and COMy) are multiplexed with other peripherals. The
 * user application must first configure the I/O Controller, to give control of
 * the requisite pins to the LCDCA.
 *
 * \subsection asfdoc_sam_drivers_lcdca_special_considerations_pmc Power Management
 *
 * This module can control the LCD display while CLK_LCDCA is disabled, but
 * stops functioning when CLK_LCD (32kHz) is disabled.
 *
 * The power consumption of LCDCA itself can be minimized by:
 * - Using the lowest acceptable frame rate (refer to the LCD glass technical
 * characteristics)
 * - Using the low-power waveform (default mode)
 * - Using automated modes of operation
 * - Configuring the lowest possible contrast value
 *
 * \subsection asfdoc_sam_drivers_lcdca_special_considerations_clocks Clocks
 *
 * The clock for this module (CLK_LCDCA) is generated by the Power Manager. It
 * can be enabled or disabled, either manually (via the Power Manager) or automatically
 * when the system enters a sleep mode that disables the clocks to the peripheral
 * bus modules.
 *
 * The 32kHz clock (CLK_LCD) must be enabled before use.
 *
 * \subsection asfdoc_sam_drivers_lcdca_special_considerations_irq Interrupts
 *
 * The LCDCA interrupt request line is connected to the Nested Vectored Interrupt
 * Controller (NVIC). Use of the LCDCA interrupt requires the interrupt controller
 * to be configured first.
 *
 * \subsection asfdoc_sam_drivers_lcdca_special_considerations_wake_up Wake Up
 *
 * The LCD Controller's wake-up signal is connected to the Power Manager Controller
 * (PMC). Use of the wake-up mechanism requires the PMC to enable the corresponding
 * asynchronous wake-up source first. Also, the LCDCA interrupt must be enabled first.
 *
 * \subsection asfdoc_sam_drivers_lcdca_special_considerations_debug Debug Operation
 *
 * When an external debugger forces the CPU into debug mode, the LCDCA continues
 * normal operation.
 *
 *
 * \section asfdoc_sam_drivers_lcdca_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_sam_drivers_lcdca_extra. This includes:
 *  - \ref asfdoc_sam_drivers_lcdca_extra_acronyms
 *  - \ref asfdoc_sam_drivers_lcdca_extra_dependencies
 *  - \ref asfdoc_sam_drivers_lcdca_extra_errata
 *  - \ref asfdoc_sam_drivers_lcdca_extra_history
 *
 * \section asfdoc_sam_drivers_lcdca_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam_drivers_lcdca_exqsg.
 *
 *
 * \section asfdoc_sam_drivers_lcdca_api_overview API Overview
 * @{
 */

#include <compiler.h>
#include <sysclk.h>
#include <conf_lcdca.h>
#include <pdca.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \name LCDCA Address Limits */
/* @{ */
/** Maximum number of common lines*/
#define LCDCA_MAX_NR_OF_COM    4
/** Maximum number of segment lines */
# define LCDCA_MAX_NBR_OF_SEG  40
/* @} */

/** \name LCDCA Display Digit*/
/* @{ */
/** 7-segment display with three common terminals */
#define LCDCA_TDG_7SEG3COM        0
/** 7-segment display with four common terminals */
#define LCDCA_TDG_7SEG4COM        1
/** 14-segment display with four common terminals */
#define LCDCA_TDG_14SEG4COM       2
/** 16-segment display with three common terminals */
#define LCDCA_TDG_16SEG3COM       3
/* @} */

/** \name LCDCA Timer Resource */
/* @{ */
/** Timer FC0 resource */
#define LCDCA_TIMER_FC0        0
/** Timer FC1 resource */
#define LCDCA_TIMER_FC1        1
/** Timer FC2 resource */
#define LCDCA_TIMER_FC2        2
/* @} */

/** \name LCDCA CMCFG Digit Reverse Mode */
/* @{ */
#define LCDCA_CMCFG_DREV_LEFT   1 /**< Decrement the segment index */
#define LCDCA_CMCFG_DREV_RIGHT  0 /**< Increment the segment index */
/* @} */

/** LCDCA automated character DMA Channel (sequential or scrolling) */
#ifndef LCDCA_AUTOMATED_CHAR_DMA_CH
#define LCDCA_AUTOMATED_CHAR_DMA_CH  3
#endif

/** \name LCDCA Duty Selection. */
/* @{ */
#define LCDCA_DUTY_1_4     0   /**< Duty=1/4, Bias=1/3, COM0:3 */
#define LCDCA_DUTY_STATIC  1   /**< Duty=Static, Bias=Static, COM0 */
#define LCDCA_DUTY_1_2     2   /**< Duty=1/2, Bias=1/3, COM0:1 */
#define LCDCA_DUTY_1_3     3   /**< Duty=1/3, Bias=1/3, COM0:2 */
/* @} */

/** LCDCA controller configuration structure */
typedef struct lcdca_config {
	/** Number of SEGx pin connections used */
	uint8_t port_mask;
	/** External bias (false: internal gen, true: external gen) */
	bool x_bias;
	/** Wave mode (false: low power waveform, true: standard waveform) */
	bool lp_wave;
	/** Duty type selection */
	uint8_t duty_type;
	/** Clock source prescale bypass enable/disable */
	bool lcd_pres;
	/** Prescale clock source divider */
	uint8_t lcd_clkdiv;
	/** Frame Counter 0 */
	uint8_t fc0;
	/** Frame Counter 1 */
	uint8_t fc1;
	/** Frame Counter 2 */
	uint8_t fc2;
	/** Contrast setting */
	int8_t contrast;
} lcdca_config_t;

/** \name LCDCA Blink Mode */
/* @{ */
/** All LCD segments will blink */
#define LCDCA_BLINK_FULL       0
/** Only the selected segment will blink */
#define LCDCA_BLINK_SELECTED   LCDCA_BCFG_MODE
/* @} */

/** Blink configuration structure */
typedef struct lcdca_blink_config {
	/** LCDCA blink timer */
	uint8_t lcd_blink_timer;
	/** Blink Mode */
	uint8_t lcd_blink_mode;
} lcdca_blink_config_t;

/** \name LCDCA Shift Register Direction */
/* @{ */
/** Right direction */
#define LCDCA_CSR_RIGHT       LCDCA_CSRCFG_DIR
/** Left direction */
#define LCDCA_CSR_LEFT        0
/* @} */

/** Circular shift configuration structure */
typedef struct lcdca_circular_shift_config {
	/** LCDCA shift register timer */
	uint8_t lcd_csr_timer;
	/** Shift direction */
	uint8_t lcd_csr_dir;
	/** Size of the circular shift register */
	uint8_t size;
	/** Circular shift register value */
	uint8_t data;
} lcdca_circular_shift_config_t;

/** \name LCDCA Automated Mode. */
/* @{ */
/** Sequential character string display mode */
#define LCDCA_AUTOMATED_MODE_SEQUENTIAL    0
/** Scrolling character string display mode */
#define LCDCA_AUTOMATED_MODE_SCROLLING     1
/* @} */

/** \name LCDCA Automated Direction. */
/* @{ */
/** Digit direction is reversed. */
#define LCDCA_AUTOMATED_DIR_REVERSE        1
/** Digit direction is not reversed. */
#define LCDCA_AUTOMATED_DIR_NOT_REVERSE    0
/* @} */

/** Automated character display configuration structure. */
typedef struct lcdca_automated_char_config {
	/** Automated display mode selection */
	uint8_t automated_mode;
	/** Timer selected for automated mode */
	uint8_t automated_timer;
	/** Type of digit selected */
	uint8_t lcd_tdg;
	/** Start segment */
	uint8_t stseg;
	/**
	 * The number of steps to use in scrolling mode.
	 * STEPS = string length - DIGN + 1
	 */
	uint8_t steps;
	/** Number of digits used in the display */
	uint8_t dign;
	/** Digit display direction */
	uint8_t dir_reverse;
} lcdca_automated_char_config_t;

/** LCDCA interrupt callback type */
typedef void (*lcdca_callback_t)(void);

void lcdca_clk_init(void);
void lcdca_set_config(struct lcdca_config *lcdca_cfg);
void lcdca_enable(void);
void lcdca_disable(void);
void lcdca_set_contrast(int8_t contrast);
void lcdca_set_display_memory(void);

/**
 * \brief Clear all the LCDCA display memory.
 */
static inline void lcdca_clear_display_memory(void)
{
	LCDCA->LCDCA_CR = LCDCA_CR_CDM;
}

/**
 * \brief Lock the LCDCA shadow display memory.
 */
static inline void lcdca_lock_shadow_dislay(void)
{
	LCDCA->LCDCA_CFG |= LCDCA_CFG_LOCK;
}

/**
 * \brief Unlock the LCDCA shadow display memory.
 */
static inline void lcdca_unlock_shadow_dislay(void)
{
	LCDCA->LCDCA_CFG &= ~LCDCA_CFG_LOCK;
}

void lcdca_enable_timer(uint8_t lcd_timer);
void lcdca_disable_timer(uint8_t lcd_timer);
void lcdca_blink_set_config(struct lcdca_blink_config *blink_cfg);
void lcdca_set_blink_pixel(uint8_t pix_com, uint8_t pix_seg);
void lcdca_clear_blink_pixel(uint8_t pix_com, uint8_t pix_seg);
void lcdca_clear_blink_all_pixel(void);

/**
 * \brief Enable the LCDCA blink mode.
 */
static inline void lcdca_blink_enable(void)
{
	/* Blinking "on" */
	LCDCA->LCDCA_CR  = LCDCA_CR_BSTART;
}

/**
 * \brief Disable the LCDCA blink mode.
 */
static inline void lcdca_blink_disable(void)
{
	/* Blinking "off" */
	LCDCA->LCDCA_CR  = LCDCA_CR_BSTOP;
}

void lcdca_automated_char_set_config(
		struct lcdca_automated_char_config *ac_cfg);
void lcdca_automated_char_start(const uint8_t *data, size_t width);
void lcdca_automated_char_reload(const uint8_t *data, size_t width);

/**
 * \brief Stop the LCDCA automated display mode.
 *
 * \note This function also disables the PDCA channel associated with the
 * LCDCA module.
 */
static inline void lcdca_automated_char_stop(void)
{
	/* Disable PDCA channel */
	pdca_channel_disable(LCDCA_AUTOMATED_CHAR_DMA_CH);

	/* Disable automated display */
	LCDCA->LCDCA_ACMCFG &= ~LCDCA_ACMCFG_EN;
}

void lcdca_circular_shift_set_config(struct lcdca_circular_shift_config *cs_cfg);

/**
 * \brief Enable the LCDCA circular shift mode.
 */
static inline void lcdca_circular_shift_enable(void)
{
	/* CSR "on" */
	LCDCA->LCDCA_CR  = LCDCA_CR_CSTART;
}

/**
 * \brief Disable the LCDCA circular shift mode.
 */
static inline void lcdca_circular_shift_disable(void)
{
	/* CSR "off" */
	LCDCA->LCDCA_CR  = LCDCA_CR_CSTOP;
}

void lcdca_write_packet(uint8_t lcd_tdg, uint8_t first_seg,
		const uint8_t *data, size_t width, uint8_t dir);
void lcdca_set_pixel(uint8_t pix_com, uint8_t pix_seg);
void lcdca_clear_pixel(uint8_t pix_com, uint8_t pix_seg);
void lcdca_toggle_pixel(uint8_t pix_com, uint8_t pix_seg);
bool lcdca_get_pixel(uint8_t pix_com, uint8_t pix_seg);

/**
 * \brief Enable the LCDCA wake-up.
 */
static inline void lcdca_enable_wakeup(void)
{
	PM->PM_AWEN |= ((0x1u << PM_AWEN_LCDCA) << PM_AWEN_AWEN_Pos);
	LCDCA->LCDCA_CR = LCDCA_CR_WEN;
}

/**
 * \brief Disable the LCDCA wake-up.
 */
static inline void lcdca_disable_wakeup(void)
{
	LCDCA->LCDCA_CR = LCDCA_CR_WDIS;
	PM->PM_AWEN &= ~((0x1u << PM_AWEN_LCDCA) << PM_AWEN_AWEN_Pos);
}

/**
 * \brief Get the LCDCA status register.
 *
 * \return The LCDCA status register.
 */
static inline uint32_t lcdca_get_status(void)
{
	return LCDCA->LCDCA_SR;
}

/**
 * \brief Clear the LCDCA beginning of frame interrupt status.
 */
static inline void lcdca_clear_status(void)
{
	LCDCA->LCDCA_SCR = LCDCA_SCR_FC0R;
}

void lcdca_set_callback(lcdca_callback_t callback,
		uint8_t irq_line, uint8_t irq_level);

/**
 * \brief Enable the LCDCA beginning of frame interrupt.
 */
static inline void lcdca_enable_interrupt(void)
{
	LCDCA->LCDCA_IER = LCDCA_IER_FC0R;
}

/**
 * \brief Disable the LCDCA beginning of frame interrupt.
 */
static inline void lcdca_disable_interrupt(void)
{
	LCDCA->LCDCA_IDR = LCDCA_IDR_FC0R;
}

#ifdef __cplusplus
}
#endif

 /** @} */

/**
 * \page asfdoc_sam_drivers_lcdca_extra Extra Information for Liquid Crystal Display Controller Driver
 *
 * \section asfdoc_sam_drivers_lcdca_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *  <tr>
 *      <th>Acronym</th>
 *      <th>Definition</th>
 *  </tr>
 *  <tr>
 *      <td>COM</td>
 *      <td>Common</td>
 * </tr>
 *  <tr>
 *      <td>NVIC</td>
 *      <td>Nested Vectored Interrupt Controller</td>
 * </tr>
 *  <tr>
 *      <td>PDCA</td>
 *      <td>Peripheral DMA Controller</td>
 * </tr>
 *  <tr>
 *      <td>PMC</td>
 *      <td>Power Manager Controller</td>
 * </tr>
 *  <tr>
 *      <td>QSG</td>
 *      <td>Quick Start Guide</td>
 * </tr>
 *  <tr>
 *      <td>SEG</td>
 *      <td>Segment</td>
 * </tr>
 * </table>
 *
 *
 * \section asfdoc_sam_drivers_lcdca_extra_dependencies Dependencies
 * This driver has the following dependencies:
 *
 * - \ref asfdoc_sam_drivers_pdca_group "Peripheral DMA Controller (PDCA) driver"
 * - \ref sysclk_group "System clock (sysclk)"
 * - \ref interrupt_group "Interrupt management"
 * - \ref sleepmgr_group "Sleep manager"
 *
 *
 * \section asfdoc_sam_drivers_lcdca_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam_drivers_lcdca_extra_history Module History
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
 * \page asfdoc_sam_drivers_lcdca_exqsg Examples for Liquid Crystal Display Controller
 *
 * This is a list of the available Quick Start Guides (QSGs) and example
 * applications for \ref asfdoc_sam_drivers_lcdca_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that a QSG can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam_drivers_lcdca_qsg
 *  - \subpage asfdoc_sam_drivers_lcdca_example
 *
 * \page asfdoc_sam_drivers_lcdca_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>42296B</td>
 *		<td>07/2015</td>
 *		<td>Updated title of application note and added list of supported devices</td>
 *	</tr>
 *	<tr>
 *		<td>42296A</td>
 *		<td>05/2014</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 *
 */

/**
 * \page asfdoc_sam_drivers_lcdca_qsg Quick Start Guide for the LCDCA Driver
 *
 * This is the quick start guide for the \ref asfdoc_sam_drivers_lcdca_group, with
 * step-by-step instructions on how to configure and use the driver for
 * a specific use case.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, for example, the main application
 * function.
 *
 * \section lcdca_qs_use_cases Use Cases
 * - \ref lcdca_basic
 *
 * \section lcdca_basic LCDCA Basic Usage
 *
 * This use case will demonstrate how to configure and use the LCDCA module
 * to address an external LCD segment (C42048A).
 *
 * \section lcdca_basic_setup Setup Steps
 *
 * \subsection lcdca_basic_prereq Prerequisites
 *
 * This module requires the following services:
 * - \ref clk_group "System clock (sysclk)"
 * - \ref sleepmgr_group "Sleep Manager"
 * - \ref asfdoc_same_drivers_pdca_group "Peripheral DMA Controller (PDCA) driver"
 *
 * \subsection lcdca_basic_setup_code Setup Code Example
 *
 * Add these code segments to the main loop, or to a setup function in your
 * application's C-file:
 * \verbatim
   #define PORT_MASK  40
   #define LCD_DUTY   LCDCA_DUTY_1_4
   #define LCD_CONTRAST_LEVEL 30

   struct lcdca_config lcdca_cfg; \endverbatim
 *
 * \snippet lcdca_example.c lcd_example_init
 *
 * \subsection lcdca_basic_setup_workflow Basic Setup Workflow
 *
 * -# Initialize the LCDCA clock:
 * \snippet lcdca_example.c lcd_example_init_clock
 * -# Configure the LCDCA module:
 * \snippet lcdca_example.c lcd_example_set_config
 * -# Enable the LCDCA module:
 * \snippet lcdca_example.c lcd_example_enable_module
 * -# Enable the frame counter timers:
 * \snippet lcdca_example.c lcd_example_enable_timers
 * -# Turn on the LCD backlight:
 * \snippet lcdca_example.c lcd_example_backlight_on
 *
 * \section lcdca_basic_usage Usage Steps
 *
 * \subsection lcdca_basic_usage_normal Normal Usage
 *
 * The following functions can be used to set/clear/toggle one pixel/segment:
 * \code lcdca_set_pixel(ICON_ARM); \endcode
 * \code lcdca_clear_pixel(ICON_ARM); \endcode
 * \code lcdca_toggle_pixel(ICON_ARM); \endcode
 *
 * The function \ref lcdca_write_packet() can be used to display ASCII
 * characters:
 * \snippet lcdca_example.c lcd_example_write_alphanumeric
 * \snippet lcdca_example.c lcd_example_write_numeric
 *
 * The LCD contrast can be changed using:
 * \code lcdca_set_contrast(contrast_value); \endcode
 *
 * \subsection lcdca_basic_usage_blink Using Hardware Blinking
 * To use hardware blinking:
 * \snippet lcdca_example.c lcd_example_blink_init
 *
 * \subsection lcdca_basic_usage_autonomous Using Hardware Autonomous Animation
 * To use the hardware's autonomous segment animation:
 * \snippet lcdca_example.c lcd_example_shift_enable
 *
 * \subsection lcdca_basic_usage_automated_char Using Hardware Automated Character
 * To use hardware automated character (e.g., scrolling here):
 * \snippet lcdca_example.c lcd_example_scroll_config_1
 * \snippet lcdca_example.c lcd_example_scroll_config_2
 * \snippet lcdca_example.c lcd_example_scrolling_enable
 */

#endif /* LCDCA_H_INCLUDED */
