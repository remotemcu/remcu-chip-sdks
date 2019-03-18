/**
 *
 * \file
 *
 * \brief This module contains WILC M2M driver APIs implementation.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "driver/source/nmbus.h"
#include "bsp/include/nm_bsp.h"
#include "driver/source/nmdrv.h"
#include "driver/source/nmasic.h"

#ifdef CONF_WILC_USE_SPI
#include "driver/source/nmspi.h"
#elif defined CONF_WILC_USE_SDIO
#include "driver/source/nmsdio.h"
#endif

#define rNMI_GP_REG_1          (0x14a0)

#define rHAVE_SDIO_IRQ_GPIO_BIT     (NBIT0)
#define rHAVE_SLEEP_CLK_SRC_RTC_BIT (NBIT2)
#define rHAVE_SLEEP_CLK_SRC_XO_BIT  (NBIT3)
#define rHAVE_LEGACY_RF_SETTINGS    (NBIT5)


static sint8 nm_get_firmware_info(tstrM2mRev* M2mRev);




static void chip_apply_conf(void)
{
	sint8 ret = M2M_SUCCESS;
	
	uint32 val32;
	val32 = 0;

#ifdef __ENABLE_SLEEP_CLK_SRC_RTC__
	val32 |= rHAVE_SLEEP_CLK_SRC_RTC;
#elif defined __ENABLE_SLEEP_CLK_SRC_XO__
	val32 |= rHAVE_SLEEP_CLK_SRC_XO;
#endif
#ifdef __ENABLE_LEGACY_RF_SETTINGS__
	val32 |= rHAVE_LEGACY_RF_SETTINGS;
#endif
#ifdef CONF_WILC_USE_SDIO_EXT_IRQ
	val32 |= rHAVE_SDIO_IRQ_GPIO_BIT;
#endif
	do  {
		nm_write_reg(rNMI_GP_REG_1, val32);
		if(val32 != 0) {		
			uint32 reg = 0;
			ret = nm_read_reg_with_ret(rNMI_GP_REG_1, &reg);
			if(ret == M2M_SUCCESS) {
				if(reg == val32)
					break;
			}
		} else {
			break;
		}
	} while(1);
}

/*
*	@fn		nm_drv_init
*	@brief	Initialize NMC1000 driver
*	@return	M2M_SUCCESS in case of success and Negative error code in case of failure
*   @param [in]	arg
*				Generic argument
*	@author	M. Abdelmawla
*	@date	15 July 2012
*	@version	1.0
*/
sint8 nm_drv_init(void * arg)
{
	tstrM2mRev strtmp;
	sint8 ret = M2M_SUCCESS;
	
	ret = nm_bus_iface_init(NULL);
	if (M2M_SUCCESS != ret) {
		M2M_ERR("[nmi start]: fail init bus\n");
		goto ERR1;
	}

#ifdef BUS_ONLY
	return;
#endif

#ifdef CONF_WILC_USE_SPI
	nm_spi_init();
#elif defined CONF_WILC_USE_SDIO
	nm_sdio_init();
#endif

#ifdef WILC_SERIAL_BRIDGE_INTERFACE
	return M2M_SUCCESS;
#endif
	M2M_INFO("Chip ID %lx\n", nmi_get_chipid());
#ifndef CONF_WILC_FW_IN_FLASH
	ret = firmware_download();
	if (M2M_SUCCESS != ret) {
		goto ERR2;
	}
#endif /* CONF_WILC_FW_IN_FLASH */
	chip_apply_conf();

	ret = cpu_start();
	if (M2M_SUCCESS != ret) {
		goto ERR2;
	}

#ifdef CONF_WILC_FW_IN_FLASH
	ret = wait_for_bootrom();
	if (M2M_SUCCESS != ret) {
		goto ERR2;
	}
#endif /*CONF_WILC_FW_IN_FLASH */
	ret = wait_for_firmware_start();
	if (M2M_SUCCESS != ret) {
		goto ERR2;
	}

#if (defined CONF_WILC_USE_3000_REV_A && !defined WILC_SERIAL_BRIDGE_INTERFACE)
#ifndef CONF_WILC_FW_IN_FLASH
	ret = firmware_download_bt();
	if (M2M_SUCCESS != ret) {
		goto ERR2;
	}
#endif /* CONF_WILC_FW_IN_FLASH */
	ret = cpu_start_bt();
	if (M2M_SUCCESS != ret) {
		goto ERR2;
	}
#endif /* (defined CONF_WILC_USE_3000_REV_A && !defined WILC_SERIAL_BRIDGE_INTERFACE) */
	ret = enable_interrupts();
	if (M2M_SUCCESS != ret) {
		M2M_ERR("failed to enable interrupts..\n");
		goto ERR2;
	}
		
	if(M2M_ERR_FW_VER_MISMATCH == nm_get_firmware_info(&strtmp))
	{
		ret = M2M_ERR_FW_VER_MISMATCH;
		M2M_ERR("Mismatch Firmawre Version\n");
		M2M_INFO("Firmware ver   : %u.%u.%u\n", strtmp.u8FirmwareMajor, strtmp.u8FirmwareMinor, strtmp.u8DriverPatch);
		M2M_INFO("Min driver ver : %u.%u.%u\n", strtmp.u8DriverMajor, strtmp.u8DriverMinor, strtmp.u8DriverPatch);
		M2M_INFO("Curr driver ver: %u.%u.%u\n", M2M_DRIVER_VERSION_MAJOR_NO, M2M_DRIVER_VERSION_MINOR_NO, M2M_DRIVER_VERSION_PATCH_NO);
	}

	return ret;
ERR2:
#ifdef CONF_WILC_USE_SDIO
	nm_sdio_deinit();
#endif
	nm_bus_iface_deinit();
ERR1:	
	return ret;
}

/*
*	@fn		nm_drv_deinit
*	@brief	Deinitialize NMC1000 driver
*	@author	M. Abdelmawla
*	@date	17 July 2012
*	@version	1.0
*/
sint8 nm_drv_deinit(void * arg) 
{
	sint8 ret;
	
	ret = chip_deinit();
	if (M2M_SUCCESS != ret) {
		M2M_ERR("[nmi stop]: chip_deinit fail\n");
		goto ERR1;
	}

#ifdef CONF_WILC_USE_SDIO
	nm_sdio_init();
#endif

	ret = nm_bus_iface_deinit();
	if (M2M_SUCCESS != ret) {
		M2M_ERR("[nmi stop]: fail init bus\n");
		goto ERR1;
	}

ERR1:
	return ret;
}

/**
*	@fn		nm_get_firmware_info(tstrM2mRev* M2mRev)
*	@brief	Get Firmware version info
*	@param [out]	M2mRev
*			    pointer holds address of structure "tstrM2mRev" that contains the firmware version parameters
*   @author		Ahmad.Mohammad.Yahya
*   @date		27 MARCH 2013
*	@version	1.0
*/
static sint8 nm_get_firmware_info(tstrM2mRev* M2mRev)
{
	uint16  curr_drv_ver, min_req_drv_ver;
	uint32	reg = 0;
	sint8	ret = M2M_SUCCESS;

	ret = nm_read_reg_with_ret(NMI_REV_REG, &reg);

	M2mRev->u8DriverMajor	= (uint8)(reg >> 24)&0xff;
	M2mRev->u8DriverMinor   = (uint8)(reg >> 20)&0x0f;
	M2mRev->u8DriverPatch	= (uint8)(reg >> 16)&0x0f;
	M2mRev->u8FirmwareMajor	= (uint8)(reg >> 8)&0xff;
	M2mRev->u8FirmwareMinor = (uint8)(reg >> 4)&0x0f;	
	M2mRev->u8FirmwarePatch = (uint8)(reg)&0x0f;	
	M2mRev->u32Chipid	= nmi_get_chipid();
	
	curr_drv_ver    = MAKE_VERSION(M2M_DRIVER_VERSION_MAJOR_NO, M2M_DRIVER_VERSION_MINOR_NO, M2M_DRIVER_VERSION_PATCH_NO);
	min_req_drv_ver = MAKE_VERSION(M2mRev->u8DriverMajor, M2mRev->u8DriverMinor,M2mRev->u8DriverPatch);
	if((curr_drv_ver <  min_req_drv_ver) || M2mRev->u8DriverMajor == 18 ) {
		ret = M2M_ERR_FW_VER_MISMATCH;
	}
	return ret;
}
