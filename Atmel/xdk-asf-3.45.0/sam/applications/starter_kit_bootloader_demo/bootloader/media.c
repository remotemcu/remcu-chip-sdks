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

#include "bootloader.h"

//#define media_dbgp dbg_print
#define media_dbgp(...)

/** Media driver struct */
struct media_driver {
	void (*init)(void);        /* Initialize */
	void (*cleanup)(void);     /* Cleanup */

	bool (*connect)(void);     /* Connect/Mount */
	void (*disconnect)(void);  /* Disconnect/Unmount */

	uint32_t lun_id;           /* LUN ID */
};

/** Medias drivers */
static struct media_driver medias[MEDIA_NUM_MAX] = {
#ifdef MEDIA_USE_SD
	{
		media_sd_init,
		media_sd_cleanup,
		media_sd_connect,
		media_sd_disconnect,
		LUN_ID_SD_MMC_0_MEM,
	},
#endif
#ifdef MEDIA_USE_MSD
	{
		media_msd_init,
		media_msd_cleanup,
		media_msd_connect,
		media_msd_disconnect,
		0xFF, /* Not available now */
	},
#endif
#ifdef MEDIA_USE_NAND
	{
		media_nand_init,
		media_nand_cleanup,
		media_nand_connect,
		media_nand_disconnect,
		0xFF, /* Not available now */
	},
#endif
#ifdef MEDIA_USE_ETH
	{
		media_eth_init,
		media_eth_cleanup,
		media_eth_connect,
		media_eth_disconnect,
		0xFF, /* No FS */
	},
#endif
#ifdef MEDIA_USE_COMM
	{
		media_comm_init,
		media_comm_cleanup,
		media_comm_connect,
		media_comm_disconnect,
		0xFF, /* No FS */
	},
#endif
};
/** Current media selection */
static enum media_types media_selection = MEDIA_NUM_MAX;

/** File name to check */
static char* file_names[1]  = {0};

/** File list to check */
static char** file_list = 0;
static uint32_t file_list_size = 0;

/** Media connection status */
static bool media_connected = false;

/* Shared file system data */
static FRESULT res;
static FATFS fs;
static FIL file_object;
static char file_path[20] = {'0', ':', 0};

/**
 * Initialize media with default check file list.
 * If boot file name is not set, the listed files will be checked.
 * \param list File check list (should be const list)
 * \param list_size Check list size
 */
void media_init(const char** list, const uint32_t list_size)
{
	uint32_t i;
	dbg_print("media: init ...\r\n");

	file_names[0] = 0;
	file_list = (char**)list;
	file_list_size = list_size;
	if (list) {
		dbg_print("media: boot list (priority high ~ low)\r\n");
		for (i = 0; i < list_size; i ++) {
			dbg_print(" #%u : %s\r\n", (unsigned)i, file_list[i]);
		}
	}
	for (i = 0; i < MEDIA_NUM_MAX; i ++) {
		if (medias[i].init) {
			medias[i].init();
		}
	}

	dbg_print("media: init ... done\r\n");
}

/**
 * Set boot file name to check.
 * If the boot file name is specified, the default check list will be disabled.
 * \param name The target boot file name
 */
void media_set_file_name(const char* name)
{
	file_names[0] = (char*)name;
	if (name) {
		dbg_print("media: boot file name %s\r\n", name);
	}
}

/**
 * Cleanup medias
 */
void media_cleanup(void)
{
	int i;
	dbg_print("media: cleanup ...\r\n");

	media_disconnect();
	for (i = 0; i < MEDIA_NUM_MAX; i ++) {
		if (medias[i].cleanup) {
			medias[i].cleanup();
		}
	}

	dbg_print("media: cleanup ... done\r\n");
}

/**
 * Change current media selection
 * \param media Media to select
 */
void media_select(enum media_types media)
{
	if (media_selection == media) {
		return;
	}
	media_dbgp("media select: %s\r\n", media_get_type_str(media));
	if (media_connected) {
		media_disconnect();
	}
	media_selection = media;
}

/**
 * Find first valid file in list
 * \param list File name list
 * \param list_size List size
 * \param open Open the file if it's found
 * \return Pointer to the file name found
 */
static char* _find_valid_file(char** list, uint32_t list_size, bool open)
{
	uint32_t i;
	for (i = 0; i < list_size; i ++) {
		/* Skip NULL string */
		if (list[i] == 0) {
			continue;
		}
		/* Prepare right path "0:...." */
		file_path[2] = 0;
		strcat(file_path, list[i]);
		res = f_open(&file_object,
				(char const *)file_path,
				FA_READ | FA_OPEN_EXISTING);
		/* If file not exist, continue next */
		if (res != FR_OK) {
			continue;
		}
		/* Found */
		if (!open) {
			f_close(&file_object);
		}
		return list[i];
	}
	return 0;
}

/**
 * Connect to source media
 * (If source is file, check if file exists)
 * \return true if connected success.
 */
bool media_connect(void)
{
	char ** check_list = file_names[0] ? file_names : file_list;
	uint32_t list_size = file_names[0] ? 1 : file_list_size;
	char *name;
	if (media_selection >= MEDIA_NUM_MAX) {
		media_dbgp("media conn: no valid media selected\r\n");
		return false;
	}
	if (!medias[media_selection].connect()) {
		media_dbgp("media conn: connect failed\r\n");
		return false;
	}
	if (medias[media_selection].lun_id == 0xFF) {
		/* No File related, just return */
		media_connected = true;
		goto media_connect_exit;
	}
	/* Mount FS */
	res = f_mount(medias[media_selection].lun_id, &fs);
	if (FR_INVALID_DRIVE == res) {
		media_dbgp("media conn: FS mount fail\r\n");
		return false;
	}
	/* Check files */
	name = _find_valid_file(check_list, list_size, false);
	if (name) {
		media_dbgp("media conn: found file %s\r\n", name);
		media_connected = true;
	}
media_connect_exit:
	return media_connected;
}

/**
 * Disconnect from source media
 */
void media_disconnect(void)
{
	if (media_connected) {
		if (medias[media_selection].lun_id != 0xFF) {
			/* Cleanup FS */
			f_close(&file_object);
			memset(&fs, 0, sizeof(FATFS));
		}
		/* Disconnect */
		if (medias[media_selection].disconnect) {
			medias[media_selection].disconnect();
		}
		media_connected = false;
	}
}

/**
 * Load file from source media
 * \param addr Target address to load to
 * \param size Max file size that can accept
 * \param block_buffer Buffer allocated for each memory block
 * \param block_size   The block buffer size
 * \param save_data_exec Function to save buffer to target
 */
uint32_t media_load_file(void* addr, uint32_t size,
	uint8_t* block_buffer, uint32_t block_size,
	uint32_t (*save_data_exec)(void* dst,void* src,uint32_t size))
{
	char ** check_list = file_names[0] ? file_names : file_list;
	uint32_t list_size = file_names[0] ? 1 : file_list_size;
	uint32_t mem_addr = (uint32_t)addr;
	uint32_t total;
	uint32_t file_size;
	UINT bytes;
	bool done;
	if (!media_connected) {
		media_dbgp("media load: not connected\r\n");
		return 0;
	}
	if (!_find_valid_file(check_list, list_size, true)) {
		media_dbgp("media load: file open fail: %d\r\n", res);
		return 0;
	}
	file_size = f_size(&file_object);
	if (file_size > size) {
		media_dbgp("media load: file too big: %u > %u\r\n",
			(unsigned)file_size, (unsigned)size);
		f_close(&file_object);
		return 0;
	}
	dbg_print("media load: from file %s\r\n", file_path);
	for (total = 0, done = false; !done; ) {
		res = f_read(&file_object, block_buffer, block_size, &bytes);
		if (res != FR_OK) {
			media_dbgp("media load: file read %u: %d\r\n",
				(unsigned)bytes, res);
			f_close(&file_object);
			return 0;
		}
		if (bytes) {
			if (save_data_exec) {
				save_data_exec((void*)mem_addr, block_buffer, bytes);
			}
			mem_addr += bytes;
			total    += bytes;
		}
		if (bytes < block_size) {
			done = true;
		}
	}
	return total;
}

/**
 * Scan files under the root path and display them
 * \param full_path true to display full file path, else file name only.
 */
void media_scan_files(bool full_path)
{
	FILINFO fno;
	DIR dir;
	char *fname;
#if _USE_LFN
	char lfname[_MAX_LFN + 1];
	fno.lfname = lfname;
	fno.lfsize = sizeof(lfname);
#endif

	if (media_selection >= MEDIA_NUM_MAX) {
		return;
	}
	if (medias[media_selection].lun_id == 0xFF) {
		/* No files */
		return;
	}
	media_connect();

	file_path[2] = 0;

	/* Open the directory */
	res = f_opendir(&dir, file_path);
	if (res == FR_OK) {
		for (;;) {
			res = f_readdir(&dir, &fno);
			if (res != FR_OK || fno.fname[0] == 0) {
				break;
			}

#if _USE_LFN
			fname = *fno.lfname ? fno.lfname : fno.fname;
#else
			fname = fno.fname;
#endif
			if (*fname == '.') {
				continue;
			}

			/* Display if it's file */
			if (0 == (fno.fattrib & AM_DIR)) {
				if (full_path) {
					dbg_print("%s/%s\r\n", file_path, fname);
				} else {
					dbg_print("%s\r\n", fname);
				}
			}
		}
	}
}

