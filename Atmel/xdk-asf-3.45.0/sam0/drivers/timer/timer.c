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
#include "timer.h"

static timer_callback_t timer_callback;
/**
 * \brief Initializes config with predefined default values.
 *
 * This function will initialize a given TIMER configuration structure to
 * a set of known default values. This function should be called on
 * any new instance of the configuration structures before being
 * modified by the user application.
 *
 * The default configuration is as follows:
 *  \li Timer interrupt set as disable
 *  \li Set relaod value as 0
 *
 * \param[out]  config  Pointer to a TIMER module configuration structure to set
 */
void timer_get_config_defaults(struct timer_config *config)
{
	config->reload_value = 0;
	config->interrupt_enable = true;
}


/**
 * \brief Get TIMER0 module current value.
 *
 * \retval Current value
 */
uint32_t timer_get_value(void)
{
	return TIMER0->VALUE.reg;
}

/**
 * \brief Set TIMER0 module value.
 *
 * \param[in]     value        Reload value
 */
void timer_set_value(uint32_t value)
{
	TIMER0->RELOAD.reg = value;
}

/**
 * \brief Get TIMER0 module interrupt status
 *
 * \retval The status of module
 */
uint32_t timer_get_interrupt_status(void)
{
	return TIMER0->INTSTATUSCLEAR.reg;
}

/**
 * \brief Clear TIMER0 module interrupt status
 *
 * Clear the TIMER0 module interrupt status
 */
void timer_clear_interrupt_status(void)
{
	TIMER0->INTSTATUSCLEAR.reg = 1;
	/* Wait for operation finish */
	while (TIMER0->INTSTATUSCLEAR.reg);
}

/**
 * \brief Set TIMER0 module enable
 *
 * Enable the TIMER0 module
 */
void timer_enable(void)
{
	TIMER0->CTRL.reg |= TIMER_CTRL_ENABLE;
}

/**
 * \brief Set TIMER0 disable
 *
 * Disable the TIMER0 module
 */
void timer_disable(void)
{
	TIMER0->CTRL.reg &= (~TIMER_CTRL_ENABLE);
}

/**
 * \brief Registers a callback.
 *
 * Registers and enable a callback function which is implemented by the user.
 *
 * \param[in]     callback_func Pointer to callback function
 */
void timer_register_callback(timer_callback_t fun)
{
	timer_callback = fun; 
}

/**
 * \brief Unregisters a callback.
 *
 * Unregisters and disable a callback function implemented by the user.
 *
 */
void timer_unregister_callback(void)
{
	timer_callback = NULL; 
}

/**
 * \brief Timer ISR handler.
 *
 * Timer ISR handler.
 *
 */
static void timer_isr_handler(void)
{
	if (timer_get_interrupt_status()) {
		timer_clear_interrupt_status();
		
		if (timer_callback) {
			timer_callback();
		}
	}
}

/**
 * \brief Initializes TIMER0 module instance.
 *
 * Initializes the TIMER0 module, based on the given
 * configuration values.
 *
 * \param[in]     config       Pointer to the TIMER configuration options struct
 *
 * \return Status of the initialization procedure.
 */
void timer_init(const struct timer_config *config)
{
	/* Global reset */
	system_peripheral_reset(PERIPHERAL_TIMER);

	TIMER0->CTRL.reg = config->interrupt_enable << TIMER_CTRL_INTERRUPT_ENABLE_Pos;
	TIMER0->RELOAD.reg = config->reload_value;
	
	timer_callback = NULL;
	system_register_isr(RAM_ISR_TABLE_TIMER0_INDEX, (uint32_t)timer_isr_handler);
}