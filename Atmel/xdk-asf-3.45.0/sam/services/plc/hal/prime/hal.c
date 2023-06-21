/**
 * \file
 *
 * \brief PRIME Hardware Abstraction Layer
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
 * Support and FAQ: visit <a href="http://www.microchip.com/support/">Microchip Support</a>
 */
#include "string.h"
#include "stdarg.h"
#include "stdio.h"
#include "asf.h"
#include "parts.h"
#include "conf_prime.h"
#include "conf_pplc_if.h"

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/* @endcond */

/**
 * \weakgroup hal_prime_group
 * @{
 */

extern const char FWVS_VERSION[32];
extern const char FWVS_MODEL[16];
extern const char FWVS_VENDOR[16];
static const char FWVS_PIB_VERSION[PRIME_PIB_VERSION_LEN] = PRIME_PIB_VERSION;

/* PRIME version */
hal_sw_version_info x_sw_version;
/* Pointer to address to store FU firmware */
static uint32_t ul_fw_mem_address;
/* Firmware Information List */
static x_fw_info_list_t x_fw_info_list[HAL_FW_INFO_NUMBER_ID];

/* Pio Pin definition for external hardware watchdog activation */
static uint32_t PIO_WD;
static uint8_t PIO_WD_IDX;
static uint8_t PIO_WD_ID;
static uint8_t PIO_WD_PIN;

/**
 * \brief Init firmware information and copy to structure.
 *
 */
static void _init_fu_info_list(void)
{
	x_fw_info_list_t *px_info_list;

	px_info_list = &x_fw_info_list[0];
	/* InfoId = 0		Manufacturer / Vendor */
	px_info_list->uc_info_id = 0;
	px_info_list->uc_len_id = strlen(FWVS_VENDOR);
	if (px_info_list->uc_len_id > HAL_FW_INFO_ID_LIST_MAX_SIZE) {
		px_info_list->uc_len_id = HAL_FW_INFO_ID_LIST_MAX_SIZE;
	}

	memcpy(px_info_list->c_data_id, FWVS_VENDOR, px_info_list->uc_len_id);

	px_info_list++;
	/* InfoId = 1		Model / Product */
	px_info_list->uc_info_id = 1;
	px_info_list->uc_len_id = strlen(FWVS_MODEL);
	if (px_info_list->uc_len_id > HAL_FW_INFO_ID_LIST_MAX_SIZE) {
		px_info_list->uc_len_id = HAL_FW_INFO_ID_LIST_MAX_SIZE;
	}

	memcpy(px_info_list->c_data_id, FWVS_MODEL, px_info_list->uc_len_id);

	px_info_list++;
	/* InfoId = 2		Version */
	px_info_list->uc_info_id = 2;
	px_info_list->uc_len_id = strlen(FWVS_VERSION);
	if (px_info_list->uc_len_id > HAL_FW_INFO_ID_LIST_MAX_SIZE) {
		px_info_list->uc_len_id = HAL_FW_INFO_ID_LIST_MAX_SIZE;
	}

	memcpy(px_info_list->c_data_id, FWVS_VERSION, px_info_list->uc_len_id);
}

/**
 * \brief Reset internal PLC Modem.
 *
 */
void hal_reset_plc_modem(void)
{
	uint32_t ul_delay = 0x00FFFFFF;

#if SAM4CP
	/* Reset on ARST of modem PLC */
	ioport_set_pin_level(PPLC_ARST_GPIO, PPLC_ARST_ACTIVE_LEVEL);
	/* Clear ARST of modem PLC */
	ioport_set_pin_level(PPLC_ARST_GPIO, PPLC_ARST_INACTIVE_LEVEL);
#elif SAM4C || SAM4CM
	;
#else
	/* Reset on ARST of modem PLC */
	gpio_set_pin_low(PPLC_ARST_GPIO);
	/* Clear ARST of modem PLC */
	gpio_set_pin_high(PPLC_ARST_GPIO);
#endif

	/* Wait to initialize system */
	while (ul_delay) {
		ul_delay--;
	}
}

/**
 * \brief Manufacturing Test Procedure function signalling
 *
 * \note if MAC configuration is not correct the system always enters in this
 * mode. Customer should implement the final functionality depending on its
 * needs.
 */
/* Manufacturing Test Procedure status indication */
/* static uint8_t uc_mtp_enable = 0; */
/* static uint8_t ul_time_swap = 100; */
void hal_mtp_signalling(void)
{
	/* defined by user as the following example */
	/* if(!ul_time_swap--){ */
	/* if(uc_mtp_enable){ */
	/* uc_mtp_enable = 0; */
	/* }else{ */
	/* uc_mtp_enable = 1; */
	/* } */
	/* ul_time_swap = 100; */
	/* } */

	/* if(uc_mtp_enable){ */
	/* LED_Off(LED0); */
	/* LED_On(LED1); */
	/* }else{ */
	/* LED_On(LED0); */
	/* LED_Off(LED1); */
	/* } */
}

/**
 * \brief Read MAC configuration from user signature
 *
 * \param pv_dst       Pointer to buffer to store information
 * \param us_size      Number of bytes to read
 *
 */
void hal_read_mac_data_cfg(void *pv_dst, uint16_t us_size)
{
	uint32_t ul_user_sign_buf[HAL_USER_SIGNATURE_SIZE];
	uint8_t *puc_mac_config;

	Disable_global_interrupt();

	/* Read user signature */
	flash_read_user_signature((void *)ul_user_sign_buf,
			HAL_USER_SIGNATURE_SIZE);

	/* provide mac address */
	puc_mac_config = (uint8_t *)ul_user_sign_buf +
			HAL_MACCFG_OFFSET_USER_SIGN;
	memcpy((uint8_t *)pv_dst, puc_mac_config, us_size);

	Enable_global_interrupt();
}

/**
 * \brief Write MAC configuration to user signature
 *
 * \param pv_src       Pointer to buffer to read MAC data
 * \param us_size      Number of bytes to write
 *
 * \return 1 if there is no error, otherwise returns 0.
 */
uint8_t hal_write_mac_data_cfg(void *pv_src, uint16_t us_size)
{
	uint32_t ul_user_sign_buf[HAL_USER_SIGNATURE_SIZE];
	uint8_t *puc_mac_config;
	uint16_t us_write_end_address;

	/* The user signature should be no longer than 512 bytes */
	us_write_end_address = us_size + (uint8_t)HAL_MACCFG_OFFSET_USER_SIGN;
	if (us_write_end_address > HAL_FLASH_PAGE_SIZE) {
		return 0;
	}

	Disable_global_interrupt();

	/* Read user signature */
	flash_read_user_signature((void *)ul_user_sign_buf,
			HAL_USER_SIGNATURE_SIZE);

	/* update mac address */
	puc_mac_config = (uint8_t *)ul_user_sign_buf +
			HAL_MACCFG_OFFSET_USER_SIGN;
	memcpy(puc_mac_config, (uint8_t *)pv_src, us_size);

	/* erase user signature */
	flash_erase_user_signature();

	/* write user signature */
	flash_write_user_signature((void *)ul_user_sign_buf,
			HAL_USER_SIGNATURE_SIZE);

	Enable_global_interrupt();

	return 1;
}

/**
 * \brief Read BOOT configuration from user signature
 *
 * \param pv_dst       Pointer to buffer to store information
 * \param us_size      Number of bytes to read
 *
 */
void hal_read_boot_cfg(void *pv_dst, uint16_t us_size)
{
	uint8_t uc_user_sign_buf[HAL_FLASH_PAGE_SIZE];
	uint8_t *puc_boot_config;

	Disable_global_interrupt();

	/* Read user signature */
	flash_read_user_signature((void *)uc_user_sign_buf,
			HAL_FLASH_PAGE_SIZE / sizeof(uint32_t));

	/* provide boot config */
	puc_boot_config = uc_user_sign_buf + HAL_BOOT_STATUS_OFFSET_USER_SIGN;
	memcpy((uint8_t *)pv_dst, puc_boot_config, us_size);

	Enable_global_interrupt();
}

/**
 * \brief Write BOOT configuration to user signature
 *
 * \param pv_src       Pointer to buffer to read MAC data
 * \param us_size      Number of bytes to write
 *
 * \return 1 if there is no error, otherwise returns 0.
 */
uint8_t hal_write_boot_cfg(void *pv_src, uint16_t us_size)
{
	uint8_t uc_user_sign_buf[HAL_FLASH_PAGE_SIZE];
	uint8_t *puc_boot_config;
	uint16_t us_write_end_address;

	/* The user signature should be no longer than 512 bytes */
	us_write_end_address = us_size + (uint8_t)HAL_BOOT_STATUS_OFFSET_USER_SIGN;
	if (us_write_end_address > HAL_FLASH_PAGE_SIZE) {
		return 0;
	}

	Disable_global_interrupt();

	/* Read user signature */
	flash_read_user_signature((void *)uc_user_sign_buf,
			HAL_FLASH_PAGE_SIZE / sizeof(uint32_t));

	/* update mac address */
	puc_boot_config = uc_user_sign_buf + HAL_BOOT_STATUS_OFFSET_USER_SIGN;
	memcpy(puc_boot_config, (uint8_t *)pv_src, us_size);

	/* erase user signature */
	flash_erase_user_signature();

	/* write user signature */
	flash_write_user_signature((void *)uc_user_sign_buf,
			HAL_FLASH_PAGE_SIZE / sizeof(uint32_t));

	Enable_global_interrupt();

	return 1;
}

/**
 * \brief Read FU configuration from GPBR peripheral
 *
 * \param pv_dst      Pointer to buffer from read information
 * \param us_size     Number of bytes to read
 *
 */
void hal_read_fu_data_cfg(void *pv_dst, uint16_t us_size)
{
	uint32_t ul_buf_value[4];
	uint32_t *pul_dst;

	pul_dst = (uint32_t *)ul_buf_value;
	*pul_dst++ = gpbr_read(GPBR0);
	*pul_dst++ = gpbr_read(GPBR1);
	*pul_dst++ = gpbr_read(GPBR2);
	*pul_dst = gpbr_read(GPBR3);
	memcpy(pv_dst, (uint8_t *)ul_buf_value, us_size);
}

/**
 * \brief Write FU configuration to GPBR peripheral
 *
 * \param pv_src      Pointer to information to save
 * \param us_size     Number of bytes to write
 *
 * \return 1 if there is no error, otherwise returns 0.
 */
uint8_t hal_write_fu_data_cfg(void *pv_src, uint16_t us_size)
{
	uint32_t ul_buf_value[4];
	uint32_t *pul_dst;

	memcpy((uint8_t *)ul_buf_value, pv_src, us_size);

	pul_dst = (uint32_t *)ul_buf_value;
	gpbr_write(GPBR0, *pul_dst++);
	gpbr_write(GPBR1, *pul_dst++);
	gpbr_write(GPBR2, *pul_dst++);
	gpbr_write(GPBR3, *pul_dst);

	return 1;
}

/**
 * \brief Read PHY configuration from user signature
 *
 * \param pv_dst       Pointer to buffer for information
 * \param us_size      Number of bytes to get
 *
 */
void hal_read_phy_data_cfg(void *pv_dst, uint16_t us_size)
{
	uint8_t uc_user_sign_buf[HAL_FLASH_PAGE_SIZE];
	uint8_t *puc_phy_config;

	Disable_global_interrupt();

	/* Read user signature */
	flash_read_user_signature((void *)uc_user_sign_buf,
			HAL_FLASH_PAGE_SIZE / sizeof(uint32_t));

	/* provide mac address */
	puc_phy_config = uc_user_sign_buf + HAL_PHYCFG_OFFSET_USER_SIGN;
	memcpy((uint8_t *)pv_dst, puc_phy_config, us_size);

	Enable_global_interrupt();
}

/**
 * \brief Write PHY configuration to user signature
 *
 * \param pv_src      Pointer to information to save
 * \param us_size     Number of bytes to write
 *
 * \return 1 if there is no error, otherwise returns 0.
 */
uint8_t hal_write_phy_data_cfg(void *pv_src, uint16_t us_size)
{
	uint8_t uc_user_sign_buf[HAL_FLASH_PAGE_SIZE];
	uint8_t *puc_phy_config;
	uint16_t us_write_end_address;

	/* The user signature should be no longer than 512 bytes */
	us_write_end_address = us_size + (uint8_t)HAL_PHYCFG_OFFSET_USER_SIGN;
	if (us_write_end_address > HAL_FLASH_PAGE_SIZE) {
		return 0;
	}

	Disable_global_interrupt();

	/* Read user signature */
	flash_read_user_signature((void *)uc_user_sign_buf,
			HAL_FLASH_PAGE_SIZE / sizeof(uint32_t));

	/* update phy parameters */
	puc_phy_config = uc_user_sign_buf + HAL_PHYCFG_OFFSET_USER_SIGN;
	memcpy(puc_phy_config, (uint8_t *)pv_src, us_size);

	/* erase user signature */
	flash_erase_user_signature();

	/* write user signature */
	flash_write_user_signature((void *)uc_user_sign_buf,
			HAL_FLASH_PAGE_SIZE / sizeof(uint32_t));

	Enable_global_interrupt();

	return 1;
}

/**
 * \brief Set addresses for program startup. Reboot using specific bootloader.
 *
 */
void hal_swap_startup_address(void)
{
#ifdef PRIME_SERVICE_NODE
	uint8_t uc_cmd;

	Disable_global_interrupt();

	hal_read_boot_cfg((void *)&uc_cmd, sizeof(uc_cmd));
	uc_cmd |= HAL_BOOT_CMD_SWAP;
	hal_write_boot_cfg((void *)&uc_cmd, sizeof(uc_cmd));

	Enable_global_interrupt();
#endif
}

/**
 * \brief Get address of the last program startup
 * Only for Service Node.
 *
 * \param pul_start_page     Pointer to get the start page address
 */
void hal_get_startup_address(uint32_t *pul_start_page)
{
	*pul_start_page = HAL_ADDR_START_SERVICE;
}

/**
 * \brief Get alternative address of the last program startup.
 * Only for Service Node.
 *
 * \param pul_start_page     Pointer to get the start page address
 */
void hal_get_optional_startup_address(uint32_t *pul_start_page)
{
#ifdef PRIME_BASE
	*pul_start_page = ul_fw_mem_address;
#else
	uint8_t uc_boot_status;

	/* Read the Boot status */
	hal_read_boot_cfg((void *)&uc_boot_status, sizeof(uc_boot_status));

	if (boot_is_fw_v1_in_use(uc_boot_status)) {
		*pul_start_page = HAL_BOOT_FW2;
	} else {
		*pul_start_page = HAL_BOOT_FW1;
	}
#endif
}

/**
 * \brief Set addresses for firmware image.
 *
 * \param ul_page_addr      New start address value
 */
void hal_set_fw_page_address(uint32_t ul_page_addr)
{
	ul_fw_mem_address = ul_page_addr;
}

/**
 * \brief Get start address for firmware image
 * Only for Service Node.
 *
 * \return Start address value
 */
uint32_t hal_get_fw_page_address(void)
{
	return ul_fw_mem_address;
}

/**
 * \brief Get firmware version and copy to structure
 *
 * \return px_sw_version   Pointer to the version information
 */
void hal_get_fw_version(hal_sw_version_info *px_sw_version)
{
	memcpy(px_sw_version, &x_sw_version, sizeof(x_sw_version));
}

/**
 * \brief Read configuration from memory
 * \param ul_addr    Image address to read
 * \param puc_buf    Pointer to buffer for information
 * \param us_size    Number of bytes to get
 */
void hal_read_fw_data(uint32_t ul_addr, uint8_t *puc_buf, uint16_t us_size)
{
	uint32_t ul_read_address;

	ul_read_address = ul_fw_mem_address + ul_addr;
	if (us_size) {
		memcpy(puc_buf, (uint8_t *)ul_read_address, us_size);
	}
}

/**
 * \brief Write configuration to memory
 * \param ul_addr		Image address to write
 * \param puc_buf		Ptr to information to save
 * \param us_size		Number of bytes to put
 *
 * \return 1 if there is no error, otherwise returns 0.
 */
uint8_t hal_write_fw_data(uint32_t ul_addr, uint8_t *puc_buf, uint16_t us_size)
{
	uint8_t uc_res = 0;
	uint32_t ul_rc;
	uint32_t ul_write_address;

	ul_write_address = ul_fw_mem_address + ul_addr;
	if (us_size) {
		Disable_global_interrupt();
		ul_rc = flash_write(ul_write_address, puc_buf, us_size, 0);
		Enable_global_interrupt();
		if (ul_rc == FLASH_RC_OK) {
			uc_res = 1;
		} else {
			uc_res = 0;
		}
	}

	return uc_res;
}

/**
 * \brief Get maximum firmware image us_size able to be stored
 *
 * \return maximum image us_size
 */
uint32_t hal_get_max_fw_size(void)
{
	return HAL_FU_MAXIMUM_FIRMW_SIZE;
}

/**
 * \brief Get firmware image information
 *
 * \param puc_buf    Pointer to store the image information
 *
 */
void hal_get_fu_info_list(uint8_t *puc_buf)
{
	memcpy(puc_buf, x_fw_info_list,
			sizeof(x_fw_info_list_t) * HAL_FW_INFO_NUMBER_ID);
}

/**
 * \brief Set firmware image information
 *
 * \param puc_buf    Pointer to read the image information
 *
 */
void hal_set_fu_info_list(uint8_t *puc_buf)
{
	memcpy(x_fw_info_list, puc_buf,
			sizeof(x_fw_info_list_t) * HAL_FW_INFO_NUMBER_ID);
}

/**
 * \brief Initalize hardware abstraction layer interface
 *
 */
void hal_init(void)
{
	/* reset hardware MODEM */
	hal_reset_plc_modem();

	/* Initialize flash: 6 wait states for flash writing. */
	flash_init(FLASH_ACCESS_MODE_128, CHIP_FLASH_WRITE_WAIT_STATE);

	/* configure version */
	x_sw_version.us_vendor_id = PRIME_PIB_VENDOR;
	x_sw_version.us_product_id = PRIME_PIB_MODEL;
	x_sw_version.uc_version_len = PRIME_PIB_VERSION_LEN;
	memcpy(x_sw_version.c_fw_version, FWVS_PIB_VERSION,
			x_sw_version.uc_version_len);

#ifdef PRIME_BASE
	/* init Flash pointer */
	ul_fw_mem_address = (uint32_t)HAL_BOOT_FW2;
#endif

	_init_fu_info_list();
}

/**
 * \brief Configure hardware interface to write MAC if it is needed
 *
 */
typedef struct {
	uint16_t ul_cfg_key;
	uint8_t uc_mac[6];
} x_mac_cfg_t;

void hal_start(void)
{
	x_mac_cfg_t x_mac;

	hal_read_mac_data_cfg(&x_mac, sizeof(x_mac));

	if (x_mac.ul_cfg_key != 0xAA55) {
		x_mac.ul_cfg_key = 0xAA55;
		x_mac.uc_mac[0] = 0xFC;
		x_mac.uc_mac[1] = 0xC2;
		x_mac.uc_mac[2] = 0x3D;
		x_mac.uc_mac[3] = 0x01;
		x_mac.uc_mac[4] = 0x8A;
#ifdef PRIME_BASE
		x_mac.uc_mac[5] = 0x70;
#else
		x_mac.uc_mac[5] = 0x7E;
#endif
		hal_write_mac_data_cfg(&x_mac, sizeof(x_mac));
	}

	hal_configure_bootloader_watchdog_mode();
}

/**
 * \brief Configure watchdog mode during bootloader firmware upgrade
 *
 */
void hal_configure_bootloader_watchdog_mode(void)
{
	uint8_t uc_user_sign_buf[HAL_FLASH_PAGE_SIZE];
	uint8_t puc_wd_mode_config;

	Disable_global_interrupt();

	/* Read user signature */
	flash_read_user_signature((void *)uc_user_sign_buf,
			HAL_FLASH_PAGE_SIZE / sizeof(uint32_t));

	/* read wd_mode bootloader */
	puc_wd_mode_config = uc_user_sign_buf[BOOT_WD_MODE_OFFSET_USER_SIGN];

	/* check if wd_mode have to be reconfigured */
	if (puc_wd_mode_config != HAL_BOOTLOADER_WD_MODE) {
		uc_user_sign_buf[BOOT_WD_MODE_OFFSET_USER_SIGN] = HAL_BOOTLOADER_WD_MODE;
		uc_user_sign_buf[BOOT_WD_MODE_OFFSET_USER_SIGN + 1] = PIO_WD_IDX;
		uc_user_sign_buf[BOOT_WD_MODE_OFFSET_USER_SIGN + 2] = PIO_WD_ID;
		uc_user_sign_buf[BOOT_WD_MODE_OFFSET_USER_SIGN + 3] = PIO_WD_PIN;
		uc_user_sign_buf[BOOT_WD_MODE_OFFSET_USER_SIGN + 4] = (PIO_WD >> 24) & (0xFF);
		uc_user_sign_buf[BOOT_WD_MODE_OFFSET_USER_SIGN + 5] = (PIO_WD >> 16) & (0xFF);
		uc_user_sign_buf[BOOT_WD_MODE_OFFSET_USER_SIGN + 6] = (PIO_WD >> 8) & (0xFF);
		uc_user_sign_buf[BOOT_WD_MODE_OFFSET_USER_SIGN + 7] = (PIO_WD) & (0xFF);
		/* erase user signature */
		flash_erase_user_signature();
		/* write user signature */
		flash_write_user_signature((void *)uc_user_sign_buf,
				HAL_FLASH_PAGE_SIZE / sizeof(uint32_t));
	}

	Enable_global_interrupt();
}

/**
 * \brief Restart program
 *
 */
void hal_restart_system(uint8_t uc_err_type)
{
	UNUSED(uc_err_type);
	NVIC_SystemReset();
}

/**
 * \brief Initialize the memory service and unlock every used pages in FU
 * process
 *
 * \return 1 if there is no error, otherwise returns 0.
 */
uint8_t hal_unlock_mem(void)
{
	uint32_t ul_next_sector;
	uint32_t *pul_sector_fw;
	uint32_t *pul_sector_end;
	uint8_t i;
#ifndef PRIME_BASE
	uint8_t uc_boot_status;
	/*  uint32_t ul_fw_flash_mem_status; */
#endif

#ifdef PRIME_BASE
	ul_next_sector = ul_fw_mem_address;
#else
	/* Read the Boot status */
	hal_read_boot_cfg((void *)&uc_boot_status, sizeof(uc_boot_status));
	if (boot_is_fw_v1_in_use(uc_boot_status)) {
		ul_next_sector = HAL_BOOT_FW2;
	} else {
		ul_next_sector = HAL_BOOT_FW1;
	}
#endif

	pul_sector_fw = (uint32_t *)ul_next_sector;
	pul_sector_end = (uint32_t *)(ul_next_sector + HAL_FU_MAXIMUM_FIRMW_SIZE);

	/* Unlock and erase used sectors */
	for (i = 1; i < HAL_FU_MAXIMUM_FIRMW_SECTORS; i++) {
		Disable_global_interrupt();
		flash_unlock(ul_next_sector, ul_next_sector + 0x10000 - 1, 0, 0);
		flash_erase_sector(ul_next_sector);
		Enable_global_interrupt();

		if (pul_sector_fw > pul_sector_end) {
			break;
		}

		ul_next_sector += 0x10000; /* sectors of 64Kb */
		pul_sector_fw = (uint32_t *)ul_next_sector;
	}
	return 1;
}

/**
 * \brief Lock every used pages in FU process
 *
 * \return 1 if there is no error, otherwise returns 0.
 */
uint8_t hal_lock_mem(void)
{
	return 1;
}

/**
 * \brief Function that updates the bootloader in flash
 *
 * \return 1 if OK, 0 if NOK.
 */
uint8_t hal_update_bootloader(void)
{
	uint32_t ul_new_boot_addr;
	uint8_t uc_boot_status;
	uint8_t uc_copy_result;

	Disable_global_interrupt();

	hal_read_boot_cfg((void *)&uc_boot_status, sizeof(uc_boot_status));

	if (boot_is_fw_v1_in_use(uc_boot_status)) {
		ul_new_boot_addr = BOOT_FLASH_FIRMWARE_V2_START_ADDRESS;
	} else {
		ul_new_boot_addr = BOOT_FLASH_FIRMWARE_V1_START_ADDRESS;
	}

	uc_copy_result = hal_copy_bootloader(ul_new_boot_addr, BOOT_START_ADDRESS);

	Enable_global_interrupt();

	return(uc_copy_result);
}

/**
 * \brief This function copies a new version of the bootloader into flash
 *
 * \param  addr_new_bootloader  new boot loader version address
 *         addr_old_bootloader  boot loader address destination
 *
 * \return 1   OK
 * \return 0  NOK
 */
uint8_t hal_copy_bootloader(uint32_t addr_new_bootloader,
		uint32_t addr_old_bootloader)
{
	uint8_t i = 0;
	uint8_t ul_result;
	uint32_t ul_page_offset = 0;
	uint8_t uc_page[BOOT_FLASH_PAGE_SIZE];

	/* Temporal buffer to store the flash pages content */
	hal_erase_Bootloader(addr_old_bootloader);

	for (i = 0; i < (BOOT_FIRMWARE_MAX_SIZE / BOOT_FLASH_PAGE_SIZE); i++) {
		ul_page_offset = i * BOOT_FLASH_PAGE_SIZE;
		memcpy(uc_page, (uint8_t *)(addr_new_bootloader + ul_page_offset),
				BOOT_FLASH_PAGE_SIZE);
		ul_result = flash_write(addr_old_bootloader + ul_page_offset,
				uc_page, BOOT_FLASH_PAGE_SIZE, 0);
	}

	return ul_result;
}

/**
 * \brief This function erases the bootloader flash region
 *
 * \param  bootloader_addr  pointer to the bootloader region start address
 *
 * \return 1   OK
 * \return 0  NOK
 */
uint8_t hal_erase_Bootloader(uint32_t bootloader_addr)
{
	uint8_t i;
	uint32_t *pul_flash;
	uint8_t ul_result;

	for (i = 0; i < (BOOT_FIRMWARE_MAX_SIZE / 0x1000); i++) {
		wdt_restart(WDT);
		pul_flash = (uint32_t *)(bootloader_addr + i * 0X1000);
		ul_result = flash_erase_page((uint32_t)pul_flash, IFLASH_ERASE_PAGES_8);
		if (ul_result != FLASH_RC_OK) {
			return 0;
		}
	}

	return 1;
}

/* @} */

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/* @endcond */
