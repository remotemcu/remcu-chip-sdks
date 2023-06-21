/**
 * \file
 *
 * \brief Configurations for the graphical window system
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
#ifndef CONF_WIN_H
#define CONF_WIN_H

/**
 * \weakgroup win_group
 * @{
 */

#include <stdint.h>

/** Datatype holding button state mask for pointer input devices. */
typedef uint8_t win_button_mask_t;

/** Datatype holding the key "scan" code for keyboard input devices. */
typedef uint8_t win_keycode_t;

/** Datatype holding sizes for the event queue. */
typedef uint8_t win_event_queue_size_t;

/**
 * \brief Custom data, can be used as a data pointer or data depending on
 * the application.
 */
typedef void *win_command_t;

/** Data type holding timestamp for events */
typedef uint16_t clock_jiffy_t;

/** Background color of root window, ie. the desktop. */
#define WIN_ROOT_COLOR GFX_COLOR(0, 0, 0)

/** Screen background color used when root window is hidden. */
#define WIN_SCREEN_COLOR GFX_COLOR(0, 0, 0)

/** Size of event queue, holding both input and command events. */
#define WIN_EVENT_QUEUE_SIZE 10

/** Button mask for touch screens. */
#define WIN_TOUCH_BUTTON (1 << 0)

/** @} */

#endif /* CONF_WIN_H */
