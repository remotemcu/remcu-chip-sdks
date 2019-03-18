/**
 * \file
 *
 * \brief Frame widget implementation
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
#include <compiler.h>
#include <stdint.h>
#include <stdlib.h>
#include <membag.h>
#include <string.h>
#include <wtk.h>

/**
 * \ingroup wtk_frame_group
 * @{
 */

/*
 * Private prototypes are required due to circular references of the functions
 */
static bool wtk_frame_handler(struct win_window *win,
		enum win_event_type type, void const *data);
static void wtk_handle_frame_press(struct wtk_frame *frame,
		struct win_pointer_event const *event);
static void wtk_handle_frame_move(struct wtk_frame *frame,
		struct win_pointer_event const *event);
static void wtk_handle_frame_release(struct wtk_frame *frame,
		struct win_pointer_event const *event);

static void wtk_handle_resize_press(struct wtk_frame *frame,
		struct win_pointer_event const *event);
static void wtk_handle_resize_move(struct wtk_frame *frame,
		struct win_pointer_event const *event);
static void wtk_handle_resize_release(struct wtk_frame *frame,
		struct win_pointer_event const *event);
static void wtk_resize_frame(struct wtk_frame *frame,
		struct win_area const *contents_area);

static void wtk_prepare_drag(struct win_point const *pos);
static bool wtk_is_drag_threshold_exceeded(struct win_point const *pos);
static void wtk_start_drag(struct win_point const *pos);
static void wtk_continue_drag(struct win_point const *last_pos,
		struct win_point const *pos);
static void wtk_stop_drag(struct win_point const *last_pos);

/** Drag origin position during drag operations. */
static struct win_point wtk_drag_origin;

/** Storage for saved screen beneath drag origin, NULL when not dragging. */
static gfx_color_t *wtk_drag_origin_pixmap;

/** Storage for saved screen beneath drag target, NULL when not dragging. */
static gfx_color_t *wtk_drag_target_pixmap;

/** Frame background bitmap */
static struct gfx_bitmap wtk_frame_background = {
	.type = GFX_BITMAP_SOLID,
	.data.color = WTK_FRAME_BACKGROUND_COLOR,
};

/**
 * Valid states for frame, relevant to pointer and keyboard operations.
 * \internal
 */
enum wtk_frame_state {
	/** Normal state, no moving or resizing. */
	WTK_FRAME_NORMAL,
	/** Waiting for move, from key or drag. */
	WTK_FRAME_AWAITING_MOVE,
	/** Currently moving. */
	WTK_FRAME_MOVING,
	/** Waiting for resize, from key or drag. */
	WTK_FRAME_AWAITING_RESIZE,
	/** Currently resizing. */
	WTK_FRAME_RESIZING
};

/**
 * \brief Frame control struct
 *
 * This is the frame control struct. It contains references to the windows
 * composing the frame, as well as non-window information required.
 *
 * \internal
 * \note Structure fields are only internally accessible, only pointers to
 *       structure is needed externally.
 */
struct wtk_frame {
	/** Container, ultimate widget parent. */
	struct win_window *container;
	/** Contents, holds child widgets. */
	struct win_window *contents;
	/** The resize handle window. */
	struct win_window *resize;
	/** Copy of caption string. */
	char *caption;
	/** Current state. */
	enum wtk_frame_state state;

	/** Frame command event handler. */
	wtk_frame_handler_t frame_handler;
	/** Data for applications and handlers. */
	void *custom_data;
};

/**
 * This function returns a reference to the window that should be used as a
 * parent for child widgets and windows. This corresponds to the internal area
 * inside borders and title bar.
 *
 * \param frame Frame widget to be a parent.
 *
 * \return Window to be used as parent for child contents.
 */
struct win_window *wtk_frame_as_parent(struct wtk_frame *frame)
{
	Assert(frame);
	return frame->contents;
}

/**
 * This function returns a reference to the window that should be used when
 * managing the widget, such as move, resize, destroy and reparenting.
 *
 * \param frame Frame widget to manage.
 *
 * \return Window to be used for managing the frame.
 */
struct win_window *wtk_frame_as_child(struct wtk_frame *frame)
{
	Assert(frame);
	return frame->container;
}

/**
 * This function returns the custom data from the frame's attributes.
 * The custom data can be used for e.g. linking to associated applications.
 *
 * \param frame Pointer to frame.
 *
 * \return Copy of the custom data.
 */
void *wtk_frame_get_custom_data(struct wtk_frame const *frame)
{
	Assert(frame);
	return frame->custom_data;
}

/**
 * This function is a helper function for the wtk_frame_handler() function.
 * It is called when a pointer PRESS event is sent to the container window.
 * This function prepares a drag operation.
 *
 * \param frame Frame the received the event.
 * \param event Pointer event information.
 */
static void wtk_handle_frame_press(struct wtk_frame *frame,
		struct win_pointer_event const *event)
{
	switch (frame->state) {
	/* If we are in normal state, prepare for move drag. */
	case WTK_FRAME_NORMAL:
		wtk_prepare_drag(&(event->pos));
		win_grab_pointer(frame->container);

		frame->state = WTK_FRAME_AWAITING_MOVE;
		break;

	default:
		break;
	}
}

/**
 * This function is a helper function for the wtk_frame_handler() function.
 * It is called when a pointer MOVE event is sent to the container window.
 * This function either starts or continues a drag operation, depending on
 * current state.
 *
 * \param frame Frame the received the event.
 * \param event Pointer event information.
 */
static void wtk_handle_frame_move(struct wtk_frame *frame,
		struct win_pointer_event const *event)
{
	switch (frame->state) {
	/* If we are waiting for move, check drag threshold and start
	 * drag if threshold exceeded.
	 */
	case WTK_FRAME_AWAITING_MOVE:
		if (wtk_is_drag_threshold_exceeded(&(event->pos))) {
			wtk_start_drag(&(event->pos));
			frame->state = WTK_FRAME_MOVING;
		}

		break;

	/* If we are already moving, continue drag. */
	case WTK_FRAME_MOVING:
		wtk_continue_drag(&(event->last_pos), &(event->pos));
		break;

	default:
		break;
	}
}

/**
 * This function is a helper function for the wtk_frame_handler() function.
 * It is called when a pointer RELEASE event is sent to the container window.
 * This function completes the move operation if the RELEASE event was inside
 * the parent window's boundaries.
 *
 * \param frame Frame the received the event.
 * \param event Pointer event information.
 */
static void wtk_handle_frame_release(struct wtk_frame *frame,
		struct win_pointer_event const *event)
{
	bool is_inside;

	switch (frame->state) {
	/* If we were moving when released, ungrab pointer and move if
	 * release was inside parent window extents.
	 */
	case WTK_FRAME_MOVING:
		/* Ungrab pointer. */
		wtk_stop_drag(&(event->last_pos));
		win_grab_pointer(NULL);
		frame->state = WTK_FRAME_NORMAL;

		/* Check release position. */
		is_inside = win_is_inside_window(win_get_parent(frame->
				container), &(event->pos));

		/* If inside, move frame according to drag distance. */
		if (is_inside) {
			struct win_area area = *win_get_area(frame->container);
			area.pos.x += event->pos.x - wtk_drag_origin.x;
			area.pos.y += event->pos.y - wtk_drag_origin.y;
			win_set_area(frame->container, &area,
					WIN_ATTR_POSITION);
		}

		break;

	default:
		break;
	}
}

/**
 * This function is a helper function for the wtk_frame_handler() function.
 * It is called when a pointer PRESS event is sent to the resize window.
 * This function prepares a drag operation.
 *
 * \param frame Frame the received the event.
 * \param event Pointer event information.
 */
static void wtk_handle_resize_press(struct wtk_frame *frame,
		struct win_pointer_event const *event)
{
	switch (frame->state) {
	/* If we are in normal state, prepare for resize drag. */
	case WTK_FRAME_NORMAL:
		wtk_prepare_drag(&(event->pos));
		win_grab_pointer(frame->resize);

		frame->state = WTK_FRAME_AWAITING_RESIZE;
		break;

	default:
		break;
	}
}

/**
 * This function is a helper function for the wtk_frame_handler() function.
 * It is called when a pointer MOVE event is sent to the resize window.
 * This function either starts or continues a drag operation, depending on
 * current state.
 *
 * \param frame Frame the received the event.
 * \param event Pointer event information.
 */
static void wtk_handle_resize_move(struct wtk_frame *frame,
		struct win_pointer_event const *event)
{
	switch (frame->state) {
	/* If we are waiting for resize, check drag threshold and start
	 * drag if threshold exceeded.
	 */
	case WTK_FRAME_AWAITING_RESIZE:
		if (wtk_is_drag_threshold_exceeded(&(event->pos))) {
			wtk_start_drag(&(event->pos));
			frame->state = WTK_FRAME_RESIZING;
		}

		break;

	/* If we are already resizing, continue drag. */
	case WTK_FRAME_RESIZING:
		wtk_continue_drag(&(event->last_pos), &(event->pos));
		break;

	default:
		break;
	}
}

/**
 * This function is a helper function for the wtk_frame_handler() function.
 * It is called when a pointer RELEASE event is sent to the resize window.
 * This function completes the resize operation if the RELEASE event was inside
 * the parent window's boundaries.
 *
 * \param frame Frame the received the event.
 * \param event Pointer event information.
 */
static void wtk_handle_resize_release(struct wtk_frame *frame,
		struct win_pointer_event const *event)
{
	bool is_inside;

	switch (frame->state) {
	/* If we were resizing when released, ungrab pointer and resize
	 * if release was inside parent window extents.
	 */
	case WTK_FRAME_RESIZING:
		/* Ungrab pointer. */
		wtk_stop_drag(&(event->last_pos));
		win_grab_pointer(NULL);
		frame->state = WTK_FRAME_NORMAL;

		/* Check release position. */
		is_inside = win_is_inside_window(win_get_parent(frame->
				container), &(event->pos));

		/* If inside, resize frame according to drag distance. */
		if (is_inside) {
			struct win_area contents_area
				= *win_get_area(frame->contents);

			contents_area.size.x += event->pos.x -
					wtk_drag_origin.x;
			contents_area.size.y += event->pos.y -
					wtk_drag_origin.y;

			wtk_resize_frame(frame, &contents_area);
		}

		break;

	default:
		break;
	}
}

/**
 * This function is a helper function used when creating a frame widget and
 * when handling resize events. Given a new size for the contents window, it
 * resizes and rearranges the windows composing the frame so that the frame
 * decorations are properly sized and positioned.
 *
 * \param frame Frame to resize.
 * \param contents_area New size for the contents window.
 */
static void wtk_resize_frame(struct wtk_frame *frame,
		struct win_area const *contents_area)
{
	struct win_area container_area;
	/* Make local copy, so that we can change it. */
	struct win_area area = *contents_area;

	/* Make sure size is not too small, override if it is. */
	if (area.size.x < WTK_FRAME_MIN_WIDTH) {
		area.size.x = WTK_FRAME_MIN_WIDTH;
	}

	if (area.size.y < WTK_FRAME_MIN_HEIGHT) {
		area.size.y = WTK_FRAME_MIN_HEIGHT;
	}

	/* Change the size of the contents window first. */
	win_set_area(frame->contents, &area, WIN_ATTR_SIZE);

	/* Read back size, in case other event handlers put other minimum
	 * limits to the size.
	 */
	area = *win_get_area(frame->contents);

	/* Get current area of container and change size according to the new
	 * size of the contents window. Then update the container window size.
	 */
	container_area = *win_get_area(frame->container);

	container_area.size.x = area.size.x +
			WTK_FRAME_LEFTBORDER + WTK_FRAME_RIGHTBORDER;

	container_area.size.y = area.size.y +
			WTK_FRAME_TOPBORDER + WTK_FRAME_TITLEBAR_HEIGHT +
			WTK_FRAME_BOTTOMBORDER;

	win_set_area(frame->container, &container_area, WIN_ATTR_SIZE);

	if (frame->resize) {
		/* Get current area of resize window and change position
		 * according to the new size of the container window. The size
		 * of the resize window is unchanged.
		 */
		struct win_area resize_area = *win_get_area(frame->resize);

		resize_area.pos.x = container_area.size.x -
				WTK_FRAME_RESIZE_WIDTH;

		resize_area.pos.y = container_area.size.y -
				WTK_FRAME_RESIZE_HEIGHT;

		win_set_area(frame->resize, &resize_area, WIN_ATTR_POSITION);
	}
}

/**
 * This function prepares for a drag operation. No drag is started yet, but
 * the drag origin is stored. To start a drag operation, one would repeatedly
 * check if the drag threshold is exceeded, then call the wtk_start_drag()
 * function.
 *
 * \param pos Pointer position for drag origin.
 */
static void wtk_prepare_drag(struct win_point const *pos)
{
	/* Store drag origin, so that we know where to draw the origin symbol
	 * if the drag threshold is exceeded.
	 */
	wtk_drag_origin = *pos;
}

/**
 * This function compares a given position with the drag origin prepared by the
 * wtk_prepare_drag() function. If either the X or Y distance exceeds the
 * WTK_DRAG_THRESHOLD value, this function returns true. That is when the widget
 * event handler should call wtk_start_drag().
 *
 * \param pos Position to compare.
 *
 * \return True if threshold exceeded.
 */
static bool wtk_is_drag_threshold_exceeded(struct win_point const *pos)
{
	bool isExceeded
		= (pos->x < (wtk_drag_origin.x - WTK_DRAG_THRESHOLD)) ||
			(pos->x > (wtk_drag_origin.x + WTK_DRAG_THRESHOLD)) ||
			(pos->y < (wtk_drag_origin.y - WTK_DRAG_THRESHOLD)) ||
			(pos->y > (wtk_drag_origin.y + WTK_DRAG_THRESHOLD));

	return isExceeded;
}

/**
 * This function starts the drag operation. It will allocate memory to store
 * the screen behind the drag handles and draw the handles themselves.
 * Do not call this function unless wtk_prepare_drag() has been called first
 * with the drag origin position.
 * If there is not enough memory, this function will no draw anything, but it
 * is still safe to call wtk_continue_drag() and wtk_stop_drag().
 *
 * \param pos Current position of drag target.
 */
static void wtk_start_drag(struct win_point const *pos)
{
	/* Allocate memory for bitmaps. */
	wtk_drag_origin_pixmap = membag_alloc(
			(WTK_DRAG_PIXMAP_SIZE * WTK_DRAG_PIXMAP_SIZE) *
			sizeof(gfx_color_t)
			);
	if (!wtk_drag_origin_pixmap) {
		goto outofmem_origin;
	}

	wtk_drag_target_pixmap = membag_alloc(
			(WTK_DRAG_PIXMAP_SIZE * WTK_DRAG_PIXMAP_SIZE) *
			sizeof(gfx_color_t)
			);
	if (!wtk_drag_target_pixmap) {
		goto outofmem_target;
	}

	/* Make sure we can draw on the entire screen, since dragging is not
	 * necessarily limited to within one window.
	 */
	gfx_set_clipping(0, 0, gfx_get_width() - 1, gfx_get_height() - 1);

	/* Store screen underneath and draw drag origin symbol. */
	gfx_get_pixmap(wtk_drag_origin_pixmap, WTK_DRAG_PIXMAP_SIZE, 0, 0,
			wtk_drag_origin.x - WTK_DRAG_HANDLE_RADIUS,
			wtk_drag_origin.y - WTK_DRAG_HANDLE_RADIUS,
			WTK_DRAG_PIXMAP_SIZE, WTK_DRAG_PIXMAP_SIZE);

	gfx_draw_filled_circle(wtk_drag_origin.x, wtk_drag_origin.y,
			WTK_DRAG_HANDLE_RADIUS,
			WTK_DRAG_ORIGIN_COLOR, GFX_WHOLE);

	/* Store screen underneath and draw drag target symbol. */
	gfx_get_pixmap(wtk_drag_target_pixmap, WTK_DRAG_PIXMAP_SIZE, 0, 0,
			pos->x - WTK_DRAG_HANDLE_RADIUS,
			pos->y - WTK_DRAG_HANDLE_RADIUS,
			WTK_DRAG_PIXMAP_SIZE, WTK_DRAG_PIXMAP_SIZE);

	gfx_draw_filled_circle(pos->x, pos->y,
			WTK_DRAG_HANDLE_RADIUS,
			WTK_DRAG_TARGET_COLOR, GFX_WHOLE);

	return;

outofmem_target:
	membag_free(wtk_drag_origin_pixmap);
	wtk_drag_origin_pixmap = NULL;

outofmem_origin:
	return;
}

/**
 * This function updated the drag target handle graphics. Call this function
 * from the MOVE event handler of the dragging widget. This function needs
 * both the current position and the last used position. The last position will
 * be either the position handed to wtk_start_drag() or the "pos" parameter of
 * the last call to wtk_continue_drag(). The pointer event struct will keep this
 * value for you. No need to store it yourself.
 *
 * \param last_pos Last position.
 * \param pos Current position.
 */
static void wtk_continue_drag(struct win_point const *last_pos,
		struct win_point const *pos)
{
	/* Don't do any graphics if we did not get memory when drag started. */
	if (!wtk_drag_origin_pixmap || !wtk_drag_target_pixmap) {
		return;
	}

	/* Make sure we can draw on the entire screen, since dragging is not
	 * necessarily limited to within one window.
	 */
	gfx_set_clipping(0, 0, gfx_get_width() - 1, gfx_get_height() - 1);

	/* Restore screen underneath drag target symbol. */
	gfx_put_pixmap(wtk_drag_target_pixmap, WTK_DRAG_PIXMAP_SIZE, 0, 0,
			last_pos->x - WTK_DRAG_HANDLE_RADIUS,
			last_pos->y - WTK_DRAG_HANDLE_RADIUS,
			WTK_DRAG_PIXMAP_SIZE, WTK_DRAG_PIXMAP_SIZE);

	/* Store screen underneath and draw new drag target symbol. */
	gfx_get_pixmap(wtk_drag_target_pixmap, WTK_DRAG_PIXMAP_SIZE, 0, 0,
			pos->x - WTK_DRAG_HANDLE_RADIUS,
			pos->y - WTK_DRAG_HANDLE_RADIUS,
			WTK_DRAG_PIXMAP_SIZE, WTK_DRAG_PIXMAP_SIZE);

	gfx_draw_filled_circle(pos->x, pos->y,
			WTK_DRAG_HANDLE_RADIUS,
			WTK_DRAG_TARGET_COLOR, GFX_WHOLE);
}

/**
 * This function stops an ongoing drag operation. Do not call this unless
 * dragging has been started with wtk_start_drag() first. This function erases
 * the drag handles and frees any allocated memory.
 *
 * \param last_pos Last position, as for wtk_continue_drag().
 */
static void wtk_stop_drag(struct win_point const *last_pos)
{
	/* Don't do any graphics if we did not get memory when drag started. */
	if (!wtk_drag_origin_pixmap || !wtk_drag_target_pixmap) {
		return;
	}

	/* Make sure we can draw on the entire screen, since dragging is not
	 * necessarily limited to within one window.
	 */
	gfx_set_clipping(0, 0, gfx_get_width() - 1, gfx_get_height() - 1);

	/* Restore screen underneath drag origin symbol. */
	gfx_put_pixmap(wtk_drag_origin_pixmap, WTK_DRAG_PIXMAP_SIZE, 0, 0,
			wtk_drag_origin.x - WTK_DRAG_HANDLE_RADIUS,
			wtk_drag_origin.y - WTK_DRAG_HANDLE_RADIUS,
			WTK_DRAG_PIXMAP_SIZE, WTK_DRAG_PIXMAP_SIZE);

	/* Restore screen underneath drag target symbol. */
	gfx_put_pixmap(wtk_drag_target_pixmap, WTK_DRAG_PIXMAP_SIZE, 0, 0,
			last_pos->x - WTK_DRAG_HANDLE_RADIUS,
			last_pos->y - WTK_DRAG_HANDLE_RADIUS,
			WTK_DRAG_PIXMAP_SIZE, WTK_DRAG_PIXMAP_SIZE);

	/* Free memory when not dragging. */
	membag_free(wtk_drag_origin_pixmap);
	membag_free(wtk_drag_target_pixmap);
}

/**
 * This function is the window event handler for frame widgets.
 * It handles all events sent to the windows composing the widget.
 *
 * \param win Window receiving the event.
 * \param type The event type.
 * \param data Custom data, depending on event type.
 *
 * \return True if the event was recognized and accepted.
 */
static bool wtk_frame_handler(struct win_window *win,
		enum win_event_type type, void const *data)
{
	/* Custom data for windows of a widget points back to the widget itself. */
	struct wtk_frame *frame = (struct wtk_frame *)win_get_custom_data(win);

	switch (type) {
	case WIN_EVENT_DRAW:
	{
		/* For DRAW events, the data parameter points to the
		 * clipping region.
		 */
		struct win_clip_region const *clip
			= (struct win_clip_region const *)data;

		struct win_area const *area = win_get_area(win);

		/* Draw frame decorations if this is the container window. */
		if (win == frame->container) {
			/* Draw left border. */
			gfx_draw_filled_rect(clip->origin.x,
					clip->origin.y,
					WTK_FRAME_LEFTBORDER,
					area->size.y,
					WTK_FRAME_BORDER_COLOR);

			/* Draw right border. */
			gfx_draw_filled_rect(clip->origin.x +
					area->size.x -
					WTK_FRAME_RIGHTBORDER,
					clip->origin.y,
					WTK_FRAME_RIGHTBORDER,
					area->size.y,
					WTK_FRAME_BORDER_COLOR);

			/* Draw top border. */
			gfx_draw_filled_rect(clip->origin.x +
					WTK_FRAME_LEFTBORDER,
					clip->origin.y,
					area->size.x -
					WTK_FRAME_LEFTBORDER -
					WTK_FRAME_RIGHTBORDER,
					WTK_FRAME_TOPBORDER,
					WTK_FRAME_BORDER_COLOR);

			/* Draw bottom border. */
			gfx_draw_filled_rect(clip->origin.x +
					WTK_FRAME_LEFTBORDER,
					clip->origin.y + area->size.y -
					WTK_FRAME_BOTTOMBORDER,
					area->size.x -
					WTK_FRAME_LEFTBORDER -
					WTK_FRAME_RIGHTBORDER,
					WTK_FRAME_BOTTOMBORDER,
					WTK_FRAME_BORDER_COLOR);

			/* Draw title bar background. */
			gfx_draw_filled_rect(clip->origin.x +
					WTK_FRAME_LEFTBORDER,
					clip->origin.y +
					WTK_FRAME_TOPBORDER,
					area->size.x -
					WTK_FRAME_LEFTBORDER -
					WTK_FRAME_RIGHTBORDER,
					WTK_FRAME_TITLEBAR_HEIGHT,
					WTK_FRAME_TITLEBAR_COLOR);

			/* Draw caption string. */
			gfx_draw_string(frame->caption,
					clip->origin.x +
					WTK_FRAME_LEFTBORDER +
					WTK_FRAME_CAPTION_X,
					clip->origin.y +
					WTK_FRAME_TOPBORDER +
					WTK_FRAME_CAPTION_Y, &sysfont,
					GFX_COLOR_TRANSPARENT,
					WTK_FRAME_CAPTION_COLOR);
		}
		/* Draw resize handle if this is the resize window. */
		else if (win == frame->resize) {
			gfx_draw_filled_circle(clip->origin.x +
					area->size.x - 1,
					clip->origin.y + area->size.y -
					1, WTK_FRAME_RESIZE_RADIUS,
					WTK_FRAME_RESIZE_COLOR,
					GFX_QUADRANT1);
		}

		/* Always accept DRAW events, as the return value is
		 * ignored anyway for that event type.
		 */
		return true;
	}

	case WIN_EVENT_POINTER:
	{
		/* For POINTER events, the data parameter points to the
		 * pointer event information.
		 */
		struct win_pointer_event const *event
			= (struct win_pointer_event const *)data;

		/* Handle move if this is the container window. */
		if (win == frame->container) {
			switch (event->type) {
			case WIN_POINTER_PRESS:
				wtk_handle_frame_press(frame, event);
				break;

			case WIN_POINTER_MOVE:
				wtk_handle_frame_move(frame, event);
				break;

			case WIN_POINTER_RELEASE:
				wtk_handle_frame_release(frame, event);
				break;

			default:
				break;
			}
		}
		/* Handle resize if this is the resize handle. */
		else if (win == frame->resize) {
			switch (event->type) {
			case WIN_POINTER_PRESS:
				wtk_handle_resize_press(frame, event);
				break;

			case WIN_POINTER_MOVE:
				wtk_handle_resize_move(frame, event);
				break;

			case WIN_POINTER_RELEASE:
				wtk_handle_resize_release(frame, event);
				break;

			default:
				break;
			}
		}

		/* Accept all POINTER events so that it does not
		 * propagate up the window tree to our parent in case
		 * we did not click anything useful inside the frame.
		 */
		return true;
	}

	case WIN_EVENT_DESTROY:
	{
		/* When the container window is destroyed, also destroy
		 * the rest of the non-window frame allocations.
		 */
		if (win == frame->container) {
			/* Memory allocated for windows will be
			 * automatically destroyed by the window
			 * system. We must destroy other allocations.
			 */
			membag_free(frame->caption);
			membag_free(frame);
		}

		/* Always accept DESTROY events, as the return value is
		 * ignored anyway for that event type.
		 */
		return true;
	}

	case WIN_EVENT_COMMAND:
	{
		/* When commands are received either directly or
		 * propagated from child widgets and windows, send it
		 * to the frame handler.
		 */
		if (win == frame->container) {
			if (frame->frame_handler) {
				/* If the frame handler returns true,
				 * it wants us to destroy the frame.
				 * This is normally used by CLOSE
				 * buttons.
				 */
				bool shouldDestroy
					= frame->frame_handler(frame,
						(win_command_t)
						data);

				/* It is safe to destroy it here, since
				 * the event handling finished right
				 * after this handler returns, and no
				 * other references to this frame or
				 * its contents will be done.
				 */
				if (shouldDestroy) {
					win_destroy(frame->container);
				}

				/* Accept the event if there was a
				 * handler installed.
				 */
				return true;
			}
		}

		/* Reject the event if there was no handler, or this
		 * was not the container window at all.
		 */
		return false;
	}

	default:
		/* Reject unknown event types. */
		return false;
	}
}

/**
 * This function creates a new frame widget. It allocates required memory and
 * intializes necessary windows to create the widget. If there is not enough
 * memory, the function returns NULL.
 *
 * To destroy the widget and all its contents, and free its memory, call
 * win_destroy() on the frame's child reference, given by wtk_frame_as_child(),
 * like this: "win_destroy(wtk_frame_as_child(my_frame_ptr));".
 * The frame's internal area will equal the area parameter, but the total
 * extents will be slightly larger, to accommodate for titlebar, borders etc.
 *
 * \param parent Parent window.
 * \param area Area of the internal contents.
 * \param caption Pointer to caption string. Will be copied into widget.
 * \param allow_resize True if resize handle should be included on the frame.
 * \param frame_handler Optional command event handler, for applications.
 * \param custom_data Optional custom data link, for applications.
 *
 * \return Pointer to frame, or NULL if failed.
 */
struct wtk_frame *wtk_frame_create(struct win_window *parent,
		struct win_area const *area,
		char const *caption,
		bool allow_resize,
		wtk_frame_handler_t frame_handler, void *custom_data)
{
	struct win_attributes attr;
	struct wtk_frame *frame;

	Assert(area);
	Assert(caption);
	Assert(parent);

	/* Allocate memory for frame control data. */
	frame = membag_alloc(sizeof(struct wtk_frame));
	if (!frame) {
		goto outofmem_frame;
	}

	frame->state = WTK_FRAME_NORMAL;
	frame->frame_handler = frame_handler;
	frame->custom_data = custom_data;

	/* Allocate memory for caption string, and copy text. */
	frame->caption = membag_alloc((strlen(caption) + 1) * sizeof(char));
	if (!frame->caption) {
		goto outofmem_caption;
	}

	wtk_copy_string(frame->caption, caption);

	/* Start with valid area info, but only contents frame will keep the
	 * original area. The other frames will be resized properly at the end.
	 * All windows have the same event handler, and the same link back to
	 * the widget object.
	 */
	attr.area = *area;
	attr.event_handler = wtk_frame_handler;
	attr.custom = frame;

	/* Prepare container frame, which will contain title bar, border, size,
	 * handle etc.
	 */
	attr.background = NULL;
	attr.behavior = WIN_BEHAVIOR_RAISE_ON_PRESS;

	/* Create the container window, the proper size will be set later. */
	frame->container = win_create(parent, &attr);
	if (!frame->container) {
		goto outofmem_container;
	}

	/* Prepare the contents frame, which will contain whatever controls
	 * owned by the frame. Size will be equal to the given area parameter.
	 */
	attr.area.pos.x = WTK_FRAME_LEFTBORDER;
	attr.area.pos.y = WTK_FRAME_TOPBORDER + WTK_FRAME_TITLEBAR_HEIGHT;
	attr.background = &wtk_frame_background;
	attr.behavior = 0;

	frame->contents = win_create(frame->container, &attr);
	if (!frame->contents) {
		goto outofmem_contents;
	}

	/* Only create resize handle window if resize is allowed. */
	if (allow_resize) {
		/* Prepare resize handle. Proper position will be set later.
		 * Size is set here, though.
		 */
		attr.area.size.x = WTK_FRAME_RESIZE_WIDTH;
		attr.area.size.y = WTK_FRAME_RESIZE_HEIGHT;
		attr.background = NULL;
		attr.behavior = 0;

		frame->resize = win_create(frame->container, &attr);
		if (!frame->resize) {
			goto outofmem_resize;
		}

		win_show(frame->resize);
	} else {
		frame->resize = NULL;
	}

	/* Now, resize and rearrange according to size of contents frame, which
	 * is equal to the given area parameter.
	 */
	wtk_resize_frame(frame, area);

	/* Make sure internals are visible when frame is mapped. */
	win_show(frame->contents);

	return frame;

outofmem_resize:
	win_destroy(frame->contents);

outofmem_contents:
	win_destroy(frame->container);

outofmem_container:
	membag_free(frame->caption);

outofmem_caption:
	membag_free(frame);

outofmem_frame:
	return NULL;
}

/** @} */
