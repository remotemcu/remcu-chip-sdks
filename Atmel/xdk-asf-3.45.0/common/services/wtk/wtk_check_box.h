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
#ifndef WTK_CHECK_BOX_H
#define WTK_CHECK_BOX_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup wtk_group
 *
 * \defgroup wtk_check_box_group Check box widget
 * @{
 */

struct wtk_check_box;

struct wtk_check_box *wtk_check_box_create(struct win_window *parent,
		struct win_area const *area,
		char const *caption, bool selected, win_command_t command_data);
struct win_window *wtk_check_box_as_child(struct wtk_check_box *check_box);
win_command_t wtk_check_box_get_command(struct wtk_check_box *check_box);
void wtk_check_box_toggle(struct wtk_check_box *check_box);
void wtk_check_box_set(struct wtk_check_box *check_box, bool selected);
bool wtk_check_box_is_selected(struct wtk_check_box const *check_box);
void wtk_check_box_size_hint(struct win_point *size, const char *caption);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
