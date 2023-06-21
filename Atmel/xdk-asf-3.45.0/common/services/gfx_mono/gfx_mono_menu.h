/**
 * \file
 *
 * \brief Simple menu system
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
#ifndef GFX_MONO_MENU_H
#define GFX_MONO_MENU_H

#include "compiler.h"
#include "conf_menu.h"

/**
 * \ingroup gfx_mono
 * \defgroup gfx_mono_menu Menu system for monochrome graphical displays
 *
 * This module provides a simple menu system for monochrome graphical
 * displays.
 *
 * Typical flow of an application using the menu system:
 *
 * 1) Define menu structure.\n
 * 2) Call gfx_mono_menu_init.\n
 * 3) Get user input.\n
 * 4) Update menu with user input using function \ref
 *    gfx_mono_menu_process_key.\n
 * 5) Interpret \ref gfx_mono_menu_process_key return value.\n
 * 6) Go to 3.\n
 *
 * The menu is declared using the \ref gfx_mono_menu struct.
 *
 * To start the menu system, call the \ref gfx_mono_menu_init function.
 * This function will clear the display and draw the menu.
 *
 * Before the menu can be updated, you need input from the user. Methods for
 * getting input is not part of the menu module.
 *
 * As soon as input is received, inform the menu system using the
 * \ref gfx_mono_menu_process_key function.
 * This function will then return a status code and act depending on the given
 * keycode:
 *
 * MENU_KEYCODE_DOWN : Change selection to next menu item (or first if at
 * bottom).
 * Returns MENU_EVENT_IDLE.
 *
 * MENU_KEYCODE_UP : Change selection to previous menu item (or last if at top).
 * Returns MENU_EVENT_IDLE.
 *
 * MENU_KEYCODE_ENTER : Nothing changes in menu. Returns the line selected.
 *
 * MENU_KEYCODE_BACK : Nothing changes in menu. Returns MENU_EVENT_EXIT.
 *
 * The value of the keycodes used are defined in conf_menu.h. These value can
 * be changed if needed.
 *
 * The graphical indicator used to indicate menu selection is defined in
 * conf_menu.h. This indicator can be changed if needed.
 * @{
 */

/** \name Menu events definitions */
/** @{ */
/** Idle. Nothing to report. */
#define GFX_MONO_MENU_EVENT_IDLE    0xFF
/** Exit. User has pressed the back button. */
#define GFX_MONO_MENU_EVENT_EXIT    0xFE
/** @} */

/** Maximum number of menu elements on display */
#define GFX_MONO_MENU_ELEMENTS_PER_SCREEN ((GFX_MONO_LCD_HEIGHT / \
	SYSFONT_LINESPACING) - 1)

/** Menu struct */
struct gfx_mono_menu {
	PROGMEM_STRING_T title;
	PROGMEM_STRING_T *strings;
	uint8_t num_elements;
	uint8_t current_selection;
	uint8_t current_page;
};

void gfx_mono_menu_init(struct gfx_mono_menu *menu);
uint8_t gfx_mono_menu_process_key(struct gfx_mono_menu *menu, uint8_t keycode);

/** @} */

#endif /* GFX_MONO_MENU_H */
