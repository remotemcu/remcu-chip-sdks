/**
 * \file
 *
 * \brief Spin control widget
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

#include "sysfont.h"
#include "stdio.h"
#include "gfx_mono.h"
#include "gfx_mono_spinctrl.h"

PROGMEM_DECLARE(gfx_mono_color_t, spin_indicator_data[]) = {
	GFX_MONO_SPINCTRL_SPIN_INDICATOR_BITMAP
};

PROGMEM_DECLARE(gfx_mono_color_t, indicator_data[]) = {
	GFX_MONO_SPINCTRL_INDICATOR_BITMAP
};

struct gfx_mono_bitmap gfx_mono_spinctrl_bitmap_spin_indicator = {
	.height = GFX_MONO_SPINCTRL_SPIN_INDICATOR_HEIGHT,
	.width = GFX_MONO_SPINCTRL_SPIN_INDICATOR_WIDTH,
	.type = GFX_MONO_BITMAP_PROGMEM,
	.data.progmem = spin_indicator_data
};

struct gfx_mono_bitmap gfx_mono_spinctrl_bitmap_indicator = {
	.height = GFX_MONO_SPINCTRL_INDICATOR_HEIGHT,
	.width = GFX_MONO_SPINCTRL_INDICATOR_WIDTH,
	.type = GFX_MONO_BITMAP_PROGMEM,
	.data.progmem = indicator_data
};

/**
 * \brief Draw or delete indicator arrow in front of spinner
 *
 * \param *spinner initialized gfx_mono_spinctrl struct
 * \param draw     true on draw, false on delete
 */
static void gfx_mono_spinctrl_draw_indicator(struct gfx_mono_spinctrl *spinner,
		bool draw)
{
	if (draw) {
		gfx_mono_put_bitmap(&gfx_mono_spinctrl_bitmap_indicator, 0,
				spinner->y);
	} else {
		gfx_mono_draw_filled_rect(0, spinner->y,
				GFX_MONO_SPINCTRL_INDICATOR_WIDTH,
				GFX_MONO_SPINCTRL_INDICATOR_HEIGHT,
				GFX_PIXEL_CLR);
	}
}

/**
 * \brief Draw or delete indicator in front of spinner data
 *
 * \param spinner  pointer to initialized gfx_mono_spinctrl struct
 * \param draw     true on draw, false on delete
 */
static void gfx_mono_spinctrl_draw_spin_indicator(struct gfx_mono_spinctrl
		*spinner, bool draw)
{
	if (draw) {
		gfx_mono_put_bitmap(&gfx_mono_spinctrl_bitmap_spin_indicator,
				GFX_MONO_LCD_WIDTH - GFX_MONO_SPINCTRL_SPIN_INDICATOR_WIDTH,
				spinner->y);
	} else {
		gfx_mono_draw_filled_rect(GFX_MONO_LCD_WIDTH -
				GFX_MONO_SPINCTRL_SPIN_INDICATOR_WIDTH,
				spinner->y,
				GFX_MONO_SPINCTRL_SPIN_INDICATOR_WIDTH,
				GFX_MONO_SPINCTRL_SPIN_INDICATOR_HEIGHT,
				GFX_PIXEL_CLR);
	}
}

/**
 * \brief Draw OK button at bottom of screen
 *
 * This function draws an OK button at the bottom of the screen. It will
 * also draw an indicator arrow in front of the button if the indicator bool
 * is true. If the draw bool is false, the OK button will be deleted, and if
 * the indicator bool is false, the indicator will be deleted.
 *
 * \param draw       true on draw, false on delete
 * \param indicator  true on draw indicator, false on delete
 */
static void gfx_mono_spinctrl_draw_button(bool draw, bool indicator)
{
	uint8_t width;
	uint8_t height;
	uint8_t offset;
	char string_buf[22];

	/* Clear bottom line */
	gfx_mono_draw_filled_rect(0,
			(SYSFONT_HEIGHT + 1) *
			GFX_MONO_SPINCTRL_MAX_ELEMENTS_IN_SPINCOLLECTION,
			GFX_MONO_LCD_WIDTH, SYSFONT_HEIGHT, GFX_PIXEL_CLR);

	snprintf(string_buf, sizeof(string_buf), "OK");
	gfx_mono_get_string_bounding_box(string_buf, &sysfont, &width, &height);
	offset = (GFX_MONO_LCD_WIDTH - width) / 2;

	if (draw) {
		/* Draw OK button in the middle of the last line */
		gfx_mono_draw_string(string_buf, offset,
				(SYSFONT_HEIGHT + 1) *
				GFX_MONO_SPINCTRL_MAX_ELEMENTS_IN_SPINCOLLECTION,
				&sysfont);
		if (indicator) {
			/* Draw indicator arrow in front of button */
			gfx_mono_put_bitmap(&gfx_mono_spinctrl_bitmap_indicator,
					offset - GFX_MONO_SPINCTRL_INDICATOR_WIDTH,
					(SYSFONT_HEIGHT + 1) *
					GFX_MONO_SPINCTRL_MAX_ELEMENTS_IN_SPINCOLLECTION);
		} else {
			/* Delete indicator */
			gfx_mono_draw_filled_rect(offset -
					GFX_MONO_SPINCTRL_INDICATOR_WIDTH,
					(SYSFONT_HEIGHT + 1) *
					GFX_MONO_SPINCTRL_MAX_ELEMENTS_IN_SPINCOLLECTION,
					GFX_MONO_SPINCTRL_INDICATOR_WIDTH,
					GFX_MONO_SPINCTRL_INDICATOR_HEIGHT,
					GFX_PIXEL_CLR);
		}
	} else {
		/* Delete OK button */
		gfx_mono_draw_filled_rect(
				offset - GFX_MONO_SPINCTRL_INDICATOR_WIDTH,
				(SYSFONT_HEIGHT + 1) *
				GFX_MONO_SPINCTRL_MAX_ELEMENTS_IN_SPINCOLLECTION, 20,
				SYSFONT_HEIGHT, GFX_PIXEL_CLR);
	}
}

/**
 * \brief Draw spinner at its position.
 *
 * This function draws a spinner at its position.
 * The title of the spinner is only drawn if the redraw option is set.
 * If the spinner is in focus, arrows will be drawn next to the spinner value
 * to indicate that it is spinnable.
 *
 * \param spinner  pointer to initialized gfx_mono_spinctrl struct
 * \param redraw   true if title of spinner should be drawn
 */
void gfx_mono_spinctrl_draw(struct gfx_mono_spinctrl *spinner, bool redraw)
{
	char string_buf[GFX_MONO_SPINCTRL_INT_SPINNER_WIDTH];
	uint8_t index;
	uint8_t offset;

	if (redraw) {
		/* Clear line */
		gfx_mono_draw_filled_rect(0, spinner->y, GFX_MONO_LCD_WIDTH,
				SYSFONT_HEIGHT, GFX_PIXEL_CLR);
		/* Draw title */
		gfx_mono_draw_progmem_string((char PROGMEM_PTR_T)spinner->title,
				GFX_MONO_SPINCTRL_INDICATOR_WIDTH + 1,
				spinner->y, &sysfont);
	}

	if (spinner->in_focus) {
		gfx_mono_spinctrl_draw_spin_indicator(spinner, true);
	} else {
		gfx_mono_spinctrl_draw_spin_indicator(spinner, false);
	}

	if (spinner->datatype == SPINTYPE_INTEGER) {
		offset = GFX_MONO_LCD_WIDTH -
				(SYSFONT_WIDTH *
				GFX_MONO_SPINCTRL_INT_SPINNER_WIDTH);
		snprintf(string_buf, sizeof(string_buf), "%d",
				spinner->integer_data);
		/* Delete previous spinner data */
		gfx_mono_draw_filled_rect(offset, spinner->y,
				GFX_MONO_LCD_WIDTH - offset -
				GFX_MONO_SPINCTRL_SPIN_INDICATOR_WIDTH,
				SYSFONT_HEIGHT,
				GFX_PIXEL_CLR);
		/* Draw integer data */
		gfx_mono_draw_string(string_buf, offset, spinner->y, &sysfont);
	} else if (spinner->datatype == SPINTYPE_STRING) {
		index = spinner->strings.index;
		offset = GFX_MONO_LCD_WIDTH -
				(SYSFONT_WIDTH *
				GFX_MONO_SPINCTRL_STRING_SPINNER_WIDTH);

		/* Delete previous spinner data */
		gfx_mono_draw_filled_rect(offset, spinner->y,
				GFX_MONO_LCD_WIDTH - offset -
				GFX_MONO_SPINCTRL_SPIN_INDICATOR_WIDTH,
				SYSFONT_HEIGHT,
				GFX_PIXEL_CLR);

		/* Draw string data */
		gfx_mono_draw_progmem_string(
				(char PROGMEM_PTR_T)spinner->strings.data[index], offset,
				spinner->y, &sysfont);
	}
}

/**
 * \brief Initialize a spinner.
 *
 * This function initializes a spinner to either
 * \ref gfx_mono_spinctrl_type_t "SPINTYPE_STRING" spinner that spins through
 * the strings in a \ref PROGMEM_STRING_T or a
 * \ref gfx_mono_spinctrl_type_t "SPINTYPE_INTEGER" spinner that spins through
 * integers.
 * If the spinner type is SPINTYPE_INTEGER, it will spin from lower_limit to
 * upper_limit.
 * If the spinner type is SPINTYPE_STRING, a pointer to a PROGMEM_STRING_T must
 * be provided, and the spinner will spin through the strings starting at
 * index lower_limit ending at index upper_limit.
 * The y parameter specifies where to place the spinner on the screen, but is
 * overwritten if the spinner is put in a spincollection.
 *
 * \param spinner      pointer to initialized gfx_mono_spinctrl struct
 * \param datatype     typer of spinner, integer or string
 * \param title        title of spinner
 * \param data         pointer to progmem string array if datatype is string.
 *                     NULL if datatype is integer.
 * \param lower_limit  lower limit and start value of spinner's data
 * \param upper_limit  upper limit of spinner's data
 * \param y            y position of spinner
 */
void gfx_mono_spinctrl_init(struct gfx_mono_spinctrl *spinner,
		gfx_mono_spinctrl_type_t datatype, PROGMEM_STRING_T title,
		PROGMEM_STRING_T *data, int16_t lower_limit,
		int16_t upper_limit,
		gfx_coord_t y)
{
	/* Initialization of spinner parameters */
	spinner->title = title;
	spinner->datatype = datatype;
	spinner->lower_limit = lower_limit;
	spinner->upper_limit = upper_limit;
	spinner->y = y;
	spinner->in_focus = false;
	spinner->last_saved_value = spinner->lower_limit;

	if (datatype == SPINTYPE_STRING) {
		spinner->strings.data = data;
		spinner->strings.index = lower_limit;
	} else {
		spinner->integer_data = lower_limit;
	}
}

/**
 * \brief Initialize a spincollection.
 *
 * This function initializes a spincollection to which spinners can be added.
 *
 * \param collection pointer to gfx_mono_spinctrl_spincollection to Initialize
 */
void gfx_mono_spinctrl_spincollection_init(struct
		gfx_mono_spinctrl_spincollection *collection)
{
	collection->active_spinner = false;
	collection->current_selection = 0;
	collection->number_of_spinners = 0;
	collection->init = true;
}

/**
 * \brief Add spinner to spincollection
 *
 * This function adds an initialized spinner to a spincollection and positions
 * it below any other spinners in the spincollection on the screen. The
 * spinners in the spincollection are linked together and number of spinners is
 * updated.
 * It is not possible to add more spinners than
 * \ref GFX_MONO_SPINCTRL_MAX_ELEMENTS_IN_SPINCOLLECTION "maximum number of
 * spinners in a spincollection".
 *
 * \param spinner       pointer to initialized gfx_mono_spinctrl struct to add
 *                      to collection
 * \param spinners      pointer to initialized gfx_mono_spinctrl_spincollection
 *                      struct
 *
 */
void gfx_mono_spinctrl_spincollection_add_spinner(struct
		gfx_mono_spinctrl *spinner,
		struct gfx_mono_spinctrl_spincollection *spinners)
{
	uint8_t i;
	struct gfx_mono_spinctrl *lastspinner;

	/* Do not add more spinner elements than maximum number of spinners */
	if (spinners->number_of_spinners >=
			GFX_MONO_SPINCTRL_MAX_ELEMENTS_IN_SPINCOLLECTION) {
		return;
	}

	/* Place new spinner below previous spinners on screen */
	spinner->y = (SYSFONT_HEIGHT + 1) * spinners->number_of_spinners;

	/* Add pointer to the spinner in spincollection if empty */
	if (spinners->number_of_spinners == 0) {
		spinners->collection = spinner;
	} else {
		lastspinner = spinners->collection;
		for (i = 1; i < spinners->number_of_spinners; i++) {
			lastspinner = lastspinner->next;
		}
		/* Link the new spinner to the current last spinner in the
		 * collection */
		lastspinner->next = spinner;
		/* Link the current last spinner as previous spinner for new
		 * spinner */
		spinner->prev = lastspinner;
	}

	/* Set added spinner as last spinner in collection */
	spinners->collection_last = spinner;
	/* Update number of spinners in collection */
	spinners->number_of_spinners++;
}

/**
 * \brief Show spincollection
 *
 * This function draws all the spinners in a spincollection to the screen,
 * together with an OK button at the bottom. It also draws an indicator arrow
 * in front of the top spinner.
 *
 * \param spinners pointer to initialized spincollection to display
 */
void gfx_mono_spinctrl_spincollection_show(struct
		gfx_mono_spinctrl_spincollection *spinners)
{
	uint8_t i;
	struct gfx_mono_spinctrl *iterator;

	/* Clear screen */
	gfx_mono_draw_filled_rect(0, 0, GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT,
			GFX_PIXEL_CLR);

	/* Make sure there are spinners in the collection */
	if (spinners->number_of_spinners == 0) {
		return;
	}

	/* Draw spinners on screen */
	iterator = spinners->collection;
	for (i = 0; i < spinners->number_of_spinners; i++) {
		gfx_mono_spinctrl_draw(iterator, true);
		iterator = iterator->next;
	}
	/* Draw OK button at bottom of screen */
	gfx_mono_spinctrl_draw_button(true, false);
	/* Draw indicator arrow in front of first spinner */
	gfx_mono_spinctrl_draw_indicator(spinners->collection, true);
}

/**
 * \brief Step up spinner data
 *
 * This function steps up the data, making sure it does not go
 * beyond the upper limit. Wraps around if it does.
 *
 * \param spinner pointer to initialized spinner.
 */
static void gfx_mono_spinctrl_step_up(struct gfx_mono_spinctrl *spinner)
{
	/* Check if spinner type is integer or string, increment integer data or
	 * move to next string index.
	 */
	if (spinner->datatype == SPINTYPE_INTEGER) {
		if (spinner->integer_data < spinner->upper_limit) {
			spinner->integer_data++;
		} else {
			spinner->integer_data = spinner->lower_limit;
		}
	} else if (spinner->datatype == SPINTYPE_STRING) {
		if (spinner->strings.index < spinner->upper_limit) {
			spinner->strings.index++;
		} else {
			(spinner->strings.index) = spinner->lower_limit;
		}
	}
}

/**
 * \brief Step down spinner data
 *
 * * This function steps down the data, making sure it does not go
 * below the lower limit. Wraps around if it does.
 *
 * \param spinner pointer to initialized spinner.
 */
static void gfx_mono_spinctrl_step_down(struct gfx_mono_spinctrl *spinner)
{
	/* Check if spinner type is integer or string, increment integer data,
	 * move to next string index.
	 */
	if (spinner->datatype == SPINTYPE_INTEGER) {
		if (spinner->integer_data > spinner->lower_limit) {
			spinner->integer_data--;
		} else {
			spinner->integer_data = spinner->upper_limit;
		}
	} else if (spinner->datatype == SPINTYPE_STRING) {
		if (spinner->strings.index > (spinner->lower_limit)) {
			spinner->strings.index--;
		} else {
			spinner->strings.index = spinner->upper_limit;
		}
	}
}

/**
 * \brief Update single spinner depending on input.
 *
 * \param spinner pointer to initialized spinner.
 * \param keycode  keycode to process
 *
 * \retval selected            selected spinner value
 * \retval GFX_MONO_SPINCTRL_EVENT_IDLE spinner spinning
 * \retval GFX_MONO_SPINCTRL_EVENT_BACK spinner deselected
 */
int16_t gfx_mono_spinctrl_process_key(struct gfx_mono_spinctrl *spinner,
		uint8_t keycode)
{
	switch (keycode) {
	case GFX_MONO_SPINCTRL_KEYCODE_DOWN:
		if (spinner->in_focus) {
			gfx_mono_spinctrl_step_down(spinner);
			/* Update spinner on display */
			gfx_mono_spinctrl_draw(spinner, false);
		}

		/* Nothing selected yet */
		return GFX_MONO_SPINCTRL_EVENT_IDLE;

	case GFX_MONO_SPINCTRL_KEYCODE_UP:
		if (spinner->in_focus) {
			gfx_mono_spinctrl_step_up(spinner);
			/* Update spinner on display */
			gfx_mono_spinctrl_draw(spinner, false);
		}

		/* Nothing selected yet */
		return GFX_MONO_SPINCTRL_EVENT_IDLE;

	case GFX_MONO_SPINCTRL_KEYCODE_ENTER:
		if (spinner->in_focus) {
			if (spinner->datatype == SPINTYPE_INTEGER) {
				spinner->in_focus = false;
				gfx_mono_spinctrl_draw(spinner, false);
				/* Store saved value in case of aborting spinner
				 * later */
				spinner->last_saved_value
					= spinner->integer_data;
				/* Got what we want. Return selection. */
				return spinner->integer_data;
			} else if (spinner->datatype == SPINTYPE_STRING) {
				spinner->in_focus = false;
				gfx_mono_spinctrl_draw(spinner, false);
				/* Store saved value in case of aborting spinner
				 * later */
				spinner->last_saved_value
					= spinner->strings.index;
				/* Got what we want. Return selection. */
				return spinner->strings.index;
			}
		} else {
			/* Spinner selected */
			spinner->in_focus = true;
			gfx_mono_spinctrl_draw(spinner, false);
			return GFX_MONO_SPINCTRL_EVENT_IDLE;
		}

	case GFX_MONO_SPINCTRL_KEYCODE_BACK:
		/* User pressed "back" key, */
		spinner->in_focus = false;
		/* Spinner choice aborted, show last saved value instead */
		if (spinner->datatype == SPINTYPE_INTEGER) {
			spinner->integer_data = spinner->last_saved_value;
		} else if (spinner->datatype == SPINTYPE_STRING) {
			spinner->strings.index = spinner->last_saved_value;
		}

		gfx_mono_spinctrl_draw(spinner, false);
		return GFX_MONO_SPINCTRL_EVENT_BACK;

	default:
		/* Unknown key event */
		return GFX_MONO_SPINCTRL_EVENT_IDLE;
	}
}

/**
 * \brief Update spincollection on screen depending on input
 *
 * This function returns \ref GFX_MONO_SPINCTRL_EVENT_FINISH if user has
 * pressed the OK button. The spinner choices can then be extracted from the
 * results array. If a spinner is of type SPINTYPE_STRING, the index of the
 * progmem string will be stored in the results array, else the selected
 * integer value will be stored.
 * The choice from the first spinner added to the spincollection will be stored
 * at index 0 in the results array, the second at index 1 and so on.
 * If user has pressed the back button, \ref GFX_MONO_SPINCTRL_EVENT_BACK is
 * returned, signalling that the application should be cancelled.
 *
 * \param spinners       pointer to initialized
 *                       gfx_mono_spinctrl_spincollection
 * \param keycode        keycode to process
 * \param results        array to store results from the spinners, must be of
 *                       same length as number of spinners
 *
 * \retval GFX_MONO_SPINCTRL_EVENT_FINISH  user pressed ok button
 * \retval GFX_MONO_SPINCTRL_EVENT_BACK    user cancelled
 * \retval GFX_MONO_SPINCTRL_EVENT_IDLE    user is navigating in spincollection
 */
int16_t gfx_mono_spinctrl_spincollection_process_key(struct
		gfx_mono_spinctrl_spincollection *spinners, uint8_t keycode,
		int16_t results[])
{
	uint8_t i;
	struct gfx_mono_spinctrl *iterator;

	/* Make sure there are spinners in the collection, if not, cancel */
	if (spinners->number_of_spinners == 0) {
		return GFX_MONO_SPINCTRL_EVENT_BACK;
	}

	/* Store initial values in results array first time function is run */
	if (spinners->init) {
		iterator = spinners->collection;
		for (i = 0; i < spinners->number_of_spinners; i++) {
			if (iterator->datatype == SPINTYPE_INTEGER) {
				results[i] = iterator->integer_data;
			} else {
				results[i] = iterator->strings.index;
			}

			iterator = iterator->next;
		}
		spinners->init = false;
	}

	/* Find current spinner selection */
	iterator = spinners->collection;
	if (spinners->current_selection != GFX_MONO_SPINCTRL_BUTTON) {
		for (i = 0; i < spinners->current_selection; i++) {
			iterator = iterator->next;
		}
	}

	if (spinners->active_spinner) {
		/* Process chosen spinner */
		spinners->selection = gfx_mono_spinctrl_process_key(iterator,
				keycode);
		if (spinners->selection == GFX_MONO_SPINCTRL_EVENT_BACK) {
			/* User has exited spinner without saving the result */
			spinners->active_spinner = false;
		} else if (spinners->selection !=
				GFX_MONO_SPINCTRL_EVENT_IDLE) {
			/* Value selected, store in array */
			results[spinners->current_selection]
				= spinners->selection;
			/* Step out of spinner and into spincollection */
			spinners->active_spinner = false;
		}

		return GFX_MONO_SPINCTRL_EVENT_IDLE;
	} else {
		switch (keycode) {
		case GFX_MONO_SPINCTRL_KEYCODE_DOWN:
			if (spinners->current_selection ==
					GFX_MONO_SPINCTRL_BUTTON) {
				spinners->current_selection = 0;
				/* Delete indicator arrow in front of button */
				gfx_mono_spinctrl_draw_button(true, false);
				/* Draw indicator arrow in front of first
				 * spinner */
				gfx_mono_spinctrl_draw_indicator(iterator,
						true);
			} else if (spinners->current_selection <
					spinners->number_of_spinners - 1) {
				/* Delete indicator arrow */
				gfx_mono_spinctrl_draw_indicator(iterator,
						false);
				spinners->current_selection++;
				/* Draw indicator arrow in front of new spinner */
				gfx_mono_spinctrl_draw_indicator(iterator->next,
						true);
			} else {
				/* Delete indicator arrow */
				gfx_mono_spinctrl_draw_indicator(iterator,
						false);
				spinners->current_selection
					= GFX_MONO_SPINCTRL_BUTTON;
				/* Draw indicator arrow in front of button */
				gfx_mono_spinctrl_draw_button(true, true);
			}

			return GFX_MONO_SPINCTRL_EVENT_IDLE;

		case GFX_MONO_SPINCTRL_KEYCODE_UP:
			if (spinners->current_selection ==
					GFX_MONO_SPINCTRL_BUTTON) {
				/* Delete indicator arrow in front of button */
				gfx_mono_spinctrl_draw_button(true, false);
				spinners->current_selection
					= spinners->number_of_spinners - 1;
				/* Draw indicator arrow in front of new spinner */
				gfx_mono_spinctrl_draw_indicator(
						spinners->collection_last,
						true);
			} else if (spinners->current_selection > 0) {
				/* Delete indicator arrow */
				gfx_mono_spinctrl_draw_indicator(iterator,
						false);
				spinners->current_selection--;
				/* Draw indicator arrow in front of new spinner */
				gfx_mono_spinctrl_draw_indicator(iterator->prev,
						true);
			} else {
				/* Delete indicator arrow */
				gfx_mono_spinctrl_draw_indicator(iterator,
						false);
				spinners->current_selection
					= GFX_MONO_SPINCTRL_BUTTON;
				/* Draw indicator arrow in front of button */
				gfx_mono_spinctrl_draw_button(true, true);
			}

			return GFX_MONO_SPINCTRL_EVENT_IDLE;

		case GFX_MONO_SPINCTRL_KEYCODE_ENTER:
			if (spinners->current_selection ==
					GFX_MONO_SPINCTRL_BUTTON) {
				/* Finished with all selections, return */
				return GFX_MONO_SPINCTRL_EVENT_FINISH;
			} else {
				/* Spinner selected, send next keycode directly
				 * to spinner */
				gfx_mono_spinctrl_process_key(iterator,
						keycode);
				spinners->active_spinner = true;
				return GFX_MONO_SPINCTRL_EVENT_IDLE;
			}

		case GFX_MONO_SPINCTRL_KEYCODE_BACK:
			/* User pressed "back" key, */
			return GFX_MONO_SPINCTRL_EVENT_BACK;

		default:
			/* Unknown key event */
			return GFX_MONO_SPINCTRL_EVENT_IDLE;
		}
	}
}
