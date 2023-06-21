/**
 * \file
 *
 * \brief Unit tests for FreeRTOS USART Interface Layer.
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
#include <usart.h>
#include <conf_test.h>
#include <conf_board.h>
#include <conf_example.h>
#include "FreeRTOS.h"
#include "task.h"
#include "freertos_usart_serial.h"

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the FreeRTOS USART Interface Layer.
 * It consists of test cases for the following functionality:
 * - Data read/write on USART bus using FreeRTOS Interface Layer
 *
 * \section files Main Files
 * - \ref usart_unit_tests.c
 * - \ref FreeRTOSConfig.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_example.h
 * - \ref conf_test.h
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
 * - sam4c16c_sam4c_ek
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
 * \def usart_test
 * \brief Init, read and write using FreeRTOS USART Interface Layer in loopback
 * mode.
 */
/* @} */

/* The size of the buffer used to receive characters from the USART driver.
 * This equals the length of the longest string used in this file. */
#define RX_BUFFER_SIZE          (78)

/* The baud rate to use. */
#define USART_BAUD_RATE         (115200)

/*-----------------------------------------------------------*/

static void create_usart_tasks(Usart *usart_base, uint16_t stack_depth_words,
		unsigned portBASE_TYPE task_priority);
static void usart_task(void *pvParameters);
static void run_usart_test(const struct test_case *test);
static void usart_echo_tx_task(void *pvParameters);

/*-----------------------------------------------------------*/

/* The buffer provided to the USART driver to store incoming character in. */
static uint8_t receive_buffer[RX_BUFFER_SIZE] = {0};
/* USART instance */
static freertos_usart_if freertos_usart;
/* The array of strings that are sent by the Tx task, and therefore received by
the Rx task. */
const uint8_t *echo_strings[] =
{
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#=+",
	(uint8_t *) "a",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#=+",
	(uint8_t *) "b",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#=+",
	(uint8_t *) "c",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#=+",
	(uint8_t *) "d",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#=+",
	(uint8_t *) "e",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#=+",
	(uint8_t *) "f",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#=+",
	(uint8_t *) "g",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#=+",
	(uint8_t *) "h",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#=+",
	(uint8_t *) "i",
	(uint8_t *) "j",
	(uint8_t *) "k",
	(uint8_t *) "l",
	(uint8_t *) "m",
	(uint8_t *) "n",
	(uint8_t *) "o",
	(uint8_t *) "p",
	(uint8_t *) "q",
	(uint8_t *) "r",
	(uint8_t *) "s",
	(uint8_t *) "t",
	(uint8_t *) "u",
	(uint8_t *) "v",
	(uint8_t *) "w",
	(uint8_t *) "x",
	(uint8_t *) "w",
	(uint8_t *) "z",
	(uint8_t *) "ab",
	(uint8_t *) "abc",
	(uint8_t *) "bcde",
	(uint8_t *) "bcdef",
	(uint8_t *) "bcdefg",
	(uint8_t *) "bcdefgh",
	(uint8_t *) "bcdefghi",
	(uint8_t *) "bcdefghij",
	(uint8_t *) "bcdefghijk",
	(uint8_t *) "bcdefghijkl",
	(uint8_t *) "bcdefghijklm",
	(uint8_t *) "bcdefghijklmn",
	(uint8_t *) "bcdefghijklmno",
	(uint8_t *) "bcdefghijklmnop",
	(uint8_t *) "bcdefghijklmnopq",
	(uint8_t *) "bcdefghijklmnopqr",
	(uint8_t *) "bcdefghijklmnopqrs",
	(uint8_t *) "bcdefghijklmnopqrst",
	(uint8_t *) "bcdefghijklmnopqrstu",
	(uint8_t *) "bcdefghijklmnopqrstuv",
	(uint8_t *) "bcdefghijklmnopqrstuvw",
	(uint8_t *) "bcdefghijklmnopqrstuvwx",
	(uint8_t *) "bcdefghijklmnopqrstuvwxy",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz12",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz123",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz12345",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz123456",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz12345678",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz123456789",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890A",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890AB",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABC",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCD",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDE",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEF",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFG",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGH",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHI",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJ",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJK",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKL",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLM",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMN",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNO",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOP",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQ",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQR",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRS",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRST",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTU",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUV",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVW",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWX",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXW",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ12",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ123",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ12345",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ123456",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ12345678",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ123456789",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[]",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#=",
	(uint8_t *) "bcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#=+",
	(uint8_t *) "_cdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#=+",
	(uint8_t *) "__defghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#=+",
	(uint8_t *) "___efghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#=+",
	(uint8_t *) "____fghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#=+",
	(uint8_t *) "_____ghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXWZ1234567890[];'#=+",
};

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
 * \brief Run USART unit tests
 */
int main(void)
{
	/* Prepare the hardware to run this demo. */
	prvSetupHardware();

	/* Create the test task. */
	create_usart_tasks(BOARD_USART, 1024, tskIDLE_PRIORITY);

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

static void create_usart_tasks(Usart *usart_base, uint16_t stack_depth_words,
		unsigned portBASE_TYPE task_priority)
{
	freertos_peripheral_options_t driver_options = {
		receive_buffer,									/* The buffer used internally by the USART driver to store incoming characters. */
		RX_BUFFER_SIZE,									/* The size of the buffer provided to the USART driver to store incoming characters. */
		configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY,	/* The priority used by the USART interrupts. */
		USART_RS232,									/* Configure the USART for RS232 operation. */
		(USE_TX_ACCESS_SEM | USE_RX_ACCESS_MUTEX)
	};

	const sam_usart_opt_t usart_settings = {
		USART_BAUD_RATE,
		US_MR_CHRL_8_BIT,
		US_MR_PAR_NO,
		US_MR_NBSTOP_1_BIT,
		US_MR_CHMODE_NORMAL,
		0 /* Only used in IrDA mode. */
	}; /*_RB_ TODO This is not SAM specific, not a good thing. */

	/* Initialise the USART interface. */
	freertos_usart = freertos_usart_serial_init(usart_base,
			&usart_settings,
			&driver_options);
	configASSERT(freertos_usart);

	/* Enable USART loopback mode. */
	usart_base->US_MR = (usart_base->US_MR &
			~US_MR_CHMODE_Msk) | US_MR_CHMODE_LOCAL_LOOPBACK;

	/* Create the two tasks as described above. */
	xTaskCreate(usart_echo_tx_task, (const signed char *const) "Tx",
			stack_depth_words, (void *) freertos_usart,
			task_priority,
			NULL);
	xTaskCreate(usart_task, (const signed char *const) "Rx",
			stack_depth_words, (void *) freertos_usart,
			task_priority + 1, NULL);
}

/*-----------------------------------------------------------*/

static void usart_task(void *pvParameters)
{
	UNUSED(pvParameters);
	/* Define all the test cases */
	DEFINE_TEST_CASE(usart_test, NULL, run_usart_test, NULL,
			"FreeRTOS USART with 2 threads read/write in loopback mode");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(usart_tests) = {
		&usart_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(usart_suite, usart_tests,
			"SAM FreeRTOS USART Interface Layer test suite");

	/* Run all tests in the test suite */
	test_suite_run(&usart_suite);

	/* Delete task */
	vTaskDelete(NULL);
}

/*-----------------------------------------------------------*/

static void run_usart_test(const struct test_case *test)
{
	static uint8_t rx_buffer[RX_BUFFER_SIZE];
	uint32_t received;
	unsigned portBASE_TYPE string_index;

	string_index = 0;

	for (;;) {
		memset(rx_buffer, 0x00, sizeof(rx_buffer));

		received = freertos_usart_serial_read_packet(freertos_usart,
				rx_buffer,
				strlen((const char *) echo_strings[string_index]),
				portMAX_DELAY);

		test_assert_true(test, received ==
				strlen((const char *) echo_strings[string_index]),
				"Test1: received size does not match!");
		test_assert_true(test,
				strcmp((const char *) rx_buffer,
				(const char *) echo_strings[string_index]) == 0,
				"Test2: unexpected string value!");

		/* Expect the next string the next time around. */
		string_index++;
		if (string_index >= (sizeof(echo_strings) / sizeof(uint8_t *))) {
			break;
		}
	}
}

/*-----------------------------------------------------------*/

static void usart_echo_tx_task(void *pvParameters)
{
	UNUSED(pvParameters);
	static uint8_t local_buffer[RX_BUFFER_SIZE];
	const portTickType time_out_definition = (100UL / portTICK_RATE_MS),
			short_delay = (10UL / portTICK_RATE_MS);
	xSemaphoreHandle notification_semaphore;
	unsigned portBASE_TYPE string_index;

	/* Check the strings being sent fit in the buffers provided. */
	for (string_index = 0;
			string_index < sizeof(echo_strings) / sizeof(uint8_t *);
			string_index++) {
		configASSERT(strlen(
				(char *) echo_strings[string_index]) <=
				RX_BUFFER_SIZE);
	}

	/* Create the semaphore to be used to get notified of end of
	transmissions. */
	vSemaphoreCreateBinary(notification_semaphore);
	configASSERT(notification_semaphore);

	/* Start with the semaphore in the expected state - no data has been sent
	yet.  A block time of zero is used as the semaphore is guaranteed to be
	there as it has only just been created. */
	xSemaphoreTake(notification_semaphore, 0);

	string_index = 0;

	for (;;) {
		/* Data cannot be sent from Flash, so copy the string to RAM. */
		strcpy((char *) local_buffer,
				(const char *) echo_strings[string_index]);

		/* Start send. */
		freertos_usart_write_packet_async(freertos_usart,
				local_buffer, strlen((char *) local_buffer),
				time_out_definition, notification_semaphore);
		configASSERT(returned_status == STATUS_OK);

		/* The async version of the write function is being used, so wait for
		the end of the transmission.  No CPU time is used while waiting for the
		semaphore.*/
		xSemaphoreTake(notification_semaphore, time_out_definition * 2);
		vTaskDelay(short_delay);

		/* Send the next string next time around. */
		string_index++;
		if (string_index >= (sizeof(echo_strings) / sizeof(uint8_t *))) {
			vTaskDelete(NULL);
		}
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
