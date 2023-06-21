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
#ifndef WTK_ICON_BUTTON_H
#define WTK_ICON_BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup wtk_group
 *
 * \defgroup wtk_icon_group Icon button widget
 * @{
 */

struct wtk_icon_group;
struct wtk_icon_group *wtk_icon_group_create(void);
struct wtk_icon_button *wtk_icon_group_get_selected(struct wtk_icon_group *group);
struct wtk_icon_button;

struct wtk_icon_button *wtk_icon_button_create(struct win_window *parent,
		struct win_area const *area, struct gfx_bitmap *icon,
		bool selected, struct wtk_icon_group *group,
		win_command_t command_data);
void wtk_icon_button_size_hint(struct win_point *size, const struct gfx_bitmap *icon_image);
struct win_window *wtk_icon_button_as_child(struct wtk_icon_button
		*icon_button);
win_command_t wtk_icon_button_get_command(struct wtk_icon_button *icon_button);
void wtk_icon_button_select(struct wtk_icon_button *icon_button);
bool wtk_icon_button_is_selected(struct wtk_icon_button const *icon_button);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
