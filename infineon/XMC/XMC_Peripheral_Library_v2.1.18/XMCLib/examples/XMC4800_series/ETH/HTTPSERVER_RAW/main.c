/*
 * Copyright (C) 2015-2016 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

/**
 * @file
 * @date 10 November,2017
 * @version 1.3.0
 *
 * @brief ETH HTTP server demo example using the netconn interface
 *
 * History <br>
 *
 * Version 1.0.0 
 * - Initial
 *
 * Version 1.0.2
 * - Stability and speed improvements
 *
 * Version 1.1.0
 * - lwIP 2.0.2
 *
 * Version 1.2.0
 * - Changed the way the interface features are assigned
 * 
 * Version 1.3.0
 * - lwIP 2.0.3
 * - Reworked example structure
 */

#include <xmc_gpio.h>

#include <lwip/netif.h>
#include <lwip/init.h>
#include <lwip/timeouts.h>
#include <netif/etharp.h>

#include "ethernetif.h"
#include "httpserver_raw/httpd.h"

#if LWIP_DHCP == 1
#include <lwip/dhcp.h>
#endif

#define LED1 P5_9
#define LED2 P5_8

#define BUTTON1 P15_13
#define BUTTON2 P15_12

/*Static IP ADDRESS*/
#define IP_ADDR0   192
#define IP_ADDR1   168
#define IP_ADDR2   0
#define IP_ADDR3   10

/*NETMASK*/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/*Gateway Address*/
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   0
#define GW_ADDR3   1

/* MAC ADDRESS*/
#define MAC_ADDR0   0x00
#define MAC_ADDR1   0x00
#define MAC_ADDR2   0x45
#define MAC_ADDR3   0x19
#define MAC_ADDR4   0x03
#define MAC_ADDR5   0x00

#define BUTTONS_TMR_INTERVAL 100

#define XMC_ETH_MAC_NUM_RX_BUF (4)
#define XMC_ETH_MAC_NUM_TX_BUF (8)

#if defined(__ICCARM__)
#pragma data_alignment=4
static XMC_ETH_MAC_DMA_DESC_t rx_desc[XMC_ETH_MAC_NUM_RX_BUF] @ ".dram";
#pragma data_alignment=4
static XMC_ETH_MAC_DMA_DESC_t tx_desc[XMC_ETH_MAC_NUM_TX_BUF] @ ".dram";
#pragma data_alignment=4
static uint8_t rx_buf[XMC_ETH_MAC_NUM_RX_BUF][XMC_ETH_MAC_BUF_SIZE] @ ".dram";
#pragma data_alignment=4
static uint8_t tx_buf[XMC_ETH_MAC_NUM_TX_BUF][XMC_ETH_MAC_BUF_SIZE] @ ".dram";
#elif defined(__CC_ARM) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
static __ALIGNED(4) XMC_ETH_MAC_DMA_DESC_t rx_desc[XMC_ETH_MAC_NUM_RX_BUF] __attribute__((section ("RW_IRAM1")));
static __ALIGNED(4) XMC_ETH_MAC_DMA_DESC_t tx_desc[XMC_ETH_MAC_NUM_TX_BUF] __attribute__((section ("RW_IRAM1")));
static __ALIGNED(4) uint8_t rx_buf[XMC_ETH_MAC_NUM_RX_BUF][XMC_ETH_MAC_BUF_SIZE] __attribute__((section ("RW_IRAM1")));
static __ALIGNED(4) uint8_t tx_buf[XMC_ETH_MAC_NUM_TX_BUF][XMC_ETH_MAC_BUF_SIZE] __attribute__((section ("RW_IRAM1")));
#elif defined(__GNUC__)
static __ALIGNED(4) XMC_ETH_MAC_DMA_DESC_t rx_desc[XMC_ETH_MAC_NUM_RX_BUF] __attribute__((section ("ETH_RAM")));
static __ALIGNED(4) XMC_ETH_MAC_DMA_DESC_t tx_desc[XMC_ETH_MAC_NUM_TX_BUF] __attribute__((section ("ETH_RAM")));
static __ALIGNED(4) uint8_t rx_buf[XMC_ETH_MAC_NUM_RX_BUF][XMC_ETH_MAC_BUF_SIZE] __attribute__((section ("ETH_RAM")));
static __ALIGNED(4) uint8_t tx_buf[XMC_ETH_MAC_NUM_TX_BUF][XMC_ETH_MAC_BUF_SIZE] __attribute__((section ("ETH_RAM")));
#endif

static ETHIF_t ethif =
{
  .phy_addr = 0,
  .mac =
  {
    .regs = ETH0,
    .rx_desc = rx_desc,
    .tx_desc = tx_desc,
    .rx_buf = &rx_buf[0][0],
    .tx_buf = &tx_buf[0][0],
    .num_rx_buf = XMC_ETH_MAC_NUM_RX_BUF,
    .num_tx_buf = XMC_ETH_MAC_NUM_TX_BUF
  },
  .phy =
  {
    .interface = XMC_ETH_LINK_INTERFACE_RMII,
    .enable_auto_negotiate = true,
  }
};

static struct netif xnetif = 
{
  /* set MAC hardware address length */
  .hwaddr_len = (u8_t)ETHARP_HWADDR_LEN,

  /* set MAC hardware address */
  .hwaddr =  {(u8_t)MAC_ADDR0, (u8_t)MAC_ADDR1,
              (u8_t)MAC_ADDR2, (u8_t)MAC_ADDR3,
              (u8_t)MAC_ADDR4, (u8_t)MAC_ADDR5},

  /* maximum transfer unit */
  .mtu = 1500U,
};

int8_t bx = 0;
static void buttons_timer(void *arg)
{
  XMC_UNUSED_ARG(arg);

  if (XMC_GPIO_GetInput(BUTTON1) != 0)
  {
    bx++;
  }

  if (XMC_GPIO_GetInput(BUTTON2) != 0)
  {
    bx--;
  }

  sys_timeout(BUTTONS_TMR_INTERVAL, buttons_timer, NULL);
}

static void LWIP_Init(void)
{
  ip_addr_t ipaddr;
  ip_addr_t netmask;
  ip_addr_t gw;

#if LWIP_DHCP == 0
  IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
  IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1 , NETMASK_ADDR2, NETMASK_ADDR3);
  IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
#else
  ipaddr.addr = 0;
  netmask.addr = 0;
  gw.addr = 0;
#endif

  lwip_init();

  /* - netif_add(struct netif *netif, struct ip_addr *ipaddr,
  struct ip_addr *netmask, struct ip_addr *gw,
  void *state, err_t (* init)(struct netif *netif),
  err_t (* input)(struct pbuf *p, struct netif *netif))

  Adds your network interface to the netif_list. Allocate a struct
  netif and pass a pointer to this structure as the first argument.
  Give pointers to cleared ip_addr structures when using DHCP,
  or fill them with sane numbers otherwise. The state pointer may be NULL.

  The init function pointer must point to a initialization function for
  your ethernet netif interface. The following code illustrates it's use.*/
  netif_add(&xnetif, &ipaddr, &netmask, &gw, &ethif, &ethernetif_init, &ethernet_input);
}

/* Initialisation of functions to be used with CGi*/
//  CGI handler to switch LED status
const char *ledcontrol_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
  if(strcmp(pcValue[0], "led1") == 0)
  {
    XMC_GPIO_ToggleOutput(LED1);
  }
  else {
    XMC_GPIO_ToggleOutput(LED2);
  }
  return "/cgi.htm";
}

const char *data_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
  return "/data.ssi";
}

tCGI led_handler_struct[] =
{
  {
    .pcCGIName = "/ledcontrol.cgi",
    .pfnCGIHandler = ledcontrol_handler
  },
  {
   .pcCGIName = "/data.cgi",
   .pfnCGIHandler = data_handler
  }
};

int cgi_init(void)
{
  http_set_cgi_handlers(led_handler_struct, 2);

  return 0;
}

/**
 * Initialize SSI handlers
 */
const char *TAGS[]={"bx"};

static uint16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen)
{
  return (sprintf(pcInsert, "%d", bx));
}

void ssi_init(void)
{
  http_set_ssi_handler(ssi_handler, (char const **)TAGS, 1);
}

int main(void)
{
  XMC_GPIO_CONFIG_t config;
  
  config.mode = XMC_GPIO_MODE_INPUT_TRISTATE;

  XMC_GPIO_Init(BUTTON1, &config);
  XMC_GPIO_Init(BUTTON2, &config);
  
  config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
  
  XMC_GPIO_Init(LED1, &config);
  XMC_GPIO_Init(LED2, &config);

  SysTick_Config(SystemCoreClock / 1000);

  LWIP_Init();
  httpd_init();
  cgi_init();
  ssi_init();

  sys_timeout(BUTTONS_TMR_INTERVAL, buttons_timer, NULL);

  while(1)
  {
    sys_check_timeouts();
  }
}

void ETH0_0_IRQHandler(void)
{
  XMC_ETH_MAC_ClearEventStatus(&ethif.mac, XMC_ETH_MAC_EVENT_RECEIVE);

  ethernetif_input(&xnetif);
}
