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

#include "ipc.h"
#include <status_codes.h>
#include <sysclk.h>

#define IPC_MAX_INTERRUPT_SOURCES  32
#define NB_IPC  2

/**
 * Describes an IPC interrupt handler, including the IPC interrupt source and
 * the associated handler.
 */
struct ipc_interrupt_handler {
	enum ipc_interrupt_source mask;
	void (*handler) (Ipc *, enum ipc_interrupt_source);
};

static struct ipc_interrupt_handler ipc_handler[NB_IPC][IPC_MAX_INTERRUPT_SOURCES];

/**
 * \brief Process an interrupt request on the given IPC.
 *
 * \param p_ipc Pointer to an IPC instance.
 */
static void ipc_handler_process(Ipc *p_ipc)
{
	uint32_t status, i, ipc;
	(p_ipc == IPC0) ? (ipc = 0) : (ipc = 1);

	/* Read IPC interrupt status */
	status = ipc_get_status(p_ipc);
	status &= ipc_get_interrupt_mask(p_ipc);

	/* Check pending events */
	if (status != 0) {
		/* Find triggering source */
		i = 0;
		while ((status != 0) && (i < IPC_MAX_INTERRUPT_SOURCES)) {
			if ((status & ipc_handler[ipc][i].mask) != 0) {
				ipc_handler[ipc][i].handler(p_ipc, ipc_handler[ipc][i].mask);
				status &= ~(ipc_handler[ipc][i].mask);
			}
			i++;
		}
	}
}

/**
 * \brief Set an interrupt handler for the specified interrput source.
 *
 * \param p_ipc Pointer to an IPC instance.
 * \param source Interrupt source enumeration.
 * \param p_handler Interrupt handler function pointer.
 */
void ipc_set_handler(Ipc *p_ipc, enum ipc_interrupt_source source,
		void (*p_handler) (Ipc *, enum ipc_interrupt_source))
{
	struct ipc_interrupt_handler *pSource;
	uint32_t i = 0;

	while (!(source & (1 << i))) {
		i++;
	}
	/* Define new source */
	if (p_ipc == IPC0) {
		pSource = &(ipc_handler[0][i]);
	} else {
		pSource = &(ipc_handler[1][i]);
	}

	pSource->mask = source;
	pSource->handler = p_handler;
}

/**
 * \brief Enable the IPC peripheral.
 *
 * \param p_ipc Pointer to an IPC instance.
 */
void ipc_enable(Ipc *p_ipc)
{
	if (p_ipc == IPC0) {
		sysclk_enable_peripheral_clock(ID_IPC0);
	} else {
		sysclk_enable_peripheral_clock(ID_IPC1);
	}
}

/**
 * \brief Disable the IPC peripheral.
 *
 * \param p_ipc Pointer to an IPC instance.
 */
void ipc_disable(Ipc *p_ipc)
{
	if (p_ipc == IPC0) {
		sysclk_disable_peripheral_clock(ID_IPC0);
	} else {
		sysclk_disable_peripheral_clock(ID_IPC1);
	}
}

/**
 * \brief IPC0 interrupt handler.
 * Redefined IPC0 interrupt handler for NVIC interrupt table.
 */
void IPC0_Handler(void)
{
	ipc_handler_process(IPC0);
}

/**
 * \brief IPC1 interrupt handler.
 * Redefined IPC1 interrupt handler for NVIC interrupt table.
 */
void IPC1_Handler(void)
{
	ipc_handler_process(IPC1);
}
