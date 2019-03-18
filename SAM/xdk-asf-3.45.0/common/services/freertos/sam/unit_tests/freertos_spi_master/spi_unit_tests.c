/**
 * \file
 *
 * \brief Unit tests for FreeRTOS SPI Interface Layer.
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
#include <spi.h>
#include <conf_test.h>
#include <conf_board.h>
#include <conf_example.h>
#include "FreeRTOS.h"
#include "task.h"
#include "freertos_spi_master.h"

/*-----------------------------------------------------------*/

/* The size of the AT25 dataflash. */
#define TOTAL_FLASH_SIZE        (4 * 1024 * 1024)

/* The page size of AT25DF series is always 256. */
#define PAGE_SIZE               256

/** Test buffer size */
#define TEST_DATA_SIZE          32

/** Test start address */
#define TEST_BLOCK_ADDR         0

/* The command always goes in the first byte of the message. */
#define COMMAND_INDEX           0

/* The address goes in bytes 2, 3 and 4 of the message. */
#define ADDRESS_INDEX           1

/* A block time used after a write to allow the flash to write the data sent
 * over the SPI bus into its internal memory. */
#define INTERNAL_WRITE_DELAY    (10 / portTICK_RATE_MS)

/* Max number when the chip selects are directly connected to peripheral device.
 **/
#define NONE_CHIP_SELECT_VALUE   0x0f

/* Instructions/commands that can be sent to the flash. */
#define STATUS  0x01 /* Write status register. */
#define WRITE   0x02 /* Write instruction. */
#define READ    0x03 /* Read instruction. */
#define RDSR    0x05 /* Read status register instruction. */
#define WREN    0x06 /* Write enable instruction. */
#define ERASE   0xD8 /* 64k block erase instruction. */

/* AT25 ready/busy status bit */
#define STATUS_RDYBSY           (1 << 0)

/* AT25 ready bit */
#define STATUS_RDYBSY_READY     (0 << 0)

/* SPI clock speed. */
#define BAUD_RATE               12000000

/* Chip select. */
#define CHIP_SELECT             CONF_TEST_CS

/* Clock polarity. */
#define CLOCK_POLARITY          0

/* Clock phase. */
#define CLOCK_PHASE             1

/* Delay before SPCK. */
#define DELAY_BEFORE            0x40

/* Delay between consecutive transfers. */
#define DELAY_BETWEEN           0x10

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the FreeRTOS SPI Interface Layer.
 * It consists of test cases for the following functionality:
 * - Data read/write on SPI bus using FreeRTOS Interface Layer
 *
 * \section files Main Files
 * - \ref spi_unit_tests.c
 * - \ref FreeRTOSConfig.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_example.h
 * - \ref conf_spi_master.h
 * - \ref conf_test.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * All SAM devices can be used.
 * This example has been tested with the following setup:
 * - sam3n4c_sam3n_ek
 * - sam4c16c_sam4c_ek
 *
 * Note: an AT25 serial flash needs to be connected to the MCU.
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
 * \def spi_test
 * \brief Init, read and write on AT25 using FreeRTOS SPI Interface Layer.
 */
/* @} */

static void run_spi_test(const struct test_case *test);
static void create_spi_task(Spi *spi_base, uint16_t stack_depth_words,
		unsigned portBASE_TYPE task_priority);
static void spi_flash_task(void *pvParameters);
static void at25dfx_send_command(uint8_t *cmd_buffer, uint32_t cmd_size,
		uint8_t *data_buffer, uint32_t data_size);
static void at25dfx_unprotect(void);
static void at25dfx_erase_block(uint32_t address);
static void at25dfx_wait_ready(void);
static void at25dfx_read(uint32_t size, uint32_t address);
static void at25dfx_spi_read(uint8_t *buffer, uint32_t number_of_bytes);
static void at25dfx_write(uint32_t size, uint32_t address);
static void at25dfx_spi_write(uint8_t *buffer, uint32_t number_of_bytes);

/* Command buffer (1 byte for cmd and 3 bytes for address) */
static uint8_t cmd_buffer[4];
/* Data buffer */
static uint8_t data_buffer[TEST_DATA_SIZE];
/* SPI instance */
static freertos_spi_if freertos_spi;
/* Used to latch errors found during the execution of the example. */
static uint32_t error_detected = pdFALSE;

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
 * \brief Run SPI unit tests
 */
int main(void)
{
	/* Prepare the hardware to run this demo. */
	prvSetupHardware();

	/* Create the test task. */
	create_spi_task(BOARD_SPI, 1024, tskIDLE_PRIORITY);

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

static void create_spi_task(Spi *spi_base, uint16_t stack_depth_words,
		unsigned portBASE_TYPE task_priority)
{
	freertos_peripheral_options_t blocking_driver_options = {
	NULL,											/* This peripheral does not need a receive buffer, so this parameter is just set to NULL. */
	0,												/* There is no Rx buffer, so the rx buffer size is not used. */
	configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY,	/* The priority used by the SPI interrupts. */
	SPI_MASTER,										/* Communicating with the flash requires the peripheral to be configured as an SPI master. */
	(USE_TX_ACCESS_SEM | USE_RX_ACCESS_MUTEX | WAIT_TX_COMPLETE | WAIT_RX_COMPLETE)	/* The blocking driver is to be used, so WAIT_TX_COMPLETE and WAIT_RX_COMPLETE are set. */
};

	/* Initialize the FreeRTOS driver for blocking operation.  The
	peripheral clock is configured in this function call. */
	freertos_spi = freertos_spi_master_init(spi_base,
			&blocking_driver_options);

	/* Check the port was initialized successfully. */
	configASSERT(freertos_spi);

	spi_disable(spi_base);
	spi_set_clock_polarity(spi_base, CHIP_SELECT, CLOCK_POLARITY);
	spi_set_clock_phase(spi_base, CHIP_SELECT, CLOCK_PHASE);
	spi_set_bits_per_transfer(spi_base, CHIP_SELECT, SPI_CSR_BITS_8_BIT);
	spi_set_baudrate_div(spi_base, CHIP_SELECT,
			(sysclk_get_cpu_hz() / BAUD_RATE));
	spi_set_transfer_delay(spi_base, CHIP_SELECT, DELAY_BEFORE,
			DELAY_BETWEEN);
	spi_configure_cs_behavior(spi_base, CHIP_SELECT, SPI_CS_KEEP_LOW);
	spi_set_peripheral_chip_select_value(spi_base, spi_get_pcs(CHIP_SELECT));
	spi_enable(spi_base);

	/* Create the task as described above. */
	xTaskCreate(spi_flash_task, (const signed char *const) "Tx",
			stack_depth_words, NULL, task_priority, NULL);
}

/*-----------------------------------------------------------*/

static void spi_flash_task(void *pvParameters)
{
	UNUSED(pvParameters);
	/* Define all the test cases */
	DEFINE_TEST_CASE(spi_test, NULL, run_spi_test, NULL,
			"FreeRTOS SPI init-read-write on AT25");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(spi_tests) = {
		&spi_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(spi_suite, spi_tests,
			"SAM FreeRTOS SPI Interface Layer test suite");

	/* Run all tests in the test suite */
	test_suite_run(&spi_suite);

	/* Delete task */
	vTaskDelete(NULL);
}

/*-----------------------------------------------------------*/

static void run_spi_test(const struct test_case *test)
{
	/* AT25 is protected by default after init, so unprotect it. */
	at25dfx_unprotect();

	/* Erase a 64k block at address TEST_BLOCK_ADDR. */
	at25dfx_erase_block(TEST_BLOCK_ADDR);

	/* Read back the same memory area from the AT25 and compare with the
	expected value. */
	at25dfx_read(TEST_DATA_SIZE, TEST_BLOCK_ADDR);

	for (uint32_t i = 0; i < TEST_DATA_SIZE; i++) {
		if (data_buffer[i] != 0xff) {
			error_detected = pdTRUE;
		}
	}

	/* Check Test1. */
	test_assert_true(test, error_detected == pdFALSE,
			"Test1: data erase failed!");

	/* Prepare the buffer in order to fill the AT25 with 0xaa, one page at a
	time. */
	memset(data_buffer, 0xaa, sizeof(data_buffer));

	/* Write the data to the SerialFlash */
	at25dfx_write(TEST_DATA_SIZE, TEST_BLOCK_ADDR);

	/* Reset the internal buffer to ensure data will be read from the AT25. */
	memset(data_buffer, 0xff, sizeof(data_buffer));

	/* Read back the same memory area from the AT25 and compare with the
	expected value. */
	at25dfx_read(TEST_DATA_SIZE, TEST_BLOCK_ADDR);

	for (uint32_t i = 0; i < TEST_DATA_SIZE; i++) {
		if (data_buffer[i] != 0xaa) {
			error_detected = pdTRUE;
		}
	}

	/* Check Test2. */
	test_assert_true(test, error_detected == pdFALSE,
			"Test2: failed to read previously written data!");
}

/*-----------------------------------------------------------*/

static void at25dfx_send_command(uint8_t *cmd_buffer, uint32_t cmd_size,
		uint8_t *data_buffer, uint32_t data_size)
{
	/* Select the AT25 chip. */
	spi_set_peripheral_chip_select_value(freertos_spi,
			(~(1 << CHIP_SELECT)));

	/* Send actual command. */
	at25dfx_spi_write( cmd_buffer, cmd_size);

	if (data_size > 0) {
		if (cmd_buffer[COMMAND_INDEX] == WRITE ||
				cmd_buffer[COMMAND_INDEX] == STATUS) {
			at25dfx_spi_write(data_buffer, data_size);
		} else {
			at25dfx_spi_read(data_buffer, data_size);
		}
	}

	/* Deselect the AT25 chip - assert all lines; no peripheral is selected. */
	spi_set_peripheral_chip_select_value(freertos_spi, NONE_CHIP_SELECT_VALUE);
	/* Last transfer, so de-assert the current NPCS if CSAAT is set. */
	spi_set_lastxfer(freertos_spi);
}

/*-----------------------------------------------------------*/

static void at25dfx_unprotect(void)
{
	uint8_t status = 0;

	/* Set the write enable latch (1 byte command). */
	cmd_buffer[COMMAND_INDEX] = WREN;
	at25dfx_send_command(cmd_buffer, 1, data_buffer, 0);

	/* Set the STATUS command. */
	cmd_buffer[COMMAND_INDEX] = STATUS;
	at25dfx_send_command(cmd_buffer, 1, &status, 1);

	/* Wait for the AT25 to be ready. */
	at25dfx_wait_ready();
}

/*-----------------------------------------------------------*/

static void at25dfx_erase_block(uint32_t address)
{
	/* Set the write enable latch (1 byte command). */
	cmd_buffer[COMMAND_INDEX] = WREN;
	at25dfx_send_command(cmd_buffer, 1, data_buffer, 0);

	/* Set the ERASE command and address. (4 bytes command). */
	cmd_buffer[COMMAND_INDEX] = ERASE;
	cmd_buffer[ADDRESS_INDEX] = (uint8_t)((address & 0xff0000U) >> 16);
	cmd_buffer[ADDRESS_INDEX + 1] = (uint8_t)((address & 0xff00U) >> 8);
	cmd_buffer[ADDRESS_INDEX + 2] = (uint8_t)((address & 0xffU));
	at25dfx_send_command(cmd_buffer, 4, data_buffer, 0);

	/* Wait for the AT25 to be ready. */
	at25dfx_wait_ready();
}

/*-----------------------------------------------------------*/

static void at25dfx_wait_ready(void)
{
	const portTickType xDelay = 100 / portTICK_RATE_MS;
	uint32_t wait_timeout = 30;
	uint8_t status = 0;

	/* Wait for the AT25 to be ready, if not delay the task and try again. */
	/* If still not ready after several attempt, forget it. */
	while (wait_timeout) {
		/* Set the READ Status command. (1 byte command). */
		cmd_buffer[COMMAND_INDEX] = RDSR;
		at25dfx_send_command(cmd_buffer, 1, &status, 1);

		/* Exit when the device is ready */
		if ((status & STATUS_RDYBSY) == STATUS_RDYBSY_READY) {
			break;
		}

		/* Give some rest to the AT25 and let the scheduler decide what to do. */
		vTaskDelay(xDelay);

		/* Decrease the number of attempts (timeout). */
		wait_timeout -= 1;
	}
}

/*-----------------------------------------------------------*/

static void at25dfx_read(uint32_t size, uint32_t address)
{
	/* Set the READ command and address. (4 bytes command). */
	cmd_buffer[COMMAND_INDEX] = READ;
	cmd_buffer[ADDRESS_INDEX] = (uint8_t)((address & 0xff0000U) >> 16);
	cmd_buffer[ADDRESS_INDEX + 1] = (uint8_t)((address & 0xff00U) >> 8);
	cmd_buffer[ADDRESS_INDEX + 2] = (uint8_t)((address & 0xffU));
	at25dfx_send_command(cmd_buffer, 4, data_buffer, size);
}

/*-----------------------------------------------------------*/

static void at25dfx_spi_read(uint8_t *buffer, uint32_t number_of_bytes)
{
	const portTickType max_block_time_ticks = 200UL / portTICK_RATE_MS;

	/* The blocking API is being used. Other tasks will run while the SPI
	read is in progress. */
	if (freertos_spi_read_packet(freertos_spi, buffer, number_of_bytes,
			max_block_time_ticks) != STATUS_OK) {
		error_detected = pdTRUE;
	}
}

/*-----------------------------------------------------------*/

static void at25dfx_write(uint32_t size, uint32_t address)
{
	uint32_t write_size;
	uint32_t written = 0;

	while (size > 0) {
		/* Compute the number of bytes to program in page */
		write_size = Min(size, PAGE_SIZE - (address % PAGE_SIZE));

		/* Set the write enable latch (1 byte command). */
		cmd_buffer[COMMAND_INDEX] = WREN;
		at25dfx_send_command(cmd_buffer, 1, data_buffer, 0);

		/* Set the WRITE command and address (4 bytes command). */
		cmd_buffer[COMMAND_INDEX] = WRITE;
		cmd_buffer[ADDRESS_INDEX] = (uint8_t) ((address & 0xff0000U) >> 16);
		cmd_buffer[ADDRESS_INDEX + 1] = (uint8_t) ((address & 0xff00U) >> 8);
		cmd_buffer[ADDRESS_INDEX + 2] = (uint8_t) ((address & 0xffU));
		at25dfx_send_command(cmd_buffer, 4, data_buffer + written,
				write_size);

		/* Compute remaining size and update pointer values. */
		written += write_size;
		size -= write_size;
		address += write_size;

		/* Wait for the AT25 to be ready. */
		at25dfx_wait_ready();
	}
}

/*-----------------------------------------------------------*/

static void at25dfx_spi_write(uint8_t *buffer, uint32_t number_of_bytes)
{
	const portTickType max_block_time_ticks = 200UL / portTICK_RATE_MS;

	/* The blocking API is being used.  Other tasks will execute while the
	SPI write is in progress. */
	if (freertos_spi_write_packet(freertos_spi, buffer, number_of_bytes,
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
	(void)pcTaskName;
	(void)pxTask;

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
