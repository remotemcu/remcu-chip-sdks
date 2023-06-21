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
#ifndef WTK_PROGRESS_BAR_H
#define WTK_PROGRESS_BAR_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup wtk_group
 *
 * \defgroup wtk_progress_bar_group Progress bar widget
 * @{
 */

/**
 * \defgroup wtk_progress_bar_options_group Progress bar widget options
 * These options can be ORed together to specify the behaviour of a
 * progress bar widget when creating it with \ref wtk_progress_bar_create
 * @{
 */

/**
 * \name Progress bar orientation configuration options.
 * For use with the option parameter of \ref wtk_progress_bar_create
 * @{
 */

/** Progress bar is horizontally oriented. */
#define WTK_PROGRESS_BAR_HORIZONTAL    (0 << 0)
/** Progress bar is vertically oriented. */
#define WTK_PROGRESS_BAR_VERTICAL      (1 << 0)

/** @} */

/**
 * \name Progress bar widget invert configuration options.
 * For use with the option parameter of \ref wtk_progress_bar_create
 * @{
 */

/** Progress bar is inverted. */
#define WTK_PROGRESS_BAR_INVERT        (1 << 1)

/** @} */

/** @} */

struct wtk_progress_bar;

struct wtk_progress_bar *wtk_progress_bar_create(struct win_window *parent,
		struct win_area const *area, uint8_t maximum, uint8_t value,
		gfx_color_t fill_color, gfx_color_t background_color,
		uint8_t option);
struct win_window *wtk_progress_bar_as_child(struct wtk_progress_bar *bar);
uint8_t wtk_progress_bar_get_value(struct wtk_progress_bar *bar);
bool wtk_progress_bar_set_value(struct wtk_progress_bar *bar, uint8_t value);
void wtk_progress_bar_set_colors(struct wtk_progress_bar *bar,
		gfx_color_t color1, gfx_color_t color2);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
