/**
 * \file
 *
 * \brief EIC driver for SAM
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

#include "eic.h"
#include "sysclk.h"
#include "sleepmgr.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \internal
 * \brief EIC callback function pointer array
 */
eic_callback_t eic_callback_pointer[EIC_NUMBER_OF_LINES];

/**
 * \brief Program the EIC hardware with the specified configuration.
 *
 * \param [in]  eic Base address of the EIC module
 * \param [in]  line_number Number of line to configure
 * \param [in]  eic_line_conf Configuration parameters for the EIC module
 * (see \ref eic_line_config)
 */
void eic_line_set_config(Eic *eic, uint8_t line_number,
	struct eic_line_config *eic_line_conf)
{
		/* Set up mode level */
		eic->EIC_MODE = (eic_line_conf->eic_mode == EIC_MODE_LEVEL_TRIGGERED)
				? (eic->EIC_MODE | (1 << line_number))
				: (eic->EIC_MODE & ~(1 << line_number));
		/* Set up edge type */
		eic->EIC_EDGE = (eic_line_conf->eic_edge == EIC_EDGE_RISING_EDGE)
				? (eic->EIC_EDGE | (1 << line_number))
				: (eic->EIC_EDGE & ~(1 << line_number));
		/* Set up level */
		eic->EIC_LEVEL = (eic_line_conf->eic_level == EIC_LEVEL_HIGH_LEVEL)
				? (eic->EIC_LEVEL | (1 << line_number))
				: (eic->EIC_LEVEL & ~(1 << line_number));
		/* Set up if filter is used */
		eic->EIC_FILTER = (eic_line_conf->eic_filter == EIC_FILTER_ENABLED)
				? (eic->EIC_FILTER | (1 << line_number))
				: (eic->EIC_FILTER & ~(1 << line_number));
		/* Set up which mode is used : asynchronous mode/ synchronous mode */
		eic->EIC_ASYNC = (eic_line_conf->eic_async == EIC_ASYNCH_MODE)
				? (eic->EIC_ASYNC | (1 << line_number))
				: (eic->EIC_ASYNC & ~(1 << line_number));

}

/**
 * \brief Disable the EIC module
 *
 * \param [in]  eic Base address of the EIC module
 */
void eic_disable(Eic *eic)
{
	sysclk_disable_peripheral_clock(eic);
	sleepmgr_unlock_mode(SLEEPMGR_BACKUP);
}

/**
 * \brief Enable the EIC module
 *
 * \param [in]  eic Base address of the EIC module
 */
void eic_enable(Eic *eic)
{
	sysclk_enable_peripheral_clock(eic);
	sleepmgr_lock_mode(SLEEPMGR_BACKUP);
}

/**
 * \brief Set callback for given EIC line
 *
 * \param [in]  eic Base address of the EIC module
 * \param [in]  line_number Number of line
 * \param [in]  callback Callback function pointer
 * \param [in]  irq_line  Interrupt line number (EIC_1_IRQn to EIC_8_IRQn)
 * \param [in]  irq_level Interrupt level (the priority of the interrupt request)
 */
void eic_line_set_callback(Eic *eic, uint8_t line_number,
	eic_callback_t callback, uint8_t irq_line, uint8_t irq_level)
{
	eic_callback_pointer[line_number] = callback;
	irq_register_handler((IRQn_Type)irq_line, irq_level);
	eic_line_enable_interrupt(eic, line_number);
}

/**
 * \internal
 * \brief Common EIC line interrupt handler
 *
 * The optional callback used by the interrupt handler is set by the
 * eic_line_set_callback() function.
 *
 * \param [in]  line_number EIC line number to handle interrupt for
 */
static void eic_line_interrupt(uint8_t line_number)
{
	if (eic_callback_pointer[line_number]) {
		eic_callback_pointer[line_number]();
	} else {
		Assert(false); /* Catch unexpected interrupt */
	}
}

/**
 * \brief Interrupt handler for EIC NMI.
 */
void NMI_Handler(void)
{
	eic_line_interrupt(0);
}

/**
 * \brief Interrupt handler for EIC line 1.
 */
void EIC_1_Handler(void)
{
	eic_line_interrupt(1);
}

/**
 * \brief Interrupt handler for EIC line 2.
 */
void EIC_2_Handler(void)
{
	eic_line_interrupt(2);
}

/**
 * \brief Interrupt handler for EIC line 3.
 */
void EIC_3_Handler(void)
{
	eic_line_interrupt(3);
}

/**
 * \brief Interrupt handler for EIC line 4.
 */
void EIC_4_Handler(void)
{
	eic_line_interrupt(4);
}

/**
 * \brief Interrupt handler for EIC line 5.
 */
void EIC_5_Handler(void)
{
	eic_line_interrupt(5);
}

/**
 * \brief Interrupt handler for EIC line 6.
 */
void EIC_6_Handler(void)
{
	eic_line_interrupt(6);
}

/**
 * \brief Interrupt handler for EIC line 7.
 */
void EIC_7_Handler(void)
{
	eic_line_interrupt(7);
}

/**
 * \brief Interrupt handler for EIC line 8.
 */
void EIC_8_Handler(void)
{
	eic_line_interrupt(8);
}


/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
