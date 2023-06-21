/**
 * \file
 *
 * \brief QT60168 configuration file.
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

#ifndef _CONF_QT60168_H_
#define _CONF_QT60168_H_

#include "qt60168.h"

#ifdef __cplusplus
extern "C" {
#endif

/** First chip select used by QT60168 components on the SPI module instance. */

#define QT60168_SPI_FIRST_NPCS      QT60168_SPI_NCPS

/** SPI master speed in Hz. */
#define QT60168_SPI_MASTER_SPEED    1000000

/** Number of bits in each SPI transfer. */
#define QT60168_SPI_BITS            8

#define QT60168_NTHR        0x0F
#define QT60168_NDRIFT      0x0F
#define QT60168_NDIL        0x02
#define QT60168_FDIL        0x04
#define QT60168_NRD         0x14
#define QT60168_BL          0x02
#define QT60168_AKS         0x00
#define QT60168_SSYNC       0x00
#define QT60168_MSYNC       0x00
#define QT60168_BS          0x01
#define QT60168_LSL         0x0064
#define QT60168_EEPROM_CRC  0x0A

/** if define, DRDY is not checked, a delay function to wait chip to be ready */
/* #define QT60168_DISABLE_DRDY */

#if (!defined _QT60168_C_)
extern
#endif
const qt60168_setups_block_t qt60168_setups_block
#if (defined _QT60168_C_)
	= {
#define QT60168_KEY_CONFIG(KEY_NUMBER, FIRST_KEY) \
	.key_cfg[FIRST_KEY + KEY_NUMBER].ndrift_nthr \
		= QT60168_NTHR + (QT60168_NDRIFT << 4),	\
	.key_cfg[FIRST_KEY + KEY_NUMBER].fdil_ndil \
		= QT60168_NDIL + (QT60168_FDIL << 4), \
	.key_cfg[FIRST_KEY + KEY_NUMBER].nrd \
		= QT60168_NRD, \
	.key_cfg[FIRST_KEY + KEY_NUMBER].ssync_aks_bl \
		= (QT60168_BL << 4) + (QT60168_AKS << 6) + \
			(QT60168_SSYNC << 7),

#define QT60168_KEY_NOT_ACTIVATED(KEY_NUMBER, FIRST_KEY) \
	.key_cfg[FIRST_KEY + KEY_NUMBER].ndrift_nthr   = 0, \
	.key_cfg[FIRST_KEY + KEY_NUMBER].fdil_ndil     = 0, \
	.key_cfg[FIRST_KEY + KEY_NUMBER].nrd           = 0, \
	.key_cfg[FIRST_KEY + KEY_NUMBER].ssync_aks_bl  = 0,

	MREPEAT(16, QT60168_KEY_CONFIG, 0)
	MREPEAT( 8, QT60168_KEY_NOT_ACTIVATED, 16)

#undef QT60168_KEY_CONFIG
#undef QT60168_KEY_NOT_ACTIVATED

	.msync = QT60168_MSYNC << 6,
	.bs   = QT60168_BS,
	.lsl  = QT60168_LSL,
	.crc  = QT60168_EEPROM_CRC
	}

#endif
;

#ifdef __cplusplus
}
#endif

#endif  /* _CONF_QT60168_H_ */
