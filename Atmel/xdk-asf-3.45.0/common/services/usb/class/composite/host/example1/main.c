/**
 * \file
 *
 * \brief Main functions for USB host mass storage and mouse composite example
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

#include <asf.h>
#include "conf_usb_host.h"
#include "ui.h"
#include "main.h"

static volatile uint16_t main_usb_sof_counter = 0;
static volatile uint8_t lun_state = 0;

#define MSG_TEST "Test UHI MSC\n"

/*! \brief Main function. Execution starts here.
 */
int main(void)
{
	sysclk_init();
	irq_initialize_vectors();
	cpu_irq_enable();

	// Initialize the sleep manager
	sleepmgr_init();

	board_init();
	ui_init();

	// Reset File System
	nav_reset();

	// Start USB host stack
	uhc_start();

	// The USB management is entirely managed by interrupts.
	// As a consequence, the user application does only have :
	// - to play with the power modes
	// - to create a file on each new LUN connected
	while (true) {
		sleepmgr_enter_sleep();
		if (main_usb_sof_counter > 2000) {
			main_usb_sof_counter = 0;
			uint8_t lun;

			for (lun = 0; (lun < uhi_msc_mem_get_lun()) && (lun < 8); lun++) {
				// Mount drive
				nav_drive_set(lun);
				if (!nav_partition_mount()) {
					if (fs_g_status == FS_ERR_HW_NO_PRESENT) {
						// The test can not be done, if LUN is not present
						lun_state &= ~(1 << lun); // LUN test reseted
						continue;
					}
					lun_state |= (1 << lun); // LUN test is done.
					ui_test_finish(false); // Test fail
					continue;
				}

				// Check if LUN has been already tested
				if (lun_state & (1 << lun)) {
					continue;
				}

				// Create a test file on the disk
				if (!nav_file_create((FS_STRING) "uhi_msc_test.txt")) {
					if (fs_g_status != FS_ERR_FILE_EXIST) {
						if (fs_g_status == FS_LUN_WP) {
							// Test can be done only on no write protected device
							continue;
						}
						lun_state |= (1 << lun); // LUN test is done.
						ui_test_finish(false); // Test fail
						continue;
					}
				}
				if (!file_open(FOPEN_MODE_APPEND)) {
					if (fs_g_status == FS_LUN_WP) {
						// Test can be done only on no write protected device
						continue;
					}
					lun_state |= (1 << lun); // LUN test is done.
					ui_test_finish(false); // Test fail
					continue;
				}
				if (!file_write_buf((uint8_t*)MSG_TEST, sizeof(MSG_TEST))) {
					lun_state |= (1 << lun); // LUN test is done.
					ui_test_finish(false); // Test fail
					continue;
				}
				file_close();
				lun_state |= (1 << lun); // LUN test is done.
				ui_test_finish(true); // Test pass
			}
			if ((lun == 0) || (lun_state == 0)) {
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
		lun_state = 0; // LUN is unplugged, reset flag
	}
	ui_usb_connection_event(dev, b_present);
}

/**
 * \mainpage ASF USB host MSC and HID mouse example
 *
 * \section intro Introduction
 * This example shows how to implement a USB host mass storage
 * and host mouse on Atmel MCU with USB module.
 *
 * \section startup Startup
 * After loading firmware, connect the board (EVKxx,Xplain,...) to a USB device
 * mouse or a U-disk (FAT/FAT32 are supported). This example creates a file
 * "uhi_msc_test.txt" on all present U-disks.
 *
 * \copydoc UI
 *
 * \section example About example
 *
 * The example uses the following module groups:
 * - Basic modules:
 *   Startup, board, clock, interrupt, power management
 * - USB host stack, MSC and HID modules:
 *   <br>services/usb/
 *   <br>services/usb/uhc/
 *   <br>services/usb/class/msc/host/
 *   <br>services/usb/class/hid/host/mouse/
 * - Specific implementation:
 *    - main.c,
 *      <br>initializes clock
 *      <br>initializes interrupt
 *      <br>manages UI
 *    - specific implementation for each target "./examples/product_board/":
 *       - conf_foo.h   configuration of each module
 *       - ui.c        implement of user's interface (buttons, leds)
 */
