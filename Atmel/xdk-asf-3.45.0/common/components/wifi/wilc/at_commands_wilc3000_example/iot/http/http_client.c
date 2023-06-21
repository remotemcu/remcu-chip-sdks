/**
 * \file
 *
 * \brief HTTP client service.
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

#include "iot/http/http_client.h"
#include "driver/include/m2m_wifi.h"
#include "iot/stream_writer.h"
#include "lwip/sockets.h"
#include "lwip/api.h"
#include "lwip/netdb.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define DEFAULT_USER_AGENT "atmel/1.0.2"

#define MIN_SEND_BUFFER_SIZE 18 + HTTP_MAX_URI_LENGTH /* DELETE {URI} HTTP/1.1\r\n */

enum http_client_req_state {
	STATE_INIT = 0,
	STATE_TRY_SOCK_CONNECT,
	STATE_SOCK_CONNECTED,
	STATE_REQ_SEND_HEADER,
	STATE_REQ_SEND_ENTITY,
};

enum http_client_resp_state {
	STATE_PARSE_HEADER,
	STATE_PARSE_ENTITY,
};

/**
 * \brief Sending the packet in blocking mode.
 *
 * \param[in]  module          Module instance of HTTP.
 * \param[in]  buffer          Buffer to be sent.
 * \param[in]  buffer_len      Buffer size.
 *
 * \return     0               Function success.
 * \return     otherwise       Function failed.
 */
int _http_client_send_wait(void *module, char *buffer, size_t buffer_len);

int _http_client_read_wait(void *module, char *buffer, size_t buffer_len);

/**
 * \brief Clear the HTTP instance.
 *
 * \param[in]  module          Module instance of HTTP.
 */
void _http_client_clear_conn(struct http_client_module *const module, int reason);
/**
 * \brief Send HTTP request packet.
 *
 * \param[in]  module          Module instance of HTTP.
 */
void _http_client_request(struct http_client_module *const module);

/**
 * \brief Start receiving HTTP packet.
 *
 * \param[in]  module          Module instance of HTTP.
 */
int32_t _http_client_recv_packet(struct http_client_module *const module);

/**
 * \brief Perform the post processing of the received packet.
 *
 * \param[in]  module          Module instance of MQTT.
 * \param[in]  read_len        Read size from the recv function.
 */
void _http_client_recved_packet(struct http_client_module *const module, int read_len);
/**
 * \brief Parse the input data from the socket.
 *
 * \param[in]  module          Module instance of HTTP.
 */
int _http_client_handle_response(struct http_client_module *const module);
/**
 * \brief Parse the HTTP header part.
 *
 * \param[in]  module          Module instance of HTTP.
 */
int _http_client_handle_header(struct http_client_module *const module);
/**
 * \brief parse the HTTP entity part.
 *
 * \param[in]  module          Module instance of HTTP.
 */
int _http_client_handle_entity(struct http_client_module *const module);
/**
 * \brief Move remain part of the buffer to the start position in the buffer.
 *
 * \param[in]  module          Module instance of HTTP.
 * \param[in]  base            Current position of the buffer pointer.
 */
void _http_client_move_buffer(struct http_client_module *const module, char *base);

/**
 * \brief Timer callback entry of HTTP client.
 *
 * \param[in]  timer_id        ID of timer.
 * \param[in]  context         Private data of timer.
 * \param[in]  context         Period of timer handle.
 */
void http_client_timer_callback(struct sw_timer_module *const module, int timer_id, void *context, int period);

/**
 * \brief Global reference of HTTP client instance.
 * Socket callback interface has not user private data.
 * So it needed reference to HTTP client module instance.
 */
static struct http_client_module *module_ref_inst[TCP_SOCK_MAX] = {NULL,};
	

void http_client_get_config_defaults(struct http_client_config *const config)
{
	config->port = DEFAULT_PORT;
	config->tls = 0;
	config->timeout = 20000;
	config->timer_inst = NULL;
	config->recv_buffer = NULL;
	config->recv_buffer_size = 256;
	config->send_buffer_size = MIN_SEND_BUFFER_SIZE;
	config->user_agent = DEFAULT_USER_AGENT;
}

int http_client_init(struct http_client_module *const module, struct http_client_config *config)
{
	/* Checks the parameters. */
	if (module == NULL || config == NULL) {
		return -EINVAL;
	}

	if (config->recv_buffer_size == 0) {
		return -EINVAL;
	}

	if (config->timer_inst == NULL) {
		return -EINVAL;
	}

	if (config->send_buffer_size < MIN_SEND_BUFFER_SIZE) {
		return -EINVAL;
	}

	memset(module, 0, sizeof(struct http_client_module));
	memcpy(&module->config, config, sizeof(struct http_client_config));

	/* Allocate the buffer in the heap. */
	if (module->config.recv_buffer == NULL) {
		module->config.recv_buffer = (char *)pvPortMalloc(config->recv_buffer_size);
		if (module->config.recv_buffer == NULL) {
			return -ENOMEM;
		}
		module->alloc_buffer = 1;
	}

	if (config->timeout > 0) {
		/* Enable the timer. */
		module->timer_id = sw_timer_register_callback(config->timer_inst, http_client_timer_callback, (void *)module, 0);
		if (module->timer_id < 0) {
			return -ENOSPC;
		}
	}

	module->req.state = STATE_INIT;
	module->resp.state = STATE_PARSE_HEADER;

	return 0;
}

int http_client_deinit(struct http_client_module *const module)
{
	/* Checks the parameters. */
	if (module == NULL) {
		return -EINVAL;
	}
	if (module->timer_id >= 0) {
		sw_timer_unregister_callback(module->config.timer_inst, module->timer_id);
	}

	if (module->alloc_buffer != 0) {
		vPortFree(module->config.recv_buffer);
	}

	if (module->req.ext_header != NULL) {
		vPortFree(module->req.ext_header);
	}

	memset(module, 0, sizeof(struct http_client_module));

	return 0;
}

int http_client_register_callback(struct http_client_module *const module, http_client_callback_t callback)
{
	/* Checks the parameters. */
	if (module == NULL) {
		return -EINVAL;
	}
	module->cb = callback;
	
	return 0;
}

int http_client_unregister_callback(struct http_client_module *const module)
{
	/* Checks the parameters. */
	if (module == NULL) {
		return -EINVAL;
	}

	module->cb = NULL;

	return 0;
}


void http_client_timer_callback(struct sw_timer_module *const module, int timer_id, void *context, int period)
{
	struct http_client_module *module_inst = (struct http_client_module *)context;

	/* Checks invalid arguments. */
	if (module_inst == NULL) {
		return;
	}
	osprintf("Request timeout\r\n");
	_http_client_clear_conn(module_inst, -ETIME);
}

static int _is_ip(const char *host)
{
	uint32_t isv6 = 0;
	uint32_t isv4 = 0;
	char ch;

	while (*host != '\0') {
		ch = *host++;
		if ((ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F') || ch == ':' || ch == '/') {
			if (isv4) {
				return 0;
			}
			isv6 = 1;
		} else if (ch == '.') {
			if (isv6) {
				return 0;
			}
			isv4 = 1;
		} else if ((ch & 0x30) != 0x30) {
			return 0;
		}
	}
	return 1;
}

/*looking for port number preceded by : in host name*/
static int _get_port(const char *host)
{
	int portnumber = -1;
	char * portString = NULL;
	char ch;
	while (*host != '\0') {
		ch = *host++;
		if (ch == ':') {
			if (portString != NULL) {
				/*already found port, not expected again;this may be a IPv6 address*/
				return -1;
			}
			portString =(char *) (host-1);
		} else if ((portString != NULL)) {
			if ((ch & 0x30) != 0x30) {
				/*Expected port number, but found something else*/
				return -1;
			}else if(portnumber == -1){
				portnumber = atoi(portString + 1);
			}
		}
	}
	if(portnumber > 0){
		/*remove port from host name*/
		memset(portString,0,strlen(portString));
	}
			
	return portnumber;
}


int http_client_send_request(struct http_client_module *const module, const char *url,
	enum http_method method, struct http_entity *const entity, const char *ext_header)
{
	struct sockaddr_in addr_in;
	const char *uri = NULL;
	int i = 0, j = 0, reconnect = 0;

	if (module == NULL) {
		return -EINVAL;
	}

	if (module->req.state > STATE_SOCK_CONNECTED) {
		return -EBUSY;
	}

	/* Separate host and uri */
	if (!strncmp(url, "http://", 7)) {
		i = 7;
	} else if (!strncmp(url, "https://", 8)) {
		i = 8;
	}
	reconnect = strncmp(module->host, url + i, strlen(module->host));

	for (; url[i] != '\0' && url[i] != '/'; i++) {
		module->host[j++] = url[i];
	}
	module->host[j] = '\0';
	uri = url + i;

	/* Checks the parameters. */
	if (strlen(module->host) == 0) {
		return -EINVAL;
	}

	if (strlen(uri) >= HTTP_MAX_URI_LENGTH) {
		return -ENAMETOOLONG;
	}

	if (module->req.ext_header != NULL) {
		vPortFree(module->req.ext_header);
	}
	if (ext_header != NULL) {
		module->req.ext_header = strdup(ext_header);
		if (module->req.ext_header == NULL) {
			return -ENOMEM;
		}
	} else {
		module->req.ext_header = NULL;
	}

	module->sending = 0;
	module->recved_size = 0;
	if (uri[0] == '/') {
		strcpy(module->req.uri, uri);
	} else {
		module->req.uri[0] = '/';
		if (uri[0] != 0) {
			strcpy(module->req.uri + 1, uri);
		}
	}

	if (entity != NULL) {
		memcpy(&module->req.entity, entity, sizeof(struct http_entity));
	} else {
		memset(&module->req.entity, 0, sizeof(struct http_entity));
	}

	module->req.method = method;
	
	switch (module->req.state) {
	case STATE_TRY_SOCK_CONNECT:
		if (!reconnect) {
			break; /* Currently try to connect to the same server. */
		}
	case STATE_SOCK_CONNECTED:
		if (!reconnect) {
			module->req.state = STATE_REQ_SEND_HEADER;
			/* Send request immediately. */
			_http_client_request(module);
			break;
		} else {
			/* Request to another peer. Disconnect and try connect again. */
			_http_client_clear_conn(module, 0);
		}
	case STATE_INIT:

		module->sock = socket(AF_INET, SOCK_STREAM, NETCONN_TCP);
		if (module->sock >= 0) {
			int ret = -1;
			module->req.state = STATE_TRY_SOCK_CONNECT;
			module_ref_inst[module->sock] = module;
			int port_number = _get_port(module->host);
			if(port_number != -1){ /*set port number if available or leave with default port*/
				module->config.port = port_number; 
			}
			if (_is_ip(module->host)) {
				addr_in.sin_family = AF_INET;
				addr_in.sin_port = _htons(module->config.port);
				addr_in.sin_addr.s_addr = inet_addr((char *)module->host);
				ret = connect(module->sock, (struct sockaddr *)&addr_in, sizeof(struct sockaddr_in));
				if(ret == 0){
					module->req.state = STATE_SOCK_CONNECTED;
					/* Send event to callback. */
					union http_client_data data;
					data.sock_connected.result = ret;
					if (module->cb != NULL) {
						module->cb(module, HTTP_CLIENT_CALLBACK_SOCK_CONNECTED, &data);
					}
					if (!reconnect) {
						module->req.state = STATE_REQ_SEND_HEADER;
						/* Send request immediately. */
						_http_client_request(module);
						break;
					} else {
						/* Request to another peer. Disconnect and try connect again. */
						_http_client_clear_conn(module, 0);
					}
				}else{
					_http_client_clear_conn(module, ret);
				}
			} else {
				struct hostent* hostent_local = gethostbyname(module->host);
				addr_in.sin_family = AF_INET;
				addr_in.sin_port = _htons(module->config.port);
				addr_in.sin_addr.s_addr = (*((in_addr_t *) *(hostent_local->h_addr_list)));
					//osprintf("module host %s IP address is %d.%d.%d.%d\r\n\r\n", (char *)module->host,
					//(int)IPV4_BYTE(addr_in.sin_addr.s_addr, 0), (int)IPV4_BYTE(addr_in.sin_addr.s_addr, 1),
					//(int)IPV4_BYTE(addr_in.sin_addr.s_addr, 2), (int)IPV4_BYTE(addr_in.sin_addr.s_addr, 3));
				ret = connect(module->sock, (struct sockaddr *)&addr_in, sizeof(struct sockaddr_in));
				if(ret == 0){
					struct timeval tv;
					module->req.state = STATE_SOCK_CONNECTED;
					
					/* Send event to callback. */
					union http_client_data data;
					data.sock_connected.result = ret;
					if (module->cb != NULL) {
						module->cb(module, HTTP_CLIENT_CALLBACK_SOCK_CONNECTED, &data);
					}
					
					/*set socket timeout, to avoid waiting forever in recv*/
					tv.tv_sec = 20;
					tv.tv_usec = 0;
					if(setsockopt(module->sock,SOL_SOCKET,SO_RCVTIMEO,(struct timeval *)&tv,sizeof(tv)) < 0)
						osprintf("set opt timeout failed \r\n");
					
					if (!reconnect) {
						module->req.state = STATE_REQ_SEND_HEADER;
						/* Send request immediately. */
						_http_client_request(module);
						break;
					} else {
						/* Request to another peer. Disconnect and try connect again. */
						_http_client_clear_conn(module, 0);
					}
				}else{
					_http_client_clear_conn(module, ret);
				}
			}
		} else {
			return -ENOSPC;
		}
		break;
	default:
	osprintf("default\r\n");
		/* STATE_TRY_REQ */
		/* STATE_WAIT_RESP */
		/* STATE_RECV_RESP */
		/* Session was busy. Try again later. */
		return -EAGAIN;
	}

	return 0;
}


int http_client_recv_response(struct http_client_module *const module){
	module->req.state = STATE_REQ_SEND_HEADER;
		
	/* Start receive packet. */
	int32_t recived_pkt_size = _http_client_recv_packet(module);
	/* Start post processing. */
	if (recived_pkt_size > 0) 
		_http_client_recved_packet(module, recived_pkt_size);
	
	return recived_pkt_size;
}

int http_client_close(struct http_client_module *const module)
{
	if (module == NULL) {
		return -EINVAL;
	}

	if (module->req.state < STATE_SOCK_CONNECTED) {
		return 0;
	}

	_http_client_clear_conn(module, 0);

	return 0;
}

void _http_client_clear_conn(struct http_client_module *const module, int reason)
{
	union http_client_data data;

	if (module->req.entity.close_entity) {
		module->req.entity.close_entity(module->req.entity.priv_data);
	}

	memset(&module->req.entity, 0, sizeof(struct http_entity));

	if (module->req.state >= STATE_TRY_SOCK_CONNECT) {
		close(module->sock);
	}

	module_ref_inst[module->sock] = NULL;
	memset(&module->req, 0, sizeof(struct http_client_req));
	memset(&module->resp, 0, sizeof(struct http_client_resp));
	module->req.state = STATE_INIT;
	module->resp.state = STATE_PARSE_HEADER;

	module->sending = 0;
	module->permanent = 0;
	data.disconnected.reason = reason;
	if (module->cb) {
		module->cb(module, HTTP_CLIENT_CALLBACK_DISCONNECTED, &data);
	}
}

int _http_client_send_wait(void *_module, char *buffer, size_t buffer_len)
{
	//osprintf("\n%.*s\r\n",buffer_len,buffer);
	int result;
	struct http_client_module *const module = (struct http_client_module *const)_module;
	
	module->sending = 1;

	if ((result = send(module->sock, (void*)buffer, buffer_len, 0)) < 0) {
		module->sending = 0;
		return result;
	}
	
	if (module->config.timeout > 0) {
		sw_timer_enable_callback(module->config.timer_inst, module->timer_id,module->config.timeout);
	}	
	return 0;
}

void _http_client_request(struct http_client_module *const module)
{
	struct stream_writer writer;
	int size;
	int result;
	char length[11];
	char *ptr;
	const char CH_LUT[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	struct http_entity * entity;
	union http_client_data data;
#define HTTP_CHUNKED_MAX_LENGTH 3 /*TCP MTU is 1400(0x578) */

	if (module == NULL) {
		return;
	}

	char buffer[module->config.send_buffer_size];

	if (module->sending != 0) {
		/* Device is busy. */
		return;
	}

	entity = &module->req.entity;

	switch (module->req.state) {
	case STATE_REQ_SEND_HEADER:
		/* Initializing variables. */
		module->req.content_length = 0;
		module->req.sent_length = 0;

		stream_writer_init(&writer, buffer, module->config.send_buffer_size, _http_client_send_wait, (void *)module);
		/* Write Method. */
		if (module->req.method == HTTP_METHOD_GET) {
			stream_writer_send_buffer(&writer, "GET ", 4);
		} else if (module->req.method == HTTP_METHOD_POST) {
			stream_writer_send_buffer(&writer, "POST ", 5);
		} else if (module->req.method == HTTP_METHOD_DELETE) {
			stream_writer_send_buffer(&writer, "DELETE ", 7);
		} else if (module->req.method == HTTP_METHOD_PUT) {
			stream_writer_send_buffer(&writer, "PUT ", 4);
		} else if (module->req.method == HTTP_METHOD_OPTIONS) {
			stream_writer_send_buffer(&writer, "OPTIONS ", 8);
		} else if (module->req.method == HTTP_METHOD_HEAD) {
			stream_writer_send_buffer(&writer, "HEAD ", 5);
		}

		/* Write URI. */
		stream_writer_send_buffer(&writer, module->req.uri, strlen(module->req.uri));

		stream_writer_send_buffer(&writer, " "HTTP_PROTO_NAME"\r\n", strlen(" "HTTP_PROTO_NAME"\r\n"));

		/* Write HTTP headers. */
		/* Default value. */
		stream_writer_send_buffer(&writer, "User-Agent: ", strlen("User-agent: "));
		stream_writer_send_buffer(&writer, (char *)module->config.user_agent, strlen(module->config.user_agent));
		stream_writer_send_buffer(&writer, "\r\n", strlen("\r\n"));
		stream_writer_send_buffer(&writer, "Host: ", strlen("Host: "));
		stream_writer_send_buffer(&writer, module->host, strlen(module->host));
		stream_writer_send_buffer(&writer, "\r\n", strlen("\r\n"));
		/* It supported persistent connection. */
		stream_writer_send_buffer(&writer, "Connection: Keep-Alive\r\n", strlen("Connection: Keep-Alive\r\n"));
		/* Notify supported encoding type and character set. */
		stream_writer_send_buffer(&writer, "Accept-Encoding: \r\n", strlen("Accept-Encoding: \r\n"));
		stream_writer_send_buffer(&writer, "Accept-Charset: utf-8\r\n", strlen("Accept-Charset: utf-8\r\n"));

		if (entity->read_entity != NULL) {
			/* HTTP Entity is exist. */
			if (entity->is_chunked) {
				/* Chunked mode. */
				module->req.content_length = -1;
				stream_writer_send_buffer(&writer, "Transfer-Encoding: chunked\r\n", strlen("Transfer-Encoding: chunked\r\n"));
			} else if(entity->get_contents_length) {
				module->req.content_length = entity->get_contents_length(entity->priv_data);
				if (module->req.content_length < 0) {
					/* Error was occurred. */
					/* Does not send any entity. */
					module->req.content_length = 0;
				} else {
					sprintf(length, "%u", (unsigned int)module->req.content_length);
					stream_writer_send_buffer(&writer, "Content-Length: ", strlen("Content-Length: "));
					stream_writer_send_buffer(&writer, length, strlen(length));
					stream_writer_send_buffer(&writer, "\r\n", strlen("\r\n"));
				}
			}
		}
		if (module->req.ext_header != NULL ) {
			stream_writer_send_buffer(&writer,
				module->req.ext_header,
				strlen(module->req.ext_header));
		}

		//See the module->header
		stream_writer_send_buffer(&writer, "\r\n", strlen("\r\n"));
		stream_writer_send_remain(&writer);

		module->req.state = STATE_REQ_SEND_ENTITY;
		/* Send first part of entity. */
	case STATE_REQ_SEND_ENTITY:
		if (module->req.content_length < 0 && entity->read_entity) {
			/* Send chunked packet. */
			/*  Chunked header (size + \r\n) tail (\r\n) */
			size = entity->read_entity(entity->priv_data, buffer + HTTP_CHUNKED_MAX_LENGTH + 2,
				module->config.send_buffer_size - HTTP_CHUNKED_MAX_LENGTH - 4, module->req.sent_length);
			if (size < 0) {
				/* If occurs problem during the operation, Close this socket. */
				size = 0;
			}
			buffer[HTTP_CHUNKED_MAX_LENGTH + 1] = '\n';
			buffer[HTTP_CHUNKED_MAX_LENGTH] = '\r';
			buffer[size + HTTP_CHUNKED_MAX_LENGTH + 2] = '\r';
			buffer[size + HTTP_CHUNKED_MAX_LENGTH + 3] = '\n';
			if (size >= 0) {
				ptr = buffer + 2;
				*ptr = CH_LUT[size % 16];
			}
			if (size >= 0x10) {
				ptr = buffer + 1;
				*ptr = CH_LUT[(size / 0x10) % 16];
			}
			if (size >= 0x100) {
				ptr = buffer;
				*ptr = CH_LUT[(size / 0x100) % 16];
			}
			result = send(module->sock, (void*)ptr, ptr + HTTP_CHUNKED_MAX_LENGTH - buffer + size + 4, 0);			
			if (result < 0) {	
				_http_client_clear_conn(module, -EIO);
				return;
			}

			module->req.sent_length += size;

			if(size == 0) {
				if (module->req.entity.close_entity) {
					module->req.entity.close_entity(module->req.entity.priv_data);
				}
				module->req.state = STATE_SOCK_CONNECTED;
				if (module->cb) {
					module->cb(module, HTTP_CLIENT_CALLBACK_REQUESTED, &data);
				}
				break;
			}
		} else if (module->req.content_length > 0 && entity->read_entity) {
			/* Send entity. */
			if (module->req.sent_length >= module->req.content_length) {
				/* Complete to send the buffer. */
				if (module->req.entity.close_entity) {
					module->req.entity.close_entity(module->req.entity.priv_data);
				}
				module->req.state = STATE_SOCK_CONNECTED;
				if (module->cb) {
					module->cb(module, HTTP_CLIENT_CALLBACK_REQUESTED, &data);
				}
				break;
			}
			size = entity->read_entity(entity->priv_data, buffer, module->config.send_buffer_size, module->req.sent_length);

			if (size < 0) {
				/* Entity occurs errors or EOS. */
				/* Disconnect it. */
				_http_client_clear_conn(module, (size == 0)?-EBADMSG:-EIO);
			} else {
				if (size > module->req.content_length - module->req.sent_length) {
					size = module->req.content_length - module->req.sent_length;
				}
				result = send(module->sock, (void*)buffer, size, 0);
				if (result < 0) {
					_http_client_clear_conn(module, -EIO);
					return;
				}
				module->req.sent_length += size;
			}
		} else {
			/* Has not any entity. */
			module->req.state = STATE_SOCK_CONNECTED;
			if (module->cb) {
				module->cb(module, HTTP_CLIENT_CALLBACK_REQUESTED, &data);
			}
			break;
		}

		break;
	default:
		/* Invalid status. */
		break;
	}
}

int32_t _http_client_recv_packet(struct http_client_module *const module)
{
	int32_t bytes_received = 0;
	if (module == NULL) {
		return -1;
	}
	
	if (module->recved_size >= module->config.recv_buffer_size) {
		/* Has not enough memory. */
		_http_client_clear_conn(module, -EOVERFLOW);
		return -1;
	}
	/* Executing read until receiving operation is started. */
	memset(module->config.recv_buffer + module->recved_size,0,module->config.recv_buffer_size - module->recved_size);

	bytes_received = recv(module->sock,
						module->config.recv_buffer + module->recved_size,
						module->config.recv_buffer_size - module->recved_size, 0);
		
	if(module->sending == 1 && module->req.state > STATE_SOCK_CONNECTED){
		sw_timer_task(module->config.timer_inst);
	}
	return bytes_received;
}

void _http_client_recved_packet(struct http_client_module *const module, int read_len)
{
	module->recved_size += read_len;
	if (module->config.timeout > 0 && module->sending == 1) {
		sw_timer_disable_callback(module->config.timer_inst, module->timer_id);
		module->sending = 0;
	}
	/* Recursive function call can be occurred overflow. */
	while(_http_client_handle_response(module) != 0);
}

int _http_client_handle_response(struct http_client_module *const module)
{		
	switch(module->resp.state) {
		case STATE_PARSE_HEADER:
			return _http_client_handle_header(module);
		case STATE_PARSE_ENTITY:
			return _http_client_handle_entity(module);
	}
	return 0;
}

int _http_client_handle_header(struct http_client_module *const module)
{
	char *ptr_line_end, *ptr;
	union http_client_data data;
	/* New line character only used in this function. So variable registered in the code region. */
	static const char *new_line = "\r\n";

	//TODO : header filter

	for (ptr = module->config.recv_buffer ; ; ) {
		ptr_line_end = strstr(ptr, new_line);
		if (ptr_line_end == NULL || ptr_line_end >= module->config.recv_buffer + module->recved_size) {
			/* not enough buffer. */
			_http_client_move_buffer(module, ptr);
			return 0;
		}

		if (!strncmp(ptr, new_line, strlen(new_line))) {
			/* Move remain data to forward part of buffer. */
			_http_client_move_buffer(module, ptr + strlen(new_line));

			/* Check validation first. */
			if (module->cb && module->resp.response_code) {
				/* Chunked transfer */
				if (module->resp.content_length < 0) {
					data.recv_response.response_code = module->resp.response_code;
					data.recv_response.is_chunked = 1;
					module->resp.read_length = 0;
					data.recv_response.content = NULL;
					module->cb(module, HTTP_CLIENT_CALLBACK_RECV_RESPONSE, &data);
				} else if (module->resp.content_length > (int)module->config.recv_buffer_size) {
					/* Entity is bigger than receive buffer. Sending the buffer to user like chunked transfer. */
					data.recv_response.response_code = module->resp.response_code;
					data.recv_response.content_length = module->resp.content_length;
					data.recv_response.content = NULL;
					module->resp.read_length = 0;
					module->cb(module, HTTP_CLIENT_CALLBACK_RECV_RESPONSE, &data);
				}
			}

			module->resp.state = STATE_PARSE_ENTITY;
			return 1;
		} else if (!strncmp(ptr, "Content-Length: ", strlen("Content-Length: "))) {
			module->resp.content_length = atoi(ptr + strlen("Content-Length: "));
		} else if (!strncmp(ptr, "Transfer-Encoding: ", strlen("Transfer-Encoding: "))) {
			/* Currently does not support gzip or deflate encoding. If received this header, disconnect session immediately*/
			char *type_ptr = ptr + strlen("Transfer-Encoding: ");
			for (; ptr_line_end > type_ptr; type_ptr++) {
				if (*type_ptr == ' ') {
					continue;
				} else if (*type_ptr == 'C' || *type_ptr == 'c') {
					/* Chunked transfer */
					module->req.content_length = -1;
				} else {
					_http_client_clear_conn(module, -ENOTSUP);
					return 0;
				}
				break;
			}
		} else if (!strncmp(ptr, "Connection: ", strlen("Connection: "))) {
			char *type_ptr = ptr + strlen("Connection: ");
			for (; ptr_line_end > type_ptr; type_ptr++) {
				if (*type_ptr == ' ') {
					continue;
				} else if (*type_ptr == 'K' || *type_ptr == 'k') {
					module->permanent = 1;
				} else {
					module->permanent = 0;
				}
				break;
			}
		} else if (!strncmp(ptr, "HTTP/", 5)) {
			module->resp.response_code = atoi(ptr + 9); /* HTTP/{Ver} {Code} {Desc} : HTTP/1.1 200 OK */
			/* Initializing the variables */
			module->resp.content_length = 0;
			/* persistent connection is turn on in the HTTP 1.1 or above version of protocols. */  
			if (ptr [5] > '1' || ptr[7] > '0') {
				module->permanent = 1;
			} else {
				module->permanent = 0;
			}
		}

		ptr = ptr_line_end + strlen(new_line);
	}
}

static void _http_client_read_chuked_entity(struct http_client_module *const module)
{		
	/* In chunked mode, read_length variable is means to remain data in the chunk. */
	union http_client_data data;
	int length = (int)module->recved_size;
	int extension = 0;
	char *buffer= module->config.recv_buffer;

	do {
		if (module->resp.read_length >= 0) {
			if (module->resp.read_length == 0) {
				/* Complete to receive the buffer. */
				module->resp.state = STATE_PARSE_HEADER;
				module->resp.response_code = 0;
				data.recv_chunked_data.is_complete = 1;
				data.recv_chunked_data.length = 0;
				data.recv_chunked_data.data = NULL;
				if (module->cb) {
					module->cb(module, HTTP_CLIENT_CALLBACK_RECV_CHUNKED_DATA, &data);
				}
				if (module->permanent == 0) {
					/* This server was not supported keep alive. */
					_http_client_clear_conn(module, 0);
					return;
				}
				_http_client_move_buffer(module, buffer + 2);
			} else if (module->resp.read_length <= length) {
				data.recv_chunked_data.length = module->resp.read_length;
				data.recv_chunked_data.data = buffer;
				data.recv_chunked_data.is_complete = 0;

				if (module->cb) {
					module->cb(module, HTTP_CLIENT_CALLBACK_RECV_CHUNKED_DATA, &data);
				}
				/* Last two character in the chunk is '\r\n'. */
				_http_client_move_buffer(module, buffer + module->resp.read_length + 2 /* sizeof newline character */);
				length = (int)module->recved_size;
				buffer = module->config.recv_buffer;
				module->resp.read_length = -1;
			}
		} else {
			/* Read chunked length. */
			module->resp.read_length = 0;
			for (; length > 0; buffer++, length--) {
				if (*buffer == '\n') {
					buffer++;
					length--;
					break;
				}
				if (extension != 0) {
					continue;
				}
				if (*buffer >= '0' && *buffer <= '9') {
					module->resp.read_length = module->resp.read_length * 0x10 + *buffer - '0';
				} else if (*buffer >= 'a' && *buffer <= 'f') {
					module->resp.read_length = module->resp.read_length * 0x10 + *buffer - 'a';
				} else if (*buffer >= 'A' && *buffer <= 'F') {
					module->resp.read_length = module->resp.read_length * 0x10 + *buffer - 'A';
				} else if (*buffer == ';') {
					extension = 1;
				}
			}

			if (module->resp.read_length > (int)module->config.recv_buffer_size) {
				/* Chunked size is too big. */
				/* Through exception. */
				_http_client_clear_conn(module, -EOVERFLOW);
				return;
			}

			if (length  == 0) {
				/* currently not received packet yet. */
				module->resp.read_length = -1;
				return;
			}
		}
	} while(module->recved_size > 0);
}

int _http_client_handle_entity(struct http_client_module *const module)
{
	union http_client_data data;
	char *buffer = module->config.recv_buffer;

	/* If data size is lesser than buffer size, read all buffer and retransmission it to application. */
	if (module->resp.content_length >= 0 && module->resp.content_length <= (int)module->config.recv_buffer_size) {
		if ((int)module->recved_size >= module->resp.content_length) {
			if (module->cb && module->resp.response_code) {
				data.recv_response.response_code = module->resp.response_code;
				data.recv_response.is_chunked = 0;
				data.recv_response.content_length = module->resp.content_length;
				data.recv_response.content = buffer;
				module->cb(module, HTTP_CLIENT_CALLBACK_RECV_RESPONSE, &data);
			}
			module->resp.state = STATE_PARSE_HEADER;
			module->resp.response_code = 0;
			
			if (module->permanent == 0) {
				/* This server was not supported keep alive. */
				_http_client_clear_conn(module, 0);
			} else {
				_http_client_move_buffer(module, buffer + module->resp.content_length);
				return module->recved_size;
			}
		}
		/* else, buffer was not received enough size yet. */
	} else {
		if (module->resp.content_length >= 0) {
			data.recv_chunked_data.length = module->recved_size;
			data.recv_chunked_data.data = buffer;
			module->resp.read_length += (int)module->recved_size;
			if (module->resp.content_length <= module->resp.read_length) {
				/* Complete to receive the buffer. */
				module->resp.state = STATE_PARSE_HEADER;
				module->resp.response_code = 0;
				data.recv_chunked_data.is_complete = 1;
			} else {
				data.recv_chunked_data.is_complete = 0;
			}
			if (module->cb) {
				module->cb(module, HTTP_CLIENT_CALLBACK_RECV_CHUNKED_DATA, &data);
			}
			
			if (data.recv_chunked_data.is_complete == 1) {
				if (module->permanent == 0) {
					/* This server was not supported keep alive. */
					_http_client_clear_conn(module, 0);
					return 0;
				}
			}
			_http_client_move_buffer(module, buffer + module->recved_size);
		} else {
			_http_client_read_chuked_entity(module);
		}
	}

	return 0;
}

void _http_client_move_buffer(struct http_client_module *const module, char *base)
{
	char *buffer = module->config.recv_buffer;
	int remain = (int)module->recved_size - (int)base + (int)buffer;

	if (remain > 0) {
		memmove(buffer, base, remain);
		module->recved_size = remain;
	} else {
		module->recved_size = 0;
	}
}
