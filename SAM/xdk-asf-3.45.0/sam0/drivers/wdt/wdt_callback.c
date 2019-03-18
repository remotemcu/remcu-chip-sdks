/**
 * \file
 *
 * \brief SAM Watchdog Driver
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
#include "wdt.h"
#include <system.h>
#include <system_interrupt.h>

wdt_callback_t wdt_early_warning_callback;

/**
 * \brief Registers an asynchronous callback function with the driver.
 *
 * Registers an asynchronous callback with the WDT driver, fired when a
 * given criteria (such as an Early Warning) is met. Callbacks are fired once
 * for each event.
 *
 * \param[in] callback  Pointer to the callback function to register
 * \param[in] type      Type of callback function to register
 *
 * \return Status of the registration operation.
 * \retval STATUS_OK               The callback was registered successfully
 * \retval STATUS_ERR_INVALID_ARG  If an invalid callback type was supplied
 */
enum status_code wdt_register_callback(
		const wdt_callback_t callback,
		const enum wdt_callback type)
{
	/* Sanity check arguments */
	Assert(callback);

	switch (type)
	{
	case WDT_CALLBACK_EARLY_WARNING:
		wdt_early_warning_callback = callback;
		return STATUS_OK;
	default:
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}
}

/**
 * \brief Unregisters an asynchronous callback function with the driver.
 *
 * Unregisters an asynchronous callback with the WDT driver, removing it
 * from the internal callback registration table.
 *
 * \param[in] type  Type of callback function to unregister
 *
 * \return Status of the de-registration operation.
 * \retval STATUS_OK               The callback was Unregistered successfully
 * \retval STATUS_ERR_INVALID_ARG  If an invalid callback type was supplied
 */
enum status_code wdt_unregister_callback(
		const enum wdt_callback type)
{
	switch (type)
	{
	case WDT_CALLBACK_EARLY_WARNING:
		wdt_early_warning_callback = NULL;
		return STATUS_OK;
	default:
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}
}

/**
 * \brief Enables asynchronous callback generation for a given type.
 *
 * Enables asynchronous callbacks for a given callback type. This must be
 * called before an external interrupt channel will generate callback events.
 *
 * \param[in] type  Type of callback function to enable
 *
 * \return Status of the callback enable operation.
 * \retval STATUS_OK               The callback was enabled successfully
 * \retval STATUS_ERR_INVALID_ARG  If an invalid callback type was supplied
 */
enum status_code wdt_enable_callback(
		const enum wdt_callback type)
{
	Wdt *const WDT_module = WDT;

	switch (type)
	{
	case WDT_CALLBACK_EARLY_WARNING:
		WDT_module->INTENSET.reg = WDT_INTENSET_EW;
		system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_WDT);
		return STATUS_OK;
	default:
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}
}

/**
 * \brief Disables asynchronous callback generation for a given type.
 *
 * Disables asynchronous callbacks for a given callback type.
 *
 * \param[in] type  Type of callback function to disable
 *
 * \return Status of the callback disable operation.
 * \retval STATUS_OK               The callback was disabled successfully
 * \retval STATUS_ERR_INVALID_ARG  If an invalid callback type was supplied
 */
enum status_code wdt_disable_callback(
		const enum wdt_callback type)
{
	Wdt *const WDT_module = WDT;

	switch (type)
	{
	case WDT_CALLBACK_EARLY_WARNING:
		WDT_module->INTENCLR.reg = WDT_INTENCLR_EW;
		return STATUS_OK;
	default:
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}
}

/** Handler for the WDT hardware module interrupt. */
void WDT_Handler(void)
{
	wdt_clear_early_warning();

	if (wdt_early_warning_callback) {
		wdt_early_warning_callback();
	}
}
