/**
 * \file
 *
 * \brief SAM LED Toggle Example
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
 * \mainpage SAM LED Toggle Example
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This application demonstrates a simple example to toggle the board LED.
 */

/**
 * \page appdoc_main SAM LED Toggle Example
 *
 * Overview:
 * - \ref appdoc_sam0_led_toggle_app_intro
 * - \ref appdoc_sam0_led_toggle_app_usage
 * - \ref appdoc_sam0_led_toggle_app_compinfo
 * - \ref appdoc_sam0_led_toggle_app_contactinfo
 *
 * \section appdoc_sam0_led_toggle_app_intro Introduction
 * This application demonstrates a simple example to toggle the board LED.
 *
 * This application has been tested on following boards:
 * - SAM D20/D21/R21/D11/L21/L22/R30/R34 Xplained Pro
 * - SAM D10 Xplained Mini
 * - SAMR21ZLL-EK
 *
 * \section appdoc_sam0_led_toggle_app_usage Usage
 * The application uses system timer to generate periodic interrupts, once the
 * interrupt occurs, LED0 will toggle.
 *
 * \section appdoc_sam0_led_toggle_app_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_led_toggle_app_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>


/** Handler for the device SysTick module, called when the SysTick counter
 *  reaches the set period.
 *
 *  \note As this is a raw device interrupt, the function name is significant
 *        and must not be altered to ensure it is hooked into the device's
 *        vector table.
 */
void SysTick_Handler(void)
{
	port_pin_toggle_output_level(LED_0_PIN);
}

/** Configure LED0, turn it off*/
static void config_led(void)
{
	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);

	pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED_0_PIN, &pin_conf);
	port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
}

int main(void)
{
	system_init();

	/*Configure system tick to generate periodic interrupts */
	SysTick_Config(system_gclk_gen_get_hz(GCLK_GENERATOR_0));

	config_led();

	while (true) {
	}
}
