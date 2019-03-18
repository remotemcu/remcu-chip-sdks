/**
 * \file
 *
 * \brief Graphical Window system
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
#ifndef WIN_H
#define WIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <gfx.h>
#include <membag.h>
#include "conf_win.h"

/**
 * \ingroup gfx_group
 * \defgroup win_group Window System
 * \brief Window system for organizing window elements in a graphical user
 *        interface (GUI)
 * 
 * See "AVR1614: Widget Toolkit - Getting Started".
 *
 * The window system is a module for organizing two dimensional windows.
 * Windows are organized in a tree strcture where each window can have
 * one parent but several children. The window system also allows
 * events to be queued and handled by the event handler of the affected
 * windows.
 *
 * A window is defined with the following properties:
 * - A position and area/size
 * - Relation to parent and children
 * - Visibility
 * - Background
 * - Behavior flags
 * - Event handler
 *
 * The window system can be used separately or together with the
 * \ref wtk_group "Widget toolkit".
 *
 * \section relation_sec Positioning and relations
 *
 * The windows are organized in a tree structure. A window can be used for
 * graphical user interface (GUI) elements drawn on a screen or display.
 * These elements are often called widgets. The window system can be used
 * to organize any built-in or custom widget. Some examples of widgets are
 * frame, static text, button, checkbox or more advanced widgets like an
 * analog clock.
 *
 * Each window can have children, and the child windows must be contained within
 * the area of the parent window. This means the child window can be as large
 * as, but not be larger than the parent window.
 * A root window filling the entire screen is created when the window
 * system is initialized with \ref win_init. If the screen orientation
 * changes the root window can be re-initialized with
 * \ref win_reset_root_geometry. A pointer to the root window is returned
 * from \ref win_get_root.
 *
 * The following figure shows the relations between windows that are used to
 * represent some example widgets. In the figure we show the top_child and
 * next_sibling pointers. The parent and prev_sibling pointers which point
 * in the opposite direction are omitted to simplify the figure.
 *
 * The figure also illustrates how the position and size affects how
 * the windows could be represented on a display.
 *
 * \image html gfx_win_overview.png
 *
 * \sa win_set_area
 * \sa win_create
 * \sa win_reparent
 * \sa win_get_parent
 *
 * \section visibility_sec Visibility
 * A window can only be shown if it has been mapped to the screen with the
 * \ref win_show function and that the parent windows are also mapped to the
 * screen.
 *
 * When a window is drawn, the following happens:
 * - If WIN_BEHAVIOR_REDRAW_PARENT attribute is set the parent will be drawn.
 * - Background for window will be drawn
 * - Event handler for window will be called to draw the window/widget.
 * - Children will be drawn starting with the bottom child and ending with the
 *   top child.
 *
 * \sa win_redraw
 * \sa win_show
 * \sa win_hide
 * \sa win_raise
 * \sa win_lower
 *
 * \section event_handling_sec Event handling
 * Propagation of events are an important part of the window system.
 * Events are added to the event queue with one of queue functions
 * (\ref win_queue_pointer_event, \ref win_queue_keyboard_event,
 * \ref win_queue_command_event). Pending events in the event queue can be
 * processed by calling the \ref win_process_events function in the main
 * application loop.
 *
 * The events are handled differently depending on the event. Valid event types
 * are defined by \ref win_event_type.
 *
 * \sa win_create
 * \sa win_get_attributes
 * \sa win_set_attributes
 *
 * - Keyboard events are sent to the window which has focus. See
 *   \ref win_set_keyboard_focus. This means that the event handler for that
 *   window will be called. If the event handler does not accept the event
 *   (ie the event handler returns false), the event will be sent to
 *   the parent window. It will continue propagating to all parents until
 *   accepted. If no window accepts the event or no window has focus, the event
 *   will be discarded.
 *   \image html gfx_win_event_handling_keyboard_event.png
 *
 * - Command events are sent to the window which is set as recipient of the
 *   event \ref win_command_event "struct win_command_event".
 *   It will propagate up to parents in the same way as the keyboard events.
 *   \image html gfx_win_event_handling_command_event.png
 *
 * - Pointer events are handled a bit differently. If a window has requested to
 *   get all pointer events with the \ref win_grab_pointer function, the event
 *   handler for that window is called. The return value of this event handler
 *   is ignored.
 *   If no window has grabbed the pointer, the pointer event will start
 *   from the \ref win_root "root window". It will then search the children
 *   to find the window that is under the pointer. \ref win_is_inside_area
 *   If no window is found or the window under the pointer does not accept the
 *   event, it will search the recursively through the children.
 *   \see win_process_pointer_event.
 *   \image html gfx_win_event_handling_pointer_event.png
 *
 * - Window draw events are sent to the window to allow it to draw itself after
 *   the window system has drawn the background for the window.
 *   See \ref visibility_sec "window visibility"
 *
 * \section win_dependencies_sec Dependencies
 * This component driver depends on the following modules:
 * - \ref gfx_group "Graphics library"
 *
 * @{
 */

/** Attribute mask for updating window position. */
#define WIN_ATTR_POSITION       (1 << 0)
/** Attribute mask for updating window size. */
#define WIN_ATTR_SIZE           (1 << 1)
/** Attribute mask for updating window background type and color/pixmap. */
#define WIN_ATTR_BACKGROUND     (1 << 2)
/** Attribute mask for updating window event handler. */
#define WIN_ATTR_EVENTHANDLER   (1 << 3)
/** Attribute mask for updating window behavior flags. */
#define WIN_ATTR_BEHAVIOR       (1 << 4)
/** Attribute mask for updating window custom data. */
#define WIN_ATTR_CUSTOM         (1 << 5)

/** Behavior mask for raising a window if itself or children are pressed. */
#define WIN_BEHAVIOR_RAISE_ON_PRESS  (1 << 0)
/** Behavior mask for requiring redraw of parent, e.g. transparent windows. */
#define WIN_BEHAVIOR_REDRAW_PARENT   (1 << 1)

/** Window control struct, including the attributes and linked list control. */
struct win_window;

/** Geometric type describing a point or vector on screen, relative or
 * absolute. */
struct win_point {
	gfx_coord_t x;
	gfx_coord_t y;
};

/** Geometric type describing an area on screen. */
struct win_area {
	struct win_point pos;  /**< Top-left corner of area. */
	struct win_point size; /**< Width and height of area. */
};

/** Geometric type describing a clipping region, used when drawing windows. */
struct win_clip_region {
	/** Absolute coordinates of top-left window corner. */
	struct win_point origin;
	/** North-west (top-left) corner of clipping region. */
	struct win_point NW;
	/** South-east (bottom-right) corner of clipping region. */
	struct win_point SE;
};

/** Valid pointer event types. */
enum win_pointer_event_type {
	/** One or more buttons have been pressed somewhere. */
	WIN_POINTER_PRESS,
	/** Pointer has moved, with or without buttons. */
	WIN_POINTER_MOVE,
	/** One or more buttons have been released somewhere. */
	WIN_POINTER_RELEASE,
};

/** Event data for all pointer events, e.g. touch screen or mouse. */
struct win_pointer_event {
	/** Position of press/release, or destination of move. */
	struct win_point pos;
	/** True if position vector is relative. */
	bool is_relative;
	/** Absolute position of last event, set by window system. */
	struct win_point last_pos;
	/** Pressed, released or held-while-move buttons. */
	win_button_mask_t buttons;
	/** Type of this event. */
	enum win_pointer_event_type type;
};

/** Valid keyboard event types. */
enum win_keyboard_event_type {
	WIN_KEYBOARD_PRESS,   /**< A key has been pressed. */
	WIN_KEYBOARD_RELEASE  /**< A key has been released. */
};

/** Event data for all keyboard events, e.g. full keyboards or smaller
 * matrices. */
struct win_keyboard_event {
	win_keycode_t keycode;        /**< Key code for pressed or released key. */
	enum win_keyboard_event_type type; /**< Type of this event. */
};

/** Event data for command events, e.g. a button widget action command. */
struct win_command_event {
	struct win_window *sender;    /**< Window that sent the event, or NULL. */
	struct win_window *recipient; /**< Intended recipient of command. */
	win_command_t data;       /**< Custom data, depending on command type. */
};

/** Valid event types sent to a window event handler. */
enum win_event_type {
	/** Pointer event, more details in the event itself. */
	WIN_EVENT_POINTER,
	/** Keyboard event, more details in the event itself. */
	WIN_EVENT_KEYBOARD,
	/** Command event, more details in the event itself. */
	WIN_EVENT_COMMAND,
	/** Window was just raised to top inside its parent. */
	WIN_EVENT_RAISE,
	/** Another window just raised to top. */
	WIN_EVENT_UNRAISE,
	/** Just got keyboard focus. */
	WIN_EVENT_GETFOCUS,
	/** Just lost keyboard focus. */
	WIN_EVENT_LOSEFOCUS,
	/** Request to draw contents, after background. */
	WIN_EVENT_DRAW,
	/** Attributes updated, attribute mask included. */
	WIN_EVENT_ATTRIBUTES,
	/** Request to free all allocated memory. */
	WIN_EVENT_DESTROY,
};

/** Event data for all events. */
struct win_event {
	clock_jiffy_t timestamp;   /**< Timestamp set when event was queued. */
	enum win_event_type type;  /**< Type of this event. */
	union {
		/** Details for pointer events. */
		struct win_pointer_event pointer;
		/** Details for keyboard events. */
		struct win_keyboard_event keyboard;
		/** Details for command events. */
		struct win_command_event command;
	};
};

/**
 * \brief Function pointer type for window event handlers.
 *
 * \param win Pointer to window to handle the event for.
 * \param type Event type specifier.
 * \param data Pointer to event-specific data.
 *
 * \retval true if event was accepted by the window.
 * \retval false if event was rejected by the window.
 */
typedef bool (*win_event_handler_t)(
	struct win_window *win,
	enum win_event_type type,
	const void *data);

/** Data type holding window behavior flags. */
typedef uint8_t win_behavior_t;

/** Window attribute data. */
struct win_attributes {
	/** Position and size of window, relative to parent. */
	struct win_area area;

	/** Window background */
	struct gfx_bitmap *background;

	/** Event handler callback, or NULL. */
	win_event_handler_t event_handler;
	/** Window behavior flags. */
	win_behavior_t behavior;
	/** Custom window data, e.g. link to associated widget. */
	void *custom;
};

/** Datatype holding attribute masks, used when updating attributes. */
typedef uint8_t win_attribute_mask_t;

void win_init(void);
struct win_window *win_get_root(void);
struct win_window *win_get_parent(const struct win_window *win);
void win_reset_root_geometry(void);
void win_set_attributes(
		struct win_window *win,
		const struct win_attributes *new_attributes,
		win_attribute_mask_t attribute_mask);
void win_set_area(
		struct win_window *win,
		const struct win_area *new_area,
		win_attribute_mask_t attribute_mask);
const struct win_attributes *win_get_attributes(const struct win_window *win);
const struct win_area *win_get_area(const struct win_window *win);
void *win_get_custom_data(const struct win_window *win);
struct win_window *win_create(
		struct win_window *parent,
		const struct win_attributes *attributes);
void win_destroy(struct win_window *win);
void win_reparent(
		struct win_window *child,
		struct win_window *new_parent);
void win_show(struct win_window *win);
void win_redraw(struct win_window *win);
void win_hide(struct win_window *win);
void win_raise(struct win_window *win);
void win_lower(struct win_window *win);
void win_queue_pointer_event(const struct win_pointer_event *event);
void win_queue_keyboard_event(const struct win_keyboard_event *event);
void win_queue_command_event(const struct win_command_event *event);
void win_process_events(void);
void win_set_keyboard_focus(struct win_window *win);
void win_grab_pointer(struct win_window *win);
void win_translate_win_to_root(struct win_window const *start_win,
		struct win_point *return_pos);
bool win_is_inside_clip(
		const struct win_clip_region *clip,
		const struct win_point *point);
bool win_is_inside_area(
		const struct win_area *area,
		const struct win_point *point);
bool win_is_inside_window(
		const struct win_window *win,
		const struct win_point *point);
void win_compute_union(struct win_area *area, const struct win_area *merge);
bool win_compute_intersection(
		struct win_clip_region *clip,
		const struct win_area *area);
bool win_compute_clipping(
		const struct win_window *win,
		const struct win_area *dirty_area,
		struct win_clip_region *clip);
void win_inflate_area(struct win_area* area, int16_t size);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* WIN_H */
