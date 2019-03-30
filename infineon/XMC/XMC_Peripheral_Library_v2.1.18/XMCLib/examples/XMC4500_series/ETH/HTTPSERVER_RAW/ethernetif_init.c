#include <xmc_gpio.h>
#include <xmc_eth_mac.h>
#include <xmc_eth_phy.h>

#include "ethernetif.h"

#define RXD1     P2_3
#define RXD0     P2_2
#define RXER     P2_4
#define CLK_RMII P15_8
#define TX_EN    P2_5
#define TXD1     P2_9
#define TXD0     P2_8
#define CRS_DV   P15_9
#define MDIO     P2_0
#define MDC      P2_7

/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
void low_level_init(struct netif *netif)
{
  XMC_ETH_MAC_PORT_CTRL_t port_control;
  XMC_GPIO_CONFIG_t gpio_config;

  ETHIF_t *ethif = netif->state;
  XMC_ETH_MAC_t *mac = &ethif->mac;
  XMC_ETH_PHY_CONFIG_t *phy_config = &ethif->phy;

  XMC_ETH_MAC_Enable(mac);
  XMC_ETH_MAC_SetManagmentClockDivider(mac);
 
  /* Do whatever else is needed to initialize interface. */
  gpio_config.mode = XMC_GPIO_MODE_INPUT_TRISTATE;
  XMC_GPIO_Init(RXD0, &gpio_config);
  XMC_GPIO_Init(RXD1, &gpio_config);
  XMC_GPIO_Init(CLK_RMII, &gpio_config);
  XMC_GPIO_Init(CRS_DV, &gpio_config);
  XMC_GPIO_Init(RXER, &gpio_config);
  XMC_GPIO_Init(MDIO, &gpio_config);

  port_control.mode = XMC_ETH_MAC_PORT_CTRL_MODE_RMII;
  port_control.rxd0 = XMC_ETH_MAC_PORT_CTRL_RXD0_P2_2;
  port_control.rxd1 = XMC_ETH_MAC_PORT_CTRL_RXD1_P2_3;
  port_control.clk_rmii = XMC_ETH_MAC_PORT_CTRL_CLK_RMII_P15_8;
  port_control.crs_dv = XMC_ETH_MAC_PORT_CTRL_CRS_DV_P15_9;
  port_control.rxer = XMC_ETH_MAC_PORT_CTRL_RXER_P2_4;
  port_control.mdio = XMC_ETH_MAC_PORT_CTRL_MDIO_P2_0;
  XMC_ETH_MAC_SetPortControl(mac, port_control);

  XMC_GPIO_SetHardwareControl(MDIO, XMC_GPIO_HWCTRL_PERIPHERAL1);

  gpio_config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  gpio_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_MEDIUM_EDGE;
  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P2_7_AF_ETH0_MDC);
  XMC_GPIO_Init(MDC, &gpio_config);

  int32_t status;
  if((status = XMC_ETH_PHY_Init(mac, ethif->phy_addr, phy_config)) != XMC_ETH_PHY_STATUS_OK)
  {
    ethernetif_error((ETHIF_ERROR_t)status);
  }

  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL |P2_8_AF_ETH0_TXD0);
  XMC_GPIO_Init(TXD0, &gpio_config);

  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P2_9_AF_ETH0_TXD1);
  XMC_GPIO_Init(TXD1, &gpio_config);

  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P2_5_AF_ETH0_TX_EN);
  XMC_GPIO_Init(TX_EN, &gpio_config);

  XMC_ETH_MAC_InitEx(mac);
  XMC_ETH_MAC_DisableJumboFrame(mac);
  XMC_ETH_MAC_SetAddressEx(mac, netif->hwaddr);
}
