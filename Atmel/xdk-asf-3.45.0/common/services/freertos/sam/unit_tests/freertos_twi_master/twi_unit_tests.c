/**
 * \file
 *
 * \brief Unit tests for FreeRTOS TWI Interface Layer.
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
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <twi.h>
#include <conf_test.h>
#include <conf_board.h>
#include <conf_example.h>
#include "FreeRTOS.h"
#include "task.h"
#include "freertos_twi_master.h"
#include "at24cxx.h"

/*-----------------------------------------------------------*/

/* Clock speed to use. */
#define TWI_CLOCK_HZ                    400000

/* The size of the EEPROM in bytes. */
#define TOTAL_EEPROM_SIZE               65536

/* The size of each page in the EEPROM. */
#define PAGE_SIZE                       128

/* The maximum time the EEPROM takes to commit its RAM buffer. */
#define INTERNAL_WRITE_DELAY            (7 / portTICK_RATE_MS)

/*-----------------------------------------------------------*/

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the FreeRTOS TWI Interface Layer.
 * It consists of test cases for the following functionality:
 * - Data read/write on TWI bus using FreeRTOS Interface Layer
 *
 * \section files Main Files
 * - \ref twi_unit_tests.c
 * - \ref FreeRTOSConfig.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_example.h
 * - \ref conf_twi_master.h
 * - \ref conf_test.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * All SAM devices can be used.
 * This example has been tested with the following setup:
 * - sam3x8h_sam3x_ek
 * - sam4c16c_sam4c_ek
 *
 * Note: this unit test takes about 20 seconds to finish.
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

/* ! \name Unit test configuration */
/* @{ */

/**
 * \def twi_test
 * \brief Init, read and write on AT25 using FreeRTOS TWI Interface Layer.
 */
/* @} */

static void run_twi_test(const struct test_case *test);
static void create_twi_task(Twi *twi_base, uint16_t stack_depth_words,
		unsigned portBASE_TYPE task_priority);
static void twi_eeprom_task(void *pvParameters);
static void write_page_to_eeprom(uint16_t page);
static void read_page_from_eeprom(uint16_t page);

/* A buffer large enough to hold a complete page of data. */
static uint8_t data_buffer[PAGE_SIZE];
/* Used to latch errors found during the execution of the example. */
static uint32_t error_detected = pdFALSE;
/* TWI instance */
static freertos_twi_if freertos_twi;

/*
 * Sets up the hardware ready to run this example.
 */
static void prvSetupHardware(void);

/*
 * FreeRTOS hook (or callback) functions that are defined in this file.
 */
void vApplicationMallocFailedHook(void);
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(xTaskHandle pxTask,
		signed char *pcTaskName);
void vApplicationTickHook(void);

/**
 * \brief Run TWI unit tests
 */
int main(void)
{
	/* Prepare the hardware to run this demo. */
	prvSetupHardware();

	/* Create the test task. */
	create_twi_task(BOARD_BASE_TWI_EEPROM, 1024, tskIDLE_PRIORITY);

	/* Start the RTOS scheduler. */
	vTaskStartScheduler();

	/* If all is well, the scheduler will now be running, and the following line
	will never be reached.  If the following line does execute, then there was
	insufficient FreeRTOS heap memory available for the idle and/or timer tasks
	to be created.  See the memory management section on the FreeRTOS web site
	for more details. */
	for (;;) {
	}
}

static void create_twi_task(Twi *twi_base, uint16_t stack_depth_words,
		unsigned portBASE_TYPE task_priority)
{
	const freertos_peripheral_options_t blocking_driver_options = {
	NULL,											/* This peripheral does not need a receive buffer, so this parameter is just set to NULL. */
	0,												/* There is no Rx buffer, so the rx buffer size is not used. */
	configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY,	/* The priority used by the TWI interrupts. */
	TWI_I2C_MASTER,									/* Communicating with the EEPROM requires the TWI to be configured as an I2C master. */
	(USE_TX_ACCESS_SEM | USE_RX_ACCESS_MUTEX | WAIT_TX_COMPLETE | WAIT_RX_COMPLETE)	/* The blocking driver is to be used, so WAIT_TX_COMPLETE and WAIT_RX_COMPLETE are set. */
};

	/* Initialize the FreeRTOS driver for blocking operation.  The
	peripheral clock is configured in this function call. */
	freertos_twi = freertos_twi_master_init(twi_base,
			&blocking_driver_options);

	/* Check the port was initialized successfully. */
	configASSERT(freertos_twi);

	/* Configure the TWI bus parameters.  Do this after calling
	freertos_twi_master_init(). */
	twi_set_speed(twi_base, TWI_CLOCK_HZ, sysclk_get_cpu_hz());

	/* Create the task as described above. */
	xTaskCreate(twi_eeprom_task, (const signed char *const) "Tx",
			stack_depth_words, (void *) freertos_twi, task_priority,
			NULL);
}

/*-----------------------------------------------------------*/

static void twi_eeprom_task(void *pvParameters)
{
	UNUSED(pvParameters);
	/* Define all the test cases */
	DEFINE_TEST_CASE(twi_test, NULL, run_twi_test, NULL,
			"FreeRTOS TWI init-read-write on EEPROM");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(twi_tests) = {
		&twi_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(twi_suite, twi_tests,
			"SAM FreeRTOS TWI Interface Layer test suite");

	/* Run all tests in the test suite */
	test_suite_run(&twi_suite);

	/* Delete task */
	vTaskDelete(NULL);
}

/*-----------------------------------------------------------*/

static void run_twi_test(const struct test_case *test)
{
	portBASE_TYPE page;
	const portBASE_TYPE max_page = TOTAL_EEPROM_SIZE / PAGE_SIZE;
	size_t byte_in_page;
	uint8_t byte_value;

	/* Fill the EEPROM with 0xaa, one page at a time. */
	memset(data_buffer, 0xaa, PAGE_SIZE);
	for (page = 0; page < max_page; page++) {
		write_page_to_eeprom(page);
	}

	/* Check that the data is read back from the EEPROM as 0xaa.  First make
	sure that the buffer contains a value other than 0xaa to be sure that it
	does not coincidentally already hold the expected data. */
	for (page = 0; page < max_page; page++) {
		memset((void *) data_buffer, 0xff, PAGE_SIZE);
		read_page_from_eeprom(page);

		/* Check each byte in the page is as expected. */
		for (byte_in_page = 0; byte_in_page < PAGE_SIZE;
				byte_in_page++) {
			if (data_buffer[byte_in_page] != 0xaa) {
				error_detected = pdTRUE;
			}
		}
	}

	/* Check Test1. */
	test_assert_true(test, error_detected == pdFALSE,
			"Test1: read/write test failed!");

	/* Fill the EEPROM with 0x55, one page at a time. */
	memset(data_buffer, 0x55, PAGE_SIZE);
	for (page = 0; page < max_page; page++) {
		write_page_to_eeprom(page);
	}

	/* Check that the data is read back from the EEPROM as 0x55.  First make
	sure that the buffer contains a value other than 0x55 to be sure that it
	does not coincidentally already hold the expected data. */
	for (page = 0; page < max_page; page++) {
		memset((void *) data_buffer, 0xff, PAGE_SIZE);
		read_page_from_eeprom(page);

		/* Check each byte in the page is as expected. */
		for (byte_in_page = 0; byte_in_page < PAGE_SIZE;
				byte_in_page++) {
			if (data_buffer[byte_in_page] != 0x55) {
				error_detected = pdTRUE;
			}
		}
	}

	/* Check Test2. */
	test_assert_true(test, error_detected == pdFALSE,
			"Test2: read/write test failed!");

	/* Fill the EEPROM using different values in each position (the value
	 * will wrap). */
	byte_value = 0;
	for (page = 0; page < max_page; page++) {
		for (byte_in_page = 0; byte_in_page < PAGE_SIZE;
				byte_in_page++) {
			data_buffer[byte_in_page] = byte_value;
			byte_value++;
		}

		write_page_to_eeprom(page);
	}

	/* Check each byte read back matches that expected once more. */
	byte_value = 0;
	for (page = 0; page < max_page; page++) {
		memset((void *) data_buffer, 0x00, PAGE_SIZE);
		read_page_from_eeprom(page);

		/* Check each byte in the page is as expected. */
		for (byte_in_page = 0; byte_in_page < PAGE_SIZE;
				byte_in_page++) {
			if (data_buffer[byte_in_page] != byte_value) {
				error_detected = pdTRUE;
			}

			byte_value++;
		}
	}

	/* Check Test3. */
	test_assert_true(test, error_detected == pdFALSE,
			"Test3: read/write test failed!");
}

/*-----------------------------------------------------------*/

static void write_page_to_eeprom(uint16_t page)
{
	twi_packet_t write_parameters;
	uint16_t calculated_address;
	const portTickType max_block_time_ticks = 200UL / portTICK_RATE_MS;

	write_parameters.chip = BOARD_AT24C_ADDRESS;
	write_parameters.buffer = data_buffer;
	write_parameters.length = PAGE_SIZE;

	/* The internal EEPROM address being written to is calculated from the page
	number. */
	calculated_address = page * PAGE_SIZE;
	write_parameters.addr[0] = (uint8_t) ((calculated_address >> 8) & 0xff);
	write_parameters.addr[1] = (uint8_t) (calculated_address & 0xff);
	write_parameters.addr_length = 2;

	/* The blocking API is being used.  Other tasks will execute while the
	write operation is in progress. */
	if (freertos_twi_write_packet(freertos_twi, &write_parameters,
			max_block_time_ticks) != STATUS_OK) {
		error_detected = pdTRUE;
	}

	/* Wait for the EEPROM to complete programming its internal memory.
	Note this is a very crude way of doing this, the EEPROM status
	register could be polled to determine when it was finished. */
	vTaskDelay(INTERNAL_WRITE_DELAY);
}

/*-----------------------------------------------------------*/

static void read_page_from_eeprom(uint16_t page)
{
	twi_packet_t read_parameters;
	uint16_t calculated_address;
	const portTickType max_block_time_ticks = 200UL / portTICK_RATE_MS;

	read_parameters.chip = BOARD_AT24C_ADDRESS;
	read_parameters.buffer = data_buffer;
	read_parameters.length = PAGE_SIZE;

	/* The internal EEPROM address being read from is calculated from the page
	number. */
	calculated_address = page * PAGE_SIZE;
	read_parameters.addr[0] = (uint8_t) ((calculated_address >> 8) & 0xff);
	read_parameters.addr[1] = (uint8_t) (calculated_address & 0xff);
	read_parameters.addr_length = 2;

	/* The blocking API is being used.  Other tasks will execute while the
	 * read operation is in progress. */
	if (freertos_twi_read_packet(freertos_twi, &read_parameters,
			max_block_time_ticks) != STATUS_OK) {
		error_detected = pdTRUE;
	}
}

/*-----------------------------------------------------------*/

static void prvSetupHardware(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.paritytype = CONF_TEST_PARITY
	};

	/* ASF function to setup clocking. */
	sysclk_init();

	/* Ensure all priority bits are assigned as preemption priority bits. */
	NVIC_SetPriorityGrouping(0);

	/* Atmel library function to setup for the evaluation kit being used. */
	board_init();
	/* Reset TWI EEPROM state to release TWI */
	at24cxx_reset();

	/* Enable unit test output peripheral. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);
}

/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook(void)
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
	for (;;) {
	}
}

/*-----------------------------------------------------------*/

void vApplicationIdleHook(void)
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(xTaskHandle pxTask,
		signed char *pcTaskName)
{
	(void) pcTaskName;
	(void) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for (;;) {
	}
}

/*-----------------------------------------------------------*/

void vApplicationTickHook(void)
{
	/* This function will be called by each tick interrupt if
	configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
	added here, but the tick hook is called from an interrupt context, so
	code must not attempt to block, and only the interrupt safe FreeRTOS API
	functions can be used (those that end in FromISR()). */
}
