/**
 * \file
 *
 * \brief Custom Serial Chat Service Declarations
 *
 * Copyright (c) 2017-2018 Microchip Technology Inc. and its subsidiaries.
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
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Atmel
 *Support</a>
 */

// <<< Use Configuration Wizard in Context Menu >>>
// <h> Custom Serial Chat Service Configuration
// =======================
#ifndef __CSCS_H__
#define __CSCS_H__

/****************************************************************************************
*							        Macros	                                     		*
****************************************************************************************/
/** @brief Custom serial chat UUID length */
#define CSC_UUID_128_LEN				(16)

/****************************************************************************************
*							        Structures                                     		*
****************************************************************************************/
/** @brief Custom serial chat service info */
typedef struct csc_serv
{
	at_ble_uuid_t	serv_uuid; 
	at_ble_handle_t	serv_handle; 
	at_ble_characteristic_t	endpoint_chars;  
}csc_serv_t;

/****************************************************************************************
*                                       Functions                                       *
****************************************************************************************/
/** @brief Initialize the csc service initialization function
  * 
  * @param[in] buf		Buffer pointer for data to be send
  * @param[in] len      size of buffer		
  */
at_ble_status_t csc_serv_init(uint8_t *buf, uint16_t len);

/** @brief Function used for sending data to remote device
  * 
 * @param[in] buf		Buffer pointer for data to be send
 * @param[in] len       size of buffer
  */
at_ble_status_t csc_serv_send_data(uint16_t connhandle, uint8_t *databuf, uint16_t datalen);


#endif /*__CSCS_H__*/
// </h>

// <<< end of configuration section >>>
