/**
 *
 * \file
 *
 * \brief HTTP File Downloader Example Implementation.
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
#include <errno.h>
#include "asf.h"
#include "httpdownloader.h"
#include "FreeRTOS.h"
#include "iot/http/http_client.h"
#include "osprintf.h"
#include "lwip/ip.h"
#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/sockets.h"
#include "os/include/net_init.h"
#include "os/include/m2m_wifi_ex.h"
#include "tinyservices.h"
#include "conf_wilc.h"
#include "ota_fw_update/ota_fw_update.h"
#include <string.h>
#include <stdio.h>

/** File download processing state. */
static download_state down_state = NOT_READY;
/** Http content length. */
static uint32_t http_file_size = 0;
/** Receiving content length. */
static uint32_t received_file_size = 0;
/** File name to download. */
//static char save_file_name[MAIN_MAX_FILE_NAME_LENGTH + 1] = "0:";

static int is_firmware = 0;
/** Instance of Timer module. */
struct sw_timer_module swt_module_inst;

/** Instance of HTTP client module. */
struct http_client_module http_client_module_inst;

char * gfileURL;

static int dismantle_http_client(void);
/**
 * \brief Initialize download state to not ready.
 */
static void init_state(void)
{
	down_state = NOT_READY;
}


/**
 * \brief Clear state parameter at download processing state.
 * \param[in] mask Check download_state.
 */
static void clear_state(download_state mask)
{
	down_state &= ~mask;
}

/**
 * \brief Add state parameter at download processing state.
 * \param[in] mask Check download_state.
 */
static void add_state(download_state mask)
{
	down_state |= mask;
}

/**
 * \brief File download processing state check.
 * \param[in] mask Check download_state.
 * \return true if this state is set, false otherwise.
 */

static inline bool is_state_set(download_state mask)
{
	return ((down_state & mask) != 0);
}

void setFirmwareDownload(int val)
{
	is_firmware = val;
}

/**
 * \brief Start file download via HTTP connection.
 */
static void start_download(char * fileURL)
{
	if (is_state_set(GET_REQUESTED)) {
		osprintf("start_download: request is sent already.\r\n");
		return;
	}

	if (is_state_set(DOWNLOADING)) {
		osprintf("start_download: running download already.\r\n");
		return;
	}
	int ret;
	/* Send the HTTP request. */
	osprintf("Sending HTTP request...\r\n");
	ret = http_client_send_request(&http_client_module_inst, fileURL, HTTP_METHOD_GET, NULL, NULL);
	if(ret != 0){
		osprintf("HTTP request send failed err %d\r\n",ret);
		return;
	}
	
	/* Receive the response*/
	osprintf("Receiving response...\r\n");
	while(!(is_state_set(COMPLETED) || is_state_set(CANCELED))){
		http_client_recv_response(&http_client_module_inst);
	
	}	
}

/**
 * \brief Ignore data, but calculate the total received size TODO: Store received packet to file
 * \param[in] data Packet data.
 * \param[in] length Packet data length.
 */
static void store_file_packet(char *data, uint32_t length)
{
	if ((data == NULL) || (length < 1)) {
		return;
	}

	if (!is_state_set(DOWNLOADING)) {
		received_file_size = 0;
		add_state(DOWNLOADING);
	}

	if (data != NULL) {
		received_file_size += length;
		osprintf("Received %lu\r",received_file_size);
		if (received_file_size >= http_file_size) {
			osprintf("Received %lu File size %lu\r\n",received_file_size,http_file_size);
			osprintf("store_file_packet: file downloaded successfully.\r\n");
#if SAM4SD32
			if(is_firmware == 1){
				if(write_to_flash(data, length,1) != SUCCESS){
					printf("Failed to write to flash!\r\n");
					//lock_all_sectors();
					add_state(CANCELED);
					return;
				}
				printf("Flash write done\r\n");
			}else{
				/*TODO : store in a memory*/
			}
#endif			
			add_state(COMPLETED);
			return;
		}
#if SAM4SD32
		if(is_firmware == 1){
			if(write_to_flash(data, length,0) != SUCCESS){
				printf("Failed to write to flash!!\r\n");
				//lock_all_sectors();
				add_state(CANCELED);
				return;
			}
		}else{
			/*TODO : store in a memory*/
		}
#endif
	}
}


/**
 * \brief Callback of the HTTP client.
 *
 * \param[in]  module_inst     Module instance of HTTP client module.
 * \param[in]  type            Type of event.
 * \param[in]  data            Data structure of the event. \refer http_client_data
 */
static void http_client_callback(struct http_client_module *module_inst, int type, union http_client_data *data)
{
	switch (type) {
	case HTTP_CLIENT_CALLBACK_SOCK_CONNECTED:
		osprintf("http_client_callback: HTTP client socket connected.\r\n");
		break;

	case HTTP_CLIENT_CALLBACK_REQUESTED:
		osprintf("http_client_callback: request completed.\r\n");
		add_state(GET_REQUESTED);
		break;

	case HTTP_CLIENT_CALLBACK_RECV_RESPONSE:
		osprintf("http_client_callback: received HTTP response %u data size %u\r\n",
				(unsigned int)data->recv_response.response_code,
				(unsigned int)data->recv_response.content_length);
		if ((unsigned int)data->recv_response.response_code == 200) {
			http_file_size = data->recv_response.content_length;
			received_file_size = 0;
		} 
		else {
			add_state(CANCELED);
			return;
		}
		if (data->recv_response.content_length <= MAIN_BUFFER_MAX_SIZE) {
			store_file_packet(data->recv_response.content, data->recv_response.content_length);
			//add_state(COMPLETED);  //Ambrose
		}
		break;

	case HTTP_CLIENT_CALLBACK_RECV_CHUNKED_DATA:
		store_file_packet(data->recv_chunked_data.data, data->recv_chunked_data.length);
		if (data->recv_chunked_data.is_complete) {
			add_state(COMPLETED);
		}

		break;

	case HTTP_CLIENT_CALLBACK_DISCONNECTED:
		osprintf("http_client_callback: disconnection reason:%d\r\n", data->disconnected.reason);

		/* If disconnect reason is equal to -ECONNRESET(-104),
		 * It means the server has closed the connection (timeout).
		 * This is normal operation.
		 */
		if (data->disconnected.reason == -EAGAIN) {
			/* Server has not responded. Retry immediately. */
			if (is_state_set(DOWNLOADING)) {
				clear_state(DOWNLOADING);
			}

			if (is_state_set(GET_REQUESTED)) {
				clear_state(GET_REQUESTED);
			}

			start_download(gfileURL);
			break;
		}
		if(data->disconnected.reason != 0) // Some error occurred, set canceled state
			add_state(CANCELED);
		break;
	}
}


/**
 * \brief Configure Timer module.
 */
static void configure_timer(void)
{
	struct sw_timer_config swt_conf;
	sw_timer_get_config_defaults(&swt_conf);

	sw_timer_init(&swt_module_inst, &swt_conf);
	sw_timer_enable(&swt_module_inst);
}

/**
 * \brief Configure HTTP client module.
 */
static int configure_http_client(void)
{
	struct http_client_config httpc_conf;
	int ret;

	http_client_get_config_defaults(&httpc_conf);

	httpc_conf.recv_buffer_size = MAIN_BUFFER_MAX_SIZE;
	httpc_conf.timer_inst = &swt_module_inst;

	ret = http_client_init(&http_client_module_inst, &httpc_conf);
	if (ret < 0) {
		osprintf("configure_http_client: HTTP client initialization failed! (res %d)\r\n", ret);
		return FAILURE;
	}

	ret = http_client_register_callback(&http_client_module_inst, http_client_callback);
	if (ret < 0) {
		osprintf("configure_http_client: register callback failed! (res %d)\r\n", ret);
		return FAILURE;
	}
	return SUCCESS;
}

/**
 * \brief close HTTP client module.
 */
static int dismantle_http_client(void)
{
	int ret;
	ret = http_client_close(&http_client_module_inst);
	if (ret < 0) {
		osprintf("HTTP client close failed! (res %d)\r\n", ret);
		return FAILURE;
	}
	ret = http_client_deinit(&http_client_module_inst);
	if (ret < 0) {
		osprintf("HTTP client close failed! (res %d)\r\n", ret);
		return FAILURE;
	}

	return SUCCESS;
}

/**
 * \brief http downloader function.
 */
int http_downloader(char * fileURL)
{
	int ret;
	int url_length = strlen(fileURL);
	gfileURL = pvPortMalloc(url_length+1);
	strcpy(gfileURL, fileURL);
	/*initialize state as NOT_READY*/
	init_state();
	
	/* Initialize the Timer. */
	configure_timer(); /* Note: the RTT timer is not used effectively in this example, as connection timeout is achieved through(dependency on) socket timeout. 
						Because call to API recv is blocking call, setting socket timeout is necessary to come out of the API. 
						after the recv API, sw_timer_task just check for the request timeout(time taken to receive response).
						Please set socket timeout to match with request timeout(RTT sw_timer timeout)*/
	/* Initialize the HTTP client service. */
	ret = configure_http_client();
	if( ret != SUCCESS)	{
		printf("configure_http_client failed\r\n");
		return FAILURE;
	}
	/*start downloading*/
	start_download(gfileURL);
	/*Downloading process completed, close the http client*/
	dismantle_http_client();
	vPortFree(gfileURL);
	if(is_state_set(COMPLETED)){
		return SUCCESS;
	}
	return FAILURE;
}