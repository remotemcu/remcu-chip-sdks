/**
 * \file
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

#ifndef MULTI_LANGUAGE_DISPLAY_H_INCLUDED
#define MULTI_LANGUAGE_DISPLAY_H_INCLUDED

#include "compiler.h"

/* Interface functions. */
void multi_language_show_switch_info(void);
void multi_language_show_start_info(void);
void multi_language_show_temperature_info(void);
void multi_language_show_light_info(void);
void multi_language_show_end_info(void);
void multi_language_show_no_sd_info(void);
void multi_language_show_sd_info(void);
void multi_language_show_normal_card_info(void);
void multi_language_show_high_capacity_card_info(void);
void multi_language_show_unknow_card_info(void);
void multi_language_show_card_size_info(char *p_string,
		uint32_t sd_card_size);
void multi_language_show_no_fatfs_info(void);
void multi_language_show_no_files_info(void);
void multi_language_show_browse_info(void);
void multi_language_show_file_name(uint8_t page,
		const char *string);

#endif /* MULTI_LANGUAGE_DISPLAY_H_INCLUDED*/
