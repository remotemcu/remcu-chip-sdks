/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "lwip/opt.h"

#if LWIP_SOCKET
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#include "lwip/netif.h"
#include "lwip/sys.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/ip.h"
#include "lwip/sockets.h"
#include "netif/etharp.h"

#include "ethernetif.h"
#include "board.h"

#include "httpsrv.h"

//dm #include "certs_buff.h"
#include "mbedtls/certs.h"

#if FSL_FEATURE_SOC_TRNG_COUNT
#include "fsl_trng.h"
#elif FSL_FEATURE_SOC_RNG_COUNT
#include "fsl_rnga.h"
#endif

#include "fsl_device_registers.h"
#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define EXAMPLE_ENET ENET

/* IP address configuration. */
#define configIP_ADDR0 192
#define configIP_ADDR1 168
#define configIP_ADDR2 0
#define configIP_ADDR3 102

/* Netmask configuration. */
#define configNET_MASK0 255
#define configNET_MASK1 255
#define configNET_MASK2 255
#define configNET_MASK3 0

/* Gateway address configuration. */
#define configGW_ADDR0 192
#define configGW_ADDR1 168
#define configGW_ADDR2 0
#define configGW_ADDR3 100

#define configPHY_ADDRESS 1

#ifndef HTTPD_DEBUG
#define HTTPD_DEBUG LWIP_DBG_ON
#endif
#ifndef HTTPD_STACKSIZE
#define HTTPD_STACKSIZE DEFAULT_THREAD_STACKSIZE
#endif
#ifndef HTTPD_PRIORITY
#define HTTPD_PRIORITY DEFAULT_THREAD_PRIO
#endif
#ifndef DEBUG_WS
#define DEBUG_WS 0
#endif

#define CGI_DATA_LENGTH_MAX (96)

/*******************************************************************************
* Prototypes
******************************************************************************/

static void cgi_urldecode(char* url);
static int cgi_rtc_data(HTTPSRV_CGI_REQ_STRUCT* param);
static int cgi_example(HTTPSRV_CGI_REQ_STRUCT* param);
static int ssi_date_time(HTTPSRV_SSI_PARAM_STRUCT* param);
static bool cgi_get_varval(char *var_str, char *var_name, char *var_val, uint32_t length);

/*******************************************************************************
* Variables
******************************************************************************/
static struct netif fsl_netif0;
/* FS data.*/
extern const HTTPSRV_FS_DIR_ENTRY     httpsrv_fs_data[];

/*
 * Authentication users
 */
static const HTTPSRV_AUTH_USER_STRUCT users[] = {
    {"admin", "admin"},
    { NULL, NULL} /* Array terminator */
};

/*
 * Authentication information.
 */
static const HTTPSRV_AUTH_REALM_STRUCT auth_realms[] = {
    { "Please use uid:admin pass:admin to login", "/auth.html", HTTPSRV_AUTH_BASIC, users},
    { NULL, NULL, HTTPSRV_AUTH_INVALID, NULL} /* Array terminator */
};

char cgi_data[CGI_DATA_LENGTH_MAX+1];

const HTTPSRV_CGI_LINK_STRUCT cgi_lnk_tbl[] = {
    { "rtcdata", cgi_rtc_data },
    { "get", cgi_example},
    { "post", cgi_example},
    { 0, 0 }    // DO NOT REMOVE - last item - end of table
};

const HTTPSRV_SSI_LINK_STRUCT ssi_lnk_tbl[] = {
 { "date_time", ssi_date_time },
 { 0, 0 } 
};

/*******************************************************************************
 * Code
 ******************************************************************************/
static int cgi_rtc_data(HTTPSRV_CGI_REQ_STRUCT* param)
{
    #define BUFF_SIZE sizeof("00\n00\n00\n")
    HTTPSRV_CGI_RES_STRUCT response;
    uint32_t time;
    uint32_t min;
    uint32_t hour;
    uint32_t sec;
    
    char str[BUFF_SIZE];
    uint32_t length = 0;
    
    if (param->request_method != HTTPSRV_REQ_GET)
    {
        return(0);
    }

    time = sys_now();
    
    sec = time / 1000;
    min = sec / 60;
    hour = min / 60;
    min %= 60;
    sec %= 60;

    response.ses_handle = param->ses_handle;
    response.content_type = HTTPSRV_CONTENT_TYPE_PLAIN;
    response.status_code = HTTPSRV_CODE_OK;
    /* 
    ** When the keep-alive is used we have to calculate a correct content length
    ** so the receiver knows when to ACK the data and continue with a next request.
    ** Please see RFC2616 section 4.4 for further details.
    */
    
    /* Calculate content length while saving it to buffer */                                  
    length = snprintf(str, BUFF_SIZE, "%ld\n%ld\n%ld\n", hour, min, sec);          
    response.data = str;
    response.data_length = length;
    response.content_length = response.data_length;
    /* Send response */
    HTTPSRV_cgi_write(&response);
    return (response.content_length);
}

/* Example Common Gateway Interface callback. */
static int cgi_example(HTTPSRV_CGI_REQ_STRUCT* param)
{
    HTTPSRV_CGI_RES_STRUCT response = {0};

    response.ses_handle = param->ses_handle;
    response.status_code = HTTPSRV_CODE_OK;
   
    if (param->request_method == HTTPSRV_REQ_GET)
    {
        char *c;
        
        /* Replace '+' with spaces. */
        while ((c = strchr(cgi_data, '+')) != NULL)
        {
            *c = ' ';
        }
        response.content_type = HTTPSRV_CONTENT_TYPE_PLAIN;
        response.data = cgi_data;
        response.data_length = strlen(cgi_data);
        response.content_length = response.data_length;
        HTTPSRV_cgi_write(&response);
    }
    else if (param->request_method == HTTPSRV_REQ_POST)
    {
        uint32_t length = 0;
        uint32_t read;
        char     buffer[sizeof("post_input = ")+CGI_DATA_LENGTH_MAX] = {0};
        
        length = param->content_length;
        read = HTTPSRV_cgi_read(param->ses_handle, buffer, (length > sizeof(buffer)) ? sizeof(buffer) : length);

        if (read > 0)
        {
            cgi_get_varval(buffer, "post_input", cgi_data, sizeof(cgi_data));
            cgi_urldecode(cgi_data);
        }

        /* Write the response using chunked transmission coding. */
        response.content_type = HTTPSRV_CONTENT_TYPE_HTML;
        /* Set content length to -1 to indicate unknown content length. */
        response.content_length = -1;
        response.data = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">";
        response.data_length = strlen(response.data);
        HTTPSRV_cgi_write(&response);
        response.data = "<html><head><title>POST successfull!</title>";
        response.data_length = strlen(response.data);
        HTTPSRV_cgi_write(&response);
        response.data = "<meta http-equiv=\"refresh\" content=\"0; url=cgi.html\"></head><body></body></html>";
        response.data_length = strlen(response.data);
        HTTPSRV_cgi_write(&response);
        response.data_length = 0;
        HTTPSRV_cgi_write(&response);
    }

    return (response.content_length);
}

static bool cgi_get_varval(char *src, char *var_name, char *dst, uint32_t length)
{
    char *name;
    bool result;
    uint32_t index;
    uint32_t n_length;

    result = false;
    dst[0] = 0;
    name = src;

    n_length = strlen(var_name);

    while ((name = strstr(name, var_name)) != 0)
    {
        if (name[n_length] == '=')
        {
            name += n_length + 1;

            index = strcspn(name, "&");
            if (index >= length)
            {
                index = length-1;
            }
            strncpy(dst, name, index);
            dst[index] = '\0';
            result = true;
            break;
        }
        else
        {
            name = strchr(name, '&');
        }
    }

    return(result);
}

/* Example Server Side Include callback. */
static int ssi_date_time(HTTPSRV_SSI_PARAM_STRUCT* param)
{
    if (strcmp(param->com_param, "time") == 0)
    {
        HTTPSRV_ssi_write(param->ses_handle, __TIME__, strlen(__TIME__));
    }
    else if (strcmp(param->com_param, "date") == 0)
    {
        HTTPSRV_ssi_write(param->ses_handle, __DATE__, strlen(__DATE__));
    }
    return(0);
}

/* Decode URL encoded string in place. */
static void cgi_urldecode(char* url)
{
    char* src = url;
    char* dst = url;

    while(*src != '\0')
    {
        if ((*src == '%') && (isxdigit((int)*(src+1))) && (isxdigit((int)*(src+2))))
        {
            *src = *(src+1);
            *(src+1) = *(src+2);
            *(src+2) = '\0';
            *dst++ = strtol(src, NULL, 16);
            src += 3;
        }
        else
        {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
}

#if HTTPSRV_CFG_WEBSOCKET_ENABLED
/*
 * Echo plugin code - simple plugin which echoes any message it receives back to
 * client.
 */
uint32_t ws_echo_connect(void* param, WS_USER_CONTEXT_STRUCT context)
{
#if DEBUG_WS
    PRINTF("WebSocket echo client connected.\r\n");
#endif
    return(0);
}

uint32_t ws_echo_disconnect(void* param, WS_USER_CONTEXT_STRUCT context)
{
#if DEBUG_WS
    PRINTF("WebSocket echo client disconnected.\r\n");
#endif
    return(0);
}

uint32_t ws_echo_message(void* param, WS_USER_CONTEXT_STRUCT context)
{
    WS_send(&context); /* Send back what was received.*/
#if DEBUG_WS 
    if (context.data.type == WS_DATA_TEXT)
    {
       /* Print received text message to console. */
       context.data.data_ptr[context.data.length] = 0;
       PRINTF("WebSocket message received:\r\n%s\r\n", context.data.data_ptr); 
    }
    else
    {
       /* Inform user about binary message. */
       PRINTF("WebSocket binary data with length of %d bytes received.", context.data.length);
    }
#endif
    
    return(0);
}

uint32_t ws_echo_error(void* param, WS_USER_CONTEXT_STRUCT context)
{
#if DEBUG_WS
    PRINTF("WebSocket error: 0x%X.\r\n", context.error);
#endif
    return(0);
}

WS_PLUGIN_STRUCT ws_tbl[] =
{
    {"/echo",     
        ws_echo_connect,
        ws_echo_message,
        ws_echo_error,
        ws_echo_disconnect,
        NULL},
    {0, 0, 0, 0 ,0, 0}
};
#endif /* HTTPSRV_CFG_WEBSOCKET_ENABLED */

#if HTTPSRV_CFG_MBEDTLS_ENABLE
static HTTPSRV_TLS_PARAM_STRUCT tls_params;
#endif

/*!
 * @brief Initializes lwIP stack.
 */
static void stack_init(void)
{
    ip4_addr_t fsl_netif0_ipaddr, fsl_netif0_netmask, fsl_netif0_gw;

#if FSL_FEATURE_SOC_LTC_COUNT
    /* Initialize LTC driver.
     * This enables clocking and resets the module to a known state. */
    LTC_Init(LTC0);
#endif
    { /* Init RNG module.*/
#if defined(FSL_FEATURE_SOC_TRNG_COUNT) && (FSL_FEATURE_SOC_TRNG_COUNT > 0)
        trng_config_t trngConfig;

        TRNG_GetDefaultConfig(&trngConfig);
        /* Set sample mode of the TRNG ring oscillator to Von Neumann, for better random data.*/
        trngConfig.sampleMode = kTRNG_SampleModeVonNeumann;
        /* Initialize TRNG */
        TRNG_Init(TRNG0, &trngConfig);
#elif defined(FSL_FEATURE_SOC_RNG_COUNT) && (FSL_FEATURE_SOC_RNG_COUNT > 0)
        RNGA_Init(RNG);
        RNGA_Seed(RNG, SIM->UIDL);
#endif
    }

    tcpip_init(NULL, NULL);

    IP4_ADDR(&fsl_netif0_ipaddr, configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP_ADDR3);
    IP4_ADDR(&fsl_netif0_netmask, configNET_MASK0, configNET_MASK1, configNET_MASK2, configNET_MASK3);
    IP4_ADDR(&fsl_netif0_gw, configGW_ADDR0, configGW_ADDR1, configGW_ADDR2, configGW_ADDR3);

    netif_add(&fsl_netif0, &fsl_netif0_ipaddr, &fsl_netif0_netmask, &fsl_netif0_gw, NULL, ethernetif_init, tcpip_input);
    netif_set_default(&fsl_netif0);
    netif_set_up(&fsl_netif0);

    LWIP_PLATFORM_DIAG(("\r\n************************************************"));
    LWIP_PLATFORM_DIAG(("mbedTLS HTTPS Server example"));
    LWIP_PLATFORM_DIAG(("************************************************"));
    LWIP_PLATFORM_DIAG((" IPv4 Address     : %u.%u.%u.%u", ((u8_t *)&fsl_netif0_ipaddr)[0],
                        ((u8_t *)&fsl_netif0_ipaddr)[1], ((u8_t *)&fsl_netif0_ipaddr)[2],
                        ((u8_t *)&fsl_netif0_ipaddr)[3]));
    LWIP_PLATFORM_DIAG((" IPv4 Subnet mask : %u.%u.%u.%u", ((u8_t *)&fsl_netif0_netmask)[0],
                        ((u8_t *)&fsl_netif0_netmask)[1], ((u8_t *)&fsl_netif0_netmask)[2],
                        ((u8_t *)&fsl_netif0_netmask)[3]));
    LWIP_PLATFORM_DIAG((" IPv4 Gateway     : %u.%u.%u.%u", ((u8_t *)&fsl_netif0_gw)[0], ((u8_t *)&fsl_netif0_gw)[1],
                        ((u8_t *)&fsl_netif0_gw)[2], ((u8_t *)&fsl_netif0_gw)[3]));
    LWIP_PLATFORM_DIAG(("************************************************"));
}

/*!
 * @brief Initializes server.
 */
static void http_server_socket_init(void)
{
    HTTPSRV_PARAM_STRUCT params;
    uint32_t httpsrv_handle;

    /* Init Fs*/
    HTTPSRV_FS_init(httpsrv_fs_data);

    /* Init HTTPSRV parameters.*/
    memset(&params, 0, sizeof(params));
    params.root_dir = "";
    params.index_page = "/index.html";
    params.auth_table = auth_realms;
    params.cgi_lnk_tbl = cgi_lnk_tbl;
    params.ssi_lnk_tbl = ssi_lnk_tbl;
#if HTTPSRV_CFG_WEBSOCKET_ENABLED
    params.ws_tbl = ws_tbl;
#endif
#if HTTPSRV_CFG_MBEDTLS_ENABLE
    tls_params.certificate_buffer = (const unsigned char*)mbedtls_test_srv_crt;
    tls_params.certificate_buffer_size = mbedtls_test_srv_crt_len;
    tls_params.private_key_buffer = (const unsigned char*)mbedtls_test_srv_key;
    tls_params.private_key_buffer_size = mbedtls_test_srv_key_len;

    params.tls_param = &tls_params;
#endif       
    /* Init HTTP Server.*/
    httpsrv_handle  = HTTPSRV_init(&params);
    if(httpsrv_handle == 0)
    {
        LWIP_PLATFORM_DIAG(("HTTPSRV_init() is Failed"));
    }
}

/*!
 * @brief The main function containing server thread.
 */
static void main_thread(void *arg)
{
    LWIP_UNUSED_ARG(arg);

    stack_init();
    http_server_socket_init();

    vTaskDelete(NULL);
}

/*!
 * @brief Main function.
 */
int main(void)
{
    SYSMPU_Type *base = SYSMPU;
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    /* Disable SYSMPU. */
    base->CESR &= ~SYSMPU_CESR_VLD_MASK;

    /* create server thread in RTOS */
    if(sys_thread_new("main", main_thread, NULL, HTTPD_STACKSIZE, HTTPD_PRIORITY) == NULL)
        LWIP_ASSERT("main(): Task creation failed.", 0);

    /* run RTOS */
    vTaskStartScheduler();

    /* should not reach this statement */
    for (;;)
        ;
}

#endif /* LWIP_SOCKET */

