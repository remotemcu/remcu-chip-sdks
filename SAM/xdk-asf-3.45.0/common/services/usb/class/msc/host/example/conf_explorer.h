/**
 * \file
 *
 * \brief FAT configuration file.
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

#ifndef _CONF_EXPLORER_H_
#define _CONF_EXPLORER_H_

#include "compiler.h"


//! Include files and compile options (do not change these settings).
#define LIB_MEM               <string.h>
#define LIB_CTRLACCESS        "ctrl_access.h"

//! Supported FATs (\c true or \c false).
#define FS_FAT_12             true
#define FS_FAT_16             true
#define FS_FAT_32             true

//! The explorer may support either the ASCII or the UNICODE string format, or both.
#define FS_ASCII              true
#define FS_UNICODE            false

//! The navigator may support only the first partition (\c false), or multiple partitions (\c true).
#define FS_MULTI_PARTITION    false

//! Maximal number of characters in file path.
#define MAX_FILE_PATH_LENGTH  30

//! Maximal size of configuration file.
#define MAX_CONFIG_FILE_SIZE  110

//! Level of features.
//! Select among:
//!  - \c FSFEATURE_READ:           All read functions.
//!  - \c FSFEATURE_WRITE:          nav_file_copy(), nav_file_paste(), nav_file_del(), file_create(), file_open(MODE_WRITE), file_write(), file_putc().
//!  - \c FSFEATURE_WRITE_COMPLET:  FSFEATURE_WRITE functions and nav_drive_format(), nav_dir_make(), nav_file_rename(), nav_file_dateset(), nav_file_attributset().
//!  - \c FSFEATURE_ALL:            All functions.
#define FS_LEVEL_FEATURES     (FSFEATURE_READ | FSFEATURE_WRITE_COMPLET)

//! Number of caches used to store a cluster list of files (interesting in case of many `open file').
//! In player mode, 1 is OK (shall be > 0).
#define FS_NB_CACHE_CLUSLIST  1

//! Maximal number of simultaneous navigators.
#define FS_NB_NAVIGATOR       2

//! Number of reserved navigators (ids from \c 0 to <tt>(FS_NB_RESERVED_NAVIGATOR - 1)</tt>).
#define FS_NB_RESERVED_NAV    0

/*! \name Navigator Affiliations
 *
 * Define the affiliations of the navigators.
 *
 * \note The explorer always has the navigator ID 0.
 */
//! @{

//! The explorer uses the navigator ID 1 to open the `copy file' and the ID 0 to open the `paste file'.
#define FS_NAV_ID_COPYFILE    1
#define FS_NAV_ID_USHELL_CMD  0
//! @}

/*! \name Playlist Configuration
 */
//! @{

//! Cache to store the path of a file (here, mapped onto a global buffer).
#define pl_cache_path           g_buffer

//! Size of cache to store the path of a file.
#define PL_CACHE_PATH_MAX_SIZE  sizeof(g_buffer)

//! Playlist format: \c false for ASCII or \c true for UNICODE.
#define PL_UNICODE              false

//! @}


#endif  // _CONF_EXPLORER_H_
