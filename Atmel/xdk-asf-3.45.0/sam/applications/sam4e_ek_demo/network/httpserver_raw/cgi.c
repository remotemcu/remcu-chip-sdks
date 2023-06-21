/**
 * \file
 *
 * \brief CGI request function handlers.
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

#include <string.h>
#include <FreeRTOS.h>
#include <task.h>
#include "lwip/debug.h"
#include "lwip/tcp.h"
#include "afec.h"
#include "httpd.h"
#include "cgi.h"
#include "led.h"
#include "sysclk.h"

#define CGI_MATCH_NONE   0
/** Select item in table only if string match */
#define CGI_MATCH_WORD   1
/** Select item in table if the extention match */
#define CGI_MATCH_EXT    2
/** Select item in table if the string is content */
#define CGI_MATCH_NAME   3

#define CGI_LED_ID_KEY    "n"
#define CGI_LED_CMD_KEY   "set"
#define GET_LED_STATUS(status, led_id) \
		(((status) & (1 << (led_id))) >> (led_id))
#define CLEAR_LED_STATUS(status, led_id)   ((status) &= ~(1 << (led_id)))
#define SET_LED_STATUS(status, led_id)     ((status) |= (1 << (led_id)))

#define CHIPID_NVTYP   (((CHIPID->CHIPID_CIDR) & \
		CHIPID_CIDR_NVPTYP_Msk) >> CHIPID_CIDR_NVPTYP_Pos)
#define CHIPID_NVPSIZ  (((CHIPID->CHIPID_CIDR) & \
		CHIPID_CIDR_NVPSIZ_Msk) >> CHIPID_CIDR_NVPSIZ_Pos)
#define CHIPID_SRAMSIZ (((CHIPID->CHIPID_CIDR) & \
		CHIPID_CIDR_SRAMSIZ_Msk) >> CHIPID_CIDR_SRAMSIZ_Pos)
#define CHIPID_ARCH    (((CHIPID->CHIPID_CIDR) & \
		CHIPID_CIDR_ARCH_Msk) >> CHIPID_CIDR_ARCH_Pos)
#define CHIPID_EPRCOC  (((CHIPID->CHIPID_CIDR) & \
		CHIPID_CIDR_EPROC_Msk) >> CHIPID_CIDR_EPROC_Pos)

/** Macro to unpack the ip address from LwIP format into 4 integers. */
#define IP_ADDR_TO_INT_TUPLE(addr)  \
		(int)((addr) >> 0 & 0xff),  \
		(int)((addr) >> 8 & 0xff),  \
		(int)((addr) >> 16 & 0xff), \
		(int)((addr) >> 24 & 0xff)

#define CGI_MSG_CMD_KEY   "msg"

extern uint32_t mag_in_buffer_int[];

static const char _unknown[] = "unknown";

static const char *const chip_id_eproc_names[] = {
	_unknown,                               /* 0 */
	"arm946es",                             /* 1 */
	"arm7tdmi",                             /* 2 */
	"cortex-m3",                            /* 3 */
	"arm920t",                              /* 4 */
	"arm926ejs",                            /* 5 */
	"cortex-a5",                            /* 6 */
	"cortex-m4"                             /* 7 */
};

static const char *const chip_id_nvpsize[] = {
	"none",                                 /*  0 */
	"8K bytes",                             /*  1 */
	"16K bytes",                            /*  2 */
	"32K bytes",                            /*  3 */
	_unknown,                               /*  4 */
	"64K bytes",                            /*  5 */
	_unknown,                               /*  6 */
	"128K bytes",                           /*  7 */
	_unknown,                               /*  8 */
	"256K bytes",                           /*  9 */
	"512K bytes",                           /* 10 */
	_unknown,                               /* 11 */
	"1024K bytes",                          /* 12 */
	_unknown,                               /* 13 */
	"2048K bytes",                          /* 14 */
	_unknown,                               /* 15 */
};

static const char *const chip_id_sramsize[] = {
	"48K bytes",                            /*  0 */
	"1K bytes",                             /*  1 */
	"2K bytes",                             /*  2 */
	"6K bytes",                             /*  3 */
	"112K bytes",                           /*  4 */
	"4K bytes",                             /*  5 */
	"80K bytes",                            /*  6 */
	"160K bytes",                           /*  7 */
	"8K bytes",                             /*  8 */
	"16K bytes",                            /*  9 */
	"32K bytes",                            /* 10 */
	"64K bytes",                            /* 11 */
	"128K bytes",                           /* 12 */
	"256K bytes",                           /* 13 */
	"96K bytes",                            /* 14 */
	"512K bytes",                           /* 15 */
};

static const struct archnames { unsigned value; const char *name; }
chip_id_archnames[] = {
	{0x19, "AT91SAM9xx Series"},
	{0x29, "AT91SAM9XExx Series"},
	{0x34, "AT91x34 Series"},
	{0x37, "CAP7 Series"},
	{0x39, "CAP9 Series"},
	{0x3B, "CAP11 Series"},
	{0x3C, "SAM4E Series"},
	{0x40, "AT91x40 Series"},
	{0x42, "AT91x42 Series"},
	{0x55, "AT91x55 Series"},
	{0x60, "AT91SAM7Axx Series"},
	{0x61, "AT91SAM7AQxx Series"},
	{0x63, "AT91x63 Series"},
	{0x70, "AT91SAM7Sxx Series"},
	{0x71, "AT91SAM7XCxx Series"},
	{0x72, "AT91SAM7SExx Series"},
	{0x73, "AT91SAM7Lxx Series"},
	{0x75, "AT91SAM7Xxx Series"},
	{0x76, "AT91SAM7SLxx Series"},
	{0x80, "ATSAM3UxC Series (100-pin version)"},
	{0x81, "ATSAM3UxE Series (144-pin version)"},
	{0x83, "ATSAM3AxC Series (100-pin version)"},
	{0x84, "ATSAM3XxC Series (100-pin version)"},
	{0x85, "ATSAM3XxE Series (144-pin version)"},
	{0x86, "ATSAM3X8H Series (217-pin version)"},
	{0x88, "ATSAM3SxA Series (48-pin version)"},
	{0x89, "ATSAM3SxB Series (64-pin version)"},
	{0x8A, "ATSAM3SxC Series (100-pin version)"},
	{0x92, "AT91x92 Series"},
	{0x95, "ATSAM3NxC Series (100-pin version)"},
	{0xF0, "AT75Cxx Series"},
	{(unsigned)-1, NULL},
};

static const char *const chip_id_nvptype[] = {
	"rom",                                    /* 0 */
	"romless or onchip flash",                /* 1 */
	"embedded flash memory",                  /* 2 */
	"rom(nvpsiz) + embedded flash (nvpsiz2)", /* 3 */
	"sram emulating flash",                   /* 4 */
};

/** HTTP buffer to store key value. */
static char key_value[80];

/** FIFO tx buffer. */
#define CONFIG_AFSK_TX_BUFLEN                   1024
u8_t tx_buf[CONFIG_AFSK_TX_BUFLEN];

/** Function declarations */
static int cgi_echo(const char *name, char *recv_buf, size_t recv_len);
static int cgi_temp(const char *name, char *recv_buf, size_t recv_len);
static int cgi_uptime(const char *name, char *recv_buf, size_t recv_len);
static int cgi_resistor(const char *name, char *recv_buf, size_t recv_len);
static int cgi_led(const char *name, char *recv_buf, size_t recv_len);
static int cgi_ledStatus(const char *name, char *recv_buf, size_t recv_len);
static int cgi_error(const char *name, char *recv_buf, size_t recv_len);
static int cgi_status(const char *name, char *recv_buf, size_t recv_len);
static int cgi_chipInfo(const char *name, char *recv_buf, size_t recv_len);
static int cgi_displayMsg(const char *name, char *recv_buf, size_t recv_len);

/**
 * CGI table where we associate one callback to one page.
 */
HttpCGI cgi_table[] = {
	{CGI_MATCH_NAME, "echo", cgi_echo},
	{CGI_MATCH_NAME, "get_temperature", cgi_temp},
	{CGI_MATCH_NAME, "get_uptime", cgi_uptime},
	{CGI_MATCH_NAME, "get_resistor", cgi_resistor},
	{CGI_MATCH_NAME, "set_led", cgi_led},
	{CGI_MATCH_NAME, "get_ledStatus", cgi_ledStatus},
	{CGI_MATCH_NAME, "error", cgi_error},
	{CGI_MATCH_NAME, "status", cgi_status},
	{CGI_MATCH_NAME, "get_chipinfo", cgi_chipInfo},
	{CGI_MATCH_NAME, "display", cgi_displayMsg},
	{CGI_MATCH_NONE, NULL, NULL}
};

/**
 * \brief Send back the input string.
 *
 * \param name Not used.
 * \param recv_buf Receive buffer to send back.
 * \param recv_len Receive buffer length.
 *
 * \return 0.
 */
static int cgi_echo(const char *name, char *recv_buf, size_t recv_len)
{
	UNUSED(name);

	http_sendOk(HTTP_CONTENT_PLAIN);
	http_write(recv_buf, recv_len);
	return 0;
}

/**
 * \brief Send the internal core temperature in string format.
 *
 * \param name Not used.
 * \param recv_buf Receive buffer.
 * \param recv_len Receive buffer length.
 *
 * \return 0.
 */
static int cgi_temp(const char *name, char *recv_buf, size_t recv_len)
{
	UNUSED(recv_buf);
	UNUSED(recv_len);
	UNUSED(name);

	sprintf((char *)tx_buf, "[%d.%d]", status.internal_temp / 100,
			status.internal_temp % 100);

	http_sendOk(HTTP_CONTENT_JSON);
	http_write((const char *)tx_buf, strlen((char *)tx_buf));

	return 0;
}

/**
 * \brief convert seconds to day/hour/minute/sec.
 *
 * \param sec_time Time value.
 * \param str Buffer to store date.
 * \param len Buffer length.
 *
 * \return 0 on success, -1 otherwise.
 */
static int sec_to_strDhms(u32_t sec_time, char *str, size_t len)
{
	u32_t h = (sec_time / 3600);
	u32_t d = h / 24;
	u32_t m = ((sec_time - (h * 3600)) / 60);
	u32_t s = (sec_time - (m * 60) - (h * 3600));

	if (len < sizeof("xxxxd xxh xxm xxs")) {
		return -1;
	}

	sprintf(str, "%ldd %ldh %ldm %lds", (long)d, (h >= 24) ? (long)(h - 24)
			: (long)h, (long)m, (long)s);

	return 0;
}

/**
 * \brief Send system uptime.
 *
 * \param name Not used.
 * \param recv_buf Receive buffer.
 * \param recv_len Receive buffer length.
 *
 * \return 0.
 */
static int cgi_uptime(const char *name, char *recv_buf, size_t recv_len)
{
	UNUSED(recv_buf);
	UNUSED(recv_len);
	UNUSED(name);

	sec_to_strDhms(status.up_time, (char *)tx_buf, sizeof(tx_buf));

	http_sendOk(HTTP_CONTENT_JSON);
	http_write((const char *)tx_buf, strlen((char *)tx_buf));

	return 0;
}

/**
 * \brief Send the potentiometer voltage.
 *
 * \param name Not used.
 * \param recv_buf Receive buffer.
 * \param recv_len Receive buffer length.
 *
 * \return 0.
 */
static int cgi_resistor(const char *name, char *recv_buf, size_t recv_len)
{
	UNUSED(recv_buf);
	UNUSED(recv_len);
	UNUSED(name);

	u16_t volt;

	volt = afec_channel_get_value(AFEC0, AFEC_CHANNEL_5) * 10000 / 4096;

	sprintf((char *)tx_buf, "[ \"%d.%dV\" ]", volt / 1000, volt % 1000);

	http_sendOk(HTTP_CONTENT_JSON);
	http_write((const char *)tx_buf, strlen((char *)tx_buf));

	return 0;
}

/**
 * \brief Set the led status and send back the new status.
 *
 * \param name String containing the led status request.
 * \param recv_buf Receive buffer.
 * \param recv_len Receive buffer length.
 *
 * \return 0.
 */
static int cgi_led(const char *name, char *recv_buf, size_t recv_len)
{
	UNUSED(recv_buf);
	UNUSED(recv_len);
	UNUSED(name);

	char *query_str = strstr(name, "?") + 1;
	size_t query_str_len = strlen(query_str);
	int led_id;
	int led_pio;
	int led_cmd;

	http_tokenizeGetRequest(query_str, query_str_len);

	if (http_getValue(query_str, query_str_len, CGI_LED_ID_KEY, key_value,
			sizeof(key_value)) < 0) {
		goto error;
	}

	led_id = atoi(key_value);

	if (http_getValue(query_str, query_str_len, CGI_LED_CMD_KEY, key_value,
			sizeof(key_value)) < 0) {
		goto error;
	}

	led_cmd = atoi(key_value);

	if (led_id == 0) {
		led_pio = LED2_GPIO;
	} else if (led_id == 1) {
		led_pio = LED1_GPIO;
	} else if (led_id == 2) {
		led_pio = LED0_GPIO;
	} else if (led_id == 3) {
		led_pio = LED3_GPIO;
	}

	if (led_cmd) {
		ioport_set_pin_level(led_pio, LED2_ACTIVE_LEVEL);
		SET_LED_STATUS(status.led_status, led_id);
	} else {
		ioport_set_pin_level(led_pio, LED2_INACTIVE_LEVEL);
		CLEAR_LED_STATUS(status.led_status, led_id);
	}

	sprintf((char *)tx_buf, "{\"n\":%d, \"set\":,%d}", led_id, led_cmd);

	http_sendOk(HTTP_CONTENT_JSON);
	http_write((const char *)tx_buf, strlen((char *)tx_buf));
	return 0;

error:
	http_sendInternalErr(HTTP_CONTENT_JSON);
	return 0;
}

/**
 * \brief Send the led status.
 *
 * \param name Not used.
 * \param recv_buf Receive buffer.
 * \param recv_len Receive buffer length.
 *
 * \return 0.
 */
static int cgi_ledStatus(const char *name, char *recv_buf, size_t recv_len)
{
	UNUSED(recv_buf);
	UNUSED(recv_len);
	UNUSED(name);

	sprintf((char *)tx_buf, "{ \"0\":\"%d\", \"1\":\"%d\", \"2\":\"%d\"}",
			GET_LED_STATUS(status.led_status, 0),
			GET_LED_STATUS(status.led_status, 1),
			GET_LED_STATUS(status.led_status, 2));

	http_sendOk(HTTP_CONTENT_JSON);
	http_write((const char *)tx_buf, strlen((char *)tx_buf));

	return 0;
}

/**
 * \brief Used to handle unsupported CGI requests.
 *
 * \param name Not used.
 * \param recv_buf Receive buffer.
 * \param recv_len Receive buffer length.
 *
 * \return -1.
 */
static int cgi_error(const char *name, char *recv_buf, size_t recv_len)
{
	UNUSED(name);
	UNUSED(recv_buf);
	UNUSED(recv_len);

	return -1;
}

/**
 * \brief Send a JSON string representing the board status.
 *
 * \param name Not used.
 * \param recv_buf Receive buffer.
 * \param recv_len Receive buffer length.
 *
 * \return 0.
 */
static int cgi_status(const char *name, char *recv_buf, size_t recv_len)
{
	UNUSED(recv_buf);
	UNUSED(recv_len);
	UNUSED(name);

	volatile uint16_t volt;
	uint32_t length = 0;
	uint32_t i;
	status.tot_req++;

	volt = afec_channel_get_value(AFEC0, AFEC_CHANNEL_5);

	status.up_time = xTaskGetTickCount() / 1000;

	/* Update board status. */
	sprintf(status.last_connected_ip, "%d.%d.%d.%d",
			IP_ADDR_TO_INT_TUPLE(g_pcb->remote_ip.addr));
	sprintf(status.local_ip, "%d.%d.%d.%d",
			IP_ADDR_TO_INT_TUPLE(g_pcb->local_ip.addr));
	length += sprintf((char *)tx_buf,
			"{\"local_ip\":\"%s\",\"last_connected_ip\":\"%s\", \"temp\":%d.%d, \"mag\":\"",
			status.local_ip, status.last_connected_ip,
			status.internal_temp / 100, status.internal_temp % 100);

	/* Update magnitude graph (98 + 1). */
	for (i = 0; i < 98; ++i) {
		length += sprintf((char *)tx_buf + length, "%d|",
				mag_in_buffer_int[i]);
	}
	length
		+= sprintf((char *)tx_buf + length, "%d\"",
			mag_in_buffer_int[i]);

	/* Remaining board status. */
	length += sprintf((char *)tx_buf + length,
			",\"volt\":%d,\"up_time\":%ld,\"tot_req\":%d, \"leds\":{ \"0\":\"%d\", \"1\":\"%d\", \"2\":\"%d\"}}",
			volt, status.up_time, status.tot_req,
			GET_LED_STATUS(status.led_status, 0),
			GET_LED_STATUS(status.led_status, 1),
			GET_LED_STATUS(status.led_status, 2));

	/* Send answer. */
	http_sendOk(HTTP_CONTENT_JSON);
	http_write((char const *)tx_buf, strlen((char *)tx_buf));

	return 0;
}

/**
 * \brief Return the chip ID name.
 *
 * \param idx Index in the chip_id_eproc_names table.
 *
 * \return The chip id name.
 */
static const char *chipid_eproc_name(int idx)
{
	if (idx <= 7) {
		return chip_id_eproc_names[idx];
	}

	return _unknown;
}

/**
 * \brief Return the non volatile programmable memory size.
 *
 * \param idx Index in the chip_id_nvpsize table.
 *
 * \return The chip non volatile programmable memory size.
 */
static const char *chipid_nvpsize(int idx)
{
	if (idx <= 15) {
		return chip_id_nvpsize[idx];
	}

	return _unknown;
}

/**
 * \brief Return the chip SRAM size.
 *
 * \param idx Index in the chip_id_sramsize table.
 *
 * \return The chip SRAM size.
 */
static const char *chipid_sramsize(int idx)
{
	if (idx <= 15) {
		return chip_id_sramsize[idx];
	}

	return _unknown;
}

/**
 * \brief Return the chip architecture name.
 *
 * \param idx Index in the chip_id_archnames table.
 *
 * \return The chip architecture name.
 */
static const char *chipid_archnames(unsigned value)
{
	for (int i = 0; chip_id_archnames[i].name; i++) {
		if (chip_id_archnames[i].value == value) {
			return chip_id_archnames[i].name;
		}
	}

	return _unknown;
}

/**
 * \brief Return the chip volatile programmable memory type.
 *
 * \param idx Index in the chip_id_nvptype table.
 *
 * \return The chip non volatile programmable memory type.
 */
static const char *chipid_nvptype(int idx)
{
	if (idx <= 4) {
		return chip_id_nvptype[idx];
	}

	return _unknown;
}

/**
 * \brief Send the chip ID information.
 *
 * \param name Not used.
 * \param recv_buf Receive buffer.
 * \param recv_len Receive buffer length.
 *
 * \return 0.
 */
static int cgi_chipInfo(const char *name, char *recv_buf, size_t recv_len)
{
	UNUSED(recv_buf);
	UNUSED(recv_len);
	UNUSED(name);

	sprintf((char *)tx_buf,
			"{ \"core_name\":\"%s\", \"arch_name\":\"%s\", \"sram_size\":\"%s\",\"flash_size\":\"%s\", \"mem_boot_type\":\"%s\" }",
			chipid_eproc_name(CHIPID_EPRCOC),
			chipid_archnames(CHIPID_ARCH),
			chipid_sramsize(CHIPID_SRAMSIZ),
			chipid_nvpsize(CHIPID_NVPSIZ),
			chipid_nvptype(CHIPID_NVTYP));

	http_sendOk(HTTP_CONTENT_JSON);
	http_write((const char *)tx_buf, strlen((char *)tx_buf));

	return 0;
}

/**
 * \brief Read a message.
 *
 * \param name Request containing the message.
 * \param recv_buf Receive buffer.
 * \param recv_len Receive buffer length.
 *
 * \return 0.
 */
static int cgi_displayMsg(const char *name, char *recv_buf, size_t recv_len)
{
	UNUSED(recv_buf);
	UNUSED(recv_len);
	UNUSED(name);

	char *query_str = strstr(name, "?") + 1;
	size_t query_str_len = strlen(query_str);

	http_tokenizeGetRequest(query_str, query_str_len);

	if (http_getValue(query_str, query_str_len, CGI_MSG_CMD_KEY, key_value,
			sizeof(key_value)) > 0) {
		http_sendOk(HTTP_CONTENT_JSON);
		return 0;
	}

	http_sendInternalErr(HTTP_CONTENT_JSON);
	return 0;
}

/**
 * \brief CGI request search engine.
 *
 * \param name CGI request name.
 * \param table CGI handler table.
 *
 * \return A valid function handler for the specified CGI request, NULL
 * otherwise.
 */
http_handler_t cgi_search(const char *name, HttpCGI *table)
{
	if (!table) {
		return NULL;
	}

	int i = 0;
	const char *ext = get_ext(name);

	while (table[i].name) {
		if (ext && table[i].type == CGI_MATCH_EXT) {
			if (!strcmp(table[i].name, ext)) {
				break;
			}
		} else if (table[i].type == CGI_MATCH_NAME) {
			if (strstr(name, table[i].name) != NULL) {
				break;
			}
		} else { /* (table[i].type == CGI_MATCH_WORD) */
			if (!strcmp(table[i].name, name)) {
				break;
			}
		}

		i++;
	}

	return table[i].handler;
}
