/**
 * \file
 *
 * \brief Default configurations for menu system
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

#ifndef DEFAULT_MENU_H_INCLUDED
#define DEFAULT_MENU_H_INCLUDED

//! \name Indicator icon definitions
//@{
//! Bitmap data, row by row, MSB is leftmost pixel, one byte per row.
#define GFX_MONO_MENU_INDICATOR_BITMAP 0xFF, 0x7E, 0x3C, 0x18
//! Height in pixels of indicator icon
#define GFX_MONO_MENU_INDICATOR_HEIGHT 8
//! Width in pixels of indicator icon
#define GFX_MONO_MENU_INDICATOR_WIDTH  4
//@}

//! \name Keyboard codes
//@{
//! Down
#define GFX_MONO_MENU_KEYCODE_DOWN  40
//! Up
#define GFX_MONO_MENU_KEYCODE_UP    38
//! Back/exit
#define GFX_MONO_MENU_KEYCODE_BACK  8
//! Enter/select
#define GFX_MONO_MENU_KEYCODE_ENTER 13
//@}

#endif /* DEFAULT_MENU_H_INCLUDED */
