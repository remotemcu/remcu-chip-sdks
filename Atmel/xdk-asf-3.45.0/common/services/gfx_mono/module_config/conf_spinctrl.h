/**
 * \file
 *
 * \brief Default configurations for gfx_mono_spinctrl
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef DEFAULT_GFX_MONO_SPINCTRL_H_INCLUDED
#define DEFAULT_GFX_MONO_SPINCTRL_H_INCLUDED

//! Spinner value indicator
/* Bitmap data, row by row, MSB is leftmost pixel, one byte per row. */
#define GFX_MONO_SPINCTRL_SPIN_INDICATOR_BITMAP 0x18, 0x3C, 0x7E, 0xFF
//! Height of spinner value indicator
#define GFX_MONO_SPINCTRL_SPIN_INDICATOR_HEIGHT 8
//! Width of spinner value indicator
#define GFX_MONO_SPINCTRL_SPIN_INDICATOR_WIDTH  4

//! Spinner indicator
/* Bitmap data, row by row, MSB is leftmost pixel, one byte per row. */
#define GFX_MONO_SPINCTRL_INDICATOR_BITMAP 0xFF, 0x7E, 0x3C, 0x18
//! Height of spinner indicator
#define GFX_MONO_SPINCTRL_INDICATOR_HEIGHT 8
//! Width of spinner indicator
#define GFX_MONO_SPINCTRL_INDICATOR_WIDTH  4

//! Keyboard code down
#define GFX_MONO_SPINCTRL_KEYCODE_DOWN  40
//! Keyboard code up
#define GFX_MONO_SPINCTRL_KEYCODE_UP    38
//! Keyboard code back
#define GFX_MONO_SPINCTRL_KEYCODE_BACK  8
//! Keyboard code enter
#define GFX_MONO_SPINCTRL_KEYCODE_ENTER 13

#endif /* DEFAULT_GFX_MONO_SPINCTRL_H_INCLUDED */
