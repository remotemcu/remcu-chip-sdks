/**
 * \file
 *
 * \brief LIN service for SAM.
 *
 * This file contains basic functions for the SAM USART, with support for all
 * modes, settings and clock speeds.
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

#include <stdio.h>
#include <string.h>
#include "compiler.h"
#include "pdc.h"
#include "usart.h"
#include "lin.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \defgroup sam_service_network_lin_group Local Interconnect Network (LIN)
 *
 * See \ref sam_lin_quickstart
 *
 * Service driver for the LIN. This driver provides access to the LIN service
 * features of the usart controller.
 *
 * @{
 */

/** Enhanced checksum used in the LIN 2.x */
#define USART_LIN_ENHANCED_CHECKSUM    0

/** Classic checksum used in the LIN 1.x */
#define USART_LIN_CLASSIC_CHECKSUM    1

/** The response data length is defined by the field DLC of DLM */
#define USART_LIN_DLM_DLC    0

/** The response data length is defined by the bits 5 and 6 of the identifier */
#define USART_LIN_DLM_IDCHR    1

/** The frame identifier used to carry diagnostic data */
#define USART_LIN_DIAGNOSTIC_FRAME_ID    60

/** LIN error offset */
#define USART_LIN_ERROR_OFFSET    25

/* Array of structure of type:'st_lin_message' */
st_lin_message lin_descript_list_node[LIN_NODE_NUM][NUMBER_OF_LIN_FRAMES_NODE];

/* Error counter */
uint16_t lin_error_number_node[LIN_NODE_NUM] = {0};

/* Last error[node_num][n]: lin_handle | status - lenght = 4 */
uint16_t lin_last_errors_node[LIN_NODE_NUM][LIN_LAST_ERR_LENGHT];

/* Tx Buffer message */
uint8_t lin_tx_buffer_node[LIN_NODE_NUM][LIN_BUFF_SIZE];

/* Rx Buffer message */
uint8_t lin_rx_buffer_node[LIN_NODE_NUM][LIN_BUFF_SIZE];

/**  Instance of the USART IP used */
Usart *usart_lin_node[LIN_NODE_NUM];

/** PDC data packet. */
pdc_packet_t g_st_packet[LIN_NODE_NUM];

/** Pointer to PDC register base. */
Pdc *g_p_pdc[LIN_NODE_NUM];

/**
 * \brief  This function commands the sending of a LIN header and response,
 * MASTER task only.
 *
 * \param uc_node Node Value.
 * \param uc_handle  Handle on the descriptor list.
 * \param uc_len     Message length corresponding to the message pointed by the
 * handle in the descriptor list.
 *
 * \return Status PASS / FAIL.
 *
 */
static uint8_t lin_tx_header_and_response(uint8_t uc_node, uint8_t uc_handle,
		uint8_t uc_len)
{
	/* Copy the data contained in the descriptor list into the tx buffer */
	memcpy(&lin_tx_buffer_node[uc_node][1],
			lin_descript_list_node[uc_node][uc_handle].uc_pt_data,
			uc_len);

	/* Set the ID First */
	lin_tx_buffer_node[uc_node][0]
		= lin_descript_list_node[uc_node][uc_handle].uc_id;

	g_st_packet[uc_node].ul_addr = (uint32_t)lin_tx_buffer_node[uc_node];
	g_st_packet[uc_node].ul_size = (uc_len + 1);
	pdc_tx_init(g_p_pdc[uc_node], &g_st_packet[uc_node], NULL);
	usart_enable_interrupt(USART0, US_IER_LINSNRE);
	pdc_enable_transfer(g_p_pdc[uc_node], PERIPH_PTCR_TXTEN);

	return PASS;
}

/**
 * \brief  This function commands the sending of a LIN response, SLAVE task of
 * MASTER or SLAVE node.
 *
 * \param uc_node Node Value.
 * \param p_data    Pointer on the data corresponding to the message pointed by
 * the handle in the descriptor list.
 * \param uc_len     Message length corresponding to the message pointed by the
 * handle in the descriptor list.
 *
 * \return Status PASS / FAIL.
 *
 */
static uint8_t lin_tx_response(uint8_t uc_node, uint8_t *p_data, uint8_t uc_len)
{
	/* Copy the data contained in the descriptor list into the tx buffer */
	memcpy(&lin_tx_buffer_node[uc_node][0], p_data, uc_len + 1);

	g_st_packet[uc_node].ul_addr = (uint32_t)lin_tx_buffer_node[uc_node];
	g_st_packet[uc_node].ul_size = uc_len;
	pdc_tx_init(g_p_pdc[uc_node], &g_st_packet[uc_node], NULL);
	pdc_enable_transfer(g_p_pdc[uc_node], PERIPH_PTCR_TXTEN);

	return PASS;
}

/**
 * \brief  This function commands the reception of a LIN response, SLAVE task
 * of MASTER or SLAVE node.
 *
 * \param uc_node Node Value.
 * \param uc_handle  Handle on the descriptor list.
 * \param uc_len     Message length corresponding to the message pointed by the
 * handle in the descriptor list.
 *
 * \return Status PASS / FAIL.
 *
 */
static uint8_t lin_rx_response(uint8_t uc_node, uint8_t uc_len)
{
	g_st_packet[uc_node].ul_addr = (uint32_t)&lin_rx_buffer_node;
	g_st_packet[uc_node].ul_size = uc_len;
	pdc_rx_init(g_p_pdc[uc_node], &g_st_packet[uc_node], NULL);

	usart_enable_interrupt(USART0, US_IER_ENDRX);

	return PASS;
}

/**
 * \brief  This function reads (empties) the reception data buffer when a LIN
 * response had been received. This function is additional of the
 * lin_rx_response()
 * function.
 *
 * \param uc_node Node Value.
 * \param p_data    Pointer on the data corresponding to the message pointed by
 * the handle in the descriptor list.
 *
 * \return Status PASS / FAIL.
 *
 */
static void lin_get_response(uint8_t uc_node, uint8_t *p_data)
{
	uint8_t i, uc_len;

	uc_len = usart_lin_get_data_length(usart_lin_node[uc_node]);
	for (i = 0; i < uc_len; i++) {
		(*p_data++) = lin_rx_buffer_node[uc_node][i];
	}
}

/**
 * \brief USART LIN interrupt handler: manage ID reception.
 *
 * \param uc_node Node Value.
 *
 */
void usart_lin_handler(uint8_t uc_node)
{
	uint8_t uc_handle = 0xFF;
	uint8_t i;
	uint32_t ul_status;

	ul_status = usart_get_status(usart_lin_node[uc_node]);

	/* Check ID Value for the current message */
	for (i = 0; i < NUMBER_OF_LIN_FRAMES_NODE; i++) {
		if (lin_descript_list_node[uc_node][i].uc_id ==
				usart_lin_read_identifier(usart_lin_node[uc_node])) {
			uc_handle = i;
			break;
		}
	}

	/* Check if the ID received is registered into the lin description list */
	if (uc_handle != 0xFF) {
		if (ul_status & US_CSR_ENDRX) {
			pdc_disable_transfer(g_p_pdc[uc_node],PERIPH_PTCR_RXTEN);

			lin_get_response(0,
					lin_descript_list_node[uc_node][uc_handle].uc_pt_data);
			/* Start of the associated task */

			if (lin_descript_list_node[uc_node][uc_handle].pt_function != NULL) {
				lin_descript_list_node[uc_node][uc_handle].pt_function(
						lin_descript_list_node[uc_node][uc_handle].uc_pt_data);
			}
		}

		/* Check Error Status */
		usart_reset_status(usart_lin_node[uc_node]);
		if (ul_status & US_CSR_LIN_ERROR) {
			lin_descript_list_node[uc_node][uc_handle].uc_status = 
				(ul_status & US_CSR_LIN_ERROR) >> USART_LIN_ERROR_OFFSET;

			lin_last_errors_node[uc_node][(((uint8_t)
			lin_error_number_node[uc_node]) &(LIN_LAST_ERR_LENGHT - 1))] \
				= ((((uint16_t)uc_handle) <<8) | \
					(ul_status & US_CSR_LIN_ERROR) >> USART_LIN_ERROR_OFFSET);
			lin_error_number_node[uc_node]++;
		}
		/* Here the communication go on only in case no error is detected!!! */
		else {
			usart_lin_set_node_action(usart_lin_node[uc_node],
					lin_descript_list_node[uc_node][uc_handle].lin_cmd);

#if (USART_LIN_VERSION == LIN_2x)
			/* Configure Parity */
			usart_lin_enable_parity(usart_lin_node[uc_node]);
			/* Configure Checksum */
			usart_lin_enable_checksum(usart_lin_node[uc_node]);
			/* Configure Checksum Type */
			usart_lin_set_checksum_type(usart_lin_node[uc_node],
					USART_LIN_ENHANCED_CHECKSUM);
			/* Configure Frameslot */
			usart_lin_enable_frame_slot(usart_lin_node[uc_node]);
			/* Configure Frame Length */

			usart_lin_set_data_len_mode(usart_lin_node[uc_node],
					USART_LIN_DLM_IDCHR);
			usart_lin_set_response_data_len(usart_lin_node[uc_node],
					lin_descript_list_node[uc_node][uc_handle].uc_dlc);
#elif (USART_LIN_VERSION == LIN_1x)
			/* Configure Parity */
			usart_lin_enable_parity(usart_lin_node[uc_node]);
			/* Configure Checksum */
			usart_lin_enable_checksum(usart_lin_node[uc_node]);
			/* Configure Checksum Type */
			usart_lin_set_checksum_type(usart_lin_node[uc_node],
					USART_LIN_CLASSIC_CHECKSUM);
			/* Configure Frameslot */
			usart_lin_enable_frame_slot(usart_lin_node[uc_node]);
			/* Configure Frame Length */
			usart_lin_set_data_len_mode(usart_lin_node[uc_node],
					USART_LIN_DLM_DLC);
#endif

			/* Diagnostic frames in LIN 2.0/2.1 */
			if ((usart_lin_read_identifier(usart_lin_node[uc_node]) >=
					USART_LIN_DIAGNOSTIC_FRAME_ID)) {
				usart_lin_set_checksum_type(
						usart_lin_node[uc_node],
						USART_LIN_CLASSIC_CHECKSUM);
				/* Configure Frame Length */
				usart_lin_set_data_len_mode(
						usart_lin_node[uc_node],
						USART_LIN_DLM_DLC);
			}

			switch (lin_descript_list_node[uc_node][uc_handle].lin_cmd) {
			case PUBLISH:
				lin_tx_response(uc_node,
						lin_descript_list_node[uc_node][uc_handle].uc_pt_data,
						lin_descript_list_node[uc_node][uc_handle].uc_dlc);
				break;

			case SUBSCRIBE:
				lin_rx_response(uc_node,
						lin_descript_list_node[uc_node][uc_handle].uc_dlc);
				break;

			case IGNORE:
			default:
				break;
			}
		}
	}
}

/**
 * \brief  This function initializes the LIN controller.
 *
 * \param usart_node Pointer to the usart instance.
 * \param b_master \c true for master, \c false for slave.
 * \param uc_node Node Value.
 * \param us_rate Baudrate Value.
 * \param ul_mck Board MCK.
 *
 * \return Status PASS / FAIL.
 */
uint8_t lin_init(Usart *usart_node, bool b_master, uint8_t uc_node,
		uint16_t us_rate, uint32_t ul_mck)
{
	/* USART options. */
	if (b_master) {
		usart_init_lin_master(usart_node, us_rate, ul_mck);
	} else {
		usart_init_lin_slave(usart_node, us_rate, ul_mck);
	}

	usart_lin_node[uc_node] = usart_node;

	/* Get board USART PDC base address and enable receiver and transmitter.*/
	g_p_pdc[uc_node] = usart_get_pdc_base(usart_lin_node[uc_node]);
	pdc_enable_transfer(g_p_pdc[uc_node],
			PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);

	return PASS;
}

/**
 * \brief  This function initializes the LIN message descriptor.
 *
 * \param uc_node LIN node id.
 * \param uc_frame_id Frame node id.
 * \param lin_desc Specific LIN descriptor.
 *
 * \return Status PASS / FAIL.
 *
 */
uint8_t lin_register_descriptor(uint8_t uc_node, uint8_t uc_frame_id,
		st_lin_message *lin_desc)
{
	lin_descript_list_node[uc_node][uc_frame_id].uc_id = lin_desc->uc_id;
	lin_descript_list_node[uc_node][uc_frame_id].uc_dlc = lin_desc->uc_dlc;
	lin_descript_list_node[uc_node][uc_frame_id].lin_cmd = lin_desc->lin_cmd;
	lin_descript_list_node[uc_node][uc_frame_id].uc_status
		= lin_desc->uc_status;
	lin_descript_list_node[uc_node][uc_frame_id].uc_pt_data
		= lin_desc->uc_pt_data;
	lin_descript_list_node[uc_node][uc_frame_id].pt_function
		= lin_desc->pt_function;

	return PASS;
}

/**
 * \brief  This function commands the sending of the LIN header, MASTER task of
 * MASTER node.
 *
 * \param uc_node Node Value.
 * \param uc_id  LIN identifier value. In case of `LIN_1X', the coded length is
 * transported into the LIN identifier.
 * \param uc_len True length (not coded), number of data bytes transported in
 * the response. This information is not used in `LIN_1X' because it is coded
 * in `uc_id'.
 *
 * \return Status PASS / FAIL.
 *
 */
uint8_t lin_send_cmd(uint8_t uc_node,uint8_t uc_id,uint8_t uc_len)
{
	uint8_t i = 0;
	uint8_t uc_handle = 0;

	/* Clear error in case of previous communication */
	usart_reset_status(usart_lin_node[uc_node]);

	for (i = 0; i < NUMBER_OF_LIN_FRAMES_NODE; i++) {
		if (lin_descript_list_node[uc_node][i].uc_id == uc_id) {
			uc_handle = i;
			break;
		}
	}

	if (uc_handle != 0xFF) {
#if USART_LIN_VERSION == LIN_2x
		usart_lin_set_node_action(usart_lin_node[uc_node],
				lin_descript_list_node[uc_node][uc_handle].lin_cmd);
		/* Configure Parity */
		usart_lin_enable_parity(usart_lin_node[uc_node]);
		/* Configure Checksum */
		usart_lin_enable_checksum(usart_lin_node[uc_node]);
		/* Configure Checksum Type */
		usart_lin_set_checksum_type(usart_lin_node[uc_node],
				USART_LIN_ENHANCED_CHECKSUM);
		/* Configure Frameslot */
		usart_lin_enable_frame_slot(usart_lin_node[uc_node]);
		/* Configure Frame Length */
		usart_lin_set_data_len_mode(usart_lin_node[uc_node],
				USART_LIN_DLM_DLC);
		usart_lin_set_response_data_len(usart_lin_node[uc_node],
				uc_len);

#elif USART_LIN_VERSION == LIN_1x
		usart_lin_set_node_action(usart_lin_node[uc_node],
				lin_descript_list_node[uc_node][uc_handle].lin_cmd);
		/* Configure Parity */
		usart_lin_enable_parity(usart_lin_node[uc_node]);
		/* Configure Checksum */
		usart_lin_enable_checksum(usart_lin_node[uc_node]);
		/* Configure Checksum Type */
		usart_lin_set_checksum_type(usart_lin_node[uc_node],
				USART_LIN_CLASSIC_CHECKSUM);
		/* Configure Frameslot */
		usart_lin_enable_frame_slot(usart_lin_node[uc_node]);
		/* Configure Frame Length */
		usart_lin_set_data_len_mode(usart_lin_node[uc_node],
				USART_LIN_DLM_IDCHR);
#endif

		/* Switch to Classic Checksum if diagnostic ID request */
		if (lin_descript_list_node[uc_node][uc_handle].uc_id >=
				USART_LIN_DIAGNOSTIC_FRAME_ID) {
			usart_lin_set_checksum_type(usart_lin_node[uc_node],
					USART_LIN_CLASSIC_CHECKSUM);
			/* Configure Frame Length */
			usart_lin_set_data_len_mode(usart_lin_node[uc_node],
					USART_LIN_DLM_IDCHR);
		}

		switch (lin_descript_list_node[uc_node][uc_handle].lin_cmd) {
		/* In Publish, the USART Send the Header and the response */
		case PUBLISH:
			lin_tx_header_and_response(uc_node, uc_handle, uc_len);
			break;

		/* In Subscribe, the USART Receive the response */
		case SUBSCRIBE:
			usart_lin_set_tx_identifier(usart_lin_node[uc_node], uc_id);
			lin_rx_response(uc_node, uc_len);
			break;

		default:
			break;
		}
		return PASS;
	} else {
		return FAIL;
	}
}

/* @} */

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

