/**
 * \file
 *
 * \brief Example application for GFX Monochrome spinner widget
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
#include <stdio.h>
#include <conf_spinctrl.h>
#include <conf_sysfont.h>

/**
 * \page asfdoc_common2_gfx_mono_spinner_example GFX Mono Spinner Example
 *
 * \section asfdoc_common2_spinctrl_example_intro Introduction
 * This simple example shows how to set up a collection of spinners and display
 * them on the screen.
 *
 * \section asfdoc_common2_spinctrl_example_files Main files:
 * - \ref example_spinctrl.c : the example itself.
 * - \ref conf_ssd1306.h
 * - \ref conf_board.h
 * - \ref conf_clocks.h
 * - \ref conf_sysfont.h
 * - \ref conf_spinctrl.h
 *
 * \section asfdoc_common2_spinctrl_example_deviceinfo Device Info
 * All SAM devices can be used.
 * This example has been tested with the following setup:
 * - SAM D20 Xplained Pro
 * - SAM D21 Xplained Pro
 * - SAM R21 Xplained Pro
 * - SAM L21 Xplained Pro
 * - SAM L22 Xplained Pro
 * - SAM R30 Xplained Pro
 *
 * \section asfdoc_common2_spinctrl_example_description Description of the example application
 * This example application will initialize string spinner and two integer
 * spinners, set up a spin collection with the spinners and display them on
 * the screen.
 *
 * \section asfdoc_common2_spinctrl_example_dependencies Dependencies
 * Relevant module dependencies for this application are:
 * - \ref asfdoc_common2_gfx_mono
 * - \ref asfdoc_common2_gfx_mono_font
 * - \ref asfdoc_common2_gfx_mono_spinctrl
 *
 * \section asfdoc_common2_spinctrl_example_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR.
 * Other compilers may or may not work.
 *
 * \section asfdoc_common2_spinctrl_example_contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 */

PROGMEM_DECLARE(char, spinnertitle[]) = "Strings:";
PROGMEM_DECLARE(char, spinnertitle2[]) = "Numbers:";
PROGMEM_DECLARE(char, spinnertitle3[]) = "Numbers2:";
PROGMEM_DECLARE(char, spinner_choice1[]) = "String";
PROGMEM_DECLARE(char, spinner_choice2[]) = "String 2";
PROGMEM_DECLARE(char, spinner_choice3[]) = "String 3";
PROGMEM_DECLARE(char, spinner_choice4[]) = "String 4";

PROGMEM_STRING_T spinner_choicestrings[] = {
	spinner_choice1,
	spinner_choice2,
	spinner_choice3,
	spinner_choice4,
};


/**
 * \brief Main entry of example application
 */
int main(void)
{
	struct gfx_mono_spinctrl spinner1;
	struct gfx_mono_spinctrl spinner2;
	struct gfx_mono_spinctrl spinner3;
	struct gfx_mono_spinctrl_spincollection spinners;

	/**
	 * Starts off by initializing the system clock before configuring the
	 * board and the monochrome graphical system.
	 */
	system_init();
	gfx_mono_init();

	int16_t tmp[3];

	// Initialize spinners
	gfx_mono_spinctrl_init(&spinner1, SPINTYPE_STRING, spinnertitle,
			spinner_choicestrings, 0, 3, 0);
	gfx_mono_spinctrl_init(&spinner2, SPINTYPE_INTEGER,
			spinnertitle2, NULL, -60, -41, 0);
	gfx_mono_spinctrl_init(&spinner3, SPINTYPE_INTEGER,
			spinnertitle3, NULL, 19999, 20200, 0);

	// Initialize spincollection
	gfx_mono_spinctrl_spincollection_init(&spinners);

	// Add spinners to spincollection
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner1, &spinners);
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner2, &spinners);
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner3, &spinners);

	// Show spincollection on screen
	gfx_mono_spinctrl_spincollection_show(&spinners);

	// Spincollection is now ready to process input from user

	while(1) {
		gfx_mono_spinctrl_spincollection_process_key(&spinners, GFX_MONO_SPINCTRL_KEYCODE_DOWN, tmp);
		delay_s(1);
		gfx_mono_spinctrl_spincollection_process_key(&spinners, GFX_MONO_SPINCTRL_KEYCODE_ENTER, tmp);
		delay_s(1);
	}
}
