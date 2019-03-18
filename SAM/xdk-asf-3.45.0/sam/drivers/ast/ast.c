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

#include "ast.h"
#include "sysclk.h"
#include "sleepmgr.h"
#include "conf_ast.h"

/**
 * \internal AST callback function pointer array
 */
ast_callback_t ast_callback_pointer[AST_INTERRUPT_SOURCE_NUM];

/**
 * \brief Check the status of the AST module.
 *
 * \param[in,out] ast Module hardware register base address pointer
 *
 * \retval false AST is not enabled
 * \retval true  AST is enabled
 */
bool ast_is_enabled(
		Ast *ast)
{
	while (ast_is_busy(ast)) {
	}
	return ((ast->AST_CR & AST_CR_EN) != 0);
}

/**
 * \brief Enable the AST module.
 *
 * \param[in] ast Module hardware register base address pointer
 */
void ast_enable(
		Ast *ast)
{
	sysclk_enable_peripheral_clock(ast);
	sleepmgr_lock_mode(SLEEPMGR_BACKUP);
}

/**
 * \brief Disable the AST counter and module.
 *
 * \param[in,out] ast Module hardware register base address pointer
 */
void ast_disable(
		Ast *ast)
{
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}
	/* Disable the AST */
	ast->AST_CR &= ~(AST_CR_EN);
	/* Wait until write is done */
	while (ast_is_busy(ast)) {
	}

	sysclk_disable_peripheral_clock(ast);
	sleepmgr_unlock_mode(SLEEPMGR_BACKUP);
}

/**
 * \brief Enable the option to clear the counter on an AST alarm.
 *
 * \param[in,out] ast        Module hardware register base address pointer
 * \param[in] alarm_channel  AST Alarm Channel
 */
void ast_enable_counter_clear_on_alarm(
		Ast *ast,
		uint8_t alarm_channel)
{
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}
	/* Enable Clear Counter on Alarm */
	ast->AST_CR
		|= (alarm_channel ? 0 : AST_CR_CA0);
	/* Wait until write is done */
	while (ast_is_busy(ast)) {
	}
}

/**
 * \brief Clear the AST periodic prescaler counter to zero.
 *
 * \param[in,out] ast Module hardware register base address pointer
 */
void ast_clear_prescalar(
		Ast *ast)
{
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}
	/* Clear Counter on Alarm */
	ast->AST_CR |= AST_CR_PCLR;
	/* Wait until write is done */
	while (ast_is_busy(ast)) {
	}
}

/**
 * \brief Initialize and enable the AST module in Calendar Mode or Counter Mode.
 *
 * \note  If you use the 32kHz oscillator it will be enabled by this function.
 *
 * \param[in,out] ast  Module hardware register base address pointer
 * \param[in] ast_conf AST configuration structure pointer
 *
 * \return Initialization result.
 * \retval 0 Initialization failed due to a software timeout
 * \retval 1 Initialization succeeded
*/
uint32_t ast_set_config(
		Ast *ast,
		struct ast_config *ast_conf)
{
	uint32_t time_out = AST_POLL_TIMEOUT;
	while (ast_is_clkbusy(ast)) {
		if (--time_out == 0) {
			return 0;
		}
	}
	ast->AST_CLOCK = ast_conf->osc_type << AST_CLOCK_CSSEL_Pos;
	time_out = AST_POLL_TIMEOUT;
	while (ast_is_clkbusy(ast)) {
		if (--time_out == 0) {
			return 0;
		}
	}
	ast->AST_CLOCK |= AST_CLOCK_CEN;
	time_out = AST_POLL_TIMEOUT;
	while (ast_is_clkbusy(ast)) {
		if (--time_out == 0) {
			return 0;
		}
	}
	/* Set the new AST configuration */
	if (ast_conf->mode == AST_CALENDAR_MODE) {
		ast->AST_CR = AST_CR_CAL | ast_conf->psel << AST_CR_PSEL_Pos;
	}

	if (ast_conf->mode == AST_COUNTER_MODE) {
		ast->AST_CR = ast_conf->psel << AST_CR_PSEL_Pos;
	}

	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}

	/* Set the calendar */
	if (ast_conf->mode == AST_CALENDAR_MODE) {
		ast_write_calendar_value(ast, ast_conf->calendar);
	}

	if (ast_conf->mode == AST_COUNTER_MODE) {
		ast_write_counter_value(ast, ast_conf->counter);
	}

	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}
	/* Enable the AST */
	ast->AST_CR |= AST_CR_EN;
	/* Wait until write is done */
	while (ast_is_busy(ast)) {
	}

	return 1;
}

/**
 * \brief Tune the AST prescaler frequency to the desired frequency.
 *
 * \note Refer to the section entitled "digital tuner" in the ast chapter of the
 * device-specific datasheet for more information.
 *
 * \param[in,out] ast     Module hardware register base address pointer
 * \param[in] input_freq  Prescaled AST Clock Frequency
 * \param[in] tuned_freq  Desired AST frequency
 */
uint32_t ast_configure_digital_tuner(
		Ast *ast,
		uint32_t input_freq,
		uint32_t tuned_freq)
{
	bool add;
	uint8_t value;
	uint8_t exp;
	uint32_t x, y, z;
	uint32_t diff;
	if (tuned_freq < input_freq) {
		/* Check for Frequency Limit */
		if (tuned_freq < ((4 * input_freq) / 5)) {
			return 0;
		}

		/* Set the ADD to 0 when freq less than input freq */
		add = false;
		/* Calculate the frequency difference */
		diff = input_freq - tuned_freq;
	} else if (tuned_freq > input_freq) {
		/* Check for Frequency Limit */
		if (tuned_freq > ((4 * input_freq) / 3)) {
			return 0;
		}

		/* Set the ADD to 1 when freq greater than input freq */
		add = true;
		/* Calculate the frequency difference */
		diff = tuned_freq - input_freq;
	} else {
		/* required & input freq are equal */
		return 1;
	}

	z = (tuned_freq) / (diff);
	if ((tuned_freq % diff) > (diff / 2)) {
		z++;
	}

	/*
	 * Initialize with minimum possible values.
	 * exp value should be greater than zero, min(exp) = 1 -> min(x)= (2^1)
	 * = 2
	 * y should be greater than one -> div_ceil(256/value) where value- 0 to
	 * 255
	 * min(y) = div_ceil(256/255) = 2
	 */
	y = 2;
	x = 2;
	exp = 1;

	/*
	 * Keep exp constant and increase y value until it reaches its limit.
	 * Increment exp and follow the same steps until we found the closest
	 * possible match for the required frequency.
	 */
	do {
		if (y < 255) {
			y++;
		} else {
			x = x << 1;
			y = 2;
			exp++;
		}
	} while (z > (x * y));
	/* Decrement y value after exit from loop */
	y = y - 1;
	/* Find VALUE from y */
	value = div_ceil(256, y);
	/* Initialize the Digital Tuner using the required parameters */
	ast_init_digital_tuner(ast, add, value, exp);
	return 1;
}

/**
 * \brief Initialize the AST digital tuner.
 *
 * \param[in,out] ast Module hardware register base address pointer
 * \param[in] add     Set to true if the frequency needs to be increased, false if it
 *                    has to be decreased.
 * \param[in] value   Parameter used in the formula
 * \param[in] exp     Parameter used in the formula
 */
void ast_init_digital_tuner(
		Ast *ast,
		bool add,
		uint8_t value,
		uint8_t exp)
{
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}

	if (add) {
		ast->AST_DTR = AST_DTR_ADD | AST_DTR_VALUE(value) | AST_DTR_EXP(
				exp);
	} else {
		ast->AST_DTR = AST_DTR_VALUE(value) | AST_DTR_EXP(exp);
	}

	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}
}

/**
 * \brief Disable the AST digital tuner.
 *
 * \param[in,out] ast Module hardware register base address pointer
 */
void ast_disable_digital_tuner(
		Ast *ast)
{
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}
	ast->AST_DTR &= ~(AST_DTR_VALUE_Msk);
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}
}

/**
 * \brief Set the AST current calendar value.
 *
 * \param[in,out] ast  Module hardware register base address pointer
 * \param[in] calendar Startup date structure
 */
void ast_write_calendar_value(
		Ast *ast,
		struct ast_calendar calendar)
{
	/* Wait until we can write into the VAL register */
	while (ast_is_busy(ast)) {
	}
	/* Set the new value */
	ast->AST_CALV = calendar.field;
	/* Wait until write is done */
	while (ast_is_busy(ast)) {
	}
}

/**
 * \brief Set the AST current counter value.
 *
 * \param[in,out] ast     Module hardware register base address pointer
 * \param[in] ast_counter Startup counter value
 */
void ast_write_counter_value(
		Ast *ast,
		uint32_t ast_counter)
{
	/* Wait until we can write into the VAL register */
	while (ast_is_busy(ast)) {
	}
	/* Set the new val value */
	ast->AST_CV = ast_counter;
	/* Wait until write is done */
	while (ast_is_busy(ast)) {
	}
}

/**
 * \brief Get the AST current calendar value.
 *
 * \note There maybe a compiler warning about returning a structure type
 * value, however it is safe because ast_calendar is actually uint32_t type.
 *
 * \param[in] ast Module hardware register base address pointer
 *
 * \return The AST current calendar value.
 */
struct ast_calendar ast_read_calendar_value(
		Ast *ast)
{
	struct ast_calendar calendar;
	calendar.field = ast->AST_CALV;
	return calendar;
}

/**
 * \brief Set the AST alarm0 value.
 *
 * \param[in,out] ast     Module hardware register base address pointer
 * \param[in] alarm_value AST alarm0 value
 */
void ast_write_alarm0_value(
		Ast *ast,
		uint32_t alarm_value)
{
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}
	/* Set the new alarm0 compare value */
	ast->AST_AR0 = alarm_value;
	/* Wait until write is done */
	while (ast_is_busy(ast)) {
	}
}

/**
 * \brief Set the AST periodic0 value.
 *
 * \param[in,out] ast Module hardware register base address pointer
 * \param[in] pir     AST periodic0
 */
void ast_write_periodic0_value(
		Ast *ast,
		uint32_t pir)
{
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}
	/* Set the periodic prescaler value */
	ast->AST_PIR0 = pir;
	/* Wait until write is done */
	while (ast_is_busy(ast)) {
	}
}

/**
 * \brief Enable an AST interrupt.
 *
 * \param[in,out] ast Module hardware register base address pointer
 * \param[in] source  AST interrupt source to be enabled
 */
void ast_enable_interrupt(
		Ast *ast,
		ast_interrupt_source_t source)
{
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}

	switch (source) {
	case AST_INTERRUPT_ALARM:
		ast->AST_IER = AST_IER_ALARM0_1;
		break;

	case AST_INTERRUPT_PER:
		ast->AST_IER = AST_IER_PER0_1;
		break;

	case AST_INTERRUPT_OVF:
		ast->AST_IER = AST_IER_OVF_1;
		break;

	case AST_INTERRUPT_READY:
		ast->AST_IER = AST_IER_READY_1;
		break;

	case AST_INTERRUPT_CLKREADY:
		ast->AST_IER = AST_IER_CLKRDY_1;
		break;

	default:
		break;
	}

	/* Wait until write is done */
	while (ast_is_busy(ast)) {
	}
}

/**
 * \brief Disable an AST interrupt.
 *
 * \param[in,out] ast Module hardware register base address pointer
 * \param[in] source  AST interrupt source to be disabled
 */
void ast_disable_interrupt(
		Ast *ast,
		ast_interrupt_source_t source)
{
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}

	switch (source) {
	case AST_INTERRUPT_ALARM:
		ast->AST_IDR = AST_IDR_ALARM0_1;
		break;

	case AST_INTERRUPT_PER:
		ast->AST_IDR = AST_IDR_PER0_1;
		break;

	case AST_INTERRUPT_OVF:
		ast->AST_IDR = AST_IDR_OVF_1;
		break;

	case AST_INTERRUPT_READY:
		ast->AST_IDR = AST_IDR_READY_1;
		break;

	case AST_INTERRUPT_CLKREADY:
		ast->AST_IDR = AST_IDR_CLKRDY_1;
		break;

	default:
		break;
	}

	/* Wait until write is done */
	while (ast_is_busy(ast)) {
	}
}

/**
 * \brief Clear an AST interrupt status flag.
 *
 * \param[in,out] ast Module hardware register base address pointer
 * \param[in] source  AST interrupt source for which the status is to be cleared
 */
void ast_clear_interrupt_flag(
		Ast *ast,
		ast_interrupt_source_t source)
{
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}

	switch (source) {
	case AST_INTERRUPT_ALARM:
		ast->AST_SCR = AST_SCR_ALARM0;
		break;

	case AST_INTERRUPT_PER:
		ast->AST_SCR = AST_SCR_PER0;
		break;

	case AST_INTERRUPT_OVF:
		ast->AST_SCR = AST_SCR_OVF;
		break;

	case AST_INTERRUPT_READY:
		ast->AST_SCR = AST_SCR_READY;
		break;

	case AST_INTERRUPT_CLKREADY:
		ast->AST_SCR = AST_SCR_CLKRDY;
		break;

	default:
		break;
	}

	/* Wait until write is done */
	while (ast_is_busy(ast)) {
	}
}

/**
 * \brief Set callback for AST interrupts.
 *
 * \param[in,out] ast   Module hardware register base address pointer
 * \param[in] source    AST interrupt source
 * \param[in] callback  Callback function pointer
 * \param[in] irq_line  Interrupt line
 * \param[in] irq_level Interrupt level
 */
void ast_set_callback(
		Ast *ast,
		ast_interrupt_source_t source,
		ast_callback_t callback,
		uint8_t irq_line,
		uint8_t irq_level)
{
	ast_callback_pointer[source] = callback;
	NVIC_ClearPendingIRQ((IRQn_Type)irq_line);
	NVIC_SetPriority((IRQn_Type)irq_line, irq_level);
	NVIC_EnableIRQ((IRQn_Type)irq_line);
	ast_enable_interrupt(ast, source);
}

/**
 * \brief Interrupt handler for AST periodic.
 */
#if defined(AST_PER_ENABLE) || defined(__DOXYGEN__)
void AST_PER_Handler(void)
{
	ast_callback_pointer[AST_INTERRUPT_PER]();
}
#endif /* AST_PER_ENABLE || defined(__DOXYGEN__) */

/**
 * \brief Interrupt handler for AST alarm.
 */
#if defined(AST_ALARM_ENABLE) || defined(__DOXYGEN__)
void AST_ALARM_Handler(void)
{
	ast_callback_pointer[AST_INTERRUPT_ALARM]();
}
#endif /* AST_ALARM_ENABLE || defined(__DOXYGEN__) */

/**
 * \brief Interrupt handler for AST periodic.
 */
#if defined(AST_OVF_ENABLE) || defined(__DOXYGEN__)
void AST_OVF_Handler(void)
{
	ast_callback_pointer[AST_INTERRUPT_OVF]();
}
#endif /* AST_OVF_ENABLE || defined(__DOXYGEN__) */

/**
 * \brief Interrupt handler for AST alarm.
 */
#if defined(AST_READY_ENABLE)  || defined(__DOXYGEN__)
void AST_READY_Handler(void)
{
	ast_callback_pointer[AST_INTERRUPT_READY]();
}
#endif /* AST_READY_ENABLE  || defined(__DOXYGEN__) */

/**
 * \brief Interrupt handler for AST periodic.
 */
#if defined(AST_CLKREADY_ENABLE)  || defined(__DOXYGEN__)
void AST_CLKREADY_Handler(void)
{
	ast_callback_pointer[AST_INTERRUPT_CLKREADY]();
}
#endif /* AST_CLKREADY_ENABLE  || defined(__DOXYGEN__) */

/**
 * \brief Enable an AST asynchronous wake-up source.
 *
 * \param[in,out] ast Module hardware register base address pointer
 * \param[in] source  AST wake-up source to be enabled
 */
void ast_enable_wakeup(
		Ast *ast,
		ast_wakeup_source_t source)
{
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}

	switch (source) {
	case AST_WAKEUP_ALARM:
		ast->AST_WER |= AST_WER_ALARM0_1;
		break;

	case AST_WAKEUP_PER:
		ast->AST_WER |= AST_WER_PER0_1;
		break;

	case AST_WAKEUP_OVF:
		ast->AST_WER |= AST_WER_OVF_1;
		break;

	default:
		break;
	}

	/* Wait until write is done */
	while (ast_is_busy(ast)) {
	}
}

/**
 * \brief Disable an AST asynchronous wake-up source.
 *
 * \param[in,out] ast Module hardware register base address pointer
 * \param[in] source  AST wake-up source to be disabled
 */
void ast_disable_wakeup(
		Ast *ast,
		ast_wakeup_source_t source)
{
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}

	switch (source) {
	case AST_WAKEUP_ALARM:
		ast->AST_WER &= ~AST_WER_ALARM0_1;
		break;

	case AST_WAKEUP_PER:
		ast->AST_WER &= ~AST_WER_PER0_1;
		break;

	case AST_WAKEUP_OVF:
		ast->AST_WER &= ~AST_WER_OVF_1;
		break;

	default:
		break;
	}

	/* Wait until write is done */
	while (ast_is_busy(ast)) {
	}
}

/**
 * \brief Enable an AST event.
 *
 * \param[in,out] ast Module hardware register base address pointer
 * \param[in] source  AST event source to be enabled
 */
void ast_enable_event(
		Ast *ast,
		ast_event_source_t source)
{
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}

	switch (source) {
	case AST_EVENT_ALARM:
		ast->AST_EVE = AST_EVE_ALARM0;
		break;

	case AST_EVENT_PER:
		ast->AST_EVE = AST_EVE_PER0;
		break;

	case AST_EVENT_OVF:
		ast->AST_EVE = AST_EVE_OVF;
		break;

	default:
		break;
	}

	/* Wait until write is done */
	while (ast_is_busy(ast)) {
	}
}

/**
 * \brief Disable an AST event.
 *
 * \param[in,out] ast Module hardware register base address pointer
 * \param[in] source  AST event source to be disabled
 */
void ast_disable_event(
		Ast *ast,
		ast_event_source_t source)
{
	/* Wait until the ast CTRL register is up-to-date */
	while (ast_is_busy(ast)) {
	}

	switch (source) {
	case AST_EVENT_ALARM:
		ast->AST_EVD = AST_EVD_ALARM0;
		break;

	case AST_EVENT_PER:
		ast->AST_EVD = AST_EVD_PER0;
		break;

	case AST_EVENT_OVF:
		ast->AST_EVD = AST_EVD_OVF;
		break;

	default:
		break;
	}

	/* Wait until write is done */
	while (ast_is_busy(ast)) {
	}
}
