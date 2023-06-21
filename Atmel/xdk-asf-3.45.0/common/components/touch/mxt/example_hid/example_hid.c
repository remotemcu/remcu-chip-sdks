/**
 * \file
 *
 * \brief Trackpad demo for mXT143E Xplained
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

/**
 * \mainpage
 *
 * \section intro Introduction
 * This example will create a HID class USB mouse on the host computer and
 * emulate a trackpad on the mXT143E Xplained.
 *
 * \section files Main files:
 * - example_hid.c: main example implementation
 * - example_hid.h: function prototypes for the USB stack
 * - ui.c: user interface implementation
 * - ui.h: user interface function prototypes
 * - conf_example.h: example configuration
 * - conf_board.h: board configuration
 * - conf_clock.h: system clock driver configuration
 * - conf_ili9341.h: display driver configuration
 * - conf_mxt.h: maXTouch driver configuration
 * - conf_sleepmgr.h: sleep manager configuration
 * - conf_sysfont.h: system font configuration
 * - conf_twim.h: TWI driver configuration
 * - conf_usb.h: USB stack configuration
 * - UC3 and SAM only: conf_spi_master.h: SPI master service configuration
 * - XMEGA only: conf_usart_spi.h: USART SPI service configuration
 *
 * \section apiinfo maXTouch low level component API
 * The maXTouch component API can be found \ref mxt_group "here", while the
 * graphics service API can be found \ref gfx_group "here".
 *
 * \section deviceinfo Device Info
 * This example has been tested with the mXT143E Xplained on the following kits:
 * - UC3-A3 Xplained
 * - XMEGA-A3BU Xplained
 * - SAM4S Xplained
 *
 * \section exampledescription Description of the example
 * When the Xplained board is connected to a host computer supporting the USB
 * HID class, it will create a mouse device. The mXT143E Xplained's display will
 * then function as a trackpad, with visualization of the touch's trail.
 *
 * The first finger on the trackpad will move the cursor and the second finger
 * will emulate a left or right click, depending on whether the second finger
 * touches on the left or right side of the first finger.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <conf_example.h>
#include "ui.h"


//! Flag to indicate if HID is currently enabled
static bool main_b_mouse_enable = false;

/**
 * \brief Set maXTouch configuration
 *
 * This function writes a set of predefined, optimal maXTouch configuration data
 * to the mXT143E Xplained.
 *
 * \param device Pointer to mxt_device struct
 */
static void mxt_init(struct mxt_device *device)
{
	enum status_code status;

	/* T8 configuration object data */
	uint8_t t8_object[] = {
		0x10, 0x05, 0x0a, 0x14, 0x64, 0x00, 0x05,
		0x0a, 0x00, 0x00,
	};

	/* T9 configuration object data */
	uint8_t t9_object[] = {
		0x8f, 0x00, 0x00, 0x0d, 0x0b, 0x00, 0x21,
		0x3c, 0x0f, 0x00, 0x32, 0x01, 0x01, 0x00,
		0x08, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x1c, 0x1c, 0x37, 0x37, 0x8f, 0x50,
		0xcf, 0x6e, 0x00, 0x02, 0x2f, 0x2c, 0x00
	};

	/* T48 configuration object data */
	uint8_t t48_object[] = {
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00
	};

	/* TWI configuration */
	twi_master_options_t twi_opt = {
		.speed = MXT_TWI_SPEED,
		.chip  = MAXTOUCH_TWI_ADDRESS,
	};

	status = twi_master_setup(TWI_INTERFACE, &twi_opt);
	Assert(status == STATUS_OK);

	/* Initialize the maXTouch device */
	status = mxt_init_device(device, TWI_INTERFACE,
			MAXTOUCH_TWI_ADDRESS, MXT143E_XPLAINED_CHG);
	Assert(status == STATUS_OK);

	/* Issue soft reset of maXTouch device by writing a non-zero value to
	 * the reset register */
	mxt_write_config_reg(device, mxt_get_object_address(device,
			MXT_GEN_COMMANDPROCESSOR_T6, 0)
			+ MXT_GEN_COMMANDPROCESSOR_RESET, 0x01);

	/* Wait for the reset of the device to complete */
	delay_ms(MXT_RESET_TIME);

	/* Write data to configuration registers in T7 configuration object */
	mxt_write_config_reg(device, mxt_get_object_address(device,
			MXT_GEN_POWERCONFIG_T7, 0) + 0, 0xff);
	mxt_write_config_reg(device, mxt_get_object_address(device,
			MXT_GEN_POWERCONFIG_T7, 0) + 1, 0xff);
	mxt_write_config_reg(device, mxt_get_object_address(device,
			MXT_GEN_POWERCONFIG_T7, 0) + 2, 0x32);

	/* Write predefined configuration data to configuration objects */
	mxt_write_config_object(device, mxt_get_object_address(device,
			MXT_GEN_ACQUISITIONCONFIG_T8, 0), &t8_object);
	mxt_write_config_object(device, mxt_get_object_address(device,
			MXT_TOUCH_MULTITOUCHSCREEN_T9, 0), &t9_object);
	mxt_write_config_object(device, mxt_get_object_address(device,
			MXT_PROCG_TOUCHSUPPRESSION_T48, 0), &t48_object);

	/* Issue recalibration command to maXTouch device by writing a non-zero
	 * value to the calibrate register */
	mxt_write_config_reg(device, mxt_get_object_address(device,
			MXT_GEN_COMMANDPROCESSOR_T6, 0)
			+ MXT_GEN_COMMANDPROCESSOR_CALIBRATE, 0x01);
}

/**
 * \brief Main application function
 *
 * This function ensures that the hardware and drivers are initialized before
 * entering an infinite work loop.
 *
 * In the work loop, the maXTouch device is polled for new touch events and any
 * new event is passed on to the user interface implementation for processing.
 * The loop then attempts to enter sleep.
 *
 * The user interface processing itself is not started by the work loop, but by
 * the USB callback function for start of frame.
 */
int main(void)
{
#ifdef USB_DEVICE_LOW_SPEED
	uint16_t virtual_sof_sub;
	uint16_t virtual_sof;
#endif

	/* maXTouch data structure */
	static struct mxt_device device;

	/* Initialize system clocks */
	sysclk_init();

	/* Initialize interrupt vectors */
	irq_initialize_vectors();

	/* Enable interrupts */
	cpu_irq_enable();

	/* Initialize the sleep manager */
	sleepmgr_init();

	/* Initialize the board */
	board_init();

	/* Initialize the mXT touch device */
	mxt_init(&device);

	/* Initialize the graphical library */
	gfx_init();

	/* Set background color */
	gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(),
			COLOR_BACKGROUND);

	/* Draw the help text */
	gfx_draw_string_aligned(
			"Middle finger to move cursor\n"
			"Index finger to left click\n"
			"Ring finger to right click",
			gfx_get_width() / 2, gfx_get_height() / 2,
			&sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE,
			TEXT_POS_CENTER, TEXT_ALIGN_CENTER);

	/* Initialize the user interface */
	ui_init();
	ui_powerdown();

	/* Start USB stack to authorize VBus monitoring */
	udc_start();

	/* Check if there are any new touch data pending */
	while (true) {
		if (mxt_is_message_pending(&device)) {
			if (mxt_read_touch_event(&device, &ui_touch_event) == STATUS_OK) {
				ui_flag_new_touch_event();
			}
		}

		/* Try to sleep */
		sleepmgr_enter_sleep();

#ifdef USB_DEVICE_LOW_SPEED
		/* No USB "Keep alive" interrupt available in low speed
		 * to scan mouse interface then use main loop */
		if (main_b_mouse_enable) {
			virtual_sof_sub = 0;
			virtual_sof = 0;
			if (virtual_sof_sub++ == 700) {
				virtual_sof_sub = 0;
				ui_process(virtual_sof++);
			}
		}
#endif
	}
}

/**
 * \name Callback functions for the USB stack
 * @{
 */

/**
 * \brief Handle suspend of bus
 *
 * Called by USB stack when host suspends the bus.
 */
void main_suspend_action(void)
{
	ui_powerdown();
}

/**
 * \brief Handle resume of bus
 *
 * Called by USB stack when the bus resumes from suspend.
 */
void main_resume_action(void)
{
	ui_wakeup();
}

/**
 * \brief Handle start of frame
 *
 * Called by USB stack when a start of frame is received, i.e., every
 * millisecond during normal operation. This function triggers processing
 * of the user interface if the HID interface has been enabled.
 */
void main_sof_action(void)
{
	if (!main_b_mouse_enable) {
		return;
	}
	ui_process(udd_get_frame_number());
}

/**
 * \brief Handle enabling of remote wake-up
 *
 * This is called by the USB stack when the host requests remote wake-up to be
 * enabled, and will request the user interface to enable wake-up.
 */
void main_remotewakeup_enable(void)
{
	ui_wakeup_enable();
}

/**
 * \brief Handle disabling of remote wake-up
 *
 * This is called by the USB stack when the host requests remote wake-up to be
 * disabled, and will request the user interface to disable wake-up.
 */
void main_remotewakeup_disable(void)
{
	ui_wakeup_disable();
}

/**
 * \brief Handle HID interface enable
 *
 * Called by the USB stack when the host enables the mouse interface.
 *
 * \retval true Signal that mouse started up OK
 */
bool main_mouse_enable(void)
{
	main_b_mouse_enable = true;
	return true;
}

/**
 * \brief Handle HID interface disable
 *
 * Called by the USB stack when the host disables the mouse interface.
 */
void main_mouse_disable(void)
{
	main_b_mouse_enable = false;
}

/** @} */
