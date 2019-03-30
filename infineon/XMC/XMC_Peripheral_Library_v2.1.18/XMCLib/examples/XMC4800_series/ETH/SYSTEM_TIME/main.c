/*
 * Copyright (C) 2015-2017 Infineon Technologies AG. All rights reserved.
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
 * @date 13 April,2017
 * @version 1.0.0
 *
 * @brief ETH HTTP server demo example using the netconn interface
 *
 * History <br>
 *
 * Version 1.0.0 
 * - Initial
 *
 */

#include <xmc_gpio.h>
#include <xmc_eth_mac.h>

#include <lwip/sys.h>
#include <lwip/netif.h>
#include <lwip/init.h>
#include <lwip/timeouts.h>
#include <netif/etharp.h>
#include <ethernetif.h>

#if LWIP_DHCP == 1
#include <lwip/dhcp.h>
#endif

#define LED1 P5_9
#define LED2 P5_8

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

#define LED_TMR_INTERVAL 1000

extern struct netif xnetif;

extern XMC_ETH_MAC_t eth_mac;

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
  netif_add(&xnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);

  /*  Registers the default network interface.*/
  netif_set_default(&xnetif);

  /* If callback enabled */
#if LWIP_NETIF_STATUS_CALLBACK == 1
  /* Initialize interface status change callback */
  netif_set_status_callback(&xnetif, ETH_NETIF_STATUS_CB_FUNCTION);
#endif
}

static void led_timer(void *arg)
{
  XMC_UNUSED_ARG(arg);

  XMC_GPIO_ToggleOutput(LED1);

  sys_timeout(LED_TMR_INTERVAL, led_timer, NULL);
}

void ETH0_0_UserIRQHandler(void)
{
  if (XMC_ETH_MAC_GetEventStatus(&eth_mac) & XMC_ETH_MAC_EVENT_TIMESTAMP)
  {
    XMC_GPIO_SetOutputHigh(LED2);

    XMC_ETH_MAC_GetPTPStatus(&eth_mac);
  }
}

const XMC_GPIO_CONFIG_t gpio_config = 
{
  .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
  .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW
};

int main(void)
{  
  XMC_GPIO_Init(LED1, &gpio_config);
  XMC_GPIO_Init(LED2, &gpio_config);

  SysTick_Config(SystemCoreClock / 1000);

  LWIP_Init();

  sys_timeout(LED_TMR_INTERVAL, led_timer, NULL);

  XMC_ETH_MAC_TIME_t alarm = {.seconds = 10, .nanoseconds = 0};
  XMC_ETH_MAC_SetPTPAlarm(&eth_mac, &alarm);

  XMC_ETH_MAC_InitPTP(&eth_mac, XMC_ETH_MAC_TIMESTAMP_CONFIG_FINE_UPDATE | XMC_ETH_MAC_TIMESTAMP_CONFIG_ENABLE_TS_INTERRUPT);
  XMC_ETH_MAC_EnableEvent(&eth_mac, XMC_ETH_MAC_EVENT_TIMESTAMP);

  while(1)
  {
    sys_check_timeouts();
  }
}
