/**
 * \file
 *
 * \brief HTTP base entity.
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

/**
 * \addtogroup sam0_httpc_group
 * @{
 */

#ifndef HTTP_ENTITY_H_INCLUDED
#define HTTP_ENTITY_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief A structure that the implementation of HTTP entity.
 */
struct http_entity {
	/** A flag for the using the chunked encoding transfer or not. */
	uint8_t is_chunked;
	/**
	 * \brief Get content mime type.
	 *
	 * \param[in]  priv_data       Private data of this entity.
	 *
	 * \return     Content type of entity.
	 */
	const char* (*get_contents_type)(void *priv_data);
	/**
	 * \brief Get content length.
	 * If using the chunked encoding, This function does not needed.
	 *
	 * \param[in]  priv_data       Private data of this entity.
	 *
	 * \return     Content length of entity.
	 */
	int (*get_contents_length)(void *priv_data);
	/**
	 * \brief Read the content.
	 *
	 * \param[in]  priv_data       Private data of this entity.
	 * \param[in]  buffer          A buffer that stored read data.
	 * \param[in]  size            Maximum size of the buffer.
	 * \param[in]  written         total size of ever read.
	 *
	 * \return     Read size.
	 */
	int (*read)(void *priv_data, char *buffer, uint32_t size, uint32_t written);
	/**
	 * \brief Close the entity.
	 * Completed to send request. So release the resource.
	 *
	 * \param[in]  priv_data       Private data of this entity.
	 */
	void (*close)(void *priv_data);
	/** Private data of this entity. Stored various data necessary for the operation of the entity. */
	void *priv_data;

};

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* HTTP_ENTITY_H_INCLUDED */
