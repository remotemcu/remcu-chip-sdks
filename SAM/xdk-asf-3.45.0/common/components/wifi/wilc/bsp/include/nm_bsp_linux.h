/**
 *
 * \file
 *
 * \brief This module contains SAM4S WILC BSP APIs declarations.
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

#ifndef _NM_BSP_SAM4S_H_
#define _NM_BSP_SAM4S_H_

#include "linux/kernel.h"
#define NM_LEVEL_INTERRUPT		(1)
#ifdef NMI_SDIO
#define CONF_WIFI_USE_SDIO
#ifdef NMI_SDIO_IRQ_GPIO
#define CONF_WIFI_USE_SDIO_EXT_IRQ
#endif
#else
#define CONF_WIFI_USE_SPI
#endif

#define CONF_WIFI_M2M_DEBUG					(1)
#define CONF_WIFI_M2M_PRINTF				printk



#define NM_DEBUG		CONF_WIFI_M2M_DEBUG
#define NM_BSP_PRINTF	CONF_WIFI_M2M_PRINTF

#endif /* _NM_BSP_SAM4S_H_ */
