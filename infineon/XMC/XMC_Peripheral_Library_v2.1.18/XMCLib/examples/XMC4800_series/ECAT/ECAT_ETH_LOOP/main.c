/*
 * Copyright (C) 2014 Infineon Technologies AG. All rights reserved.
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
 * @date 9 November,2015
 * @version 1.0.0
 *
 * @brief Ethernet - EtherCAT loop
 *
 * History
 *
 * Version 1.0.0 
 * - Initial
 *
 * Version 1.0.2
 * - Update to latest XMClib
 */

#include "xmc_scu.h"
#include "xmc_gpio.h"
#include "xmc_eth_mac.h"
#include "xmc_eth_phy.h"
#include "xmc_ecat.h"

#define ETH_PHY_ADDR 0
#define ECAT_P0_PHY_ADDR 0
#define ECAT_P1_PHY_ADDR 1

#define ETH_RXD1     P2_3
#define ETH_RXD0     P2_2
#define ETH_RXER     P2_4
#define ETH_CLK_RMII P15_8
#define ETH_TX_EN    P2_5
#define ETH_TXD1     P2_9
#define ETH_TXD0     P2_8
#define ETH_CRS_DV   P15_9
#define ETH_MDIO     P2_0
#define ETH_MDC      P2_7

#define ECAT_MDO			  P0_12
#define ECAT_MCLK			  P3_3
#define ECAT_CLK25			  P6_0
#define ECAT_PHY_RESET		  P0_0
#define ECAT_LED_RUN		  P0_8
#define ECAT_LED_ERR		  P0_7

#define ECAT_LED8			  P3_11
#define ECAT_LED7			  P5_3
#define ECAT_LED6			  P3_13
#define ECAT_LED5			  P1_12
#define ECAT_LED4			  P0_15
#define ECAT_LED3			  P3_14
#define ECAT_LED2			  P0_14
#define ECAT_LED1			  P1_14

#define ECAT_P0_LINK_STATUS   P1_15
#define ECAT_P0_LED_LINK_ACT  P6_3
#define ECAT_P0_RXD3		  P5_7
#define ECAT_P0_RXD2		  P5_2
#define ECAT_P0_RXD1		  P5_1
#define ECAT_P0_RXD0		  P5_0
#define ECAT_P0_RX_DV		  P5_6
#define ECAT_P0_RX_CLK		  P5_4
#define ECAT_P0_RX_ERR		  P2_6
#define ECAT_P0_TXD3		  P6_6
#define ECAT_P0_TXD2		  P6_5
#define ECAT_P0_TXD1		  P6_4
#define ECAT_P0_TXD0		  P6_2
#define ECAT_P0_TX_EN		  P6_1
#define ECAT_P0_TX_CLK		  P5_5

#define ECAT_P1_LINK_STATUS   P3_4
#define ECAT_P1_LED_LINK_ACT  P3_12
#define ECAT_P1_RXD3		  P0_4
#define ECAT_P1_RXD2		  P0_5
#define ECAT_P1_RXD1		  P0_6
#define ECAT_P1_RXD0		  P0_11
#define ECAT_P1_RX_DV		  P0_9
#define ECAT_P1_RX_CLK		  P0_1
#define ECAT_P1_RX_ERR		  P15_2
#define ECAT_P1_TXD3		  P0_3
#define ECAT_P1_TXD2		  P0_2
#define ECAT_P1_TXD1		  P3_2
#define ECAT_P1_TXD0		  P3_1
#define ECAT_P1_TX_EN		  P3_0
#define ECAT_P1_TX_CLK		  P0_10


/* MAC ADDRESS*/
#define MAC_ADDR0   0x00
#define MAC_ADDR1   0x00
#define MAC_ADDR2   0x45
#define MAC_ADDR3   0x19
#define MAC_ADDR4   0x03
#define MAC_ADDR5   0x00
#define MAC_ADDR    ((uint64_t)MAC_ADDR0 | \
                     ((uint64_t)MAC_ADDR1 << 8) | \
                     ((uint64_t)MAC_ADDR2 << 16) | \
                     ((uint64_t)MAC_ADDR3 << 24) | \
                     ((uint64_t)MAC_ADDR4 << 32) | \
                     ((uint64_t)MAC_ADDR5 << 40))

#define XMC_ETH_MAC_NUM_RX_BUF (4)
#define XMC_ETH_MAC_NUM_TX_BUF (4)

#if defined(__ICCARM__)
#pragma data_alignment=4
static XMC_ETH_MAC_DMA_DESC_t rx_desc[XMC_ETH_MAC_NUM_RX_BUF] @ ".dram";
#pragma data_alignment=4
static XMC_ETH_MAC_DMA_DESC_t tx_desc[XMC_ETH_MAC_NUM_TX_BUF] @ ".dram";
#pragma data_alignment=4
static uint8_t rx_buf[XMC_ETH_MAC_NUM_RX_BUF][XMC_ETH_MAC_BUF_SIZE] @ ".dram";
#pragma data_alignment=4
static uint8_t tx_buf[XMC_ETH_MAC_NUM_TX_BUF][XMC_ETH_MAC_BUF_SIZE] @ ".dram";
#endif

#if defined(__CC_ARM)
static __attribute__((aligned(4))) XMC_ETH_MAC_DMA_DESC_t rx_desc[XMC_ETH_MAC_NUM_RX_BUF] __attribute__((section ("RW_IRAM1")));
static __attribute__((aligned(4))) XMC_ETH_MAC_DMA_DESC_t tx_desc[XMC_ETH_MAC_NUM_TX_BUF] __attribute__((section ("RW_IRAM1")));
static __attribute__((aligned(4))) uint8_t rx_buf[XMC_ETH_MAC_NUM_RX_BUF][XMC_ETH_MAC_BUF_SIZE] __attribute__((section ("RW_IRAM1")));
static __attribute__((aligned(4))) uint8_t tx_buf[XMC_ETH_MAC_NUM_TX_BUF][XMC_ETH_MAC_BUF_SIZE] __attribute__((section ("RW_IRAM1")));
#endif

#if defined(__GNUC__)
static __attribute__((aligned(4))) XMC_ETH_MAC_DMA_DESC_t rx_desc[XMC_ETH_MAC_NUM_RX_BUF] __attribute__((section ("ETH_RAM")));
static __attribute__((aligned(4))) XMC_ETH_MAC_DMA_DESC_t tx_desc[XMC_ETH_MAC_NUM_TX_BUF] __attribute__((section ("ETH_RAM")));
static __attribute__((aligned(4))) uint8_t rx_buf[XMC_ETH_MAC_NUM_RX_BUF][XMC_ETH_MAC_BUF_SIZE] __attribute__((section ("ETH_RAM")));
static __attribute__((aligned(4))) uint8_t tx_buf[XMC_ETH_MAC_NUM_TX_BUF][XMC_ETH_MAC_BUF_SIZE] __attribute__((section ("ETH_RAM")));
#endif

static XMC_ETH_PHY_CONFIG_t eth_phy_config =
{
  .interface = XMC_ETH_LINK_INTERFACE_RMII,
  .enable_auto_negotiate = true
};

static XMC_ETH_MAC_t eth_mac =
{
  .regs = ETH0,
  .address = MAC_ADDR,
  .rx_desc = rx_desc,
  .tx_desc = tx_desc,
  .rx_buf = &rx_buf[0][0],
  .tx_buf = &tx_buf[0][0],
  .num_rx_buf = XMC_ETH_MAC_NUM_RX_BUF,
  .num_tx_buf = XMC_ETH_MAC_NUM_TX_BUF
};

static __attribute__((aligned(4))) uint8_t buffer[XMC_ETH_MAC_BUF_SIZE];

static __attribute__((aligned(4))) uint8_t brd_frame[60] =
{
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x14, /* ........ */
  0x4f, 0x23, 0x98, 0xcf, 0x88, 0xa4, 0x0e, 0x10, /* O#...... */
  0x07, 0x02, 0x00, 0x00, 0x30, 0x01, 0x02, 0x00, /* ....0... */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
  0x00, 0x00, 0x00, 0x00                          /* .... */
};

/* Clock configuration */
/* fPLL = 288MHz */
/* fPLLUSB = 200MHz */
/* fSYS = 144MHz */
/* fECAT = 100MHz */
const XMC_SCU_CLOCK_CONFIG_t clock_config =
{
  .syspll_config.p_div = 2,
  .syspll_config.n_div = 48,
  .syspll_config.k_div = 1,
  .syspll_config.mode = XMC_SCU_CLOCK_SYSPLL_MODE_NORMAL,
  .syspll_config.clksrc = XMC_SCU_CLOCK_SYSPLLCLKSRC_OSCHP,
  .enable_oschp = true,
  .calibration_mode = XMC_SCU_CLOCK_FOFI_CALIBRATION_MODE_FACTORY,
  .fsys_clksrc = XMC_SCU_CLOCK_SYSCLKSRC_PLL,
  .fsys_clkdiv = 2,
  .fcpu_clkdiv = 1,
  .fccu_clkdiv = 1,
  .fperipheral_clkdiv = 1
};

void SystemCoreClockSetup(void)
{
  /* Setup settings for USB clock */
  XMC_SCU_CLOCK_Init(&clock_config);
  
  XMC_SCU_CLOCK_EnableUsbPll();
  XMC_SCU_CLOCK_StartUsbPll(3, 100);
  XMC_SCU_CLOCK_SetECATClockDivider(2);
  XMC_SCU_CLOCK_SetECATClockSource(XMC_SCU_CLOCK_ECATCLKSRC_USBPLL);

  SystemCoreClockUpdate();
}

void ETH_MAC_Init(void);
void ECAT_Init(void);

volatile bool g_received_frame = false;

int main(void)
{
  XMC_GPIO_CONFIG_t config;
  config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
  config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE;

  XMC_GPIO_Init(ECAT_LED1, &config);
  XMC_GPIO_Init(ECAT_LED2, &config);
  XMC_GPIO_Init(ECAT_LED3, &config);
  XMC_GPIO_Init(ECAT_LED4, &config);
  XMC_GPIO_Init(ECAT_LED5, &config);
  XMC_GPIO_Init(ECAT_LED6, &config);
  XMC_GPIO_Init(ECAT_LED7, &config);
  XMC_GPIO_Init(ECAT_LED8, &config);

  ECAT_Init();
  ETH_MAC_Init();

  XMC_ETH_MAC_SendFrame(&eth_mac, &brd_frame[0], 60, 0);

  while(1)
  {
	if (g_received_frame == true)
	{
	  (buffer[29] & 0x01) == 0 ? XMC_GPIO_SetOutputHigh(ECAT_LED1) : XMC_GPIO_SetOutputLow(ECAT_LED1);
	  (buffer[29] & 0x02) == 0 ? XMC_GPIO_SetOutputHigh(ECAT_LED2) : XMC_GPIO_SetOutputLow(ECAT_LED2);
	  (buffer[29] & 0x04) == 0 ? XMC_GPIO_SetOutputHigh(ECAT_LED3) : XMC_GPIO_SetOutputLow(ECAT_LED3);
	  (buffer[29] & 0x08) == 0 ? XMC_GPIO_SetOutputHigh(ECAT_LED4) : XMC_GPIO_SetOutputLow(ECAT_LED4);
	  (buffer[29] & 0x10) == 0 ? XMC_GPIO_SetOutputHigh(ECAT_LED5) : XMC_GPIO_SetOutputLow(ECAT_LED5);
	  (buffer[29] & 0x20) == 0 ? XMC_GPIO_SetOutputHigh(ECAT_LED6) : XMC_GPIO_SetOutputLow(ECAT_LED6);
	  (buffer[29] & 0x40) == 0 ? XMC_GPIO_SetOutputHigh(ECAT_LED7) : XMC_GPIO_SetOutputLow(ECAT_LED7);
	  (buffer[29] & 0x80) == 0 ? XMC_GPIO_SetOutputHigh(ECAT_LED8) : XMC_GPIO_SetOutputLow(ECAT_LED8);

	  g_received_frame = false;
      XMC_ETH_MAC_SendFrame(&eth_mac, &buffer[0], 60, 0);
	}
  }

}

void ETH_MAC_Init(void)
{
  XMC_ETH_MAC_PORT_CTRL_t port_control;
  XMC_GPIO_CONFIG_t gpio_config;

  gpio_config.mode = XMC_GPIO_MODE_INPUT_TRISTATE;
  XMC_GPIO_Init(ETH_RXD0, &gpio_config);
  XMC_GPIO_Init(ETH_RXD1, &gpio_config);
  XMC_GPIO_Init(ETH_CLK_RMII, &gpio_config);
  XMC_GPIO_Init(ETH_CRS_DV, &gpio_config);
  XMC_GPIO_Init(ETH_RXER, &gpio_config);
  XMC_GPIO_Init(ETH_MDIO, &gpio_config);

  port_control.mode = XMC_ETH_MAC_PORT_CTRL_MODE_RMII;
  port_control.rxd0 = XMC_ETH_MAC_PORT_CTRL_RXD0_P2_2;
  port_control.rxd1 = XMC_ETH_MAC_PORT_CTRL_RXD1_P2_3;
  port_control.clk_rmii = XMC_ETH_MAC_PORT_CTRL_CLK_RMII_P15_8;
  port_control.crs_dv = XMC_ETH_MAC_PORT_CTRL_CRS_DV_P15_9;
  port_control.rxer = XMC_ETH_MAC_PORT_CTRL_RXER_P2_4;
  port_control.mdio = XMC_ETH_MAC_PORT_CTRL_MDIO_P2_0;
  XMC_ETH_MAC_SetPortControl(&eth_mac, port_control);

  XMC_ETH_MAC_Init(&eth_mac);

  XMC_ETH_MAC_DisableJumboFrame(&eth_mac);

  gpio_config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  gpio_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE;
  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P2_8_AF_ETH0_TXD0);
  XMC_GPIO_Init(ETH_TXD0, &gpio_config);

  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P2_9_AF_ETH0_TXD1);
  XMC_GPIO_Init(ETH_TXD1, &gpio_config);

  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P2_5_AF_ETH0_TX_EN);
  XMC_GPIO_Init(ETH_TX_EN, &gpio_config);

  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P2_7_AF_ETH0_MDC);
  XMC_GPIO_Init(ETH_MDC, &gpio_config);

  XMC_GPIO_SetHardwareControl(ETH_MDIO, P2_0_HWCTRL_ETH0_MDO);

  XMC_ETH_PHY_Init(&eth_mac, ETH_PHY_ADDR, &eth_phy_config);

  while(XMC_ETH_PHY_GetLinkStatus(&eth_mac, ETH_PHY_ADDR) != XMC_ETH_LINK_STATUS_UP);

  XMC_ETH_LINK_SPEED_t speed = XMC_ETH_PHY_GetLinkSpeed(&eth_mac, ETH_PHY_ADDR);
  XMC_ETH_LINK_DUPLEX_t duplex = XMC_ETH_PHY_GetLinkDuplex(&eth_mac, ETH_PHY_ADDR);

  XMC_ETH_MAC_SetLink(&eth_mac, speed, duplex);

  /* Enable ethernet interrupts */
  XMC_ETH_MAC_EnableEvent(&eth_mac, XMC_ETH_MAC_EVENT_RECEIVE);

  NVIC_SetPriority(ETH0_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
  NVIC_ClearPendingIRQ(ETH0_0_IRQn);
  NVIC_EnableIRQ(ETH0_0_IRQn);

  XMC_ETH_MAC_EnableTx(&eth_mac);
  XMC_ETH_MAC_EnableRx(&eth_mac);
}

void ECAT_Init(void)
{
  XMC_ECAT_PORT_CTRL_t port_control;
  XMC_ECAT_CONFIG_t ecat_config;
  XMC_GPIO_CONFIG_t gpio_config;

  gpio_config.mode = XMC_GPIO_MODE_INPUT_TRISTATE;
  XMC_GPIO_Init(ECAT_P0_LINK_STATUS, &gpio_config);
  XMC_GPIO_Init(ECAT_P0_RXD3, &gpio_config);
  XMC_GPIO_Init(ECAT_P0_RXD2, &gpio_config);
  XMC_GPIO_Init(ECAT_P0_RXD1, &gpio_config);
  XMC_GPIO_Init(ECAT_P0_RXD0, &gpio_config);
  XMC_GPIO_Init(ECAT_P0_RX_DV, &gpio_config);
  XMC_GPIO_Init(ECAT_P0_RX_CLK, &gpio_config);
  XMC_GPIO_Init(ECAT_P0_RX_ERR, &gpio_config);
  XMC_GPIO_Init(ECAT_P0_TX_CLK, &gpio_config);

  XMC_GPIO_Init(ECAT_P1_LINK_STATUS, &gpio_config);
  XMC_GPIO_Init(ECAT_P1_RXD3, &gpio_config);
  XMC_GPIO_Init(ECAT_P1_RXD2, &gpio_config);
  XMC_GPIO_Init(ECAT_P1_RXD1, &gpio_config);
  XMC_GPIO_Init(ECAT_P1_RXD0, &gpio_config);
  XMC_GPIO_Init(ECAT_P1_RX_DV, &gpio_config);
  XMC_GPIO_Init(ECAT_P1_RX_CLK, &gpio_config);
  XMC_GPIO_Init(ECAT_P1_RX_ERR, &gpio_config);
  XMC_GPIO_Init(ECAT_P1_TX_CLK, &gpio_config);

  XMC_GPIO_Init(ECAT_MDO, &gpio_config);

  port_control.common.mdio = XMC_ECAT_PORT_CTRL_MDIO_P0_12;
  port_control.port0.rxd0 = XMC_ECAT_PORT0_CTRL_RXD0_P5_0;
  port_control.port0.rxd1 = XMC_ECAT_PORT0_CTRL_RXD1_P5_1;
  port_control.port0.rxd2 = XMC_ECAT_PORT0_CTRL_RXD2_P5_2;
  port_control.port0.rxd3 = XMC_ECAT_PORT0_CTRL_RXD3_P5_7;
  port_control.port0.rx_clk = XMC_ECAT_PORT0_CTRL_RX_CLK_P5_4;
  port_control.port0.rx_dv = XMC_ECAT_PORT0_CTRL_RX_DV_P5_6;
  port_control.port0.rx_err = XMC_ECAT_PORT0_CTRL_RX_ERR_P2_6;
  port_control.port0.link = XMC_ECAT_PORT0_CTRL_LINK_P1_15;
  port_control.port0.tx_clk = XMC_ECAT_PORT0_CTRL_TX_CLK_P5_5;
  port_control.port1.rxd0 = XMC_ECAT_PORT1_CTRL_RXD0_P0_11;
  port_control.port1.rxd1 = XMC_ECAT_PORT1_CTRL_RXD1_P0_6;
  port_control.port1.rxd2 = XMC_ECAT_PORT1_CTRL_RXD2_P0_5;
  port_control.port1.rxd3 = XMC_ECAT_PORT1_CTRL_RXD3_P0_4;
  port_control.port1.rx_clk = XMC_ECAT_PORT1_CTRL_RX_CLK_P0_1;
  port_control.port1.rx_dv = XMC_ECAT_PORT1_CTRL_RX_DV_P0_9;
  port_control.port1.rx_err = XMC_ECAT_PORT1_CTRL_RX_ERR_P15_2;
  port_control.port1.link = XMC_ECAT_PORT1_CTRL_LINK_P3_4;
  port_control.port1.tx_clk = XMC_ECAT_PORT1_CTRL_TX_CLK_P0_10;
  XMC_ECAT_SetPortControl(port_control);

  ecat_config.enable_dc_sync_out = false;
  ecat_config.enable_dc_latch_in = false;
  ecat_config.enable_enhanced_link_p0 = true;
  ecat_config.enable_enhanced_link_p1 = true;
  ecat_config.sync_pulse_length = 1000;
  ecat_config.station_alias = 0;
  ecat_config.checksum = 0x88A4;

  XMC_ECAT_Init(&ecat_config);

  gpio_config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  gpio_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE;
  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P6_6_AF_ECAT0_P0_TXD3);
  XMC_GPIO_Init(ECAT_P0_TXD3, &gpio_config);
  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P6_5_AF_ECAT0_P0_TXD2);
  XMC_GPIO_Init(ECAT_P0_TXD2, &gpio_config);
  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P6_4_AF_ECAT0_P0_TXD1);
  XMC_GPIO_Init(ECAT_P0_TXD1, &gpio_config);
  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P6_2_AF_ECAT0_P0_TXD0);
  XMC_GPIO_Init(ECAT_P0_TXD0, &gpio_config);
  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P6_1_AF_ECAT0_P0_TX_ENA);
  XMC_GPIO_Init(ECAT_P0_TX_EN, &gpio_config);
  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P0_3_AF_ECAT0_P1_TXD3);
  XMC_GPIO_Init(ECAT_P1_TXD3, &gpio_config);
  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P0_2_AF_ECAT0_P1_TXD2);
  XMC_GPIO_Init(ECAT_P1_TXD2, &gpio_config);
  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P3_2_AF_ECAT0_P1_TXD1);
  XMC_GPIO_Init(ECAT_P1_TXD1, &gpio_config);
  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P3_1_AF_ECAT0_P1_TXD0);
  XMC_GPIO_Init(ECAT_P1_TXD0, &gpio_config);
  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P3_0_AF_ECAT0_P1_TX_ENA);
  XMC_GPIO_Init(ECAT_P1_TX_EN, &gpio_config);

  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P6_0_AF_ECAT0_PHY_CLK25);
  XMC_GPIO_Init(ECAT_CLK25, &gpio_config);

  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P3_3_AF_ECAT0_MCLK);
  XMC_GPIO_Init(ECAT_MCLK, &gpio_config);

  gpio_config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE;
  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P6_3_AF_ECAT0_P0_LED_LINK_ACT);
  XMC_GPIO_Init(ECAT_P0_LED_LINK_ACT, &gpio_config);

  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P3_12_AF_ECAT0_P1_LED_LINK_ACT);
  XMC_GPIO_Init(ECAT_P1_LED_LINK_ACT, &gpio_config);

  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P0_8_AF_ECAT0_LED_RUN);
  XMC_GPIO_Init(ECAT_LED_RUN, &gpio_config);

  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P0_8_AF_ECAT0_LED_RUN);
  XMC_GPIO_Init(ECAT_LED_ERR, &gpio_config);

  XMC_GPIO_SetHardwareControl(ECAT_MDO, P0_12_HWCTRL_ECAT0_MDO);

  gpio_config.mode = (XMC_GPIO_MODE_t)((uint32_t)XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P0_0_AF_ECAT0_PHY_RESET);
  XMC_GPIO_Init(ECAT_PHY_RESET, &gpio_config);


}

void ETH0_0_IRQHandler(void)
{
  uint32_t status;
  uint32_t len;

  status = XMC_ETH_MAC_GetEventStatus(&eth_mac);

  if (status & XMC_ETH_MAC_EVENT_RECEIVE)
  {
    XMC_ETH_MAC_DisableEvent(&eth_mac, XMC_ETH_MAC_EVENT_RECEIVE);

    len = XMC_ETH_MAC_GetRxFrameSize(&eth_mac);
    XMC_ETH_MAC_ReadFrame(&eth_mac, &buffer[0], len);

    g_received_frame = true;

    XMC_ETH_MAC_EnableEvent(&eth_mac, XMC_ETH_MAC_EVENT_RECEIVE);
  }

  XMC_ETH_MAC_ClearEventStatus(&eth_mac, status);

}

