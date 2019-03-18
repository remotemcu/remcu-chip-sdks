/**
 * \file
 *
 * \brief Application layer for low power and full features demo initialization.
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

#include "app.h"

/**
 *  \brief Application initialization: at startup the application run in full
 *  demo mode (all features on, includes QTouch and segment LCD). Initialize the
 *  board IO configuration, clocks, QTouch library, xternal interrupts, NVIC and
 *  UI. SAM4L is running at 12 MHz from internal RCFAST (configured at 12MHz).
 */
void app_init(void)
{
	// Initialize board features
	board_init();

	// Initialize clock
	sysclk_init();

	// Initialize EIC Controller
	event_button_init();

	// Initialize Qtouch
	event_qtouch_init();

	// Set MCU Status
	ui_set_mcu_status(POWER_SCALING_PS1, SLEEP_MODE_RUN,
		12000000, CPU_SRC_RC4M);

	// Initialize Board Monitor
	ui_bm_init();

	// Set LCD backlight
	ioport_set_pin_level(LCD_BL_GPIO, IOPORT_PIN_LEVEL_HIGH);

	// Initialize LCD
	ui_lcd_init();

}

/**
 *  \brief Initialize the app in low power: now PB0 push button has been pressed
 *  once, the application switches in low power mode: Stop LCD controller, stop
 *  LCD backlight, stop QTouch acquisition, switch SAM4L in power scaling PS1
 *  mode. SAM4L is in RUN mode.
 */
void app_init_lowpower(void)
{

	// Stop LCD Controller
	lcdca_disable();

	// Stop QTouch Initialization
	touch_sensors_deinit();

	// Initialize board features
	board_init();

	// Clear LCD backlight
	ioport_set_pin_level(LCD_BL_GPIO, IOPORT_PIN_LEVEL_LOW);

	// Disable the peripheral that we do not use anymore
	sysclk_disable_peripheral_clock(CATB);
	sysclk_disable_peripheral_clock(PDCA);
	sysclk_disable_peripheral_clock(LCDCA);

	// Set MCU Status
	ui_set_mcu_status(POWER_SCALING_PS1, SLEEP_MODE_RUN,
		12000000, CPU_SRC_RC4M);

	// Switch in selected Power Scaling mode
	app_switch_power_scaling(ui_get_power_scaling_mcu_status());

	// Send new MCU status to the board monitor
	ui_bm_send_mcu_status();

}

/**
 *  \brief Prime Number function
 */
void app_prime_number_run(void)
{
	#define PRIM_NUMS 8
	uint32_t i, d, n;
	uint32_t primes[PRIM_NUMS];


	// Find prime numbers forever
	primes[0] = 1;
	for (i = 1; i < PRIM_NUMS;) {
		for (n = primes[i - 1] + 1; ;n++) {
			for (d = 2; d <= n; d++) {
				if (n == d) {
					primes[i] = n;
					goto nexti;
				}
				if (n%d == 0) break;
			}
		}
		nexti:
		i++;
	}
}

/**
 * \brief Switch into selected Power Scaling.
 * \param power_scaling selected Power Scaling.
 */
void app_switch_power_scaling(power_scaling_t power_scaling)
{
	if (power_scaling == POWER_SCALING_PS1){
		bpm_configure_power_scaling(BPM,
				BPM_PMCON_PS(BPM_PS_1),
				true);
	} else if (power_scaling == POWER_SCALING_PS2){
		bpm_configure_power_scaling(BPM,
				BPM_PMCON_PS(BPM_PS_2),
				true);
	} else {
		bpm_configure_power_scaling(BPM,
				BPM_PMCON_PS(BPM_PS_0),
				true);
	}
	while((bpm_get_status(BPM) & BPM_SR_PSOK) == 0);
}

/**
 * \brief Enter into sleep mode
 * \param sleep_mode selected sleep mode.
 */
void app_enter_sleep_mode(sleep_mode_t sleep_mode)
{
	enum sleepmgr_mode  current_sleep_mode;
	switch(sleep_mode){
		case SLEEP_MODE_WAIT:
			current_sleep_mode = SLEEPMGR_WAIT;
		break;
		case SLEEP_MODE_RETENTION:
			current_sleep_mode = SLEEPMGR_RET;
		break;
		case SLEEP_MODE_BACKUP:
			current_sleep_mode = SLEEPMGR_BACKUP;
		break;
		case SLEEP_MODE_RUN:
		default:
			current_sleep_mode = SLEEPMGR_ACTIVE;
		break;
	}
	sleepmgr_sleep(current_sleep_mode);
}

