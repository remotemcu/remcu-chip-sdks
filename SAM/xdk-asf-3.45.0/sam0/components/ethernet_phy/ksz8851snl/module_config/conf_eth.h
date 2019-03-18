/**
 * \file
 *
 * \brief KSZ8851SNL driver configuration.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef CONF_ETH_H_INCLUDED
#define CONF_ETH_H_INCLUDED

#include <board.h>

/* Disable lwIP checksum (performed by hardware). */
#define CHECKSUM_GEN_IP                               0
#define CHECKSUM_GEN_UDP                              0
#define CHECKSUM_GEN_TCP                              0
#define CHECKSUM_GEN_ICMP                             0
#define CHECKSUM_CHECK_IP                             0
#define CHECKSUM_CHECK_UDP                            0
#define CHECKSUM_CHECK_TCP                            0

/* Number of buffer for RX */
#define NETIF_RX_BUFFERS                              2

/* Number of buffer for TX */
#define NETIF_TX_BUFFERS                              2

/* MAC address definition.  The MAC address must be unique on the network. */
#define ETHERNET_CONF_ETHADDR0                        0x00
#define ETHERNET_CONF_ETHADDR1                        0x04
#define ETHERNET_CONF_ETHADDR2                        0x25
#define ETHERNET_CONF_ETHADDR3                        0x1C
#define ETHERNET_CONF_ETHADDR4                        0xA0
#define ETHERNET_CONF_ETHADDR5                        0x02

/* The IP address being used. */
#define ETHERNET_CONF_IPADDR0                         192
#define ETHERNET_CONF_IPADDR1                         168
#define ETHERNET_CONF_IPADDR2                         0
#define ETHERNET_CONF_IPADDR3                         100

/* The gateway address being used. */
#define ETHERNET_CONF_GATEWAY_ADDR0                   192
#define ETHERNET_CONF_GATEWAY_ADDR1                   168
#define ETHERNET_CONF_GATEWAY_ADDR2                   0
#define ETHERNET_CONF_GATEWAY_ADDR3                   250

/* The network mask being used. */
#define ETHERNET_CONF_NET_MASK0                       255
#define ETHERNET_CONF_NET_MASK1                       255
#define ETHERNET_CONF_NET_MASK2                       255
#define ETHERNET_CONF_NET_MASK3                       0

#ifdef EXT1_SPI_MODULE
/* Interface configuration for SAM Xplained Pro */
#  define KSZ8851SNL_SPI                                EXT1_SPI_MODULE
#  define KSZ8851SNL_SPI_IRQn                           SERCOM0_IRQn

/* Pins configuration. */
#  define KSZ8851SNL_RSTN_PIN                           EXT1_PIN_6
#  define KSZ8851SNL_CS_PIN                             EXT1_PIN_15
#  define KSZ8851SNL_INTN_EIC_CHANNEL                   EXT1_IRQ_INPUT
#  define KSZ8851SNL_INTN_EIC_PIN                       EXT1_IRQ_PIN
#  define KSZ8851SNL_INTN_EIC_PIN_MUX                   EXT1_IRQ_PINMUX

/* SPI settings. */
#  define KSZ8851SNL_SPI_PINMUX_SETTING                 EXT1_SPI_SERCOM_MUX_SETTING
#  define KSZ8851SNL_SPI_PINMUX_PAD0                    EXT1_SPI_SERCOM_PINMUX_PAD0
#  define KSZ8851SNL_SPI_PINMUX_PAD1                    PINMUX_UNUSED
#  define KSZ8851SNL_SPI_PINMUX_PAD2                    EXT1_SPI_SERCOM_PINMUX_PAD2
#  define KSZ8851SNL_SPI_PINMUX_PAD3                    EXT1_SPI_SERCOM_PINMUX_PAD3

#else
/* Dummy configuration */
#  define KSZ8851SNL_SPI                                0
#  define KSZ8851SNL_SPI_IRQn                           0

/* Pins configuration. */
#  define KSZ8851SNL_RSTN_PIN                           0
#  define KSZ8851SNL_CS_PIN                             0
#  define KSZ8851SNL_INTN_EIC_CHANNEL                   0
#  define KSZ8851SNL_INTN_EIC_PIN                       0
#  define KSZ8851SNL_INTN_EIC_PIN_MUX                   0

/* SPI settings. */
#  define KSZ8851SNL_SPI_PINMUX_SETTING                 0
#  define KSZ8851SNL_SPI_PINMUX_PAD0                    0
#  define KSZ8851SNL_SPI_PINMUX_PAD1                    0
#  define KSZ8851SNL_SPI_PINMUX_PAD2                    0
#  define KSZ8851SNL_SPI_PINMUX_PAD3                    0
#endif

/* Minimum clock period is 50ns@3.3V -> max frequency is 20MHz
 * Warning SAMD20 revision D (and below) has a limitation on pad speed -> max frequency is 10MHz
 */
#define KSZ8851SNL_CLOCK_SPEED                        10000000UL

/* Interrupt priorities. (lowest value = highest priority)
 * ISRs using FreeRTOS *FromISR APIs must have priorities below or equal to
 * configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#define INT_PRIORITY_SPI                              12
#define INT_PRIORITY_PIO                              12

#endif /* CONF_ETH_H_INCLUDED */
