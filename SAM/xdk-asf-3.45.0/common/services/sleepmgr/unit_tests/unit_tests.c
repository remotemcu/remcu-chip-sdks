/**
 * \file
 *
 * \brief Unit tests for MegaRF Sleep Manager driver
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

#include <asf.h>
#include <conf_test.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test for the MEGARF Sleep Manager. After setting the lock
 * mode, the device is put into sleep and check whether the device has slept in
 * the deepest allowable sleep mode. This is checked by enabling ADC and
 * Timer/Counter2 and verify device is waked up by the interrupts.
 * First the device is put to idle sleep and check whether ADC conversion
 * complete interrupt is waking the device from sleep. Then the device is set
 * into Power Save mode and check only Timer/Counter2 is only able to wake the
 * device from sleep.
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 * - \ref conf_sleepmgr.h
 *
 * \section device_info Device Info
 * This example has been tested with the following setup(s):
 * - atmega128rfa1_stk600-rc128x_rfx 
 * - atmega256rfr2_xplained_pro
 *
 * \section description Description of the unit tests
 * See the documentation for the individual unit test functions
 * \ref unit_tests.c "here" for detailed descriptions of the tests.
 *
 * \section dependencies Dependencies
 * This example depends directly on the following modules:
 * - \ref test_suite_group
 * - \ref megarf_usart_group
 * - \ref megarf_sleep_group
 * - \ref megarf_adc_group
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for AVR. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 */

 //! \name Unit test configuration
//@{
/**
 * \def CONF_TEST_USART
 * \brief USART to redirect STDIO to
 */
/**
 * \def CONF_TEST_BAUDRATE
 * \brief Baudrate of USART
 */
/**
 * \def CONF_TEST_CHARLENGTH
 * \brief Character length (bits) of USART
 */
/**
 * \def CONF_TEST_PARITY
 * \brief Parity mode of USART
 */
/**
 * \def CONF_TEST_STOPBITS
 * \brief Stop bit configuration of USART
 */
//@}

/* ADC Initialization */
static void adc_initialisation(void);

/* Timer/Counter2 Initialization */
static void timer2_initialisation(void);

/* Variable for trigger counter **/
static volatile uint8_t trigger_count = 0;

/* ADC Conversion complete ISR */
ISR(ADC_vect)
{
	/* Clear ADC conversion interrupt flag */
	ADCSRA = (1 << ADIF);
	/* Increment trigger count */
	trigger_count++;
}


/* Timer/Counter2 Overflow ISR */
ISR(TIMER2_OVF_vect)
{
	/* Clear Timer Overflow flag */
	TIFR2 |= (1 << TOV2);
	/* Increment trigger count */
	trigger_count++;
}

/* Initialize ADC */
static void adc_initialisation()
{
	/* Enable a peripherals clock */
	sysclk_enable_peripheral_clock(&ADC);
	/* set prescaler and enable ADC */
	adc_init(ADC_PRESCALER_DIV128);
	/* set voltage reference, mux input and right adjustment */
	adc_set_admux(ADC_VREF_AVCC | ADC_MUX_ADC0 | ADC_ADJUSTMENT_RIGHT);
	adc_enable_interrupt();
}

/* Timer/Counter2 Initialization */
static void timer2_initialisation()
{
	sysclk_enable_peripheral_clock(&TCCR2A);
	/* Set TC2 in Asynchronous mode */
	TIMSK2 =  0x00;
	ASSR   =  (1 << AS2);
	TCNT2  =  0x00;
	TCCR2A =  0x00;
	TCCR2B =  0x00;
	OCR2A  =  0x00;
	TIMSK2 |= (1 << TOIE2);
	/* divide clock by 128 to get 1s interrupt */
	TCCR2B |= ((1 << CS20) | (1 << CS22));
	/* wait for TCCR2B to update */
	while (ASSR & (1 << TCR2BUB)) {
	}
}

/**
 * \brief Test interrupt is getting triggered in various Sleep mode.
 *
 * This function put the device in Idle and Power Save sleep mode and check
 * whether the ADC conversion complete interrupt is executed only in Idle sleep
 * mode.
 * The device will wakeup from power save mode when Timer/Counter2 overflow
 * occur.
 *
 * \param test Current test case.
 */
static void run_sleep_trigger_test(const struct test_case *test)
{
	/* Disable Global interrupt */
	cpu_irq_disable();
	/* Initialize the lock counts */
	sleepmgr_init();
	/* Initialize the ADC */
	adc_initialisation();
	/* Initialize the Timer/Counter2 */
	timer2_initialisation();
	/* Lock Idle Sleep mode */
	sleepmgr_lock_mode(SLEEPMGR_IDLE);
	/* Clear Timer/Counter2 Register */
	TCNT2 = 0;
	/* Wait for TCNT2 register to get updated */
	while (ASSR & (1 << TCN2UB)) {
	}
	/* Start ADC Conversion */
	adc_start_conversion();
	/* Enable Global interrupt */
	cpu_irq_enable();
	/* Go to sleep in the deepest allowed mode */
	sleepmgr_enter_sleep();
	/* Unlock Idle Sleep mode */
	sleepmgr_unlock_mode(SLEEPMGR_IDLE);
	/* Lock Power Save mode */
	sleepmgr_lock_mode(SLEEPMGR_PSAVE);
	/* Clear Timer/Counter2 Register */
	TCNT2 = 0;
	/* Wait for TCNT2 register to get updated */
	while (ASSR & (1 << TCN2UB)) {
	}
	/* Start ADC Conversion */
	adc_start_conversion();
	/* Go to sleep in the deepest allowed mode */
	sleepmgr_enter_sleep();
	/* Disable ADC */
	adc_disable();
	/* Unlock Power Save mode */
	sleepmgr_unlock_mode(SLEEPMGR_PSAVE);

	/* Disable Global interrupt */
	cpu_irq_disable();

	test_assert_true(test, trigger_count == 2,
			"ADC interrupt trigger failed.");
}

/**
 * \brief Test different parameters of the Sleep Manager module
 *
 * This function locks & unlocks the different sleep modes, and verifies that
 * the correct values are being set.
 *
 * \param test Current test case.
 */
static void run_set_functions_test(const struct test_case *test)
{
	volatile enum sleepmgr_mode sleep_mode;

	/* Initialize the lock counts */
	sleepmgr_init();

	/* Lock Power Down mode */
	sleepmgr_lock_mode(SLEEPMGR_PDOWN);
	/* get the deepest allowable sleep mode */
	sleep_mode = sleepmgr_get_sleep_mode();
	test_assert_true(test, sleep_mode == SLEEPMGR_PDOWN,
			"Trying to lock Power Down mode failed.");

	/* Lock Power Save mode */
	sleepmgr_lock_mode(SLEEPMGR_PSAVE);
	/* get the deepest allowable sleep mode */
	sleep_mode = sleepmgr_get_sleep_mode();
	test_assert_true(test, sleep_mode == SLEEPMGR_PSAVE,
			"Trying to lock Power Save mode failed.");

	/* Lock Idle Sleep mode */
	sleepmgr_lock_mode(SLEEPMGR_IDLE);
	/* get the deepest allowable sleep mode */
	sleep_mode = sleepmgr_get_sleep_mode();
	test_assert_true(test, sleep_mode == SLEEPMGR_IDLE,
			"Trying to lock Idle Sleep mode failed.");

	/* Unlock Idle Sleep mode */
	sleepmgr_unlock_mode(SLEEPMGR_IDLE);
	/* get the deepest allowable sleep mode */
	sleep_mode = sleepmgr_get_sleep_mode();
	test_assert_true(test, sleep_mode == SLEEPMGR_PSAVE,
			"Trying to unlock Idle Sleep mode failed.");

	/* Unlock Power Save mode */
	sleepmgr_unlock_mode(SLEEPMGR_PSAVE);
	/* get the deepest allowable sleep mode */
	sleep_mode = sleepmgr_get_sleep_mode();
	test_assert_true(test, sleep_mode == SLEEPMGR_PDOWN,
			"Trying to unlock Power Save Sleep mode failed.");

	/* Unlock Power Down mode */
	sleepmgr_unlock_mode(SLEEPMGR_PDOWN);
	/* get the deepest allowable sleep mode */
	sleep_mode = sleepmgr_get_sleep_mode();
	test_assert_true(test, sleep_mode == (SLEEPMGR_NR_OF_MODES - 1),
			"Trying to unlock Power Down mode failed.");
}

/**
 * \brief Run Sleep Manager unit tests
 *
 * Initializes the clock system, board and serial output, then sets up the
 * Sleep Manager unit test suite and runs it.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS,
	};

	board_init();
	sysclk_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	DEFINE_TEST_CASE(sleep_trigger_test, NULL, run_sleep_trigger_test, NULL,
			"Test sleep interrupt is getting triggered");
	DEFINE_TEST_CASE(set_functions_test, NULL, run_set_functions_test, NULL,
			"Test setting of various lock modes");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(sleep_manager_tests) = {
		&set_functions_test,
		&sleep_trigger_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(sleep_manager_suite, sleep_manager_tests,
			"MEGARF SLEEP MANAGER test suite");

	/* Run all tests in the suite */
	test_suite_run(&sleep_manager_suite);

	while (1) {
		/* Intentionally left empty. */
	}
}
