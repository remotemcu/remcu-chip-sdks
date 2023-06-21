/**
 *
 * \file
 *
 * \brief This module contains WILC bus wrapper APIs implementation.
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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
 
#include "linux_wlan_sdio.h"

#include "bsp/include/nm_bsp.h"
#include "common/include/nm_common.h"
#include "bus_wrapper/include/nm_bus_wrapper.h"
#include "linux_wlan_spi.h"
#include "NMI_WFI_NetDevice.h"
extern linux_wlan_t* g_linux_wlan;


//struct spi_device* nmc_spidev;

/*
*	@fn		nm_bus_init
*	@brief	Initialize the bus wrapper
*	@return	M2M_SUCCESS in case of success and M2M_ERR_BUS_FAIL in case of failure
*	@author	M.S.M
*	@date	28 oct 2013
*	@version	1.0
*/
sint8 nm_bus_init(void *pvInitValue)
{
	sint8 result = M2M_SUCCESS;
#ifdef CONF_WIFI_USE_SPI
	linux_spi_init(nmc_spi_dev);
	g_linux_wlan->nmc_spidev = nmc_spi_dev;
#elif defined CONF_WIFI_USE_SDIO
	linux_sdio_init(NULL);
#endif
	return result;
}

/*
*	@fn		nm_bus_ioctl
*	@brief	send/receive from the bus
*	@param[IN]	u8Cmd
*					IOCTL command for the operation
*	@param[IN]	pvParameter
*					Arbitrary parameter depenging on IOCTL
*	@return	M2M_SUCCESS in case of success and M2M_ERR_BUS_FAIL in case of failure
*	@author	M.S.M
*	@date	28 oct 2013
*	@note	For SPI only, it's important to be able to send/receive at the same time
*	@version	1.0
*/
sint8 nm_bus_ioctl(uint8 u8Cmd, void* pvParameter)
{
	sint8 s8Ret = 0;
	switch(u8Cmd)
	{

#ifdef CONF_WIFI_USE_SPI
		case NM_BUS_IOCTL_RW: 
		{
			tstrNmSpiRw *pstrParam = (tstrNmSpiRw *)pvParameter;
			s8Ret = linux_spi_write_read(pstrParam->pu8InBuf, pstrParam->pu8OutBuf, pstrParam->u16Sz);
		}
		break;
#elif defined CONF_WIFI_USE_SDIO
		case NM_BUS_IOCTL_CMD_52: 
		{
			tstrNmSdioCmd52* pstrParam = (tstrNmSdioCmd52 *)pvParameter;
			s8Ret = linux_sdio_cmd52(pstrParam);
		}
		break;
		case NM_BUS_IOCTL_CMD_53: 
		{
			tstrNmSdioCmd53* pstrParam = (tstrNmSdioCmd53 *)pvParameter;
			s8Ret = linux_sdio_cmd53(pstrParam);
		}
		break;
#endif
		default:
			s8Ret = -1;
			M2M_ERR("invalide ioclt cmd\n");
			break;
	}

	return s8Ret;
}

/*
*	@fn		nm_bus_deinit
*	@brief	De-initialize the bus wrapper
*	@author	M.S.M
*	@date	28 oct 2013
*	@version	1.0
*/
sint8 nm_bus_deinit(void)
{
#ifdef CONF_WIFI_USE_SPI
	linux_spi_deinit(NULL);
#elif defined CONF_WIFI_USE_SDIO
	linux_sdio_deinit(NULL);
#endif
	return 0;
}

/*
*	@fn			nm_bus_reinit
*	@brief		re-initialize the bus wrapper
*	@param [in]	void *config
*					re-init configuration data
*	@return		M2M_SUCCESS in case of success and M2M_ERR_BUS_FAIL in case of failure
*	@author		Dina El Sissy
*	@date		19 Sept 2012
*	@version	1.0
*/
sint8 nm_bus_reinit(void* config)
{
	return M2M_SUCCESS;
}

