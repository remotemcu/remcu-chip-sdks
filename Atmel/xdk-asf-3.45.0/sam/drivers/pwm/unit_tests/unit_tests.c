/**
 * \file
 *
 * \brief Unit tests for PWM driver.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

#include <stdint.h>
#include <stdbool.h>
#include <board.h>
#include <sysclk.h>
#include <pwm.h>
#include <pdc.h>
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include <conf_board.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the PWM driver.
 * It consists of test cases for the following functionality:
 * - PWM period interrupt
 * - PWM comparison interrupt
 * - PWM PDC transfer interrupt
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * All SAM devices can be used.
 * This example has been tested with the following setup:
 * - sam3n4c_sam3n_ek
 * - sam3s4c_sam3s_ek
 * - sam3sd8c_sam3s_ek2
 * - sam3u4e_sam3u_ek
 * - sam3x8h_sam3x_ek
 * - sam4s16c_sam4s_ek
 * - sam4sd32c_sam4s_ek2
 * - sam4sd32c_atpl230amb
 * - sam4n16c_sam4n_xplained_pro
 * - sam4c16c_sam4c_ek
 * - sam4cmp16c_sam4cmp_db
 * - sam4cms16c_sam4cms_db
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

//! \name Unit test configuration
//@{
/**
 * \def CONF_TEST_PWM
 * \brief Start PWM, check period, comparison and PDC transfer interrupt.
 */
//@}

/** PWM frequency in Hz */
#define PWM_FREQUENCY  50
/** PWM period value */
#define PERIOD_VALUE   50

/** PDC transfer packet */
pdc_packet_t g_pdc_tx_packet;

/* Changed when a PWM period interrupt happens */
static volatile int32_t gs_l_pwm_period_int_flag = 0U;

#if (SAM3U || SAM3S || SAM3XA || SAM4S)
/* Changed when a PWM comparison interrupt happens */
static volatile int32_t gs_l_pwm_comparison_int_flag = 0U;

/* Changed when a PWM PDC transfer interrupt happens */
static volatile int32_t gs_l_pwm_pdc_tx_int_flag = 0U;
#endif /* (SAM3N) */

/* Systick Counter */
static volatile uint32_t gs_ul_ms_ticks = 0U;

/**
 * \brief PWM interrupt handler.
 */
void PWM_Handler(void)
{
	gs_l_pwm_period_int_flag = pwm_channel_get_interrupt_status(PWM) &
			(1 << PWM_UNIT_TEST_CH);

#if (SAM3U || SAM3S || SAM3XA || SAM4S)
	uint32_t status2 = pwm_get_interrupt_status(PWM);
	gs_l_pwm_comparison_int_flag = (status2 >> 8) & (1 << PWM_UNIT_TEST_CMP);
	gs_l_pwm_pdc_tx_int_flag = status2 & PWM_ISR2_ENDTX;
#endif
}


/**
 * \brief SysTick handler.
 */
void SysTick_Handler(void)
{
	/* Increment counter necessary in delay(). */
	gs_ul_ms_ticks++;
}

/**
 * \brief Delay number of tick Systicks (happens every 1 ms).
 */
static void delay_ms(uint32_t ul_dly_ticks)
{
	uint32_t ul_cur_ticks;

	ul_cur_ticks = gs_ul_ms_ticks;
	while ((gs_ul_ms_ticks - ul_cur_ticks) < ul_dly_ticks) {
	}
}

/**
 * \brief Test PWM setting
 *
 * This test sets the PWM APIs.
 *
 * \param test Current test case.
 */
static void run_pwm_test(const struct test_case *test)
{
	/* Enable PWM interrupt line from the core */
	NVIC_DisableIRQ(PWM_IRQn);
	NVIC_ClearPendingIRQ(PWM_IRQn);
	NVIC_SetPriority(PWM_IRQn, 4);
	NVIC_EnableIRQ(PWM_IRQn);

	/* Enable PWMC peripheral clock */
	pmc_enable_periph_clk(ID_PWM);

	/* Disable PWM channel */
	pwm_channel_disable(PWM, PWM_UNIT_TEST_CH);

	/* Set PWM clock A as PWM_FREQUENCY*PERIOD_VALUE (clock B is not used) */
	pwm_clock_t test_clock = {
		.ul_clka = PWM_FREQUENCY * PERIOD_VALUE,
		.ul_clkb = 0,
		.ul_mck = sysclk_get_cpu_hz()
	};
	pwm_init(PWM, &test_clock);

	/* Test1 */
	/* Configure PWM channel */
	pwm_channel_t test_channel = {
		/* Use PWM clock A as source clock */
		.ul_prescaler = PWM_CMR_CPRE_CLKA,
		/* Period value */
		.ul_period = PERIOD_VALUE,
	};

	/* Initialize PWM channel */
	test_channel.channel = PWM_UNIT_TEST_CH;
	pwm_channel_init(PWM, &test_channel);

	/* Enable PWM channel */
	pwm_channel_enable(PWM, PWM_UNIT_TEST_CH);

	/*
	 * Enable PWM channel event interrupt and wait for PWM to trigger
	 * a period interrupt after PERIOD_VALUE.
	 */
	pwm_channel_enable_interrupt(PWM, PWM_UNIT_TEST_CH, 0);
	delay_ms(50);
	test_assert_true(test, gs_l_pwm_period_int_flag != 0,
			"Test1: No period interrupt triggered!");
	/* Disable event interrupt and PWM channel */
	pwm_channel_disable_interrupt(PWM, PWM_UNIT_TEST_CH, 0);
	pwm_channel_disable(PWM, PWM_UNIT_TEST_CH);

#if (SAM3U || SAM3S || SAM3XA || SAM4S)
	/* Test2 */

	/* Configure comparison unit */
	pwm_cmp_t comparison_unit = {
		/* Use PWM_UNIT_TEST_CMP as comparison unit */
		.unit =  PWM_UNIT_TEST_CMP,
		/* Enable the comparison unit */
		.b_enable = 1,
		/* Comparison value = Period value - 1 */
		.ul_value = PERIOD_VALUE - 1
	};

	/* Initialize PWM comparison unit */
	pwm_cmp_init(PWM, &comparison_unit);

	/* Initialize PWM channel */
	test_channel.channel = PWM_UNIT_TEST_CH;
	pwm_channel_init(PWM, &test_channel);

	pwm_cmp_enable_interrupt(PWM, PWM_UNIT_TEST_CMP, PWM_CMP_MATCH);

	/* Enable PWM channel */
	pwm_channel_enable(PWM, PWM_UNIT_TEST_CH);

	/*
	 * Wait for PWM to trigger a comparison match interrupt
	 * after PERIOD_VALUE - 1.
	 */
	delay_ms(50);
	test_assert_true(test, gs_l_pwm_comparison_int_flag != 0,
			"Test2: No comparison match interrupt triggered!");

	/* Test3 */
	/* Disable PWM channel */
	pwm_cmp_disable_interrupt(PWM, PWM_UNIT_TEST_CMP, PWM_CMP_MATCH);
	pwm_channel_disable(PWM, PWM_UNIT_TEST_CH);

	/* Initialize PWM channel */
	test_channel.channel = PWM_UNIT_TEST_CH;
	pwm_channel_init(PWM, &test_channel);

	/*
	 * Initialize PWM synchronous channels
	 * Synchronous Update Mode: Automatic update duty cycle value by the PDC
	 * and automatic update of synchronous channels. The update occurs when
	 * the Update Period is elapsed (MODE 2).
	 * Synchronous Update Period = 1.
	 */
	pwm_sync_init(PWM, PWM_SYNC_UPDATE_MODE_2, 1);

	/*
	 * Request PDC transfer as soon as the synchronous update period is
	 * elapsed (comparison unit is ignored).
	 */
	pwm_pdc_set_request_mode(PWM, PWM_PDC_UPDATE_PERIOD_ELAPSED,
			PWM_UNIT_TEST_CMP);

	/* Configure the PDC transfer packet and enable PDC transfer */
	g_pdc_tx_packet.ul_addr = (uint32_t)(&gs_ul_ms_ticks);
	g_pdc_tx_packet.ul_size = 1;
	pdc_tx_init(PDC_PWM, &g_pdc_tx_packet, 0);
	pwm_pdc_enable_interrupt(PWM, PWM_IER2_ENDTX);
	pdc_enable_transfer(PDC_PWM, PERIPH_PTCR_TXTEN);

	/* Enable PWM channel */
	pwm_channel_enable(PWM, PWM_UNIT_TEST_CH);

	/* Wait for PWM to trigger a PDC transfer end interrupt */
	delay_ms(100);
	test_assert_true(test, gs_l_pwm_pdc_tx_int_flag != 0,
			"Test3: No PDC transfer end interrupt triggered!");
	/* Disable PWM channel */
	pwm_channel_disable(PWM, PWM_UNIT_TEST_CH);
#endif /* (SAM3N) */
}

/**
 * \brief Run PWM driver unit tests
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.paritytype = CONF_TEST_PARITY
	};

	sysclk_init();
	board_init();

	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Set up SysTick Timer for 1 msec interrupts. */
	if (SysTick_Config(sysclk_get_cpu_hz() / 1000)) {
		/* Capture error. */
		while (1) {
		}
	}

	/* Define all the test cases */
	DEFINE_TEST_CASE(pwm_test, NULL, run_pwm_test, NULL,
		"PWM period, comparison and PDC transfer");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(pwm_tests) = {
		&pwm_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(pwm_suite, pwm_tests, "SAM PWM driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&pwm_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
