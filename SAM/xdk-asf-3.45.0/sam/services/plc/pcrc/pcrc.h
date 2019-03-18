/**
 * \file
 *
 * \brief PLC PRIME CRC calculation service
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

#ifndef PCRC_H_INCLUDED
#define PCRC_H_INCLUDED

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/* @endcond */

/**
 * \ingroup plc_group
 * \defgroup pcrc_plc_group PLC PRIME CRC Calculation
 *
 * This module provides configuration and utils to calculate the CRC
 * for PRIME messages in a PLC network.
 *
 * @{
 */

/* \name CRC types */

/*** WARNING: duplicated definitions ***
 *   Keep numerically consistent with those in atpl230.h
 */
enum PCRC_CRC_types {
	PCRC_CRC_TYPE_8 = 0,
	PCRC_CRC_TYPE_16 = 1,
	PCRC_CRC_TYPE_24 = 2,
	PCRC_CRC_TYPE_32 = 3,
};

/* \name Header type */

/*** WARNING: duplicated definitions ***
 *   Keep numerically consistent with those in atpl230.h
 */
/* @{ */
/* Header type: GENERIC PACKET */
#define PCRC_HT_GENERIC               0
/* Header type: PROMOTION PACKET */
#define PCRC_HT_PROMOTION             1
/* Header type: BEACON PACKET */
#define PCRC_HT_BEACON                2
/* Header type: USI message */
#define PCRC_HT_USI                   3
/* @} */

/* Invalid CRC */
#define PCRC_CRC_INVALID 0xFFFFFFFF

/* CRC length for the promotion needed PDUs */
#define PCRC_PROMOTION_CRC_LENGTH 13

/* \name PLC PRIME CRC Calculation interface */
/* @{ */
uint32_t pcrc_calculate_prime_crc(uint8_t *puc_buf, uint32_t ul_len,
		uint8_t uc_header_type, uint8_t uc_crc_type);
void pcrc_configure_sna(uint8_t *sna);

/* @} */

/* @} */

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/* @endcond */

#endif /* PCRC_H_INCLUDED */
