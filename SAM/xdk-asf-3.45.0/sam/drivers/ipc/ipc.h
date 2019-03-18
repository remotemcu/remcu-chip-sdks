/**
 * \file
 *
 * \brief Interprocessor Communication (IPC) driver for SAM.
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

#ifndef IPC_H_INCLUDED
#define IPC_H_INCLUDED

#include "compiler.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \defgroup sam_drivers_ipc_group IPC - Interprocessor Communication
 *
 * This driver provides a unified interface for the configuration and
 * management of IPC (Interprocessor Communication) module.
 *
 * \{
 */

enum ipc_interrupt_source {
	IPC_INTERRUPT_SRC_IRQ0  = IPC_ISCR_IRQ0,
	IPC_INTERRUPT_SRC_IRQ1  = IPC_ISCR_IRQ1,
	IPC_INTERRUPT_SRC_IRQ2  = IPC_ISCR_IRQ2,
	IPC_INTERRUPT_SRC_IRQ3  = IPC_ISCR_IRQ3,
	IPC_INTERRUPT_SRC_IRQ4  = IPC_ISCR_IRQ4,
	IPC_INTERRUPT_SRC_IRQ5  = IPC_ISCR_IRQ5,
	IPC_INTERRUPT_SRC_IRQ6  = IPC_ISCR_IRQ6,
	IPC_INTERRUPT_SRC_IRQ7  = IPC_ISCR_IRQ7,
	IPC_INTERRUPT_SRC_IRQ8  = IPC_ISCR_IRQ8,
	IPC_INTERRUPT_SRC_IRQ9  = IPC_ISCR_IRQ9,
	IPC_INTERRUPT_SRC_IRQ10 = IPC_ISCR_IRQ10,
	IPC_INTERRUPT_SRC_IRQ11 = IPC_ISCR_IRQ11,
	IPC_INTERRUPT_SRC_IRQ12 = IPC_ISCR_IRQ12,
	IPC_INTERRUPT_SRC_IRQ13 = IPC_ISCR_IRQ13,
	IPC_INTERRUPT_SRC_IRQ14 = IPC_ISCR_IRQ14,
	IPC_INTERRUPT_SRC_IRQ15 = IPC_ISCR_IRQ15,
	IPC_INTERRUPT_SRC_IRQ16 = IPC_ISCR_IRQ16,
	IPC_INTERRUPT_SRC_IRQ17 = IPC_ISCR_IRQ17,
	IPC_INTERRUPT_SRC_IRQ18 = IPC_ISCR_IRQ18,
	IPC_INTERRUPT_SRC_IRQ19 = IPC_ISCR_IRQ19,
	IPC_INTERRUPT_SRC_IRQ20 = IPC_ISCR_IRQ20,
	IPC_INTERRUPT_SRC_IRQ21 = IPC_ISCR_IRQ21,
	IPC_INTERRUPT_SRC_IRQ22 = IPC_ISCR_IRQ22,
	IPC_INTERRUPT_SRC_IRQ23 = IPC_ISCR_IRQ23,
	IPC_INTERRUPT_SRC_IRQ24 = IPC_ISCR_IRQ24,
	IPC_INTERRUPT_SRC_IRQ25 = IPC_ISCR_IRQ25,
	IPC_INTERRUPT_SRC_IRQ26 = IPC_ISCR_IRQ26,
	IPC_INTERRUPT_SRC_IRQ27 = IPC_ISCR_IRQ27,
	IPC_INTERRUPT_SRC_IRQ28 = IPC_ISCR_IRQ28,
	IPC_INTERRUPT_SRC_IRQ29 = IPC_ISCR_IRQ29,
	IPC_INTERRUPT_SRC_IRQ30 = IPC_ISCR_IRQ30,
	IPC_INTERRUPT_SRC_IRQ31 = IPC_ISCR_IRQ31
};

/**
 * \brief Set the specified interrupt(s).
 *
 * \param p_ipc Pointer to an IPC instance.
 * \param mask Bit mask of the interrupt source.
 */
static inline void ipc_set_command(Ipc *p_ipc, uint32_t mask)
{
	p_ipc->IPC_ISCR = mask;
}

/**
 * \brief Clear the specified interrupt(s).
 *
 * \param p_ipc Pointer to an IPC instance.
 * \param mask Bit mask of the interrupt source.
 */
static inline void ipc_clear_command(Ipc *p_ipc, uint32_t mask)
{
	p_ipc->IPC_ICCR = mask;
}

/**
 * \brief Return the pending interrupt(s).
 *
 * \param p_ipc Pointer to an IPC instance.
 *
 * \return Bit mask of the pending interrupt source.
 */
static inline uint32_t ipc_get_pending_interrupt(Ipc *p_ipc)
{
	return p_ipc->IPC_IPR;
}

/**
 * \brief Enable the specified interrupt(s).
 *
 * \param p_ipc Pointer to an IPC instance.
 * \param mask Bit mask of the interrupt source.
 */
static inline void ipc_enable_interrupt(Ipc *p_ipc, uint32_t mask)
{
	p_ipc->IPC_IECR = mask;
}

/**
 * \brief Disable the specified interrupt(s).
 *
 * \param p_ipc Pointer to an IPC instance.
 * \param mask Bit mask of the interrupt source.
 */
static inline void ipc_disable_interrupt(Ipc *p_ipc, uint32_t mask)
{
	p_ipc->IPC_IDCR = mask;
}

/**
 * \brief Return the bit mask of enabled interrupt(s).
 *
 * \param p_ipc Pointer to an IPC instance.
 *
 * \return Bit mask of the enabled interrupt source.
 */
static inline uint32_t ipc_get_interrupt_mask(Ipc *p_ipc)
{
	return p_ipc->IPC_IMR;
}

/**
 * \brief Return the status of interrupt(s).
 *
 * \param p_ipc Pointer to an IPC instance.
 *
 * \return Bit mask of the interrupt status.
 */
static inline uint32_t ipc_get_status(Ipc *p_ipc)
{
	return p_ipc->IPC_ISR;
}

/**
 * \brief Set an interrupt handler for the specified interrput source.
 *
 * \param p_ipc Pointer to an IPC instance.
 * \param ipc_interrupt_source Interrupt source enumeration.
 * \param p_handler Interrupt handler function pointer.
 */
void ipc_set_handler(Ipc *p_ipc, enum ipc_interrupt_source source,
		void (*p_handler) (Ipc *, enum ipc_interrupt_source));

/**
 * \brief Enable the IPC peripheral.
 *
 * \param p_ipc Pointer to an IPC instance.
 */
void ipc_enable(Ipc *p_ipc);

/**
 * \brief Disable the IPC peripheral.
 *
 * \param p_ipc Pointer to an IPC instance.
 */
void ipc_disable(Ipc *p_ipc);

/**
 * \}
 */

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \page sam_ipc_quick_start Quick Start Guide for the IPC driver
 *
 * This is the quick start guide for the \ref sam_drivers_ipc_group, with
 * step-by-step instructions on how to configure and use the driver for
 * a specific use case.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section ipc_qs_use_cases Use Cases
 * - \ref ipc_basic_use_case
 *
 * \section ipc_basic_use_case IPC Basic Use Case
 *
 * This use case will demonstrate how to use the IPC module on SAM4C. In this
 * use case, the IRQ0 of IPC0 is enabled and to toggle the on-board LED (LED0)
 * when it was set by core 1. The interrupt handler is running in core 0.
 *
 * \section ipc_basic_setup Setup Steps
 *
 * \subsection ipc_basic_prereq Prerequisites
 *
 * This module requires the clock service (\ref clk_group). And since 2 cores
 * are used to communicated with each other, the clock of coprocessor must be
 * enabled and configured.
 * \code
 *   #define CONFIG_CPCLK_ENABLE
 *   #define CONFIG_CPCLK_SOURCE        CPCLK_SRC_MCK
 *   #define CONFIG_CPCLK_PRES          1
 * \endcode
 * The code above sets the coprocessor clock as the same as the application
 * processor clock.
 *
 * \subsection ipc_basic_setup_code Setup Code Example
 *
 * Add the following to main function of the application processor program:
 * \code
 *   // Initialize the system
 *   sysclk_init();
 *   board_init();
 *
 *   ipc_enable(IPC0);
 *   ipc_set_handler(IPC0, IPC_INTERRUPT_SRC_IRQ0, ipc_core1_signal_handler);
 *   ipc_enable_interrupt(IPC0, IPC_INTERRUPT_SRC_IRQ0);
 *   NVIC_EnableIRQ(IPC0_IRQn);
 *
 *   // Load the coprocessor program
 *   copy_core1_image_into_sram1();
 *   // Deasserts Coprocessor reset
 *   rstc_deassert_reset_of_coprocessor(RSTC, RSTC_CPMR_CPROCEN);
 *
 *   while (1);
 * \endcode
 * The definition of the callback function ipc_core1_signal_handler, which will
 * toggle the LED0 and clear the IRQ. The function is called by IPC interrupt
 * handler when the corresponding IRQ is set.
 * \code
 *   static void ipc_core1_signal_handler(Ipc *p, enum ipc_interrupt_source mask)
 *   {
 *      LED_Toggle(LED0);
 *      ipc_clear_command(p, mask);
 *   }
 * \endcode
 *
 * \subsection ipc_basic_setup_workflow Basic Setup Workflow
 *
 * -# Enable IPC0 peripheral. Only when it is enabled, all IRQs of it can be
 * enabled then and the callback function for the IRQs can be called.
 *  \code
 *   ipc_enable(IPC0);
 *  \endcode
 *
 * -# Set up the callback function for IRQ0 of IPC0. The callback function must
 * be set before the interrupt is enabled.
 *  \code
 *   ipc_set_handler(IPC0, IPC_INTERRUPT_SRC_IRQ0, ipc_core1_signal_handler);
 *  \endcode
 *
 * -# Enable IRQ0 of IPC0. To receive the interrupt signal correctly, the
 * interrupt for IRQ of IPC as well as the interrupt of IPC itself (controlled
 * by NVIC) must be enabled.
 *  \code
 *   ipc_enable_interrupt(IPC0, IPC_INTERRUPT_SRC_IRQ0);
 *   NVIC_EnableIRQ(IPC0_IRQn);
 *  \endcode
 *
 * \section ipc_basic_usage IPC Basic Usage
 *
 * The IRQ0 of IPC0 has been enabled and the corresponding callback function
 * has been set up in the application core (core 0). To communicate with core 0,
 * the coprocessor core (core 1) shall send the signal to it by setting IRQ0 of
 * IPC0.
 *  \code
 *   ipc_set_command(IPC0, IPC_INTERRUPT_SRC_IRQ0);
 *  \endcode
 * Once ipc_set_command() is called, the handler of IPC is called, in which the
 * callback function for the IRQ will be executed as well. And to clear the
 * IRQ interrupt request set by ipc_set_command(), ipc_clear_command() is
 * available.
 */

#endif /* IPC_H_INCLUDED */
