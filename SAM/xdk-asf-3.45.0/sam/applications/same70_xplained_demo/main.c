/**
 *
 * \file
 *
 * \brief SAME70 Weather Client Demo Example.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

/** \mainpage
 * \section intro Introduction
 * This example demonstrates the use of the WINC1500 with the SAM Xplained Pro
 * board to retrieve weather information from openweathermap.org server.
 * The related informaiton will be displayed on LCD. It can switch different city
 * by pushing button.
 *
 * It uses the following hardware:
 * - the SAM Xplained Pro.
 * - the WINC1500-Xpro on EXT1.
 * - the ATMXT-Xpro on EXT2.
 *
 * \section files Main Files
 * - main.c : Initialize the WINC1500 and retrieve information.
 *
 * \section usage Usage
 * -# Build the program and download it into the board.
 * -# On the computer, open and configure a terminal application as the follows.
 * \code
 *    Baud Rate : 115200
 *    Data : 8bit
 *    Parity bit : none
 *    Stop bit : 1bit
 *    Flow control : none
 * \endcode
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 * \code
 *    -- SAME70 Weather Client Demo --
 *    -- SAMXXX_XPLAINED_PRO --
 *    -- Compiled: xxx xx xxxx xx:xx:xx --
 *    Connecting to AVRGUEST.
 *    Wi-Fi connected
 *    Wi-Fi IP is xxx.xxx.xxx.xxx
 *    Host IP is 144.76.102.166
 *    Host Name is openweathermap.org
 *    City: Shanghai
 *    Temperature: 18.6
 *    Weather Condition: rain
 *    City: Seoul
 *    Temperature: 20.63
 *    Weather Condition: sky is clear
 * \endcode
 *
 * \section compinfo Compilation Information
 * This software was written for the GNU GCC compiler using Atmel Studio 6.2
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com">Microchip</A>.\n
 */

#include "asf.h"
#include "image.h"
#include "main_wifi.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "bsp/include/nm_bsp.h"
#include "driver/include/m2m_wifi.h"
#include "socket/include/socket.h"

/** IP address of host. */
uint32_t gu32HostIp = 0;

uint32_t g_ul_sec_ticks = 0;

/** TCP client socket handlers. */
static SOCKET tcp_client_socket = -1;

/** Receive buffer definition. */
static uint8_t gau8ReceivedBuffer[MAIN_WIFI_M2M_BUFFER_SIZE] = {0};

/** Wi-Fi status variable. */
static bool gbConnectedWifi = false;

/** Get host IP status variable. */
static bool gbHostIpByName = false;

/** Continue Receive status variable. */
static bool gbContinueReceive = false;

/** TCP Connection status variable. */
static bool gbTcpConnection = false;

/** Server host name. */
static char server_host_name[] = MAIN_WEATHER_SERVER_NAME;

static char gcWeatherInfo[2048] = {0};

/** Weather client status variable. */
static bool gbFinishedGetWeather = false;
static bool gbRequireWeather = false;

/** ASCII char definition for backspace. */
#define ASCII_BS    0x7F
/** ASCII char definition for carriage return. */
#define ASCII_CR    13

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- SAME70 Weather Client Demo --"STRING_EOL	\
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

struct ili9488_opt_t g_ili9488_display_opt;

char *pcCity = NULL;
char *pcTemperature = NULL;
char *pcWeather = NULL;
uint8_t ucWeatherNum = 0;

char Temperature_sha[30];
char Weather_sha[30];
uint8_t ucWeatherNum_sha;

char Temperature_seoul[30];
char Weather_seoul[30];
uint8_t ucWeatherNum_seoul;

bool city_is_sha = true;
bool display_is_sha = true;

char *gWeatherIcon[4] = {
	gImage_sun,
	gImage_cloud,
	gImage_rain,
	gImage_snow,
};
const uint8_t mark[11] = {'S', 'A', 'M', 'E','7', '0', 'D', 'E', 'M','O'};

void wifi_connect(void);
void ili9488_draw_temperature(uint32_t ul_x, uint32_t ul_y, char* temperature);
void ili9488_draw_number(uint32_t ul_x, uint32_t ul_y, uint8_t index);
void configure_rtt(void);

/**
 * \brief Callback function of IP address.
 *
 * \param[in] hostName Domain name.
 * \param[in] hostIp Server IP.
 *
 * \return None.
 */
static void resolve_cb(uint8_t *hostName, uint32_t hostIp)
{
	gu32HostIp = hostIp;
	gbHostIpByName = true;
	printf("Host IP is %d.%d.%d.%d\r\n", (int)IPV4_BYTE(hostIp, 0), (int)IPV4_BYTE(hostIp, 1),
			(int)IPV4_BYTE(hostIp, 2), (int)IPV4_BYTE(hostIp, 3));
	printf("Host Name is %s\r\n", hostName);
	//ili9488_set_foreground_color(COLOR_CONVERT(COLOR_WHITE));
	//ili9488_draw_filled_rectangle(0, 300, ILI9488_LCD_WIDTH-1, 315);
	//ili9488_set_foreground_color(COLOR_CONVERT(COLOR_BLACK));
	//ili9488_draw_string(10, 300, (uint8_t *)"Push button");
	configure_rtt();
	//pio_enable_interrupt(PIN_PUSHBUTTON_1_PIO, PIN_PUSHBUTTON_1_MASK);
}

/**
 * \brief Callback function of TCP client socket.
 *
 * \param[in] sock socket handler.
 * \param[in] u8Msg Type of Socket notification
 * \param[in] pvMsg A structure contains notification informations.
 *
 * \return None.
 */
static void socket_cb(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
	/* Check for socket event on TCP socket. */
	if (sock == tcp_client_socket) {
		switch (u8Msg) {
		case SOCKET_MSG_CONNECT:
		{
			if (gbTcpConnection) {

				tstrSocketConnectMsg *pstrConnect = (tstrSocketConnectMsg *)pvMsg;
				if (pstrConnect && pstrConnect->s8Error >= SOCK_ERR_NO_ERROR) {
					gbRequireWeather = true;
					//g_ul_sec_ticks = 58;
				} else {
					printf("socket_cb: connect error!\r\n");
					g_ul_sec_ticks = 0;
					gbRequireWeather = false;
					gbTcpConnection = false;
					close(tcp_client_socket);
					tcp_client_socket = -1;
				}
			}
		}
		break;

		case SOCKET_MSG_RECV:
		{
			tstrSocketRecvMsg *pstrRecv = (tstrSocketRecvMsg *)pvMsg;
			if (pstrRecv && pstrRecv->s16BufferSize > 0) {
				strcpy(gcWeatherInfo, (char *)pstrRecv->pu8Buffer);
				gbFinishedGetWeather = true;
			} else {
				printf("socket_cb: recv error!\r\n");
				g_ul_sec_ticks = 0;
				gbRequireWeather = false;
				gbTcpConnection = false;
				close(tcp_client_socket);
				tcp_client_socket = -1;
			}
		}
		break;

		default:
			break;
		}
	}
}

/**
 * \brief Callback to get the Wi-Fi status update.
 *
 * \param[in] u8MsgType Type of Wi-Fi notification.
 * \param[in] pvMsg A pointer to a buffer containing the notification parameters.
 *
 * \return None.
 */
static void wifi_cb(uint8_t u8MsgType, void *pvMsg)
{
	switch (u8MsgType) {
	case M2M_WIFI_RESP_CON_STATE_CHANGED:
	{
		tstrM2mWifiStateChanged *pstrWifiState = (tstrM2mWifiStateChanged *)pvMsg;
		if (pstrWifiState->u8CurrState == M2M_WIFI_CONNECTED) {
			printf("Wi-Fi connected\r\n");
			m2m_wifi_request_dhcp_client();
		} else if (pstrWifiState->u8CurrState == M2M_WIFI_DISCONNECTED) {
			printf("Wi-Fi disconnected\r\n");
			printf("Please reconnect Wi-Fi\r\n");
			gbConnectedWifi = false;
			wifi_connect();
		}

		break;
	}

	case M2M_WIFI_REQ_DHCP_CONF:
	{
		uint8_t *pu8IPAddress = (uint8_t *)pvMsg;
		/* Turn LED0 on to declare that IP address received. */
		printf("Wi-Fi IP is %u.%u.%u.%u\r\n",
				pu8IPAddress[0], pu8IPAddress[1], pu8IPAddress[2], pu8IPAddress[3]);
		gbConnectedWifi = true;
		/* Obtain the IP Address by network name */
		gethostbyname((uint8_t *)server_host_name);
		break;
	}

	default:
	{
		break;
	}
	}
}

static void wifi_init(void)
{
	tstrWifiInitParam param;
	int8_t ret;

	/* Initialize the BSP. */
	nm_bsp_init();

	/* Initialize Wi-Fi parameters structure. */
	memset((uint8_t *)&param, 0, sizeof(tstrWifiInitParam));

	/* Initialize Wi-Fi driver with data and status callbacks. */
	param.pfAppWifiCb = wifi_cb;
	ret = m2m_wifi_init(&param);
	if (M2M_SUCCESS != ret) {
		printf("main: m2m_wifi_init call error!(%d)\r\n", ret);
		while (1) {
		}
	}

	/* Initialize socket API. */
	socketInit();
	registerSocketCallback(socket_cb, resolve_cb);
}

void wifi_connect(void)
{
	char wlan_ssid[32];
	char wlan_pwd[32];
	uint8_t c;
	uint32_t i;
	volatile uint8_t ssid_length = 0;
	volatile uint8_t pwd_length = 0;
	uint8_t page_buffer[IFLASH_PAGE_SIZE];
	uint32_t page_addr = IFLASH_ADDR + IFLASH_SIZE - IFLASH_PAGE_SIZE;
	uint8_t *p_page_addr = (uint8_t *)page_addr;
	uint32_t ul_rc;
	bool is_need_input = false;

	for(i = 0; i < 32; i++) {
		wlan_ssid[i] = 0;
		wlan_pwd[i] = 0;
	}
	for(i = 0; i < IFLASH_PAGE_SIZE; i++) {
		page_buffer[i] = p_page_addr[i];
	}
	for(i = 0; i < 11; i++) {
		if(page_buffer[i] != mark[i]) {
			is_need_input = true;
		}
	}
	if(!ioport_get_pin_level(GPIO_PUSH_BUTTON_1)) {
		is_need_input = true;
	}
	if(is_need_input) {
		ili9488_set_foreground_color(COLOR_CONVERT(COLOR_BLACK));
		ili9488_draw_string(10, 300, (uint8_t *)"Input SSID and Password...");	
		printf("Please input your WLAN SSID Name.\r\n");
		while (1) {
			scanf("%c", &c);

			if (c == ASCII_BS) {
				printf("%c", ASCII_BS);
				ssid_length--;
				wlan_ssid[ssid_length] = 0;
			} else if(c == ASCII_CR) {
				wlan_ssid[ssid_length] = 0;
				printf("\r\n");
				break;
				} else {
				printf("%c", c);
				wlan_ssid[ssid_length] = c;
				ssid_length++;
			}
		}
		printf("Please input your WLAN Password.\r\n");
		while (1) {
			scanf("%c", &c);

			if (c == ASCII_BS) {
				printf("%c", ASCII_BS);
				pwd_length--;
				wlan_pwd[pwd_length] = 0;
			} else if(c == ASCII_CR) {
				wlan_pwd[pwd_length] = 0;
				printf("\r\n");
				break;
				} else {
				printf("%c", c);
				wlan_pwd[pwd_length] = c;
				pwd_length++;
			}
		}
		for(i = 0; i< 11; i++) {
			page_buffer[i] = mark[i];
		}
		for(i = 0; i < ssid_length; i++) {
			page_buffer[11 + i] = wlan_ssid[i];
		}
		for(i = 0; i < pwd_length; i++) {
			page_buffer[11 + ssid_length + i] = wlan_pwd[i];
		}
		page_buffer[75] = ssid_length;
		page_buffer[76] = pwd_length;

		ul_rc = flash_init(FLASH_ACCESS_MODE_128, 6);
		if (ul_rc != FLASH_RC_OK) {
			printf("-F- Initialization error %lu\n\r", ul_rc);
			return 0;
		}

		printf("-I- Unlocking test page: 0x%08x\r\n", page_addr);
		ul_rc = flash_unlock(page_addr,  page_addr + IFLASH_PAGE_SIZE - 1, 0, 0);
		if (ul_rc != FLASH_RC_OK) {
			printf("-F- Unlock error %lu\n\r", ul_rc);
			return 0;
		}
		ul_rc = flash_erase_sector(page_addr);
		if (ul_rc != FLASH_RC_OK) {
			printf("-F- Flash programming error %lu\n\r", ul_rc);
			return 0;
		}
		ul_rc = flash_write(page_addr, page_buffer, IFLASH_PAGE_SIZE, 0);
		if (ul_rc != FLASH_RC_OK) {
			printf("-F- Flash programming error %lu\n\r", ul_rc);
		return 0;
	}
	}else {
		ssid_length = page_buffer[75];
		pwd_length = page_buffer[76];
		for(i = 0; i < ssid_length; i++) {
			wlan_ssid[i] = page_buffer[11 + i];
		}
		for(i = 0; i < pwd_length; i++) {
			wlan_pwd[i] = page_buffer[11 + ssid_length + i] ;
		}
	}

	printf("Connecting to %s.\r\n", wlan_ssid);
	m2m_wifi_connect((char *)wlan_ssid, ssid_length, MAIN_WLAN_AUTH, (void *)wlan_pwd, M2M_WIFI_CH_ALL);
	//printf("Connecting to %s.\r\n", (char *)MAIN_WLAN_SSID);
	//m2m_wifi_connect((char *)MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID), MAIN_WLAN_AUTH, (void *)MAIN_WLAN_PSK, M2M_WIFI_CH_ALL);
}

static void wifi_handle_events(void)
{
	m2m_wifi_handle_events(NULL);
}

static void wifi_require_weather(char *city_name)
{
	memset(gau8ReceivedBuffer, 0, sizeof(gau8ReceivedBuffer));
	sprintf((char *)gau8ReceivedBuffer, "%s%s%s%s", MAIN_PREFIX_BUFFER, city_name, MAIN_APP_ID, MAIN_POST_BUFFER);
	send(tcp_client_socket, gau8ReceivedBuffer, strlen((char *)gau8ReceivedBuffer), 0);

	memset(gau8ReceivedBuffer, 0, MAIN_WIFI_M2M_BUFFER_SIZE);
	recv(tcp_client_socket, &gau8ReceivedBuffer[0], MAIN_WIFI_M2M_BUFFER_SIZE, 0);
}

static uint8_t parse_weather_icon(char* pcWeather)
{
	char *pcStartPtr;
	char *pcEndPtr;

	pcStartPtr = pcWeather;
	pcEndPtr = strstr(pcStartPtr, "cloud");
	if(pcEndPtr != NULL) {
		return 1;
	}

	pcStartPtr = pcWeather;
	pcEndPtr = strstr(pcStartPtr, "rain");
	if(pcEndPtr != NULL) {
		return 2;
	}

	pcStartPtr = pcWeather;
	pcEndPtr = strstr(pcStartPtr, "snow");
	if(pcEndPtr != NULL) {
		return 3;
	}

	return 0;
}


void wifi_recieve_packet(void)
{
	char *pcIndxPtr;
	char *pcEndPtr;

	if (!gbContinueReceive) {
		/* Get city name */
		pcIndxPtr = strstr(gcWeatherInfo, "name=");
		printf("City: ");
		if (NULL != pcIndxPtr) {
			pcIndxPtr = pcIndxPtr + strlen("name=") + 1;
			pcEndPtr = strstr(pcIndxPtr, "\">");
			if (NULL != pcEndPtr) {
				*pcEndPtr = 0;
			}
			pcCity = pcIndxPtr;
			printf("%s\r\n", pcIndxPtr);
		} else {
			printf("N/A\r\n");
			return;
		}

		/* Get temperature */
		pcIndxPtr = strstr(pcEndPtr + 1, "temperature value");
		printf("Temperature: ");
		if (NULL != pcIndxPtr) {
			pcIndxPtr = pcIndxPtr + strlen("temperature value") + 2;
			pcEndPtr = strstr(pcIndxPtr, "\" ");
			if (NULL != pcEndPtr) {
				*pcEndPtr = 0;
			}
			pcTemperature = pcIndxPtr;
			if(display_is_sha) {
				strcpy(Temperature_sha, pcTemperature);
			} else {
				strcpy(Temperature_seoul, pcTemperature);
			}
			printf("%s\r\n", pcIndxPtr);
		} else {
			printf("N/A\r\n");
			return;
		}

		/* Get weather condition */
		pcIndxPtr = strstr(pcEndPtr + 1, "weather number");
		if (NULL != pcIndxPtr) {
			printf("Weather Condition: ");
			pcIndxPtr = pcIndxPtr + strlen("weather number") + 14;
			pcEndPtr = strstr(pcIndxPtr, "\" ");
			if (NULL != pcEndPtr) {
				*pcEndPtr = 0;
			}
			pcWeather = pcIndxPtr;
			ucWeatherNum = parse_weather_icon(pcWeather);
			if(display_is_sha) {
				strcpy(Weather_sha, pcWeather);
				ucWeatherNum_sha = ucWeatherNum;
			} else {
				strcpy(Weather_seoul, pcWeather);
				ucWeatherNum_seoul = ucWeatherNum;
			}
			printf("%s\r\n", pcIndxPtr);
			gbContinueReceive = false;
			return;
		} else {
			gbContinueReceive = true;
		}
	} else {
		/* Get weather condition */
		pcIndxPtr = strstr(gcWeatherInfo, "weather number");
		printf("Weather Condition: ");
		if (NULL != pcIndxPtr) {
			pcIndxPtr = pcIndxPtr + strlen("weather number") + 14;
			pcEndPtr = strstr(pcIndxPtr, "\" ");
			if (NULL != pcEndPtr) {
				*pcEndPtr = 0;
			}
			pcWeather = pcIndxPtr;
			if(display_is_sha) {
				strcpy(Weather_sha, pcWeather);
			} else {
				strcpy(Weather_seoul, pcWeather);
			}
			printf("%s\r\n", pcIndxPtr);
			gbContinueReceive = false;
			gbTcpConnection = false;
			return;
		} else {
			gbContinueReceive = true;
			printf("N/A\r\n");
		}
	}

	memset(gau8ReceivedBuffer, 0, sizeof(gau8ReceivedBuffer));
	recv(tcp_client_socket, &gau8ReceivedBuffer[0], MAIN_WIFI_M2M_BUFFER_SIZE, 0);

}
/**
 * \brief Configure UART console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate =		CONF_UART_BAUDRATE,
		.charlength =	CONF_UART_CHAR_LENGTH,
		.paritytype =	CONF_UART_PARITY,
		.stopbits =		CONF_UART_STOP_BITS,
	};

	/* Configure UART console. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}
static void refresh_display()
{
	ili9488_set_foreground_color(COLOR_CONVERT(COLOR_WHITE));
	ili9488_draw_filled_rectangle(0, 0, ILI9488_LCD_WIDTH-1, ILI9488_LCD_HEIGHT-1);

	ili9488_set_foreground_color(COLOR_CONVERT(0x0078C0));
	ili9488_draw_filled_rectangle(0, 120, ILI9488_LCD_WIDTH-1, 360-1);

	if(display_is_sha) {
		ili9488_draw_pixmap(30, 180, 120, 120, gWeatherIcon[ucWeatherNum_sha]);
		ili9488_draw_pixmap(159, 120, 160, 60, gImage_shanghai);
		ili9488_set_foreground_color(COLOR_CONVERT(COLOR_WHITE));
		ili9488_draw_temperature(150, 220, (uint8_t *)Temperature_sha);
		ili9488_draw_string(60, 320, (uint8_t *)Weather_sha);
	} else {
		ili9488_draw_pixmap(30, 180, 120, 120, gWeatherIcon[ucWeatherNum_seoul]);
		ili9488_draw_pixmap(159, 120, 160, 60, gImage_seoul);
		ili9488_set_foreground_color(COLOR_CONVERT(COLOR_WHITE));
		ili9488_draw_temperature(150, 220, (uint8_t *)Temperature_seoul);
		ili9488_draw_string(60, 320, (uint8_t *)Weather_seoul);
	}

	ili9488_set_foreground_color(COLOR_CONVERT(COLOR_BLACK));
	ili9488_draw_string(10, 10, (uint8_t *)"openweathermap.org");
}

/**
 * \brief Interrupt handler for the RTT.
 *
 * Display the current time on the terminal.
 */
void RTT_Handler(void)
{
	uint32_t ul_status;

	/* Get RTT status */
	ul_status = rtt_get_status(RTT);

	/* Time has changed, refresh display */
	if ((ul_status & RTT_SR_RTTINC) == RTT_SR_RTTINC) {
		g_ul_sec_ticks++;
	}
}

/**
 * \brief RTT configuration function.
 *
 * Configure the RTT to generate a one second tick, which triggers the RTTINC
 * interrupt.
 */
void configure_rtt(void)
{
	/* Configure RTT for a 1 second tick interrupt */
	rtt_sel_source(RTT, false);

	rtt_init(RTT, 32768);

	/* Enable RTT interrupt */
	NVIC_DisableIRQ(RTT_IRQn);
	NVIC_ClearPendingIRQ(RTT_IRQn);
	NVIC_SetPriority(RTT_IRQn, 0);
	NVIC_EnableIRQ(RTT_IRQn);
	rtt_enable_interrupt(RTT, RTT_MR_RTTINCIEN);
}

/**
 * \brief Main application function.
 *
 * Initialize system, UART console, network then start weather client.
 *
 * \return Program return value.
 */
int main(void)
{
	struct sockaddr_in addr_in;

	/* Initialize the board. */
	sysclk_init();
	board_init();
	ioport_init();

	/* Initialize the UART console. */
	configure_console();
	printf(STRING_HEADER);

	/* Set direction and pullup on the given button IOPORT */
	ioport_set_pin_dir(GPIO_PUSH_BUTTON_1, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(GPIO_PUSH_BUTTON_1, IOPORT_MODE_PULLUP);

	/* Initialize display parameter */
	g_ili9488_display_opt.ul_width = ILI9488_LCD_WIDTH;
	g_ili9488_display_opt.ul_height = ILI9488_LCD_HEIGHT;
	g_ili9488_display_opt.foreground_color = COLOR_CONVERT(COLOR_WHITE);
	g_ili9488_display_opt.background_color = COLOR_CONVERT(COLOR_WHITE);

	/* Initialize LCD */
	ili9488_init(&g_ili9488_display_opt);
	ili9488_draw_filled_rectangle(0, 0, ILI9488_LCD_WIDTH-1, ILI9488_LCD_HEIGHT-1);
	ili9488_set_foreground_color(COLOR_CONVERT(0x0078C0));
	ili9488_draw_filled_rectangle(0, 0, ILI9488_LCD_WIDTH-1, 120-1);
	ili9488_draw_filled_rectangle(0, 360, ILI9488_LCD_WIDTH-1, 480-1);
	ili9488_draw_pixmap(80, 200, 156, 76, gImage_atmel_18bit);

	wifi_init();

	wifi_connect();

	ili9488_set_foreground_color(COLOR_CONVERT(COLOR_WHITE));
	ili9488_draw_filled_rectangle(0, 300, ILI9488_LCD_WIDTH-1, 315);
	ili9488_set_foreground_color(COLOR_CONVERT(COLOR_BLACK));
	ili9488_draw_string(10, 300, (uint8_t *)"Connecting......");

	while (1) {
		wifi_handle_events();

		if (gbConnectedWifi && !gbTcpConnection) {
			if (gbHostIpByName) {
				/* Open TCP client socket. */
				if (tcp_client_socket < 0) {
					if ((tcp_client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
						printf("main: failed to create TCP client socket error!\r\n");
						continue;
					}
				}

				/* Connect TCP client socket. */
				addr_in.sin_family = AF_INET;
				addr_in.sin_port = _htons(MAIN_SERVER_PORT);
				addr_in.sin_addr.s_addr = gu32HostIp;
				if (connect(tcp_client_socket, (struct sockaddr *)&addr_in, sizeof(struct sockaddr_in)) != SOCK_ERR_NO_ERROR) {
					printf("main: failed to connect socket error!\r\n");
					continue;
				}
				gbTcpConnection = true;
			}
		}

		if(gbFinishedGetWeather)
		{
			wifi_recieve_packet();
			refresh_display();
			gbFinishedGetWeather = false;
		}
		if((g_ul_sec_ticks == 60) || (gbRequireWeather == true)) {
			if(city_is_sha) {
				wifi_require_weather("Shanghai");
				city_is_sha = false;
				display_is_sha = true;
			} else {
				wifi_require_weather("seoul");
				city_is_sha = true;
				display_is_sha = false;
			}
			g_ul_sec_ticks = 0;
			gbRequireWeather = false;
		}
	}
	return 0;
}
