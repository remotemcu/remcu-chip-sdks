/**
 * \file
 *
 * \brief SAM AON Sleep Timer Driver for SAMB11
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
#include "aon_sleep_timer.h"

#define AON_SLEEP_TIMER_CONTROL_SLP_TIMER_SINGLE_COUNT_ENABLE_DLY_BIT14_Msk (0x4u << AON_SLEEP_TIMER_CONTROL_SLP_TIMER_SINGLE_COUNT_ENABLE_DLY_Pos)
#define AON_SLEEP_TIMER_CONTROL_SLP_TIMER_CLK_RELOAD_DLY_BIT9_Msk (0x2u << AON_SLEEP_TIMER_CONTROL_SLP_TIMER_CLK_RELOAD_DLY_Pos)

static aon_sleep_timer_callback_t aon_sleep_timer_callback = NULL;

static void delay_cycle(uint32_t cycles)
{
	volatile uint32_t i = 0;

	for (i = 0; i < cycles*100; i++) {
		asm volatile ("nop");
	}
}

/**
 * \brief Initializes config with predefined default values.
 *
 * This function will initialize a given AON Sleep Timer configuration structure to
 * a set of known default values. This function should be called on
 * any new instance of the configuration structures before being
 * modified by the user application.
 *
 * \param[out]  config  Pointer to a AON Sleep Timer module configuration structure to set
 */
void aon_sleep_timer_get_config_defaults(struct aon_sleep_timer_config *config)
{
	/* Default configuration values */
	config->wakeup = AON_SLEEP_TIMER_WAKEUP_ARM;
	config->mode = AON_SLEEP_TIMER_SINGLE_MODE;
	config->counter = 32000;
}

/**
 * \brief Disable AON Sleep Timer module instance.
 *
 * AON Sleep Timer module instance disable.
 */
void aon_sleep_timer_disable(void)
{
	uint32_t regval;

	AON_SLEEP_TIMER0->SINGLE_COUNT_DURATION.reg = 0;
	regval = AON_SLEEP_TIMER0->CONTROL.reg;
	regval &= ~AON_SLEEP_TIMER_CONTROL_RELOAD_ENABLE;
	regval &= ~AON_SLEEP_TIMER_CONTROL_SINGLE_COUNT_ENABLE;
	AON_SLEEP_TIMER0->CONTROL.reg = regval;

	while ((AON_SLEEP_TIMER0->CONTROL.reg & AON_SLEEP_TIMER_CONTROL_SLP_TIMER_SINGLE_COUNT_ENABLE_DLY_BIT14_Msk) || \
	(AON_SLEEP_TIMER0->CONTROL.reg & AON_SLEEP_TIMER_CONTROL_SLP_TIMER_CLK_RELOAD_DLY_BIT9_Msk)) {
	}

	/* Reset the AON Timer to reset the current counter value to zero immediately */
	system_peripheral_aon_reset(PERIPHERAL_AON_SLEEP_TIMER);
}

/**
 * \brief Get AON Sleep Timer module instance current value.
 *
 * \retval Current value
 */
uint32_t aon_sleep_timer_get_current_value(void)
{
	return AON_SLEEP_TIMER0->CURRENT_COUNT_VALUE.reg;
}

/**
 * \brief If AON Sleep Timer is active
 *
 * \return Active status of the AON Sleep Timer.
 */
bool aon_sleep_timer_sleep_timer_active(void)
{
	return AON_SLEEP_TIMER0->CONTROL.bit.SLEEP_TIMER_ACTIVE;
}

/**
 * \brief Clear AON Sleep Timer module instance interrupt.
 *
 * This flag will be cleared automatically once the IRQ
 * has been seen on the sleep clock.
 */
void aon_sleep_timer_clear_interrupt(void)
{
	AON_SLEEP_TIMER0->CONTROL.reg |= AON_SLEEP_TIMER_CONTROL_IRQ_CLEAR;
}

/**
 * \brief Registers a callback.
 *
 * Registers the user callback and enables the interrupt
 *
 * \param[in]     callback_func Pointer to callback function
 */
void aon_sleep_timer_register_callback(aon_sleep_timer_callback_t fun)
{
	aon_sleep_timer_callback = fun;

	NVIC_EnableIRQ(AON_SLEEP_TIMER0_IRQn);
}

/**
 * \brief Unregisters a callback.
 *
 * Unregisters the user callback and disables the interrupt.
 *
 */
void aon_sleep_timer_unregister_callback(void)
{
	NVIC_DisableIRQ(AON_SLEEP_TIMER0_IRQn);

	aon_sleep_timer_callback = NULL;
}

/**
 * \brief Timer ISR handler.
 *
 * Timer ISR handler.
 *
 */
static void aon_sleep_timer_isr_handler(void)
{
	aon_sleep_timer_clear_interrupt();

	if (aon_sleep_timer_callback) {
		aon_sleep_timer_callback();
	}
}

/**
 * \brief Initializes AON Sleep Timer module instance.
 *
 * Initializes the AON Sleep Timer module, based on the parameters,
 * and start timer.
 *
 * \param[in]     config       Pointer to the AON Sleep Timer configuration options struct
 *
 */
void aon_sleep_timer_init(const struct aon_sleep_timer_config *config)
{
	uint32_t aon_st_ctrl = 0;

	AON_PWR_SEQ0->AON_ST_WAKEUP_CTRL.reg = AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_RESETVALUE;
	if (config->wakeup == AON_SLEEP_TIMER_WAKEUP_ARM_BLE) {
		AON_PWR_SEQ0->AON_ST_WAKEUP_CTRL.reg |=
				AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_ARM_ENABLE |
				AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_BLE_ENABLE;
	} else if (config->wakeup == AON_SLEEP_TIMER_WAKEUP_ARM) {
		AON_PWR_SEQ0->AON_ST_WAKEUP_CTRL.reg &=
				~AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_BLE_ENABLE;
		AON_PWR_SEQ0->AON_ST_WAKEUP_CTRL.reg |=
				AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_ARM_ENABLE;
	}

	system_clock_peripheral_aon_enable(PERIPHERAL_AON_SLEEP_TIMER);

	aon_st_ctrl = AON_SLEEP_TIMER0->CONTROL.reg;
	while (aon_st_ctrl & ~(AON_SLEEP_TIMER_CONTROL_SLEEP_TIMER_NOT_ACTIVE_Msk)) {
		AON_SLEEP_TIMER0->CONTROL.reg = 0;
		delay_cycle(3);
		while (aon_st_ctrl & ((config->mode == AON_SLEEP_TIMER_RELOAD_MODE) ?
				(AON_SLEEP_TIMER_CONTROL_SLP_TIMER_CLK_RELOAD_DLY_BIT9_Msk) : (AON_SLEEP_TIMER_CONTROL_SLP_TIMER_SINGLE_COUNT_ENABLE_DLY_BIT14_Msk))) {
			aon_st_ctrl = AON_SLEEP_TIMER0->CONTROL.reg;
		}
		aon_st_ctrl = AON_SLEEP_TIMER0->CONTROL.reg;
	}

	if (config->mode == AON_SLEEP_TIMER_RELOAD_MODE) {
		/* Reload counter will start here */
		AON_SLEEP_TIMER0->SINGLE_COUNT_DURATION.reg = config->counter;
		AON_SLEEP_TIMER0->CONTROL.reg = AON_SLEEP_TIMER_CONTROL_RELOAD_ENABLE;
	} else {
		/* Single counter will start here */
		AON_SLEEP_TIMER0->SINGLE_COUNT_DURATION.reg = config->counter;
		AON_SLEEP_TIMER0->CONTROL.reg = AON_SLEEP_TIMER_CONTROL_SINGLE_COUNT_ENABLE;
	}

	if (config->mode == AON_SLEEP_TIMER_SINGLE_MODE) {
		while ((AON_SLEEP_TIMER0->CONTROL.reg &
				AON_SLEEP_TIMER_CONTROL_SLP_TIMER_SINGLE_COUNT_ENABLE_DLY_Msk)
				!= AON_SLEEP_TIMER_CONTROL_SLP_TIMER_SINGLE_COUNT_ENABLE_DLY_Msk) {
		}
	}

	if (config->mode == AON_SLEEP_TIMER_RELOAD_MODE) {
		while ((AON_SLEEP_TIMER0->CONTROL.reg &
				AON_SLEEP_TIMER_CONTROL_SLP_TIMER_CLK_RELOAD_DLY_Msk)
				!= AON_SLEEP_TIMER_CONTROL_SLP_TIMER_CLK_RELOAD_DLY_Msk) {
		}
	}

	system_register_isr(RAM_ISR_TABLE_AON_SLEEP_TIMER_INDEX, (uint32_t)aon_sleep_timer_isr_handler);
}
