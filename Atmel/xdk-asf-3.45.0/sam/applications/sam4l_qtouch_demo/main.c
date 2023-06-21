/**
 * \file
 *
 * \brief Low Power and QTouch Demo for SAM4L.
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
 * \mainpage Low Power and QTouch Demo for SAM4L
 *
 * \section Purpose
 *
 * The Low Power and QTouch demo will help new users get familiar with Atmel's
 * SAM4L microcontrollers. This basic application shows how to initialize
 * the QTouch library and optimize the SAM4L configuration to target low power
 * applications.
 *
 * \section files Main Files
 * - main.c demo application,
 * - app.c manage SAM4L low-level configuration,
 * - event.c manage QTouch and push button,
 * - ui.c LCD display and Board Monitor transfers.
 *
 * \section Requirements
 *
 * This package can be used with SAM4L-EK evaluation kits.
 *
 * \section Description
 *
 * - At startup the application run in full demo mode (all features on, includes
 * QTouch and segment LCD). The applications captures QTouch inputs
 * (sliders and CS0 QTouch button): displays the slider value (0..255)  to the
 * segment LCD, CS0 will change the SAM4L Power Scaling mode (from PS0 to PS2).
 * - Once the PB0 push button has been pressed, the application switches in low
 * power mode: Stop LCD controller, stop LCD back light, stop QTouch
 * acquisition, switch SAM4L in power scaling PS1 mode. SAM4L is still in RUN
 * mode.
 * - If PB0 is pressed, the SAM4L will enter one of  the sleep modes
 * (from RUN to WAIT to RET to BACKUP, then restart to RUN). For each sleep mode
 * transition, the SAM4L is sending the information to the board monitor
 * (over the USART). The current SAM4L sleep mode is displayed by the board
 * monitor on the OLED display.
 *
 * It requires a board monitor firmware version V1.4 if it runs on SAM4L_EK board.
 *
 * \section Usage
 *
 * - Build the program and download it to the evaluation board. Please
 *  refer to the SAM4L main page documentation
 *  http://www.microchip.com/developmenttools/productdetails/partno/atsam4l-ek
 * - Start the application.
 * - The message "SAM4L-EK DEMO" is scrolling on SAM4L-EK on-board LCD segment.
 * - Play with QTouch and push button.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include "asf.h"
#include "app.h"
#include "ui.h"
#include "event.h"


/**
 * \brief Check if PS2 mode is supported by the part.
 * \retval true   The part support PS2 mode.
 * \retval false  The part doesn't support PS2 mode.
 */
static bool is_ps2_mode_supported_by_the_part(void)
{
	/*
	 * PS2 mode is not supported by Engineering Samples. PS2 mode support is
	 * supported only by parts with calibration version higher than 0.
	 *
	 * Fix/Workaround:
	 * The calibration version can be checked by reading a 32-bit word at
	 * address 0x0080020C. The calibration version bitfield is 4-bit wide and
	 * located from bit 4 to bit 7 in this word. Any value higher than 0 ensures
	 * that the part supports the PS2 mode
	 */

	uint32_t cal_ver = *((uint32_t *)0x0080020C);
	return (cal_ver & 0xF0);
}

/**
 *  \brief Lower power and QTouch Demo for SAM4L entry point.
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t event_qtouch_slider_position = 0;
	power_scaling_t power_scaling = POWER_SCALING_PS1;
	sleep_mode_t sleep_mode = SLEEP_MODE_RUN;
	/*
	 * QTouch library:
	 * Use touch_config_sam4l.h file to configure Sensor Pins, number of Sensors
	 * and Sensor Global configuration information.

	 * Use touch.c touch_sensors_config() function to set Sensor specific
	 * configuration data such as the Sensor Threshold setting.
	 */

	/*
	 * At startup the application run in full demo mode (all features on,
	 * includes QTouch and segment LCD). Initialize the board IO configuration,
	 * clocks, QTouch library, External interrupts, NVIC and UI SAM4L is running
	 * at 12 MHz from internal RCFAST (configured at 12MHz).
	 */
	app_init();

	// Stay in full demo mode until push button PB0 button is pressed
	while (!event_is_push_button_pressed()){
		// Runs prime number algorithm
		app_prime_number_run();
		/*
		 * Capture QTouch inputs (sliders and CS0 QTouch button): displays the
		 * slider value (0..255) to the segment LCD, CS0 will change the SAM4L
		 * Power Scaling mode (from PS0 to PS2).
		 */
		touch_sensors_measure();
		if (event_qtouch_get_button_state()) {
			/*
			 * Change Power Scaling Mode: circle from PS0 to PS2.
			 * - Read current Power Scaling status,
			 * - Change Power Scaling Value,
			 * - Switch into this Power Scaling Value.
			 */
			power_scaling = ui_get_power_scaling_mcu_status();
			if (power_scaling == POWER_SCALING_PS0) {
				power_scaling = POWER_SCALING_PS1;
			} else if ((power_scaling == POWER_SCALING_PS1) &&
					   (is_ps2_mode_supported_by_the_part())) {
				power_scaling = POWER_SCALING_PS2;
			} else {
				power_scaling = POWER_SCALING_PS0;
			}
			ui_set_power_scaling_mcu_status(power_scaling);
			app_switch_power_scaling(power_scaling);
			// Send new MCU status to the board monitor
			ui_bm_send_mcu_status();
			// Refresh LCD Text area with this new power scaling value
			ui_lcd_refresh_txt();
			// Initialize touch sensing after Power Scaling mode change
			touch_sensors_deinit();
			touch_sensors_init();
		}
		/*
		 * Display slider value (0...255) if slider is pressed, clear display
		 * if not.
		 */
		if (event_qtouch_get_slider_state(&event_qtouch_slider_position)) {
			ui_lcd_refresh_alphanum(true,
				event_qtouch_slider_position);
		} else {
			ui_lcd_refresh_alphanum(false,
				event_qtouch_slider_position);
		}
	}
	/*
	 * Now PB0 push button has been pressed once, the application switches in
	 * low power mode: Stop LCD controller, stop LCD back light, stop QTouch
	 * acquisition, switch SAM4L in power scaling PS1 mode.
	 * SAM4L is in RUN mode.
	 */
	app_init_lowpower();

	while(1u){
		// Runs prime number algorithm
		app_prime_number_run();
		/*
		 * Run in low power mode: if PB0 is pressed, the SAM4L will enter one of
		 * the sleep modes (from RUN to WAIT to RET to BACKUP, then restart to
		 * RUN). For each sleep mode transition, the SAM4L is sending the
		 * information for the board monitor (over the USART). The current SAM4L
		 * sleep mode is displayed by the board monitor on the OLED display.
		*/
		if (event_is_push_button_pressed()) {
			/*
			 * Change Sleep Mode: RUN->WAIT->RET->BACKUP.
			 * - Read current Sleep Mode status,
			 * - Change Sleep Mode Value,
			 * - Enter into this Sleep Mode Value.
			 */
			sleep_mode = ui_get_sleep_mode_mcu_status();
			switch(sleep_mode){
				case SLEEP_MODE_WAIT:
					sleep_mode = SLEEP_MODE_RETENTION;
				break;
				case SLEEP_MODE_RETENTION:
					sleep_mode = SLEEP_MODE_BACKUP;
				break;
				case SLEEP_MODE_BACKUP:
					sleep_mode = SLEEP_MODE_RUN;
				break;
				case SLEEP_MODE_RUN:
				default:
					sleep_mode = SLEEP_MODE_WAIT;
				break;
			}
			ui_set_sleep_mode_mcu_status(sleep_mode);
			// Send new MCU status to the board monitor
			ui_bm_send_mcu_status();
			// Now we're ready to enter the selected sleep mode
			app_enter_sleep_mode(sleep_mode);
		}
	}

}// end main function
