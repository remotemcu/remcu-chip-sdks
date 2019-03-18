/**
 * \file
 *
 * \brief GMAC (Ethernet MAC) driver for SAM.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef GMAC_RAW_H_INCLUDED
#define GMAC_RAW_H_INCLUDED

#include "compiler.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \brief Input parameters when initializing the gmac module mode.
 */
typedef struct gmac_options {
	/*  Enable/Disable CopyAllFrame */
	uint8_t uc_copy_all_frame;
	/* Enable/Disable NoBroadCast */
	uint8_t uc_no_boardcast;
	/* MAC address */
	uint8_t uc_mac_addr[GMAC_ADDR_LENGTH];
} gmac_options_t;

/** RX callback */
typedef void (*gmac_dev_tx_cb_t) (uint32_t ul_status);
/** Wakeup callback */
typedef void (*gmac_dev_wakeup_cb_t) (void);

typedef struct gmac_queue {

	/**
	 * Pointer to allocated TX buffer.
	 * Section 3.6 of AMBA 2.0 spec states that burst should not cross
	 * 1K Boundaries.
	 * Receive buffer manager writes are burst of 2 words => 3 lsb bits
	 * of the address shall be set to 0.
	 */
	uint8_t *p_tx_buffer;
	/** Pointer to allocated RX buffer */
	uint8_t *p_rx_buffer;
	/** Pointer to Rx TDs (must be 8-byte aligned) */
	gmac_rx_descriptor_t *p_rx_dscr;
	/** Pointer to Tx TDs (must be 8-byte aligned) */
	gmac_tx_descriptor_t *p_tx_dscr;
	/** Optional callback to be invoked once a frame has been received */
	gmac_dev_tx_cb_t func_rx_cb;
	/** Optional callback to be invoked once several TDs have been released */
	gmac_dev_wakeup_cb_t func_wakeup_cb;
	/** Optional callback list to be invoked once TD has been processed */
	gmac_dev_tx_cb_t *func_tx_cb_list;
	/** RX TD list size */
	uint16_t us_rx_list_size;
	/** RX index for current processing TD */
	uint16_t us_rx_idx;
	/** TX TD list size */
	uint16_t us_tx_list_size;
	/** Circular buffer head pointer by upper layer (buffer to be sent) */
	uint16_t us_tx_head;
	/** Circular buffer tail pointer incremented by handlers (buffer sent) */
	uint16_t us_tx_tail;

	/** Number of free TD before wakeup callback is invoked */
	uint8_t uc_wakeup_threshold;
}gmac_queue_t;
/**
 * GMAC driver structure.
 */
typedef struct gmac_device {

	/** Pointer to HW register base */
	Gmac *p_hw;
    /** Base Queue list params **/
    gmac_queue_t gmac_queue_list[GMAC_QUE_N];
} gmac_device_t;

void gmac_dev_init(Gmac* p_gmac, gmac_device_t* p_gmac_dev,
		gmac_options_t* p_opt);
uint32_t gmac_dev_rx_buf_used(gmac_device_t* p_gmac_dev, gmac_quelist_t queue_idx);
uint32_t gmac_dev_read(gmac_device_t* p_gmac_dev, gmac_quelist_t queue_idx, uint8_t* p_frame,
		uint32_t ul_frame_size, uint32_t* p_rcv_size);
uint32_t gmac_dev_tx_buf_used(gmac_device_t* p_gmac_dev, gmac_quelist_t queue_idx);
uint32_t gmac_dev_write(gmac_device_t* p_gmac_dev, gmac_quelist_t queue_idx, void *p_buffer,
		uint32_t ul_size, gmac_dev_tx_cb_t func_tx_cb);
uint32_t gmac_dev_write_nocopy(gmac_device_t* p_gmac_dev, gmac_quelist_t queue_idx,
		uint32_t ul_size, gmac_dev_tx_cb_t func_tx_cb);
uint8_t *gmac_dev_get_tx_buffer(gmac_device_t* p_gmac_dev, gmac_quelist_t queue_idx);
uint32_t gmac_dev_get_tx_load(gmac_device_t* p_gmac_dev, gmac_quelist_t queue_idx);
void gmac_dev_set_rx_callback(gmac_device_t* p_gmac_dev, gmac_quelist_t queue_idx,
		gmac_dev_tx_cb_t func_rx_cb);
uint8_t gmac_dev_set_tx_wakeup_callback(gmac_device_t* p_gmac_dev, gmac_quelist_t queue_idx,
		gmac_dev_wakeup_cb_t func_wakeup, uint8_t uc_threshold);
void gmac_dev_reset(gmac_device_t* p_gmac_dev, gmac_quelist_t queue_idx);
void gmac_handler(gmac_device_t* p_gmac_dev, gmac_quelist_t queue_idx);

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \page gmac_quickstart Quickstart guide for GMAC driver.
 *
 * This is the quickstart guide for the \ref gmac_group "Ethernet MAC",
 * with step-by-step instructions on how to configure and use the driver in a
 * selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section gmac_basic_use_case Basic use case
 * In the basic use case, the GMAC driver are configured for:
 * - PHY component KSZ8061RNB is used
 * - GMAC uses RMII mode
 * - The number of receive buffer is 16
 * - The number of transfer buffer is 8
 * - MAC address is set to 00-04-25-1c-a0-02
 * - IP address is set to 192.168.0.2
 * - Gateway is set to 192.168.0.1
 * - Network mask is 255.255.255.0
 * - PHY operation max retry count is 1000000
 * - GMAC is configured to not support copy all frame and support broadcast
 * - The data will be read from the ethernet
 *
 * \section gmac_basic_use_case_setup Setup steps
 *
 * \subsection gmac_basic_use_case_setup_prereq Prerequisites
 * -# \ref sysclk_group "System Clock Management (sysclock)"
 * -# \ref pmc_group "Power Management Controller (pmc)"
 * -# \ref ksz8061rnb_ethernet_phy_group "PHY component (KSZ8061RNB)"
 *
 * \subsection gmac_basic_use_case_setup_code Example code
 * Content of conf_eth.h
 * \code
 * #define GMAC_RX_BUFFERS                               16
 * #define GMAC_TX_BUFFERS                               8
 * #define MAC_PHY_RETRY_MAX                             1000000
 * #define ETHERNET_CONF_ETHADDR0                        0x00
 * #define ETHERNET_CONF_ETHADDR0                        0x00
 * #define ETHERNET_CONF_ETHADDR1                        0x04
 * #define ETHERNET_CONF_ETHADDR2                        0x25
 * #define ETHERNET_CONF_ETHADDR3                        0x1C
 * #define ETHERNET_CONF_ETHADDR4                        0xA0
 * #define ETHERNET_CONF_ETHADDR5                        0x02
 * #define ETHERNET_CONF_IPADDR0                         192
 * #define ETHERNET_CONF_IPADDR1                         168
 * #define ETHERNET_CONF_IPADDR2                         0
 * #define ETHERNET_CONF_IPADDR3                         2
 * #define ETHERNET_CONF_GATEWAY_ADDR0                   192
 * #define ETHERNET_CONF_GATEWAY_ADDR1                   168
 * #define ETHERNET_CONF_GATEWAY_ADDR2                   0
 * #define ETHERNET_CONF_GATEWAY_ADDR3                   1
 * #define ETHERNET_CONF_NET_MASK0                       255
 * #define ETHERNET_CONF_NET_MASK1                       255
 * #define ETHERNET_CONF_NET_MASK2                       255
 * #define ETHERNET_CONF_NET_MASK3                       0
 * #define ETH_PHY_MODE                                  ETH_PHY_MODE
 * \endcode
 *
 * A specific gmac device and the receive data buffer must be defined; another ul_frm_size should be defined
 * to trace the actual size of the data received.
 * \code
 * static gmac_device_t gs_gmac_dev;
 * static volatile uint8_t gs_uc_eth_buffer[GMAC_FRAME_LENTGH_MAX];
 *
 * uint32_t ul_frm_size;
 * \endcode
 *
 * Add to application C-file:
 * \code
 *   void gmac_init(void)
 *   {
 *       sysclk_init();
 *
 *       board_init();
 *
 *       pmc_enable_periph_clk(ID_GMAC);
 *
 *       gmac_option.uc_copy_all_frame = 0;
 *       gmac_option.uc_no_boardcast = 0;
 *       memcpy(gmac_option.uc_mac_addr, gs_uc_mac_address, sizeof(gs_uc_mac_address));
 *       gs_gmac_dev.p_hw = GMAC;
 *
 *       gmac_dev_init(GMAC, &gs_gmac_dev, &gmac_option);
 *
 *       NVIC_EnableIRQ(GMAC_IRQn);
 *
 *       ethernet_phy_init(GMAC, BOARD_GMAC_PHY_ADDR, sysclk_get_cpu_hz());
 *
 *       ethernet_phy_auto_negotiate(GMAC, BOARD_GMAC_PHY_ADDR);
 *
 *       ethernet_phy_set_link(GMAC, BOARD_GMAC_PHY_ADDR, 1);
 * \endcode
 *
 * \subsection gmac_basic_use_case_setup_flow Workflow
 * -# Ensure that conf_eth.h is present and contains the
 * following configuration symbol. This configuration file is used
 * by the driver and should not be included by the user.
 *   - \code
 *        #define GMAC_RX_BUFFERS                               16
 *        #define GMAC_TX_BUFFERS                               8
 *        #define MAC_PHY_RETRY_MAX                             1000000
 *        #define ETHERNET_CONF_ETHADDR0                        0x00
 *        #define ETHERNET_CONF_ETHADDR0                        0x00
 *        #define ETHERNET_CONF_ETHADDR1                        0x04
 *        #define ETHERNET_CONF_ETHADDR2                        0x25
 *        #define ETHERNET_CONF_ETHADDR3                        0x1C
 *        #define ETHERNET_CONF_ETHADDR4                        0xA0
 *        #define ETHERNET_CONF_ETHADDR5                        0x02
 *        #define ETHERNET_CONF_IPADDR0                         192
 *        #define ETHERNET_CONF_IPADDR1                         168
 *        #define ETHERNET_CONF_IPADDR2                         0
 *        #define ETHERNET_CONF_IPADDR3                         2
 *        #define ETHERNET_CONF_GATEWAY_ADDR0                   192
 *        #define ETHERNET_CONF_GATEWAY_ADDR1                   168
 *        #define ETHERNET_CONF_GATEWAY_ADDR2                   0
 *        #define ETHERNET_CONF_GATEWAY_ADDR3                   1
 *        #define ETHERNET_CONF_NET_MASK0                       255
 *        #define ETHERNET_CONF_NET_MASK1                       255
 *        #define ETHERNET_CONF_NET_MASK2                       255
 *        #define ETHERNET_CONF_NET_MASK3                       0
 *        #define ETH_PHY_MODE                                  GMAC_PHY_MII
 *   \endcode
 * -# Enable the system clock:
 *   - \code sysclk_init(); \endcode
 * -# Enable PIO configurations for GMAC:
 *   - \code board_init(); \endcode
 * -# Enable PMC clock for GMAC:
 *   - \code pmc_enable_periph_clk(ID_GMAC); \endcode
 * -# Set the GMAC options; it's set to copy all frame and support broadcast:
 *   - \code
 *         gmac_option.uc_copy_all_frame = 0;
 *         gmac_option.uc_no_boardcast = 0;
 *         memcpy(gmac_option.uc_mac_addr, gs_uc_mac_address, sizeof(gs_uc_mac_address));
 *         gs_gmac_dev.p_hw = GMAC;
 * \endcode
 * -# Initialize GMAC device with the filled option:
 *   - \code
 *         gmac_dev_init(GMAC, &gs_gmac_dev, &gmac_option);
 * \endcode
 * -# Enable the interrupt service for GMAC:
 *   - \code
 *         NVIC_EnableIRQ(GMAC_IRQn);
 * \endcode
 * -# Initialize the PHY component:
 *   - \code
 *         ethernet_phy_init(GMAC, BOARD_GMAC_PHY_ADDR, sysclk_get_cpu_hz());
 * \endcode
  * -# The link will be established based on auto negotiation.
 *   - \code
 *         ethernet_phy_auto_negotiate(GMAC, BOARD_GMAC_PHY_ADDR);
 * \endcode
 * -# Establish the ethernet link; the network can be worked from now on:
 *   - \code
 *         ethernet_phy_set_link(GMAC, BOARD_GMAC_PHY_ADDR, 1);
 * \endcode
 *
 * \section gmac_basic_use_case_usage Usage steps
 * \subsection gmac_basic_use_case_usage_code Example code
 * Add to, e.g., main loop in application C-file:
 * \code
 *    gmac_dev_read(&gs_gmac_dev, (uint8_t *) gs_uc_eth_buffer, sizeof(gs_uc_eth_buffer), &ul_frm_size));
 * \endcode
 *
 * \subsection gmac_basic_use_case_usage_flow Workflow
 * -# Start reading the data from the ethernet:
 *   - \code gmac_dev_read(&gs_gmac_dev, (uint8_t *) gs_uc_eth_buffer, sizeof(gs_uc_eth_buffer), &ul_frm_size)); \endcode
 */

#endif /* GMAC_RAW_H_INCLUDED */
