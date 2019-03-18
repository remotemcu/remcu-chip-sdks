/**
 * \file
 *
 * \brief Virtual file system management.
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

#include "lwipopts.h"

#if defined(HTTP_RAW_USED)

#include <string.h>
#include "fs.h"
#include "fsdata.h"

/**
 * \brief Open the specified filename in the virtual file system.
 *
 * \param name Filename to open.
 * \param file Pointer to an allocated struct fs_file, to be filled by fs_open
 * if the specified filename is found.
 *
 * \return 1 on success, 0 otherwise.
 */
int fs_open(char *name, struct fs_file *file)
{
	struct fsdata_file_noconst *f;

	for (f = (struct fsdata_file_noconst *)FS_ROOT;
			f != NULL;
			f = (struct fsdata_file_noconst *)f->next) {
		if (!strcmp(name, (char *)f->name)) {
			file->data = (char *)f->data;
			file->len = f->len;
			return 1;
		}
	}
	return 0;
}

#endif /* HTTP_RAW_USED */
