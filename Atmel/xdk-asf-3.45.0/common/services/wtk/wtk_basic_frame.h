/**
 * \file
 *
 * \brief Graphical Widget toolkit
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
#ifndef WTK_BASIC_FRAME_H
#define WTK_BASIC_FRAME_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup wtk_group
 *
 * \defgroup wtk_basic_frame_group Basic frame widget
 *
 * Basic frame widget provides a frame with only a background color.
 * @{
 */

struct wtk_basic_frame;

/**
 * \brief Basic frame command event handler callback
 *
 * The basic frame command event handler callback is used to handle
 * command events from widgets inside the basic frame. Command events
 * are typically queued when the user has given some input to a widget.
 * Examples are pushing a button widget or checking a check box widget.
 *
 * \note The maximum stack usage can be affected by the implementation of the
 *       event handler. The handler will be called from within the event
 *       handling of the \ref win_group "window system". This event handling
 *       is done recursively to traverse all child windows connected to the
 *       \ref win_root "window root".
 *
 * \param basic_frame  Pointer to the basic frame which contains the widget that
 *                     generated the event.
 * \param command_data The command data that was set for the specific widget.
 *                     This is typically an ID for the widget or a pointer to
 *                     data needed by the widget. This is widget-specific.
 * \return             True if the basic frame and it's children should be
 *                     destroyed, false otherwise.
 */
typedef bool (*wtk_basic_frame_command_handler_t)(
	struct wtk_basic_frame *basic_frame, win_command_t command_data);

/**
 * \brief Basic frame draw event handler callback
 *
 * The basic frame draw event handler callback can be used to draw simple
 * graphical display elements without the need for implementing a custom
 * widget.
 * The handler is called to redraw the full or a subregion of basic frame
 * after the background for the widget has been drawn.
 *
 * If \ref CONFIG_GFX_USE_CLIPPING has been set the clipping region is set
 * before the handler is called.
 *
 * \note The maximum stack usage can be affected by the implementation of the
 *       event handler. The handler will be called from within the event
 *       handling of the \ref win_group "window system". This event handling
 *       is done recursively to traverse all child windows connected to the
 *       \ref win_root "window root".
 *
 * \param win  Pointer to the window of the basic frame widget to be drawn.
 * \param clip Region of the basic frame to be drawn in global display
 *             coordinates.
 */
typedef void (*wtk_basic_frame_draw_handler_t)(
	struct win_window *win, struct win_clip_region const *clip);

struct wtk_basic_frame *wtk_basic_frame_create(struct win_window *parent,
		const struct win_area *area, struct gfx_bitmap *background,
		wtk_basic_frame_draw_handler_t draw_handler,
		wtk_basic_frame_command_handler_t frame_handler,
		void *custom_data);
struct win_window *wtk_basic_frame_as_child(
		struct wtk_basic_frame *basic_frame);
void *wtk_basic_frame_get_custom_data(
		const struct wtk_basic_frame *basic_frame);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
