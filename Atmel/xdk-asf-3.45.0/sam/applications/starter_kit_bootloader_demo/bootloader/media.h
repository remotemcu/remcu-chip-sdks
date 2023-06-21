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
#ifndef MEDIA_H_INCLUDED
#define MEDIA_H_INCLUDED

/** Media sources types (check first ~ last) */
typedef enum media_types {
#ifdef MEDIA_USE_SD
	MEDIA_SD,
#endif
#ifdef MEDIA_USE_MSD
	MEDIA_MSD,
#endif
#ifdef MEDIA_USE_NAND
	MEDIA_NAND,
#endif
#ifdef MEDIA_USE_ETH
	MEDIA_ETH,
#endif
#ifdef MEDIA_USE_COMM
	MEDIA_COMM,
#endif
	MEDIA_NUM_MAX
} media_types_t;
/** Media names for debug */
static const char *media_types_str[] = {
#ifdef MEDIA_USE_SD
	"SD/MMC",
#endif
#ifdef MEDIA_USE_MSD
	"MSD",
#endif
#ifdef MEDIA_USE_NAND
	"NAND"
#endif
#ifdef MEDIA_USE_ETH
	"ETH",
#endif
#ifdef MEDIA_USE_COMM
	"COMM",
#endif
};
/**
 * Return the media name
 * \return const string of media name
 */
__always_inline static const char* media_get_type_str(enum media_types media)
{
	return media_types_str[media];
}


void media_init(const char** file_check_list, const uint32_t list_size);
void media_set_file_name(const char* name);

void media_cleanup(void);

void media_select(enum media_types media);
bool media_connect(void);
void media_disconnect(void);
uint32_t media_load_file(void* addr, uint32_t size,
	uint8_t* block_buffer, uint32_t block_size,
	uint32_t (*save_data_exec)(void* dst,void* src,uint32_t size));
void media_scan_files(bool show_full_path);

#ifdef MEDIA_USE_SD
/* Media: SD card */
extern void media_sd_init(void);
extern void media_sd_cleanup(void);
extern bool media_sd_connect(void);
extern void media_sd_disconnect(void);
#endif


#ifdef MEDIA_USE_MSD
/* Media: MSD */
#define media_msd_init           0
#define media_msd_cleanup        0
#define media_msd_connect        0
#define media_msd_disconnect     0
#endif


#ifdef MEDIA_USE_NAND
/* Media: NAND */
#define media_nand_init          0
#define media_nand_cleanup       0
#define media_nand_connect       0
#define media_nand_disconnect    0
#endif


#ifdef MEDIA_USE_ETH
/* Media: ETHERNET */
#define media_eth_init           0
#define media_eth_cleanup        0
#define media_eth_connect        0
#define media_eth_disconnect     0
#endif


#ifdef MEDIA_USE_COMM
/* Media: COMM */
#define media_comm_init          0
#define media_comm_cleanup       0
#define media_comm_connect       0
#define media_comm_disconnect    0
#endif

#endif /* #ifndef MEDIA_H_INCLUDED */
