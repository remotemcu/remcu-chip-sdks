/*
 * \file
 *
 * \brief WINC1500 Exosite Example.
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
#ifndef ATMEL_EXOSITE_H_INCLUDE
#define ATMEL_EXOSITE_H_INCLUDE

#include <compiler.h>
#include "iot/http/http_client.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*exosite_http_cb)(struct http_client_module *module_inst, int type, union http_client_data *data);

/*
*	\brief Initialize exosite-demo.
*/
bool	exosite_example_init(exosite_http_cb cb);

/*
*	\brief Send message to exosite server for activiate.
*
*	\param activate_data	device information data. Data format is "vendor=xxx&model=xxx&sn=xxx"
*
*	\return	true send message to server successfully.
*/
bool	exosite_example_activiate(char * activate_data);

/*
*	\brief Send message to exosite server for Io1 sensor information and request led state value.
*
*
*	\return	true send message to server. ex> temperature, light voltage. 
*/
bool	exosite_example_read_and_write(char * write_data, char * cik);

#ifdef __cplusplus
}
#endif

#endif /* ATMEL_EXOSITE_H_ */