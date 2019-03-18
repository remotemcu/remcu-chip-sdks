/**
 * \file
 *
 * \brief Main functions for USB host mass storage example
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

#include <asf.h>
#include "conf_usb_host.h"
#include "ui.h"
#include "main.h"
#include "string.h"

#define MAX_DRIVE      _VOLUMES
#define TEST_FILE_NAME "0:uhi_msc_test.txt"
#define MSG_TEST "Test UHI MSC\n"

typedef enum test_state {
	TEST_NULL,
	TEST_OK,
	TEST_NO_PRESENT,
	TEST_ERROR
} test_state_t;

static volatile uint16_t main_usb_sof_counter = 0;

static test_state_t lun_states[MAX_DRIVE];

static FATFS fs; // Re-use fs for LUNs to reduce memory footprint
static FIL file_object;

static char test_file_name[] = {
	TEST_FILE_NAME
};

static void main_reset_states(void);
static int main_count_states(test_state_t state);

/*! \brief Main function. Execution starts here.
 */
int main(void)
{
#if SAMD21 || SAML21 || SAMR30
	system_init();
#else
	sysclk_init();
	board_init();
#endif
	irq_initialize_vectors();
	cpu_irq_enable();

	// Initialize the sleep manager
	sleepmgr_init();

	ui_init();

	// Start USB host stack
	uhc_start();

	// The USB management is entirely managed by interrupts.
	// As a consequence, the user application does only have :
	// - to play with the power modes
	// - to create a file on each new LUN connected
	while (true) {
		//sleepmgr_enter_sleep();
		if (main_usb_sof_counter > 2000) {
			main_usb_sof_counter = 0;
			volatile uint8_t lun;
			FRESULT res;

			for (lun = LUN_ID_USB; (lun < LUN_ID_USB +
					uhi_msc_mem_get_lun()) &&
					(lun < MAX_DRIVE); lun++) {
				// Check if LUN has been already tested
				if (TEST_OK == lun_states[lun] ||
						TEST_ERROR == lun_states[lun]) {
					continue;
				}
				// Mount drive
				memset(&fs, 0, sizeof(FATFS));
				res = f_mount(lun, &fs);
				if (FR_INVALID_DRIVE == res) {
					// LUN is not present
					lun_states[lun] = TEST_NO_PRESENT;
					continue;
				}
				// Create a test file on the disk
				test_file_name[0] = lun + '0';
				res = f_open(&file_object,
						(char const *)test_file_name,
						FA_CREATE_ALWAYS | FA_WRITE);
				if (res == FR_NOT_READY) {
					// LUN not ready
					lun_states[lun] = TEST_NO_PRESENT;
					f_close(&file_object);
					continue;
				}
				if (res != FR_OK) {
					// LUN test error
					lun_states[lun] = TEST_ERROR;
					f_close(&file_object);
					continue;
				}
				// Write to test file
				f_puts(MSG_TEST, &file_object);
				// LUN test OK
				lun_states[lun] = TEST_OK;
				f_close(&file_object);
			}
			if (main_count_states(TEST_NO_PRESENT) == MAX_DRIVE) {
				ui_test_finish(false); // Test fail
			} else if (MAX_DRIVE != main_count_states(TEST_NULL)) {
				if (main_count_states(TEST_ERROR)) {
					ui_test_finish(false); // Test fail
				} else if (main_count_states(TEST_OK)) {
					ui_test_flag_reset();
					ui_test_finish(true); // Test OK
				}
			} else {
				ui_test_flag_reset();
			}
		}
	}
}

void main_usb_sof_event(void)
{
	main_usb_sof_counter++;
	ui_usb_sof_event();
}

void main_usb_connection_event(uhc_device_t * dev, bool b_present)
{
	if (!b_present) {
		main_reset_states(); // LUN is unplugged, reset flags
	}
	ui_usb_connection_event(dev, b_present);
}

static void main_reset_states(void)
{
	int i;
	for (i = 0; i < MAX_DRIVE; i ++) {
		lun_states[i] = TEST_NULL;
	}
}

static int main_count_states(test_state_t state)
{
	int i, count = 0;
	for (i = 0; i < MAX_DRIVE; i ++) {
		if (lun_states[i] == state) {
			count ++;
		}
	}
	return count;
}

/**
 * \mainpage ASF USB host mass storage
 *
 * \section intro Introduction
 * This example shows how to implement a USB host mass storage
 * on Atmel MCU with USB module.
 *
 * \section startup Startup
 * After loading firmware, connect the board (EVKxx,XPlain,...) to a U-Disk
 * (FAT/FAT32 are supported). This example creates a file "uhi_msc_test.txt"
 * on all present U-disks.
 *
 * \copydoc UI
 *
 * \section example About example
 *
 * The example uses the following module groups:
 * - Basic modules:
 *   Startup, board, clock, interrupt, power management
 * - USB host stack and MSC modules:
 *   <br>services/usb/
 *   <br>services/usb/uhc/
 *   <br>services/usb/class/msc/host/
 * - Thirdparty modules:
 *   <br>thirdparty/fatfs
 * - Specific implementation:
 *    - main.c,
 *      <br>initializes clock
 *      <br>initializes interrupt
 *      <br>manages UI
 *    - specific implementation for each target "./examples/product_board/":
 *       - conf_foo.h   configuration of each module
 *       - ui.c        implement of user's interface (buttons, leds)
 */
