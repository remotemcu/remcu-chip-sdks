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

#ifndef REGIONS_H_INCLUDED
#define REGIONS_H_INCLUDED

#define REGIONS_INFO_SIZE          (INFO_SIZE)
#define REGIONS_INFO_RESERVED_SIZE (INFO_SIZE/4 - 6 - 12/4)
/** Boot informations (for regions) */
typedef struct regions_info {
	/** Firmware length in regions */
	uint32_t length[2];
	/** Firmware signature in regions */
	uint32_t signature[2];
	/** Firmware to boot in region # (0 or 1) */
	uint32_t boot_region;
	/** Software trigger to force action */
	uint32_t trigger;
	/** Boot file name, if update from extended memory (8+.+3) */
	char  boot_file_name[12];
	/** padding words */
	uint32_t padding[REGIONS_INFO_RESERVED_SIZE];
} regions_info_t;

void region_info_read(void *addr, struct regions_info *info);
void region_info_write(void *addr, struct regions_info *info);
uint32_t region_signature(void *addr, uint32_t size);
bool region_check_valid(void *addr, uint32_t size, uint32_t signature);

#endif /* REGIONS_H_INCLUDED */
